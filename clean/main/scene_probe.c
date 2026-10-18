/* What blocks the way just ahead of a scene object (scene_probe.h). */
#include "scene_probe.h"

#include "clean.h"
#include "collision_map.h"
#include "collision_query.h"
#include "field_collision.h"
#include "ov004/room_objects.h"

/* The object's position and walking angle. */
#define SCENE_PROBE_OBJECT_POSITION 0x5c   /* Vec3 */
#define SCENE_PROBE_OBJECT_WALK_ANGLE 0x94 /* s16 */

#define SCENE_PROBE_POINTS 2

/* The ground under a point (func_02034270 fills it, func_0203423c releases it). */
typedef struct SceneProbeGround {
    u8 unk_00[0x30];
    s32 unk_30; /* nonzero: something stands there */
    u8 unk_34[0x0c];
} SceneProbeGround;

static_assert(sizeof(SceneProbeGround) == 0x40, "SceneProbeGround layout");

/* The two points' offsets, and 1 while the scene is in a room. */
extern Vec3 data_021c16e4[SCENE_PROBE_POINTS];
extern u8 data_020e54a8;

extern fx32 FX_MulFunc(fx32 a, fx32 b);
extern const s16 FX_SinCosTable_[];

/* func_0201ae40: the bits. */
int SceneProbe_Bits(u8 *self)
{
    return *self;
}
CLEAN_AS(func_0201ae40, SceneProbe_Bits)

/* func_0201ae44: the two points ahead of the object (SceneProbe_PointAt) tested
 * (SceneProbe_IsBlocked); each one blocked sets its bit. Bits already set stay. */
void SceneProbe_Update(u8 *self, u8 *object)
{
    for (int i = 0; i < SCENE_PROBE_POINTS; i++) {
        Vec3 point;
        SceneProbe_PointAt(&point, (const Vec3 *) (const void *) (object + SCENE_PROBE_OBJECT_POSITION), &data_021c16e4[i],
                           *(const s16 *) (const void *) (object + SCENE_PROBE_OBJECT_WALK_ANGLE));
        if (SceneProbe_IsBlocked(&point)) {
            *self = (u8) (*self | (1u << i));
        }
    }
}
CLEAN_AS(func_0201ae44, SceneProbe_Update)

/* func_0201ae8c: whether `point` is blocked: in a room, by furniture (func_02030890) or the
 * room's other test (func_ov004_0223c5a4); outdoors, when the ground there has something on it
 * (its word 0x30), rises above the walking level (func_020341c8) or fails func_0203104c. */
int SceneProbe_IsBlocked(Vec3 *point)
{
    if (data_020e54a8 == 1) {
        if (CollisionMap_UnclaimedObjectAtPoint(point) != -1) {
            return 1;
        }
        return RoomObjects_HeightAtPoint(point) != 0;
    }

    SceneProbeGround ground;
    int blocked;
    CollisionGround_Init((CollisionGround *) &ground, point, 0, 0);
    if (ground.unk_30 != 0 || CollisionGround_GetHeight((const CollisionGround *) &ground, 1) > 0 ||
        CollisionQuery_HasPostAtPoint(point) != 0) {
        blocked = 1;
    } else {
        blocked = 0;
    }
    CollisionGround_Destroy((CollisionGround *) &ground);
    return blocked;
}
CLEAN_AS(func_0201ae8c, SceneProbe_IsBlocked)

/* func_0201af0c: no bits (each frame, before SceneProbe_Update). */
void SceneProbe_Clear(u8 *self)
{
    *self = 0;
}
CLEAN_AS(func_0201af0c, SceneProbe_Clear)

/* func_0201af14: the constructor: no bits. */
void SceneProbe_Construct(u8 *self)
{
    *self = 0;
}
CLEAN_AS(func_0201af14, SceneProbe_Construct)

/* func_0201af58: `origin` plus `offset` turned about the vertical by `angle` (its x and z;
 * the result's y is 0). The products are taken in the order x cos, z sin, x sin, z cos, and x
 * is written before the second two are read (`out` may be `offset`). */
void SceneProbe_PointAt(Vec3 *out, const Vec3 *origin, const Vec3 *offset, int angle)
{
    int index = (u16) angle >> 4;
    fx32 sin = FX_SinCosTable_[index * 2];
    fx32 cos = FX_SinCosTable_[index * 2 + 1];

    fx32 x_cos = FX_MulFunc(offset->x, cos);
    fx32 z_sin = FX_MulFunc(offset->z, sin);
    out->x = (fx32) ((u32) origin->x + (u32) x_cos + (u32) z_sin);
    out->y = 0;
    fx32 x_sin = FX_MulFunc(offset->x, sin);
    fx32 z_cos = FX_MulFunc(offset->z, cos);
    out->z = (fx32) ((u32) origin->z - (u32) x_sin + (u32) z_cos);
}
CLEAN_AS(func_0201af58, SceneProbe_PointAt)
