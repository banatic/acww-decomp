/* The talk scene of overlay 73's character (class vtable 0x02279a70, at 0x658 of the character,
 * boar.h): a scene of class 0x020d9ff8 (obj_020d9ff8.h) that shows the lines of the archive
 * "sp_npc_boar" and sells the counted items 0x1531-0x153a (town_spoil.h) by tens at the
 * week's turnip price (turnip_prices.h), and item 0x1567 for 1000 Bells once a week (flag 4 of
 * the state block, which turnip_prices.h clears a week after).
 *
 * Its vtable slots:
 * - 0x78 (BoarTalk_Line): the first line, by the topic: line 0 the first talk of the day
 *   (daily bit 3 of the player), else line 4;
 * - 0x14 (BoarTalk_OnLineShown): line 0x12 opens the screen of mode 0x3a where the player picks
 *   how many tens to buy; line 0x15 goes on to 0x1a (item 0x1567 sold) or 0x16;
 * - 0x18 (BoarTalk_OnAnswer): the player's answer to the line shown: the price put in, the
 *   purchase checked (the Bells, a free slot, room for the items) and made;
 * - 0x84 (BoarTalk_RunAfterScreen): when a command of the scene ends, the function left to run
 *   after the screen it opened (BoarTalk_SetAfterScreen), once. */
#ifndef CLEAN_OV073_BOAR_TALK_H
#define CLEAN_OV073_BOAR_TALK_H

#include "main/scene_base.h"
#include "ov004/member_pointer.h"
#include "types.h"

struct Boar;

/* The topics (BoarTalk.topic): which line it starts with (BoarTalk_Line). */
#define BOAR_TALK_TOPIC_FIRST 0 /* the first talk of the day: line 0 */
#define BOAR_TALK_TOPIC_AGAIN 1 /* a later talk: line 4 */
#define BOAR_TALK_TOPICS 3      /* topic 2 (no archive, line 0) is never taken */

/* What runs after a screen (BoarTalk_SetAfterScreen). */
#define BOAR_TALK_AFTER_COUNT_PICKED 0
#define BOAR_TALK_AFTERS 1

/* The talk scene (0xcc bytes). */
typedef struct BoarTalk {
    SceneBase scene;            /* 0x00: the receiver's message (byte 0x1e) is the line shown */
    u8 unk_80[0x30];            /* 0x80 */
    u32 topic;                  /* 0xb0: BOAR_TALK_TOPIC_* */
    struct Boar *owner;         /* 0xb4 */
    MemberPointer after_screen; /* 0xb8: run once the screen's command ends; null for none */
    s32 price;                  /* 0xc0: the Bells the tens picked cost */
    s32 tens;                   /* 0xc4: how many tens were picked */
    u8 sold_1567;               /* 0xc8: the sale was item 0x1567 */
    u8 unk_c9[3];               /* 0xc9 */
} BoarTalk;

/* What its slot 0x78 gives (and a row of the table data_ov073_02279844): the archive's name
 * and the line to say. */
typedef struct BoarTalkLine {
    const char *name;
    u8 message;
    u8 unk_05[3];
} BoarTalkLine;

/* Its slots. */
void BoarTalk_OnAnswer(BoarTalk *talk);
void BoarTalk_OnLineShown(BoarTalk *talk);
void BoarTalk_Line(BoarTalk *talk, BoarTalkLine *line);
void BoarTalk_Begin(BoarTalk *talk, struct Boar *owner);
int BoarTalk_GiveTens(BoarTalk *talk);
int BoarTalk_IsEmptySlot(u16 *item);

/* Its life. */
void BoarTalk_Reset(BoarTalk *talk);
BoarTalk *BoarTalk_DestructDelete(BoarTalk *talk);
BoarTalk *BoarTalk_Destruct(BoarTalk *talk);
BoarTalk *BoarTalk_Construct(BoarTalk *talk);

/* What runs after a screen. */
void BoarTalk_AfterCountPicked(BoarTalk *talk);
void BoarTalk_SetAfterScreen(BoarTalk *talk, int after);
void BoarTalk_RunAfterScreen(BoarTalk *talk);

#endif
