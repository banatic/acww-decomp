/* The moon (kind SKY_OBJECT_MOON, entry 31; SkyEvents_UpdateMoon keeps it from 19:00 to 3:59).
 *
 * It crosses the sky over those nine hours (SkyMoon_Position): from x 272 to x -16, along an
 * arc from y 60 that is highest (y 44) at 23:30, its place taken again every 128 frames (by
 * data_021fbdd0, the frames drawn). It tints the overridable colours 10 to 14 of the objects'
 * palettes (SkyPalettes_SetOverride): each is mixed from the moon palettes of the hour and of
 * the next by the minute, between the palettes' colours 11 to 15 (a clear sky) and 3 to 7
 * (rain), by how clear the sky is: 1.0 at weather levels below 3, else 0, eased towards that
 * by 1/16 every 128 frames once the moon is up. */
#ifndef CLEAN_MAIN_SKY_MOON_H
#define CLEAN_MAIN_SKY_MOON_H

#include "autoload_2/vector.h"
#include "sky_object_kinds.h"
#include "sky_objects.h"
#include "types.h"

#define SKY_MOON_COLORS 5       /* the overridable colours it tints */
#define SKY_MOON_FIRST_COLOR 10 /* from colour 10 */

/* The words at 0x60 of the moon. */
typedef struct SkyMoonVars {
    u32 param;  /* 0x60 */
    u32 unk_64; /* 0x64 */
    u32 unk_68; /* 0x68 */
    fx32 clear; /* 0x6c: 1.0 under a clear sky, 0 in rain */
    u32 unk_70; /* 0x70 */
} SkyMoonVars;

/* A palette of the moon (in SkyFiles.palettes from 14: the hours from 19:00). */
typedef struct SkyMoonPalette {
    u16 colors[16];
} SkyMoonPalette;

#define SKY_MOON_RAIN_COLOR 3   /* the palette's colours 3 to 7: in rain */
#define SKY_MOON_CLEAR_COLOR 11 /* 11 to 15: under a clear sky */

void SkyMoon_TakeDown(SkyObject *object);
void SkyMoon_Run(SkyObject *object);
void SkyMoon_SetUp(SkyObject *object);
void SkyMoon_ClearColors(void);
void SkyMoon_RefreshColors(SkyObject *object);
void SkyMoon_StartColors(SkyObject *object);
void SkyMoon_EaseClear(SkyObject *object);
void SkyMoon_SetClear(SkyObject *object);
void SkyMoon_MixColors(SkyObject *object);
int SkyMoon_Position(Vec3 *position);

#endif
