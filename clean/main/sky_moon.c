/* The moon (sky_moon.h). */
#include "sky_moon.h"

#include "autoload_2/approach.h"
#include "calendar.h"
#include "clean.h"
#include "clock.h"
#include "sky.h"
#include "sky_resources.h"

static_assert(sizeof(SkyMoonVars) == 0x14, "the words at 0x60");
static_assert(sizeof(SkyMoonPalette) == 0x20, "a palette");

#define SKY_MOON_ANIMATION 0x12
#define SKY_MOON_PRIORITY 3
#define SKY_MOON_FRAMES_MASK 0x7f /* every 128 frames */
#define SKY_MOON_RISE_HOUR 19
#define SKY_MOON_SET_HOUR 4
#define SKY_MOON_SECONDS_TO_MIDNIGHT 0x4650 /* five hours */
#define SKY_MOON_SECONDS_UP 0x7e90          /* nine hours */
#define SKY_MOON_EASE_STEP 0x100

extern Sky data_021f75b0;
extern SkyPalettes data_021fba00;            /* the objects' palettes (0x2eb8 of the objects) */
extern const SkyMoonPalette data_021fb8bc[]; /* the moon's palettes, from 19:00 */
extern u16 data_021f6cfc[SKY_MOON_COLORS];   /* the colours mixed */
extern int data_021fbdd0;                    /* the frames drawn */

extern fx32 FX_MulFunc(fx32 a, fx32 b);
extern fx32 FX_Div(fx32 numerator, fx32 denominator);
extern fx32 FX_Sqrt(fx32 value);

static SkyMoonVars *sky_moon_vars(SkyObject *object)
{
    return (SkyMoonVars *) (void *) SkyObject_Body(object)->words;
}

/* Clear at the weather levels without rain or snow. */
static fx32 sky_moon_clear_for(s32 weather)
{
    return weather != SKY_WEATHER_RAIN && weather != SKY_WEATHER_HEAVY_RAIN ? 0x1000 : 0;
}

/* The moon's colours given to the objects' palettes. */
static void sky_moon_override_colors(void)
{
    for (u32 i = 0; i < SKY_MOON_COLORS; i++) {
        SkyPalettes_SetOverride(&data_021fba00, (int) (i + SKY_MOON_FIRST_COLOR), &data_021f6cfc[i]);
    }
}

/* func_020c0b1c: the moon taken down: its colours cleared. */
void SkyMoon_TakeDown(SkyObject *object)
{
    SkyMoon_ClearColors();
    SkyObjectKinds_Remove(object);
}
CLEAN_AS(func_020c0b1c, SkyMoon_TakeDown)

/* func_020c0b30: a frame of the moon: every 128 frames its place taken again (done once the
 * night is over) and its colours. */
void SkyMoon_Run(SkyObject *object)
{
    if ((data_021fbdd0 & SKY_MOON_FRAMES_MASK) != 0) {
        return;
    }
    if (!SkyMoon_Position(&object->position)) {
        object->state = SKY_OBJECT_DONE;
    }
    SkyMoon_RefreshColors(object);
}
CLEAN_AS(func_020c0b30, SkyMoon_Run)

/* func_020c0b60: the moon set up at its place for the time, with its colours; by day it is
 * done at once. */
void SkyMoon_SetUp(SkyObject *object)
{
    SkyObjectBody *body = SkyObject_Body(object);
    if (SkyMoon_Position(&body->position)) {
        body->animation = SKY_MOON_ANIMATION;
        body->priority = SKY_MOON_PRIORITY;
        SkyMoon_StartColors(object);
    } else {
        body->state = SKY_OBJECT_DONE;
    }
}
CLEAN_AS(func_020c0b60, SkyMoon_SetUp)

/* func_020c0b88: the moon's colours cleared from the objects' palettes. */
void SkyMoon_ClearColors(void)
{
    for (u32 i = 0; i < SKY_MOON_COLORS; i++) {
        SkyPalettes_ClearOverride(&data_021fba00, (int) (i + SKY_MOON_FIRST_COLOR));
    }
}
CLEAN_AS(func_020c0b88, SkyMoon_ClearColors)

/* func_020c0bac: how clear the sky is eased towards the weather it is changing to, and the
 * moon's colours mixed and given to the palettes. */
void SkyMoon_RefreshColors(SkyObject *object)
{
    SkyMoon_EaseClear(object);
    SkyMoon_MixColors(object);
    sky_moon_override_colors();
}
CLEAN_AS(func_020c0bac, SkyMoon_RefreshColors)

/* func_020c0be4: how clear the sky is set from the weather, and the moon's colours mixed and
 * given to the palettes. */
void SkyMoon_StartColors(SkyObject *object)
{
    SkyMoon_SetClear(object);
    SkyMoon_MixColors(object);
    sky_moon_override_colors();
}
CLEAN_AS(func_020c0be4, SkyMoon_StartColors)

/* func_020c0c1c: how clear the sky is moved by 1/16 towards the level the weather changes to. */
void SkyMoon_EaseClear(SkyObject *object)
{
    SkyMoonVars *vars = sky_moon_vars(object);
    fx32 target = sky_moon_clear_for(data_021f75b0.next_weather);
    int clear = vars->clear;
    Approach_S32(&clear, target, SKY_MOON_EASE_STEP);
    vars->clear = clear;
}
CLEAN_AS(func_020c0c1c, SkyMoon_EaseClear)

/* func_020c0c58: how clear the sky is, from the weather's level. */
void SkyMoon_SetClear(SkyObject *object)
{
    sky_moon_vars(object)->clear = sky_moon_clear_for(data_021f75b0.weather);
}
CLEAN_AS(func_020c0c58, SkyMoon_SetClear)

/* A component of two colours mixed: `a` by 1 - f and `b` by f. */
static fx32 sky_moon_mix(u32 a, u32 b, fx32 f, fx32 rest)
{
    fx32 first = FX_MulFunc((fx32) (a << 12), rest);
    return first + FX_MulFunc((fx32) (b << 12), f);
}

/* func_020c0c78: the moon's five colours: each mixed from this hour's palette and the next's
 * by the minute, for a clear sky (colours 11 to 15) and for rain (3 to 7), and those two by
 * how clear the sky is.
 * QUIRK: by day (4:00 to 18:59) the palettes read would be past the moon's, as the original
 * reads them; the moon only runs at night. */
void SkyMoon_MixColors(SkyObject *object)
{
    Time now;
    Calendar_Now(&now);
    u32 hour = now.hour;
    u32 minute = now.minute;
    int index = hour >= SKY_MOON_RISE_HOUR ? (int) hour - SKY_MOON_RISE_HOUR : (int) hour + 5;
    const SkyMoonPalette *this_hour = &data_021fb8bc[index];
    const SkyMoonPalette *next_hour = &data_021fb8bc[index + 1];
    fx32 clear = sky_moon_vars(object)->clear;
    fx32 rain = 0x1000 - clear;
    fx32 f = (fx32) (minute << 12) / 60;
    fx32 rest = 0x1000 - f;
    for (u32 i = 0; i < SKY_MOON_COLORS; i++) {
        u16 clear_a = this_hour->colors[SKY_MOON_CLEAR_COLOR + i];
        u16 clear_b = next_hour->colors[SKY_MOON_CLEAR_COLOR + i];
        u16 rain_a = this_hour->colors[SKY_MOON_RAIN_COLOR + i];
        u16 rain_b = next_hour->colors[SKY_MOON_RAIN_COLOR + i];
        fx32 red_clear = sky_moon_mix(clear_a & 0x1fu, clear_b & 0x1fu, f, rest);
        fx32 green_clear = sky_moon_mix((clear_a >> 5) & 0x1fu, (clear_b >> 5) & 0x1fu, f, rest);
        fx32 blue_clear = sky_moon_mix((clear_a >> 10) & 0x1fu, (clear_b >> 10) & 0x1fu, f, rest);
        fx32 red_rain = sky_moon_mix(rain_a & 0x1fu, rain_b & 0x1fu, f, rest);
        fx32 green_rain = sky_moon_mix((rain_a >> 5) & 0x1fu, (rain_b >> 5) & 0x1fu, f, rest);
        fx32 blue_rain = sky_moon_mix((rain_a >> 10) & 0x1fu, (rain_b >> 10) & 0x1fu, f, rest);
        fx32 red = FX_MulFunc(red_clear, clear);
        red += FX_MulFunc(red_rain, rain);
        fx32 green = FX_MulFunc(green_clear, clear);
        green += FX_MulFunc(green_rain, rain);
        fx32 blue = FX_MulFunc(blue_clear, clear);
        blue += FX_MulFunc(blue_rain, rain);
        u32 r = (u32) ((red + 0x800) >> 12);
        u32 g = (u32) ((green + 0x800) >> 12);
        u32 b = (u32) ((blue + 0x800) >> 12);
        data_021f6cfc[i] = (u16) (r | (g << 5) | (b << 10));
    }
}
CLEAN_AS(func_020c0c78, SkyMoon_MixColors)

/* func_020c0e44: the moon's place for the time, from 19:00 (x 272, y 60) to 4:00 (x -16) on
 * an arc highest at 23:30 (y 44); 0 by day, when it is left as it is. */
int SkyMoon_Position(Vec3 *position)
{
    Time now;
    Calendar_Now(&now);
    u32 hour = now.hour;
    u32 minute = now.minute;
    u32 second = (u32) Clock_Second();
    int night = 1;
    u32 seconds = 0;
    if (hour >= SKY_MOON_RISE_HOUR) {
        seconds = second + (60 * minute + 3600 * (hour - SKY_MOON_RISE_HOUR));
    } else if (hour < SKY_MOON_SET_HOUR) {
        seconds = second + (3600 * hour + SKY_MOON_SECONDS_TO_MIDNIGHT + 60 * minute);
    } else {
        night = 0;
    }
    if (night) {
        fx32 along = (fx32) ((seconds << 12) / SKY_MOON_SECONDS_UP);
        fx32 x = FX_MulFunc(-0x120000, along) + 0x110000;
        fx32 from_middle = along - 0x800;
        fx32 height = FX_Sqrt(0x1000 - FX_MulFunc(from_middle, from_middle));
        height = FX_Div(height - 0xddb, 0x225);
        position->x = x;
        position->y = height * -16 + 0x3c000;
        position->z = 0;
    }
    return night;
}
CLEAN_AS(func_020c0e44, SkyMoon_Position)
