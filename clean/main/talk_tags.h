/* The tags of a talk's messages (class data_020defe4, constructor func_0206bde0, 0xe4 bytes): a
 * walker of the message texts (MessageWalker, message_cursor.h) that shows a talk's message and
 * acts on the tags it meets. func_0206b840 picks a handler table by the tag's group (0 to 11,
 * and 0xff), each table a handler by the tag's kind; the handlers here are:
 *
 * - group 4 (func_0206b228): texts walked in place of the tag: the talk's parts 0 to 10 (kinds
 *   15 to 25, as in the message reader), its four names (kinds 26 to 29), and texts loaded
 *   from the villager talked to or about (kinds 11 to 14 and 30 to 34): each name between two
 *   colour tags (MessageTag_ColourTag), its last Hangul syllable kept for the particles after
 *   it;
 * - group 5 kind 5: the four choices of the slider window (talk_windows.h);
 * - group 6 (func_0206b04c): branches: the receiver is told the branch and its number of
 *   choices, a value of the game picks one of the message numbers the tag carries, and the talk
 *   goes on with that message (func_0206b964);
 * - group 9 (func_0206aec4): the receiver's scene moves (scene_base.h): who has the focus,
 *   looks and turns, and passing the turn;
 * - group 11 (func_0206ace4), kinds 1 to 7: the walker's own settings;
 * - groups 8 and 10, and group 4 kind 32: nothing.
 *
 * The talk (0x1e9c bytes, talk_process.h) is the walker's word at 0x24; its receiver (a
 * Base_02066994, the scene or object the talk is for) at 0x14a8. */
#ifndef CLEAN_MAIN_TALK_TAGS_H
#define CLEAN_MAIN_TALK_TAGS_H

#include "message_decoder.h"
#include "types.h"

/* The walker (0xe4 bytes). */
typedef struct TalkTagsWalker {
    MessageWalker base; /* 0x00 */
    u8 *talk;           /* 0x24: the talk shown */
    void *window;       /* 0x28: the constructor's second argument */
    s32 lines;          /* 0x2c */
    s32 state;          /* 0x30: TALK_TAGS_STATE_CHOOSING while the slider window is open */
    s32 unk_34;         /* 0x34 */
    MessageTag tag;     /* 0x38: the tag being handled */
    u8 unk_4c[4];       /* 0x4c */
    s32 unk_50;         /* 0x50 */
    s32 unk_54;         /* 0x54 */
    s32 unk_58;         /* 0x58 */
    s32 name_colour;    /* 0x5c: the colour tag put before a name */
    u8 unk_60[0x3c];    /* 0x60 */
    u8 unk_9c[0x3c];    /* 0x9c */
    u8 choices_shown;   /* 0xd8: set while the slider tag waits to open its window */
    u8 convert_next;    /* 0xd9: turn the next character into its other form */
    u8 unk_da[2];       /* 0xda */
    u32 unk_dc;         /* 0xdc */
    s32 unk_e0;         /* 0xe0: 1 or 2 from tags 11/1 and 11/2; 0 when a part is walked */
} TalkTagsWalker;

/* TalkTagsWalker.state while the slider window is open. */
#define TALK_TAGS_STATE_CHOOSING 5

/* Group 11. */
void TalkTags_NotePart2(TalkTagsWalker *walker);
void TalkTags_NotePart1(TalkTagsWalker *walker);
void TalkTags_NotePart0(TalkTagsWalker *walker);
void TalkTags_Nothing11_4(void);
void TalkTags_ConvertNext(TalkTagsWalker *walker);
void TalkTags_SetE0Two(TalkTagsWalker *walker);
void TalkTags_SetE0One(TalkTagsWalker *walker);

/* Groups 8 and 10. */
void TalkTags_Nothing10_0(void *walker);
void TalkTags_Nothing8_2(void *walker);
void TalkTags_Nothing8_1(void *walker);
void TalkTags_Nothing8_0(void *walker);

/* Group 9. */
void TalkTags_PassTurn(TalkTagsWalker *walker);
void TalkTags_FaceSecond(TalkTagsWalker *walker);
void *TalkTags_LookAtSecond(TalkTagsWalker *walker);
void TalkTags_FaceFirst(TalkTagsWalker *walker);
void TalkTags_LookAtFirst(TalkTagsWalker *walker);
void TalkTags_FacePlayer(TalkTagsWalker *walker);
void TalkTags_LookAtPlayer(TalkTagsWalker *walker);
void TalkTags_FocusSecond(TalkTagsWalker *walker);
void TalkTags_FocusFirst(TalkTagsWalker *walker);
void TalkTags_FocusPlayer(TalkTagsWalker *walker);

/* Group 6. */
void TalkTags_BranchBySpecies(TalkTagsWalker *walker);
void TalkTags_BranchByResident(TalkTagsWalker *walker);
void TalkTags_BranchByWeekday(TalkTagsWalker *walker);
void TalkTags_BranchByPlayers(TalkTagsWalker *walker);
void TalkTags_BranchByFalling(TalkTagsWalker *walker);
void TalkTags_BranchByPartOfDay(TalkTagsWalker *walker);
void TalkTags_BranchByVillagers(TalkTagsWalker *walker);
void TalkTags_BranchByFish(TalkTagsWalker *walker);
void TalkTags_BranchByInsects(TalkTagsWalker *walker);
void TalkTags_BranchByHouse(TalkTagsWalker *walker);
void TalkTags_BranchByPlayerKind(TalkTagsWalker *walker);
void TalkTags_BranchByFondness(TalkTagsWalker *walker);
void TalkTags_BranchRandom3(TalkTagsWalker *walker);
void TalkTags_BranchRandom2(TalkTagsWalker *walker);

/* Group 5. */
void TalkTags_SliderChoices(TalkTagsWalker *walker);

/* Group 4. */
void TalkTags_PutBoom(TalkTagsWalker *walker);
void TalkTags_PutPraise(TalkTagsWalker *walker);
void TalkTags_Nothing4_32(void);
void TalkTags_PutNickname(TalkTagsWalker *walker);
void TalkTags_PutImpression(TalkTagsWalker *walker);
void TalkTags_PutName3(TalkTagsWalker *walker);
void TalkTags_PutName2(TalkTagsWalker *walker);
void TalkTags_PutName1(TalkTagsWalker *walker);
void TalkTags_PutName0(TalkTagsWalker *walker);
void TalkTags_PutPart10(TalkTagsWalker *walker);
void TalkTags_PutPart9(TalkTagsWalker *walker);
void TalkTags_PutPart8(TalkTagsWalker *walker);
void TalkTags_PutPart7(TalkTagsWalker *walker);
void TalkTags_PutPart6(TalkTagsWalker *walker);
void TalkTags_PutPart5(TalkTagsWalker *walker);
void TalkTags_PutPart4(TalkTagsWalker *walker);
void TalkTags_PutPart3(TalkTagsWalker *walker);
void TalkTags_PutPart2(TalkTagsWalker *walker);
void TalkTags_PutPart1(TalkTagsWalker *walker);
void TalkTags_PutPart0(TalkTagsWalker *walker);
void TalkTags_PutOtherPlayer(TalkTagsWalker *walker);
void TalkTags_PutRandomNpc(TalkTagsWalker *walker);
void TalkTags_PutDislikedNpc(TalkTagsWalker *walker);
void TalkTags_PutLikedNpc(TalkTagsWalker *walker);

/* The other groups' handlers and the tables that pick them (TalkTags_DispatchGroup*):
 *
 * - group 0: characters that stand for codes in a text, put as themselves ("*", "/", "&", "%",
 *   "{"), and nothing for the other kinds;
 * - group 1: the walk itself: a pause, a stop that keeps the window, the whole text at once,
 *   no hurrying, a text the villager remembers, the window shaken with a sound, the receiver's
 *   slot 0x1c, the talk's word 0x10;
 * - group 2: two to five choices from the tag's texts (also with the last as the cancel), after
 *   the walk went through a lone tag 1/1;
 * - group 3: the receiver's slots 0x20 to 0x30;
 * - group 4 kinds 0 to 10: the player's, the receiver's and the town's names, the villager's
 *   catchphrase, and the date and time the talk began;
 * - group 7: the speaker's talking motion in the style the tag's kind gives;
 * - group 0xff: two handlers (kinds 0 and 2) of the talk's own. */

/* The walker's flags at 0x4c (TalkTagsWalker.unk_4c). */
#define TALK_TAGS_FLAG_HURRY 0    /* asked to hurry (func_0206bd2c), unless TALK_TAGS_FLAG_NO_HURRY */
#define TALK_TAGS_FLAG_INSTANT 2  /* the whole text is shown at once */
#define TALK_TAGS_FLAG_NO_HURRY 3 /* the walk cannot be hurried */

/* TalkTagsWalker.state where the walk stops as at a full page, but the talk goes on without
 * clearing the window (func_02067be0 rather than func_02067bb8). */
#define TALK_TAGS_STATE_STOP_KEEP 4

/* Group 4, kinds 0 to 10. */
void TalkTags_PutSecond(TalkTagsWalker *walker);
void TalkTags_PutMinute(TalkTagsWalker *walker);
void TalkTags_PutHour12(TalkTagsWalker *walker);
void TalkTags_PutWeekday(TalkTagsWalker *walker);
void TalkTags_PutDay(TalkTagsWalker *walker);
void TalkTags_PutMonth(TalkTagsWalker *walker);
void TalkTags_PutYear(TalkTagsWalker *walker);
void TalkTags_PutTownName(TalkTagsWalker *walker);
void TalkTags_PutCatchphrase(TalkTagsWalker *walker);
void TalkTags_PutReceiverName(TalkTagsWalker *walker);
void TalkTags_PutPlayerName(TalkTagsWalker *walker);

/* Group 3. */
void TalkTags_TellReceiver30(TalkTagsWalker *walker);
void TalkTags_TellReceiver2c(TalkTagsWalker *walker);
void TalkTags_TellReceiver28(TalkTagsWalker *walker);
void TalkTags_TellReceiver24(TalkTagsWalker *walker);
void TalkTags_TellReceiver20(TalkTagsWalker *walker);

/* Group 2. */
void TalkTags_FiveChoicesCancelLast(TalkTagsWalker *walker);
void TalkTags_FourChoicesCancelLast(TalkTagsWalker *walker);
void TalkTags_ThreeChoicesCancelLast(TalkTagsWalker *walker);
void TalkTags_TwoChoicesCancelLast(TalkTagsWalker *walker);
void TalkTags_FiveChoices(TalkTagsWalker *walker);
void TalkTags_FourChoices(TalkTagsWalker *walker);
void TalkTags_ThreeChoices(TalkTagsWalker *walker);
void TalkTags_TwoChoices(TalkTagsWalker *walker);

/* Group 1. */
void TalkTags_SetTalkWord10(TalkTagsWalker *walker);
void TalkTags_Receiver1cWith4(TalkTagsWalker *walker);
void TalkTags_Receiver1cWith3(TalkTagsWalker *walker);
void TalkTags_Receiver1cWith2(TalkTagsWalker *walker);
void TalkTags_Receiver1cWith1(TalkTagsWalker *walker);
void TalkTags_Receiver1cWith0(TalkTagsWalker *walker);
void TalkTags_ShakeStrong(TalkTagsWalker *walker);
void TalkTags_ShakeMedium(TalkTagsWalker *walker);
void TalkTags_ShakeLight(TalkTagsWalker *walker);
void TalkTags_RememberedEnd(void);
void TalkTags_RememberedText(TalkTagsWalker *walker);
void TalkTags_HurryAllowed(TalkTagsWalker *walker);
void TalkTags_HurryForbidden(TalkTagsWalker *walker);
void TalkTags_InstantOff(TalkTagsWalker *walker);
void TalkTags_InstantOn(TalkTagsWalker *walker);
void TalkTags_StopKeepWindow(TalkTagsWalker *walker);
void TalkTags_Pause(TalkTagsWalker *walker);

/* Group 0. */
void TalkTags_PutLeftBrace(TalkTagsWalker *walker);
void TalkTags_PutPercent(TalkTagsWalker *walker);
void TalkTags_PutAmpersand(TalkTagsWalker *walker);
void TalkTags_PutSlash(TalkTagsWalker *walker);
void TalkTags_PutAsterisk(TalkTagsWalker *walker);
void TalkTags_Nothing(void);

/* The tables by group, and group 7. */
void TalkTags_DispatchGroupFF(TalkTagsWalker *walker);
void TalkTags_DispatchGroup11(TalkTagsWalker *walker);
void TalkTags_DispatchGroup10(TalkTagsWalker *walker);
void TalkTags_DispatchGroup9(TalkTagsWalker *walker);
void TalkTags_DispatchGroup8(TalkTagsWalker *walker);
void TalkTags_SpeakerTalkStyle(TalkTagsWalker *walker);
void TalkTags_DispatchGroup6(TalkTagsWalker *walker);
void TalkTags_DispatchGroup5(TalkTagsWalker *walker);
void TalkTags_DispatchGroup4(TalkTagsWalker *walker);
void TalkTags_DispatchGroup3(TalkTagsWalker *walker);
void TalkTags_DispatchGroup2(TalkTagsWalker *walker);
void TalkTags_DispatchGroup1(TalkTagsWalker *walker);
void TalkTags_DispatchGroup0(TalkTagsWalker *walker);

/* ---- The walker itself: its vtable (data_020defe4) after the base class's (message_walker.h)
 * holds the destructor, the deleting destructor, then slots 2 (the text was set:
 * TalkTags_OnText), 3 (the end: TalkTags_OnEnd), 4 (a character: TalkTags_OnCharacter), 5 (a
 * tag: TalkTags_OnTag) and 6 (whether to go on: TalkTags_WantsMore).
 *
 * The talk shows its text a few characters a frame: the walk goes on while slot 6 says so, and
 * TalkTags_Pace lets 1 and 2 characters through on alternate frames (3 when hurried), each
 * also stepping the two spans of a 0xff/2 tag (talk_span.h, at 0x60 and 0x9c). The characters go
 * into the page of the talk's window (talk_page.h, the walker's word at 0x28). */

/* TalkTagsWalker.state, besides TALK_TAGS_STATE_STOP_KEEP and TALK_TAGS_STATE_CHOOSING. */
#define TALK_TAGS_STATE_IDLE 0
#define TALK_TAGS_STATE_RUNNING 1   /* the text is being shown */
#define TALK_TAGS_STATE_PAGE_FULL 2 /* three lines are shown: the walk waits */
#define TALK_TAGS_STATE_ENDED 3

/* TalkTagsWalker.unk_34: the message's speed (from its kind, set by TalkTags_SetSpeed). */
#define TALK_TAGS_SPEED_NORMAL 0
#define TALK_TAGS_SPEED_INSTANT 1 /* the whole text at once */
#define TALK_TAGS_SPEED_STEADY 2  /* never hurried */

/* The walker's flag at 0x4d (TalkTagsWalker.unk_4c[1]): the next frame shows nothing. */
#define TALK_TAGS_FLAG_HOLD 1

void TalkTags_DispatchTag(TalkTagsWalker *walker);
void TalkTags_GoToMessage(TalkTagsWalker *walker, const u8 *message);
void TalkTags_NotePart(TalkTagsWalker *walker, void *part);
void TalkTags_NoteNothing(void);
void TalkTags_PutName(TalkTagsWalker *walker, int index);
void TalkTags_PutPart(TalkTagsWalker *walker, int index);
void TalkTags_ClearE0(TalkTagsWalker *walker);
int TalkTags_Pace(TalkTagsWalker *walker);
void TalkTags_StepSpans(TalkTagsWalker *walker);
int TalkTags_SpansIdle(TalkTagsWalker *walker);
void TalkTags_FailureNote(void *walker, int line, const void *label);
int TalkTags_WantsMore(TalkTagsWalker *walker);
void TalkTags_OnTag(TalkTagsWalker *walker, int position);
void TalkTags_OnCharacter(TalkTagsWalker *walker, int character);
void TalkTags_OnEnd(TalkTagsWalker *walker);
void TalkTags_OnText(TalkTagsWalker *walker);
void TalkTags_ResetColour(TalkTagsWalker *walker);
void TalkTags_ClearHurry(TalkTagsWalker *walker);
void TalkTags_Hurry(TalkTagsWalker *walker);
void TalkTags_SetSpeed(TalkTagsWalker *walker, int speed);
void TalkTags_NewPage(TalkTagsWalker *walker);
void *TalkTags_Delete(void *walker);
void *TalkTags_Destruct(void *walker);
TalkTagsWalker *TalkTags_Construct(TalkTagsWalker *walker, u8 *talk, void *page);

/* Tags 0xff/0 and 0xff/2, and group 11 from kind 8 on. */
void TalkTags_StartSpans(TalkTagsWalker *walker);
void TalkTags_ChangeColour(TalkTagsWalker *walker);
void TalkTags_PutParticle(TalkTagsWalker *walker);
void TalkTags_NoteValue3(TalkTagsWalker *walker);
void TalkTags_NoteValue2(TalkTagsWalker *walker);
void TalkTags_NoteValue1(TalkTagsWalker *walker);
void TalkTags_NoteValue0(TalkTagsWalker *walker);
void TalkTags_NotePart10(TalkTagsWalker *walker);
void TalkTags_NotePart9(TalkTagsWalker *walker);
void TalkTags_NotePart8(TalkTagsWalker *walker);
void TalkTags_NotePart7(TalkTagsWalker *walker);
void TalkTags_NotePart6(TalkTagsWalker *walker);
void TalkTags_NotePart5(TalkTagsWalker *walker);
void TalkTags_NotePart4(TalkTagsWalker *walker);
void TalkTags_NotePart3(TalkTagsWalker *walker);

#endif
