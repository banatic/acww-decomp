/* The sign board: its number, its message and its life (sign_board.h). */
#include "sign_board.h"

#include "autoload_2/heap.h" /* Heap_FreeAux, Heap_AllocAuxZeroed */
#include "clean.h"
#include "main/message_receiver.h"
#include "main/name_texts.h"
#include "main/shadow.h"
#include "main/talk_object.h"
#include "main/town_record.h"

static_assert(offsetof(SceneActor, position) == 0x5c, "position");
static_assert(offsetof(SceneActor, receiver_vtable) == 0xec, "receiver");
static_assert(offsetof(SceneActor, message) == 0x10a, "receiver byte 0x1e");
static_assert(offsetof(SceneActor, link) == 0x12c, "receiver word 0x40");
static_assert(offsetof(SignBoard, number) == 0x2b4, "number");
static_assert(sizeof(SignBoard) == 0x2b8, "the size SignBoard_New allocates");

#define SIGN_BOARD_RECEIVER_OFFSET 0xec
/* It shows messages 1 to 14 of its file. */
#define SIGN_BOARD_MESSAGES 14
#define SIGN_BOARD_FIRST_MESSAGE 1
/* The talk's part that names the town's fruit. */
#define SIGN_BOARD_FRUIT_PART 1
/* The first fruit's item (town_record.h): the town's fruit is this plus its number. */
#define SIGN_BOARD_FIRST_FRUIT 0x1518

/* "obj_etc_board" */
extern const char data_ov003_02239724[];
/* The vtables: the class's and its receiver part's. */
extern const u8 data_ov003_022395e8[];
extern const u8 data_ov003_022396ac[];
/* The town's record in the state block. */
extern TownRecord data_021f39fc;

/* The count overlay 3 keeps at data_ov003_0223ce54. */
extern u16 func_ov003_022203d0(void);
/* Overlay 9's scene actor's destructor and constructor. */
extern void *func_ov009_0226539c(SignBoard *board);
extern void *func_ov009_0226552c(SignBoard *board);

/* func_ov003_0221e9d8 (vtable slot 0x8c): whether a talk asks main for a visit record; always
 * 0, so the talk starts at once. */
int SignBoard_WantsVisit(void)
{
    return 0;
}
CLEAN_AS(func_ov003_0221e9d8, SignBoard_WantsVisit)

/* func_ov003_0221e9dc (vtable slot 0x78, before a talk): names the receiver "obj_etc_board",
 * picks message 1 + (number % 14), and puts the name of the town's fruit in part 1 of the talk
 * (the first fruit, 0x1518, when the town's record holds no valid one). */
void SignBoard_PrepareTalk(SignBoard *board)
{
    MessageReceiver_SetName((MessageReceiver *) (void *) &board->actor.receiver_vtable, data_ov003_02239724);
    board->actor.message = (u8) (board->number % SIGN_BOARD_MESSAGES + SIGN_BOARD_FIRST_MESSAGE);

    u16 fruit = SIGN_BOARD_FIRST_FRUIT;
    if (data_021f39fc.own_fruit < TOWN_RECORD_FRUITS) {
        fruit = (u16) (SIGN_BOARD_FIRST_FRUIT + data_021f39fc.own_fruit);
    }
    NameText name;
    NameText_ConstructItem(&name, &fruit);
    TalkObject_SetPart((TalkObject *) (void *) board->actor.link, SIGN_BOARD_FRUIT_PART, (TextBase *) (void *) &name);
    NameText_Destruct(&name);
}
CLEAN_AS(func_ov003_0221e9dc, SignBoard_PrepareTalk)

/* func_ov003_0221ea50 (vtable slot 0x24, its drawing): a narrow shadow at its position; always
 * 1. */
int SignBoard_DrawShadow(SignBoard *board)
{
    ObjShadow_DrawNarrow(&board->actor.position);
    return 1;
}
CLEAN_AS(func_ov003_0221ea50, SignBoard_DrawShadow)

/* func_ov003_0221ea64 (vtable slot 0x70, setting it up): keeps overlay 3's count as its number;
 * always 1. */
int SignBoard_SetUp(SignBoard *board)
{
    board->number = func_ov003_022203d0();
    return 1;
}
CLEAN_AS(func_ov003_0221ea64, SignBoard_SetUp)

/* The vtables set back, then overlay 9's destructor. */
static void sign_board_destroy_parts(SignBoard *board)
{
    board->actor.vtable = data_ov003_022395e8;
    board->actor.receiver_vtable = data_ov003_022396ac;
    func_ov009_0226539c(board);
}

/* func_ov003_0221ea7c (vtable slot 0x44, the deleting destructor): the destructor's work, then
 * the memory freed. */
SignBoard *SignBoard_DestroyAndFree(SignBoard *board)
{
    sign_board_destroy_parts(board);
    Heap_FreeAux(board);
    return board;
}
CLEAN_AS(func_ov003_0221ea7c, SignBoard_DestroyAndFree)

/* func_ov003_0221eaa8 (vtable slot 0x40): the destructor, without freeing. */
SignBoard *SignBoard_Destroy(SignBoard *board)
{
    sign_board_destroy_parts(board);
    return board;
}
CLEAN_AS(func_ov003_0221eaa8, SignBoard_Destroy)

/* func_ov003_0221eacc: the constructor: overlay 9's, then the vtables. */
SignBoard *SignBoard_Construct(SignBoard *board)
{
    func_ov009_0226552c(board);
    board->actor.vtable = data_ov003_022395e8;
    board->actor.receiver_vtable = data_ov003_022396ac;
    return board;
}
CLEAN_AS(func_ov003_0221eacc, SignBoard_Construct)

/* func_ov003_0221eaf0 (the class's entry in the overlay's table of profiles): allocates and
 * constructs one; nothing keeps the pointer here. */
void SignBoard_New(void)
{
    SignBoard *board = Heap_AllocAuxZeroed(sizeof(SignBoard));
    if (board != NULL) {
        SignBoard_Construct(board);
    }
}
CLEAN_AS(func_ov003_0221eaf0, SignBoard_New)

/* The board around its receiver part, as the receiver vtable's thunks find it. */
static SignBoard *sign_board_from_receiver(void *receiver)
{
    return (SignBoard *) (void *) ((u8 *) receiver - SIGN_BOARD_RECEIVER_OFFSET);
}

/* _ZThn236_N18Obj_ov003_022395e8D0Ev (receiver slot 0x04): SignBoard_DestroyAndFree. */
SignBoard *SignBoard_ReceiverDestroyAndFree(void *receiver)
{
    return SignBoard_DestroyAndFree(sign_board_from_receiver(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov003_022395e8D0Ev, SignBoard_ReceiverDestroyAndFree)

/* _ZThn236_N18Obj_ov003_022395e8D1Ev (receiver slot 0x00): SignBoard_Destroy. */
SignBoard *SignBoard_ReceiverDestroy(void *receiver)
{
    return SignBoard_Destroy(sign_board_from_receiver(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov003_022395e8D1Ev, SignBoard_ReceiverDestroy)
