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

#include "screen_icon.h" /* CellAnim */
#include "types.h"

#define QUICK_MESSAGE_BALLOONS 4

/* A balloon (constructed by func_0203a23c, destroyed by func_0203a1f8). Its vtable's entry 2
 * draws it and entry 3 updates it. */
typedef struct QuickMessageBalloon {
    const void *vtable;
    s32 x; /* 0x04: the sprite base's place (func_0208aef0, func_0208aeec) */
    s32 y;
    s32 position;      /* 0x0c: 0 for this system's own balloon */
    s32 palette;       /* 0x10: the slot's colour + 5 */
    s32 tag_anim;      /* 0x14: entry of data_020d5b3c for the name tag */
    s32 frame_anim;    /* 0x18: entry of data_020d5b3c for the balloon */
    CellAnim tag;      /* 0x1c: the name tag's frames, one for each width in tiles */
    CellAnim frame;    /* 0x30: the balloon's frames, one for each width in tiles */
    s32 stack_offset;  /* 0x44: 16 pixels for each other system's balloon shown above it */
    s32 placed_offset; /* 0x48: stack_offset when the balloon was placed */
    s32 bounce;        /* 0x4c: the vertical offset of the appearing and leaving moves */
    s32 base_y;        /* 0x50: QuickMessage_BalloonPlaceY */
    u8 text[0x34];     /* 0x54: label: the message */
    u8 name[0x14];     /* 0x88: label: the player's name */
    void *boxes[2];    /* 0x9c: its text boxes, QUICK_BALLOON_NAME_BOX and QUICK_BALLOON_TEXT_BOX */
    /* 0xa4: the state (QuickMessageBalloonState). When not 0, placing the balloon again sets
     * unk_b0 to 0 (func_02039ebc); when 0, placing it sets unk_b0 to 2 (func_02039edc). */
    s32 unk_a4;
    s32 timer;  /* 0xa8: frames left in the state */
    s32 delay;  /* 0xac: while above 0 the balloon is not placed */
    s32 unk_b0; /* 0xb0: with unk_a4, both 0: the balloon is done and taken off the board */
    u8 visible; /* 0xb4: drawn */
    u8 pad_b5[3];
} QuickMessageBalloon;

/* QuickMessageBalloon.boxes */
#define QUICK_BALLOON_NAME_BOX 0 /* the player's name, on the tag of another system's balloon */
#define QUICK_BALLOON_TEXT_BOX 1 /* the message */

/* QuickMessageBalloon.unk_a4. A placed balloon (unk_b0 set) appears, holds for 600 frames or
 * until it is posted again (unk_b0 cleared), leaves, and then waits `delay` frames. */
enum QuickMessageBalloonState {
    QUICK_BALLOON_IDLE = 0,
    QUICK_BALLOON_APPEARING = 1,
    QUICK_BALLOON_HOLDING = 2,
    QUICK_BALLOON_LEAVING = 3,
};

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

/* The text objects of quick_message.c. */
struct QuickMessageView;
struct QuickMessageWide;
struct QuickMessageName;
struct QuickMessageText;

int QuickMessage_QueueBalloon(QuickMessageBoard *board, QuickMessageBalloon *balloon);
void QuickMessage_DismissSlot(QuickMessageBoard *board, int slot);
int QuickMessage_SlotColor(int unused, int slot);
int QuickMessage_SlotPosition(int unused, int slot);
void QuickMessage_PostOn(QuickMessageBoard *board, int slot, void *name, void *text);
QuickMessageBoard *QuickMessage_BoardDestructDelete(QuickMessageBoard *board);
void *QuickMessage_BoardDestruct(QuickMessageBoard *board);
QuickMessageBoard *QuickMessage_BoardConstruct(QuickMessageBoard *board);
void QuickMessage_ResetCurrent(void);
void QuickMessage_RedrawCurrent(void);
int QuickMessage_OwnBalloonBusy(void);
int QuickMessage_OtherBalloonBusy(void);
void QuickMessage_DismissAll(void);
void QuickMessage_Dismiss(unsigned int slot);
void QuickMessage_Post(int slot, void *name, void *text);
void QuickMessage_BalloonFreeTextBox(QuickMessageBalloon *balloon);
void QuickMessage_BalloonOpenTextBox(QuickMessageBalloon *balloon);
void QuickMessage_BalloonFreeNameBox(QuickMessageBalloon *balloon);
void QuickMessage_BalloonOpenNameBox(QuickMessageBalloon *balloon);
void QuickMessage_BalloonFitFrames(QuickMessageBalloon *balloon);
void QuickMessage_BalloonLoadAnims(QuickMessageBalloon *balloon);
void QuickMessage_BalloonLeaving(QuickMessageBalloon *balloon);
void QuickMessage_BalloonStartLeaving(QuickMessageBalloon *balloon);
void QuickMessage_BalloonHolding(QuickMessageBalloon *balloon);
void QuickMessage_BalloonStartHolding(QuickMessageBalloon *balloon);
void QuickMessage_BalloonAppearing(QuickMessageBalloon *balloon);
void QuickMessage_BalloonStartAppearing(QuickMessageBalloon *balloon);
void QuickMessage_BalloonIdle(QuickMessageBalloon *balloon);
void QuickMessage_BalloonStop(QuickMessageBalloon *balloon);
void QuickMessage_BalloonReset(QuickMessageBalloon *balloon);
void QuickMessage_BalloonRedraw(QuickMessageBalloon *balloon);
int QuickMessage_BalloonRelease(QuickMessageBalloon *balloon);
int QuickMessage_BalloonRequest(QuickMessageBalloon *balloon);
void QuickMessage_BalloonSetup(QuickMessageBalloon *balloon, int position, int tag_anim, int frame_anim);
void QuickMessage_BalloonSetMessage(QuickMessageBalloon *balloon, void *name, void *text, int color);
void QuickMessage_BalloonPlaceY(QuickMessageBalloon *balloon);
void QuickMessage_BalloonUpdate(QuickMessageBalloon *balloon);
void QuickMessage_BalloonDraw(QuickMessageBalloon *balloon);
QuickMessageBalloon *QuickMessage_BalloonDestructDelete(QuickMessageBalloon *balloon);
QuickMessageBalloon *QuickMessage_BalloonDestruct(QuickMessageBalloon *balloon);
QuickMessageBalloon *QuickMessage_BalloonConstruct(QuickMessageBalloon *balloon);
int QuickMessage_ViewBuffer(struct QuickMessageView *view);
int QuickMessage_ViewCapacity(struct QuickMessageView *view);
struct QuickMessageView *QuickMessage_ViewDestructDelete(struct QuickMessageView *view);
void QuickMessage_ViewDestruct(struct QuickMessageView *view);
void QuickMessage_ViewConstruct(struct QuickMessageView *view, unsigned int chars, unsigned int count);
int QuickMessage_NameBuffer(int name);
int QuickMessage_NameCapacity(void);
struct QuickMessageName *QuickMessage_NameDestructDelete(struct QuickMessageName *name);
void QuickMessage_NameDestruct(struct QuickMessageName *name);
struct QuickMessageName *QuickMessage_NameConstruct(struct QuickMessageName *name);
int QuickMessage_WideBuffer(struct QuickMessageWide *wide);
int QuickMessage_WideCapacity(struct QuickMessageWide *wide);
struct QuickMessageWide *QuickMessage_WideDestructDelete(struct QuickMessageWide *wide);
struct QuickMessageWide *QuickMessage_WideDestruct(struct QuickMessageWide *wide);
struct QuickMessageWide *QuickMessage_WideConstruct(struct QuickMessageWide *wide, int chars, int count);
int QuickMessage_TextBuffer(int text);
int QuickMessage_TextCapacity(void);
struct QuickMessageText *QuickMessage_TextDestructDelete(struct QuickMessageText *text);
struct QuickMessageText *QuickMessage_TextDestruct(struct QuickMessageText *text);

#endif
