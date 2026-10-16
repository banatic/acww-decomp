/* The field camera's modes run from main (camera_control.h, camera_view.h): each has a start,
 * which loads the goal view's preset and the move's timing, and a frame, which moves the point
 * followed and places the camera. The others (7-16, 18, 20) are in overlays 3, 4 and 68.
 *
 *   0  follow the player (indoors kept inside the room)
 *   1  hold still, or with a view saved, follow the player
 *   2  look at the player and one or two points near
 *   3, 4  follow the player closely
 *   5  look past the player towards the actor FieldActor_PlayerFocus gives
 *   6  the view kept outside the camera (CameraControl_KeepView)
 *   17 shake along the camera's up vector
 *   19 a preset of its own
 *
 * Also here: the spans the focus of mode 2 is measured with. */
#ifndef CLEAN_MAIN_CAMERA_MODES_H
#define CLEAN_MAIN_CAMERA_MODES_H

#include "autoload_2/vector.h"
#include "camera_control.h"
#include "types.h"

/* The modes named here (CAMERA_MODE_3, 4, 5, 17 and 19 are in camera_control.h). */
enum CameraControlModeMore {
    CAMERA_MODE_FOLLOW = 0,
    CAMERA_MODE_STILL = 1,
    CAMERA_MODE_FOCUS = 2,
    CAMERA_MODE_6 = 6,
    CAMERA_MODE_7 = 7,
    CAMERA_MODE_8 = 8,
    CAMERA_MODE_9 = 9,
    CAMERA_MODE_10 = 0xa,
    CAMERA_MODE_13 = 0xd,
    CAMERA_MODE_14 = 0xe
};

/* The 8 bytes at 0x21c (CameraControl.unk_21c) belong to the mode. */
typedef union CameraControlModeData {
    struct {
        int amplitude;  /* eased to 0 (fx32) */
        s16 phase;      /* an angle */
        s16 phase_step; /* eased to 0x6000 */
    } shake;            /* mode 17 */
    void *actor;        /* mode 7: the actor followed */
} CameraControlModeData;

void CameraControl_FocusOnPair(const Vec3 *a, const Vec3 *b);
int CameraControl_FocusOn(const Vec3 *point);
int CameraControl_SpanOfThree(const Vec3 *a, const Vec3 *b, const Vec3 *c, Vec3 *center, fx32 *half_depth);
int CameraControl_SpanOfTwo(const Vec3 *a, const Vec3 *b, Vec3 *center, fx32 *half_depth);
int CameraControl_SetModeStill(void);
int CameraControl_ResetMode(void);
void CameraControl_Mode19Frame(CameraControl *camera);
int CameraControl_Mode19Start(CameraControl *camera);
void CameraControl_ShakeFrame(CameraControl *camera);
int CameraControl_ShakeStart(CameraControl *camera);
void CameraControl_Mode6Frame(CameraControl *camera);
int CameraControl_Mode6Start(void);
void CameraControl_Mode5Frame(CameraControl *camera);
int CameraControl_Mode5Start(CameraControl *camera);
void CameraControl_Mode4Frame(CameraControl *camera);
int CameraControl_Mode4Start(CameraControl *camera);
void CameraControl_Mode3Frame(CameraControl *camera);
int CameraControl_Mode3Start(CameraControl *camera);
void CameraControl_FocusFrame(CameraControl *camera);
int CameraControl_FocusStart(CameraControl *camera);
void CameraControl_StillFrame(CameraControl *camera);
int CameraControl_StillStart(CameraControl *camera);
void CameraControl_PutSavedViewBack(CameraControl *camera);
void CameraControl_SaveGoalView(CameraControl *camera);
void CameraControl_FollowFrame(CameraControl *camera);
int CameraControl_FollowStart(CameraControl *camera);

#endif
