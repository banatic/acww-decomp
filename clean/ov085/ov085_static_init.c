/* Overlay 85 (the turtle, turtle5.h): its static initialiser, run when the overlay is loaded,
 * which fills in the table of the turtle's states (data_ov085_022795e0, Turtle5_SetState and
 * Turtle5_Update): each state's entry and update, copied from the overlay's constants (C++
 * pointers to member functions, which the compiler does not fold into the table). */
#include <stdint.h>

#include "clean.h"
#include "turtle5.h"
#include "types.h"

/* The table of the turtle's states. */
extern Turtle5Step data_ov085_022795e0[TURTLE5_STATES];
/* The null member pointer (state 2 has no entry), and each state's entry and update. */
extern const MemberPointer __ptmf_null;
extern const MemberPointer data_ov085_022793e0, data_ov085_022793e8, data_ov085_022793f0, data_ov085_022793f8,
    data_ov085_02279400;

/* __sinit_ov085_02279368: the entries and updates of the turtle's three states, in order. The
 * address of the table. */
int Turtle5Init_States(void)
{
    static const MemberPointer *const steps[2 * TURTLE5_STATES] = {
        &data_ov085_022793f8, &data_ov085_02279400, /* 0: Turtle5_EnterStand, Turtle5_UpdateStand */
        &data_ov085_022793f0, &data_ov085_022793e8, /* 1: Turtle5_EnterTalk, Turtle5_UpdateTalk */
        &__ptmf_null,         &data_ov085_022793e0, /* 2: none, Turtle5_UpdateTalked */
    };
    for (int i = 0; i < TURTLE5_STATES; i++) {
        data_ov085_022795e0[i].enter = *steps[2 * i];
        data_ov085_022795e0[i].update = *steps[2 * i + 1];
    }
    return (int) (uintptr_t) data_ov085_022795e0;
}
CLEAN_AS(__sinit_ov085_02279368, Turtle5Init_States)
