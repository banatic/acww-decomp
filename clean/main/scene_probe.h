/* What blocks the way just ahead of a scene object (class 0x020d8c64, obj_020d8c64.h: its byte
 * at 0x3a8): each frame two points ahead of the object (data_021c16e4: 0.9375 on and 0.4375 to
 * either side, x +0x700 then -0x700, turned by its walking angle at 0x94) are tested
 * (SceneProbe_IsBlocked); bit 0 is set when the first is blocked, bit 1 the second.
 * func_0201c194 reads the bits to step aside. */
#ifndef CLEAN_MAIN_SCENE_PROBE_H
#define CLEAN_MAIN_SCENE_PROBE_H

#include "autoload_2/vector.h"
#include "types.h"

int SceneProbe_Bits(u8 *self);
void SceneProbe_Update(u8 *self, u8 *object);
int SceneProbe_IsBlocked(Vec3 *point);
void SceneProbe_Clear(u8 *self);
void SceneProbe_Construct(u8 *self);
void SceneProbe_PointAt(Vec3 *out, const Vec3 *origin, const Vec3 *offset, int angle);

#endif
