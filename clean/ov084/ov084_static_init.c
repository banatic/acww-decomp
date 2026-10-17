/* Overlay 84 (the turtle, turtle4.h): its static initialiser, run when the overlay is loaded,
 * which fills in the table of the turtle's states (data_ov084_022795a0, Turtle4_SetState and
 * Turtle4_Update): each state's entry and update, copied from the overlay's constants (C++
 * pointers to member functions, which the compiler does not fold into the table). */
#include <stdint.h>

#include "clean.h"
#include "turtle4.h"
#include "types.h"

/* The table of the turtle's states. */
extern Turtle4Step data_ov084_022795a0[TURTLE4_STATES];
/* The null member pointer (state 2 has no entry), and each state's entry and update. */
extern const MemberPointer __ptmf_null;
extern const MemberPointer data_ov084_02279388, data_ov084_02279390, data_ov084_02279398, data_ov084_022793a0,
    data_ov084_022793a8;

/* __sinit_ov084_0227931c: the entries and updates of the turtle's three states, in order. The
 * address of the table. */
int Turtle4Init_States(void)
{
    static const MemberPointer *const steps[2 * TURTLE4_STATES] = {
        &data_ov084_022793a8, &data_ov084_02279390, /* 0: Turtle4_EnterStand, Turtle4_UpdateStand */
        &data_ov084_02279388, &data_ov084_02279398, /* 1: Turtle4_EnterTalk, Turtle4_UpdateTalk */
        &__ptmf_null,         &data_ov084_022793a0, /* 2: none, Turtle4_UpdateTalked */
    };
    for (int i = 0; i < TURTLE4_STATES; i++) {
        data_ov084_022795a0[i].enter = *steps[2 * i];
        data_ov084_022795a0[i].update = *steps[2 * i + 1];
    }
    return (int) (uintptr_t) data_ov084_022795a0;
}
CLEAN_AS(__sinit_ov084_0227931c, Turtle4Init_States)
