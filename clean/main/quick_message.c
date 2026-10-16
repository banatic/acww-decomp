/* Quick messages of the multiplayer session (quick_message.h). */
#include "quick_message.h"

#include "a_mes_obj.h"        /* AMesObj_IsReady */
#include "autoload_2/heap.h"  /* Heap_AllocAuxZeroed, Heap_FreeAux */
#include "autoload_2/input.h" /* PadState */
#include "clean.h"
#include "main/session.h"   /* Session_IsLinked, Session_IsSlotTaken, Session_GetRecord */
#include "session_record.h" /* SessionRecord_Update, SessionRecord_GetSize */
#include "sound.h"          /* SoundSys_PlaySe */
#include "text_string.h"    /* TextString_ClearWide, TextString_BytesToWide, ... */

static_assert(offsetof(QuickMessageBalloon, position) == 0x0c, "balloon position");
static_assert(offsetof(QuickMessageBalloon, stack_offset) == 0x44, "balloon offset");
static_assert(offsetof(QuickMessageBalloon, text) == 0x54, "balloon text");
static_assert(offsetof(QuickMessageBalloon, name) == 0x88, "balloon name");
static_assert(offsetof(QuickMessageBalloon, unk_a4) == 0xa4, "balloon a4");
static_assert(offsetof(QuickMessageBalloon, delay) == 0xac, "balloon delay");
static_assert(sizeof(QuickMessageBalloon) == 0xb8, "balloon size");
static_assert(offsetof(QuickMessageBoard, waiting) == 0x2e4, "waiting balloons");
static_assert(offsetof(QuickMessageBoard, shown) == 0x2f4, "shown balloons");
static_assert(offsetof(QuickMessageProcess, sender) == 0x50, "sender");
static_assert(offsetof(QuickMessageProcess, board) == 0x54, "board");
static_assert(offsetof(QuickMessageProcess, receiver) == 0x358, "receiver");
static_assert(sizeof(QuickMessageProcess) == 0x35c, "process size");

#define PAD_A 0x0001
#define PAD_B 0x0002
#define PAD_SELECT 0x0004
#define PAD_START 0x0008
#define PAD_X 0x0400
#define PAD_Y 0x0800

/* The messages of the menu archive a button posts. */
#define QUICK_MESSAGE_START 0xef /* START, or QuickMessage_PostDefault */
#define QUICK_MESSAGE_SELECT 0xf0
#define QUICK_MESSAGE_X 0xf1
#define QUICK_MESSAGE_Y 0xf2
#define QUICK_MESSAGE_A 0xf3
#define QUICK_MESSAGE_B 0xf4

#define QUICK_MESSAGE_SOUND 0x32
#define QUICK_MESSAGE_COOLDOWN 30 /* frames after a post before the next one */
#define QUICK_MESSAGE_FIRST_RECORD 20
#define QUICK_MESSAGE_RECORD_SIZE 0x2e
#define QUICK_MESSAGE_NAME_CHARS 6
#define QUICK_MESSAGE_TEXT_CHARS 16
#define QUICK_MESSAGE_LINE_HEIGHT 0x10

/* Vtable entries of a balloon. */
#define BALLOON_DRAW 2
#define BALLOON_UPDATE 3

/* The vtables: the process's, its base class's, the parts' and the board's. */
extern const u8 data_020da674[];
extern const u8 data_020da13c[];
extern const u8 data_020da5e8[];
extern const u8 data_020da5c8[];

/* The session, this system's pad, and the frames left before another post. */
extern NetSession *data_020ccf94;
extern PadState data_021fbe40;
extern int data_021c6730;
/* The board while the process is created. */
extern QuickMessageBoard *data_021c6738;
/* A quick message record (quick_message.h): its flag byte, the name, the message. */
extern u8 data_021c675c[];
extern u16 data_021c675e[];
extern u16 data_021c676a[];
/* One 0 byte, copied over a record's flag once its message is taken. */
extern const u8 data_020ca154[];
/* The two animations of each balloon position. */
extern const int data_020ca134[QUICK_MESSAGE_BALLOONS];
extern const int data_020ca144[QUICK_MESSAGE_BALLOONS];

/* The process base: constructed, destroyed. operator delete. */
extern void *func_020ee660(void *process);
extern void func_020ee62c(void *process);
extern void func_020edb3c(void *block);
/* The board's constructor and destructor (they construct and destroy the four balloons). */
extern void *func_020397a0(QuickMessageBoard *board);
extern void *func_0203977c(QuickMessageBoard *board);

/* Text objects on the stack:
 *   a view of 16-bit characters elsewhere (vtable data_020da610; func_0203a2f0 constructs,
 *   func_0203a2dc destroys), 0xc bytes;
 *   a wide text over 16-bit characters elsewhere (vtable data_020da628; func_0203a3a4,
 *   func_0203a38c), 0x18 bytes;
 *   a 14-byte label (vtable data_020da5f8; func_0203a344 constructs it empty, func_0203a330),
 *   0x14 bytes, the type of a balloon's name;
 *   a label (vtable data_020da640; func_0203a404 constructs it empty, func_0203a3ec), 0x34
 *   bytes, the type of a balloon's message;
 *   a player's name (func_02094fd4, func_02094fbc), 0x20 bytes. */
typedef struct QuickMessageView {
    u32 words[3];
} QuickMessageView;
typedef struct QuickMessageWide {
    u32 words[6];
} QuickMessageWide;
typedef struct QuickMessageName {
    u32 words[5];
} QuickMessageName;
typedef struct QuickMessageText {
    u32 words[13];
} QuickMessageText;
typedef struct QuickMessagePlayerName {
    u32 words[8];
} QuickMessagePlayerName;

extern void func_0203a2f0(QuickMessageView *view, u16 *chars, int count);
extern void func_0203a2dc(QuickMessageView *view);
extern void *func_0203a3a4(QuickMessageWide *wide, u16 *chars, int count);
extern void *func_0203a38c(QuickMessageWide *wide);
extern void *func_0203a344(QuickMessageName *label);
extern void func_0203a330(QuickMessageName *label);
extern void *func_0203a404(QuickMessageText *label);
extern void *func_0203a3ec(QuickMessageText *label);
extern void *func_02094fd4(QuickMessagePlayerName *name);
extern void *func_02094fbc(QuickMessagePlayerName *name);

/* Label to wide text and back (text_label.h). Message `*number` of the menu archive loaded into
 * a label. */
extern int func_020a87e0(void *wide, void *label);
extern int func_020a8a70(void *label, void *wide, int escape_newlines, int end_code);
extern int func_020b4980(void *label, u8 *number, int table);

/* The current player's record, its player, and that player's name copied to a name. */
extern int func_020984e8(void);
extern int func_02099870(int record);
extern void *func_02095074(int player, QuickMessagePlayerName *name);

/* What func_02096718(4) holds at 0x7f0 (0x93 without it): a scene number. */
extern int func_020960d8(int which);
/* Whether data_021c72b8 is set. */
extern int func_0203ec98(void);
/* The scene. */
extern u8 func_020b65c4(void);

/* A message shown in the balloon of `slot`, with a name and a message label. */
extern void func_020398e8(int slot, void *name, void *text);

/* A balloon: reset; given its position and animations; its boxes asked to redraw; its x
 * placed; its state restarted when shown again or started when placed. */
extern void func_02039e44(QuickMessageBalloon *balloon);
extern void func_02039efc(QuickMessageBalloon *balloon, int position, int animation_a, int animation_b);
extern void func_02039e84(QuickMessageBalloon *balloon);
extern void func_02039f30(QuickMessageBalloon *balloon);
extern int func_02039ebc(QuickMessageBalloon *balloon);
extern int func_02039edc(QuickMessageBalloon *balloon);
/* Whether a balloon is among the board's shown ones (slots.h). */
extern int func_02039444(QuickMessageBoard *board, QuickMessageBalloon *balloon);

extern void MI_CpuCopy8(const void *src, void *dst, u32 size);

/* Entry `slot` of a balloon's vtable called on it. */
static void balloon_call(QuickMessageBalloon *balloon, int slot)
{
    typedef void BalloonMethod(QuickMessageBalloon * balloon);
    u32 method = ((const u32 *) balloon->vtable)[slot];
    ((BalloonMethod *) (uintptr_t) method)(balloon);
}

/* The entries from `entries[0]` on moved down over the empty ones, keeping their order. */
static void compact(QuickMessageBalloon **entries)
{
    for (int i = 0; i < QUICK_MESSAGE_BALLOONS; i++) {
        if (entries[i] != NULL) {
            continue;
        }
        for (int j = i + 1; j < QUICK_MESSAGE_BALLOONS; j++) {
            if (entries[j] != NULL) {
                entries[i] = entries[j];
                entries[j] = NULL;
                break;
            }
        }
    }
}

/* ---- The process */

/* func_02038d74 (vtable slot 3): the parts told of the deletion; done at once. */
int QuickMessage_Delete(QuickMessageProcess *self)
{
    QuickMessage_ReceiverDelete(&self->receiver);
    QuickMessage_BoardDelete(&self->board);
    QuickMessage_SenderDelete(&self->sender);
    return 1;
}
CLEAN_AS(func_02038d74, QuickMessage_Delete)

/* func_02038d9c (vtable slot 9): the board drawn while func_02011ec8 allows it. */
int QuickMessage_Draw(QuickMessageProcess *self)
{
    if (AMesObj_IsReady() != 0) {
        QuickMessage_DrawBoard(&self->board);
    }
    return 1;
}
CLEAN_AS(func_02038d9c, QuickMessage_Draw)

/* func_02038db8 (vtable slot 6): the sender polled, the board updated while func_02011ec8
 * allows it, the records read. */
int QuickMessage_Execute(QuickMessageProcess *self)
{
    QuickMessage_SenderExecute((int) (uintptr_t) &self->sender);
    if (AMesObj_IsReady() != 0) {
        QuickMessage_UpdateBoard(&self->board);
    }
    QuickMessage_ReceiverExecute(&self->receiver);
    return 1;
}
CLEAN_AS(func_02038db8, QuickMessage_Execute)

/* func_02038de8 (vtable slot 0): the parts created; done at once. */
int QuickMessage_Create(QuickMessageProcess *self)
{
    QuickMessage_SenderCreate(&self->sender);
    QuickMessage_BoardCreate(&self->board);
    QuickMessage_ReceiverCreate(&self->receiver);
    return 1;
}
CLEAN_AS(func_02038de8, QuickMessage_Create)

/* func_02038e10 (vtable slot 17): the destructor, and the object freed to the heap processes
 * come from. */
QuickMessageProcess *QuickMessage_DestructFree(QuickMessageProcess *self)
{
    QuickMessage_Destruct(self);
    Heap_FreeAux(self);
    return self;
}
CLEAN_AS(func_02038e10, QuickMessage_DestructFree)

/* func_02038e54 (vtable slot 16): the parts destroyed, last first, then the bases. */
QuickMessageProcess *QuickMessage_Destruct(QuickMessageProcess *self)
{
    self->vtable = data_020da674;
    QuickMessage_ReceiverDestruct(&self->receiver);
    func_0203977c(&self->board);
    QuickMessage_SenderDestruct(&self->sender);
    self->vtable = data_020da13c;
    func_020ee62c(self);
    return self;
}
CLEAN_AS(func_02038e54, QuickMessage_Destruct)

/* func_02038e94: the constructor. */
QuickMessageProcess *QuickMessage_Construct(QuickMessageProcess *self)
{
    func_020ee660(self);
    self->vtable = data_020da13c;
    self->vtable = data_020da674;
    QuickMessage_SenderConstruct(&self->sender);
    func_020397a0(&self->board);
    QuickMessage_ReceiverConstruct(&self->receiver);
    return self;
}
CLEAN_AS(func_02038e94, QuickMessage_Construct)

/* func_02038ed0: the profile's create: the process allocated zeroed and constructed.
 * QUIRK: declared without a result, as its matching source is; the ROM's code leaves the new
 * process (or NULL) in r0, the register a profile's create returns it in. */
void QuickMessage_Spawn(void)
{
    QuickMessageProcess *self = Heap_AllocAuxZeroed(sizeof(QuickMessageProcess));
    if (self != NULL) {
        QuickMessage_Construct(self);
    }
}
CLEAN_AS(func_02038ed0, QuickMessage_Spawn)

/* ---- The sender */

/* func_02038eec: with no post in the last 30 frames, in scene 0x28, 0x2b, 8 or 9
 * (func_020960d8(4)), while linked and data_021c72b8 is clear, a button pressed this frame
 * posts its message under this system's slot: SELECT, X, Y, A, B in that order of priority,
 * else START, which only the system in slot 0 posts. */
void QuickMessage_PollButtons(int unused)
{
    (void) unused;
    int scene = func_020960d8(4);
    int in_scene = scene == 0x28 || scene == 0x2b || scene == 8 || scene == 9;

    u16 pressed = data_021fbe40.pressed;
    int any = (pressed & (PAD_START | PAD_SELECT | PAD_X | PAD_Y | PAD_A | PAD_B)) != 0;

    NetSession *session = data_020ccf94;
    int linked = Session_IsLinked(session);
    int idle = func_0203ec98() == 0;

    if (data_021c6730 > 0) {
        return;
    }
    if (!in_scene || !any || !linked || !idle) {
        return;
    }

    QuickMessageText text;
    func_0203a404(&text);

    u8 number;
    int post = 1;
    if ((pressed & PAD_SELECT) != 0) {
        number = QUICK_MESSAGE_SELECT;
    } else if ((pressed & PAD_X) != 0) {
        number = QUICK_MESSAGE_X;
    } else if ((pressed & PAD_Y) != 0) {
        number = QUICK_MESSAGE_Y;
    } else if ((pressed & PAD_A) != 0) {
        number = QUICK_MESSAGE_A;
    } else if ((pressed & PAD_B) != 0) {
        number = QUICK_MESSAGE_B;
    } else {
        number = QUICK_MESSAGE_START;
        post = session->local_slot == 0;
    }

    if (post) {
        func_020b4980(&text, &number, 0);
        QuickMessagePlayerName name;
        func_02094fd4(&name);
        func_02095074(func_02099870(func_020984e8()), &name);
        func_020398e8(session->local_slot, &name, &text);
        SoundSys_PlaySe(QUICK_MESSAGE_SOUND);
        data_021c6730 = QUICK_MESSAGE_COOLDOWN;
        func_02094fbc(&name);
    }
    func_0203a3ec(&text);
}
CLEAN_AS(func_02038eec, QuickMessage_PollButtons)

/* func_02039064 (the sender's execute; `sender` is its address): the cooldown counted down, the
 * buttons polled. */
void QuickMessage_SenderExecute(int sender)
{
    if (data_021c6730 > 0) {
        data_021c6730--;
    }
    QuickMessage_PollButtons(sender);
}
CLEAN_AS(func_02039064, QuickMessage_SenderExecute)

/* func_0203907c: the sender has nothing to do on deletion. */
void QuickMessage_SenderDelete(void *sender)
{
    (void) sender;
}
CLEAN_AS(func_0203907c, QuickMessage_SenderDelete)

/* func_02039080: nor on creation. */
void QuickMessage_SenderCreate(void *sender)
{
    (void) sender;
}
CLEAN_AS(func_02039080, QuickMessage_SenderCreate)

/* func_02039084 (the sender's vtable entry 1) */
QuickMessagePart *QuickMessage_SenderDestructDelete(QuickMessagePart *sender)
{
    sender->vtable = data_020da5e8;
    func_020edb3c(sender);
    return sender;
}
CLEAN_AS(func_02039084, QuickMessage_SenderDestructDelete)

/* func_0203909c (the sender's vtable entry 0) */
void QuickMessage_SenderDestruct(QuickMessagePart *sender)
{
    sender->vtable = data_020da5e8;
}
CLEAN_AS(func_0203909c, QuickMessage_SenderDestruct)

/* func_020390a8 */
void QuickMessage_SenderConstruct(QuickMessagePart *sender)
{
    sender->vtable = data_020da5e8;
}
CLEAN_AS(func_020390a8, QuickMessage_SenderConstruct)

/* func_020390b4: message 0xef posted under this system's slot, unless a post was made in the
 * last 30 frames or there is no current player. */
void QuickMessage_PostDefault(void)
{
    int record = func_020984e8();
    if (data_021c6730 > 0 || record == 0) {
        return;
    }

    QuickMessagePlayerName name;
    QuickMessageText text;
    func_02094fd4(&name);
    func_0203a404(&text);
    func_02095074(func_02099870(record), &name);
    u8 number = QUICK_MESSAGE_START;
    func_020b4980(&text, &number, 0);
    func_020398e8(data_020ccf94->local_slot, &name, &text);
    SoundSys_PlaySe(QUICK_MESSAGE_SOUND);
    data_021c6730 = QUICK_MESSAGE_COOLDOWN;
    func_0203a3ec(&text);
    func_02094fbc(&name);
}
CLEAN_AS(func_020390b4, QuickMessage_PostDefault)

/* ---- The records */

/* func_02039128: the writer of records 20-23: the balloon's name and message written to the
 * record, flagged as holding a message.
 * QUIRK: returns what the wide text's destructor returns, the address of that temporary on
 * this function's stack; the writers ignore it. */
void *QuickMessage_WriteRecordOf(u8 *record, int id, QuickMessageBalloon *balloon)
{
    QuickMessageWide text;
    QuickMessageView name;
    func_0203a3a4(&text, data_021c676a, QUICK_MESSAGE_TEXT_CHARS);
    func_0203a2f0(&name, data_021c675e, QUICK_MESSAGE_NAME_CHARS);
    TextString_ClearWide((TextObject *) &text);
    TextString_ClearWide((TextObject *) &name);
    func_020a87e0(&text, balloon->text);
    TextString_BytesToWide((TextObject *) &name, (TextObject *) balloon->name);
    data_021c675c[0] = 1;
    MI_CpuCopy8(data_021c675c, record, SessionRecord_GetSize((u32) id));
    func_0203a2dc(&name);
    return func_0203a38c(&text);
}
CLEAN_AS(func_02039128, QuickMessage_WriteRecordOf)

/* func_0203919c: whether slot `slot`'s record holds a message to show. One that does is copied
 * to data_021c675c, unless the scene is 0x0c-0x0e, 0x2e or 0x2f, where it is dropped; either
 * way the record's flag is cleared. */
int QuickMessage_TakeRecord(int slot)
{
    u8 *record = Session_GetRecord(data_020ccf94, slot + QUICK_MESSAGE_FIRST_RECORD);
    u8 present = record[0];
    if (present != 0) {
        int scene = func_020b65c4();
        if (scene == 0x2e || scene == 0x0c || scene == 0x0d || scene == 0x0e || scene == 0x2f) {
            present = 0;
        } else {
            MI_CpuCopy8(record, data_021c675c, QUICK_MESSAGE_RECORD_SIZE);
        }
        MI_CpuCopy8(data_020ca154, record, 1);
    }
    return present;
}
CLEAN_AS(func_0203919c, QuickMessage_TakeRecord)

/* func_020391fc: while linked, the message in each other taken slot's record shown in its
 * balloon. */
void QuickMessage_ReadRecords(void)
{
    NetSession *session = data_020ccf94;
    int own = session->local_slot;
    if (!Session_IsLinked(session)) {
        return;
    }
    for (int slot = 0; slot < QUICK_MESSAGE_BALLOONS; slot++) {
        if (slot == own || !Session_IsSlotTaken(session, slot) || !QuickMessage_TakeRecord(slot)) {
            continue;
        }
        QuickMessageView name_chars;
        QuickMessageWide text_chars;
        QuickMessageName name;
        QuickMessageText text;
        func_0203a2f0(&name_chars, data_021c675e, QUICK_MESSAGE_NAME_CHARS);
        func_0203a3a4(&text_chars, data_021c676a, QUICK_MESSAGE_TEXT_CHARS);
        func_0203a344(&name);
        func_0203a404(&text);
        TextString_WideToBytes((TextObject *) &name, (TextObject *) &name_chars);
        func_020a8a70(&text, &text_chars, 0, 0);
        func_020398e8(slot, &name, &text);
        func_0203a3ec(&text);
        func_0203a330(&name);
        func_0203a38c(&text_chars);
        func_0203a2dc(&name_chars);
    }
}
CLEAN_AS(func_020391fc, QuickMessage_ReadRecords)

/* func_020392a0: the balloon written to slot `slot`'s record and sent, when the slot is taken in
 * a linked session. */
void QuickMessage_WriteRecord(int slot, QuickMessageBalloon *balloon)
{
    if (slot >= QUICK_MESSAGE_BALLOONS) {
        return;
    }
    NetSession *session = data_020ccf94;
    if (Session_IsLinked(session) && Session_IsSlotTaken(session, slot)) {
        SessionRecord_Update(slot + QUICK_MESSAGE_FIRST_RECORD, balloon, 0, 1);
    }
}
CLEAN_AS(func_020392a0, QuickMessage_WriteRecord)

/* ---- The receiver */

/* func_020392dc: the records read. */
void QuickMessage_ReceiverExecute(void *receiver)
{
    (void) receiver;
    QuickMessage_ReadRecords();
}
CLEAN_AS(func_020392dc, QuickMessage_ReceiverExecute)

/* func_020392e4: nothing to do on deletion. */
void QuickMessage_ReceiverDelete(void *receiver)
{
    (void) receiver;
}
CLEAN_AS(func_020392e4, QuickMessage_ReceiverDelete)

/* func_020392e8: nor on creation. */
void QuickMessage_ReceiverCreate(void *receiver)
{
    (void) receiver;
}
CLEAN_AS(func_020392e8, QuickMessage_ReceiverCreate)

/* func_020392ec (the receiver's vtable entry 1) */
QuickMessagePart *QuickMessage_ReceiverDestructDelete(QuickMessagePart *receiver)
{
    receiver->vtable = data_020da5c8;
    func_020edb3c(receiver);
    return receiver;
}
CLEAN_AS(func_020392ec, QuickMessage_ReceiverDestructDelete)

/* func_02039304 (the receiver's vtable entry 0) */
void QuickMessage_ReceiverDestruct(QuickMessagePart *receiver)
{
    receiver->vtable = data_020da5c8;
}
CLEAN_AS(func_02039304, QuickMessage_ReceiverDestruct)

/* func_02039310 */
void QuickMessage_ReceiverConstruct(QuickMessagePart *receiver)
{
    receiver->vtable = data_020da5c8;
}
CLEAN_AS(func_02039310, QuickMessage_ReceiverConstruct)

/* ---- The board */

/* func_0203931c: every balloon reset, none waiting or shown. */
void QuickMessage_ResetBoard(QuickMessageBoard *board)
{
    for (int i = 0; i < QUICK_MESSAGE_BALLOONS; i++) {
        func_02039e44(&board->balloons[i]);
        board->waiting[i] = NULL;
        board->shown[i] = NULL;
    }
}
CLEAN_AS(func_0203931c, QuickMessage_ResetBoard)

/* func_02039358: the text boxes of every shown balloon asked to redraw. */
void QuickMessage_RedrawShown(QuickMessageBoard *board)
{
    for (int i = 0; i < QUICK_MESSAGE_BALLOONS; i++) {
        if (board->shown[i] != NULL) {
            func_02039e84(board->shown[i]);
        }
    }
}
CLEAN_AS(func_02039358, QuickMessage_RedrawShown)

/* func_02039380: the shown balloons placed and drawn, the last entry first. */
void QuickMessage_DrawBoard(QuickMessageBoard *board)
{
    for (int i = QUICK_MESSAGE_BALLOONS - 1; i >= 0; i--) {
        QuickMessageBalloon *balloon = board->shown[i];
        if (balloon != NULL) {
            func_02039f30(balloon);
            balloon_call(balloon, BALLOON_DRAW);
        }
    }
}
CLEAN_AS(func_02039380, QuickMessage_DrawBoard)

/* func_020393b4: the waiting balloons placed, the others' restacked, every balloon updated and
 * the finished ones taken off. */
void QuickMessage_UpdateBoard(QuickMessageBoard *board)
{
    QuickMessage_PlaceWaiting(board);
    QuickMessage_Restack(board);
    for (int i = 0; i < QUICK_MESSAGE_BALLOONS; i++) {
        balloon_call(&board->balloons[i], BALLOON_UPDATE);
    }
    QuickMessage_DropFinished(board);
}
CLEAN_AS(func_020393b4, QuickMessage_UpdateBoard)

/* func_020393ec: the board reset and no longer the current one. */
void QuickMessage_BoardDelete(QuickMessageBoard *board)
{
    QuickMessage_ResetBoard(board);
    data_021c6738 = NULL;
}
CLEAN_AS(func_020393ec, QuickMessage_BoardDelete)

/* func_02039404: the board made the current one, each balloon given its position and the two
 * animations of it. */
void QuickMessage_BoardCreate(QuickMessageBoard *board)
{
    data_021c6738 = board;
    for (int i = 0; i < QUICK_MESSAGE_BALLOONS; i++) {
        func_02039efc(&board->balloons[i], i, data_020ca144[i], data_020ca134[i]);
    }
}
CLEAN_AS(func_02039404, QuickMessage_BoardCreate)

/* func_02039474: whether `balloon` (an address) is waiting. */
int QuickMessage_IsWaiting(QuickMessageBoard *board, int balloon)
{
    for (int i = 0; i < QUICK_MESSAGE_BALLOONS; i++) {
        if ((int) (uintptr_t) board->waiting[i] == balloon) {
            return 1;
        }
    }
    return 0;
}
CLEAN_AS(func_02039474, QuickMessage_IsWaiting)

/* func_020394a4: the shown balloons that are done taken off, the rest moved down. */
void QuickMessage_DropFinished(QuickMessageBoard *board)
{
    for (int i = 0; i < QUICK_MESSAGE_BALLOONS; i++) {
        QuickMessageBalloon *balloon = board->shown[i];
        if (balloon != NULL && balloon->unk_a4 == 0 && balloon->unk_b0 == 0) {
            board->shown[i] = NULL;
        }
    }
    compact(board->shown);
}
CLEAN_AS(func_020394a4, QuickMessage_DropFinished)

/* func_02039510: the other systems' shown balloons stacked 16 pixels apart, from the last entry
 * down. */
void QuickMessage_Restack(QuickMessageBoard *board)
{
    int offset = 0;
    for (int i = QUICK_MESSAGE_BALLOONS - 1; i >= 0; i--) {
        QuickMessageBalloon *balloon = board->shown[i];
        if (balloon != NULL && balloon->position != 0) {
            balloon->stack_offset = offset;
            offset += QUICK_MESSAGE_LINE_HEIGHT;
        }
    }
}
CLEAN_AS(func_02039510, QuickMessage_Restack)

/* func_02039540: each waiting balloon that can be placed taken off the waiting ones, the rest
 * moved down. */
void QuickMessage_PlaceWaiting(QuickMessageBoard *board)
{
    for (int i = 0; i < QUICK_MESSAGE_BALLOONS; i++) {
        if (board->waiting[i] != NULL && QuickMessage_PlaceBalloon(board, board->waiting[i]) != 0) {
            board->waiting[i] = NULL;
        }
    }
    compact(board->waiting);
}
CLEAN_AS(func_02039540, QuickMessage_PlaceWaiting)

/* func_020395a8: whether the balloon was placed. One already shown is restarted
 * (func_02039ebc) and stays waiting; one with a delay waits. Otherwise it goes in the last free
 * shown entry, above the other systems' balloons in the entries after it (16 pixels each), or
 * at offset 0 when it is this system's own, and is started; with no free entry it waits.
 * QUIRK: a shown balloon posted again stays waiting, and func_02039ebc runs on it every frame
 * while it is shown. */
int QuickMessage_PlaceBalloon(QuickMessageBoard *board, QuickMessageBalloon *balloon)
{
    if (func_02039444(board, balloon) != 0) {
        func_02039ebc(balloon);
        return 0;
    }
    if (balloon->delay > 0) {
        return 0;
    }
    int offset = 0;
    for (int i = QUICK_MESSAGE_BALLOONS - 1; i >= 0; i--) {
        QuickMessageBalloon *other = board->shown[i];
        if (other != NULL) {
            if (other->position != 0) {
                offset += QUICK_MESSAGE_LINE_HEIGHT;
            }
            continue;
        }
        board->shown[i] = balloon;
        if (balloon->position == 0) {
            offset = 0;
        }
        balloon->placed_offset = offset;
        balloon->stack_offset = offset;
        func_02039f30(balloon);
        func_02039edc(balloon);
        return 1;
    }
    return 0;
}
CLEAN_AS(func_020395a8, QuickMessage_PlaceBalloon)
