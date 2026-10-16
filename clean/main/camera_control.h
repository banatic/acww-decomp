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
    /* 0x80-0xb7: adjustments added to the view, the projection and the move's timing; all
     * cleared by CameraControl_ClearAdjustments. */
    fx32 extra_distance; /* 0x80: added to the current view's distance */
    Vec3 target_adjust;  /* 0x84: added to the point looked at (Camera.followed) */
    fx32 extra_near;     /* 0x90 */
    fx32 extra_far;      /* 0x94 */
    s16 extra_fov;       /* 0x98 */
    s16 extra_pitch;     /* 0x9a */
    s16 extra_yaw;       /* 0x9c */
    u8 unk_9e[2];
    fx32 extra_follow_radius; /* 0xa0 */
    u8 unk_a4[4];
    fx32 extra_delay;    /* 0xa8 */
    fx32 extra_length;   /* 0xac */
    fx32 extra_ease_in;  /* 0xb0 */
    fx32 extra_ease_out; /* 0xb4 */
    fx32 unk_b8;         /* 0xb8: the move's delay, 20.12 frames (CameraTiming) */
    fx32 unk_bc;         /* 0xbc: func_0203c4e4 keeps the largest length here */
    fx32 ease_in;        /* 0xc0 */
    fx32 ease_out;       /* 0xc4 */
    fx32 move_time;      /* 0xc8: frames of the move so far, 20.12 */
    Mtx43 inverse_view;  /* 0xcc: the inverse of the view matrix (the camera in the world) */
    CameraView goal;     /* 0xfc */
    CameraView saved;    /* 0x11c: the goal kept by func_0203b994, put back by func_0203b868 */
    Vec3 saved_point;    /* 0x13c: `point`, kept with it */
    CameraView current;  /* 0x148 */
    Vec3 point;          /* 0x168 */
    s16 roll;            /* 0x174: of the up vector, about Z */
    u8 unk_176[2];
    fx32 room_min_x;   /* 0x178: the bounds the point followed is kept in, indoors */
    fx32 room_max_x;   /* 0x17c */
    fx32 room_min_z;   /* 0x180 */
    fx32 room_max_z;   /* 0x184 */
    Vec3 drawn_target; /* 0x188: the point looked at, bent onto the curved ground */
    Vec3 drawn_eye;    /* 0x194: `point`, bent the same way */
    Vec3 up;           /* 0x1a0 */
    s16 ground_angle;  /* 0x1ac: of the curved ground under the eye */
    u8 unk_1ae[2];
    fx32 aspect;        /* 0x1b0 */
    fx32 near_distance; /* 0x1b4 */
    fx32 far_distance;  /* 0x1b8 */
    fx32 half_fov_sin;  /* 0x1bc */
    fx32 half_fov_cos;  /* 0x1c0 */
    u32 projection;     /* 0x1c4: func_0203c53c */
    s16 fov;            /* 0x1c8: the vertical field of view */
    u8 look_both;       /* 0x1ca: the focus is on `look_at` and `look_at2`, not only `look_at` */
    u8 unk_1cb;
    Vec3 look_at;      /* 0x1cc */
    Vec3 look_at2;     /* 0x1d8 */
    fx32 unk_1e4;      /* 0x1e4: what unk_1e8 is eased towards */
    fx32 unk_1e8;      /* 0x1e8: eased towards the value at 0x1e4 (func_0203be6c) */
    s32 preset_column; /* 0x1ec: of the table of presets data_020ca158 */
    s32 preset_row;    /* 0x1f0 */
    u8 view_saved;     /* 0x1f4 */
    u8 unk_1f5;
    u8 unk_1f6;
    u8 sounds_muted;   /* 0x1f7: CameraControl_PlaySound plays nothing */
    s32 mode;          /* 0x1f8 */
    s32 previous_mode; /* 0x1fc */
    s32 initial_mode;  /* 0x200: the mode it was created in; switching to it keeps the saved view */
    Vec3 fixed_target; /* 0x204: the point looked at and the eye, kept when mode 1 starts */
    Vec3 fixed_eye;    /* 0x210 */
    u32 unk_21c;       /* 0x21c: set with mode 17; ov068 counts frames in its low half */
    u16 unk_220;       /* 0x220: ov068's length for its stage */
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
