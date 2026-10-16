/* An upright cylinder of the collision code (0x14 bytes, the start of CollisionPost of
 * field_collision.h and of the touch pick's cylinders): where a path hits its side or its top,
 * landing on its top, pushing a point out of its side, and its setter and destructors.
 *
 * It stands on `base` and goes up by `height`; func_020306a4 says whether a point is within
 * `radius` of the axis (seen from above). */
#ifndef CLEAN_MAIN_COLLISION_CYLINDER_H
#define CLEAN_MAIN_COLLISION_CYLINDER_H

#include "autoload_2/vector.h"
#include "types.h"

typedef struct CollisionCylinder {
    Vec3 base;
    fx32 radius; /* 0x0c */
    fx32 height; /* 0x10 */
} CollisionCylinder;

int CollisionCylinder_HitSide(CollisionCylinder *cylinder, Vec3 *end, const Vec3 *start);
int CollisionCylinder_HitCaps(CollisionCylinder *cylinder, Vec3 *end, const Vec3 *start);
int CollisionCylinder_HitSideBelowTop(CollisionCylinder *cylinder, Vec3 *end, const Vec3 *start);
int CollisionCylinder_HitTop(CollisionCylinder *cylinder, Vec3 *end, const Vec3 *start);
int CollisionCylinder_LandOnTop(CollisionCylinder *cylinder, Vec3 *position, const Vec3 *previous);
int CollisionCylinder_PushOut(CollisionCylinder *cylinder, Vec3 *position, fx32 radius);
void CollisionCylinder_Set(CollisionCylinder *cylinder, const Vec3 *base, fx32 radius, fx32 height);
CollisionCylinder *CollisionCylinder_DestructBase(CollisionCylinder *cylinder);
CollisionCylinder *CollisionCylinder_Destruct(CollisionCylinder *cylinder);

#endif
