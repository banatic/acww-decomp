/* The field camera's focus mode in the town (town_camera_focus.h). */
#include "town_camera_focus.h"

#include "autoload_2/vector.h"
#include "clean.h"
#include "main/camera_modes.h"
#include "main/camera_view.h"
#include "main/player_actor_ops.h"

extern fx32 FX_Div(fx32 numerator, fx32 denominator);

/* The player at this console (main's player number). */
#define TOWN_CAMERA_FOCUS_PLAYER 4
/* The span the blend runs over: up to 4.5 the focus preset, from 11.0 the follow preset. */
#define TOWN_CAMERA_FOCUS_NEAR 0x4800
#define TOWN_CAMERA_FOCUS_FAR 0xb000
/* The presets blended: the focus mode's outdoors and the follow mode's outdoors. */
#define TOWN_CAMERA_FOCUS_PRESET_FOCUS 10
#define TOWN_CAMERA_FOCUS_PRESET_FOLLOW 0
#define TOWN_CAMERA_FOCUS_ONE 0x1000

/* func_ov003_02236564: the goal's second offset set to the middle of the player and the
 * focused point (or both points), moved on in z by half their depth; their span, kept between
 * 4.5 and 11.0, gives the blend t from preset 10 (t = 0) to preset 0 (t = 1), and unk_1e4 is
 * set to 1 - t. */
void TownCameraFocus_SetGoal(CameraControl *camera)
{
    Vec3 *player = PlayerActorOps_StartPosition(TOWN_CAMERA_FOCUS_PLAYER);
    fx32 half_depth;
    int span;
    if (camera->look_both != 0) {
        span =
            CameraControl_SpanOfThree(player, &camera->look_at, &camera->look_at2, &camera->goal.second_offset, &half_depth);
    } else {
        span = CameraControl_SpanOfTwo(player, &camera->look_at, &camera->goal.second_offset, &half_depth);
    }
    camera->goal.second_offset.z += half_depth;
    if (span < TOWN_CAMERA_FOCUS_NEAR) {
        span = TOWN_CAMERA_FOCUS_NEAR;
    } else if (span > TOWN_CAMERA_FOCUS_FAR) {
        span = TOWN_CAMERA_FOCUS_FAR;
    }
    fx32 t = FX_Div(span - TOWN_CAMERA_FOCUS_NEAR, TOWN_CAMERA_FOCUS_FAR - TOWN_CAMERA_FOCUS_NEAR);
    camera->unk_1e4 = TOWN_CAMERA_FOCUS_ONE - t;
    CameraControl_BlendPresets(camera, TOWN_CAMERA_FOCUS_PRESET_FOCUS, TOWN_CAMERA_FOCUS_PRESET_FOLLOW, t);
}
CLEAN_AS(func_ov003_02236564, TownCameraFocus_SetGoal)
