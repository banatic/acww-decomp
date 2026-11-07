/* The marks and sounds of a scene object's steps (the member at 0x558 of an object of class
 * 0x020d8c64, obj_020d8c64.h): each frame (func_0201b910) it looks at the mode of the object's
 * scene mover (its member at 0x350, SceneMover_Mode, scene_mover.h). In the modes 1 to 3
 * (walking, walking 2, turning) it spawns effect 0x28 (func_020912d4) at the object's foot
 * points (0x490 and 0x484) on the frames 1 and 9 of the body's animation (at 0x188,
 * func_02056f28), and effect 0 too in mode 2, and plays the sound of the ground under the
 * object (func_020b1cb0) through its sound emitter at 0x514. Starting to move from mode 0
 * (standing) marks both feet at once. */
#ifndef CLEAN_MAIN_FOOTSTEPS_H
#define CLEAN_MAIN_FOOTSTEPS_H

#include "types.h"

typedef struct Footsteps {
    u8 enabled; /* 0x00: whether steps leave marks and sounds */
    u8 unk_01[3];
    s32 mode; /* 0x04: the scene mover's mode of the last frame (5 until the first) */
} Footsteps;

void Footsteps_Update(Footsteps *steps, void *object);
void Footsteps_PlaySound(Footsteps *steps, void *object);
void Footsteps_Disable(Footsteps *steps);
void Footsteps_Enable(Footsteps *steps);
void Footsteps_Init(Footsteps *steps);
void Footsteps_Destruct(Footsteps *steps);
void Footsteps_Construct(Footsteps *steps);

#endif
