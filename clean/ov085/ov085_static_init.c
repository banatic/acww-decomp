/* Overlay 85 (the turtle, turtle_snow_festival.h): its static initializer, run when the overlay is loaded,
 * which fills in the table of the turtle's states (data_ov085_022795e0, TurtleSnowFestival_SetState and
 * TurtleSnowFestival_Update): each state's entry and update, copied from the overlay's constants (C++
 * pointers to member functions, which the compiler does not fold into the table). */
#include <stdint.h>

#include "clean.h"
#include "turtle_snow_festival.h"
#include "types.h"

/* The table of the turtle's states. */
extern TurtleSnowFestivalStep data_ov085_022795e0[TURTLE_SNOW_FESTIVAL_STATE_COUNT];
/* The null member pointer (state 2 has no entry), and each state's entry and update. */
extern const MemberPointer __ptmf_null;
extern const MemberPointer data_ov085_022793e0, data_ov085_022793e8, data_ov085_022793f0, data_ov085_022793f8,
    data_ov085_02279400;

/* __sinit_ov085_02279368: the entries and updates of the turtle's three states, in order. The
 * address of the table. */
int TurtleSnowFestivalInit_States(void)
{
    static const MemberPointer *const steps[2 * TURTLE_SNOW_FESTIVAL_STATE_COUNT] = {
        &data_ov085_022793f8, &data_ov085_02279400, /* 0: TurtleSnowFestival_EnterStand, TurtleSnowFestival_UpdateStand */
        &data_ov085_022793f0, &data_ov085_022793e8, /* 1: TurtleSnowFestival_EnterTalk, TurtleSnowFestival_UpdateTalk */
        &__ptmf_null,         &data_ov085_022793e0, /* 2: none, TurtleSnowFestival_UpdateTalked */
    };
    for (int i = 0; i < TURTLE_SNOW_FESTIVAL_STATE_COUNT; i++) {
        data_ov085_022795e0[i].enter = *steps[2 * i];
        data_ov085_022795e0[i].update = *steps[2 * i + 1];
    }
    return (int) (uintptr_t) data_ov085_022795e0;
}
CLEAN_AS(__sinit_ov085_02279368, TurtleSnowFestivalInit_States)
