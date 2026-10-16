/* The scene object that opens a screen (screen_object.h). */
#include "screen_object.h"

#include <stdint.h>

#include "autoload_2/approach.h" /* Math_AbsDiff16 */
#include "autoload_2/heap.h"     /* Heap_FreeAux, Heap_AllocAuxZeroed */
#include "clean.h"
#include "main/group_params.h" /* GroupParams_CanOpen, GroupParams_Open */
#include "ov004/member_pointer.h"

static_assert(offsetof(ScreenObject, yaw) == 0x8e, "yaw");
static_assert(offsetof(ScreenObject, receiver_vtable) == 0xec, "receiver");
static_assert(offsetof(ScreenObject, flags_235) == 0x235, "flags");
static_assert(offsetof(ScreenObject, state) == 0x2b4, "state");
static_assert(sizeof(ScreenObject) == 0x2b8, "size");
static_assert(offsetof(ScreenObjectViewer, yaw) == 0x8e, "viewer yaw");

/* The scene events of vtable slot 0x4c. */
#define SCREEN_OBJECT_EVENT_OPEN 0
#define SCREEN_OBJECT_EVENT_OPEN_AGAIN 1
#define SCREEN_OBJECT_EVENT_IDLE 8

/* The mode of group 9 it opens. */
#define SCREEN_OBJECT_MODE 0

/* The vtables: the class's and its receiver part's. */
extern const u8 data_ov003_02238434[];
extern const u8 data_ov003_022384f8[];

/* The machine's tables (member_pointer.h): their guards, the tables and their constants. */
extern u32 data_ov003_0223c74c;
extern MemberPointer data_ov003_0223c754[SCREEN_OBJECT_STATES];
extern const MemberPointer data_ov003_022383e4, data_ov003_022383fc, data_ov003_0223840c;
extern u32 data_ov003_0223c748;
extern MemberPointer data_ov003_0223c76c[SCREEN_OBJECT_STATES];
extern const MemberPointer data_ov003_022383ec, data_ov003_022383f4, data_ov003_02238404;

/* Lets the scene go on. */
extern int func_0203e020(ScreenObject *object);
extern void func_0203edd0(ScreenObject *object);
/* Overlay 9's scene actor's destructor and constructor. */
extern void *func_ov009_0226539c(ScreenObject *object);
extern void *func_ov009_0226552c(ScreenObject *object);

/* func_ov003_0221b7f0 (update of SCREEN_OBJECT_OPEN): once main can open a screen again, the
 * scene goes on. Its state stays SCREEN_OBJECT_OPEN until the scene sets another. */
void ScreenObject_UpdateOpen(ScreenObject *object)
{
    if (GroupParams_CanOpen()) {
        func_0203e020(object);
    }
}
CLEAN_AS(func_ov003_0221b7f0, ScreenObject_UpdateOpen)

/* func_ov003_0221b808 (entry of SCREEN_OBJECT_OPEN) */
int ScreenObject_EnterOpen(ScreenObject *object)
{
    (void) object;
    return 1;
}
CLEAN_AS(func_ov003_0221b808, ScreenObject_EnterOpen)

/* _ZN18Obj_ov003_0223843419func_ov003_0221b80cEv (update of SCREEN_OBJECT_OPENING): on to
 * SCREEN_OBJECT_OPEN. */
void ScreenObject_UpdateOpening(ScreenObject *object)
{
    ScreenObject_SetState(object, SCREEN_OBJECT_OPEN);
}
CLEAN_AS(_ZN18Obj_ov003_0223843419func_ov003_0221b80cEv, ScreenObject_UpdateOpening)

/* func_ov003_0221b818 (entry of SCREEN_OBJECT_OPENING): whether main agreed to open group 9 in
 * mode 0. */
int ScreenObject_EnterOpening(ScreenObject *object)
{
    (void) object;
    return GroupParams_Open(SCREEN_OBJECT_MODE) != 0;
}
CLEAN_AS(func_ov003_0221b818, ScreenObject_EnterOpening)

/* func_ov003_0221b834 (update of SCREEN_OBJECT_IDLE) */
void ScreenObject_UpdateIdle(void) {}
CLEAN_AS(func_ov003_0221b834, ScreenObject_UpdateIdle)

/* func_ov003_0221b838 (entry of SCREEN_OBJECT_IDLE) */
int ScreenObject_EnterIdle(ScreenObject *object)
{
    (void) object;
    return 1;
}
CLEAN_AS(func_ov003_0221b838, ScreenObject_EnterIdle)

/* func_ov003_0221b83c: the state's update, through its table.
 * REQUIRES: the state is not negative (ScreenObject_SetState only sets 0 to 2). */
void ScreenObject_UpdateState(ScreenObject *object)
{
    static const MemberPointer *const updates[SCREEN_OBJECT_STATES] = {
        &data_ov003_022383e4, /* ScreenObject_UpdateIdle */
        &data_ov003_022383fc, /* ScreenObject_UpdateOpening */
        &data_ov003_0223840c, /* ScreenObject_UpdateOpen */
    };
    MemberTable_InitOnce(&data_ov003_0223c74c, data_ov003_0223c754, updates, SCREEN_OBJECT_STATES);
    if (object->state < SCREEN_OBJECT_STATES) {
        MemberPointer_CallVoid(&data_ov003_0223c754[object->state], object);
    }
}
CLEAN_AS(func_ov003_0221b83c, ScreenObject_UpdateState)

/* _ZN18Obj_ov003_0223843419func_ov003_0221b8b8Ei: enters state `state` if its entry (through a
 * table) agrees; whether it did. States 3 and above do not exist.
 * REQUIRES: `state` is not negative. */
int ScreenObject_SetState(ScreenObject *object, int state)
{
    static const MemberPointer *const entries[SCREEN_OBJECT_STATES] = {
        &data_ov003_022383ec, /* ScreenObject_EnterIdle */
        &data_ov003_022383f4, /* ScreenObject_EnterOpening */
        &data_ov003_02238404, /* ScreenObject_EnterOpen */
    };
    MemberTable_InitOnce(&data_ov003_0223c748, data_ov003_0223c76c, entries, SCREEN_OBJECT_STATES);
    if (state < SCREEN_OBJECT_STATES && MemberPointer_CallInt(&data_ov003_0223c76c[state], object) != 0) {
        object->state = state;
        return 1;
    }
    return 0;
}
CLEAN_AS(_ZN18Obj_ov003_0223843419func_ov003_0221b8b8Ei, ScreenObject_SetState)

/* _ZN18Obj_ov003_0223843419func_ov003_0221b944Ei (vtable slot 0x4c): the scene's events: 0 and
 * 1 open the screen, 8 makes it idle; others do nothing. */
void ScreenObject_OnSceneEvent(ScreenObject *object, int event)
{
    switch (event) {
        case SCREEN_OBJECT_EVENT_OPEN:
        case SCREEN_OBJECT_EVENT_OPEN_AGAIN:
            ScreenObject_SetState(object, SCREEN_OBJECT_OPENING);
            break;
        case SCREEN_OBJECT_EVENT_IDLE:
            ScreenObject_SetState(object, SCREEN_OBJECT_IDLE);
            break;
        default:
            break;
    }
}
CLEAN_AS(_ZN18Obj_ov003_0223843419func_ov003_0221b944Ei, ScreenObject_OnSceneEvent)

/* func_ov003_0221b96c (vtable slot 0x48): whether `viewer` faces it (its yaw within 0x1300 of
 * the object's turned half round) while bit 3 of the byte at 0x235 is set; then func_0203edd0
 * runs on the object. */
int ScreenObject_IsFacedBy(ScreenObject *object, ScreenObjectViewer *viewer)
{
    if ((object->flags_235 & 8) && viewer != NULL && Math_AbsDiff16((s16) (object->yaw + 0x8000), viewer->yaw) < 0x1300) {
        func_0203edd0(object);
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov003_0221b96c, ScreenObject_IsFacedBy)

/* func_ov003_0221b9b8 (vtable slot 0x0c): always 1. */
int ScreenObject_Slot0C(void)
{
    return 1;
}
CLEAN_AS(func_ov003_0221b9b8, ScreenObject_Slot0C)

/* func_ov003_0221b9bc (vtable slot 0x24): always 1. */
int ScreenObject_Slot24(void)
{
    return 1;
}
CLEAN_AS(func_ov003_0221b9bc, ScreenObject_Slot24)

/* func_ov003_0221b9c0 (vtable slot 0x18): the state's update; always 1. */
int ScreenObject_Update(ScreenObject *object)
{
    ScreenObject_UpdateState(object);
    return 1;
}
CLEAN_AS(func_ov003_0221b9c0, ScreenObject_Update)

/* _ZN18Obj_ov003_0223843419func_ov003_0221b9d0Ev (vtable slot 0x70): makes it idle; always 1. */
int ScreenObject_Reset(ScreenObject *object)
{
    ScreenObject_SetState(object, SCREEN_OBJECT_IDLE);
    return 1;
}
CLEAN_AS(_ZN18Obj_ov003_0223843419func_ov003_0221b9d0Ev, ScreenObject_Reset)

/* The vtables set back, then overlay 9's destructor. */
static void destroy_parts(ScreenObject *object)
{
    object->vtable = data_ov003_02238434;
    object->receiver_vtable = data_ov003_022384f8;
    func_ov009_0226539c(object);
}

/* func_ov003_0221b9e4 (the deleting destructor): the destructor's work, then the memory freed. */
ScreenObject *ScreenObject_DestroyAndFree(ScreenObject *object)
{
    destroy_parts(object);
    Heap_FreeAux(object);
    return object;
}
CLEAN_AS(func_ov003_0221b9e4, ScreenObject_DestroyAndFree)

/* func_ov003_0221ba10: the destructor, without freeing. */
ScreenObject *ScreenObject_Destroy(ScreenObject *object)
{
    destroy_parts(object);
    return object;
}
CLEAN_AS(func_ov003_0221ba10, ScreenObject_Destroy)

/* func_ov003_0221ba34: the constructor: overlay 9's, then the vtables. */
ScreenObject *ScreenObject_Construct(ScreenObject *object)
{
    func_ov009_0226552c(object);
    object->vtable = data_ov003_02238434;
    object->receiver_vtable = data_ov003_022384f8;
    return object;
}
CLEAN_AS(func_ov003_0221ba34, ScreenObject_Construct)

/* func_ov003_0221ba58: allocates and constructs one; nothing keeps the pointer here. */
void ScreenObject_New(void)
{
    ScreenObject *object = Heap_AllocAuxZeroed(sizeof(ScreenObject));
    if (object != NULL) {
        ScreenObject_Construct(object);
    }
}
CLEAN_AS(func_ov003_0221ba58, ScreenObject_New)

/* func_ov003_0221ba74 (the receiver vtable's deleting destructor): ScreenObject_DestroyAndFree
 * on the object around `receiver`. */
ScreenObject *ScreenObject_ReceiverDestroyAndFree(void *receiver)
{
    return ScreenObject_DestroyAndFree((ScreenObject *) (void *) ((u8 *) receiver - 0xec));
}
CLEAN_AS(_ZThn236_N18Obj_ov003_02238434D0Ev, ScreenObject_ReceiverDestroyAndFree)
