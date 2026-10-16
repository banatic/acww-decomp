/* The field camera's object (a process of 0x234 bytes, vtable data_020da87c, built by
 * func_0203caf0; data_021c67a4 points to it while it exists; itcm/camera.h has the point it
 * looks at) and the functions the rest of the game drives it with: its mode (func_0203c0ac
 * switches to one of 21 and remembers the one before), its view, a saved copy of the view, the
 * move from one view to the next, and placing a point on the screen.
 *
 * A view (CameraView) is two angles, a distance and two offsets from the followed point. The
 * camera keeps the view it is going to (`goal`) and the one it shows (`current`), eased towards
 * the goal over a move: `move_time` counts the move's frames in 20.12 fixed point up to the
 * move's length (func_0203c4e4). */
#ifndef CLEAN_MAIN_CAMERA_CONTROL_H
#define CLEAN_MAIN_CAMERA_CONTROL_H

#include "autoload_2/matrix.h"
#include "autoload_2/vector.h"
#include "types.h"

typedef struct CameraView {
    s16 yaw;       /* about Y (Vec_RotateY in func_0203bd84) */
    s16 pitch;     /* about X */
    fx32 distance; /* from the point looked at */
    Vec3 offset;
    Vec3 second_offset;
} CameraView;

typedef struct CameraControl {
    const u8 *vtable;
    u8 unk_04[0x4c];
    Mtx43 view_matrix; /* 0x50 */
    u8 unk_80[0x38];
    fx32 unk_b8;
    fx32 unk_bc; /* 0xbc: func_0203c4e4 keeps the largest length here */
    u8 unk_c0[8];
    fx32 move_time; /* 0xc8: frames of the move so far, 20.12 */
    u8 unk_cc[0x30];
    CameraView goal;    /* 0xfc */
    CameraView saved;   /* 0x11c: the goal kept by func_0203b994, put back by func_0203b868 */
    Vec3 saved_point;   /* 0x13c: `point`, kept with it */
    CameraView current; /* 0x148 */
    Vec3 point;         /* 0x168 */
    u8 unk_174[0x50];
    u32 projection; /* 0x1c4: func_0203c53c */
    u8 unk_1c8[4];
    Vec3 look_at; /* 0x1cc */
    u8 unk_1d8[0x10];
    fx32 unk_1e8;      /* 0x1e8: eased towards the value at 0x1e4 (func_0203be6c) */
    s32 preset_column; /* 0x1ec: of the table of presets data_020ca158 */
    s32 preset_row;    /* 0x1f0 */
    u8 view_saved;     /* 0x1f4 */
    u8 unk_1f5;
    u8 unk_1f6;
    u8 sounds_muted;   /* 0x1f7: CameraControl_PlaySound plays nothing */
    s32 mode;          /* 0x1f8 */
    s32 previous_mode; /* 0x1fc */
    u8 unk_200[0x1c];
    u32 unk_21c; /* 0x21c: set with mode 17; ov068 counts frames in its low half */
    u16 unk_220; /* 0x220: ov068's length for its stage */
    u8 unk_222[2];
    u8 unk_224; /* 0x224: ov068's stage, 0-3 */
    u8 unk_225[0xf];
} CameraControl;

/* The camera's modes set here (func_0203c0ac). */
enum CameraControlMode {
    CAMERA_MODE_3 = 3,
    CAMERA_MODE_4 = 4,
    CAMERA_MODE_5 = 5,
    CAMERA_MODE_17 = 0x11,
    CAMERA_MODE_19 = 0x13
};

CameraControl *CameraControl_Destruct(CameraControl *camera);
CameraControl *CameraControl_DestructFree(CameraControl *camera);
void CameraControl_ScreenPosition(int *x, int *y, const Vec3 *point);
int CameraControl_ProjectPoint(int *x, int *y, const Vec3 *point);
int CameraControl_SelectPreset(int row, int column);
Mtx43 *CameraControl_ViewMatrix(void);
void CameraControl_PlaySound(CameraControl *camera, int number);
void CameraControl_UnmuteSounds(void);
void CameraControl_MuteSounds(void);
void CameraControl_SnapToPoint(const Vec3 *point);
void CameraControl_SetFlag1F5(void);
void CameraControl_StartStage3(void);
int CameraControl_RestoreView(void);
int CameraControl_SaveView(void);
int CameraControl_IsViewSaved(void);
void CameraControl_LoadKeptView(void);
void CameraControl_KeepView(void);
u8 CameraControl_MoveFramesLeft(void);
void CameraControl_RestartMove(void);
void CameraControl_EndMove(void);
int CameraControl_IsMoving(void);
u32 CameraControl_Value1E8(void);
int CameraControl_IsPastGoalZ(const Vec3 *point, int unused, fx32 size);
int CameraControl_LookAt(const Vec3 *at);
void CameraControl_SetMode5(void);
void CameraControl_SetMode4(void);
int CameraControl_SetPreviousMode(void);
void CameraControl_SetMode3(void);
void CameraControl_SetMode19(void);
void CameraControl_SetMode17(u32 value);

#endif
