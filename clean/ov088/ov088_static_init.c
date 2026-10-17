/* Overlay 88's static initialiser, run when the overlay is loaded: colours its source files
 * define for themselves, the tables of member functions its character (reaction_npc.h) and its
 * talk scene (reaction_npc_talk.h) dispatch through, copied from the overlay's constants (the
 * compiler cannot place member pointers in initialised data), and the two points beside its
 * way it steps to, registered for destruction like static C++ objects. */
#include <stdint.h>

#include "autoload_2/vector.h"
#include "clean.h"
#include "ov004/member_pointer.h"
#include "reaction_npc.h"
#include "reaction_npc_talk.h"
#include "types.h"

/* A colour of four 5-bit components (the fourth always 31). */
typedef struct ReactionNpcInitColour {
    u8 c0;
    u8 c1;
    u8 c2;
    u8 c3;
} ReactionNpcInitColour;

/* The record __register_global_object links an object into, so that its destructor runs when
 * the overlay goes. */
typedef struct ReactionNpcInitRecord {
    struct ReactionNpcInitRecord *next;
    void *destruct;
    void *object;
} ReactionNpcInitRecord;

/* The six colours: red, blue, yellow, green, cyan and grey. */
extern ReactionNpcInitColour data_ov088_02279df4, data_ov088_02279de8, data_ov088_02279de4, data_ov088_02279de0,
    data_ov088_02279df0, data_ov088_02279dec;
/* The null member pointer (the C++ runtime's), the talk scene's steps' functions and the
 * states' functions. */
extern const MemberPointer __ptmf_null;
extern const MemberPointer data_ov088_02279b78, data_ov088_02279bb0, data_ov088_02279b88, data_ov088_02279b98;
extern const MemberPointer data_ov088_02279ba8, data_ov088_02279bb8, data_ov088_02279b80, data_ov088_02279b60,
    data_ov088_02279b68, data_ov088_02279b70, data_ov088_02279bc0, data_ov088_02279b90, data_ov088_02279ba0;
extern ReactionNpcTalkStep data_ov088_02279c14[REACTION_NPC_STEPS];
extern ReactionNpcStep data_ov088_02279e28[REACTION_NPC_STATES];
/* The points beside its way, and their records. */
extern Vec3 data_ov088_02279e10[2];
extern ReactionNpcInitRecord data_ov088_02279df8, data_ov088_02279e04;

extern void __register_global_object(void *object, void *destruct, void *record);
/* The destructor of a point: nothing (the game's function is handed on). */
extern void func_020012dc(void *object);

static void rnpc_init_colour(ReactionNpcInitColour *colour, u8 c0, u8 c1, u8 c2, u8 c3)
{
    colour->c0 = c0;
    colour->c1 = c1;
    colour->c2 = c2;
    colour->c3 = c3;
}

static void rnpc_init_point(Vec3 *point, fx32 x, ReactionNpcInitRecord *record)
{
    point->x = x;
    point->y = 0;
    point->z = 0x1000;
    __register_global_object(point, (void *) (uintptr_t) func_020012dc, record);
}

/* __sinit_ov088_022799c4: the colours; the talk scene's five steps (step 0 has no function);
 * the five states' entries and updates, in order (state 1's entry is step 0's, the null
 * member pointer, read back); the points (0.5, 0, 1.0) and (-0.5, 0, 1.0), each registered. */
void ReactionNpcInit_Tables(void)
{
    static const MemberPointer *const steps[REACTION_NPC_STEPS] = {
        &__ptmf_null, &data_ov088_02279b78, &data_ov088_02279bb0, &data_ov088_02279b88, &data_ov088_02279b98,
    };
    rnpc_init_colour(&data_ov088_02279df4, 31, 20, 20, 31);
    rnpc_init_colour(&data_ov088_02279de8, 20, 20, 31, 31);
    rnpc_init_colour(&data_ov088_02279de4, 31, 31, 20, 31);
    rnpc_init_colour(&data_ov088_02279de0, 20, 31, 20, 31);
    rnpc_init_colour(&data_ov088_02279df0, 20, 31, 31, 31);
    rnpc_init_colour(&data_ov088_02279dec, 20, 24, 24, 31);
    for (int i = 0; i < REACTION_NPC_STEPS; i++) {
        data_ov088_02279c14[i].run = *steps[i];
    }
    const MemberPointer *const states[2 * REACTION_NPC_STATES] = {
        &data_ov088_02279ba8,        &data_ov088_02279bb8, /* 0: talk end */
        &data_ov088_02279c14[0].run, &data_ov088_02279b80, /* 1: talked */
        &data_ov088_02279b60,        &data_ov088_02279b68, /* 2: wander */
        &data_ov088_02279b70,        &data_ov088_02279bc0, /* 3: wait */
        &data_ov088_02279b90,        &data_ov088_02279ba0, /* 4: talk */
    };
    for (int i = 0; i < REACTION_NPC_STATES; i++) {
        data_ov088_02279e28[i].enter = *states[2 * i];
        data_ov088_02279e28[i].update = *states[2 * i + 1];
    }
    rnpc_init_point(&data_ov088_02279e10[0], 0x800, &data_ov088_02279df8);
    rnpc_init_point(&data_ov088_02279e10[1], -0x800, &data_ov088_02279e04);
}
CLEAN_AS(__sinit_ov088_022799c4, ReactionNpcInit_Tables)
