/* What the room's televisions show (tv_broadcast.h). */
#include "tv_broadcast.h"

#include "clean.h"
#include "main/c_library.h"
#include "main/calendar.h"
#include "main/date_time.h"
#include "main/frame_ctrl.h"
#include "main/model_cache.h"
#include "main/rom_file.h"
#include "main/vram_region.h"
#include "room_manager.h"

static_assert(offsetof(TvScreen, slot) == 0x10, "slot");
static_assert(offsetof(TvScreen, channel) == 0xa0, "channel");
static_assert(offsetof(TvScreen, forecast) == 0xa4, "forecast");
static_assert(offsetof(TvScreen, loops) == 0xa6, "loops");
static_assert(sizeof(TvScreen) == 0xa8, "a screen");
static_assert(offsetof(TvBroadcast, screens) == 0x004, "screens");
static_assert(offsetof(TvBroadcast, texture) == 0x154, "texture");
static_assert(offsetof(TvBroadcast, sound) == 0x15c, "sound");
static_assert(sizeof(TvScheduleEntry) == 3, "a schedule's entry");

#define SCREEN_HEAP_SIZE 0xe00
#define SOUND_HEAP_EXTRA 0x60 /* the sound heap's size over the largest sound object */
#define FILE_ALIGN 4
#define NAME_SIZE 0x28
#define DAYS_PER_WEEK 7
#define LOOPS_MAX 0xffff

/* Set by the room's start (func_ov004_0223d434) when func_020b67d4 or func_020b6680 says so:
 * the TV's sound is played. */
extern u8 data_ov004_022595b8;
/* The heap files are loaded on, and the room's heap the TV's texture is copied into. */
extern Heap *data_021fbe94;
extern Heap *data_021c9b24;
/* The week's schedule, Sunday first (Calendar_TodayWeekday). */
extern const TvSchedule data_ov004_02247cf4[DAYS_PER_WEEK];
/* The forecasts' names, "tv_ff" to "tv_sc" (enum TvForecast). */
extern const char *const data_ov004_02255fe4[TV_FORECAST_COUNT];
/* Byte 3 of this state picks the forecast by its low 5 bits (what sets it is not known
 * here). */
extern const u8 data_021f3b28[];
/* "/ftr/tv/tv.nsbtx"; the programmes' and forecasts' files ("/ftr/tv/prog/tv_program%d.nsbtx"
 * and ".nsbtp", "/ftr/tv/weather/%s.nsbtx" and ".nsbtp"); the slot's texture and palette,
 * "tv.0" and "tv_pl". */
extern const char data_ov004_02256060[];
extern const char data_ov004_02256074[];
extern const char data_ov004_02256094[];
extern const char data_ov004_022560b4[];
extern const char data_ov004_022560d0[];
extern const char data_ov004_022560ec[];
extern const char data_ov004_022560f4[];

/* The screen's constructor and destructor, which the array's constructor is given. */
extern void *func_ov004_0223adb4(void *screen);
extern void *func_ov004_0223adc8(void *screen);
extern void __cxa_vec_ctor(void *array, int count, int size, void *(*construct)(void *), void *(*destruct)(void *) );
extern void __cxa_vec_cleanup(void *array, int count, int size, void *(*destruct)(void *) );
/* NitroSystem: the texture resource of a texture file, a file's set of texture pattern
 * animations and animation `index` of a set. */
extern G3dResTex *func_021077e8(void *file);
extern void *NNS_G3dGetTexPatAnmSet(void *file);
extern const u8 *func_02107bf8(void *set, int index);

/* The screen shown, by the low bit of `shown` (screen 1 before any is). */
static TvScreen *shown_screen(TvBroadcast *tv)
{
    return &tv->screens[tv->shown & 1];
}

/* func_ov004_0223a790: the frame the shown screen's animation is at. */
int TvBroadcast_Frame(TvBroadcast *tv)
{
    return TvScreen_Frame(shown_screen(tv));
}
CLEAN_AS(func_ov004_0223a790, TvBroadcast_Frame)

/* func_ov004_0223a7a8 */
u16 TvBroadcast_Loops(TvBroadcast *tv)
{
    return TvScreen_Loops(shown_screen(tv));
}
CLEAN_AS(func_ov004_0223a7a8, TvBroadcast_Loops)

/* func_ov004_0223a7c0: the sound object's address. */
int TvBroadcast_Sound(TvBroadcast *tv)
{
    return (int) (uintptr_t) tv->sound;
}
CLEAN_AS(func_ov004_0223a7c0, TvBroadcast_Sound)

/* func_ov004_0223a7cc: the TV's texture's address. */
int TvBroadcast_Texture(TvBroadcast *tv)
{
    return (int) (uintptr_t) tv->texture;
}
CLEAN_AS(func_ov004_0223a7cc, TvBroadcast_Texture)

/* func_ov004_0223a7d8 */
int TvBroadcast_Forecast(TvBroadcast *tv)
{
    return TvScreen_Forecast(shown_screen(tv));
}
CLEAN_AS(func_ov004_0223a7d8, TvBroadcast_Forecast)

/* func_ov004_0223a7f0 */
unsigned long TvBroadcast_Channel(TvBroadcast *tv)
{
    return TvScreen_Channel(shown_screen(tv));
}
CLEAN_AS(func_ov004_0223a7f0, TvBroadcast_Channel)

/* func_ov004_0223a808: whether a screen was shown yet. */
int TvBroadcast_IsShowing(TvBroadcast *tv)
{
    return tv->shown != -1;
}
CLEAN_AS(func_ov004_0223a808, TvBroadcast_IsShowing)

/* func_ov004_0223a818 (at the room's end): no screen shown, the sound and its heap deleted, and
 * both screens' heaps. The texture copied into the room's heap is only forgotten. */
void TvBroadcast_Release(TvBroadcast *tv)
{
    tv->shown = -1;
    tv->texture = NULL;
    if (data_ov004_022595b8 != 0 && tv->sound_heap != NULL) {
        if (tv->sound != NULL) {
            SoundObject_Release(tv->sound);
            tv->sound = NULL;
        }
        Heap_Delete(tv->sound_heap);
        tv->sound_heap = NULL;
    }
    TvScreen_Delete(&tv->screens[0]);
    TvScreen_Delete(&tv->screens[1]);
}
CLEAN_AS(func_ov004_0223a818, TvBroadcast_Release)

/* func_ov004_0223a87c: the forecast for the value data_021f3b28 holds (0-31). In the snowy
 * periods the forecasts with rain show snow. */
int TvBroadcast_ForecastNow(TvBroadcast *tv)
{
    (void) tv;
    int value = data_021f3b28[3] & 0x1f;
    if (value <= 6) {
        return TV_FORECAST_FF;
    }
    if (value <= 9) {
        return TV_FORECAST_CC;
    }
    if (value <= 15) {
        return TvBroadcast_IsSnowSeason() ? TV_FORECAST_SS : TV_FORECAST_RR;
    }
    if (value <= 18) {
        return TV_FORECAST_FC;
    }
    if (value <= 21) {
        return TV_FORECAST_CF;
    }
    if (value <= 25) {
        return TV_FORECAST_FR;
    }
    if (value <= 28) {
        return TvBroadcast_IsSnowSeason() ? TV_FORECAST_CS : TV_FORECAST_CR;
    }
    return TvBroadcast_IsSnowSeason() ? TV_FORECAST_SC : TV_FORECAST_RC;
}
CLEAN_AS(func_ov004_0223a87c, TvBroadcast_ForecastNow)

/* func_ov004_0223a8f0: whether today falls in periods 0-2 or 14-18 of the year
 * (Calendar_PeriodA), where the forecasts show snow. */
int TvBroadcast_IsSnowSeason(void)
{
    DateTime now = {0};
    DateTime_Now(&now);
    Date today = {now.day, now.month, now.year, 0};
    switch (Calendar_PeriodA(&today)) {
        case 0:
        case 1:
        case 2:
        case 14:
        case 15:
        case 16:
        case 17:
        case 18:
            return 1;
        default:
            return 0;
    }
}
CLEAN_AS(func_ov004_0223a8f0, TvBroadcast_IsSnowSeason)

/* func_ov004_0223a968: the channel of today's last programme that has started by now, or
 * TV_CHANNEL_FORECAST when none has. */
int TvBroadcast_ScheduledChannel(TvBroadcast *tv)
{
    (void) tv;
    const TvSchedule *day = &data_ov004_02247cf4[Calendar_TodayWeekday()];
    Time now;
    Calendar_Now(&now);
    unsigned int time = ((unsigned int) now.hour << 8) | now.minute;
    for (int i = day->count - 1; i >= 0; i--) {
        const TvScheduleEntry *entry = &day->entries[i];
        if (time >= (((unsigned int) entry->hour << 8) | entry->minute)) {
            return entry->channel;
        }
    }
    return TV_CHANNEL_FORECAST;
}
CLEAN_AS(func_ov004_0223a968, TvBroadcast_ScheduledChannel)

/* func_ov004_0223a9b8 (each frame): the shown screen's animation steps, once one is shown. */
void TvBroadcast_UpdateScreen(TvBroadcast *tv)
{
    if (TvBroadcast_IsShowing(tv)) {
        TvScreen_Update(shown_screen(tv));
    }
}
CLEAN_AS(func_ov004_0223a9b8, TvBroadcast_UpdateScreen)

/* func_ov004_0223a9e0 (each frame): when the schedule's programme, or without one the
 * forecast, is not the one shown, it is shown and the room told. */
void TvBroadcast_FollowSchedule(TvBroadcast *tv)
{
    int channel = TvBroadcast_ScheduledChannel(tv);
    if (channel == TV_CHANNEL_FORECAST) {
        int forecast = TvBroadcast_ForecastNow(tv);
        if (forecast != TvBroadcast_Forecast(tv)) {
            TvBroadcast_Show(tv, channel, forecast);
            RoomManager_SetBroadcastChanged();
        }
    } else if ((unsigned long) channel != TvBroadcast_Channel(tv)) {
        TvBroadcast_Show(tv, channel, TV_CHANNEL_FORECAST);
        RoomManager_SetBroadcastChanged();
    }
}
CLEAN_AS(func_ov004_0223a9e0, TvBroadcast_FollowSchedule)

/* func_ov004_0223aa30: the shown screen's files freed, then `channel` (or the forecast) loaded
 * into the other one. When it loads, that screen is shown and, with the TV's sound, the sound
 * object is made again for the channel and started. Whether it loaded.
 * QUIRK: when the load fails, the screen still shown is the one whose files were freed. */
int TvBroadcast_Show(TvBroadcast *tv, int channel, int forecast)
{
    TvScreen_Clear(shown_screen(tv));
    int next = (tv->shown + 1) & 1;
    if (TvScreen_Load(&tv->screens[next], channel, forecast) == 0) {
        return 0;
    }
    tv->shown = (s16) next;
    if (data_ov004_022595b8 != 0 && tv->sound_heap != NULL) {
        if (tv->sound != NULL) {
            SoundObject_Release(tv->sound);
            tv->sound = NULL;
        }
        Heap_FreeAll(tv->sound_heap);
        tv->sound = SoundObject_New(tv->sound_heap, channel);
        if (tv->sound != NULL) {
            SoundObject_Start(tv->sound);
        }
    }
    return 1;
}
CLEAN_AS(func_ov004_0223aa30, TvBroadcast_Show)

/* func_ov004_0223aad4 (at the room's start): the TV's texture loaded, placed in VRAM and copied
 * into the room's heap; the screens' heaps; with the TV's sound, its heap; then what the
 * schedule says shown. */
void TvBroadcast_Init(TvBroadcast *tv)
{
    tv->shown = -1;
    tv->texture = NULL;
    void *file = RomFile_Load(data_ov004_02256060, data_021fbe94, FILE_ALIGN, NULL);
    if (file != NULL) {
        G3dResTex *texture = func_021077e8(file);
        VramRegion_LoadTexture(texture, NULL);
        tv->texture = ModelCache_CopyTexture(texture, data_021c9b24);
        Heap_FreeCurrent(file);
    }
    TvScreen_Init(&tv->screens[0], tv->texture);
    TvScreen_Init(&tv->screens[1], tv->texture);
    if (data_ov004_022595b8 != 0) {
        tv->sound_heap = FrameHeap_Create((int) (SoundObject_MaxSize() + SOUND_HEAP_EXTRA), data_021fbe94);
    }
    int channel = TvBroadcast_ScheduledChannel(tv);
    TvBroadcast_Show(tv, channel, TvBroadcast_ForecastNow(tv));
}
CLEAN_AS(func_ov004_0223aad4, TvBroadcast_Init)

/* func_ov004_0223ab7c */
TvBroadcast *TvBroadcast_Destruct(TvBroadcast *tv)
{
    __cxa_vec_cleanup(tv->screens, TV_SCREEN_COUNT, sizeof(TvScreen), func_ov004_0223adb4);
    return tv;
}
CLEAN_AS(func_ov004_0223ab7c, TvBroadcast_Destruct)

/* func_ov004_0223ab98 */
TvBroadcast *TvBroadcast_Construct(TvBroadcast *tv)
{
    __cxa_vec_ctor(tv->screens, TV_SCREEN_COUNT, sizeof(TvScreen), func_ov004_0223adc8, func_ov004_0223adb4);
    tv->shown = -1;
    tv->texture = NULL;
    tv->sound_heap = NULL;
    tv->sound = NULL;
    return tv;
}
CLEAN_AS(func_ov004_0223ab98, TvBroadcast_Construct)

/* func_ov004_0223abe0: the whole frame of the screen's animation (bits 12-27 of its 20.12
 * fixed point frame). */
int TvScreen_Frame(TvScreen *screen)
{
    return (int) (((u32) screen->slot.ctrl.frame >> 12) & 0xffff);
}
CLEAN_AS(func_ov004_0223abe0, TvScreen_Frame)

/* func_ov004_0223abe8 */
unsigned short TvScreen_Loops(TvScreen *screen)
{
    return screen->loops;
}
CLEAN_AS(func_ov004_0223abe8, TvScreen_Loops)

/* func_ov004_0223abf0: the forecast shown, or -1 when a programme is. */
int TvScreen_Forecast(TvScreen *screen)
{
    if (TvScreen_Channel(screen) == TV_CHANNEL_FORECAST) {
        return screen->forecast;
    }
    return -1;
}
CLEAN_AS(func_ov004_0223abf0, TvScreen_Forecast)

/* func_ov004_0223ac0c */
unsigned long TvScreen_Channel(TvScreen *screen)
{
    return (unsigned long) (u32) screen->channel;
}
CLEAN_AS(func_ov004_0223ac0c, TvScreen_Channel)

/* func_ov004_0223ac14: the screen's heap deleted and its files forgotten, the TV's texture
 * too. */
void TvScreen_Delete(TvScreen *screen)
{
    if (screen->heap != NULL) {
        Heap_Delete(screen->heap);
        screen->heap = NULL;
    }
    screen->anim = NULL;
    screen->source = NULL;
    screen->target = NULL;
}
CLEAN_AS(func_ov004_0223ac14, TvScreen_Delete)

/* func_ov004_0223ac34: with a picture loaded, its animation steps (copying the frame's texture
 * into the slot), and each pass of frame 0 is counted. */
void TvScreen_Update(TvScreen *screen)
{
    if (screen->source != NULL && screen->anim != NULL) {
        TexSlotAnim_Update(&screen->slot);
        if (FrameCtrl_Passed(&screen->slot.ctrl, 0)) {
            int loops = screen->loops + 1;
            screen->loops = (u16) (loops > LOOPS_MAX ? LOOPS_MAX : loops);
        }
    }
}
CLEAN_AS(func_ov004_0223ac34, TvScreen_Update)

/* func_ov004_0223ac7c: the picture's files freed (the heap emptied). The channel and forecast
 * stay. */
void TvScreen_Clear(TvScreen *screen)
{
    if (screen->heap != NULL) {
        Heap_FreeAll(screen->heap);
    }
    screen->source = NULL;
    screen->anim = NULL;
}
CLEAN_AS(func_ov004_0223ac7c, TvScreen_Clear)

/* func_ov004_0223ac98: the programme `channel`, or for TV_CHANNEL_FORECAST the picture of
 * `forecast`, loaded on the screen's heap and its animation started into the TV's slot. Whether
 * it started; then the screen keeps the channel, the forecast (-1 for a programme) and no
 * loops.
 * QUIRK: the files' loads are not checked; what a failed one gives is handed on. */
int TvScreen_Load(TvScreen *screen, int channel, int forecast)
{
    char texture_path[NAME_SIZE];
    char anim_path[NAME_SIZE];
    int shown_forecast = -1;

    TvScreen_Clear(screen);
    if (channel != TV_CHANNEL_FORECAST) {
        CLib_SPrintf(texture_path, data_ov004_02256074, channel);
        CLib_SPrintf(anim_path, data_ov004_02256094, channel);
    } else {
        const char *name = (const char *) (uintptr_t) (u32) TvBroadcast_ForecastName((unsigned int) forecast);
        CLib_SPrintf(texture_path, data_ov004_022560b4, name);
        CLib_SPrintf(anim_path, data_ov004_022560d0, name);
        shown_forecast = forecast;
    }
    screen->source = func_021077e8(RomFile_Load(texture_path, screen->heap, FILE_ALIGN, NULL));
    screen->anim = func_02107bf8(NNS_G3dGetTexPatAnmSet(RomFile_Load(anim_path, screen->heap, FILE_ALIGN, NULL)), 0);
    if (TexSlotAnim_Start(&screen->slot, screen->target, data_ov004_022560ec, data_ov004_022560f4, screen->source,
                          screen->anim, 0) == 0) {
        return 0;
    }
    screen->channel = channel;
    screen->forecast = (s16) shown_forecast;
    screen->loops = 0;
    return 1;
}
CLEAN_AS(func_ov004_0223ac98, TvScreen_Load)

/* func_ov004_0223ad64: the address of the forecast's name, the first one's past the last. */
int TvBroadcast_ForecastName(unsigned int forecast)
{
    if (forecast < TV_FORECAST_COUNT) {
        return (int) (uintptr_t) data_ov004_02255fe4[forecast];
    }
    return (int) (uintptr_t) data_ov004_02255fe4[0];
}
CLEAN_AS(func_ov004_0223ad64, TvBroadcast_ForecastName)

/* func_ov004_0223ad7c: nothing shown, a heap made for the screen's files, and the TV's
 * texture. */
void TvScreen_Init(TvScreen *screen, G3dResTex *texture)
{
    screen->channel = -1;
    screen->forecast = -1;
    screen->heap = FrameHeap_Create(SCREEN_HEAP_SIZE, data_021fbe94);
    screen->target = texture;
}
CLEAN_AS(func_ov004_0223ad7c, TvScreen_Init)

/* func_ov004_0223adb4 */
TvScreen *TvScreen_Destruct(TvScreen *screen)
{
    TexSlotAnim_Destruct(&screen->slot);
    return screen;
}
CLEAN_AS(func_ov004_0223adb4, TvScreen_Destruct)

/* func_ov004_0223adc8 */
TvScreen *TvScreen_Construct(TvScreen *screen)
{
    TexSlotAnim_Construct(&screen->slot);
    screen->channel = -1;
    screen->forecast = -1;
    screen->heap = NULL;
    screen->loops = 0;
    return screen;
}
CLEAN_AS(func_ov004_0223adc8, TvScreen_Construct)
