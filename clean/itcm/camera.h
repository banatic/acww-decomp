/* The field camera (data_021c67a4): the point it looks at is the point it follows plus two
 * offsets, each eased towards a goal of its own (func_0203be6c). */
#ifndef CLEAN_ITCM_CAMERA_H
#define CLEAN_ITCM_CAMERA_H

#include "autoload_2/vector.h"
#include "types.h"

typedef struct Camera {
    u8 unk_00[0x84];
    Vec3 followed; /* 0x84: the point the camera follows */
    u8 unk_90[0x150 - 0x90];
    Vec3 offset;        /* 0x150: eased towards the goal at 0x104 */
    Vec3 second_offset; /* 0x15c: eased towards the goal at 0x110 */
} Camera;

void Camera_GetOffsetPoint(Vec3 *out, Camera *camera);
void Camera_GetTarget(Vec3 *out, Camera *camera);

#endif
