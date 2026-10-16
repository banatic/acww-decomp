/* The effect system: a process (vtable data_020e2724, 0x186c bytes, data_021d52c4 while it
 * lives) that runs the particle effects of /spl/spl.spa and the effects drawn as models
 * (effect_models.h).
 *
 * At its creation it takes 0xc000 bytes of the current heap for a frame heap, makes the
 * particle manager in it (32 emitters, 100 particles), loads the file's textures into VRAM and
 * copies its resources into the frame heap, then loads the models. Each frame it follows its
 * instances, steps the models and updates the particles; drawn, the particles are bent over the
 * globe (Globe_BendFar) and the models drawn.
 *
 * Effects are started by sets (the table at data_020d0f88, effect_kinds.h): a set names the
 * particle resources of its emitters. The place being started is in data_021d52d4 while its
 * set's emitters are made.
 * - A one-shot set (EffectSystem_StartSet) makes its emitters with one set-up function each;
 *   a set marked shared makes each resource's emitter once (kept in the system's table of 10)
 *   and from then on only makes it emit again at the new place.
 * - A kept set (EffectSystem_StartKeptSet) makes an instance of each emitter in the system's
 *   table of 32, with two functions: one that places it at the start, one that follows it each
 *   frame until it answers 0, when the instance ends. */
#ifndef CLEAN_MAIN_EFFECT_SYSTEM_H
#define CLEAN_MAIN_EFFECT_SYSTEM_H

#include "autoload_2/particle.h"
#include "autoload_2/process.h"
#include "autoload_2/vector.h"
#include "main/effect_models.h"
#include "types.h"

#define EFFECT_SYSTEM_INSTANCES 32
#define EFFECT_SYSTEM_SHARED 10  /* the emitters of shared sets kept */
#define EFFECT_SYSTEM_SET_MAX 10 /* the emitters a kept set may have */
#define EFFECT_SYSTEM_FREE (-1)  /* the resource of a free instance or table entry */

struct EffectSystemInstance;

/* The two set-up words a kept set gives each of its emitters. */
typedef struct EffectSystemKeptSetup {
    void (*place)(struct EffectSystemInstance *instance);
    int (*follow)(struct EffectSystemInstance *instance);
} EffectSystemKeptSetup;

/* Three bytes an instance is started with, passed as one word. */
typedef struct EffectSystemInstanceTag {
    u8 index;  /* its entry in the table */
    u8 serial; /* the low byte of the system's count of kept sets started */
    u8 number; /* its emitter's number in its set */
    u8 unk_03;
} EffectSystemInstanceTag;

/* An instance of an emitter of a kept set (0x18 bytes; EffectKindsInstance is its start). */
typedef struct EffectSystemInstance {
    s32 resource;                /* 0x00: its emitter's resource, EFFECT_SYSTEM_FREE for none */
    EffectSystemInstanceTag tag; /* 0x04: its index also names its place, data_021d52d8 */
    u8 held;                     /* 0x08: 1 while it is kept on (set when it starts or its follow
                                 * function answers nonzero) */
    u8 number_again;             /* 0x09: the number again, written when an instance is reused */
    u8 unk_0a[2];
    ParticleEmitter *emitter;    /* 0x0c */
    EffectSystemKeptSetup setup; /* 0x10 */
} EffectSystemInstance;

/* The table of instances (0x304 bytes). */
typedef struct EffectSystemInstances {
    u8 next;                                            /* 0x00: where the search for a free entry starts */
    EffectSystemInstance list[EFFECT_SYSTEM_INSTANCES]; /* 0x04 */
} EffectSystemInstances;

/* An emitter of a shared set kept by its resource. */
typedef struct EffectSystemShared {
    s32 resource; /* EFFECT_SYSTEM_FREE for none */
    ParticleEmitter *emitter;
} EffectSystemShared;

/* A set of the table at data_020d0f88 (12 bytes). */
typedef struct EffectSystemSet {
    u32 flags; /* EFFECT_SYSTEM_SET_* */
    const s32 *resources;
    s32 count;
} EffectSystemSet;

#define EFFECT_SYSTEM_SET_HALVES 0x1 /* two halves: the second for a first angle >= 0 */
#define EFFECT_SYSTEM_SET_SHARED 0x2 /* one-shot set whose emitters are made once */

typedef struct EffectSystem {
    Process process;                                 /* 0x0000 */
    ParticleSystem *particles;                       /* 0x0050 */
    u32 kept_started;                                /* 0x0054: kept sets started */
    EffectSystemInstances instances;                 /* 0x0058 */
    EffectModelGroup models[EFFECT_MODELS_GROUPS];   /* 0x035c */
    EffectSystemShared shared[EFFECT_SYSTEM_SHARED]; /* 0x181c */
} EffectSystem;

void *EffectSystem_Destruct(EffectSystem *system);
void *EffectSystem_Delete(EffectSystem *system);
int EffectSystem_AddShared(EffectSystemShared *shared, int resource, ParticleEmitter *emitter);
int EffectSystem_FindShared(EffectSystemShared *shared, int resource);
void EffectSystem_DestructShared(EffectSystemShared *shared);
void EffectSystem_InitShared(EffectSystemShared *shared);
void EffectSystem_DestructSharedEntry(EffectSystemShared *entry);
void EffectSystem_InitSharedEntry(EffectSystemShared *entry);
int EffectSystem_NewInstance(EffectSystemInstances *table, int resource, const Vec3 *position, const s16 *angle,
                             const EffectSystemKeptSetup *setup, int serial, int number);
EffectSystemInstance *EffectSystem_FindInstance(EffectSystemInstances *table, int resource);
void EffectSystem_EndInstances(EffectSystemInstances *table);
void EffectSystem_FollowInstances(EffectSystemInstances *table);
void EffectSystem_InitInstances(EffectSystemInstances *table);
void EffectSystem_EndInstance(EffectSystemInstance *instance);
int EffectSystem_StartInstance(EffectSystemInstance *instance, int resource, const Vec3 *position, const s16 *angle,
                               const EffectSystemKeptSetup *setup, EffectSystemInstanceTag tag);
void EffectSystem_StartModel(int model, void (*setup)(void *transform));
int EffectSystem_StartKeptSet(int set, const Vec3 *position, const s16 *angle, void *const *setups);
int EffectSystem_StartSet(int set, const Vec3 *position, const s16 *angle, void *const *setups);
int EffectSystem_FollowTinted(EffectSystemInstance *instance);
void EffectSystem_PlaceInstance(EffectSystemInstance *instance);
void EffectSystem_PlaceEmitter(ParticleEmitter *emitter);
void EffectSystem_TintEmitter(ParticleEmitter *emitter);
int EffectSystem_PeriodColor(void);
short EffectSystem_PeriodColorOf(ParticleEmitter *emitter);
int EffectSystem_Remove(EffectSystem *system);
int EffectSystem_Draw(EffectSystem *system);
unsigned short EffectSystem_BendParticle(Vec3 *out, Vec3 position);
int EffectSystem_Execute(EffectSystem *system);
int EffectSystem_Create(EffectSystem *system);
int EffectSystem_CopyResources(EffectSystem *system, const u8 *file);
int EffectSystem_UploadTextures(EffectSystem *system);
void *EffectSystem_LoadFile(EffectSystem *system);
void *EffectSystem_Alloc(unsigned int size);
void *EffectSystem_New(void);

#endif
