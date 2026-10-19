/* The "obj_etc_board" scene object of the rooms (room_etc_board.h). */
#include "room_etc_board.h"

#include <stdint.h>

#include "autoload_2/approach.h" /* Math_AbsDiff16 */
#include "autoload_2/heap.h"
#include "autoload_2/vector.h"
#include "clean.h"
#include "main/actor.h"
#include "main/event_queue.h"
#include "main/scene_query.h"
#include "main/talk_flow.h"

static_assert(offsetof(RoomEtcBoard, receiver) == 0xec, "receiver");
static_assert(offsetof(RoomEtcBoard, receiver.base.message) == 0x10a, "receiver's message");
static_assert(offsetof(RoomEtcBoard, receiver.talk) == 0x12c, "receiver's talk");
static_assert(offsetof(RoomEtcBoard, state) == 0x134, "state");
static_assert(offsetof(RoomEtcBoard, touch_sphere) == 0x138, "touch sphere");
static_assert(offsetof(RoomEtcBoard, index) == 0x154, "index");
static_assert(offsetof(RoomEtcBoard, message) == 0x156, "message");
static_assert(offsetof(RoomEtcBoard, reach) == 0x158, "reach");
static_assert(sizeof(RoomEtcBoard) == 0x15c, "the size RoomEtcBoard_New allocates");

/* The profile (class id) Actor_Spawn makes a board from. */
#define ROOM_ETC_BOARD_PROFILE 0x17
/* The touch pick kind of the boards (TouchPick_RoomEntry40). */
#define ROOM_ETC_BOARD_TOUCH_KIND 16
/* How far beyond its reach a board can be talked to from, and how far from facing it (the
 * opposite of the board's own direction) the viewer may turn. */
#define ROOM_ETC_BOARD_TALK_DISTANCE 0x2ccd
#define ROOM_ETC_BOARD_TALK_ANGLE 0x1300
/* What a talk's next state is set to to open it (TalkObject.next_state). */
#define ROOM_ETC_BOARD_TALK_OPENING TALK_OBJECT_OPENING

/* The boards by index, and how many there are. */
extern RoomEtcBoard *data_ov004_02257804[ROOM_ETC_BOARD_MAX];
extern u8 data_ov004_022577ac;
/* What RoomEtcBoard_Spawn leaves for the board's constructor to read (RoomEtcBoard_OnCreate):
 * its message and its reach. */
extern s16 data_ov004_02253238;
extern fx32 data_ov004_022577d0;

/* The vtables: the class's, and its receiver part's. */
extern const u32 data_ov004_0225328c[];
extern const u8 data_ov004_022532f4[];
/* "obj_etc_board" */
extern const char data_ov004_0225336c[];

/* The receiver part of a board, as a C++ conversion makes it: null stays null. */
static TalkReceiver *receiver_of(RoomEtcBoard *board)
{
    return board != NULL ? &board->receiver : NULL;
}

/* func_ov004_0221ad0c: makes a board at `position`, turned `yaw` about the vertical axis, that
 * is picked within `reach` and shows `message`; the two are left for its constructor. */
void RoomEtcBoard_Spawn(Vec3 *position, fx32 reach, u16 yaw, u16 message)
{
    s16 angle[3];

    data_ov004_02253238 = (s16) message;
    data_ov004_022577d0 = reach;
    angle[0] = 0;
    angle[1] = (s16) yaw;
    angle[2] = 0;
    Actor_Spawn(ROOM_ETC_BOARD_PROFILE, 0, position, angle, NULL);
}
CLEAN_AS(func_ov004_0221ad0c, RoomEtcBoard_Spawn)

/* func_ov004_0221ad40: the board with `index`, or null when there is none or `index` is out of
 * 0-63. */
RoomEtcBoard *RoomEtcBoard_Get(int index)
{
    if (index >= 0 && index < ROOM_ETC_BOARD_MAX) {
        return data_ov004_02257804[index];
    }
    return NULL;
}
CLEAN_AS(func_ov004_0221ad40, RoomEtcBoard_Get)

/* func_ov004_0221ad58: state 2's update. Once the talk has closed, the receiver is released and
 * the event ends. */
void RoomEtcBoard_UpdateOpen(RoomEtcBoard *board)
{
    if (board->receiver.talk != NULL && board->receiver.talk->state == TALK_OBJECT_CLOSED) {
        SceneObjectBase_ReleaseReceiver(&board->base, receiver_of(board));
        EventQueue_FinishObjectEvent(board);
    }
}
CLEAN_AS(func_ov004_0221ad58, RoomEtcBoard_UpdateOpen)

/* func_ov004_0221ad88: entering state 2 always succeeds. */
int RoomEtcBoard_EnterOpen(RoomEtcBoard *board)
{
    (void) board;
    return 1;
}
CLEAN_AS(func_ov004_0221ad88, RoomEtcBoard_EnterOpen)

/* func_ov004_0221ad8c: state 1's update: on to state 2 once the talk is up. */
void RoomEtcBoard_UpdateWaiting(RoomEtcBoard *board)
{
    if (board->receiver.talk != NULL && board->receiver.talk->state != TALK_OBJECT_CLOSED) {
        RoomEtcBoard_SetState(board, ROOM_ETC_BOARD_OPEN);
    }
}
CLEAN_AS(func_ov004_0221ad8c, RoomEtcBoard_UpdateWaiting)

/* func_ov004_0221adb0: entering state 1 (always succeeds). The receiver is taken, named
 * "obj_etc_board" with the low byte of the board's message, and its talk asked to open.
 * REQUIRES: the receiver has a talk (the scene that sent event 0 gave it one). */
int RoomEtcBoard_EnterWaiting(RoomEtcBoard *board)
{
    SceneObjectBase_TakeReceiver(&board->base, receiver_of(board));
    MessageReceiver_SetName(&board->receiver.base, data_ov004_0225336c);
    board->receiver.base.message = (u8) board->message;
    board->receiver.talk->next_state = ROOM_ETC_BOARD_TALK_OPENING;
    return 1;
}
CLEAN_AS(func_ov004_0221adb0, RoomEtcBoard_EnterWaiting)

/* func_ov004_0221adf8: state 0's update does nothing. */
void RoomEtcBoard_UpdateIdle(RoomEtcBoard *board)
{
    (void) board;
}
CLEAN_AS(func_ov004_0221adf8, RoomEtcBoard_UpdateIdle)

/* func_ov004_0221adfc: entering state 0 always succeeds. */
int RoomEtcBoard_EnterIdle(RoomEtcBoard *board)
{
    (void) board;
    return 1;
}
CLEAN_AS(func_ov004_0221adfc, RoomEtcBoard_EnterIdle)

/* func_ov004_0221ae00: the update of the current state (the ROM picks it from a table of member
 * function pointers). REQUIRES: the state is 0-2, as RoomEtcBoard_SetState leaves it; the ROM
 * reads before its table for a negative one, while this does nothing. */
void RoomEtcBoard_Update(RoomEtcBoard *board)
{
    switch (board->state) {
        case ROOM_ETC_BOARD_IDLE:
            RoomEtcBoard_UpdateIdle(board);
            break;
        case ROOM_ETC_BOARD_WAITING:
            RoomEtcBoard_UpdateWaiting(board);
            break;
        case ROOM_ETC_BOARD_OPEN:
            RoomEtcBoard_UpdateOpen(board);
            break;
        default:
            break;
    }
}
CLEAN_AS(_ZN18Obj_ov004_0225328c19func_ov004_0221ae00Ev, RoomEtcBoard_Update)

/* func_ov004_0221ae7c: moves to `state` when entering it succeeds; whether it did.
 * REQUIRES: `state` is not negative (the callers pass 0-2); the ROM reads before its table of
 * entry functions for a negative one, while this refuses it. */
int RoomEtcBoard_SetState(RoomEtcBoard *board, int state)
{
    int entered;

    switch (state) {
        case ROOM_ETC_BOARD_IDLE:
            entered = RoomEtcBoard_EnterIdle(board);
            break;
        case ROOM_ETC_BOARD_WAITING:
            entered = RoomEtcBoard_EnterWaiting(board);
            break;
        case ROOM_ETC_BOARD_OPEN:
            entered = RoomEtcBoard_EnterOpen(board);
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
CLEAN_AS(func_ov004_0221ae7c, RoomEtcBoard_SetState)

/* func_ov004_0221af08 (vtable slot 0x4c): event 0 starts the board (state 1), event 8 stops it
 * (state 0); other events are ignored. */
void RoomEtcBoard_HandleEvent(RoomEtcBoard *board, int event)
{
    switch (event) {
        case 0:
            RoomEtcBoard_SetState(board, ROOM_ETC_BOARD_WAITING);
            break;
        case 8:
            RoomEtcBoard_SetState(board, ROOM_ETC_BOARD_IDLE);
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov004_0221af08, RoomEtcBoard_HandleEvent)

/* func_ov004_0221af2c (vtable slot 0x48): whether `viewer` stands closer than the board's reach
 * plus 0x2ccd and faces it: its direction less than 0x1300 from the board's own turned half a
 * turn. */
int RoomEtcBoard_IsFacedBy(RoomEtcBoard *board, const SceneObjectBase *viewer)
{
    fx32 distance = board->reach + ROOM_ETC_BOARD_TALK_DISTANCE;

    return viewer != NULL && Vec_DistanceXZ(&viewer->position, &board->base.position) < distance &&
           Math_AbsDiff16((s16) (board->base.yaw + 0x8000), viewer->yaw) < ROOM_ETC_BOARD_TALK_ANGLE;
}
CLEAN_AS(func_ov004_0221af2c, RoomEtcBoard_IsFacedBy)

/* func_ov004_0221af84: takes the board out of the table; whether it was in it.
 * QUIRK: the count is a byte and wraps below 0. */
int RoomEtcBoard_Unregister(RoomEtcBoard *board)
{
    if (board->index < ROOM_ETC_BOARD_MAX) {
        data_ov004_02257804[board->index] = NULL;
        data_ov004_022577ac--;
        board->index = ROOM_ETC_BOARD_NO_INDEX;
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov004_0221af84, RoomEtcBoard_Unregister)

/* func_ov004_0221afb8: enters the board in the table under the next index (the count); whether
 * there was room. The index is kept even when there was not. */
int RoomEtcBoard_Register(RoomEtcBoard *board)
{
    board->index = data_ov004_022577ac;
    if (board->index < ROOM_ETC_BOARD_MAX) {
        data_ov004_02257804[board->index] = board;
        data_ov004_022577ac++;
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov004_0221afb8, RoomEtcBoard_Register)

/* func_ov004_0221afe8: empties the table when no board is counted in it. */
void RoomEtcBoard_ClearTableIfEmpty(void)
{
    if (data_ov004_022577ac != 0) {
        return;
    }
    for (int i = 0; i < ROOM_ETC_BOARD_MAX; i++) {
        data_ov004_02257804[i] = NULL;
    }
}
CLEAN_AS(func_ov004_0221afe8, RoomEtcBoard_ClearTableIfEmpty)

/* func_ov004_0221b00c (vtable slot 0x0c, the deletion's work): takes the board out of the
 * table; done at once. */
int RoomEtcBoard_OnDelete(RoomEtcBoard *board)
{
    RoomEtcBoard_Unregister(board);
    return 1;
}
CLEAN_AS(func_ov004_0221b00c, RoomEtcBoard_OnDelete)

/* func_ov004_0221b01c (vtable slot 0x24, the drawing): nothing to draw; done. */
int RoomEtcBoard_Draw(void)
{
    return 1;
}
CLEAN_AS(func_ov004_0221b01c, RoomEtcBoard_Draw)

/* func_ov004_0221b020 (vtable slot 0x18, each frame): the state's update, then the board's
 * sphere of radius `reach` at its position put in the field's pen picking (kind 16, its index);
 * always 1. */
int RoomEtcBoard_Execute(RoomEtcBoard *board)
{
    RoomEtcBoard_Update(board);
    TouchPick_SetSphereAndAdd((TouchPick *) (intptr_t) SceneQuery_FieldObject(), &board->touch_sphere, &board->base.position,
                              board->reach, ROOM_ETC_BOARD_TOUCH_KIND, board->index);
    return 1;
}
CLEAN_AS(_ZN18Obj_ov004_0225328c19func_ov004_0221b020Ev, RoomEtcBoard_Execute)

/* func_ov004_0221b060 (vtable slot 0x00, the creation's work): takes the message and reach
 * RoomEtcBoard_Spawn left, enters the board in the table (emptying it first when it holds none),
 * registers it under its index and the current scene and starts it idle. Fails when the table
 * is full. */
int RoomEtcBoard_OnCreate(RoomEtcBoard *board)
{
    RoomEtcBoard_ClearTableIfEmpty();
    board->message = data_ov004_02253238;
    board->reach = data_ov004_022577d0;
    if (RoomEtcBoard_Register(board)) {
        SceneObjectBase_SetId(&board->base, (u16) (board->index | SceneQuery_Current() << 8));
        RoomEtcBoard_SetState(board, ROOM_ETC_BOARD_IDLE);
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov004_0221b060, RoomEtcBoard_OnCreate)

static void set_vtables(RoomEtcBoard *board)
{
    board->base.process.vtable = data_ov004_0225328c;
    board->receiver.base.vtable = data_ov004_022532f4;
}

/* func_ov004_0221b0c4: the deleting destructor: the sphere, the receiver part and the base
 * destroyed in turn, then the memory freed. */
RoomEtcBoard *RoomEtcBoard_Delete(RoomEtcBoard *board)
{
    set_vtables(board);
    TouchPickSphere_Destruct2(&board->touch_sphere);
    TalkReceiver_Destruct(&board->receiver);
    SceneObjectBase_DestructBase(&board->base);
    Heap_FreeAux(board);
    return board;
}
CLEAN_AS(func_ov004_0221b0c4, RoomEtcBoard_Delete)

/* func_ov004_0221b104: the destructor, without freeing. */
RoomEtcBoard *RoomEtcBoard_Destroy(RoomEtcBoard *board)
{
    set_vtables(board);
    TouchPickSphere_Destruct2(&board->touch_sphere);
    TalkReceiver_Destruct(&board->receiver);
    SceneObjectBase_DestructBase(&board->base);
    return board;
}
CLEAN_AS(func_ov004_0221b104, RoomEtcBoard_Destroy)

/* func_ov004_0221b140: the constructor: the base and the receiver part, then the vtables and
 * the sphere. The board's own fields are left as the allocation zeroed them. */
RoomEtcBoard *RoomEtcBoard_Construct(RoomEtcBoard *board)
{
    SceneObjectBase_Construct(&board->base);
    TalkReceiver_ConstructBase(&board->receiver);
    set_vtables(board);
    TouchPickSphere_Construct(&board->touch_sphere);
    return board;
}
CLEAN_AS(func_ov004_0221b140, RoomEtcBoard_Construct)

/* func_ov004_0221b178: allocates (zeroed) and constructs a board; nothing keeps the pointer
 * here. */
void RoomEtcBoard_New(void)
{
    RoomEtcBoard *board = Heap_AllocAuxZeroed(sizeof(RoomEtcBoard));
    if (board != NULL) {
        RoomEtcBoard_Construct(board);
    }
}
CLEAN_AS(func_ov004_0221b178, RoomEtcBoard_New)

/* The board a pointer to its receiver part belongs to. */
static RoomEtcBoard *board_of(void *receiver)
{
    return (RoomEtcBoard *) (void *) ((u8 *) receiver - offsetof(RoomEtcBoard, receiver));
}

/* func_ov004_0221b194 (the receiver vtable's deleting destructor): RoomEtcBoard_Delete on the
 * board around `receiver`. */
RoomEtcBoard *RoomEtcBoardReceiver_Delete(void *receiver)
{
    return RoomEtcBoard_Delete(board_of(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov004_0225328cD0Ev, RoomEtcBoardReceiver_Delete)

/* func_ov004_0221b1b0 (the receiver vtable's destructor): RoomEtcBoard_Destroy on the board
 * around `receiver`. */
RoomEtcBoard *RoomEtcBoardReceiver_Destroy(void *receiver)
{
    return RoomEtcBoard_Destroy(board_of(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov004_0225328cD1Ev, RoomEtcBoardReceiver_Destroy)
