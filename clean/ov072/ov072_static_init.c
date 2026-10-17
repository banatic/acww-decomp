/* Overlay 72's static initialiser, run when the overlay is loaded: the six colours its source
 * file defines for itself, then the talk scene's steps (gull_talk.h) and the table of its
 * character's states (gull.h), filled from the overlay's constants. */
#include "clean.h"
#include "gull.h"
#include "gull_talk.h"
#include "ov004/member_pointer.h"
#include "types.h"

/* A colour of four 5-bit components (the fourth always 31). */
typedef struct GullInitColour {
    u8 c0;
    u8 c1;
    u8 c2;
    u8 c3;
} GullInitColour;

static void gull_init_colour(GullInitColour *colour, u8 c0, u8 c1, u8 c2, u8 c3)
{
    colour->c0 = c0;
    colour->c1 = c1;
    colour->c2 = c2;
    colour->c3 = c3;
}

/* Red, blue, yellow, green, cyan and grey. */
extern GullInitColour data_ov072_02279bd0, data_ov072_02279bc0, data_ov072_02279bcc, data_ov072_02279bd4, data_ov072_02279bc4,
    data_ov072_02279bc8;

/* The constants: step 1's run (GullTalk_StepTurnToPlayer), then each state's entry and run;
 * GULL_TALKED has no entry. */
extern const MemberPointer __ptmf_null;
extern const MemberPointer data_ov072_022799c0, data_ov072_022799d0, data_ov072_022799d8, data_ov072_022799e0,
    data_ov072_022799e8, data_ov072_022799f0, data_ov072_022799f8, data_ov072_022799c8;

/* __sinit_ov072_022798b4: the colours, the steps' runs (step 0 none), then the states' table
 * in order. */
void GullInit_Tables(void)
{
    static const MemberPointer *const states[2 * GULL_STATES] = {
        &data_ov072_022799d0, &data_ov072_022799d8, /* GULL_UNMET: Gull_EnterUnmet, Gull_UpdateUnmet */
        &data_ov072_022799e0, &data_ov072_022799e8, /* GULL_IDLE */
        &data_ov072_022799f0, &data_ov072_022799f8, /* GULL_TALK */
        &__ptmf_null,         &data_ov072_022799c8, /* GULL_TALKED: no entry, Gull_UpdateTalked */
    };

    gull_init_colour(&data_ov072_02279bd0, 31, 20, 20, 31);
    gull_init_colour(&data_ov072_02279bc0, 20, 20, 31, 31);
    gull_init_colour(&data_ov072_02279bcc, 31, 31, 20, 31);
    gull_init_colour(&data_ov072_02279bd4, 20, 31, 20, 31);
    gull_init_colour(&data_ov072_02279bc4, 20, 31, 31, 31);
    gull_init_colour(&data_ov072_02279bc8, 20, 24, 24, 31);
    data_ov072_02279a24[GULL_TALK_STEP_NONE].run = __ptmf_null;
    data_ov072_02279a24[GULL_TALK_STEP_TURN_TO_PLAYER].run = data_ov072_022799c0;
    for (int i = 0; i < GULL_STATES; i++) {
        data_ov072_02279bd8[i].enter = *states[2 * i];
        data_ov072_02279bd8[i].run = *states[2 * i + 1];
    }
}
CLEAN_AS(__sinit_ov072_022798b4, GullInit_Tables)
