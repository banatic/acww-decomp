/* The post office clerk's talk scene (PostClerkTalk, post_clerk.h; class vtable
 * data_ov054_02263004, derived from the scene class 0x020d9ff8).
 *
 * Its vtable slots, beyond the scene's: 0x00 and 0x04 its destructors, 0x10 a line begins
 * (PostClerkTalk_OnLineBegin), 0x14 a line ended (PostClerkTalk_OnLineEnd), 0x18 the player's
 * answer (PostClerkTalk_OnAnswer), 0x78 the line the talk starts with (PostClerkTalk_Line),
 * 0x80 before each step of the scene and 0x84 a command of the scene ended (the steps, below).
 *
 * Its message files, by clerk (data_ov054_02262fac): her own ("sp_npc_ypelican" or
 * "sp_npc_opelican"), her dated events' ("sp_npc_drama5" or "sp_npc_drama6") and, for the
 * clerk of the day, "sp_etc_sequence4" (while a game is being started anew). The answers and
 * the ends of lines go to a handler by the file of the line shown (the receiver's file name):
 * her own, another, or the sequence's while a game is being started anew.
 *
 * What the talk does:
 * - the menu (lines 0, 0x52, 0x53 and 0x56 end with it, PostClerkTalk_OfferMenu): the letters
 *   (the letter screen, overlay 104's letter_send.h), the savings (the account's screen), the
 *   house's loan (when one is owed and the player's flag 1 is clear), the screen in mode 0x26
 *   (unless this system has a slot in a session) and goodbye; a system that is linked and not
 *   the host gets only the letters and goodbye;
 * - after the letter screen, a line by what was posted (the screen's result flags,
 *   group_params.h); a letter to the player themself may be kept as the dated letter;
 * - the savings: the balance and a 200th of it told after the account's screen; the bells
 *   taken (deposited) or handed over (withdrawn);
 * - the loan: what is left of it told after its screen; paid off, flag 0 of block 0x021d27ac
 *   is set and flag 0x10 of the state block cleared;
 * - an amount added to the town-wide amount (savings.h) after the screen in mode 0x37, and the
 *   savings rank it reaches (PostClerkTalk_TellSavingsRank);
 * - a villager's errand for the clerk: the item handed over from the pockets;
 * - a linked game (line 0x36): the session started, a game looked for for up to 600 frames,
 *   joined, then activity job 0x12 or 0x1f asked for (activity_job.h).
 *
 * Its steps (PostClerkTalk.step), a member function each from data_ov054_02263140 (filled at
 * start-up), run once when a command of the scene ends, or before each step of the scene when
 * the entry's flag (byte 8, the overlay's data) is set (steps 8, 9 and 12 to 15). */
#ifndef CLEAN_OV054_POST_CLERK_TALK_H
#define CLEAN_OV054_POST_CLERK_TALK_H

#include "post_clerk.h"
#include "types.h"

enum PostClerkTalkStepId {
    POST_CLERK_TALK_STEP_NONE = 0,
    POST_CLERK_TALK_STEP_LETTERS = 1,       /* PostClerkTalk_AfterLetters */
    POST_CLERK_TALK_STEP_SCREEN_26 = 2,     /* PostClerkTalk_AfterScreen26 */
    POST_CLERK_TALK_STEP_TOWN_AMOUNT = 3,   /* PostClerkTalk_AfterTownAmount */
    POST_CLERK_TALK_STEP_SCREEN_3F = 4,     /* PostClerkTalk_AfterScreen3f */
    POST_CLERK_TALK_STEP_DATED_LETTER = 5,  /* PostClerkTalk_AfterDatedLetter */
    POST_CLERK_TALK_STEP_LOAN = 6,          /* PostClerkTalk_AfterLoan */
    POST_CLERK_TALK_STEP_SAVINGS = 7,       /* PostClerkTalk_AfterSavings */
    POST_CLERK_TALK_STEP_ASK_JOB_12 = 8,    /* PostClerkTalk_AskJob12, each step */
    POST_CLERK_TALK_STEP_AWAIT_JOB_12 = 9,  /* PostClerkTalk_AwaitJob12, each step */
    POST_CLERK_TALK_STEP_NEXT_LINE = 10,    /* PostClerkTalk_NextLine */
    POST_CLERK_TALK_STEP_ERRAND = 11,       /* PostClerkTalk_AfterErrand */
    POST_CLERK_TALK_STEP_SEARCH = 12,       /* PostClerkTalk_SearchGame, each step */
    POST_CLERK_TALK_STEP_CONNECT = 13,      /* PostClerkTalk_AwaitConnection, each step */
    POST_CLERK_TALK_STEP_ASK_JOB_1F = 14,   /* PostClerkTalk_AskJob1f, each step */
    POST_CLERK_TALK_STEP_AWAIT_JOB_1F = 15, /* PostClerkTalk_AwaitJob1f, each step */
    POST_CLERK_TALK_STEPS = 16
};

/* A step's function in data_ov054_02263140. */
typedef struct PostClerkTalkStep {
    MemberPointer run; /* void (talk) */
    u8 each_step;      /* 0x08: run before each step, else when a command ends */
    u8 unk_09[3];
} PostClerkTalkStep;

/* PostClerkTalk.menu: the answers offered (data_ov054_02262f50, data_ov054_022629b4). */
enum PostClerkTalkMenu {
    POST_CLERK_TALK_MENU_PLAIN = 0,       /* letters, savings, screen 0x26, goodbye */
    POST_CLERK_TALK_MENU_LOAN = 1,        /* letters, loan, savings, screen 0x26, goodbye */
    POST_CLERK_TALK_MENU_GUEST = 2,       /* letters, goodbye */
    POST_CLERK_TALK_MENU_LINKED = 3,      /* letters, savings, goodbye */
    POST_CLERK_TALK_MENU_LINKED_LOAN = 4, /* letters, loan, savings, goodbye */
    POST_CLERK_TALK_MENUS = 5
};

/* The clerk's message files (data_ov054_02262fac, by PostClerk.clerk). */
typedef struct PostClerkFiles {
    const char *own;      /* "sp_npc_ypelican" or "sp_npc_opelican" */
    const char *drama;    /* "sp_npc_drama5" or "sp_npc_drama6" */
    const char *sequence; /* "sp_etc_sequence4" for the clerk of the day, else null */
} PostClerkFiles;

/* What the line function gives: the message file's name and the line. */
typedef struct PostClerkTalkLine {
    const char *name;
    u8 message;
    u8 unk_05[3];
} PostClerkTalkLine;

/* The class (post_clerk_talk.c). */
PostClerkTalk *PostClerkTalk_Construct(PostClerkTalk *talk);
PostClerkTalk *PostClerkTalk_Destruct(PostClerkTalk *talk);
PostClerkTalk *PostClerkTalk_DestructDelete(PostClerkTalk *talk);
void PostClerkTalk_Begin(PostClerkTalk *talk, PostClerk *owner);
void PostClerkTalk_SetStep(PostClerkTalk *talk, unsigned long step);
void PostClerkTalk_RunCommandStep(PostClerkTalk *talk);
void PostClerkTalk_RunEachStep(PostClerkTalk *talk);
void PostClerkTalk_EndLinkedGame(PostClerkTalk *talk);

/* The lines. */
void PostClerkTalk_Line(PostClerkTalk *talk, PostClerkTalkLine *out);
void PostClerkTalk_OnLineBegin(PostClerkTalk *talk);
void PostClerkTalk_ShowLetters(PostClerkTalk *talk);
int PostClerkTalk_UnsentLine(PostClerkTalk *talk);
int PostClerkTalk_NoAddresseeLine(PostClerkTalk *talk);
u8 PostClerkTalk_FullMailboxLine(PostClerkTalk *talk);
int PostClerkTalk_PostedLine(PostClerkTalk *talk);

/* The answers. */
void PostClerkTalk_OnAnswer(PostClerkTalk *talk, u32 arg);
void PostClerkTalk_OnOwnAnswer(PostClerkTalk *talk, unsigned int arg);
void PostClerkTalk_OnDramaAnswer(PostClerkTalk *talk, unsigned int arg);
void PostClerkTalk_OnSequenceAnswer(PostClerkTalk *talk, unsigned int arg);
void PostClerkTalk_OfferMenu(PostClerkTalk *talk, int arg);
void PostClerkTalk_OnMenuAnswer(PostClerkTalk *talk, unsigned int arg);
void PostClerkTalk_ChooseLetters(PostClerkTalk *talk);
void PostClerkTalk_ChooseLoan(PostClerkTalk *talk);
void PostClerkTalk_ChooseSavings(PostClerkTalk *talk);
void PostClerkTalk_ChooseScreen26(PostClerkTalk *talk);
void PostClerkTalk_ChooseGoodbye(PostClerkTalk *talk);
unsigned short PostClerkTalk_IsErrandItem(unsigned short *item, int state);

/* The ends of lines. */
void PostClerkTalk_OnLineEnd(PostClerkTalk *talk, u32 arg);
void PostClerkTalk_OnOwnLineEnd(PostClerkTalk *talk, int arg);
void PostClerkTalk_OnDramaLineEnd(PostClerkTalk *talk, unsigned int arg);
void PostClerkTalk_OnSequenceLineEnd(PostClerkTalk *talk, unsigned int arg);
void PostClerkTalk_TellSavingsRank(PostClerkTalk *talk, int arg);

/* The steps. */
void PostClerkTalk_AfterLetters(PostClerkTalk *talk);
void PostClerkTalk_AfterScreen26(PostClerkTalk *talk);
void PostClerkTalk_AfterTownAmount(PostClerkTalk *talk);
void PostClerkTalk_AfterScreen3f(PostClerkTalk *talk);
void PostClerkTalk_AfterDatedLetter(PostClerkTalk *talk);
void PostClerkTalk_AfterLoan(PostClerkTalk *talk);
void PostClerkTalk_AfterSavings(PostClerkTalk *talk);
void PostClerkTalk_AskJob12(PostClerkTalk *talk);
void PostClerkTalk_AwaitJob12(PostClerkTalk *talk);
void PostClerkTalk_NextLine(PostClerkTalk *talk);
void PostClerkTalk_AfterErrand(PostClerkTalk *talk);
void PostClerkTalk_SearchGame(PostClerkTalk *talk);
void PostClerkTalk_AwaitConnection(PostClerkTalk *talk);
void PostClerkTalk_AskJob1f(PostClerkTalk *talk);
void PostClerkTalk_AwaitJob1f(PostClerkTalk *talk);

#endif
