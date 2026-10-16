/* The particle system (NitroSystem's SPL library, as its layout and behaviours show): a
 * manager holds emitters, each made from a resource of the particle file, and the emitters give
 * off particles, which a frame's update moves and ages and a frame's draw sends to the 3D engine.
 *
 * - Emitters and particles come from free lists the manager fills at its creation; an emitter
 *   takes particles from the manager's free list and gives them back when they are older than
 *   their life. Each particle may give off child particles of its own (the resource's child
 *   part), which live in a second list of the emitter.
 * - A resource is a header (ParticleHeader) and the parts its flags announce: scale, colour,
 *   alpha and texture animations, the child part, and up to six behaviours (gravity, random
 *   push, magnet, spin, collision plane, convergence) run on each particle every update.
 * - Particles are drawn as billboards, as billboards stretched along their velocity, or as
 *   polygons turned by one of the rotation functions of a table; each sets the polygon's
 *   attributes, matrix and colour and draws one textured quad.
 *
 * Positions are in 20.12 fixed point; angles are 16-bit fractions of a turn. */
#ifndef CLEAN_AUTOLOAD_2_PARTICLE_H
#define CLEAN_AUTOLOAD_2_PARTICLE_H

#include "matrix.h"
#include "types.h"
#include "vector.h"

/* A vector in 4.12 fixed point (NitroSDK's VecFx16). */
typedef struct ParticleVec16 {
    fx16 x;
    fx16 y;
    fx16 z;
} ParticleVec16;

/* A 3x3 matrix (NitroSDK's MtxFx33). */
typedef struct ParticleMtx33 {
    fx32 m[3][3];
} ParticleMtx33;

/* The links of an emitter or a particle in one of the lists. */
typedef struct ParticleLink {
    struct ParticleLink *next; /* 0x00: towards the oldest */
    struct ParticleLink *prev; /* 0x04: towards the newest, the list's first */
} ParticleLink;

/* A list: its newest member first. */
typedef struct ParticleList {
    ParticleLink *first; /* 0x00 */
    int count;           /* 0x04 */
} ParticleList;

/* --- The particle file --- */

/* ParticleHeader.flags */
#define PARTICLE_EMISSION_SHIFT 0 /* 4 bits: the shape particles start in (Particle_Emit) */
#define PARTICLE_DRAW_SHIFT 4     /* 2 bits: 0 billboard, 1 along the velocity, 2 polygon */
#define PARTICLE_AXIS_SHIFT 6     /* 2 bits: the emitter's axis: 0 Z, 1 Y, 2 X, 3 its own */
#define PARTICLE_HAS_SCALE_ANIM (1u << 8)
#define PARTICLE_HAS_COLOR_ANIM (1u << 9)
#define PARTICLE_HAS_ALPHA_ANIM (1u << 10)
#define PARTICLE_HAS_TEX_ANIM (1u << 11)
#define PARTICLE_HAS_ROTATION (1u << 12)     /* a random angular velocity */
#define PARTICLE_RANDOM_ANGLE (1u << 13)     /* a random first angle */
#define PARTICLE_SELF_MAINTAINING (1u << 14) /* the emitter ends by itself after its life */
#define PARTICLE_FOLLOW_EMITTER (1u << 15)
#define PARTICLE_HAS_CHILDREN (1u << 16)
#define PARTICLE_ROT_TYPE_SHIFT 17  /* 2 bits: the polygon's rotation function */
#define PARTICLE_QUAD_TYPE_SHIFT 19 /* 1 bit: the polygon's quad function */
#define PARTICLE_RANDOM_LOOP_START (1u << 20)
#define PARTICLE_CHILDREN_FIRST (1u << 21)
#define PARTICLE_HIDE_PARENTS (1u << 22)
#define PARTICLE_VIEW_SPACE (1u << 23) /* drawn about the resource's base position */
#define PARTICLE_GRAVITY (1u << 24)
#define PARTICLE_RANDOM (1u << 25)
#define PARTICLE_MAGNET (1u << 26)
#define PARTICLE_SPIN (1u << 27)
#define PARTICLE_COLLISION (1u << 28)
#define PARTICLE_CONVERGE (1u << 29)
#define PARTICLE_FIXED_POLYGON_ID (1u << 30)
#define PARTICLE_CHILD_FIXED_POLYGON_ID (1u << 31)

/* ParticleHeader.misc */
#define PARTICLE_LOOP_FRAMES_SHIFT 0 /* 8 bits */
#define PARTICLE_STRETCH_SHIFT 8     /* 16 bits: how much a particle along its velocity stretches */
#define PARTICLE_TEX_S_SHIFT 24      /* 2 bits: the texture repeats 1 << n times in S */
#define PARTICLE_TEX_T_SHIFT 26      /* 2 bits: and in T */
#define PARTICLE_SCALE_DIR_SHIFT 28  /* 3 bits: 0 the scale animation scales X and Y, 1 X, 2 Y */

/* ParticleHeader.draw_flags */
#define PARTICLE_TILT 0x10 /* the draw callback's angle tilts the particle about X */

/* A resource's header in the file, 0x54 bytes. */
typedef struct ParticleHeader {
    u32 flags;            /* 0x00 */
    Vec3 base_pos;        /* 0x04: added to an emitter's position */
    fx32 emission_count;  /* 0x10: particles given off each time, with a fraction */
    fx32 radius;          /* 0x14 */
    fx32 length;          /* 0x18 */
    ParticleVec16 axis;   /* 0x1c */
    u16 color;            /* 0x22 */
    fx32 speed;           /* 0x24: the first speed away from the emitter's centre */
    fx32 axis_speed;      /* 0x28: the first speed along the emitter's axis */
    fx32 base_scale;      /* 0x2c */
    fx16 aspect;          /* 0x30: X's scale over Y's */
    u16 start_delay;      /* 0x32: frames before the emitter starts */
    s16 min_rotation;     /* 0x34 */
    s16 max_rotation;     /* 0x36 */
    u16 emitter_life;     /* 0x38: frames; 0 for ever */
    u16 particle_life;    /* 0x3a */
    u8 random_scale;      /* 0x3c: how much of each the random numbers take off */
    u8 random_life;       /* 0x3d */
    u8 random_speed;      /* 0x3e */
    u8 pad_3f;            /* 0x3f */
    u8 emission_interval; /* 0x40: frames between emissions */
    u8 base_alpha;        /* 0x41 */
    u8 air_resistance;    /* 0x42: the velocity is kept (0x180 + this) / 0x200 */
    u8 texture;           /* 0x43 */
    u32 misc;             /* 0x44: PARTICLE_*_SHIFT */
    u32 tex_flip;         /* 0x48: bit 0 flips S, bit 1 T */
    fx16 polygon_x;       /* 0x4c: the polygon's centre */
    fx16 polygon_y;       /* 0x4e */
    u8 draw_flags;        /* 0x50 */
    u8 pad_51[3];         /* 0x51 */
} ParticleHeader;

/* A scale animation: start, middle and end, the middle from `in` to `out` (of 255). */
typedef struct ParticleScaleAnim {
    fx16 start; /* 0x00 */
    fx16 mid;   /* 0x02 */
    fx16 end;   /* 0x04 */
    u8 in;      /* 0x06 */
    u8 out;     /* 0x07 */
    u16 flags;  /* 0x08: bit 0 runs on the loop's rate */
    u16 pad_0a;
} ParticleScaleAnim;

/* A colour animation: start, the header's colour from `peak`, end from `out`. */
typedef struct ParticleColorAnim {
    u16 start; /* 0x00 */
    u16 end;   /* 0x02 */
    u8 in;     /* 0x04 */
    u8 peak;   /* 0x05 */
    u8 out;    /* 0x06 */
    u8 pad_07;
    u16 flags; /* 0x08: bit 0 a random one of the three colours instead, bit 1 loop, bit 2 blend */
    u16 pad_0a;
} ParticleColorAnim;

/* An alpha animation: three alphas of 5 bits in `alpha`, the middle from `in` to `out`. */
typedef struct ParticleAlphaAnim {
    u16 alpha;       /* 0x00: start bits 0-4, middle 5-9, end 10-14 */
    u8 random_range; /* 0x02 */
    u8 flags;        /* 0x03: bit 0 loop */
    u8 in;           /* 0x04 */
    u8 out;          /* 0x05 */
    u16 pad_06;
} ParticleAlphaAnim;

/* A texture animation: `count` textures, each for `step` of 255. */
typedef struct ParticleTexAnim {
    u8 textures[8]; /* 0x00 */
    u8 count;       /* 0x08 */
    u8 step;        /* 0x09 */
    u16 flags;      /* 0x0a: bit 0 a random first texture (and no animation), bit 1 loop */
} ParticleTexAnim;

/* ParticleChild.flags */
#define PARTICLE_CHILD_BEHAVIORS (1u << 0) /* the parent's behaviours run on the children */
#define PARTICLE_CHILD_SCALE_ANIM (1u << 1)
#define PARTICLE_CHILD_ALPHA_ANIM (1u << 2)
#define PARTICLE_CHILD_ROTATION_SHIFT 3 /* 2 bits: 0 none, 1 the parent's angle, 2 and turning */
#define PARTICLE_CHILD_FOLLOW_EMITTER (1u << 5)
#define PARTICLE_CHILD_OWN_COLOR (1u << 6)
#define PARTICLE_CHILD_DRAW_SHIFT 7     /* 2 bits, as PARTICLE_DRAW_SHIFT */
#define PARTICLE_CHILD_ROT_TYPE_SHIFT 9 /* 2 bits */
#define PARTICLE_CHILD_QUAD_TYPE_SHIFT 11

/* The children a particle gives off. */
typedef struct ParticleChild {
    u16 flags;         /* 0x00 */
    fx16 random_speed; /* 0x02 */
    fx16 end_scale;    /* 0x04 */
    u16 life;          /* 0x06 */
    u8 speed_ratio;    /* 0x08: of the parent's velocity, out of 255 */
    u8 scale_ratio;    /* 0x09: of the parent's scale, (n + 1) / 64 */
    u16 color;         /* 0x0a */
    u8 count;          /* 0x0c: children each time */
    u8 delay;          /* 0x0d: of the parent's life (of 255) before the first */
    u8 interval;       /* 0x0e */
    u8 texture;        /* 0x0f */
    u32 tex_flags;     /* 0x10: repeat S bits 0-1, T 2-3, flip S bit 4, T bit 5 */
} ParticleChild;

struct Particle;
struct ParticleEmitter;

/* A behaviour, called for each particle with the frame's acceleration to add to. */
typedef void (*ParticleBehaviorFn)(const void *data, struct Particle *ptcl, Vec3 *acc, struct ParticleEmitter *emitter);
typedef struct ParticleBehavior {
    ParticleBehaviorFn fn; /* 0x00: one of the game's six */
    const void *data;      /* 0x04: its part of the file */
} ParticleBehavior;

typedef struct ParticleGravity {
    ParticleVec16 force; /* 0x00 */
    u16 pad_06;
} ParticleGravity;

typedef struct ParticleRandom {
    ParticleVec16 range; /* 0x00 */
    u16 interval;        /* 0x06: frames of the particle's age between pushes */
} ParticleRandom;

/* The magnet and the convergence: a target and a strength. */
typedef struct ParticleTarget {
    Vec3 target;   /* 0x00 */
    fx16 strength; /* 0x0c */
    u16 pad_0e;
} ParticleTarget;

typedef struct ParticleSpin {
    u16 angle; /* 0x00: a turn each frame */
    u16 axis;  /* 0x02: 0 X, 1 Y, 2 Z */
} ParticleSpin;

typedef struct ParticleCollision {
    fx32 y;          /* 0x00: the plane's height, unless the emitter has its own */
    fx16 elasticity; /* 0x04 */
    u16 flags;       /* 0x06: bits 0-1: 0 the particle ends there, 1 it bounces */
} ParticleCollision;

/* A resource as the manager keeps it: pointers into the file. */
typedef struct ParticleResource {
    const ParticleHeader *header;        /* 0x00 */
    const ParticleScaleAnim *scale_anim; /* 0x04 */
    const ParticleColorAnim *color_anim; /* 0x08 */
    const ParticleAlphaAnim *alpha_anim; /* 0x0c */
    const ParticleTexAnim *tex_anim;     /* 0x10 */
    const ParticleChild *child;          /* 0x14 */
    ParticleBehavior *behaviors;         /* 0x18 */
    u16 behavior_count;                  /* 0x1c */
    u16 pad_1e;
} ParticleResource;

/* ParticleTexFile.param and ParticleTexture.param */
#define PARTICLE_TEX_FORMAT_MASK 0xfu   /* GXTexFmt: 2 four-colour, 5 4x4 compressed */
#define PARTICLE_TEX_SIZE_S_SHIFT 4     /* 4 bits: 8 << n texels */
#define PARTICLE_TEX_SIZE_T_SHIFT 8     /* 4 bits */
#define PARTICLE_TEX_REPEAT_SHIFT 12    /* 2 bits */
#define PARTICLE_TEX_FLIP_SHIFT 14      /* 2 bits */
#define PARTICLE_TEX_COLOR0_SHIFT 16    /* 1 bit: palette colour 0 is transparent */
#define PARTICLE_TEX_SHARED (1u << 17)  /* the image of another texture of the file */
#define PARTICLE_TEX_SHARED_ID_SHIFT 18 /* 8 bits: that texture */
#define PARTICLE_TEX_FORMAT_PLTT4 2
#define PARTICLE_TEX_FORMAT_COMP4X4 5

/* A texture in the file: this header, its image at 0x20, its palette at `palette`. */
typedef struct ParticleTexFile {
    u32 magic;        /* 0x00 */
    u32 param;        /* 0x04 */
    u32 image_size;   /* 0x08 */
    u32 palette;      /* 0x0c: the palette's offset from this header */
    u32 palette_size; /* 0x10 */
    u32 unk_14;
    u32 unk_18;
    u32 size; /* 0x1c: the texture's bytes with this header */
} ParticleTexFile;

/* A texture as the manager keeps it, with its places in VRAM. */
typedef struct ParticleTexture {
    const ParticleTexFile *file; /* 0x00 */
    u32 image_addr;              /* 0x04 */
    u32 palette_addr;            /* 0x08 */
    u32 param;                   /* 0x0c */
    u16 width;                   /* 0x10 */
    u16 height;                  /* 0x12 */
} ParticleTexture;

/* The file's header. */
typedef struct ParticleFile {
    u32 magic;          /* 0x00 */
    u32 version;        /* 0x04 */
    u16 resource_count; /* 0x08 */
    u16 texture_count;  /* 0x0a */
    u8 unk_0c[0x14];
} ParticleFile;

/* --- What the manager keeps --- */

/* Particle.visibility */
#define PARTICLE_BASE_ALPHA_SHIFT 0  /* 5 bits */
#define PARTICLE_ANIM_ALPHA_SHIFT 5  /* 5 bits */
#define PARTICLE_POLYGON_ID_SHIFT 10 /* 6 bits */

typedef struct Particle {
    ParticleLink link;    /* 0x00 */
    Vec3 position;        /* 0x08: from emitter_pos */
    Vec3 velocity;        /* 0x14 */
    u16 rotation;         /* 0x20 */
    s16 angular_velocity; /* 0x22 */
    u16 life;             /* 0x24 */
    u16 age;              /* 0x26 */
    u16 loop_factor;      /* 0x28: 0xffff over the loop's frames */
    u16 life_factor;      /* 0x2a: 0xffff over the life */
    u8 texture;           /* 0x2c */
    u8 loop_offset;       /* 0x2d */
    u16 visibility;       /* 0x2e */
    fx32 base_scale;      /* 0x30 */
    fx16 anim_scale;      /* 0x34 */
    u16 color;            /* 0x36 */
    Vec3 emitter_pos;     /* 0x38 */
} Particle;

/* ParticleEmitter.state */
#define EMITTER_ENDING (1u << 0) /* removed once it has no particles left */
#define EMITTER_NO_EMISSION (1u << 1)
#define EMITTER_NO_UPDATE (1u << 2)
#define EMITTER_HIDDEN (1u << 3)
#define EMITTER_STARTED (1u << 4) /* set after the start delay; its age counts from there */

/* ParticleEmitter.misc */
#define EMITTER_INTERVAL_SHIFT 0      /* 8 bits */
#define EMITTER_BASE_ALPHA_SHIFT 8    /* 8 bits */
#define EMITTER_UPDATE_CYCLE_SHIFT 16 /* 3 bits: 0 every frame, n on frames of parity n - 1 */

/* No collision height of the emitter's own. */
#define EMITTER_NO_COLLISION_Y ((fx32) INT32_MIN)

typedef struct ParticleEmitter {
    ParticleLink link;                                                     /* 0x00 */
    ParticleList particles;                                                /* 0x08 */
    ParticleList children;                                                 /* 0x10 */
    const ParticleResource *resource;                                      /* 0x18 */
    u32 state;                                                             /* 0x1c */
    Vec3 position;                                                         /* 0x20 */
    Vec3 velocity;                                                         /* 0x2c */
    u16 age;                                                               /* 0x38 */
    s16 emission_fraction;                                                 /* 0x3a */
    ParticleVec16 axis;                                                    /* 0x3c */
    u16 init_angle;                                                        /* 0x42 */
    fx32 radius;                                                           /* 0x44 */
    fx32 length;                                                           /* 0x48 */
    fx32 speed;                                                            /* 0x4c */
    fx32 axis_speed;                                                       /* 0x50 */
    fx32 base_scale;                                                       /* 0x54 */
    u16 particle_life;                                                     /* 0x58 */
    u16 color;                                                             /* 0x5a */
    fx32 collision_y;                                                      /* 0x5c */
    s16 tex_s;                                                             /* 0x60: the quad's texture coordinates */
    s16 tex_t;                                                             /* 0x62 */
    s16 child_tex_s;                                                       /* 0x64 */
    s16 child_tex_t;                                                       /* 0x66 */
    u32 misc;                                                              /* 0x68 */
    ParticleVec16 cross1;                                                  /* 0x6c: two axes square to `axis` */
    ParticleVec16 cross2;                                                  /* 0x72 */
    void (*callback)(struct ParticleEmitter *emitter, unsigned int after); /* 0x78 */
    void *user_ptr;                                                        /* 0x7c */
    u32 user_data;                                                         /* 0x80 */
} ParticleEmitter;

/* ParticleSystem.polygon_ids */
#define PARTICLE_ID_MIN_SHIFT 0    /* 6 bits: the polygon IDs given in turn */
#define PARTICLE_ID_MAX_SHIFT 6    /* 6 bits */
#define PARTICLE_ID_NEXT_SHIFT 12  /* 6 bits */
#define PARTICLE_ID_FIXED_SHIFT 18 /* 6 bits: the one for resources with a fixed ID */

/* The draw callback: given the particle's place (twice: by address and by value), the angle
 * a tilted particle turns by. */
typedef fx32 (*ParticleDrawCallback)(Vec3 *pos, Vec3 value);

typedef struct ParticleSystem {
    void *(*alloc)(u32 size);    /* 0x00 */
    ParticleList emitters;       /* 0x04 */
    ParticleList free_emitters;  /* 0x0c */
    ParticleList free_particles; /* 0x14 */
    ParticleResource *resources; /* 0x1c */
    ParticleTexture *textures;   /* 0x20 */
    u16 resource_count;          /* 0x24 */
    u16 texture_count;           /* 0x26 */
    u16 max_emitters;            /* 0x28 */
    u16 max_particles;           /* 0x2a */
    u32 polygon_ids;             /* 0x2c */
    u32 polygon_attr;            /* 0x30: or-ed into each particle's polygon attributes */
    ParticleEmitter *emitter;    /* 0x34: the one being drawn */
    const Mtx43 *view;           /* 0x38 */
} ParticleSystem;

/* `width` bits of `word` from bit `shift`. */
static inline u32 particle_bits(u32 word, int shift, int width)
{
    return (word >> shift) & ((1u << width) - 1);
}

/* `word` with `width` bits from bit `shift` set to `value`. */
static inline u32 particle_with_bits(u32 word, int shift, int width, u32 value)
{
    u32 mask = ((1u << width) - 1) << shift;
    return (word & ~mask) | ((value << shift) & mask);
}

/* The ARM's 32-bit arithmetic: sums and products wrap. */
static inline s32 particle_add(s32 a, s32 b)
{
    return (s32) ((u32) a + (u32) b);
}

static inline s32 particle_sub(s32 a, s32 b)
{
    return (s32) ((u32) a - (u32) b);
}

static inline s32 particle_mul(s32 a, s32 b)
{
    return (s32) ((u32) a * (u32) b);
}

/* An arithmetic shift right, as the ARM's ASR does it, for negative values too. */
static inline s32 particle_asr(s32 value, int bits)
{
    return value >= 0 ? value >> bits : ~(~value >> bits);
}

/* `a` times `b` in 20.12, rounded to nearest, kept to 32 bits (FX_MUL). */
static inline fx32 particle_fx_mul(s32 a, s32 b)
{
    return (fx32) (u32) ((u64) ((s64) a * b + 0x800) >> 12);
}

/* The ROM's signed division (_s32_div_f): a divisor of 0 gives the numerator back, and
 * INT32_MIN / -1 gives INT32_MIN. */
static inline s32 particle_div(s32 numerator, s32 divisor)
{
    if (divisor == 0) {
        return numerator;
    }
    if (divisor == -1) {
        return particle_sub(0, numerator);
    }
    return numerator / divisor;
}

/* Its remainder: 0 for a divisor of 0 (and of -1). */
static inline s32 particle_mod(s32 numerator, s32 divisor)
{
    if (divisor == 0 || divisor == -1) {
        return 0;
    }
    return numerator % divisor;
}

/* The particle system's random numbers: a linear congruential generator of its own. */
extern u32 data_021fd278;

static inline u32 particle_random(void)
{
    data_021fd278 = data_021fd278 * 0x5eedf715u + 0x1b0cb173u;
    return data_021fd278;
}

/* The top `bits` bits of the next random number. */
static inline u32 particle_random_bits(int bits)
{
    return particle_random() >> (32 - bits);
}

/* A random value from -`range` to `range` (less one 256th). */
static inline s32 particle_random_range(s32 range)
{
    s32 r = (s32) particle_random_bits(9);
    return particle_asr(particle_sub(particle_mul(range, r), particle_mul(range, 256)), 8);
}

/* `value` less a random part of up to `amount` / 256 of it (amount 0 to 255). */
static inline s32 particle_random_less(s32 value, int amount)
{
    s32 r = (s32) particle_random_bits(8);
    return particle_asr(particle_mul(value, 255 - ((amount * r) >> 8)), 8);
}

/* `value` more or less a random part of up to `amount` / 256 of it. */
static inline s32 particle_random_around(s32 value, int amount)
{
    s32 r = (s32) particle_random_bits(8);
    return particle_asr(particle_mul(value, 255 + amount - ((amount * r) >> 7)), 8);
}

/* particle_system.c */
ParticleLink *ParticleList_Remove(ParticleList *list, ParticleLink *node);
ParticleLink *ParticleList_Pop(ParticleList *list);
void ParticleList_Push(ParticleList *list, ParticleLink *node);
void ParticleSys_EmitAt(ParticleSystem *sys, ParticleEmitter *emitter, const Vec3 *offset);
ParticleEmitter *ParticleSys_CreateEmitterWith(ParticleSystem *sys, int resource, void (*init)(ParticleEmitter *emitter));
ParticleEmitter *ParticleSys_CreateEmitterAt(ParticleSystem *sys, int resource, const Vec3 *pos);
void ParticleSys_Draw(ParticleSystem *sys, const Mtx43 *view, ParticleDrawCallback callback);
void ParticleSys_Update(ParticleSystem *sys);
int ParticleSys_UploadPalettes(ParticleSystem *sys);
int ParticleSys_UploadTextures(ParticleSystem *sys);
int ParticleSys_UploadPalettesWith(ParticleSystem *sys, u32 (*alloc)(u32 size, int four_colors));
int ParticleSys_UploadTexturesWith(ParticleSystem *sys, u32 (*alloc)(u32 size, int compressed));
void ParticleSys_LoadResources(ParticleSystem *sys, const u8 *file);
void ParticleSys_LoadTextures(ParticleSystem *sys, const ParticleFile *file);
ParticleSystem *ParticleSys_Create(void *(*alloc)(u32 size), int max_emitters, int max_particles, int fixed_id, u16 min_id,
                                   u16 max_id);
int ParticleSys_AllocPaletteVram(int size, int four_colors);
int ParticleSys_AllocTextureVram(int size, int compressed);
void ParticleSys_EmitFrom(ParticleEmitter *emitter, ParticleList *free_particles);
void ParticleSys_DrawEmitter(ParticleSystem *sys, ParticleDrawCallback callback);
void ParticleSys_DrawChildren(ParticleSystem *sys, ParticleDrawCallback callback);
void ParticleSys_DrawParents(ParticleSystem *sys, ParticleDrawCallback callback);
void ParticleSys_UpdateEmitter(ParticleSystem *sys, ParticleEmitter *emitter);
void ParticleEmitter_Init(ParticleEmitter *emitter, const ParticleResource *resource, const Vec3 *pos);

/* particle_draw.c */
void ParticleDraw_NoTexture(const ParticleTexture *texture);
void ParticleDraw_BindTexture(const ParticleTexture *texture);
void ParticleDraw_ChildPolygon(ParticleSystem *sys, Particle *ptcl, ParticleDrawCallback callback);
void ParticleDraw_Polygon(ParticleSystem *sys, Particle *ptcl, ParticleDrawCallback callback);
void ParticleDraw_ChildStretched(ParticleSystem *sys, Particle *ptcl, ParticleDrawCallback callback);
void ParticleDraw_Stretched(ParticleSystem *sys, Particle *ptcl, ParticleDrawCallback callback);
void ParticleDraw_ChildBillboard(ParticleSystem *sys, Particle *ptcl, ParticleDrawCallback callback);
void ParticleDraw_Billboard(ParticleSystem *sys, Particle *ptcl, ParticleDrawCallback callback);
void ParticleDraw_RotY(fx32 sine, fx32 cosine, Mtx43 *mtx);
void ParticleDraw_RotDiagonal(fx32 sine, fx32 cosine, Mtx43 *mtx);
void ParticleDraw_QuadXZ(fx32 s, fx32 t, fx32 x, fx32 z);
void ParticleDraw_QuadXY(fx32 s, fx32 t, fx32 x, fx32 y);

/* particle_emit.c */
void Particle_EmitChildren(Particle *ptcl, ParticleEmitter *emitter, ParticleList *free_particles);
void Particle_Emit(ParticleEmitter *emitter, ParticleList *free_particles);
void Particle_FromEmitterAxes(Vec3 *out, const Vec3 *pos, const ParticleEmitter *emitter);
void Particle_ComputeEmitterAxes(ParticleEmitter *emitter);
void Particle_RandomDirectionXY(Vec3 *vec);
void Particle_RandomDirection(Vec3 *vec);

/* particle_anim.c */
void ParticleAnim_ChildAlpha(Particle *ptcl, const ParticleResource *res, int rate);
void ParticleAnim_ChildScale(Particle *ptcl, const ParticleResource *res, int rate);
void ParticleAnim_Texture(Particle *ptcl, const ParticleResource *res, int rate);
void ParticleAnim_Alpha(Particle *ptcl, const ParticleResource *res, int rate);
void ParticleAnim_Color(Particle *ptcl, const ParticleResource *res, int rate);
void ParticleAnim_Scale(Particle *ptcl, const ParticleResource *res, int rate);
void ParticleBehavior_Converge(const ParticleTarget *data, Particle *ptcl, Vec3 *acc, ParticleEmitter *emitter);
void ParticleBehavior_Collision(const ParticleCollision *data, Particle *ptcl, Vec3 *acc, ParticleEmitter *emitter);
void ParticleBehavior_Spin(const ParticleSpin *data, Particle *ptcl, Vec3 *acc, ParticleEmitter *emitter);
void ParticleBehavior_Magnet(const ParticleTarget *data, Particle *ptcl, Vec3 *acc, ParticleEmitter *emitter);
void ParticleBehavior_Random(const ParticleRandom *data, Particle *ptcl, Vec3 *acc, ParticleEmitter *emitter);
void ParticleBehavior_Gravity(const ParticleGravity *data, Particle *ptcl, Vec3 *acc, ParticleEmitter *emitter);

#endif
