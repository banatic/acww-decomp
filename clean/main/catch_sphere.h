/* The spheres a swing of the net is tested against (data_021d3124): overlay 3's insects add
 * theirs each frame (CatchSphere_Add), which also registers them with the pen's pick
 * (touch_pick_shapes.h) as kind CATCH_SPHERE_PICK_KIND, and FieldActor_SweepState56 asks which
 * one lies along the net's sweep (CatchSphere_FindAlong). The scene empties the list. */
#ifndef CLEAN_MAIN_CATCH_SPHERE_H
#define CLEAN_MAIN_CATCH_SPHERE_H

#include "autoload_2/vector.h"
#include "main/touch_pick_shapes.h"
#include "types.h"

#define CATCH_SPHERE_PICK_KIND 4
#define CATCH_SPHERE_SWEEP_POINTS 6

/* A sphere of the list (0x28 bytes): the pick's sphere, then the list's own fields. */
typedef struct CatchSphere {
    TouchPickSphere sphere;   /* its centre in the drawn world, its index */
    struct CatchSphere *next; /* 0x1c */
    u8 in_reach;              /* 0x20: the last sweep reached it */
    u8 unk_21[3];
    fx32 reach; /* 0x24: added to the sweep's radius */
} CatchSphere;

int CatchSphere_FindAlong(const Vec3 *from, const Vec3 *to, fx32 radius, u8 *index, int unused);
void CatchSphere_Add(CatchSphere *sphere, Vec3 *centre, fx32 reach, fx32 radius, u8 index);
int CatchSphere_Destruct(CatchSphere *sphere);
CatchSphere *CatchSphere_Construct(CatchSphere *sphere);

#endif
