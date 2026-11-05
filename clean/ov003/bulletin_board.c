/* The town's bulletin board, the scene object that opens its screen (bulletin_board.h). */
#include "bulletin_board.h"

#include <stdint.h>

#include "autoload_2/approach.h" /* Math_AbsDiff16 */
#include "autoload_2/heap.h"     /* Heap_FreeAux, Heap_AllocAuxZeroed */
#include "clean.h"
#include "main/group_params.h" /* GroupParams_CanOpen, GroupParams_Open */
#include "ov004/member_pointer.h"
#include "main/event_queue.h"
#include "main/scene_object_base.h"
#include "ov009/town_object_actor_life.h"

static_assert(offsetof(BulletinBoard, yaw) == 0x8e, "yaw");
static_assert(offsetof(BulletinBoard, receiver_vtable) == 0xec, "receiver");
static_assert(offsetof(BulletinBoard, flags_235) == 0x235, "flags");
static_assert(offsetof(BulletinBoard, state) == 0x2b4, "state");
static_assert(sizeof(BulletinBoard) == 0x2b8, "size");
static_assert(offsetof(BulletinBoardViewer, yaw) == 0x8e, "viewer yaw");

/* The scene events of vtable slot 0x4c. */
#define BULLETIN_BOARD_EVENT_OPEN 0
#define BULLETIN_BOARD_EVENT_OPEN_AGAIN 1
#define BULLETIN_BOARD_EVENT_IDLE 8

/* The mode of group 9 it opens: the bulletin board's screen (ov113/bbs_board.h). */
#define BULLETIN_BOARD_MODE 0

/* The vtables: the class's and its receiver part's. */
extern const u8 data_ov003_02238434[];
extern const u8 data_ov003_022384f8[];

/* The machine's tables (member_pointer.h): their guards, the tables and their constants. */
extern u32 data_ov003_0223c74c;
extern MemberPointer data_ov003_0223c754[BULLETIN_BOARD_STATES];
extern const MemberPointer data_ov003_022383e4, data_ov003_022383fc, data_ov003_0223840c;
extern u32 data_ov003_0223c748;
extern MemberPointer data_ov003_0223c76c[BULLETIN_BOARD_STATES];
extern const MemberPointer data_ov003_022383ec, data_ov003_022383f4, data_ov003_02238404;

/* func_ov003_0221b7f0 (update of BULLETIN_BOARD_OPEN): once main can open a screen again, the
 * scene goes on. Its state stays BULLETIN_BOARD_OPEN until the scene sets another. */
void BulletinBoard_UpdateOpen(BulletinBoard *object)
{
    if (GroupParams_CanOpen()) {
        EventQueue_FinishObjectEvent(object);
    }
}
CLEAN_AS(func_ov003_0221b7f0, BulletinBoard_UpdateOpen)

/* func_ov003_0221b808 (entry of BULLETIN_BOARD_OPEN) */
int BulletinBoard_EnterOpen(BulletinBoard *object)
{
    (void) object;
    return 1;
}
CLEAN_AS(func_ov003_0221b808, BulletinBoard_EnterOpen)

/* _ZN18Obj_ov003_0223843419func_ov003_0221b80cEv (update of BULLETIN_BOARD_OPENING): on to
 * BULLETIN_BOARD_OPEN. */
void BulletinBoard_UpdateOpening(BulletinBoard *object)
{
    BulletinBoard_SetState(object, BULLETIN_BOARD_OPEN);
}
CLEAN_AS(_ZN18Obj_ov003_0223843419func_ov003_0221b80cEv, BulletinBoard_UpdateOpening)

/* func_ov003_0221b818 (entry of BULLETIN_BOARD_OPENING): whether main agreed to open group 9 in
 * mode 0. */
int BulletinBoard_EnterOpening(BulletinBoard *object)
{
    (void) object;
    return GroupParams_Open(BULLETIN_BOARD_MODE) != 0;
}
CLEAN_AS(func_ov003_0221b818, BulletinBoard_EnterOpening)

/* func_ov003_0221b834 (update of BULLETIN_BOARD_IDLE) */
void BulletinBoard_UpdateIdle(void) {}
CLEAN_AS(func_ov003_0221b834, BulletinBoard_UpdateIdle)

/* func_ov003_0221b838 (entry of BULLETIN_BOARD_IDLE) */
int BulletinBoard_EnterIdle(BulletinBoard *object)
{
    (void) object;
    return 1;
}
CLEAN_AS(func_ov003_0221b838, BulletinBoard_EnterIdle)

/* func_ov003_0221b83c: the state's update, through its table.
 * REQUIRES: the state is not negative (BulletinBoard_SetState only sets 0 to 2). */
void BulletinBoard_UpdateState(BulletinBoard *object)
{
    static const MemberPointer *const updates[BULLETIN_BOARD_STATES] = {
        &data_ov003_022383e4, /* BulletinBoard_UpdateIdle */
        &data_ov003_022383fc, /* BulletinBoard_UpdateOpening */
        &data_ov003_0223840c, /* BulletinBoard_UpdateOpen */
    };
    MemberTable_InitOnce(&data_ov003_0223c74c, data_ov003_0223c754, updates, BULLETIN_BOARD_STATES);
    if (object->state < BULLETIN_BOARD_STATES) {
        MemberPointer_CallVoid(&data_ov003_0223c754[object->state], object);
    }
}
CLEAN_AS(func_ov003_0221b83c, BulletinBoard_UpdateState)

/* _ZN18Obj_ov003_0223843419func_ov003_0221b8b8Ei: enters state `state` if its entry (through a
 * table) agrees; whether it did. States 3 and above do not exist.
 * REQUIRES: `state` is not negative. */
int BulletinBoard_SetState(BulletinBoard *object, int state)
{
    static const MemberPointer *const entries[BULLETIN_BOARD_STATES] = {
        &data_ov003_022383ec, /* BulletinBoard_EnterIdle */
        &data_ov003_022383f4, /* BulletinBoard_EnterOpening */
        &data_ov003_02238404, /* BulletinBoard_EnterOpen */
    };
    MemberTable_InitOnce(&data_ov003_0223c748, data_ov003_0223c76c, entries, BULLETIN_BOARD_STATES);
    if (state < BULLETIN_BOARD_STATES && MemberPointer_CallInt(&data_ov003_0223c76c[state], object) != 0) {
        object->state = state;
        return 1;
    }
    return 0;
}
CLEAN_AS(_ZN18Obj_ov003_0223843419func_ov003_0221b8b8Ei, BulletinBoard_SetState)

/* _ZN18Obj_ov003_0223843419func_ov003_0221b944Ei (vtable slot 0x4c): the scene's events: 0 and
 * 1 open the screen, 8 makes it idle; others do nothing. */
void BulletinBoard_OnSceneEvent(BulletinBoard *object, int event)
{
    switch (event) {
        case BULLETIN_BOARD_EVENT_OPEN:
        case BULLETIN_BOARD_EVENT_OPEN_AGAIN:
            BulletinBoard_SetState(object, BULLETIN_BOARD_OPENING);
            break;
        case BULLETIN_BOARD_EVENT_IDLE:
            BulletinBoard_SetState(object, BULLETIN_BOARD_IDLE);
            break;
        default:
            break;
    }
}
CLEAN_AS(_ZN18Obj_ov003_0223843419func_ov003_0221b944Ei, BulletinBoard_OnSceneEvent)

/* func_ov003_0221b96c (vtable slot 0x48): whether `viewer` faces it (its yaw within 0x1300 of
 * the object's turned half round) while bit 3 of the byte at 0x235 is set; then func_0203edd0
 * runs on the object. */
int BulletinBoard_IsFacedBy(BulletinBoard *object, BulletinBoardViewer *viewer)
{
    if ((object->flags_235 & 8) && viewer != NULL && Math_AbsDiff16((s16) (object->yaw + 0x8000), viewer->yaw) < 0x1300) {
        SceneObjectBase_ClearApproach((SceneObjectBase *) object);
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov003_0221b96c, BulletinBoard_IsFacedBy)

/* func_ov003_0221b9b8 (vtable slot 0x0c): always 1. */
int BulletinBoard_Slot0C(void)
{
    return 1;
}
CLEAN_AS(func_ov003_0221b9b8, BulletinBoard_Slot0C)

/* func_ov003_0221b9bc (vtable slot 0x24): always 1. */
int BulletinBoard_Slot24(void)
{
    return 1;
}
CLEAN_AS(func_ov003_0221b9bc, BulletinBoard_Slot24)

/* func_ov003_0221b9c0 (vtable slot 0x18): the state's update; always 1. */
int BulletinBoard_Update(BulletinBoard *object)
{
    BulletinBoard_UpdateState(object);
    return 1;
}
CLEAN_AS(func_ov003_0221b9c0, BulletinBoard_Update)

/* _ZN18Obj_ov003_0223843419func_ov003_0221b9d0Ev (vtable slot 0x70): makes it idle; always 1. */
int BulletinBoard_Reset(BulletinBoard *object)
{
    BulletinBoard_SetState(object, BULLETIN_BOARD_IDLE);
    return 1;
}
CLEAN_AS(_ZN18Obj_ov003_0223843419func_ov003_0221b9d0Ev, BulletinBoard_Reset)

/* The vtables set back, then overlay 9's destructor. */
static void destroy_parts(BulletinBoard *object)
{
    object->vtable = data_ov003_02238434;
    object->receiver_vtable = data_ov003_022384f8;
    TownObjectActor_Destruct((TownObjectActor *) object);
}

/* func_ov003_0221b9e4 (the deleting destructor): the destructor's work, then the memory freed. */
BulletinBoard *BulletinBoard_DestroyAndFree(BulletinBoard *object)
{
    destroy_parts(object);
    Heap_FreeAux(object);
    return object;
}
CLEAN_AS(func_ov003_0221b9e4, BulletinBoard_DestroyAndFree)

/* func_ov003_0221ba10: the destructor, without freeing. */
BulletinBoard *BulletinBoard_Destroy(BulletinBoard *object)
{
    destroy_parts(object);
    return object;
}
CLEAN_AS(func_ov003_0221ba10, BulletinBoard_Destroy)

/* func_ov003_0221ba34: the constructor: overlay 9's, then the vtables. */
BulletinBoard *BulletinBoard_Construct(BulletinBoard *object)
{
    TownObjectActor_ConstructBase((TownObjectActor *) object);
    object->vtable = data_ov003_02238434;
    object->receiver_vtable = data_ov003_022384f8;
    return object;
}
CLEAN_AS(func_ov003_0221ba34, BulletinBoard_Construct)

/* func_ov003_0221ba58: allocates and constructs one; nothing keeps the pointer here. */
void BulletinBoard_New(void)
{
    BulletinBoard *object = Heap_AllocAuxZeroed(sizeof(BulletinBoard));
    if (object != NULL) {
        BulletinBoard_Construct(object);
    }
}
CLEAN_AS(func_ov003_0221ba58, BulletinBoard_New)

/* func_ov003_0221ba74 (the receiver vtable's deleting destructor): BulletinBoard_DestroyAndFree
 * on the object around `receiver`. */
BulletinBoard *BulletinBoard_ReceiverDestroyAndFree(void *receiver)
{
    return BulletinBoard_DestroyAndFree((BulletinBoard *) (void *) ((u8 *) receiver - 0xec));
}
CLEAN_AS(_ZThn236_N18Obj_ov003_02238434D0Ev, BulletinBoard_ReceiverDestroyAndFree)

/* _ZThn236_N18Obj_ov003_02238434D1Ev (the receiver vtable's destructor): BulletinBoard_Destroy
 * on the object around `receiver`. */
BulletinBoard *BulletinBoard_ReceiverDestroy(void *receiver)
{
    return BulletinBoard_Destroy((BulletinBoard *) (void *) ((u8 *) receiver - 0xec));
}
CLEAN_AS(_ZThn236_N18Obj_ov003_02238434D1Ev, BulletinBoard_ReceiverDestroy)
