/* Overlay 45's static initialiser, run when the overlay is loaded: the tables of member
 * functions the fortune teller (fortune_teller.h) and her talk scene (fortune_teller_talk.h)
 * dispatch through, copied from the overlay's constants (the compiler cannot place member
 * pointers in initialised data). */
#include "clean.h"
#include "fortune_teller.h"
#include "fortune_teller_talk.h"
#include "types.h"

/* The talk scene's sequences: none (the null member pointer), then the name taken. Their flags
 * (byte 8 of each entry) are not written. */
extern const MemberPointer __ptmf_null;
extern const MemberPointer data_ov045_022613a4;
extern FortuneTellerTalkStep data_ov045_022615a4[FORTUNE_TELLER_TALK_SEQUENCES];
/* Her states: each one's entry, then its update. */
extern const MemberPointer data_ov045_022613b4, data_ov045_022613c4, data_ov045_0226138c, data_ov045_02261384,
    data_ov045_02261394, data_ov045_022613bc, data_ov045_0226139c, data_ov045_022613ac;
extern FortuneTellerStep data_ov045_022615bc[FORTUNE_TELLER_STATES];

/* __sinit_ov045_022612d8: the two sequences' functions, then the entries and updates of the
 * four states, in order. The address of the states' table. */
int FortuneTellerInit_Tables(void)
{
    static const MemberPointer *const states[2 * FORTUNE_TELLER_STATES] = {
        &data_ov045_022613b4, &data_ov045_022613c4, /* 0: sit */
        &data_ov045_0226138c, &data_ov045_02261384, /* 1: talk */
        &data_ov045_02261394, &data_ov045_022613bc, /* 2: talked */
        &data_ov045_0226139c, &data_ov045_022613ac, /* 3: closing */
    };
    data_ov045_022615a4[FORTUNE_TELLER_TALK_SEQUENCE_NONE].run = __ptmf_null;
    data_ov045_022615a4[FORTUNE_TELLER_TALK_SEQUENCE_TAKE_NAME].run = data_ov045_022613a4;
    for (int i = 0; i < FORTUNE_TELLER_STATES; i++) {
        data_ov045_022615bc[i].enter = *states[2 * i];
        data_ov045_022615bc[i].update = *states[2 * i + 1];
    }
    return (int) (u32) (uintptr_t) data_ov045_022615bc;
}
CLEAN_AS(__sinit_ov045_022612d8, FortuneTellerInit_Tables)
