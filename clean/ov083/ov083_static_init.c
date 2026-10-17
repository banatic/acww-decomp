/* Overlay 83 (the turtle as the judge of the town's gardens, turtle_gardens.h): its static
 * initialiser, run when the overlay is loaded, which fills in the table of his states
 * (data_ov083_02279360, TurtleGardens_SetState and TurtleGardens_Update): each state's entry
 * and update, copied from the overlay's constants (C++ pointers to member functions, which the
 * compiler does not fold into the table). */
#include <stdint.h>

#include "clean.h"
#include "turtle_gardens.h"
#include "types.h"

/* The table of his states. */
extern TurtleGardensStep data_ov083_02279360[TURTLE_GARDENS_STATES];
/* The null member pointer (state 2 has no entry), and each state's entry and update. */
extern const MemberPointer __ptmf_null;
extern const MemberPointer data_ov083_02279180, data_ov083_02279188, data_ov083_02279190, data_ov083_02279198,
    data_ov083_022791a0;

/* __sinit_ov083_02279100: the entries and updates of his three states, in order. The address
 * of the table. */
int Ov083Init_TurtleGardensStates(void)
{
    static const MemberPointer *const steps[2 * TURTLE_GARDENS_STATES] = {
        &data_ov083_02279198, &data_ov083_022791a0, /* 0: TurtleGardens_EnterStand, TurtleGardens_UpdateStand */
        &data_ov083_02279190, &data_ov083_02279188, /* 1: TurtleGardens_EnterTalk, TurtleGardens_UpdateTalk */
        &__ptmf_null,         &data_ov083_02279180, /* 2: none, TurtleGardens_UpdateTalked */
    };
    for (int i = 0; i < TURTLE_GARDENS_STATES; i++) {
        data_ov083_02279360[i].enter = *steps[2 * i];
        data_ov083_02279360[i].update = *steps[2 * i + 1];
    }
    return (int) (uintptr_t) data_ov083_02279360;
}
CLEAN_AS(__sinit_ov083_02279100, Ov083Init_TurtleGardensStates)
