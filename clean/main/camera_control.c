/* Driving the field camera (camera_control.h). */
#include "camera_control.h"

#include "autoload_2/heap.h"    /* Heap_FreeAux */
#include "autoload_2/process.h" /* Process_Destruct */
#include "clean.h"
#include "itcm/camera.h" /* Camera_GetTarget */
#include "sound.h"       /* SoundSys_PlaySe */
#include "camera_modes.h"
#include "camera_view.h"
#include "globe.h"
#include "ov068/field_camera_modes.h"

static_assert(sizeof(CameraView) == 0x20, "a view");
static_assert(offsetof(CameraControl, view_matrix) == 0x50, "the view matrix");
static_assert(offsetof(CameraControl, unk_b8) == 0xb8, "0xb8");
static_assert(offsetof(CameraControl, move_time) == 0xc8, "the move's time");
static_assert(offsetof(CameraControl, goal) == 0xfc, "the goal view");
static_assert(offsetof(CameraControl, saved) == 0x11c, "the saved view");
static_assert(offsetof(CameraControl, current) == 0x148, "the current view");
static_assert(offsetof(CameraControl, point) == 0x168, "the point");
static_assert(offsetof(CameraControl, projection) == 0x1c4, "the projection");
static_assert(offsetof(CameraControl, look_at) == 0x1cc, "the point looked at");
static_assert(offsetof(CameraControl, unk_1e8) == 0x1e8, "0x1e8");
static_assert(offsetof(CameraControl, view_saved) == 0x1f4, "the saved flag");
static_assert(offsetof(CameraControl, mode) == 0x1f8, "the mode");
static_assert(offsetof(CameraControl, unk_21c) == 0x21c, "0x21c");
static_assert(sizeof(CameraControl) == 0x234, "the camera");

/* The camera, NULL when there is none. */
extern CameraControl *data_021c67a4;

/* A view and point kept outside the camera (CameraControl_KeepView). */
extern CameraView data_021c6800;
extern Vec3 data_021c67f4;

/* Where CameraControl_ProjectPoint copies the view matrix to. */
extern Mtx43 data_021fbe48;

/* The vtables of the camera's class and of its two bases, the destructors put back in turn. */
extern const u8 data_020da87c[];
extern const u8 data_020e58cc[];
extern const u8 data_020da13c[];

/* The preset of the goal view that the snap uses. */
#define SNAP_PRESET 0xb
/* What the projection divides by the projection value (6.0). */
#define PROJECTION_SCALE 0x60000
/* In mode 19 CameraControl_LookAt sets this length (21 frames). */
#define MODE_19_LENGTH 0x15000
/* What CameraControl_LookAt sets at 0x1f6. */
#define LOOK_AT_1F6 3
/* The stage CameraControl_StartStage3 starts. */
#define STAGE_3 3
/* How far before the goal's second offset CameraControl_IsPastGoalZ looks (2.0). */
#define GOAL_Z_MARGIN 0x2000

extern void MTX_MultVec43(const Vec3 *vector, const Mtx43 *mtx, Vec3 *out);
extern fx32 FX_Div(fx32 numerator, fx32 denominator);

/* func_0203a9cc: the destructor: each class's vtable put back, down to the process's. */
CameraControl *CameraControl_Destruct(CameraControl *camera)
{
    camera->vtable = data_020da87c;
    camera->vtable = data_020e58cc;
    camera->vtable = data_020da13c;
    Process_Destruct((Process *) camera);
    return camera;
}
CLEAN_AS(func_0203a9cc, CameraControl_Destruct)

/* func_0203a9f4: destroyed and freed to the auxiliary heap. */
CameraControl *CameraControl_DestructFree(CameraControl *camera)
{
    camera->vtable = data_020da87c;
    camera->vtable = data_020e58cc;
    camera->vtable = data_020da13c;
    Process_Destruct((Process *) camera);
    Heap_FreeAux(camera);
    return camera;
}
CLEAN_AS(func_0203a9f4, CameraControl_DestructFree)

/* func_0203aa24: where a point on the flat ground shows on the screen, from its middle. */
void CameraControl_ScreenPosition(int *x, int *y, const Vec3 *point)
{
    Vec3 curved;
    Globe_Bend(&curved, point);
    CameraControl_ProjectPoint(x, y, &curved);
}
CLEAN_AS(func_0203aa24, CameraControl_ScreenPosition)

/* func_0203aa48: where `point` shows on the screen, in pixels from its middle, y up; whether
 * there is a camera (without one, nothing is written). */
int CameraControl_ProjectPoint(int *x, int *y, const Vec3 *point)
{
    if (data_021c67a4 == NULL) {
        return 0;
    }
    data_021fbe48 = *CameraControl_ViewMatrix();
    Vec3 view;
    MTX_MultVec43(point, &data_021fbe48, &view);
    fx32 scale = -FX_Div(PROJECTION_SCALE, (fx32) CameraControl_Projection(data_021c67a4));
    scale = FX_Div(scale, view.z);
    Vec_Scale(&view, scale);
    *x = view.x >> 12;
    *y = -(view.y >> 12);
    return 1;
}
CLEAN_AS(func_0203aa48, CameraControl_ProjectPoint)

/* func_0203aad0: the preset the goal view comes from set to (`row`, `column`), restarting the
 * move; whether it changed (0 without a camera). */
int CameraControl_SelectPreset(int row, int column)
{
    CameraControl *camera = data_021c67a4;
    if (camera == NULL || (camera->preset_column == column && camera->preset_row == row)) {
        return 0;
    }
    CameraControl_RestartMove();
    data_021c67a4->preset_row = row;
    data_021c67a4->preset_column = column;
    return 1;
}
CLEAN_AS(func_0203aad0, CameraControl_SelectPreset)

/* func_0203ab20: the camera's view matrix; NULL without a camera. */
Mtx43 *CameraControl_ViewMatrix(void)
{
    return data_021c67a4 != NULL ? &data_021c67a4->view_matrix : NULL;
}
CLEAN_AS(func_0203ab20, CameraControl_ViewMatrix)

/* func_0203ab34: sound effect `number` played unless the camera's sounds are muted. */
void CameraControl_PlaySound(CameraControl *camera, int number)
{
    if (camera->sounds_muted == 0) {
        SoundSys_PlaySe(number);
    }
}
CLEAN_AS(func_0203ab34, CameraControl_PlaySound)

/* func_0203ab50 */
void CameraControl_UnmuteSounds(void)
{
    data_021c67a4->sounds_muted = 0;
}
CLEAN_AS(func_0203ab50, CameraControl_UnmuteSounds)

/* func_0203ab64 */
void CameraControl_MuteSounds(void)
{
    data_021c67a4->sounds_muted = 1;
}
CLEAN_AS(func_0203ab64, CameraControl_MuteSounds)

/* func_0203ab78: the goal view set to preset 11 with its second offset at `point`, shown at once
 * (copied to the current view), and the camera placed for it. */
void CameraControl_SnapToPoint(const Vec3 *point)
{
    CameraControl_SetPresetPoint(data_021c67a4, &data_021c67a4->goal, point);
    data_021c67a4->current = data_021c67a4->goal;
    Vec3 target;
    Camera_GetTarget(&target, (Camera *) data_021c67a4);
    int pitch = CameraControl_Pitch(data_021c67a4);
    int yaw = CameraControl_Yaw(data_021c67a4);
    int distance = CameraControl_Distance(data_021c67a4);
    CameraControl_Place(data_021c67a4, &target, pitch, yaw, distance);
}
CLEAN_AS(func_0203ab78, CameraControl_SnapToPoint)

/* func_0203ac04 */
void CameraControl_SetFlag1F5(void)
{
    data_021c67a4->unk_1f5 = 1;
}
CLEAN_AS(func_0203ac04, CameraControl_SetFlag1F5)

/* func_0203ac18: overlay 68's stage 3 started on the camera (func_ov068_0226dc64). */
void CameraControl_StartStage3(void)
{
    FieldCameraModes_SetRiseStage(data_021c67a4, STAGE_3);
}
CLEAN_AS(func_0203ac18, CameraControl_StartStage3)

/* func_0203ac2c: the saved view put back; 1. */
int CameraControl_RestoreView(void)
{
    CameraControl_PutSavedViewBack(data_021c67a4);
    return 1;
}
CLEAN_AS(func_0203ac2c, CameraControl_RestoreView)

/* func_0203ac44: the goal view saved; 1. */
int CameraControl_SaveView(void)
{
    CameraControl_SaveGoalView(data_021c67a4);
    return 1;
}
CLEAN_AS(func_0203ac44, CameraControl_SaveView)

/* func_0203ac5c: whether a view is
 * saved. */
int CameraControl_IsViewSaved(void)
{
    return data_021c67a4->view_saved != 0;
}
CLEAN_AS(func_0203ac5c, CameraControl_IsViewSaved)

/* func_0203ac78: the goal view and the point set to those kept outside the camera. */
void CameraControl_LoadKeptView(void)
{
    data_021c67a4->goal = data_021c6800;
    data_021c67a4->point = data_021c67f4;
}
CLEAN_AS(func_0203ac78, CameraControl_LoadKeptView)

/* func_0203acd8: the goal view and the point kept outside the camera. */
void CameraControl_KeepView(void)
{
    data_021c6800 = data_021c67a4->goal;
    data_021c67f4 = data_021c67a4->point;
}
CLEAN_AS(func_0203acd8, CameraControl_KeepView)

/* func_0203ad30: the whole frames left of the move, in 8 bits. */
u8 CameraControl_MoveFramesLeft(void)
{
    fx32 length = CameraControl_MoveLength(data_021c67a4);
    return (u8) ((length - data_021c67a4->move_time) >> 12);
}
CLEAN_AS(func_0203ad30, CameraControl_MoveFramesLeft)

/* func_0203ad58 */
void CameraControl_RestartMove(void)
{
    data_021c67a4->move_time = 0;
}
CLEAN_AS(func_0203ad58, CameraControl_RestartMove)

/* func_0203ad68: the move taken to its end. */
void CameraControl_EndMove(void)
{
    data_021c67a4->move_time = CameraControl_MoveLength(data_021c67a4);
}
CLEAN_AS(func_0203ad68, CameraControl_EndMove)

/* func_0203ad88: whether the move has not run past its length. */
int CameraControl_IsMoving(void)
{
    fx32 length = CameraControl_MoveLength(data_021c67a4);
    return data_021c67a4->move_time <= length;
}
CLEAN_AS(func_0203ad88, CameraControl_IsMoving)

/* func_0203adb0 */
u32 CameraControl_Value1E8(void)
{
    return (u32) data_021c67a4->unk_1e8;
}
CLEAN_AS(func_0203adb0, CameraControl_Value1E8)

/* func_0203adc4: in modes 2 and 4, in mode 1 entered from mode 2, or while a view is saved:
 * whether `point`'s z less half of `size` is past 2.0 before the goal's second offset's z.
 * 0 otherwise, and without a camera. */
int CameraControl_IsPastGoalZ(const Vec3 *point, int unused, fx32 size)
{
    (void) unused;
    CameraControl *camera = data_021c67a4;
    if (camera == NULL) {
        return 0;
    }
    int mode = camera->mode;
    if (mode != 2 && mode != 4 && !(mode == 1 && camera->previous_mode == 2) && camera->view_saved == 0) {
        return 0;
    }
    return point->z - (size >> 1) > camera->goal.second_offset.z - GOAL_Z_MARGIN;
}
CLEAN_AS(func_0203adc4, CameraControl_IsPastGoalZ)

/* func_0203ae28: the camera turned to look at `at` (byte 0x1f6 set to 3), restarting the move;
 * 1.
 * QUIRK: in mode 19 `at` is not used: the move restarts with 0xb8 cleared and 0xbc set to 21
 * frames instead. */
int CameraControl_LookAt(const Vec3 *at)
{
    if (data_021c67a4->mode == CAMERA_MODE_19) {
        data_021c67a4->move_time = 0;
        data_021c67a4->unk_b8 = 0;
        data_021c67a4->unk_bc = MODE_19_LENGTH;
        return 1;
    }
    data_021c67a4->look_at = *at;
    data_021c67a4->move_time = 0;
    data_021c67a4->unk_1f6 = LOOK_AT_1F6;
    return 1;
}
CLEAN_AS(func_0203ae28, CameraControl_LookAt)

/* func_0203ae84 */
void CameraControl_SetMode5(void)
{
    CameraControl_SetMode(data_021c67a4, CAMERA_MODE_5);
}
CLEAN_AS(func_0203ae84, CameraControl_SetMode5)

/* func_0203ae98 */
void CameraControl_SetMode4(void)
{
    CameraControl_SetMode(data_021c67a4, CAMERA_MODE_4);
}
CLEAN_AS(func_0203ae98, CameraControl_SetMode4)

/* func_0203aeac: back to the mode before; func_0203c0ac's answer. */
int CameraControl_SetPreviousMode(void)
{
    return CameraControl_SetMode(data_021c67a4, data_021c67a4->previous_mode);
}
CLEAN_AS(func_0203aeac, CameraControl_SetPreviousMode)

/* func_0203aec4 */
void CameraControl_SetMode3(void)
{
    CameraControl_SetMode(data_021c67a4, CAMERA_MODE_3);
}
CLEAN_AS(func_0203aec4, CameraControl_SetMode3)

/* func_0203aed8 */
void CameraControl_SetMode19(void)
{
    CameraControl_SetMode(data_021c67a4, CAMERA_MODE_19);
}
CLEAN_AS(func_0203aed8, CameraControl_SetMode19)

/* func_0203aeec: mode 17, with `value` at 0x21c. */
void CameraControl_SetMode17(u32 value)
{
    data_021c67a4->unk_21c = value;
    CameraControl_SetMode(data_021c67a4, CAMERA_MODE_17);
}
CLEAN_AS(func_0203aeec, CameraControl_SetMode17)

extern void MTX_Identity43_(Mtx43 *mtx);

/* func_0203caf0: a new camera from the auxiliary heap (zeroed), built as a process, then each
 * class's vtable in turn, the camera's own last; its view matrix starts as the identity. NULL
 * when the heap has no room. */
CameraControl *CameraControl_New(void)
{
    CameraControl *camera = Heap_AllocAuxZeroed(sizeof(CameraControl));
    if (camera != NULL) {
        Process_Construct((Process *) camera);
        camera->vtable = data_020da13c;
        camera->vtable = data_020e58cc;
        MTX_Identity43_(&camera->view_matrix);
        camera->vtable = data_020da87c;
    }
    return camera;
}
CLEAN_AS(func_0203caf0, CameraControl_New)
