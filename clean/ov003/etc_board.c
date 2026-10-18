/* The "obj_etc_board" scene object (etc_board.h). */
#include "etc_board.h"

#include <assert.h>
#include <stddef.h>

#include "clean.h"
#include "autoload_2/heap.h"
#include "autoload_2/vector.h"
#include "main/event_queue.h"
#include "main/message_receiver.h"
#include "main/npc_id.h"
#include "main/player_id.h"
#include "main/scene_object_base.h"
#include "main/scene_query.h"
#include "main/talk_object.h"
#include "main/talk_receiver.h"
#include "main/touch_pick_shapes.h"
#include "main/town_villager.h"
#include "main/villager_roster.h"

static_assert(offsetof(EtcBoard, index) == 0x08, "index");
static_assert(offsetof(EtcBoard, position) == 0x5c, "position");
static_assert(offsetof(EtcBoard, receiver_vtable) == 0xec, "receiver");
static_assert(offsetof(EtcBoard, receiver_name) == 0xf0, "receiver name");
static_assert(offsetof(EtcBoard, receiver_unk_1E) == 0x10a, "receiver byte 0x1e");
static_assert(offsetof(EtcBoard, link) == 0x12c, "link");
static_assert(offsetof(EtcBoard, state) == 0x134, "state");
static_assert(offsetof(EtcBoard, member_138) == 0x138, "member");
static_assert(sizeof(EtcBoard) == 0x154, "size");
static_assert(offsetof(EtcBoardViewer, yaw) == 0x8e, "yaw");

/* The boards by index, and how many there are. */
extern EtcBoard *data_ov003_0223c5f4[ETC_BOARD_MAX];
extern u8 data_ov003_0223c5a0;

/* The vtables: the class's, and its receiver part's. */
extern const u8 data_ov003_02238010[];
extern const u8 data_ov003_02238078[];
/* "obj_etc_board" */
extern const char data_ov003_022380f0[];
/* The table whose entry `index` the board shows (eight entries of 0x7ec bytes). */
extern u8 data_021e5a2c[];

/* The receiver part of a board, as a C++ conversion makes it: null stays null. */
static void *receiver_of(EtcBoard *board)
{
    return board != NULL ? (void *) &board->receiver_vtable : NULL;
}

/* func_ov003_0220bf00: the board with `index`, or null when there is none or `index` is out of
 * 0-7. */
EtcBoard *EtcBoard_Get(int index)
{
    if (index >= 0 && index < ETC_BOARD_MAX) {
        return data_ov003_0223c5f4[index];
    }
    return NULL;
}
CLEAN_AS(func_ov003_0220bf00, EtcBoard_Get)

/* func_ov003_0220bf18: state 2's update. Once the link has closed, the receiver is released. */
void EtcBoard_UpdateOpen(EtcBoard *board)
{
    if (board->link != NULL && board->link->open == 0) {
        SceneObjectBase_ReleaseReceiver((SceneObjectBase *) board, receiver_of(board));
        EventQueue_FinishObjectEvent(board);
    }
}
CLEAN_AS(func_ov003_0220bf18, EtcBoard_UpdateOpen)

/* func_ov003_0220bf48: entering state 2 always succeeds. */
int EtcBoard_EnterOpen(EtcBoard *board)
{
    (void) board;
    return 1;
}
CLEAN_AS(func_ov003_0220bf48, EtcBoard_EnterOpen)

/* func_ov003_0220bf4c: state 1's update: on to state 2 once the link has opened. */
void EtcBoard_UpdateWaiting(EtcBoard *board)
{
    if (board->link != NULL && board->link->open != 0) {
        EtcBoard_SetState(board, ETC_BOARD_OPEN);
    }
}
CLEAN_AS(_ZN18Obj_ov003_0223801019func_ov003_0220bf4cEv, EtcBoard_UpdateWaiting)

/* func_ov003_0220bf70: entering state 1 (always succeeds). The receiver is taken and named,
 * and the link gets the text of the board's table entry with its request raised. */
int EtcBoard_EnterWaiting(EtcBoard *board)
{
    u8 text[0x24];

    SceneObjectBase_TakeReceiver((SceneObjectBase *) board, receiver_of(board));
    MessageReceiver_SetName((MessageReceiver *) &board->receiver_vtable, data_ov003_022380f0);
    board->receiver_unk_1E = 0;
    board->link->requested = 1;

    PlayerIdText_Construct((PlayerIdText *) text);
    NpcId_FormatName(TownVillager_NpcId(VillagerRoster_At((VillagerTown *) data_021e5a2c, (int) board->index)), (char *) text);
    TalkObject_SetPart((TalkObject *) board->link, 0, (TextBase *) text);
    PlayerIdText_Destruct((PlayerIdText *) text);
    return 1;
}
CLEAN_AS(func_ov003_0220bf70, EtcBoard_EnterWaiting)

/* func_ov003_0220bfe0: state 0's update does nothing. */
void EtcBoard_UpdateIdle(EtcBoard *board)
{
    (void) board;
}
CLEAN_AS(func_ov003_0220bfe0, EtcBoard_UpdateIdle)

/* func_ov003_0220bfe4: entering state 0 always succeeds. */
int EtcBoard_EnterIdle(EtcBoard *board)
{
    (void) board;
    return 1;
}
CLEAN_AS(func_ov003_0220bfe4, EtcBoard_EnterIdle)

/* func_ov003_0220bfe8: the update of the current state (the ROM picks it from a table of member
 * function pointers). REQUIRES: the state is 0-2, as EtcBoard_SetState leaves it; the ROM
 * reads before its table for a negative one, while this does nothing. */
void EtcBoard_Update(EtcBoard *board)
{
    switch (board->state) {
        case ETC_BOARD_IDLE:
            EtcBoard_UpdateIdle(board);
            break;
        case ETC_BOARD_WAITING:
            EtcBoard_UpdateWaiting(board);
            break;
        case ETC_BOARD_OPEN:
            EtcBoard_UpdateOpen(board);
            break;
        default:
            break;
    }
}
CLEAN_AS(_ZN18Obj_ov003_0223801019func_ov003_0220bfe8Ev, EtcBoard_Update)

/* func_ov003_0220c064: moves to `state` when entering it succeeds; whether it did.
 * REQUIRES: `state` is not negative (the callers pass 0-2); the ROM reads before its table of
 * entry functions for a negative one, while this refuses it. */
int EtcBoard_SetState(EtcBoard *board, int state)
{
    int entered;

    switch (state) {
        case ETC_BOARD_IDLE:
            entered = EtcBoard_EnterIdle(board);
            break;
        case ETC_BOARD_WAITING:
            entered = EtcBoard_EnterWaiting(board);
            break;
        case ETC_BOARD_OPEN:
            entered = EtcBoard_EnterOpen(board);
            break;
        default:
            return 0;
    }
    if (entered) {
        board->state = state;
        return 1;
    }
    return 0;
}
CLEAN_AS(_ZN18Obj_ov003_0223801019func_ov003_0220c064Ei, EtcBoard_SetState)

/* func_ov003_0220c0f0 (vtable slot 0x4c): event 0 starts the board (state 1), event 8 stops it
 * (state 0); other events are ignored. */
void EtcBoard_HandleEvent(EtcBoard *board, int event)
{
    switch (event) {
        case 0:
            EtcBoard_SetState(board, ETC_BOARD_WAITING);
            break;
        case 8:
            EtcBoard_SetState(board, ETC_BOARD_IDLE);
            break;
        default:
            break;
    }
}
CLEAN_AS(_ZN18Obj_ov003_0223801019func_ov003_0220c0f0Ei, EtcBoard_HandleEvent)

/* func_ov003_0220c114 (vtable slot 0x48): whether `viewer` stands within 0x2333 of the board
 * facing within 0x1100 of angle 0x8000. func_0203edd0 runs on the board first in any case. */
int EtcBoard_IsFacedBy(EtcBoard *board, const EtcBoardViewer *viewer)
{
    SceneObjectBase_ClearApproach((SceneObjectBase *) board);
    return viewer != NULL && Vec_DistanceXZ(&viewer->position, &board->position) < 0x2333 &&
           Math_AbsDiff16(-0x8000, viewer->yaw) <= 0x1100;
}
CLEAN_AS(func_ov003_0220c114, EtcBoard_IsFacedBy)

/* func_ov003_0220c160: empties the table when no board is counted in it. */
void EtcBoard_ClearTableIfEmpty(void)
{
    if (data_ov003_0223c5a0 == 0) {
        for (int i = 0; i < ETC_BOARD_MAX; i++) {
            data_ov003_0223c5f4[i] = NULL;
        }
    }
}
CLEAN_AS(func_ov003_0220c160, EtcBoard_ClearTableIfEmpty)

/* func_ov003_0220c184 (vtable slot 0x0c): takes the board out of the table; always 1.
 * REQUIRES: the board's index is 0-7, as EtcBoard_Init entered it. QUIRK: the count is a byte
 * and wraps below 0. */
int EtcBoard_Unregister(EtcBoard *board)
{
    data_ov003_0223c5f4[board->index] = NULL;
    data_ov003_0223c5a0--;
    return 1;
}
CLEAN_AS(func_ov003_0220c184, EtcBoard_Unregister)

/* func_ov003_0220c1a4 (vtable slot 0x24): always 1. */
int EtcBoard_Slot24(void)
{
    return 1;
}
CLEAN_AS(func_ov003_0220c1a4, EtcBoard_Slot24)

/* func_ov003_0220c1a8 (vtable slot 0x18): the state's update, then the member at 0x138 handed
 * to func_020b7d84 at the board's position, with 0xc00, 9 and the index's low byte; always 1. */
int EtcBoard_Run(EtcBoard *board)
{
    EtcBoard_Update(board);
    TouchPick_SetSphereAndAdd((TouchPick *) (uintptr_t) SceneQuery_FieldObject(), (TouchPickSphere *) board->member_138,
                              &board->position, 0xc00, 9, (u8) board->index);
    return 1;
}
CLEAN_AS(_ZN18Obj_ov003_0223801019func_ov003_0220c1a8Ev, EtcBoard_Run)

/* func_ov003_0220c1e4 (vtable slot 0x00): starts the board idle and enters it in the table
 * under its index (emptying the table first when it holds none); always 1.
 * REQUIRES: the index is 0-7. */
int EtcBoard_Init(EtcBoard *board)
{
    EtcBoard_ClearTableIfEmpty();
    SceneObjectBase_SetId((SceneObjectBase *) board, (u16) board->index);
    EtcBoard_SetState(board, ETC_BOARD_IDLE);
    data_ov003_0223c5f4[board->index] = board;
    data_ov003_0223c5a0++;
    return 1;
}
CLEAN_AS(_ZN18Obj_ov003_0223801019func_ov003_0220c1e4Ev, EtcBoard_Init)

/* func_ov003_0220c220: the deleting destructor: the member, the receiver part and the base
 * destroyed in turn, then the memory freed. */
EtcBoard *EtcBoard_DestroyAndFree(EtcBoard *board)
{
    board->vtable = data_ov003_02238010;
    board->receiver_vtable = data_ov003_02238078;
    TouchPickSphere_Destruct2((TouchPickSphere *) board->member_138);
    TalkReceiver_Destruct((TalkReceiver *) &board->receiver_vtable);
    SceneObjectBase_DestructBase((SceneObjectBase *) board);
    Heap_FreeAux(board);
    return board;
}
CLEAN_AS(func_ov003_0220c220, EtcBoard_DestroyAndFree)

/* func_ov003_0220c260: the destructor, without freeing. */
EtcBoard *EtcBoard_Destroy(EtcBoard *board)
{
    board->vtable = data_ov003_02238010;
    board->receiver_vtable = data_ov003_02238078;
    TouchPickSphere_Destruct2((TouchPickSphere *) board->member_138);
    TalkReceiver_Destruct((TalkReceiver *) &board->receiver_vtable);
    SceneObjectBase_DestructBase((SceneObjectBase *) board);
    return board;
}
CLEAN_AS(func_ov003_0220c260, EtcBoard_Destroy)

/* func_ov003_0220c29c: the constructor: the base and the receiver part, then the vtables and
 * the member at 0x138. */
EtcBoard *EtcBoard_Construct(EtcBoard *board)
{
    SceneObjectBase_Construct((SceneObjectBase *) board);
    TalkReceiver_ConstructBase((TalkReceiver *) &board->receiver_vtable);
    board->vtable = data_ov003_02238010;
    board->receiver_vtable = data_ov003_02238078;
    TouchPickSphere_Construct((TouchPickSphere *) board->member_138);
    return board;
}
CLEAN_AS(func_ov003_0220c29c, EtcBoard_Construct)

/* func_ov003_0220c2d4: allocates and constructs a board; nothing keeps the pointer here. */
void EtcBoard_New(void)
{
    EtcBoard *board = Heap_AllocAuxZeroed(sizeof(EtcBoard));
    if (board != NULL) {
        EtcBoard_Construct(board);
    }
}
CLEAN_AS(func_ov003_0220c2d4, EtcBoard_New)

/* The board a pointer to its receiver part belongs to. */
static EtcBoard *board_of(void *receiver)
{
    return (EtcBoard *) ((u8 *) receiver - offsetof(EtcBoard, receiver_vtable));
}

/* func_ov003_0220c2f0 (the receiver vtable's deleting destructor): EtcBoard_DestroyAndFree on
 * the board around `receiver`. */
EtcBoard *EtcBoard_ReceiverDestroyAndFree(void *receiver)
{
    return EtcBoard_DestroyAndFree(board_of(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov003_02238010D0Ev, EtcBoard_ReceiverDestroyAndFree)

/* func_ov003_0220c30c (the receiver vtable's destructor): EtcBoard_Destroy on the board
 * around `receiver`. */
EtcBoard *EtcBoard_ReceiverDestroy(void *receiver)
{
    return EtcBoard_Destroy(board_of(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov003_02238010D1Ev, EtcBoard_ReceiverDestroy)
