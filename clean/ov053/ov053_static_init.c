/* Overlay 53 (the barber, barber.h): its static initialiser, run when the overlay is loaded,
 * which fills in the table of the barber's states (data_ov053_02261c64, Barber_SetState and
 * Barber_Update): each state's entry and update, copied from the overlay's constants (C++
 * pointers to member functions, which the compiler does not fold into the table). */
#include <stdint.h>

#include "barber.h"
#include "clean.h"
#include "types.h"

/* The table of the barber's states. */
extern BarberStep data_ov053_02261c64[BARBER_STATES];
/* Each state's entry, then its update. */
extern const MemberPointer data_ov053_02261a0c, data_ov053_02261984, data_ov053_02261994, data_ov053_02261a2c,
    data_ov053_02261a24, data_ov053_02261a1c, data_ov053_02261a14, data_ov053_022619ac, data_ov053_02261a04,
    data_ov053_022619fc, data_ov053_022619a4, data_ov053_022619f4, data_ov053_022619d4, data_ov053_022619dc,
    data_ov053_022619e4, data_ov053_022619ec, data_ov053_022619c4, data_ov053_022619bc, data_ov053_022619b4,
    data_ov053_0226198c, data_ov053_0226199c, data_ov053_022619cc;

/* __sinit_ov053_0226182c: the entries and updates of the barber's eleven states, in order.
 * QUIRK: it answers the address of state 8's entry in the table (the last base it used, left in
 * the register). */
int Ov053Init_BarberStates(void)
{
    static const MemberPointer *const steps[2 * BARBER_STATES] = {
        &data_ov053_02261a0c, &data_ov053_02261984, /* 0: Barber_EnterCall, Barber_UpdateCall */
        &data_ov053_02261994, &data_ov053_02261a2c, /* 1: Barber_EnterStand, Barber_UpdateStand */
        &data_ov053_02261a24, &data_ov053_02261a1c, /* 2: Barber_EnterTalk, Barber_UpdateTalk */
        &data_ov053_02261a14, &data_ov053_022619ac, /* 3: Barber_EnterTalked, Barber_UpdateTalked */
        &data_ov053_02261a04, &data_ov053_022619fc, /* 4: Barber_EnterTurnBack, Barber_UpdateTurnBack */
        &data_ov053_022619a4, &data_ov053_022619f4, /* 5: Barber_EnterWalkA, Barber_UpdateWalkA */
        &data_ov053_022619d4, &data_ov053_022619dc, /* 6: Barber_EnterWalkB, Barber_UpdateWalkB */
        &data_ov053_022619e4, &data_ov053_022619ec, /* 7: Barber_EnterToCut, Barber_UpdateToCut */
        &data_ov053_022619c4, &data_ov053_022619bc, /* 8: Barber_EnterCut, Barber_UpdateCut */
        &data_ov053_022619b4, &data_ov053_0226198c, /* 9: Barber_EnterSendBack, Barber_UpdateSendBack */
        &data_ov053_0226199c, &data_ov053_022619cc, /* 10: Barber_EnterPaused, Barber_UpdatePaused */
    };
    for (int i = 0; i < BARBER_STATES; i++) {
        data_ov053_02261c64[i].enter = *steps[2 * i];
        data_ov053_02261c64[i].update = *steps[2 * i + 1];
    }
    return (int) (uintptr_t) &data_ov053_02261c64[BARBER_STATE_CUT].enter;
}
CLEAN_AS(__sinit_ov053_0226182c, Ov053Init_BarberStates)
