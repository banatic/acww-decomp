/* Overlay 54's static initialiser, run when the overlay is loaded: the tables of member
 * functions the post office clerk (post_clerk.h) and her talk scene (post_clerk_talk.h)
 * dispatch through, copied from the overlay's constants (the compiler cannot place member
 * pointers in initialised data). */
#include "clean.h"
#include "post_clerk.h"
#include "post_clerk_talk.h"
#include "types.h"

/* The talk scene's steps: none (the null member pointer), then steps 1 to 15. Their flags
 * (byte 8 of each entry) are not written. */
extern const MemberPointer __ptmf_null;
extern const MemberPointer data_ov054_02262d18, data_ov054_02262de0, data_ov054_02262de8, data_ov054_02262dc8,
    data_ov054_02262dc0, data_ov054_02262d08, data_ov054_02262d10, data_ov054_02262e48, data_ov054_02262ed0,
    data_ov054_02262e00, data_ov054_02262ee0, data_ov054_02262cf8, data_ov054_02262d20, data_ov054_02262da0,
    data_ov054_02262d40;
extern PostClerkTalkStep data_ov054_02263140[POST_CLERK_TALK_STEPS];
/* Her states: each one's entry, then its update. */
extern const MemberPointer data_ov054_02262d48, data_ov054_02262d90, data_ov054_02262ed8, data_ov054_02262d70,
    data_ov054_02262d78, data_ov054_02262d80, data_ov054_02262eb8, data_ov054_02262e08, data_ov054_02262ea8,
    data_ov054_02262e10, data_ov054_02262e98, data_ov054_02262e28, data_ov054_02262e88, data_ov054_02262e30,
    data_ov054_02262e78, data_ov054_02262e50, data_ov054_02262e60, data_ov054_02262e68, data_ov054_02262e70,
    data_ov054_02262e80, data_ov054_02262ea0, data_ov054_02262eb0, data_ov054_02262e38, data_ov054_02262d38;
extern PostClerkStep data_ov054_022632dc[POST_CLERK_STATES];

/* __sinit_ov054_02262a70: the sixteen steps' functions, then the entries and updates of the
 * twelve states, in order. */
void Ov054Init_PostClerkTables(void)
{
    static const MemberPointer *const steps[POST_CLERK_TALK_STEPS - 1] = {
        &data_ov054_02262d18, /* 1: PostClerkTalk_AfterLetters */
        &data_ov054_02262de0, /* 2: PostClerkTalk_AfterScreen26 */
        &data_ov054_02262de8, /* 3: PostClerkTalk_AfterTownAmount */
        &data_ov054_02262dc8, /* 4: PostClerkTalk_AfterScreen3f */
        &data_ov054_02262dc0, /* 5: PostClerkTalk_AfterDatedLetter */
        &data_ov054_02262d08, /* 6: PostClerkTalk_AfterLoan */
        &data_ov054_02262d10, /* 7: PostClerkTalk_AfterSavings */
        &data_ov054_02262e48, /* 8: PostClerkTalk_AskJob12 */
        &data_ov054_02262ed0, /* 9: PostClerkTalk_AwaitJob12 */
        &data_ov054_02262e00, /* 10: PostClerkTalk_NextLine */
        &data_ov054_02262ee0, /* 11: PostClerkTalk_AfterErrand */
        &data_ov054_02262cf8, /* 12: PostClerkTalk_SearchGame */
        &data_ov054_02262d20, /* 13: PostClerkTalk_AwaitConnection */
        &data_ov054_02262da0, /* 14: PostClerkTalk_AskJob1f */
        &data_ov054_02262d40, /* 15: PostClerkTalk_AwaitJob1f */
    };
    static const MemberPointer *const states[2 * POST_CLERK_STATES] = {
        &data_ov054_02262d48, &data_ov054_02262d90, /* 0: greet */
        &data_ov054_02262ed8, &data_ov054_02262d70, /* 1: call over */
        &data_ov054_02262d78, &data_ov054_02262d80, /* 2: stand */
        &data_ov054_02262eb8, &data_ov054_02262e08, /* 3: walk */
        &data_ov054_02262ea8, &data_ov054_02262e10, /* 4: talk */
        &data_ov054_02262e98, &data_ov054_02262e28, /* 5: talked */
        &data_ov054_02262e88, &data_ov054_02262e30, /* 6: turn */
        &data_ov054_02262e78, &data_ov054_02262e50, /* 7: act */
        &data_ov054_02262e60, &data_ov054_02262e68, /* 8: leave */
        &data_ov054_02262e70, &data_ov054_02262e80, /* 9: await */
        &data_ov054_02262ea0, &data_ov054_02262eb0, /* 10: other */
        &data_ov054_02262e38, &data_ov054_02262d38, /* 11: paused */
    };
    data_ov054_02263140[POST_CLERK_TALK_STEP_NONE].run = __ptmf_null;
    for (int i = 1; i < POST_CLERK_TALK_STEPS; i++) {
        data_ov054_02263140[i].run = *steps[i - 1];
    }
    for (int i = 0; i < POST_CLERK_STATES; i++) {
        data_ov054_022632dc[i].enter = *states[2 * i];
        data_ov054_022632dc[i].update = *states[2 * i + 1];
    }
}
CLEAN_AS(__sinit_ov054_02262a70, Ov054Init_PostClerkTables)
