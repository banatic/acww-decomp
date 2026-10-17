/* The talk scene of overlay 88's character (reaction_npc.h: ReactionNpcTalk, vtable 0x02279c58).
 *
 * Its vtable slots, beyond those of main's scene class 0x020d9ff8: 0x00 and 0x04 its
 * destructors, 0x14 a line ended (ReactionNpcTalk_OnLineEnded), 0x18 the player's answer
 * (ReactionNpcTalk_OnAnswer), 0x78 the line the talk starts with (ReactionNpcTalk_FirstLine),
 * 0x80 and 0x84 the scene's steps (a table of member functions with a flag, data_ov088_02279c14:
 * a step with the flag runs each frame while the talk's link is open, one without runs once
 * it closes and the scene goes back to step 0; only step 0, which has no function, lacks the
 * flag) and 0x88 the answers offered (ReactionNpcTalk_SetAnswers).
 *
 * What it does, by the lines of "sp_npc_reaction" (REACTION_NPC_LINE_*): it shows a reaction
 * (line 0x1c plus the reaction's number) and watches for the number its motion shows to be
 * taken (ReactionNpc.watch, ReactionNpc_MotionNumber); taken in time, the reaction is put in
 * an empty motion slot of the player, or in one the player gives up. The first lesson teaches
 * reaction 0x17 into slot 0; later ones offer four reactions not known yet, drawn at random.
 *
 * Its daily bit (TalkChecks_TestSetDailyBit) 0x0e: taught today. Flag 0x10 of the player
 * record: taught once. */
#ifndef CLEAN_OV088_REACTION_NPC_TALK_H
#define CLEAN_OV088_REACTION_NPC_TALK_H

#include "ov004/member_pointer.h"
#include "reaction_npc.h"
#include "types.h"

/* What the first line function gives: the message file's name (an address) and the message. */
typedef struct ReactionNpcLine {
    u32 text;
    u8 message;
    u8 unk_05[3];
} ReactionNpcLine;

/* The scene's steps (ReactionNpcTalk.step). */
enum ReactionNpcTalkSteps {
    REACTION_NPC_STEP_NONE = 0,
    REACTION_NPC_STEP_FIRST_LESSON = 1, /* watches the first reaction, 0x17 */
    REACTION_NPC_STEP_OFFER = 2,        /* the answers offered, after line 0x17 or 0x18 */
    REACTION_NPC_STEP_WATCH = 3,        /* watches the reaction chosen */
    REACTION_NPC_STEP_PAUSE = 4,        /* the next line after a pause */
    REACTION_NPC_STEPS = 5
};

/* A step of the scene: its member function and whether it runs each frame while the talk's
 * link is open (else once it closes). */
typedef struct ReactionNpcTalkStep {
    MemberPointer run;
    u8 each_frame;
    u8 unk_09[3];
} ReactionNpcTalkStep;

/* The ways ReactionNpcTalk_SetAnswers offers reactions. */
enum ReactionNpcAnswers {
    REACTION_NPC_ANSWERS_NEW = 0,   /* four not known yet, drawn at random */
    REACTION_NPC_ANSWERS_SAME = 1,  /* the four offered last */
    REACTION_NPC_ANSWERS_SLOTS = 2, /* the player's four motion slots, and a fifth answer */
};

/* No line (the lines are bytes). */
#define REACTION_NPC_NO_LINE 0xff

/* The lines of "sp_npc_reaction" (the reaction `n` is shown with line 0x1c + n). */
#define REACTION_NPC_LINE_FIRST 0x01        /* the talk's line until taught once */
#define REACTION_NPC_LINE_LESSON 0x0b       /* ends with the first lesson */
#define REACTION_NPC_LINE_LEARNT_FIRST 0x0c /* the first reaction taken */
#define REACTION_NPC_LINE_ONE_KNOWN 0x0d    /* 0x0d-0x0f: one motion slot filled */
#define REACTION_NPC_LINE_MORE_KNOWN 0x10   /* 0x10-0x12: more */
#define REACTION_NPC_LINE_NOT_TODAY 0x13    /* 0x13-0x14: not taught today yet */
#define REACTION_NPC_LINE_OFFER 0x17        /* ends with new reactions offered */
#define REACTION_NPC_LINE_MISSED 0x18       /* not taken in time; the same ones offered */
#define REACTION_NPC_LINE_LEARNT 0x19       /* taken; ends with it put in an empty slot */
#define REACTION_NPC_LINE_NO_SLOT 0x1a      /* taken, no empty slot; ends with the slots offered */
#define REACTION_NPC_LINE_KEPT 0x1b         /* the fifth answer: none given up */
#define REACTION_NPC_LINE_REPLACED 0x1c     /* a slot given up for it */
#define REACTION_NPC_LINE_REACTIONS 0x1d    /* 0x1d-0x39: the reactions 1 to 29 */
#define REACTION_NPC_LINE_REACTIONS_LAST 0x39

void ReactionNpcTalk_OnAnswer(ReactionNpcTalk *talk);
void ReactionNpcTalk_OnLineEnded(ReactionNpcTalk *talk);
void ReactionNpcTalk_FirstLine(ReactionNpcTalk *talk, ReactionNpcLine *out);
void ReactionNpcTalk_Begin(ReactionNpcTalk *talk, ReactionNpc *owner);
void *ReactionNpcTalk_Delete(void *talk);
void *ReactionNpcTalk_Destroy(void *talk);
void *ReactionNpcTalk_Construct(void *talk);
void ReactionNpcTalk_StepPause(ReactionNpcTalk *talk);
void ReactionNpcTalk_StepWatch(ReactionNpcTalk *talk);
void ReactionNpcTalk_StepOffer(ReactionNpcTalk *talk);
void ReactionNpcTalk_StepFirstLesson(ReactionNpcTalk *talk);
void ReactionNpcTalk_SetStep(ReactionNpcTalk *talk, unsigned int step);
void ReactionNpcTalk_OnTalkClosed(ReactionNpcTalk *talk);
void ReactionNpcTalk_WhileTalkOpen(ReactionNpcTalk *talk);
void ReactionNpcTalk_SetAnswers(ReactionNpcTalk *talk, int way);
int ReactionNpcTalk_PickUnknown(int unused, const unsigned char *known, int count);
int ReactionNpcTalk_CountUnknown(int unused, unsigned char *known, int count);

#endif
