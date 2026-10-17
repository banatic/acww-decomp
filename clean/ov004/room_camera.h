/* The field camera's modes that overlay 4 (the rooms) runs, and the calls the rest of the game
 * switches to them with (main/camera_control.h has the camera, main/camera_modes.h the modes
 * run from main). Each mode is a start, which loads the goal view and the move's timing, and a
 * frame, which moves the goal's second offset and places the camera:
 *
 *   2  (indoors) the goal of the focus on the player and a point (RoomCamera_FocusGoal)
 *   10 a preset at the point data_021fbee8, reached at once
 *   14 the preset of the camera's row and column at the point (16.0, 0, 17.0) (scenes 0x13,
 *      0x14 and 0x2f start in it; the gatekeepers' walk to the gate too)
 *   15 preset 0x1d at the same point (the gatekeepers' walk through the gate)
 *   16 between the player and the point looked at
 *   18 the cafe's show: the camera turns about one spot after another of fourteen
 *   20 the point looked at
 *
 * The functions that take no camera use the field camera (data_021c67a4).
 * REQUIRES: the camera exists for those that do not test it. */
#ifndef CLEAN_OV004_ROOM_CAMERA_H
#define CLEAN_OV004_ROOM_CAMERA_H

#include "autoload_2/vector.h"
#include "main/camera_control.h"
#include "types.h"

/* The modes started here (main's CameraControl_SetMode). */
enum RoomCameraMode {
    ROOM_CAMERA_MODE_11 = 0xb,
    ROOM_CAMERA_MODE_12 = 0xc,
    ROOM_CAMERA_MODE_14 = 0xe,
    ROOM_CAMERA_MODE_15 = 0xf,
    ROOM_CAMERA_MODE_BETWEEN = 0x10,
    ROOM_CAMERA_MODE_SHOW = 0x12,
    ROOM_CAMERA_MODE_LOOK_AT = 0x14
};

/* A spot of the cafe's show (data_ov004_022569ec, 0x24 bytes). The spots come in pairs (2k and
 * 2k + 1), and a pair once taken is not taken again for the next two picks. */
typedef struct RoomCameraSpot {
    Vec3 position;      /* 0x00: where the goal's offsets add up to */
    fx32 orbit_x;       /* 0x0c: the offset the camera turns about, x */
    fx32 orbit_z;       /* 0x10: and z */
    fx32 distance;      /* 0x14: the goal's distance */
    fx32 distance_step; /* 0x18: added to the distance each frame while it is over 1.25 */
    s16 yaw;            /* 0x1c: the goal's yaw */
    s16 pitch;          /* 0x1e: the goal's pitch */
    s16 turn_step;      /* 0x20: turned each frame */
    u8 unk_22[2];
} RoomCameraSpot;

/* Mode 18's data, at 0x21c of the camera (CameraControl.unk_21c on). */
typedef struct RoomCameraShow {
    s16 turn;        /* 0x21c: turned about the spot so far */
    s16 spot;        /* 0x21e: the spot, -1 before the first */
    s16 moving;      /* 0x220: 1 while the frame follows the spot */
    s16 previous[2]; /* 0x222: the two spots taken last, -1 for none */
    s16 slot;        /* 0x226: which of them the next pick replaces, 0 or 1 */
    s16 choices;     /* 0x228: how many spots a pick chooses among */
    u8 flags;        /* 0x22a: bits 0 and 1 cleared by the start */
} RoomCameraShow;

int RoomCamera_ResetGoalNow(void);
void RoomCamera_SetShowViews(CameraControl *camera);
void RoomCamera_PickShowSpot(CameraControl *camera);
void RoomCamera_SetShowClose(CameraControl *camera);
void RoomCamera_ShowFrame(CameraControl *camera);
int RoomCamera_ShowStart(CameraControl *camera);
void RoomCamera_ShowViews(void);
void RoomCamera_ShowNextSpot(void);
void RoomCamera_ShowClose(void);
int RoomCamera_SetModeShow(void);
int RoomCamera_SetModeLookAt(const Vec3 *point);
void RoomCamera_LookAtFrame(CameraControl *camera);
int RoomCamera_LookAtStart(CameraControl *camera);
int RoomCamera_SetMode15(void);
int RoomCamera_SetMode14(void);
void RoomCamera_Mode15Frame(CameraControl *camera);
int RoomCamera_Mode15Start(CameraControl *camera);
void RoomCamera_Mode14Frame(CameraControl *camera);
int RoomCamera_Mode14Start(CameraControl *camera);
void RoomCamera_BetweenFrame(CameraControl *camera);
int RoomCamera_BetweenStart(CameraControl *camera);
int RoomCamera_SetModeBetween(const Vec3 *point);
int RoomCamera_SetMode12(void);
int RoomCamera_SetMode11(void);
int RoomCamera_NookShopSize(void);
void RoomCamera_Mode10Frame(CameraControl *camera);
int RoomCamera_ResetGoal(CameraControl *camera);
int RoomCamera_Mode10Start(CameraControl *camera);
void RoomCamera_FocusGoal(CameraControl *camera, CameraView *view);

#endif
