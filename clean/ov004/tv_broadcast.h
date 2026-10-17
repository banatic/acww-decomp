/* What the room's televisions show (the member at 0x64 of the room, data_ov004_022595c0; tv.h
 * draws it): the programme of the weekly schedule at the time of day, or, when none is on, a
 * weather forecast. Each is a texture pattern animation ("/ftr/tv/prog/tv_program%d" or
 * "/ftr/tv/weather/tv_xx", .nsbtx and .nsbtp) copied into the slot "tv.0"/"tv_pl" of the TV's
 * texture ("/ftr/tv/tv.nsbtx", copied once into the room's heap).
 *
 * Two screens take turns: a new picture is loaded into the screen not shown, which then is
 * shown. Each screen has a frame heap of its own for its files. When the room plays the TV's
 * sound (data_ov004_022595b8), a sound object of the programme's kind (the channel, 0xff for
 * the forecast) is made on a heap of the broadcast's whenever the picture changes. */
#ifndef CLEAN_OV004_TV_BROADCAST_H
#define CLEAN_OV004_TV_BROADCAST_H

#include "autoload_2/heap.h"
#include "main/g3d_resource.h"
#include "main/sound_object.h"
#include "main/tex_slot_anim.h"
#include "types.h"

/* TvScreen.channel for the forecast, and what TvBroadcast_ScheduledChannel gives when the
 * schedule has no programme on. */
#define TV_CHANNEL_FORECAST 0xff
#define TV_SCREEN_COUNT 2

/* The forecasts' pictures, by the letters of their files' names ("tv_ff" to "tv_sc"; they read
 * as fine, cloudy, rain and snow). The snow ones replace the rain ones in the snowy periods of
 * the year (TvBroadcast_IsSnowSeason). */
enum TvForecast {
    TV_FORECAST_FF,
    TV_FORECAST_CC,
    TV_FORECAST_RR,
    TV_FORECAST_FC,
    TV_FORECAST_CF,
    TV_FORECAST_FR,
    TV_FORECAST_CR,
    TV_FORECAST_RC,
    TV_FORECAST_SS,
    TV_FORECAST_CS,
    TV_FORECAST_SC,
    TV_FORECAST_COUNT
};

/* One screen (0xa8 bytes, constructed and destructed as an array of C++ objects). */
typedef struct TvScreen {
    Heap *heap;        /* 0x00: a frame heap of 0xe00 bytes for the picture's files */
    G3dResTex *target; /* 0x04: the TV's texture, holding the slot */
    G3dResTex *source; /* 0x08: the picture's textures */
    const u8 *anim;    /* 0x0c: the picture's texture pattern animation */
    TexSlotAnim slot;  /* 0x10 */
    int channel;       /* 0xa0: the programme shown, TV_CHANNEL_FORECAST, or -1 for none */
    s16 forecast;      /* 0xa4: the forecast shown (enum TvForecast), or -1 */
    u16 loops;         /* 0xa6: the times the animation passed its frame 0, up to 0xffff */
} TvScreen;

typedef struct TvBroadcast {
    s16 shown; /* 0x000: the screen shown (its low bit), -1 for none yet */
    u8 pad_002[2];
    TvScreen screens[TV_SCREEN_COUNT]; /* 0x004 */
    G3dResTex *texture;                /* 0x154: the TV's texture, copied into the room's heap */
    Heap *sound_heap;                  /* 0x158: with the TV's sound, a frame heap for it */
    SoundObject *sound;                /* 0x15c */
} TvBroadcast;

/* One programme of a day's schedule, from its start time on. */
typedef struct TvScheduleEntry {
    u8 channel;
    u8 hour;
    u8 minute;
} TvScheduleEntry;

/* A day's schedule, in start times' order. */
typedef struct TvSchedule {
    const TvScheduleEntry *entries;
    int count;
} TvSchedule;

int TvBroadcast_Frame(TvBroadcast *tv);
u16 TvBroadcast_Loops(TvBroadcast *tv);
int TvBroadcast_Sound(TvBroadcast *tv);
int TvBroadcast_Texture(TvBroadcast *tv);
int TvBroadcast_Forecast(TvBroadcast *tv);
unsigned long TvBroadcast_Channel(TvBroadcast *tv);
int TvBroadcast_IsShowing(TvBroadcast *tv);
void TvBroadcast_Release(TvBroadcast *tv);
int TvBroadcast_ForecastNow(TvBroadcast *tv);
int TvBroadcast_IsSnowSeason(void);
int TvBroadcast_ScheduledChannel(TvBroadcast *tv);
void TvBroadcast_UpdateScreen(TvBroadcast *tv);
void TvBroadcast_FollowSchedule(TvBroadcast *tv);
int TvBroadcast_Show(TvBroadcast *tv, int channel, int forecast);
void TvBroadcast_Init(TvBroadcast *tv);
TvBroadcast *TvBroadcast_Destruct(TvBroadcast *tv);
TvBroadcast *TvBroadcast_Construct(TvBroadcast *tv);
int TvScreen_Frame(TvScreen *screen);
unsigned short TvScreen_Loops(TvScreen *screen);
int TvScreen_Forecast(TvScreen *screen);
unsigned long TvScreen_Channel(TvScreen *screen);
void TvScreen_Delete(TvScreen *screen);
void TvScreen_Update(TvScreen *screen);
void TvScreen_Clear(TvScreen *screen);
int TvScreen_Load(TvScreen *screen, int channel, int forecast);
int TvBroadcast_ForecastName(unsigned int forecast);
void TvScreen_Init(TvScreen *screen, G3dResTex *texture);
TvScreen *TvScreen_Destruct(TvScreen *screen);
TvScreen *TvScreen_Construct(TvScreen *screen);

#endif
