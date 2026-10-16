/* Tables by animation resource (the resources of anim_slots.h): how a body animation lets the
 * held item animate (AnimTables_HeldMode), the group of joint pairs a held item's animation
 * binds (AnimTables_HeldJointGroup, the pairs by AnimTables_HeldJointCount,
 * AnimTables_HeldJointA and AnimTables_HeldJointB), and the face's two animations that go with
 * a body animation (AnimTables_FaceAnimA and AnimTables_FaceAnimB). field_actor_anim.c and
 * scene_face.h read them. */
#ifndef CLEAN_MAIN_ANIM_TABLES_H
#define CLEAN_MAIN_ANIM_TABLES_H

#include "types.h"

/* AnimTables_HeldMode: the held item animates normally (0), only for items 0x1380 to 0x13a7
 * (1), with group 1's first joint pair as well (2), or not at all (3). */
#define ANIM_TABLES_HELD_NORMAL 0
#define ANIM_TABLES_HELD_SOME_ITEMS 1
#define ANIM_TABLES_HELD_EXTRA_PAIR 2
#define ANIM_TABLES_HELD_NONE 3

/* A joint pair of a group. */
typedef struct AnimTablesJointPair {
    u8 a;
    u8 b;
} AnimTablesJointPair;

unsigned char AnimTables_HeldMode(unsigned int animation);
unsigned short AnimTables_HeldJointGroup(unsigned int held);
unsigned char AnimTables_HeldJointB(int group, int index);
unsigned char AnimTables_HeldJointA(int group, int index);
unsigned char AnimTables_HeldJointCount(unsigned int group);
unsigned short AnimTables_FaceAnimB(unsigned int animation);
unsigned short AnimTables_FaceAnimA(unsigned int animation);

#endif
