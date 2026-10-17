/* Overlay 49's static initialiser, run when the overlay is loaded: the tables of member
 * functions Mabel (mabel.h) and her talk scene (mabel_talk.h) dispatch through, copied from
 * the overlay's constants (the compiler cannot place member pointers in initialised data). */
#include "clean.h"
#include "mabel.h"
#include "mabel_talk.h"
#include "types.h"

/* The talk scene's sequences: none (the null member pointer), then 1 to 9. Their flags (byte
 * 8 of each entry) are the overlay's data and are not written. */
extern const MemberPointer __ptmf_null;
extern const MemberPointer data_ov049_02263280, data_ov049_022630c8, data_ov049_022630c0, data_ov049_02263110,
    data_ov049_02263160, data_ov049_02263118, data_ov049_02263138, data_ov049_02263290, data_ov049_02263150;
extern MabelTalkStep data_ov049_022633b0[MABEL_TALK_SEQUENCES];
/* Her states: each one's entry, then its update; the table's second half (states 8 to 15)
 * has a symbol of its own. */
extern const MemberPointer data_ov049_02263140, data_ov049_02263148, data_ov049_02263170, data_ov049_02263268,
    data_ov049_02263260, data_ov049_02263190, data_ov049_02263198, data_ov049_02263248, data_ov049_02263240,
    data_ov049_02263238, data_ov049_02263230, data_ov049_02263210, data_ov049_02263218, data_ov049_02263228,
    data_ov049_02263250, data_ov049_02263208, data_ov049_02263200, data_ov049_022631f8, data_ov049_022631f0,
    data_ov049_022631e8, data_ov049_022631e0, data_ov049_022631d8, data_ov049_022630f0, data_ov049_022631c8,
    data_ov049_022630e8, data_ov049_022631b8, data_ov049_022630e0, data_ov049_022631a8, data_ov049_022630d8,
    data_ov049_022630d0, data_ov049_022630b0, data_ov049_02263188;
extern MabelStep data_ov049_02263640[MABEL_STATES];
extern MabelStep data_ov049_022636c0[MABEL_STATES / 2];

/* __sinit_ov049_02262e14: the nine sequences' functions, then the entries and updates of the
 * sixteen states, in order. The address of the states' second half. */
int MabelInit_Tables(void)
{
    static const MemberPointer *const sequences[MABEL_TALK_SEQUENCES - 1] = {
        &data_ov049_02263280, /* 1: MabelTalk_SayDesignPicked */
        &data_ov049_022630c8, /* 2: MabelTalk_SayAfterScreenB */
        &data_ov049_022630c0, /* 3: MabelTalk_ShowDesign */
        &data_ov049_02263110, /* 4: MabelTalk_BuyDesign */
        &data_ov049_02263160, /* 5: MabelTalk_SwapDesign */
        &data_ov049_02263118, /* 6: MabelTalk_PriceSale */
        &data_ov049_02263138, /* 7: MabelTalk_WatchTryOn */
        &data_ov049_02263290, /* 8: MabelTalk_EndTryOn */
        &data_ov049_02263150, /* 9: MabelTalk_TakeErrand */
    };
    static const MemberPointer *const states[2 * MABEL_STATES] = {
        &data_ov049_02263140, &data_ov049_02263148, /* 0: greet */
        &data_ov049_02263170, &data_ov049_02263268, /* 1: stand */
        &data_ov049_02263260, &data_ov049_02263190, /* 2: turn */
        &data_ov049_02263198, &data_ov049_02263248, /* 3: walk */
        &data_ov049_02263240, &data_ov049_02263238, /* 4: talk */
        &data_ov049_02263230, &data_ov049_02263210, /* 5: talk, leave */
        &data_ov049_02263218, &data_ov049_02263228, /* 6: talked */
        &data_ov049_02263250, &data_ov049_02263208, /* 7: act */
        &data_ov049_02263200, &data_ov049_022631f8, /* 8: await */
        &data_ov049_022631f0, &data_ov049_022631e8, /* 9: other */
        &data_ov049_022631e0, &data_ov049_022631d8, /* 10: linked stand */
        &data_ov049_022630f0, &data_ov049_022631c8, /* 11: linked turn */
        &data_ov049_022630e8, &data_ov049_022631b8, /* 12: paused */
        &data_ov049_022630e0, &data_ov049_022631a8, /* 13: approach */
        &data_ov049_022630d8, &data_ov049_022630d0, /* 14: speaker */
        &data_ov049_022630b0, &data_ov049_02263188, /* 15: turn, ask */
    };

    data_ov049_022633b0[MABEL_TALK_SEQUENCE_NONE].run = __ptmf_null;
    for (int i = 1; i < MABEL_TALK_SEQUENCES; i++) {
        data_ov049_022633b0[i].run = *sequences[i - 1];
    }
    for (int i = 0; i < MABEL_STATES; i++) {
        data_ov049_02263640[i].enter = *states[2 * i];
        data_ov049_02263640[i].update = *states[2 * i + 1];
    }
    return (int) (u32) (uintptr_t) data_ov049_022636c0;
}
CLEAN_AS(__sinit_ov049_02262e14, MabelInit_Tables)
