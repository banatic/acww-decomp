/* The talk scene of overlay 87's character (acorn_npc.h: AcornNpcTalk, vtable 0x0227945c).
 *
 * Its vtable slots, beyond those of main's scene class 0x020d9ff8: 0x00 and 0x04 its
 * destructors, 0x14 a line ended (AcornNpcTalk_OnLineEnded), 0x18 the player's answer
 * (AcornNpcTalk_OnAnswer) and 0x78 the line the talk starts with (AcornNpcTalk_FirstLine).
 *
 * What it does, by the lines of "sp_npc_acorn" (ACORN_NPC_LINE_*):
 * - the items 0x1542-0x1546 (ACORN_NPC_ITEM_FIRST to _LAST) the player brings are taken out of
 *   the pockets; unless one of them is 0x1546 (compared without its variant), each is a point
 *   of the player record's object at 0x2416 (PlayerField2416_Points);
 * - the points reach the rewards of a table of twelve levels (data_ov087_02279324): at each
 *   level, an item given once the points reach the level's bound (PlayerField2416_Level, raised
 *   when the item is given);
 * - once a day it offers a fortune: a letter of "ev_fortune" whose four parts are messages of
 *   "st_fortune" (one of four kinds) and "st_fortune2" (lines of that kind).
 *
 * Its daily bits (TalkChecks_TestSetDailyBit): 0x19 talked today, 0x1a the fortune given
 * today. Flag 0x0f of the player record: met the character. */
#ifndef CLEAN_OV087_ACORN_NPC_TALK_H
#define CLEAN_OV087_ACORN_NPC_TALK_H

#include "acorn_npc.h"
#include "types.h"

/* What the first line function gives: the message file's name (an address) and the message. */
typedef struct AcornNpcLine {
    u32 text;
    u8 message;
    u8 unk_05[3];
} AcornNpcLine;

/* A level of the rewards (data_ov087_02279324). */
typedef struct AcornNpcLevel {
    u16 item;  /* 0x00: the reward */
    u8 points; /* 0x02: the points it needs */
    u8 unk_03;
} AcornNpcLevel;

#define ACORN_NPC_LEVELS 12

/* A part of the fortune letter (data_ov087_02279304): the message file it is read from and the
 * letter's part it goes into. */
typedef struct AcornNpcFortunePart {
    const char *file;
    s32 part;
} AcornNpcFortunePart;

#define ACORN_NPC_FORTUNE_PARTS 4

/* The items it takes, and the one that spoils the lot. */
#define ACORN_NPC_ITEM_FIRST 0x1542
#define ACORN_NPC_ITEM_LAST 0x1546
#define ACORN_NPC_ITEM_SPOILER 0x1546

/* No line (the lines are bytes). */
#define ACORN_NPC_NO_LINE 0xff

/* The lines of "sp_npc_acorn". */
#define ACORN_NPC_LINE_MEET 0x00         /* the first talk ever */
#define ACORN_NPC_LINE_TODAY 0x02        /* the first talk today */
#define ACORN_NPC_LINE_AGAIN 0x03        /* a later talk */
#define ACORN_NPC_LINE_NEEDED 0x04       /* the points still needed (value slot 1) */
#define ACORN_NPC_LINE_BROUGHT 0x05      /* how many of the items the pockets hold (slot 2) */
#define ACORN_NPC_LINE_TAKEN 0x07        /* 0x07-0x09: taken for points */
#define ACORN_NPC_LINE_POINTS 0x0a       /* the points (slot 0) */
#define ACORN_NPC_LINE_REWARD 0x0b       /* a reward is due (its name in slot 0) */
#define ACORN_NPC_LINE_NO_ROOM 0x0c      /* no room for the reward */
#define ACORN_NPC_LINE_NEXT_REWARD 0x0d  /* given, and the next one is due too */
#define ACORN_NPC_LINE_GIVEN 0x0e        /* given */
#define ACORN_NPC_LINE_NOT_YET 0x0f      /* not due: the points still needed (slot 1) */
#define ACORN_NPC_LINE_FORTUNE 0x10      /* offers the fortune */
#define ACORN_NPC_LINE_NO_LETTER 0x12    /* no free letter for it */
#define ACORN_NPC_LINE_FORTUNE_DONE 0x13 /* the fortune written */
#define ACORN_NPC_LINE_14 0x14           /* ends with item 0x1565 shown, then 0x15 */
#define ACORN_NPC_LINE_15 0x15
/* After 0x02/0x03 when the points reach the level's bound; after 0x07-0x09 when every level
 * was given. */
#define ACORN_NPC_LINE_16 0x16
#define ACORN_NPC_LINE_ALL_GIVEN 0x17    /* every level given (after 0x02/0x03) */
#define ACORN_NPC_LINE_SPOILED_SOME 0x18 /* 0x1546 among the others: no points */
#define ACORN_NPC_LINE_SPOILED_ALL 0x19  /* only 0x1546: no points */

void AcornNpcTalk_OnAnswer(AcornNpcTalk *talk);
void AcornNpcTalk_OnLineEnded(AcornNpcTalk *talk);
int AcornNpcTalk_IsItemInState0(u16 *item, int state);
void AcornNpcTalk_FirstLine(AcornNpcTalk *talk, AcornNpcLine *out);
void AcornNpcTalk_Begin(AcornNpcTalk *talk, AcornNpc *owner);
void *AcornNpcTalk_Delete(void *talk);
void *AcornNpcTalk_Destroy(void *talk);
void *AcornNpcTalk_Construct(void *talk);

#endif
