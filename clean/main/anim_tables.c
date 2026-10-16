/* Tables by animation resource (anim_tables.h). */
#include "anim_tables.h"

#include "clean.h"

extern const u8 data_020cc008[];                   /* the held mode by body animation */
extern const u16 data_020dd424[];                  /* the joint group by held item animation */
extern const u8 data_020dd410[];                   /* the number of joint pairs by group */
extern const AnimTablesJointPair *data_020dd414[]; /* the joint pairs by group */
extern const u16 data_020cc3d4[];                  /* the face's second animation by body animation */
extern const u16 data_020cc14c[];                  /* the face's first animation by body animation */

/* func_0205ceb0: how the body's `animation` lets the held item animate (ANIM_TABLES_HELD_*). */
unsigned char AnimTables_HeldMode(unsigned int animation)
{
    return data_020cc008[animation];
}
CLEAN_AS(func_0205ceb0, AnimTables_HeldMode)

/* func_0205cebc: the joint group of the held item's animation `held`; 4 or more is none. */
unsigned short AnimTables_HeldJointGroup(unsigned int held)
{
    return data_020dd424[held];
}
CLEAN_AS(func_0205cebc, AnimTables_HeldJointGroup)

/* func_0205cec8: the second joint of the group's pair `index`.
 * QUIRK: the group's count is looked up and not used: `index` is not checked against it. */
unsigned char AnimTables_HeldJointB(int group, int index)
{
    AnimTables_HeldJointCount((unsigned int) group);
    return data_020dd414[group][index].b;
}
CLEAN_AS(func_0205cec8, AnimTables_HeldJointB)

/* func_0205ceec: the first joint of the group's pair `index` (the same QUIRK). */
unsigned char AnimTables_HeldJointA(int group, int index)
{
    AnimTables_HeldJointCount((unsigned int) group);
    return data_020dd414[group][index].a;
}
CLEAN_AS(func_0205ceec, AnimTables_HeldJointA)

/* func_0205cf10: the number of joint pairs of the group. */
unsigned char AnimTables_HeldJointCount(unsigned int group)
{
    return data_020dd410[group];
}
CLEAN_AS(func_0205cf10, AnimTables_HeldJointCount)

/* func_0205cf1c: the face's second animation for the body's `animation`. */
unsigned short AnimTables_FaceAnimB(unsigned int animation)
{
    return data_020cc3d4[animation];
}
CLEAN_AS(func_0205cf1c, AnimTables_FaceAnimB)

/* func_0205cf28: the face's first animation for the body's `animation`. */
unsigned short AnimTables_FaceAnimA(unsigned int animation)
{
    return data_020cc14c[animation];
}
CLEAN_AS(func_0205cf28, AnimTables_FaceAnimA)
