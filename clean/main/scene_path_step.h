/* Where a scene object (class 0x020d8c64, obj_020d8c64.h) steps next on the field's paths on its
 * way to a target point (overlay 52's objects ask). Each tile of the field has four bits, the
 * directions 1, 2, 4 and 8 in which a path leaves it (AcreTile_PathDirections); the steps to the
 * four tiles around a tile are the table at data_020c81fc: -z, -x, +z and +x, one tile
 * (0x2000) each. */
#ifndef CLEAN_MAIN_SCENE_PATH_STEP_H
#define CLEAN_MAIN_SCENE_PATH_STEP_H

#include "autoload_2/vector.h"
#include "types.h"

#define SCENE_PATH_STEPS 4

void ScenePathStep_Choose(Vec3 *out, u8 *object, const Vec3 *target);

#endif
