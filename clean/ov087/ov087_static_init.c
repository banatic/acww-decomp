/* Overlay 87's static initialiser, run when the overlay is loaded: the table of states of its
 * character (acorn_npc.h), copied from the overlay's constants (the compiler cannot place
 * member pointers in initialised data). */
#include <stdint.h>

#include "acorn_npc.h"
#include "clean.h"
#include "ov004/member_pointer.h"
#include "types.h"

/* The states: each one's entry, then its update (state 2 has no entry: the null member
 * pointer). */
extern const MemberPointer data_ov087_022793c8, data_ov087_022793e0, data_ov087_022793e8, data_ov087_022793d8,
    data_ov087_022793d0;
extern const MemberPointer __ptmf_null;
extern AcornNpcStep data_ov087_022795c0[ACORN_NPC_STATES];

/* __sinit_ov087_02279354: the entries and updates of the three states, in order. The table's
 * address (the value left in the result register). */
int AcornNpcInit_Tables(void)
{
    static const MemberPointer *const states[2 * ACORN_NPC_STATES] = {
        &data_ov087_022793c8, &data_ov087_022793e0, /* 0: stand */
        &data_ov087_022793e8, &data_ov087_022793d8, /* 1: talk */
        &__ptmf_null,         &data_ov087_022793d0, /* 2: talked */
    };
    for (int i = 0; i < ACORN_NPC_STATES; i++) {
        data_ov087_022795c0[i].enter = *states[2 * i];
        data_ov087_022795c0[i].update = *states[2 * i + 1];
    }
    return (int) (u32) (uintptr_t) data_ov087_022795c0;
}
CLEAN_AS(__sinit_ov087_02279354, AcornNpcInit_Tables)
