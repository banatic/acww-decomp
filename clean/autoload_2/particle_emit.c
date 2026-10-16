/* Giving off particles and their children (particle.h): where each starts, by the resource's
 * emission shape, and its first velocity, scale, colour, angle, life and texture. */
#include "particle.h"

#include <stddef.h>
#include <stdint.h>

#include "clean.h"

/* The emission shapes (ParticleHeader.flags bits 0-3); the circles and cylinders lie in the
 * plane of the emitter's two cross axes, about its axis. */
enum EmissionShape {
    SHAPE_POINT = 0,
    SHAPE_SPHERE = 1,          /* on a sphere of the emitter's radius */
    SHAPE_CIRCLE = 2,          /* on a circle */
    SHAPE_CIRCLE_EVEN = 3,     /* on a circle, evenly spaced */
    SHAPE_BALL = 4,            /* within a sphere */
    SHAPE_DISC = 5,            /* within a circle */
    SHAPE_CYLINDER = 6,        /* on a cylinder of the emitter's length, moving away from it */
    SHAPE_CYLINDER_FILLED = 7, /* within a cylinder */
    SHAPE_HEMISPHERE = 8,      /* on the half sphere on the side of the axes' normal */
    SHAPE_HALF_BALL = 9,       /* between half and all of the radius, on that side */
};

/* The direction an emitter's axes are worked out from, unless the axis is along it: up. */
extern const ParticleVec16 data_0213f270;
extern const fx16 FX_SinCosTable_[];

extern fx32 FX_Div(fx32 numerator, fx32 denominator);
extern void VEC_Normalize(const Vec3 *src, Vec3 *dst);
extern fx32 VEC_DotProduct(const Vec3 *a, const Vec3 *b);
extern void VEC_Fx16CrossProduct(const ParticleVec16 *a, const ParticleVec16 *b, ParticleVec16 *axb);
extern void VEC_Fx16Normalize(const ParticleVec16 *src, ParticleVec16 *dst);
extern fx32 VEC_Fx16DotProduct(const ParticleVec16 *a, const ParticleVec16 *b);

/* --- Directions and axes --- */

/* func_020ff938: a random direction in the plane XY (Z 0), normalized. */
void Particle_RandomDirectionXY(Vec3 *vec)
{
    vec->x = particle_asr((s32) particle_random(), 8);
    vec->y = particle_asr((s32) particle_random(), 8);
    vec->z = 0;
    VEC_Normalize(vec, vec);
}
CLEAN_AS(func_020ff938, Particle_RandomDirectionXY)

/* func_020ff994: a random direction, normalized. */
void Particle_RandomDirection(Vec3 *vec)
{
    vec->x = particle_asr((s32) particle_random(), 8);
    vec->y = particle_asr((s32) particle_random(), 8);
    vec->z = particle_asr((s32) particle_random(), 8);
    VEC_Normalize(vec, vec);
}
CLEAN_AS(func_020ff994, Particle_RandomDirection)

/* func_020fec0c: `pos` from the emitter's axes into the world: x along the first cross axis,
 * y along the second, z along their normal. */
void Particle_FromEmitterAxes(Vec3 *out, const Vec3 *pos, const ParticleEmitter *emitter)
{
    ParticleVec16 normal;

    VEC_Fx16CrossProduct(&emitter->cross1, &emitter->cross2, &normal);
    VEC_Fx16Normalize(&normal, &normal);
    out->x = particle_add(particle_add(particle_fx_mul(pos->x, emitter->cross1.x), particle_fx_mul(pos->y, emitter->cross2.x)),
                          particle_fx_mul(pos->z, normal.x));
    out->y = particle_add(particle_add(particle_fx_mul(pos->x, emitter->cross1.y), particle_fx_mul(pos->y, emitter->cross2.y)),
                          particle_fx_mul(pos->z, normal.y));
    out->z = particle_add(particle_add(particle_fx_mul(pos->x, emitter->cross1.z), particle_fx_mul(pos->y, emitter->cross2.z)),
                          particle_fx_mul(pos->z, normal.z));
}
CLEAN_AS(func_020fec0c, Particle_FromEmitterAxes)

/* `a` crossed with `b`, each kept to 16 bits. */
static void cross16(ParticleVec16 *out, const ParticleVec16 *a, const ParticleVec16 *b)
{
    out->x = (fx16) particle_sub(particle_fx_mul(a->y, b->z), particle_fx_mul(a->z, b->y));
    out->y = (fx16) particle_sub(particle_fx_mul(a->z, b->x), particle_fx_mul(a->x, b->z));
    out->z = (fx16) particle_sub(particle_fx_mul(a->x, b->y), particle_fx_mul(a->y, b->x));
}

/* func_020fed6c: the emitter's two cross axes, square to its axis (Z, Y, X or its own, by
 * the resource) and to each other: the axis crossed with up (or with X when the axis is up or
 * down), then the axis crossed with that; both normalized. */
void Particle_ComputeEmitterAxes(ParticleEmitter *emitter)
{
    ParticleVec16 up = data_0213f270;
    ParticleVec16 axis = {0, 0, 0};
    fx32 dot;

    switch (particle_bits(emitter->resource->header->flags, PARTICLE_AXIS_SHIFT, 2)) {
        case 2:
            axis.x = 0x1000;
            break;
        case 1:
            axis.y = 0x1000;
            break;
        case 0:
            axis.z = 0x1000;
            break;
        default:
            VEC_Fx16Normalize(&emitter->axis, &axis);
            break;
    }

    dot = VEC_Fx16DotProduct(&up, &axis);
    if (dot == 0x1000 || dot == -0x1000) {
        up.x = 0x1000;
        up.y = 0;
        up.z = 0;
    }

    cross16(&emitter->cross1, &axis, &up);
    cross16(&emitter->cross2, &axis, &emitter->cross1);
    VEC_Fx16Normalize(&emitter->cross1, &emitter->cross1);
    VEC_Fx16Normalize(&emitter->cross2, &emitter->cross2);
}
CLEAN_AS(func_020fed6c, Particle_ComputeEmitterAxes)

/* --- Emission --- */

/* The table's entry `index` (0 or more). */
static fx32 sin_cos_entry(s32 index)
{
    return FX_SinCosTable_[index];
}

/* `v` times `scale`, each component. */
static void scale_vec(Vec3 *v, fx32 scale)
{
    v->x = particle_fx_mul(v->x, scale);
    v->y = particle_fx_mul(v->y, scale);
    v->z = particle_fx_mul(v->z, scale);
}

/* The normal of the emitter's two cross axes, as a vector of 20.12. */
static Vec3 axes_normal(const ParticleEmitter *emitter)
{
    ParticleVec16 normal;
    Vec3 out;

    VEC_Fx16CrossProduct(&emitter->cross1, &emitter->cross2, &normal);
    out.x = normal.x;
    out.y = normal.y;
    out.z = normal.z;
    return out;
}

/* `v` turned round. */
static void negate(Vec3 *v)
{
    v->x = particle_sub(0, v->x);
    v->y = particle_sub(0, v->y);
    v->z = particle_sub(0, v->z);
}

/* The particle's place from the emitter by the emission shape; the `index`th of `count`
 * particles given off together (for the evenly spaced circle). Other shapes (10 to 15) leave
 * the place as it was. */
static void start_position(ParticleEmitter *emitter, Particle *ptcl, u32 shape, int index, int count)
{
    fx32 radius = emitter->radius;
    Vec3 pos;

    switch (shape) {
        case SHAPE_POINT:
            ptcl->position.x = 0;
            ptcl->position.y = 0;
            ptcl->position.z = 0;
            break;
        case SHAPE_SPHERE:
            Particle_RandomDirection(&ptcl->position);
            scale_vec(&ptcl->position, emitter->radius);
            break;
        case SHAPE_CIRCLE:
            Particle_RandomDirectionXY(&pos);
            pos.x = particle_fx_mul(pos.x, radius);
            pos.y = particle_fx_mul(pos.y, radius);
            pos.z = 0;
            Particle_FromEmitterAxes(&ptcl->position, &pos, emitter);
            break;
        case SHAPE_CIRCLE_EVEN: {
            s32 angle = particle_div(particle_mul(index, 0x10000), count);
            pos.x = particle_fx_mul(sin_cos_entry(particle_asr(angle, 4) * 2), radius);
            pos.y = particle_fx_mul(sin_cos_entry(particle_asr(angle, 4) * 2 + 1), radius);
            pos.z = 0;
            Particle_FromEmitterAxes(&ptcl->position, &pos, emitter);
            break;
        }
        case SHAPE_BALL:
            Particle_RandomDirection(&ptcl->position);
            ptcl->position.x =
                particle_fx_mul(particle_fx_mul(ptcl->position.x, emitter->radius), particle_random_range(0x1000));
            ptcl->position.y =
                particle_fx_mul(particle_fx_mul(ptcl->position.y, emitter->radius), particle_random_range(0x1000));
            ptcl->position.z =
                particle_fx_mul(particle_fx_mul(ptcl->position.z, emitter->radius), particle_random_range(0x1000));
            break;
        case SHAPE_DISC:
            Particle_RandomDirectionXY(&pos);
            pos.x = particle_fx_mul(particle_fx_mul(pos.x, emitter->radius), particle_random_range(0x1000));
            pos.y = particle_fx_mul(particle_fx_mul(pos.y, emitter->radius), particle_random_range(0x1000));
            Particle_FromEmitterAxes(&ptcl->position, &pos, emitter);
            break;
        case SHAPE_HEMISPHERE:
        case SHAPE_HALF_BALL: {
            Vec3 normal;

            Particle_RandomDirection(&ptcl->position);
            normal = axes_normal(emitter);
            if (shape == SHAPE_HEMISPHERE) {
                if (VEC_DotProduct(&normal, &ptcl->position) <= 0) {
                    negate(&ptcl->position);
                }
                scale_vec(&ptcl->position, emitter->radius);
            } else {
                if (VEC_DotProduct(&normal, &ptcl->position) < 0) {
                    negate(&ptcl->position);
                }
                ptcl->position.x = particle_fx_mul(particle_fx_mul(ptcl->position.x, emitter->radius),
                                                   particle_asr(particle_random_range(0x1000), 1) + 0x800);
                ptcl->position.y = particle_fx_mul(particle_fx_mul(ptcl->position.y, emitter->radius),
                                                   particle_asr(particle_random_range(0x1000), 1) + 0x800);
                ptcl->position.z = particle_fx_mul(particle_fx_mul(ptcl->position.z, emitter->radius),
                                                   particle_asr(particle_random_range(0x1000), 1) + 0x800);
            }
            break;
        }
        case SHAPE_CYLINDER:
        case SHAPE_CYLINDER_FILLED:
            /* The direction round the axis is kept in the velocity, which Particle_Emit then
             * makes from it. */
            Particle_RandomDirectionXY(&ptcl->velocity);
            if (shape == SHAPE_CYLINDER) {
                pos.x = particle_fx_mul(ptcl->velocity.x, emitter->radius);
                pos.y = particle_fx_mul(ptcl->velocity.y, emitter->radius);
            } else {
                pos.x = particle_fx_mul(particle_fx_mul(ptcl->velocity.x, emitter->radius), particle_random_range(0x1000));
                pos.y = particle_fx_mul(particle_fx_mul(ptcl->velocity.y, emitter->radius), particle_random_range(0x1000));
            }
            pos.z = particle_random_range(emitter->length);
            Particle_FromEmitterAxes(&ptcl->position, &pos, emitter);
            break;
        default:
            break;
    }
}

/* Whether the shape lies on the emitter's axes, which are then worked out first. */
static int shape_uses_axes(u32 shape)
{
    switch (shape) {
        case SHAPE_CIRCLE:
        case SHAPE_CIRCLE_EVEN:
        case SHAPE_DISC:
        case SHAPE_CYLINDER:
        case SHAPE_CYLINDER_FILLED:
        case SHAPE_HEMISPHERE:
        case SHAPE_HALF_BALL:
            return 1;
        default:
            return 0;
    }
}

/* func_020fded0: the emitter gives off its count of particles (with the fraction carried from
 * the last time), taken from `free_particles` while there are any. Each starts at its place by
 * the shape, moving away from the emitter's centre (or round the cylinder, or a random way
 * from the centre itself) and along the axis, each speed less a random part; at the
 * emitter's scale, the header's colour (or a random one of the animation's three), the
 * emitter's alpha, a life less a random part, and the resource's texture.
 * QUIRK: an animated texture's random start texture is taken by a remainder by the frame
 * count, 0 for a count of 0 (the ROM's division); the loop's and the life's factors are
 * 0xffff when the loop's frames or the life are 0, as the ROM's division gives. */
void Particle_Emit(ParticleEmitter *emitter, ParticleList *free_particles)
{
    const ParticleResource *res = emitter->resource;
    const ParticleHeader *header = res->header;
    s32 total = particle_add(header->emission_count, emitter->emission_fraction);
    int count = particle_asr(total, 12);
    u32 shape = header->flags & 0xf;

    emitter->emission_fraction = (s16) (total & 0xfff);
    if (shape_uses_axes(shape)) {
        Particle_ComputeEmitterAxes(emitter);
    }

    for (int i = 0; i < count; i++) {
        Particle *ptcl = (Particle *) ParticleList_Pop(free_particles);
        s32 speed;
        s32 axis_speed;
        Vec3 away;

        if (ptcl == NULL) {
            return;
        }
        ParticleList_Push(&emitter->particles, &ptcl->link);

        start_position(emitter, ptcl, shape, i, count);

        speed = particle_random_around(emitter->speed, header->random_speed);
        axis_speed = particle_random_around(emitter->axis_speed, header->random_speed);
        if (shape == SHAPE_CYLINDER) {
            Vec3 round;
            round.x = particle_add(particle_fx_mul(ptcl->velocity.x, emitter->cross1.x),
                                   particle_fx_mul(ptcl->velocity.y, emitter->cross2.x));
            round.y = particle_add(particle_fx_mul(ptcl->velocity.x, emitter->cross1.y),
                                   particle_fx_mul(ptcl->velocity.y, emitter->cross2.y));
            round.z = particle_add(particle_fx_mul(ptcl->velocity.x, emitter->cross1.z),
                                   particle_fx_mul(ptcl->velocity.y, emitter->cross2.z));
            VEC_Normalize(&round, &away);
        } else if (ptcl->position.x == 0 && ptcl->position.y == 0 && ptcl->position.z == 0) {
            Particle_RandomDirection(&away);
        } else {
            VEC_Normalize(&ptcl->position, &away);
        }
        ptcl->velocity.x = particle_add(particle_fx_mul(away.x, speed), particle_fx_mul(emitter->axis.x, axis_speed));
        ptcl->velocity.y = particle_add(particle_fx_mul(away.y, speed), particle_fx_mul(emitter->axis.y, axis_speed));
        ptcl->velocity.z = particle_add(particle_fx_mul(away.z, speed), particle_fx_mul(emitter->axis.z, axis_speed));

        ptcl->emitter_pos = emitter->position;
        ptcl->base_scale = particle_random_around(emitter->base_scale, header->random_scale);
        ptcl->anim_scale = 0x1000;

        if ((header->flags & PARTICLE_HAS_COLOR_ANIM) && (res->color_anim->flags & 1)) {
            u32 pick = particle_random_bits(12);
            u16 colors[3];
            colors[0] = res->color_anim->start;
            colors[1] = header->color;
            colors[2] = res->color_anim->end;
            ptcl->color = colors[pick % 3];
        } else {
            ptcl->color = header->color;
        }

        ptcl->visibility = (u16) particle_with_bits(ptcl->visibility, PARTICLE_BASE_ALPHA_SHIFT, 5,
                                                    particle_bits(emitter->misc, EMITTER_BASE_ALPHA_SHIFT, 8));
        ptcl->visibility = (u16) particle_with_bits(ptcl->visibility, PARTICLE_ANIM_ALPHA_SHIFT, 5, 31);

        if (header->flags & PARTICLE_RANDOM_ANGLE) {
            ptcl->rotation = (u16) particle_random();
        } else {
            ptcl->rotation = 0;
        }
        if (header->flags & PARTICLE_HAS_ROTATION) {
            /* A random angular velocity from min to max. */
            u32 between = (u32) (header->max_rotation - header->min_rotation) * particle_random_bits(12) +
                          (u32) header->min_rotation * 0x1000u;
            ptcl->angular_velocity = (s16) (between >> 12);
        } else {
            ptcl->angular_velocity = 0;
        }

        ptcl->life = (u16) (particle_random_less(emitter->particle_life, header->random_life) + 1);
        ptcl->age = 0;

        if ((header->flags & PARTICLE_HAS_TEX_ANIM) && (res->tex_anim->flags & 1)) {
            u32 pick = particle_random_bits(12);
            u32 frames = res->tex_anim->count;
            ptcl->texture = res->tex_anim->textures[frames != 0 ? pick % frames : 0];
        } else if (header->flags & PARTICLE_HAS_TEX_ANIM) {
            ptcl->texture = res->tex_anim->textures[0];
        } else {
            ptcl->texture = header->texture;
        }

        ptcl->loop_factor = (u16) particle_div(0xffff, (s32) particle_bits(res->header->misc, PARTICLE_LOOP_FRAMES_SHIFT, 8));
        ptcl->life_factor = (u16) particle_div(0xffff, ptcl->life);
        ptcl->loop_offset = 0;
        if (header->flags & PARTICLE_RANDOM_LOOP_START) {
            ptcl->loop_offset = (u8) particle_random_bits(8);
        }
    }
}
CLEAN_AS(func_020fded0, Particle_Emit)

/* func_020fdc08: the particle gives off its children, taken from `free_particles` while there
 * are any: at its place, with its velocity times the child part's ratio and a random push, a
 * part of its scale, its colour or the child part's, its alpha, its angle (and turning) as
 * the child part says, and the child part's life and texture.
 * QUIRK: the loop's and the life's factors are worked out from the parent's life; the
 * children's own animations go by their age over their life instead. A rotation type of 3
 * leaves a child's angle and turning as the free particle had them. */
void Particle_EmitChildren(Particle *ptcl, ParticleEmitter *emitter, ParticleList *free_particles)
{
    const ParticleChild *child = emitter->resource->child;

    for (int i = 0; i < child->count; i++) {
        Particle *kid = (Particle *) ParticleList_Pop(free_particles);
        fx32 ratio;
        s32 scale;
        u32 alpha;

        if (kid == NULL) {
            return;
        }
        ParticleList_Push(&emitter->children, &kid->link);

        kid->position = ptcl->position;
        ratio = FX_Div(child->speed_ratio * 0x1000, 255 * 0x1000);
        kid->velocity.x = particle_add(particle_fx_mul(ptcl->velocity.x, ratio), particle_random_range(child->random_speed));
        kid->velocity.y = particle_add(particle_fx_mul(ptcl->velocity.y, ratio), particle_random_range(child->random_speed));
        kid->velocity.z = particle_add(particle_fx_mul(ptcl->velocity.z, ratio), particle_random_range(child->random_speed));
        kid->emitter_pos = ptcl->emitter_pos;

        scale = particle_asr(particle_mul(ptcl->base_scale, ptcl->anim_scale), 12);
        kid->base_scale = particle_asr(particle_mul(scale, child->scale_ratio + 1), 6);
        kid->anim_scale = 0x1000;

        kid->color = (child->flags & PARTICLE_CHILD_OWN_COLOR) ? child->color : ptcl->color;

        alpha = (particle_bits(ptcl->visibility, PARTICLE_BASE_ALPHA_SHIFT, 5) *
                 (particle_bits(ptcl->visibility, PARTICLE_ANIM_ALPHA_SHIFT, 5) + 1)) >>
                5;
        kid->visibility = (u16) particle_with_bits(kid->visibility, PARTICLE_BASE_ALPHA_SHIFT, 5, alpha);
        kid->visibility = (u16) particle_with_bits(kid->visibility, PARTICLE_ANIM_ALPHA_SHIFT, 5, 31);

        switch (particle_bits(child->flags, PARTICLE_CHILD_ROTATION_SHIFT, 2)) {
            case 0:
                kid->rotation = 0;
                kid->angular_velocity = 0;
                break;
            case 1:
                kid->rotation = ptcl->rotation;
                kid->angular_velocity = 0;
                break;
            case 2:
                kid->rotation = ptcl->rotation;
                kid->angular_velocity = ptcl->angular_velocity;
                break;
            default:
                break;
        }

        kid->life = child->life;
        kid->age = 0;
        kid->texture = child->texture;
        kid->loop_factor = (u16) particle_div(0xffff, ptcl->life / 2);
        kid->life_factor = (u16) particle_div(0xffff, ptcl->life);
        kid->loop_offset = 0;
    }
}
CLEAN_AS(func_020fdc08, Particle_EmitChildren)
