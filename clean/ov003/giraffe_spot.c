/* The scene object that marks the giraffe's spot (giraffe_spot.h). */
#include "giraffe_spot.h"

#include "autoload_2/heap.h" /* Heap_FreeAux, Heap_AllocAuxZeroed */
#include "clean.h"
#include "main/calendar.h" /* DateTime */
#include "main/date_time.h"
#include "main/event_calendar.h"
#include "main/scene_query.h"
#include "main/spawner.h"
#include "ov009/town_object_actor.h"
#include "ov009/town_object_actor_life.h"

static_assert(offsetof(GiraffeSpot, position) == 0x5c, "position");
static_assert(offsetof(GiraffeSpot, receiver_vtable) == 0xec, "receiver");
static_assert(sizeof(GiraffeSpot) == 0x2b4, "size");

#define GIRAFFE_SPOT_RECEIVER_OFFSET 0xec
#define GIRAFFE_SPOT_EVENT 0x40 /* the giraffe's visit, asked of func_0203fc78 */

/* The vtables: the class's and its receiver part's. */
extern const u8 data_ov003_022387a8[];
extern const u8 data_ov003_0223886c[];
/* The profile it asks the spawner for: 0x6c, the giraffe. */
extern const u16 data_ov003_02238784[];

extern void MI_CpuCopy8(const void *src, void *dst, u32 size);

/* _ZThn236_N18Obj_ov009_022658dc17vfunc_02066994_14Ev: overlay 9's receiver slot 0x14
 * (func_ov009_02263344) on the actor around `receiver`; the giraffe spot's and the
 * checkpoint's receivers use it. */
void GiraffeSpot_ReceiverSlot14(void *receiver)
{
    TownObjectActor_OnMessageEnd((TownObjectActor *) ((u8 *) receiver - GIRAFFE_SPOT_RECEIVER_OFFSET));
}
CLEAN_AS(_ZThn236_N18Obj_ov009_022658dc17vfunc_02066994_14Ev, GiraffeSpot_ReceiverSlot14)

/* func_ov003_0221c314 (vtable slot 0x70): while event 0x40 is on now, asks the spawner for
 * the giraffe (profile 0x6c) in this scene, where the object stands; always 1. */
int GiraffeSpot_SetUp(GiraffeSpot *object)
{
    DateTime now = {0};
    DateTime when;
    DateTime_Now(&now);
    MI_CpuCopy8(&now, &when, sizeof when);
    if (EventCalendar_State(GIRAFFE_SPOT_EVENT, &when, 0) != 0) {
        Spawner_RequestAt(data_ov003_02238784, SceneQuery_Current(), &object->position);
    }
    return 1;
}
CLEAN_AS(func_ov003_0221c314, GiraffeSpot_SetUp)

/* The vtables set back, then overlay 9's destructor. */
static void giraffe_spot_destroy_parts(GiraffeSpot *object)
{
    object->vtable = data_ov003_022387a8;
    object->receiver_vtable = data_ov003_0223886c;
    TownObjectActor_Destruct((TownObjectActor *) object);
}

/* func_ov003_0221c368 (the deleting destructor): the destructor's work, then the memory
 * freed. */
GiraffeSpot *GiraffeSpot_Delete(GiraffeSpot *object)
{
    giraffe_spot_destroy_parts(object);
    Heap_FreeAux(object);
    return object;
}
CLEAN_AS(func_ov003_0221c368, GiraffeSpot_Delete)

/* func_ov003_0221c394: the destructor, without freeing. */
GiraffeSpot *GiraffeSpot_Destruct(GiraffeSpot *object)
{
    giraffe_spot_destroy_parts(object);
    return object;
}
CLEAN_AS(func_ov003_0221c394, GiraffeSpot_Destruct)

/* func_ov003_0221c3b8: the constructor: overlay 9's, then the vtables. */
GiraffeSpot *GiraffeSpot_Construct(GiraffeSpot *object)
{
    TownObjectActor_ConstructBase((TownObjectActor *) object);
    object->vtable = data_ov003_022387a8;
    object->receiver_vtable = data_ov003_0223886c;
    return object;
}
CLEAN_AS(func_ov003_0221c3b8, GiraffeSpot_Construct)

/* func_ov003_0221c3dc: allocates and constructs one; nothing keeps the pointer here. */
void GiraffeSpot_New(void)
{
    GiraffeSpot *object = Heap_AllocAuxZeroed(sizeof(GiraffeSpot));
    if (object != NULL) {
        GiraffeSpot_Construct(object);
    }
}
CLEAN_AS(func_ov003_0221c3dc, GiraffeSpot_New)

/* _ZThn236_N18Obj_ov003_022387a8D0Ev (the receiver vtable's deleting destructor):
 * GiraffeSpot_Delete on the object around `receiver`. */
GiraffeSpot *GiraffeSpot_ReceiverDelete(void *receiver)
{
    return GiraffeSpot_Delete((GiraffeSpot *) (void *) ((u8 *) receiver - GIRAFFE_SPOT_RECEIVER_OFFSET));
}
CLEAN_AS(_ZThn236_N18Obj_ov003_022387a8D0Ev, GiraffeSpot_ReceiverDelete)

/* _ZThn236_N18Obj_ov003_022387a8D1Ev (the receiver vtable's destructor): GiraffeSpot_Destruct on
 * the object around `receiver`. */
GiraffeSpot *GiraffeSpot_ReceiverDestruct(void *receiver)
{
    return GiraffeSpot_Destruct((GiraffeSpot *) (void *) ((u8 *) receiver - GIRAFFE_SPOT_RECEIVER_OFFSET));
}
CLEAN_AS(_ZThn236_N18Obj_ov003_022387a8D1Ev, GiraffeSpot_ReceiverDestruct)
