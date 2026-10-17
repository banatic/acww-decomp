/* Overlay 3's search for where a villager walks to in town (called by overlay 68's walks): the
 * day's spot (WalkTarget_DaySpot), or the nearest code of the families' lines a mask names
 * (WalkTarget_NearFamily). */
#ifndef CLEAN_OV003_WALK_TARGET_H
#define CLEAN_OV003_WALK_TARGET_H

#include "autoload_2/vector.h"
#include "types.h"

int WalkTarget_DaySpot(Vec3 *target, const Vec3 *from);
int WalkTarget_NearFamily(Vec3 *target, const Vec3 *from, int lines);

#endif
