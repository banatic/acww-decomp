/* The DS 3D hardware; see gpu3d.h. Arithmetic follows GBATEK's "DS 3D" chapters: matrices
 * are 1.19.12 fixed point multiplied in 64 bits and truncated with an arithmetic shift,
 * vertices 1.3.12, normals and light vectors 1.0.9, texture coordinates 1.11.4, colours
 * 5 bits per component expanded to 6 for blending. Where GBATEK does not say how the hardware
 * rounds (clipping, the rasteriser's edge and span interpolation), this file uses one
 * documented rule throughout so that the same command stream always gives the same frame. */
#include "gpu3d.h"

#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "frame.h"
#include "io.h"
#include "render.h"

#define SCREEN_W 256
#define SCREEN_H 192
#define VERTEX_RAM 6144
#define POLYGON_RAM 2048
#define MAX_POLY_VERTICES 10 /* a quad clipped against six planes */
#define FIFO_SIZE 65536      /* entries the model can hold while SWAP_BUFFERS stalls the engine */
#define FIFO_HW 256          /* the hardware FIFO's depth, as GXSTAT reports it */

/* A CPU vertex in clip space, carrying the attributes the rasteriser interpolates. */
typedef struct ClipVertex {
    int32_t x, y, z, w; /* 1.19.12 clip coordinates */
    int32_t r, g, b;    /* 5-bit vertex colour */
    int32_t s, t;       /* 1.11.4 texture coordinates, after the transformation mode */
} ClipVertex;

/* A vertex of the rendering engine's list: clip coordinates kept for the depth value, screen
 * position after the viewport transformation. */
typedef struct Vertex {
    int32_t x, y, z, w;
    int32_t sx, sy;  /* integer screen pixel */
    int32_t r, g, b; /* 6-bit colour (GBATEK's 5-to-6 expansion) */
    int32_t s, t;
    int32_t depth; /* 24-bit z (Z-buffering) or w (W-buffering) */
    uint32_t w16;  /* w reduced to 16 bits for perspective interpolation */
} Vertex;

typedef struct Polygon {
    int count;
    Vertex v[MAX_POLY_VERTICES];
    uint32_t attr, texparam, pltt;
    int translucent; /* alpha 1-30 or an A3I5 / A5I3 texture: rendered in the second pass */
    int ytop, ybot;  /* screen rows, ybot exclusive (ytop == ybot: a one-line polygon) */
    int order;       /* submission index, to keep the sort stable */
} Polygon;

/* The two polygon lists: the geometry engine fills one while the other is rendered. */
typedef struct PolygonList {
    Polygon *poly;
    int polygons, vertices; /* the RAM_COUNT values */
    int wbuffer, manual_sort;
} PolygonList;

/* Geometry engine state --------------------------------------------------------------------- */

static struct {
    /* the command FIFO: 40-bit entries (command, parameter) */
    uint8_t *fifo_cmd;
    uint32_t *fifo_param;
    int fifo_head, fifo_count;
    int fifo_tests;   /* BOX/POS/VEC_TEST commands waiting in the FIFO (GXSTAT bit 0) */
    int fifo_partial; /* parameters the newest FIFO command still waits for */
    /* packed-command decoding of writes to 0x400 */
    uint32_t packed;
    int packed_remaining, packed_params, packed_total;

    int mode;
    int32_t proj[16], pos[16], vec[16], tex[16], clip[16];
    int32_t proj_stack[16], pos_stack[32][16], vec_stack[32][16], tex_stack[16];
    int proj_sp, pos_sp, tex_sp;
    int stack_error;

    int32_t vx, vy, vz;   /* the current vertex, 16-bit components */
    int32_t cr, cg, cb;   /* the current vertex colour, 5 bits each */
    int32_t raw_s, raw_t; /* the last TEXCOORD */
    int32_t s, t;         /* texture coordinates after transformation */
    int32_t normal[3];
    uint32_t polyattr, polyattr_next, texparam, pltt;
    int32_t light_dir[4][3], light_color[4][3];
    int32_t dif[3], amb[3], spe[3], emi[3];
    int use_shininess;
    uint8_t shininess[128];
    uint32_t viewport;

    int in_vtxs, primitive, strip_count;
    ClipVertex strip[4]; /* the vertices of the polygon being assembled */

    int swap_pending;
    uint32_t swap_param, swap_param_next;
    int box_result;
    int32_t pos_result[4];
    int32_t vec_result[3];
} ge;

static PolygonList lists[2];
static int geometry_list; /* the list the geometry engine writes; the other is rendered */

/* Counters for the report. */
static uint64_t count_commands, count_polygons, count_dropped, count_swaps, count_frames, count_fifo_lost;
static double render_seconds;
static int trace_gx; /* RUN_TRACE contains "gx": a line per rendered list on stderr */

static int sign_extend(uint32_t v, int bits)
{
    return (int) (v << (32 - bits)) >> (32 - bits);
}

/* Matrices ---------------------------------------------------------------------------------- */

static const int32_t identity[16] = {0x1000, 0, 0, 0, 0, 0x1000, 0, 0, 0, 0, 0x1000, 0, 0, 0, 0, 0x1000};

/* C = M * C for 4x4 M: each result element is a 64-bit sum of four products, truncated. */
static void matrix_mult(int32_t *c, const int32_t *m)
{
    int32_t old[16];
    memcpy(old, c, sizeof(old));
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            int64_t sum = (int64_t) m[row * 4 + 0] * old[0 * 4 + col] + (int64_t) m[row * 4 + 1] * old[1 * 4 + col] +
                          (int64_t) m[row * 4 + 2] * old[2 * 4 + col] + (int64_t) m[row * 4 + 3] * old[3 * 4 + col];
            c[row * 4 + col] = (int32_t) (sum >> 12);
        }
    }
}

static void matrix_scale(int32_t *c, const int32_t *s)
{
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 4; col++) {
            c[row * 4 + col] = (int32_t) (((int64_t) c[row * 4 + col] * s[row]) >> 12);
        }
    }
}

static void matrix_translate(int32_t *c, const int32_t *t)
{
    for (int col = 0; col < 4; col++) {
        int64_t sum = (int64_t) t[0] * c[0 * 4 + col] + (int64_t) t[1] * c[1 * 4 + col] + (int64_t) t[2] * c[2 * 4 + col];
        c[3 * 4 + col] += (int32_t) (sum >> 12);
    }
}

/* The 4x3 and 3x3 parameter layouts expanded to 4x4 (GBATEK, "DS 3D Matrix Types"). */
static void expand_4x3(const uint32_t *p, int32_t *m)
{
    for (int row = 0; row < 4; row++) {
        m[row * 4 + 0] = (int32_t) p[row * 3 + 0];
        m[row * 4 + 1] = (int32_t) p[row * 3 + 1];
        m[row * 4 + 2] = (int32_t) p[row * 3 + 2];
        m[row * 4 + 3] = row == 3 ? 0x1000 : 0;
    }
}

static void expand_3x3(const uint32_t *p, int32_t *m)
{
    memcpy(m, identity, sizeof(identity));
    for (int row = 0; row < 3; row++) {
        m[row * 4 + 0] = (int32_t) p[row * 3 + 0];
        m[row * 4 + 1] = (int32_t) p[row * 3 + 1];
        m[row * 4 + 2] = (int32_t) p[row * 3 + 2];
    }
}

static void update_clip_matrix(void)
{
    memcpy(ge.clip, ge.proj, sizeof(ge.clip));
    matrix_mult(ge.clip, ge.pos);
}

/* The matrices a command in the current mode applies to; the stack commands treat mode 1 as
 * mode 2 and MTX_SCALE treats mode 2 as mode 1 (GBATEK, "DS 3D Matrix Load/Multiply"). */
static void for_current(void (*op)(int32_t *, const int32_t *), const int32_t *arg, int scale)
{
    switch (ge.mode) {
        case 0:
            op(ge.proj, arg);
            update_clip_matrix();
            break;
        case 1:
            op(ge.pos, arg);
            update_clip_matrix();
            break;
        case 2:
            op(ge.pos, arg);
            if (!scale) {
                op(ge.vec, arg);
            }
            update_clip_matrix();
            break;
        default:
            op(ge.tex, arg);
            break;
    }
}

static void matrix_load(int32_t *c, const int32_t *m)
{
    memcpy(c, m, 16 * sizeof(int32_t));
}

static void matrix_push(void)
{
    if (ge.mode == 0) {
        if (ge.proj_sp > 0) {
            ge.stack_error = 1;
        }
        memcpy(ge.proj_stack, ge.proj, sizeof(ge.proj));
        ge.proj_sp = (ge.proj_sp + 1) & 1;
    } else if (ge.mode == 3) {
        if (ge.tex_sp > 0) {
            ge.stack_error = 1;
        }
        memcpy(ge.tex_stack, ge.tex, sizeof(ge.tex));
        ge.tex_sp = (ge.tex_sp + 1) & 1;
    } else {
        if (ge.pos_sp > 30) {
            ge.stack_error = 1; /* entry 31 exists but is an error to touch */
        }
        memcpy(ge.pos_stack[ge.pos_sp & 31], ge.pos, sizeof(ge.pos));
        memcpy(ge.vec_stack[ge.pos_sp & 31], ge.vec, sizeof(ge.vec));
        ge.pos_sp = (ge.pos_sp + 1) & 63;
    }
}

static void matrix_pop(uint32_t param)
{
    if (ge.mode == 0) {
        ge.proj_sp = (ge.proj_sp - 1) & 1;
        if (ge.proj_sp > 0) {
            ge.stack_error = 1;
        }
        memcpy(ge.proj, ge.proj_stack, sizeof(ge.proj));
        update_clip_matrix();
    } else if (ge.mode == 3) {
        ge.tex_sp = (ge.tex_sp - 1) & 1;
        if (ge.tex_sp > 0) {
            ge.stack_error = 1;
        }
        memcpy(ge.tex, ge.tex_stack, sizeof(ge.tex));
    } else {
        ge.pos_sp = (ge.pos_sp - sign_extend(param, 6)) & 63;
        if (ge.pos_sp > 30) {
            ge.stack_error = 1;
        }
        memcpy(ge.pos, ge.pos_stack[ge.pos_sp & 31], sizeof(ge.pos));
        memcpy(ge.vec, ge.vec_stack[ge.pos_sp & 31], sizeof(ge.vec));
        update_clip_matrix();
    }
}

static void matrix_store(uint32_t param)
{
    if (ge.mode == 0) {
        memcpy(ge.proj_stack, ge.proj, sizeof(ge.proj));
    } else if (ge.mode == 3) {
        memcpy(ge.tex_stack, ge.tex, sizeof(ge.tex));
    } else {
        uint32_t n = param & 31;
        if (n == 31) {
            ge.stack_error = 1;
        }
        memcpy(ge.pos_stack[n], ge.pos, sizeof(ge.pos));
        memcpy(ge.vec_stack[n], ge.vec, sizeof(ge.vec));
    }
}

static void matrix_restore(uint32_t param)
{
    if (ge.mode == 0) {
        memcpy(ge.proj, ge.proj_stack, sizeof(ge.proj));
        update_clip_matrix();
    } else if (ge.mode == 3) {
        memcpy(ge.tex, ge.tex_stack, sizeof(ge.tex));
    } else {
        uint32_t n = param & 31;
        if (n == 31) {
            ge.stack_error = 1;
        }
        memcpy(ge.pos, ge.pos_stack[n], sizeof(ge.pos));
        memcpy(ge.vec, ge.vec_stack[n], sizeof(ge.vec));
        update_clip_matrix();
    }
}

/* Lighting ---------------------------------------------------------------------------------- */

/* A 1.0.9 vector (three 10-bit fields) through the 3x3 part of the vector matrix: the result
 * keeps 9 fractional bits, so a unit vector stays near 512. */
static void transform_vector(uint32_t param, int32_t *out)
{
    int32_t v[3] = {sign_extend(param & 0x3ff, 10), sign_extend((param >> 10) & 0x3ff, 10),
                    sign_extend((param >> 20) & 0x3ff, 10)};
    for (int col = 0; col < 3; col++) {
        int64_t sum =
            (int64_t) v[0] * ge.vec[0 * 4 + col] + (int64_t) v[1] * ge.vec[1 * 4 + col] + (int64_t) v[2] * ge.vec[2 * 4 + col];
        out[col] = (int32_t) (sum >> 12);
    }
}

static void set_light_vector(uint32_t param)
{
    transform_vector(param, ge.light_dir[param >> 30]);
}

/* NORMAL: the vertex colour from the four lights (GBATEK, "DS 3D Polygon Light Parameters").
 * Levels are 0..255 fractions; the products of 5-bit colours are reduced back to 5 bits. */
static void set_normal(uint32_t param)
{
    int32_t n[3];
    if ((ge.texparam >> 30) == 2) {
        /* normal-source texture coordinates: the untransformed normal through the texture
           matrix; the 9+12 fractional bits are dropped entirely, the SDK scales the matrix
           by 16 so the result lands in 1.11.4 */
        int32_t raw[3] = {sign_extend(param & 0x3ff, 10), sign_extend((param >> 10) & 0x3ff, 10),
                          sign_extend((param >> 20) & 0x3ff, 10)};
        int64_t s = (int64_t) raw[0] * ge.tex[0] + (int64_t) raw[1] * ge.tex[4] + (int64_t) raw[2] * ge.tex[8];
        int64_t t = (int64_t) raw[0] * ge.tex[1] + (int64_t) raw[1] * ge.tex[5] + (int64_t) raw[2] * ge.tex[9];
        ge.s = (int16_t) (ge.raw_s + (int32_t) (s >> 21));
        ge.t = (int16_t) (ge.raw_t + (int32_t) (t >> 21));
    }
    transform_vector(param, n);
    memcpy(ge.normal, n, sizeof(n));
    int32_t color[3] = {ge.emi[0], ge.emi[1], ge.emi[2]};
    for (int i = 0; i < 4; i++) {
        if ((ge.polyattr & (1u << i)) == 0) {
            continue;
        }
        const int32_t *l = ge.light_dir[i];
        int32_t diffuse = (int32_t) (-((int64_t) l[0] * n[0] + (int64_t) l[1] * n[1] + (int64_t) l[2] * n[2]) >> 10);
        if (diffuse < 0) {
            diffuse = 0;
        } else if (diffuse > 255) {
            diffuse = 255;
        }
        /* the half vector between the light and the line of sight (0,0,-1), unnormalised */
        int32_t shine = -(
            int32_t) (((int64_t) (l[0] >> 1) * n[0] + (int64_t) (l[1] >> 1) * n[1] + (int64_t) ((l[2] - 0x200) >> 1) * n[2]) >>
                      10);
        if (shine < 0) {
            shine = 0;
        } else if (shine > 255) {
            shine = (0x100 - shine) & 0xff; /* the hardware keeps 8 bits of an overflow */
        }
        shine = ((shine * shine) >> 7) - 0x100; /* the hardware's 2cos^2-1 approximation */
        if (shine < 0) {
            shine = 0;
        }
        if (ge.use_shininess) {
            shine = ge.shininess[shine >> 1];
        }
        for (int c = 0; c < 3; c++) {
            int32_t lc = ge.light_color[i][c];
            color[c] += (ge.spe[c] * lc * shine) >> 13;
            color[c] += (ge.dif[c] * lc * diffuse) >> 13;
            color[c] += (ge.amb[c] * lc) >> 5;
            if (color[c] > 31) {
                color[c] = 31;
            }
        }
    }
    ge.cr = color[0];
    ge.cg = color[1];
    ge.cb = color[2];
}

/* Texture coordinates ----------------------------------------------------------------------- */

static void set_texcoord(uint32_t param)
{
    ge.raw_s = (int16_t) (param & 0xffff);
    ge.raw_t = (int16_t) (param >> 16);
    if ((ge.texparam >> 30) == 1) {
        /* texcoord source: (s t 1/16 1/16) through the first two columns, 4+12 fractional
           bits back to 4; the 1/16 constants make m[8] and m[12] plain additions */
        int64_t s = (int64_t) ge.raw_s * ge.tex[0] + (int64_t) ge.raw_t * ge.tex[4] + ge.tex[8] + ge.tex[12];
        int64_t t = (int64_t) ge.raw_s * ge.tex[1] + (int64_t) ge.raw_t * ge.tex[5] + ge.tex[9] + ge.tex[13];
        ge.s = (int16_t) (s >> 12);
        ge.t = (int16_t) (t >> 12);
    } else {
        ge.s = ge.raw_s;
        ge.t = ge.raw_t;
    }
}

/* Vertices, clipping and the polygon list --------------------------------------------------- */

static void box_or_polygon_overflow(void)
{
    /* DISP3DCNT bit 13: polygon/vertex RAM overflow. The register lives in io.c, which
       clears the flag when the game writes 1 to it. */
    io_reg_store(0x060, io_reg(0x04000060) | (1u << 13));
}

/* The intersection of edge a-b with a clip plane, where `da` (>= 0) and `db` (< 0) are the
 * signed distances of the ends from the plane in clip units. Attributes follow linearly. */
static ClipVertex clip_intersect(const ClipVertex *a, const ClipVertex *b, int64_t da, int64_t db)
{
    ClipVertex r;
    int64_t den = da - db;
#define LERP(f) r.f = (int32_t) (a->f + ((int64_t) (b->f - a->f) * da) / den)
    LERP(x);
    LERP(y);
    LERP(z);
    LERP(w);
    LERP(r);
    LERP(g);
    LERP(b);
    LERP(s);
    LERP(t);
#undef LERP
    return r;
}

/* Sutherland-Hodgman against one plane: component `axis` (0 x, 1 y, 2 z) must satisfy
 * c <= w (`side` +1) or c >= -w (`side` -1). Returns the new vertex count. */
static int clip_plane(ClipVertex *in, int n, int axis, int side, ClipVertex *out)
{
    int m = 0;
    for (int i = 0; i < n; i++) {
        const ClipVertex *a = &in[i], *b = &in[(i + 1) % n];
        int32_t ca = axis == 0 ? a->x : axis == 1 ? a->y : a->z;
        int32_t cb = axis == 0 ? b->x : axis == 1 ? b->y : b->z;
        int64_t da = side > 0 ? (int64_t) a->w - ca : (int64_t) a->w + ca;
        int64_t db = side > 0 ? (int64_t) b->w - cb : (int64_t) b->w + cb;
        if (da >= 0) {
            out[m++] = *a;
        }
        if ((da >= 0) != (db >= 0)) {
            /* the edge crosses the plane: the intersection joins the output */
            if (da >= 0) {
                out[m++] = clip_intersect(a, b, da, db);
            } else {
                out[m++] = clip_intersect(b, a, db, da);
            }
        }
    }
    return m;
}

static int32_t clamp_i32(int64_t v, int32_t lo, int32_t hi)
{
    return v < lo ? lo : v > hi ? hi : (int32_t) v;
}

static int32_t expand6(int32_t c5)
{
    return c5 ? c5 * 2 + 1 : 0;
}

/* The highest set bit position + 1 of an unsigned value. */
static int bit_width(uint32_t v)
{
    int n = 0;
    while (v) {
        n++;
        v >>= 1;
    }
    return n;
}

/* A complete polygon in clip space: culling, clipping, the viewport transformation, then the
 * polygon and vertex RAM of the geometry engine's list. */
static void submit_polygon(ClipVertex *cv, int n)
{
    PolygonList *list = &lists[geometry_list];
    uint32_t attr = ge.polyattr;
    count_polygons++;

    /* Facing: the sign of the (x, y, w) triple product of the first three vertices, which is
       the screen winding without a division. A zero (a line segment) is always rendered. */
    int64_t ax = (int64_t) cv[1].x - cv[0].x, ay = (int64_t) cv[1].y - cv[0].y, aw = (int64_t) cv[1].w - cv[0].w;
    int64_t bx = (int64_t) cv[2].x - cv[0].x, by = (int64_t) cv[2].y - cv[0].y, bw = (int64_t) cv[2].w - cv[0].w;
    int64_t nx = ay * bw - aw * by, ny = aw * bx - ax * bw, nz = ax * by - ay * bx;
    while ((nx != (int32_t) nx) || (ny != (int32_t) ny) || (nz != (int32_t) nz)) {
        nx >>= 4;
        ny >>= 4;
        nz >>= 4;
    }
    int64_t dot = nx * cv[0].x + ny * cv[0].y + nz * cv[0].w;
    if (dot > 0 && (attr & (1u << 7)) == 0) {
        return; /* a front face, hidden */
    }
    if (dot < 0 && (attr & (1u << 6)) == 0) {
        return; /* a back face, hidden */
    }

    /* Far-plane intersecting polygons are dropped unless attribute bit 12 allows clipping. */
    int outside = 0;
    for (int i = 0; i < n; i++) {
        if (cv[i].z > cv[i].w && (attr & (1u << 12)) == 0) {
            return;
        }
        if (cv[i].x < -cv[i].w || cv[i].x > cv[i].w || cv[i].y < -cv[i].w || cv[i].y > cv[i].w || cv[i].z < -cv[i].w ||
            cv[i].z > cv[i].w) {
            outside = 1;
        }
    }
    ClipVertex a[MAX_POLY_VERTICES], b[MAX_POLY_VERTICES];
    memcpy(a, cv, (size_t) n * sizeof(ClipVertex));
    if (outside) {
        n = clip_plane(a, n, 2, +1, b);
        n = clip_plane(b, n, 2, -1, a);
        n = clip_plane(a, n, 1, +1, b);
        n = clip_plane(b, n, 1, -1, a);
        n = clip_plane(a, n, 0, +1, b);
        n = clip_plane(b, n, 0, -1, a);
        if (n < 3) {
            return; /* nothing of it is in the view volume */
        }
    }
    if (list->polygons >= POLYGON_RAM || list->vertices + n > VERTEX_RAM) {
        box_or_polygon_overflow();
        count_dropped++;
        return;
    }

    Polygon *p = &list->poly[list->polygons];
    memset(p, 0, sizeof(*p));
    p->count = n;
    p->attr = attr;
    p->texparam = ge.texparam;
    p->pltt = ge.pltt;
    p->order = list->polygons;
    uint32_t alpha = (attr >> 16) & 31, format = (ge.texparam >> 26) & 7;
    p->translucent = (alpha > 0 && alpha < 31) || format == 1 || format == 6;

    /* The viewport: X1,Y1 are the lower-left corner in 3D terms, Y2 the top. */
    int32_t vx1 = ge.viewport & 0xff, vy1 = (ge.viewport >> 8) & 0xff, vx2 = (ge.viewport >> 16) & 0xff,
            vy2 = ge.viewport >> 24;
    int32_t vw = vx2 - vx1 + 1, vh = vy2 - vy1 + 1, vtop = 191 - vy2;
    uint32_t wmax = 0;
    p->ytop = SCREEN_H;
    p->ybot = 0;
    for (int i = 0; i < n; i++) {
        Vertex *v = &p->v[i];
        v->x = a[i].x;
        v->y = a[i].y;
        v->z = a[i].z;
        v->w = a[i].w;
        v->r = expand6(clamp_i32(a[i].r, 0, 31));
        v->g = expand6(clamp_i32(a[i].g, 0, 31));
        v->b = expand6(clamp_i32(a[i].b, 0, 31));
        v->s = a[i].s;
        v->t = a[i].t;
        int64_t w = v->w;
        if (w <= 0) {
            /* only a degenerate polygon reaches here (every clipped vertex has w >= |z|) */
            v->sx = vx1;
            v->sy = vtop;
            v->depth = 0;
            v->w = 1;
        } else {
            /* x == w maps to vx2 + 1 and y == -w to 192: the right and bottom edges of a
               polygon are not drawn, so a full-screen polygon covers exactly 256 x 192 */
            v->sx = clamp_i32(((int64_t) (v->x + w) * vw) / (w * 2) + vx1, 0, SCREEN_W);
            v->sy = clamp_i32(((int64_t) (-v->y + w) * vh) / (w * 2) + vtop, 0, SCREEN_H);
            if (list->wbuffer) {
                v->depth = (int32_t) (w & 0xffffff);
            } else {
                /* GBATEK: Z = ((Z * 0x4000 / W) + 0x3FFF) * 0x200, within 24 bits */
                v->depth = clamp_i32((((int64_t) v->z * 0x4000) / w + 0x3fff) * 0x200, 0, 0xffffff);
            }
        }
        if ((uint32_t) v->w > wmax) {
            wmax = (uint32_t) v->w;
        }
        if (v->sy < p->ytop) {
            p->ytop = v->sy;
        }
        if (v->sy > p->ybot) {
            p->ybot = v->sy;
        }
    }
    /* w reduced to 16 bits for the interpolators, the same shift for every vertex */
    int shift = bit_width(wmax) - 16;
    if (shift < 0) {
        shift = 0;
    }
    for (int i = 0; i < n; i++) {
        p->v[i].w16 = ((uint32_t) p->v[i].w >> shift);
        if (p->v[i].w16 == 0) {
            p->v[i].w16 = 1;
        }
    }
    list->polygons++;
    list->vertices += n;
}

/* The current vertex through the clip matrix, with the current attributes. */
static void submit_vertex(void)
{
    if (!ge.in_vtxs) {
        return;
    }
    ClipVertex v;
    int64_t x = ge.vx, y = ge.vy, z = ge.vz;
    const int32_t *m = ge.clip;
    v.x = (int32_t) ((x * m[0] + y * m[4] + z * m[8] + (int64_t) 0x1000 * m[12]) >> 12);
    v.y = (int32_t) ((x * m[1] + y * m[5] + z * m[9] + (int64_t) 0x1000 * m[13]) >> 12);
    v.z = (int32_t) ((x * m[2] + y * m[6] + z * m[10] + (int64_t) 0x1000 * m[14]) >> 12);
    v.w = (int32_t) ((x * m[3] + y * m[7] + z * m[11] + (int64_t) 0x1000 * m[15]) >> 12);
    v.r = ge.cr;
    v.g = ge.cg;
    v.b = ge.cb;
    if ((ge.texparam >> 30) == 3) {
        /* vertex-source texture coordinates: the 12+12 fractional bits are dropped, the
           matrix again carries the factor 16 */
        int64_t s = x * ge.tex[0] + y * ge.tex[4] + z * ge.tex[8];
        int64_t t = x * ge.tex[1] + y * ge.tex[5] + z * ge.tex[9];
        v.s = (int16_t) (ge.raw_s + (int32_t) (s >> 24));
        v.t = (int16_t) (ge.raw_t + (int32_t) (t >> 24));
    } else {
        v.s = ge.s;
        v.t = ge.t;
    }

    switch (ge.primitive) {
        case 0: /* separate triangles */
            ge.strip[ge.strip_count++] = v;
            if (ge.strip_count == 3) {
                submit_polygon(ge.strip, 3);
                ge.strip_count = 0;
            }
            break;
        case 1: /* separate quads */
            ge.strip[ge.strip_count++] = v;
            if (ge.strip_count == 4) {
                submit_polygon(ge.strip, 4);
                ge.strip_count = 0;
            }
            break;
        case 2: /* triangle strips: strip[0..2] hold the last three vertices; every second
                   triangle has its first two swapped so that the winding stays consistent */
            if (ge.strip_count < 3) {
                ge.strip[ge.strip_count] = v;
            } else {
                ge.strip[0] = ge.strip[1];
                ge.strip[1] = ge.strip[2];
                ge.strip[2] = v;
            }
            ge.strip_count++;
            if (ge.strip_count >= 3) {
                int odd = (ge.strip_count - 3) & 1;
                ClipVertex tri[3] = {ge.strip[odd ? 1 : 0], ge.strip[odd ? 0 : 1], ge.strip[2]};
                submit_polygon(tri, 3);
            }
            break;
        default: /* quad strips: v0 v1 v3 v2, then each new pair with the previous pair */
            ge.strip[ge.strip_count++] = v;
            if (ge.strip_count == 4) {
                ClipVertex quad[4] = {ge.strip[0], ge.strip[1], ge.strip[3], ge.strip[2]};
                submit_polygon(quad, 4);
                ge.strip[0] = ge.strip[2];
                ge.strip[1] = ge.strip[3];
                ge.strip_count = 2;
            }
            break;
    }
}

/* Tests ------------------------------------------------------------------------------------- */

static void transform_point(int32_t x, int32_t y, int32_t z, int32_t *out)
{
    const int32_t *m = ge.clip;
    for (int col = 0; col < 4; col++) {
        out[col] = (int32_t) (((int64_t) x * m[col] + (int64_t) y * m[4 + col] + (int64_t) z * m[8 + col] +
                               (int64_t) 0x1000 * m[12 + col]) >>
                              12);
    }
}

static void box_test(const uint32_t *p)
{
    int32_t x0 = (int16_t) (p[0] & 0xffff), y0 = (int16_t) (p[0] >> 16), z0 = (int16_t) (p[1] & 0xffff);
    int32_t x1 = (int16_t) (x0 + (int16_t) (p[1] >> 16)), y1 = (int16_t) (y0 + (int16_t) (p[2] & 0xffff)),
            z1 = (int16_t) (z0 + (int16_t) (p[2] >> 16));
    ClipVertex corner[8];
    for (int i = 0; i < 8; i++) {
        int32_t c[4];
        transform_point((i & 1) ? x1 : x0, (i & 2) ? y1 : y0, (i & 4) ? z1 : z0, c);
        memset(&corner[i], 0, sizeof(corner[i]));
        corner[i].x = c[0];
        corner[i].y = c[1];
        corner[i].z = c[2];
        corner[i].w = c[3];
    }
    static const int faces[6][4] = {{0, 1, 3, 2}, {4, 5, 7, 6}, {0, 1, 5, 4}, {2, 3, 7, 6}, {0, 2, 6, 4}, {1, 3, 7, 5}};
    ge.box_result = 0;
    for (int f = 0; f < 6 && !ge.box_result; f++) {
        ClipVertex a[MAX_POLY_VERTICES], b[MAX_POLY_VERTICES];
        for (int i = 0; i < 4; i++) {
            a[i] = corner[faces[f][i]];
        }
        int n = 4;
        n = clip_plane(a, n, 2, +1, b);
        n = clip_plane(b, n, 2, -1, a);
        n = clip_plane(a, n, 1, +1, b);
        n = clip_plane(b, n, 1, -1, a);
        n = clip_plane(a, n, 0, +1, b);
        n = clip_plane(b, n, 0, -1, a);
        if (n > 0) {
            ge.box_result = 1;
        }
    }
}

static void pos_test(const uint32_t *p)
{
    /* POS_TEST replaces the current vertex, as on the hardware */
    ge.vx = (int16_t) (p[0] & 0xffff);
    ge.vy = (int16_t) (p[0] >> 16);
    ge.vz = (int16_t) (p[1] & 0xffff);
    transform_point(ge.vx, ge.vy, ge.vz, ge.pos_result);
}

static void vec_test(uint32_t param)
{
    int32_t v[3] = {sign_extend(param & 0x3ff, 10), sign_extend((param >> 10) & 0x3ff, 10),
                    sign_extend((param >> 20) & 0x3ff, 10)};
    for (int col = 0; col < 3; col++) {
        int64_t sum = (int64_t) v[0] * ge.vec[col] + (int64_t) v[1] * ge.vec[4 + col] + (int64_t) v[2] * ge.vec[8 + col];
        /* 9+12 fractional bits to 12; 13 significant bits, the top one the sign */
        ge.vec_result[col] = sign_extend((uint32_t) (sum >> 9) & 0x1fff, 13);
    }
}

/* Command execution ------------------------------------------------------------------------- */

static const uint8_t param_count[0x80] = {
    [0x10] = 1, [0x11] = 0, [0x12] = 1, [0x13] = 1, [0x14] = 1, [0x15] = 0, [0x16] = 16, [0x17] = 12, [0x18] = 16, [0x19] = 12,
    [0x1a] = 9, [0x1b] = 3, [0x1c] = 3, [0x20] = 1, [0x21] = 1, [0x22] = 1, [0x23] = 2,  [0x24] = 1,  [0x25] = 1,  [0x26] = 1,
    [0x27] = 1, [0x28] = 1, [0x29] = 1, [0x2a] = 1, [0x2b] = 1, [0x30] = 1, [0x31] = 1,  [0x32] = 1,  [0x33] = 1,  [0x34] = 32,
    [0x40] = 1, [0x41] = 0, [0x50] = 1, [0x60] = 1, [0x70] = 3, [0x71] = 2, [0x72] = 1,
};

static int command_valid(uint32_t cmd)
{
    return (cmd >= 0x10 && cmd <= 0x1c) || (cmd >= 0x20 && cmd <= 0x2b) || (cmd >= 0x30 && cmd <= 0x34) || cmd == 0x40 ||
           cmd == 0x41 || cmd == 0x50 || cmd == 0x60 || (cmd >= 0x70 && cmd <= 0x72);
}

static void execute(uint32_t cmd, const uint32_t *p)
{
    int32_t m[16];
    count_commands++;
    switch (cmd) {
        case 0x10:
            ge.mode = (int) (p[0] & 3);
            break;
        case 0x11:
            matrix_push();
            break;
        case 0x12:
            matrix_pop(p[0]);
            break;
        case 0x13:
            matrix_store(p[0]);
            break;
        case 0x14:
            matrix_restore(p[0]);
            break;
        case 0x15:
            for_current(matrix_load, identity, 0);
            break;
        case 0x16:
            for_current(matrix_load, (const int32_t *) p, 0);
            break;
        case 0x17:
            expand_4x3(p, m);
            for_current(matrix_load, m, 0);
            break;
        case 0x18:
            for_current(matrix_mult, (const int32_t *) p, 0);
            break;
        case 0x19:
            expand_4x3(p, m);
            for_current(matrix_mult, m, 0);
            break;
        case 0x1a:
            expand_3x3(p, m);
            for_current(matrix_mult, m, 0);
            break;
        case 0x1b:
            for_current(matrix_scale, (const int32_t *) p, 1);
            break;
        case 0x1c:
            for_current(matrix_translate, (const int32_t *) p, 0);
            break;
        case 0x20:
            ge.cr = p[0] & 31;
            ge.cg = (p[0] >> 5) & 31;
            ge.cb = (p[0] >> 10) & 31;
            break;
        case 0x21:
            set_normal(p[0]);
            break;
        case 0x22:
            set_texcoord(p[0]);
            break;
        case 0x23:
            ge.vx = (int16_t) (p[0] & 0xffff);
            ge.vy = (int16_t) (p[0] >> 16);
            ge.vz = (int16_t) (p[1] & 0xffff);
            submit_vertex();
            break;
        case 0x24:
            ge.vx = sign_extend(p[0] & 0x3ff, 10) << 6;
            ge.vy = sign_extend((p[0] >> 10) & 0x3ff, 10) << 6;
            ge.vz = sign_extend((p[0] >> 20) & 0x3ff, 10) << 6;
            submit_vertex();
            break;
        case 0x25:
            ge.vx = (int16_t) (p[0] & 0xffff);
            ge.vy = (int16_t) (p[0] >> 16);
            submit_vertex();
            break;
        case 0x26:
            ge.vx = (int16_t) (p[0] & 0xffff);
            ge.vz = (int16_t) (p[0] >> 16);
            submit_vertex();
            break;
        case 0x27:
            ge.vy = (int16_t) (p[0] & 0xffff);
            ge.vz = (int16_t) (p[0] >> 16);
            submit_vertex();
            break;
        case 0x28: /* 1.0.9 differences, as twelfths: the 10-bit value is the delta itself */
            ge.vx = (int16_t) (ge.vx + sign_extend(p[0] & 0x3ff, 10));
            ge.vy = (int16_t) (ge.vy + sign_extend((p[0] >> 10) & 0x3ff, 10));
            ge.vz = (int16_t) (ge.vz + sign_extend((p[0] >> 20) & 0x3ff, 10));
            submit_vertex();
            break;
        case 0x29:
            ge.polyattr_next = p[0];
            break;
        case 0x2a:
            ge.texparam = p[0];
            break;
        case 0x2b:
            ge.pltt = p[0] & 0x1fff;
            break;
        case 0x30:
            for (int c = 0; c < 3; c++) {
                ge.dif[c] = (p[0] >> (5 * c)) & 31;
                ge.amb[c] = (p[0] >> (16 + 5 * c)) & 31;
            }
            if (p[0] & 0x8000) {
                ge.cr = ge.dif[0];
                ge.cg = ge.dif[1];
                ge.cb = ge.dif[2];
            }
            break;
        case 0x31:
            for (int c = 0; c < 3; c++) {
                ge.spe[c] = (p[0] >> (5 * c)) & 31;
                ge.emi[c] = (p[0] >> (16 + 5 * c)) & 31;
            }
            ge.use_shininess = (p[0] >> 15) & 1;
            break;
        case 0x32:
            set_light_vector(p[0]);
            break;
        case 0x33:
            for (int c = 0; c < 3; c++) {
                ge.light_color[p[0] >> 30][c] = (p[0] >> (5 * c)) & 31;
            }
            break;
        case 0x34:
            for (int i = 0; i < 32; i++) {
                for (int j = 0; j < 4; j++) {
                    ge.shininess[i * 4 + j] = (uint8_t) (p[i] >> (8 * j));
                }
            }
            break;
        case 0x40:
            ge.polyattr = ge.polyattr_next;
            ge.primitive = (int) (p[0] & 3);
            ge.in_vtxs = 1;
            ge.strip_count = 0;
            break;
        case 0x41:
            ge.in_vtxs = 0;
            break;
        case 0x50:
            ge.swap_pending = 1;
            ge.swap_param_next = p[0] & 3;
            break;
        case 0x60:
            ge.viewport = p[0];
            break;
        case 0x70:
            box_test(p);
            break;
        case 0x71:
            pos_test(p);
            break;
        case 0x72:
            vec_test(p[0]);
            break;
        default:
            break;
    }
}

static int is_test(uint32_t cmd)
{
    return cmd >= 0x70 && cmd <= 0x72;
}

/* Runs every complete command at the head of the FIFO. After SWAP_BUFFERS the engine halts
 * until VBlank (GBATEK, "DS 3D Display Control"): the commands sent meanwhile wait here and
 * go into the next list. */
static void drain_fifo(void)
{
    while (ge.fifo_count > 0 && !ge.swap_pending) {
        uint32_t cmd = ge.fifo_cmd[ge.fifo_head];
        int need = param_count[cmd & 0x7f];
        int entries = need ? need : 1;
        if (ge.fifo_count < entries) {
            return; /* parameters still to come */
        }
        uint32_t params[32];
        for (int i = 0; i < entries; i++) {
            params[i] = ge.fifo_param[(ge.fifo_head + i) % FIFO_SIZE];
        }
        ge.fifo_head = (ge.fifo_head + entries) % FIFO_SIZE;
        ge.fifo_count -= entries;
        if (is_test(cmd)) {
            ge.fifo_tests--;
        }
        execute(cmd, params);
    }
}

static void fifo_push(uint32_t cmd, uint32_t param)
{
    if (!command_valid(cmd)) {
        return; /* GBATEK: invalid commands are ignored and fetch no parameters */
    }
    if (ge.fifo_count == FIFO_SIZE) {
        /* the CPU would have stalled long before (the hardware holds 256 entries); a game
           that floods a stalled engine loses commands here, which the report shows */
        count_fifo_lost++;
        return;
    }
    int slot = (ge.fifo_head + ge.fifo_count) % FIFO_SIZE;
    ge.fifo_cmd[slot] = (uint8_t) cmd;
    ge.fifo_param[slot] = param;
    ge.fifo_count++;
    /* the first entry of a command starts it: a test is pending from then on */
    if (ge.fifo_partial == 0) {
        if (is_test(cmd)) {
            ge.fifo_tests++;
        }
        ge.fifo_partial = param_count[cmd] ? param_count[cmd] - 1 : 0;
    } else {
        ge.fifo_partial--;
    }
    drain_fifo();
}

/* A word written to 0x400-0x43f: a packed command word when no command is waiting for
 * parameters, otherwise the next parameter. Commands without parameters in a packed word
 * run at once, without a dummy parameter; a NOP byte after the first is padding. */
static void fifo_write_packed(uint32_t value)
{
    if (ge.packed_remaining == 0) {
        ge.packed = value;
        ge.packed_remaining = 4;
        ge.packed_params = 0;
        ge.packed_total = param_count[ge.packed & 0x7f];
        if (ge.packed_total > 0 && command_valid(ge.packed & 0xff)) {
            return; /* its parameters follow */
        }
    } else {
        ge.packed_params++;
    }
    for (;;) {
        uint32_t cmd = ge.packed & 0xff;
        if (cmd != 0 || ge.packed_remaining == 4) {
            fifo_push(cmd, value);
        }
        if (ge.packed_params >= ge.packed_total) {
            ge.packed >>= 8;
            ge.packed_remaining--;
            if (ge.packed_remaining == 0) {
                return;
            }
            ge.packed_params = 0;
            ge.packed_total = param_count[ge.packed & 0x7f];
            if (!command_valid(ge.packed & 0xff)) {
                ge.packed_total = 0;
            }
        }
        if (ge.packed_params < ge.packed_total) {
            return;
        }
    }
}

void gpu3d_write(uint32_t offset, uint32_t value)
{
    if (offset < 0x440) {
        fifo_write_packed(value);
    } else if (offset < 0x600) {
        fifo_push((offset - 0x400) >> 2, value);
    }
}

uint32_t gpu3d_read(uint32_t offset)
{
    switch (offset) {
        case 0x600: {
            /* commands run the moment they are complete, so the engine is busy only while a
               swap holds it (or a command still waits for parameters) */
            int count = ge.fifo_count > FIFO_HW ? FIFO_HW : ge.fifo_count;
            uint32_t v = 0;
            v |= ge.fifo_tests > 0 ? 1u : 0u;
            v |= (uint32_t) ge.box_result << 1;
            v |= (uint32_t) (ge.pos_sp & 31) << 8;
            v |= (uint32_t) (ge.proj_sp & 1) << 13;
            v |= (uint32_t) ge.stack_error << 15;
            v |= (uint32_t) count << 16;
            if (count == FIFO_HW) {
                v |= 1u << 24;
            }
            if (count < FIFO_HW / 2) {
                v |= 1u << 25;
            }
            if (count == 0) {
                v |= 1u << 26;
            }
            if (ge.fifo_count > 0 || ge.swap_pending) {
                v |= 1u << 27;
            }
            return v;
        }
        case 0x604:
            return (uint32_t) lists[geometry_list].polygons | ((uint32_t) lists[geometry_list].vertices << 16);
        default:
            break;
    }
    if (offset >= 0x620 && offset < 0x630) {
        return (uint32_t) ge.pos_result[(offset - 0x620) / 4];
    }
    if (offset >= 0x630 && offset < 0x638) {
        uint32_t i = (offset - 0x630) / 4;
        uint32_t lo = (uint32_t) ge.vec_result[i * 2] & 0xffff;
        uint32_t hi = i == 0 ? (uint32_t) ge.vec_result[1] & 0xffff : 0;
        return lo | (hi << 16);
    }
    if (offset >= 0x640 && offset < 0x680) {
        return (uint32_t) ge.clip[(offset - 0x640) / 4];
    }
    if (offset >= 0x680 && offset < 0x6a4) {
        uint32_t i = (offset - 0x680) / 4;
        return (uint32_t) ge.vec[(i / 3) * 4 + i % 3];
    }
    return 0;
}

void gpu3d_gxstat_write(uint32_t value)
{
    if (value & 0x8000) {
        ge.stack_error = 0;
        ge.proj_sp = 0;
        ge.tex_sp = 0;
    }
}

/* The rendering engine ---------------------------------------------------------------------- */

/* The frame buffer the rendering engine fills: 6-bit colour, 5-bit alpha, 24-bit depth, and
 * the attribute buffer (opaque and translucent polygon IDs, fog, edge and stencil flags). */
typedef struct Pixel {
    uint8_t r, g, b, a;
    uint32_t depth;
    uint8_t opaque_id, trans_id, flags;
} Pixel;
#define PF_FOG 1
#define PF_EDGE 2
#define PF_STENCIL 4
#define PF_TRANSLUCENT 8 /* a translucent pixel sits here: its ID blocks same-ID blending */

static Pixel frame[SCREEN_H][SCREEN_W];
static uint16_t out_color[SCREEN_H][SCREEN_W];
static uint8_t out_alpha[SCREEN_H][SCREEN_W];

/* The rendering registers, captured when a frame starts. */
static struct {
    uint32_t disp3dcnt, clear_color, clear_depth, clrimage_offset, fog_color, fog_offset, alpha_ref, dot_depth;
    uint8_t fog_table[32];
    uint16_t toon[32], edge[8];
} rr;

static void capture_registers(void)
{
    rr.disp3dcnt = io_view_reg(0x060) & 0xffff;
    rr.alpha_ref = io_view_reg(0x340) & 31;
    rr.clear_color = io_view_reg(0x350);
    rr.clear_depth = io_view_reg(0x354) & 0x7fff;
    rr.clrimage_offset = (io_view_reg(0x354) >> 16) & 0xffff;
    rr.fog_color = io_view_reg(0x358);
    rr.fog_offset = io_view_reg(0x35c) & 0x7fff;
    rr.dot_depth = io_view_reg(0x610) & 0x7fff;
    for (int i = 0; i < 8; i++) {
        uint32_t w = io_view_reg(0x360 + 4 * i);
        for (int j = 0; j < 4; j++) {
            rr.fog_table[i * 4 + j] = (uint8_t) ((w >> (8 * j)) & 0x7f);
        }
    }
    for (int i = 0; i < 16; i++) {
        uint32_t w = io_view_reg(0x380 + 4 * i);
        rr.toon[i * 2] = (uint16_t) w;
        rr.toon[i * 2 + 1] = (uint16_t) (w >> 16);
    }
    for (int i = 0; i < 4; i++) {
        uint32_t w = io_view_reg(0x330 + 4 * i);
        rr.edge[i * 2] = (uint16_t) w;
        rr.edge[i * 2 + 1] = (uint16_t) (w >> 16);
    }
}

/* Texture memory: the 512 KiB image space and the 128 KiB palette space, by bank slot. A
 * read where no bank is mapped gives zero, as the hardware's open bus does roughly. */
static uint8_t tex_read8(uint32_t address)
{
    const uint8_t *slot = io_vram_texture((int) ((address >> 17) & 3));
    return slot ? slot[address & 0x1ffff] : 0;
}

static uint16_t tex_read16(uint32_t address)
{
    const uint8_t *slot = io_vram_texture((int) ((address >> 17) & 3));
    if (slot == NULL) {
        return 0;
    }
    address &= 0x1fffe;
    return (uint16_t) (slot[address] | (slot[address + 1] << 8));
}

static uint32_t tex_read32(uint32_t address)
{
    return (uint32_t) tex_read16(address) | ((uint32_t) tex_read16(address + 2) << 16);
}

static uint16_t pal_read16(uint32_t address)
{
    const uint8_t *slot = io_vram_texture_palette((int) ((address >> 14) & 7));
    if (slot == NULL) {
        return 0;
    }
    address &= 0x3ffe;
    return (uint16_t) (slot[address] | (slot[address + 1] << 8));
}

/* One texel at (s, t) in 1.11.4, after repeat/flip/clamp: colour expanded to 6 bits, alpha
 * 5 bits (0 = transparent). Returns 0 for the transparent texel. */
static int sample_texture(const Polygon *p, int32_t s, int32_t t, int32_t *r, int32_t *g, int32_t *b, int32_t *a)
{
    uint32_t param = p->texparam;
    int sshift = 3 + (int) ((param >> 20) & 7), tshift = 3 + (int) ((param >> 23) & 7);
    int32_t width = 1 << sshift, height = 1 << tshift;
    s >>= 4;
    t >>= 4;
    if (param & (1u << 16)) {
        int odd = (s >> sshift) & 1;
        s &= width - 1;
        if (odd && (param & (1u << 18))) {
            s = width - 1 - s;
        }
    } else {
        s = s < 0 ? 0 : s >= width ? width - 1 : s;
    }
    if (param & (1u << 17)) {
        int odd = (t >> tshift) & 1;
        t &= height - 1;
        if (odd && (param & (1u << 19))) {
            t = height - 1 - t;
        }
    } else {
        t = t < 0 ? 0 : t >= height ? height - 1 : t;
    }
    uint32_t base = (param & 0xffff) << 3, pltt = p->pltt << 4;
    uint32_t index, color = 0, alpha = 31;
    switch ((param >> 26) & 7) {
        case 1: { /* A3I5 */
            uint8_t v = tex_read8(base + (uint32_t) (t * width + s));
            index = v & 31;
            alpha = (uint32_t) ((v >> 5) * 4 + (v >> 6));
            color = pal_read16(pltt + index * 2);
            break;
        }
        case 2: { /* 4 colours, palette base in 8-byte steps */
            uint8_t v = tex_read8(base + (uint32_t) (t * width + s) / 4);
            index = (v >> ((s & 3) * 2)) & 3;
            if (index == 0 && (param & (1u << 29))) {
                return 0;
            }
            color = pal_read16((p->pltt << 3) + index * 2);
            break;
        }
        case 3: { /* 16 colours */
            uint8_t v = tex_read8(base + (uint32_t) (t * width + s) / 2);
            index = (s & 1) ? v >> 4 : v & 15;
            if (index == 0 && (param & (1u << 29))) {
                return 0;
            }
            color = pal_read16(pltt + index * 2);
            break;
        }
        case 4: { /* 256 colours */
            index = tex_read8(base + (uint32_t) (t * width + s));
            if (index == 0 && (param & (1u << 29))) {
                return 0;
            }
            color = pal_read16(pltt + index * 2);
            break;
        }
        case 5: { /* 4x4 compressed: blocks in slot 0 or 2, their palette words in slot 1 */
            uint32_t block = base + (uint32_t) ((t / 4) * (width / 4) + s / 4) * 4;
            uint32_t texels = tex_read32(block);
            uint32_t info_addr = 0x20000 + ((block & 0x1ffff) >> 1) + ((block & 0x40000) ? 0x10000 : 0);
            uint16_t info = tex_read16(info_addr);
            uint32_t pal = pltt + (uint32_t) (info & 0x3fff) * 4;
            uint32_t mode = info >> 14;
            index = (texels >> (((t & 3) * 4 + (s & 3)) * 2)) & 3;
            uint16_t c0 = pal_read16(pal), c1 = pal_read16(pal + 2);
            switch (index) {
                case 0:
                    color = c0;
                    break;
                case 1:
                    color = c1;
                    break;
                case 2:
                    if (mode == 1) { /* (c0 + c1) / 2 per component */
                        color =
                            (uint32_t) ((((c0 & 31) + (c1 & 31)) >> 1) | (((((c0 >> 5) & 31) + ((c1 >> 5) & 31)) >> 1) << 5) |
                                        (((((c0 >> 10) & 31) + ((c1 >> 10) & 31)) >> 1) << 10));
                    } else if (mode == 3) { /* (c0*5 + c1*3) / 8 */
                        color = (uint32_t) ((((c0 & 31) * 5 + (c1 & 31) * 3) >> 3) |
                                            (((((c0 >> 5) & 31) * 5 + ((c1 >> 5) & 31) * 3) >> 3) << 5) |
                                            (((((c0 >> 10) & 31) * 5 + ((c1 >> 10) & 31) * 3) >> 3) << 10));
                    } else {
                        color = pal_read16(pal + 4);
                    }
                    break;
                default:
                    if (mode == 2) {
                        color = pal_read16(pal + 6);
                    } else if (mode == 3) { /* (c0*3 + c1*5) / 8 */
                        color = (uint32_t) ((((c0 & 31) * 3 + (c1 & 31) * 5) >> 3) |
                                            (((((c0 >> 5) & 31) * 3 + ((c1 >> 5) & 31) * 5) >> 3) << 5) |
                                            (((((c0 >> 10) & 31) * 3 + ((c1 >> 10) & 31) * 5) >> 3) << 10));
                    } else {
                        return 0;
                    }
                    break;
            }
            break;
        }
        case 6: { /* A5I3 */
            uint8_t v = tex_read8(base + (uint32_t) (t * width + s));
            index = v & 7;
            alpha = v >> 3;
            color = pal_read16(pltt + index * 2);
            break;
        }
        case 7: { /* direct colour, bit 15 the alpha */
            uint16_t v = tex_read16(base + (uint32_t) (t * width + s) * 2);
            color = v;
            alpha = (v & 0x8000) ? 31 : 0;
            break;
        }
        default:
            return 0;
    }
    if (alpha == 0) {
        return 0;
    }
    *r = expand6((int32_t) (color & 31));
    *g = expand6((int32_t) ((color >> 5) & 31));
    *b = expand6((int32_t) ((color >> 10) & 31));
    *a = (int32_t) alpha;
    return 1;
}

/* Perspective-correct interpolation: the position of `pos` in 0..len between two ends with
 * reduced w's, as a 16-bit fraction. Equal w's (and a zero span) give the linear factor. */
static int32_t interp_factor(int32_t pos, int32_t len, uint32_t w0, uint32_t w1)
{
    if (len <= 0) {
        return 0;
    }
    if (pos >= len) {
        return 0x10000;
    }
    if (w0 == w1) {
        return (int32_t) (((int64_t) pos << 16) / len);
    }
    /* 1/w is linear on the screen: f = (pos/w1) / ((len-pos)/w0 + pos/w1) */
    int64_t num = (int64_t) w0 * pos, den = (int64_t) w0 * pos + (int64_t) w1 * (len - pos);
    if (den == 0) {
        return 0;
    }
    return (int32_t) ((num << 16) / den);
}

static int32_t lerp(int32_t a, int32_t b, int32_t f)
{
    return a + (int32_t) (((int64_t) (b - a) * f) >> 16);
}

/* Attributes at a point of an edge or a span. */
typedef struct Sample {
    int32_t r, g, b, s, t, depth;
    uint32_t w16;
} Sample;

static void sample_from_vertex(Sample *o, const Vertex *v)
{
    o->r = v->r;
    o->g = v->g;
    o->b = v->b;
    o->s = v->s;
    o->t = v->t;
    o->depth = v->depth;
    o->w16 = v->w16;
}

/* Between two samples: colour and texture coordinates perspective-correct, depth linear in
 * screen space for Z-buffering (z/w is affine) and perspective-correct for W-buffering. */
static void sample_between(Sample *o, const Sample *a, const Sample *b, int32_t pos, int32_t len, int wbuffer)
{
    int32_t f = interp_factor(pos, len, a->w16, b->w16);
    int32_t fl = len > 0 ? (int32_t) (((int64_t) pos << 16) / len) : 0;
    o->r = lerp(a->r, b->r, f);
    o->g = lerp(a->g, b->g, f);
    o->b = lerp(a->b, b->b, f);
    o->s = lerp(a->s, b->s, f);
    o->t = lerp(a->t, b->t, f);
    o->depth = lerp(a->depth, b->depth, wbuffer ? f : fl);
    o->w16 = (uint32_t) lerp((int32_t) a->w16, (int32_t) b->w16, f);
}

/* An edge of the polygon on one scanline: the pixels it covers and its attributes there. */
typedef struct EdgeSpan {
    int32_t xs, xe; /* inclusive pixel range on this line */
    Sample at;
} EdgeSpan;

/* The pixels an edge from (x0, y0) to (x1, y1), y0 < y1, covers on line y (y0 <= y < y1):
 * an x-major edge covers from its position at y to the one at y + 1 (exclusive), a y-major
 * edge the nearest pixel to its position at y. */
static void edge_at(const Vertex *v0, const Vertex *v1, int y, int wbuffer, EdgeSpan *out)
{
    int32_t dy = v1->sy - v0->sy, dx = v1->sx - v0->sx;
    int32_t rel = y - v0->sy;
    int32_t adx = dx < 0 ? -dx : dx;
    if (adx > dy) {
        int64_t a = ((int64_t) adx * rel) / dy, b = ((int64_t) adx * (rel + 1)) / dy;
        if (dx >= 0) {
            out->xs = v0->sx + (int32_t) a;
            out->xe = v0->sx + (int32_t) b - 1;
        } else {
            out->xs = v0->sx - (int32_t) b + 1;
            out->xe = v0->sx - (int32_t) a;
        }
        if (out->xe < out->xs) {
            out->xe = out->xs;
        }
    } else {
        int64_t x = ((int64_t) adx * rel * 2 + dy) / (2 * dy); /* nearest */
        out->xs = out->xe = v0->sx + (int32_t) (dx >= 0 ? x : -x);
    }
    Sample s0, s1;
    sample_from_vertex(&s0, v0);
    sample_from_vertex(&s1, v1);
    sample_between(&out->at, &s0, &s1, rel, dy, wbuffer);
}

/* Texture blending per the polygon mode on 6-bit colours (GBATEK, "DS 3D Texture
 * Blending"); returns the pixel alpha, 0 for a transparent texel. */
static int32_t shade(const Polygon *p, const Sample *smp, int32_t *r, int32_t *g, int32_t *b)
{
    uint32_t mode = (p->attr >> 4) & 3;
    int highlight = mode == 2 && (rr.disp3dcnt & 2);
    int32_t alpha = (int32_t) ((p->attr >> 16) & 31);
    if (alpha == 0) {
        alpha = 31; /* wire-frame edges are solid */
    }
    int32_t vr = smp->r > 63 ? 63 : smp->r, vg = smp->g > 63 ? 63 : smp->g, vb = smp->b > 63 ? 63 : smp->b;
    int32_t hr = 0, hg = 0, hb = 0;
    if (mode == 2) {
        /* the vertex red indexes the toon table. Toon: the entry replaces the vertex colour.
           Highlight: the vertex colour becomes grey (red in all three) and the entry is
           added after the modulation. */
        uint16_t c = rr.toon[vr >> 1];
        if (highlight) {
            hr = expand6(c & 31);
            hg = expand6((c >> 5) & 31);
            hb = expand6((c >> 10) & 31);
            vg = vb = vr;
        } else {
            vr = expand6(c & 31);
            vg = expand6((c >> 5) & 31);
            vb = expand6((c >> 10) & 31);
        }
    }
    int32_t tr, tg, tb, ta;
    int textured = ((p->texparam >> 26) & 7) != 0 && (rr.disp3dcnt & 1);
    if (!textured) {
        /* the formulas below with a white opaque texel reduce to the vertex colour */
        tr = tg = tb = 63;
        ta = 31;
    } else if (!sample_texture(p, smp->s, smp->t, &tr, &tg, &tb, &ta)) {
        if (mode != 1) {
            return 0;
        }
        ta = 0; /* decal shows the vertex colour through a transparent texel */
        tr = tg = tb = 0;
    }
    if (mode == 1) {
        if (ta == 0) {
            *r = vr;
            *g = vg;
            *b = vb;
        } else if (ta == 31) {
            *r = tr;
            *g = tg;
            *b = tb;
        } else {
            *r = (tr * ta + vr * (31 - ta)) >> 5;
            *g = (tg * ta + vg * (31 - ta)) >> 5;
            *b = (tb * ta + vb * (31 - ta)) >> 5;
        }
        return alpha;
    }
    /* modulation, toon, highlight, shadow */
    *r = ((tr + 1) * (vr + 1) - 1) >> 6;
    *g = ((tg + 1) * (vg + 1) - 1) >> 6;
    *b = ((tb + 1) * (vb + 1) - 1) >> 6;
    if (highlight) {
        *r = *r + hr > 63 ? 63 : *r + hr;
        *g = *g + hg > 63 ? 63 : *g + hg;
        *b = *b + hb > 63 ? 63 : *b + hb;
    }
    return ((ta + 1) * (alpha + 1) - 1) >> 5;
}

/* One pixel of a polygon through the depth test, alpha test, stencil and blending. */
static void draw_pixel(const Polygon *p, int x, int y, const Sample *smp, int edge)
{
    Pixel *px = &frame[y][x];
    uint32_t attr = p->attr;
    uint32_t id = (attr >> 24) & 63;
    uint32_t mode = (attr >> 4) & 3;
    uint32_t depth = (uint32_t) smp->depth & 0xffffff;

    int pass;
    if (attr & (1u << 14)) {
        int64_t d = (int64_t) depth - (int64_t) px->depth;
        pass = d >= -0x200 && d <= 0x200;
    } else {
        pass = depth < px->depth;
    }
    if (mode == 3 && id == 0) {
        /* the shadow mask: marks the pixels its back faces fail the depth test on */
        if (!pass) {
            px->flags |= PF_STENCIL;
        }
        return;
    }
    if (!pass) {
        return;
    }
    if (mode == 3) {
        if ((px->flags & PF_STENCIL) == 0) {
            return;
        }
        px->flags &= (uint8_t) ~PF_STENCIL;
        if (px->opaque_id == id) {
            return;
        }
    }
    int32_t r, g, b;
    int32_t alpha = shade(p, smp, &r, &g, &b);
    if (alpha == 0) {
        return;
    }
    if (rr.disp3dcnt & 4) {
        if (alpha <= (int32_t) rr.alpha_ref) {
            return;
        }
    }
    if (alpha == 31) {
        px->r = (uint8_t) r;
        px->g = (uint8_t) g;
        px->b = (uint8_t) b;
        px->a = 31;
        px->depth = depth;
        px->opaque_id = (uint8_t) id;
        px->flags = (uint8_t) ((px->flags & PF_STENCIL) | ((attr & (1u << 15)) ? PF_FOG : 0) | (edge ? PF_EDGE : 0));
        return;
    }
    /* translucent: never over a translucent pixel of the same ID, blended when enabled and
       the destination has any alpha, the depth written only when attribute bit 11 asks */
    if ((px->flags & PF_TRANSLUCENT) && px->trans_id == id) {
        return;
    }
    if ((rr.disp3dcnt & 8) && px->a != 0) {
        px->r = (uint8_t) ((r * (alpha + 1) + px->r * (31 - alpha)) / 32);
        px->g = (uint8_t) ((g * (alpha + 1) + px->g * (31 - alpha)) / 32);
        px->b = (uint8_t) ((b * (alpha + 1) + px->b * (31 - alpha)) / 32);
        px->a = (uint8_t) (alpha > px->a ? alpha : px->a);
    } else {
        px->r = (uint8_t) r;
        px->g = (uint8_t) g;
        px->b = (uint8_t) b;
        px->a = (uint8_t) alpha;
    }
    if (attr & (1u << 11)) {
        px->depth = depth;
    }
    px->trans_id = (uint8_t) id;
    px->flags |= PF_TRANSLUCENT;
    if ((attr & (1u << 15)) == 0) {
        px->flags &= (uint8_t) ~PF_FOG;
    }
}

static void draw_polygon(const Polygon *p, int wbuffer)
{
    int n = p->count;
    int wireframe = ((p->attr >> 16) & 31) == 0;

    if (p->ytop == p->ybot) {
        /* a polygon on one line: the span between its leftmost and rightmost vertices */
        int y = p->ytop;
        if (y < 0 || y >= SCREEN_H) {
            return;
        }
        const Vertex *l = &p->v[0], *r = &p->v[0];
        for (int i = 1; i < n; i++) {
            if (p->v[i].sx < l->sx) {
                l = &p->v[i];
            }
            if (p->v[i].sx > r->sx) {
                r = &p->v[i];
            }
        }
        if (l->sx == r->sx) {
            /* a 0x0 polygon: the 1-dot depth rule, on w with three fractional bits */
            if ((p->attr & (1u << 13)) == 0) {
                int visible = 0;
                for (int i = 0; i < n; i++) {
                    if (((uint32_t) p->v[i].w >> 9) <= rr.dot_depth) {
                        visible = 1;
                    }
                }
                if (!visible) {
                    return;
                }
            }
        }
        Sample a, b, s;
        sample_from_vertex(&a, l);
        sample_from_vertex(&b, r);
        for (int x = l->sx; x <= r->sx && x < SCREEN_W; x++) {
            sample_between(&s, &a, &b, x - l->sx, r->sx - l->sx, wbuffer);
            draw_pixel(p, x, y, &s, 1);
        }
        return;
    }

    for (int y = p->ytop; y < p->ybot && y < SCREEN_H; y++) {
        EdgeSpan left, right;
        int have_left = 0, have_right = 0;
        for (int i = 0; i < n; i++) {
            const Vertex *v0 = &p->v[i], *v1 = &p->v[(i + 1) % n];
            if (v0->sy == v1->sy) {
                continue;
            }
            if (v0->sy > v1->sy) {
                const Vertex *t = v0;
                v0 = v1;
                v1 = t;
            }
            if (y < v0->sy || y >= v1->sy) {
                continue;
            }
            EdgeSpan e;
            edge_at(v0, v1, y, wbuffer, &e);
            if (!have_left || e.xs < left.xs || (e.xs == left.xs && e.xe < left.xe)) {
                left = e;
                have_left = 1;
            }
            if (!have_right || e.xe > right.xe || (e.xe == right.xe && e.xs > right.xs)) {
                right = e;
                have_right = 1;
            }
        }
        if (!have_left || !have_right) {
            continue;
        }
        int xl = left.xs, xr = right.xe;
        if (xr < xl) {
            xr = xl;
        }
        /* a vertical right edge is not drawn (GBATEK, "Polygon Size"), unless it is all
           there is of the line */
        int right_vertical = right.xs == right.xe;
        int xend = xr;
        if (right_vertical && xr > xl) {
            xend = xr - 1;
        }
        int border = y == p->ytop || y == p->ybot - 1;
        for (int x = xl; x <= xend; x++) {
            if (x < 0 || x >= SCREEN_W) {
                continue;
            }
            int edge = border || x <= left.xe || x >= right.xs;
            if (wireframe && !edge) {
                continue;
            }
            Sample s;
            sample_between(&s, &left.at, &right.at, x - xl, xr - xl, wbuffer);
            draw_pixel(p, x, y, &s, edge);
        }
    }
}

/* The rear plane: one colour/depth/ID for the screen, or the two bitmaps in texture slots 2
 * and 3 scrolled by CLRIMAGE_OFFSET (DISP3DCNT bit 14). */
static void clear_frame(void)
{
    uint32_t cc = rr.clear_color;
    uint32_t id = (cc >> 24) & 63;
    uint32_t depth15 = rr.clear_depth;
    uint32_t depth = depth15 * 0x200 + ((depth15 + 1) / 0x8000) * 0x1ff;
    Pixel base;
    base.r = (uint8_t) expand6((int32_t) (cc & 31));
    base.g = (uint8_t) expand6((int32_t) ((cc >> 5) & 31));
    base.b = (uint8_t) expand6((int32_t) ((cc >> 10) & 31));
    base.a = (uint8_t) ((cc >> 16) & 31);
    base.depth = depth;
    base.opaque_id = (uint8_t) id;
    base.trans_id = 0;
    base.flags = (uint8_t) ((cc & 0x8000) ? PF_FOG : 0);
    if ((rr.disp3dcnt & (1u << 14)) == 0) {
        for (int y = 0; y < SCREEN_H; y++) {
            for (int x = 0; x < SCREEN_W; x++) {
                frame[y][x] = base;
            }
        }
        return;
    }
    uint32_t xofs = rr.clrimage_offset & 0xff, yofs = (rr.clrimage_offset >> 8) & 0xff;
    for (int y = 0; y < SCREEN_H; y++) {
        for (int x = 0; x < SCREEN_W; x++) {
            uint32_t sx = (x + xofs) & 0xff, sy = (y + yofs) & 0xff;
            uint16_t c = tex_read16(0x40000 + (sy * 256 + sx) * 2);
            uint16_t d = tex_read16(0x60000 + (sy * 256 + sx) * 2);
            Pixel *px = &frame[y][x];
            *px = base;
            px->r = (uint8_t) expand6(c & 31);
            px->g = (uint8_t) expand6((c >> 5) & 31);
            px->b = (uint8_t) expand6((c >> 10) & 31);
            px->a = (c & 0x8000) ? 31 : 0;
            uint32_t d15 = d & 0x7fff;
            px->depth = d15 * 0x200 + ((d15 + 1) / 0x8000) * 0x1ff;
            px->flags = (uint8_t) ((d & 0x8000) ? PF_FOG : 0);
        }
    }
}

/* Edge marking: an edge pixel whose opaque ID differs from a neighbour's, and that is nearer
 * than that neighbour, takes the edge colour of its ID group. Outside the screen the rear
 * plane's ID counts. */
static void edge_marking(void)
{
    static uint8_t mark[SCREEN_H][SCREEN_W];
    uint32_t clear_id = (rr.clear_color >> 24) & 63;
    for (int y = 0; y < SCREEN_H; y++) {
        for (int x = 0; x < SCREEN_W; x++) {
            const Pixel *px = &frame[y][x];
            mark[y][x] = 0;
            if ((px->flags & PF_EDGE) == 0) {
                continue;
            }
            static const int dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1};
            for (int k = 0; k < 4; k++) {
                int nx = x + dx[k], ny = y + dy[k];
                uint32_t nid;
                uint32_t ndepth;
                if (nx < 0 || nx >= SCREEN_W || ny < 0 || ny >= SCREEN_H) {
                    nid = clear_id;
                    ndepth = 0xffffffffu;
                } else {
                    nid = frame[ny][nx].opaque_id;
                    ndepth = frame[ny][nx].depth;
                }
                if (nid != px->opaque_id && px->depth < ndepth) {
                    mark[y][x] = 1;
                    break;
                }
            }
        }
    }
    for (int y = 0; y < SCREEN_H; y++) {
        for (int x = 0; x < SCREEN_W; x++) {
            if (mark[y][x]) {
                uint16_t c = rr.edge[frame[y][x].opaque_id >> 3];
                frame[y][x].r = (uint8_t) expand6(c & 31);
                frame[y][x].g = (uint8_t) expand6((c >> 5) & 31);
                frame[y][x].b = (uint8_t) expand6((c >> 10) & 31);
            }
        }
    }
}

/* Fog: the density from the 32-entry table at the pixel's depth (depth >> 9 against the
 * 15-bit boundaries), blended over colour and alpha, or alpha only (DISP3DCNT bit 6). */
static void apply_fog(void)
{
    uint32_t shift = (rr.disp3dcnt >> 8) & 15;
    int32_t step = (int32_t) (0x400u >> shift);
    int32_t offset = (int32_t) rr.fog_offset;
    int32_t fr = expand6((int32_t) (rr.fog_color & 31)), fg = expand6((int32_t) ((rr.fog_color >> 5) & 31)),
            fb = expand6((int32_t) ((rr.fog_color >> 10) & 31)), fa = (int32_t) ((rr.fog_color >> 16) & 31);
    int alpha_only = (rr.disp3dcnt >> 6) & 1;
    for (int y = 0; y < SCREEN_H; y++) {
        for (int x = 0; x < SCREEN_W; x++) {
            Pixel *px = &frame[y][x];
            if ((px->flags & PF_FOG) == 0) {
                continue;
            }
            int32_t d = (int32_t) (px->depth >> 9);
            int32_t density;
            if (step == 0 || d < offset + step) {
                density = rr.fog_table[0];
            } else if (d >= offset + step * 32) {
                density = rr.fog_table[31];
            } else {
                int32_t n = (d - offset) / step - 1; /* boundary n = offset + step * (n + 1) */
                int32_t frac = (d - offset) % step;
                density = rr.fog_table[n] + ((rr.fog_table[n + 1] - rr.fog_table[n]) * frac) / step;
            }
            if (density == 127) {
                density = 128;
            }
            if (!alpha_only) {
                px->r = (uint8_t) ((fr * density + px->r * (128 - density)) / 128);
                px->g = (uint8_t) ((fg * density + px->g * (128 - density)) / 128);
                px->b = (uint8_t) ((fb * density + px->b * (128 - density)) / 128);
            }
            px->a = (uint8_t) ((fa * density + px->a * (128 - density)) / 128);
        }
    }
}

/* The rendering order within each pass: by the bottom line, then the top line, then the
 * order of submission (GBATEK, "DS 3D Polygon Definitions by Vertices"). */
static int compare_y(const void *x, const void *y)
{
    const Polygon *const *a = x, *const *b = y;
    if ((*a)->ybot != (*b)->ybot) {
        return (*a)->ybot < (*b)->ybot ? -1 : 1;
    }
    if ((*a)->ytop != (*b)->ytop) {
        return (*a)->ytop < (*b)->ytop ? -1 : 1;
    }
    return (*a)->order<(*b)->order ? -1 : (*a)->order>(*b)->order ? 1 : 0;
}

static void render_list(PolygonList *list)
{
    clock_t start = clock();
    capture_registers();
    clear_frame();

    /* opaque polygons in order, then translucent ones, by top line unless sorted manually */
    static Polygon *order[POLYGON_RAM];
    int opaque = 0, translucent = 0;
    for (int i = 0; i < list->polygons; i++) {
        if (!list->poly[i].translucent) {
            order[opaque++] = &list->poly[i];
        }
    }
    for (int i = 0; i < list->polygons; i++) {
        if (list->poly[i].translucent) {
            order[opaque + translucent++] = &list->poly[i];
        }
    }
    qsort(order, (size_t) opaque, sizeof(order[0]), compare_y);
    if (!list->manual_sort) {
        qsort(order + opaque, (size_t) translucent, sizeof(order[0]), compare_y);
    }
    for (int i = 0; i < opaque + translucent; i++) {
        draw_polygon(order[i], list->wbuffer);
    }
    if (rr.disp3dcnt & (1u << 5)) {
        edge_marking();
    }
    if (rr.disp3dcnt & (1u << 7)) {
        apply_fog();
    }
    for (int y = 0; y < SCREEN_H; y++) {
        for (int x = 0; x < SCREEN_W; x++) {
            const Pixel *px = &frame[y][x];
            out_color[y][x] = (uint16_t) ((px->r >> 1) | ((px->g >> 1) << 5) | ((px->b >> 1) << 10) | (px->a ? 0x8000 : 0));
            out_alpha[y][x] = px->a;
        }
    }
    render_seconds += (double) (clock() - start) / CLOCKS_PER_SEC;
    count_frames++;
}

/* Frame dumps -------------------------------------------------------------------------------- */

static const char *dump_dir;
/* The frames to dump, as ranges first..last by step (tools/run.py's --frames syntax). */
static struct {
    uint32_t first, last, step;
} dump_ranges[64];
static int dump_range_count, dump_all;

/* The frame as 0x00RRGGBB for frame.c's PNG writer. Pixels without alpha (where BG0 shows
 * what is behind the 3D layer) become a grey checkerboard so they stand out; partly
 * translucent pixels show their colour. */
int gpu3d_dump_png(const char *path)
{
    static uint32_t rgb[SCREEN_H * SCREEN_W];
    for (int y = 0; y < SCREEN_H; y++) {
        for (int x = 0; x < SCREEN_W; x++) {
            uint16_t c = out_color[y][x];
            uint32_t v;
            if ((c & 0x8000) == 0) {
                v = (((x >> 3) + (y >> 3)) & 1) ? 0x404040u : 0x606060u;
            } else {
                uint32_t r = c & 31, g = (c >> 5) & 31, b = (c >> 10) & 31;
                v = ((r << 3 | r >> 2) << 16) | ((g << 3 | g >> 2) << 8) | (b << 3 | b >> 2);
            }
            rgb[y * SCREEN_W + x] = v;
        }
    }
    return png_write(path, rgb, SCREEN_W, SCREEN_H);
}

static void maybe_dump(void)
{
    if (dump_dir == NULL) {
        return;
    }
    uint32_t frame_no = io_frame();
    int wanted = dump_all;
    for (int i = 0; i < dump_range_count; i++) {
        if (frame_no >= dump_ranges[i].first && frame_no <= dump_ranges[i].last &&
            (frame_no - dump_ranges[i].first) % dump_ranges[i].step == 0) {
            wanted = 1;
        }
    }
    if (!wanted) {
        return;
    }
    char path[512];
    snprintf(path, sizeof(path), "%s/3d-%u.png", dump_dir, frame_no);
    gpu3d_dump_png(path);
}

/* Swapping and the output ------------------------------------------------------------------- */

void gpu3d_vblank(void)
{
    if (!ge.swap_pending) {
        maybe_dump(); /* the image stays what the last swap rendered */
        return;
    }
    ge.swap_pending = 0;
    count_swaps++;
    PolygonList *done = &lists[geometry_list];
    /* the parameters of the swap apply to the list built after it */
    done->wbuffer = (int) (ge.swap_param >> 1) & 1;
    done->manual_sort = (int) ge.swap_param & 1;
    ge.swap_param = ge.swap_param_next;
    render_3d(geometry_list); /* gpu3d_render, here or on the drawing thread */
    geometry_list ^= 1;
    lists[geometry_list].polygons = 0;
    lists[geometry_list].vertices = 0;
    lists[geometry_list].wbuffer = (int) (ge.swap_param >> 1) & 1;
    lists[geometry_list].manual_sort = (int) ge.swap_param & 1;
    drain_fifo(); /* the engine resumes with the commands that waited for the swap */
}

void gpu3d_render(int list)
{
    PolygonList *done = &lists[list];
    render_list(done);
    if (trace_gx) {
        int drawn = 0;
        for (int y = 0; y < SCREEN_H; y++) {
            for (int x = 0; x < SCREEN_W; x++) {
                drawn += (out_color[y][x] >> 15) & 1;
            }
        }
        fprintf(stderr, "gx: frame %u swap %u: %d polygons %d vertices, DISP3DCNT %04x clear %08x, %d pixels drawn\n",
                io_frame(), ge.swap_param, done->polygons, done->vertices, rr.disp3dcnt, rr.clear_color, drawn);
    }
    maybe_dump();
}

const uint16_t *gpu3d_line(int y)
{
    return out_color[y < 0 ? 0 : y >= SCREEN_H ? SCREEN_H - 1 : y];
}

const uint8_t *gpu3d_line_alpha(int y)
{
    return out_alpha[y < 0 ? 0 : y >= SCREEN_H ? SCREEN_H - 1 : y];
}

void gpu3d_report(FILE *out)
{
    fprintf(out,
            "gx: %llu commands (%llu lost to a full queue), %llu polygons (%llu dropped), %llu swaps, %llu frames "
            "rendered in %.1f ms (%.2f ms each)\n",
            (unsigned long long) count_commands, (unsigned long long) count_fifo_lost, (unsigned long long) count_polygons,
            (unsigned long long) count_dropped, (unsigned long long) count_swaps, (unsigned long long) count_frames,
            render_seconds * 1000.0, count_frames ? render_seconds * 1000.0 / (double) count_frames : 0.0);
}

void gpu3d_init(void)
{
    uint8_t *fifo_cmd = ge.fifo_cmd;
    uint32_t *fifo_param = ge.fifo_param;
    memset(&ge, 0, sizeof(ge));
    ge.fifo_cmd = fifo_cmd ? fifo_cmd : malloc(FIFO_SIZE);
    ge.fifo_param = fifo_param ? fifo_param : malloc(FIFO_SIZE * sizeof(uint32_t));
    memcpy(ge.proj, identity, sizeof(identity));
    memcpy(ge.pos, identity, sizeof(identity));
    memcpy(ge.vec, identity, sizeof(identity));
    memcpy(ge.tex, identity, sizeof(identity));
    update_clip_matrix();
    ge.viewport = 0xbfff0000u; /* the full screen */
    for (int i = 0; i < 2; i++) {
        if (lists[i].poly == NULL) {
            lists[i].poly = calloc(POLYGON_RAM, sizeof(Polygon));
        }
        lists[i].polygons = lists[i].vertices = 0;
    }
    geometry_list = 0;
    memset(out_color, 0, sizeof(out_color));
    memset(out_alpha, 0, sizeof(out_alpha));

    /* RUN_DUMP3D=<dir>[:<list>], the list as n, a-b or a-b/step, comma-separated; without
       one RUN_PNG_FRAMES (tools/run.py --frames) is used, and without that every frame. The
       list separator is the last colon, so a Windows drive letter is not taken for one. */
    const char *trace = getenv("RUN_TRACE");
    trace_gx = trace != NULL && strstr(trace, "gx") != NULL;
    const char *dump = getenv("RUN_DUMP3D");
    if (dump != NULL && dump[0] != '\0' && dump_dir == NULL) {
        char *copy = strdup(dump);
        char *colon = strrchr(copy, ':');
        char *list = NULL;
        if (colon != NULL && colon != copy + 1 && colon[1] >= '0' && colon[1] <= '9') {
            *colon = '\0';
            list = colon + 1;
        } else if (getenv("RUN_PNG_FRAMES") != NULL) {
            list = strdup(getenv("RUN_PNG_FRAMES"));
        }
        if (list == NULL) {
            dump_all = 1;
        }
        for (char *tok = list ? strtok(list, ",") : NULL; tok != NULL && dump_range_count < 64; tok = strtok(NULL, ",")) {
            char *end;
            uint32_t first = (uint32_t) strtoul(tok, &end, 10), last = first, step = 1;
            if (*end == '-') {
                last = (uint32_t) strtoul(end + 1, &end, 10);
            }
            if (*end == '/') {
                step = (uint32_t) strtoul(end + 1, &end, 10);
            }
            dump_ranges[dump_range_count].first = first;
            dump_ranges[dump_range_count].last = last;
            dump_ranges[dump_range_count].step = step ? step : 1;
            dump_range_count++;
        }
        dump_dir = copy;
    }
}
