/* The furniture's sounds: a row of four sound numbers for each of the 0x6e9 pieces of furniture
 * (data_ov004_02247fb4), looked up by the furniture's number. The room objects play them
 * (room_object_anims.h, room_point_sound.h); 0xffff is no sound. */
#ifndef CLEAN_OV004_FURNITURE_SOUNDS_H
#define CLEAN_OV004_FURNITURE_SOUNDS_H

#include "types.h"

#define FURNITURE_SOUND_ROWS 0x6e9
#define FURNITURE_SOUND_NONE 0xffff

typedef struct FurnitureSoundRow {
    u16 sounds[4];
} FurnitureSoundRow;

int FurnitureSounds_Sound3(int number);
int FurnitureSounds_Sound2(int number);
int FurnitureSounds_Sound1(int number);
u16 FurnitureSounds_Sound0(int number);
const FurnitureSoundRow *FurnitureSounds_Row(int number);

#endif
