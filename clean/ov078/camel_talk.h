/* The camel's talk scene (class vtable 0x02279a9c, at 0x658 of the camel, camel.h): a scene of
 * class 0x020d9ff8 (obj_020d9ff8.h) that shows the lines of the message file "sp_npc_camel".
 *
 * Its vtable slots, beyond those of the scene class:
 * - 0x78 (CamelTalk_FirstLine): the line the talk starts with, by the player's errand (the
 *   entry at 0x94 of the player's villager part, villager_part_entry.h, whose object's bits 0-4
 *   are the errand's step) and whether the pockets hold item 0x13ac;
 * - 0x18 (CamelTalk_OnAnswer): the player's answer to the line shown;
 * - 0x14 (CamelTalk_OnLineEnded): a line ended: the errand handed over, the reward drawn, given
 *   and marked, or item 0x13ac taken for another item.
 *
 * The errand's steps as she reads and sets them: 0 handed over (its villager's name is put in
 * the talk's part 0), 1 done by the player (she draws the reward: line 0x0c), 2 the reward
 * offered, 3 the reward given (event 0x3e marked taken part in). */
#ifndef CLEAN_OV078_CAMEL_TALK_H
#define CLEAN_OV078_CAMEL_TALK_H

#include "main/scene_base.h"
#include "types.h"

struct Camel;

/* The two items drawn for her reward (CamelTalk.rewards). */
#define CAMEL_TALK_REWARDS 2

/* What CamelTalk.pocket holds besides the slot of item 0x13ac in the pockets. */
#define CAMEL_TALK_POCKET_UNKNOWN (-1) /* not looked for yet */
#define CAMEL_TALK_POCKET_DONE (-2)    /* taken, or the player declined, in this visit */

/* The talk scene (0xbc bytes). */
typedef struct CamelTalk {
    SceneBase scene;                 /* 0x00: the receiver's message (byte 0x1e) is the line shown */
    u8 unk_80[0x30];                 /* 0x80: the scene's commands (scene_command.h) */
    struct Camel *owner;             /* 0xb0 */
    s32 pocket;                      /* 0xb4: the slot of item 0x13ac, or CAMEL_TALK_POCKET_* */
    u16 rewards[CAMEL_TALK_REWARDS]; /* 0xb8: item code objects; 0xfff1 when made */
} CamelTalk;

/* What its slot 0x78 gives: the message file's name (an address) and the line to say. */
typedef struct CamelTalkLine {
    u32 text;
    u8 message;
    u8 unk_05[3];
} CamelTalkLine;

/* The lines of "sp_npc_camel" her code picks. */
#define CAMEL_LINE_REWARD_GIVEN 0x00 /* the errand's step is 3 */
#define CAMEL_LINE_FIRST_TODAY 0x01  /* the first talk of the day (daily bit 0x0b) */
#define CAMEL_LINE_OFFER 0x02        /* answered 0: line 0x05, or 0x1d with no free slot */
#define CAMEL_LINE_NO_ERRAND 0x04    /* no errand: as line 0x02 */
#define CAMEL_LINE_ERRAND 0x05       /* ends with the errand handed over */
#define CAMEL_LINE_ERRAND_155F 0x06  /* the errand's item is 0x155f */
#define CAMEL_LINE_ERRAND_OTHER 0x07 /* another item */
#define CAMEL_LINE_ERRAND_GIVEN 0x08
#define CAMEL_LINE_ERRAND_OPEN 0x09 /* the errand at step 0 */
#define CAMEL_LINE_ERRAND_NEXT 0x0a /* the errand advanced (VillagerPartEntry_Advance) */
#define CAMEL_LINE_ERRAND_NEXT_GIVEN 0x0b
#define CAMEL_LINE_REWARD_DRAW 0x0c   /* the errand at step 1: ends with the reward drawn */
#define CAMEL_LINE_REWARD_CHOICE 0x0d /* the player picks one of the two items */
#define CAMEL_LINE_REWARD_CHOICE_2 0x13
#define CAMEL_LINE_REWARD_TAKEN 0x0e /* ends with the errand's step 3 */
#define CAMEL_LINE_NO_ROOM 0x12      /* the pockets have no free slot */
#define CAMEL_LINE_TRADE_ASK 0x14    /* the pockets hold item 0x13ac; answered 0: taken, line 0x16 */
#define CAMEL_LINE_TRADE_DECLINED 0x15
#define CAMEL_LINE_TRADE 0x16 /* ends with item 0x37e0 (line 0x17) or 0x34a8 (0x18) given */
#define CAMEL_LINE_TRADE_37E0 0x17
#define CAMEL_LINE_TRADE_34A8 0x18
#define CAMEL_LINE_POCKETS_FULL 0x1d

void CamelTalk_OnAnswer(CamelTalk *talk);
void CamelTalk_OnLineEnded(CamelTalk *talk);
void CamelTalk_FirstLine(CamelTalk *talk, CamelTalkLine *out);
void CamelTalk_Begin(CamelTalk *talk, struct Camel *owner);
CamelTalk *CamelTalk_DestructDelete(CamelTalk *talk);
CamelTalk *CamelTalk_Destruct(CamelTalk *talk);
CamelTalk *CamelTalk_Construct(CamelTalk *talk);

#endif
