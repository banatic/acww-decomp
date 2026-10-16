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

/* --- The places effects start at and follow, and the kinds' start functions --- */

#include "main/effect_places.h"

static_assert(sizeof(EffectKindsPlace) == 0x1c && offsetof(EffectKindsPlace, handle) == 0x14, "EffectKindsPlace");
static_assert(offsetof(EffectKindsPlace, unk_10) == 0x10 && offsetof(EffectKindsPlace, kind) == 0x18, "EffectKindsPlace");
static_assert(offsetof(EffectSystemPlaces, starting) == 0x380 && offsetof(EffectSystemPlaces, next_handle) == 0x39c,
              "EffectSystemPlaces");
static_assert(offsetof(EffectKindsInstance, slot) == 0x04 && offsetof(EffectKindsInstance, emitter) == 0x0c,
              "EffectKindsInstance");
static_assert(offsetof(Particle, rotation) == 0x20 && offsetof(Particle, life) == 0x24 && offsetof(Particle, age) == 0x26,
              "Particle");

/* The places, and the kinds. */
extern EffectSystemPlaces data_021d52d8;
extern const EffectSystemKind data_020e2c1c[EFFECT_SYSTEM_KINDS];

/* The kinds' set-up words (effect_kinds.h): one per emitter of a one-shot set, two (place,
 * follow) per emitter of a kept one. data_020e2ac4 is a kept set's default. */
extern void *data_020e2798[];
extern void *data_020e27c0[];
extern void *data_020e27d0[];
extern void *data_020e286c[];
extern void *data_020e2934[];
extern void *data_020e2944[];
extern void *data_020e2984[];
extern void *data_020e29c4[];
extern void *data_020e2a1c[];
extern void *data_020e2ac4[];

/* Offsets and axes the kinds' emitters are put at (turned by their place's angle). */
extern const Vec3 data_020d16d8; /* (0, -0.5, 1) */
extern const Vec3 data_020d16f0; /* (0, 0, 0.82) */
extern const Vec3 data_020d1744; /* (-1, 1, 0) */
extern const Vec3 data_020d1750; /* (0, 0, 1) */
extern const Vec3 data_020d175c; /* (0, -0.5, 1) */
extern const Vec3 data_020d178c; /* (1, 1, 0) */
extern const Vec3 data_020d17bc; /* (0, 0.8, 0.8) */
extern const Vec3 data_020d1810; /* (0, 0, 0.2) */
extern const Vec3 data_020d1828; /* (-0.4, 0, 0.5) */
extern const Vec3 data_020d1834; /* (-0.4, 0.47, 0) */
extern const Vec3 data_020d1840; /* (0.4, 0, 0.5) */
extern const Vec3 data_020d184c; /* (0.4, 0.47, 0) */
/* Kind 0x4e's offsets, nine each, chosen by its place's half-word 0x10. */
extern const Vec3 data_020e2b44[];
extern const Vec3 data_020e2bb0[];

#define EFFECT_SYSTEM_NO_HANDLE (-1)
#define EFFECT_SYSTEM_FOR_EVER (-1)
#define EFFECT_SYSTEM_KEPT_STARTED 0 /* a start function's answers */
#define EFFECT_SYSTEM_KEPT_UNHANDED 2
#define EFFECT_SYSTEM_NOT_STARTED 3
#define EFFECT_SYSTEM_UNK_10_DEFAULT 0x1000
#define EFFECT_SYSTEM_KIND_KEPT_SET 0x65
#define EFFECT_SYSTEM_KIND_ONE_SHOT_SET 0x64
#define EFFECT_SYSTEM_RAISED 3          /* a place's half-word 0x10 for kind 0x54's raised offsets */
#define EFFECT_SYSTEM_SPIN 12500        /* kind 0x59's particles' angle, by the side it turns to */
#define EFFECT_SYSTEM_FADE_STEP 6       /* kind 0x56's base alpha per frame left */
#define EFFECT_SYSTEM_KIND_56_FRAMES 4  /* the frames kind 0x56's places last once ended */
#define EFFECT_SYSTEM_KIND_55_FRAMES 15 /* the frames kind 0x55 follows its places */
#define EFFECT_SYSTEM_KIND_59_FRAMES 0x25

/* The particle file's sets the kinds start. */
#define EFFECT_SYSTEM_SET_KIND_62 0x7d
#define EFFECT_SYSTEM_SET_KIND_61 0x7c
#define EFFECT_SYSTEM_SET_KIND_60 0x7b
#define EFFECT_SYSTEM_SET_KIND_5F 0x51
#define EFFECT_SYSTEM_SET_KIND_5C 0x15
#define EFFECT_SYSTEM_SET_KIND_5B 0x82
#define EFFECT_SYSTEM_SET_KIND_5A 0x14
#define EFFECT_SYSTEM_SET_KIND_59 0x13
#define EFFECT_SYSTEM_SET_KIND_59_KEPT 0x62
#define EFFECT_SYSTEM_SET_KIND_58 0x12
#define EFFECT_SYSTEM_SET_KIND_57 0x11
#define EFFECT_SYSTEM_SET_KIND_56 0x10
#define EFFECT_SYSTEM_SET_KIND_55 0x0f
#define EFFECT_SYSTEM_SET_KIND_54 0x0e
#define EFFECT_SYSTEM_SET_KIND_53 0x0d
#define EFFECT_SYSTEM_SET_KIND_52 0x5d
#define EFFECT_SYSTEM_SET_KIND_51 0x0c
#define EFFECT_SYSTEM_SET_KIND_50 0x0b
#define EFFECT_SYSTEM_SET_KIND_4F 0x0a
#define EFFECT_SYSTEM_SET_KIND_4E 0x09
#define EFFECT_SYSTEM_SET_KIND_4D 0x16
#define EFFECT_SYSTEM_SET_KIND_4C 0x08
/* The models kinds 0x5d and 0x5e start. */
#define EFFECT_SYSTEM_MODEL_KIND_5D 0
#define EFFECT_SYSTEM_MODEL_KIND_5E 1

/* The emitter's point: `at` and its resource's base position. */
static void effect_system_put_emitter(ParticleEmitter *emitter, const Vec3 *at)
{
    const Vec3 *base = &emitter->resource->header->base_pos;

    emitter->position.x = particle_add(at->x, base->x);
    emitter->position.y = particle_add(at->y, base->y);
    emitter->position.z = particle_add(at->z, base->z);
}

/* func_0209120c: the kept set `set` started at a place filled from the arguments (kind 0x65);
 * its handle, or -1 when it did not start. */
int EffectSystem_StartKeptSetNumber(int set, const Vec3 *position, const s16 *angle, const s16 *extra)
{
    return EffectSystem_StartKindIn(&data_021d52d8, EFFECT_SYSTEM_KIND_KEPT_SET, position, angle, extra, set);
}
CLEAN_AS(func_0209120c, EffectSystem_StartKeptSetNumber)

/* func_02091230: the one-shot set `set` started at a place filled from the arguments (kind
 * 0x64); -1 (a one-shot set has no handle). */
int EffectSystem_StartOneShotSetNumber(int set, const Vec3 *position, const s16 *angle, const s16 *extra)
{
    return EffectSystem_StartKindIn(&data_021d52d8, EFFECT_SYSTEM_KIND_ONE_SHOT_SET, position, angle, extra, set);
}
CLEAN_AS(func_02091230, EffectSystem_StartOneShotSetNumber)

/* func_02091254: the same as EffectSystem_StartOneShotSetNumber, a second copy in the ROM. */
int EffectSystem_StartOneShotSetNumberCopy(int set, const Vec3 *position, const s16 *angle, const s16 *extra)
{
    return EffectSystem_StartKindIn(&data_021d52d8, EFFECT_SYSTEM_KIND_ONE_SHOT_SET, position, angle, extra, set);
}
CLEAN_AS(func_02091254, EffectSystem_StartOneShotSetNumberCopy)

/* func_02091278: the places of handle `handle` moved to `position`, and given `angle` and the
 * half-word `extra` when they are not NULL. */
void EffectSystem_MoveHandle(int handle, const Vec3 *position, const s16 *angle, const s16 *extra)
{
    EffectSystem_MovePlaces(data_021d52d8.places, handle, position, angle, extra);
}
CLEAN_AS(func_02091278, EffectSystem_MoveHandle)

/* func_0209129c: the effect of handle `handle` ended by its kind's end function. */
void EffectSystem_EndHandle(int handle)
{
    EffectSystem_EndHandleIn(&data_021d52d8, handle);
}
CLEAN_AS(func_0209129c, EffectSystem_EndHandle)

/* func_020912ac: kind `kind` started at `position` and `angle`, its place's half-word 0x10
 * `extra`; its handle, or -1. */
int EffectSystem_StartKindWithExtra(int kind, short extra, const Vec3 *position, const s16 *angle)
{
    s16 given = extra;

    return EffectSystem_StartKindIn(&data_021d52d8, (unsigned int) kind, position, angle, &given, -1);
}
CLEAN_AS(func_020912ac, EffectSystem_StartKindWithExtra)

/* func_020912d4: kind `kind` started at `position` (`angle` and `extra` may be NULL); its
 * handle when it started a kept set, else -1. */
int EffectSystem_StartKind(int kind, const Vec3 *position, const s16 *angle, const s16 *extra)
{
    return EffectSystem_StartKindIn(&data_021d52d8, (unsigned int) kind, position, angle, extra, -1);
}
CLEAN_AS(func_020912d4, EffectSystem_StartKind)

/* func_02091300: every place cleared and the handles counted from 0 again. */
void EffectSystem_ResetPlaces(void)
{
    EffectSystem_ResetPlacesIn(&data_021d52d8);
}
CLEAN_AS(func_02091300, EffectSystem_ResetPlaces)

/* func_02091310: the kind of the first place of handle `handle`, EFFECT_SYSTEM_KINDS for none. */
unsigned short EffectSystem_KindOfHandle(EffectSystemPlaces *places, int handle)
{
    const EffectKindsPlace *place = (const EffectKindsPlace *) (uintptr_t) EffectSystem_FindHandle(
        places->places, handle, places->places, EFFECT_SYSTEM_PLACES);

    if (place == NULL) {
        return EFFECT_SYSTEM_KINDS;
    }
    return (unsigned short) place->kind;
}
CLEAN_AS(func_02091310, EffectSystem_KindOfHandle)

/* func_0209132c: the end function of the kind of handle `handle` called with it, when the
 * handle is not -1, has a place and its kind has one. */
void EffectSystem_EndHandleIn(EffectSystemPlaces *places, int handle)
{
    unsigned int kind;

    if (handle == EFFECT_SYSTEM_NO_HANDLE) {
        return;
    }
    kind = EffectSystem_KindOfHandle(places, handle);
    if (kind >= EFFECT_SYSTEM_KINDS) {
        return;
    }
    if (data_020e2c1c[kind].end != NULL) {
        data_020e2c1c[kind].end(handle);
    }
}
CLEAN_AS(func_0209132c, EffectSystem_EndHandleIn)

/* func_02091358: kind `kind`'s start function called (`set` is the set of kinds 0x64 and
 * 0x65). When it started a kept set the next handle is used up: handed out when it answered
 * 0, kept back when it answered 2. The handle, or -1. */
int EffectSystem_StartKindIn(EffectSystemPlaces *places, unsigned int kind, const Vec3 *position, const s16 *angle,
                             const s16 *extra, int set)
{
    int handle = EFFECT_SYSTEM_NO_HANDLE;
    int result;

    if (kind >= EFFECT_SYSTEM_KINDS || data_020e2c1c[kind].start == NULL) {
        return handle;
    }
    result = data_020e2c1c[kind].start((int) kind, position, angle, extra, set);
    if (result == EFFECT_SYSTEM_KEPT_STARTED) {
        handle = places->next_handle;
        places->next_handle++;
    } else if (result == EFFECT_SYSTEM_KEPT_UNHANDED) {
        places->next_handle++;
    }
    return handle;
}
CLEAN_AS(func_02091358, EffectSystem_StartKindIn)

/* func_020913b0: every place cleared and the handles counted from 0 again. */
void EffectSystem_ResetPlacesIn(EffectSystemPlaces *places)
{
    EffectSystem_ClearPlaces(places);
    places->next_handle = 0;
}
CLEAN_AS(func_020913b0, EffectSystem_ResetPlacesIn)

/* func_020913c8: the frames left of each of the 32 places of handle `handle` set to `frames`
 * (none for handle -1). */
void EffectSystem_SetHandleFrames(EffectKindsPlace *places, int handle, short frames)
{
    int i;

    if (handle == EFFECT_SYSTEM_NO_HANDLE) {
        return;
    }
    for (i = 0; i < EFFECT_SYSTEM_PLACES; i++) {
        if (handle == places[i].handle) {
            places[i].frames = frames;
        }
    }
}
CLEAN_AS(func_020913c8, EffectSystem_SetHandleFrames)

/* func_020913f0: each of the 32 places of handle `handle` moved to `position`, and given
 * `angle` and the half-word `extra` when they are not NULL (none for handle -1). */
void EffectSystem_MovePlaces(EffectKindsPlace *places, int handle, const Vec3 *position, const s16 *angle, const s16 *extra)
{
    int i;

    if (handle == EFFECT_SYSTEM_NO_HANDLE) {
        return;
    }
    for (i = 0; i < EFFECT_SYSTEM_PLACES; i++) {
        EffectKindsPlace *place = &places[i];

        if (handle == place->handle) {
            place->position.x = position->x;
            place->position.y = position->y;
            place->position.z = position->z;
            if (angle != NULL) {
                place->angle = *angle;
            }
            if (extra != NULL) {
                place->unk_10 = *extra;
            }
        }
    }
}
CLEAN_AS(func_020913f0, EffectSystem_MovePlaces)

/* func_02091444: the first of `count` places from `places` with handle `handle` (its address),
 * 0 for none. QUIRK: the first argument is not read. */
int EffectSystem_FindHandle(EffectKindsPlace *unused, int handle, EffectKindsPlace *places, int count)
{
    int i;

    (void) unused;
    for (i = 0; i < count; i++) {
        if (handle == places[i].handle) {
            return (int) (uintptr_t) &places[i];
        }
    }
    return 0;
}
CLEAN_AS(func_02091444, EffectSystem_FindHandle)

/* func_02091468: the place being started cleared, then the 32 kept ones. */
void EffectSystem_ClearPlaces(EffectSystemPlaces *places)
{
    int i;

    EffectSystem_ClearPlace(&places->starting);
    for (i = 0; i < EFFECT_SYSTEM_PLACES; i++) {
        EffectSystem_ClearPlace(&places->places[i]);
    }
}
CLEAN_AS(func_02091468, EffectSystem_ClearPlaces)

/* func_02091494: the place cleared, then given the handle, the kind, the point, the angle and
 * the half-word 0x10 when they are not NULL, and the frames to follow it (-1 for ever). */
void EffectSystem_FillPlace(EffectKindsPlace *place, int handle, short kind, const Vec3 *position, const s16 *angle,
                            const s16 *extra, short frames)
{
    EffectSystem_ClearPlace(place);
    place->handle = handle;
    place->kind = kind;
    place->position.x = position->x;
    place->position.y = position->y;
    place->position.z = position->z;
    if (angle != NULL) {
        place->angle = *angle;
    }
    if (extra != NULL) {
        place->unk_10 = *extra;
    }
    place->frames = frames;
}
CLEAN_AS(func_02091494, EffectSystem_FillPlace)

/* func_020914dc: the place cleared: point and angle 0, followed for ever, the half-word 0x10
 * 0x1000, no handle and no kind. */
void EffectSystem_ClearPlace(EffectKindsPlace *place)
{
    MI_CpuFill8(place, 0, offsetof(EffectKindsPlace, handle));
    place->frames = EFFECT_SYSTEM_FOR_EVER;
    place->unk_10 = EFFECT_SYSTEM_UNK_10_DEFAULT;
    place->handle = EFFECT_SYSTEM_NO_HANDLE;
    place->kind = EFFECT_SYSTEM_KINDS;
}
CLEAN_AS(func_020914dc, EffectSystem_ClearPlace)

/* func_02091504: kind 0x65, the kept set `set` with the default words. */
void EffectSystem_StartKind65(int kind, const Vec3 *position, const s16 *angle, const s16 *extra, int set)
{
    /* QUIRK: declared without a result; in the ROM the set's result is still in r0 when it
     * returns, and the kind table's caller (func_02091358) reads it as the kind's. */
    EffectPlaces_StartKept(set, kind, position, angle, extra, NULL);
}
CLEAN_AS(func_02091504, EffectSystem_StartKind65)

/* func_02091528: kind 0x64, the one-shot set `set` with the default words. */
int EffectSystem_StartKind64(int kind, const Vec3 *position, const s16 *angle, const s16 *extra, int set)
{
    return EffectPlaces_StartOneShot(set, kind, position, angle, extra, NULL);
}
CLEAN_AS(func_02091528, EffectSystem_StartKind64)

/* CMD_ReservedReqCmd (0x0209154c): kind 0x63, which starts nothing. */
int EffectSystem_StartKind63(void)
{
    return EFFECT_SYSTEM_NOT_STARTED;
}
CLEAN_AS(CMD_ReservedReqCmd, EffectSystem_StartKind63)

/* func_02091550: kind 0x62, one-shot set 0x7d. */
int EffectSystem_StartKind62(int kind, const Vec3 *position, const s16 *angle, const s16 *extra)
{
    return EffectPlaces_StartOneShot(EFFECT_SYSTEM_SET_KIND_62, kind, position, angle, extra, NULL);
}
CLEAN_AS(func_02091550, EffectSystem_StartKind62)

/* func_02091574: kind 0x61, kept set 0x7c. */
int EffectSystem_StartKind61(int kind, const Vec3 *position, const s16 *angle, const s16 *extra)
{
    return EffectPlaces_StartKept(EFFECT_SYSTEM_SET_KIND_61, kind, position, angle, extra, NULL);
}
CLEAN_AS(func_02091574, EffectSystem_StartKind61)

/* func_02091598: kind 0x60, one-shot set 0x7b. */
void EffectSystem_StartKind60(int kind, const Vec3 *position, const s16 *angle, const s16 *extra)
{
    /* QUIRK: declared without a result; in the ROM the set's result is still in r0 when it
     * returns, and the kind table's caller (func_02091358) reads it as the kind's. */
    EffectPlaces_StartOneShot(EFFECT_SYSTEM_SET_KIND_60, kind, position, angle, extra, data_020e2798);
}
CLEAN_AS(func_02091598, EffectSystem_StartKind60)

/* func_020915c0: kind 0x60's first emitter set up a little ahead of its place, its axis
 * forward and down. */
void EffectSystem_SetUpKind60(ParticleEmitter *emitter)
{
    EffectPlaces_SetUpAt(emitter, &data_020d1810, &data_020d16d8);
}
CLEAN_AS(func_020915c0, EffectSystem_SetUpKind60)

/* func_020915d4: kind 0x5f, one-shot set 0x51. */
void EffectSystem_StartKind5f(int kind, const Vec3 *position, const s16 *angle, const s16 *extra)
{
    /* QUIRK: declared without a result; in the ROM the set's result is still in r0 when it
     * returns, and the kind table's caller (func_02091358) reads it as the kind's. */
    EffectPlaces_StartOneShot(EFFECT_SYSTEM_SET_KIND_5F, kind, position, angle, extra, data_020e286c);
}
CLEAN_AS(func_020915d4, EffectSystem_StartKind5f)

/* func_020915fc: kind 0x5f's first two emitters set up ahead of their place, their axis
 * forward and down. */
void EffectSystem_SetUpKind5f(ParticleEmitter *emitter)
{
    EffectPlaces_SetUpAt(emitter, &data_020d16f0, &data_020d175c);
}
CLEAN_AS(func_020915fc, EffectSystem_SetUpKind5f)

/* func_02091610: kind 0x5e, model 1 at its place. */
void EffectSystem_StartKind5e(int kind, const Vec3 *position, const s16 *angle, const s16 *extra)
{
    /* QUIRK: declared without a result; in the ROM the model's result is still in r0 when it
     * returns, and the kind table's caller (func_02091358) reads it as the kind's. */
    EffectKinds_StartModel(EFFECT_SYSTEM_MODEL_KIND_5E, kind, position, angle, extra, NULL);
}
CLEAN_AS(func_02091610, EffectSystem_StartKind5e)

/* func_02091634: kind 0x5d, model 0 at its place. */
int EffectSystem_StartKind5d(int kind, const Vec3 *position, const s16 *angle, const s16 *extra)
{
    return EffectKinds_StartModel(EFFECT_SYSTEM_MODEL_KIND_5D, kind, position, angle, extra, NULL);
}
CLEAN_AS(func_02091634, EffectSystem_StartKind5d)

/* func_02091658: kind 0x5c, one-shot set 0x15. */
void EffectSystem_StartKind5c(int kind, const Vec3 *position, const s16 *angle, const s16 *extra)
{
    /* QUIRK: declared without a result; in the ROM the set's result is still in r0 when it
     * returns, and the kind table's caller (func_02091358) reads it as the kind's. */
    EffectPlaces_StartOneShot(EFFECT_SYSTEM_SET_KIND_5C, kind, position, angle, extra, NULL);
}
CLEAN_AS(func_02091658, EffectSystem_StartKind5c)

/* func_0209167c: kind 0x5b, one-shot set 0x82 with kind 0x5a's words. */
void EffectSystem_StartKind5b(int kind, const Vec3 *position, const s16 *angle, const s16 *extra)
{
    /* QUIRK: declared without a result; in the ROM the set's result is still in r0 when it
     * returns, and the kind table's caller (func_02091358) reads it as the kind's. */
    EffectPlaces_StartOneShot(EFFECT_SYSTEM_SET_KIND_5B, kind, position, angle, extra, data_020e27d0);
}
CLEAN_AS(func_0209167c, EffectSystem_StartKind5b)

/* func_020916a4: kind 0x5a, one-shot set 0x14. */
void EffectSystem_StartKind5a(int kind, const Vec3 *position, const s16 *angle, const s16 *extra)
{
    /* QUIRK: declared without a result; in the ROM the set's result is still in r0 when it
     * returns, and the kind table's caller (func_02091358) reads it as the kind's. */
    EffectPlaces_StartOneShot(EFFECT_SYSTEM_SET_KIND_5A, kind, position, angle, extra, data_020e27d0);
}
CLEAN_AS(func_020916a4, EffectSystem_StartKind5a)

/* func_020916cc: the first emitter of kinds 0x5a and 0x5b set up above and ahead of its place,
 * its axis forward. */
void EffectSystem_SetUpKind5a(ParticleEmitter *emitter)
{
    EffectPlaces_SetUpAt(emitter, &data_020d17bc, &data_020d1750);
}
CLEAN_AS(func_020916cc, EffectSystem_SetUpKind5a)

/* func_020916e0: kind 0x59, one-shot set 0x13; then, whatever it answered, kept set 0x62 at the
 * place filled again with the next handle and 0x25 frames, 2 when that started, else 3. The
 * place being started is cleared after. */
int EffectSystem_StartKind59(int kind, const Vec3 *position, const s16 *angle, const s16 *extra)
{
    int result = EFFECT_SYSTEM_NOT_STARTED;

    EffectPlaces_StartOneShot(EFFECT_SYSTEM_SET_KIND_59, kind, position, angle, extra, NULL);
    EffectSystem_FillPlace(&data_021d52d8.starting, data_021d52d8.next_handle, (short) kind, position, angle, extra,
                           EFFECT_SYSTEM_KIND_59_FRAMES);
    if (EffectSystem_StartKeptSet(EFFECT_SYSTEM_SET_KIND_59_KEPT, position, angle, data_020e2944) != 0) {
        result = EFFECT_SYSTEM_KEPT_UNHANDED;
    }
    EffectSystem_ClearPlace(&data_021d52d8.starting);
    return result;
}
CLEAN_AS(func_020916e0, EffectSystem_StartKind59)

/* func_02091744: kind 0x59's follow word: while the instance's place has a handle and frames
 * left, the angle of each of its emitter's particles is set (+12500, or -12500 when the place's
 * angle is negative) and a counted frame used up; else the place is cleared. The emitter stays
 * where it is. Whether it lasted. */
int EffectSystem_FollowKind59(EffectKindsInstance *instance)
{
    EffectKindsPlace *place = &data_021d52d8.places[instance->slot];
    int lasts = 0;

    if (place->handle != EFFECT_SYSTEM_NO_HANDLE && place->frames != 0) {
        u16 rotation = (u16) (place->angle < 0 ? -EFFECT_SYSTEM_SPIN : EFFECT_SYSTEM_SPIN);
        ParticleLink *link;

        for (link = instance->emitter->particles.first; link != NULL; link = link->next) {
            ((Particle *) link)->rotation = rotation;
        }
        if (place->frames > 0) {
            place->frames--;
        }
        lasts = 1;
    }
    if (!lasts) {
        EffectSystem_ClearPlace(place);
    }
    return lasts;
}
CLEAN_AS(func_02091744, EffectSystem_FollowKind59)

/* func_020917c8: kind 0x58, one-shot set 0x12. */
void EffectSystem_StartKind58(int kind, const Vec3 *position, const s16 *angle, const s16 *extra)
{
    /* QUIRK: declared without a result; in the ROM the set's result is still in r0 when it
     * returns, and the kind table's caller (func_02091358) reads it as the kind's. */
    EffectPlaces_StartOneShot(EFFECT_SYSTEM_SET_KIND_58, kind, position, angle, extra, NULL);
}
CLEAN_AS(func_020917c8, EffectSystem_StartKind58)

/* func_020917ec: kind 0x57, one-shot set 0x11. */
void EffectSystem_StartKind57(int kind, const Vec3 *position, const s16 *angle, const s16 *extra)
{
    /* QUIRK: declared without a result; in the ROM the set's result is still in r0 when it
     * returns, and the kind table's caller (func_02091358) reads it as the kind's. */
    EffectPlaces_StartOneShot(EFFECT_SYSTEM_SET_KIND_57, kind, position, angle, extra, NULL);
}
CLEAN_AS(func_020917ec, EffectSystem_StartKind57)

/* func_02091810: kind 0x56's end function: its places of handle `handle` left 4 frames, while
 * which their emitters fade (EffectSystem_FollowKind56). */
void EffectSystem_EndKind56(int handle)
{
    EffectSystem_SetHandleFrames(data_021d52d8.places, handle, EFFECT_SYSTEM_KIND_56_FRAMES);
}
CLEAN_AS(func_02091810, EffectSystem_EndKind56)

/* func_02091824: kind 0x56, kept set 0x10. */
void EffectSystem_StartKind56(int kind, const Vec3 *position, const s16 *angle, const s16 *extra)
{
    /* QUIRK: declared without a result; in the ROM the set's result is still in r0 when it
     * returns, and the kind table's caller (func_02091358) reads it as the kind's. */
    EffectPlaces_StartKept(EFFECT_SYSTEM_SET_KIND_56, kind, position, angle, extra, data_020e2a1c);
}
CLEAN_AS(func_02091824, EffectSystem_StartKind56)

/* func_0209184c: the follow word of kind 0x56's emitters after the first: while the instance's
 * place has a handle and frames left, its emitter is put at the place (not turned); while the
 * frames are counted (once the effect is ended) the emitter's base alpha is 6 per frame left
 * and a frame is used up. Else the place is cleared. Whether it lasted. */
int EffectSystem_FollowKind56(EffectKindsInstance *instance)
{
    EffectKindsPlace *place = &data_021d52d8.places[instance->slot];
    int lasts = 0;

    if (place->handle != EFFECT_SYSTEM_NO_HANDLE && place->frames != 0) {
        ParticleEmitter *emitter = instance->emitter;

        effect_system_put_emitter(emitter, &place->position);
        if (place->frames > 0) {
            /* QUIRK: the alpha is the low byte of the product. */
            emitter->misc =
                particle_with_bits(emitter->misc, EMITTER_BASE_ALPHA_SHIFT, 8, (u8) (EFFECT_SYSTEM_FADE_STEP * place->frames));
            place->frames--;
        }
        lasts = 1;
    }
    if (!lasts) {
        EffectSystem_ClearPlace(place);
    }
    return lasts;
}
CLEAN_AS(func_0209184c, EffectSystem_FollowKind56)

/* func_020918d8: the follow word of kind 0x56's first emitter: while the instance's place has a
 * handle and is followed for ever, its emitter is put at the place (not turned). Else (once the
 * effect is ended) each of the emitter's particles is made as old as its life, which ends it,
 * and the place is cleared. Whether it lasted. */
int EffectSystem_FollowKind56First(EffectKindsInstance *instance)
{
    EffectKindsPlace *place = &data_021d52d8.places[instance->slot];
    int lasts = 0;

    if (place->handle != EFFECT_SYSTEM_NO_HANDLE && place->frames == EFFECT_SYSTEM_FOR_EVER) {
        effect_system_put_emitter(instance->emitter, &place->position);
        lasts = 1;
    }
    if (!lasts) {
        ParticleLink *link;

        for (link = instance->emitter->particles.first; link != NULL; link = link->next) {
            Particle *particle = (Particle *) link;

            particle->age = particle->life;
        }
        EffectSystem_ClearPlace(place);
    }
    return lasts;
}
CLEAN_AS(func_020918d8, EffectSystem_FollowKind56First)

/* func_02091960: kind 0x55, kept set 0x0f with the default words at the place filled with the
 * next handle and 15 frames; 2 when it started, else 3. The place being started is cleared
 * after. */
int EffectSystem_StartKind55(int kind, const Vec3 *position, const s16 *angle, const s16 *extra)
{
    int result = EFFECT_SYSTEM_NOT_STARTED;

    EffectSystem_FillPlace(&data_021d52d8.starting, data_021d52d8.next_handle, (short) kind, position, angle, extra,
                           EFFECT_SYSTEM_KIND_55_FRAMES);
    if (EffectSystem_StartKeptSet(EFFECT_SYSTEM_SET_KIND_55, position, angle, data_020e2ac4) != 0) {
        result = EFFECT_SYSTEM_KEPT_UNHANDED;
    }
    EffectSystem_ClearPlace(&data_021d52d8.starting);
    return result;
}
CLEAN_AS(func_02091960, EffectSystem_StartKind55)

/* func_020919ac: kind 0x54, kept set 0x0e: two emitters on either side of the place, raised
 * when the place's half-word 0x10 is 3. */
void EffectSystem_StartKind54(int kind, const Vec3 *position, const s16 *angle, const s16 *extra)
{
    /* QUIRK: declared without a result; in the ROM the set's result is still in r0 when it
     * returns, and the kind table's caller (func_02091358) reads it as the kind's. */
    EffectPlaces_StartKept(EFFECT_SYSTEM_SET_KIND_54, kind, position, angle, extra, data_020e2934);
}
CLEAN_AS(func_020919ac, EffectSystem_StartKind54)

/* func_020919d4: kind 0x54's second emitter moved with its place, on its -X side. */
void EffectSystem_FollowKind54Second(EffectKindsInstance *instance)
{
    const EffectKindsPlace *place = &data_021d52d8.places[instance->slot];

    /* QUIRK: declared without a result; the follow's result is still in r0 when it returns. */
    EffectPlaces_Follow(instance, place->unk_10 != EFFECT_SYSTEM_RAISED ? &data_020d1828 : &data_020d1834, &data_020d1744);
}
CLEAN_AS(func_020919d4, EffectSystem_FollowKind54Second)

/* func_02091a24: kind 0x54's first emitter moved with its place, on its +X side. */
void EffectSystem_FollowKind54First(EffectKindsInstance *instance)
{
    const EffectKindsPlace *place = &data_021d52d8.places[instance->slot];

    /* QUIRK: declared without a result; the follow's result is still in r0 when it returns. */
    EffectPlaces_Follow(instance, place->unk_10 != EFFECT_SYSTEM_RAISED ? &data_020d1840 : &data_020d184c, &data_020d178c);
}
CLEAN_AS(func_02091a24, EffectSystem_FollowKind54First)

/* func_02091a74: kind 0x54's second emitter placed on the -X side of the place being started.
 * QUIRK: the place is copied into the instance's entry twice (EffectPlaces_Place copies it
 * too). */
void EffectSystem_PlaceKind54Second(EffectKindsInstance *instance)
{
    u8 slot = instance->slot;

    EffectPlaces_Place(instance, data_021d52d8.starting.unk_10 != EFFECT_SYSTEM_RAISED ? &data_020d1828 : &data_020d1834,
                       &data_020d1744);
    MI_CpuCopy8(&data_021d52d8.starting, &data_021d52d8.places[slot], sizeof(EffectKindsPlace));
}
CLEAN_AS(func_02091a74, EffectSystem_PlaceKind54Second)

/* func_02091ad0: kind 0x54's first emitter placed on the +X side of the place being started.
 * QUIRK: the place is copied into the instance's entry twice. */
void EffectSystem_PlaceKind54First(EffectKindsInstance *instance)
{
    u8 slot = instance->slot;

    EffectPlaces_Place(instance, data_021d52d8.starting.unk_10 != EFFECT_SYSTEM_RAISED ? &data_020d1840 : &data_020d184c,
                       &data_020d178c);
    MI_CpuCopy8(&data_021d52d8.starting, &data_021d52d8.places[slot], sizeof(EffectKindsPlace));
}
CLEAN_AS(func_02091ad0, EffectSystem_PlaceKind54First)

/* func_02091b2c: kind 0x53, kept set 0x0d. */
void EffectSystem_StartKind53(int kind, const Vec3 *position, const s16 *angle, const s16 *extra)
{
    /* QUIRK: declared without a result; in the ROM the set's result is still in r0 when it
     * returns, and the kind table's caller (func_02091358) reads it as the kind's. */
    EffectPlaces_StartKept(EFFECT_SYSTEM_SET_KIND_53, kind, position, angle, extra, data_020e2984);
}
CLEAN_AS(func_02091b2c, EffectSystem_StartKind53)

/* func_02091b54: kind 0x52, one-shot set 0x5d. */
void EffectSystem_StartKind52(int kind, const Vec3 *position, const s16 *angle, const s16 *extra)
{
    /* QUIRK: declared without a result; in the ROM the set's result is still in r0 when it
     * returns, and the kind table's caller (func_02091358) reads it as the kind's. */
    EffectPlaces_StartOneShot(EFFECT_SYSTEM_SET_KIND_52, kind, position, angle, extra, data_020e27c0);
}
CLEAN_AS(func_02091b54, EffectSystem_StartKind52)

/* func_02091b7c: kind 0x52's first emitter set up below the place being started, at height 0,
 * and tinted. */
void EffectSystem_SetUpKind52(ParticleEmitter *emitter)
{
    Vec3 at = data_021d52d8.starting.position;

    at.y = 0;
    effect_system_put_emitter(emitter, &at);
    EffectSystem_TintEmitter(emitter);
}
CLEAN_AS(func_02091b7c, EffectSystem_SetUpKind52)

/* func_02091bc4: kind 0x51, one-shot set 0x0c. */
void EffectSystem_StartKind51(int kind, const Vec3 *position, const s16 *angle, const s16 *extra)
{
    /* QUIRK: declared without a result; in the ROM the set's result is still in r0 when it
     * returns, and the kind table's caller (func_02091358) reads it as the kind's. */
    EffectPlaces_StartOneShot(EFFECT_SYSTEM_SET_KIND_51, kind, position, angle, extra, NULL);
}
CLEAN_AS(func_02091bc4, EffectSystem_StartKind51)

/* func_02091be8: kind 0x50, one-shot set 0x0b. */
int EffectSystem_StartKind50(int kind, const Vec3 *position, const s16 *angle, const s16 *extra)
{
    return EffectPlaces_StartOneShot(EFFECT_SYSTEM_SET_KIND_50, kind, position, angle, extra, NULL);
}
CLEAN_AS(func_02091be8, EffectSystem_StartKind50)

/* func_02091c0c: kind 0x4f, one-shot set 0x0a. */
int EffectSystem_StartKind4f(int kind, const Vec3 *position, const s16 *angle, const s16 *extra)
{
    return EffectPlaces_StartOneShot(EFFECT_SYSTEM_SET_KIND_4F, kind, position, angle, extra, NULL);
}
CLEAN_AS(func_02091c0c, EffectSystem_StartKind4f)

/* func_02091c30: kind 0x4e, kept set 9: two emitters at offsets chosen by the place's
 * half-word 0x10, then two more. */
void EffectSystem_StartKind4e(int kind, const Vec3 *position, const s16 *angle, const s16 *extra)
{
    /* QUIRK: declared without a result; in the ROM the set's result is still in r0 when it
     * returns, and the kind table's caller (func_02091358) reads it as the kind's. */
    EffectPlaces_StartKept(EFFECT_SYSTEM_SET_KIND_4E, kind, position, angle, extra, data_020e29c4);
}
CLEAN_AS(func_02091c30, EffectSystem_StartKind4e)

/* func_02091c58: kind 0x4e's second emitter moved with its place, at the offset of
 * data_020e2bb0 its half-word 0x10 chooses (the table has nine; the ROM reads past it the same
 * way for others). */
void EffectSystem_FollowKind4eSecond(EffectKindsInstance *instance)
{
    const EffectKindsPlace *place = &data_021d52d8.places[instance->slot];

    /* QUIRK: declared without a result; the follow's result is still in r0 when it returns. */
    EffectPlaces_Follow(instance, &data_020e2bb0[place->unk_10], NULL);
}
CLEAN_AS(func_02091c58, EffectSystem_FollowKind4eSecond)

/* func_02091ca0: kind 0x4e's first emitter moved with its place, at the offset of
 * data_020e2b44 its half-word 0x10 chooses. */
void EffectSystem_FollowKind4eFirst(EffectKindsInstance *instance)
{
    const EffectKindsPlace *place = &data_021d52d8.places[instance->slot];

    /* QUIRK: declared without a result; the follow's result is still in r0 when it returns. */
    EffectPlaces_Follow(instance, &data_020e2b44[place->unk_10], NULL);
}
CLEAN_AS(func_02091ca0, EffectSystem_FollowKind4eFirst)

/* func_02091ce8: kind 0x4e's second emitter placed at the offset of data_020e2bb0 the place
 * being started chooses. QUIRK: the place is copied into the instance's entry twice. */
void EffectSystem_PlaceKind4eSecond(EffectKindsInstance *instance)
{
    u8 slot = instance->slot;

    EffectPlaces_Place(instance, &data_020e2bb0[data_021d52d8.starting.unk_10], NULL);
    MI_CpuCopy8(&data_021d52d8.starting, &data_021d52d8.places[slot], sizeof(EffectKindsPlace));
}
CLEAN_AS(func_02091ce8, EffectSystem_PlaceKind4eSecond)

/* func_02091d3c: kind 0x4e's first emitter placed at the offset of data_020e2b44 the place
 * being started chooses. QUIRK: the place is copied into the instance's entry twice. */
void EffectSystem_PlaceKind4eFirst(EffectKindsInstance *instance)
{
    u8 slot = instance->slot;

    EffectPlaces_Place(instance, &data_020e2b44[data_021d52d8.starting.unk_10], NULL);
    MI_CpuCopy8(&data_021d52d8.starting, &data_021d52d8.places[slot], sizeof(EffectKindsPlace));
}
CLEAN_AS(func_02091d3c, EffectSystem_PlaceKind4eFirst)

/* func_02091d90: kind 0x4d, kept set 0x16 with the default words. */
void EffectSystem_StartKind4d(int kind, const Vec3 *position, const s16 *angle, const s16 *extra)
{
    /* QUIRK: declared without a result; in the ROM the set's result is still in r0 when it
     * returns, and the kind table's caller (func_02091358) reads it as the kind's. */
    EffectPlaces_StartKept(EFFECT_SYSTEM_SET_KIND_4D, kind, position, angle, extra, NULL);
}
CLEAN_AS(func_02091d90, EffectSystem_StartKind4d)

/* func_02091db4: kind 0x4c, kept set 8 with the default words. */
void EffectSystem_StartKind4c(int kind, const Vec3 *position, const s16 *angle, const s16 *extra)
{
    /* QUIRK: declared without a result; in the ROM the set's result is still in r0 when it
     * returns, and the kind table's caller (func_02091358) reads it as the kind's. */
    EffectPlaces_StartKept(EFFECT_SYSTEM_SET_KIND_4C, kind, position, angle, extra, NULL);
}
CLEAN_AS(func_02091db4, EffectSystem_StartKind4c)
