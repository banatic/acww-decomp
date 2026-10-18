/* What the pen picks on the field: the pick object, its shapes and its update
 * (touch_pick_shapes.h). */
#include "touch_pick_shapes.h"

#include "autoload_2/matrix.h"
#include "clean.h"
#include "itcm/vector.h"
#include "main/actor_table.h"
#include "main/camera_control.h"
#include "main/camera_view.h"
#include "main/touch_pick.h"
#include "collision_cylinder.h"
#include "collision_line.h"
#include "collision_query.h"
#include "collision_sphere.h"
#include "collision_triangle.h"
#include "globe.h"
#include "ov003/object_actors.h"

static_assert(sizeof(TouchPickFace) == 0x44, "TouchPickFace");
static_assert(sizeof(TouchPickSphere) == 0x1c, "TouchPickSphere");
static_assert(sizeof(TouchPickCylinder) == 0x20, "TouchPickCylinder");
static_assert(offsetof(TouchPick, faces) == 0x1c, "TouchPick");

/* The modes of data_020e54a8: 0 outdoors. */
#define TOUCH_PICK_MODE_OUTDOORS 0

/* The kind of post (func_02031078) that is one of overlay 3's outdoor objects. */
#define TOUCH_PICK_POST_OUTDOOR_OBJECT 10

/* The screen is 256 by 192 pixels; the pen's pixel is taken from its middle. */
#define TOUCH_PICK_SCREEN_HALF_WIDTH 0x80000
#define TOUCH_PICK_SCREEN_HALF_HEIGHT 0x60000

/* A unit's middle from its number, and the unit of a coordinate. */
#define TOUCH_PICK_UNIT 0x2000

typedef struct TouchPickScene {
    u8 unk_00[4];
    u8 bent; /* 4: 1 where the world is drawn round the globe */
} TouchPickScene;

/* A node of the field's bodies (data_021d3120): objects that push each other apart
 * (func_02089ce0). Its vtable's first entry gives its position. */
typedef struct BodyNode {
    const u32 *vtable;
    fx32 radius; /* 0x04 */
    fx32 height; /* 0x08 */
    u8 kind;     /* 0x0c */
    u8 index;    /* 0x0d */
    u8 unk_0e[0x2a];
    struct BodyNode *next; /* 0x38 */
} BodyNode;
static_assert(offsetof(BodyNode, next) == 0x38, "BodyNode");

typedef Vec3 *(*BodyPositionMethod)(BodyNode *body);

/* A cylinder of the collision code (func_02030678, 0x14 bytes). */
typedef struct TouchPickTestCylinder {
    Vec3 base;
    fx32 radius;
    fx32 height;
} TouchPickTestCylinder;

/* A segment of the collision code (func_0203005c, 0x24 bytes): its ends and direction. */
typedef struct TouchPickTestSegment {
    Vec3 start;
    Vec3 end;
    Vec3 direction;
} TouchPickTestSegment;

extern u8 data_020e54a8;
extern u8 data_021f6c38; /* with data_021f6c34: the pen came down this frame */
extern u8 data_021f6c34;
extern int data_021c8c9c;                   /* 1 when the 3D screen is the top one */
extern TouchPickScene *data_021f6948;       /* the running scene's setup */
extern CameraControl *data_021c67a4;        /* the field camera, or NULL */
extern Vec3 data_021c67d0;                  /* the point the camera looks at */
extern const Mtx43 data_0213fee4;           /* the view matrix */
extern Mtx43 data_021fbe48;                 /* a copy of the camera's view matrix */
extern BodyNode *data_021d3120;             /* the field's bodies */
extern const fx32 data_020ca0e8;            /* an acre's depth; the pen ray's length */
extern const fx32 data_020ca0ec;            /* an acre's width */
extern const s32 data_020c904c;             /* a height over the ground (player_messages.c) */
extern const u8 data_020d2254[23];          /* per kind: whether it can be picked */
extern const unsigned char data_020e5810[]; /* TouchPickFace's vtable */
/* Two values the update works out once (guarded by bit 0 of the words before them). */
extern u32 data_021f6ad0;
extern fx32 data_021f6ad4; /* the globe's length: six acres */
extern u32 data_021f6ac8;
extern fx32 data_021f6ad8; /* the globe's radius raised by data_020c904c */

extern const fx16 FX_SinCosTable_[];
extern fx32 FX_Div(fx32 numerator, fx32 denominator);
extern fx32 FX_MulFunc(fx32 a, fx32 b);
extern int MTX_Inverse43(const Mtx43 *mtx, Mtx43 *inverse);
extern void MTX_MultVec43(const Vec3 *vector, const Mtx43 *mtx, Vec3 *out);
extern void __cxa_vec_ctor(void *array, int count, int size, void (*construct)(void *), void (*destruct)(void *));
extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));

/* The game's symbols for the box's constructor and destructor, for __cxa_vec_*. */
extern void func_020b8038(void *face);
extern void func_020b8020(void *face);

static int sine_of(int angle)
{
    return FX_SinCosTable_[((u16) angle >> 4) * 2];
}

static int cosine_of(int angle)
{
    return FX_SinCosTable_[((u16) angle >> 4) * 2 + 1];
}

/* (u, v) turned by the angle of sine `s` and cosine `c`. */
static void turn_pair(fx32 *u, fx32 *v, int s, int c)
{
    fx32 old_u = *u;
    fx32 old_v = *v;
    fx32 cu = FX_MulFunc(c, old_u);
    *u = cu - FX_MulFunc(s, old_v);
    fx32 su = FX_MulFunc(s, old_u);
    *v = su + FX_MulFunc(c, old_v);
}

/* The middle of unit `unit` along an axis. */
static fx32 unit_middle(int unit)
{
    return unit * TOUCH_PICK_UNIT + TOUCH_PICK_UNIT / 2;
}

static int is_bent_world(void)
{
    return data_021f6948->bent == 1;
}

/* Whether the triangle separates `start` (on its front) from `end` (behind it). */
static int crosses_from_front(CollisionTriangle *triangle, Vec3 *start, Vec3 *end)
{
    return CollisionTriangle_Distance(triangle, start) >= 0 && CollisionTriangle_Distance(triangle, end) < 0;
}

/* func_020b74ec: the object of a kind that has none. */
int TouchPick_NoObject(void)
{
    return 0;
}
CLEAN_AS(func_020b74ec, TouchPick_NoObject)

/* func_020b74f0: the picked object (TouchPick_PickedObject), only on the frame the pen came
 * down (data_021f6c38 and data_021f6c34 both set); else 0. */
int TouchPick_ObjectOnPenDown(TouchPick *pick, int *kind, u8 *index)
{
    if (data_021f6c38 != 0 && data_021f6c34 != 0) {
        return TouchPick_PickedObject(pick, kind, index);
    }
    return 0;
}
CLEAN_AS(func_020b74f0, TouchPick_ObjectOnPenDown)

/* func_020b7524: the object the pen picked (TouchPick_Object of the kind and index), or 0 when
 * the kind cannot be picked; the kind and index also go to `kind` and `index` when given. */
int TouchPick_PickedObject(TouchPick *pick, int *kind, u8 *index)
{
    Vec3 point;
    int own_kind;
    u8 own_index;

    if (kind == NULL) {
        kind = &own_kind;
    }
    if (index == NULL) {
        index = &own_index;
    }
    if (TouchPick_GetPick(pick, &point, (u32 *) kind, index)) {
        return TouchPick_Object(*kind, *index);
    }
    return 0;
}
CLEAN_AS(func_020b7524, TouchPick_PickedObject)

/* func_020b755c: the picked point, kind and index (each when asked for); whether the kind can be
 * picked. */
u8 TouchPick_GetPick(TouchPick *pick, Vec3 *point, u32 *kind, u8 *index)
{
    if (point != NULL) {
        point->x = pick->point.x;
        point->y = pick->point.y;
        point->z = pick->point.z;
    }
    if (kind != NULL) {
        *kind = pick->kind;
    }
    if (index != NULL) {
        *index = pick->index;
    }
    return TouchPick_KindPickable(pick->kind);
}
CLEAN_AS(func_020b755c, TouchPick_GetPick)

/* func_020b758c: the ground point (to `ground` when given); whether the ray met the ground. */
int TouchPick_GetGround(TouchPick *pick, Vec3 *ground)
{
    if (ground != NULL) {
        /* Word by word, as the ROM does (it matters only if `ground` overlapped the pick). */
        ground->x = pick->ground.x;
        ground->y = pick->ground.y;
        ground->z = pick->ground.z;
    }
    return pick->ground.x != TOUCH_PICK_NO_POINT;
}
CLEAN_AS(func_020b758c, TouchPick_GetGround)

/* func_020b75b0: the destructor of the pick's empty base. */
void TouchPick_DestructBase(void) {}
CLEAN_AS(func_020b75b0, TouchPick_DestructBase)

/* func_020b75b4: the constructor of the pick's empty base. */
void TouchPick_ConstructBase(void) {}
CLEAN_AS(func_020b75b4, TouchPick_ConstructBase)

/* The ground on the globe, outdoors (part of TouchPick_Update): the segment from `from` to `to`
 * against the globe raised by data_020c904c, where the ground there has unk_30 set (byte 0x14 of
 * its attribute's row); then against the globe itself; then against the far wall, a square
 * standing at the camera's acre four acres' depth along the ray. Each hit shortens the segment
 * to it and sets the ground point. */
static void touch_pick_ground_bent(TouchPick *pick, Vec3 *from, Vec3 *to, const Vec3 *direction)
{
    Vec3 hit;
    fx32 length;

    if ((data_021f6ad0 & 1) == 0) {
        data_021f6ad4 = 6 * data_020ca0ec;
        data_021f6ad0 |= 1;
    }
    if ((data_021f6ac8 & 1) == 0) {
        data_021f6ad8 = data_020c904c + Globe_Radius();
        data_021f6ac8 |= 1;
    }
    length = data_021f6ad4;

    if (TouchPick_SegmentHitsGlobe(&hit, from, to, data_021f6ad8, length)) {
        Vec3 map;
        CollisionGround ground;
        Globe_Unbend(&map, &hit);
        CollisionGround_Init(&ground, &map, 0, 0);
        if (ground.unk_30 != 0) {
            *to = hit;
            map.y = data_020c904c;
            pick->ground = map;
        }
        CollisionGround_Destroy(&ground);
    }

    if (!TouchPick_GetGround(pick, NULL)) {
        if (TouchPick_SegmentHitsGlobe(&hit, from, to, Globe_Radius(), length)) {
            Vec3 map;
            *to = hit;
            Globe_Unbend(&map, &hit);
            map.y = 0;
            pick->ground = map;
        }
    }

    if (!TouchPick_GetGround(pick, NULL)) {
        CameraControl *camera = data_021c67a4;
        if (camera != NULL) {
            Vec3 target = data_021c67d0;
            Vec3 reach_vector = *direction;
            fx32 depth = data_020ca0e8;
            Vec3 tip;
            Vec3 corner[4];
            Vec3 drawn[4];
            Vec3 normal;
            Mtx43 mtx;
            CollisionTriangle wall[2];

            Vec_Scale(&reach_vector, depth * 4);
            Vec_Add(&tip, from, &reach_vector);

            fx32 half = data_020ca0ec;
            fx32 left = target.x - half;
            fx32 right = target.x + half;
            corner[0] = (Vec3){left, depth, 0};
            corner[1] = (Vec3){left, -0x2000, 0};
            corner[2] = (Vec3){right, -0x2000, 0};
            corner[3] = (Vec3){right, depth, 0};

            Mtx43_RotX(&mtx, CameraControl_GroundAngle(camera));
            Mtx43_Translate(&mtx, 0, Globe_Radius(), 0);
            Mtx43_RotateX(&mtx, -0x1000);
            Mtx43_RotateX(&mtx, 0);
            for (int i = 0; i < 4; i++) {
                MTX_MultVec43(&corner[i], &mtx, &drawn[i]);
            }

            CollisionTriangle_CornerNormal(&normal, &drawn[0], &drawn[1], &drawn[2]);
            CollisionTriangle_ConstructSet(&wall[0], &drawn[0], &drawn[1], &drawn[2], &normal);
            CollisionTriangle_ConstructSet(&wall[1], &drawn[0], &drawn[2], &drawn[3], &normal);
            for (int i = 0; i < 2; i++) {
                Vec3 crossing;
                if (crosses_from_front(&wall[i], from, &tip) &&
                    CollisionTriangle_SegmentHit(&wall[i], &crossing, from, &tip)) {
                    Vec3 map;
                    *to = crossing;
                    Globe_Unbend(&map, &crossing);
                    pick->ground = map;
                    pick->ground.y = 0;
                }
            }
            CollisionTriangle_Destruct(&wall[1]);
            CollisionTriangle_Destruct(&wall[0]);
        }
    }
}

/* The ground on a flat map (part of TouchPick_Update): the top of each unit under the segment
 * whose ground is above 0 and below 4.0 (two triangles at its height); failing those, the plane
 * y = 0 when the segment goes down through it. Each hit shortens the segment. */
static void touch_pick_ground_flat(TouchPick *pick, Vec3 *from, Vec3 *to)
{
    int from_x = from->x >> COLLISION_UNIT_SHIFT;
    int from_z = from->z >> COLLISION_UNIT_SHIFT;
    int to_x = to->x >> COLLISION_UNIT_SHIFT;
    int to_z = to->z >> COLLISION_UNIT_SHIFT;
    int x_low = from_x <= to_x ? from_x : to_x;
    int x_high = from_x <= to_x ? to_x : from_x;
    int z_low = from_z <= to_z ? from_z : to_z;
    int z_high = from_z <= to_z ? to_z : from_z;
    int found = 0;

    for (int x = x_low; x <= x_high; x++) {
        fx32 middle_x = unit_middle(x);
        for (int z = z_low; z <= z_high; z++) {
            CollisionGround ground;
            CollisionGround_InitAtUnit(&ground, x, z, 0, 0);
            fx32 height = CollisionGround_GetHeight(&ground, 0);
            if (height < 0x4000 && height != 0) {
                fx32 middle_z = unit_middle(z);
                fx32 low_x = middle_x - COLLISION_HALF_UNIT;
                fx32 high_x = middle_x + COLLISION_HALF_UNIT;
                fx32 low_z = middle_z - COLLISION_HALF_UNIT;
                fx32 high_z = middle_z + COLLISION_HALF_UNIT;
                Vec3 corner[4] = {
                    {low_x, height, low_z},
                    {low_x, height, high_z},
                    {high_x, height, high_z},
                    {high_x, height, low_z},
                };
                Vec3 up = {0, 0x1000, 0};
                CollisionTriangle top[2];

                CollisionTriangle_Construct(&top[0]);
                CollisionTriangle_Construct(&top[1]);
                CollisionTriangle_Set(&top[0], &corner[0], &corner[1], &corner[3], &up);
                CollisionTriangle_Set(&top[1], &corner[1], &corner[2], &corner[3], &up);
                for (int i = 0; i < 2; i++) {
                    Vec3 crossing;
                    if (crosses_from_front(&top[i], from, to) && CollisionTriangle_SegmentHit(&top[i], &crossing, from, to)) {
                        *to = crossing;
                        pick->ground = *to;
                        found = 1;
                    }
                }
                CollisionTriangle_Destruct(&top[1]);
                CollisionTriangle_Destruct(&top[0]);
            }
            CollisionGround_Destroy(&ground);
        }
    }

    if (!found && from->y > 0 && to->y <= 0) {
        Vec3 step;
        Vec3 hit;
        CollisionGround ground;

        Vec_Subtract(&step, to, from);
        fx32 above = from->y < 0 ? -from->y : from->y;
        fx32 drop = from->y - to->y;
        if (drop < 0) {
            drop = -drop;
        }
        fx32 t = FX_Div(above, drop);
        hit.x = from->x + FX_MulFunc(step.x, t);
        hit.y = from->y + FX_MulFunc(step.y, t);
        hit.z = from->z + FX_MulFunc(step.z, t);
        *to = hit;
        /* QUIRK: the ground there is looked up and dropped unread. */
        CollisionGround_Init(&ground, &hit, 0, 0);
        pick->ground = hit;
        CollisionGround_Destroy(&ground);
    }
}

/* The map's posts on the units under the segment, the last units first (part of
 * TouchPick_Update): a post of kind 10 outdoors is overlay 3's outdoor object on its tile
 * (kind 6, with its slot), any other a plain post (kind 5, index 0). */
static void touch_pick_posts(TouchPick *pick, Vec3 *from, Vec3 *to)
{
    Vec3 a;
    Vec3 b;

    Globe_Unbend(&a, from);
    Globe_Unbend(&b, to);
    int x_low = a.x < b.x ? a.x : b.x;
    int x_high = a.x < b.x ? b.x : a.x;
    int z_low = a.z < b.z ? a.z : b.z;
    int z_high = a.z < b.z ? b.z : a.z;
    x_low >>= COLLISION_UNIT_SHIFT;
    z_low >>= COLLISION_UNIT_SHIFT;
    x_high >>= COLLISION_UNIT_SHIFT;
    z_high >>= COLLISION_UNIT_SHIFT;

    for (int z = z_high; z >= z_low; z--) {
        fx32 middle_z = unit_middle(z);
        for (int x = x_high; x >= x_low; x--) {
            int radius;
            int height;
            int kind = 0;
            if (!CollisionQuery_PostAt(x, z, (fx32 *) &radius, (fx32 *) &height, &kind) || kind == 0) {
                continue;
            }
            Vec3 middle = {unit_middle(x), 0, middle_z};
            if (TouchPick_SegmentHitsCylinder(to, from, &middle, radius, height)) {
                pick->point = middle;
                pick->index = 0;
                if (data_020e54a8 == TOUCH_PICK_MODE_OUTDOORS && kind == TOUCH_PICK_POST_OUTDOOR_OBJECT) {
                    int tile_x;
                    int tile_z;
                    pick->kind = TOUCH_PICK_KIND_OUTDOOR_ENTRY;
                    Position_Tile(&tile_x, &tile_z, (const Position *) &pick->point);
                    pick->index = (u8) ObjectActors_IndexOf((SceneActor *) (uintptr_t) ((
                        int) (uintptr_t) ObjectActors_FindAtTile((unsigned int) tile_x, (unsigned int) tile_z)));
                } else {
                    pick->kind = TOUCH_PICK_KIND_POST;
                }
            }
        }
    }
}

/* func_020b75b8: the frame's pick. Clears the pick (keeping `pen_down`); with the pen down and
 * the 3D screen at the bottom, casts the ray from the pen's pixel (`pen_x`, `pen_y`), finds the
 * ground, then tests, each on the segment as shortened by the hits before so that the nearest
 * wins: the cylinders, the bodies whose kind can be picked, the map's posts, the faces and the
 * spheres (the spheres on the segment as it is then, without shortening it). Empties the three
 * lists either way. */
void TouchPick_Update(TouchPick *pick, u8 pen_x, u8 pen_y, int pen_down)
{
    TouchPickRay ray;
    Vec3 from;
    Vec3 to;

    TouchPick_Reset(pick, (u8) pen_down);
    if (pen_down == 0 || data_021c8c9c == 1) {
        pick->spheres = NULL;
        pick->cylinders = NULL;
        pick->faces = NULL;
        return;
    }

    TouchPick_PenRay(&ray, pen_x, pen_y);
    from = ray.origin;
    to = ray.end;

    if (is_bent_world()) {
        touch_pick_ground_bent(pick, &from, &to, &ray.direction);
    } else {
        touch_pick_ground_flat(pick, &from, &to);
    }

    for (TouchPickCylinder *cylinder = pick->cylinders; cylinder != NULL; cylinder = cylinder->next) {
        if (TouchPick_SegmentHitsCylinder(&to, &from, &cylinder->base, cylinder->radius, cylinder->height)) {
            pick->point = cylinder->base;
            pick->kind = (u8) cylinder->kind;
            pick->index = cylinder->index;
        }
    }

    for (BodyNode *body = data_021d3120; body != NULL; body = body->next) {
        if (TouchPick_KindPickable(body->kind)) {
            BodyPositionMethod position_of = (BodyPositionMethod) (uintptr_t) body->vtable[0];
            if (TouchPick_SegmentHitsCylinder(&to, &from, position_of(body), body->radius, body->height)) {
                pick->point = *position_of(body);
                pick->kind = body->kind;
                pick->index = body->index;
            }
        }
    }

    touch_pick_posts(pick, &from, &to);

    for (TouchPickFace *face = pick->faces; face != NULL; face = face->next) {
        Vec3 crossing;
        if (crosses_from_front(&face->triangle, &from, &to) &&
            CollisionTriangle_SegmentHit(&face->triangle, &crossing, &from, &to)) {
            Vec3 map;
            to = crossing;
            Globe_Unbend(&map, &to);
            pick->point = map;
            pick->kind = (u8) face->kind;
            pick->index = face->index;
        }
    }

    for (TouchPickSphere *sphere = pick->spheres; sphere != NULL;) {
        TouchPickTestSegment segment;
        Vec3 out;
        CollisionLine_Construct((CollisionLine *) &segment, &from, &to);
        if (CollisionSphere_HitLine((CollisionSphere *) sphere, &out, (CollisionLine *) &segment)) {
            Vec3 map;
            Globe_Unbend(&map, &sphere->centre);
            pick->point = map;
            pick->kind = (u8) sphere->kind;
            pick->index = sphere->index;
        }
        sphere = sphere->next;
        CollisionLine_Destruct((CollisionLine *) &segment);
    }

    pick->spheres = NULL;
    pick->cylinders = NULL;
    pick->faces = NULL;
}
CLEAN_AS(func_020b75b8, TouchPick_Update)

/* func_020b7cf4: sets `face` from three map points (TouchPickFace_SetAtMapPoints) and adds it;
 * always 1. */
int TouchPick_SetFaceAndAdd(TouchPick *pick, TouchPickFace *face, Vec3 *a, Vec3 *b, Vec3 *c, int kind, u8 index)
{
    TouchPickFace_SetAtMapPoints(face, a, b, c, kind, index);
    return TouchPick_AddFace(pick, face);
}
CLEAN_AS(func_020b7cf4, TouchPick_SetFaceAndAdd)

/* func_020b7d24: puts `face` at the head of the faces; 1. */
int TouchPick_AddFace(TouchPick *pick, TouchPickFace *face)
{
    face->next = pick->faces;
    pick->faces = face;
    return 1;
}
CLEAN_AS(func_020b7d24, TouchPick_AddFace)

/* func_020b7d3c: sets `cylinder` and adds it; 1. */
int TouchPick_SetCylinderAndAdd(TouchPick *pick, TouchPickCylinder *cylinder, Vec3 *base, fx32 radius, fx32 height, int kind,
                                u8 index)
{
    TouchPickCylinder_Set(cylinder, base, radius, height, kind, index);
    return TouchPick_AddCylinder(pick, cylinder);
}
CLEAN_AS(func_020b7d3c, TouchPick_SetCylinderAndAdd)

/* func_020b7d6c: puts `cylinder` at the head of the cylinders; 1. */
int TouchPick_AddCylinder(TouchPick *pick, TouchPickCylinder *cylinder)
{
    cylinder->next = pick->cylinders;
    pick->cylinders = cylinder;
    return 1;
}
CLEAN_AS(func_020b7d6c, TouchPick_AddCylinder)

/* func_020b7d84: sets `sphere` round a map point and adds it. */
void TouchPick_SetSphereAndAdd(TouchPick *pick, TouchPickSphere *sphere, Vec3 *centre, fx32 radius, int kind, u8 index)
{
    TouchPickSphere_SetAtMapPoint(sphere, centre, (u32) radius, (u32) kind, index);
    TouchPick_AddSphere(pick, sphere);
}
CLEAN_AS(func_020b7d84, TouchPick_SetSphereAndAdd)

/* func_020b7db0: puts `sphere` at the head of the spheres; 1. */
int TouchPick_AddSphere(TouchPick *pick, TouchPickSphere *sphere)
{
    sphere->next = pick->spheres;
    pick->spheres = sphere;
    return 1;
}
CLEAN_AS(func_020b7db0, TouchPick_AddSphere)

/* func_020b7dc8: sets the ten faces of a box (TouchPickFaces_SetBox) and adds them; 1. */
int TouchPick_SetBoxAndAdd(TouchPick *pick, TouchPickFace *faces, Vec3 *centre, fx32 width, fx32 depth, fx32 height, s16 angle,
                           int kind, u8 index)
{
    TouchPickFaces_SetBox(faces, centre, width, depth, height, angle, kind, index);
    return TouchPick_AddFaces(pick, faces);
}
CLEAN_AS(func_020b7dc8, TouchPick_SetBoxAndAdd)

/* func_020b7e04: adds the ten faces of a box; 1. */
int TouchPick_AddFaces(TouchPick *pick, TouchPickFace *faces)
{
    for (int i = 0; i < TOUCH_PICK_BOX_FACES; i++) {
        TouchPick_AddFace(pick, &faces[i]);
    }
    return 1;
}
CLEAN_AS(func_020b7e04, TouchPick_AddFaces)

/* func_020b7e3c: the pick's constructor: cleared, pen up, no shapes. */
TouchPick *TouchPick_Construct(TouchPick *pick)
{
    TouchPick_ConstructBase();
    TouchPick_Reset(pick, 0);
    pick->faces = NULL;
    pick->spheres = NULL;
    pick->cylinders = NULL;
    return pick;
}
CLEAN_AS(func_020b7e3c, TouchPick_Construct)

/* func_020b7e5c: the pick's destructor. */
TouchPick *TouchPick_Destruct(TouchPick *pick)
{
    TouchPick_DestructBase();
    return pick;
}
CLEAN_AS(func_020b7e5c, TouchPick_Destruct)

/* func_020b7e6c (when a scene ends, func_020b6ae0): cleared, pen up, no shapes. */
void TouchPick_ResetOnSceneEnd(TouchPick *pick)
{
    TouchPick_Reset(pick, 0);
    pick->faces = NULL;
    pick->spheres = NULL;
    pick->cylinders = NULL;
}
CLEAN_AS(func_020b7e6c, TouchPick_ResetOnSceneEnd)

/* func_020b7e84 (when a scene starts, func_020b6fd0): the same. */
void TouchPick_ResetOnSceneStart(TouchPick *pick)
{
    TouchPick_Reset(pick, 0);
    pick->faces = NULL;
    pick->spheres = NULL;
    pick->cylinders = NULL;
}
CLEAN_AS(func_020b7e84, TouchPick_ResetOnSceneStart)

/* func_020b7e9c: no ground, nothing picked, and whether the pen is down. */
void TouchPick_Reset(TouchPick *pick, u8 pen_down)
{
    pick->ground = (Vec3){TOUCH_PICK_NO_POINT, 0, 0};
    pick->kind = 0;
    pick->index = 0;
    pick->point = (Vec3){0, 0, 0};
    pick->pen_down = pen_down;
}
CLEAN_AS(func_020b7e9c, TouchPick_Reset)

/* func_020b7ebc: sets a cylinder on a map point; 1. */
int TouchPickCylinder_Set(TouchPickCylinder *cylinder, Vec3 *base, fx32 radius, fx32 height, int kind, u8 index)
{
    cylinder->kind = kind;
    cylinder->index = index;
    CollisionCylinder_Set((CollisionCylinder *) cylinder, base, radius, height);
    return 1;
}
CLEAN_AS(func_020b7ebc, TouchPickCylinder_Set)

/* func_020b7ed8 */
TouchPickCylinder *TouchPickCylinder_Destruct(TouchPickCylinder *cylinder)
{
    CollisionCylinder_DestructBase((CollisionCylinder *) cylinder);
    return cylinder;
}
CLEAN_AS(func_020b7ed8, TouchPickCylinder_Destruct)

/* func_020b7ee8: a cylinder of kind 0, index 0xff, in no list. */
TouchPickCylinder *TouchPickCylinder_Construct(TouchPickCylinder *cylinder)
{
    CollisionCylinder_Construct((CollisionCylinder *) cylinder);
    cylinder->kind = 0;
    cylinder->next = NULL;
    cylinder->index = 0xff;
    return cylinder;
}
CLEAN_AS(func_020b7ee8, TouchPickCylinder_Construct)

/* func_020b7f04: sets a sphere round a point of the drawn world; 1. */
int TouchPickSphere_Set(TouchPickSphere *sphere, Vec3 *centre, fx32 radius, int kind, u8 index)
{
    sphere->kind = kind;
    sphere->index = index;
    CollisionSphere_Set((CollisionSphere *) sphere, centre, radius);
    return 1;
}
CLEAN_AS(func_020b7f04, TouchPickSphere_Set)

/* func_020b7f24: sets a sphere round a map point. */
void TouchPickSphere_SetAtMapPoint(TouchPickSphere *sphere, Vec3 *centre, u32 radius, u32 kind, u8 index)
{
    Vec3 drawn;
    Globe_Bend(&drawn, centre);
    TouchPickSphere_Set(sphere, &drawn, (fx32) radius, (int) kind, index);
}
CLEAN_AS(func_020b7f24, TouchPickSphere_SetAtMapPoint)

/* func_020b7f50 */
TouchPickSphere *TouchPickSphere_Destruct(TouchPickSphere *sphere)
{
    CollisionSphere_Destruct();
    return sphere;
}
CLEAN_AS(func_020b7f50, TouchPickSphere_Destruct)

/* func_020b7f60: the same as func_020b7f50. */
TouchPickSphere *TouchPickSphere_Destruct2(TouchPickSphere *sphere)
{
    CollisionSphere_Destruct();
    return sphere;
}
CLEAN_AS(func_020b7f60, TouchPickSphere_Destruct2)

/* func_020b7f70: a sphere of kind 0, index 0, in no list. */
TouchPickSphere *TouchPickSphere_Construct(TouchPickSphere *sphere)
{
    CollisionSphere_Construct((CollisionSphere *) sphere);
    sphere->kind = 0;
    sphere->index = 0;
    sphere->next = NULL;
    return sphere;
}
CLEAN_AS(func_020b7f70, TouchPickSphere_Construct)

/* func_020b7f88: the same as func_020b7f70. */
TouchPickSphere *TouchPickSphere_Construct2(TouchPickSphere *sphere)
{
    CollisionSphere_Construct((CollisionSphere *) sphere);
    sphere->kind = 0;
    sphere->index = 0;
    sphere->next = NULL;
    return sphere;
}
CLEAN_AS(func_020b7f88, TouchPickSphere_Construct2)

/* func_020b7fa0: sets a face from three corners of the drawn world; 0 (and the face untouched)
 * when they make no normal. */
int TouchPickFace_Set(TouchPickFace *face, Vec3 *a, Vec3 *b, Vec3 *c, int kind, u8 index)
{
    Vec3 normal;
    if (CollisionTriangle_CornerNormal(&normal, a, b, c)) {
        face->kind = kind;
        face->index = index;
        return CollisionTriangle_Set(&face->triangle, a, b, c, &normal);
    }
    return 0;
}
CLEAN_AS(func_020b7fa0, TouchPickFace_Set)

/* func_020b7fe0: sets a face from three map points. */
int TouchPickFace_SetAtMapPoints(TouchPickFace *face, Vec3 *a, Vec3 *b, Vec3 *c, int kind, u8 index)
{
    Vec3 drawn_a;
    Vec3 drawn_b;
    Vec3 drawn_c;
    Globe_Bend(&drawn_a, a);
    Globe_Bend(&drawn_b, b);
    Globe_Bend(&drawn_c, c);
    return TouchPickFace_Set(face, &drawn_a, &drawn_b, &drawn_c, kind, index);
}
CLEAN_AS(func_020b7fe0, TouchPickFace_SetAtMapPoints)

/* func_020b8020: the face's destructor. */
TouchPickFace *TouchPickFace_Destruct(TouchPickFace *face)
{
    face->triangle.vtable = data_020e5810;
    CollisionTriangle_DestructBase(&face->triangle);
    return face;
}
CLEAN_AS(func_020b8020, TouchPickFace_Destruct)

/* func_020b8038: a face of kind 0, index 0xff, in no list. */
TouchPickFace *TouchPickFace_Construct(TouchPickFace *face)
{
    CollisionTriangle_ConstructBase(&face->triangle);
    face->triangle.vtable = data_020e5810;
    face->kind = 0;
    face->next = NULL;
    face->index = 0xff;
    return face;
}
CLEAN_AS(func_020b8038, TouchPickFace_Construct)

/* func_020b8060: the ten faces of a box `width` by `depth` (on X and Z before turning by
 * `angle` about Y) and `height` tall, standing on the map point `centre`: two for the top and
 * two for each side, facing out. QUIRK: always true, whether the faces could be set or not. */
u8 TouchPickFaces_SetBox(TouchPickFace *faces, Vec3 *centre, fx32 width, fx32 depth, fx32 height, int angle, int kind,
                         int index)
{
    /* 0-3 the bottom corners, 4-7 the top ones above them. */
    Vec3 v[8];
    fx32 half_width = width >> 1;
    fx32 half_depth = depth >> 1;
    static const signed char corner_x[4] = {-1, -1, 1, 1};
    static const signed char corner_z[4] = {-1, 1, 1, -1};

    for (int i = 0; i < 4; i++) {
        v[i].x = corner_x[i] < 0 ? -half_width : half_width;
        v[i].y = 0;
        v[i].z = corner_z[i] < 0 ? -half_depth : half_depth;
        v[i + 4] = v[i];
    }
    if (angle != 0) {
        for (int i = 0; i < 4; i++) {
            Vec_RotateY(&v[i], angle);
        }
        for (int i = 0; i < 4; i++) {
            v[i + 4] = v[i];
        }
    }
    for (int i = 0; i < 8; i++) {
        v[i].x += centre->x;
        v[i].z += centre->z;
        v[i].y = i < 4 ? centre->y : centre->y + height;
    }

    static const u8 triangles[TOUCH_PICK_BOX_FACES][3] = {
        {4, 5, 6}, {4, 6, 7}, {5, 1, 2}, {5, 2, 6}, {6, 2, 3}, {6, 3, 7}, {4, 0, 1}, {4, 1, 5}, {7, 3, 0}, {7, 0, 4},
    };
    for (int i = 0; i < TOUCH_PICK_BOX_FACES; i++) {
        TouchPickFace_SetAtMapPoints(&faces[i], &v[triangles[i][0]], &v[triangles[i][1]], &v[triangles[i][2]], kind,
                                     (u8) index);
    }
    return 1;
}
CLEAN_AS(func_020b8060, TouchPickFaces_SetBox)

/* func_020b82d0: destructs the ten faces of a box. */
TouchPickFace *TouchPickFaces_DestructBox(TouchPickFace *faces)
{
    __cxa_vec_cleanup(faces, TOUCH_PICK_BOX_FACES, sizeof(TouchPickFace), func_020b8020);
    return faces;
}
CLEAN_AS(func_020b82d0, TouchPickFaces_DestructBox)

/* func_020b82ec: constructs the ten faces of a box. */
TouchPickFace *TouchPickFaces_ConstructBox(TouchPickFace *faces)
{
    __cxa_vec_ctor(faces, TOUCH_PICK_BOX_FACES, sizeof(TouchPickFace), func_020b8038, func_020b8020);
    return faces;
}
CLEAN_AS(func_020b82ec, TouchPickFaces_ConstructBox)

/* func_020b8314: the ray through the pen's pixel: from the camera to the point the length of an
 * acre's depth away through the pixel on the near plane, in the drawn world. */
void TouchPick_PenRay(TouchPickRay *ray, int pen_x, int pen_y)
{
    Vec3 eye = {0, 0, 0};
    Vec3 through;
    Vec3 far_point;
    Vec3 world_eye;
    Vec3 world_far;
    Vec3 direction;
    Mtx43 inverse;

    fx32 near = -FX_Div(0x60000, (fx32) CameraControl_Projection(data_021c67a4));
    through.x = pen_x * 0x1000 - TOUCH_PICK_SCREEN_HALF_WIDTH;
    through.y = -(pen_y * 0x1000 - TOUCH_PICK_SCREEN_HALF_HEIGHT);
    through.z = near;
    Vec_NormalizeNonZero(&through);
    Vec_Scale(&through, data_020ca0e8);
    Vec_Add(&far_point, &eye, &through);

    inverse = data_0213fee4;
    MTX_Inverse43(&inverse, &inverse);
    MTX_MultVec43(&eye, &inverse, &world_eye);
    MTX_MultVec43(&far_point, &inverse, &world_far);
    ray->origin = world_eye;
    ray->end = world_far;
    Vec_Subtract(&direction, &ray->end, &ray->origin);
    ray->direction = direction;
    Vec_NormalizeNonZero(&ray->direction);
}
CLEAN_AS(func_020b8314, TouchPick_PenRay)

/* func_020b83ec: whether the segment from `start` to `end` (drawn points) meets the upright
 * cylinder on the map point `base`; when it does, `end` becomes the hit. The test is made with
 * everything turned about X so that the cylinder stands upright where it is drawn. */
int TouchPick_SegmentHitsCylinder(Vec3 *end, Vec3 *start, Vec3 *base, fx32 radius, fx32 height)
{
    Vec3 drawn_base;
    TouchPickTestCylinder cylinder;

    int angle = Globe_BendFar(&drawn_base, base);
    Vec3 a = *start;
    Vec3 b = *end;
    Vec3 c = drawn_base;
    int s = sine_of(-angle);
    int co = cosine_of(-angle);
    turn_pair(&a.y, &a.z, s, co);
    turn_pair(&b.y, &b.z, s, co);
    turn_pair(&c.y, &c.z, s, co);

    CollisionCylinder_ConstructSet((CollisionCylinder *) &cylinder, &c, radius, height);
    if (CollisionCylinder_HitCaps((CollisionCylinder *) &cylinder, &b, &a) != 0 ||
        CollisionCylinder_HitSide((CollisionCylinder *) &cylinder, &b, &a) != 0) {
        Vec_RotateX(&b, angle);
        *end = b;
        CollisionCylinder_Destruct((CollisionCylinder *) &cylinder);
        return 1;
    }
    CollisionCylinder_Destruct((CollisionCylinder *) &cylinder);
    return 0;
}
CLEAN_AS(func_020b83ec, TouchPick_SegmentHitsCylinder)

/* func_020b8538: whether shapes of `kind` can be picked (data_020d2254: all of 0-22 but 0 and
 * 21); 0 outside 0-22. */
u8 TouchPick_KindPickable(int kind)
{
    if (kind < 0 || kind >= TOUCH_PICK_KINDS) {
        return 0;
    }
    return data_020d2254[kind];
}
CLEAN_AS(func_020b8538, TouchPick_KindPickable)

/* func_020b8550: whether the segment from `start` to `end` meets the globe of `radius` (the
 * drum along X from 0 to `length`); the hit to `hit` when it does. The test turns the segment a
 * quarter turn about Z (so the drum stands along Y) and the hit three quarters on. */
int TouchPick_SegmentHitsGlobe(Vec3 *hit, Vec3 *start, Vec3 *end, fx32 radius, fx32 length)
{
    Vec3 origin = {0, 0, 0};
    TouchPickTestCylinder drum;

    CollisionCylinder_ConstructSet((CollisionCylinder *) &drum, &origin, radius, length);
    Vec3 a = *start;
    Vec3 b = *end;
    int s = sine_of(0x4000);
    int c = cosine_of(0x4000);
    turn_pair(&a.x, &a.y, s, c);
    turn_pair(&b.x, &b.y, s, c);
    if (CollisionCylinder_HitSide((CollisionCylinder *) &drum, &b, &a) != 0) {
        turn_pair(&b.x, &b.y, sine_of(0xc000), cosine_of(0xc000));
        *hit = b;
        CollisionCylinder_Destruct((CollisionCylinder *) &drum);
        return 1;
    }
    CollisionCylinder_Destruct((CollisionCylinder *) &drum);
    return 0;
}
CLEAN_AS(func_020b8550, TouchPick_SegmentHitsGlobe)
