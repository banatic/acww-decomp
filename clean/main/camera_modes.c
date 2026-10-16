/* The field camera's modes run from main (camera_modes.h). */
#include "camera_modes.h"

#include "autoload_2/approach.h" /* Approach_S16, Approach_EaseS32MinMax */
#include "camera_control.h"
#include "camera_view.h"
#include "clean.h"
#include "itcm/camera.h" /* Camera_GetTarget */
#include "itcm/vector.h" /* Vec_Add */
#include "state_flags.h" /* StateFlags_ValueOrZero */

static_assert(sizeof(CameraControlModeData) == 8, "the mode's data");
static_assert(offsetof(CameraControl, unk_21c) == 0x21c, "the mode's data");

/* The camera, NULL when there is none. */
extern CameraControl *data_021c67a4;

/* Where the point followed goes when there is no player. */
extern Vec3 data_021fbee8;
/* The scale of z in CameraControl_SpanOfTwo. */
extern fx32 data_020da718;

/* The scene the camera is in (data_021f6948): byte 4 says whether outdoors (the town, overlay 3)
 * or indoors (a room, overlay 4). */
typedef struct CameraModesScene {
    u8 unk_00[4];
    u8 outdoors;
} CameraModesScene;
extern CameraModesScene *data_021f6948;

/* The table of presets the follow mode reads indoors, by row and column. */
extern const int data_020ca158[][3];

extern const s16 FX_SinCosTable_[];
extern fx32 FX_MulFunc(fx32 a, fx32 b);
extern fx32 VEC_Mag(const Vec3 *v);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *sum);
/* Reads the 3 x 3 part of `mtx`. */
extern void MTX_MultVec33(const Vec3 *vec, const Mtx43 *mtx, Vec3 *dst);

/* The player's position (actor 4, the one at this console), or NULL. */
extern Vec3 *func_02095794(int actor);
/* The point of the actor the player is turned to (overlay 3). */
Vec3 *FieldActor_PlayerFocus(int player);
/* The yaw from `from` towards `to`. */
s16 Vec_YawTo(const Vec3 *from, const Vec3 *to);
extern u8 func_020b65c4(void); /* the scene */
/* Whether the scene is one of the kinds these three test. */
extern int func_020b67d4(void);
extern int func_020b6680(void);
extern int func_020b66d8(void);
/* Mode 2's frame indoors (with the view it sets; NULL for the goal) and outdoors. */
extern void func_ov004_02247438(CameraControl *camera, CameraView *view);
extern void func_ov003_02236564(CameraControl *camera);
/* In mode 1 after mode 9: how much higher the point looked at goes (overlay 68). */
extern int func_ov068_0226dabc(CameraControl *camera);

#define PLAYER 4
/* Focus on points whose span with the player reaches 11.0 is not taken. */
#define FOCUS_SPAN 0xb000
/* A scene where the camera does not focus on a point. */
#define SCENE_NO_FOCUS 0xc
/* Scenes CameraControl_FollowFrame does not keep inside the room. */
#define SCENE_20 0x20
#define SCENE_22 0x22
/* The sound effects of starting and of leaving mode 2. */
#define SE_FOCUS 0x2f
#define SE_UNFOCUS 0x30
/* The presets and timings the modes start with; the first preset of a pair is indoors'. */
#define PRESET_OUTDOORS 0
#define PRESET_FOCUS_INDOORS 0xb
#define PRESET_FOCUS_OUTDOORS 0xa
#define PRESET_3_INDOORS 0x1c
#define PRESET_3_OUTDOORS 0x1b
#define PRESET_4_INDOORS 0xd
#define PRESET_4_OUTDOORS 0xc
#define PRESET_STILL_INDOORS 0xf
#define PRESET_STILL_OUTDOORS 0xe
#define PRESET_19 0x1f
#define TIMING_0 0
#define TIMING_STILL 1
#define TIMING_SAVED_VIEW 2
#define TIMING_3 3
#define TIMING_19 5
/* The shake's start and how it dies down. */
#define SHAKE_STEP 0x2000
#define SHAKE_STEP_GOAL 0x6000
#define SHAKE_STEP_RATE 0x180
#define SHAKE_EASE 0x400
#define SHAKE_EASE_MAX 0x80
#define SHAKE_EASE_MIN 0x10
/* In mode 5, how far past the player the camera looks, of the way to the actor (0.7). */
#define MODE_5_SHARE 0xb33

static CameraModesScene *scene(void)
{
    return data_021f6948;
}

/* The current view eased towards the goal, and the camera placed at the current view around the
 * point looked at. */
static void place(CameraControl *camera)
{
    CameraControl_Ease(camera);
    Vec3 target;
    Camera_GetTarget(&target, (Camera *) camera);
    int pitch = CameraControl_Pitch(camera);
    int yaw = CameraControl_Yaw(camera);
    int distance = CameraControl_Distance(camera);
    CameraControl_Place(camera, &target, pitch, yaw, distance);
}

/* The player's position, or data_021fbee8 without one. */
static Vec3 player_position(void)
{
    Vec3 position = data_021fbee8;
    Vec3 *player = func_02095794(PLAYER);
    if (player != NULL) {
        position = *player;
    }
    return position;
}

/* func_0203af08: mode 2, focused on the player, `a` and `b` together, unless their span reaches
 * 11.0: then back to mode 0. */
void CameraControl_FocusOnPair(const Vec3 *a, const Vec3 *b)
{
    int span = CameraControl_SpanOfThree(func_02095794(PLAYER), a, b, NULL, NULL);
    if (span >= FOCUS_SPAN) {
        CameraControl_ResetMode();
        return;
    }
    data_021c67a4->look_both = 1;
    data_021c67a4->look_at = *a;
    data_021c67a4->look_at2 = *b;
    CameraControl_SetMode(data_021c67a4, CAMERA_MODE_FOCUS);
}
CLEAN_AS(func_0203af08, CameraControl_FocusOnPair)

/* func_0203af80: mode 2, focused on the player and `point`, unless their span reaches 11.0
 * (then back to mode 0, with its answer); not in mode 9 nor in scene 12 (0). Otherwise whether
 * the camera switched. */
int CameraControl_FocusOn(const Vec3 *point)
{
    if (data_021c67a4->mode == CAMERA_MODE_9) {
        return 0;
    }
    if (func_020b65c4() == SCENE_NO_FOCUS) {
        return 0;
    }
    if (CameraControl_SpanOfTwo(func_02095794(PLAYER), point, NULL, NULL) >= FOCUS_SPAN) {
        return CameraControl_ResetMode();
    }
    data_021c67a4->look_both = 0;
    data_021c67a4->look_at = *point;
    return CameraControl_SetMode(data_021c67a4, CAMERA_MODE_FOCUS);
}
CLEAN_AS(func_0203af80, CameraControl_FocusOn)

/* func_0203affc: the larger side, in x or z, of the box around three points in the ground plane.
 * With `center`: the box's middle there, at the height midway between `a` and `b`; with
 * `half_depth` too, half of the box's depth in z. */
int CameraControl_SpanOfThree(const Vec3 *a, const Vec3 *b, const Vec3 *c, Vec3 *center, fx32 *half_depth)
{
    Vec3 min = *a;
    Vec3 max = *a;
    if (min.x > b->x) {
        min.x = b->x;
    } else {
        max.x = b->x;
    }
    if (min.z > b->z) {
        min.z = b->z;
    } else {
        max.z = b->z;
    }
    if (min.x > c->x) {
        min.x = c->x;
    }
    if (min.z > c->z) {
        min.z = c->z;
    }
    if (max.x < c->x) {
        max.x = c->x;
    }
    if (max.z < c->z) {
        max.z = c->z;
    }
    Vec3 size;
    Vec_Subtract(&size, &max, &min);
    int span = size.x > size.z ? size.x : size.z;
    if (center != NULL) {
        Vec3 sum;
        Vec_Add(&sum, &min, &max);
        Vec3 middle;
        Vec_ShiftRightCopy(&middle, &sum, 1);
        *center = middle;
        center->y = (a->y + b->y) >> 1;
        if (half_depth != NULL) {
            *half_depth = size.z >> 1;
        }
    }
    return span;
}
CLEAN_AS(func_0203affc, CameraControl_SpanOfThree)

/* func_0203b0b8: the distance between two points, z scaled by data_020da718. With `center`:
 * their middle there; with `half_depth` too, half of their distance in z. */
int CameraControl_SpanOfTwo(const Vec3 *a, const Vec3 *b, Vec3 *center, fx32 *half_depth)
{
    Vec3 difference;
    Vec_Subtract(&difference, a, b);
    Vec3 scaled = difference;
    scaled.z = FX_MulFunc(difference.z, data_020da718);
    int span = VEC_Mag(&scaled);
    if (center != NULL) {
        Vec3 sum;
        Vec_Add(&sum, a, b);
        Vec3 middle;
        Vec_ShiftRightCopy(&middle, &sum, 1);
        *center = middle;
        if (half_depth != NULL) {
            fx32 half = difference.z >> 1;
            *half_depth = half < 0 ? -half : half;
        }
    }
    return span;
}
CLEAN_AS(func_0203b0b8, CameraControl_SpanOfTwo)

/* func_0203b130: mode 1; whether the camera switched. */
int CameraControl_SetModeStill(void)
{
    return CameraControl_SetMode(data_021c67a4, CAMERA_MODE_STILL);
}
CLEAN_AS(func_0203b130, CameraControl_SetModeStill)

/* func_0203b144: back to mode 0; 1 when already there, 0 in mode 9 (which keeps the camera),
 * else whether the camera switched. */
int CameraControl_ResetMode(void)
{
    CameraControl *camera = data_021c67a4;
    int mode = camera->mode;
    if (mode == CAMERA_MODE_9) {
        return 0;
    }
    if (mode == CAMERA_MODE_FOLLOW) {
        return 1;
    }
    return CameraControl_SetMode(camera, CAMERA_MODE_FOLLOW);
}
CLEAN_AS(func_0203b144, CameraControl_ResetMode)

/* func_0203b174: mode 19's frame. */
void CameraControl_Mode19Frame(CameraControl *camera)
{
    place(camera);
}
CLEAN_AS(func_0203b174, CameraControl_Mode19Frame)

/* func_0203b1b4: mode 19's start: preset 31 and timing 5, the move restarted. */
int CameraControl_Mode19Start(CameraControl *camera)
{
    CameraControl_LoadPreset(camera, PRESET_19, NULL);
    CameraControl_SelectTiming(camera, TIMING_19);
    CameraControl_RestartMove();
    return 1;
}
CLEAN_AS(func_0203b1b4, CameraControl_Mode19Start)

/* func_0203b1d4: the shake's frame: the phase turns by its step, which speeds up towards 0x6000;
 * the goal follows the saved view's point; the shake's amplitude dies down; the camera is placed
 * and then the drawn eye and point looked at both moved along the camera's up vector by the
 * amplitude times the sine of the phase (taken before the amplitude died down). */
void CameraControl_ShakeFrame(CameraControl *camera)
{
    CameraControlModeData *data = (CameraControlModeData *) &camera->unk_21c;
    data->shake.phase = (s16) (data->shake.phase + data->shake.phase_step);
    Approach_S16(&data->shake.phase_step, SHAKE_STEP_GOAL, SHAKE_STEP_RATE);
    fx32 lift = FX_MulFunc(FX_SinCosTable_[((u16) data->shake.phase >> 4) * 2], data->shake.amplitude);
    CameraControl_Follow(camera, &camera->saved.second_offset);
    Approach_EaseS32MinMax(&data->shake.amplitude, 0, SHAKE_EASE, SHAKE_EASE_MAX, SHAKE_EASE_MIN);
    place(camera);
    Vec3 up = {0, 0x1000, 0};
    MTX_MultVec33(&up, &camera->inverse_view, &up);
    Vec_Scale(&up, lift);
    VEC_Add(&camera->drawn_eye, &up, &camera->drawn_eye);
    VEC_Add(&camera->drawn_target, &up, &camera->drawn_target);
}
CLEAN_AS(func_0203b1d4, CameraControl_ShakeFrame)

/* func_0203b2b8: the shake's start (its amplitude is set by CameraControl_SetMode17): the phase
 * at 0 turning by 0x2000, the move ended. */
int CameraControl_ShakeStart(CameraControl *camera)
{
    CameraControlModeData *data = (CameraControlModeData *) &camera->unk_21c;
    data->shake.phase = 0;
    data->shake.phase_step = SHAKE_STEP;
    CameraControl_EndMove();
    return 1;
}
CLEAN_AS(func_0203b2b8, CameraControl_ShakeStart)

/* func_0203b2dc: mode 6's frame: the kept view loaded again, the camera placed. */
void CameraControl_Mode6Frame(CameraControl *camera)
{
    CameraControl_LoadKeptView();
    place(camera);
}
CLEAN_AS(func_0203b2dc, CameraControl_Mode6Frame)

/* func_0203b320: mode 6's start: the kept view loaded, the move ended. */
int CameraControl_Mode6Start(void)
{
    CameraControl_LoadKeptView();
    CameraControl_EndMove();
    return 1;
}
CLEAN_AS(func_0203b320, CameraControl_Mode6Start)

/* func_0203b334: mode 5's frame: with both the player and the actor FieldActor_PlayerFocus
 * gives, the point followed is 0.7 of their distance in the ground plane from the player, in the
 * actor's direction; else data_021fbee8. */
void CameraControl_Mode5Frame(CameraControl *camera)
{
    Vec3 point = data_021fbee8;
    Vec3 *player = func_02095794(PLAYER);
    Vec3 *focus = FieldActor_PlayerFocus(PLAYER);
    if (player != NULL && focus != NULL) {
        Vec3 between;
        Vec_Subtract(&between, player, focus);
        fx32 distance = Vec_LengthXZ(&between);
        int yaw = Vec_YawTo(player, focus);
        distance = FX_MulFunc(distance, MODE_5_SHARE);
        point = *player;
        int index = (u16) yaw >> 4;
        point.x += FX_MulFunc(distance, FX_SinCosTable_[index * 2]);
        point.z += FX_MulFunc(distance, FX_SinCosTable_[index * 2 + 1]);
    }
    CameraControl_Follow(camera, &point);
    place(camera);
}
CLEAN_AS(func_0203b334, CameraControl_Mode5Frame)

/* func_0203b40c: mode 5's start: preset 0 and timing 0, the move restarted. */
int CameraControl_Mode5Start(CameraControl *camera)
{
    CameraControl_LoadPreset(camera, PRESET_OUTDOORS, NULL);
    CameraControl_SelectTiming(camera, TIMING_0);
    CameraControl_RestartMove();
    return 1;
}
CLEAN_AS(func_0203b40c, CameraControl_Mode5Start)

/* func_0203b42c: mode 4's frame: the point followed put at the player, the camera placed. */
void CameraControl_Mode4Frame(CameraControl *camera)
{
    camera->goal.second_offset = player_position();
    place(camera);
}
CLEAN_AS(func_0203b42c, CameraControl_Mode4Frame)

/* func_0203b4b4: mode 4's start: preset 13 (12 outdoors) and timing 0, the move restarted, 0x1e4
 * set to 1.0. */
int CameraControl_Mode4Start(CameraControl *camera)
{
    CameraControl_LoadPreset(camera, scene()->outdoors == 0 ? PRESET_4_INDOORS : PRESET_4_OUTDOORS, NULL);
    CameraControl_SelectTiming(camera, TIMING_0);
    CameraControl_RestartMove();
    camera->unk_1e4 = 0x1000;
    return 1;
}
CLEAN_AS(func_0203b4b4, CameraControl_Mode4Start)

/* func_0203b4fc: mode 3's frame, as mode 4's. */
void CameraControl_Mode3Frame(CameraControl *camera)
{
    camera->goal.second_offset = player_position();
    place(camera);
}
CLEAN_AS(func_0203b4fc, CameraControl_Mode3Frame)

/* func_0203b584: mode 3's start: preset 28 (27 outdoors) and timing 3, the move restarted. */
int CameraControl_Mode3Start(CameraControl *camera)
{
    CameraControl_LoadPreset(camera, scene()->outdoors == 0 ? PRESET_3_INDOORS : PRESET_3_OUTDOORS, NULL);
    CameraControl_SelectTiming(camera, TIMING_3);
    CameraControl_RestartMove();
    return 1;
}
CLEAN_AS(func_0203b584, CameraControl_Mode3Start)

/* func_0203b5bc: mode 2's frame: the goal set by the room's or the town's overlay, the camera
 * placed. */
void CameraControl_FocusFrame(CameraControl *camera)
{
    if (scene()->outdoors == 0) {
        func_ov004_02247438(camera, NULL);
    } else {
        func_ov003_02236564(camera);
    }
    place(camera);
}
CLEAN_AS(func_0203b5bc, CameraControl_FocusFrame)

/* func_0203b618: mode 2's start: preset 11 (with 0x1f6 set to 3 and the room's goal set at once)
 * or outdoors preset 10 (and the town's goal), timing 0, the move ended when coming from mode 1
 * else restarted, and the focus sound played. */
int CameraControl_FocusStart(CameraControl *camera)
{
    if (scene()->outdoors == 0) {
        CameraControl_LoadPreset(camera, PRESET_FOCUS_INDOORS, NULL);
        camera->unk_1f6 = 3;
        func_ov004_02247438(camera, NULL);
    } else {
        CameraControl_LoadPreset(camera, PRESET_FOCUS_OUTDOORS, NULL);
        func_ov003_02236564(camera);
    }
    CameraControl_SelectTiming(camera, TIMING_0);
    if (camera->previous_mode == CAMERA_MODE_STILL) {
        CameraControl_EndMove();
    } else {
        CameraControl_RestartMove();
    }
    CameraControl_PlaySound(camera, SE_FOCUS);
    return 1;
}
CLEAN_AS(func_0203b618, CameraControl_FocusStart)

/* func_0203b684: mode 1's frame. With no view saved, the camera stays where it is, the eye put
 * back on its sphere around the point looked at while a move lasts; both are raised as
 * StateFlags_ValueOrZero falls below 1.0 (the point 15 times, the eye twice as far), the point
 * more after mode 9 (overlay 68), and the camera placed at them. With a view saved, the point
 * followed is put at the player and the camera placed. */
void CameraControl_StillFrame(CameraControl *camera)
{
    Vec3 player = player_position();
    if (camera->view_saved != 0) {
        camera->goal.second_offset = player;
        place(camera);
        return;
    }
    CameraControl_Ease(camera);
    Vec3 target;
    Camera_GetTarget(&target, (Camera *) camera);
    Vec3 eye = *CameraControl_Eye(camera);
    if (CameraControl_IsMoving()) {
        Vec3 behind = {0, 0, CameraControl_Distance(camera)};
        Vec_RotateX(&behind, (s16) -CameraControl_Pitch(camera));
        Vec_RotateY(&behind, CameraControl_Yaw(camera));
        Vec3 placed;
        Vec_Add(&placed, &target, &behind);
        eye = placed;
    }
    target.y += (0x1000 - StateFlags_ValueOrZero()) * 15;
    eye.y += (0x1000 - StateFlags_ValueOrZero()) * 2;
    if (camera->previous_mode == CAMERA_MODE_9) {
        target.y += func_ov068_0226dabc(camera);
    }
    CameraControl_PlaceAt(camera, &target, &eye);
}
CLEAN_AS(func_0203b684, CameraControl_StillFrame)

/* func_0203b7d0: mode 1's start. With no view saved: the point looked at and the eye kept, the
 * move ended. With one: preset 15 (14 outdoors) and timing 1, the move restarted. */
int CameraControl_StillStart(CameraControl *camera)
{
    if (camera->view_saved == 0) {
        Vec3 target;
        Camera_GetTarget(&target, (Camera *) camera);
        camera->fixed_target = target;
        camera->fixed_eye = *CameraControl_Eye(camera);
        CameraControl_EndMove();
    } else {
        CameraControl_LoadPreset(camera, scene()->outdoors == 0 ? PRESET_STILL_INDOORS : PRESET_STILL_OUTDOORS, NULL);
        CameraControl_SelectTiming(camera, TIMING_STILL);
        CameraControl_RestartMove();
    }
    return 1;
}
CLEAN_AS(func_0203b7d0, CameraControl_StillStart)

/* func_0203b868: the saved view put back: mode 1's start run with no view saved, then the goal
 * and the eye set to the saved ones, the point followed and the eye kept, the move restarted
 * with timing 2. */
void CameraControl_PutSavedViewBack(CameraControl *camera)
{
    camera->view_saved = 0;
    CameraControl_StillStart(camera);
    camera->goal = camera->saved;
    camera->point = camera->saved_point;
    camera->fixed_target = camera->goal.second_offset;
    camera->fixed_eye = camera->point;
    CameraControl_RestartMove();
    CameraControl_SelectTiming(camera, TIMING_SAVED_VIEW);
}
CLEAN_AS(func_0203b868, CameraControl_PutSavedViewBack)

/* func_0203b994: the goal view and the eye saved, then mode 1's start run with the view saved. */
void CameraControl_SaveGoalView(CameraControl *camera)
{
    camera->view_saved = 1;
    camera->saved = camera->goal;
    camera->saved_point = camera->point;
    CameraControl_StillStart(camera);
}
CLEAN_AS(func_0203b994, CameraControl_SaveGoalView)

/* func_0203ba60: mode 0's frame. Outdoors the point followed trails the player within the follow
 * radius. Indoors it is put at the player and kept inside the room, except that in scenes of the
 * kinds func_020b67d4, func_020b6680 or func_020b66d8 (but not 0x20 or 0x22) test for, the
 * preset is first taken again from the table and the point kept inside only below row 0. */
void CameraControl_FollowFrame(CameraControl *camera)
{
    Vec3 player = player_position();
    if (scene()->outdoors != 0) {
        CameraControl_Follow(camera, &player);
    } else if (func_020b67d4() || func_020b6680() ||
               (func_020b66d8() && func_020b65c4() != SCENE_20 && func_020b65c4() != SCENE_22)) {
        CameraControl_LoadPreset(camera, data_020ca158[camera->preset_row][camera->preset_column], NULL);
        camera->goal.second_offset = player;
        if (camera->preset_row != 0) {
            CameraControl_ClampToRoom(camera, &camera->goal.second_offset);
        }
    } else {
        camera->goal.second_offset = player;
        CameraControl_ClampToRoom(camera, &camera->goal.second_offset);
    }
    place(camera);
}
CLEAN_AS(func_0203ba60, CameraControl_FollowFrame)

/* func_0203bb8c: mode 0's start: indoors the preset of the table's row and column (and coming
 * from mode 2, 0x1f5 cleared), outdoors preset 0; timing 0. Coming from modes 2, 4, 5, 6, 11,
 * 12, 16 or 18 the move restarts; from the others it ends, with 0x1e8 cleared. 0x1e4 is
 * cleared, and coming from mode 2 or 16 the unfocus sound plays. */
int CameraControl_FollowStart(CameraControl *camera)
{
    if (scene()->outdoors == 0) {
        if (camera->previous_mode == CAMERA_MODE_FOCUS) {
            camera->unk_1f5 = 0;
        }
        CameraControl_LoadPreset(camera, data_020ca158[camera->preset_row][camera->preset_column], NULL);
    } else {
        CameraControl_LoadPreset(camera, PRESET_OUTDOORS, NULL);
    }
    CameraControl_SelectTiming(camera, TIMING_0);
    switch (camera->previous_mode) {
        case 2:
        case 4:
        case 5:
        case 6:
        case 0xb:
        case 0xc:
        case 0x10:
        case 0x12:
            CameraControl_RestartMove();
            camera->unk_1e4 = 0;
            break;
        default:
            camera->unk_1e4 = 0;
            camera->unk_1e8 = 0;
            CameraControl_EndMove();
            break;
    }
    if (camera->previous_mode == CAMERA_MODE_FOCUS || camera->previous_mode == 0x10) {
        CameraControl_PlaySound(camera, SE_UNFOCUS);
    }
    return 1;
}
CLEAN_AS(func_0203bb8c, CameraControl_FollowStart)
