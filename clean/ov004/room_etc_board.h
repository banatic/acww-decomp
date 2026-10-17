/* The "obj_etc_board" scene object of overlay 4 (class vtable 0x0225328c, receiver part
 * 0x022532f4, 0x15c bytes): the rooms' counterpart of overlay 3's board (ov003/etc_board.h).
 *
 * func_ov004_02231c7c makes one for each entry of a list of the room (RoomEtcBoard_Spawn):
 * where it stands, how far it can be talked to from and which message it shows. Up to 64 exist
 * at once: a table at data_ov004_02257804 holds them by their index (the byte at 0x154), with
 * their count at data_ov004_022577ac; main's pen picking reads it (touch pick kind 16,
 * TouchPick_RoomEntry40).
 *
 * Like the other scene objects it is a SceneObjectBase with a message receiver at 0xec. Its
 * update runs one of three states, chosen by the word at 0x134:
 *
 *   0 idle:    nothing happens; event 0 moves it to state 1.
 *   1 waiting: entering it takes the receiver, names it "obj_etc_board" with the board's
 *              message and asks the talk to open; it moves to state 2 once the talk is up.
 *   2 open:    once the talk has closed it releases the receiver and ends the event.
 *
 * Event 8 puts it back to state 0. */
#ifndef CLEAN_OV004_ROOM_ETC_BOARD_H
#define CLEAN_OV004_ROOM_ETC_BOARD_H

#include "main/scene_object_base.h" /* SceneObjectBase, MessageReceiver */
#include "main/touch_pick_shapes.h"
#include "types.h"

enum RoomEtcBoardState { ROOM_ETC_BOARD_IDLE, ROOM_ETC_BOARD_WAITING, ROOM_ETC_BOARD_OPEN, ROOM_ETC_BOARD_STATES };

#define ROOM_ETC_BOARD_MAX 64
/* RoomEtcBoard.index of a board that is in no entry of the table. */
#define ROOM_ETC_BOARD_NO_INDEX 0xff

typedef struct RoomEtcBoard {
    SceneObjectBase base;         /* 0x000: its vtable data_ov004_0225328c */
    MessageReceiver receiver;     /* 0x0ec: its vtable data_ov004_022532f4 */
    s32 state;                    /* 0x134: enum RoomEtcBoardState */
    TouchPickSphere touch_sphere; /* 0x138: where the pen picks it */
    u8 index;                     /* 0x154: its entry in the table, ROOM_ETC_BOARD_NO_INDEX for none */
    u8 unk_155;
    s16 message; /* 0x156: the message it shows (its low byte) */
    fx32 reach;  /* 0x158: the radius it is picked in, and added to how far it is talked to from */
} RoomEtcBoard;

void RoomEtcBoard_Spawn(Vec3 *position, fx32 reach, u16 yaw, u16 message);
RoomEtcBoard *RoomEtcBoard_Get(int index);
void RoomEtcBoard_UpdateOpen(RoomEtcBoard *board);
int RoomEtcBoard_EnterOpen(RoomEtcBoard *board);
void RoomEtcBoard_UpdateWaiting(RoomEtcBoard *board);
int RoomEtcBoard_EnterWaiting(RoomEtcBoard *board);
void RoomEtcBoard_UpdateIdle(RoomEtcBoard *board);
int RoomEtcBoard_EnterIdle(RoomEtcBoard *board);
void RoomEtcBoard_Update(RoomEtcBoard *board);
int RoomEtcBoard_SetState(RoomEtcBoard *board, int state);
void RoomEtcBoard_HandleEvent(RoomEtcBoard *board, int event);
int RoomEtcBoard_IsFacedBy(RoomEtcBoard *board, const SceneObjectBase *viewer);
int RoomEtcBoard_Unregister(RoomEtcBoard *board);
int RoomEtcBoard_Register(RoomEtcBoard *board);
void RoomEtcBoard_ClearTableIfEmpty(void);
int RoomEtcBoard_OnDelete(RoomEtcBoard *board);
int RoomEtcBoard_Draw(void);
int RoomEtcBoard_Execute(RoomEtcBoard *board);
int RoomEtcBoard_OnCreate(RoomEtcBoard *board);
RoomEtcBoard *RoomEtcBoard_Delete(RoomEtcBoard *board);
RoomEtcBoard *RoomEtcBoard_Destroy(RoomEtcBoard *board);
RoomEtcBoard *RoomEtcBoard_Construct(RoomEtcBoard *board);
void RoomEtcBoard_New(void);
RoomEtcBoard *RoomEtcBoardReceiver_Delete(void *receiver);
RoomEtcBoard *RoomEtcBoardReceiver_Destroy(void *receiver);

#endif
