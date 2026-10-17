/* The field camera's modes run by overlay 4 (room_camera.h). */
#include "room_camera.h"

#include "clean.h"
#include "itcm/camera.h"           /* Camera_GetTarget */
#include "itcm/vector.h"           /* Vec_Add */
#include "main/actor.h"            /* Vec_YawTo */
#include "main/camera_modes.h"     /* CameraControl_SpanOfTwo */
#include "main/camera_view.h"      /* CameraControl_LoadPreset, CameraTiming, ... */
#include "main/main_random.h"      /* MainRandom_Below */
#include "main/player_actor_ops.h" /* PlayerActorOps_StartPosition */
#include "main/scene_query.h"      /* SceneQuery_Current */

static_assert(sizeof(RoomCameraSpot) == 0x24, "a spot of the show");
static_assert(offsetof(RoomCameraShow, choices) == 0x228 - 0x21c, "the show's choices");
static_assert(offsetof(RoomCameraShow, flags) == 0x22a - 0x21c, "the show's flags");

/* The camera, NULL when there is none. */
extern CameraControl *data_021c67a4;
/* The table of presets, by the camera's row and column. */
extern const int data_020ca158[][3];
/* Mode 10's point (the point followed when there is no player). */
extern Vec3 data_021fbee8;
/* Modes 14's and 15's point, (16.0, 0, 17.0) both. */
extern const Vec3 data_ov004_0224de64;
extern const Vec3 data_ov004_0224de70;

/* The show's views and timings: the view the show sets the camera at, the wide goal it then
 * moves to over 1080 frames (and goes to over 60 when the mode starts), and the close goal it
 * moves to over 2000 (the offsets are set by the overlay's static initialiser). */
extern CameraView data_ov004_0225698c; /* yaw 0x1b00, pitch 0x1000, distance 9.44 */
extern CameraView data_ov004_022569ac; /* pitch 0x1100, distance 20.06 */
extern CameraView data_ov004_022569cc; /* pitch -0x200, distance 6.63 */
extern const CameraTiming data_ov004_0225695c;
extern const CameraTiming data_ov004_0225696c;
extern const CameraTiming data_ov004_0225697c;
/* The show's fourteen spots. */
#define ROOM_CAMERA_SPOTS 14
extern const RoomCameraSpot data_ov004_022569ec[ROOM_CAMERA_SPOTS];

extern const s16 FX_SinCosTable_[];
extern fx32 FX_Div(fx32 numerator, fx32 denominator);
extern fx32 FX_MulFunc(fx32 a, fx32 b);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *sum);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *difference);

/* The player at this console. */
#define ROOM_CAMERA_PLAYER 4
/* The presets and timings the modes start with. */
#define ROOM_CAMERA_PRESET_10 0x11
#define ROOM_CAMERA_PRESET_15 0x1d
#define ROOM_CAMERA_PRESET_16 0x1e
#define ROOM_CAMERA_PRESET_LOOK_AT 0x20
#define ROOM_CAMERA_PRESET_FOCUS 0xb
#define ROOM_CAMERA_TIMING_0 0
#define ROOM_CAMERA_TIMING_15 4
/* The sound effect of starting mode 16 (the focus sound of main's mode 2). */
#define ROOM_CAMERA_SE_FOCUS 0x2f
/* In the show, the distance stops changing at 1.25. */
#define ROOM_CAMERA_SHOW_NEAREST 0x1400
/* The focus: the span with the player blended over 4.5 to 11.0, the most the yaw turns, how
 * far off the line to the target the camera may look past it, and the scene that always takes
 * side 1. */
#define ROOM_CAMERA_FOCUS_NEAR 0x4800
#define ROOM_CAMERA_FOCUS_FAR 0xb000
#define ROOM_CAMERA_FOCUS_TURN 0xe02
#define ROOM_CAMERA_FOCUS_SPREAD 0x2000
#define ROOM_CAMERA_FOCUS_SIDE_LIMIT 0x701
#define ROOM_CAMERA_FOCUS_SCENE 0x10

/* The four of Nook's shops (scene_query.h's 0x1a-0x1f): the last has two floors. */
#define ROOM_CAMERA_SCENE_NOOK_1 0x1a
#define ROOM_CAMERA_SCENE_NOOK_2 0x1b
#define ROOM_CAMERA_SCENE_NOOK_3 0x1c
#define ROOM_CAMERA_SCENE_NOOK_4 0x1d
#define ROOM_CAMERA_SCENE_NOOK_4_UP 0x1e

static RoomCameraShow *RoomCamera_show(CameraControl *camera)
{
    return (RoomCameraShow *) (void *) ((u8 *) camera + offsetof(CameraControl, unk_21c));
}

/* The current view eased towards the goal and the camera placed at it around the point looked
 * at. */
static void RoomCamera_place(CameraControl *camera)
{
    CameraControl_Ease(camera);
    Vec3 target;
    Camera_GetTarget(&target, (Camera *) camera);
    int pitch = CameraControl_Pitch(camera);
    int yaw = CameraControl_Yaw(camera);
    int distance = CameraControl_Distance(camera);
    CameraControl_Place(camera, &target, pitch, yaw, distance);
}

/* A 16-bit angle's size.
 * QUIRK: -0x8000 stays -0x8000. */
static int RoomCamera_abs16(int angle)
{
    return angle < 0 ? (s16) -angle : angle;
}

/* func_ov004_02246a74: the field camera's goal reset to the player (RoomCamera_ResetGoal);
 * 1. */
int RoomCamera_ResetGoalNow(void)
{
    return RoomCamera_ResetGoal(data_021c67a4);
}
CLEAN_AS(func_ov004_02246a74, RoomCamera_ResetGoalNow)

/* func_ov004_02246a84: the show from the start again: no turn, spot 0, not moving (2); the
 * goal the wide view and the current view the show's own, the slow timing, the move
 * restarted. */
void RoomCamera_SetShowViews(CameraControl *camera)
{
    RoomCameraShow *show = RoomCamera_show(camera);
    show->turn = 0;
    show->spot = 0;
    show->moving = 2;
    camera->goal = data_ov004_022569ac;
    camera->current = data_ov004_0225698c;
    CameraControl_SetTiming(camera, &data_ov004_0225695c);
    CameraControl_RestartMove();
}
CLEAN_AS(func_ov004_02246a84, RoomCamera_SetShowViews)

/* func_ov004_02246b6c: the next spot of the show, at random of those whose pair is not one of
 * the last two taken (one pair fewer half the time), and the goal taken there at once: its
 * second offset the spot less the first offset, its angles and distance the spot's. The first
 * two picks each leave a pair fewer to choose among.
 * REQUIRES: the slot is 0 or 1 and the spot picked is one of the fourteen (the game's choices
 * keep them so). */
void RoomCamera_PickShowSpot(CameraControl *camera)
{
    RoomCameraShow *show = RoomCamera_show(camera);
    show->turn = 0;
    if (MainRandom_Below(2) == 1) {
        show->spot = (s16) MainRandom_Below(show->choices - 2);
    } else {
        show->spot = (s16) MainRandom_Below(show->choices);
    }

    /* the spots of the pairs taken last are skipped over, the lower pair first */
    int excluded[2];
    if (show->previous[0] > show->previous[1]) {
        excluded[0] = show->previous[1];
        excluded[1] = show->previous[0];
    } else {
        excluded[0] = show->previous[0];
        excluded[1] = show->previous[1];
    }
    for (int i = 0; i < 2; i++) {
        if (excluded[i] != -1 && (show->spot >> 1) >= (excluded[i] >> 1)) {
            show->spot = (s16) (show->spot + 2);
        }
    }
    if (show->previous[show->slot] == -1) {
        show->choices = (s16) (show->choices - 2);
    }
    show->previous[show->slot] = show->spot;
    show->slot ^= 1;
    show->moving = 1;

    const RoomCameraSpot *spot = &data_ov004_022569ec[show->spot];
    camera->goal.second_offset = spot->position;
    VEC_Subtract(&camera->goal.second_offset, &camera->goal.offset, &camera->goal.second_offset);
    camera->goal.pitch = spot->pitch;
    camera->goal.yaw = spot->yaw;
    camera->goal.distance = spot->distance;
    CameraControl_EndMove();
}
CLEAN_AS(func_ov004_02246b6c, RoomCamera_PickShowSpot)

/* func_ov004_02246c7c: the goal the close view, reached over 2000 frames, the move
 * restarted. */
void RoomCamera_SetShowClose(CameraControl *camera)
{
    camera->goal = data_ov004_022569cc;
    CameraControl_SetTiming(camera, &data_ov004_0225697c);
    CameraControl_RestartMove();
}
CLEAN_AS(func_ov004_02246c7c, RoomCamera_SetShowClose)

/* func_ov004_02246cf4: mode 18's frame: while at a spot, the goal's second offset is put back
 * to the spot, the distance changes by the spot's step while it is over 1.25, and the yaw and
 * the turn go on by the spot's turn step; the second offset is moved by the spot's orbit offset
 * less that offset turned by the turn, so the camera turns about it. Then the camera is
 * placed. */
void RoomCamera_ShowFrame(CameraControl *camera)
{
    RoomCameraShow *show = RoomCamera_show(camera);
    if (show->moving == 1) {
        const RoomCameraSpot *spot = &data_ov004_022569ec[show->spot];
        Vec3 *second = &camera->goal.second_offset;
        *second = spot->position;
        VEC_Subtract(second, &camera->goal.offset, second);
        if (CameraControl_Distance(camera) > ROOM_CAMERA_SHOW_NEAREST) {
            camera->goal.distance += spot->distance_step;
        }
        camera->goal.yaw = (s16) (camera->goal.yaw + spot->turn_step);
        show->turn = (s16) (show->turn + spot->turn_step);
        Vec3 orbit = {spot->orbit_x, 0, spot->orbit_z};
        VEC_Add(second, &orbit, second);
        Vec_RotateY(&orbit, show->turn);
        VEC_Subtract(second, &orbit, second);
    }
    RoomCamera_place(camera);
}
CLEAN_AS(func_ov004_02246cf4, RoomCamera_ShowFrame)

/* func_ov004_02246de8: mode 18's start: no spot taken yet (fourteen to choose among), its two
 * flags cleared, the goal the wide view reached over 60 frames, the move restarted; 1. */
int RoomCamera_ShowStart(CameraControl *camera)
{
    RoomCameraShow *show = RoomCamera_show(camera);
    show->turn = 0;
    show->spot = -1;
    show->moving = 0;
    show->previous[0] = -1;
    show->previous[1] = -1;
    show->slot = 0;
    show->choices = ROOM_CAMERA_SPOTS;
    show->flags &= (u8) ~1;
    show->flags &= (u8) ~2;
    camera->goal = data_ov004_022569ac;
    CameraControl_SetTiming(camera, &data_ov004_0225696c);
    CameraControl_RestartMove();
    return 1;
}
CLEAN_AS(func_ov004_02246de8, RoomCamera_ShowStart)

/* func_ov004_02246e88: RoomCamera_SetShowViews of the field camera. */
void RoomCamera_ShowViews(void)
{
    RoomCamera_SetShowViews(data_021c67a4);
}
CLEAN_AS(func_ov004_02246e88, RoomCamera_ShowViews)

/* func_ov004_02246e98: RoomCamera_PickShowSpot of the field camera. */
void RoomCamera_ShowNextSpot(void)
{
    RoomCamera_PickShowSpot(data_021c67a4);
}
CLEAN_AS(func_ov004_02246e98, RoomCamera_ShowNextSpot)

/* func_ov004_02246ea8: RoomCamera_SetShowClose of the field camera. */
void RoomCamera_ShowClose(void)
{
    RoomCamera_SetShowClose(data_021c67a4);
}
CLEAN_AS(func_ov004_02246ea8, RoomCamera_ShowClose)

/* func_ov004_02246eb8: mode 18 (the show); whether the camera switched. */
int RoomCamera_SetModeShow(void)
{
    return CameraControl_SetMode(data_021c67a4, ROOM_CAMERA_MODE_SHOW);
}
CLEAN_AS(func_ov004_02246eb8, RoomCamera_SetModeShow)

/* func_ov004_02246ecc: mode 20 on `point` (kept as the point looked at); whether the camera
 * switched. */
int RoomCamera_SetModeLookAt(const Vec3 *point)
{
    data_021c67a4->look_at = *point;
    return CameraControl_SetMode(data_021c67a4, ROOM_CAMERA_MODE_LOOK_AT);
}
CLEAN_AS(func_ov004_02246ecc, RoomCamera_SetModeLookAt)

/* func_ov004_02246ef4: mode 20's frame: the goal's second offset at the point looked at, the
 * camera placed. */
void RoomCamera_LookAtFrame(CameraControl *camera)
{
    camera->goal.second_offset = camera->look_at;
    RoomCamera_place(camera);
}
CLEAN_AS(func_ov004_02246ef4, RoomCamera_LookAtFrame)

/* func_ov004_02246f64: mode 20's start: preset 0x20, reached at once; 1. */
int RoomCamera_LookAtStart(CameraControl *camera)
{
    CameraControl_LoadPreset(camera, ROOM_CAMERA_PRESET_LOOK_AT, NULL);
    CameraControl_EndMove();
    return 1;
}
CLEAN_AS(func_ov004_02246f64, RoomCamera_LookAtStart)

/* func_ov004_02246f7c: mode 15; whether the camera switched. */
int RoomCamera_SetMode15(void)
{
    return CameraControl_SetMode(data_021c67a4, ROOM_CAMERA_MODE_15);
}
CLEAN_AS(func_ov004_02246f7c, RoomCamera_SetMode15)

/* func_ov004_02246f90: mode 14; whether the camera switched. */
int RoomCamera_SetMode14(void)
{
    return CameraControl_SetMode(data_021c67a4, ROOM_CAMERA_MODE_14);
}
CLEAN_AS(func_ov004_02246f90, RoomCamera_SetMode14)

/* func_ov004_02246fa4: mode 15's frame: the goal's second offset at its point, the camera
 * placed. */
void RoomCamera_Mode15Frame(CameraControl *camera)
{
    camera->goal.second_offset = data_ov004_0224de70;
    RoomCamera_place(camera);
}
CLEAN_AS(func_ov004_02246fa4, RoomCamera_Mode15Frame)

/* func_ov004_02247008: mode 15's start: preset 0x1d and timing 4, the move restarted; 1. */
int RoomCamera_Mode15Start(CameraControl *camera)
{
    CameraControl_LoadPreset(camera, ROOM_CAMERA_PRESET_15, NULL);
    CameraControl_SelectTiming(camera, ROOM_CAMERA_TIMING_15);
    CameraControl_RestartMove();
    return 1;
}
CLEAN_AS(func_ov004_02247008, RoomCamera_Mode15Start)

/* func_ov004_02247028: mode 14's frame: the goal's second offset at its point, the camera
 * placed. */
void RoomCamera_Mode14Frame(CameraControl *camera)
{
    camera->goal.second_offset = data_ov004_0224de64;
    RoomCamera_place(camera);
}
CLEAN_AS(func_ov004_02247028, RoomCamera_Mode14Frame)

/* func_ov004_0224708c: mode 14's start: the preset of the camera's row and column and timing
 * 0, the move restarted; 1.
 * REQUIRES: the row and column are in the table (the game keeps them at 0-2). */
int RoomCamera_Mode14Start(CameraControl *camera)
{
    CameraControl_LoadPreset(camera, data_020ca158[camera->preset_row][camera->preset_column], NULL);
    CameraControl_SelectTiming(camera, ROOM_CAMERA_TIMING_0);
    CameraControl_RestartMove();
    return 1;
}
CLEAN_AS(func_ov004_0224708c, RoomCamera_Mode14Start)

/* func_ov004_022470cc: mode 16's frame: the goal's second offset half way between the player
 * and the point looked at, pushed back in z by half the gap in z between them; the camera
 * placed.
 * REQUIRES: the player has an actor. */
void RoomCamera_BetweenFrame(CameraControl *camera)
{
    Vec3 *player = PlayerActorOps_StartPosition(ROOM_CAMERA_PLAYER);
    Vec3 sum;
    Vec_Add(&sum, player, &camera->look_at);
    Vec3 middle;
    Vec_ShiftRightCopy(&middle, &sum, 1);
    camera->goal.second_offset = middle;
    int gap = player->z - camera->look_at.z;
    if (gap < 0) {
        gap = -gap;
    }
    camera->goal.second_offset.z += gap >> 1;
    RoomCamera_place(camera);
}
CLEAN_AS(func_ov004_022470cc, RoomCamera_BetweenFrame)

/* func_ov004_0224716c: mode 16's start: preset 0x1e and timing 0, the move restarted, the
 * focus sound played; 1.
 * QUIRK: the player's position is asked for and not used. */
int RoomCamera_BetweenStart(CameraControl *camera)
{
    PlayerActorOps_StartPosition(ROOM_CAMERA_PLAYER);
    CameraControl_LoadPreset(camera, ROOM_CAMERA_PRESET_16, NULL);
    CameraControl_SelectTiming(camera, ROOM_CAMERA_TIMING_0);
    CameraControl_RestartMove();
    CameraControl_PlaySound(camera, ROOM_CAMERA_SE_FOCUS);
    return 1;
}
CLEAN_AS(func_ov004_0224716c, RoomCamera_BetweenStart)

/* func_ov004_0224719c: mode 16 with `point` kept as the point looked at; whether the camera
 * switched (0 without a camera). */
int RoomCamera_SetModeBetween(const Vec3 *point)
{
    if (data_021c67a4 != NULL) {
        data_021c67a4->look_at = *point;
        return CameraControl_SetMode(data_021c67a4, ROOM_CAMERA_MODE_BETWEEN);
    }
    return 0;
}
CLEAN_AS(func_ov004_0224719c, RoomCamera_SetModeBetween)

/* func_ov004_022472ec: mode 12; whether the camera switched (0 without a camera). */
int RoomCamera_SetMode12(void)
{
    if (data_021c67a4 != NULL) {
        return CameraControl_SetMode(data_021c67a4, ROOM_CAMERA_MODE_12);
    }
    return 0;
}
CLEAN_AS(func_ov004_022472ec, RoomCamera_SetMode12)

/* func_ov004_0224730c: mode 11; whether the camera switched (0 without a camera). */
int RoomCamera_SetMode11(void)
{
    if (data_021c67a4 != NULL) {
        return CameraControl_SetMode(data_021c67a4, ROOM_CAMERA_MODE_11);
    }
    return 0;
}
CLEAN_AS(func_ov004_0224730c, RoomCamera_SetMode11)

/* func_ov004_0224732c: which of Nook's shops the scene is, 0 to 3 (both floors of the last
 * give 3); 0 in any other scene. */
int RoomCamera_NookShopSize(void)
{
    switch (SceneQuery_Current()) {
        case ROOM_CAMERA_SCENE_NOOK_2:
            return 1;
        case ROOM_CAMERA_SCENE_NOOK_3:
            return 2;
        case ROOM_CAMERA_SCENE_NOOK_4:
        case ROOM_CAMERA_SCENE_NOOK_4_UP:
            return 3;
        case ROOM_CAMERA_SCENE_NOOK_1:
        default:
            return 0;
    }
}
CLEAN_AS(func_ov004_0224732c, RoomCamera_NookShopSize)

/* func_ov004_02247368: mode 10's frame: the camera placed. */
void RoomCamera_Mode10Frame(CameraControl *camera)
{
    RoomCamera_place(camera);
}
CLEAN_AS(func_ov004_02247368, RoomCamera_Mode10Frame)

/* func_ov004_022473a8: the goal reset: the preset of row 1, column 1 (the middle one) and
 * timing 0, its second offset at the player, the move restarted; 1.
 * REQUIRES: the player has an actor. */
int RoomCamera_ResetGoal(CameraControl *camera)
{
    CameraControl_LoadPreset(camera, data_020ca158[1][1], NULL);
    CameraControl_SelectTiming(camera, ROOM_CAMERA_TIMING_0);
    camera->goal.second_offset = *PlayerActorOps_StartPosition(ROOM_CAMERA_PLAYER);
    CameraControl_RestartMove();
    return 1;
}
CLEAN_AS(func_ov004_022473a8, RoomCamera_ResetGoal)

/* func_ov004_022473f4: mode 10's start: preset 0x11 and timing 0, the goal's second offset at
 * data_021fbee8, reached at once; 1. */
int RoomCamera_Mode10Start(CameraControl *camera)
{
    CameraControl_LoadPreset(camera, ROOM_CAMERA_PRESET_10, NULL);
    CameraControl_SelectTiming(camera, ROOM_CAMERA_TIMING_0);
    camera->goal.second_offset = data_021fbee8;
    CameraControl_EndMove();
    return 1;
}
CLEAN_AS(func_ov004_022473f4, RoomCamera_Mode10Start)

/* func_ov004_02247438: the goal of main's mode 2 indoors, set in `view` (the goal when NULL).
 * The middle of the player and the point looked at goes in the goal's second offset (always
 * the goal's), and the span between them blends preset 11 (near, 4.5 or less) into the
 * camera's own preset (far, 11.0 or more); 0x1e4 keeps the share of the near one. The view
 * then turns from the side the player or the point (whichever is further in z) is on, by up to
 * 0xe02 times the near share when the target is within 0x2000 of straight ahead, and looks
 * past that much to the side; its second offset goes back in z by half their gap in z.
 * 0x1f6 is the side (0 none, 1 or 2), chosen once when it is 3: the target's, or with a room
 * edge on that side, none past 0x701 else the other; always 1 in scene 0x10. Nothing turns
 * while 0x1f5 is set.
 * REQUIRES: the player has an actor. */
void RoomCamera_FocusGoal(CameraControl *camera, CameraView *view)
{
    if (view == NULL) {
        view = &camera->goal;
    }
    Vec3 *player = PlayerActorOps_StartPosition(ROOM_CAMERA_PLAYER);
    fx32 depth;
    int span = CameraControl_SpanOfTwo(player, &camera->look_at, &camera->goal.second_offset, &depth);
    if (span < ROOM_CAMERA_FOCUS_NEAR) {
        span = ROOM_CAMERA_FOCUS_NEAR;
    } else if (span > ROOM_CAMERA_FOCUS_FAR) {
        span = ROOM_CAMERA_FOCUS_FAR;
    }
    fx32 far_share = FX_Div(span - ROOM_CAMERA_FOCUS_NEAR, ROOM_CAMERA_FOCUS_FAR - ROOM_CAMERA_FOCUS_NEAR);
    fx32 near_share = 0x1000 - far_share;
    camera->unk_1e4 = near_share;
    CameraControl_BlendPresets(camera, ROOM_CAMERA_PRESET_FOCUS, data_020ca158[camera->preset_row][camera->preset_column],
                               far_share);

    Vec3 target = player->z > camera->look_at.z ? *player : camera->look_at;
    int edge = CameraControl_RoomEdgeX(camera, &view->second_offset);
    fx32 lateral = 0;
    int angle = Vec_YawTo(&view->second_offset, &target);
    int ahead = ROOM_CAMERA_FOCUS_SPREAD - RoomCamera_abs16(angle);
    if (ahead < 0) {
        ahead = 0;
    }
    int turn = (s16) FX_MulFunc(FX_MulFunc(ahead >> 1, ROOM_CAMERA_FOCUS_SPREAD), ROOM_CAMERA_FOCUS_TURN);
    if (turn > ROOM_CAMERA_FOCUS_TURN) {
        turn = ROOM_CAMERA_FOCUS_TURN;
    }
    if (turn > 0 && camera->unk_1f5 == 0) {
        if (camera->unk_1f6 == 3) {
            int side = angle > 0 ? 1 : 2;
            if (edge == 1 && side == 1) {
                side = RoomCamera_abs16(angle) > ROOM_CAMERA_FOCUS_SIDE_LIMIT ? 0 : 2;
            }
            if (edge == 2 && side == 2) {
                side = RoomCamera_abs16(angle) > ROOM_CAMERA_FOCUS_SIDE_LIMIT ? 0 : 1;
            }
            if (SceneQuery_Current() == ROOM_CAMERA_FOCUS_SCENE) {
                side = 1;
            }
            camera->unk_1f6 = (u8) side;
        }
        if (camera->unk_1f6 == 1) {
            turn = (s16) -turn;
        }
        if (camera->unk_1f6 != 0) {
            u16 yaw = (u16) FX_MulFunc(turn, near_share);
            view->yaw = (s16) yaw;
            lateral = FX_MulFunc(depth, FX_SinCosTable_[(yaw >> 4) * 2]);
        }
    }
    view->second_offset.z += depth;
    view->second_offset.x += lateral;
}
CLEAN_AS(func_ov004_02247438, RoomCamera_FocusGoal)
