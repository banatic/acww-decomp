/* Members of the model of the room (room_shell_members.h). */
#include "room_shell_members.h"

#include <stdint.h>

#include "autoload_2/heap.h"
#include "clean.h"
#include "main/model_anim.h"
#include "main/scene_kinds.h"
#include "main/scene_query.h"
#include "main/trivial_object.h"

static_assert(sizeof(RoomShellTouch) == 0x24, "touch");
static_assert(offsetof(RoomShellTouch, enabled) == 0x20, "touch enabled");
static_assert(sizeof(CollisionBox) == 0x9c, "collision box");
static_assert(sizeof(RoomShellMaterialAnim) == sizeof(ModelAnim), "material anim");
static_assert(offsetof(RoomShellMaterialAnim, anim) == offsetof(ModelAnim, anim), "material anim object");
static_assert(sizeof(RoomShellMaterialAnim) == 0x20, "material anim size");
static_assert(sizeof(RoomShellModel) == 0xb8, "model");
static_assert(offsetof(RoomShellModel, anim) == offsetof(AnimatedModel, anim), "model anim");

/* The scene whose touch cylinder is enabled, and the cylinder. */
#define ROOM_SHELL_TOUCH_SCENE 0x22
#define ROOM_SHELL_TOUCH_X 0x108f6
#define ROOM_SHELL_TOUCH_Z 0x1351e
#define ROOM_SHELL_TOUCH_RADIUS 0xf33
#define ROOM_SHELL_TOUCH_HEIGHT 0x6000
#define ROOM_SHELL_TOUCH_KIND 0x16
#define ROOM_SHELL_TOUCH_INDEX 0xff

/* The scene with the single box, and the box. */
#define ROOM_SHELL_BOX_SCENE 10
#define ROOM_SHELL_BOX_X 0xe000
#define ROOM_SHELL_BOX_Z_PAST 0x1000u
#define ROOM_SHELL_BOX_WIDTH 0x8000
#define ROOM_SHELL_BOX_DEPTH 0x2000
#define ROOM_SHELL_BOX_HEIGHT 0x1000

/* The two boxes. */
#define ROOM_SHELL_BOXES_WIDTH 0x2000
#define ROOM_SHELL_BOXES_HEIGHT 0x4000
#define ROOM_SHELL_BOXES_X0 0xd000
#define ROOM_SHELL_BOXES_X1 0x13000
#define ROOM_SHELL_BOXES_Z 0x1c000

/* The material animation's class. */
extern const u32 data_ov004_02255ab8[];

/* A z the scenes' places are measured from (scene_place.c). */
extern const fx32 data_020ca0f0;

/* The single box's point: a function-local static built on first use (its guard, bit 0 of
 * data_ov004_022589f0), registered for destruction with its record. */
extern u32 data_ov004_022589f0;
extern Vec3 data_ov004_02258a54;
extern u8 data_ov004_02258a48[];

/* The collision box's constructor and destructor, handed to the C++ runtime: the game's. */
extern CollisionBox *func_020324c4(CollisionBox *box);
extern CollisionBox *func_020324fc(CollisionBox *box);
extern void func_020012dc(void *object);

extern void __register_global_object(void *object, void *destruct, void *record);
extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));
extern void __cxa_vec_ctor(void *array, int count, int size, void (*construct)(void *), void (*destruct)(void *));

static TouchPick *RoomShellTouch_pick(void)
{
    return (TouchPick *) (intptr_t) SceneQuery_FieldObject();
}

/* func_ov004_0223226c (at the room's release): nothing to do. */
void RoomShellTouch_Remove(RoomShellTouch *self)
{
    (void) self;
}
CLEAN_AS(func_ov004_0223226c, RoomShellTouch_Remove)

/* func_ov004_02232270 (each frame): the cylinder offered to the pick while enabled; what the
 * pick answers, 0 while disabled. */
int RoomShellTouch_Offer(RoomShellTouch *self)
{
    if (self->enabled != 0) {
        return TouchPick_AddCylinder(RoomShellTouch_pick(), &self->cylinder);
    }
    return 0;
}
CLEAN_AS(func_ov004_02232270, RoomShellTouch_Offer)

/* func_ov004_0223228c (at the room's start): enabled in scene 0x22, and then set up and
 * offered to the pick. */
void RoomShellTouch_Init(RoomShellTouch *self)
{
    if (SceneQuery_Current() == ROOM_SHELL_TOUCH_SCENE) {
        self->enabled = 1;
    }
    if (self->enabled != 0) {
        Vec3 base = {ROOM_SHELL_TOUCH_X, 0, ROOM_SHELL_TOUCH_Z};
        TouchPick_SetCylinderAndAdd(RoomShellTouch_pick(), &self->cylinder, &base, ROOM_SHELL_TOUCH_RADIUS,
                                    ROOM_SHELL_TOUCH_HEIGHT, ROOM_SHELL_TOUCH_KIND, ROOM_SHELL_TOUCH_INDEX);
    }
}
CLEAN_AS(func_ov004_0223228c, RoomShellTouch_Init)

/* func_ov004_022322ec: the cylinder destroyed; the address back, as an int. */
int RoomShellTouch_Destruct(RoomShellTouch *self)
{
    TouchPickCylinder_Destruct(&self->cylinder);
    return (int) (intptr_t) self;
}
CLEAN_AS(func_ov004_022322ec, RoomShellTouch_Destruct)

/* func_ov004_022322fc: disabled. */
RoomShellTouch *RoomShellTouch_Construct(RoomShellTouch *self)
{
    TouchPickCylinder_Construct(&self->cylinder);
    self->enabled = 0;
    return self;
}
CLEAN_AS(func_ov004_022322fc, RoomShellTouch_Construct)

/* func_ov004_02232314 (at the room's release): in scene 10, the box taken off the field and
 * what that answers.
 * QUIRK: in other scenes the result is the scene's number. */
int RoomShellBox_Remove(CollisionBox *box)
{
    int scene = SceneQuery_Current();
    if (scene == ROOM_SHELL_BOX_SCENE) {
        return CollisionBox_Remove(box);
    }
    return scene;
}
CLEAN_AS(func_ov004_02232314, RoomShellBox_Remove)

/* func_ov004_0223232c (at the room's start): in scene 10, the box put on the field (not
 * turned, not scaled) at its point, which the first call works out. */
void RoomShellBox_Add(CollisionBox *box)
{
    if (SceneQuery_Current() != ROOM_SHELL_BOX_SCENE) {
        return;
    }
    if ((data_ov004_022589f0 & 1) == 0) {
        data_ov004_02258a54.x = ROOM_SHELL_BOX_X;
        data_ov004_02258a54.y = 0;
        data_ov004_02258a54.z = (fx32) ((u32) data_020ca0f0 + ROOM_SHELL_BOX_Z_PAST);
        __register_global_object(&data_ov004_02258a54, (void *) (uintptr_t) func_020012dc, data_ov004_02258a48);
        data_ov004_022589f0 |= 1;
    }
    CollisionBox_Add(box, ROOM_SHELL_BOX_WIDTH, ROOM_SHELL_BOX_DEPTH, ROOM_SHELL_BOX_HEIGHT, &data_ov004_02258a54, 0, NULL);
}
CLEAN_AS(func_ov004_0223232c, RoomShellBox_Add)

/* func_ov004_022323b0 (at the room's release): where the boxes are wanted, both taken off the
 * field. Always 1. */
int RoomShellBoxes_Remove(CollisionBox *boxes)
{
    if (RoomShellBoxes_Wanted()) {
        CollisionBox_Remove(&boxes[0]);
        CollisionBox_Remove(&boxes[1]);
    }
    return 1;
}
CLEAN_AS(func_ov004_022323b0, RoomShellBoxes_Remove)

/* func_ov004_022323d4 (at the room's start): where the boxes are wanted, both put on the
 * field; whether both were. */
int RoomShellBoxes_Add(CollisionBox *boxes)
{
    if (!RoomShellBoxes_Wanted()) {
        return 0;
    }
    Vec3 left = {ROOM_SHELL_BOXES_X0, 0, ROOM_SHELL_BOXES_Z};
    Vec3 right = {ROOM_SHELL_BOXES_X1, 0, ROOM_SHELL_BOXES_Z};
    int added_left = CollisionBox_Add(&boxes[0], ROOM_SHELL_BOXES_WIDTH, 0, ROOM_SHELL_BOXES_HEIGHT, &left, 0, NULL);
    int added_right = CollisionBox_Add(&boxes[1], ROOM_SHELL_BOXES_WIDTH, 0, ROOM_SHELL_BOXES_HEIGHT, &right, 0, NULL);
    return added_left != 0 && added_right != 0;
}
CLEAN_AS(func_ov004_022323d4, RoomShellBoxes_Add)

/* func_ov004_02232450: whether the boxes are wanted: in a room of the player's house or in
 * scenes 6 to 8. */
int RoomShellBoxes_Wanted(void)
{
    if (SceneKinds_CurrentIsHouseRoom()) {
        return 1;
    }
    return SceneKinds_CurrentIn6To8() != 0;
}
CLEAN_AS(func_ov004_02232450, RoomShellBoxes_Wanted)

/* func_ov004_02232470 */
CollisionBox *RoomShellBoxes_Destruct(CollisionBox *boxes)
{
    __cxa_vec_cleanup(boxes, ROOM_SHELL_BOXES, sizeof(CollisionBox), (void (*)(void *))(uintptr_t) func_020324c4);
    return boxes;
}
CLEAN_AS(func_ov004_02232470, RoomShellBoxes_Destruct)

/* func_ov004_0223248c */
CollisionBox *RoomShellBoxes_Construct(CollisionBox *boxes)
{
    __cxa_vec_ctor(boxes, ROOM_SHELL_BOXES, sizeof(CollisionBox), (void (*)(void *))(uintptr_t) func_020324fc,
                   (void (*)(void *))(uintptr_t) func_020324c4);
    return boxes;
}
CLEAN_AS(func_ov004_0223248c, RoomShellBoxes_Construct)

/* func_ov004_022324b4: the animation object, 0 before it is allocated. */
static ModelAnim *RoomShellMaterialAnim_base(RoomShellMaterialAnim *anim)
{
    return (ModelAnim *) (void *) anim;
}

unsigned long RoomShellMaterialAnim_Anim(RoomShellMaterialAnim *anim)
{
    return (unsigned long) (uintptr_t) anim->anim;
}
CLEAN_AS(func_ov004_022324b4, RoomShellMaterialAnim_Anim)

/* func_ov004_022324b8 (the deleting destructor) */
RoomShellMaterialAnim *RoomShellMaterialAnim_Delete(RoomShellMaterialAnim *anim)
{
    anim->ctrl.vtable = data_ov004_02255ab8;
    ModelAnim_Destruct(RoomShellMaterialAnim_base(anim));
    Heap_OperatorDeleteB(anim);
    return anim;
}
CLEAN_AS(func_ov004_022324b8, RoomShellMaterialAnim_Delete)

/* func_ov004_022324d8 (the destructor) */
RoomShellMaterialAnim *RoomShellMaterialAnim_Destruct(RoomShellMaterialAnim *anim)
{
    anim->ctrl.vtable = data_ov004_02255ab8;
    ModelAnim_Destruct(RoomShellMaterialAnim_base(anim));
    return anim;
}
CLEAN_AS(func_ov004_022324d8, RoomShellMaterialAnim_Destruct)

/* func_ov004_022324f0 (the constructor) */
RoomShellMaterialAnim *RoomShellMaterialAnim_Construct(RoomShellMaterialAnim *anim)
{
    ModelAnim_ConstructBase(RoomShellMaterialAnim_base(anim));
    anim->ctrl.vtable = data_ov004_02255ab8;
    return anim;
}
CLEAN_AS(func_ov004_022324f0, RoomShellMaterialAnim_Construct)
