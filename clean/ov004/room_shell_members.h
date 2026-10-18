/* Members of the model of the room (room_shell.h) with code of their own:
 *
 * - its material animation (0x108): a ModelAnim (model_anim.h) of a class of overlay 4 (vtable
 *   0x02255ab8) that only has its own destructors;
 * - two collision boxes (0x3328) put on the field in the player's house rooms and scenes 6 to
 *   8: flat ones (no depth), 2.0 wide and 4.0 high, standing at (13.0, 0, 28.0) and
 *   (19.0, 0, 28.0);
 * - a collision box (0x3460) put on the field in scene 10 only: 8.0 wide, 2.0 deep and 1.0
 *   high at (14.0, 0, 1.0 past data_020ca0f0);
 * - a touch cylinder (0x34fc) for the pick object (touch_pick_shapes.h), enabled in scene 0x22
 *   only, and offered to the pick each frame while enabled. */
#ifndef CLEAN_OV004_ROOM_SHELL_MEMBERS_H
#define CLEAN_OV004_ROOM_SHELL_MEMBERS_H

#include "main/collision_box.h"
#include "main/frame_ctrl.h"
#include "main/model_object.h"
#include "main/touch_pick_shapes.h"
#include "types.h"

/* The room's model has the layout of RmoAnimatedModel (rmo_object.h): an animated model
 * without the blended model's ramp, smaller than main/animated_model.h's AnimatedModel. Its
 * material animation has the layout of ModelAnim (model_anim.h). */

/* NitroSystem's animation object (NNSG3dAnmObj) as far as its frame. */
typedef struct RoomShellAnimObject {
    fx32 frame;
} RoomShellAnimObject;

/* An animated model (animated_model.h) without the blended model's part. */
typedef struct RoomShellModel {
    ModelObject object;        /* 0x00: object.unk_64 is the model's base matrix (a Mtx43) */
    FrameCtrl frames;          /* 0x9c */
    RoomShellAnimObject *anim; /* 0xb4: its joint animation's object */
} RoomShellModel;

/* A ModelAnim: a frame control and its animation object for a model. */
typedef struct RoomShellMaterialAnim {
    FrameCtrl ctrl;            /* 0x00: its vtable is the class's */
    RoomShellAnimObject *anim; /* 0x18: NULL until allocated */
    u8 *model;                 /* 0x1c */
} RoomShellMaterialAnim;

/* The boxes at 0x3328. */
#define ROOM_SHELL_BOXES 2

typedef struct RoomShellTouch {
    TouchPickCylinder cylinder; /* 0x00 */
    u8 enabled;                 /* 0x20 */
    u8 pad_21[3];
} RoomShellTouch;

void RoomShellTouch_Remove(RoomShellTouch *self);
int RoomShellTouch_Offer(RoomShellTouch *self);
void RoomShellTouch_Init(RoomShellTouch *self);
int RoomShellTouch_Destruct(RoomShellTouch *self);
RoomShellTouch *RoomShellTouch_Construct(RoomShellTouch *self);
int RoomShellBox_Remove(CollisionBox *box);
void RoomShellBox_Add(CollisionBox *box);
int RoomShellBoxes_Remove(CollisionBox *boxes);
int RoomShellBoxes_Add(CollisionBox *boxes);
int RoomShellBoxes_Wanted(void);
CollisionBox *RoomShellBoxes_Destruct(CollisionBox *boxes);
CollisionBox *RoomShellBoxes_Construct(CollisionBox *boxes);
unsigned long RoomShellMaterialAnim_Anim(RoomShellMaterialAnim *anim);
RoomShellMaterialAnim *RoomShellMaterialAnim_Delete(RoomShellMaterialAnim *anim);
RoomShellMaterialAnim *RoomShellMaterialAnim_Destruct(RoomShellMaterialAnim *anim);
RoomShellMaterialAnim *RoomShellMaterialAnim_Construct(RoomShellMaterialAnim *anim);

#endif
