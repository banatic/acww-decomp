/* A level between 0 and 1.0 (0x1000) that moves towards a target by a speed, or flashes
 * through a table of 11 levels after a wait of 5 frames: overlay 4's room objects glow by one
 * (ov004/room_object_parts.h, where the type is described), and so do the lights of overlay
 * 9's scene actors (building_lights.h).
 *
 * func_020b36c8 runs a frame of it, func_020b3720 switches it at once, func_020b3740 builds
 * it and func_020b373c takes it down. */
#ifndef CLEAN_MAIN_FADER_H
#define CLEAN_MAIN_FADER_H

#include "ov004/room_object_parts.h" /* Fader */
#include "types.h"

#define FADER_FULL 0x1000
#define FADER_FLASH_WAIT 5

int Fader_Level(const Fader *fader);
int Fader_Mix(int level, int from, int to);
int Fader_Switch(Fader *fader, int on, int fade, int flash, int speed);
void Fader_Run(Fader *fader);
void Fader_Set(Fader *fader, int on);
void Fader_Destruct(Fader *fader);
void Fader_Construct(Fader *fader);

#endif
