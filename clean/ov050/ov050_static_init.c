/* Overlay 50's static initialiser, run when the overlay is loaded: the table of member
 * functions the clerks' states dispatch through (nook_clerk.h), copied from the overlay's
 * constants (the compiler cannot place member pointers in initialised data). */
#include "clean.h"
#include "nook_clerk.h"
#include "types.h"

/* The states: each one's entry, then its update. The table has three symbols: states 0 to 7,
 * 8 to 15 and 16 to 18. */
extern const MemberPointer data_ov050_022654b8, data_ov050_02265758, data_ov050_02265590, data_ov050_02265460,
    data_ov050_022654e0, data_ov050_02265630, data_ov050_022655d0, data_ov050_02265628, data_ov050_02265588,
    data_ov050_022654a8, data_ov050_02265720, data_ov050_02265578, data_ov050_02265598, data_ov050_022654a0,
    data_ov050_022654b0, data_ov050_02265458, data_ov050_022655d8, data_ov050_02265468, data_ov050_022655e0,
    data_ov050_022657d8, data_ov050_022654e8, data_ov050_02265608, data_ov050_02265448, data_ov050_02265450,
    data_ov050_02265470, data_ov050_022657f0, data_ov050_022657e8, data_ov050_022657e0, data_ov050_02265738,
    data_ov050_02265748, data_ov050_022657c8, data_ov050_022657c0, data_ov050_022657b8, data_ov050_022657b0,
    data_ov050_022657a8, data_ov050_022657a0, data_ov050_02265798, data_ov050_02265790;
extern NookClerkStep data_ov050_02265f08[NOOK_CLERK_STATES];
extern NookClerkStep data_ov050_02266008[3];

/* __sinit_ov050_0226520c: the entries and updates of the nineteen states, in order. The address
 * of the table's last part. */
int NookClerkInit_Tables(void)
{
    static const MemberPointer *const states[2 * NOOK_CLERK_STATES] = {
        &data_ov050_022654b8, &data_ov050_02265758, /* 0: greet */
        &data_ov050_02265590, &data_ov050_02265460, /* 1: stand */
        &data_ov050_022654e0, &data_ov050_02265630, /* 2: turn */
        &data_ov050_022655d0, &data_ov050_02265628, /* 3: walk */
        &data_ov050_02265588, &data_ov050_022654a8, /* 4: talk */
        &data_ov050_02265720, &data_ov050_02265578, /* 5: talk, leave */
        &data_ov050_02265598, &data_ov050_022654a0, /* 6: talked */
        &data_ov050_022654b0, &data_ov050_02265458, /* 7: act */
        &data_ov050_022655d8, &data_ov050_02265468, /* 8: await */
        &data_ov050_022655e0, &data_ov050_022657d8, /* 9: other */
        &data_ov050_022654e8, &data_ov050_02265608, /* 10: await twin */
        &data_ov050_02265448, &data_ov050_02265450, /* 11: face */
        &data_ov050_02265470, &data_ov050_022657f0, /* 12: still */
        &data_ov050_022657e8, &data_ov050_022657e0, /* 13: linked stand */
        &data_ov050_02265738, &data_ov050_02265748, /* 14: linked turn */
        &data_ov050_022657c8, &data_ov050_022657c0, /* 15: paused */
        &data_ov050_022657b8, &data_ov050_022657b0, /* 16: approach */
        &data_ov050_022657a8, &data_ov050_022657a0, /* 17: lead */
        &data_ov050_02265798, &data_ov050_02265790, /* 18: turn, ask */
    };

    for (int i = 0; i < NOOK_CLERK_STATES; i++) {
        data_ov050_02265f08[i].enter = *states[2 * i];
        data_ov050_02265f08[i].update = *states[2 * i + 1];
    }
    return (int) (u32) (uintptr_t) data_ov050_02266008;
}
CLEAN_AS(__sinit_ov050_0226520c, NookClerkInit_Tables)
