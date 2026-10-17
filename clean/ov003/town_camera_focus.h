/* The field camera's focus mode (mode 2, main/camera_modes.c) in the town: the goal set between
 * the player at this console and the point or points the camera focuses on, and the view
 * blended between the focus preset and the follow preset by how far apart they are. */
#ifndef CLEAN_OV003_TOWN_CAMERA_FOCUS_H
#define CLEAN_OV003_TOWN_CAMERA_FOCUS_H

#include "main/camera_control.h"

void TownCameraFocus_SetGoal(CameraControl *camera);

#endif
