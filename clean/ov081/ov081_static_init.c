/* Overlay 81 (the turtle as the fishing tourney's host, turtle_fishing.h): its static
 * initialiser, run when the overlay is loaded, which fills in the table of his states
 * (data_ov081_022798b4, TurtleFishing_SetState and TurtleFishing_Update): each state's entry
 * and update, copied from the overlay's constants (C++ pointers to member functions, which the
 * compiler does not fold into the table). */
#include <stdint.h>

#include "clean.h"
#include "turtle_fishing.h"
#include "types.h"

/* The table of his states. */
extern TurtleFishingStep data_ov081_022798b4[TURTLE_FISHING_STATES];
/* The null member pointer (state 2 has no entry), and each state's entry and update. */
extern const MemberPointer __ptmf_null;
extern const MemberPointer data_ov081_022796a0, data_ov081_022796b8, data_ov081_022796c0, data_ov081_022796c8,
    data_ov081_022796d0;

/* __sinit_ov081_02279620: the entries and updates of his three states, in order. The address
 * of the table. */
int Ov081Init_TurtleFishingStates(void)
{
    static const MemberPointer *const steps[2 * TURTLE_FISHING_STATES] = {
        &data_ov081_022796a0, &data_ov081_022796b8, /* 0: TurtleFishing_EnterStand, TurtleFishing_UpdateStand */
        &data_ov081_022796d0, &data_ov081_022796c8, /* 1: TurtleFishing_EnterTalk, TurtleFishing_UpdateTalk */
        &__ptmf_null,         &data_ov081_022796c0, /* 2: none, TurtleFishing_UpdateTalked */
    };
    for (int i = 0; i < TURTLE_FISHING_STATES; i++) {
        data_ov081_022798b4[i].enter = *steps[2 * i];
        data_ov081_022798b4[i].update = *steps[2 * i + 1];
    }
    return (int) (uintptr_t) data_ov081_022798b4;
}
CLEAN_AS(__sinit_ov081_02279620, Ov081Init_TurtleFishingStates)
