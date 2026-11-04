/* Overlay 86 (the turtle, turtle_countdown.h): its static initialiser, run when the overlay is loaded,
 * which fills in the table of the turtle's states (data_ov086_02279480, TurtleCountdown_SetState and
 * TurtleCountdown_Update): each state's entry and update, copied from the overlay's constants (C++
 * pointers to member functions, which the compiler does not fold into the table). */
#include <stdint.h>

#include "clean.h"
#include "turtle_countdown.h"
#include "types.h"

/* The table of the turtle's states. */
extern TurtleCountdownStep data_ov086_02279480[TURTLE_COUNTDOWN_STATES];
/* The null member pointer (state 2 has no entry), and each state's entry and update. */
extern const MemberPointer __ptmf_null;
extern const MemberPointer data_ov086_02279268, data_ov086_02279270, data_ov086_02279278, data_ov086_02279280,
    data_ov086_02279288;

/* __sinit_ov086_022791f0: the entries and updates of the turtle's three states, in order. The
 * address of the table. */
int TurtleCountdownInit_States(void)
{
    static const MemberPointer *const steps[2 * TURTLE_COUNTDOWN_STATES] = {
        &data_ov086_02279268, &data_ov086_02279280, /* 0: TurtleCountdown_EnterStand, TurtleCountdown_UpdateStand */
        &data_ov086_02279288, &data_ov086_02279278, /* 1: TurtleCountdown_EnterTalk, TurtleCountdown_UpdateTalk */
        &__ptmf_null,         &data_ov086_02279270, /* 2: none, TurtleCountdown_UpdateTalked */
    };
    for (int i = 0; i < TURTLE_COUNTDOWN_STATES; i++) {
        data_ov086_02279480[i].enter = *steps[2 * i];
        data_ov086_02279480[i].update = *steps[2 * i + 1];
    }
    return (int) (uintptr_t) data_ov086_02279480;
}
CLEAN_AS(__sinit_ov086_022791f0, TurtleCountdownInit_States)
