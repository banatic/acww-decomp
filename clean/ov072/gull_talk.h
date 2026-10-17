/* The talk scene of overlay 72's character (class vtable 0x02279a78, at 0x658 of the character,
 * gull.h): a scene of class 0x020d9ff8 (obj_020d9ff8.h) that shows the lines of the archive
 * "sp_npc_gull" and keeps the count of item 0x1568 the character takes (item_1568_count.h).
 *
 * Its vtable slots:
 * - 0x78 (GullTalk_Line): the first line, by the talk's topic (GULL_TALK_TOPIC_*), which it
 *   picks itself: the first talk of the day (daily bit 0x14 of the player) before or after the
 *   count's mark, five counted, or how many of item 0x1568 the player brings. Each of item
 *   0x1568 in the player's pockets is taken out and counted (up to five);
 * - 0x14 (GullTalk_OnLineShown): what follows the line shown (the receiver's message, byte
 *   0x1e): the closing of the first talk, the placing of item 0x1568 in the town
 *   (gull_spots.h), and the gift once five were counted;
 * - 0x18 (GullTalk_OnAnswer): the player's answer read and dropped;
 * - 0x80 and 0x84: the scene's steps, a table of member functions with a flag (the scene's
 *   table data_ov072_02279a24): a step with the flag runs each frame while the talk's link is
 *   open, one without runs once it closes and the scene goes back to step 0. Step 1, entered
 *   when line 0 is shown, plays the character's animation 0xd5 once the talk window is gone,
 *   turns it to the player, sets the count's mark and shows one of the lines 5-9. */
#ifndef CLEAN_OV072_GULL_TALK_H
#define CLEAN_OV072_GULL_TALK_H

#include "main/scene_base.h"
#include "ov004/member_pointer.h"
#include "types.h"

struct Gull;

/* The topics (GullTalk.topic): which line it starts with (GullTalk_Line). */
#define GULL_TALK_TOPIC_FIRST_MEETING 0 /* the first talk of the day, no mark: one of lines 0-4 */
#define GULL_TALK_TOPIC_1 1             /* line 5; this code never picks it */
#define GULL_TALK_TOPIC_FIRST_MARKED 2  /* the first talk of the day after the mark: line 0x1e */
#define GULL_TALK_TOPIC_ALL_COUNTED 3   /* five counted: one of lines 0xd-0x11 */
#define GULL_TALK_TOPIC_NONE_YET 4      /* none counted and none in the pockets: line 0x12 */
#define GULL_TALK_TOPIC_MORE_NEEDED 5   /* some counted, none in the pockets: line 0x13 */
#define GULL_TALK_TOPIC_BROUGHT_AGAIN 6 /* some taken from the pockets, not the first time today */
#define GULL_TALK_TOPIC_BROUGHT 7       /* some taken from the pockets, the first time today */
#define GULL_TALK_TOPICS 8

/* The scene's steps (GullTalk.step). */
#define GULL_TALK_STEP_NONE 0
#define GULL_TALK_STEP_TURN_TO_PLAYER 1
#define GULL_TALK_STEPS 2

/* The talk scene (0xc0 bytes). */
typedef struct GullTalk {
    SceneBase scene;    /* 0x00: the receiver's message (byte 0x1e) is the line shown */
    u8 unk_80[0x30];    /* 0x80 */
    s32 step;           /* 0xb0: GULL_TALK_STEP_* */
    u8 step_state;      /* 0xb4: how far step 1 is */
    u8 unk_b5[3];       /* 0xb5 */
    s32 topic;          /* 0xb8: GULL_TALK_TOPIC_* */
    struct Gull *owner; /* 0xbc */
} GullTalk;

/* What its slot 0x78 gives (and a row of the table data_ov072_02279874): the archive's name
 * and the line to say. */
typedef struct GullTalkLine {
    const char *name;
    u8 message;
    u8 unk_05[3];
} GullTalkLine;

/* A step of the scene: its member function and whether it runs each frame while the talk's
 * link is open (else once it closes). */
typedef struct GullTalkStep {
    MemberPointer run;
    u8 each_frame;
    u8 unk_09[3];
} GullTalkStep;
extern GullTalkStep data_ov072_02279a24[GULL_TALK_STEPS];

/* Its life. */
GullTalk *GullTalk_DestructDelete(GullTalk *talk);
GullTalk *GullTalk_Destruct(GullTalk *talk);
GullTalk *GullTalk_Construct(GullTalk *talk);
void GullTalk_Begin(GullTalk *talk, struct Gull *owner);

/* Its slots and steps. */
void GullTalk_OnAnswer(GullTalk *talk);
void GullTalk_OnLineShown(GullTalk *talk);
void GullTalk_Line(GullTalk *talk, GullTalkLine *line);
void GullTalk_StepTurnToPlayer(GullTalk *talk);
void GullTalk_SetStep(GullTalk *talk, int step);
void GullTalk_OnTalkClosed(GullTalk *talk);
void GullTalk_WhileTalkOpen(GullTalk *talk);

#endif
