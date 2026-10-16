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

/* --- The places effects start at and follow, and the kinds' start functions ---
 *
 * An effect is started by kind (EffectSystem_StartKind): the kind's start function, from the
 * table at data_020e2c1c (EffectSystemKind), fills the place being started and starts its
 * sets (effect_kinds.h). When it started a kept set, the places it keeps are named by a handle:
 * the caller gets the handle, can move those places (EffectSystem_MoveHandle) and end them
 * through the kind's end function (EffectSystem_EndHandle). Kinds 0x4c-0x65 start here; kind
 * 0x64 starts a one-shot set and kind 0x65 a kept set given by number. */

#include "main/effect_kinds.h"

#define EFFECT_SYSTEM_KINDS 0x66 /* the kinds; also the kind of a free place */
#define EFFECT_SYSTEM_PLACES 32

/* The places (data_021d52d8, 0x39e bytes). */
typedef struct EffectSystemPlaces {
    EffectKindsPlace places[EFFECT_SYSTEM_PLACES]; /* 0x000: those kept for kept sets */
    EffectKindsPlace starting;                     /* 0x380: the one being started (data_021d5658) */
    u16 next_handle;                               /* 0x39c */
} EffectSystemPlaces;

/* An entry of the kind table. A start function answers 0 when a kept set started (the caller
 * gets the next handle), 2 when one started that the caller keeps no handle of, 1 for a
 * one-shot set and 3 when nothing started. */
typedef struct EffectSystemKind {
    int (*start)(int kind, const Vec3 *position, const s16 *angle, const s16 *extra, int set);
    void (*end)(int handle); /* NULL for none */
} EffectSystemKind;

/* Starting and following places */
int EffectSystem_StartKeptSetNumber(int set, const Vec3 *position, const s16 *angle, const s16 *extra);
int EffectSystem_StartOneShotSetNumber(int set, const Vec3 *position, const s16 *angle, const s16 *extra);
int EffectSystem_StartOneShotSetNumberCopy(int set, const Vec3 *position, const s16 *angle, const s16 *extra);
void EffectSystem_MoveHandle(int handle, const Vec3 *position, const s16 *angle, const s16 *extra);
void EffectSystem_EndHandle(int handle);
int EffectSystem_StartKindWithExtra(int kind, short extra, const Vec3 *position, const s16 *angle);
int EffectSystem_StartKind(int kind, const Vec3 *position, const s16 *angle, const s16 *extra);
void EffectSystem_ResetPlaces(void);
unsigned short EffectSystem_KindOfHandle(EffectSystemPlaces *places, int handle);
void EffectSystem_EndHandleIn(EffectSystemPlaces *places, int handle);
int EffectSystem_StartKindIn(EffectSystemPlaces *places, unsigned int kind, const Vec3 *position, const s16 *angle,
                             const s16 *extra, int set);
void EffectSystem_ResetPlacesIn(EffectSystemPlaces *places);
void EffectSystem_SetHandleFrames(EffectKindsPlace *places, int handle, short frames);
void EffectSystem_MovePlaces(EffectKindsPlace *places, int handle, const Vec3 *position, const s16 *angle, const s16 *extra);
int EffectSystem_FindHandle(EffectKindsPlace *unused, int handle, EffectKindsPlace *places, int count);
void EffectSystem_ClearPlaces(EffectSystemPlaces *places);
void EffectSystem_FillPlace(EffectKindsPlace *place, int handle, short kind, const Vec3 *position, const s16 *angle,
                            const s16 *extra, short frames);
void EffectSystem_ClearPlace(EffectKindsPlace *place);

/* Kinds 0x4c-0x65 */
void EffectSystem_StartKind65(int kind, const Vec3 *position, const s16 *angle, const s16 *extra, int set);
int EffectSystem_StartKind64(int kind, const Vec3 *position, const s16 *angle, const s16 *extra, int set);
int EffectSystem_StartKind63(void);
int EffectSystem_StartKind62(int kind, const Vec3 *position, const s16 *angle, const s16 *extra);
int EffectSystem_StartKind61(int kind, const Vec3 *position, const s16 *angle, const s16 *extra);
void EffectSystem_StartKind60(int kind, const Vec3 *position, const s16 *angle, const s16 *extra);
void EffectSystem_SetUpKind60(ParticleEmitter *emitter);
void EffectSystem_StartKind5f(int kind, const Vec3 *position, const s16 *angle, const s16 *extra);
void EffectSystem_SetUpKind5f(ParticleEmitter *emitter);
void EffectSystem_StartKind5e(int kind, const Vec3 *position, const s16 *angle, const s16 *extra);
int EffectSystem_StartKind5d(int kind, const Vec3 *position, const s16 *angle, const s16 *extra);
void EffectSystem_StartKind5c(int kind, const Vec3 *position, const s16 *angle, const s16 *extra);
void EffectSystem_StartKind5b(int kind, const Vec3 *position, const s16 *angle, const s16 *extra);
void EffectSystem_StartKind5a(int kind, const Vec3 *position, const s16 *angle, const s16 *extra);
void EffectSystem_SetUpKind5a(ParticleEmitter *emitter);
int EffectSystem_StartKind59(int kind, const Vec3 *position, const s16 *angle, const s16 *extra);
int EffectSystem_FollowKind59(EffectKindsInstance *instance);
void EffectSystem_StartKind58(int kind, const Vec3 *position, const s16 *angle, const s16 *extra);
void EffectSystem_StartKind57(int kind, const Vec3 *position, const s16 *angle, const s16 *extra);
void EffectSystem_EndKind56(int handle);
void EffectSystem_StartKind56(int kind, const Vec3 *position, const s16 *angle, const s16 *extra);
int EffectSystem_FollowKind56(EffectKindsInstance *instance);
int EffectSystem_FollowKind56First(EffectKindsInstance *instance);
int EffectSystem_StartKind55(int kind, const Vec3 *position, const s16 *angle, const s16 *extra);
void EffectSystem_StartKind54(int kind, const Vec3 *position, const s16 *angle, const s16 *extra);
void EffectSystem_FollowKind54Second(EffectKindsInstance *instance);
void EffectSystem_FollowKind54First(EffectKindsInstance *instance);
void EffectSystem_PlaceKind54Second(EffectKindsInstance *instance);
void EffectSystem_PlaceKind54First(EffectKindsInstance *instance);
void EffectSystem_StartKind53(int kind, const Vec3 *position, const s16 *angle, const s16 *extra);
void EffectSystem_StartKind52(int kind, const Vec3 *position, const s16 *angle, const s16 *extra);
void EffectSystem_SetUpKind52(ParticleEmitter *emitter);
void EffectSystem_StartKind51(int kind, const Vec3 *position, const s16 *angle, const s16 *extra);
int EffectSystem_StartKind50(int kind, const Vec3 *position, const s16 *angle, const s16 *extra);
int EffectSystem_StartKind4f(int kind, const Vec3 *position, const s16 *angle, const s16 *extra);
void EffectSystem_StartKind4e(int kind, const Vec3 *position, const s16 *angle, const s16 *extra);
void EffectSystem_FollowKind4eSecond(EffectKindsInstance *instance);
void EffectSystem_FollowKind4eFirst(EffectKindsInstance *instance);
void EffectSystem_PlaceKind4eSecond(EffectKindsInstance *instance);
void EffectSystem_PlaceKind4eFirst(EffectKindsInstance *instance);
void EffectSystem_StartKind4d(int kind, const Vec3 *position, const s16 *angle, const s16 *extra);
void EffectSystem_StartKind4c(int kind, const Vec3 *position, const s16 *angle, const s16 *extra);

#endif
