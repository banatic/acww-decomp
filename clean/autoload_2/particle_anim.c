/* What a frame's update does to each particle (particle.h): the animations of its scale,
 * colour, alpha and texture, run on its rate (0 to 255 through its life or its loop), and the
 * behaviours, which add to the frame's acceleration or move it directly. */
#include "particle.h"

#include <stddef.h>
#include <stdint.h>

#include "clean.h"

extern const fx16 FX_SinCosTable_[];
extern void MTX_RotX33_(ParticleMtx33 *mtx, fx32 sine, fx32 cosine);
extern void MTX_RotY33_(ParticleMtx33 *mtx, fx32 sine, fx32 cosine);
extern void MTX_RotZ33_(ParticleMtx33 *mtx, fx32 sine, fx32 cosine);
extern void MTX_MultVec33(const Vec3 *vec, const ParticleMtx33 *mtx, Vec3 *dst);

/* --- Animations --- */

/* A value in three stages over the rate: from `start` to `mid` until `in`, `mid` until `out`,
 * then on to `end` at 255. QUIRK: a stage of no length divides by 0, which the ROM's division
 * answers with the numerator. */
static s32 three_stages(s32 rate, s32 start, s32 mid, s32 end, s32 in, s32 out)
{
    if (rate < in) {
        return particle_add(start, particle_div(particle_mul(rate, mid - start), in));
    }
    if (rate < out) {
        return mid;
    }
    return particle_add(end, particle_div(particle_mul(particle_sub(rate, 255), end - mid), 255 - out));
}

/* func_020ff3a4: the particle's scale animation. */
void ParticleAnim_Scale(Particle *ptcl, const ParticleResource *res, int rate)
{
    const ParticleScaleAnim *anim = res->scale_anim;

    ptcl->anim_scale = (fx16) three_stages(rate, anim->start, anim->mid, anim->end, anim->in, anim->out);
}
CLEAN_AS(func_020ff3a4, ParticleAnim_Scale)

/* func_020ff0fc: the particle's alpha animation, less a random part of up to `random_range`
 * / 256 every frame (a flicker). */
void ParticleAnim_Alpha(Particle *ptcl, const ParticleResource *res, int rate)
{
    const ParticleAlphaAnim *anim = res->alpha_anim;
    s32 alpha = three_stages(rate, particle_bits(anim->alpha, 0, 5), particle_bits(anim->alpha, 5, 5),
                             particle_bits(anim->alpha, 10, 5), anim->in, anim->out);

    alpha = particle_random_less(alpha, anim->random_range);
    ptcl->visibility = (u16) particle_with_bits(ptcl->visibility, PARTICLE_ANIM_ALPHA_SHIFT, 5, (u32) alpha);
}
CLEAN_AS(func_020ff0fc, ParticleAnim_Alpha)

/* The colour `steps` of `length` of the way from `from` to `to`, each of red, green and blue
 * apart; just `to` when the animation does not blend.
 * QUIRK: the channels are or-ed together unmasked, as the ROM does; out of the rates the game
 * gives they stay within 0 to 31. */
static u16 blend(u16 from, u16 to, s32 steps, s32 length, int blends)
{
    u32 rgb = 0;

    if (!blends) {
        return to & 0x7fff;
    }
    for (int shift = 0; shift <= 10; shift += 5) {
        s32 f = (from >> shift) & 0x1f;
        s32 t = (to >> shift) & 0x1f;
        rgb |= (u32) particle_add(f, particle_div(particle_mul(steps, t - f), length)) << shift;
    }
    return (u16) rgb;
}

/* func_020ff1d8: the particle's colour animation: the start colour until `in`, then to the
 * header's colour by `peak`, then to the end colour by `out`, then the end colour.
 * REQUIRES: the animation is halfword-aligned, as every part of the file is (the ARM9 reads
 * a halfword at an odd address from the even one below). */
void ParticleAnim_Color(Particle *ptcl, const ParticleResource *res, int rate)
{
    const ParticleColorAnim *anim = res->color_anim;
    int blends = (anim->flags >> 2) & 1;

    if (rate < anim->in) {
        ptcl->color = anim->start;
    } else if (rate < anim->peak) {
        ptcl->color = blend(anim->start, res->header->color, particle_sub(rate, anim->in), anim->peak - anim->in, blends);
    } else if (rate < anim->out) {
        ptcl->color = blend(res->header->color, anim->end, particle_sub(rate, anim->peak), anim->out - anim->peak, blends);
    } else {
        ptcl->color = anim->end;
    }
}
CLEAN_AS(func_020ff1d8, ParticleAnim_Color)

/* func_020ff098: the particle's texture: the animation's frame the rate falls in, each
 * `step` long; unchanged past the last. */
void ParticleAnim_Texture(Particle *ptcl, const ParticleResource *res, int rate)
{
    const ParticleTexAnim *anim = res->tex_anim;

    for (int i = 0; i < anim->count; i++) {
        if (rate < (i + 1) * anim->step) {
            ptcl->texture = anim->textures[i];
            return;
        }
    }
}
CLEAN_AS(func_020ff098, ParticleAnim_Texture)

/* func_020ff04c: a child's scale, from 1 at its birth to the child part's end scale. */
void ParticleAnim_ChildScale(Particle *ptcl, const ParticleResource *res, int rate)
{
    s32 end = res->child->end_scale;

    ptcl->anim_scale = (fx16) particle_add(end, particle_mul(end - 0x1000, particle_sub(rate, 255)) / 255);
}
CLEAN_AS(func_020ff04c, ParticleAnim_ChildScale)

/* func_020feff4: a child's alpha, from 31 at its birth to 0 (the resource is not used). */
void ParticleAnim_ChildAlpha(Particle *ptcl, const ParticleResource *res, int rate)
{
    u16 alpha = (u16) (particle_mul(particle_sub(255, rate), 31) / 255);

    (void) res;
    ptcl->visibility = (u16) particle_with_bits(ptcl->visibility, PARTICLE_ANIM_ALPHA_SHIFT, 5, alpha);
}
CLEAN_AS(func_020feff4, ParticleAnim_ChildAlpha)

/* --- Behaviours --- */

/* func_020ff434: the particle drawn towards the target by `strength` (1.0: all the way) of
 * the distance each frame. */
void ParticleBehavior_Converge(const ParticleTarget *data, Particle *ptcl, Vec3 *acc, ParticleEmitter *emitter)
{
    (void) acc;
    (void) emitter;
    ptcl->position.x =
        particle_add(ptcl->position.x, particle_fx_mul(data->strength, particle_sub(data->target.x, ptcl->position.x)));
    ptcl->position.y =
        particle_add(ptcl->position.y, particle_fx_mul(data->strength, particle_sub(data->target.y, ptcl->position.y)));
    ptcl->position.z =
        particle_add(ptcl->position.z, particle_fx_mul(data->strength, particle_sub(data->target.z, ptcl->position.z)));
}
CLEAN_AS(func_020ff434, ParticleBehavior_Converge)

/* func_020ff4c8: a particle on the other side of the plane from its emitter is put on the
 * plane (the emitter's own height when it has one), and either ends (its age set to its
 * life) or bounces, its vertical speed turned round and times the elasticity. Other
 * collision types do nothing. */
void ParticleBehavior_Collision(const ParticleCollision *data, Particle *ptcl, Vec3 *acc, ParticleEmitter *emitter)
{
    fx32 y = data->y;
    fx32 from = ptcl->emitter_pos.y;
    u32 type = data->flags & 3;
    int crossed;

    (void) acc;
    if (emitter->collision_y != EMITTER_NO_COLLISION_Y) {
        y = emitter->collision_y;
    }
    if (type > 1) {
        return;
    }
    crossed =
        (from < y && particle_add(from, ptcl->position.y) > y) || (from >= y && particle_add(from, ptcl->position.y) < y);
    if (!crossed) {
        return;
    }
    ptcl->position.y = particle_sub(y, from);
    if (type == 0) {
        ptcl->age = ptcl->life;
    } else {
        ptcl->velocity.y = particle_sub(0, particle_fx_mul(ptcl->velocity.y, data->elasticity));
    }
}
CLEAN_AS(func_020ff4c8, ParticleBehavior_Collision)

/* func_020ff5e4: the particle's place (from its emitter) turned about X, Y or Z by the
 * behaviour's angle each frame.
 * BUG: for another axis the matrix is left unset, and the place is multiplied by whatever
 * the stack held. */
void ParticleBehavior_Spin(const ParticleSpin *data, Particle *ptcl, Vec3 *acc, ParticleEmitter *emitter)
{
    ParticleMtx33 mtx;
    fx32 sine = FX_SinCosTable_[(data->angle >> 4) * 2];
    fx32 cosine = FX_SinCosTable_[(data->angle >> 4) * 2 + 1];

    (void) acc;
    (void) emitter;
    switch (data->axis) {
        case 0:
            MTX_RotX33_(&mtx, sine, cosine);
            break;
        case 1:
            MTX_RotY33_(&mtx, sine, cosine);
            break;
        case 2:
            MTX_RotZ33_(&mtx, sine, cosine);
            break;
    }
    MTX_MultVec33(&ptcl->position, &mtx, &ptcl->position);
}
CLEAN_AS(func_020ff5e4, ParticleBehavior_Spin)

/* func_020ff6bc: the particle pulled towards the target by `strength` times the distance.
 * QUIRK: the distance is the target less the particle's place and less its velocity (its
 * place counts from its emitter's position, which is not taken off); the product is kept to
 * 32 bits, unrounded. */
void ParticleBehavior_Magnet(const ParticleTarget *data, Particle *ptcl, Vec3 *acc, ParticleEmitter *emitter)
{
    (void) emitter;
    acc->x = particle_add(
        acc->x,
        particle_asr(
            particle_mul(data->strength, particle_sub(particle_sub(data->target.x, ptcl->position.x), ptcl->velocity.x)), 12));
    acc->y = particle_add(
        acc->y,
        particle_asr(
            particle_mul(data->strength, particle_sub(particle_sub(data->target.y, ptcl->position.y), ptcl->velocity.y)), 12));
    acc->z = particle_add(
        acc->z,
        particle_asr(
            particle_mul(data->strength, particle_sub(particle_sub(data->target.z, ptcl->position.z), ptcl->velocity.z)), 12));
}
CLEAN_AS(func_020ff6bc, ParticleBehavior_Magnet)

/* func_020ff740: a random push of up to the range each way, every `interval` frames of the
 * particle's age (every frame for an interval of 0: the ROM's remainder by 0 is 0). */
void ParticleBehavior_Random(const ParticleRandom *data, Particle *ptcl, Vec3 *acc, ParticleEmitter *emitter)
{
    (void) emitter;
    if (particle_mod(ptcl->age, data->interval) == 0) {
        acc->x = particle_add(acc->x, particle_random_range(data->range.x));
        acc->y = particle_add(acc->y, particle_random_range(data->range.y));
        acc->z = particle_add(acc->z, particle_random_range(data->range.z));
    }
}
CLEAN_AS(func_020ff740, ParticleBehavior_Random)

/* func_020ff808: a constant force. */
void ParticleBehavior_Gravity(const ParticleGravity *data, Particle *ptcl, Vec3 *acc, ParticleEmitter *emitter)
{
    (void) ptcl;
    (void) emitter;
    acc->x = particle_add(acc->x, data->force.x);
    acc->y = particle_add(acc->y, data->force.y);
    acc->z = particle_add(acc->z, data->force.z);
}
CLEAN_AS(func_020ff808, ParticleBehavior_Gravity)
