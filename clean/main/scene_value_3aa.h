/* A pair of halfwords of a scene object (class 0x020d8c64, obj_020d8c64.h: its member at 0x3aa).
 * The motions set the second (scene_motion_kinds.h: -2 while still, 1 for a walk); the first is
 * graded below 100, below 800 or above (SceneValue3aa_Grade), which kind 9's run and overlays
 * 78 and 79 read. Overlays clear both when they set up their objects. */
#ifndef CLEAN_MAIN_SCENE_VALUE_3AA_H
#define CLEAN_MAIN_SCENE_VALUE_3AA_H

#include "types.h"

typedef struct SceneValue3aa {
    u16 value;  /* 0x00: graded */
    u16 second; /* 0x02: set by the motions */
} SceneValue3aa;

void SceneValue3aa_SetSecond(SceneValue3aa *self, int second);
int SceneValue3aa_Grade(SceneValue3aa *self);
void SceneValue3aa_Clear(SceneValue3aa *self);

#endif
