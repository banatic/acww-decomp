/* The objects of the show (kind SKY_OBJECT_SHOW, launched by sky_show.h): what each one does
 * from its set-up to its take-down (SkyObjectKinds_SetUp, SkyObjectKinds_Run and
 * SkyObjectKinds_TakeDown call these by its kind).
 *
 * An object's look is the low four bits of its parameter (SKY_SHOW_PARAM_LOOK), its animation
 * that plus 0x1d. Four looks (animations 0x21, 0x24, 0x27 and 0x2a) are shells: a shell starts
 * below the screen and rises 4 pixels a frame, stretched at first, to its height (kept in its
 * position's z); there it grows until hidden and, 7 frames later, is done and bursts into two
 * objects of the show at that point: the looks two and one below its own, the second with bit
 * 30 of its parameter (a large shell: look 0 and look 1 with bit 30, both large). The other
 * looks are bursts: animated once, sized each frame from a table by the animation's frame, and
 * the burst without bit 30 tints two of the overridable colours (SkyPalettes_SetOverride) from
 * its place's colours, fading over frames 16 to 27, flickering from frame 11; bit 29 of its
 * parameter is set at frame 29 (SkyShow_PlaceFreeForLarge reads it).
 *
 * Every one is placed on the sky shifted by the camera (SkyShowObject_PlaceShifted): sideways
 * against the camera's distance from the middle of the town's width, and lower the farther
 * north the camera looks, the more the higher on the screen. */
#ifndef CLEAN_MAIN_SKY_SHOW_OBJECTS_H
#define CLEAN_MAIN_SKY_SHOW_OBJECTS_H

#include "autoload_2/vector.h"
#include "sky_object_kinds.h"
#include "sky_objects.h"
#include "types.h"

#define SKY_SHOW_OBJECT_ANIMATION_FIRST 0x1d /* the animation of look 0 */
#define SKY_SHOW_PARAM_SECOND 0x40000000u    /* the second object of a burst: it sets no colours */
#define SKY_SHOW_OBJECT_NO_COLOR 15          /* SkyShowObject_ColorIndex: none */

/* The words at 0x60 of an object of the show. */
typedef struct SkyShowObjectVars {
    u32 param;   /* 0x60: SKY_SHOW_PARAM_... */
    s32 timer;   /* 0x64: frames since it was set up */
    s32 wait;    /* 0x68: a shell's frames hidden before it bursts */
    fx32 base_x; /* 0x6c: its place before the camera's shift */
    fx32 base_y; /* 0x70 */
} SkyShowObjectVars;

/* An entry of data_020d2344: a place's colours, fading from one to the other. */
typedef struct SkyShowColors {
    u16 from;
    u16 to;
} SkyShowColors;

void SkyShowObject_TakeDown(SkyObject *object);
void SkyShowObject_ShellRun(SkyObject *object);
void SkyShowObject_BurstRun(SkyObject *object);
void SkyShowObject_Run(SkyObject *object);
void SkyShowObject_ShellSetUp(SkyObject *object, u32 param);
void SkyShowObject_BurstSetUp(SkyObject *object, u32 param);
void SkyShowObject_SetUp(SkyObject *object, int param);
void SkyShowObject_SetScale(SkyObject *object, int frame);
fx32 SkyShowObject_RiseDistance(fx32 unused, int frames);
void SkyShowObject_ClearColors(SkyObject *object);
void SkyShowObject_SetColors(SkyObject *object);
void SkyShowObject_PlaceShifted(Vec3 *position, fx32 x, fx32 y, int large);
int SkyShowObject_ColorIndex(int place, int large);

#endif
