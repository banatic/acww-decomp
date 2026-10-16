/* A line of the collision code (CollisionLine of collision_sphere.h: two ends and the unit
 * direction from the start to the end): its constructor, destructor and setter, the point of
 * the infinite line nearest a point, the distance to it, and whether a point is between the
 * ends along the line. */
#ifndef CLEAN_MAIN_COLLISION_LINE_H
#define CLEAN_MAIN_COLLISION_LINE_H

#include "autoload_2/vector.h"
#include "collision_sphere.h"
#include "types.h"

int CollisionLine_Spans(const CollisionLine *line, const Vec3 *point);
void CollisionLine_NearestPoint(const CollisionLine *line, Vec3 *nearest, const Vec3 *point);
fx32 CollisionLine_NearestDistance(const CollisionLine *line, Vec3 *nearest, const Vec3 *point);
void CollisionLine_Set(CollisionLine *line, const Vec3 *start, const Vec3 *end);
fx32 CollisionLine_Distance(const CollisionLine *line, const Vec3 *point);
void CollisionLine_SetDirection(const CollisionLine *line, Vec3 *direction);
void CollisionLine_Destruct(CollisionLine *line);
CollisionLine *CollisionLine_Construct(CollisionLine *line, const Vec3 *start, const Vec3 *end);

#endif
