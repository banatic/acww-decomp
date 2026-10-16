/* The town's sky (data_021f75b0): clouds on background 3 seen in perspective, a gradient of
 * colours behind them, the stars on background 1 and the weather that picks the clouds
 * ("/sky/..." files) and the colours.
 *
 * The weather is a level from 0 to 4 (the cloud screens "b", "f", "c", "r" and "h"); 3 and 4
 * bring rain, or snow in the coldest periods of the year (Sky_FallingKindOf). It follows a
 * pattern of 24 hours (data_020d28ac, one row per pattern of the day, a column per hour from
 * 6:00) and changes one level at a time: the clouds of the change are drawn row by row over the
 * old ones while the colours fade towards the next level (`fade` 0 to 0x20), then the next
 * level's clouds are drawn row by row (Sky_StepChange). A row of the cloud map is replaced only
 * when it is just out of view. When the sky is not drawn the change is only timed
 * (Sky_StepChangeHidden).
 *
 * The sky is drawn on the sub screen (screen 0) or on the main screen (screen 1, Sky_ShowOn) by
 * HBlank and VBlank functions (itcm/line_effects.h) that read two sets of tables: one is shown
 * while the other is written (`shown`). The stars scroll a column a day and rise through the
 * night (Sky_StarsXAt, Sky_StarsYAt).
 *
 * The process that runs it (vtable data_020e69a4, block_020ba298.h) loads the sky and draws it
 * only when data_020e54a8 was 0 at its creation (data_021f6cd8); otherwise only the weather and
 * colours are kept. */
#ifndef CLEAN_MAIN_SKY_H
#define CLEAN_MAIN_SKY_H

#include "itcm/interrupts.h"
#include "itcm/line_effects.h"
#include "main/calendar.h"
#include "types.h"

#define SKY_WEATHER_LEVELS 5
#define SKY_WEATHER_RAIN 3       /* the first level that brings rain or snow */
#define SKY_WEATHER_HEAVY_RAIN 4 /* the "h" clouds */

/* Sky.direction. */
enum SkyDirection {
    SKY_DIRECTION_UP = 0,   /* towards a higher level */
    SKY_DIRECTION_DOWN = 1, /* towards a lower one */
    SKY_DIRECTION_NONE = 2,
};

/* Sky.step: the steps of a change of weather (Sky_StepChange, Sky_StepChangeHidden). */
enum SkyStep {
    SKY_STEP_IDLE = 0,
    SKY_STEP_START = 1,  /* the change's clouds loaded */
    SKY_STEP_FADE = 2,   /* the change's clouds drawn row by row, the colours faded */
    SKY_STEP_LOAD = 3,   /* the next level's clouds loaded */
    SKY_STEP_FINISH = 4, /* the next level's clouds drawn row by row */
};

/* Sky.precipitation (Sky_FallingKindOf). */
enum SkyFalling {
    SKY_FALLING_NONE = 0,
    SKY_FALLING_RAIN = 1,
    SKY_FALLING_SNOW = 2,
};

/* The kinds of cloud screen files (data_020e5e0c, Sky_LoadCloudScreen): a level's own, and the
 * screens of a change up or down to a level. */
enum SkyCloudScreen {
    SKY_CLOUDS_LEVEL = 0,
    SKY_CLOUDS_UP = 1,
    SKY_CLOUDS_DOWN = 2,
};

#define SKY_SCREEN_SUB 0
#define SKY_SCREEN_MAIN 1

#define SKY_MAP_ROWS 32
#define SKY_MAP_ROW_SIZE 0x20 /* bytes of a row of the clouds' map */
#define SKY_CHANGE_FRAMES 0x2a8
#define SKY_FADE_STEPS 0x20

/* A palette of the sky (16 colours): colours 4 and 5 are the gradient's top and bottom. */
typedef struct SkyPalette {
    u16 colors[4];
    u16 gradient_top;    /* 0x08 */
    u16 gradient_bottom; /* 0x0a */
    u16 more[10];
} SkyPalette;

/* data_021f75b0 (0x1598 bytes; func_020bb99c constructs it). Its beginning is what the HBlank
 * functions read as LineLayers (itcm/line_effects.h). */
typedef struct Sky {
    u32 screen;                         /* 0x0000: SKY_SCREEN_...: where the sky was set up */
    u32 shown;                          /* 0x0004: which set of line tables is shown */
    LineAffine clouds[2][SCREEN_LINES]; /* 0x0008: background 3 of each line */
    s32 cloud_scroll;                   /* 0x1208: 8.8 pixels, below 0x10000 */
    s32 fade;                           /* 0x120c: 0 to SKY_FADE_STEPS: of the colours */
    u16 blend_alpha[2][SCREEN_LINES];   /* 0x1210: BLDALPHA of each line */
    u8 unk_1510[4];                     /* 0x1510 */
    s32 shift[2];                       /* 0x1514: the lines' shift, one per set */
    u32 shift_index;                    /* 0x151c: the one used */
    u32 changing;                       /* 0x1520: a change of weather is under way */
    s32 weather;                        /* 0x1524: the level */
    s32 next_weather;                   /* 0x1528: the level the colours fade to */
    s32 target_weather;                 /* 0x152c: the level asked for, -1: none */
    u32 direction;                      /* 0x1530: SKY_DIRECTION_... */
    s32 precipitation;                  /* 0x1534: SKY_FALLING_... */
    u16 unk_1538;                       /* 0x1538: set by func_020bbc90 from the date */
    u16 unk_153a;                       /* 0x153a */
    u16 stars_x;                        /* 0x153c: BG1HOFS of the stars */
    u16 stars_y;                        /* 0x153e: BG1VOFS before the shift; 0x100: hidden */
    u8 unk_1540[4];                     /* 0x1540 */
    u8 *hour_colors[2][2];              /* 0x1544: (func_020bbd30) */
    u32 hour_colors_size[2][2];         /* 0x1554 */
    SkyPalette *palettes[3];            /* 0x1564: the level's, the next level's, the mix */
    s32 variant;                        /* 0x1570: of the level's cloud screen (0 or 1) */
    s32 next_variant;                   /* 0x1574 */
    s32 row;                            /* 0x1578: the next row of the map drawn, -1: none */
    u8 *screen_data;                    /* 0x157c: the level's cloud screen */
    u32 screen_size;                    /* 0x1580 */
    u8 *change_screen_data;             /* 0x1584: the change's cloud screen */
    u32 change_screen_size;             /* 0x1588 */
    u32 step;                           /* 0x158c: SKY_STEP_... */
    s32 frames;                         /* 0x1590: of the hidden change's steps */
    s32 player_z;                       /* 0x1594: the player's Z last frame */
} Sky;

/* The day's weather in the state block (at 0x1737e of data_021dc7a8; func_020c1608 keeps it).
 * A day starts at 6:00. */
typedef struct SkyWeatherDay {
    u8 day;          /* 0x0 */
    u8 month;        /* 0x1 */
    u8 year;         /* 0x2 */
    u8 unk_03;       /* 0x3 */
    u8 pattern;      /* 0x4: today's row of data_020d28ac */
    u8 next_pattern; /* 0x5: tomorrow's */
    s8 hour;         /* 0x6: the hour whose weather was asked for last, from 6:00 */
    u8 wet;          /* 0x7: set when a level of rain was asked for */
} SkyWeatherDay;

/* A slot of the object at data_021f8b48 that the sky process runs (func_020be400 constructs
 * it: 60 entries of 0x74 bytes, then these five slots). */
typedef struct SkyObjectSlot {
    s32 kind; /* 0x34: none */
    u8 unk_04[4];
    u8 loaded;  /* 0x08 */
    u8 changed; /* 0x09 */
    u8 unk_0a[2];
} SkyObjectSlot;

extern Sky data_021f75b0;
extern LineGradient data_021f6f70;
extern LineHandler data_021f6d2c; /* the sky's line handler */
extern int data_021f6cd8;         /* the sky is drawn */

void Sky_SwapLineShift(void);
void Sky_Objects020bdf68(int player);
void Sky_Objects020bdfd8(int arg);
void Sky_ReseedForLink(void);
void Sky_ReseedForMode3(void);
void Sky_ReseedForMode4(void);
void Sky_ReseedForMode2(void);
void Sky_TimeForStarScroll(DateTime *when, int scroll_x, int scroll_y);
unsigned short Sky_StarsY(void);
unsigned short Sky_StarsX(void);
SkyPalette *Sky_ShownPalette(void);
int Sky_Precipitation(void);
void Sky_GetWeathers(s32 *weather, s32 *next_weather);
int Sky_WeatherNow(void);
int Sky_Falling(void);
void Sky_HideOnMain(void);
int Sky_ShowOn(int screen);
void Sky_ResetObjects(void);
int Sky_LoadStars(int screen);
int Sky_ReloadChangeRows(int screen);
int Sky_LoadClouds(int screen);
void Sky_FrameHidden(void);
void Sky_Frame(void);
void Sky_VBlankOff(void);
void Sky_VBlankMain(void);
void Sky_VBlankSub(void);
void Sky_UpdateClouds(void);
void Sky_UpdateGradient(void);
void Sky_SetGradientEnd(LineGradient *gradient, int end, unsigned short color, unsigned int line);
int Sky_StarsYNow(Sky *sky);
int Sky_StarsYAt(Sky *sky, const DateTime *when);
int Sky_StarsXAt(Sky *sky, const DateTime *when);
void Sky_StepChangeHidden(Sky *sky);
void Sky_HiddenFinish(Sky *sky);
void Sky_HiddenLoad(Sky *sky);
void Sky_HiddenFade(Sky *sky);
void Sky_HiddenStart(Sky *sky);
void Sky_StepChange(Sky *sky);
void Sky_ChangeFinish(Sky *sky);
void Sky_ChangeLoad(Sky *sky);
void Sky_ChangeFade(Sky *sky);
void Sky_ChangeStart(Sky *sky);
int Sky_LoadCloudScreen(Sky *sky, u8 **data, u32 *size, int kind, int weather);
int Sky_LoadCloudChars(Sky *sky, int weather, int layer);
signed char Sky_WeatherOfPattern(Sky *sky, int pattern, int hour);
int Sky_WeatherInHours(Sky *sky, int hours);
void Sky_UpdateHour(Sky *sky);
int Sky_RequestWeather(Sky *sky, int weather);
void Sky_SetTarget(Sky *sky, int weather);
void Sky_SetWeathers(Sky *sky, int weather, int next_weather);
int Sky_FallingKindOf(Sky *sky, int weather);
int Sky_LoadColors(int screen);
void Sky_Reset(Sky *sky);

void Sky_Destruct(Sky *sky);
Sky *Sky_Construct(Sky *sky);
void Sky_UpdateColors(void);
int Sky_LoadPalette(int screen);
void Sky_ColorWeights(Sky *sky, u32 *minute_weight, u32 *fade_weight);
void Sky_MixPalette(SkyPalette *dst, const SkyPalette *a, const SkyPalette *b, int weight);
void Sky_MixColor(u16 *dst, const u16 *a, const u16 *b, int weight);
void Sky_DrawDayAngle(Sky *sky);
int Sky_AllocPalettes(SkyPalette **palettes);
int Sky_LoadHourColors(void);
unsigned char Sky_LightLevel(int index);
short Sky_LightColor(int index);
void Sky_UpdateLight(int minute_weight, int fade_weight);
void Sky_MixLightLevels(int minute_weight, int fade_weight, unsigned int hour, unsigned int next_hour);
void Sky_MixFogOffset(unsigned int minute_weight, unsigned int fade_weight, unsigned int hour, unsigned int next_hour);
void Sky_MixLightColors(int minute_weight, int fade_weight, int hour, int next_hour);

#endif
