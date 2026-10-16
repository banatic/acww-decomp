/* The drops of rain (kind SKY_OBJECT_RAIN) and the flakes of snow (SKY_OBJECT_SNOW) that
 * SkyEvents_Rain and SkyEvents_Snow add.
 *
 * Both start above the screen (or, added with parameter 1, anywhere down it), at a random x on
 * either half in turn, and move with the player: each frame they are shifted against the
 * player actor's sideways movement in the world (Actor.position less last_position) by a
 * factor of their layer, and wrapped around from one side to the other past x -20 or x 276.
 *
 * - A drop falls in a straight line, 0x24 a frame along an angle from the objects' wind
 *   (SkyObjects.unk_2f54) and Sky.unk_1538, turned to match, one of three looks; it is done
 *   once it has fallen to its own line, 256 to 447 pixels down by its look.
 * - A flake falls at its layer's speed, swaying sideways by a sine, and is done below y 468. */
#ifndef CLEAN_MAIN_SKY_FALLING_H
#define CLEAN_MAIN_SKY_FALLING_H

#include "sky_object_kinds.h"
#include "sky_objects.h"
#include "types.h"

/* The words at 0x60 of a drop or a flake. */
typedef struct SkyFallingVars {
    s32 speed;   /* 0x60: a flake: its sway's step; a drop: its line (pixels past 256) */
    s32 phase;   /* 0x64: a flake: its sway's angle (an s16 kept in a word) */
    s32 layer;   /* 0x68: a flake: its layer, 0 to 2; a drop: 0 */
    fx32 base_x; /* 0x6c: a flake: its x before the sway */
    fx32 sway;   /* 0x70: a flake: how far it sways */
} SkyFallingVars;

void SkySnow_TakeDown(SkyObject *object);
void SkySnow_Run(SkyObject *object);
void SkySnow_SetUp(SkyObject *object, int start);
void SkyRain_TakeDown(SkyObject *object);
void SkyRain_Run(SkyObject *object);
void SkyRain_SetUp(SkyObject *object, int start);

#endif
