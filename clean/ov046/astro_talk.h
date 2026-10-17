/* The talk scene of overlay 46's character (class vtable 0x0226204c, at 0x658 of the
 * character, astro.h): a scene of class 0x020d9ff8 (obj_020d9ff8.h) that shows the lines of the
 * archive "sp_npc_astro" and opens the screens that make and change the players'
 * constellations (constellations.h).
 *
 * Its vtable slots:
 * - 0x78 (AstroTalk_Line): the first line, by the topic (ASTRO_TALK_TOPIC_*);
 * - 0x14 (AstroTalk_OnLineShown): the handlers of the line shown (the receiver's message, byte
 *   0x1e) from a table keyed by line, without the player's answer;
 * - 0x18 (AstroTalk_OnAnswer): the same with the player's answer, from a second table;
 * - 0x84 (AstroTalk_RunAfterScreen): when a command of the scene ends, the function a handler
 *   left to run after the screen it opened (AstroTalk_SetAfterScreen), once;
 * - 0x88 (AstroTalk_ListConstellations): the kept constellations offered as answers, four at a
 *   time from `cursor`, and a last answer to go on or to stop.
 * A handler sets `next_line`; when it is not 0xff that line is shown next.
 *
 * A list's `purpose` says what the constellation picked from it is for (ASTRO_TALK_PURPOSE_*). */
#ifndef CLEAN_OV046_ASTRO_TALK_H
#define CLEAN_OV046_ASTRO_TALK_H

#include "main/scene_base.h"
#include "ov004/member_pointer.h"
#include "types.h"

struct Astro;

/* The topics (AstroTalk.topic): which line it starts with (AstroTalk_Line). */
#define ASTRO_TALK_TOPIC_FIRST_BUSY 0 /* the first talk of the day, after its animation */
#define ASTRO_TALK_TOPIC_FIRST 1      /* the first talk of the day */
#define ASTRO_TALK_TOPIC_AGAIN_BUSY 2 /* a later talk, after its animation */
#define ASTRO_TALK_TOPIC_AGAIN 3      /* a later talk */
#define ASTRO_TALK_TOPIC_CALLED 4     /* the player called it over (Astro_TakeCall) */
#define ASTRO_TALK_TOPIC_PENDING 5    /* one of 0-3, picked when the line is asked for */
#define ASTRO_TALK_TOPICS 5

/* What a constellation picked from the list is for. */
#define ASTRO_TALK_PURPOSE_REMOVE 0 /* asked to confirm, then removed */
#define ASTRO_TALK_PURPOSE_TIME 1   /* the time it is in view told */
#define ASTRO_TALK_PURPOSE_SCREEN 2 /* screen mode 0x2e opened on it */

/* The answers a list shows at most, and its entries (the last for "go on" or "stop"). */
#define ASTRO_TALK_LIST_ANSWERS 4
#define ASTRO_TALK_LIST_ENTRIES 5

/* No line next. */
#define ASTRO_TALK_NO_LINE 0xff

/* The talk scene (0xe0 bytes). */
typedef struct AstroTalk {
    SceneBase scene;                     /* 0x00: the receiver's message (byte 0x1e) is the line shown */
    u8 unk_80[0x30];                     /* 0x80 */
    u32 topic;                           /* 0xb0: ASTRO_TALK_TOPIC_* */
    struct Astro *owner;                 /* 0xb4 */
    MemberPointer after_screen;          /* 0xb8: run once the screen's command ends; null for none */
    s32 constellation;                   /* 0xc0: the constellation worked on, -1 for none */
    u8 cursor;                           /* 0xc4: the first constellation the list looks at next */
    u8 remaining;                        /* 0xc5: the kept constellations not yet listed */
    u8 purpose;                          /* 0xc6: ASTRO_TALK_PURPOSE_* */
    u8 unk_c7;                           /* 0xc7 */
    s32 listed[ASTRO_TALK_LIST_ENTRIES]; /* 0xc8: each answer's constellation, -1 for none */
    s32 next_line;                       /* 0xdc: the line to show next, ASTRO_TALK_NO_LINE for none */
} AstroTalk;

/* What its slot 0x78 gives: the archive's name and the line to say. */
typedef struct AstroTalkLine {
    const char *name;
    u8 message;
    u8 unk_05[3];
} AstroTalkLine;

/* The handlers of the answers, by the line answered. */
void AstroTalk_OnAnswer38(AstroTalk *talk, int answer);
void AstroTalk_OnAnswer35(AstroTalk *talk, int answer);
void AstroTalk_OnAnswer24(AstroTalk *talk, int answer);
void AstroTalk_OnAnswer20(AstroTalk *talk, int answer);
void AstroTalk_OnAnswerMenuShared(AstroTalk *talk, int answer);
void AstroTalk_OnAnswerMake(AstroTalk *talk, int answer);
void AstroTalk_OnAnswerRemove(AstroTalk *talk, int answer);
void AstroTalk_OnAnswerMenuWithKept(AstroTalk *talk, int answer);
void AstroTalk_OnAnswerMenuNoneKept(AstroTalk *talk, int answer);
void AstroTalk_OnAnswerDiscard(AstroTalk *talk, int answer);
void AstroTalk_OnAnswer31(AstroTalk *talk, int answer);
void AstroTalk_OnPick(AstroTalk *talk, int answer);
void AstroTalk_OnAnswer08(AstroTalk *talk, int answer);
void AstroTalk_OnAnswer(AstroTalk *talk);

/* The handlers of the lines shown. */
void AstroTalk_OpenScreen2d(AstroTalk *talk);
void AstroTalk_OpenScreen12ForChanged(AstroTalk *talk);
void AstroTalk_OpenScreen12ForNew(AstroTalk *talk);
void AstroTalk_List(AstroTalk *talk);
void AstroTalk_ToMenu(AstroTalk *talk);
void AstroTalk_RandomLine(AstroTalk *talk);
void AstroTalk_MakeInFreeSlot(AstroTalk *talk);
void AstroTalk_CalledLine(AstroTalk *talk);
void AstroTalk_TellNew(AstroTalk *talk);
void AstroTalk_OnLineShown(AstroTalk *talk);

/* The menu, the first line and the topic. */
int AstroTalk_MenuLine(AstroTalk *talk);
void AstroTalk_Line(AstroTalk *talk, AstroTalkLine *line);
void AstroTalk_SetTopic(AstroTalk *talk, unsigned long topic);
void AstroTalk_SetOwner(AstroTalk *talk, struct Astro *owner);

/* Its life. */
void AstroTalk_Reset(AstroTalk *talk);
AstroTalk *AstroTalk_DestructDelete(AstroTalk *talk);
AstroTalk *AstroTalk_Destruct(AstroTalk *talk);
AstroTalk *AstroTalk_Construct(AstroTalk *talk);

/* What runs after a screen. */
void AstroTalk_AfterScreen12Changed(AstroTalk *talk);
void AstroTalk_AfterScreen2eChanged(AstroTalk *talk);
void AstroTalk_AfterScreen12New(AstroTalk *talk);
void AstroTalk_AfterScreen2eNew(AstroTalk *talk);
void AstroTalk_AfterScreen2d(AstroTalk *talk);
void AstroTalk_SetAfterScreen(AstroTalk *talk, int after);
void AstroTalk_RunAfterScreen(AstroTalk *talk);
void AstroTalk_ListConstellations(AstroTalk *talk);

#endif
