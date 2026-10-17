/* The field camera's modes of overlay 68 (field_camera_modes.h). */
#include "field_camera_modes.h"

#include "autoload_2/approach.h"
#include "clean.h"
#include "itcm/camera.h"
#include "main/acre_map.h"
#include "main/acre_tile.h"
#include "main/camera_view.h"
#include "main/main_random.h"
#include "main/player_actor_ops.h"

static_assert(sizeof(FieldCameraSwayStage) == 0xc, "sway stage");
static_assert(offsetof(FieldCameraSway, rise_stage) == 0x08, "sway stage byte");
static_assert(offsetof(FieldCameraTour, offset) == 0x10, "tour offset");
static_assert(sizeof(FieldCameraTour) == 0x18, "tour");
static_assert(0x21c + sizeof(FieldCameraTour) == sizeof(CameraControl), "the mode's data ends the camera");

extern const s16 FX_SinCosTable_[];
extern fx32 FX_MulFunc(fx32 a, fx32 b);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *sum);

/* Where the point followed goes without a player: the origin. */
extern Vec3 data_021fbee8;
/* The town's map (main's acre_map.h), or null. */
extern AcreMap *data_021c80bc;
/* The sway's four stages. */
extern const FieldCameraSwayStage data_020ca17c[];
/* The tour's stops: the item range of each (the first two words written as the tour goes
 * round), the acre flags it is found in, and its offsets. */
extern u16 data_ov068_022772d4[][2];
extern const s32 data_ov068_022767cc[];
extern const Vec3 *const data_ov068_022772f0[];
/* The tour's glide: the speed's rise per frame (1) and most (0x100), and the share of the
 * distance taken each frame (0x80, 1/32). */
extern const fx32 data_ov068_02277280;
extern const fx32 data_ov068_02277284;
extern const fx32 data_ov068_02277288;

#define MODE_DATA 0x21c

/* The presets and timings the modes start with (main's camera_view.h). */
#define PRESET_0 0
#define PRESET_SWAY 0x10
#define PRESET_PLAYER 0x1a
#define TIMING_0 0
/* The mode the sway restarts the move after. */
#define MODE_FOCUS 2
#define SWAY_FOV 0x1c71
#define SWAY_STAGES 4
#define SWAY_STILL 0x100              /* a phase within this of 0 may change its stage */
#define SWAY_RISE_STAGE_1_CHANCE 0x50 /* in 100 */

#define TOUR_WAIT 0x3c
#define TOUR_STOPS 7
#define TOUR_MIN_STEP 8
#define TOUR_FIRST_STOP_FIRST 0x5014
#define TOUR_FIRST_STOP_LAST 0x501a
#define TOUR_FIRST_STOP_FLAGS 1
#define TOUR_HOUSE_FIRST 0x5001
#define TOUR_HOUSE_LAST 0x5008
#define TOUR_ROUND_FIRST 0x500d
#define TOUR_ROUND_LAST 0x5010

#define PLAYER 4

static FieldCameraSway *sway_of(CameraControl *camera)
{
    return (FieldCameraSway *) (void *) ((u8 *) camera + MODE_DATA);
}

static FieldCameraTour *tour_of(CameraControl *camera)
{
    return (FieldCameraTour *) (void *) ((u8 *) camera + MODE_DATA);
}

/* The current view eased towards the goal, and the camera placed at it around the point looked
 * at. */
static void place(CameraControl *camera)
{
    CameraControl_Ease(camera);
    Vec3 target;
    Camera_GetTarget(&target, (Camera *) (void *) camera);
    int pitch = CameraControl_Pitch(camera);
    int yaw = CameraControl_Yaw(camera);
    int distance = CameraControl_Distance(camera);
    CameraControl_Place(camera, &target, pitch, yaw, distance);
}

/* The size of a 16-bit value, as a 16-bit value: -0x8000 stays negative. */
static s16 size16(s16 value)
{
    return value < 0 ? (s16) -value : value;
}

/* The sine of `phase` times `size`. */
static fx32 sine(s16 phase, fx32 size)
{
    return FX_MulFunc(FX_SinCosTable_[((u16) phase >> 4) * 2], size);
}

/* func_ov068_0226dabc: a frame of the sway; the height it adds to the point looked at. When a
 * stage's frames run out while its phase is within 0x100 of 0, the next stage: for the rise,
 * from stage 0 stage 1 (80 in 100) or 2, from stage 2 stage 1, else 0; for the roll, from
 * stages 0 and 2 stage 1, else 0. Each phase moves by its stage's speed; the roll (0x174) and
 * the height are the sines of the phases times their stages' sizes, the roll kept only when
 * its speed is not 0, the height 0 when its speed is 0.
 * QUIRK: the phases' sizes are 16-bit values: a phase of -0x8000 counts as within 0x100.
 * REQUIRES: the stages are 0 to 3 (FieldCameraModes_SetRiseStage keeps them so). */
int FieldCameraModes_Sway(CameraControl *camera)
{
    FieldCameraSway *sway = sway_of(camera);
    if (Countdown_Tick16(&sway->rise_frames) == 0 && size16(sway->rise_phase) < SWAY_STILL) {
        if (sway->rise_stage == 0) {
            sway->rise_stage = MainRandom_Below(100) < SWAY_RISE_STAGE_1_CHANCE ? 1 : 2;
        } else {
            sway->rise_stage = sway->rise_stage == 2 ? 1 : 0;
        }
        FieldCameraModes_SetRiseStage(camera, sway->rise_stage);
    }
    if (Countdown_Tick16(&sway->roll_frames) == 0 && size16(sway->roll_phase) < SWAY_STILL) {
        if (sway->roll_stage == 0) {
            sway->roll_stage = 1;
        } else {
            sway->roll_stage = sway->roll_stage == 2 ? 1 : 0;
        }
        FieldCameraModes_SetRollStage(camera, sway->roll_stage);
    }
    const FieldCameraSwayStage *roll = &data_020ca17c[sway->roll_stage];
    if (roll->speed != 0) {
        sway->roll_phase = (s16) (sway->roll_phase + roll->speed);
        camera->roll = (s16) sine(sway->roll_phase, roll->size);
    }
    const FieldCameraSwayStage *rise = &data_020ca17c[sway->rise_stage];
    if (rise->speed == 0) {
        return 0;
    }
    sway->rise_phase = (s16) (sway->rise_phase + rise->speed);
    return sine(sway->rise_phase, rise->size);
}
CLEAN_AS(func_ov068_0226dabc, FieldCameraModes_Sway)

/* func_ov068_0226dc08: the roll's stage set (4 and above give 0), with its frames drawn and its
 * phase at 0. */
void FieldCameraModes_SetRollStage(CameraControl *camera, u8 stage)
{
    FieldCameraSway *sway = sway_of(camera);
    sway->roll_stage = stage;
    if (sway->roll_stage >= SWAY_STAGES) {
        sway->roll_stage = 0;
    }
    const FieldCameraSwayStage *entry = &data_020ca17c[sway->roll_stage];
    sway->roll_frames = entry->frames;
    sway->roll_frames = (u16) (sway->roll_frames + MainRandom_Below(entry->spread));
    sway->roll_phase = 0;
}
CLEAN_AS(func_ov068_0226dc08, FieldCameraModes_SetRollStage)

/* func_ov068_0226dc64: the rise's stage set (4 and above give 0), with its frames drawn and its
 * phase at 0. */
void FieldCameraModes_SetRiseStage(CameraControl *camera, u8 stage)
{
    FieldCameraSway *sway = sway_of(camera);
    sway->rise_stage = stage;
    if (sway->rise_stage >= SWAY_STAGES) {
        sway->rise_stage = 0;
    }
    const FieldCameraSwayStage *entry = &data_020ca17c[sway->rise_stage];
    sway->rise_frames = entry->frames;
    sway->rise_frames = (u16) (sway->rise_frames + MainRandom_Below(entry->spread));
    sway->rise_phase = 0;
}
CLEAN_AS(func_ov068_0226dc64, FieldCameraModes_SetRiseStage)

/* func_ov068_0226dcc0: mode 9's frame: the point followed at the origin raised by the sway, and
 * the camera placed. */
void FieldCameraModes_SwayFrame(CameraControl *camera)
{
    camera->goal.second_offset = data_021fbee8;
    camera->goal.second_offset.y += FieldCameraModes_Sway(camera);
    place(camera);
}
CLEAN_AS(func_ov068_0226dcc0, FieldCameraModes_SwayFrame)

/* func_ov068_0226dd34: mode 9's start: preset 16 and timing 0, the move restarted after mode 2
 * and else taken to its end, the field of view 0x1c71 and the rise's stage 0; 1. */
int FieldCameraModes_SwayStart(CameraControl *camera)
{
    CameraControl_LoadPreset(camera, PRESET_SWAY, NULL);
    CameraControl_SelectTiming(camera, TIMING_0);
    if (camera->previous_mode == MODE_FOCUS) {
        CameraControl_RestartMove();
    } else {
        CameraControl_EndMove();
    }
    CameraControl_SetFov(camera, SWAY_FOV);
    FieldCameraModes_SetRiseStage(camera, 0);
    return 1;
}
CLEAN_AS(func_ov068_0226dd34, FieldCameraModes_SwayStart)

/* func_ov068_0226dd7c: mode 13's frame: the point followed taken to this console's player (the
 * origin without one), and the camera placed. */
void FieldCameraModes_PlayerFrame(CameraControl *camera)
{
    Vec3 point = data_021fbee8;
    Vec3 *player = PlayerActorOps_StartPosition(PLAYER);
    if (player != NULL) {
        point = *player;
    }
    CameraControl_Follow(camera, &point);
    place(camera);
}
CLEAN_AS(func_ov068_0226dd7c, FieldCameraModes_PlayerFrame)

/* func_ov068_0226ddec: mode 13's start: preset 0x1a, the move taken to its end; 1. */
int FieldCameraModes_PlayerStart(CameraControl *camera)
{
    CameraControl_LoadPreset(camera, PRESET_PLAYER, NULL);
    CameraControl_EndMove();
    return 1;
}
CLEAN_AS(func_ov068_0226ddec, FieldCameraModes_PlayerStart)

/* The next stop's item range: the houses' and the round of items 0x500d to 0x5010 move on to
 * their next item (the latter's place in the round given in `round`). */
static void tour_next_item(u16 *range, int *round)
{
    if (range[0] >= TOUR_HOUSE_FIRST && range[0] <= TOUR_HOUSE_LAST) {
        range[0]++;
        if (range[0] > TOUR_HOUSE_LAST) {
            range[0] = TOUR_HOUSE_FIRST;
        }
        range[1] = range[0];
    } else if (range[0] >= TOUR_ROUND_FIRST && range[0] <= TOUR_ROUND_LAST) {
        range[0]++;
        if (range[0] > TOUR_ROUND_LAST) {
            range[0] = TOUR_ROUND_FIRST;
        }
        range[1] = range[0];
        *round = range[0] - TOUR_ROUND_FIRST;
    }
}

/* func_ov068_0226de04: mode 8's frame. The speed rises by 1 to 0x100, and the point followed
 * glides in the ground plane a 32nd of the way at a time (at least 8, at most the speed) to the
 * stop's point (its base plus its offset). Arrived, and once its wait of 60 frames is out, the
 * tour goes on to the next stop (after the last, the first): with a map, the stop's item range
 * moves on (tour_next_item) until a structure of it is found in an acre of the stop's flags,
 * whose tile's centre is the new base, the stop's offset (by the round's place) the new offset,
 * and the speed 0. Then the camera is placed.
 * QUIRK: with no structure of the range in the town the search goes on for ever (the houses'
 * and the round's ranges move on; the others are searched again unchanged). */
void FieldCameraModes_TourFrame(CameraControl *camera)
{
    FieldCameraTour *tour = tour_of(camera);
    Vec3 point = tour->base;
    VEC_Add(&point, tour->offset, &point);
    Approach_S32(&tour->speed, data_ov068_02277288, data_ov068_02277280);
    if (Approach_PointXZ(&camera->goal.second_offset, &point, data_ov068_02277284, tour->speed, TOUR_MIN_STEP) == 0 &&
        Approach_S16(&tour->wait, 0, 1) != 0) {
        tour->wait = TOUR_WAIT;
        if (Approach_S16(&tour->stop, TOUR_STOPS, 1) != 0) {
            tour->stop = 0;
        }
        AcreMap *map = data_021c80bc;
        int round = 0;
        int acre_x = 0;
        int acre_z = 0;
        int x = 0;
        int z = 0;
        if (map != NULL) {
            u16 first;
            u16 last;
            do {
                u16 *range = data_ov068_022772d4[tour->stop];
                tour_next_item(range, &round);
                first = range[0];
                last = range[1];
            } while (AcreTile_FindItemAllFlags(map, &acre_x, &acre_z, &x, &z, &first, &last, data_ov068_022767cc[tour->stop],
                                               0) == 0);
            Vec3 centre;
            AcreTile_TileCentreInAcre(&centre, acre_x, acre_z, x, z);
            tour->base = centre;
            tour->offset = data_ov068_022772f0[tour->stop] + round;
            tour->speed = 0;
        }
    }
    place(camera);
}
CLEAN_AS(func_ov068_0226de04, FieldCameraModes_TourFrame)

/* func_ov068_0226e008: mode 8's start: preset 0 and timing 0, the move taken to its end, the
 * first stop with its wait of 60 frames; with a map where the structure of items 0x5014 to
 * 0x501a is found in an acre of flag 1, the point followed at its tile's centre and the first
 * stop's offset; then the base is the point followed, the point followed moves on by the
 * offset, and the speed is 0; 1.
 * BUG: without a map or that structure the offset is whatever the camera's mode data held.
 * REQUIRES: then it holds a pointer that can be read. */
int FieldCameraModes_TourStart(CameraControl *camera)
{
    FieldCameraTour *tour = tour_of(camera);
    CameraControl_LoadPreset(camera, PRESET_0, NULL);
    CameraControl_SelectTiming(camera, TIMING_0);
    CameraControl_EndMove();
    AcreMap *map = data_021c80bc;
    int acre_x = 0;
    int acre_z = 0;
    int x = 0;
    int z = 0;
    tour->wait = TOUR_WAIT;
    tour->stop = 0;
    if (map != NULL) {
        u16 range[2] = {TOUR_FIRST_STOP_FIRST, TOUR_FIRST_STOP_LAST};
        if (AcreTile_FindItemAllFlags(map, &acre_x, &acre_z, &x, &z, &range[0], &range[1], TOUR_FIRST_STOP_FLAGS, 0) == 1) {
            Vec3 centre;
            AcreTile_TileCentreInAcre(&centre, acre_x, acre_z, x, z);
            tour->offset = data_ov068_022772f0[0];
            camera->goal.second_offset = centre;
        }
    }
    tour->base = camera->goal.second_offset;
    camera->goal.second_offset.x += tour->offset->x;
    camera->goal.second_offset.y += tour->offset->y;
    camera->goal.second_offset.z += tour->offset->z;
    tour->speed = 0;
    return 1;
}
CLEAN_AS(func_ov068_0226e008, FieldCameraModes_TourStart)

/* func_ov068_0226e0f8: mode 7's frame: the point followed taken to the position of the actor in
 * the mode's data (the zero point without one), and the camera placed. */
void FieldCameraModes_ActorFrame(CameraControl *camera)
{
    const u8 *actor = *(const u8 *const *) (const void *) ((const u8 *) camera + MODE_DATA);
    Vec3 point = {0, 0, 0};
    if (actor != NULL) {
        point = *(const Vec3 *) (const void *) (actor + 0x5c);
    }
    CameraControl_Follow(camera, &point);
    place(camera);
}
CLEAN_AS(func_ov068_0226e0f8, FieldCameraModes_ActorFrame)

/* func_ov068_0226e164: mode 7's start: preset 0 and timing 0, the move taken to its end; 1. */
int FieldCameraModes_ActorStart(CameraControl *camera)
{
    CameraControl_LoadPreset(camera, PRESET_0, NULL);
    CameraControl_SelectTiming(camera, TIMING_0);
    CameraControl_EndMove();
    return 1;
}
CLEAN_AS(func_ov068_0226e164, FieldCameraModes_ActorStart)
