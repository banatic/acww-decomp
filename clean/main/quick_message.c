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
#include "autoload_2/approach.h"
#include "text_draw.h"

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

/* ---- The board, through its slots */

static_assert(offsetof(QuickMessageBalloon, tag) == 0x1c, "balloon tag");
static_assert(offsetof(QuickMessageBalloon, frame) == 0x30, "balloon frame");
static_assert(offsetof(QuickMessageBalloon, bounce) == 0x4c, "balloon bounce");
static_assert(offsetof(QuickMessageBalloon, boxes) == 0x9c, "balloon boxes");
static_assert(offsetof(QuickMessageBalloon, timer) == 0xa8, "balloon timer");
static_assert(offsetof(QuickMessageBalloon, visible) == 0xb4, "balloon visible");

/* The vtables of the board and of a balloon. */
extern const u8 data_020da5d8[];
extern const u8 data_020da658[];

/* A balloon's constructor and destructor as the game's code, handed to the array helpers. */
extern void func_0203a23c(void *balloon);
extern void func_0203a1f8(void *balloon);
extern void __cxa_vec_ctor(void *array, int count, int size, void (*construct)(void *), void (*destruct)(void *));
extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));

/* func_02039628: the balloon added to the waiting ones unless it already is. Returns 0 only
 * when every waiting entry is taken. */
int QuickMessage_QueueBalloon(QuickMessageBoard *board, QuickMessageBalloon *balloon)
{
    if (QuickMessage_IsWaiting(board, (int) (uintptr_t) balloon) != 0) {
        return 1;
    }
    for (int i = 0; i < QUICK_MESSAGE_BALLOONS; i++) {
        if (board->waiting[i] == NULL) {
            board->waiting[i] = balloon;
            return 1;
        }
    }
    return 0;
}
CLEAN_AS(func_02039628, QuickMessage_QueueBalloon)

/* func_02039668: the balloon of slot `slot` (4: this system without a slot) taken off the
 * waiting ones, and released when shown. */
void QuickMessage_DismissSlot(QuickMessageBoard *board, int slot)
{
    if (slot > 4) {
        return;
    }
    int position = QuickMessage_SlotPosition((int) (uintptr_t) board, slot);
    for (int i = 0; i < QUICK_MESSAGE_BALLOONS; i++) {
        QuickMessageBalloon *balloon = board->waiting[i];
        if (balloon != NULL && balloon->position == position) {
            board->waiting[i] = NULL;
            break;
        }
    }
    for (int i = 0; i < QUICK_MESSAGE_BALLOONS; i++) {
        QuickMessageBalloon *balloon = board->shown[i];
        if (balloon != NULL && balloon->position == position) {
            QuickMessage_BalloonRelease(balloon);
            break;
        }
    }
}
CLEAN_AS(func_02039668, QuickMessage_DismissSlot)

/* func_020396d0: the colour of slot `slot`'s balloon: the slot, slot 0's for slot 4 (no
 * slot). */
int QuickMessage_SlotColor(int unused, int slot)
{
    (void) unused;
    return slot == 4 ? 0 : slot;
}
CLEAN_AS(func_020396d0, QuickMessage_SlotColor)

/* func_020396dc: the balloon of slot `slot`: how far the slot comes after this system's slot,
 * mod 4, so that this system's own balloon is balloon 0. */
int QuickMessage_SlotPosition(int unused, int slot)
{
    (void) unused;
    return (slot - data_020ccf94->local_slot + 4) % 4;
}
CLEAN_AS(func_020396dc, QuickMessage_SlotPosition)

/* func_020396fc: the player's `name` and the message `text` (labels) put in slot `slot`'s
 * balloon and the balloon queued, unless every waiting entry is taken. A message for this
 * system's own balloon is also written to its record (QuickMessage_WriteRecord), for the
 * others to read.
 * REQUIRES: slot is at least 0 (a session slot, or 4 for none); a slot below
 * local_slot - 4 would give a balloon before the board. */
void QuickMessage_PostOn(QuickMessageBoard *board, int slot, void *name, void *text)
{
    if (slot > 4) {
        return;
    }
    QuickMessageBalloon *balloon = &board->balloons[QuickMessage_SlotPosition((int) (uintptr_t) board, slot)];
    if (QuickMessage_QueueBalloon(board, balloon) == 0) {
        return;
    }
    QuickMessage_BalloonSetMessage(balloon, name, text, QuickMessage_SlotColor((int) (uintptr_t) board, slot));
    if (balloon->position != 0) {
        return;
    }
    QuickMessage_WriteRecord(slot, balloon);
}
CLEAN_AS(func_020396fc, QuickMessage_PostOn)

/* func_02039750 (the board's vtable entry 1): destroyed and freed. */
QuickMessageBoard *QuickMessage_BoardDestructDelete(QuickMessageBoard *board)
{
    board->vtable = data_020da5d8;
    __cxa_vec_cleanup(board->balloons, QUICK_MESSAGE_BALLOONS, sizeof(QuickMessageBalloon), func_0203a1f8);
    func_020edb3c(board);
    return board;
}
CLEAN_AS(func_02039750, QuickMessage_BoardDestructDelete)

/* func_0203977c (the board's vtable entry 0): the balloons destroyed. */
void *QuickMessage_BoardDestruct(QuickMessageBoard *board)
{
    board->vtable = data_020da5d8;
    __cxa_vec_cleanup(board->balloons, QUICK_MESSAGE_BALLOONS, sizeof(QuickMessageBalloon), func_0203a1f8);
    return board;
}
CLEAN_AS(func_0203977c, QuickMessage_BoardDestruct)

/* func_020397a0: the balloons constructed, none waiting or shown. */
QuickMessageBoard *QuickMessage_BoardConstruct(QuickMessageBoard *board)
{
    board->vtable = data_020da5d8;
    __cxa_vec_ctor(board->balloons, QUICK_MESSAGE_BALLOONS, sizeof(QuickMessageBalloon), func_0203a23c, func_0203a1f8);
    for (int i = 0; i < QUICK_MESSAGE_BALLOONS; i++) {
        board->waiting[i] = NULL;
        board->shown[i] = NULL;
    }
    return board;
}
CLEAN_AS(func_020397a0, QuickMessage_BoardConstruct)

/* func_020397f0: the current board reset (the process must exist). */
void QuickMessage_ResetCurrent(void)
{
    QuickMessage_ResetBoard(data_021c6738);
}
CLEAN_AS(func_020397f0, QuickMessage_ResetCurrent)

/* func_02039800: the current board's shown balloons redrawn (the process must exist). */
void QuickMessage_RedrawCurrent(void)
{
    QuickMessage_RedrawShown(data_021c6738);
}
CLEAN_AS(func_02039800, QuickMessage_RedrawCurrent)

/* func_02039810: whether this system's own balloon is out, or any balloon waits out its delay.
 * QUIRK: the delay of every balloon counts, the other systems' too. */
int QuickMessage_OwnBalloonBusy(void)
{
    for (int i = 0; i < QUICK_MESSAGE_BALLOONS; i++) {
        QuickMessageBalloon *balloon = &data_021c6738->balloons[i];
        if ((balloon->position == 0 && balloon->unk_a4 != QUICK_BALLOON_IDLE) || balloon->delay > 0) {
            return 1;
        }
    }
    return 0;
}
CLEAN_AS(func_02039810, QuickMessage_OwnBalloonBusy)

/* func_02039860: whether another system's balloon is out, or any balloon waits out its delay.
 * QUIRK: the delay of every balloon counts, this system's own too. */
int QuickMessage_OtherBalloonBusy(void)
{
    for (int i = 0; i < QUICK_MESSAGE_BALLOONS; i++) {
        QuickMessageBalloon *balloon = &data_021c6738->balloons[i];
        if ((balloon->position != 0 && balloon->unk_a4 != QUICK_BALLOON_IDLE) || balloon->delay > 0) {
            return 1;
        }
    }
    return 0;
}
CLEAN_AS(func_02039860, QuickMessage_OtherBalloonBusy)

/* func_020398b0: the balloons of slots 0-3 dismissed from the current board. */
void QuickMessage_DismissAll(void)
{
    for (int slot = 0; slot < QUICK_MESSAGE_BALLOONS; slot++) {
        QuickMessage_DismissSlot(data_021c6738, slot);
    }
}
CLEAN_AS(func_020398b0, QuickMessage_DismissAll)

/* func_020398d4: the balloon of slot `slot` dismissed from the current board. */
void QuickMessage_Dismiss(unsigned int slot)
{
    QuickMessage_DismissSlot(data_021c6738, (int) slot);
}
CLEAN_AS(func_020398d4, QuickMessage_Dismiss)

/* func_020398e8: a message posted on the current board. */
void QuickMessage_Post(int slot, void *name, void *text)
{
    QuickMessage_PostOn(data_021c6738, slot, name, text);
}
CLEAN_AS(func_020398e8, QuickMessage_Post)

/* ---- A balloon
 *
 * A balloon is a sprite (base class constructed by func_0208af30) drawn with two cell
 * animations of data_020d5b3c, each held on the frame as wide as its text: the balloon, and
 * for the other systems' balloons a tag with the player's name. The texts are drawn by two
 * text boxes into the objects' tiles: the message 20 tiles wide from tile 0xc0 + 64 *
 * position, the name 8 tiles wide from tile 0x1c0 + 8 * position, two rows each.
 *
 * Its moves come from a table of tuning values (func_0209d368, which returns 0 in this
 * build): entries 0x136-0x138 for this system's own balloon and 0x12c-0x12e for the others',
 * one for each of the states appearing, holding and leaving. */

#define TUNE_OWN_APPEAR 0x136
#define TUNE_OWN_HOLD 0x137
#define TUNE_OWN_LEAVE 0x138
#define TUNE_OTHER_APPEAR 0x12c
#define TUNE_OTHER_HOLD 0x12d
#define TUNE_OTHER_LEAVE 0x12e

#define BALLOON_HOLD_FRAMES 600
#define BALLOON_APPEAR_SOUND 0x3f /* when another system's balloon appears */
#define BALLOON_PALETTE_BASE 5

/* The text boxes' tiles and colours. */
#define TEXT_BOX_FIRST_TILE 0xc0
#define TEXT_BOX_TILE_STRIDE 64
#define TEXT_BOX_CELLS 20
#define NAME_BOX_FIRST_TILE 0x1c0
#define NAME_BOX_TILE_STRIDE 8
#define NAME_BOX_CELLS 8
#define BOX_ROWS 2
#define BOX_LAYER_OBJECTS 4
#define BOX_COLOR 0xd
#define TEXT_BOX_BACKGROUND 0xf
#define NAME_BOX_BACKGROUND 0xe

/* An entry of data_020d5b3c: the cells of an animation and how many frames it has. */
typedef struct QuickMessageAnimData {
    const void *cells;
    s32 frames;
} QuickMessageAnimData;
extern const QuickMessageAnimData data_020d5b3c[];

/* A tuning value (table entry, index); 0 in this build. */
extern int func_0209d368(int entry, int index);

/* The sprite base: constructed, destroyed, its place. */
extern void func_0208af30(QuickMessageBalloon *balloon);
extern void func_0208af00(QuickMessageBalloon *balloon);
extern int func_0208aef0(QuickMessageBalloon *balloon); /* x */
extern int func_0208aeec(QuickMessageBalloon *balloon); /* y */

/* Cell animations (screen_icon.h): constructed, destroyed, given their data, held on the last
 * frame, given a speed, put on a frame, advanced; the data, the frame's cell and offsets. */
extern void func_0208a1f8(CellAnim *anim);
extern void func_0208a1f4(CellAnim *anim);
extern void func_0208a1f0(CellAnim *anim, const QuickMessageAnimData *data);
extern void func_0208a1ec(CellAnim *anim, int hold);
extern void *func_0208a1e8(CellAnim *anim, fx32 speed);
extern void *func_0208a1e0(CellAnim *anim, int frame, fx32 time);
extern void func_0208a0c8(CellAnim *anim);
extern const QuickMessageAnimData *func_0208a1c8(CellAnim *anim);
extern int func_0208a1d0(CellAnim *anim);
extern s16 func_0208a1b0(CellAnim *anim, int frame); /* the current one for -1 */
extern s16 func_0208a198(CellAnim *anim, int frame);

/* An object drawn from a cell. */
extern void func_02088df8(int a0, int cell, int x, int y, int palette, int priority, fx32 scale_x, fx32 scale_y, int rotation,
                          int p9, int p10, int p11);

/* A text box from VRAM tile `first_tile`, `cells` tiles wide and `rows` high, in the boxes'
 * heap (NULL when it is full); a box destroyed and freed. */
extern TextDrawBox *func_020a9034(int first_tile, int cells, int rows);
extern void func_020a8fb8(TextDrawBox *box);

/* A label emptied; a label set from another. */
extern void func_020a8c1c(void *label);
extern void *func_020a8bb8(void *label, void *from);

/* State flag 4's value, or 1.0 / 0 while the flag is clear (state_flags.h). */
extern fx32 func_0206fd10(void);
extern fx32 func_0206fd34(void);
extern fx32 FX_MulFunc(fx32 a, fx32 b);

/* POWCNT1's swap bit: 1 for the main engine on top. */
extern int data_021c8c9c;

/* The address of a text object's characters, through its vtable (slot 3). */
static int text_buffer(void *object)
{
    typedef int TextBufferMethod(void *object);
    const TextObject *text = object;
    return ((TextBufferMethod *) (uintptr_t) text->vtable->buffer)(object);
}

/* A text box's text width in pixels, through its vtable (slot 3). */
static u32 box_text_width(TextDrawBox *box)
{
    typedef u32 TextMeasureMethod(TextDrawBox * box);
    return ((TextMeasureMethod *) (uintptr_t) box->vtable[3])(box);
}

/* The animation put on its frame for a text `cells` tiles wide, within its frames. */
static void fit_frame(CellAnim *anim, int cells)
{
    int last = func_0208a1c8(anim)->frames - 1;
    int frame = cells - 1;
    if (frame < 0) {
        frame = 0;
    } else if (frame > last) {
        frame = last;
    }
    func_0208a1e0(anim, frame, 0);
}

/* The animation given its data, held still. */
static void load_anim(CellAnim *anim, const QuickMessageAnimData *data)
{
    func_0208a1f0(anim, data);
    func_0208a1ec(anim, 1);
    func_0208a1e8(anim, 0);
}

/* func_0203990c: the message's text box freed. */
void QuickMessage_BalloonFreeTextBox(QuickMessageBalloon *balloon)
{
    if (balloon->boxes[QUICK_BALLOON_TEXT_BOX] != NULL) {
        func_020a8fb8(balloon->boxes[QUICK_BALLOON_TEXT_BOX]);
        balloon->boxes[QUICK_BALLOON_TEXT_BOX] = NULL;
    }
}
CLEAN_AS(func_0203990c, QuickMessage_BalloonFreeTextBox)

/* func_02039928: unless it has one, a text box for the message, drawn into the objects' tiles
 * of both screens (only the main screen's while data_021c8c9c is set) in colour 0xd on 0xf,
 * each frame by the text process; its drawing asked for. None when the boxes' heap is full. */
void QuickMessage_BalloonOpenTextBox(QuickMessageBalloon *balloon)
{
    if (balloon->boxes[QUICK_BALLOON_TEXT_BOX] != NULL) {
        return;
    }
    TextDrawBox *box = func_020a9034(TEXT_BOX_FIRST_TILE + balloon->position * TEXT_BOX_TILE_STRIDE, TEXT_BOX_CELLS, BOX_ROWS);
    balloon->boxes[QUICK_BALLOON_TEXT_BOX] = box;
    if (box == NULL) {
        return;
    }
    box->layer = BOX_LAYER_OBJECTS;
    box->text = (const char *) (uintptr_t) text_buffer(balloon->text);
    box->screens = data_021c8c9c == 0 ? TEXT_DRAW_TO_BOTH : TEXT_DRAW_TO_MAIN;
    box->update_mode = TEXT_DRAW_GROUP_1;
    box->rows_full_width = 1;
    box->background = TEXT_BOX_BACKGROUND;
    box->color = BOX_COLOR;
    TextDraw_RequestDraw(box);
}
CLEAN_AS(func_02039928, QuickMessage_BalloonOpenTextBox)

/* func_020399c8: the name's text box freed. */
void QuickMessage_BalloonFreeNameBox(QuickMessageBalloon *balloon)
{
    if (balloon->boxes[QUICK_BALLOON_NAME_BOX] != NULL) {
        func_020a8fb8(balloon->boxes[QUICK_BALLOON_NAME_BOX]);
        balloon->boxes[QUICK_BALLOON_NAME_BOX] = NULL;
    }
}
CLEAN_AS(func_020399c8, QuickMessage_BalloonFreeNameBox)

/* func_020399e4: for another system's balloon without one, a text box for the player's name,
 * as the message's but on background 0xe. */
void QuickMessage_BalloonOpenNameBox(QuickMessageBalloon *balloon)
{
    if (balloon->position == 0 || balloon->boxes[QUICK_BALLOON_NAME_BOX] != NULL) {
        return;
    }
    TextDrawBox *box = func_020a9034(NAME_BOX_FIRST_TILE + balloon->position * NAME_BOX_TILE_STRIDE, NAME_BOX_CELLS, BOX_ROWS);
    balloon->boxes[QUICK_BALLOON_NAME_BOX] = box;
    if (box == NULL) {
        return;
    }
    box->layer = BOX_LAYER_OBJECTS;
    box->text = (const char *) (uintptr_t) text_buffer(balloon->name);
    box->screens = data_021c8c9c == 0 ? TEXT_DRAW_TO_BOTH : TEXT_DRAW_TO_MAIN;
    box->update_mode = TEXT_DRAW_GROUP_1;
    box->rows_full_width = 1;
    box->background = NAME_BOX_BACKGROUND;
    box->color = BOX_COLOR;
    TextDraw_RequestDraw(box);
}
CLEAN_AS(func_020399e4, QuickMessage_BalloonOpenNameBox)

/* func_02039a94: the tag and the balloon put on the frames as wide as the name and the
 * message, in whole tiles. The name is pushed to the right end of its tiles; this system's own
 * message is centred in its tiles, the others' start at the left.
 * REQUIRES: the message's text box exists (QuickMessage_BalloonOpenTextBox just made it); the
 * original measures it without looking, so a full boxes' heap would read address 0. */
void QuickMessage_BalloonFitFrames(QuickMessageBalloon *balloon)
{
    TextDrawBox *name_box = balloon->boxes[QUICK_BALLOON_NAME_BOX];
    if (name_box != NULL) {
        u32 width = box_text_width(name_box);
        int cells = (int) ((width + 7) >> 3);
        u32 spare = (u32) cells * 8 - width;
        fit_frame(&balloon->tag, cells);
        ((TextDrawBox *) balloon->boxes[QUICK_BALLOON_NAME_BOX])->offset = spare;
    }

    u32 width = box_text_width(balloon->boxes[QUICK_BALLOON_TEXT_BOX]);
    int cells = (int) ((width + 7) >> 3);
    fit_frame(&balloon->frame, cells);
    TextDrawBox *text_box = balloon->boxes[QUICK_BALLOON_TEXT_BOX];
    if (balloon->position == 0 && text_box != NULL) {
        text_box->offset = ((u32) cells * 8 - width) >> 1;
    }
}
CLEAN_AS(func_02039a94, QuickMessage_BalloonFitFrames)

/* func_02039b30: the animations of the tag (for another system's balloon) and of the balloon
 * loaded from their entries, held still. */
void QuickMessage_BalloonLoadAnims(QuickMessageBalloon *balloon)
{
    const QuickMessageAnimData *frame = &data_020d5b3c[balloon->frame_anim];
    if (balloon->position != 0) {
        load_anim(&balloon->tag, &data_020d5b3c[balloon->tag_anim]);
    }
    load_anim(&balloon->frame, frame);
}
CLEAN_AS(func_02039b30, QuickMessage_BalloonLoadAnims)

/* func_02039b90 (state leaving): the balloon moved 11 pixels a frame, this system's own one
 * down and the others' up. When its time is over the boxes are freed, the balloon stops, and
 * it waits 0 frames (own) or 10 (the others') before it may be placed again. */
void QuickMessage_BalloonLeaving(QuickMessageBalloon *balloon)
{
    int move;
    if (balloon->position == 0) {
        move = func_0209d368(TUNE_OWN_LEAVE, 3) + 11;
    } else {
        move = func_0209d368(TUNE_OTHER_LEAVE, 3) - 11;
    }
    balloon->bounce += move;
    balloon->timer--;
    if (balloon->timer > 0) {
        return;
    }
    QuickMessage_BalloonFreeNameBox(balloon);
    QuickMessage_BalloonFreeTextBox(balloon);
    QuickMessage_BalloonStop(balloon);
    if (balloon->position == 0) {
        balloon->delay = func_0209d368(TUNE_OWN_LEAVE, 4);
    } else {
        balloon->delay = func_0209d368(TUNE_OTHER_LEAVE, 4) + 10;
    }
}
CLEAN_AS(func_02039b90, QuickMessage_BalloonLeaving)

/* func_02039c0c: the balloon starts leaving, for 2 frames. */
void QuickMessage_BalloonStartLeaving(QuickMessageBalloon *balloon)
{
    balloon->unk_a4 = QUICK_BALLOON_LEAVING;
    balloon->visible = 1;
    if (balloon->position == 0) {
        balloon->timer = func_0209d368(TUNE_OWN_LEAVE, 2) + 2;
    } else {
        balloon->timer = func_0209d368(TUNE_OTHER_LEAVE, 2) + 2;
    }
}
CLEAN_AS(func_02039c0c, QuickMessage_BalloonStartLeaving)

/* func_02039c4c (state holding): the balloon moved towards its place in the stack, 6 pixels a
 * frame; once its time is over, or it was released, it starts leaving. */
void QuickMessage_BalloonHolding(QuickMessageBalloon *balloon)
{
    int step;
    if (balloon->position == 0) {
        step = func_0209d368(TUNE_OWN_HOLD, 3) + 6;
    } else {
        step = func_0209d368(TUNE_OTHER_HOLD, 3) + 6;
    }
    Approach_S32Again((int *) &balloon->placed_offset, balloon->stack_offset, step);
    balloon->timer--;
    if (balloon->timer <= 0) {
        balloon->unk_b0 = 0;
    }
    if (balloon->unk_b0 == 0) {
        QuickMessage_BalloonStartLeaving(balloon);
    }
}
CLEAN_AS(func_02039c4c, QuickMessage_BalloonHolding)

/* func_02039cb4: the balloon starts holding, for 600 frames. */
void QuickMessage_BalloonStartHolding(QuickMessageBalloon *balloon)
{
    balloon->unk_a4 = QUICK_BALLOON_HOLDING;
    balloon->visible = 1;
    if (balloon->position == 0) {
        balloon->timer = func_0209d368(TUNE_OWN_HOLD, 2) + BALLOON_HOLD_FRAMES;
    } else {
        balloon->timer = func_0209d368(TUNE_OTHER_HOLD, 2) + BALLOON_HOLD_FRAMES;
    }
}
CLEAN_AS(func_02039cb4, QuickMessage_BalloonStartHolding)

/* func_02039cf8 (state appearing): the balloon moved 6 pixels a frame (this system's own one
 * up, the others' down) and, in its last 2 frames, 2 pixels back; then it rests on its place
 * and starts holding. */
void QuickMessage_BalloonAppearing(QuickMessageBalloon *balloon)
{
    int turn;
    int move;
    int settle;
    if (balloon->position == 0) {
        turn = func_0209d368(TUNE_OWN_APPEAR, 4) + 2;
    } else {
        turn = func_0209d368(TUNE_OTHER_APPEAR, 4) + 2;
    }
    if (balloon->position == 0) {
        move = func_0209d368(TUNE_OWN_APPEAR, 5) - 6;
    } else {
        move = func_0209d368(TUNE_OTHER_APPEAR, 5) + 6;
    }
    if (balloon->position == 0) {
        settle = func_0209d368(TUNE_OWN_APPEAR, 6) + 2;
    } else {
        settle = func_0209d368(TUNE_OTHER_APPEAR, 6) - 2;
    }

    balloon->bounce += balloon->timer > turn ? move : settle;
    balloon->timer--;
    if (balloon->timer <= 0) {
        balloon->bounce = 0;
        QuickMessage_BalloonStartHolding(balloon);
    }
}
CLEAN_AS(func_02039cf8, QuickMessage_BalloonAppearing)

/* func_02039d98: the balloon starts appearing, for 3 frames, 5 pixels below its place (this
 * system's own one) or above it (the others', which also play sound 0x3f). */
void QuickMessage_BalloonStartAppearing(QuickMessageBalloon *balloon)
{
    balloon->unk_a4 = QUICK_BALLOON_APPEARING;
    balloon->visible = 1;
    int frames;
    int start;
    if (balloon->position == 0) {
        frames = func_0209d368(TUNE_OWN_APPEAR, 2) + 3;
    } else {
        frames = func_0209d368(TUNE_OTHER_APPEAR, 2) + 3;
    }
    if (balloon->position == 0) {
        start = func_0209d368(TUNE_OWN_APPEAR, 3) + 5;
    } else {
        start = func_0209d368(TUNE_OTHER_APPEAR, 3) - 5;
    }
    balloon->timer = frames;
    balloon->bounce = start;
    if (balloon->position != 0) {
        SoundSys_PlaySe(BALLOON_APPEAR_SOUND);
    }
}
CLEAN_AS(func_02039d98, QuickMessage_BalloonStartAppearing)

/* func_02039e08 (state idle): once the balloon is asked to appear, its text boxes are opened,
 * its frames fitted to them, and it starts appearing. */
void QuickMessage_BalloonIdle(QuickMessageBalloon *balloon)
{
    if (balloon->unk_b0 != 0) {
        QuickMessage_BalloonOpenNameBox(balloon);
        QuickMessage_BalloonOpenTextBox(balloon);
        QuickMessage_BalloonFitFrames(balloon);
        QuickMessage_BalloonStartAppearing(balloon);
    }
}
CLEAN_AS(func_02039e08, QuickMessage_BalloonIdle)

/* func_02039e34: the balloon idle and hidden. */
void QuickMessage_BalloonStop(QuickMessageBalloon *balloon)
{
    balloon->unk_a4 = QUICK_BALLOON_IDLE;
    balloon->visible = 0;
}
CLEAN_AS(func_02039e34, QuickMessage_BalloonStop)

/* func_02039e44: the texts emptied, the boxes freed, the balloon stopped with no time, delay
 * or request left. */
void QuickMessage_BalloonReset(QuickMessageBalloon *balloon)
{
    func_020a8c1c(balloon->text);
    TextString_ClearBytes((TextObject *) balloon->name);
    QuickMessage_BalloonFreeNameBox(balloon);
    QuickMessage_BalloonFreeTextBox(balloon);
    balloon->timer = 0;
    balloon->delay = 0;
    balloon->unk_b0 = 0;
    QuickMessage_BalloonStop(balloon);
}
CLEAN_AS(func_02039e44, QuickMessage_BalloonReset)

/* func_02039e84: each text box sent to both screens and asked to redraw. */
void QuickMessage_BalloonRedraw(QuickMessageBalloon *balloon)
{
    TextDrawBox *name_box = balloon->boxes[QUICK_BALLOON_NAME_BOX];
    if (name_box != NULL) {
        name_box->screens = TEXT_DRAW_TO_BOTH;
        TextDraw_RequestDraw(name_box);
    }
    TextDrawBox *text_box = balloon->boxes[QUICK_BALLOON_TEXT_BOX];
    if (text_box != NULL) {
        text_box->screens = TEXT_DRAW_TO_BOTH;
        TextDraw_RequestDraw(text_box);
    }
}
CLEAN_AS(func_02039e84, QuickMessage_BalloonRedraw)

/* func_02039ebc: whether the balloon is out; one that is loses its request, so that it leaves
 * once it holds. */
int QuickMessage_BalloonRelease(QuickMessageBalloon *balloon)
{
    int out = balloon->unk_a4 != QUICK_BALLOON_IDLE;
    if (out) {
        balloon->unk_b0 = 0;
    }
    return out;
}
CLEAN_AS(func_02039ebc, QuickMessage_BalloonRelease)

/* func_02039edc: whether the balloon is idle; one that is is asked to appear. */
int QuickMessage_BalloonRequest(QuickMessageBalloon *balloon)
{
    int idle = balloon->unk_a4 == QUICK_BALLOON_IDLE;
    if (idle) {
        balloon->unk_b0 = 2;
    }
    return idle;
}
CLEAN_AS(func_02039edc, QuickMessage_BalloonRequest)

/* func_02039efc: the balloon given its position and the entries of its animations. */
void QuickMessage_BalloonSetup(QuickMessageBalloon *balloon, int position, int tag_anim, int frame_anim)
{
    balloon->position = position;
    balloon->tag_anim = tag_anim;
    balloon->frame_anim = frame_anim;
    QuickMessage_BalloonLoadAnims(balloon);
}
CLEAN_AS(func_02039efc, QuickMessage_BalloonSetup)

/* func_02039f0c: the player's name and the message copied in, the palette of colour `color`
 * chosen. */
void QuickMessage_BalloonSetMessage(QuickMessageBalloon *balloon, void *name, void *text, int color)
{
    TextString_CopyBytes((TextObject *) balloon->name, name);
    func_020a8bb8(balloon->text, text);
    balloon->palette = color + BALLOON_PALETTE_BASE;
}
CLEAN_AS(func_02039f0c, QuickMessage_BalloonSetMessage)

/* func_02039f30: the balloon's height from state flag 4's value v (fx32): this system's own
 * one between 76 (v = 1.0, also while the flag is clear) and 192 (v = 0), the others' between
 * -92 (v = 1.0) and 48 (v = 0, also while the flag is clear). */
void QuickMessage_BalloonPlaceY(QuickMessageBalloon *balloon)
{
    if (balloon->position == 0) {
        fx32 v = func_0206fd10();
        fx32 at_one = FX_MulFunc(0x4c000, v);
        fx32 at_zero = FX_MulFunc(0xc0000, 0x1000 - v);
        balloon->base_y = (at_one + at_zero) >> 12;
    } else {
        fx32 v = func_0206fd34();
        fx32 at_one = FX_MulFunc(-0x5c000, v);
        fx32 at_zero = FX_MulFunc(0x30000, 0x1000 - v);
        balloon->base_y = (at_one + at_zero) >> 12;
    }
}
CLEAN_AS(func_02039f30, QuickMessage_BalloonPlaceY)

/* func_02039f98 (vtable entry 3): the delay counted down, the state run, and the animations
 * of a balloon that is out advanced.
 * REQUIRES: the state is 0-3; the original indexes a table of four member pointers with it. */
void QuickMessage_BalloonUpdate(QuickMessageBalloon *balloon)
{
    if (balloon->delay > 0) {
        balloon->delay--;
    }
    switch (balloon->unk_a4) {
        case QUICK_BALLOON_IDLE:
            QuickMessage_BalloonIdle(balloon);
            break;
        case QUICK_BALLOON_APPEARING:
            QuickMessage_BalloonAppearing(balloon);
            break;
        case QUICK_BALLOON_HOLDING:
            QuickMessage_BalloonHolding(balloon);
            break;
        case QUICK_BALLOON_LEAVING:
            QuickMessage_BalloonLeaving(balloon);
            break;
        default:
            break;
    }
    if (balloon->unk_a4 != QUICK_BALLOON_IDLE) {
        if (balloon->position != 0) {
            func_0208a0c8(&balloon->tag);
        }
        func_0208a0c8(&balloon->frame);
    }
}
CLEAN_AS(func_02039f98, QuickMessage_BalloonUpdate)

/* Where an animation's cell is drawn: the sprite's place plus the frame's offset, moved by the
 * balloon's height, bounce and place in the stack. */
typedef struct QuickMessageCell {
    int cell;
    int x;
    int y;
} QuickMessageCell;

static QuickMessageCell balloon_cell(QuickMessageBalloon *balloon, CellAnim *anim)
{
    QuickMessageCell out;
    out.cell = func_0208a1d0(anim);
    int x = func_0208aef0(balloon);
    out.x = x + func_0208a1b0(anim, -1);
    int y = func_0208aeec(balloon);
    int frame_y = func_0208a198(anim, -1);
    out.y = balloon->base_y + balloon->bounce + balloon->placed_offset + y + frame_y;
    return out;
}

static void draw_cell(int a0, const QuickMessageCell *cell, int palette)
{
    func_02088df8(a0, cell->cell, cell->x, cell->y, palette, -1, 0x1000, 0x1000, 0, -1, 0, 0);
}

/* func_0203a054 (vtable entry 2): a visible balloon drawn: this system's own one alone (first
 * argument 0), the others' with the name tag first (first argument 2). */
void QuickMessage_BalloonDraw(QuickMessageBalloon *balloon)
{
    if (balloon->visible == 0) {
        return;
    }
    if (balloon->position == 0) {
        QuickMessageCell frame = balloon_cell(balloon, &balloon->frame);
        draw_cell(0, &frame, balloon->palette);
    } else {
        QuickMessageCell tag = balloon_cell(balloon, &balloon->tag);
        QuickMessageCell frame = balloon_cell(balloon, &balloon->frame);
        draw_cell(2, &tag, balloon->palette);
        draw_cell(2, &frame, balloon->palette);
    }
}
CLEAN_AS(func_0203a054, QuickMessage_BalloonDraw)

/* func_0203a1ac (vtable entry 1): destroyed and freed. */
QuickMessageBalloon *QuickMessage_BalloonDestructDelete(QuickMessageBalloon *balloon)
{
    QuickMessage_BalloonDestruct(balloon);
    func_020edb3c(balloon);
    return balloon;
}
CLEAN_AS(func_0203a1ac, QuickMessage_BalloonDestructDelete)

/* func_0203a1f8 (vtable entry 0): the boxes freed, the members destroyed, last first. */
QuickMessageBalloon *QuickMessage_BalloonDestruct(QuickMessageBalloon *balloon)
{
    balloon->vtable = data_020da658;
    QuickMessage_BalloonFreeNameBox(balloon);
    QuickMessage_BalloonFreeTextBox(balloon);
    QuickMessage_NameDestruct((QuickMessageName *) balloon->name);
    QuickMessage_TextDestruct((QuickMessageText *) balloon->text);
    func_0208a1f4(&balloon->frame);
    func_0208a1f4(&balloon->tag);
    func_0208af00(balloon);
    return balloon;
}
CLEAN_AS(func_0203a1f8, QuickMessage_BalloonDestruct)

/* func_0203a23c: the constructor: everything 0, the labels empty. */
QuickMessageBalloon *QuickMessage_BalloonConstruct(QuickMessageBalloon *balloon)
{
    func_0208af30(balloon);
    balloon->vtable = data_020da658;
    balloon->position = 0;
    balloon->palette = 0;
    balloon->tag_anim = 0;
    balloon->frame_anim = 0;
    func_0208a1f8(&balloon->tag);
    func_0208a1f8(&balloon->frame);
    balloon->stack_offset = 0;
    balloon->placed_offset = 0;
    balloon->bounce = 0;
    balloon->base_y = 0;
    func_0203a404((QuickMessageText *) balloon->text);
    QuickMessage_NameConstruct((QuickMessageName *) balloon->name);
    balloon->boxes[QUICK_BALLOON_NAME_BOX] = NULL;
    balloon->boxes[QUICK_BALLOON_TEXT_BOX] = NULL;
    balloon->unk_a4 = QUICK_BALLOON_IDLE;
    balloon->timer = 0;
    balloon->delay = 0;
    balloon->unk_b0 = 0;
    balloon->visible = 0;
    return balloon;
}
CLEAN_AS(func_0203a23c, QuickMessage_BalloonConstruct)

/* ---- The text objects (declared above, before the process)
 *
 * Each class's vtable has the destructor, the deleting destructor, the capacity and the
 * address of the characters.
 * - A view: words[1] the address of its 16-bit characters, words[2] how many; its base class
 *   has vtable data_020da6c4.
 * - A wide text: words[1-3] its base's (func_020a88ec constructs it, func_020a887c destroys
 *   it), words[4] the address of its 16-bit characters, words[5] how many.
 * - A name label: up to 14 8-bit characters from byte 4 on; its base class has vtable
 *   data_020da6dc.
 * - A message label: a label base (func_020a8c38 destroys it), then up to 34 8-bit characters
 *   from byte 18 on. */

#define VIEW_CHARS 1
#define VIEW_COUNT 2
#define WIDE_CHARS 4
#define WIDE_COUNT 5
#define NAME_CHARS_AT 4
#define NAME_CAPACITY 14
#define TEXT_CHARS_AT 18
#define TEXT_CAPACITY 34

extern const u8 data_020da610[]; /* a view */
extern const u8 data_020da6c4[]; /* its base */
extern const u8 data_020da5f8[]; /* a name label */
extern const u8 data_020da6dc[]; /* its base */
extern const u8 data_020da628[]; /* a wide text */
extern const u8 data_020da640[]; /* a message label */

extern void *func_020a88ec(QuickMessageWide *wide);
extern void *func_020a887c(QuickMessageWide *wide);
extern void *func_020a8c38(QuickMessageText *text);

/* A vtable's address, as the object's first word holds it. */
static u32 vtable_word(const u8 *vtable)
{
    return (u32) (uintptr_t) vtable;
}

/* func_0203a2b4 (a view's vtable slot 3): the address of its characters. */
int QuickMessage_ViewBuffer(QuickMessageView *view)
{
    return (int) view->words[VIEW_CHARS];
}
CLEAN_AS(func_0203a2b4, QuickMessage_ViewBuffer)

/* func_0203a2b8 (slot 2): how many characters it has. */
int QuickMessage_ViewCapacity(QuickMessageView *view)
{
    return (int) view->words[VIEW_COUNT];
}
CLEAN_AS(func_0203a2b8, QuickMessage_ViewCapacity)

/* func_0203a2bc (slot 1): destroyed and freed. */
QuickMessageView *QuickMessage_ViewDestructDelete(QuickMessageView *view)
{
    view->words[0] = vtable_word(data_020da610);
    view->words[0] = vtable_word(data_020da6c4);
    func_020edb3c(view);
    return view;
}
CLEAN_AS(func_0203a2bc, QuickMessage_ViewDestructDelete)

/* func_0203a2dc (slot 0): destroyed. */
void QuickMessage_ViewDestruct(QuickMessageView *view)
{
    view->words[0] = vtable_word(data_020da610);
    view->words[0] = vtable_word(data_020da6c4);
}
CLEAN_AS(func_0203a2dc, QuickMessage_ViewDestruct)

/* func_0203a2f0: a view of `count` 16-bit characters at address `chars`. */
void QuickMessage_ViewConstruct(QuickMessageView *view, unsigned int chars, unsigned int count)
{
    view->words[0] = vtable_word(data_020da6c4);
    view->words[0] = vtable_word(data_020da610);
    view->words[VIEW_CHARS] = chars;
    view->words[VIEW_COUNT] = count;
}
CLEAN_AS(func_0203a2f0, QuickMessage_ViewConstruct)

/* func_0203a308 (a name label's vtable slot 3): the address of its characters. */
int QuickMessage_NameBuffer(int name)
{
    return name + NAME_CHARS_AT;
}
CLEAN_AS(func_0203a308, QuickMessage_NameBuffer)

/* func_0203a30c (slot 2) */
int QuickMessage_NameCapacity(void)
{
    return NAME_CAPACITY;
}
CLEAN_AS(func_0203a30c, QuickMessage_NameCapacity)

/* func_0203a310 (slot 1): destroyed and freed. */
QuickMessageName *QuickMessage_NameDestructDelete(QuickMessageName *name)
{
    name->words[0] = vtable_word(data_020da5f8);
    name->words[0] = vtable_word(data_020da6dc);
    func_020edb3c(name);
    return name;
}
CLEAN_AS(func_0203a310, QuickMessage_NameDestructDelete)

/* func_0203a330 (slot 0): destroyed. */
void QuickMessage_NameDestruct(QuickMessageName *name)
{
    name->words[0] = vtable_word(data_020da5f8);
    name->words[0] = vtable_word(data_020da6dc);
}
CLEAN_AS(func_0203a330, QuickMessage_NameDestruct)

/* func_0203a344: an empty name label. */
QuickMessageName *QuickMessage_NameConstruct(QuickMessageName *name)
{
    name->words[0] = vtable_word(data_020da6dc);
    name->words[0] = vtable_word(data_020da5f8);
    TextString_ClearBytes((TextObject *) name);
    return name;
}
CLEAN_AS(func_0203a344, QuickMessage_NameConstruct)

/* func_0203a364 (a wide text's vtable slot 3): the address of its characters. */
int QuickMessage_WideBuffer(QuickMessageWide *wide)
{
    return (int) wide->words[WIDE_CHARS];
}
CLEAN_AS(func_0203a364, QuickMessage_WideBuffer)

/* func_0203a368 (slot 2): how many characters it has. */
int QuickMessage_WideCapacity(QuickMessageWide *wide)
{
    return (int) wide->words[WIDE_COUNT];
}
CLEAN_AS(func_0203a368, QuickMessage_WideCapacity)

/* func_0203a36c (slot 1): destroyed and freed. */
QuickMessageWide *QuickMessage_WideDestructDelete(QuickMessageWide *wide)
{
    wide->words[0] = vtable_word(data_020da628);
    func_020a887c(wide);
    func_020edb3c(wide);
    return wide;
}
CLEAN_AS(func_0203a36c, QuickMessage_WideDestructDelete)

/* func_0203a38c (slot 0): destroyed. */
QuickMessageWide *QuickMessage_WideDestruct(QuickMessageWide *wide)
{
    wide->words[0] = vtable_word(data_020da628);
    func_020a887c(wide);
    return wide;
}
CLEAN_AS(func_0203a38c, QuickMessage_WideDestruct)

/* func_0203a3a4: a wide text over `count` 16-bit characters at address `chars`. */
QuickMessageWide *QuickMessage_WideConstruct(QuickMessageWide *wide, int chars, int count)
{
    func_020a88ec(wide);
    wide->words[0] = vtable_word(data_020da628);
    wide->words[WIDE_CHARS] = (u32) chars;
    wide->words[WIDE_COUNT] = (u32) count;
    return wide;
}
CLEAN_AS(func_0203a3a4, QuickMessage_WideConstruct)

/* func_0203a3c4 (a message label's vtable slot 3): the address of its characters. */
int QuickMessage_TextBuffer(int text)
{
    return text + TEXT_CHARS_AT;
}
CLEAN_AS(func_0203a3c4, QuickMessage_TextBuffer)

/* func_0203a3c8 (slot 2) */
int QuickMessage_TextCapacity(void)
{
    return TEXT_CAPACITY;
}
CLEAN_AS(func_0203a3c8, QuickMessage_TextCapacity)

/* func_0203a3cc (slot 1): destroyed and freed. */
QuickMessageText *QuickMessage_TextDestructDelete(QuickMessageText *text)
{
    text->words[0] = vtable_word(data_020da640);
    func_020a8c38(text);
    func_020edb3c(text);
    return text;
}
CLEAN_AS(func_0203a3cc, QuickMessage_TextDestructDelete)

/* func_0203a3ec (slot 0): destroyed. */
QuickMessageText *QuickMessage_TextDestruct(QuickMessageText *text)
{
    text->words[0] = vtable_word(data_020da640);
    func_020a8c38(text);
    return text;
}
CLEAN_AS(func_0203a3ec, QuickMessage_TextDestruct)

/* A label's base (func_020a8cac constructs it) and its text emptied. */
extern void *func_020a8cac(QuickMessageText *text);

/* func_0203a404: an empty message label. */
QuickMessageText *QuickMessage_TextConstruct(QuickMessageText *text)
{
    func_020a8cac(text);
    text->words[0] = vtable_word(data_020da640);
    func_020a8c1c(text);
    return text;
}
CLEAN_AS(func_0203a404, QuickMessage_TextConstruct)

/* func_0203a424 (vtable slot 0 of a name label's base class, which other 8-bit labels share):
 * destroyed. */
void QuickMessage_NameBaseDestruct(QuickMessageName *name)
{
    name->words[0] = vtable_word(data_020da6dc);
}
CLEAN_AS(func_0203a424, QuickMessage_NameBaseDestruct)

/* func_0203a430 (slot 1): destroyed and freed. */
QuickMessageName *QuickMessage_NameBaseDestructDelete(QuickMessageName *name)
{
    name->words[0] = vtable_word(data_020da6dc);
    Heap_OperatorDeleteB(name);
    return name;
}
CLEAN_AS(func_0203a430, QuickMessage_NameBaseDestructDelete)

/* func_0203a448 (vtable slot 0 of the base class of views and wide texts): destroyed. */
void QuickMessage_ViewBaseDestruct(QuickMessageView *view)
{
    view->words[0] = vtable_word(data_020da6c4);
}
CLEAN_AS(func_0203a448, QuickMessage_ViewBaseDestruct)

/* func_0203a454 (slot 1): destroyed and freed. */
QuickMessageView *QuickMessage_ViewBaseDestructDelete(QuickMessageView *view)
{
    view->words[0] = vtable_word(data_020da6c4);
    Heap_OperatorDeleteB(view);
    return view;
}
CLEAN_AS(func_0203a454, QuickMessage_ViewBaseDestructDelete)
