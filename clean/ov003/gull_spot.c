/* The spot that asks the spawner for the gull (gull_spot.h). */
#include "gull_spot.h"

#include "autoload_2/heap.h" /* Heap_FreeAux, Heap_AllocAuxZeroed */
#include "clean.h"
#include "main/scene_query.h"
#include "main/spawner.h"
#include "ov009/town_object_actor_life.h"

static_assert(offsetof(TownObjectActor, position) == 0x5c, "position");
static_assert(offsetof(TownObjectActor, receiver_vtable) == 0xec, "receiver");
static_assert(sizeof(GullSpot) == 0x2b4, "the size GullSpot_New allocates");

#define SPAWN_SPOT_RECEIVER_OFFSET 0xec

/* The profile it asks for: 0x60. */
extern const u16 data_ov003_022398c4[];
/* The vtables: the class's and its receiver part's. */
extern const u8 data_ov003_022398e8[];
extern const u8 data_ov003_022399ac[];

/* func_ov003_0221ee48 (vtable slot 0x0c): always 1. */
int GullSpot_Slot0c(void)
{
    return 1;
}
CLEAN_AS(func_ov003_0221ee48, GullSpot_Slot0c)

/* func_ov003_0221ee4c (vtable slot 0x24, its drawing): nothing to draw; always 1. */
int GullSpot_Draw(void)
{
    return 1;
}
CLEAN_AS(func_ov003_0221ee4c, GullSpot_Draw)

/* func_ov003_0221ee50 (vtable slot 0x18, its update): nothing to do; always 1. */
int GullSpot_Update(void)
{
    return 1;
}
CLEAN_AS(func_ov003_0221ee50, GullSpot_Update)

/* func_ov003_0221ee54 (vtable slot 0x70, setting it up): asks the spawner for an actor of
 * profile 0x60 in the current scene at its position; always 1. */
int GullSpot_SetUp(GullSpot *spot)
{
    Spawner_RequestAt(data_ov003_022398c4, SceneQuery_Current(), &spot->actor.position);
    return 1;
}
CLEAN_AS(func_ov003_0221ee54, GullSpot_SetUp)

/* The vtables set back, then overlay 9's destructor. */
static void spawn_spot_destroy_parts(GullSpot *spot)
{
    spot->actor.vtable = data_ov003_022398e8;
    spot->actor.receiver_vtable = data_ov003_022399ac;
    TownObjectActor_Destruct((TownObjectActor *) spot);
}

/* func_ov003_0221ee74 (vtable slot 0x44, the deleting destructor): the destructor's work, then
 * the memory freed. */
GullSpot *GullSpot_DestroyAndFree(GullSpot *spot)
{
    spawn_spot_destroy_parts(spot);
    Heap_FreeAux(spot);
    return spot;
}
CLEAN_AS(func_ov003_0221ee74, GullSpot_DestroyAndFree)

/* func_ov003_0221eea0 (vtable slot 0x40): the destructor, without freeing. */
GullSpot *GullSpot_Destroy(GullSpot *spot)
{
    spawn_spot_destroy_parts(spot);
    return spot;
}
CLEAN_AS(func_ov003_0221eea0, GullSpot_Destroy)

/* func_ov003_0221eec4: the constructor: overlay 9's, then the vtables. */
GullSpot *GullSpot_Construct(GullSpot *spot)
{
    TownObjectActor_ConstructBase((TownObjectActor *) spot);
    spot->actor.vtable = data_ov003_022398e8;
    spot->actor.receiver_vtable = data_ov003_022399ac;
    return spot;
}
CLEAN_AS(func_ov003_0221eec4, GullSpot_Construct)

/* func_ov003_0221eee8 (the class's entry in the overlay's table of profiles): allocates and
 * constructs one; nothing keeps the pointer here. */
void GullSpot_New(void)
{
    GullSpot *spot = Heap_AllocAuxZeroed(sizeof(GullSpot));
    if (spot != NULL) {
        GullSpot_Construct(spot);
    }
}
CLEAN_AS(func_ov003_0221eee8, GullSpot_New)

/* The spot around its receiver part, as the receiver vtable's thunks find it. */
static GullSpot *spawn_spot_from_receiver(void *receiver)
{
    return (GullSpot *) (void *) ((u8 *) receiver - SPAWN_SPOT_RECEIVER_OFFSET);
}

/* _ZThn236_N18Obj_ov003_022398e8D0Ev (receiver slot 0x04): GullSpot_DestroyAndFree. */
GullSpot *GullSpot_ReceiverDestroyAndFree(void *receiver)
{
    return GullSpot_DestroyAndFree(spawn_spot_from_receiver(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov003_022398e8D0Ev, GullSpot_ReceiverDestroyAndFree)

/* _ZThn236_N18Obj_ov003_022398e8D1Ev (receiver slot 0x00): GullSpot_Destroy. */
GullSpot *GullSpot_ReceiverDestroy(void *receiver)
{
    return GullSpot_Destroy(spawn_spot_from_receiver(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov003_022398e8D1Ev, GullSpot_ReceiverDestroy)
