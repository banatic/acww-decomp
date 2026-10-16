/* The "obj_etc_board" scene object of overlay 3 (class vtable 0x02238010, 0x154 bytes).
 *
 * Up to eight exist at once, one per index 0-7 (the word at 0x08, which also picks the entry
 * of the table at 0x021e5a2c whose text it shows). A table at 0x0223c5f4 holds them by index,
 * with their count at 0x0223c5a0.
 *
 * Like the other scene objects it is a Base_0203f080 with a message receiver (Base_02066994)
 * at 0xec. Its update runs one of three states, chosen by the word at 0x134:
 *
 *   0 idle:    nothing happens; event 0 moves it to state 1.
 *   1 waiting: entering it names the receiver "obj_etc_board", fills the receiver's text from
 *              its table entry and raises the link's request; it moves to state 2 once the
 *              link reports itself open.
 *   2 open:    once the link closes it releases the receiver.
 *
 * Event 8 puts it back to state 0. */
#ifndef CLEAN_OV003_ETC_BOARD_H
#define CLEAN_OV003_ETC_BOARD_H

#include "autoload_2/approach.h" /* Vec3 */
#include "types.h"

/* What the receiver's link (Base_02066994's word at 0x40) points at. */
typedef struct EtcBoardLink {
    int unk_00;
    int open;      /* nonzero while what the request opened is up */
    int requested; /* set to 1 when the board enters state 1 */
} EtcBoardLink;

enum EtcBoardState { ETC_BOARD_IDLE, ETC_BOARD_WAITING, ETC_BOARD_OPEN, ETC_BOARD_STATES };

typedef struct EtcBoard {
    const void *vtable; /* data_ov003_02238010 */
    u8 unk_04[4];
    u32 index; /* 0-7 */
    u8 unk_0C[0x5c - 0x0c];
    Vec3 position;
    u8 unk_68[0xec - 0x68];
    /* The message receiver (Base_02066994) */
    const void *receiver_vtable; /* data_ov003_02238078 */
    char receiver_name[25];      /* written by func_020a8164 */
    u8 unk_109;
    u8 receiver_unk_1E; /* Base_02066994's byte at 0x1e */
    u8 unk_10B[0x12c - 0x10b];
    EtcBoardLink *link; /* Base_02066994's word at 0x40 */
    u8 unk_130[4];
    int state;        /* enum EtcBoardState */
    u8 member_138[4]; /* constructed by func_020b7f70, destroyed by func_020b7f60 */
    u8 unk_13C[0x154 - 0x13c];
} EtcBoard;

#define ETC_BOARD_MAX 8

/* What EtcBoard_IsFacedBy reads of the other actor. */
typedef struct EtcBoardViewer {
    u8 unk_00[0x5c];
    Vec3 position;
    u8 unk_68[0x8e - 0x68];
    s16 yaw; /* the direction it faces */
} EtcBoardViewer;

EtcBoard *EtcBoard_Get(int index);
void EtcBoard_UpdateOpen(EtcBoard *board);
int EtcBoard_EnterOpen(EtcBoard *board);
void EtcBoard_UpdateWaiting(EtcBoard *board);
int EtcBoard_EnterWaiting(EtcBoard *board);
void EtcBoard_UpdateIdle(EtcBoard *board);
int EtcBoard_EnterIdle(EtcBoard *board);
void EtcBoard_Update(EtcBoard *board);
int EtcBoard_SetState(EtcBoard *board, int state);
void EtcBoard_HandleEvent(EtcBoard *board, int event);
int EtcBoard_IsFacedBy(EtcBoard *board, const EtcBoardViewer *viewer);
void EtcBoard_ClearTableIfEmpty(void);
int EtcBoard_Unregister(EtcBoard *board);
int EtcBoard_Slot24(void);
int EtcBoard_Run(EtcBoard *board);
int EtcBoard_Init(EtcBoard *board);
EtcBoard *EtcBoard_DestroyAndFree(EtcBoard *board);
EtcBoard *EtcBoard_Destroy(EtcBoard *board);
EtcBoard *EtcBoard_Construct(EtcBoard *board);
void EtcBoard_New(void);
EtcBoard *EtcBoard_ReceiverDestroyAndFree(void *receiver);
EtcBoard *EtcBoard_ReceiverDestroy(void *receiver);

#endif
