/* A sound of overlay 4's scenes, and five bytes of main whose purpose is not known yet: the
 * kind of the last scene actor of overlay 9 that went away (data_021f4b48) and two flags
 * (data_021f4b18 and data_021f4b1c) the scenes' sound classes test (scene_sound.c,
 * music_queue.c). */
#ifndef CLEAN_MAIN_BLOCK_020B220C_H
#define CLEAN_MAIN_BLOCK_020B220C_H

#include "types.h"

void Block020b220c_PlaySceneSound(void);
int Block020b220c_GoneKind(void);
void Block020b220c_SetGoneKind(unsigned int kind);
u8 Block020b220c_Flag4b18(void);
void Block020b220c_ClearFlag4b18(void);
void Block020b220c_SetFlag4b18(void);
u8 Block020b220c_Flag4b1c(void);
void Block020b220c_ClearFlag4b1c(void);
void Block020b220c_SetFlag4b1c(void);

#endif
