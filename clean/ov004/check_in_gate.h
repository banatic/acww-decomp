/* A room object of the RMO family (rmo_object.h; vtable 0x02254e4c, 0x498 bytes) built from
 * /roomObj/obj_check_in.arc and its .nsbtx: the check-in counter with its gate that overlay
 * 48's gatekeeper opens and closes (CheckInGate_Open, CheckInGate_Close, CheckInGate_IsOpen).
 * data_ov004_0225827c points to the last one started.
 *
 * Its model takes the field's ground texture first, then its own; the lights of seven
 * materials ("m_grd_clf" and others) are set to the overlay's light mask, and the colour of
 * three materials ("m_lt", "m_ltdoor", "m_open") follows the time of day while it is drawn, from
 * a table of 24 hours (data_ov004_02247784) blended by the minute. It plays a joint animation
 * and a material animation (at 0x290) together, and stands in two fixed collision boxes.
 *
 * Its gate's state (RmoObject byte 0x24c) is entered through vtable slot 0x60 and stepped by
 * its update, through tables of member pointers (member_pointer.h): closed, opening (sounds
 * 0x4eb and, at frame 0x3a, 0x4ed), open, closing (0x4ec and 0x4ee); the opening and closing go
 * on to open and closed when their joint animation has run out. A flat wall stands at the
 * door, set up again each frame: at offset 0 while closed, eased to -0x2000 while opening and
 * back while closing, and while open only in scene 11 (at -0x2000). */
#ifndef CLEAN_OV004_CHECK_IN_GATE_H
#define CLEAN_OV004_CHECK_IN_GATE_H

#include "autoload_2/vector.h"
#include "main/collision_box.h"
#include "main/model_anim.h"
#include "rmo_object.h"
#include "types.h"

#define CHECK_IN_GATE_LIGHTS 3 /* the materials whose colour follows the time of day */
#define CHECK_IN_GATE_BOXES 2

typedef struct CheckInGate {
    RmoObject base;                            /* 0x000: base.unk_24c[0] is the gate's state */
    ModelAnim material_anim;                   /* 0x290 */
    s32 light_materials[CHECK_IN_GATE_LIGHTS]; /* 0x2b0: "m_lt", "m_ltdoor", "m_open" */
    CollisionBox door_box;                     /* 0x2bc: the flat wall at the door */
    CollisionBox boxes[CHECK_IN_GATE_BOXES];   /* 0x358 */
    u8 door_on;                                /* 0x490: the door's wall stands this frame */
    u8 pad_491[3];
    fx32 door_offset; /* 0x494: along Z, 0 closed to -0x2000 open */
} CheckInGate;

/* The gate's states (CheckInGate.base.unk_24c[0]). */
enum CheckInGateState {
    CHECK_IN_GATE_CLOSED = 0,
    CHECK_IN_GATE_OPENING = 1,
    CHECK_IN_GATE_OPEN = 2,
    CHECK_IN_GATE_CLOSING = 3,
    CHECK_IN_GATE_STATE_COUNT = 4
};

/* The parts of NitroSystem's NNSG3dRenderObj and NNSG3dRS the material hook uses: the user
 * object is kept at 0x2c (ModelObject_SetInitHook puts it there). */
typedef struct CheckInGateRenderObject {
    u8 unk_00[0x2c];
    struct CheckInGate *user; /* 0x2c */
} CheckInGateRenderObject;

/* NitroSystem's NNSG3dMatAnmResult, its colour and polygon words. */
typedef struct CheckInGateMaterialResult {
    u32 flags;        /* 0x00 */
    u32 diffuse;      /* 0x04: diffuse colour in bits 0-14 */
    u32 unk_08;       /* 0x08 */
    u32 polygon_attr; /* 0x0c: POLYGON_ATTR, the alpha in bits 16-20 */
} CheckInGateMaterialResult;

#define CHECK_IN_GATE_G3D_COMMANDS 0x20

typedef struct CheckInGateHookState {
    const u8 *command;                           /* 0x00: byte 1 is the material */
    CheckInGateRenderObject *render_object;      /* 0x04 */
    u32 flags;                                   /* 0x08 */
    u32 hooks[CHECK_IN_GATE_G3D_COMMANDS];       /* 0x0c: each command's hook, 0 for none */
    u8 hook_timings[CHECK_IN_GATE_G3D_COMMANDS]; /* 0x8c */
    u8 unk_ac[4];                                /* 0xac */
    CheckInGateMaterialResult *material;         /* 0xb0 */
} CheckInGateHookState;

void CheckInGate_UpdateClosing(CheckInGate *self);
int CheckInGate_EnterClosing(CheckInGate *self);
void CheckInGate_UpdateOpen(CheckInGate *self);
int CheckInGate_EnterOpen(CheckInGate *self);
void CheckInGate_UpdateOpening(CheckInGate *self);
int CheckInGate_EnterOpening(CheckInGate *self);
void CheckInGate_UpdateClosed(CheckInGate *self);
int CheckInGate_EnterClosed(CheckInGate *self);
void CheckInGate_UpdateState(CheckInGate *self);
int CheckInGate_SetState(CheckInGate *self, unsigned int state);
void CheckInGate_RemoveDoorBox(CheckInGate *self);
void CheckInGate_UpdateDoorBox(CheckInGate *self);
void CheckInGate_SetDoor(CheckInGate *self, fx32 offset);
CheckInGate *CheckInGate_ClearDoor(CheckInGate *self);
void CheckInGate_MaterialHook(CheckInGate *self, int material, CheckInGateHookState *state);
int CheckInGate_IsOpen(void);
int CheckInGate_Close(void);
int CheckInGate_Open(void);
void CheckInGate_SetCurrent(CheckInGate *gate);
int CheckInGate_StartMaterialAnim(CheckInGate *self);
int CheckInGate_StartJointAnim(CheckInGate *self);
void CheckInGate_LightMaterials(CheckInGate *self);
int CheckInGate_BindTextures(CheckInGate *self);
int CheckInGate_Release(CheckInGate *self);
int CheckInGate_Draw(CheckInGate *self);
int CheckInGate_Update(CheckInGate *self);
int CheckInGate_Start(CheckInGate *self);
CheckInGate *CheckInGate_Delete(CheckInGate *self);
CheckInGate *CheckInGate_Destruct(CheckInGate *self);
CheckInGate *CheckInGate_Construct(CheckInGate *self);
void CheckInGate_SetModelHooks(CheckInGateHookState *state);
void CheckInGate_RunMaterialHook(CheckInGateHookState *state);
void CheckInGate_Create(void);

#endif
