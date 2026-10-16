/* The point the field camera looks at (camera.h). */
#include "camera.h"

#include <assert.h>
#include <stddef.h>

#include "clean.h"
#include "vector.h"

static_assert(offsetof(Camera, followed) == 0x84, "the followed point");
static_assert(offsetof(Camera, offset) == 0x150, "the first offset");
static_assert(offsetof(Camera, second_offset) == 0x15c, "the second offset");

/* func_01ffcb9c: the followed point plus the first offset. */
void Camera_GetOffsetPoint(Vec3 *out, Camera *camera)
{
    Vec_Add(out, &camera->offset, &camera->followed);
}
CLEAN_AS(func_01ffcb9c, Camera_GetOffsetPoint)

/* func_01ffcbb0: the point the camera looks at: the followed point plus both offsets. */
void Camera_GetTarget(Vec3 *out, Camera *camera)
{
    Vec3 point;
    Camera_GetOffsetPoint(&point, camera);
    Vec_Add(out, &camera->second_offset, &point);
}
CLEAN_AS(func_01ffcbb0, Camera_GetTarget)
