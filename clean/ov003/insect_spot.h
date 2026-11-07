/* Overlay 3's search for a spot an insect of the town settles on (called by overlay 68's
 * InsectPath_FindSpot): the day's spot (InsectSpot_DaySpot), or the nearest code of the flower lines a mask names
 * (InsectSpot_NearFlower). */
#ifndef CLEAN_OV003_INSECT_SPOT_H
#define CLEAN_OV003_INSECT_SPOT_H

#include "autoload_2/vector.h"
#include "types.h"

int InsectSpot_DaySpot(Vec3 *target, const Vec3 *from);
int InsectSpot_NearFlower(Vec3 *target, const Vec3 *from, int lines);

#endif
