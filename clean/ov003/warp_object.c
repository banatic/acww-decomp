/* The scene object that sends the player to place 0x6c (warp_object.h). */
#include "warp_object.h"

#include "autoload_2/heap.h" /* Heap_FreeAux, Heap_AllocAuxZeroed */
#include "clean.h"
#include "main/calendar.h" /* DateTime */
#include "main/date_time.h"
#include "main/event_calendar.h"
#include "main/scene_query.h"
#include "main/spawner.h"
#include "ov009/scene_actor.h"
#include "ov009/scene_actor_life.h"

static_assert(offsetof(WarpObject, position) == 0x5c, "position");
static_assert(offsetof(WarpObject, receiver_vtable) == 0xec, "receiver");
static_assert(sizeof(WarpObject) == 0x2b4, "size");

#define WARP_OBJECT_RECEIVER_OFFSET 0xec
#define WARP_OBJECT_EVENT 0x40 /* the event it asks func_0203fc78 about */

/* The vtables: the class's and its receiver part's. */
extern const u8 data_ov003_022387a8[];
extern const u8 data_ov003_0223886c[];
/* The place it sends the player to: 0x6c. */
extern const u16 data_ov003_02238784[];

extern void MI_CpuCopy8(const void *src, void *dst, u32 size);

/* _ZThn236_N18Obj_ov009_022658dc17vfunc_02066994_14Ev: overlay 9's receiver slot 0x14
 * (func_ov009_02263344) on the actor around `receiver`; the warp object's and the
 * checkpoint's receivers use it. */
void WarpObject_ReceiverSlot14(void *receiver)
{
    SceneActor_OnMessageEnd((SceneActor *) ((u8 *) receiver - WARP_OBJECT_RECEIVER_OFFSET));
}
CLEAN_AS(_ZThn236_N18Obj_ov009_022658dc17vfunc_02066994_14Ev, WarpObject_ReceiverSlot14)

/* func_ov003_0221c314 (vtable slot 0x70): while event 0x40 is on now, requests the change
 * to place 0x6c in this scene, arriving where the object stands; always 1. */
int WarpObject_Enter(WarpObject *object)
{
    DateTime now = {0};
    DateTime when;
    DateTime_Now(&now);
    MI_CpuCopy8(&now, &when, sizeof when);
    if (EventCalendar_State(WARP_OBJECT_EVENT, &when, 0) != 0) {
        Spawner_RequestAt(data_ov003_02238784, SceneQuery_Current(), &object->position);
    }
    return 1;
}
CLEAN_AS(func_ov003_0221c314, WarpObject_Enter)

/* The vtables set back, then overlay 9's destructor. */
static void warp_object_destroy_parts(WarpObject *object)
{
    object->vtable = data_ov003_022387a8;
    object->receiver_vtable = data_ov003_0223886c;
    SceneActor_Destruct((SceneActor *) object);
}

/* func_ov003_0221c368 (the deleting destructor): the destructor's work, then the memory
 * freed. */
WarpObject *WarpObject_DestroyAndFree(WarpObject *object)
{
    warp_object_destroy_parts(object);
    Heap_FreeAux(object);
    return object;
}
CLEAN_AS(func_ov003_0221c368, WarpObject_DestroyAndFree)

/* func_ov003_0221c394: the destructor, without freeing. */
WarpObject *WarpObject_Destroy(WarpObject *object)
{
    warp_object_destroy_parts(object);
    return object;
}
CLEAN_AS(func_ov003_0221c394, WarpObject_Destroy)

/* func_ov003_0221c3b8: the constructor: overlay 9's, then the vtables. */
WarpObject *WarpObject_Construct(WarpObject *object)
{
    SceneActor_ConstructBase((SceneActor *) object);
    object->vtable = data_ov003_022387a8;
    object->receiver_vtable = data_ov003_0223886c;
    return object;
}
CLEAN_AS(func_ov003_0221c3b8, WarpObject_Construct)

/* func_ov003_0221c3dc: allocates and constructs one; nothing keeps the pointer here. */
void WarpObject_New(void)
{
    WarpObject *object = Heap_AllocAuxZeroed(sizeof(WarpObject));
    if (object != NULL) {
        WarpObject_Construct(object);
    }
}
CLEAN_AS(func_ov003_0221c3dc, WarpObject_New)

/* _ZThn236_N18Obj_ov003_022387a8D0Ev (the receiver vtable's deleting destructor):
 * WarpObject_DestroyAndFree on the object around `receiver`. */
WarpObject *WarpObject_ReceiverDestroyAndFree(void *receiver)
{
    return WarpObject_DestroyAndFree((WarpObject *) (void *) ((u8 *) receiver - WARP_OBJECT_RECEIVER_OFFSET));
}
CLEAN_AS(_ZThn236_N18Obj_ov003_022387a8D0Ev, WarpObject_ReceiverDestroyAndFree)

/* _ZThn236_N18Obj_ov003_022387a8D1Ev (the receiver vtable's destructor): WarpObject_Destroy on
 * the object around `receiver`. */
WarpObject *WarpObject_ReceiverDestroy(void *receiver)
{
    return WarpObject_Destroy((WarpObject *) (void *) ((u8 *) receiver - WARP_OBJECT_RECEIVER_OFFSET));
}
CLEAN_AS(_ZThn236_N18Obj_ov003_022387a8D1Ev, WarpObject_ReceiverDestroy)
