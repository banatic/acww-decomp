/* The spot that asks the spawner for an actor (spawn_spot.h). */
#include "spawn_spot.h"

#include "autoload_2/heap.h" /* Heap_FreeAux, Heap_AllocAuxZeroed */
#include "clean.h"
#include "main/scene_query.h"
#include "main/spawner.h"
#include "ov009/scene_actor_life.h"

static_assert(offsetof(SceneActor, position) == 0x5c, "position");
static_assert(offsetof(SceneActor, receiver_vtable) == 0xec, "receiver");
static_assert(sizeof(SpawnSpot) == 0x2b4, "the size SpawnSpot_New allocates");

#define SPAWN_SPOT_RECEIVER_OFFSET 0xec

/* The profile it asks for: 0x60. */
extern const u16 data_ov003_022398c4[];
/* The vtables: the class's and its receiver part's. */
extern const u8 data_ov003_022398e8[];
extern const u8 data_ov003_022399ac[];

/* func_ov003_0221ee48 (vtable slot 0x0c): always 1. */
int SpawnSpot_Slot0C(void)
{
    return 1;
}
CLEAN_AS(func_ov003_0221ee48, SpawnSpot_Slot0C)

/* func_ov003_0221ee4c (vtable slot 0x24, its drawing): nothing to draw; always 1. */
int SpawnSpot_Draw(void)
{
    return 1;
}
CLEAN_AS(func_ov003_0221ee4c, SpawnSpot_Draw)

/* func_ov003_0221ee50 (vtable slot 0x18, its update): nothing to do; always 1. */
int SpawnSpot_Update(void)
{
    return 1;
}
CLEAN_AS(func_ov003_0221ee50, SpawnSpot_Update)

/* func_ov003_0221ee54 (vtable slot 0x70, setting it up): asks the spawner for an actor of
 * profile 0x60 in the current scene at its position; always 1. */
int SpawnSpot_SetUp(SpawnSpot *spot)
{
    Spawner_RequestAt(data_ov003_022398c4, SceneQuery_Current(), &spot->actor.position);
    return 1;
}
CLEAN_AS(func_ov003_0221ee54, SpawnSpot_SetUp)

/* The vtables set back, then overlay 9's destructor. */
static void spawn_spot_destroy_parts(SpawnSpot *spot)
{
    spot->actor.vtable = data_ov003_022398e8;
    spot->actor.receiver_vtable = data_ov003_022399ac;
    SceneActor_Destruct((SceneActor *) spot);
}

/* func_ov003_0221ee74 (vtable slot 0x44, the deleting destructor): the destructor's work, then
 * the memory freed. */
SpawnSpot *SpawnSpot_DestroyAndFree(SpawnSpot *spot)
{
    spawn_spot_destroy_parts(spot);
    Heap_FreeAux(spot);
    return spot;
}
CLEAN_AS(func_ov003_0221ee74, SpawnSpot_DestroyAndFree)

/* func_ov003_0221eea0 (vtable slot 0x40): the destructor, without freeing. */
SpawnSpot *SpawnSpot_Destroy(SpawnSpot *spot)
{
    spawn_spot_destroy_parts(spot);
    return spot;
}
CLEAN_AS(func_ov003_0221eea0, SpawnSpot_Destroy)

/* func_ov003_0221eec4: the constructor: overlay 9's, then the vtables. */
SpawnSpot *SpawnSpot_Construct(SpawnSpot *spot)
{
    SceneActor_ConstructBase((SceneActor *) spot);
    spot->actor.vtable = data_ov003_022398e8;
    spot->actor.receiver_vtable = data_ov003_022399ac;
    return spot;
}
CLEAN_AS(func_ov003_0221eec4, SpawnSpot_Construct)

/* func_ov003_0221eee8 (the class's entry in the overlay's table of profiles): allocates and
 * constructs one; nothing keeps the pointer here. */
void SpawnSpot_New(void)
{
    SpawnSpot *spot = Heap_AllocAuxZeroed(sizeof(SpawnSpot));
    if (spot != NULL) {
        SpawnSpot_Construct(spot);
    }
}
CLEAN_AS(func_ov003_0221eee8, SpawnSpot_New)

/* The spot around its receiver part, as the receiver vtable's thunks find it. */
static SpawnSpot *spawn_spot_from_receiver(void *receiver)
{
    return (SpawnSpot *) (void *) ((u8 *) receiver - SPAWN_SPOT_RECEIVER_OFFSET);
}

/* _ZThn236_N18Obj_ov003_022398e8D0Ev (receiver slot 0x04): SpawnSpot_DestroyAndFree. */
SpawnSpot *SpawnSpot_ReceiverDestroyAndFree(void *receiver)
{
    return SpawnSpot_DestroyAndFree(spawn_spot_from_receiver(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov003_022398e8D0Ev, SpawnSpot_ReceiverDestroyAndFree)

/* _ZThn236_N18Obj_ov003_022398e8D1Ev (receiver slot 0x00): SpawnSpot_Destroy. */
SpawnSpot *SpawnSpot_ReceiverDestroy(void *receiver)
{
    return SpawnSpot_Destroy(spawn_spot_from_receiver(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov003_022398e8D1Ev, SpawnSpot_ReceiverDestroy)
