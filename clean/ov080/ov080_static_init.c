/* Overlay 80 (the turtle, turtle.h): its static initialiser, run when the overlay is loaded,
 * which fills in the table of the turtle's states (data_ov080_022793e0, Turtle_SetState and
 * Turtle_Update): each state's entry and run, copied from the overlay's constants (C++
 * pointers to member functions, which the compiler does not fold into the table). */
#include <stdint.h>

#include "clean.h"
#include "ov004/member_pointer.h"
#include "turtle.h"
#include "types.h"

/* The null member pointer (TURTLE_TALKED has no entry), and each state's entry and run. */
extern const MemberPointer __ptmf_null;
extern const MemberPointer data_ov080_022791e0, data_ov080_022791e8, data_ov080_022791f0, data_ov080_022791f8,
    data_ov080_02279200;

/* __sinit_ov080_02279178: the entries and runs of the turtle's three states, in order. The
 * address of the table. */
int TurtleInit_Tables(void)
{
    static const MemberPointer *const states[2 * TURTLE_STATES] = {
        &data_ov080_022791f8, &data_ov080_02279200, /* TURTLE_STAND: Turtle_EnterStand, Turtle_UpdateStand */
        &data_ov080_022791f0, &data_ov080_022791e8, /* TURTLE_TALK: Turtle_EnterTalk, Turtle_UpdateTalk */
        &__ptmf_null,         &data_ov080_022791e0, /* TURTLE_TALKED: none, Turtle_UpdateTalked */
    };
    for (int i = 0; i < TURTLE_STATES; i++) {
        data_ov080_022793e0[i].enter = *states[2 * i];
        data_ov080_022793e0[i].run = *states[2 * i + 1];
    }
    return (int) (uintptr_t) data_ov080_022793e0;
}
CLEAN_AS(__sinit_ov080_02279178, TurtleInit_Tables)
