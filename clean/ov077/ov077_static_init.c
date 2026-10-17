/* Overlay 77's static initialiser, run when the overlay is loaded: the functions of the mole's
 * talk sequences (mole_talk.h) and of his states (mole.h), copied from the overlay's constants
 * (the compiler cannot place member pointers in initialised data). */
#include <stdint.h>

#include "clean.h"
#include "mole.h"
#include "mole_talk.h"
#include "ov004/member_pointer.h"
#include "types.h"

/* The talk's sequences: none, MoleTalk_AfterPhrase, MoleTalk_Wait. */
extern const MemberPointer __ptmf_null;
extern const MemberPointer data_ov077_0227973c, data_ov077_02279714;
/* His states: each one's entry, then its run. */
extern const MemberPointer data_ov077_0227971c, data_ov077_0227976c, data_ov077_02279764, data_ov077_02279744,
    data_ov077_02279754, data_ov077_0227974c, data_ov077_0227970c, data_ov077_02279724, data_ov077_02279704,
    data_ov077_0227972c, data_ov077_0227975c, data_ov077_02279734;

/* __sinit_ov077_02279608: the sequences' functions (their flags stay as the data has them),
 * then the entries and runs of the six states, in order. The address of the states' table.
 * QUIRK: the address answered is only what the routine leaves in its result register. */
int MoleInit_Tables(void)
{
    static const MemberPointer *const sequences[MOLE_TALK_SEQUENCES] = {
        &__ptmf_null,         /* none */
        &data_ov077_0227973c, /* MoleTalk_AfterPhrase */
        &data_ov077_02279714, /* MoleTalk_Wait */
    };
    static const MemberPointer *const states[2 * MOLE_STATES] = {
        &data_ov077_0227971c, &data_ov077_0227976c, /* MOLE_STATE_0 */
        &data_ov077_02279764, &data_ov077_02279744, /* MOLE_TALK */
        &data_ov077_02279754, &data_ov077_0227974c, /* MOLE_TALKED */
        &data_ov077_0227970c, &data_ov077_02279724, /* MOLE_WAIT */
        &data_ov077_02279704, &data_ov077_0227972c, /* MOLE_RISE */
        &data_ov077_0227975c, &data_ov077_02279734, /* MOLE_SINK */
    };
    for (int i = 0; i < MOLE_TALK_SEQUENCES; i++) {
        data_ov077_022797d0[i].run = *sequences[i];
    }
    for (int i = 0; i < MOLE_STATES; i++) {
        data_ov077_022799a0[i].enter = *states[2 * i];
        data_ov077_022799a0[i].run = *states[2 * i + 1];
    }
    return (int) (u32) (uintptr_t) data_ov077_022799a0;
}
CLEAN_AS(__sinit_ov077_02279608, MoleInit_Tables)
