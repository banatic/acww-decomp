/* Quick messages of the multiplayer session (session.h): a process (profile data_020da598,
 * created by QuickMessage_Spawn, 0x35c bytes) that lets this system's player post one of six
 * fixed messages with a button and shows the messages of every system in up to four
 * balloons, one per slot, each with the player's name.
 *
 * The process has three parts, each a small class of its own:
 *   0x050  the sender (vtable data_020da5e8): each frame, while no message was posted in the
 *          last 30 frames (data_021c6730), a button pressed in one of four scenes posts
 *          message 0xf0-0xf4 or 0xef of the menu archive under this system's slot, with
 *          sound 0x32 (QuickMessage_PollButtons; QuickMessage_PostDefault posts 0xef);
 *   0x054  the board (vtable data_020da5d8, its address in data_021c6738): four balloons
 *          (0xb8 bytes each, at position (slot - this system's slot) mod 4, so position 0 is
 *          this system's own), the balloons waiting to be shown and the balloons shown;
 *   0x358  the receiver (vtable data_020da5c8): each frame the shared records 20-23 of the
 *          other slots are read, and a message found there is posted under its slot.
 *
 * A message posted under this system's slot is also written to its shared record 20 + slot
 * (func_020392a0, QuickMessage_WriteRecord), from which the others read it: one byte set while
 * the record holds a message not yet taken, then the name in 6 and the message in 16 16-bit
 * characters (data_021c675c, 46 bytes). */
#ifndef CLEAN_MAIN_QUICK_MESSAGE_H
#define CLEAN_MAIN_QUICK_MESSAGE_H

#include "types.h"

#define QUICK_MESSAGE_BALLOONS 4

/* A balloon (constructed by func_0203a23c, destroyed by func_0203a1f8). Its vtable's entry 2
 * draws it and entry 3 updates it. */
typedef struct QuickMessageBalloon {
    const void *vtable;
    u8 unk_04[8];
    s32 position; /* 0x0c: 0 for this system's own balloon */
    u8 unk_10[0x34];
    s32 stack_offset;  /* 0x44: 16 pixels for each other system's balloon shown above it */
    s32 placed_offset; /* 0x48: stack_offset when the balloon was placed */
    u8 unk_4c[8];
    u8 text[0x34];  /* 0x54: label: the message */
    u8 name[0x14];  /* 0x88: label: the player's name */
    void *boxes[2]; /* 0x9c: its two text boxes */
    /* 0xa4: when not 0, placing the balloon again sets unk_b0 to 0 (func_02039ebc); when 0,
     * placing it sets unk_b0 to 2 (func_02039edc). */
    s32 unk_a4;
    s32 unk_a8;
    s32 delay;  /* 0xac: while above 0 the balloon is not placed */
    s32 unk_b0; /* 0xb0: with unk_a4, both 0: the balloon is done and taken off the board */
    u8 unk_b4[4];
} QuickMessageBalloon;

typedef struct QuickMessageBoard {
    const void *vtable; /* data_020da5d8 */
    QuickMessageBalloon balloons[QUICK_MESSAGE_BALLOONS];
    QuickMessageBalloon *waiting[QUICK_MESSAGE_BALLOONS]; /* 0x2e4: to be placed, first ones first */
    QuickMessageBalloon *shown[QUICK_MESSAGE_BALLOONS];   /* 0x2f4: placed from the last entry down */
} QuickMessageBoard;

/* A part with nothing but its vtable. */
typedef struct QuickMessagePart {
    const void *vtable;
} QuickMessagePart;

typedef struct QuickMessageProcess {
    const void *vtable; /* data_020da674 */
    u8 process[0x4c];   /* the rest of the process (autoload_2/process.h) */
    QuickMessagePart sender;
    QuickMessageBoard board;
    QuickMessagePart receiver;
} QuickMessageProcess;

int QuickMessage_Delete(QuickMessageProcess *self);
int QuickMessage_Draw(QuickMessageProcess *self);
int QuickMessage_Execute(QuickMessageProcess *self);
int QuickMessage_Create(QuickMessageProcess *self);
QuickMessageProcess *QuickMessage_DestructFree(QuickMessageProcess *self);
QuickMessageProcess *QuickMessage_Destruct(QuickMessageProcess *self);
QuickMessageProcess *QuickMessage_Construct(QuickMessageProcess *self);
void QuickMessage_Spawn(void);
void QuickMessage_PollButtons(int unused);
void QuickMessage_SenderExecute(int sender);
void QuickMessage_SenderDelete(void *sender);
void QuickMessage_SenderCreate(void *sender);
QuickMessagePart *QuickMessage_SenderDestructDelete(QuickMessagePart *sender);
void QuickMessage_SenderDestruct(QuickMessagePart *sender);
void QuickMessage_SenderConstruct(QuickMessagePart *sender);
void QuickMessage_PostDefault(void);
void *QuickMessage_WriteRecordOf(u8 *record, int id, QuickMessageBalloon *balloon);
int QuickMessage_TakeRecord(int slot);
void QuickMessage_ReadRecords(void);
void QuickMessage_WriteRecord(int slot, QuickMessageBalloon *balloon);
void QuickMessage_ReceiverExecute(void *receiver);
void QuickMessage_ReceiverDelete(void *receiver);
void QuickMessage_ReceiverCreate(void *receiver);
QuickMessagePart *QuickMessage_ReceiverDestructDelete(QuickMessagePart *receiver);
void QuickMessage_ReceiverDestruct(QuickMessagePart *receiver);
void QuickMessage_ReceiverConstruct(QuickMessagePart *receiver);
void QuickMessage_ResetBoard(QuickMessageBoard *board);
void QuickMessage_RedrawShown(QuickMessageBoard *board);
void QuickMessage_DrawBoard(QuickMessageBoard *board);
void QuickMessage_UpdateBoard(QuickMessageBoard *board);
void QuickMessage_BoardDelete(QuickMessageBoard *board);
void QuickMessage_BoardCreate(QuickMessageBoard *board);
int QuickMessage_IsWaiting(QuickMessageBoard *board, int balloon);
void QuickMessage_DropFinished(QuickMessageBoard *board);
void QuickMessage_Restack(QuickMessageBoard *board);
void QuickMessage_PlaceWaiting(QuickMessageBoard *board);
int QuickMessage_PlaceBalloon(QuickMessageBoard *board, QuickMessageBalloon *balloon);

#endif
