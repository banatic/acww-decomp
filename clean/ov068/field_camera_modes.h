/* The field camera's modes that live in overlay 68 (main's camera_modes.h has the others):
 * each a start and a frame in the mode table main fills (data_021c6820).
 *
 *   7  follow an actor: the point followed is the position of the actor kept in the mode's
 *      data (zero without one), with preset 0;
 *   8  a tour of the town: from the structure of items 0x5014 to 0x501a (stop 0) the point
 *      looked at glides, 60 frames after it arrives, to the next of seven stops, each the
 *      structure of an item range of its own (data_ov068_022772d4) in an acre with flags of its
 *      own, seen from an offset of its own; at the stop of the houses (0x5001 to 0x5008) and
 *      that of items 0x500d to 0x5010 the next item of the range is taken each time round, the
 *      latter with an offset for each of its four;
 *   9  sway: the point looked at is the origin, preset 16 with a field of view of 0x1c71; it
 *      rises and falls and the camera rolls, each on a sine whose speed and size change by
 *      stages (FieldCameraModes_SetRiseStage and FieldCameraModes_SetRollStage); main's mode 1
 *      keeps the rise after it (CameraControl_StillFrame);
 *   13 follow this console's player (the origin without one) with preset 0x1a.
 *
 * The modes keep their data in the camera's last 0x18 bytes (0x21c, CameraControl.unk_21c). */
#ifndef CLEAN_OV068_FIELD_CAMERA_MODES_H
#define CLEAN_OV068_FIELD_CAMERA_MODES_H

#include "autoload_2/vector.h"
#include "main/camera_control.h"
#include "types.h"

/* Mode 9's data. */
typedef struct FieldCameraSway {
    s16 rise_phase;  /* 0x00 (0x21c): an angle */
    s16 roll_phase;  /* 0x02 */
    u16 rise_frames; /* 0x04: the frames left of the rise's stage */
    u16 roll_frames; /* 0x06 */
    u8 rise_stage;   /* 0x08: 0-3 */
    u8 roll_stage;   /* 0x09 */
} FieldCameraSway;

/* A stage of the sway (the table data_020ca17c, four of them). */
typedef struct FieldCameraSwayStage {
    u16 frames; /* the least it lasts */
    u16 spread; /* and a random part below this */
    s16 speed;  /* added to the phase each frame; 0 holds still */
    u8 unk_06[2];
    fx32 size; /* of the sine */
} FieldCameraSwayStage;

/* Mode 8's data. */
typedef struct FieldCameraTour {
    s16 wait;           /* 0x00 (0x21c): frames before the next stop once arrived */
    s16 stop;           /* 0x02: 0-6 */
    Vec3 base;          /* 0x04: the centre of the stop's building's tile */
    const Vec3 *offset; /* 0x10: from it to the point looked at */
    int speed;          /* 0x14: the most the point moves in a frame (fx32), rising to 0x100 */
} FieldCameraTour;

int FieldCameraModes_Sway(CameraControl *camera);
void FieldCameraModes_SetRollStage(CameraControl *camera, u8 stage);
void FieldCameraModes_SetRiseStage(CameraControl *camera, u8 stage);
void FieldCameraModes_SwayFrame(CameraControl *camera);
int FieldCameraModes_SwayStart(CameraControl *camera);
void FieldCameraModes_PlayerFrame(CameraControl *camera);
int FieldCameraModes_PlayerStart(CameraControl *camera);
void FieldCameraModes_TourFrame(CameraControl *camera);
int FieldCameraModes_TourStart(CameraControl *camera);
void FieldCameraModes_ActorFrame(CameraControl *camera);
int FieldCameraModes_ActorStart(CameraControl *camera);

#endif
