/* The scene object that sends the player to place 0x6c (warp_object.h). */
#include "warp_object.h"

#include "autoload_2/heap.h" /* Heap_FreeAux, Heap_AllocAuxZeroed */
#include "clean.h"
#include "main/calendar.h" /* DateTime */

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

/* Overlay 9's scene actor: the update of its receiver slot 0x14, its destructor and its
 * constructor. */
extern void func_ov009_02263344(void *actor);
extern void *func_ov009_0226539c(WarpObject *object);
extern void *func_ov009_0226552c(WarpObject *object);
/* The clock's date and time (DateTime_Now). */
extern void func_0209e474(DateTime *now);
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
/* Whether event `event` is on at `when`. */
extern int func_0203fc78(int event, DateTime *when, int arg);
/* Requests a change to the scene of place `*place` in scene `scene`, arriving at `position`. */
extern int func_02084cd0(const u16 *place, int scene, const Vec3 *position);
/* The scene. */
extern u8 func_020b65c4(void);

/* _ZThn236_N18Obj_ov009_022658dc17vfunc_02066994_14Ev: overlay 9's receiver slot 0x14
 * (func_ov009_02263344) on the actor around `receiver`; the warp object's and the
 * checkpoint's receivers use it. */
void WarpObject_ReceiverSlot14(void *receiver)
{
    func_ov009_02263344((u8 *) receiver - WARP_OBJECT_RECEIVER_OFFSET);
}
CLEAN_AS(_ZThn236_N18Obj_ov009_022658dc17vfunc_02066994_14Ev, WarpObject_ReceiverSlot14)

/* func_ov003_0221c314 (vtable slot 0x70): while event 0x40 is on now, requests the change
 * to place 0x6c in this scene, arriving where the object stands; always 1. */
int WarpObject_Enter(WarpObject *object)
{
    DateTime now = {0};
    DateTime when;
    func_0209e474(&now);
    MI_CpuCopy8(&now, &when, sizeof when);
    if (func_0203fc78(WARP_OBJECT_EVENT, &when, 0) != 0) {
        func_02084cd0(data_ov003_02238784, func_020b65c4(), &object->position);
    }
    return 1;
}
CLEAN_AS(func_ov003_0221c314, WarpObject_Enter)

/* The vtables set back, then overlay 9's destructor. */
static void warp_object_destroy_parts(WarpObject *object)
{
    object->vtable = data_ov003_022387a8;
    object->receiver_vtable = data_ov003_0223886c;
    func_ov009_0226539c(object);
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
    func_ov009_0226552c(object);
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
