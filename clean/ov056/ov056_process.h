/* Overlay 56: a process class that adds nothing to the game's process class (data_020da13c,
 * main's game_process.h): its vtable (data_ov056_022604b0) differs only by its destructors.
 * Scene 0x32 names overlay 56 in its SceneInfo (data_020e55bc, scene_process.h); the class is
 * process class 0xcd, whose profile (data_ov056_022604a0: execute order 0xcd, draw order 0xc9)
 * main's profile table data_020e3134 points to. An object is 0x50 bytes, a bare Process. */
#ifndef CLEAN_OV056_OV056_PROCESS_H
#define CLEAN_OV056_OV056_PROCESS_H

#include "autoload_2/process.h"
#include "types.h"

Process *Ov056Process_Create(void);
Process *Ov056Process_Destroy(Process *self);
Process *Ov056Process_Delete(Process *self);

#endif
