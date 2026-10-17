/* Overlay 68's static initialisers (ov068_static_init.h). */
#include "ov068_static_init.h"

#include "clean.h"
#include "ov004/member_pointer.h"
#include "types.h"

/* ---- What the initialisers share */

/* `count` member pointers copied from the overlay's constants, in order. */
static void ov068_init_copy(MemberPointer *table, const MemberPointer *const *constants, int count)
{
    for (int i = 0; i < count; i++) {
        table[i] = *constants[i];
    }
}

/* A colour of four 5-bit components (the fourth always 31). */
typedef struct Ov068InitColour {
    u8 c0;
    u8 c1;
    u8 c2;
    u8 c3;
} Ov068InitColour;

static void ov068_init_colour(Ov068InitColour *colour, u8 c0, u8 c1, u8 c2, u8 c3)
{
    colour->c0 = c0;
    colour->c1 = c1;
    colour->c2 = c2;
    colour->c3 = c3;
}

/* The six colours several source files define for themselves: red, blue, yellow, green, cyan
 * and grey, in that order. */
static void ov068_init_colours(Ov068InitColour *red, Ov068InitColour *blue, Ov068InitColour *yellow, Ov068InitColour *green,
                               Ov068InitColour *cyan, Ov068InitColour *grey)
{
    ov068_init_colour(red, 31, 20, 20, 31);
    ov068_init_colour(blue, 20, 20, 31, 31);
    ov068_init_colour(yellow, 31, 31, 20, 31);
    ov068_init_colour(green, 20, 31, 20, 31);
    ov068_init_colour(cyan, 20, 31, 31, 31);
    ov068_init_colour(grey, 20, 24, 24, 31);
}

/* A row of a scene's steps: the member function and whether it runs each frame (the flag is
 * not written here). */
typedef struct Ov068InitStep {
    MemberPointer run;
    u8 each_frame;
    u8 unk_09[3];
} Ov068InitStep;

static_assert(sizeof(Ov068InitStep) == 0xc, "step row");

/* The null member pointer (the C++ runtime's). */
extern const MemberPointer __ptmf_null;

/* ---- The initialisers, in address order */

/* The outdoor villager's behaviours (outdoor_villager_behaviour.h): 24 rows of a start and an
 * update, i.e. 48 member pointers. */
extern MemberPointer data_ov068_02278484[48];
extern const MemberPointer data_ov068_02276e58, data_ov068_02276e70, data_ov068_02276ea8, data_ov068_02276eb8,
    data_ov068_02276ec8, data_ov068_02276ed0, data_ov068_02276ed8, data_ov068_02276ee8, data_ov068_02276ef0,
    data_ov068_02276ef8, data_ov068_02276f00, data_ov068_02276f08, data_ov068_02276f28, data_ov068_02276f30,
    data_ov068_02276f38, data_ov068_02276f58, data_ov068_02276f68, data_ov068_02276f80, data_ov068_02276f98,
    data_ov068_02276fa0, data_ov068_02276fa8, data_ov068_02276fc8, data_ov068_02276fd0, data_ov068_02277008,
    data_ov068_02277010, data_ov068_02277028, data_ov068_02277038, data_ov068_02277040, data_ov068_022770c0,
    data_ov068_022770d0, data_ov068_022770d8, data_ov068_022770e0, data_ov068_022770f0, data_ov068_022770f8,
    data_ov068_02277100, data_ov068_02277108, data_ov068_02277110, data_ov068_02277118, data_ov068_02277130,
    data_ov068_02277138, data_ov068_02277140, data_ov068_02277148, data_ov068_02277158, data_ov068_02277178,
    data_ov068_02277180, data_ov068_02277188, data_ov068_02277190, data_ov068_02277198;

/* The half-angles of facing the outdoor villager uses (outdoor_villager_moves.c,
 * outdoor_villager.c), copied from main's. */
extern s16 data_ov068_02278264, data_ov068_02278260;
extern s16 data_020c80f0;
extern s16 data_020ca4cc;

/* __sinit_ov068_02276800: the outdoor villager's behaviour table, then its two angles. */
void Ov068Init_OutdoorVillagerBehaviours(void)
{
    static const MemberPointer *const constants[48] = {
        &data_ov068_02276eb8, &data_ov068_02276ea8, &data_ov068_02276ed0, &data_ov068_02276ec8, &data_ov068_02276ed8,
        &data_ov068_02277180, &data_ov068_02276ee8, &data_ov068_02276ef0, &data_ov068_02276ef8, &data_ov068_02277190,
        &data_ov068_02276f00, &data_ov068_02276e70, &data_ov068_02276f08, &data_ov068_02276e58, &data_ov068_02276f28,
        &data_ov068_02276f30, &data_ov068_02276f38, &data_ov068_02277198, &data_ov068_02276f58, &data_ov068_02277188,
        &data_ov068_02276f68, &data_ov068_02277178, &data_ov068_02276f80, &data_ov068_02276f98, &data_ov068_02276fa0,
        &data_ov068_02277158, &data_ov068_02276fa8, &data_ov068_02277148, &data_ov068_02277140, &data_ov068_02277138,
        &data_ov068_02277130, &data_ov068_02276fc8, &data_ov068_02276fd0, &data_ov068_02277118, &data_ov068_02277110,
        &data_ov068_02277108, &data_ov068_02277100, &data_ov068_022770f8, &data_ov068_022770f0, &data_ov068_02277008,
        &data_ov068_02277010, &data_ov068_022770e0, &data_ov068_022770d8, &data_ov068_022770d0, &data_ov068_02277028,
        &data_ov068_022770c0, &data_ov068_02277038, &data_ov068_02277040,
    };
    ov068_init_copy(data_ov068_02278484, constants, 48);
    data_ov068_02278264 = data_020c80f0;
    data_ov068_02278260 = data_020ca4cc;
}
CLEAN_AS(__sinit_ov068_02276800, Ov068Init_OutdoorVillagerBehaviours)

extern Ov068InitColour data_ov068_02278614, data_ov068_02278610, data_ov068_02278604, data_ov068_02278608, data_ov068_02278618,
    data_ov068_0227860c;

/* __sinit_ov068_02276ad8: the six colours of its source file. */
void Ov068Init_Colours02278604(void)
{
    ov068_init_colours(&data_ov068_02278614, &data_ov068_02278610, &data_ov068_02278604, &data_ov068_02278608,
                       &data_ov068_02278618, &data_ov068_0227860c);
}
CLEAN_AS(__sinit_ov068_02276ad8, Ov068Init_Colours02278604)

/* Tom Nook in the town (town_nook.h): his scene's two steps, and his six states' starts and
 * updates. */
extern Ov068InitStep data_ov068_02277454[2];
extern MemberPointer data_ov068_02278658[12];
extern const MemberPointer data_ov068_02277370, data_ov068_02277350, data_ov068_02277358, data_ov068_02277398,
    data_ov068_02277348, data_ov068_022773a0, data_ov068_02277388, data_ov068_02277340, data_ov068_02277368,
    data_ov068_02277360, data_ov068_02277378, data_ov068_02277380, data_ov068_02277390;

/* __sinit_ov068_02276b34: Tom Nook's step and state tables; the first step is the null member
 * pointer. QUIRK: it returns the address of the state table. */
int Ov068Init_TownNookTables(void)
{
    static const MemberPointer *const states[12] = {
        &data_ov068_02277350, &data_ov068_02277358, &data_ov068_02277398, &data_ov068_02277348,
        &data_ov068_022773a0, &data_ov068_02277388, &data_ov068_02277340, &data_ov068_02277368,
        &data_ov068_02277360, &data_ov068_02277378, &data_ov068_02277380, &data_ov068_02277390,
    };
    data_ov068_02277454[0].run = __ptmf_null;
    data_ov068_02277454[1].run = data_ov068_02277370;
    ov068_init_copy(data_ov068_02278658, states, 12);
    return (int) (uintptr_t) data_ov068_02278658;
}
CLEAN_AS(__sinit_ov068_02276b34, Ov068Init_TownNookTables)

extern Ov068InitColour data_ov068_022786d0, data_ov068_022786d8, data_ov068_022786e4, data_ov068_022786e0, data_ov068_022786d4,
    data_ov068_022786dc;

/* __sinit_ov068_02276c08: the six colours of its source file. */
void Ov068Init_Colours022786d0(void)
{
    ov068_init_colours(&data_ov068_022786d0, &data_ov068_022786d8, &data_ov068_022786e4, &data_ov068_022786e0,
                       &data_ov068_022786d4, &data_ov068_022786dc);
}
CLEAN_AS(__sinit_ov068_02276c08, Ov068Init_Colours022786d0)

/* The cafe guest (cafe_guest.h): its scene's six steps, and its five states' starts and
 * updates. */
extern Ov068InitStep data_ov068_02277d70[6];
extern MemberPointer data_ov068_02278840[10];
extern const MemberPointer data_ov068_02277a3c, data_ov068_022779bc, data_ov068_02277a2c, data_ov068_02277a5c,
    data_ov068_02277a64, data_ov068_02277a34, data_ov068_02277a24, data_ov068_022779e4, data_ov068_022779cc,
    data_ov068_022779d4, data_ov068_02277a14, data_ov068_02277a0c, data_ov068_022779f4, data_ov068_022779ec,
    data_ov068_02277a54;

/* __sinit_ov068_02276c64: the cafe guest's step and state tables; the first step is the null
 * member pointer. QUIRK: it returns the address of the state table. */
int Ov068Init_CafeGuestTables(void)
{
    static const MemberPointer *const steps[6] = {
        &__ptmf_null,         &data_ov068_02277a3c, &data_ov068_022779bc,
        &data_ov068_02277a2c, &data_ov068_02277a5c, &data_ov068_02277a64,
    };
    static const MemberPointer *const states[10] = {
        &data_ov068_02277a34, &data_ov068_02277a24, &data_ov068_022779e4, &data_ov068_022779cc, &data_ov068_022779d4,
        &data_ov068_02277a14, &data_ov068_02277a0c, &data_ov068_022779f4, &data_ov068_022779ec, &data_ov068_02277a54,
    };
    for (int i = 0; i < 6; i++) {
        data_ov068_02277d70[i].run = *steps[i];
    }
    ov068_init_copy(data_ov068_02278840, states, 10);
    return (int) (uintptr_t) data_ov068_02278840;
}
CLEAN_AS(__sinit_ov068_02276c64, Ov068Init_CafeGuestTables)

extern Ov068InitColour data_ov068_022788a8, data_ov068_022788a4, data_ov068_02278894, data_ov068_022788ac, data_ov068_02278898,
    data_ov068_0227889c;

/* __sinit_ov068_02276d54: the six colours of its source file. */
void Ov068Init_Colours02278894(void)
{
    ov068_init_colours(&data_ov068_022788a8, &data_ov068_022788a4, &data_ov068_02278894, &data_ov068_022788ac,
                       &data_ov068_02278898, &data_ov068_0227889c);
}
CLEAN_AS(__sinit_ov068_02276d54, Ov068Init_Colours02278894)

extern Ov068InitColour data_ov068_022788e8, data_ov068_022788d8, data_ov068_022788f0, data_ov068_022788e0, data_ov068_022788dc,
    data_ov068_022788e4;

/* __sinit_ov068_02276db0: the six colours of its source file. */
void Ov068Init_Colours022788d8(void)
{
    ov068_init_colours(&data_ov068_022788e8, &data_ov068_022788d8, &data_ov068_022788f0, &data_ov068_022788e0,
                       &data_ov068_022788dc, &data_ov068_022788e4);
}
CLEAN_AS(__sinit_ov068_02276db0, Ov068Init_Colours022788d8)
