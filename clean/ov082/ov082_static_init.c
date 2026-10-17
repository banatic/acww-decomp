/* Overlay 82 (the turtle as the insect contest's host, turtle_insects.h): its static
 * initialiser, run when the overlay is loaded, which fills in the table of his states
 * (data_ov082_02279914, TurtleInsects_SetState and TurtleInsects_Update): each state's entry
 * and update, copied from the overlay's constants (C++ pointers to member functions, which the
 * compiler does not fold into the table). */
#include <stdint.h>

#include "clean.h"
#include "turtle_insects.h"
#include "types.h"

/* The table of his states. */
extern TurtleInsectsStep data_ov082_02279914[TURTLE_INSECTS_STATES];
/* The null member pointer (state 2 has no entry), and each state's entry and update. */
extern const MemberPointer __ptmf_null;
extern const MemberPointer data_ov082_02279700, data_ov082_02279718, data_ov082_02279720, data_ov082_02279728,
    data_ov082_02279730;

/* __sinit_ov082_02279684: the entries and updates of his three states, in order. The address
 * of the table. */
int Ov082Init_TurtleInsectsStates(void)
{
    static const MemberPointer *const steps[2 * TURTLE_INSECTS_STATES] = {
        &data_ov082_02279700, &data_ov082_02279718, /* 0: TurtleInsects_EnterStand, TurtleInsects_UpdateStand */
        &data_ov082_02279730, &data_ov082_02279728, /* 1: TurtleInsects_EnterTalk, TurtleInsects_UpdateTalk */
        &__ptmf_null,         &data_ov082_02279720, /* 2: none, TurtleInsects_UpdateTalked */
    };
    for (int i = 0; i < TURTLE_INSECTS_STATES; i++) {
        data_ov082_02279914[i].enter = *steps[2 * i];
        data_ov082_02279914[i].update = *steps[2 * i + 1];
    }
    return (int) (uintptr_t) data_ov082_02279914;
}
CLEAN_AS(__sinit_ov082_02279684, Ov082Init_TurtleInsectsStates)
