/* Overlay 76 (the otter, otter.h): its static initialiser, run when the overlay is loaded,
 * which fills in the table of the otter's states (data_ov076_0227988c, Otter_SetState and
 * Otter_Update): each state's entry and update, copied from the overlay's constants (C++
 * pointers to member functions, which the compiler does not fold into the table). */
#include <stdint.h>

#include "clean.h"
#include "otter.h"
#include "types.h"

/* The table of the otter's states. */
extern OtterStep data_ov076_0227988c[OTTER_STATES];
/* The null member pointer (state 2 has no entry), and each state's entry and update. */
extern const MemberPointer __ptmf_null;
extern const MemberPointer data_ov076_02279680, data_ov076_02279690, data_ov076_02279698, data_ov076_022796a0,
    data_ov076_022796a8, data_ov076_022796b0, data_ov076_022796b8, data_ov076_022796c0, data_ov076_022796c8,
    data_ov076_022796d0, data_ov076_022796d8;

/* __sinit_ov076_022795ac: the entries and updates of the otter's six states, in order. The
 * address of the table. */
int Ov076Init_OtterStates(void)
{
    static const MemberPointer *const steps[2 * OTTER_STATES] = {
        &data_ov076_022796c8, &data_ov076_022796d8, /* 0: Otter_EnterStand, Otter_UpdateStand */
        &data_ov076_022796d0, &data_ov076_022796a8, /* 1: Otter_EnterTalk, Otter_UpdateTalk */
        &__ptmf_null,         &data_ov076_022796c0, /* 2: none, Otter_UpdateTalked */
        &data_ov076_022796b8, &data_ov076_02279680, /* 3: Otter_EnterTurn, Otter_UpdateTurn */
        &data_ov076_022796b0, &data_ov076_022796a0, /* 4: Otter_EnterDive, Otter_UpdateDive */
        &data_ov076_02279690, &data_ov076_02279698, /* 5: Otter_EnterGone, Otter_UpdateGone */
    };
    for (int i = 0; i < OTTER_STATES; i++) {
        data_ov076_0227988c[i].enter = *steps[2 * i];
        data_ov076_0227988c[i].update = *steps[2 * i + 1];
    }
    return (int) (uintptr_t) data_ov076_0227988c;
}
CLEAN_AS(__sinit_ov076_022795ac, Ov076Init_OtterStates)
