/* The owl's talk scene (OwlTalk, owl.h; class vtable data_ov047_02262c14, derived from the scene
 * class 0x020d9ff8): the line it starts with (slot 0x78, OwlTalk_Line), the player's answers
 * (slot 0x18, OwlTalk_OnAnswer), what follows the end of a line (slot 0x14, owl_donation.h), and
 * the work done once a command of the scene ends (slot 0x84, OwlTalk_RunAfter).
 *
 * The answers go to the handlers of a table keyed by the line shown (the receiver's message,
 * byte 0x1e). The menu (lines 0x0c and 0x44, OwlTalk_OnMenu) offers five choices: to give an item
 * to the museum (0), to have a fossil assessed (1), how far the museum is (3), and two more (2 and 4, OwlTalk_OnMenu).
 * Its handlers set the line the talk goes on with (OwlTalk.next_line), which the talk then
 * shows; some instead open a screen of the pockets with a test of the items offered
 * (SceneCommand_SetPocketPredicate) and set the work to do once it closes (OwlTalk_SetAfter):
 *   0  OwlTalk_TakeOffered:  the item offered for the museum;
 *   1  OwlTalk_TakeFossil:   the fossil offered to be assessed (item 0x1549);
 *   2  OwlTalk_TakeErrand:   the item 0x155f or 0x1560 offered for a villager's errand;
 *   3  OwlTalk_SayProgress:  how far the museum is, after its screen 2 (mode 0x41);
 *   4  OwlTalk_NextLine:     the next line (set as the work after 0 and 1).
 *
 * The talk's messages are of "sp_npc_owl" (data_ov047_02262fc0); "sp_etc_sequence4" when a
 * game is being started anew and "sp_npc_drama1" for the dated events of kind 1. */
#ifndef CLEAN_OV047_OWL_TALK_H
#define CLEAN_OV047_OWL_TALK_H

#include "owl.h"
#include "types.h"

/* The work done once a command of the scene ends (OwlTalk_SetAfter, OwlTalk_SetNext). */
enum OwlTalkAfter {
    OWL_TALK_AFTER_TAKE_OFFERED = 0,
    OWL_TALK_AFTER_TAKE_FOSSIL = 1,
    OWL_TALK_AFTER_TAKE_ERRAND = 2,
    OWL_TALK_AFTER_SAY_PROGRESS = 3,
    OWL_TALK_AFTER_NEXT_LINE = 4,
    OWL_TALK_AFTERS = 5
};

/* What the talk starts with (its slot 0x78): the message file and the line. */
typedef struct OwlTalkStart {
    const char *name;
    u8 message;
    u8 unk_05[3];
} OwlTalkStart;

/* The constructor, the destructors and the reset. */
OwlTalk *OwlTalk_Construct(OwlTalk *talk);
void *OwlTalk_Destruct(OwlTalk *talk);
void *OwlTalk_DestructDelete(void *talk);
void OwlTalk_Reset(OwlTalk *talk);
void OwlTalk_Begin(OwlTalk *talk, Owl *owner);

/* Its line and answers. */
void OwlTalk_Line(OwlTalk *talk, OwlTalkStart *out);
void OwlTalk_OnAnswer(OwlTalk *talk, int arg);
void OwlTalk_OnPlainAnswer(OwlTalk *talk, int unused);
void OwlTalk_OnDramaAnswer(OwlTalk *talk, int unused);
void OwlTalk_OnMenu(OwlTalk *talk, int choice);
void OwlTalk_OnAnswer0e(OwlTalk *talk, int answer);
void OwlTalk_OnAnswer1e(OwlTalk *talk, int answer);
void OwlTalk_OnAnswer20(OwlTalk *talk, int answer);
void OwlTalk_OnAnswer21(OwlTalk *talk, int answer);
void OwlTalk_OnAnswer23(OwlTalk *talk, int answer);
void OwlTalk_OnAnswer27(OwlTalk *talk, int answer);
void OwlTalk_OnAnswer6b(OwlTalk *talk, int answer);
void OwlTalk_OnAnswerErrand(OwlTalk *talk, int answer);

/* The work after a command. */
void OwlTalk_AfterAt(OwlTalk *talk, MemberPointer *out, int after);
void OwlTalk_SetAfter(OwlTalk *talk, int after);
void OwlTalk_SetNext(OwlTalk *talk, int after);
void OwlTalk_RunAfter(OwlTalk *talk);

#endif
