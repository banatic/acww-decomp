/* Overlay 47 (the museum's owl, owl.h): its static initialiser, run when the overlay is loaded,
 * which fills in the table of the owl's states (data_ov047_02263048, Owl_SetState and
 * Owl_Update): each state's entry and update, copied from the overlay's constants (C++ pointers
 * to member functions, which the compiler does not fold into the table). */
#include "clean.h"
#include "owl.h"
#include "types.h"

/* The table of the owl's states. */
extern OwlStep data_ov047_02263048[OWL_STATES];
/* The null member pointer (state 4 has no entry). */
extern const MemberPointer __ptmf_null;
/* Each state's entry, then its update. */
extern const MemberPointer data_ov047_022629d8, data_ov047_02262970, data_ov047_022629e0, data_ov047_02262978,
    data_ov047_022629a8, data_ov047_02262b30, data_ov047_02262bb8, data_ov047_02262bb0, data_ov047_02262ba8,
    data_ov047_02262ba0, data_ov047_02262b98, data_ov047_02262b90, data_ov047_02262b88, data_ov047_02262b80,
    data_ov047_02262b78, data_ov047_02262b70, data_ov047_02262b68;

/* __sinit_ov047_02262838: the entries and updates of the owl's nine states, in order. */
void Ov047Init_OwlStates(void)
{
    static const MemberPointer *const steps[2 * OWL_STATES] = {
        &data_ov047_022629d8, &data_ov047_02262970, /* 0: Owl_EnterStand, Owl_UpdateStand */
        &data_ov047_022629e0, &data_ov047_02262978, /* 1: Owl_EnterTurnBack, Owl_UpdateTurnBack */
        &data_ov047_022629a8, &data_ov047_02262b30, /* 2: Owl_EnterAsleep, Owl_UpdateAsleep */
        &data_ov047_02262bb8, &data_ov047_02262bb0, /* 3: Owl_EnterTalk, Owl_UpdateTalk */
        &__ptmf_null,         &data_ov047_02262ba8, /* 4: none, Owl_UpdateTalked */
        &data_ov047_02262ba0, &data_ov047_02262b98, /* 5: Owl_EnterAct, Owl_UpdateAct */
        &data_ov047_02262b90, &data_ov047_02262b88, /* 6: Owl_EnterAwait, Owl_UpdateAwait */
        &data_ov047_02262b80, &data_ov047_02262b78, /* 7: Owl_EnterOther, Owl_UpdateOther */
        &data_ov047_02262b70, &data_ov047_02262b68, /* 8: Owl_EnterPaused, Owl_UpdatePaused */
    };
    for (int i = 0; i < OWL_STATES; i++) {
        data_ov047_02263048[i].enter = *steps[2 * i];
        data_ov047_02263048[i].update = *steps[2 * i + 1];
    }
}
CLEAN_AS(__sinit_ov047_02262838, Ov047Init_OwlStates)
