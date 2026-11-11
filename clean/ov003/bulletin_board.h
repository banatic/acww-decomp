/* The town's bulletin board, an outdoor scene object of overlay 3 (class Obj_ov003_02238434,
 * vtable 0x02238434, receiver part 0x022384f8, 0x2b8 bytes) that opens the board's screen when
 * it is checked (group 9 in mode 0 is overlay group 11, ov113/bbs_board.h, which shows the
 * posts of main/bbs.h): its own state machine
 * (the word at 0x2b4) runs through tables of member pointers (ov004/member_pointer.h):
 *
 *   0 idle:    nothing happens; scene event 0 or 1 opens the screen (state 1).
 *   1 opening: entering it asks main to open group 9 in mode 0 (GroupParams_Open), and fails
 *              when main refuses; the next frame moves to state 2.
 *   2 open:    once main can open a screen again (GroupParams_CanOpen) it lets the scene go on
 *              (func_0203e020).
 *
 * Scene event 8 and vtable slot 0x70 make it idle. It is derived from overlay 9's town object actor
 * (Obj_ov009_022658dc), which runs the rest. */
#ifndef CLEAN_OV003_BULLETIN_BOARD_H
#define CLEAN_OV003_BULLETIN_BOARD_H

#include "types.h"

enum BulletinBoardState { BULLETIN_BOARD_IDLE, BULLETIN_BOARD_OPENING, BULLETIN_BOARD_OPEN, BULLETIN_BOARD_STATES };

typedef struct BulletinBoard {
    const void *vtable; /* data_ov003_02238434 */
    u8 unk_04[0x8e - 0x04];
    s16 yaw; /* the direction it faces */
    u8 unk_90[0xec - 0x90];
    const void *receiver_vtable; /* data_ov003_022384f8 */
    u8 unk_f0[0x235 - 0xf0];
    u8 flags_235; /* BulletinBoard_IsFacedBy needs bit 3 */
    u8 unk_236[0x2b4 - 0x236];
    int state; /* enum BulletinBoardState */
} BulletinBoard;

/* What BulletinBoard_IsFacedBy reads of the other actor. */
typedef struct BulletinBoardViewer {
    u8 unk_00[0x8e];
    s16 yaw;
} BulletinBoardViewer;

void BulletinBoard_UpdateOpen(BulletinBoard *object);
int BulletinBoard_EnterOpen(BulletinBoard *object);
void BulletinBoard_UpdateOpening(BulletinBoard *object);
int BulletinBoard_EnterOpening(BulletinBoard *object);
void BulletinBoard_UpdateIdle(void);
int BulletinBoard_EnterIdle(BulletinBoard *object);
void BulletinBoard_UpdateState(BulletinBoard *object);
int BulletinBoard_SetState(BulletinBoard *object, int state);
void BulletinBoard_OnSceneEvent(BulletinBoard *object, int event);
int BulletinBoard_IsFacedBy(BulletinBoard *object, BulletinBoardViewer *viewer);
int BulletinBoard_Slot0c(void);
int BulletinBoard_Slot24(void);
int BulletinBoard_Update(BulletinBoard *object);
int BulletinBoard_Reset(BulletinBoard *object);
BulletinBoard *BulletinBoard_Delete(BulletinBoard *object);
BulletinBoard *BulletinBoard_Destruct(BulletinBoard *object);
BulletinBoard *BulletinBoard_Construct(BulletinBoard *object);
void BulletinBoard_New(void);
BulletinBoard *BulletinBoard_ReceiverDelete(void *receiver);
BulletinBoard *BulletinBoard_ReceiverDestruct(void *receiver);

#endif
