/* A sign board of overlay 3 (class Obj_ov003_022395e8, vtable 0x022395e8, receiver part
 * 0x022396ac, 0x2b8 bytes; profile 0x20): a scene object whose message receiver is named
 * "obj_etc_board". It is derived from overlay 9's town object actor (ov009/town_object_actor.h), which runs
 * the rest; talking to it starts at once, without asking main for a visit record (vtable slot
 * 0x8c says no).
 *
 * Set up (slot 0x70), it keeps as its number the halfword overlay 3 counts up at
 * data_ov003_0223ce54 while it places the town's objects (func_ov003_02220520). Before a talk
 * (slot 0x78) it shows message 1 + (number % 14) of "obj_etc_board", with the name of the
 * town's own fruit (town_record.h) as part 1 of the talk. Its drawing (slot 0x24) draws a
 * narrow shadow at its position. The messages are the town's notice signs: fishing tips
 * (messages 1 and 2), the fruit Nook buys (5, with the town's fruit) and other hints. */
#ifndef CLEAN_OV003_SIGN_BOARD_H
#define CLEAN_OV003_SIGN_BOARD_H

#include "ov009/town_object_actor.h"
#include "types.h"

typedef struct SignBoard {
    TownObjectActor actor;
    u16 number; /* 0x2b4: picks its message */
    u8 unk_2B6[2];
} SignBoard;

int SignBoard_WantsVisit(void);
void SignBoard_PrepareTalk(SignBoard *board);
int SignBoard_DrawShadow(SignBoard *board);
int SignBoard_SetUp(SignBoard *board);
SignBoard *SignBoard_DestroyAndFree(SignBoard *board);
SignBoard *SignBoard_Destroy(SignBoard *board);
SignBoard *SignBoard_Construct(SignBoard *board);
void SignBoard_New(void);
SignBoard *SignBoard_ReceiverDestroyAndFree(void *receiver);
SignBoard *SignBoard_ReceiverDestroy(void *receiver);

#endif
