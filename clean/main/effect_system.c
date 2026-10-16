/* The effect system's process, its instances and its shared emitters (effect_system.h). */
#include "effect_system.h"

#include <string.h>

#include "autoload_2/heap.h"
#include "clean.h"
#include "main/globe.h"
#include "main/rom_file.h"
#include "main/scene_lights.h"
#include "main/season.h"
#include "main/town_record.h"

static_assert(sizeof(EffectSystemInstance) == 0x18, "EffectSystemInstance");
static_assert(offsetof(EffectSystemInstance, held) == 0x08 && offsetof(EffectSystemInstance, emitter) == 0x0c,
              "EffectSystemInstance");
static_assert(offsetof(EffectSystemInstance, setup) == 0x10, "EffectSystemInstance.setup");
static_assert(offsetof(EffectSystemInstances, list) == 0x04 && sizeof(EffectSystemInstances) == 0x304,
              "EffectSystemInstances");
static_assert(sizeof(EffectSystemSet) == 12, "EffectSystemSet");
static_assert(offsetof(EffectSystem, particles) == 0x50 && offsetof(EffectSystem, kept_started) == 0x54, "EffectSystem");
static_assert(offsetof(EffectSystem, instances) == 0x58 && offsetof(EffectSystem, models) == 0x35c, "EffectSystem");
static_assert(offsetof(EffectSystem, shared) == 0x181c && sizeof(EffectSystem) == 0x186c, "EffectSystem");
static_assert(offsetof(ParticleEmitter, particles) == 0x08 && offsetof(ParticleEmitter, user_data) == 0x80, "ParticleEmitter");
static_assert(offsetof(ParticleHeader, draw_flags) == 0x50, "ParticleHeader.draw_flags");

/* The system while it lives; the frame heap of its particles and the block of the current heap
 * it lies in; the place being started while a set's emitters are made (NULL otherwise). */
extern EffectSystem *data_021d52c4;
extern void *data_021d52cc;
extern void *data_021d52d0;
extern const Vec3 *data_021d52d4;
/* The sets (effect_kinds.h). */
extern const EffectSystemSet data_020d0f88[];
/* The particle file, "/spl/spl.spa". */
extern const char data_020e276c[];
/* The tints by the period of the day (TownRecord_Period): one for the emitters that take the
 * period's tint, and four, chosen by the emitter's user byte, for those that take their own. */
extern const s16 data_020e26bc[];
extern const s16 *const data_020e2488[];
/* The camera's matrix the particles are drawn with. */
extern const Mtx43 data_0213fee4;
/* The process's vtable and the base process's. */
extern const u32 data_020e2724[];
extern const u32 data_020da13c[];

extern void MI_CpuFill8(void *dst, u8 value, u32 size);
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
extern void MIi_CpuClear32(u32 value, void *dst, u32 size);
extern void *NNS_FndCreateFrmHeapEx(void *start, u32 size, u16 options);
extern void NNS_FndDestroyFrmHeap(void *heap);
extern void *NNS_FndAllocFromFrmHeapEx(void *heap, u32 size, int align);
extern void __cxa_vec_ctor(void *array, int count, int size, void (*construct)(void *), void (*destruct)(void *));
extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));

/* The functions handed to the game: the models' group constructor and destructor, the
 * particles' allocator and their draw callback. */
extern void *func_020911b0(void *group);
extern void *func_0209028c(void *group);
extern void *func_02091140(unsigned int size);
extern unsigned short func_02090f88(Vec3 *out, Vec3 position);

#define EFFECT_SYSTEM_SIZE 0x186c
#define EFFECT_SYSTEM_HEAP_SIZE 0xc000
#define EFFECT_SYSTEM_MAX_EMITTERS 0x20
#define EFFECT_SYSTEM_MAX_PARTICLES 0x64
#define EFFECT_SYSTEM_FIXED_ID 0x14
#define EFFECT_SYSTEM_MIN_ID 0x15
#define EFFECT_SYSTEM_MAX_ID 0x32
#define EFFECT_SYSTEM_POLYGON_ATTR 0x8800
#define EFFECT_SYSTEM_RESOURCES_SIZE 0x18 /* in the particle file: the resources' size */
#define EFFECT_SYSTEM_RESOURCES 0x20      /* and where they start */

/* ParticleHeader.draw_flags: how an emitter is tinted (EffectSystem_TintEmitter). */
#define EFFECT_SYSTEM_TINTED 0x80          /* by the scene's ambient colour, times one of: */
#define EFFECT_SYSTEM_TINT_SEASON 0x40     /* the season's colour */
#define EFFECT_SYSTEM_TINT_OWN_PERIOD 0x20 /* the period's colour of the emitter's table */
#define EFFECT_SYSTEM_TINT_PERIOD 0x08     /* the period's colour */
#define EFFECT_SYSTEM_WHITE 0x7fff

/* The process's destructor, without freeing it. */
static void effect_system_destruct(EffectSystem *system)
{
    system->process.vtable = data_020e2724;
    __cxa_vec_cleanup(system->models, EFFECT_MODELS_GROUPS, sizeof(EffectModelGroup),
                      (void (*)(void *))(uintptr_t) func_0209028c);
    system->process.vtable = data_020da13c;
    Process_Destruct(&system->process);
}

/* func_0209020c: the process's destructor. */
void *EffectSystem_Destruct(EffectSystem *system)
{
    effect_system_destruct(system);
    return system;
}
CLEAN_AS(func_0209020c, EffectSystem_Destruct)

/* func_02090248: the process's destructor, then its memory freed. */
void *EffectSystem_Delete(EffectSystem *system)
{
    effect_system_destruct(system);
    Heap_FreeAux(system);
    return system;
}
CLEAN_AS(func_02090248, EffectSystem_Delete)

/* func_020902d0: the emitter kept for `resource` in the first free entry; 1 when kept, 0 when
 * the table is full. */
int EffectSystem_AddShared(EffectSystemShared *shared, int resource, ParticleEmitter *emitter)
{
    int i;
    for (i = 0; i < EFFECT_SYSTEM_SHARED; i++) {
        if (shared[i].resource == EFFECT_SYSTEM_FREE) {
            shared[i].resource = resource;
            shared[i].emitter = emitter;
            return 1;
        }
    }
    return 0;
}
CLEAN_AS(func_020902d0, EffectSystem_AddShared)

/* func_020902f8: the emitter kept for `resource`, 0 for none. */
int EffectSystem_FindShared(EffectSystemShared *shared, int resource)
{
    int i;
    for (i = 0; i < EFFECT_SYSTEM_SHARED; i++) {
        if (resource == shared[i].resource) {
            return (int) (uintptr_t) shared[i].emitter;
        }
    }
    return 0;
}
CLEAN_AS(func_020902f8, EffectSystem_FindShared)

/* func_0209031c: the table's destructor, an empty one for each entry. */
void EffectSystem_DestructShared(EffectSystemShared *shared)
{
    int i;
    for (i = 0; i < EFFECT_SYSTEM_SHARED; i++) {
        EffectSystem_DestructSharedEntry(&shared[i]);
    }
}
CLEAN_AS(func_0209031c, EffectSystem_DestructShared)

/* func_0209033c: every entry of the table emptied. */
void EffectSystem_InitShared(EffectSystemShared *shared)
{
    int i;
    for (i = 0; i < EFFECT_SYSTEM_SHARED; i++) {
        EffectSystem_InitSharedEntry(&shared[i]);
    }
}
CLEAN_AS(func_0209033c, EffectSystem_InitShared)

/* func_0209035c: an entry's destructor: nothing to do. */
void EffectSystem_DestructSharedEntry(EffectSystemShared *entry)
{
    (void) entry;
}
CLEAN_AS(func_0209035c, EffectSystem_DestructSharedEntry)

/* func_02090360 */
void EffectSystem_InitSharedEntry(EffectSystemShared *entry)
{
    entry->resource = EFFECT_SYSTEM_FREE;
    entry->emitter = NULL;
}
CLEAN_AS(func_02090360, EffectSystem_InitSharedEntry)

/* func_020908a0: an instance started in the first free entry from the table's search start
 * (the start moved past each busy entry, and past the new one); the instance, or 0 when none
 * started. QUIRK: only the first free entry found is tried: when its emitter cannot be made,
 * no other is. BUG: the tag's fourth byte, which the instance keeps at 0x07, is never set: it
 * holds what the stack held (nothing reads it). BUGFIX: 0. */
int EffectSystem_NewInstance(EffectSystemInstances *table, int resource, const Vec3 *position, const s16 *angle,
                             const EffectSystemKeptSetup *setup, int serial, int number)
{
    u8 bytes[sizeof(EffectSystemInstanceTag)]; /* the tag's, the fourth never set */
    EffectSystemInstanceTag tag;
    EffectSystemInstance *started = NULL;
    int i;

    bytes[1] = (u8) serial;
    bytes[2] = (u8) number;
#ifdef BUGFIX
    bytes[3] = 0;
#endif
    for (i = 0; i < EFFECT_SYSTEM_INSTANCES; i++) {
        int index = table->next;
        if (table->list[index].resource != EFFECT_SYSTEM_FREE) {
            table->next = (u8) ((index + 1) % EFFECT_SYSTEM_INSTANCES);
            continue;
        }
        bytes[0] = (u8) index;
        memcpy(&tag, bytes, sizeof(tag));
        if (EffectSystem_StartInstance(&table->list[index], resource, position, angle, setup, tag) != 0) {
            started = &table->list[table->next];
            table->next = (u8) ((table->next + 1) % EFFECT_SYSTEM_INSTANCES);
        }
        break;
    }
    return (int) (uintptr_t) started;
}
CLEAN_AS(func_020908a0, EffectSystem_NewInstance)

/* func_02090930: the first instance of `resource` that is not held, NULL for none. */
EffectSystemInstance *EffectSystem_FindInstance(EffectSystemInstances *table, int resource)
{
    int i;
    for (i = 0; i < EFFECT_SYSTEM_INSTANCES; i++) {
        EffectSystemInstance *instance = &table->list[i];
        if (resource == instance->resource && instance->held != 1) {
            return instance;
        }
    }
    return NULL;
}
CLEAN_AS(func_02090930, EffectSystem_FindInstance)

/* func_02090968: every instance ended; the search start left at the last one. */
void EffectSystem_EndInstances(EffectSystemInstances *table)
{
    int i;
    for (i = 0; i < EFFECT_SYSTEM_INSTANCES; i++) {
        EffectSystemInstance *instance = &table->list[i];
        if (instance->resource != EFFECT_SYSTEM_FREE) {
            instance->held = 0;
            EffectSystem_EndInstance(instance);
            table->next = (u8) i;
        }
    }
}
CLEAN_AS(func_02090968, EffectSystem_EndInstances)

/* func_0209099c: each instance followed a frame: held while its follow function answers
 * nonzero, ended (and the search start moved to it) once it answers 0. QUIRK: the follow
 * function is called without a check for NULL (the ROM tests the address of the instance's
 * set-up words, never 0). */
void EffectSystem_FollowInstances(EffectSystemInstances *table)
{
    int i;
    for (i = 0; i < EFFECT_SYSTEM_INSTANCES; i++) {
        EffectSystemInstance *instance = &table->list[i];
        if (instance->resource == EFFECT_SYSTEM_FREE) {
            continue;
        }
        instance->held = 0;
        if (instance->setup.follow(instance) != 0) {
            instance->held = 1;
        }
        if (instance->held != 1) {
            EffectSystem_EndInstance(instance);
            table->next = (u8) i;
        }
    }
}
CLEAN_AS(func_0209099c, EffectSystem_FollowInstances)

/* func_020909f8: every entry free and the search at the first. QUIRK: the entries are freed
 * twice (the class's constructor, then its reset). */
void EffectSystem_InitInstances(EffectSystemInstances *table)
{
    int i;
    for (i = 0; i < EFFECT_SYSTEM_INSTANCES; i++) {
        table->list[i].resource = EFFECT_SYSTEM_FREE;
    }
    table->next = 0;
    for (i = 0; i < EFFECT_SYSTEM_INSTANCES; i++) {
        table->list[i].resource = EFFECT_SYSTEM_FREE;
    }
}
CLEAN_AS(func_020909f8, EffectSystem_InitInstances)

/* func_02090a2c: the instance's emitter told to end once its particles are gone, and the entry
 * freed. */
void EffectSystem_EndInstance(EffectSystemInstance *instance)
{
    ParticleEmitter *emitter = instance->emitter;
    if (emitter != NULL) {
        emitter->state |= EMITTER_ENDING;
    }
    instance->resource = EFFECT_SYSTEM_FREE;
}
CLEAN_AS(func_02090a2c, EffectSystem_EndInstance)

/* func_02090a44: an emitter of `resource` made at `position` for the instance, which is then
 * held with its set-up words and tag and placed by its place function; 1 when made, else 0.
 * `angle` is not used. */
int EffectSystem_StartInstance(EffectSystemInstance *instance, int resource, const Vec3 *position, const s16 *angle,
                               const EffectSystemKeptSetup *setup, EffectSystemInstanceTag tag)
{
    (void) angle;
    instance->emitter = ParticleSys_CreateEmitterAt(data_021d52c4->particles, resource, position);
    if (instance->emitter == NULL) {
        return 0;
    }
    instance->resource = resource;
    instance->held = 1;
    instance->setup.place = setup->place;
    instance->setup.follow = setup->follow;
    instance->tag = tag;
    setup->place(instance);
    return 1;
}
CLEAN_AS(func_02090a44, EffectSystem_StartInstance)

/* func_02090aa4: a copy of model `model` started and handed to `setup` (EffectModels_Start). */
void EffectSystem_StartModel(int model, void (*setup)(void *transform))
{
    EffectModels_Start(data_021d52c4->models, model, setup);
}
CLEAN_AS(func_02090aa4, EffectSystem_StartModel)

/* The emitters of a set, and how many: for a set of two halves given an angle, its first half,
 * or its second when the first angle is 0 or more. */
static const s32 *effect_system_set_resources(const EffectSystemSet *set, const s16 *angle, int *count)
{
    const s32 *resources = set->resources;
    *count = set->count;
    if (angle != NULL && (set->flags & EFFECT_SYSTEM_SET_HALVES) != 0) {
        *count >>= 1;
        if (angle[0] >= 0) {
            resources += *count;
        }
    }
    return resources;
}

/* func_02090ac4: the kept set `set` started at `position`: for each of its emitters, an instance
 * of the resource that is not held is taken again (held, with this start's serial and number,
 * and placed again), else a new one is started with the emitter's two set-up words. When one
 * cannot start, those started by this call are ended and the result is 0; else 1. The count of
 * kept sets started goes up by one either way, but not for a NULL position (result 0).
 * REQUIRES: the set has at most 10 emitters (the ROM's have at most 8). */
int EffectSystem_StartKeptSet(int set, const Vec3 *position, const s16 *angle, void *const *setups)
{
    const EffectSystemKeptSetup *setup = (const EffectSystemKeptSetup *) (const void *) setups;
    EffectSystemInstance *started[EFFECT_SYSTEM_SET_MAX];
    EffectSystemInstances *table;
    const s32 *resources;
    int count;
    int ok = 1;
    int i;
    int j;

    MIi_CpuClear32(0, started, sizeof(started));
    if (position == NULL) {
        return 0;
    }
    table = &data_021d52c4->instances;
    resources = effect_system_set_resources(&data_020d0f88[set], angle, &count);
    data_021d52d4 = position;
    for (i = 0; i < count; i++) {
        EffectSystemInstance *instance = EffectSystem_FindInstance(table, *resources);
        if (instance != NULL) {
            instance->held = 1;
            instance->number_again = (u8) i;
            instance->tag.serial = (u8) data_021d52c4->kept_started;
            instance->tag.number = (u8) i;
            instance->setup.place(instance);
        } else {
            instance = (EffectSystemInstance *) (uintptr_t) EffectSystem_NewInstance(table, *resources, position, angle, setup,
                                                                                     (int) data_021d52c4->kept_started, i);
            if (instance == NULL) {
                ok = 0;
                for (j = 0; j < i; j++) {
                    EffectSystem_EndInstance(started[j]);
                }
                break;
            }
        }
        started[i] = instance;
        resources++;
        setup++;
    }
    data_021d52d4 = NULL;
    data_021d52c4->kept_started++;
    return ok;
}
CLEAN_AS(func_02090ac4, EffectSystem_StartKeptSet)

/* An emitter of a one-shot set made to emit at the place; its newest particle turned by the
 * first angle when there is one. REQUIRES: the emitter has a particle once it has emitted (the
 * ROM writes through the list's first link unchecked). */
static void effect_system_emit_shared(ParticleEmitter *emitter, const Vec3 *position, const s16 *angle)
{
    ParticleSys_EmitAt(data_021d52c4->particles, emitter, position);
    if (angle != NULL) {
        ((Particle *) (void *) emitter->particles.first)->rotation = (u16) angle[0];
    }
}

/* func_02090c2c: the one-shot set `set` started at `position`, each emitter made with its set-up
 * function (one word each). A shared set makes each resource's emitter once, keeping it with
 * emission stopped, and makes it emit at the place each time it starts. 0 for a NULL position,
 * else 1. QUIRK: every emitter's particle is turned by the first angle. QUIRK: an emitter of a
 * shared set made when the table is full is neither kept nor made to emit here. */
int EffectSystem_StartSet(int set, const Vec3 *position, const s16 *angle, void *const *setups)
{
    EffectSystem *system;
    const EffectSystemSet *entry;
    const s32 *resources;
    int count;
    int i;

    if (position == NULL) {
        return 0;
    }
    system = data_021d52c4;
    entry = &data_020d0f88[set];
    resources = effect_system_set_resources(entry, angle, &count);
    data_021d52d4 = position;

    if ((entry->flags & EFFECT_SYSTEM_SET_SHARED) != 0) {
        EffectSystemShared *shared = system->shared;
        for (i = 0; i < count; i++) {
            ParticleEmitter *emitter = (ParticleEmitter *) (uintptr_t) EffectSystem_FindShared(shared, *resources);
            if (emitter == NULL) {
                emitter = ParticleSys_CreateEmitterWith(data_021d52c4->particles, *resources,
                                                        (void (*)(ParticleEmitter *))(uintptr_t) *setups);
                if (emitter != NULL && EffectSystem_AddShared(shared, *resources, emitter) != 0) {
                    emitter->state |= EMITTER_NO_EMISSION;
                    effect_system_emit_shared(emitter, position, angle);
                }
            } else {
                effect_system_emit_shared(emitter, position, angle);
            }
            resources++;
            setups++;
        }
    } else {
        for (i = 0; i < count; i++) {
            ParticleSys_CreateEmitterWith(data_021d52c4->particles, *resources,
                                          (void (*)(ParticleEmitter *))(uintptr_t) *setups);
            resources++;
            setups++;
        }
    }

    data_021d52d4 = NULL;
    return 1;
}
CLEAN_AS(func_02090c2c, EffectSystem_StartSet)

/* func_02090d50: a follow function: the emitter tinted again, and kept on. */
int EffectSystem_FollowTinted(EffectSystemInstance *instance)
{
    EffectSystem_TintEmitter(instance->emitter);
    return 1;
}
CLEAN_AS(func_02090d50, EffectSystem_FollowTinted)

/* func_02090d64: a place function (EffectSystem_PlaceEmitter). */
void EffectSystem_PlaceInstance(EffectSystemInstance *instance)
{
    EffectSystem_PlaceEmitter(instance->emitter);
}
CLEAN_AS(func_02090d64, EffectSystem_PlaceInstance)

/* func_02090d70: a set-up function: the emitter tinted and, while a place is being started,
 * put at that place plus its resource's base position. */
void EffectSystem_PlaceEmitter(ParticleEmitter *emitter)
{
    const Vec3 *place;
    const Vec3 *base;

    EffectSystem_TintEmitter(emitter);
    place = data_021d52d4;
    if (place != NULL) {
        base = &emitter->resource->header->base_pos;
        emitter->position.x = place->x + base->x;
        emitter->position.y = place->y + base->y;
        emitter->position.z = place->z + base->z;
    }
}
CLEAN_AS(func_02090d70, EffectSystem_PlaceEmitter)

/* func_02090db0: an emitter whose resource asks for it tinted: the scene's ambient colour,
 * each of red, green and blue times the tint's (of 31); the ambient colour's top bit kept. */
void EffectSystem_TintEmitter(ParticleEmitter *emitter)
{
    u8 flags = emitter->resource->header->draw_flags;
    u16 ambient;
    u16 tint;
    unsigned int red;
    unsigned int green;
    unsigned int blue;

    if ((flags & EFFECT_SYSTEM_TINTED) == 0) {
        return;
    }
    ambient = (u16) SceneLights_AmbientColour();
    if ((flags & EFFECT_SYSTEM_TINT_SEASON) != 0) {
        tint = Season_Color();
    } else if ((flags & EFFECT_SYSTEM_TINT_OWN_PERIOD) != 0) {
        tint = (u16) EffectSystem_PeriodColorOf(emitter);
    } else if ((flags & EFFECT_SYSTEM_TINT_PERIOD) != 0) {
        tint = (u16) EffectSystem_PeriodColor();
    } else {
        tint = EFFECT_SYSTEM_WHITE;
    }
    red = (tint & 0x1fu) * (ambient & 0x1fu) / 31;
    green = ((tint >> 5) & 0x1fu) * ((ambient >> 5) & 0x1fu) / 31;
    blue = ((tint >> 10) & 0x1fu) * ((ambient >> 10) & 0x1fu) / 31;
    emitter->color = (u16) ((ambient & 0x8000u) | red | (green << 5) | (blue << 10));
}
CLEAN_AS(func_02090db0, EffectSystem_TintEmitter)

/* func_02090ebc: the tint of the period of the day. */
int EffectSystem_PeriodColor(void)
{
    return data_020e26bc[TownRecord_Period()];
}
CLEAN_AS(func_02090ebc, EffectSystem_PeriodColor)

/* func_02090ed4: the tint of the period of the day from the emitter's own table (its user
 * byte, 0-3). */
short EffectSystem_PeriodColorOf(ParticleEmitter *emitter)
{
    int period = TownRecord_Period();
    return data_020e2488[(u8) emitter->user_data][period];
}
CLEAN_AS(func_02090ed4, EffectSystem_PeriodColorOf)

/* The particles' frame heap destroyed and its block freed (the instances ended first). */
static void effect_system_free_heap(EffectSystem *system)
{
    if (data_021d52cc != NULL) {
        NNS_FndDestroyFrmHeap(data_021d52cc);
        data_021d52cc = NULL;
    }
    if (data_021d52d0 != NULL) {
        EffectSystem_EndInstances(&system->instances);
        Heap_FreeCurrent(data_021d52d0);
        data_021d52d0 = NULL;
    }
}

/* func_02090ef4: the process removed: the particles' heap and the models released, the system
 * gone. QUIRK: the instances end (their emitters marked) after the frame heap holding the
 * emitters is destroyed, while its block is still allocated. */
int EffectSystem_Remove(EffectSystem *system)
{
    effect_system_free_heap(system);
    EffectModels_ReleaseAll(system->models);
    EffectSystem_DestructShared(system->shared);
    data_021d52c4 = NULL;
    return 1;
}
CLEAN_AS(func_02090ef4, EffectSystem_Remove)

/* func_02090f5c: the process drawn: the particles with the camera's matrix, bent over the
 * globe, then the models. */
int EffectSystem_Draw(EffectSystem *system)
{
    ParticleSys_Draw(system->particles, &data_0213fee4, (ParticleDrawCallback) (uintptr_t) func_02090f88);
    EffectModels_DrawAll(system->models);
    return 1;
}
CLEAN_AS(func_02090f5c, EffectSystem_Draw)

/* func_02090f88: the particles' draw callback: a particle's place bent over the globe into
 * `out`, and the angle it tilts by (Globe_BendFar), as a halfword. */
unsigned short EffectSystem_BendParticle(Vec3 *out, Vec3 position)
{
    return (unsigned short) Globe_BendFar(out, &position);
}
CLEAN_AS(func_02090f88, EffectSystem_BendParticle)

/* func_02090fac: the process's frame: the instances followed, the models stepped, the
 * particles updated. */
int EffectSystem_Execute(EffectSystem *system)
{
    EffectSystem_FollowInstances(&system->instances);
    EffectModels_StepAll(system->models);
    ParticleSys_Update(system->particles);
    return 1;
}
CLEAN_AS(func_02090fac, EffectSystem_Execute)

/* func_02090fd0: the process created (effect_system.h); 1 when the particles are ready, then
 * the models are loaded and the shared emitters' table emptied; 0 when not, the heap given
 * back. BUG: the particle manager's polygon attributes are written before it is checked for
 * NULL. QUIRK: the model groups, already constructed, are cleared to 0 (their vtables too)
 * before they load. */
int EffectSystem_Create(EffectSystem *system)
{
    int ok = 0;

    data_021d52c4 = system;
    system->particles = NULL;
    data_021d52cc = NULL;
    system->kept_started = 0;
    data_021d52d4 = NULL;
    data_021d52d0 = Heap_AllocCurrent(EFFECT_SYSTEM_HEAP_SIZE);
    if (data_021d52d0 != NULL) {
        data_021d52cc = NNS_FndCreateFrmHeapEx(data_021d52d0, EFFECT_SYSTEM_HEAP_SIZE, 0);
        system->particles = ParticleSys_Create((void *(*) (u32))(uintptr_t) func_02091140, EFFECT_SYSTEM_MAX_EMITTERS,
                                               EFFECT_SYSTEM_MAX_PARTICLES, EFFECT_SYSTEM_FIXED_ID, EFFECT_SYSTEM_MIN_ID,
                                               EFFECT_SYSTEM_MAX_ID);
#ifdef BUGFIX
        if (system->particles != NULL) {
            system->particles->polygon_attr = EFFECT_SYSTEM_POLYGON_ATTR;
        }
#else
        system->particles->polygon_attr = EFFECT_SYSTEM_POLYGON_ATTR;
#endif
        if (system->particles != NULL) {
            u8 *file = EffectSystem_LoadFile(system);
            if (file != NULL) {
                ParticleSys_LoadTextures(system->particles, (const ParticleFile *) (const void *) file);
                if (EffectSystem_UploadTextures(system) != 0) {
                    const u8 *resources = (const u8 *) (uintptr_t) EffectSystem_CopyResources(system, file);
                    if (resources != NULL) {
                        ParticleSys_LoadResources(system->particles, resources);
                        ok = 1;
                    }
                }
                Heap_FreeCurrent(file);
            }
        }
    }
    if (ok == 0) {
        effect_system_free_heap(system);
    } else {
        MI_CpuFill8(system->models, 0, sizeof(system->models));
        EffectModels_LoadAll(system->models);
        EffectSystem_InitShared(system->shared);
    }
    return ok;
}
CLEAN_AS(func_02090fd0, EffectSystem_Create)

/* func_020910e4: the particle file's resources copied into the frame heap; the copy, or 0 when
 * it does not fit. */
int EffectSystem_CopyResources(EffectSystem *system, const u8 *file)
{
    u32 size;
    void *copy;

    (void) system;
    size = *(const u32 *) (const void *) (file + EFFECT_SYSTEM_RESOURCES_SIZE);
    copy = EffectSystem_Alloc(size);
    if (copy != NULL) {
        MI_CpuCopy8(file + EFFECT_SYSTEM_RESOURCES, copy, size);
    }
    return (int) (uintptr_t) copy;
}
CLEAN_AS(func_020910e4, EffectSystem_CopyResources)

/* func_0209110c: the particles' textures, then their palettes, put in VRAM; 1 when both were. */
int EffectSystem_UploadTextures(EffectSystem *system)
{
    if (ParticleSys_UploadTextures(system->particles) != 0 && ParticleSys_UploadPalettes(system->particles) != 0) {
        return 1;
    }
    return 0;
}
CLEAN_AS(func_0209110c, EffectSystem_UploadTextures)

/* func_02091130: the particle file loaded into the current heap. */
void *EffectSystem_LoadFile(EffectSystem *system)
{
    (void) system;
    return RomFile_LoadDefault(data_020e276c);
}
CLEAN_AS(func_02091130, EffectSystem_LoadFile)

/* func_02091140: the particles' allocator: from their frame heap, 4-aligned. */
void *EffectSystem_Alloc(unsigned int size)
{
    return NNS_FndAllocFromFrmHeapEx(data_021d52cc, size, 4);
}
CLEAN_AS(func_02091140, EffectSystem_Alloc)

/* func_02091154: the process allocated (zeroed) and constructed. */
void *EffectSystem_New(void)
{
    EffectSystem *system = Heap_AllocAuxZeroed(EFFECT_SYSTEM_SIZE);
    if (system != NULL) {
        Process_Construct(&system->process);
        system->process.vtable = data_020da13c;
        system->process.vtable = data_020e2724;
        EffectSystem_InitInstances(&system->instances);
        __cxa_vec_ctor(system->models, EFFECT_MODELS_GROUPS, sizeof(EffectModelGroup),
                       (void (*)(void *))(uintptr_t) func_020911b0, (void (*)(void *))(uintptr_t) func_0209028c);
    }
    return system;
}
CLEAN_AS(func_02091154, EffectSystem_New)
