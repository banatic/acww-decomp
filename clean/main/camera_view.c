/* The field camera's view (camera_view.h). */
#include "camera_view.h"

#include "acre_map.h"      /* AcreMap */
#include "acre_record.h"   /* AcreRecord_Model */
#include "actor_entries.h" /* ActorEntries_PickGameE */
#include "actor_table.h"   /* Actors_SlotE */
#include "autoload_2/approach.h"
#include "camera_control.h"
#include "camera_modes.h"
#include "clean.h"
#include "itcm/camera.h" /* Camera_GetTarget */
#include "itcm/vector.h" /* Vec_Add */
#include "ov004/member_pointer.h"
#include "player_record.h"  /* PlayerRecord_TestFlag */
#include "player_records.h" /* PlayerRecords_Current */
#include "view_frustum.h"   /* ViewFrustum_Set */

static_assert(sizeof(CameraPreset) == 0x14, "a preset");
static_assert(sizeof(CameraTiming) == 0x10, "a timing");
static_assert(offsetof(CameraControl, extra_distance) == 0x80, "the extra distance");
static_assert(offsetof(CameraControl, target_adjust) == 0x84, "the target's adjustment");
static_assert(offsetof(CameraControl, extra_fov) == 0x98, "the extra field of view");
static_assert(offsetof(CameraControl, extra_follow_radius) == 0xa0, "the extra radius");
static_assert(offsetof(CameraControl, extra_delay) == 0xa8, "the extra delay");
static_assert(offsetof(CameraControl, ease_in) == 0xc0, "the ease in");
static_assert(offsetof(CameraControl, inverse_view) == 0xcc, "the inverse view");
static_assert(offsetof(CameraControl, roll) == 0x174, "the roll");
static_assert(offsetof(CameraControl, room_min_x) == 0x178, "the room's bounds");
static_assert(offsetof(CameraControl, drawn_target) == 0x188, "the drawn target");
static_assert(offsetof(CameraControl, drawn_eye) == 0x194, "the drawn eye");
static_assert(offsetof(CameraControl, up) == 0x1a0, "the up vector");
static_assert(offsetof(CameraControl, ground_angle) == 0x1ac, "the ground's angle");
static_assert(offsetof(CameraControl, aspect) == 0x1b0, "the aspect ratio");
static_assert(offsetof(CameraControl, half_fov_sin) == 0x1bc, "the sine");
static_assert(offsetof(CameraControl, fov) == 0x1c8, "the field of view");
static_assert(offsetof(CameraControl, look_both) == 0x1ca, "both points");
static_assert(offsetof(CameraControl, look_at2) == 0x1d8, "the second point");
static_assert(offsetof(CameraControl, unk_1e4) == 0x1e4, "0x1e4");
static_assert(offsetof(CameraControl, initial_mode) == 0x200, "the first mode");
static_assert(offsetof(CameraControl, fixed_target) == 0x204, "the kept target");
static_assert(offsetof(CameraControl, fixed_eye) == 0x210, "the kept eye");

/* The camera, NULL when there is none. */
extern CameraControl *data_021c67a4;

/* The presets of views, and the timings of moves. */
extern const CameraPreset data_020ca20c[];
extern const CameraTiming data_020ca1ac[];

/* The modes' member functions (filled by __sinit_020c4d74). */
typedef struct CameraControlModeFunctions {
    MemberPointer start; /* returns whether the camera switches to the mode */
    MemberPointer frame;
} CameraControlModeFunctions;
extern CameraControlModeFunctions data_021c6820[CAMERA_MODES];

/* The point looked at, the eye and their distance, as last placed. */
extern Vec3 data_021c67d0;
extern Vec3 data_021c67b8;
extern fx32 data_021c679c;

/* The frustum the actors are culled against. */
extern ViewFrustum data_021f6a6c;

/* The world's depth of an acre (32.0): the least depth a room's bounds reach to. */
extern const fx32 data_020ca0e8;
/* The scale of z in CameraControl_SpanOfTwo: 1.5, or 1.0 in scene 9. */
extern fx32 data_020da718;
/* In scene 0x2c: the slot of the actor the camera was made to follow, 8 for none. */
extern int data_020da714;
/* The map of acres the player is in. */
extern AcreMap *data_021c80bc;
/* What func_0203f684 is handed the point looked at for each frame. */
extern u8 data_021c749c[];

/* The 3D state of the NITRO System's G3D: its flags, its camera's vectors and its projection and
 * camera matrices. */
typedef struct CameraViewG3dState {
    u8 unk_00[0x7c];
    u32 flags; /* 0x7c */
} CameraViewG3dState;
typedef struct CameraViewG3dCamera {
    u8 unk_00[0x40];
    Vec3 position; /* 0x40 */
    Vec3 up;       /* 0x4c */
    Vec3 target;   /* 0x58 */
} CameraViewG3dCamera;
extern CameraViewG3dState data_027e0148;
extern CameraViewG3dCamera data_027e02c8;
extern u8 data_027e00d0[]; /* the projection matrix */
extern u8 data_027e0114[]; /* the camera matrix */

extern const s16 FX_SinCosTable_[];
extern fx32 FX_MulFunc(fx32 a, fx32 b);
extern fx32 FX_InvA(fx32 x);
extern fx32 VEC_Mag(const Vec3 *v);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *sum);
extern void G3i_PerspectiveW_(unsigned int sin, unsigned int cos, unsigned int aspect, unsigned int near, unsigned int far,
                              unsigned int scale_w, unsigned int draw, void *matrix);
extern void G3i_LookAt_(Vec3 *position, Vec3 *up, Vec3 *target, int draw, void *matrix);
extern int MTX_Inverse43(const Mtx43 *mtx, Mtx43 *inverse);

/* The player's position (actor 4, the one at this console), or NULL. */
extern Vec3 *func_02095794(int actor);
/* `in` bent onto the curved ground drawn outdoors into `out`; the angle it is turned by (0
 * elsewhere). */
extern int func_0203f844(Vec3 *out, const Vec3 *in);
/* Outdoors, the angle of the curved ground under `point`; else 0. */
extern s16 func_0203f768(const Vec3 *point);
/* The share of a move done after `time`: 0 to 1.0, rising over `ease_in` and falling over
 * `ease_out` between `start` and `end`. */
extern fx32 func_020643dc(fx32 time, fx32 start, fx32 end, fx32 ease_in, fx32 ease_out);
/* Indoors, the bounds of the room's floor tiles in world units (x, then z). */
extern int func_02030738(fx32 *min_x, fx32 *max_x, fx32 *min_z, fx32 *max_z);
extern u8 func_020b65c4(void);                /* the scene */
extern u8 func_020b65b8(void);                /* the scene byte at data_020e54b0 */
extern int func_020b67e8(unsigned int scene); /* whether 1 <= scene <= 5 */
extern int func_020b9464(CameraControl *camera);
extern void func_0203f684(u8 *out, const Vec3 *point);

/* The scene the camera is in (data_021f6948): byte 4 says whether outdoors (the town, whose
 * ground is curved, overlay 3) or indoors (a room, overlay 4). */
typedef struct CameraViewScene {
    u8 unk_00[4];
    u8 outdoors;
} CameraViewScene;
extern CameraViewScene *data_021f6948;

/* The player whose position the camera follows. */
#define PLAYER 4
/* How far the point followed stays from a room's walls (5.0), and from its front wall in z
 * (2.0). */
#define ROOM_MARGIN 0x5000
#define ROOM_FRONT_MARGIN 0x2000
/* Scenes the camera is set up for in CameraControl_Create and CameraControl_SetRoomBounds. */
#define SCENE_TOWN 0
#define SCENE_6 6
#define SCENE_9 9
#define SCENE_12 0xc
#define SCENE_13 0xd
#define SCENE_14 0xe
#define SCENE_29 0x29
#define SCENE_ACTOR_FOLLOWED 0x2c
#define SCENE_2D 0x2d
#define SCENE_2F 0x2f
/* The actor slots searched in scene 0x2c, and the value for none. */
#define FOLLOWED_SLOTS 8
/* The vtable slot of an actor asked whether the camera may follow it there. */
#define ACTOR_SLOT_CAMERA_FOLLOWS 42
/* The camera's own vtable slot of its draw (CameraControl_Draw). */
#define CAMERA_SLOT_DRAW 9
/* The flag of the player's record tested in the town. */
#define RECORD_FLAG_23 0x23
/* The preset loaded by CameraControl_SetPresetPoint. */
#define POINT_PRESET 0xb

/* func_0203bc50: the goal's second offset (the point followed) taken to `point`'s height and,
 * when farther than the follow radius from it in the ground plane, pulled to that radius. */
void CameraControl_Follow(CameraControl *camera, const Vec3 *point)
{
    Vec3 *followed = &camera->goal.second_offset;
    followed->y = point->y;
    Vec3 away;
    Vec_Subtract(&away, followed, point);
    fx32 distance = Vec_LengthXZ(&away);
    if (distance > (fx32) CameraControl_FollowRadius(camera)) {
        distance -= (fx32) CameraControl_FollowRadius(camera);
        if (Vec_NormalizeNonZero(&away)) {
            followed->x -= FX_MulFunc(away.x, distance);
            followed->z -= FX_MulFunc(away.z, distance);
        }
    }
}
CLEAN_AS(func_0203bc50, CameraControl_Follow)

/* func_0203bcc4: the camera placed to look from `eye` at `target`, both bent onto the curved
 * ground; the up vector leans by the ground's angle under the target, then turns by the roll. */
void CameraControl_PlaceAt(CameraControl *camera, const Vec3 *target, const Vec3 *eye)
{
    int angle = func_0203f844(&camera->drawn_target, target);
    func_0203f844(&camera->drawn_eye, eye);
    int index = (u16) angle >> 4;
    camera->up.x = 0;
    camera->up.y = FX_SinCosTable_[index * 2 + 1];
    camera->up.z = FX_SinCosTable_[index * 2];
    Vec_RotateZ(&camera->up, camera->roll);
    data_021c67d0 = *target;
    data_021c67b8 = *eye;
    Vec3 between;
    Vec_Subtract(&between, target, eye);
    data_021c679c = VEC_Mag(&between);
}
CLEAN_AS(func_0203bcc4, CameraControl_PlaceAt)

/* func_0203bd84: the eye (`point`) placed `distance` behind `target`, turned up by `pitch` and
 * round by `yaw`; both bent onto the curved ground, the up vector leaning by the ground's angle
 * under the target and turned by the roll. */
void CameraControl_Place(CameraControl *camera, const Vec3 *target, int pitch, int yaw, int distance)
{
    Vec3 behind = {0, 0, distance};
    Vec_RotateX(&behind, (s16) -pitch);
    Vec_RotateY(&behind, yaw);
    Vec3 eye;
    Vec_Add(&eye, target, &behind);
    camera->point = eye;
    int angle = func_0203f844(&camera->drawn_target, target);
    func_0203f844(&camera->drawn_eye, CameraControl_Eye(camera));
    camera->up.x = 0;
    camera->up.y = 0x1000;
    camera->up.z = 0;
    Vec_RotateX(&camera->up, angle);
    Vec_RotateZ(&camera->up, camera->roll);
    data_021c67d0 = *target;
    data_021c67b8 = *CameraControl_Eye(camera);
    data_021c679c = distance;
}
CLEAN_AS(func_0203bd84, CameraControl_Place)

/* `*value` moved `share` of the way to `to`. */
static void ease_point(Vec3 *value, const Vec3 *to, fx32 share)
{
    Vec3 step;
    Vec_Subtract(&step, to, value);
    Vec_Scale(&step, share);
    Vec3 moved;
    Vec_Add(&moved, value, &step);
    *value = moved;
}

/* func_0203be6c: while the move lasts, the current view eased towards the goal by the share of
 * the move done (one frame more each call); after it, the goal copied. 0x1e8 follows 0x1e4 the
 * same way. */
void CameraControl_Ease(CameraControl *camera)
{
    if (CameraControl_IsMoving()) {
        fx32 delay = CameraControl_Delay(camera);
        fx32 length = CameraControl_MoveLength(camera);
        fx32 ease_in = CameraControl_EaseIn(camera);
        fx32 ease_out = CameraControl_EaseOut(camera);
        fx32 share = func_020643dc(camera->move_time, delay, length, ease_in, ease_out);
        ease_point(&camera->current.second_offset, &camera->goal.second_offset, share);
        ease_point(&camera->current.offset, &camera->goal.offset, share);
        camera->current.pitch = (s16) (camera->current.pitch + FX_MulFunc(camera->goal.pitch - camera->current.pitch, share));
        camera->current.yaw = (s16) (camera->current.yaw + FX_MulFunc(camera->goal.yaw - camera->current.yaw, share));
        camera->current.distance += FX_MulFunc(camera->goal.distance - camera->current.distance, share);
        camera->unk_1e8 += FX_MulFunc(camera->unk_1e4 - camera->unk_1e8, share);
        camera->move_time += 0x1000;
    } else {
        camera->current.second_offset = camera->goal.second_offset;
        camera->current.offset = camera->goal.offset;
        camera->current.pitch = camera->goal.pitch;
        camera->current.yaw = camera->goal.yaw;
        camera->current.distance = camera->goal.distance;
        camera->unk_1e8 = camera->unk_1e4;
    }
}
CLEAN_AS(func_0203be6c, CameraControl_Ease)

/* func_0203c030: the projection set to 4:3 (1.33), from 0.06 to 250.0, with the field of view
 * kept. */
void CameraControl_ResetProjection(CameraControl *camera)
{
    camera->aspect = 0x1548;
    camera->near_distance = 0xf6;
    camera->far_distance = 0x3e800;
    CameraControl_SetFov(camera, camera->fov);
}
CLEAN_AS(func_0203c030, CameraControl_ResetProjection)

/* func_0203c068: the mode's frame run, then the ground's angle under the eye updated. */
void CameraControl_RunMode(CameraControl *camera)
{
    int mode = camera->mode;
    if (mode < CAMERA_MODES) {
        MemberPointer_CallVoid(&data_021c6820[mode].frame, camera);
        CameraControl_UpdateGroundAngle(camera);
    }
}
CLEAN_AS(func_0203c068, CameraControl_RunMode)

/* func_0203c0ac: the camera switched to `mode` if the mode's start allows it, with the projection
 * reset and the mode's first frame run; whether it was. Leaving a mode for another remembers the
 * mode left and, unless the new one is the mode the camera was created in, saves the goal view
 * and the eye. The saved flag is cleared whatever the answer.
 * REQUIRES: mode >= 0 (below 21 is checked). */
int CameraControl_SetMode(CameraControl *camera, int mode)
{
    if (mode >= CAMERA_MODES) {
        return 0;
    }
    if (mode != camera->mode) {
        camera->previous_mode = camera->mode;
        if (mode != camera->initial_mode) {
            camera->saved = camera->goal;
            camera->saved_point = camera->point;
        }
    }
    camera->view_saved = 0;
    if (!MemberPointer_CallInt(&data_021c6820[mode].start, camera)) {
        return 0;
    }
    CameraControl_ResetProjection(camera);
    camera->mode = mode;
    CameraControl_RunMode(camera);
    return 1;
}
CLEAN_AS(func_0203c0ac, CameraControl_SetMode)

/* func_0203c1e0: 1 when `point` is within the margin of the room's left wall, 2 of its right
 * wall, else 0. */
int CameraControl_RoomEdgeX(CameraControl *camera, const Vec3 *point)
{
    fx32 x = point->x;
    if (x < camera->room_min_x + ROOM_MARGIN) {
        return 1;
    }
    if (x > camera->room_max_x - ROOM_MARGIN) {
        return 2;
    }
    return 0;
}
CLEAN_AS(func_0203c1e0, CameraControl_RoomEdgeX)

/* func_0203c210: the goal set to preset 11 and the second offset of `view` (the goal when NULL)
 * to `point`.
 * QUIRK: the preset always goes to the goal, whatever `view` is. */
void CameraControl_SetPresetPoint(CameraControl *camera, CameraView *view, const Vec3 *point)
{
    if (view == NULL) {
        view = &camera->goal;
    }
    CameraControl_LoadPreset(camera, POINT_PRESET, NULL);
    view->second_offset = *point;
}
CLEAN_AS(func_0203c210, CameraControl_SetPresetPoint)

/* One axis of CameraControl_ClampToRoom: `*value` kept between `low` and `high`, or put midway
 * between the walls when they are `narrow` or less apart; whether it was set. */
static int clamp_axis(fx32 *value, fx32 min, fx32 max, fx32 narrow, fx32 low, fx32 high)
{
    if (max - min <= narrow) {
        *value = (max + min) >> 1;
        return 1;
    }
    if (*value < low) {
        *value = low;
        return 1;
    }
    if (*value > high) {
        *value = high;
        return 1;
    }
    return 0;
}

/* func_0203c23c: `point` kept inside the room in x and z, a margin from the walls (less from the
 * front in z), or midway when the room is too narrow for both margins; whether it was moved.
 * QUIRK: a point already midway in a narrow room counts as moved. */
int CameraControl_ClampToRoom(CameraControl *camera, Vec3 *point)
{
    int changed = 0;
    fx32 min = camera->room_min_x;
    fx32 max = camera->room_max_x;
    changed |= clamp_axis(&point->x, min, max, 2 * ROOM_MARGIN, min + ROOM_MARGIN, max - ROOM_MARGIN);
    min = camera->room_min_z;
    max = camera->room_max_z;
    changed |= clamp_axis(&point->z, min, max, ROOM_FRONT_MARGIN + ROOM_MARGIN, min + ROOM_FRONT_MARGIN, max - ROOM_MARGIN);
    return changed;
}
CLEAN_AS(func_0203c23c, CameraControl_ClampToRoom)

/* func_0203c2d4: indoors, the room's bounds from its floor tiles, at least an acre deep; then in
 * scene 0x29 the bounds widened by 4.0 at the right and the front, elsewhere narrowed by 2.0 on
 * one side or both by the model of the map's first acre.
 * QUIRK: with no acre the model is asked of NULL. */
void CameraControl_SetRoomBounds(CameraControl *camera)
{
    if (data_021f6948->outdoors == 0) {
        func_02030738(&camera->room_min_x, &camera->room_max_x, &camera->room_min_z, &camera->room_max_z);
        if (camera->room_max_z < data_020ca0e8) {
            camera->room_max_z = data_020ca0e8;
        }
    }
    if (func_020b65c4() == SCENE_29) {
        camera->room_max_x += 0x4000;
        camera->room_max_z += 0x4000;
        return;
    }
    const AcreRecord *acre = NULL;
    if (data_021c80bc->acres_wide != 0 && data_021c80bc->acres_high != 0 && data_021c80bc->acres != NULL) {
        acre = (const AcreRecord *) data_021c80bc->acres;
    }
    switch (AcreRecord_Model(acre)) {
        case 0x1009:
        case 0x100c:
            camera->room_min_x += 0x2000;
            break;
        case 0x100a:
            camera->room_max_x -= 0x2000;
            break;
        case 0x100b:
        case 0x100d:
            camera->room_min_x += 0x2000;
            camera->room_max_x -= 0x2000;
            break;
        default:
            break;
    }
}
CLEAN_AS(func_0203c2d4, CameraControl_SetRoomBounds)

/* func_0203c3c4: the acre the point looked at is in (32.0 to an acre). */
void CameraControl_TargetAcre(CameraControl *camera, int *x, int *z)
{
    Vec3 target;
    Camera_GetTarget(&target, (Camera *) camera);
    *x = target.x >> 17;
    *z = target.z >> 17;
}
CLEAN_AS(func_0203c3c4, CameraControl_TargetAcre)

/* func_0203c3ec */
void CameraControl_UpdateGroundAngle(CameraControl *camera)
{
    camera->ground_angle = func_0203f768(&camera->drawn_eye);
}
CLEAN_AS(func_0203c3ec, CameraControl_UpdateGroundAngle)

/* func_0203c40c: the field of view set to `fov`; with its adjustment, the sine and cosine of half
 * of it and their ratio (the projection's scale), and the frustum the actors are culled against
 * set up the same way. */
void CameraControl_SetFov(CameraControl *camera, s16 fov)
{
    camera->fov = fov;
    s16 total = (s16) (camera->fov + camera->extra_fov);
    int index = (u16) (total >> 1) >> 4;
    camera->half_fov_sin = FX_SinCosTable_[index * 2];
    camera->half_fov_cos = FX_SinCosTable_[index * 2 + 1];
    camera->projection = (u32) FX_MulFunc(camera->half_fov_sin, FX_InvA(camera->half_fov_cos));
    ViewFrustum_Set(&data_021f6a6c, camera->aspect, (u16) (s16) (camera->fov + camera->extra_fov),
                    camera->near_distance + camera->extra_near, camera->far_distance + camera->extra_far);
}
CLEAN_AS(func_0203c40c, CameraControl_SetFov)

/* func_0203c4bc: the move's ease out with its adjustment, at least 0. */
int CameraControl_EaseOut(CameraControl *camera)
{
    int ease_out = camera->ease_out + camera->extra_ease_out;
    return ease_out < 0 ? 0 : ease_out;
}
CLEAN_AS(func_0203c4bc, CameraControl_EaseOut)

/* func_0203c4d0: the move's ease in with its adjustment, at least 0. */
int CameraControl_EaseIn(CameraControl *camera)
{
    int ease_in = camera->ease_in + camera->extra_ease_in;
    return ease_in < 0 ? 0 : ease_in;
}
CLEAN_AS(func_0203c4d0, CameraControl_EaseIn)

/* func_0203c4e4: the move's length: the length (raised for good to the delay and both eases
 * together if shorter) with its adjustment, but never less than the three. */
int CameraControl_MoveLength(CameraControl *camera)
{
    int ease_out = CameraControl_EaseOut(camera);
    int delay = CameraControl_Delay(camera);
    int ease_in = CameraControl_EaseIn(camera);
    int least = ease_out + (delay + ease_in);
    if (camera->unk_bc < least) {
        camera->unk_bc = least;
    }
    int length = camera->unk_bc + camera->extra_length;
    return length < least ? least : length;
}
CLEAN_AS(func_0203c4e4, CameraControl_MoveLength)

/* func_0203c528: the move's delay with its adjustment, at least 0. */
int CameraControl_Delay(CameraControl *camera)
{
    int delay = camera->unk_b8 + camera->extra_delay;
    return delay < 0 ? 0 : delay;
}
CLEAN_AS(func_0203c528, CameraControl_Delay)

/* func_0203c53c */
u32 CameraControl_Projection(CameraControl *camera)
{
    return camera->projection;
}
CLEAN_AS(func_0203c53c, CameraControl_Projection)

/* func_0203c548: the current view's distance with its adjustment. */
int CameraControl_Distance(CameraControl *camera)
{
    return camera->current.distance + camera->extra_distance;
}
CLEAN_AS(func_0203c548, CameraControl_Distance)

/* func_0203c558: how far the point followed may stay from the player (0.94) with its
 * adjustment. */
u32 CameraControl_FollowRadius(CameraControl *camera)
{
    return (u32) camera->extra_follow_radius + 0xf0a;
}
CLEAN_AS(func_0203c558, CameraControl_FollowRadius)

/* func_0203c568: the current view's yaw with its adjustment. */
s16 CameraControl_Yaw(CameraControl *camera)
{
    return (s16) (camera->current.yaw + camera->extra_yaw);
}
CLEAN_AS(func_0203c568, CameraControl_Yaw)

/* func_0203c57c: the current view's pitch with its adjustment. */
s16 CameraControl_Pitch(CameraControl *camera)
{
    return (s16) (camera->current.pitch + camera->extra_pitch);
}
CLEAN_AS(func_0203c57c, CameraControl_Pitch)

/* func_0203c590 */
s16 CameraControl_GroundAngle(CameraControl *camera)
{
    return camera->ground_angle;
}
CLEAN_AS(func_0203c590, CameraControl_GroundAngle)

/* func_0203c59c: the eye (`point`). */
Vec3 *CameraControl_Eye(CameraControl *camera)
{
    return &camera->point;
}
CLEAN_AS(func_0203c59c, CameraControl_Eye)

/* func_0203c5a8: the adjustments cleared (all but the word at 0xa4). */
void CameraControl_ClearAdjustments(CameraControl *camera)
{
    camera->extra_distance = 0;
    camera->extra_pitch = 0;
    camera->extra_yaw = 0;
    camera->target_adjust.x = 0;
    camera->target_adjust.y = 0;
    camera->target_adjust.z = 0;
    camera->extra_fov = 0;
    camera->extra_near = 0;
    camera->extra_far = 0;
    camera->extra_follow_radius = 0;
    camera->extra_delay = 0;
    camera->extra_length = 0;
    camera->extra_ease_in = 0;
    camera->extra_ease_out = 0;
}
CLEAN_AS(func_0203c5a8, CameraControl_ClearAdjustments)

/* func_0203c600: the process's delete: there is no camera any more; done. */
int CameraControl_Delete(void)
{
    data_021c67a4 = NULL;
    return 1;
}
CLEAN_AS(func_0203c600, CameraControl_Delete)

/* func_0203c610: the process's draw: the projection and the view sent to the geometry engine
 * (the view matrix and its inverse kept), then G3D's projection (with the adjustments) and
 * camera set from the same vectors, its flags 0x50 and 0xe8 cleared after each.
 * HW: the first projection and view go to the geometry engine, in this order. */
void CameraControl_Draw(CameraControl *camera)
{
    int index = camera->fov >> 5;
    G3i_PerspectiveW_((unsigned int) FX_SinCosTable_[index * 2], (unsigned int) FX_SinCosTable_[index * 2 + 1],
                      (unsigned int) camera->aspect, (unsigned int) camera->near_distance, (unsigned int) camera->far_distance,
                      0x1000, 1, NULL);
    G3i_LookAt_(&camera->drawn_eye, &camera->up, &camera->drawn_target, 1, &camera->view_matrix);
    MTX_Inverse43(&camera->view_matrix, &camera->inverse_view);
    s16 fov = (s16) (camera->fov + camera->extra_fov);
    index = fov >> 5;
    G3i_PerspectiveW_((unsigned int) FX_SinCosTable_[index * 2], (unsigned int) FX_SinCosTable_[index * 2 + 1],
                      (unsigned int) camera->aspect, (unsigned int) (camera->near_distance + camera->extra_near),
                      (unsigned int) (camera->far_distance + camera->extra_far), 0x1000, 0, data_027e00d0);
    data_027e0148.flags &= ~0x50u;
    data_027e02c8.position = camera->drawn_eye;
    data_027e02c8.up = camera->up;
    data_027e02c8.target = camera->drawn_target;
    G3i_LookAt_(&camera->drawn_eye, &camera->up, &camera->drawn_target, 0, data_027e0114);
    data_027e0148.flags &= ~0xe8u;
    func_020b9464(camera);
}
CLEAN_AS(func_0203c610, CameraControl_Draw)

/* func_0203c76c: the process's execute: the mode's frame, then the point looked at handed to
 * func_0203f684; done. */
int CameraControl_Execute(CameraControl *camera)
{
    CameraControl_RunMode(camera);
    Vec3 target;
    Camera_GetTarget(&target, (Camera *) camera);
    func_0203f684(data_021c749c, &target);
    return 1;
}
CLEAN_AS(func_0203c76c, CameraControl_Execute)

/* The actor the camera follows in scene 0x2c, NULL for none: after the last one followed
 * (data_020da714) the next slot whose actor agrees (its vtable slot 42), going round from slot
 * 0; with none followed before, the one func_0208258c picks. The slot reached is kept.
 * QUIRK: the search stops at slot 8 (back to 0) without going round to the slots before; and an
 * actor that did not agree is still the answer when the search ends on it. */
static void *followed_actor(void)
{
    void *actor = NULL;
    int slot = data_020da714;
    if (slot == FOLLOWED_SLOTS) {
        return ActorEntries_PickGameE(&data_020da714);
    }
    slot++;
    if (slot == FOLLOWED_SLOTS) {
        slot = 0;
    } else {
        while (slot != data_020da714) {
            actor = Actors_SlotE(slot);
            if (actor != NULL) {
                const u32 *vtable = *(const u32 *const *) actor;
                int (*agrees)(void *) = (int (*)(void *))(uintptr_t) vtable[ACTOR_SLOT_CAMERA_FOLLOWS];
                if (agrees(actor)) {
                    break;
                }
            }
            slot++;
            if (slot == FOLLOWED_SLOTS) {
                slot = 0;
                break;
            }
        }
    }
    data_020da714 = slot;
    return actor;
}

/* func_0203c794: the process's create: the camera made the current one, with its adjustments
 * cleared, the middle preset (row 1, column 1), a field of view of 30 degrees, mode 0 started
 * (the point followed put at the player); the room's bounds set up; the scale of z set for the
 * scene; the scene's own mode started; the camera drawn once and the moves ended; done. */
int CameraControl_Create(CameraControl *camera)
{
    data_021c67a4 = camera;
    CameraControl_ClearAdjustments(camera);
    camera->preset_column = 1;
    camera->preset_row = 1;
    camera->fov = 0x1555;
    camera->unk_1e4 = 0;
    camera->unk_1e8 = 0;
    camera->previous_mode = CAMERA_MODE_FOLLOW;
    camera->mode = camera->previous_mode;
    if (CameraControl_SetMode(camera, CAMERA_MODE_FOLLOW)) {
        Vec3 *player = func_02095794(PLAYER);
        if (player != NULL) {
            camera->goal.second_offset = *player;
        }
    }
    CameraControl_SetRoomBounds(camera);
    int scene = func_020b65c4();
    data_020da718 = scene == SCENE_9 ? 0x1000 : 0x1800;
    switch (scene) {
        case SCENE_ACTOR_FOLLOWED: {
            void *actor = followed_actor();
            if (actor != NULL) {
                ((CameraControlModeData *) &camera->unk_21c)->actor = actor;
                CameraControl_SetMode(camera, CAMERA_MODE_7);
            } else {
                data_020da714 = FOLLOWED_SLOTS;
                CameraControl_SetMode(camera, CAMERA_MODE_8);
            }
            break;
        }
        case SCENE_2D:
            CameraControl_SetMode(camera, CAMERA_MODE_9);
            break;
        case SCENE_6:
            CameraControl_SetMode(camera, CAMERA_MODE_10);
            break;
        case SCENE_13:
        case SCENE_14:
        case SCENE_2F:
            CameraControl_SetMode(camera, CAMERA_MODE_14);
            break;
        case SCENE_12:
            CameraControl_SetMode(camera, CAMERA_MODE_6);
            break;
        case SCENE_TOWN: {
            u8 *record = PlayerRecords_Current();
            if (record != NULL && PlayerRecord_TestFlag(record, RECORD_FLAG_23) &&
                (func_020b67e8(func_020b65b8()) || func_020b65b8() == SCENE_6)) {
                CameraControl_SetMode(camera, CAMERA_MODE_13);
            }
            break;
        }
        default:
            break;
    }
    void (*draw)(CameraControl *) = (void (*)(CameraControl *))(uintptr_t) ((const u32 *) camera->vtable)[CAMERA_SLOT_DRAW];
    draw(camera);
    camera->previous_mode = camera->mode;
    camera->initial_mode = camera->previous_mode;
    CameraControl_EndMove();
    return 1;
}
CLEAN_AS(func_0203c794, CameraControl_Create)

/* func_0203c97c */
void CameraControl_SetTiming(CameraControl *camera, const CameraTiming *timing)
{
    camera->unk_b8 = timing->delay;
    camera->unk_bc = timing->length;
    camera->ease_in = timing->ease_in;
    camera->ease_out = timing->ease_out;
}
CLEAN_AS(func_0203c97c, CameraControl_SetTiming)

/* func_0203c99c: the move's timing set to entry `index` of the game's table. */
void CameraControl_SelectTiming(CameraControl *camera, int index)
{
    CameraControl_SetTiming(camera, &data_020ca1ac[index]);
}
CLEAN_AS(func_0203c99c, CameraControl_SelectTiming)

/* func_0203c9b0: the goal view set `t` of the way from preset `from` to preset `to` (its second
 * offset kept); the angles' differences taken in 16 bits. */
void CameraControl_BlendPresets(CameraControl *camera, int from, int to, fx32 t)
{
    const CameraPreset *a = &data_020ca20c[from];
    const CameraPreset *b = &data_020ca20c[to];
    CameraView *goal = &camera->goal;
    Vec3 difference = {b->offset.x - a->offset.x, b->offset.y - a->offset.y, b->offset.z - a->offset.z};
    goal->offset = a->offset;
    fx32 distance = a->distance;
    goal->distance = distance;
    s16 pitch = a->pitch;
    goal->pitch = pitch;
    s16 yaw = a->yaw;
    goal->yaw = yaw;
    Vec3 step;
    Vec_ScaleCopy(&step, &difference, t);
    VEC_Add(&goal->offset, &step, &goal->offset);
    goal->distance += FX_MulFunc(b->distance - distance, t);
    goal->pitch += (s16) FX_MulFunc((s16) (b->pitch - pitch), t);
    goal->yaw += (s16) FX_MulFunc((s16) (b->yaw - yaw), t);
}
CLEAN_AS(func_0203c9b0, CameraControl_BlendPresets)

/* func_0203caa4: `view` (the goal when NULL) set to preset `index`, its second offset kept. */
void CameraControl_LoadPreset(CameraControl *camera, int index, CameraView *view)
{
    if (view == NULL) {
        view = &camera->goal;
    }
    const CameraPreset *preset = &data_020ca20c[index];
    view->offset = preset->offset;
    view->distance = preset->distance;
    view->pitch = preset->pitch;
    view->yaw = preset->yaw;
}
CLEAN_AS(func_0203caa4, CameraControl_LoadPreset)
