/* Drawing particles with the 3D engine's geometry commands (particle.h): the texture, then
 * for each particle its polygon attributes, its matrix, its colour and one quad.
 *
 * HW: every function here writes the geometry engine's command registers, whose order is the
 * order of the commands. */
#include "particle.h"

#include <stddef.h>
#include <stdint.h>

#include "clean.h"

#define REG32(address) (*(volatile u32 *) (address))
#define REG_MTX_MODE REG32(0x04000440)
#define REG_MTX_IDENTITY REG32(0x04000454)
#define REG_MTX_SCALE REG32(0x0400046c)
#define REG_MTX_TRANS REG32(0x04000470)
#define REG_COLOR REG32(0x04000480)
#define REG_TEXCOORD REG32(0x04000488)
#define REG_VTX_10 REG32(0x04000490)
#define REG_POLYGON_ATTR REG32(0x040004a4)
#define REG_TEXIMAGE_PARAM REG32(0x040004a8)
#define REG_TEXPLTT_BASE REG32(0x040004ac)
#define REG_BEGIN_VTXS REG32(0x04000500)
#define REG_END_VTXS REG32(0x04000504)

#define MTX_MODE_POSITION 1
#define MTX_MODE_TEXTURE 3
#define BEGIN_QUADS 1
#define TEXGEN_TEXCOORD 1
/* Polygon attributes: both faces drawn. */
#define POLYGON_BOTH_FACES 0xc0

/* NitroSDK's table of sines and cosines, a pair for each 16th of an angle step. */
extern const fx16 FX_SinCosTable_[];
/* The polygons' rotation functions by type: ParticleDraw_RotY and ParticleDraw_RotDiagonal.
 * REQUIRES: a type of 0 or 1 (the table has two entries; 2 and 3 read the words after it, the
 * up vector of particle_emit.c, as addresses). And the quad functions: QuadXY, QuadXZ. */
extern void (*const data_0213f268[4])(fx32 sine, fx32 cosine, Mtx43 *mtx);
extern void (*const data_0213f260[2])(fx32 s, fx32 t, fx32 x, fx32 y);

extern void MTX_Scale43_(Mtx43 *dst, fx32 x, fx32 y, fx32 z);
extern void MTX_Concat43(const Mtx43 *a, const Mtx43 *b, Mtx43 *ab);
extern void MTX_RotX43_(Mtx43 *mtx, fx32 sine, fx32 cosine);
extern void MTX_MultVec43(const Vec3 *vec, const Mtx43 *mtx, Vec3 *dst);
extern void MTX_MultVec33(const Vec3 *vec, const ParticleMtx33 *mtx, Vec3 *dst);
extern void MI_Copy36B(const void *src, void *dst);
extern void G3_LoadMtx43(const Mtx43 *mtx);
extern void G3_MultMtx43(const Mtx43 *mtx);
extern void VEC_CrossProduct(const Vec3 *a, const Vec3 *b, Vec3 *axb);
extern void VEC_Normalize(const Vec3 *src, Vec3 *dst);

/* The table's entry `index`, read where the ROM reads it for any index. */
static fx16 sin_cos_entry(s32 index)
{
    return *(const fx16 *) ((uintptr_t) FX_SinCosTable_ + (uintptr_t) particle_mul(index, 2));
}

/* The sine and cosine of `angle` (16 bits to a turn; only bits 4 and up count). */
static fx32 sin_of(s32 angle)
{
    return sin_cos_entry(particle_asr(angle, 4) * 2);
}

static fx32 cos_of(s32 angle)
{
    return sin_cos_entry(particle_asr(angle, 4) * 2 + 1);
}

static void g3_identity(void)
{
    REG_MTX_IDENTITY = 0;
}

static void g3_translate(fx32 x, fx32 y, fx32 z)
{
    REG_MTX_TRANS = (u32) x;
    REG_MTX_TRANS = (u32) y;
    REG_MTX_TRANS = (u32) z;
}

/* The particle's polygon attributes: both faces, its polygon ID and its alpha, the base alpha
 * times the animation's (out of 32); the alpha. The register is read back after. */
static u32 set_polygon_attr(const ParticleSystem *sys, const Particle *ptcl)
{
    u32 base = particle_bits(ptcl->visibility, PARTICLE_BASE_ALPHA_SHIFT, 5);
    u32 anim = particle_bits(ptcl->visibility, PARTICLE_ANIM_ALPHA_SHIFT, 5);
    u32 alpha = (base * (anim + 1)) >> 5;

    REG_POLYGON_ATTR = sys->polygon_attr | POLYGON_BOTH_FACES |
                       particle_bits(ptcl->visibility, PARTICLE_POLYGON_ID_SHIFT, 6) << 24 | alpha << 16;
    (void) REG_POLYGON_ATTR;
    return alpha;
}

/* The particle's scale: its base scale (X times the aspect), times the animation's scale in
 * X and Y (0), X (1) or Y (2). With `others_y`, any other direction scales Y too. */
static void particle_scale(const ParticleHeader *header, const Particle *ptcl, int others_y, fx32 *sx, fx32 *sy)
{
    fx32 x = particle_fx_mul(ptcl->base_scale, header->aspect);
    fx32 y = ptcl->base_scale;

    switch (particle_bits(header->misc, PARTICLE_SCALE_DIR_SHIFT, 3)) {
        case 0:
            x = particle_fx_mul(x, ptcl->anim_scale);
            y = particle_fx_mul(y, ptcl->anim_scale);
            break;
        case 1:
            x = particle_fx_mul(x, ptcl->anim_scale);
            break;
        case 2:
            y = particle_fx_mul(y, ptcl->anim_scale);
            break;
        default:
            if (others_y) {
                y = particle_fx_mul(y, ptcl->anim_scale);
            }
            break;
    }
    *sx = x;
    *sy = y;
}

/* The particle's place: from its emitter's position, less the resource's base position when
 * the resource is drawn in view space. */
static void particle_place(const ParticleHeader *header, const Particle *ptcl, Vec3 *trs)
{
    trs->x = particle_add(ptcl->position.x, ptcl->emitter_pos.x);
    trs->y = particle_add(ptcl->position.y, ptcl->emitter_pos.y);
    trs->z = particle_add(ptcl->position.z, ptcl->emitter_pos.z);
    if (header->flags & PARTICLE_VIEW_SPACE) {
        trs->x = particle_sub(trs->x, header->base_pos.x);
        trs->y = particle_sub(trs->y, header->base_pos.y);
        trs->z = particle_sub(trs->z, header->base_pos.z);
    }
}

/* The particle's colour times the emitter's, each of red, green and blue out of 32. */
static void set_color(const Particle *ptcl, const ParticleEmitter *emitter)
{
    s32 p = ptcl->color;
    s32 e = emitter->color;
    u16 rgb = (u16) ((((p & 0x1f) * (e & 0x1f)) >> 5) | ((((p & 0x3e0) * (e & 0x3e0)) >> 15) << 5) |
                     ((((p & 0x7c00) * (e & 0x7c00)) >> 25) << 10));

    REG_COLOR = rgb;
}

/* The tilt the draw callback's angle gives, about X, when the resource asks for it. */
static void tilt(const ParticleHeader *header, Mtx43 *mtx, fx32 angle)
{
    if (header->draw_flags & PARTICLE_TILT) {
        MTX_RotX43_(mtx, sin_of(angle), cos_of(angle));
        G3_MultMtx43(mtx);
    }
}

/* func_020fb8e4: a texture binding that does nothing, for particles that keep the
 * resource's. */
void ParticleDraw_NoTexture(const ParticleTexture *texture)
{
    (void) texture;
}
CLEAN_AS(func_020fb8e4, ParticleDraw_NoTexture)

/* func_020fb8e8: the texture made current: its image and palette, and a texture matrix that
 * scales the quads' coordinates (1.0 a whole texture) to its size in texels. */
void ParticleDraw_BindTexture(const ParticleTexture *texture)
{
    u32 param = texture->param;
    u32 format = param & PARTICLE_TEX_FORMAT_MASK;

    REG_TEXIMAGE_PARAM =
        texture->image_addr >> 3 | format << 26 | (u32) TEXGEN_TEXCOORD << 30 |
        particle_bits(param, PARTICLE_TEX_SIZE_S_SHIFT, 4) << 20 | particle_bits(param, PARTICLE_TEX_SIZE_T_SHIFT, 4) << 23 |
        particle_bits(param, PARTICLE_TEX_REPEAT_SHIFT, 2) << 16 | particle_bits(param, PARTICLE_TEX_FLIP_SHIFT, 2) << 18 |
        particle_bits(param, PARTICLE_TEX_COLOR0_SHIFT, 1) << 29;
    /* Four-colour palettes are addressed in 8 bytes, the others in 16. */
    REG_TEXPLTT_BASE = texture->palette_addr >> (format == PARTICLE_TEX_FORMAT_PLTT4 ? 3 : 4);
    REG_MTX_MODE = MTX_MODE_TEXTURE;
    REG_MTX_IDENTITY = 0;
    REG_MTX_SCALE = (u32) texture->width << 12;
    REG_MTX_SCALE = (u32) texture->height << 12;
    REG_MTX_SCALE = 0;
    REG_MTX_MODE = MTX_MODE_POSITION;
}
CLEAN_AS(func_020fb8e8, ParticleDraw_BindTexture)

/* A particle drawn as a polygon: turned by the rotation function of its type and scaled, at
 * its place in the camera's view. The child's and the parent's differ in the type they take
 * (the child part's or the header's), the order of rotation and scale, and the quad. */
static void draw_polygon(ParticleSystem *sys, Particle *ptcl, ParticleDrawCallback callback, int child)
{
    const ParticleEmitter *emitter = sys->emitter;
    const ParticleResource *res = emitter->resource;
    const ParticleHeader *header = res->header;
    Mtx43 rot;
    Mtx43 scale;
    Mtx43 mtx;
    Mtx43 tilt_mtx;
    Vec3 trs;
    fx32 sx;
    fx32 sy;
    fx32 angle;
    u32 rot_type;

    if (set_polygon_attr(sys, ptcl) == 0) {
        return;
    }

    if (child) {
        rot_type = particle_bits(res->child->flags, PARTICLE_CHILD_ROT_TYPE_SHIFT, 2);
    } else {
        rot_type = particle_bits(header->flags, PARTICLE_ROT_TYPE_SHIFT, 2);
    }
    data_0213f268[rot_type](sin_of(ptcl->rotation), cos_of(ptcl->rotation), &rot);

    particle_scale(header, ptcl, 0, &sx, &sy);
    MTX_Scale43_(&scale, sx, sy, sy);
    if (child) {
        MTX_Concat43(&rot, &scale, &mtx);
    } else {
        MTX_Concat43(&scale, &rot, &mtx);
    }

    particle_place(header, ptcl, &trs);
    angle = callback(&trs, trs);
    if (!(header->flags & PARTICLE_VIEW_SPACE)) {
        G3_LoadMtx43(sys->view);
    } else {
        g3_identity();
        g3_translate(header->base_pos.x, header->base_pos.y, header->base_pos.z);
        G3_MultMtx43(sys->view);
    }
    g3_translate(trs.x, trs.y, trs.z);
    tilt(header, &tilt_mtx, angle);
    G3_MultMtx43(&mtx);

    set_color(ptcl, emitter);
    if (child) {
        data_0213f260[particle_bits(res->child->flags, PARTICLE_CHILD_QUAD_TYPE_SHIFT, 1)](emitter->child_tex_s,
                                                                                           emitter->child_tex_t, 0, 0);
    } else {
        data_0213f260[particle_bits(header->flags, PARTICLE_QUAD_TYPE_SHIFT, 1)](emitter->tex_s, emitter->tex_t,
                                                                                 header->polygon_x, header->polygon_y);
    }
}

/* func_020fb9d4: a child drawn as a polygon (it takes the parent's scale settings). */
void ParticleDraw_ChildPolygon(ParticleSystem *sys, Particle *ptcl, ParticleDrawCallback callback)
{
    draw_polygon(sys, ptcl, callback, 1);
}
CLEAN_AS(func_020fb9d4, ParticleDraw_ChildPolygon)

/* func_020fbda4: a particle drawn as a polygon. */
void ParticleDraw_Polygon(ParticleSystem *sys, Particle *ptcl, ParticleDrawCallback callback)
{
    draw_polygon(sys, ptcl, callback, 0);
}
CLEAN_AS(func_020fbda4, ParticleDraw_Polygon)

/* A particle drawn facing the camera and stretched along its velocity as the camera sees it:
 * longer the more the velocity crosses the line of sight. Nothing is drawn (after the polygon
 * attributes) when the velocity is along the line of sight. */
static void draw_stretched(ParticleSystem *sys, Particle *ptcl, ParticleDrawCallback callback, int child)
{
    const Mtx43 *view = sys->view;
    const ParticleEmitter *emitter = sys->emitter;
    const ParticleHeader *header = emitter->resource->header;
    Vec3 trs;
    Vec3 dir;
    Vec3 cam_z;
    Vec3 vel;
    ParticleMtx33 view33;
    Mtx43 mtx;
    fx32 sx;
    fx32 sy;
    fx32 dot;
    fx32 stretch;
    fx32 angle;

    if (set_polygon_attr(sys, ptcl) == 0) {
        return;
    }
    particle_scale(header, ptcl, 0, &sx, &sy);

    particle_place(header, ptcl, &trs);
    angle = callback(&trs, trs);

    /* The quad's X along the velocity crossed with the camera's Z, in the camera's space. */
    dir = ptcl->velocity;
    cam_z.x = view->m[0][2];
    cam_z.y = view->m[1][2];
    cam_z.z = view->m[2][2];
    VEC_CrossProduct(&dir, &cam_z, &dir);
    if (dir.x == 0 && dir.y == 0 && dir.z == 0) {
        return;
    }
    VEC_Normalize(&dir, &dir);
    MI_Copy36B(view, &view33);
    MTX_MultVec33(&dir, &view33, &dir);
    MTX_MultVec43(&trs, view, &trs);

    /* Y stretched by (1 - |cos|) times the resource's stretch, the cosine between the velocity
     * and the camera's line of sight. */
    vel = ptcl->velocity;
    VEC_Normalize(&vel, &vel);
    dot = particle_add(particle_add(particle_fx_mul(vel.x, particle_sub(0, view->m[0][2])),
                                    particle_fx_mul(vel.y, particle_sub(0, view->m[1][2]))),
                       particle_fx_mul(vel.z, particle_sub(0, view->m[2][2])));
    if (dot < 0) {
        dot = particle_sub(0, dot);
    }
    stretch = (fx32) particle_bits(header->misc, PARTICLE_STRETCH_SHIFT, 16);
    sy = particle_fx_mul(sy, particle_add(particle_fx_mul(particle_sub(0x1000, dot), stretch), 0x1000));

    mtx.m[0][0] = particle_fx_mul(dir.x, sx);
    mtx.m[0][1] = particle_fx_mul(dir.y, sx);
    mtx.m[0][2] = 0;
    mtx.m[1][0] = particle_fx_mul(particle_sub(0, dir.y), sy);
    mtx.m[1][1] = particle_fx_mul(dir.x, sy);
    mtx.m[1][2] = 0;
    mtx.m[2][0] = 0;
    mtx.m[2][1] = 0;
    mtx.m[2][2] = 0x1000;
    mtx.m[3][0] = trs.x;
    mtx.m[3][1] = trs.y;
    mtx.m[3][2] = trs.z;
    g3_identity();
    if (header->flags & PARTICLE_VIEW_SPACE) {
        g3_translate(header->base_pos.x, header->base_pos.y, header->base_pos.z);
    }
    G3_MultMtx43(&mtx);

    tilt(header, &mtx, angle);
    set_color(ptcl, emitter);
    if (child) {
        ParticleDraw_QuadXY(emitter->child_tex_s, emitter->child_tex_t, 0, 0);
    } else {
        ParticleDraw_QuadXY(emitter->tex_s, emitter->tex_t, header->polygon_x, header->polygon_y);
    }
}

/* func_020fc174: a child drawn stretched along its velocity. */
void ParticleDraw_ChildStretched(ParticleSystem *sys, Particle *ptcl, ParticleDrawCallback callback)
{
    draw_stretched(sys, ptcl, callback, 1);
}
CLEAN_AS(func_020fc174, ParticleDraw_ChildStretched)

/* func_020fc8c4: a particle drawn stretched along its velocity. */
void ParticleDraw_Stretched(ParticleSystem *sys, Particle *ptcl, ParticleDrawCallback callback)
{
    draw_stretched(sys, ptcl, callback, 0);
}
CLEAN_AS(func_020fc8c4, ParticleDraw_Stretched)

/* A particle drawn facing the camera, turned by its rotation about the line of sight.
 * REQUIRES: the draw callback leaves the colours as they are (the parent's version reads them
 * before calling it, the child's after). */
static void draw_billboard(ParticleSystem *sys, Particle *ptcl, ParticleDrawCallback callback, int child)
{
    const ParticleEmitter *emitter = sys->emitter;
    const ParticleHeader *header = emitter->resource->header;
    const Mtx43 *view = sys->view;
    Mtx43 mtx;
    Mtx43 tilt_mtx;
    Vec3 trs;
    fx32 sx;
    fx32 sy;
    fx32 sine;
    fx32 cosine;
    fx32 angle;

    if (set_polygon_attr(sys, ptcl) == 0) {
        return;
    }
    /* QUIRK: the parent's version scales Y for the scale directions 3 to 7 too. */
    particle_scale(header, ptcl, !child, &sx, &sy);

    particle_place(header, ptcl, &trs);
    angle = callback(&trs, trs);
    MTX_MultVec43(&trs, view, &trs);

    sine = sin_of(ptcl->rotation);
    cosine = cos_of(ptcl->rotation);
    mtx.m[0][0] = particle_fx_mul(cosine, sx);
    mtx.m[0][1] = particle_fx_mul(sine, sx);
    mtx.m[0][2] = 0;
    mtx.m[1][0] = particle_fx_mul(-sine, sy);
    mtx.m[1][1] = particle_fx_mul(cosine, sy);
    mtx.m[1][2] = 0;
    mtx.m[2][0] = 0;
    mtx.m[2][1] = 0;
    mtx.m[2][2] = 0x1000;
    mtx.m[3][0] = 0;
    mtx.m[3][1] = 0;
    mtx.m[3][2] = 0;
    g3_identity();
    if (header->flags & PARTICLE_VIEW_SPACE) {
        g3_translate(header->base_pos.x, header->base_pos.y, header->base_pos.z);
    }
    g3_translate(trs.x, trs.y, trs.z);
    tilt(header, &tilt_mtx, angle);
    G3_MultMtx43(&mtx);

    set_color(ptcl, emitter);
    if (child) {
        ParticleDraw_QuadXY(emitter->child_tex_s, emitter->child_tex_t, 0, 0);
    } else {
        ParticleDraw_QuadXY(emitter->tex_s, emitter->tex_t, header->polygon_x, header->polygon_y);
    }
}

/* func_020fd01c: a child drawn as a billboard. */
void ParticleDraw_ChildBillboard(ParticleSystem *sys, Particle *ptcl, ParticleDrawCallback callback)
{
    draw_billboard(sys, ptcl, callback, 1);
}
CLEAN_AS(func_020fd01c, ParticleDraw_ChildBillboard)

/* func_020fd4e0: a particle drawn as a billboard. */
void ParticleDraw_Billboard(ParticleSystem *sys, Particle *ptcl, ParticleDrawCallback callback)
{
    draw_billboard(sys, ptcl, callback, 0);
}
CLEAN_AS(func_020fd4e0, ParticleDraw_Billboard)

/* func_020fd9a4: a rotation about Y by the angle of `sine` and `cosine`, with no translation. */
void ParticleDraw_RotY(fx32 sine, fx32 cosine, Mtx43 *mtx)
{
    mtx->m[0][0] = cosine;
    mtx->m[0][1] = 0;
    mtx->m[0][2] = particle_sub(0, sine);
    mtx->m[1][0] = 0;
    mtx->m[1][1] = 0x1000;
    mtx->m[1][2] = 0;
    mtx->m[2][0] = sine;
    mtx->m[2][1] = 0;
    mtx->m[2][2] = cosine;
    mtx->m[3][0] = 0;
    mtx->m[3][1] = 0;
    mtx->m[3][2] = 0;
}
CLEAN_AS(func_020fd9a4, ParticleDraw_RotY)

/* func_020fd9e4: a rotation about the diagonal (1, 1, 1) by the angle of `sine` and `cosine`
 * (0x555 is 1/3, 0x93d 1/sqrt(3)), with no translation. */
void ParticleDraw_RotDiagonal(fx32 sine, fx32 cosine, Mtx43 *mtx)
{
    fx32 a = particle_fx_mul(particle_sub(0x1000, cosine), 0x555);
    fx32 b = particle_fx_mul(sine, 0x93d);
    fx32 plus = particle_add(a, b);
    fx32 minus = particle_sub(a, b);
    fx32 diagonal = particle_add(a, cosine);

    mtx->m[0][0] = diagonal;
    mtx->m[0][1] = minus;
    mtx->m[0][2] = plus;
    mtx->m[1][0] = plus;
    mtx->m[1][1] = diagonal;
    mtx->m[1][2] = minus;
    mtx->m[2][0] = minus;
    mtx->m[2][1] = plus;
    mtx->m[2][2] = diagonal;
    mtx->m[3][0] = 0;
    mtx->m[3][1] = 0;
    mtx->m[3][2] = 0;
}
CLEAN_AS(func_020fd9e4, ParticleDraw_RotDiagonal)

/* A texture coordinate command: S and T in 12.4. */
static void g3_texcoord(fx32 s, fx32 t)
{
    REG_TEXCOORD = (u32) (u16) particle_asr(s, 8) | (u32) (u16) particle_asr(t, 8) << 16;
}

/* A vertex command of three 10-bit coordinates, each the top bits of a 4.12 value. */
static void g3_vtx10(fx32 x, fx32 y, fx32 z)
{
    REG_VTX_10 = ((u32) particle_asr((fx16) x, 6) & 0x3ff) | ((u32) particle_asr((fx16) y, 6) & 0x3ff) << 10 |
                 ((u32) particle_asr((fx16) z, 6) & 0x3ff) << 20;
}

/* func_020fda90: a quad two units wide in the plane XZ about (x, 0, z), its texture from (0, 0)
 * to (s, t). */
void ParticleDraw_QuadXZ(fx32 s, fx32 t, fx32 x, fx32 z)
{
    REG_BEGIN_VTXS = BEGIN_QUADS;
    g3_texcoord(0, 0);
    g3_vtx10(particle_sub(x, 0x1000), 0, particle_add(z, 0x1000));
    g3_texcoord(s, 0);
    g3_vtx10(particle_add(x, 0x1000), 0, particle_add(z, 0x1000));
    g3_texcoord(s, t);
    g3_vtx10(particle_add(x, 0x1000), 0, particle_sub(z, 0x1000));
    g3_texcoord(0, t);
    g3_vtx10(particle_sub(x, 0x1000), 0, particle_sub(z, 0x1000));
    REG_END_VTXS = 0;
}
CLEAN_AS(func_020fda90, ParticleDraw_QuadXZ)

/* func_020fdb4c: a quad two units wide in the plane XY about (x, y, 0), its texture from
 * (0, 0) to (s, t). */
void ParticleDraw_QuadXY(fx32 s, fx32 t, fx32 x, fx32 y)
{
    REG_BEGIN_VTXS = BEGIN_QUADS;
    g3_texcoord(0, 0);
    g3_vtx10(particle_sub(x, 0x1000), particle_add(y, 0x1000), 0);
    g3_texcoord(s, 0);
    g3_vtx10(particle_add(x, 0x1000), particle_add(y, 0x1000), 0);
    g3_texcoord(s, t);
    g3_vtx10(particle_add(x, 0x1000), particle_sub(y, 0x1000), 0);
    g3_texcoord(0, t);
    g3_vtx10(particle_sub(x, 0x1000), particle_sub(y, 0x1000), 0);
    REG_END_VTXS = 0;
}
CLEAN_AS(func_020fdb4c, ParticleDraw_QuadXY)
