/* Overlay 75's static initialiser, run when the overlay is loaded: colours its source files
 * define for themselves, the tables of member functions the town pelican (town_pelican.h) and
 * his talk scene (town_pelican_talk.h) dispatch through, copied from the overlay's constants
 * (the compiler cannot place member pointers in initialised data), and the two points beside
 * his way he steps to, registered for destruction like static C++ objects. */
#include "autoload_2/vector.h"
#include "clean.h"
#include "town_pelican.h"
#include "town_pelican_talk.h"
#include "types.h"

/* A colour of four 5-bit components (the fourth always 31). */
typedef struct TownPelicanInitColour {
    u8 c0;
    u8 c1;
    u8 c2;
    u8 c3;
} TownPelicanInitColour;

/* The record __register_global_object links an object into, so that its destructor runs when
 * the overlay goes. */
typedef struct TownPelicanInitRecord {
    struct TownPelicanInitRecord *next;
    void *destruct;
    void *object;
} TownPelicanInitRecord;

/* The six colours: red, blue, yellow, green, cyan and grey. */
extern TownPelicanInitColour data_ov075_02279acc, data_ov075_02279ad4, data_ov075_02279ad0, data_ov075_02279ac4,
    data_ov075_02279ac8, data_ov075_02279ac0;
/* The null member pointer (the C++ runtime's). */
extern const MemberPointer __ptmf_null;
/* The talk scene's sequences: none, then the waking (TownPelicanTalk_Wake). Their flags (byte
 * 8 of each entry) are the overlay's data and are not written. */
extern const MemberPointer data_ov075_022798c0;
extern TownPelicanTalkStep data_ov075_02279930[TOWN_PELICAN_TALK_SEQUENCES];
/* His states: each one's entry, then its update. */
extern const MemberPointer data_ov075_022798d8, data_ov075_022798e0, data_ov075_022798f0, data_ov075_022798f8,
    data_ov075_022798c8, data_ov075_022798a0, data_ov075_022798a8, data_ov075_022798b0, data_ov075_022798b8,
    data_ov075_022798d0, data_ov075_022798e8;
extern TownPelicanStep data_ov075_02279b08[TOWN_PELICAN_STATES];
/* The points beside his way, and their records. */
extern Vec3 data_ov075_02279af0[2];
extern TownPelicanInitRecord data_ov075_02279ad8, data_ov075_02279ae4;

extern void __register_global_object(void *object, void *destruct, void *record);
/* The destructor of a point: nothing (the game's function is handed on). */
extern void func_020012dc(void *object);

static void tpel_init_colour(TownPelicanInitColour *colour, u8 c0, u8 c1, u8 c2, u8 c3)
{
    colour->c0 = c0;
    colour->c1 = c1;
    colour->c2 = c2;
    colour->c3 = c3;
}

static void tpel_init_point(Vec3 *point, fx32 x, TownPelicanInitRecord *record)
{
    point->x = x;
    point->y = 0;
    point->z = 0x1000;
    __register_global_object(point, (void *) (uintptr_t) func_020012dc, record);
}

/* __sinit_ov075_02279724: the colours; the two sequences' functions; the six states' entries
 * and updates, in order (state 3's entry is read back from sequence 0's function, the null one); the
 * points (0.5, 0, 1.0) and (-0.5, 0, 1.0), each registered. */
void TownPelicanInit_Tables(void)
{
    static const MemberPointer *const states[2 * TOWN_PELICAN_STATES] = {
        &data_ov075_022798d8,
        &data_ov075_022798e0, /* 0: rest */
        &data_ov075_022798f0,
        &data_ov075_022798f8, /* 1: talk */
        &data_ov075_022798c8,
        &data_ov075_022798a0, /* 2: talk end */
        &data_ov075_02279930[TOWN_PELICAN_TALK_SEQUENCE_NONE].run,
        &data_ov075_022798a8, /* 3: talked */
        &data_ov075_022798b0,
        &data_ov075_022798b8, /* 4: hidden */
        &data_ov075_022798d0,
        &data_ov075_022798e8, /* 5: wander */
    };

    tpel_init_colour(&data_ov075_02279acc, 31, 20, 20, 31);
    tpel_init_colour(&data_ov075_02279ad4, 20, 20, 31, 31);
    tpel_init_colour(&data_ov075_02279ad0, 31, 31, 20, 31);
    tpel_init_colour(&data_ov075_02279ac4, 20, 31, 20, 31);
    tpel_init_colour(&data_ov075_02279ac8, 20, 31, 31, 31);
    tpel_init_colour(&data_ov075_02279ac0, 20, 24, 24, 31);
    data_ov075_02279930[TOWN_PELICAN_TALK_SEQUENCE_NONE].run = __ptmf_null;
    data_ov075_02279930[TOWN_PELICAN_TALK_SEQUENCE_WAKE].run = data_ov075_022798c0;
    for (int i = 0; i < TOWN_PELICAN_STATES; i++) {
        data_ov075_02279b08[i].enter = *states[2 * i];
        data_ov075_02279b08[i].update = *states[2 * i + 1];
    }
    tpel_init_point(&data_ov075_02279af0[0], 0x800, &data_ov075_02279ad8);
    tpel_init_point(&data_ov075_02279af0[1], -0x800, &data_ov075_02279ae4);
}
CLEAN_AS(__sinit_ov075_02279724, TownPelicanInit_Tables)
