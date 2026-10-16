/* The "obj_etc_board" scene object (etc_board.h). */
#include "etc_board.h"

#include <assert.h>
#include <stddef.h>

#include "clean.h"

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

extern void func_0203ee08(EtcBoard *board, void *receiver);
extern int func_0203e020(EtcBoard *board);
extern void func_0203ee14(EtcBoard *board, void *receiver);
/* Copies at most 25 characters of `name` into the receiver's name. */
extern void func_020a8164(void *receiver, const char *name);
/* A string object: built by func_02094fd4, destroyed by func_02094fbc. */
extern void *func_02094fd4(void *text);
extern void *func_02094fbc(void *text);
/* Entry `index` of the table, or null when `index` is 8 or more. */
extern void *func_0207cec0(void *table, int index);
/* 0x7a0 bytes into an entry. */
extern void *func_0208150c(void *entry);
extern int func_02003618(void *source, void *text);
extern void func_02068404(EtcBoardLink *link, int line, void *text);
extern void func_0203edd0(EtcBoard *board);
extern int func_020ea990(const Vec3 *a, const Vec3 *b);
extern void *func_020b6590(void);
extern void func_020b7d84(void *renderer, void *member, Vec3 *position, int scale, int kind, u8 index);
extern void func_0203efb0(EtcBoard *board, u32 value);
/* The member at 0x138, the receiver part and the base: destructors and constructors. */
extern void func_020b7f60(void *member);
extern void func_02066994(void *receiver);
extern void func_0203f080(EtcBoard *board);
extern void func_020b7f70(void *member);
extern void func_02066a30(void *receiver);
extern void func_0203f130(EtcBoard *board);
/* operator delete and operator new */
extern void func_020edf54(void *block);
extern void *func_020edf70(u32 size);

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
        func_0203ee08(board, receiver_of(board));
        func_0203e020(board);
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

    func_0203ee14(board, receiver_of(board));
    func_020a8164(&board->receiver_vtable, data_ov003_022380f0);
    board->receiver_unk_1E = 0;
    board->link->requested = 1;

    func_02094fd4(text);
    func_02003618(func_0208150c(func_0207cec0(data_021e5a2c, (int) board->index)), text);
    func_02068404(board->link, 0, text);
    func_02094fbc(text);
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
    func_0203edd0(board);
    return viewer != NULL && func_020ea990(&viewer->position, &board->position) < 0x2333 &&
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
    func_020b7d84(func_020b6590(), board->member_138, &board->position, 0xc00, 9, (u8) board->index);
    return 1;
}
CLEAN_AS(_ZN18Obj_ov003_0223801019func_ov003_0220c1a8Ev, EtcBoard_Run)

/* func_ov003_0220c1e4 (vtable slot 0x00): starts the board idle and enters it in the table
 * under its index (emptying the table first when it holds none); always 1.
 * REQUIRES: the index is 0-7. */
int EtcBoard_Init(EtcBoard *board)
{
    EtcBoard_ClearTableIfEmpty();
    func_0203efb0(board, (u16) board->index);
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
    func_020b7f60(board->member_138);
    func_02066994(&board->receiver_vtable);
    func_0203f080(board);
    func_020edf54(board);
    return board;
}
CLEAN_AS(func_ov003_0220c220, EtcBoard_DestroyAndFree)

/* func_ov003_0220c260: the destructor, without freeing. */
EtcBoard *EtcBoard_Destroy(EtcBoard *board)
{
    board->vtable = data_ov003_02238010;
    board->receiver_vtable = data_ov003_02238078;
    func_020b7f60(board->member_138);
    func_02066994(&board->receiver_vtable);
    func_0203f080(board);
    return board;
}
CLEAN_AS(func_ov003_0220c260, EtcBoard_Destroy)

/* func_ov003_0220c29c: the constructor: the base and the receiver part, then the vtables and
 * the member at 0x138. */
EtcBoard *EtcBoard_Construct(EtcBoard *board)
{
    func_0203f130(board);
    func_02066a30(&board->receiver_vtable);
    board->vtable = data_ov003_02238010;
    board->receiver_vtable = data_ov003_02238078;
    func_020b7f70(board->member_138);
    return board;
}
CLEAN_AS(func_ov003_0220c29c, EtcBoard_Construct)

/* func_ov003_0220c2d4: allocates and constructs a board; nothing keeps the pointer here. */
void EtcBoard_New(void)
{
    EtcBoard *board = func_020edf70(sizeof(EtcBoard));
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
