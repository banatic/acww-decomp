/* The DS 3D hardware; see gpu3d.h. Arithmetic follows GBATEK's "DS 3D" chapters: matrices
 * are 1.19.12 fixed point multiplied in 64 bits and truncated with an arithmetic shift,
 * vertices 1.3.12, normals and light vectors 1.0.9, texture coordinates 1.11.4, colours
 * 5 bits per component. Where GBATEK is silent (lighting, clipping, the viewport division,
 * the rasteriser's edges, interpolation and fill rules, anti-aliasing coverage), this file
 * follows what hardware tests have shown, as melonDS's notes describe them: the steps keep
 * the hardware's precision, so products wrap at 32 bits where the hardware's multipliers do. */
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

/* 32-bit arithmetic that wraps, as the hardware's does. */
static int32_t mul32(int32_t a, int32_t b)
{
    return (int32_t) ((uint32_t) a * (uint32_t) b);
}

static int32_t add32(int32_t a, int32_t b)
{
    return (int32_t) ((uint32_t) a + (uint32_t) b);
}

static int32_t sub32(int32_t a, int32_t b)
{
    return (int32_t) ((uint32_t) a - (uint32_t) b);
}

/* The low `bits` bits of v as a signed number. */
static int32_t sext(uint32_t v, int bits)
{
    return (int32_t) (v << (32 - bits)) >> (32 - bits);
}

/* A vertex of the geometry engine: clip coordinates, the colour with 12 fractional bits (it
 * keeps them through clipping), the texture coordinates; once it is part of a polygon, its
 * screen position and its 9-bit colour. */
typedef struct GVertex {
    int32_t pos[4];
    int32_t col[3];
    int16_t tex[2];
    uint8_t clipped; /* made by clipping */
    int32_t sx, sy;
    int32_t rgb[3];
} GVertex;

typedef struct Polygon {
    int count;
    GVertex v[MAX_POLY_VERTICES];
    int32_t z[MAX_POLY_VERTICES]; /* the depth value: z/w scaled, or w */
    int32_t w[MAX_POLY_VERTICES]; /* w normalised to 16 bits for the interpolators */
    uint32_t attr, texparam, pltt;
    uint8_t wbuffer, facing, translucent, shadow_mask, shadow, degenerate;
    int vtop, vbot, ytop, ybot; /* the top and bottom vertices and lines */
    uint32_t key;               /* the rendering order: translucent, bottom line, top line */
    int order;
    uint32_t command; /* the list's command that completed it (for the check) */
} Polygon;

/* The two polygon lists: the geometry engine fills one while the other is rendered. */
typedef struct PolygonList {
    Polygon *poly;
    int polygons, vertices; /* the RAM_COUNT values */
    int manual_sort;
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

    int16_t vtx[3];     /* the current vertex */
    uint8_t color[3];   /* the current vertex colour, 5 bits each */
    int16_t raw_st[2];  /* the last TEXCOORD */
    int16_t st[2];      /* texture coordinates after the transformation */
    uint32_t polyattr;  /* the attributes of the polygons being given (latched by BEGIN_VTXS) */
    uint32_t polyattr_next, texparam, pltt;
    int16_t light_dir[4][3]; /* negated, through the vector matrix, 11 bits */
    int32_t spec_recip[4];   /* the reciprocal the specular level is scaled by */
    uint8_t light_color[4][3];
    uint8_t dif[3], amb[3], spe[3], emi[3];
    int use_shininess;
    uint8_t shininess[128];
    uint32_t viewport;
    int32_t vp_x, vp_top, vp_w, vp_h;
    uint32_t light_param[4];   /* the last LIGHT_VECTOR parameters, and the vector matrix */
    int32_t light_vecm[4][16]; /* they went through (for the check's capture) */
    uint32_t dot_limit;        /* DISP_1DOT_DEPTH as a w */

    int primitive;        /* of the last BEGIN_VTXS */
    GVertex in[4];        /* the vertices of the polygon being given */
    int in_count;         /* how many of them are given */
    uint32_t consecutive; /* polygons of the strip so far */
    int last_strip;       /* the strip's previous polygon in the list, or -1 */

    int swap_pending;
    uint32_t flush_attr; /* the parameter of the last SWAP_BUFFERS */
    int box_result;
    int32_t pos_result[4];
    int16_t vec_result[3];
} ge;

static PolygonList lists[2];
static int geometry_list; /* the list the geometry engine writes; the other is rendered */

/* Counters for the report. */
static uint64_t count_commands, count_polygons, count_dropped, count_swaps, count_frames, count_fifo_lost;
static double render_seconds;
static int trace_gx; /* RUN_TRACE contains "gx": a line per rendered list on stderr */

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
        c[3 * 4 + col] = add32(c[3 * 4 + col], (int32_t) (sum >> 12));
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
        ge.pos_sp = (ge.pos_sp - sext(param, 6)) & 63;
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

/* The three 10-bit fields of a 1.0.9 vector. */
static void unpack_vector(uint32_t param, int32_t *v)
{
    v[0] = sext(param & 0x3ff, 10);
    v[1] = sext((param >> 10) & 0x3ff, 10);
    v[2] = sext((param >> 20) & 0x3ff, 10);
}

/* Column `col` of v times the 3x3 part of the vector matrix, as the hardware's 32-bit sum. */
static int32_t vector_dot(const int32_t *v, int col)
{
    return add32(add32(mul32(v[0], ge.vec[col]), mul32(v[1], ge.vec[4 + col])), mul32(v[2], ge.vec[8 + col]));
}

/* LIGHT_VECTOR: the direction through the vector matrix, negated and kept to 11 bits, and the
 * reciprocal that scales the specular level, from the direction's z with 10 fractional bits. */
static void set_light_vector(uint32_t param)
{
    int l = (int) (param >> 30);
    int32_t d[3];
    ge.light_param[l] = param;
    memcpy(ge.light_vecm[l], ge.vec, sizeof(ge.vec));
    unpack_vector(param, d);
    for (int c = 0; c < 3; c++) {
        ge.light_dir[l][c] = (int16_t) sext((uint32_t) - (vector_dot(d, c) >> 12), 11);
    }
    int32_t den = 0x200 - sext((uint32_t) vector_dot(d, 2) >> 12, 11);
    ge.spec_recip[l] = den ? (1 << 18) / den : 0;
}

/* NORMAL: the vertex colour from the four lights. The normal goes through the vector matrix
 * to 11 bits; per light, the products with the light direction lose 9 bits before they are
 * summed; a positive sum gives the diffuse level (11 bits, its products with the colours kept
 * to 20 bits) and, with the normal's z added, the specular level: its square in 10 bits times
 * the light's reciprocal, less one, clamped to 9 bits (or through the shininess table). The
 * colour is the sum with 14 fractional bits, saturated at 31. */
static void set_normal(uint32_t param)
{
    int32_t n[3];
    unpack_vector(param, n);
    if ((ge.texparam >> 30) == 2) {
        /* normal-source texture coordinates: the untransformed normal through the texture
           matrix, 9 + 12 fractional bits dropped (the SDK scales the matrix by 16) */
        int64_t s = (int64_t) n[0] * ge.tex[0] + (int64_t) n[1] * ge.tex[4] + (int64_t) n[2] * ge.tex[8];
        int64_t t = (int64_t) n[0] * ge.tex[1] + (int64_t) n[1] * ge.tex[5] + (int64_t) n[2] * ge.tex[9];
        ge.st[0] = (int16_t) (ge.raw_st[0] + (int32_t) (s >> 21));
        ge.st[1] = (int16_t) (ge.raw_st[1] + (int32_t) (t >> 21));
    }
    int32_t nt[3];
    for (int c = 0; c < 3; c++) {
        nt[c] = sext((uint32_t) vector_dot(n, c) >> 12, 11);
    }
    uint32_t acc[3] = {(uint32_t) ge.emi[0] << 14, (uint32_t) ge.emi[1] << 14, (uint32_t) ge.emi[2] << 14};
    for (int i = 0; i < 4; i++) {
        if ((ge.polyattr & (1u << i)) == 0) {
            continue;
        }
        const int16_t *l = ge.light_dir[i];
        const uint8_t *lc = ge.light_color[i];
        int32_t dot = add32(add32(mul32(l[0], nt[0]) >> 9, mul32(l[1], nt[1]) >> 9), mul32(l[2], nt[2]) >> 9);
        int32_t shine = 0;
        if (dot > 0) {
            int32_t diffuse = sext((uint32_t) dot, 11);
            for (int c = 0; c < 3; c++) {
                acc[c] += (uint32_t) mul32(ge.dif[c] * lc[c], diffuse) & 0xfffff;
            }
            int32_t h = sext((uint32_t) add32(dot, nt[2]), 11);
            h = (mul32(h, h) >> 10) & 0x3ff;
            shine = (mul32(h, ge.spec_recip[i]) >> 8) - 0x200;
            if (shine < 0) {
                shine = 0;
            } else {
                shine = sext((uint32_t) shine, 14);
                shine = shine < 0 ? 0 : shine > 0x1ff ? 0x1ff : shine;
            }
        }
        if (ge.use_shininess) {
            shine = ge.shininess[shine >> 2] << 1;
        }
        for (int c = 0; c < 3; c++) {
            acc[c] += (uint32_t) ((ge.spe[c] * shine + (ge.amb[c] << 9)) * lc[c]);
        }
    }
    for (int c = 0; c < 3; c++) {
        ge.color[c] = (uint8_t) ((acc[c] >> 14) > 31 ? 31 : acc[c] >> 14);
    }
}

/* Texture coordinates ----------------------------------------------------------------------- */

static void set_texcoord(uint32_t param)
{
    ge.raw_st[0] = (int16_t) (param & 0xffff);
    ge.raw_st[1] = (int16_t) (param >> 16);
    if ((ge.texparam >> 30) == 1) {
        /* texcoord source: (s t 1/16 1/16) through the first two columns, in the hardware's
           32-bit sum; the 1/16 constants make m[8] and m[12] plain additions */
        for (int c = 0; c < 2; c++) {
            int32_t sum = add32(add32(mul32(ge.raw_st[0], ge.tex[c]), mul32(ge.raw_st[1], ge.tex[4 + c])),
                                add32(ge.tex[8 + c], ge.tex[12 + c]));
            ge.st[c] = (int16_t) (sum >> 12);
        }
    } else {
        ge.st[0] = ge.raw_st[0];
        ge.st[1] = ge.raw_st[1];
    }
}

/* Clipping ---------------------------------------------------------------------------------- */

/* The point where the edge from `out` (outside plane `side` * axis `c`) to `in` (inside)
 * crosses the plane; the distances are the hardware's 32-bit ones and each attribute moves by
 * its difference times the outer distance over the difference of the distances. */
static void clip_edge(GVertex *r, const GVertex *out, const GVertex *in, int c, int side, int attribs)
{
    int64_t num = sub32(out->pos[3], mul32(side, out->pos[c]));
    int32_t den = (int32_t) (num - sub32(in->pos[3], mul32(side, in->pos[c])));
    *r = *out;
    if (den == 0) {
        den = 1; /* cannot happen: one end is inside, the other not */
    }
#define CLIP_LERP(f) (out->f + ((int64_t) sub32(in->f, out->f) * num) / den)
    for (int k = 0; k < 4; k++) {
        if (k != c) {
            r->pos[k] = (int32_t) CLIP_LERP(pos[k]);
        }
    }
    r->pos[c] = mul32(side, r->pos[3]);
    if (attribs) {
        for (int k = 0; k < 3; k++) {
            r->col[k] = (int32_t) CLIP_LERP(col[k]);
        }
        for (int k = 0; k < 2; k++) {
            r->tex[k] = (int16_t) (out->tex[k] + ((int64_t) (in->tex[k] - out->tex[k]) * num) / den);
        }
    }
#undef CLIP_LERP
    r->clipped = 1;
}

/* Both planes of axis `c`, the far one (+) first: each vertex outside is replaced by the
 * crossings of its edges to its inside neighbours. The first `start` vertices (shared with the
 * previous polygon of a strip) are not tested. Returns the new count, 0 when the polygon is
 * rejected: one that crosses the far plane without attribute bit 12. */
static int clip_axis(GVertex *v, int n, int start, int c, uint32_t attr, int attribs)
{
    GVertex tmp[16];
    int m = start;
    for (int i = 0; i < start; i++) {
        tmp[i] = v[i];
    }
    for (int i = start; i < n; i++) {
        int prev = i ? i - 1 : n - 1, next = i + 1 < n ? i + 1 : 0;
        if (v[i].pos[c] > v[i].pos[3]) {
            if (c == 2 && (attr & (1u << 12)) == 0) {
                return 0;
            }
            if (v[prev].pos[c] <= v[prev].pos[3]) {
                clip_edge(&tmp[m++], &v[i], &v[prev], c, 1, attribs);
            }
            if (v[next].pos[c] <= v[next].pos[3]) {
                clip_edge(&tmp[m++], &v[i], &v[next], c, 1, attribs);
            }
        } else {
            tmp[m++] = v[i];
        }
        if (m > 14) {
            return 0;
        }
    }
    n = m;
    m = start;
    for (int i = start; i < n; i++) {
        int prev = i ? i - 1 : n - 1, next = i + 1 < n ? i + 1 : 0;
        if (tmp[i].pos[c] < -tmp[i].pos[3]) {
            if (tmp[prev].pos[c] >= -tmp[prev].pos[3]) {
                clip_edge(&v[m++], &tmp[i], &tmp[prev], c, -1, attribs);
            }
            if (tmp[next].pos[c] >= -tmp[next].pos[3]) {
                clip_edge(&v[m++], &tmp[i], &tmp[next], c, -1, attribs);
            }
        } else {
            v[m++] = tmp[i];
        }
        if (m > MAX_POLY_VERTICES) {
            return 0;
        }
    }
    /* the colours' fractional bits are set again after each axis */
    for (int i = 0; i < m; i++) {
        for (int k = 0; k < 3; k++) {
            v[i].col[k] = (v[i].col[k] & ~0xfff) + 0xfff;
        }
    }
    return m;
}

/* Z, then Y, then X. */
static int clip_polygon(GVertex *v, int n, int start, uint32_t attr, int attribs)
{
    for (int c = 2; c >= 0 && n > 0; c--) {
        n = clip_axis(v, n, start, c, attr, attribs);
    }
    return n;
}

/* Vertices and the polygon list ------------------------------------------------------------- */

/* The check's capture (below): the commands of the current list so far. */
static struct {
    uint32_t commands;
} capture_count;

static void box_or_polygon_overflow(void)
{
    /* DISP3DCNT bit 13: polygon/vertex RAM overflow. The register lives in io.c, which
       clears the flag when the game writes 1 to it. */
    io_reg_store(0x060, io_reg(0x04000060) | (1u << 13));
}

static int fits32(int64_t v)
{
    return ((v >> 31) ^ (v >> 63)) == 0;
}

/* A complete polygon of the vertices given: culling, clipping, the viewport, then the
 * polygon and vertex RAM of the geometry engine's list. */
static void submit_polygon(void)
{
    PolygonList *list = &lists[geometry_list];
    uint32_t attr = ge.polyattr;
    int n = (ge.primitive & 1) ? 4 : 3;
    const GVertex *in = ge.in;
    count_polygons++;

    /* Facing: the normal of the first three vertices in (x, y, w), reduced by 4 bits at a
       time until it fits 32 bits, against the second vertex. Negative faces the viewer. */
    int64_t ax = sub32(in[0].pos[0], in[1].pos[0]), ay = sub32(in[0].pos[1], in[1].pos[1]),
            aw = sub32(in[0].pos[3], in[1].pos[3]);
    int64_t bx = sub32(in[2].pos[0], in[1].pos[0]), by = sub32(in[2].pos[1], in[1].pos[1]),
            bw = sub32(in[2].pos[3], in[1].pos[3]);
    int64_t nx = ay * bw - aw * by, ny = aw * bx - ax * bw, nz = ax * by - ay * bx;
    while (!fits32(nx) || !fits32(ny) || !fits32(nz)) {
        nx >>= 4;
        ny >>= 4;
        nz >>= 4;
    }
    int64_t dot = (int64_t) ((uint64_t) ((int64_t) in[1].pos[0] * nx) + (uint64_t) ((int64_t) in[1].pos[1] * ny) +
                             (uint64_t) ((int64_t) in[1].pos[3] * nz));
    if ((dot < 0 && (attr & (1u << 7)) == 0) || (dot > 0 && (attr & (1u << 6)) == 0)) {
        ge.last_strip = -1; /* a hidden front or back face; a line (0) is always drawn */
        return;
    }

    /* A strip's polygon shares two vertices with the previous one when that one kept its
       vertex count through clipping and those two vertices are its own, not made by
       clipping: they are taken as they are, neither clipped nor counted again. */
    GVertex cv[16];
    int start = 0, last_n = 0, id0 = 0, id1 = 0;
    const Polygon *last = NULL;
    if (ge.primitive >= 2 && ge.last_strip >= 0) {
        if (ge.primitive == 2) {
            id0 = (ge.consecutive & 1) ? 2 : 0;
            id1 = (ge.consecutive & 1) ? 1 : 2;
            last_n = 3;
        } else {
            id0 = 3;
            id1 = 2;
            last_n = 4;
        }
        const Polygon *lp = &list->poly[ge.last_strip];
        if (lp->count == last_n && !lp->v[id0].clipped && !lp->v[id1].clipped) {
            cv[0] = lp->v[id0];
            cv[1] = lp->v[id1];
            start = 2;
            last = lp;
        }
    }
    for (int i = start; i < n; i++) {
        cv[i] = in[i];
    }
    n = clip_polygon(cv, n, start, attr, 1);
    if (n == 0) {
        ge.last_strip = -1;
        return;
    }
    if (list->polygons >= POLYGON_RAM || list->vertices + n > VERTEX_RAM) {
        box_or_polygon_overflow();
        count_dropped++;
        ge.last_strip = -1;
        return;
    }

    /* The viewport: w kept to 24 bits, the division done by a 32-bit divider (a w above
       16 bits loses one bit), the screen position in 9 and 8 bits. */
    for (int i = start; i < n; i++) {
        GVertex *v = &cv[i];
        v->pos[3] &= 0xffffff;
        uint32_t w = (uint32_t) v->pos[3], px = 0, py = 0;
        if (w != 0) {
            px = (uint32_t) v->pos[0] + w;
            py = w - (uint32_t) v->pos[1];
            uint32_t den = w;
            if (w > 0xffff) {
                px >>= 1;
                py >>= 1;
                den >>= 1;
            }
            den <<= 1;
            px = (px * (uint32_t) ge.vp_w) / den + (uint32_t) ge.vp_x;
            py = (py * (uint32_t) ge.vp_h) / den + (uint32_t) ge.vp_top;
        }
        v->sx = (int32_t) (px & 0x1ff);
        v->sy = (int32_t) (py & 0xff);
    }

    /* A polygon on one dot is dropped when all its vertices are farther than DISP_1DOT_DEPTH,
       unless attribute bit 13 asks to draw it. */
    if ((attr & (1u << 13)) == 0) {
        int one_dot = 1, behind = 1;
        for (int i = 0; i < n; i++) {
            if (cv[i].sx != cv[0].sx || cv[i].sy != cv[0].sy) {
                one_dot = 0;
                break;
            }
            if ((uint32_t) cv[i].pos[3] <= ge.dot_limit) {
                behind = 0;
                break;
            }
        }
        if (one_dot && behind) {
            ge.last_strip = -1;
            return;
        }
    }

    int index = list->polygons++;
    Polygon *p = &list->poly[index];
    p->count = n;
    p->attr = attr;
    p->texparam = ge.texparam;
    p->pltt = ge.pltt;
    p->order = index;
    p->command = capture_count.commands;
    p->facing = dot <= 0;
    uint32_t alpha = (attr >> 16) & 31, format = (ge.texparam >> 26) & 7;
    p->translucent = (alpha > 0 && alpha < 31) || format == 1 || format == 6;
    p->shadow_mask = (attr & 0x3f000030u) == 0x30;
    p->shadow = (attr & 0x30) == 0x30 && !p->shadow_mask;
    p->degenerate = 0;
    if (last != NULL && n != last_n) {
        list->vertices += 2; /* the shared vertices are copied into this polygon's */
    }
    list->vertices += n - start;
    for (int i = 0; i < n; i++) {
        GVertex *v = &p->v[i];
        if (i < start) {
            *v = last->v[i == 0 ? id0 : id1]; /* as the previous polygon has it */
            continue;
        }
        *v = cv[i];
        for (int k = 0; k < 3; k++) {
            int32_t c5 = v->col[k] >> 12;
            v->rgb[k] = c5 ? (c5 << 4) + 0xf : 0; /* 9 bits */
        }
    }

    /* The top vertex (the first on the top line) and the bottom one (the rightmost on the
       bottom line); w is normalised to 16 bits in steps of 4 bits, up or down. */
    int ytop = SCREEN_H, ybot = 0, xbot = 0, wsize = 0;
    p->vtop = p->vbot = 0;
    for (int i = 0; i < n; i++) {
        const GVertex *v = &p->v[i];
        if (v->sy < ytop) {
            ytop = v->sy;
            p->vtop = i;
        }
        if (v->sy > ybot || (v->sy == ybot && v->sx > xbot)) {
            xbot = v->sx;
            ybot = v->sy;
            p->vbot = i;
        }
        uint32_t w = (uint32_t) v->pos[3];
        if (w == 0) {
            p->degenerate = 1;
        }
        while (wsize < 32 && (w >> wsize) != 0) {
            wsize += 4;
        }
    }
    p->ytop = ytop;
    p->ybot = ybot;
    if (ybot > SCREEN_H) {
        p->degenerate = 1;
    }
    p->key = ((uint32_t) ybot << 8) | (uint32_t) ytop | (p->translucent ? 0x10000u : 0);
    p->wbuffer = (ge.flush_attr >> 1) & 1;
    for (int i = 0; i < n; i++) {
        uint32_t w = (uint32_t) p->v[i].pos[3], wn, wback;
        if (wsize < 16) {
            wn = w << (16 - wsize);
            wback = wn >> (16 - wsize);
        } else {
            wn = w >> (wsize - 16);
            wback = wn << (wsize - 16);
        }
        int32_t z;
        if (p->wbuffer) {
            z = (int32_t) wback;
        } else if (w != 0) {
            /* GBATEK: ((z * 0x4000 / w) + 0x3fff) * 0x200, truncated to 32 bits */
            z = (int32_t) ((((int64_t) p->v[i].pos[2] * 0x4000) / (int32_t) w + 0x3fff) * 0x200);
        } else {
            z = 0x7ffe00;
        }
        p->z[i] = z < 0 ? 0 : z > 0xffffff ? 0xffffff : z;
        p->w[i] = (int32_t) wn;
    }
    ge.last_strip = ge.primitive >= 2 ? index : -1;
}

/* The current vertex through the clip matrix, with the current attributes; a polygon is
 * complete with its third (fourth) vertex, a strip's next one with each further vertex
 * (two for quads). Vertices count whether or not a BEGIN_VTXS is open: END_VTXS does
 * nothing (GBATEK). */
static void submit_vertex(void)
{
    GVertex *v = &ge.in[ge.in_count];
    int64_t x = ge.vtx[0], y = ge.vtx[1], z = ge.vtx[2];
    const int32_t *m = ge.clip;
    memset(v, 0, sizeof(*v));
    for (int c = 0; c < 4; c++) {
        v->pos[c] = (int32_t) ((x * m[c] + y * m[4 + c] + z * m[8 + c] + (int64_t) 0x1000 * m[12 + c]) >> 12);
    }
    for (int c = 0; c < 3; c++) {
        v->col[c] = (ge.color[c] << 12) + 0xfff;
    }
    if ((ge.texparam >> 30) == 3) {
        /* vertex-source texture coordinates: the 12 + 12 fractional bits are dropped, the
           matrix again carries the factor 16 */
        for (int c = 0; c < 2; c++) {
            int64_t s = x * ge.tex[c] + y * ge.tex[4 + c] + z * ge.tex[8 + c];
            v->tex[c] = (int16_t) (ge.raw_st[c] + (int32_t) (s >> 24));
        }
    } else {
        v->tex[0] = ge.st[0];
        v->tex[1] = ge.st[1];
    }
    ge.in_count++;
    GVertex t;
    switch (ge.primitive) {
        case 0: /* separate triangles */
        case 1: /* separate quads */
            if (ge.in_count == (ge.primitive ? 4 : 3)) {
                ge.in_count = 0;
                submit_polygon();
                ge.consecutive++;
            }
            break;
        case 2: /* triangle strips: every second triangle has its first two swapped, so that
                   the winding stays the same; the last two go on */
            if (ge.in_count < 3) {
                break;
            }
            if (ge.consecutive & 1) {
                t = ge.in[0];
                ge.in[0] = ge.in[1];
                ge.in[1] = t;
                ge.in_count = 2;
                submit_polygon();
                ge.consecutive++;
                ge.in[1] = ge.in[2];
            } else {
                ge.in_count = 2;
                submit_polygon();
                ge.consecutive++;
                ge.in[0] = ge.in[1];
                ge.in[1] = ge.in[2];
            }
            break;
        default: /* quad strips: v0 v1 v3 v2, then each new pair with the previous pair */
            if (ge.in_count == 4) {
                t = ge.in[3];
                ge.in[3] = ge.in[2];
                ge.in[2] = t;
                ge.in_count = 2;
                submit_polygon();
                ge.consecutive++;
                ge.in[0] = ge.in[3];
                ge.in[1] = ge.in[2];
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

/* BOX_TEST: whether any face of the box keeps a vertex through the clipping of polygons (with
 * its far-plane rule for the current attributes). */
static void box_test(const uint32_t *p)
{
    int16_t x0 = (int16_t) (p[0] & 0xffff), y0 = (int16_t) (p[0] >> 16), z0 = (int16_t) (p[1] & 0xffff);
    int16_t x1 = (int16_t) (x0 + (int16_t) (p[1] >> 16)), y1 = (int16_t) (y0 + (int16_t) (p[2] & 0xffff)),
            z1 = (int16_t) (z0 + (int16_t) (p[2] >> 16));
    static const int16_t corner_sel[8][3] = {{0, 0, 0}, {1, 0, 0}, {1, 1, 0}, {0, 1, 0},
                                             {0, 1, 1}, {0, 0, 1}, {1, 0, 1}, {1, 1, 1}};
    GVertex corner[8];
    for (int i = 0; i < 8; i++) {
        memset(&corner[i], 0, sizeof(corner[i]));
        transform_point(corner_sel[i][0] ? x1 : x0, corner_sel[i][1] ? y1 : y0, corner_sel[i][2] ? z1 : z0, corner[i].pos);
    }
    /* front, back, left, right, bottom, top */
    static const int faces[6][4] = {{0, 1, 2, 3}, {4, 5, 6, 7}, {0, 3, 4, 5}, {1, 2, 7, 6}, {0, 1, 6, 5}, {2, 3, 4, 7}};
    ge.box_result = 0;
    for (int f = 0; f < 6 && !ge.box_result; f++) {
        GVertex face[16];
        for (int i = 0; i < 4; i++) {
            face[i] = corner[faces[f][i]];
        }
        ge.box_result = clip_polygon(face, 4, 0, ge.polyattr, 0) > 0;
    }
}

static void pos_test(const uint32_t *p)
{
    /* POS_TEST replaces the current vertex, as on the hardware */
    ge.vtx[0] = (int16_t) (p[0] & 0xffff);
    ge.vtx[1] = (int16_t) (p[0] >> 16);
    ge.vtx[2] = (int16_t) (p[1] & 0xffff);
    transform_point(ge.vtx[0], ge.vtx[1], ge.vtx[2], ge.pos_result);
}

/* VEC_TEST: the vector through the vector matrix to 12 fractional bits, in 16 bits whose
 * top four copy bit 12 when it is set. */
static void vec_test(uint32_t param)
{
    int32_t v[3];
    unpack_vector(param, v);
    for (int c = 0; c < 3; c++) {
        uint16_t r = (uint16_t) (vector_dot(v, c) >> 9);
        if (r & 0x1000) {
            r |= 0xf000;
        }
        ge.vec_result[c] = (int16_t) r;
    }
}

/* The check's capture ---------------------------------------------------------------------- */

/* With the capture on (gpu3d_capture_start), each list keeps what it was made from: the
 * engine's state at its start (after the swap before it, as the commands that waited for that
 * swap begin), every command executed until its SWAP_BUFFERS, with the test results, and,
 * once it is rendered, the video state it was rendered from and its polygons. The layout is
 * gpu3d.h's (gpu3d_capture_write). */
typedef struct Words {
    uint32_t *w;
    size_t n, cap;
} Words;

static struct {
    int on;
    int cur_valid, last_valid; /* the list has been followed from its start */
    Words cur_state, cur_log, last_state, last_log, last_polys;
    uint8_t *regs, *mem;
} cap;

static void put(Words *b, uint32_t v)
{
    if (b->n == b->cap) {
        b->cap = b->cap ? b->cap * 2 : 4096;
        b->w = realloc(b->w, b->cap * sizeof(uint32_t));
    }
    b->w[b->n++] = v;
}

static void put_n(Words *b, const int32_t *v, size_t words)
{
    for (size_t i = 0; i < words; i++) {
        put(b, (uint32_t) v[i]);
    }
}

static void put_bytes(Words *b, const uint8_t *v, size_t n)
{
    for (size_t i = 0; i < n; i++) {
        put(b, v[i]);
    }
}

static void capture_state(Words *b)
{
    put(b, (uint32_t) ge.mode);
    put_n(b, ge.proj, 16);
    put_n(b, ge.pos, 16);
    put_n(b, ge.vec, 16);
    put_n(b, ge.tex, 16);
    put_n(b, ge.proj_stack, 16);
    put_n(b, &ge.pos_stack[0][0], 32 * 16);
    put_n(b, &ge.vec_stack[0][0], 32 * 16);
    put_n(b, ge.tex_stack, 16);
    put(b, (uint32_t) ge.proj_sp);
    put(b, (uint32_t) ge.pos_sp);
    put(b, (uint32_t) ge.tex_sp);
    put(b, (uint32_t) ge.stack_error);
    for (int i = 0; i < 3; i++) {
        put(b, (uint32_t) ge.vtx[i]);
    }
    put_bytes(b, ge.color, 3);
    put(b, (uint32_t) ge.raw_st[0]);
    put(b, (uint32_t) ge.raw_st[1]);
    put(b, (uint32_t) ge.st[0]);
    put(b, (uint32_t) ge.st[1]);
    put(b, ge.polyattr);
    put(b, ge.polyattr_next);
    put(b, ge.texparam);
    put(b, ge.pltt);
    for (int i = 0; i < 4; i++) {
        put(b, ge.light_param[i]);
    }
    put_n(b, &ge.light_vecm[0][0], 4 * 16);
    put_bytes(b, &ge.light_color[0][0], 4 * 3);
    put_bytes(b, ge.dif, 3);
    put_bytes(b, ge.amb, 3);
    put_bytes(b, ge.spe, 3);
    put_bytes(b, ge.emi, 3);
    put(b, (uint32_t) ge.use_shininess);
    put_bytes(b, ge.shininess, 128);
    put(b, ge.viewport);
    put(b, (uint32_t) ge.primitive);
    put(b, (uint32_t) ge.in_count | (ge.last_strip >= 0 ? 0x100u : 0)); /* a polygon or strip going on */
    put(b, ge.flush_attr);
    put(b, ge.dot_limit);
    put(b, ge.consecutive);
    for (int i = 0; i < 4; i++) {
        put_n(b, ge.in[i].pos, 4);
        put_n(b, ge.in[i].col, 3);
        put(b, (uint32_t) ge.in[i].tex[0]);
        put(b, (uint32_t) ge.in[i].tex[1]);
        put(b, ge.in[i].clipped);
    }
}

/* Per polygon, as the rendering engine receives it: count, attributes, TEXIMAGE_PARAM,
 * PLTT_BASE, flags (W-buffer, facing the viewer, translucent, not drawn), top and bottom
 * line, top and bottom vertex, the number of the log's command that completed it (from 1),
 * then ten vertices of x, y, depth, normalised w, the 9-bit
 * colour and the texture coordinates. */
#define CAPTURE_POLYGON_WORDS (10 + MAX_POLY_VERTICES * 9)

static void capture_polygons(Words *b, const PolygonList *list)
{
    put(b, (uint32_t) list->polygons);
    put(b, CAPTURE_POLYGON_WORDS);
    for (int i = 0; i < list->polygons; i++) {
        const Polygon *p = &list->poly[i];
        put(b, (uint32_t) p->count);
        put(b, p->attr);
        put(b, p->texparam);
        put(b, p->pltt);
        put(b, (uint32_t) (p->wbuffer | p->facing << 1 | p->translucent << 2 | p->degenerate << 3));
        put(b, (uint32_t) p->ytop);
        put(b, (uint32_t) p->ybot);
        put(b, (uint32_t) p->vtop);
        put(b, (uint32_t) p->vbot);
        put(b, p->command);
        for (int j = 0; j < MAX_POLY_VERTICES; j++) {
            const GVertex *v = &p->v[j];
            int used = j < p->count;
            put(b, used ? (uint32_t) v->sx : 0);
            put(b, used ? (uint32_t) v->sy : 0);
            put(b, used ? (uint32_t) p->z[j] : 0);
            put(b, used ? (uint32_t) p->w[j] : 0);
            for (int k = 0; k < 3; k++) {
                put(b, used ? (uint32_t) v->rgb[k] : 0);
            }
            put(b, used ? (uint32_t) v->tex[0] : 0);
            put(b, used ? (uint32_t) v->tex[1] : 0);
        }
    }
}

static void capture_list_start(void)
{
    cap.cur_state.n = 0;
    cap.cur_log.n = 0;
    capture_count.commands = 0;
    capture_state(&cap.cur_state);
    cap.cur_valid = 1;
}

/* A command of the list, before it executes. */
static void capture_command(uint32_t cmd, const uint32_t *p, int params, int results)
{
    if (!cap.on || !cap.cur_valid) {
        return;
    }
    capture_count.commands++;
    put(&cap.cur_log, cmd | ((uint32_t) params << 8) | ((uint32_t) results << 16));
    for (int i = 0; i < params; i++) {
        put(&cap.cur_log, p[i]);
    }
}

/* The list is complete and about to be rendered: it becomes the last one. */
static void capture_list_end(const PolygonList *list)
{
    if (!cap.on) {
        return;
    }
    Words t = cap.last_state;
    cap.last_state = cap.cur_state;
    cap.cur_state = t;
    t = cap.last_log;
    cap.last_log = cap.cur_log;
    cap.cur_log = t;
    cap.last_valid = cap.cur_valid;
    cap.last_polys.n = 0;
    capture_polygons(&cap.last_polys, list);
    const IoVideo *v = io_video_live();
    if (cap.regs == NULL) {
        cap.regs = malloc(IO_REG_SIZE);
        cap.mem = malloc(IO_VIDEO_SIZE);
    }
    memcpy(cap.regs, v->regs, IO_REG_SIZE);
    memcpy(cap.mem, v->mem, IO_VIDEO_SIZE);
}

void gpu3d_capture_start(void)
{
    cap.on = 1;
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

static void set_viewport(uint32_t p)
{
    /* X1,Y1 are the lower-left corner in 3D terms, Y2 the top; the sizes wrap */
    ge.viewport = p;
    int32_t x1 = (int32_t) (p & 0xff), x2 = (int32_t) ((p >> 16) & 0xff);
    int32_t bottom = (191 - (int32_t) ((p >> 8) & 0xff)) & 0xff, top = (191 - (int32_t) (p >> 24)) & 0xff;
    ge.vp_x = x1;
    ge.vp_top = top;
    ge.vp_w = (x2 - x1 + 1) & 0x1ff;
    ge.vp_h = (bottom - top + 1) & 0xff;
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
            ge.color[0] = (uint8_t) (p[0] & 31);
            ge.color[1] = (uint8_t) ((p[0] >> 5) & 31);
            ge.color[2] = (uint8_t) ((p[0] >> 10) & 31);
            break;
        case 0x21:
            set_normal(p[0]);
            break;
        case 0x22:
            set_texcoord(p[0]);
            break;
        case 0x23:
            ge.vtx[0] = (int16_t) (p[0] & 0xffff);
            ge.vtx[1] = (int16_t) (p[0] >> 16);
            ge.vtx[2] = (int16_t) (p[1] & 0xffff);
            submit_vertex();
            break;
        case 0x24:
            ge.vtx[0] = (int16_t) (sext(p[0] & 0x3ff, 10) * 64);
            ge.vtx[1] = (int16_t) (sext((p[0] >> 10) & 0x3ff, 10) * 64);
            ge.vtx[2] = (int16_t) (sext((p[0] >> 20) & 0x3ff, 10) * 64);
            submit_vertex();
            break;
        case 0x25:
            ge.vtx[0] = (int16_t) (p[0] & 0xffff);
            ge.vtx[1] = (int16_t) (p[0] >> 16);
            submit_vertex();
            break;
        case 0x26:
            ge.vtx[0] = (int16_t) (p[0] & 0xffff);
            ge.vtx[2] = (int16_t) (p[0] >> 16);
            submit_vertex();
            break;
        case 0x27:
            ge.vtx[1] = (int16_t) (p[0] & 0xffff);
            ge.vtx[2] = (int16_t) (p[0] >> 16);
            submit_vertex();
            break;
        case 0x28: /* 1.0.9 differences, as twelfths: the 10-bit value is the delta itself */
            ge.vtx[0] = (int16_t) (ge.vtx[0] + sext(p[0] & 0x3ff, 10));
            ge.vtx[1] = (int16_t) (ge.vtx[1] + sext((p[0] >> 10) & 0x3ff, 10));
            ge.vtx[2] = (int16_t) (ge.vtx[2] + sext((p[0] >> 20) & 0x3ff, 10));
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
                ge.dif[c] = (uint8_t) ((p[0] >> (5 * c)) & 31);
                ge.amb[c] = (uint8_t) ((p[0] >> (16 + 5 * c)) & 31);
            }
            if (p[0] & 0x8000) {
                memcpy(ge.color, ge.dif, 3);
            }
            break;
        case 0x31:
            for (int c = 0; c < 3; c++) {
                ge.spe[c] = (uint8_t) ((p[0] >> (5 * c)) & 31);
                ge.emi[c] = (uint8_t) ((p[0] >> (16 + 5 * c)) & 31);
            }
            ge.use_shininess = (p[0] >> 15) & 1;
            break;
        case 0x32:
            set_light_vector(p[0]);
            break;
        case 0x33:
            for (int c = 0; c < 3; c++) {
                ge.light_color[p[0] >> 30][c] = (uint8_t) ((p[0] >> (5 * c)) & 31);
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
            ge.in_count = 0;
            ge.consecutive = 0;
            ge.last_strip = -1;
            break;
        case 0x41: /* END_VTXS has no effect */
            break;
        case 0x50:
            ge.swap_pending = 1;
            ge.flush_attr = p[0] & 3;
            break;
        case 0x60:
            set_viewport(p[0]);
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
        int results = cmd == 0x70 ? 1 : cmd == 0x71 ? 4 : cmd == 0x72 ? 3 : 0;
        capture_command(cmd, params, need, results);
        execute(cmd, params);
        if (results && cap.on && cap.cur_valid) {
            if (cmd == 0x70) {
                put(&cap.cur_log, (uint32_t) ge.box_result);
            } else if (cmd == 0x71) {
                put_n(&cap.cur_log, ge.pos_result, 4);
            } else {
                for (int i = 0; i < 3; i++) {
                    put(&cap.cur_log, (uint32_t) (int32_t) ge.vec_result[i]);
                }
            }
        }
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

void gpu3d_dot_depth_write(uint32_t value)
{
    capture_command(0x81, &value, 1, 0); /* not a command: the register write, in order */
    ge.dot_limit = (value & 0x7fff) * 0x200 + 0x1ff;
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
        uint32_t lo = (uint16_t) ge.vec_result[i * 2];
        uint32_t hi = i == 0 ? (uint16_t) ge.vec_result[1] : 0;
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
        uint32_t ack = 0x8000;
        capture_command(0x80, &ack, 1, 0); /* not a command: the acknowledgement, in order */
        ge.stack_error = 0;
        ge.proj_sp = 0;
        ge.tex_sp = 0;
    }
}

/* The rendering engine ---------------------------------------------------------------------- */

/* The frame buffers: two layers of colour (6 bits each and 5-bit alpha), depth and attributes,
 * the top one what the screen shows, the bottom one what an anti-aliased edge covers. A
 * border of one pixel around the screen holds the rear plane's depth and ID for edge marking.
 * Attribute bits: 0-3 the polygon edge the pixel is on (left, right, top, bottom), 4 a back
 * face, 8-12 the anti-aliasing coverage, 15 fog, 16-21 the translucent polygon ID, 22 a
 * translucent pixel, 24-29 the opaque polygon ID. */
#define BUF_W (SCREEN_W + 2)
#define BUF_H (SCREEN_H + 2)
#define BUF_SIZE (BUF_W * BUF_H)
#define PIXEL(x, y) (BUF_W + 1 + (y) * BUF_W + (x))
#define COLOR(r, g, b, a) ((uint32_t) (r) | ((uint32_t) (g) << 8) | ((uint32_t) (b) << 16) | ((uint32_t) (a) << 24))
#define A_EDGES 0xfu
#define A_BACK 0x10u
#define A_FOG 0x8000u
#define A_TRANSLUCENT 0x400000u

static uint32_t color_buf[2 * BUF_SIZE], depth_buf[2 * BUF_SIZE], attr_buf[2 * BUF_SIZE];
static uint8_t stencil[2][SCREEN_W]; /* shadow masks, by line parity: bit 0 top, bit 1 bottom */
static int prev_shadow_mask;
static uint16_t out_color[SCREEN_H][SCREEN_W];
static uint32_t out_full[SCREEN_H][SCREEN_W];

/* The rendering registers, captured when a frame starts. */
static struct {
    uint32_t disp3dcnt, alpha_ref, clear1, clear2, fog_color, fog_offset, fog_shift;
    uint8_t fog_table[34]; /* the 32 entries with the first and last repeated at the ends */
    uint16_t toon[32], edge[8];
} rr;

static void capture_registers(void)
{
    rr.disp3dcnt = io_view_reg(0x060) & 0xffff;
    rr.alpha_ref = (rr.disp3dcnt & 4) ? io_view_reg(0x340) & 31 : 0; /* alpha 0 is never drawn */
    rr.clear1 = io_view_reg(0x350);
    rr.clear2 = io_view_reg(0x354);
    rr.fog_color = io_view_reg(0x358);
    rr.fog_offset = (io_view_reg(0x35c) & 0x7fff) * 0x200;
    rr.fog_shift = (rr.disp3dcnt >> 8) & 15;
    for (int i = 0; i < 8; i++) {
        uint32_t w = io_view_reg(0x360 + 4 * i);
        for (int j = 0; j < 4; j++) {
            rr.fog_table[1 + i * 4 + j] = (uint8_t) ((w >> (8 * j)) & 0x7f);
        }
    }
    rr.fog_table[0] = rr.fog_table[1];
    rr.fog_table[33] = rr.fog_table[32];
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

/* A 5-bit component to 6 bits: zero stays zero, others gain a low bit. */
static uint32_t c6(uint32_t c5)
{
    return c5 ? c5 * 2 + 1 : 0;
}

static uint32_t rgb555_to_6(uint32_t c)
{
    return COLOR(c6(c & 31), c6((c >> 5) & 31), c6((c >> 10) & 31), 0);
}

/* Texture memory: the 512 KiB image space and the 128 KiB palette space, by bank slot. A
 * read where no bank is mapped gives zero. */
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

static uint16_t pal_read16(uint32_t address)
{
    const uint8_t *slot = io_vram_texture_palette((int) ((address >> 14) & 7));
    if (slot == NULL) {
        return 0;
    }
    address &= 0x3ffe;
    return (uint16_t) (slot[address] | (slot[address + 1] << 8));
}

/* (c0 * a + c1 * b) / 8 per component, for 4x4 compressed textures' mixed colours. */
static uint32_t mix555(uint32_t c0, uint32_t c1, uint32_t a, uint32_t b, uint32_t shift)
{
    uint32_t r = (((c0 & 0x1f) * a + (c1 & 0x1f) * b) >> shift) & 0x1f;
    uint32_t g = (((c0 & 0x3e0) * a + (c1 & 0x3e0) * b) >> shift) & 0x3e0;
    uint32_t bl = (((c0 & 0x7c00) * a + (c1 & 0x7c00) * b) >> shift) & 0x7c00;
    return r | g | bl;
}

/* One texel at (s, t) in 1.11.4 after repeat, flip or clamp: the RGB555 colour and a 5-bit
 * alpha (0 transparent). */
static void sample_texture(uint32_t param, uint32_t pltt, int32_t s, int32_t t, uint32_t *color, uint32_t *alpha)
{
    int32_t width = 8 << ((param >> 20) & 7), height = 8 << ((param >> 23) & 7);
    s >>= 4;
    t >>= 4;
    if (param & (1u << 16)) {
        s = ((param & (1u << 18)) && (s & width)) ? (width - 1) - (s & (width - 1)) : s & (width - 1);
    } else {
        s = s < 0 ? 0 : s >= width ? width - 1 : s;
    }
    if (param & (1u << 17)) {
        t = ((param & (1u << 19)) && (t & height)) ? (height - 1) - (t & (height - 1)) : t & (height - 1);
    } else {
        t = t < 0 ? 0 : t >= height ? height - 1 : t;
    }
    uint32_t base = (param & 0xffff) << 3, texel = (uint32_t) (t * width + s);
    uint32_t alpha0 = (param & (1u << 29)) ? 0 : 31; /* colour 0 transparent */
    uint32_t v, pal = pltt << 4;
    switch ((param >> 26) & 7) {
        case 1: /* A3I5 */
            v = tex_read8(base + texel);
            *color = pal_read16(pal + (v & 31) * 2);
            *alpha = ((v >> 3) & 0x1c) + (v >> 6);
            return;
        case 2: /* 4 colours, the palette base in 8-byte steps */
            v = (uint32_t) (tex_read8(base + texel / 4) >> ((s & 3) * 2)) & 3;
            *color = pal_read16((pltt << 3) + v * 2);
            *alpha = v ? 31 : alpha0;
            return;
        case 3: /* 16 colours */
            v = tex_read8(base + texel / 2);
            v = (s & 1) ? v >> 4 : v & 15;
            *color = pal_read16(pal + v * 2);
            *alpha = v ? 31 : alpha0;
            return;
        case 4: /* 256 colours */
            v = tex_read8(base + texel);
            *color = pal_read16(pal + v * 2);
            *alpha = v ? 31 : alpha0;
            return;
        case 5: { /* 4x4 blocks of 2-bit texels in slot 0 or 2, a palette word per block in slot 1;
                     the address wraps at the end of slot 3, and texels in slot 1 read as zero */
            uint32_t addr = (base + (uint32_t) ((t & 0x3fc) * (width >> 2)) + (uint32_t) (s & 0x3fc) + (uint32_t) (t & 3)) &
                            0x7ffff;
            uint32_t info_addr = 0x20000 + ((addr & 0x1fffc) >> 1) + (addr >= 0x40000 ? 0x10000 : 0);
            v = (addr >= 0x20000 && addr < 0x40000) ? 0 : (uint32_t) (tex_read8(addr) >> (2 * (s & 3))) & 3;
            uint32_t info = tex_read16(info_addr), mode = info >> 14;
            uint32_t pbase = pal + ((info & 0x3fff) << 2);
            *alpha = 31;
            switch (v) {
                case 0:
                    *color = pal_read16(pbase);
                    break;
                case 1:
                    *color = pal_read16(pbase + 2);
                    break;
                case 2:
                    if (mode == 1) {
                        *color = mix555(pal_read16(pbase), pal_read16(pbase + 2), 1, 1, 1);
                    } else if (mode == 3) {
                        *color = mix555(pal_read16(pbase), pal_read16(pbase + 2), 5, 3, 3);
                    } else {
                        *color = pal_read16(pbase + 4);
                    }
                    break;
                default:
                    if (mode == 2) {
                        *color = pal_read16(pbase + 6);
                    } else if (mode == 3) {
                        *color = mix555(pal_read16(pbase), pal_read16(pbase + 2), 3, 5, 3);
                    } else {
                        *color = 0;
                        *alpha = 0;
                    }
                    break;
            }
            return;
        }
        case 6: /* A5I3 */
            v = tex_read8(base + texel);
            *color = pal_read16(pal + (v & 7) * 2);
            *alpha = v >> 3;
            return;
        case 7: /* direct colour, bit 15 the alpha */
            *color = tex_read16(base + texel * 2);
            *alpha = (*color & 0x8000) ? 31 : 0;
            return;
        default:
            *color = 0;
            *alpha = 31;
            return;
    }
}

/* A pixel's colour from its 6-bit vertex colour and texture coordinates, by the polygon's
 * mode (GBATEK, "DS 3D Texture Blending"): modulation, decal, toon or highlight (the toon
 * table indexed by the vertex red), shadow (as modulation). */
static uint32_t shade(const Polygon *p, uint32_t vr, uint32_t vg, uint32_t vb, int16_t s, int16_t t)
{
    uint32_t mode = (p->attr >> 4) & 3, polyalpha = (p->attr >> 16) & 31;
    uint32_t r, g, b, a;
    int highlight = mode == 2 && (rr.disp3dcnt & 2);
    if (mode == 2) {
        if (highlight) {
            vg = vb = vr; /* the colour is computed from grey; the toon colour is added after */
        } else {
            uint32_t toon = rgb555_to_6(rr.toon[vr >> 1]);
            vr = toon & 0x3f;
            vg = (toon >> 8) & 0x3f;
            vb = (toon >> 16) & 0x3f;
        }
    }
    if ((rr.disp3dcnt & 1) && ((p->texparam >> 26) & 7) != 0) {
        uint32_t tc, ta;
        sample_texture(p->texparam, p->pltt, s, t, &tc, &ta);
        uint32_t tx = rgb555_to_6(tc), tr = tx & 0x3f, tg = (tx >> 8) & 0x3f, tb = (tx >> 16) & 0x3f;
        if (mode & 1) { /* decal (and shadow) */
            if (ta == 0) {
                r = vr, g = vg, b = vb;
            } else if (ta == 31) {
                r = tr, g = tg, b = tb;
            } else {
                r = (tr * ta + vr * (31 - ta)) >> 5;
                g = (tg * ta + vg * (31 - ta)) >> 5;
                b = (tb * ta + vb * (31 - ta)) >> 5;
            }
            a = polyalpha;
        } else {
            r = ((tr + 1) * (vr + 1) - 1) >> 6;
            g = ((tg + 1) * (vg + 1) - 1) >> 6;
            b = ((tb + 1) * (vb + 1) - 1) >> 6;
            a = ((ta + 1) * (polyalpha + 1) - 1) >> 5;
        }
    } else {
        r = vr, g = vg, b = vb;
        a = polyalpha;
    }
    if (highlight) {
        uint32_t toon = rgb555_to_6(rr.toon[vr >> 1]);
        r += toon & 0x3f;
        g += (toon >> 8) & 0x3f;
        b += (toon >> 16) & 0x3f;
        r = r > 63 ? 63 : r;
        g = g > 63 ? 63 : g;
        b = b > 63 ? 63 : b;
    }
    if (polyalpha == 0) {
        a = 31; /* wire frames are solid */
    }
    return COLOR(r & 0xff, g & 0xff, b & 0xff, a & 0xff);
}

/* Interpolation along an edge (by line) or a span (by pixel). The hardware finds a
 * perspective-correct factor from the two w's, 9 bits along an edge and 8 along a span, and
 * moves each attribute linearly by it; with equal w's whose low bits are clear (bits 0-6
 * along a span, 1-6 along an edge) it interpolates linearly. Z-buffer depth is always linear,
 * with the hardware's reciprocal of the length. */
typedef struct Interp {
    int32_t x0, xdiff, x;
    int shift, linear, wbuffer, along_y;
    int32_t zrecip, w0n, w0d, w1d;
    uint32_t f;
} Interp;

static void interp_setup(Interp *ip, int32_t x0, int32_t x1, int32_t w0, int32_t w1, int wbuffer, int along_y)
{
    ip->x0 = x0;
    ip->xdiff = x1 - x0;
    ip->x = 0;
    ip->f = 0;
    ip->wbuffer = wbuffer;
    ip->along_y = along_y;
    ip->zrecip = ip->xdiff != 0 ? (1 << 22) / ip->xdiff : 0;
    int32_t mask = along_y ? 0x7e : 0x7f;
    ip->linear = w0 == w1 && !(w0 & mask);
    if (along_y) {
        ip->w0n = w0 >> 1;
        ip->w0d = (w0 + ((w0 & ~w1) & 1)) >> 1;
        ip->w1d = w1 >> 1;
        ip->shift = 9;
    } else {
        ip->w0n = w0;
        ip->w0d = w0;
        ip->w1d = w1;
        ip->shift = 8;
    }
}

static void interp_at(Interp *ip, int32_t x)
{
    x -= ip->x0;
    ip->x = x;
    if (ip->xdiff != 0 && (!ip->linear || ip->wbuffer)) {
        uint32_t num = ((uint32_t) x * (uint32_t) ip->w0n) << ip->shift;
        uint32_t den = (uint32_t) x * (uint32_t) ip->w0d + (uint32_t) (ip->xdiff - x) * (uint32_t) ip->w1d;
        ip->f = den ? num / den : 0;
    }
}

static int32_t interp_value(const Interp *ip, int32_t a, int32_t b)
{
    if (ip->xdiff == 0 || a == b) {
        return a;
    }
    if (!ip->linear) {
        if (a < b) {
            return (int32_t) ((uint32_t) a + (((uint32_t) (b - a) * ip->f) >> ip->shift));
        }
        return (int32_t) ((uint32_t) b + (((uint32_t) (a - b) * ((1u << ip->shift) - ip->f)) >> ip->shift));
    }
    if (a < b) {
        return (int32_t) (a + (int64_t) (b - a) * ip->x / ip->xdiff);
    }
    return (int32_t) (b + (int64_t) (a - b) * (ip->xdiff - ip->x) / ip->xdiff);
}

static int32_t interp_depth(const Interp *ip, int32_t a, int32_t b)
{
    if (ip->xdiff == 0 || a == b) {
        return a;
    }
    if (ip->wbuffer) {
        if (a < b) {
            return (int32_t) (a + (((int64_t) (b - a) * ip->f) >> ip->shift));
        }
        return (int32_t) (b + (((int64_t) (a - b) * (int64_t) (uint32_t) ((1u << ip->shift) - ip->f)) >> ip->shift));
    }
    int32_t base = a < b ? a : b, disp = a < b ? b - a : a - b, factor = a < b ? ip->x : ip->xdiff - ip->x;
    if (ip->along_y) {
        int shift = 0;
        while (disp > 0x3ff) {
            disp >>= 1;
            shift++;
        }
        return (int32_t) (base + ((((int64_t) disp * factor * ip->zrecip) >> 22) << shift));
    }
    disp >>= 9;
    return (int32_t) (base + (((int64_t) disp * factor * ip->zrecip) >> 13));
}

/* A polygon edge from one vertex to the next, stepped by line: x in 18 fractional bits from
 * the reciprocal of the height (1/y times x, as the hardware computes it), the start offset by
 * half a pixel on x-major edges; the pixels an x-major edge covers on a line, and its
 * anti-aliasing coverage. */
typedef struct Edge {
    int32_t x0, xmin, xmax, xlen, ylen, dx, y, inc, xcov_incr;
    int negative, xmajor, right;
    Interp ip;
} Edge;

static int32_t edge_x(const Edge *e)
{
    int32_t x = e->negative ? e->x0 - (e->dx >> 18) : e->x0 + (e->dx >> 18);
    return x < e->xmin ? e->xmin : x > e->xmax ? e->xmax : x;
}

static int32_t edge_setup(Edge *e, int right, int32_t x0, int32_t x1, int32_t y0, int32_t y1, int32_t w0, int32_t w1,
                          int32_t y, int wbuffer)
{
    e->right = right;
    e->x0 = x0;
    e->y = y;
    if (x1 > x0) {
        e->xmin = x0;
        e->xmax = x1 - 1;
        e->negative = 0;
    } else if (x1 < x0) {
        e->xmin = x1;
        e->xmax = x0 - 1;
        e->negative = 1;
    } else {
        e->xmin = e->xmax = x0;
        e->negative = 0;
    }
    e->xlen = e->xmax + 1 - e->xmin;
    e->ylen = y1 - y0;
    if (e->ylen == 0) {
        e->inc = 0;
    } else if (e->ylen == e->xlen && e->xlen != 1) {
        e->inc = 0x40000;
    } else {
        e->inc = (x1 - x0) * ((1 << 18) / e->ylen);
        if (e->inc < 0) {
            e->inc = -e->inc;
        }
    }
    e->xmajor = e->inc > 0x40000;
    if (e->xmajor) {
        e->dx = right ? (e->negative ? 0x60000 : e->inc - 0x20000) : (e->negative ? e->inc - 0x20000 + 0x40000 : 0x20000);
    } else {
        e->dx = (e->inc != 0 && e->negative) ? 0x40000 : 0;
    }
    e->dx += (y - y0) * e->inc;
    int32_t offset = (e->inc >= 0x40000) && (right ^ e->negative);
    interp_setup(&e->ip, y0 - offset, y1 - offset, w0, w1, wbuffer, 1);
    interp_at(&e->ip, y);
    e->xcov_incr = e->xmajor ? (e->ylen << 10) / e->xlen : 0;
    return edge_x(e);
}

/* The edges of a polygon on one line: both at x. */
static int32_t edge_point(Edge *e, int right, int32_t x0, int wbuffer)
{
    memset(e, 0, sizeof(*e));
    e->right = right;
    e->x0 = e->xmin = e->xmax = x0;
    interp_setup(&e->ip, 0, 0, 0, 0, wbuffer, 1);
    interp_at(&e->ip, 0);
    return x0;
}

static int32_t edge_step(Edge *e)
{
    e->dx += e->inc;
    e->y++;
    interp_at(&e->ip, e->y);
    return edge_x(e);
}

/* The pixels the edge covers on this line (`length`) and its coverage: for an x-major edge
 * bit 31 set, the first pixel's coverage in bits 12-21 and the step per pixel in bits 0-9;
 * for a y-major edge the 5-bit coverage itself. With the polygon's left and right edges
 * swapped on this line, the length is one pixel and y-major coverages turn over. */
static void edge_params(const Edge *e, int swapped, int32_t *length, uint32_t *coverage)
{
    *length = 1;
    if (e->xmajor) {
        if (e->right ^ e->negative) {
            *length = (e->dx >> 18) - ((e->dx - e->inc) >> 18);
        } else {
            *length = ((e->dx + e->inc) >> 18) - (e->dx >> 18);
        }
        int32_t startx = e->dx >> 18;
        if (e->negative) {
            startx = e->xlen - startx;
        }
        if (e->right) {
            startx = startx - *length + 1;
        }
        int32_t startcov = (int32_t) (((int64_t) ((startx << 10) + 0x1ff) * e->ylen) / e->xlen);
        *coverage = 0x80000000u | (((uint32_t) startcov & 0x3ff) << 12) | ((uint32_t) e->xcov_incr & 0x3ff);
        if (swapped) {
            *length = 1;
        }
        return;
    }
    if (e->inc == 0) {
        *coverage = swapped ? 0 : 31; /* vertical */
        return;
    }
    int32_t cov = ((e->dx >> 9) + (e->inc >> 10)) >> 4;
    if ((cov >> 5) != (e->dx >> 18)) {
        cov = 31;
    }
    cov &= 31;
    if (swapped ? (e->right ^ e->negative) : !(e->right ^ e->negative)) {
        cov = 31 - cov;
    }
    *coverage = (uint32_t) cov;
}

/* A polygon being rasterised: its left and right edges and their vertices (current and next;
 * the left side walks the vertices forward for a front face, the right side backward). */
typedef struct Raster {
    const Polygon *p;
    Edge l, r;
    int32_t xl, xr;
    int cl, nl, cr, nr;
} Raster;

static Raster raster[POLYGON_RAM];

static int next_vertex(const Polygon *p, int i, int forward)
{
    if (forward) {
        return i + 1 >= p->count ? 0 : i + 1;
    }
    return i - 1 < 0 ? p->count - 1 : i - 1;
}

static void left_edge(Raster *rp, int32_t y)
{
    const Polygon *p = rp->p;
    while (y >= p->v[rp->nl].sy && rp->cl != p->vbot) {
        rp->cl = rp->nl;
        rp->nl = next_vertex(p, rp->cl, p->facing);
    }
    rp->xl = edge_setup(&rp->l, 0, p->v[rp->cl].sx, p->v[rp->nl].sx, p->v[rp->cl].sy, p->v[rp->nl].sy, p->w[rp->cl],
                        p->w[rp->nl], y, p->wbuffer);
}

static void right_edge(Raster *rp, int32_t y)
{
    const Polygon *p = rp->p;
    while (y >= p->v[rp->nr].sy && rp->cr != p->vbot) {
        rp->cr = rp->nr;
        rp->nr = next_vertex(p, rp->cr, !p->facing);
    }
    rp->xr = edge_setup(&rp->r, 1, p->v[rp->cr].sx, p->v[rp->nr].sx, p->v[rp->cr].sy, p->v[rp->nr].sy, p->w[rp->cr],
                        p->w[rp->nr], y, p->wbuffer);
}

static void raster_setup(Raster *rp, const Polygon *p)
{
    rp->p = p;
    rp->cl = rp->cr = p->vtop;
    rp->nl = next_vertex(p, p->vtop, p->facing);
    rp->nr = next_vertex(p, p->vtop, !p->facing);
    if (p->ytop == p->ybot) {
        /* a polygon on one line spans from its leftmost to its rightmost vertex, of the
           first, second and last */
        int lo = 0, hi = 0;
        int cand[2] = {1, p->count - 1};
        for (int k = 0; k < 2; k++) {
            int i = cand[k];
            if (p->v[i].sx < p->v[lo].sx) {
                lo = i;
            }
            if (p->v[i].sx > p->v[hi].sx) {
                hi = i;
            }
        }
        rp->cl = rp->nl = lo;
        rp->cr = rp->nr = hi;
        rp->xl = edge_point(&rp->l, 0, p->v[lo].sx, p->wbuffer);
        rp->xr = edge_point(&rp->r, 1, p->v[hi].sx, p->wbuffer);
        return;
    }
    left_edge(rp, p->ytop);
    right_edge(rp, p->ytop);
}

/* What a line of a polygon covers: the span and its ends' depth and w, which edges are drawn
 * and how far, the vertices and interpolators of the span's left and right end. */
typedef struct Span {
    int32_t xstart, xend, wl, wr, zl, zr;
    int32_t l_len, r_len;
    uint32_t l_cov, r_cov;
    int l_fill, r_fill;
    const GVertex *lcur, *lnext, *rcur, *rnext;
    const Interp *ileft, *iright;
    int yedge;
} Span;

static void span_setup(Raster *rp, int32_t y, Span *sp)
{
    const Polygon *p = rp->p;
    if (p->ytop != p->ybot) {
        if (y >= p->v[rp->nl].sy && rp->cl != p->vbot) {
            left_edge(rp, y);
        }
        if (y >= p->v[rp->nr].sy && rp->cr != p->vbot) {
            right_edge(rp, y);
        }
    }
    sp->xstart = rp->xl;
    sp->xend = rp->xr;
    sp->wl = interp_value(&rp->l.ip, p->w[rp->cl], p->w[rp->nl]);
    sp->wr = interp_value(&rp->r.ip, p->w[rp->cr], p->w[rp->nr]);
    sp->zl = interp_depth(&rp->l.ip, p->z[rp->cl], p->z[rp->nl]);
    sp->zr = interp_depth(&rp->r.ip, p->z[rp->cr], p->z[rp->nr]);
    /* a vertical right edge is drawn one pixel to the left, unless the span is a single
       pixel under a vertical left edge or at the screen's left border */
    if (rp->r.inc == 0 && (rp->l.inc != 0 || sp->xstart != sp->xend) && sp->xend != 0) {
        sp->xend--;
    }
    uint32_t alpha = (p->attr >> 16) & 31;
    int all = (rr.disp3dcnt & 0x30) || (alpha < 31 && (rr.disp3dcnt & 8)) || alpha == 0;
    int bottom = y == p->ybot - 1;
    if (sp->xstart > sp->xend) {
        /* the edges cross on this line: drawn from the right edge to the left one */
        sp->lcur = &p->v[rp->cr];
        sp->lnext = &p->v[rp->nr];
        sp->rcur = &p->v[rp->cl];
        sp->rnext = &p->v[rp->nl];
        sp->ileft = &rp->r.ip;
        sp->iright = &rp->l.ip;
        edge_params(&rp->r, 1, &sp->l_len, &sp->l_cov);
        edge_params(&rp->l, 1, &sp->r_len, &sp->r_cov);
        int32_t t = sp->xstart;
        sp->xstart = sp->xend;
        sp->xend = t;
        t = sp->wl, sp->wl = sp->wr, sp->wr = t;
        t = sp->zl, sp->zl = sp->zr, sp->zr = t;
        int differ = sp->lnext->sx != sp->rnext->sx;
        sp->l_fill = all || rp->r.negative || !rp->r.xmajor || (bottom && rp->r.xmajor && differ);
        sp->r_fill = all || (!rp->l.negative && rp->l.xmajor) || (!(rp->l.negative && rp->l.xmajor) && rp->r.inc == 0) ||
                     (bottom && rp->l.xmajor && differ);
    } else {
        sp->lcur = &p->v[rp->cl];
        sp->lnext = &p->v[rp->nl];
        sp->rcur = &p->v[rp->cr];
        sp->rnext = &p->v[rp->nr];
        sp->ileft = &rp->l.ip;
        sp->iright = &rp->r.ip;
        edge_params(&rp->l, 0, &sp->l_len, &sp->l_cov);
        edge_params(&rp->r, 0, &sp->r_len, &sp->r_cov);
        /* filled: left edges of slope up to 1, right edges steeper than that or vertical,
           the bottom pixels of x-major edges next to a flat bottom, and the left edge of a
           span both edges of which cover whole */
        int differ = sp->lnext->sx != sp->rnext->sx;
        sp->l_fill = all || rp->l.negative || !rp->l.xmajor || (bottom && rp->l.xmajor && differ) ||
                     (rp->l.inc == rp->r.inc && sp->xstart + sp->l_len == sp->xend + 1);
        sp->r_fill = all || (!rp->r.negative && rp->r.xmajor) || rp->r.inc == 0 || (bottom && rp->r.xmajor && differ);
    }
    sp->yedge = y == p->ytop ? 4 : y == p->ybot - 1 ? 8 : 0;
}

/* The depth test: less, or less or equal over an opaque back face for a front face; within
 * 0x200 (Z) or 0xff (W) with attribute bit 14. */
static int depth_pass(const Polygon *p, uint32_t dst, int32_t z, uint32_t dstattr)
{
    if (p->attr & (1u << 14)) {
        int32_t d = (int32_t) dst - z;
        return p->wbuffer ? (uint32_t) (d + 0xff) <= 0x1fe : (uint32_t) (d + 0x200) <= 0x400;
    }
    if (p->facing && (dstattr & (A_TRANSLUCENT | A_BACK)) == A_BACK) {
        return z <= (int32_t) dst;
    }
    return z < (int32_t) dst;
}

/* A translucent pixel: not over a translucent pixel of the same ID (a shadow: not over the
 * pixel of its own ID, opaque or translucent), blended when enabled over a pixel with alpha,
 * alpha the greater of the two, fog only where both ask for it. */
static void plot_translucent(int addr, uint32_t color, int32_t z, int write_depth, uint32_t polyattr, int shadow)
{
    uint32_t dst = attr_buf[addr];
    uint32_t attr = (polyattr & 0xe0f0) | ((polyattr >> 8) & 0xff0000) | A_TRANSLUCENT | (dst & 0xff001f0fu);
    if (shadow && !(dst & A_TRANSLUCENT)) {
        if ((dst & 0x3f000000u) == (polyattr & 0x3f000000u)) {
            return;
        }
    } else if ((dst & 0x7f0000) == (attr & 0x7f0000)) {
        return;
    }
    if (!(dst & A_FOG)) {
        attr &= ~A_FOG;
    }
    uint32_t below = color_buf[addr], alpha = color >> 24, dst_alpha = below >> 24;
    if (dst_alpha != 0) {
        uint32_t r = color & 0x3f, g = (color >> 8) & 0x3f, b = (color >> 16) & 0x3f;
        if (rr.disp3dcnt & 8) {
            uint32_t k = alpha + 1;
            r = (r * k + (below & 0x3f) * (32 - k)) >> 5;
            g = (g * k + ((below >> 8) & 0x3f) * (32 - k)) >> 5;
            b = (b * k + ((below >> 16) & 0x3f) * (32 - k)) >> 5;
        }
        color = COLOR(r, g, b, alpha > dst_alpha ? alpha : dst_alpha);
    }
    if (write_depth) {
        depth_buf[addr] = (uint32_t) z;
    }
    color_buf[addr] = color;
    attr_buf[addr] = attr;
}

/* The three parts of a span: the left edge, the inside, the right edge. */
enum { PART_LEFT, PART_INSIDE, PART_RIGHT };

static void draw_line(Raster *rp, int32_t y)
{
    const Polygon *p = rp->p;
    uint32_t polyattr = (p->attr & 0x3f008000u) | (p->facing ? 0 : A_BACK);
    int wireframe = ((p->attr >> 16) & 31) == 0;
    prev_shadow_mask = 0;
    Span sp;
    span_setup(rp, y, &sp);
    /* the attributes at the span's ends */
    int32_t cl[3], cr[3], sl, tl, sr, tr;
    for (int k = 0; k < 3; k++) {
        cl[k] = interp_value(sp.ileft, sp.lcur->rgb[k], sp.lnext->rgb[k]);
        cr[k] = interp_value(sp.iright, sp.rcur->rgb[k], sp.rnext->rgb[k]);
    }
    sl = interp_value(sp.ileft, sp.lcur->tex[0], sp.lnext->tex[0]);
    tl = interp_value(sp.ileft, sp.lcur->tex[1], sp.lnext->tex[1]);
    sr = interp_value(sp.iright, sp.rcur->tex[0], sp.rnext->tex[0]);
    tr = interp_value(sp.iright, sp.rcur->tex[1], sp.rnext->tex[1]);
    Interp ix;
    interp_setup(&ix, sp.xstart, sp.xend + 1, sp.wl, sp.wr, p->wbuffer, 0);
    int32_t x = sp.xstart < 0 ? 0 : sp.xstart, xcov = 0;
    int aa = (rr.disp3dcnt & 0x10) != 0;
    for (int part = PART_LEFT; part <= PART_RIGHT; part++) {
        int32_t limit;
        uint32_t edge = (uint32_t) sp.yedge, cov_param = 0;
        if (part == PART_LEFT) {
            limit = sp.xstart + sp.l_len;
            edge |= 1;
            cov_param = sp.l_cov;
        } else if (part == PART_INSIDE) {
            limit = sp.xend - sp.r_len + 1;
        } else {
            limit = sp.xend + 1;
            edge |= 2;
            cov_param = sp.r_cov;
        }
        if (limit > sp.xend + 1) {
            limit = sp.xend + 1;
        }
        if (limit > SCREEN_W) {
            limit = SCREEN_W;
        }
        if (cov_param & 0x80000000u) {
            xcov = (int32_t) ((cov_param >> 12) & 0x3ff);
            if (xcov == 0x3ff) {
                xcov = 0;
            }
        }
        if ((part == PART_LEFT && !sp.l_fill) || (part == PART_INSIDE && wireframe && !sp.yedge)) {
            if (x < limit) {
                x = limit;
            }
            continue;
        }
        if (part == PART_RIGHT && !sp.r_fill) {
            continue;
        }
        for (; x < limit; x++) {
            int addr = PIXEL(x, y);
            uint32_t dstattr = attr_buf[addr];
            if (p->shadow) {
                uint8_t st = stencil[y & 1][x];
                if (!st) {
                    continue;
                }
                if (!(st & 1)) {
                    addr += BUF_SIZE;
                }
                if (!(st & 2)) {
                    dstattr &= ~A_EDGES; /* not under an anti-aliased edge */
                }
            }
            interp_at(&ix, x);
            int32_t z = interp_depth(&ix, sp.zl, sp.zr);
            /* failing against the top pixel, an edge pixel's lower one is tried */
            if (!depth_pass(p, depth_buf[addr], z, dstattr)) {
                if (!(dstattr & A_EDGES) || addr >= BUF_SIZE) {
                    continue;
                }
                addr += BUF_SIZE;
                dstattr = attr_buf[addr];
                if (!depth_pass(p, depth_buf[addr], z, dstattr)) {
                    continue;
                }
            }
            uint32_t vr = (uint32_t) interp_value(&ix, cl[0], cr[0]), vg = (uint32_t) interp_value(&ix, cl[1], cr[1]),
                     vb = (uint32_t) interp_value(&ix, cl[2], cr[2]);
            int16_t s = (int16_t) interp_value(&ix, sl, sr), t = (int16_t) interp_value(&ix, tl, tr);
            uint32_t color = shade(p, (vr >> 3) & 0xff, (vg >> 3) & 0xff, (vb >> 3) & 0xff, s, t);
            uint32_t alpha = color >> 24;
            if (alpha <= rr.alpha_ref) {
                continue;
            }
            if (alpha == 31) {
                uint32_t attr = polyattr | edge;
                if (aa && (part != PART_INSIDE || (attr & A_EDGES))) {
                    uint32_t cov = 31;
                    if (part != PART_INSIDE) {
                        cov = cov_param;
                        if (cov & 0x80000000u) {
                            int32_t c = part == PART_LEFT ? xcov >> 5 : 31 - (xcov >> 5);
                            cov = (uint32_t) (c < 0 ? 0 : c > 31 ? 31 : c);
                            xcov += (int32_t) (cov_param & 0x3ff);
                        }
                    }
                    attr |= cov << 8;
                    if (addr < BUF_SIZE) { /* the pixel under the edge is kept below */
                        color_buf[addr + BUF_SIZE] = color_buf[addr];
                        depth_buf[addr + BUF_SIZE] = depth_buf[addr];
                        attr_buf[addr + BUF_SIZE] = attr_buf[addr];
                    }
                }
                depth_buf[addr] = (uint32_t) z;
                color_buf[addr] = color;
                attr_buf[addr] = attr;
            } else {
                int write_depth = (p->attr & (1u << 11)) != 0;
                plot_translucent(addr, color, z, write_depth, polyattr, p->shadow);
                if ((dstattr & A_EDGES) && addr < BUF_SIZE) {
                    plot_translucent(addr + BUF_SIZE, color, z, write_depth, polyattr, p->shadow);
                }
            }
        }
    }
    rp->xl = edge_step(&rp->l);
    rp->xr = edge_step(&rp->r);
}

/* A shadow mask's line: where it fails the depth test it marks the stencil (bit 1 for the
 * lower pixel under an edge); it draws nothing. The stencil is cleared when a mask follows
 * another polygon. */
static void mask_line(Raster *rp, int32_t y)
{
    const Polygon *p = rp->p;
    uint32_t alpha = (p->attr >> 16) & 31;
    int wireframe = alpha == 0;
    if (!prev_shadow_mask) {
        memset(stencil[y & 1], 0, SCREEN_W);
    }
    prev_shadow_mask = 1;
    Span sp;
    span_setup(rp, y, &sp);
    if (wireframe) {
        alpha = 31;
    }
    if (alpha > rr.alpha_ref) {
        Interp ix;
        interp_setup(&ix, sp.xstart, sp.xend + 1, sp.wl, sp.wr, p->wbuffer, 0);
        int32_t x = sp.xstart < 0 ? 0 : sp.xstart;
        for (int part = PART_LEFT; part <= PART_RIGHT; part++) {
            int32_t limit = part == PART_LEFT ? sp.xstart + sp.l_len : part == PART_INSIDE ? sp.xend - sp.r_len + 1 : sp.xend + 1;
            if (limit > sp.xend + 1) {
                limit = sp.xend + 1;
            }
            if (limit > SCREEN_W) {
                limit = SCREEN_W;
            }
            if ((part == PART_LEFT && !sp.l_fill) || (part == PART_INSIDE && wireframe && !sp.yedge)) {
                if (x < limit) {
                    x = limit;
                }
                continue;
            }
            if (part == PART_RIGHT && !sp.r_fill) {
                continue;
            }
            for (; x < limit; x++) {
                int addr = PIXEL(x, y);
                interp_at(&ix, x);
                int32_t z = interp_depth(&ix, sp.zl, sp.zr);
                uint32_t dstattr = attr_buf[addr];
                if (!depth_pass(p, depth_buf[addr], z, dstattr)) {
                    stencil[y & 1][x] = 1;
                }
                if (dstattr & A_EDGES) {
                    if (!depth_pass(p, depth_buf[addr + BUF_SIZE], z, attr_buf[addr + BUF_SIZE])) {
                        stencil[y & 1][x] |= 2;
                    }
                }
            }
        }
    }
    rp->xl = edge_step(&rp->l);
    rp->xr = edge_step(&rp->r);
}

/* The rear plane: one colour, depth, ID and fog flag for the screen, or the two bitmaps in
 * texture slots 2 and 3 scrolled by CLRIMAGE_OFFSET (DISP3DCNT bit 14); the depth gains 0x1ff
 * below its 15 bits. The border holds the depth and ID; the lower layer starts empty. */
static void clear_frame(void)
{
    uint32_t depth = (rr.clear2 & 0x7fff) * 0x200 + 0x1ff, id = rr.clear1 & 0x3f000000u;
    memset(color_buf + BUF_SIZE, 0, BUF_SIZE * sizeof(uint32_t));
    memset(depth_buf + BUF_SIZE, 0, BUF_SIZE * sizeof(uint32_t));
    memset(attr_buf + BUF_SIZE, 0, BUF_SIZE * sizeof(uint32_t));
    for (int i = 0; i < BUF_SIZE; i++) {
        color_buf[i] = 0;
        depth_buf[i] = depth;
        attr_buf[i] = id;
    }
    if (rr.disp3dcnt & (1u << 14)) {
        uint32_t xofs = (rr.clear2 >> 16) & 0xff, yofs = (rr.clear2 >> 24) & 0xff;
        for (int y = 0; y < SCREEN_H; y++) {
            for (int x = 0; x < SCREEN_W; x++) {
                uint32_t at = (((yofs + (uint32_t) y) & 0xff) << 9) + (((xofs + (uint32_t) x) & 0xff) << 1);
                uint16_t c = tex_read16(0x40000 + at), d = tex_read16(0x60000 + at);
                int addr = PIXEL(x, y);
                color_buf[addr] = rgb555_to_6(c) | ((c & 0x8000) ? 0x1f000000u : 0);
                depth_buf[addr] = (d & 0x7fffu) * 0x200 + 0x1ff;
                attr_buf[addr] = id | (d & 0x8000u);
            }
        }
        return;
    }
    uint32_t color = rgb555_to_6(rr.clear1) | (((rr.clear1 >> 16) & 31) << 24);
    for (int y = 0; y < SCREEN_H; y++) {
        for (int x = 0; x < SCREEN_W; x++) {
            int addr = PIXEL(x, y);
            color_buf[addr] = color;
            attr_buf[addr] = id | (rr.clear1 & 0x8000u);
        }
    }
}

/* Edge marking: a top pixel on a polygon edge whose opaque ID differs from a neighbour's,
 * and that is nearer than it, takes the edge colour of its ID group (the alpha stays) and
 * half coverage. */
static void edge_marking(void)
{
    for (int y = 0; y < SCREEN_H; y++) {
        for (int x = 0; x < SCREEN_W; x++) {
            int addr = PIXEL(x, y);
            uint32_t attr = attr_buf[addr];
            if (!(attr & A_EDGES)) {
                continue;
            }
            uint32_t id = attr >> 24, z = depth_buf[addr];
            static const int step[4] = {-1, 1, -BUF_W, BUF_W};
            int mark = 0;
            for (int k = 0; k < 4 && !mark; k++) {
                mark = id != (attr_buf[addr + step[k]] >> 24) && z < depth_buf[addr + step[k]];
            }
            if (mark) {
                color_buf[addr] = rgb555_to_6(rr.edge[id >> 3]) | (color_buf[addr] & 0xff000000u);
                attr_buf[addr] = (attr & ~0x1f00u) | 0x1000u;
            }
        }
    }
}

/* The fog density at a depth: the table entry by (depth - offset) / 4 shifted by the fog
 * shift, 17 bits of it the fraction towards the next entry; 127 counts as 128. */
static uint32_t fog_density(uint32_t z)
{
    uint32_t id = 0, frac = 0;
    if (z >= rr.fog_offset) {
        z = ((z - rr.fog_offset) >> 2) << rr.fog_shift;
        id = z >> 17;
        frac = z & 0x1ffff;
        if (id >= 32) {
            id = 32;
            frac = 0;
        }
    }
    uint32_t d = (rr.fog_table[id] * (0x20000 - frac) + rr.fog_table[id + 1] * frac) >> 17;
    return d >= 127 ? 128 : d;
}

static void fog_pixel(int addr, int color_too)
{
    uint32_t d = fog_density(depth_buf[addr]), c = color_buf[addr], f = rgb555_to_6(rr.fog_color);
    uint32_t r = c & 0x3f, g = (c >> 8) & 0x3f, b = (c >> 16) & 0x3f, a = (c >> 24) & 0x1f;
    if (color_too) {
        r = ((f & 0x3f) * d + r * (128 - d)) >> 7;
        g = (((f >> 8) & 0x3f) * d + g * (128 - d)) >> 7;
        b = (((f >> 16) & 0x3f) * d + b * (128 - d)) >> 7;
    }
    a = (((rr.fog_color >> 16) & 31) * d + a * (128 - d)) >> 7;
    color_buf[addr] = COLOR(r, g, b, a);
}

/* Fog over colour and alpha, or alpha only (DISP3DCNT bit 6), on the top pixels and on the
 * lower ones of edges. */
static void apply_fog(void)
{
    int color_too = !(rr.disp3dcnt & (1u << 6));
    for (int y = 0; y < SCREEN_H; y++) {
        for (int x = 0; x < SCREEN_W; x++) {
            int addr = PIXEL(x, y);
            uint32_t attr = attr_buf[addr];
            if (attr & A_FOG) {
                fog_pixel(addr, color_too);
            }
            if ((attr & A_EDGES) && (attr_buf[addr + BUF_SIZE] & A_FOG)) {
                fog_pixel(addr + BUF_SIZE, color_too);
            }
        }
    }
}

/* Anti-aliasing: an edge pixel is mixed with the one below by its coverage; the colour only
 * when the lower pixel has alpha. */
static void anti_alias(void)
{
    for (int y = 0; y < SCREEN_H; y++) {
        for (int x = 0; x < SCREEN_W; x++) {
            int addr = PIXEL(x, y);
            uint32_t attr = attr_buf[addr];
            if (!(attr & A_EDGES)) {
                continue;
            }
            uint32_t cov = (attr >> 8) & 31;
            if (cov == 31) {
                continue;
            }
            uint32_t below = color_buf[addr + BUF_SIZE];
            if (cov == 0) {
                color_buf[addr] = below;
                continue;
            }
            uint32_t top = color_buf[addr], k = cov + 1;
            uint32_t r = top & 0x3f, g = (top >> 8) & 0x3f, b = (top >> 16) & 0x3f, a = (top >> 24) & 0x1f;
            uint32_t ba = (below >> 24) & 0x1f;
            if (ba > 0) {
                r = (r * k + (below & 0x3f) * (32 - k)) >> 5;
                g = (g * k + ((below >> 8) & 0x3f) * (32 - k)) >> 5;
                b = (b * k + ((below >> 16) & 0x3f) * (32 - k)) >> 5;
            }
            a = (a * k + ba * (32 - k)) >> 5;
            color_buf[addr] = COLOR(r, g, b, a);
        }
    }
}

/* The rendering order: opaque polygons first, then translucent ones, each by bottom line,
 * then top line, then submission; translucent ones in submission order when sorted manually
 * (the last SWAP_BUFFERS bit 0). */
static int compare_polygons(const void *x, const void *y)
{
    const Polygon *const *a = x, *const *b = y;
    if ((*a)->key != (*b)->key) {
        return (*a)->key < (*b)->key ? -1 : 1;
    }
    return (*a)->order < (*b)->order ? -1 : (*a)->order > (*b)->order;
}

static int compare_order(const void *x, const void *y)
{
    const Polygon *const *a = x, *const *b = y;
    int ta = (*a)->translucent, tb = (*b)->translucent;
    if (ta != tb) {
        return ta - tb;
    }
    if (!ta) {
        return compare_polygons(x, y);
    }
    return (*a)->order < (*b)->order ? -1 : (*a)->order > (*b)->order;
}

static void render_list(PolygonList *list)
{
    clock_t start = clock();
    capture_registers();
    clear_frame();

    static const Polygon *order[POLYGON_RAM];
    for (int i = 0; i < list->polygons; i++) {
        order[i] = &list->poly[i];
    }
    qsort(order, (size_t) list->polygons, sizeof(order[0]), list->manual_sort ? compare_order : compare_polygons);
    int count = 0;
    for (int i = 0; i < list->polygons; i++) {
        if (!order[i]->degenerate) {
            raster_setup(&raster[count++], order[i]);
        }
    }
    /* line by line, each polygon on the line in order */
    prev_shadow_mask = 0;
    for (int y = 0; y < SCREEN_H; y++) {
        for (int i = 0; i < count; i++) {
            Raster *rp = &raster[i];
            const Polygon *p = rp->p;
            if (y < p->ytop || (y >= p->ybot && !(y == p->ytop && p->ybot == p->ytop))) {
                continue;
            }
            if (p->shadow_mask) {
                mask_line(rp, y);
            } else {
                draw_line(rp, y);
            }
        }
    }
    if (rr.disp3dcnt & (1u << 5)) {
        edge_marking();
    }
    if (rr.disp3dcnt & (1u << 7)) {
        apply_fog();
    }
    if (rr.disp3dcnt & (1u << 4)) {
        anti_alias();
    }
    for (int y = 0; y < SCREEN_H; y++) {
        for (int x = 0; x < SCREEN_W; x++) {
            uint32_t c = color_buf[PIXEL(x, y)] & 0x1f3f3f3fu, a = c >> 24;
            out_full[y][x] = c;
            out_color[y][x] =
                (uint16_t) (((c & 0x3f) >> 1) | (((c >> 8) & 0x3f) >> 1) << 5 | (((c >> 16) & 0x3f) >> 1) << 10 | (a ? 0x8000 : 0));
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
    done->manual_sort = (int) ge.flush_attr & 1;
    capture_list_end(done);
    render_3d(geometry_list); /* gpu3d_render, here or on the drawing thread */
    geometry_list ^= 1;
    lists[geometry_list].polygons = 0;
    lists[geometry_list].vertices = 0;
    ge.last_strip = -1; /* the polygon RAM is the other list's now */
    if (cap.on) {
        capture_list_start();
    }
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
                io_frame(), ge.flush_attr, done->polygons, done->vertices, rr.disp3dcnt, rr.clear1, drawn);
    }
    maybe_dump();
}

const uint16_t *gpu3d_line(int y)
{
    return out_color[y < 0 ? 0 : y >= SCREEN_H ? SCREEN_H - 1 : y];
}

const uint32_t *gpu3d_line_rgb6(int y)
{
    return out_full[y < 0 ? 0 : y >= SCREEN_H ? SCREEN_H - 1 : y];
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

int gpu3d_capture_write(const char *path)
{
    if (!cap.last_valid) {
        return 1;
    }
    FILE *f = fopen(path, "wb");
    if (f == NULL) {
        return -1;
    }
    uint32_t head[4] = {0x44335847u, 1, (uint32_t) cap.last_state.n, (uint32_t) cap.last_log.n};
    int ok = fwrite(head, 4, 4, f) == 4;
    ok &= fwrite(cap.last_state.w, 4, cap.last_state.n, f) == cap.last_state.n;
    ok &= fwrite(cap.last_log.w, 4, cap.last_log.n, f) == cap.last_log.n;
    uint32_t np = (uint32_t) cap.last_polys.n;
    ok &= fwrite(&np, 4, 1, f) == 1;
    ok &= fwrite(cap.last_polys.w, 4, cap.last_polys.n, f) == cap.last_polys.n;
    ok &= fwrite(cap.regs, 1, IO_REG_SIZE, f) == IO_REG_SIZE;
    ok &= fwrite(cap.mem, 1, IO_VIDEO_SIZE, f) == IO_VIDEO_SIZE;
    ok &= fwrite(out_full, 4, SCREEN_W * SCREEN_H, f) == SCREEN_W * SCREEN_H;
    ok &= fclose(f) == 0;
    return ok ? 0 : -1;
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
    set_viewport(0xbfff0000u); /* the full screen */
    ge.dot_limit = 0xffffff;   /* until DISP_1DOT_DEPTH is written, no dot is too far */
    ge.last_strip = -1;
    for (int i = 0; i < 2; i++) {
        if (lists[i].poly == NULL) {
            lists[i].poly = calloc(POLYGON_RAM, sizeof(Polygon));
        }
        lists[i].polygons = lists[i].vertices = 0;
    }
    geometry_list = 0;
    memset(out_color, 0, sizeof(out_color));
    memset(out_full, 0, sizeof(out_full));

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
