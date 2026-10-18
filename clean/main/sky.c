/* The town's sky (sky.h). */
#include "sky.h"

#include "autoload_2/heap.h"
#include "camera_control.h"
#include "clean.h"
#include "constellations.h"
#include "date_time.h"
#include "display_layers.h"
#include "display_shadow.h"
#include "line_handlers.h"
#include "main/actor.h"
#include "star_palette.h"
#include "state_block.h"
#include "state_flags.h"
#include "main_random.h"
#include "rom_file.h"
#include "scene_lights.h"
#include "session_players.h"
#include "sky_events.h"
#include "sky_objects.h"
#include "sky_resources.h"
#include "sky_shots.h"
#include "sky_weather_day.h"
#include "town_name.h"

static_assert(offsetof(Sky, cloud_scroll) == 0x1208, "the clouds' scroll");
static_assert(offsetof(Sky, blend_alpha) == 0x1210, "the blending tables");
static_assert(offsetof(Sky, shift) == 0x1514, "the shifts");
static_assert(offsetof(Sky, changing) == 0x1520, "the change");
static_assert(offsetof(Sky, precipitation) == 0x1534, "the precipitation");
static_assert(offsetof(Sky, stars_x) == 0x153c, "the stars");
static_assert(offsetof(Sky, hour_colors) == 0x1544, "the colour tables");
static_assert(offsetof(Sky, palettes) == 0x1564, "the palettes");
static_assert(offsetof(Sky, variant) == 0x1570, "the variant");
static_assert(offsetof(Sky, screen_data) == 0x157c, "the cloud screens");
static_assert(offsetof(Sky, step) == 0x158c, "the step");
static_assert(sizeof(Sky) == 0x1598, "the sky");
static_assert(sizeof(SkyObjectSlot) == 12, "an object slot");
static_assert(sizeof(SkyWeatherDay) == 8, "the day's weather");
static_assert(sizeof(SkyPalette) == 0x20, "a palette");

#define REG16(address) (*(volatile u16 *) (address))
#define REG32(address) (*(volatile u32 *) (address))
#define REG_DISPCNT REG32(0x04000000)
#define REG_BG1CNT REG16(0x0400000a)
#define REG_BG3CNT REG16(0x0400000e)
#define REG_BG1HOFS REG16(0x04000014)
#define REG_BG1VOFS REG16(0x04000016)
#define REG_BG3PA REG16(0x04000030)
#define REG_BG3X REG32(0x04000038)
#define REG_BG3Y REG32(0x0400003c)
#define REG_BLDCNT REG16(0x04000050)
#define REG_DB_DISPCNT REG32(0x04001000)
#define REG_DB_BG1CNT REG16(0x0400100a)
#define REG_DB_BG3CNT REG16(0x0400100e)
#define REG_DB_BG1HOFS REG16(0x04001014)
#define REG_DB_BG1VOFS REG16(0x04001016)
#define REG_DB_BG3PA REG16(0x04001030)
#define REG_DB_BG3X REG32(0x04001038)
#define REG_DB_BG3Y REG32(0x0400103c)
#define REG_DB_BLDCNT REG16(0x04001050)
#define REG_BACKDROP REG16(0x05000000)    /* the main screen's palette colour 0 */
#define REG_DB_BACKDROP REG16(0x05000400) /* the sub screen's */

#define DISPCNT_BG1 0x0200
#define DISPCNT_BG3 0x0800
#define PLANE_BG1 0x02
#define PLANE_BG3 0x08
#define PLANE_OBJ 0x10
#define BGCNT_PRIORITY 0x0003
#define BGCNT_KEPT 0x0043 /* the priority and the mosaic */
/* BLDCNT: the stars (background 1), nothing, or background 3 blended over the backdrop */
#define BLEND_BG1_OVER_BACKDROP 0x2042
#define BLEND_NONE_OVER_BACKDROP 0x2040
#define BLEND_BG3_OVER_BACKDROP 0x2048

/* The lines of the shift past which the main screen's sky hides its clouds and its stars. */
#define LINE_HIDE_BG3 0xa8
#define LINE_HIDE_BG1 0x97

/* The stars' night: 12 hours from 18:00, and the height they rise through. */
#define SKY_NIGHT_MINUTES 720
#define SKY_STARS_HEIGHT 0x68
#define SKY_STARS_HIDDEN 0x100
#define SKY_STARS_COLUMNS 64
#define SKY_STARS_WIDTH 0x200
#define SKY_DAY_START_HOUR 6
#define SKY_HOURS 24

#define SKY_CHARS_SIZE 0x1000
#define SKY_STARS_PATH data_020e7aa8
#define SKY_STARS_MAP_PATH data_020e7abc

/* The objects the sky process runs (SkyObjectSlot). */
#define SKY_OBJECT_SLOTS 5
#define SKY_OBJECTS_SLOTS_OFFSET 0x1b30
#define SKY_OBJECTS_2EB8_OFFSET 0x2eb8

extern u8 data_021f8b48[];
extern StarPalette data_021f7280;
extern StateBlock data_021dc7a8;
extern Heap *data_021fbe94;
extern void *data_021c67a4; /* the field camera (itcm/camera.h) */
extern u8 data_021fba88[];
extern u8 data_021f6cbc;     /* the clouds' tables were filled once */
extern s32 data_021f6ce8[2]; /* the X they were filled for, per set */
extern s32 data_021f6ce0[2]; /* the scroll they were filled for, per set */
extern u16 data_020e597c[2]; /* the blending they were filled for, per set */

/* The layers of each screen: the clouds' characters, the sky's palette, the stars and the
 * clouds' screen. */
extern const u8 data_020d22b0[];
extern const u8 data_020d22b4[];
extern const u8 data_020d22b8[];
extern const u8 data_020d22bc[];
extern const char *const data_020e6070[];        /* the clouds' characters per level */
extern const char *const *const data_020e5e0c[]; /* SkyCloudScreen: the cloud screens */
extern const s8 data_020d28ac[][SKY_HOURS];      /* the levels of a day's pattern, per hour */
extern const char data_020e7aa8[];               /* "menu/star/a_bg.bch" */
extern const char data_020e7abc[];               /* "menu/star/bg.bsc" */

extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
extern void func_01ffcd4c(void);
extern void func_01ffcd50(void);
extern void func_01ffceb8(void);
extern void func_020babb4(void);
extern void func_020bad44(void);
extern void func_020bab74(void);

/* The weather of the day (at 0x1737e of the state block). */
static SkyWeatherDay *weather_day(void)
{
    return (SkyWeatherDay *) (void *) data_021dc7a8.part_1737e;
}

static SkyObjectSlot *object_slots(void)
{
    return (SkyObjectSlot *) (void *) (data_021f8b48 + SKY_OBJECTS_SLOTS_OFFSET);
}

/* func_020ba340: the other set's shift used from now on, and func_020be2d4 run on the sky's
 * objects.
 * QUIRK: func_020be2d4's second argument is unused; the game passes 0x1500 bytes into the sky. */
void Sky_SwapLineShift(void)
{
    data_021f75b0.shift_index ^= 1;
    SkyObjects_ReloadChangedSlots((SkyObjects *) (void *) data_021f8b48, (u8 *) &data_021f75b0 + 0x1500);
}
CLEAN_AS(func_020ba340, Sky_SwapLineShift)

/* func_020ba35c */
void Sky_Objects020bdf68(int player)
{
    SkyShots_Fire((SkyObjects *) (void *) data_021f8b48, player);
}
CLEAN_AS(func_020ba35c, Sky_Objects020bdf68)

/* func_020ba36c */
void Sky_Objects020bdfd8(int arg)
{
    SkyEvents_Refresh((SkyObjects *) (void *) data_021f8b48, arg);
}
CLEAN_AS(func_020ba36c, Sky_Objects020bdfd8)

/* func_020ba37c: func_020bbc90 run on the sky (by ActivityLinkJobs). */
void Sky_ReseedForLink(void)
{
    Sky_DrawDayAngle(&data_021f75b0);
}
CLEAN_AS(func_020ba37c, Sky_ReseedForLink)

/* func_020ba38c: the same, by StateBlock_StartMode3. */
void Sky_ReseedForMode3(void)
{
    Sky_DrawDayAngle(&data_021f75b0);
}
CLEAN_AS(func_020ba38c, Sky_ReseedForMode3)

/* func_020ba39c: the same, by StateBlock_StartMode4. */
void Sky_ReseedForMode4(void)
{
    Sky_DrawDayAngle(&data_021f75b0);
}
CLEAN_AS(func_020ba39c, Sky_ReseedForMode4)

/* func_020ba3ac: the same, by StateBlock_StartMode2. */
void Sky_ReseedForMode2(void)
{
    Sky_DrawDayAngle(&data_021f75b0);
}
CLEAN_AS(func_020ba3ac, Sky_ReseedForMode2)

/* func_020ba3bc: the next time at which the stars are scrolled by (scroll_x, scroll_y) from
 * where they are now: as many days ahead as columns of 8 pixels to the right (the 0x200 pixels
 * round), at the time of the night the height gives (18:00 for 0, moved past 6:00 back to 5:00),
 * and a full round of 64 days later when that is not at least 30 minutes ahead.
 * QUIRK: the clock's time is first given to Sky_StarsYAt, whose answer is not used. */
void Sky_TimeForStarScroll(DateTime *when, int scroll_x, int scroll_y)
{
    DateTime now = {0};
    DateTime_Now(&now);
    Sky_StarsYAt(&data_021f75b0, &now);
    DateTime_SubtractHours(&now, SKY_DAY_START_HOUR);
    int today_x = Sky_StarsXAt(&data_021f75b0, &now);
    MI_CpuCopy8(&now, when, sizeof(DateTime));

    if (scroll_x < 0) {
        scroll_x += SKY_STARS_WIDTH;
    }
    if (scroll_x < today_x) {
        scroll_x += SKY_STARS_WIDTH;
    }
    DateTime_AddDays(when, (scroll_x - today_x) / 8);

    if (scroll_y < 0) {
        scroll_y = 0;
    } else if (scroll_y > SKY_STARS_HEIGHT) {
        scroll_y = SKY_STARS_HEIGHT;
    }
    when->hour = 18;
    when->minute = 0;
    when->second = 0;
    DateTime_AddMinutes(when, scroll_y * SKY_NIGHT_MINUTES / SKY_STARS_HEIGHT);
    if (when->hour == SKY_DAY_START_HOUR) {
        DateTime_SubtractHours(when, 1);
    }

    DateTime_Now(&now);
    DateTime_AddMinutes(&now, 30);
    if (DateTime_Compare(&now, when, DATE_TIME_MINUTE | DATE_TIME_HOUR | DATE_TIME_DAY | DATE_TIME_MONTH | DATE_TIME_YEAR) ==
        1) {
        DateTime_AddDays(when, SKY_STARS_COLUMNS);
    }
}
CLEAN_AS(func_020ba3bc, Sky_TimeForStarScroll)

/* func_020ba488 */
unsigned short Sky_StarsY(void)
{
    return data_021f75b0.stars_y;
}
CLEAN_AS(func_020ba488, Sky_StarsY)

/* func_020ba494 */
unsigned short Sky_StarsX(void)
{
    return data_021f75b0.stars_x;
}
CLEAN_AS(func_020ba494, Sky_StarsX)

/* func_020ba4a0: the palette shown: the mix during a change of colours, else the level's. */
SkyPalette *Sky_ShownPalette(void)
{
    if (data_021f75b0.next_weather != data_021f75b0.weather) {
        return data_021f75b0.palettes[2];
    }
    return data_021f75b0.palettes[0];
}
CLEAN_AS(func_020ba4a0, Sky_ShownPalette)

/* func_020ba4b8 */
int Sky_Precipitation(void)
{
    return data_021f75b0.precipitation;
}
CLEAN_AS(func_020ba4b8, Sky_Precipitation)

/* func_020ba4c4 */
void Sky_GetWeathers(s32 *weather, s32 *next_weather)
{
    *weather = data_021f75b0.weather;
    *next_weather = data_021f75b0.next_weather;
}
CLEAN_AS(func_020ba4c4, Sky_GetWeathers)

/* func_020ba4d4: the level of the pattern for this hour. */
int Sky_WeatherNow(void)
{
    return Sky_WeatherInHours(&data_021f75b0, 0);
}
CLEAN_AS(func_020ba4d4, Sky_WeatherNow)

/* func_020ba4e4: what falls from the sky (SkyFalling) at levels 2 to 4, else nothing. */
int Sky_Falling(void)
{
    switch (data_021f75b0.weather) {
        case 2:
        case 3:
        case 4:
            if (data_021f75b0.precipitation == SKY_FALLING_RAIN) {
                return SKY_FALLING_RAIN;
            }
            if (data_021f75b0.precipitation == SKY_FALLING_SNOW) {
                return SKY_FALLING_SNOW;
            }
            return SKY_FALLING_NONE;
        default:
            return SKY_FALLING_NONE;
    }
}
CLEAN_AS(func_020ba4e4, Sky_Falling)

/* func_020ba518: the sky taken off the main screen: no HBlank function, Sky_VBlankOff each
 * VBlank, its clouds and stars hidden. */
void Sky_HideOnMain(void)
{
    LineHandlers_RequestChange(&data_021f6d2c, (int) (uintptr_t) func_01ffcd4c, (int) (uintptr_t) func_020bab74);
    DisplayShadow_HideMainPlanes(PLANE_BG1 | PLANE_BG3);
}
CLEAN_AS(func_020ba518, Sky_HideOnMain)

/* The stars are hidden from 6:00 to 17:59. */
static int is_daytime(void)
{
    Time now;
    Calendar_Now(&now);
    return now.hour >= SKY_DAY_START_HOUR && now.hour < 18;
}

/* func_020ba540: the sky shown on `screen`: background mode 1 there, the stars shown at night
 * only, the objects and the clouds shown, backgrounds 1 (the stars, priority 3) and 3 (the
 * clouds, priority 2) set up, and its HBlank and VBlank functions asked for. Its clouds, stars
 * and colours are loaded unless it is already set up on the sub screen; 1 when they were.
 * The player's Z is taken as the clouds' reference in any case.
 * HW: each BGCNT is read and written in this order. */
int Sky_ShowOn(int screen)
{
    int loaded = 0;

    if (screen == SKY_SCREEN_SUB) {
        DisplayShadow_SetSubBgMode(1);
        if (is_daytime()) {
            DisplayShadow_HideSubPlanes(PLANE_BG1);
        } else {
            DisplayShadow_ShowSubPlanes(PLANE_BG1);
        }
        DisplayShadow_ShowSubPlanes(PLANE_OBJ);
        DisplayShadow_ShowSubPlanes(PLANE_BG3);
        REG_DB_BG1CNT = (u16) ((REG_DB_BG1CNT & ~BGCNT_PRIORITY) | 3);
        REG_DB_BG3CNT = (u16) ((REG_DB_BG3CNT & ~BGCNT_PRIORITY) | 2);
        REG_DB_BG1CNT = (u16) ((REG_DB_BG1CNT & BGCNT_KEPT) | 0x4c00); /* 256x256, map base 12 */
        REG_DB_BG3CNT = (u16) ((REG_DB_BG3CNT & BGCNT_KEPT) | 0x6f00); /* 256x256, wraps, map base 15 */
        LineHandlers_RequestChange(&data_021f6d2c, (int) (uintptr_t) func_01ffceb8, (int) (uintptr_t) func_020bad44);
    } else {
        DisplayShadow_SetMainBgMode(1);
        if (is_daytime()) {
            DisplayShadow_HideMainPlanes(PLANE_BG1);
        } else {
            DisplayShadow_ShowMainPlanes(PLANE_BG1);
        }
        DisplayShadow_ShowMainPlanes(PLANE_OBJ);
        DisplayShadow_ShowMainPlanes(PLANE_BG3);
        REG_BG1CNT = (u16) ((REG_BG1CNT & ~BGCNT_PRIORITY) | 3);
        REG_BG3CNT = (u16) ((REG_BG3CNT & ~BGCNT_PRIORITY) | 2);
        REG_BG1CNT = (u16) ((REG_BG1CNT & BGCNT_KEPT) | 0x4400); /* 256x256, map base 4 */
        REG_BG3CNT = (u16) ((REG_BG3CNT & BGCNT_KEPT) | 0x6700); /* 256x256, wraps, map base 7 */
        LineHandlers_RequestChange(&data_021f6d2c, (int) (uintptr_t) func_01ffcd50, (int) (uintptr_t) func_020babb4);
    }

    if ((u32) screen != data_021f75b0.screen || screen == SKY_SCREEN_MAIN) {
        if (Sky_LoadClouds(screen) && Sky_ReloadChangeRows(screen) && Sky_LoadStars(screen)) {
            data_021f75b0.screen = (u32) screen;
            Sky_ResetObjects();
            loaded = 1;
        }
    }

    /* The game also checks the address of the player's position, which is never null. */
    Actor *player = SessionPlayers_ActorOf(4);
    data_021f75b0.player_z = 0;
    if (player != NULL) {
        data_021f75b0.player_z = player->position.z;
    }
    return loaded;
}
CLEAN_AS(func_020ba540, Sky_ShowOn)

/* func_020ba6b8: the five object slots marked not loaded, then the sky's objects refreshed. */
void Sky_ResetObjects(void)
{
    SkyObjectSlot *slots = object_slots();
    for (int i = 0; i < SKY_OBJECT_SLOTS; i++) {
        slots[i].loaded = 0;
    }
    SkyPalettes_Forget((SkyPalettes *) (void *) (data_021f8b48 + SKY_OBJECTS_2EB8_OFFSET), -1);
    SkyObjects_LoadSlots((SkyObjects *) (void *) data_021f8b48);
    SkyObjects_ResetTime((SkyObjects *) (void *) data_021f8b48);
}
CLEAN_AS(func_020ba6b8, Sky_ResetObjects)

/* func_020ba6f4: the stars of `screen`: their characters (16 to 31), their map with the
 * players' constellations marked in it, and their twinkling started; 1 when all loaded. */
int Sky_LoadStars(int screen)
{
    Heap *heap = data_021fbe94;
    u8 layer = data_020d22b8[screen];

    if (!DisplayLayer_LoadCharsFromFile(SKY_STARS_PATH, heap, layer, 0x10, 0x10, 0x1f)) {
        return 0;
    }
    u16 *map = Heap_AllocBack(heap, SKY_CHARS_SIZE);
    if (map == NULL) {
        return 0;
    }
    RomFile_Read(SKY_STARS_MAP_PATH, map, SKY_CHARS_SIZE);
    Constellations_MarkSkyMap(map);
    int loaded = DisplayLayer_LoadScreen(map, layer, SKY_CHARS_SIZE, 0);
    Heap_Free(heap, map);
    if (!loaded) {
        return 0;
    }
    StarPalette_Start(&data_021f7280, layer);
    return 1;
}
CLEAN_AS(func_020ba6f4, Sky_LoadStars)

/* func_020ba78c: the rows of the change's cloud screen already drawn over the old clouds,
 * drawn again on `screen`'s layer; 1 when there are none or they were.
 * Once the colours are the level's (`next_weather` is `weather`), the rows not yet replaced by
 * the level's clouds are the ones drawn, from the change's screen up or down to the level
 * during SKY_STEP_LOAD and SKY_STEP_FINISH.
 * QUIRK: the change's screen is loaded again into change_screen_data, from the kind the
 * direction gives even when it is the level's own number. */
int Sky_ReloadChangeRows(int screen)
{
    Sky *sky = &data_021f75b0;
    if (sky->changing == 0 || sky->direction == SKY_DIRECTION_NONE) {
        return 1;
    }

    u32 direction = sky->direction;
    int rows = sky->row;
    int weather = sky->weather;
    int colors_settled = sky->next_weather == weather;
    if (colors_settled && rows >= 0) {
        rows = SKY_MAP_ROWS - rows;
    }
    if (rows <= 0) {
        return 1;
    }

    u8 layer = data_020d22bc[screen];
    int target;
    int kind;
    if (direction == SKY_DIRECTION_UP) {
        target = weather + 1;
        kind = SKY_CLOUDS_UP;
    } else {
        target = weather - 1;
        kind = SKY_CLOUDS_DOWN;
    }
    if ((sky->step == SKY_STEP_LOAD || sky->step == SKY_STEP_FINISH) && colors_settled) {
        target = weather;
    }
    if (!Sky_LoadCloudChars(sky, target, layer)) {
        return 0;
    }
    if (!Sky_LoadCloudScreen(sky, &sky->change_screen_data, &sky->change_screen_size, kind, target)) {
        return 0;
    }

    u8 *data = sky->change_screen_data;
    int size = rows * SKY_MAP_ROW_SIZE;
    int offset = 0;
    if (target == sky->weather) {
        offset = (SKY_MAP_ROWS - rows) * SKY_MAP_ROW_SIZE;
        data += offset;
    }
    return DisplayLayer_LoadScreen(data, layer, size, offset) != 0;
}
CLEAN_AS(func_020ba78c, Sky_ReloadChangeRows)

/* func_020ba86c: the colours and the level's clouds on `screen`: the colour tables and
 * palettes, the clouds' characters and screen; 1 when all loaded. */
int Sky_LoadClouds(int screen)
{
    int weather = data_021f75b0.weather;
    u8 layer = data_020d22b0[screen];

    if (!Sky_LoadColors(screen)) {
        return 0;
    }
    if (!Sky_LoadCloudChars(&data_021f75b0, weather, layer)) {
        return 0;
    }
    if (!Sky_LoadCloudScreen(&data_021f75b0, &data_021f75b0.screen_data, &data_021f75b0.screen_size, SKY_CLOUDS_LEVEL,
                             weather)) {
        return 0;
    }
    if (!DisplayLayer_LoadScreen(data_021f75b0.screen_data, layer, (int) data_021f75b0.screen_size, 0)) {
        return 0;
    }
    return 1;
}
CLEAN_AS(func_020ba86c, Sky_LoadClouds)

/* func_020baad8: the frame function while the sky is not drawn: the change of weather timed
 * (unless state flag 1 is set), then the colours worked out. */
void Sky_FrameHidden(void)
{
    u32 seconds, fade;
    if (!StateFlags_Test1()) {
        Sky_StepChangeHidden(&data_021f75b0);
    }
    Sky_ColorWeights(&data_021f75b0, &seconds, &fade);
    Sky_UpdateColors();
}
CLEAN_AS(func_020baad8, Sky_FrameHidden)

/* func_020bab04: the frame function while the sky is drawn: the gradient, and unless state flag
 * 1 is set the clouds and the change of weather; the colours; with a field camera the shift the
 * other set's lines will use (from the state flags' value and the camera's); the stars'
 * height.
 * REQUIRES: shift_index is 0 or 1. */
void Sky_Frame(void)
{
    Sky_UpdateGradient();
    if (!StateFlags_Test1()) {
        Sky_UpdateClouds();
        Sky_StepChange(&data_021f75b0);
    }
    Sky_LoadPalette((int) data_021f75b0.screen);
    if (data_021c67a4 != NULL) {
        int from_flags = (StateFlags_ValueOrZero() * 0x123) >> 12;
        int from_camera = ((int) CameraControl_Value1E8() * 0x1e) >> 12;
        data_021f75b0.shift[data_021f75b0.shift_index ^ 1] = from_flags + from_camera;
    }
    data_021f75b0.stars_y = (u16) Sky_StarsYNow(&data_021f75b0);
}
CLEAN_AS(func_020bab04, Sky_Frame)

/* func_020bab74: the VBlank function of the main screen without the sky: the sub screen's
 * backdrop the gradient's top colour, the main one the last line's colour of the first table,
 * backgrounds 1 and 3 off.
 * HW: the sub backdrop, the main backdrop, then DISPCNT read and written. */
void Sky_VBlankOff(void)
{
    REG_DB_BACKDROP = data_021f6f70.top_color;
    REG_BACKDROP = data_021f6f70.colors[0][SCREEN_LINES - 1];
    REG_DISPCNT &= ~(u32) (DISPCNT_BG1 | DISPCNT_BG3);
}
CLEAN_AS(func_020bab74, Sky_VBlankOff)

/* The first line's clouds of the set shown.
 * REQUIRES: shown is 0 or 1. */
static const LineAffine *first_line_clouds(void)
{
    return &data_021f75b0.clouds[data_021f75b0.shown][0];
}

/* The stars' vertical scroll with the shift, at most SKY_STARS_HIDDEN. */
static u16 stars_scroll_y(int shift)
{
    u32 y = (u16) (shift + data_021f75b0.stars_y);
    return (u16) (y > SKY_STARS_HIDDEN ? SKY_STARS_HIDDEN : y);
}

/* func_020babb4: the VBlank function of the sky on the main screen: both backdrops the
 * gradient's top colour; background 3 set for the first line; the stars hidden by day; past
 * line LINE_HIDE_BG3 of the shift the clouds and stars hidden, past LINE_HIDE_BG1 the stars; the
 * blending; the stars' scroll; window 0 covering the lines the shift leaves to the sky.
 * REQUIRES: shift_index and shown are 0 or 1.
 * HW: the backdrops, BG3PA, BG3X, BG3Y, DISPCNT (read and written), BLDCNT and the stars'
 * scroll are accessed in this order, between the calls. */
void Sky_VBlankMain(void)
{
    int shift = data_021f75b0.shift[data_021f75b0.shift_index];

    REG_DB_BACKDROP = data_021f6f70.top_color;
    REG_BACKDROP = data_021f6f70.top_color;
    const LineAffine *clouds = first_line_clouds();
    REG_BG3PA = (u16) clouds->scale_x;
    REG_BG3X = (u32) clouds->x;
    REG_BG3Y = (u32) clouds->y;

    if (is_daytime()) {
        REG_DISPCNT &= ~(u32) DISPCNT_BG1;
        DisplayShadow_HideMainPlanes(PLANE_BG1);
    } else {
        REG_DISPCNT |= DISPCNT_BG1;
        DisplayShadow_ShowMainPlanes(PLANE_BG1);
    }

    if (shift > LINE_HIDE_BG3) {
        REG_DISPCNT &= ~(u32) (DISPCNT_BG1 | DISPCNT_BG3);
        DisplayShadow_HideMainPlanes(PLANE_BG1 | PLANE_BG3);
        REG_BLDCNT = BLEND_NONE_OVER_BACKDROP;
    } else {
        REG_DISPCNT |= DISPCNT_BG3;
        DisplayShadow_ShowMainPlanes(PLANE_BG3);
        if (shift > LINE_HIDE_BG1) {
            REG_DISPCNT &= ~(u32) DISPCNT_BG1;
            DisplayShadow_HideMainPlanes(PLANE_BG1);
            REG_BLDCNT = BLEND_BG3_OVER_BACKDROP;
        } else if (data_021fba88[0x11]) {
            REG_BLDCNT = BLEND_NONE_OVER_BACKDROP;
        } else {
            REG_BLDCNT = BLEND_BG1_OVER_BACKDROP;
        }
    }

    int sky_lines = SCREEN_LINES - shift;
    if (sky_lines < 0) {
        sky_lines = 0;
    } else if (sky_lines > SCREEN_LINES) {
        sky_lines = SCREEN_LINES;
    }

    REG_BG1VOFS = stars_scroll_y(shift);
    REG_BG1HOFS = data_021f75b0.stars_x;

    DisplayShadow_EnableMainWindows(1);
    DisplayShadow_SetMainWindow0Planes(0x15);
    DisplayShadow_SetMainOutsidePlanes(0x1f);
    DisplayShadow_SetMainWindow0(0, (u8) sky_lines, 0xff, SCREEN_LINES);
}
CLEAN_AS(func_020babb4, Sky_VBlankMain)

/* func_020bad44: the VBlank function of the sky on the sub screen: its backdrop the gradient's
 * top colour, the main screen's its bottom colour; background 3 set for the first line; the
 * stars hidden by day (the display copy left alone while state flag 1 is set); the blending;
 * the stars' scroll.
 * REQUIRES: shift_index and shown are 0 or 1.
 * HW: the backdrops, BG3PA, BG3X, BG3Y, DISPCNT (read and written), BLDCNT and the stars'
 * scroll are accessed in this order, between the calls. */
void Sky_VBlankSub(void)
{
    int shift = data_021f75b0.shift[data_021f75b0.shift_index];

    REG_DB_BACKDROP = data_021f6f70.top_color;
    REG_BACKDROP = data_021f6f70.bottom_color;
    const LineAffine *clouds = first_line_clouds();
    REG_DB_BG3PA = (u16) clouds->scale_x;
    REG_DB_BG3X = (u32) clouds->x;
    REG_DB_BG3Y = (u32) clouds->y;

    if (is_daytime()) {
        REG_DB_DISPCNT &= ~(u32) DISPCNT_BG1;
        if (!StateFlags_Test1()) {
            DisplayShadow_HideSubPlanes(PLANE_BG1);
        }
    } else {
        REG_DB_DISPCNT |= DISPCNT_BG1;
        if (!StateFlags_Test1()) {
            DisplayShadow_ShowSubPlanes(PLANE_BG1);
        }
    }

    REG_DB_BLDCNT = data_021fba88[0x11] ? BLEND_NONE_OVER_BACKDROP : BLEND_BG1_OVER_BACKDROP;
    REG_DB_BG1VOFS = stars_scroll_y(shift);
    REG_DB_BG1HOFS = data_021f75b0.stars_x;
}
CLEAN_AS(func_020bad44, Sky_VBlankSub)

/* The scale of background 3 on `line`: the clouds seen in perspective, 1 (0x100) at the top
 * line and twice as large near the bottom. */
static s16 clouds_scale(int line)
{
    int rise = -(line << 8) / SCREEN_LINES;
    return (s16) (0x10000 / (rise + 0x200));
}

/* func_020bae60: the clouds' tables of the set not shown, which is then shown. The clouds
 * scroll by 0x60 a frame, faster or slower as the player walks up or down (the change of Z);
 * their X follows the player's X / 8. The tables of both sets are filled once, then moved by the
 * change of X and of scroll since the set was last filled. The blending of the clouds (from
 * func_020655c4(1)) is the same down to line 0x76, fades out to line 0x96, then the backdrop
 * fades in over 16 lines; written again only when it changed.
 * QUIRK: the scroll wraps back below 0x10000 but not below 0.
 * REQUIRES: shown is 0 or 1. */
void Sky_UpdateClouds(void)
{
    Sky *sky = &data_021f75b0;
    int x = 0;
    int speed_up = 0;
    int set = (int) (sky->shown + 1) % 2;
    u16 *blend = sky->blend_alpha[set];

    /* The game also checks the address of the player's position, which is never null. */
    Actor *player = SessionPlayers_ActorOf(4);
    if (player != NULL) {
        x = player->position.x >> 3;
        int z = player->position.z;
        int moved = (z - sky->player_z) >> 4;
        if (moved < 0) {
            speed_up = (moved * -0xb0) >> 8;
        } else {
            speed_up = -(moved * 0x80) >> 8;
        }
        sky->player_z = z;
    }

    int scroll = sky->cloud_scroll + 0x60 + speed_up;
    if (scroll >= 0x10000) {
        scroll -= 0x10000;
    }
    sky->cloud_scroll = scroll;

    if (data_021f6cbc == 0) {
        data_021f6cbc = 1;
        for (int i = 0; i < 2; i++) {
            data_021f6ce8[i] = x;
            data_021f6ce0[i] = scroll;
            LineAffine *line = sky->clouds[i];
            for (int j = 0; j < SCREEN_LINES; j++, line++) {
                line->scale_x = clouds_scale(j);
                line->x = x - (line->scale_x - 0x100) * 128;
                int depth = (0xc000 * j / SCREEN_LINES + 0x3000) / SCREEN_LINES;
                line->y = scroll + SCREEN_LINES * ((depth * depth) >> 8);
            }
        }
    }

    int dx = x - data_021f6ce8[set];
    int dscroll = scroll - data_021f6ce0[set];
    if (dx != 0 || dscroll != 0) {
        data_021f6ce8[set] = x;
        data_021f6ce0[set] = scroll;
        LineAffine *line = sky->clouds[set];
        for (int j = 0; j < SCREEN_LINES; j++, line++) {
            if (dx != 0) {
                line->x += dx;
            }
            if (dscroll != 0) {
                line->y += dscroll;
            }
        }
    }

    u32 alpha = SceneLights_LightLevel(1);
    if (alpha != data_020e597c[set]) {
        data_020e597c[set] = (u16) alpha;
        int n = 0;
        for (; n < 0x77; n++) {
            *blend++ = (u16) (alpha | 0x1000);
        }
        for (; n < 0x97; n++) {
            *blend++ = (u16) ((alpha - ((alpha * (u32) (n - 0x77)) >> 5)) | 0x1000);
        }
        for (; n < 0x98; n++) {
            *blend++ = 0x10;
        }
        for (; n < 0xa8; n++) {
            int backdrop = n - 0x98;
            *blend++ = (u16) ((0x10 - backdrop) | (backdrop << 8));
        }
        for (; n < SCREEN_LINES; n++) {
            *blend++ = 0x1000;
        }
    }
    sky->shown = (u32) set;
}
CLEAN_AS(func_020bae60, Sky_UpdateClouds)

/* A colour component's mix: `a` weighted by 0x100 - t, `b` by t. */
static u16 mix(int a, int b, int t)
{
    return (u16) ((a * (0x100 - t) + b * t) >> 8);
}

/* func_020bb090: the backdrop gradient of the set not shown, which is then shown: the top colour
 * down to top_line, the bottom colour from bottom_line, a mix of the two between.
 * REQUIRES: data_021f6f70.shown is 0 or 1. */
void Sky_UpdateGradient(void)
{
    LineGradient *gradient = &data_021f6f70;
    int set = (int) (gradient->shown + 1) % 2;
    u16 top = gradient->top_color;
    u16 bottom = gradient->bottom_color;
    u16 *colors = gradient->colors[set];
    int top_line = gradient->top_line;
    int bottom_line = gradient->bottom_line;
    int span = bottom_line - top_line;

    for (int y = 0; y < SCREEN_LINES; y++) {
        if (y <= top_line) {
            colors[y] = top;
        } else if (y >= bottom_line) {
            colors[y] = bottom;
        } else {
            int t = ((y - top_line) << 8) / span;
            u16 red = mix(top & 0x1f, bottom & 0x1f, t);
            u16 green = mix((top >> 5) & 0x1f, (bottom >> 5) & 0x1f, t);
            u16 blue = mix((top >> 10) & 0x1f, (bottom >> 10) & 0x1f, t);
            colors[y] = (u16) ((blue << 10) | red | (green << 5));
        }
    }
    gradient->shown = (u32) set;
}
CLEAN_AS(func_020bb090, Sky_UpdateGradient)

/* func_020bb18c: an end of the gradient (0 the top, 1 the bottom): its colour and line. */
void Sky_SetGradientEnd(LineGradient *gradient, int end, unsigned short color, unsigned int line)
{
    *(u16 *) ((uintptr_t) &gradient->top_color + (u32) end * 2) = color;
    *(u32 *) ((uintptr_t) &gradient->top_line + (u32) end * 4) = line;
}
CLEAN_AS(func_020bb18c, Sky_SetGradientEnd)

/* func_020bb1b0: the stars' height now. */
int Sky_StarsYNow(Sky *sky)
{
    DateTime now = {0};
    DateTime_Now(&now);
    return Sky_StarsYAt(sky, &now);
}
CLEAN_AS(func_020bb1b0, Sky_StarsYNow)

/* func_020bb1d4: the stars' height at `when`: 0 at 18:00 rising to 0x67 at 5:59 (at
 * SKY_STARS_HEIGHT / 12 an hour), SKY_STARS_HIDDEN from 6:00 to 17:59. */
int Sky_StarsYAt(Sky *sky, const DateTime *when)
{
    (void) sky;
    int hours = (when->hour + 6) % SKY_HOURS;
    if (hours >= 12) {
        return SKY_STARS_HIDDEN;
    }
    int minutes = hours * 60 + when->minute;
    return (minutes * (SKY_STARS_HEIGHT << 12) / SKY_NIGHT_MINUTES) >> 12;
}
CLEAN_AS(func_020bb1d4, Sky_StarsYAt)

/* func_020bb214: the stars' scroll on the day of `when`: a column of 8 pixels a day since
 * 2000-01-01, round in 64 days.
 * QUIRK: a date before 2000 gives a negative remainder, cut to 16 bits. */
int Sky_StarsXAt(Sky *sky, const DateTime *when)
{
    (void) sky;
    DateTime start = {0};
    start.day = 1;
    start.month = 1;
    return (u16) ((DateTime_DaysBetween(&start, when) % SKY_STARS_COLUMNS) * 8);
}
CLEAN_AS(func_020bb214, Sky_StarsXAt)

/* func_020bb240: a frame of the change of weather while the sky is not drawn. */
void Sky_StepChangeHidden(Sky *sky)
{
    if (sky->changing == 0) {
        return;
    }
    switch (sky->step) {
        case SKY_STEP_START:
            Sky_HiddenStart(sky);
            break;
        case SKY_STEP_FADE:
            Sky_HiddenFade(sky);
            break;
        case SKY_STEP_LOAD:
            Sky_HiddenLoad(sky);
            break;
        case SKY_STEP_FINISH:
            Sky_HiddenFinish(sky);
            break;
    }
}
CLEAN_AS(func_020bb240, Sky_StepChangeHidden)

/* The level asked for reached: the change over; else the next level's change started. */
static void end_change(Sky *sky)
{
    if (sky->target_weather == sky->weather) {
        sky->step = SKY_STEP_IDLE;
        sky->target_weather = -1;
        sky->direction = SKY_DIRECTION_NONE;
        sky->changing = 0;
    } else {
        sky->step = SKY_STEP_START;
    }
}

/* func_020bb290: SKY_STEP_FINISH while hidden: after SKY_CHANGE_FRAMES frames the level is
 * reached. */
void Sky_HiddenFinish(Sky *sky)
{
    sky->frames++;
    if (sky->frames < SKY_CHANGE_FRAMES) {
        return;
    }
    end_change(sky);
}
CLEAN_AS(func_020bb290, Sky_HiddenFinish)

/* func_020bb2ec: SKY_STEP_LOAD while hidden: nothing to load. */
void Sky_HiddenLoad(Sky *sky)
{
    sky->fade = SKY_FADE_STEPS;
    sky->step = SKY_STEP_FINISH;
    sky->frames = 0;
}
CLEAN_AS(func_020bb2ec, Sky_HiddenLoad)

/* func_020bb30c: SKY_STEP_FADE while hidden: the colours faded over SKY_CHANGE_FRAMES frames,
 * then the next level is the level. */
void Sky_HiddenFade(Sky *sky)
{
    sky->frames++;
    if (sky->frames >= SKY_CHANGE_FRAMES) {
        Sky_SetWeathers(sky, sky->next_weather, sky->next_weather);
        sky->step = SKY_STEP_LOAD;
    }
    sky->fade = sky->frames * SKY_FADE_STEPS / SKY_CHANGE_FRAMES;
}
CLEAN_AS(func_020bb30c, Sky_HiddenFade)

/* func_020bb35c: SKY_STEP_START while hidden: a level towards the one asked for. */
void Sky_HiddenStart(Sky *sky)
{
    int weather = sky->weather;
    int next = sky->target_weather > weather ? weather + 1 : weather - 1;
    Sky_SetWeathers(sky, weather, next);
    sky->fade = 0;
    sky->step = SKY_STEP_FADE;
    sky->frames = 0;
}
CLEAN_AS(func_020bb35c, Sky_HiddenStart)

/* func_020bb3a4: a frame of the change of weather while the sky is drawn. */
void Sky_StepChange(Sky *sky)
{
    if (sky->changing == 0) {
        return;
    }
    switch (sky->step) {
        case SKY_STEP_START:
            Sky_ChangeStart(sky);
            break;
        case SKY_STEP_FADE:
            Sky_ChangeFade(sky);
            break;
        case SKY_STEP_LOAD:
            Sky_ChangeLoad(sky);
            break;
        case SKY_STEP_FINISH:
            Sky_ChangeFinish(sky);
            break;
    }
}
CLEAN_AS(func_020bb3a4, Sky_StepChange)

/* The row of the clouds' map just above the view, which can be replaced unseen. */
static int hidden_row(const Sky *sky)
{
    return (((sky->cloud_scroll >> 8) - 8) & 0xff) >> 3;
}

/* func_020bb3f4: SKY_STEP_FINISH while drawn: the level's clouds drawn over the change's, a
 * row when it is out of view; after the last row the level is reached. The clouds are on the
 * sub screen's background 3. */
void Sky_ChangeFinish(Sky *sky)
{
    int row = sky->row;
    int hidden = hidden_row(sky);
    if (hidden != row) {
        return;
    }
    if (!DisplayLayer_LoadScreen(sky->screen_data + hidden * SKY_MAP_ROW_SIZE, LAYER_SUB_BG3, SKY_MAP_ROW_SIZE,
                                 hidden * SKY_MAP_ROW_SIZE)) {
        return;
    }
    row++;
    if (row >= SKY_MAP_ROWS) {
        row = -1;
        end_change(sky);
    }
    sky->row = row;
}
CLEAN_AS(func_020bb3f4, Sky_ChangeFinish)

/* func_020bb480: SKY_STEP_LOAD while drawn: the level's clouds loaded. */
void Sky_ChangeLoad(Sky *sky)
{
    int weather = sky->weather;
    if (Sky_LoadCloudChars(sky, weather, LAYER_SUB_BG3) &&
        Sky_LoadCloudScreen(sky, &sky->screen_data, &sky->screen_size, SKY_CLOUDS_LEVEL, weather)) {
        sky->row = 0;
        sky->fade = SKY_FADE_STEPS;
        sky->step = SKY_STEP_FINISH;
    }
}
CLEAN_AS(func_020bb480, Sky_ChangeLoad)

/* func_020bb4e0: SKY_STEP_FADE while drawn: the change's clouds drawn, a row when it is out of
 * view, and the colours faded a step a row; after the last row the next level is the level,
 * with the cloud variant drawn for the change. */
void Sky_ChangeFade(Sky *sky)
{
    int row = sky->row;
    int hidden = hidden_row(sky);
    if (hidden != row) {
        return;
    }
    int offset = hidden * SKY_MAP_ROW_SIZE;
    if (!DisplayLayer_LoadScreen(sky->change_screen_data + offset, LAYER_SUB_BG3, SKY_MAP_ROW_SIZE, offset)) {
        return;
    }
    int fade = sky->fade + 1;
    row++;
    if (row >= SKY_MAP_ROWS) {
        row = -1;
        fade = SKY_FADE_STEPS;
        Sky_SetWeathers(sky, sky->next_weather, sky->next_weather);
        sky->variant = sky->next_variant;
        sky->step = SKY_STEP_LOAD;
    }
    sky->row = row;
    sky->fade = fade;
}
CLEAN_AS(func_020bb4e0, Sky_ChangeFade)

/* func_020bb568: SKY_STEP_START while drawn: the change's clouds a level towards the one asked
 * for loaded; func_020bbc90 run when the change goes from a dry level to a wet one. */
void Sky_ChangeStart(Sky *sky)
{
    int kind;
    int next;
    if (sky->direction == SKY_DIRECTION_UP) {
        kind = SKY_CLOUDS_UP;
        next = sky->weather + 1;
    } else {
        kind = SKY_CLOUDS_DOWN;
        next = sky->weather - 1;
    }
    if (Sky_LoadCloudChars(sky, next, LAYER_SUB_BG3) &&
        Sky_LoadCloudScreen(sky, &sky->change_screen_data, &sky->change_screen_size, kind, next)) {
        Sky_SetWeathers(sky, sky->weather, next);
        if (sky->weather < SKY_WEATHER_RAIN && sky->next_weather >= SKY_WEATHER_RAIN) {
            Sky_DrawDayAngle(sky);
        }
        sky->row = 0;
        sky->fade = 0;
        sky->step = SKY_STEP_FADE;
    }
}
CLEAN_AS(func_020bb568, Sky_ChangeStart)

/* func_020bb608: a cloud screen file (data_020e5e0c[kind]: for SKY_CLOUDS_LEVEL the level's
 * variant, else the change's to `weather`) read into *data, which is allocated on the first use
 * (*size its size); 1 when read. */
int Sky_LoadCloudScreen(Sky *sky, u8 **data, u32 *size, int kind, int weather)
{
    int index = kind == SKY_CLOUDS_LEVEL ? weather * 2 + sky->variant : weather;
    const char *path = data_020e5e0c[kind][index];
    if (*data == NULL) {
        *data = RomFile_Load(path, data_021fbe94, -4, size);
        return *data != NULL;
    }
    return RomFile_Read(path, *data, (int) *size) != 0;
}
CLEAN_AS(func_020bb608, Sky_LoadCloudScreen)

/* func_020bb66c: the clouds' characters of `weather` (16 to 47, 256 colours) on `layer`; 1 when
 * loaded. */
int Sky_LoadCloudChars(Sky *sky, int weather, int layer)
{
    (void) sky;
    return DisplayLayer_LoadChars256FromFile(data_020e6070[weather], data_021fbe94, layer, 16, 16, 47) != 0;
}
CLEAN_AS(func_020bb66c, Sky_LoadCloudChars)

/* func_020bb6a0: the level of `pattern` at `hour` (counted from 6:00). The address is computed
 * as the ARM does, whatever the indices. */
signed char Sky_WeatherOfPattern(Sky *sky, int pattern, int hour)
{
    (void) sky;
    return *(const s8 *) ((uintptr_t) data_020d28ac + (u32) pattern * SKY_HOURS + (u32) hour);
}
CLEAN_AS(func_020bb6a0, Sky_WeatherOfPattern)

/* func_020bb6b0: the level of today's pattern `hours` after the hour asked for last. */
int Sky_WeatherInHours(Sky *sky, int hours)
{
    const SkyWeatherDay *day = weather_day();
    int hour = (hours + day->hour) % SKY_HOURS;
    return Sky_WeatherOfPattern(sky, day->pattern, hour);
}
CLEAN_AS(func_020bb6b0, Sky_WeatherInHours)

/* func_020bb6d8: on a new hour, the day's weather brought up to date and the next hour's level
 * of the pattern asked for (the day marked wet for levels 3 and 4); the hour is taken once the
 * level is or will be shown. */
void Sky_UpdateHour(Sky *sky)
{
    SkyWeatherDay *day = weather_day();
    DateTime now = {0};
    DateTime_Now(&now);
    if ((day->hour + 6) % SKY_HOURS == now.hour) {
        return;
    }
    SkyWeatherDay_Update(day, &now);
    int weather = Sky_WeatherInHours(sky, 1);
    if (weather == SKY_WEATHER_RAIN || weather == SKY_WEATHER_HEAVY_RAIN) {
        day->wet = 1;
    }
    if (!Sky_RequestWeather(sky, weather)) {
        return;
    }
    int hour = now.hour - SKY_DAY_START_HOUR;
    if (hour < 0) {
        hour += SKY_HOURS;
    }
    day->hour = (s8) hour;
}
CLEAN_AS(func_020bb6d8, Sky_UpdateHour)

/* func_020bb75c: a change to level `weather` asked for: 1 when it is the level already or the
 * change started; 0 for -1 or while another change is under way. */
int Sky_RequestWeather(Sky *sky, int weather)
{
    if (weather == -1) {
        return 0;
    }
    if (weather == sky->weather) {
        return 1;
    }
    if (sky->changing != 0) {
        return 0;
    }
    Sky_SetTarget(sky, weather);
    sky->step = SKY_STEP_START;
    sky->changing = 1;
    return 1;
}
CLEAN_AS(func_020bb75c, Sky_RequestWeather)

/* func_020bb7a0: the level asked for, its direction, and the cloud variant after the change
 * drawn at random. */
void Sky_SetTarget(Sky *sky, int weather)
{
    sky->target_weather = weather;
    sky->direction = weather > sky->weather ? SKY_DIRECTION_UP : SKY_DIRECTION_DOWN;
    sky->next_variant = (s32) MainRandom_Below(2);
}
CLEAN_AS(func_020bb7a0, Sky_SetTarget)

/* func_020bb7e0: the level and the next level; what falls is the level's, else the next one's. */
void Sky_SetWeathers(Sky *sky, int weather, int next_weather)
{
    int falling = Sky_FallingKindOf(sky, weather);
    int next_falling = Sky_FallingKindOf(sky, next_weather);
    if (falling != SKY_FALLING_NONE) {
        sky->precipitation = falling;
    } else if (next_falling != SKY_FALLING_NONE) {
        sky->precipitation = next_falling;
    } else {
        sky->precipitation = SKY_FALLING_NONE;
    }
    sky->weather = weather;
    sky->next_weather = next_weather;
}
CLEAN_AS(func_020bb7e0, Sky_SetWeathers)

/* func_020bb830: what falls at level `weather` today: snow at levels 3 and 4 in periods 0 to 2
 * and 14 to 18 of the year (Calendar_PeriodAOf), rain at them otherwise, else nothing. */
int Sky_FallingKindOf(Sky *sky, int weather)
{
    (void) sky;
    DateTime now = {0};
    DateTime_Now(&now);
    if (weather != SKY_WEATHER_RAIN && weather != SKY_WEATHER_HEAVY_RAIN) {
        return SKY_FALLING_NONE;
    }
    switch (Calendar_PeriodAOf(&now)) {
        case 0:
        case 1:
        case 2:
        case 14:
        case 15:
        case 16:
        case 17:
        case 18:
            return SKY_FALLING_SNOW;
        default:
            return SKY_FALLING_RAIN;
    }
}
CLEAN_AS(func_020bb830, Sky_FallingKindOf)

/* func_020bb89c: the colour tables and the three palette buffers; then the palette loaded on
 * `screen` when the sky is drawn, else only the colours worked out; 1 when all done. */
int Sky_LoadColors(int screen)
{
    if (!Sky_LoadHourColors() || !Sky_AllocPalettes(data_021f75b0.palettes)) {
        return 0;
    }
    if (data_021f6cd8 != 0) {
        return Sky_LoadPalette(screen);
    }
    Sky_UpdateColors();
    return 1;
}
CLEAN_AS(func_020bb89c, Sky_LoadColors)

/* func_020bb8e0: the sky reset to this hour's level of the pattern (the day marked wet for
 * levels 3 and 4), no change under way, the cloud variant drawn at random, and the stars set
 * for now. */
void Sky_Reset(Sky *sky)
{
    int weather = Sky_WeatherInHours(sky, 0);
    if (weather == SKY_WEATHER_RAIN || weather == SKY_WEATHER_HEAVY_RAIN) {
        weather_day()->wet = 1;
    }
    Sky_SetWeathers(sky, weather, weather);
    sky->screen = SKY_SCREEN_MAIN;
    sky->step = SKY_STEP_IDLE;
    sky->target_weather = -1;
    sky->direction = SKY_DIRECTION_NONE;
    sky->next_variant = (s32) MainRandom_Below(2);
    sky->variant = sky->next_variant;
    sky->changing = 0;
    sky->row = 0;
    sky->fade = 0;

    DateTime now = {0};
    DateTime_Now(&now);
    sky->stars_y = (u16) Sky_StarsYAt(sky, &now);
    DateTime_SubtractHours(&now, SKY_DAY_START_HOUR);
    sky->stars_x = (u16) Sky_StarsXAt(sky, &now);
}
CLEAN_AS(func_020bb8e0, Sky_Reset)

/* The sky's colours of the hour: each level's hour colours (two sets of two half-days of 12
 * palettes, files of data_020e5fe0) mixed between this hour and the next by the minute, then
 * between the level and the next level by the fade; the light colours, light levels and fog
 * offset of the 3D scene mixed the same way from the tables of each level. */

#include "autoload_2/fx_math.h"
#include "display_3d.h"
#include "scene_display.h"

#define SKY_WEIGHT_ONE 0x1000      /* the weights are fractions of 0x1000 */
#define SKY_MIXED_COLORS 6         /* the palette colours mixed: 0 to 5 */
#define SKY_HALF_DAY_HOURS 12      /* palettes of a half-day's colour table */
#define SKY_HOUR_PALETTE_SIZE 0x20 /* bytes of a palette in it */
#define SKY_LIGHT_COLORS 4
#define SKY_LIGHT_LEVELS 2
#define SKY_CLEAR_DEPTH 0x1c2
#define SKY_DAY_ANGLE_RANGE 0x2aaa /* a sixth of a turn */

extern const char *const data_020e5fe0[2][2];       /* the hour colour files */
extern const s32 data_020d2364[SKY_WEATHER_LEVELS]; /* the set of hour colours per level */
extern const u16 *const *const data_020e6084[];     /* per level: 4 light colours per hour */
extern const u16 *const data_020e6098[];            /* per level: the fog offset per hour */
extern const u8 *const *const data_020e60c0[];      /* per level: 2 light levels per hour */
extern u16 data_021f6cf0[SKY_LIGHT_COLORS];         /* the light colours of now */
extern u8 data_021f6cf8[SKY_LIGHT_LEVELS];          /* the light levels of now */
extern void NNS_G3dGlbMaterialColorSpecEmi(int specular, unsigned short emission, int shininess);

/* func_020bb998: the destructor (registered at start-up): nothing to do. */
void Sky_Destruct(Sky *sky)
{
    (void) sky;
}
CLEAN_AS(func_020bb998, Sky_Destruct)

/* func_020bb99c: the constructor: no screen, no change, no buffers, no row, the shifts 0, no
 * precipitation; then the day's angle drawn. */
Sky *Sky_Construct(Sky *sky)
{
    sky->screen = 0;
    sky->changing = 0;
    sky->screen_data = NULL;
    sky->change_screen_data = NULL;
    sky->step = SKY_STEP_IDLE;
    sky->row = -1;
    sky->shift[0] = 0;
    sky->shift[1] = 0;
    sky->shift_index = 0;
    sky->palettes[0] = NULL;
    sky->palettes[1] = NULL;
    sky->palettes[2] = NULL;
    sky->precipitation = SKY_FALLING_NONE;
    Sky_DrawDayAngle(sky);
    return sky;
}
CLEAN_AS(func_020bb99c, Sky_Construct)

/* The palette of `hour` (0 to 23) in the hour colours of level `weather`.
 * REQUIRES: weather is a level. */
static const SkyPalette *hour_palette(int weather, int hour)
{
    int set = data_020d2364[weather];
    int half = hour >= SKY_HALF_DAY_HOURS ? 1 : 0;
    const u8 *table = data_021f75b0.hour_colors[set][half];
    return (const SkyPalette *) (const void *) (table + (hour - half * SKY_HALF_DAY_HOURS) * SKY_HOUR_PALETTE_SIZE);
}

/* func_020bba14: the palettes of now: the level's (this hour's colours towards the next hour's
 * by the minute), during a change of colours the next level's and the mix of the two by the
 * fade; the gradient's ends from the palette shown (the top at line 0, the bottom at line
 * 0xc0); then the light of the 3D scene.
 * REQUIRES: weather and next_weather are levels. */
void Sky_UpdateColors(void)
{
    Sky *sky = &data_021f75b0;
    u32 minute_weight = 0;
    u32 fade_weight = 0;
    Sky_ColorWeights(sky, &minute_weight, &fade_weight);
    Time now;
    Calendar_Now(&now);
    int hour = now.hour;
    int next_hour = (int) ((u32) (hour + 1) % SKY_HOURS);

    Sky_MixPalette(sky->palettes[0], hour_palette(sky->weather, hour), hour_palette(sky->weather, next_hour),
                   (int) minute_weight);
    const SkyPalette *shown;
    if (sky->next_weather != sky->weather) {
        Sky_MixPalette(sky->palettes[1], hour_palette(sky->next_weather, hour), hour_palette(sky->next_weather, next_hour),
                       (int) minute_weight);
        Sky_MixPalette(sky->palettes[2], sky->palettes[0], sky->palettes[1], (int) fade_weight);
        shown = sky->palettes[2];
    } else {
        shown = sky->palettes[0];
    }
    Sky_SetGradientEnd(&data_021f6f70, 0, shown->gradient_top, 0);
    Sky_SetGradientEnd(&data_021f6f70, 1, shown->gradient_bottom, SCREEN_LINES);
    Sky_UpdateLight((int) minute_weight, (int) fade_weight);
}
CLEAN_AS(func_020bba14, Sky_UpdateColors)

/* func_020bbb20: the colours of now worked out, and the palette shown (the mix during a change
 * of colours, else the level's) loaded as colours 1 on `screen`'s layer; its answer. */
int Sky_LoadPalette(int screen)
{
    Sky_UpdateColors();
    SkyPalette *palette =
        data_021f75b0.next_weather != data_021f75b0.weather ? data_021f75b0.palettes[2] : data_021f75b0.palettes[0];
    return DisplayLayer_LoadPalettes((u8 *) palette, data_020d22b4[screen], 1, 1, 1);
}
CLEAN_AS(func_020bbb20, Sky_LoadPalette)

/* func_020bbb6c: the weights of the colours' mixes: the minute's in its hour (minute / 60 of
 * SKY_WEIGHT_ONE, rounded down) and, during a change of colours, the fade's. */
void Sky_ColorWeights(Sky *sky, u32 *minute_weight, u32 *fade_weight)
{
    Time now;
    Calendar_Now(&now);
    *minute_weight = ((u32) now.minute * 0x44445) >> 12;
    if (sky->next_weather != sky->weather) {
        *fade_weight = (u32) ((s32) ((u32) sky->fade << 12) / SKY_FADE_STEPS);
    } else {
        *fade_weight = 0;
    }
}
CLEAN_AS(func_020bbb6c, Sky_ColorWeights)

/* func_020bbbc0: colours 0 to 5 of a palette mixed from two (`weight` of the second). */
void Sky_MixPalette(SkyPalette *dst, const SkyPalette *a, const SkyPalette *b, int weight)
{
    u16 *to = (u16 *) (void *) dst;
    const u16 *from_a = (const u16 *) (const void *) a;
    const u16 *from_b = (const u16 *) (const void *) b;
    for (int i = 0; i < SKY_MIXED_COLORS; i++) {
        Sky_MixColor(to + i, from_a + i, from_b + i, weight);
    }
}
CLEAN_AS(func_020bbbc0, Sky_MixPalette)

/* A component of an RGB555 colour mixed, cut to its 5 bits and put back in its place. */
static u16 mix_component(u16 a, u16 b, int shift, int weight)
{
    int value = ((a >> shift) & 0x1f) * (SKY_WEIGHT_ONE - weight) + ((b >> shift) & 0x1f) * weight;
    return (u16) (((value >> 12) & 0x1f) << shift);
}

/* func_020bbbf0: an RGB555 colour mixed from two (`weight` of the second, of SKY_WEIGHT_ONE),
 * its top bit cleared. */
void Sky_MixColor(u16 *dst, const u16 *a, const u16 *b, int weight)
{
    u16 from_a = *a;
    u16 from_b = *b;
    *dst = (u16) (mix_component(from_a, from_b, 0, weight) | mix_component(from_a, from_b, 5, weight) |
                  mix_component(from_a, from_b, 10, weight));
}
CLEAN_AS(func_020bbbf0, Sky_MixColor)

/* func_020bbc90: the day's angle (Sky.unk_1538), within a twelfth of a turn either way, drawn
 * from the town's number and today's date (the day, month and year).
 * QUIRK: the generator is seeded with 1 before it is seeded with the date. */
void Sky_DrawDayAngle(Sky *sky)
{
    DateTime now = {0};
    StateBlockTown town;
    TownName_CopyTo((const u16 *) &data_021dc7a8.town, (u16 *) &town);
    DateTime_Now(&now);
    u32 seed = now.day | ((u32) now.month << 5) | ((u32) town.number << 16) | ((u32) (now.year & 0x1f) << 9);

    Random random;
    Random_Init(&random, 1);
    Random_Init(&random, seed);
    sky->unk_1538 = (u16) (Random_Below(&random, SKY_DAY_ANGLE_RANGE) - SKY_DAY_ANGLE_RANGE / 2);
}
CLEAN_AS(func_020bbc90, Sky_DrawDayAngle)

/* func_020bbcfc: the three palette buffers allocated where missing; 0 when one could not be. */
int Sky_AllocPalettes(SkyPalette **palettes)
{
    for (int i = 0; i < 3; i++) {
        if (palettes[i] == NULL) {
            palettes[i] = Heap_AllocCurrentBack(sizeof(SkyPalette));
            if (palettes[i] == NULL) {
                return 0;
            }
        }
    }
    return 1;
}
CLEAN_AS(func_020bbcfc, Sky_AllocPalettes)

/* func_020bbd30: the four hour colour tables read, each allocated on its first use; 0 when one
 * could not be. */
int Sky_LoadHourColors(void)
{
    Sky *sky = &data_021f75b0;
    for (int set = 0; set < 2; set++) {
        for (int half = 0; half < 2; half++) {
            u8 *table = sky->hour_colors[set][half];
            const char *path = data_020e5fe0[set][half];
            if (table == NULL) {
                sky->hour_colors[set][half] = RomFile_Load(path, data_021fbe94, -4, &sky->hour_colors_size[set][half]);
                if (sky->hour_colors[set][half] == NULL) {
                    return 0;
                }
            } else {
                RomFile_Read(path, table, (int) sky->hour_colors_size[set][half]);
            }
        }
    }
    return 1;
}
CLEAN_AS(func_020bbd30, Sky_LoadHourColors)

/* func_020bbef4: a light level of now (1: the clouds' blending).
 * The address is computed as the ARM does, whatever the index. */
unsigned char Sky_LightLevel(int index)
{
    return *(const u8 *) ((uintptr_t) data_021f6cf8 + (u32) index);
}
CLEAN_AS(func_020bbef4, Sky_LightLevel)

/* func_020bbf00: a light colour of now (2: the 3D materials' emission).
 * The address is computed as the ARM does, whatever the index. */
short Sky_LightColor(int index)
{
    return *(const s16 *) ((uintptr_t) data_021f6cf0 + (u32) index * 2);
}
CLEAN_AS(func_020bbf00, Sky_LightColor)

/* func_020bbf0c: the 3D scene's light of now: the light colours, light levels and fog offset
 * mixed between this hour and the next; when the sky is drawn no fog, the clear depth
 * SKY_CLEAR_DEPTH and the clear colour the gradient's bottom; the materials' emission. */
void Sky_UpdateLight(int minute_weight, int fade_weight)
{
    Time now;
    Calendar_Now(&now);
    unsigned int hour = now.hour;
    unsigned int next_hour = (hour + 1) % SKY_HOURS;
    Sky_MixLightColors(minute_weight, fade_weight, (int) hour, (int) next_hour);
    Sky_MixLightLevels(minute_weight, fade_weight, hour, next_hour);
    Sky_MixFogOffset((unsigned int) minute_weight, (unsigned int) fade_weight, hour, next_hour);
    if (data_021f6cd8 != 0) {
        SceneDisplay_SetFogAlpha(0);
        Display3D_SetClearDepth(SKY_CLEAR_DEPTH);
        Display3D_SetClearColor(data_021f6f70.bottom_color);
    }
    NNS_G3dGlbMaterialColorSpecEmi(0, (u16) SceneLights_EmissionColour(), 0);
}
CLEAN_AS(func_020bbf0c, Sky_UpdateLight)

/* A light level of a level's table at `hour`, the addresses computed as the ARM does whatever
 * the values. */
static int light_level_at(int weather, int index, unsigned int hour)
{
    const u8 *const *tables = *(const u8 *const *const *) ((uintptr_t) data_020e60c0 + (u32) weather * 4);
    const u8 *table = *(const u8 *const *) ((uintptr_t) tables + (u32) index * 4);
    return *(const u8 *) ((uintptr_t) table + hour);
}

/* A level's light level mixed between `hour` and `next_hour`, of SKY_WEIGHT_ONE. */
static int light_level_mix(int weather, int index, unsigned int hour, unsigned int next_hour, int weight)
{
    return light_level_at(weather, index, hour) * (SKY_WEIGHT_ONE - weight) +
           light_level_at(weather, index, next_hour) * weight;
}

/* func_020bbf9c: the two light levels of now: the level's mixed between this hour and the next
 * by the minute, during a change of colours mixed with the next level's by the fade.
 * QUIRK: the hour mixes of a change are cut to 16 bits before the fade's mix. */
void Sky_MixLightLevels(int minute_weight, int fade_weight, unsigned int hour, unsigned int next_hour)
{
    const Sky *sky = &data_021f75b0;
    u8 *out = data_021f6cf8;
    if (sky->next_weather != sky->weather) {
        for (int i = 0; i < SKY_LIGHT_LEVELS; i++) {
            int from = (u16) (light_level_mix(sky->weather, i, hour, next_hour, minute_weight) >> 12);
            int to = (u16) (light_level_mix(sky->next_weather, i, hour, next_hour, minute_weight) >> 12);
            out[i] = (u8) ((from * (SKY_WEIGHT_ONE - fade_weight) + to * fade_weight) >> 12);
        }
    } else {
        for (int i = 0; i < SKY_LIGHT_LEVELS; i++) {
            out[i] = (u8) (light_level_mix(sky->weather, i, hour, next_hour, minute_weight) >> 12);
        }
    }
}
CLEAN_AS(func_020bbf9c, Sky_MixLightLevels)

/* A level's fog offset mixed between `hour` and `next_hour`.
 * REQUIRES: weather is a level, the hours 0 to 23. */
static unsigned int fog_offset_mix(int weather, unsigned int hour, unsigned int next_hour, unsigned int weight)
{
    const u16 *row = data_020e6098[weather];
    return (((SKY_WEIGHT_ONE - weight) * row[hour] + weight * row[next_hour]) << 4) >> 16;
}

/* func_020bc078: the fog offset of now: the level's mixed between this hour and the next by the
 * minute, during a change of colours mixed with the next level's by the fade. */
void Sky_MixFogOffset(unsigned int minute_weight, unsigned int fade_weight, unsigned int hour, unsigned int next_hour)
{
    const Sky *sky = &data_021f75b0;
    unsigned int from = fog_offset_mix(sky->weather, hour, next_hour, minute_weight);
    if (sky->next_weather != sky->weather) {
        unsigned int to = fog_offset_mix(sky->next_weather, hour, next_hour, minute_weight);
        SceneDisplay_SetFogOffset(((from * (SKY_WEIGHT_ONE - fade_weight) + to * fade_weight) << 4) >> 16);
        return;
    }
    SceneDisplay_SetFogOffset(from);
}
CLEAN_AS(func_020bc078, Sky_MixFogOffset)

/* func_020bc110: the four light colours of now: the level's mixed between this hour and the
 * next by the minute, during a change of colours mixed with the next level's by the fade.
 * REQUIRES: weather and next_weather are levels, the hours 0 to 23. */
void Sky_MixLightColors(int minute_weight, int fade_weight, int hour, int next_hour)
{
    const Sky *sky = &data_021f75b0;
    u16 *out = data_021f6cf0;
    if (sky->next_weather != sky->weather) {
        for (int i = 0; i < SKY_LIGHT_COLORS; i++) {
            u16 mixed[2];
            const u16 *from = data_020e6084[sky->weather][i];
            Sky_MixColor(&mixed[0], &from[hour], &from[next_hour], minute_weight);
            const u16 *to = data_020e6084[sky->next_weather][i];
            Sky_MixColor(&mixed[1], &to[hour], &to[next_hour], minute_weight);
            Sky_MixColor(&out[i], &mixed[0], &mixed[1], fade_weight);
        }
    } else {
        const u16 *const *colors = data_020e6084[sky->weather];
        for (int i = 0; i < SKY_LIGHT_COLORS; i++) {
            Sky_MixColor(&out[i], &colors[i][hour], &colors[i][next_hour], minute_weight);
        }
    }
}
CLEAN_AS(func_020bc110, Sky_MixLightColors)
