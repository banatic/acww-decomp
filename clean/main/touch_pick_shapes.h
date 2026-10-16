/* What the pen picks on the field: main's object at data_021f6a14 (TouchPick, see
 * touch_pick.h for the kinds and the objects behind them) casts a ray from the pen's pixel into
 * the scene each frame (TouchPick_Update) and keeps where it meets the ground and the nearest
 * shape it meets.
 *
 * The shapes are registered each frame by the objects that can be picked, in three lists of
 * nodes the objects own (each node names its kind and an index): triangles (TouchPickFace),
 * spheres (TouchPickSphere) and upright cylinders (TouchPickCylinder). The update also tests the
 * field's bodies (data_021d3120, BodyNode) and the posts the map has on its units
 * (func_02031078), and empties the three lists when it is done.
 *
 * Points are 20.12 fixed point. Outdoors the world is drawn bent round a drum along X of radius
 * 0x1f576 (func_0203f758, "the globe"); func_0203f844 bends a map point into the drawn world
 * and func_0203f7d0 takes a drawn point back to the map. The pen's ray is in the drawn world,
 * the points the pick keeps are map points. */
#ifndef CLEAN_MAIN_TOUCH_PICK_SHAPES_H
#define CLEAN_MAIN_TOUCH_PICK_SHAPES_H

#include "autoload_2/vector.h"
#include "main/field_collision.h"
#include "types.h"

/* The ground point's X when the ray met no ground (-300.0). */
#define TOUCH_PICK_NO_POINT ((fx32) 0xffed4000)

/* Kinds the update gives the map's posts (touch_pick.h). */
#define TOUCH_PICK_KIND_POST 5
#define TOUCH_PICK_KIND_OUTDOOR_ENTRY 6

#define TOUCH_PICK_BOX_FACES 10

/* A triangle that can be picked (0x44 bytes, vtable data_020e5810 over the collision
 * triangle's). */
typedef struct TouchPickFace {
    CollisionTriangle triangle;
    struct TouchPickFace *next; /* 0x38 */
    int kind;                   /* 0x3c */
    u8 index;                   /* 0x40 */
    u8 unk_41[3];
} TouchPickFace;

/* A sphere that can be picked (0x1c bytes). */
typedef struct TouchPickSphere {
    Vec3 centre; /* in the drawn world */
    fx32 radius; /* 0x0c */
    u8 index;    /* 0x10 */
    u8 unk_11[3];
    int kind;                     /* 0x14 */
    struct TouchPickSphere *next; /* 0x18 */
} TouchPickSphere;

/* An upright cylinder that can be picked (0x20 bytes), standing on a map point. */
typedef struct TouchPickCylinder {
    Vec3 base;
    fx32 radius; /* 0x0c */
    fx32 height; /* 0x10 */
    int kind;    /* 0x14 */
    u8 index;    /* 0x18 */
    u8 unk_19[3];
    struct TouchPickCylinder *next; /* 0x1c */
} TouchPickCylinder;

/* The pick object (data_021f6a14). */
typedef struct TouchPick {
    Vec3 ground; /* where the ray met the ground (a map point), or NO_POINT */
    Vec3 point;  /* 0x0c: the picked shape's point */
    u8 kind;     /* 0x18: the picked shape's kind, 0 for none */
    u8 index;    /* 0x19 */
    u8 pen_down; /* 0x1a: the pen was down at the last update */
    u8 unk_1b;
    TouchPickFace *faces;         /* 0x1c */
    TouchPickSphere *spheres;     /* 0x20 */
    TouchPickCylinder *cylinders; /* 0x24 */
} TouchPick;

/* The pen's ray (func_020b8314): from the camera to the far point, and its unit direction. */
typedef struct TouchPickRay {
    Vec3 origin;
    Vec3 end;
    Vec3 direction;
} TouchPickRay;

int TouchPick_NoObject(void);
int TouchPick_ObjectOnPenDown(TouchPick *pick, int *kind, u8 *index);
int TouchPick_PickedObject(TouchPick *pick, int *kind, u8 *index);
u8 TouchPick_GetPick(TouchPick *pick, Vec3 *point, u32 *kind, u8 *index);
int TouchPick_GetGround(TouchPick *pick, Vec3 *ground);
void TouchPick_DestructBase(void);
void TouchPick_ConstructBase(void);
void TouchPick_Update(TouchPick *pick, u8 pen_x, u8 pen_y, int pen_down);
int TouchPick_SetFaceAndAdd(TouchPick *pick, TouchPickFace *face, Vec3 *a, Vec3 *b, Vec3 *c, int kind, u8 index);
int TouchPick_AddFace(TouchPick *pick, TouchPickFace *face);
int TouchPick_SetCylinderAndAdd(TouchPick *pick, TouchPickCylinder *cylinder, Vec3 *base, fx32 radius, fx32 height, int kind,
                                u8 index);
int TouchPick_AddCylinder(TouchPick *pick, TouchPickCylinder *cylinder);
void TouchPick_SetSphereAndAdd(TouchPick *pick, TouchPickSphere *sphere, Vec3 *centre, fx32 radius, int kind, u8 index);
int TouchPick_AddSphere(TouchPick *pick, TouchPickSphere *sphere);
int TouchPick_SetBoxAndAdd(TouchPick *pick, TouchPickFace *faces, Vec3 *centre, fx32 width, fx32 depth, fx32 height, s16 angle,
                           int kind, u8 index);
int TouchPick_AddFaces(TouchPick *pick, TouchPickFace *faces);
TouchPick *TouchPick_Construct(TouchPick *pick);
TouchPick *TouchPick_Destruct(TouchPick *pick);
void TouchPick_ResetOnSceneEnd(TouchPick *pick);
void TouchPick_ResetOnSceneStart(TouchPick *pick);
void TouchPick_Reset(TouchPick *pick, u8 pen_down);
int TouchPickCylinder_Set(TouchPickCylinder *cylinder, Vec3 *base, fx32 radius, fx32 height, int kind, u8 index);
TouchPickCylinder *TouchPickCylinder_Destruct(TouchPickCylinder *cylinder);
TouchPickCylinder *TouchPickCylinder_Construct(TouchPickCylinder *cylinder);
int TouchPickSphere_Set(TouchPickSphere *sphere, Vec3 *centre, fx32 radius, int kind, u8 index);
void TouchPickSphere_SetAtMapPoint(TouchPickSphere *sphere, Vec3 *centre, u32 radius, u32 kind, u8 index);
TouchPickSphere *TouchPickSphere_Destruct(TouchPickSphere *sphere);
TouchPickSphere *TouchPickSphere_Destruct2(TouchPickSphere *sphere);
TouchPickSphere *TouchPickSphere_Construct(TouchPickSphere *sphere);
TouchPickSphere *TouchPickSphere_Construct2(TouchPickSphere *sphere);
int TouchPickFace_Set(TouchPickFace *face, Vec3 *a, Vec3 *b, Vec3 *c, int kind, u8 index);
int TouchPickFace_SetAtMapPoints(TouchPickFace *face, Vec3 *a, Vec3 *b, Vec3 *c, int kind, u8 index);
TouchPickFace *TouchPickFace_Destruct(TouchPickFace *face);
TouchPickFace *TouchPickFace_Construct(TouchPickFace *face);
u8 TouchPickFaces_SetBox(TouchPickFace *faces, Vec3 *centre, fx32 width, fx32 depth, fx32 height, int angle, int kind,
                         int index);
TouchPickFace *TouchPickFaces_DestructBox(TouchPickFace *faces);
TouchPickFace *TouchPickFaces_ConstructBox(TouchPickFace *faces);
void TouchPick_PenRay(TouchPickRay *ray, int pen_x, int pen_y);
int TouchPick_SegmentHitsCylinder(Vec3 *end, Vec3 *start, Vec3 *base, fx32 radius, fx32 height);
u8 TouchPick_KindPickable(int kind);
int TouchPick_SegmentHitsGlobe(Vec3 *hit, Vec3 *start, Vec3 *end, fx32 radius, fx32 length);

#endif
