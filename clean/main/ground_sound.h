/* The sound of the ground under a point: what footsteps play (footsteps.h, the field actors'
 * GroundSound_AtPoint).
 *
 * The ground's attribute (CollisionGround, field_collision.h) names a row of the collision
 * table (data_020c907c) whose first halfword is the sound, 0xffff for none. Standing on an
 * object of the map (func_02030890), the scene decides instead: scenes 0x1a-0x1f and
 * 0x20-0x29 sound as attribute 5, scenes 1-8 as attribute 6. In mode 1 (data_020e54a8, a
 * mode many scenes test) attribute 0x1a is first replaced by what overlay 4's item there
 * gives. */
#ifndef CLEAN_MAIN_GROUND_SOUND_H
#define CLEAN_MAIN_GROUND_SOUND_H

#include "autoload_2/vector.h"
#include "types.h"

int GroundSound_AtPoint(const Vec3 *point);
int GroundSound_OfAttr(int attr);
int GroundSound_GroundAttr(const Vec3 *point);
int GroundSound_ResolveAttr(int attr);
int GroundSound_Lookup(int attr);

#endif
