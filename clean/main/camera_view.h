/* The field camera's view (camera_control.h): the goal view loaded from the game's table of
 * presets or blended between two of them, the move's timing, easing the current view towards
 * the goal, placing the eye and the point looked at (bent onto the curved ground outdoors), the
 * bounds of a room, the projection, and the camera's process functions: create, run the mode's
 * frame, draw and delete.
 *
 * A move eases the current view to the goal over its length in 20.12 frames: nothing happens
 * for its delay, then the speed rises over `ease_in`, stays, and falls over `ease_out`
 * (func_020643dc). Each of the four has an adjustment of its own added (camera_control.h). */
#ifndef CLEAN_MAIN_CAMERA_VIEW_H
#define CLEAN_MAIN_CAMERA_VIEW_H

#include "autoload_2/vector.h"
#include "camera_control.h"
#include "types.h"

/* A preset of a view (the table data_020ca20c): a view without its second offset. */
typedef struct CameraPreset {
    s16 yaw;
    s16 pitch;
    fx32 distance;
    Vec3 offset;
} CameraPreset;

/* The timing of a move (the table data_020ca1ac), in 20.12 frames. */
typedef struct CameraTiming {
    fx32 delay;
    fx32 length;
    fx32 ease_in;
    fx32 ease_out;
} CameraTiming;

/* The modes there are; a mode is a pair of member functions (data_021c6820): its start, which
 * says whether the camera may switch to it, and its frame. */
#define CAMERA_MODES 21

void CameraControl_Follow(CameraControl *camera, const Vec3 *point);
void CameraControl_PlaceAt(CameraControl *camera, const Vec3 *target, const Vec3 *eye);
void CameraControl_Place(CameraControl *camera, const Vec3 *target, int pitch, int yaw, int distance);
void CameraControl_Ease(CameraControl *camera);
void CameraControl_ResetProjection(CameraControl *camera);
void CameraControl_RunMode(CameraControl *camera);
int CameraControl_SetMode(CameraControl *camera, int mode);
int CameraControl_RoomEdgeX(CameraControl *camera, const Vec3 *point);
void CameraControl_SetPresetPoint(CameraControl *camera, CameraView *view, const Vec3 *point);
int CameraControl_ClampToRoom(CameraControl *camera, Vec3 *point);
void CameraControl_SetRoomBounds(CameraControl *camera);
void CameraControl_TargetAcre(CameraControl *camera, int *x, int *z);
void CameraControl_UpdateGroundAngle(CameraControl *camera);
void CameraControl_SetFov(CameraControl *camera, s16 fov);
int CameraControl_EaseOut(CameraControl *camera);
int CameraControl_EaseIn(CameraControl *camera);
int CameraControl_MoveLength(CameraControl *camera);
int CameraControl_Delay(CameraControl *camera);
u32 CameraControl_Projection(CameraControl *camera);
int CameraControl_Distance(CameraControl *camera);
u32 CameraControl_FollowRadius(CameraControl *camera);
s16 CameraControl_Yaw(CameraControl *camera);
s16 CameraControl_Pitch(CameraControl *camera);
s16 CameraControl_GroundAngle(CameraControl *camera);
Vec3 *CameraControl_Eye(CameraControl *camera);
void CameraControl_ClearAdjustments(CameraControl *camera);
int CameraControl_Delete(void);
void CameraControl_Draw(CameraControl *camera);
int CameraControl_Execute(CameraControl *camera);
int CameraControl_Create(CameraControl *camera);
void CameraControl_SetTiming(CameraControl *camera, const CameraTiming *timing);
void CameraControl_SelectTiming(CameraControl *camera, int index);
void CameraControl_BlendPresets(CameraControl *camera, int from, int to, fx32 t);
void CameraControl_LoadPreset(CameraControl *camera, int index, CameraView *view);

#endif
