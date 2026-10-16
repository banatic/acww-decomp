/* A sphere of the collision code (a centre and a radius, 0x10 bytes), the start of the
 * pickable spheres of touch_pick_shapes.h: its constructor, destructor and setter, and its
 * test against a line (CollisionLine, built by func_0203005c: two ends and the direction). */
#ifndef CLEAN_MAIN_COLLISION_SPHERE_H
#define CLEAN_MAIN_COLLISION_SPHERE_H

#include "autoload_2/vector.h"
#include "types.h"

typedef struct CollisionSphere {
    Vec3 centre;
    fx32 radius; /* 0x0c */
} CollisionSphere;

typedef struct CollisionLine {
    Vec3 start;
    Vec3 end;       /* 0x0c */
    Vec3 direction; /* 0x18: of unit length */
} CollisionLine;

int CollisionSphere_HitLine(CollisionSphere *sphere, Vec3 *out, CollisionLine *line);
void CollisionSphere_Set(CollisionSphere *sphere, const Vec3 *centre, u32 radius);
void CollisionSphere_Destruct(void);
void CollisionSphere_Construct(CollisionSphere *sphere);

#endif
