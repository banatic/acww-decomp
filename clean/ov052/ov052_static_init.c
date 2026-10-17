/* Overlay 52 (the fox in his tent, fox_tent.h): its static initialiser, run when the overlay is
 * loaded, which fills in the table of the fox's states (data_ov052_02262000, FoxTent_SetState
 * and FoxTent_Update): each state's entry and update, copied from the overlay's constants (C++
 * pointers to member functions, which the compiler does not fold into the table). */
#include <stdint.h>

#include "clean.h"
#include "fox_tent.h"
#include "types.h"

/* The table of the fox's states. */
extern FoxTentStep data_ov052_02262000[FOX_TENT_STATES];
/* Each state's entry, then its update. */
extern const MemberPointer data_ov052_02261da0, data_ov052_02261da8, data_ov052_02261e08, data_ov052_02261e40,
    data_ov052_02261e48, data_ov052_02261de0, data_ov052_02261e38, data_ov052_02261e30, data_ov052_02261e28,
    data_ov052_02261e20, data_ov052_02261e18, data_ov052_02261e10, data_ov052_02261dc8, data_ov052_02261db8,
    data_ov052_02261df8, data_ov052_02261df0, data_ov052_02261de8, data_ov052_02261db0, data_ov052_02261dd8,
    data_ov052_02261dd0, data_ov052_02261dc0, data_ov052_02261e00;

/* The state the compiler's second pointer into the table points at (0x02262080). */
#define OV052_INIT_SECOND_PART 8

/* __sinit_ov052_02261c48: the entries and updates of the fox's eleven states, in order. The
 * address of state 8's entry (where the compiler's second pointer into the table starts). */
int Ov052Init_FoxTentStates(void)
{
    static const MemberPointer *const steps[2 * FOX_TENT_STATES] = {
        &data_ov052_02261da0, &data_ov052_02261da8, /* 0: FoxTent_EnterGreet, FoxTent_UpdateGreet */
        &data_ov052_02261e08, &data_ov052_02261e40, /* 1: FoxTent_EnterStand, FoxTent_UpdateStand */
        &data_ov052_02261e48, &data_ov052_02261de0, /* 2: FoxTent_EnterTurn, FoxTent_UpdateTurn */
        &data_ov052_02261e38, &data_ov052_02261e30, /* 3: FoxTent_EnterFollow, FoxTent_UpdateFollow */
        &data_ov052_02261e28, &data_ov052_02261e20, /* 4: FoxTent_EnterFollow4, FoxTent_UpdateFollow4 */
        &data_ov052_02261e18, &data_ov052_02261e10, /* 5: FoxTent_EnterTalk, FoxTent_UpdateTalk */
        &data_ov052_02261dc8, &data_ov052_02261db8, /* 6: FoxTent_EnterTalkThenOut, FoxTent_UpdateTalkThenOut */
        &data_ov052_02261df8, &data_ov052_02261df0, /* 7: FoxTent_EnterTalked, FoxTent_UpdateTalked */
        &data_ov052_02261de8, &data_ov052_02261db0, /* 8: FoxTent_EnterPaused, FoxTent_UpdatePaused */
        &data_ov052_02261dd8, &data_ov052_02261dd0, /* 9: FoxTent_EnterCome, FoxTent_UpdateCome */
        &data_ov052_02261dc0, &data_ov052_02261e00, /* 10: FoxTent_EnterAtExit, FoxTent_UpdateAtExit */
    };
    for (int i = 0; i < FOX_TENT_STATES; i++) {
        data_ov052_02262000[i].enter = *steps[2 * i];
        data_ov052_02262000[i].update = *steps[2 * i + 1];
    }
    return (int) (uintptr_t) &data_ov052_02262000[OV052_INIT_SECOND_PART];
}
CLEAN_AS(__sinit_ov052_02261c48, Ov052Init_FoxTentStates)
