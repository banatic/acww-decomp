/* The compass (compass.h). */
#include "compass.h"

#include <stdint.h>

#include "autoload_2/approach.h"
#include "clean.h"
#include "main/model_matrix.h"
#include "room_object_life.h"
#include "room_object_map.h"
#include "room_object_parts.h"

static_assert(offsetof(Compass, needle) == 0x844, "needle");
static_assert(offsetof(Compass, turn_frames) == 0x846, "turn frames");
static_assert(offsetof(Compass, phase) == 0x848, "phase");
static_assert(offsetof(Compass, swing) == 0x84c, "swing");
static_assert(offsetof(Compass, deflection) == 0x850, "deflection");
static_assert(sizeof(Compass) == 0x854, "the size Compass_Create allocates");

#define COMPASS_SIZE 0x854
#define COMPASS_NO_NODE (-1)
#define COMPASS_DEGREES_360 0x168000 /* 360.0 */
#define COMPASS_SWING_FRAME 8        /* the frame of a turn the needle swings at */
#define COMPASS_SWING 0x2d000        /* 45.0 degrees */
#define COMPASS_STEP 0x5a00          /* 5.625 degrees: the most the swing and deflection change a frame */
#define COMPASS_PHASE_STEP 0x960

/* NNS_G3D_JNTANM_RESULTFLAG_ROT_ZERO: the joint's rotation is the identity, not yet written. */
#define COMPASS_ROTATION_IDENTITY 2

/* The joint being drawn (NitroSystem's NNSG3dJntAnmResult), as NodeHookState.unk_B4 points to
 * it. */
typedef struct CompassJoint {
    u32 flags;
    u8 unk_04[0x24]; /* its scales */
    Mtx33 rotation;
} CompassJoint;

static_assert(offsetof(CompassJoint, rotation) == 0x28, "rotation");

/* "compass", the needle's node. */
extern const char data_ov004_022531c0[];

/* The class's vtables, and its receiver part's. */
extern const u8 data_ov004_02251c6c[];
extern const u8 data_ov004_02251d18[];

/* NitroSDK's table of sines and cosines, interleaved, for 4096 angles. */
extern const s16 FX_SinCosTable_[];
extern fx32 FX_Div(fx32 numerator, fx32 denominator);
extern fx32 FX_MulFunc(fx32 a, fx32 b);
extern void MTX_RotY33_(Mtx33 *mtx, fx32 sin, fx32 cos);
extern void MTX_Concat33(const Mtx33 *a, const Mtx33 *b, Mtx33 *out);
/* The index of the model's node named `name`. */
extern int func_0205790c(G3dModel *model, const char *name);

/* An arithmetic shift right, for negative values too. */
static s32 Compass_shift_right(s32 value, int bits)
{
    return value >= 0 ? value >> bits : ~(~value >> bits);
}

/* func_ov004_022136f8 (vtable slot 0x6c, the model's hook after a node's description): for the
 * needle, turns its joint about Y by the deflection less the object's facing; that of the
 * object it stands on, plus its turn on it (Mount_Angle), when it stands on one. The turn is
 * put before the joint's rotation, or in its place while that is the identity. */
void Compass_NeedleHook(Compass *compass, int node, NodeHookState *state)
{
    if (compass->needle != node) {
        return;
    }
    CompassJoint *joint = state->unk_B4;
    /* The deflection as a 16-bit angle: its fraction of a turn (FX_Div by 360) times 0x10000. */
    fx32 turns = FX_MulFunc(FX_Div(compass->deflection, COMPASS_DEGREES_360), 0x10000000);
    s32 deflection = Compass_shift_right((s32) ((u32) turns << 4), 16);
    u16 angle;
    int parent = RoomObject_MountParent(&compass->base);
    if (parent != 0) {
        s16 parent_angle = ((const RoomObject *) (uintptr_t) parent)->angle;
        int on_parent = Mount_Angle(&compass->base.mount);
        angle = (u16) ((u32) deflection - ((u32) parent_angle + (u32) on_parent));
    } else {
        angle = (u16) ((u32) deflection - (u32) compass->base.angle);
    }
    int index = (angle >> 4) * 2;
    Mtx33 turn;
    MTX_RotY33_(&turn, FX_SinCosTable_[index], FX_SinCosTable_[index + 1]);
    if ((joint->flags & COMPASS_ROTATION_IDENTITY) != 0) {
        joint->rotation = turn;
    } else {
        MTX_Concat33(&joint->rotation, &turn, &joint->rotation);
    }
    joint->flags &= ~(u32) COMPASS_ROTATION_IDENTITY;
}
CLEAN_AS(func_ov004_022136f8, Compass_NeedleHook)

/* func_ov004_022137c8 (vtable slot 0x9c, each frame of a turn): at the 8th frame the phase
 * starts again and the swing is set to +45 degrees when turning towards a lower angle, -45
 * otherwise.
 * QUIRK: the swing is first multiplied by the sine of the phase, read after the phase was set
 * to 0, so by 0: the old swing never counts. The clamp to 45 degrees is then a second write. */
void Compass_OnTurnFrame(Compass *compass, int down)
{
    compass->turn_frames = (s16) (compass->turn_frames + 1);
    if (compass->turn_frames != COMPASS_SWING_FRAME) {
        return;
    }
    compass->phase = 0;
    fx32 kept = FX_MulFunc(compass->swing, FX_SinCosTable_[(compass->phase >> 4) * 2]);
    if (down != 0) {
        compass->swing = (fx32) ((u32) kept + COMPASS_SWING);
        if (compass->swing > COMPASS_SWING) {
            compass->swing = COMPASS_SWING;
        }
    } else {
        compass->swing = (fx32) ((u32) kept - COMPASS_SWING);
        if (compass->swing < -COMPASS_SWING) {
            compass->swing = -COMPASS_SWING;
        }
    }
}
CLEAN_AS(func_ov004_022137c8, Compass_OnTurnFrame)

/* func_ov004_02213850 (vtable slot 0x98, when a turn starts): counts the turn's frames from 0.
 * Returns the compass. */
Compass *Compass_OnTurnStart(Compass *compass)
{
    compass->turn_frames = 0;
    return compass;
}
CLEAN_AS(func_ov004_02213850, Compass_OnTurnStart)

/* func_ov004_0221385c (vtable slot 0x0c) */
int Compass_Vfunc0C(void)
{
    return 1;
}
CLEAN_AS(func_ov004_0221385c, Compass_Vfunc0C)

/* func_ov004_02213860 (vtable slot 0x80, each frame while neither appearing nor vanishing):
 * the swing decays towards 0; the phase advances while it is not 0 and is 0 once it is; the
 * deflection moves towards the swing times the phase.
 * QUIRK: the phase is taken as a signed 20.12 multiplier (-8 to 8, a sawtooth), not through its
 * sine. */
int Compass_Update(Compass *compass)
{
    Approach_S32Again(&compass->swing, 0, COMPASS_STEP);
    if (compass->swing == 0) {
        compass->phase = 0;
    } else {
        compass->phase = (u16) (compass->phase + COMPASS_PHASE_STEP);
    }
    Approach_S32Again(&compass->deflection, FX_MulFunc(compass->swing, (s16) compass->phase), COMPASS_STEP);
    return 1;
}
CLEAN_AS(func_ov004_02213860, Compass_Update)

/* func_ov004_022138c0 (vtable slot 0x7c, once the model is bound): finds the needle's node;
 * done at once. */
int Compass_Start(Compass *compass)
{
    compass->needle = (s16) func_0205790c(compass->base.model_resource, data_ov004_022531c0);
    return 1;
}
CLEAN_AS(func_ov004_022138c0, Compass_Start)

static void Compass_set_vtables(Compass *compass)
{
    compass->base.vtable = (const RoomObjectVtable *) data_ov004_02251c6c;
    compass->base.receiver_vtable = data_ov004_02251d18;
}

/* func_ov004_022138e8 (the deleting destructor, vtable slot 0x44) */
Compass *Compass_Delete(Compass *compass)
{
    Compass_set_vtables(compass);
    RoomObject_DestructBase(&compass->base);
    RoomObject_Free(compass);
    return compass;
}
CLEAN_AS(func_ov004_022138e8, Compass_Delete)

/* func_ov004_02213914 (the destructor, vtable slot 0x40) */
Compass *Compass_Destroy(Compass *compass)
{
    Compass_set_vtables(compass);
    RoomObject_DestructBase(&compass->base);
    return compass;
}
CLEAN_AS(func_ov004_02213914, Compass_Destroy)

/* func_ov004_02213938 (the constructor): no needle yet. Its other fields are left as the
 * allocation zeroed them. */
Compass *Compass_Construct(Compass *compass)
{
    RoomObject_ConstructBase(&compass->base);
    Compass_set_vtables(compass);
    compass->needle = COMPASS_NO_NODE;
    return compass;
}
CLEAN_AS(func_ov004_02213938, Compass_Construct)

/* func_ov004_02213968: a new compass from the room's heap; nothing when it has no room. */
void Compass_Create(void)
{
    Compass *compass = RoomObject_Alloc(COMPASS_SIZE);
    if (compass != NULL) {
        Compass_Construct(compass);
    }
}
CLEAN_AS(func_ov004_02213968, Compass_Create)
