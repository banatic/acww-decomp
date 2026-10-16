/* What adds the sky's objects by the weather, the time and the calendar (sky_events.h). */
#include "sky_events.h"

#include "actor_table.h"
#include "autoload_2/approach.h"
#include "beside_spot.h"
#include "block_021d27ac.h"
#include "clean.h"
#include "date_time.h"
#include "event_calendar.h"
#include "mail.h"
#include "near_spot.h"
#include "player_record.h"
#include "player_records.h"
#include "scene_object.h"
#include "session.h"
#include "sky_shots.h"
#include "state_block.h"

#define SKY_EVENTS_FALL_MAX 0x6400 /* the rain's or snow's rate (SkyObjects.unk_2f08) at most */
#define SKY_EVENTS_FALL_STEP 2
#define SKY_EVENTS_FALL_GROWN 50 /* SkyObjects.unk_2f0c: the snow's intervals counted, at most */
#define SKY_EVENTS_RAIN_MIN_INTERVAL 0x23
#define SKY_EVENTS_THUNDER_START 50
#define SKY_EVENTS_THUNDER_SPREAD 200
#define SKY_EVENTS_THUNDER_MIN 10
#define SKY_EVENTS_THUNDER_SOUND 0 /* func_02065268's number */
#define SKY_EVENTS_NIGHT_END 4     /* hours 19:00 to 3:59 are the night */
#define SKY_EVENTS_NIGHT_START 19
#define SKY_EVENTS_KIND_3_SECOND 30
#define SKY_EVENTS_KIND_3_DELAY 600
#define SKY_EVENTS_KIND_10_FIRST_PATTERN 0x13
#define SKY_EVENTS_KIND_10_LAST_PATTERN 0x17
#define SKY_EVENTS_BLEND_RISE 15    /* minutes of the blending's rise, then its fall */
#define SKY_EVENTS_BLEND_MINUTES 45 /* its minutes in all */
#define SKY_EVENTS_BLEND_MAX 0xc000 /* 12 (fx32) */
#define SKY_EVENTS_ODDS 8
#define SKY_EVENTS_STATE_FLAG_9 9   /* the state block's flag that ends kind 6 */
#define SKY_EVENTS_ACTOR_D_KIND_7 8 /* the D actor whose scene object ends kind 7 */
#define SKY_EVENTS_FLAG_30 0x30     /* a player record's flag that keeps kind 5's variant away */
#define SKY_EVENTS_FLAG_32 0x32     /* a player record's flag SkyEvents_PostFlag32Letters answers */
#define SKY_EVENTS_KIND_12_COUNT 3
#define SKY_EVENTS_THIS_PLAYERS 4

/* The item list func_02063ccc builds (8 bytes). */
typedef struct SkyEventsItemList {
    u32 words[2];
} SkyEventsItemList;

extern NetSession *data_020ccf94;
extern StateBlock data_021dc7a8;
extern const u8 data_020d22b5[];  /* per weather pattern: the hour of kind 10 (0x13 to 0x17) */
extern const s32 data_020d2404[]; /* per level of rain: an interval and its random part */
extern const s32 data_020d2424[]; /* per level of snow */
extern const u8 data_020e7ad0[];  /* func_02066024's arguments for the letter */
extern const u8 data_020e5970[];
extern const u8 data_020e596c[];
extern u32 func_020644cc(int bound); /* a random number below `bound` */
extern void func_02065268(int number);
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
extern void func_02066694(MailLetter *letter); /* a letter's constructor */
extern void func_02066688(MailLetter *letter); /* and destructor */
extern void func_02066024(MailLetter *letter, u8 *message, const u8 *a, const u8 *b, const u8 *c, void *player);
extern void func_02063ccc(SkyEventsItemList *list, int kind, int group);
extern void func_020638d4(u16 *item, SkyEventsItemList *list, int a, int b, int c, int d, int e);
extern void func_02063cc8(SkyEventsItemList *list);
extern u16 func_02065ed0(MailLetter *letter, u16 item, int arg); /* the item the letter carries */
extern void func_020bece0(void *palettes);                       /* a random pick for the palettes' part */

/* The day's weather pattern (sky.h, at 0x1737e of the state block). */
static int sky_events_pattern(void)
{
    return ((const SkyWeatherDay *) (const void *) data_021dc7a8.part_1737e)->pattern;
}

/* This system is in a session with others. */
static int sky_events_in_session(void)
{
    NetSession *session = data_020ccf94;
    return Session_IsSlotTaken(session, session->local_slot) != 0;
}

/* A comparison of DateTime_Compare: the first is before the second or the same. */
static int sky_events_not_after(int compared)
{
    return compared == -1 || compared == 0;
}

/* func_020bceb4: once asked for (SKY_EVENT_KIND_12_DUE), three objects of kind 12 (parameters 0
 * to 2) when nothing falls, from March 16 to September 15 and from 6:00 to 8:59. */
void SkyEvents_AddKind12(SkyObjects *objects)
{
    if (objects->unk_2f24[SKY_EVENT_KIND_12_DUE] == 0) {
        return;
    }
    objects->unk_2f24[SKY_EVENT_KIND_12_DUE] = 0;
    int dry = Sky_Falling() == 0;
    DateTime first = {0};
    DateTime last = {0};
    DateTime now = {0};
    DateTime_Now(&now);
    MI_CpuCopy8(&now, &first, sizeof(DateTime));
    MI_CpuCopy8(&now, &last, sizeof(DateTime));
    first.month = 3;
    first.day = 16;
    last.month = 9;
    last.day = 15;
    int after_first = DateTime_Compare(&first, &now, DATE_TIME_DAY | DATE_TIME_MONTH);
    int before_last = DateTime_Compare(&now, &last, DATE_TIME_DAY | DATE_TIME_MONTH);
    int in_season = sky_events_not_after(after_first) && sky_events_not_after(before_last);
    first.hour = 6;
    last.hour = 9;
    after_first = DateTime_Compare(&first, &now, DATE_TIME_HOUR);
    before_last = DateTime_Compare(&now, &last, DATE_TIME_HOUR);
    int in_hours = sky_events_not_after(after_first) && before_last == -1;
    if (dry && in_season && in_hours) {
        for (int i = 0; i < SKY_EVENTS_KIND_12_COUNT; i++) {
            SkyObjects_Add(objects, SKY_OBJECT_KIND_12, SKY_ENTRY_ANY, NULL, i);
        }
    }
}
CLEAN_AS(func_020bceb4, SkyEvents_AddKind12)

/* func_020bd054: the clouds' blending in the hour of kind 10 (on days of weather pattern 0x13
 * to 0x17, the hour data_020d22b5 gives): rising over 15 minutes to 12 and falling back over
 * the next 30, rounded; 0 otherwise. While it is not 0 it is applied (SkyObjects_SetBlend)
 * and an object of kind 10 kept in entry 32 (none to add: no blending); else that object is
 * taken down. */
void SkyEvents_UpdateKind10(SkyObjects *objects)
{
    objects->blend_alpha = 0;
    int pattern = sky_events_pattern();
    if (pattern >= SKY_EVENTS_KIND_10_FIRST_PATTERN && pattern <= SKY_EVENTS_KIND_10_LAST_PATTERN &&
        data_020d22b5[pattern] == objects->time.hour) {
        int minute = objects->time.minute;
        if (minute < SKY_EVENTS_BLEND_MINUTES) {
            int level;
            if (minute <= SKY_EVENTS_BLEND_RISE) {
                level = minute * 0xccc;
            } else {
                level = (minute - SKY_EVENTS_BLEND_RISE) * -0x666 + SKY_EVENTS_BLEND_MAX;
            }
            if (level < 0) {
                level = 0;
            } else if (level > SKY_EVENTS_BLEND_MAX) {
                level = SKY_EVENTS_BLEND_MAX;
            }
            objects->blend_alpha = (u8) ((level + 0x800) >> 12);
        }
    }

    int shown = objects->entries[SKY_ENTRY_KIND_10].kind == SKY_OBJECT_KIND_10;
    if (objects->blend_alpha != 0) {
        SkyObjects_SetBlend(objects);
        if (!shown && SkyObjects_Add(objects, SKY_OBJECT_KIND_10, SKY_ENTRY_KIND_10, NULL, 0) == NULL) {
            objects->blend_alpha = 0;
        }
    } else if (shown) {
        SkyObjects_RemoveKind(objects, SKY_OBJECT_KIND_10);
    }
}
CLEAN_AS(func_020bd054, SkyEvents_UpdateKind10)

/* func_020bd124: while calendar event 0x45 is on (SKY_EVENT_45, cleared for good once the
 * scene object of D actor 8 is enabled), outside a session and when nothing falls: an object
 * of kind 7 in entry 45 as the hour turns 9:00 or 17:00, unless the near spot of data_021d27ac
 * was served or entry 45 holds kind 7. */
void SkyEvents_AddKind7(SkyObjects *objects)
{
    if (objects->unk_2f24[SKY_EVENT_45] != 0) {
        u8 *actor = Actors_GetDByIndex(SKY_EVENTS_ACTOR_D_KIND_7);
        if (actor != NULL && SceneObject_IsEnabled(actor)) {
            objects->unk_2f24[SKY_EVENT_45] = 0;
        }
    }
    if (objects->unk_2f24[SKY_EVENT_45] == 0 || sky_events_in_session()) {
        return;
    }
    int falling = Sky_Falling();
    if (falling == SKY_FALLING_RAIN || falling == SKY_FALLING_SNOW) {
        return;
    }
    int hour = objects->time.hour;
    if (hour == objects->last_time.hour || (hour != 9 && hour != 17)) {
        return;
    }
    if (NearSpot_WasServed((const NearSpot *) (void *) Block021d27ac_Part24(Block021d27ac_Get())) ||
        objects->entries[SKY_ENTRY_VISITOR].kind == SKY_OBJECT_KIND_7) {
        return;
    }
    SkyObjects_Add(objects, SKY_OBJECT_KIND_7, SKY_ENTRY_VISITOR, NULL, 0);
}
CLEAN_AS(func_020bd124, SkyEvents_AddKind7)

/* A chance at growing odds: drawn from 1 to 8 when 0; the object comes when a draw below 8 is
 * below them (they then fall back to 1), else they grow by 1 up to 8. 1 when it comes. */
static int sky_events_try_odds(u8 *odds)
{
    if (*odds == 0) {
        *odds = (u8) (func_020644cc(SKY_EVENTS_ODDS) + 1);
    }
    u32 current = *odds;
    if (func_020644cc(SKY_EVENTS_ODDS) < current) {
        return 1;
    }
    if (current < SKY_EVENTS_ODDS) {
        (*odds)++;
    }
    return 0;
}

/* func_020bd1c4: while calendar event 0x44 is on (SKY_EVENT_44, cleared for good once flag 9
 * of the state block is set or the event is no longer on) and outside a session: as the
 * minute turns to one ending in 2 or 7, unless the beside spot of data_021d27ac was served or
 * entry 45 holds kind 6, an object of kind 6 in entry 45 at growing odds. */
void SkyEvents_AddKind6(SkyObjects *objects)
{
    if (objects->unk_2f24[SKY_EVENT_44] != 0) {
        if (StateBlock_TestFlag((u32 *) (void *) &data_021dc7a8, SKY_EVENTS_STATE_FLAG_9)) {
            objects->unk_2f24[SKY_EVENT_44] = 0;
        } else {
            DateTime now = {0};
            DateTime when;
            DateTime_Now(&now);
            MI_CpuCopy8(&now, &when, sizeof(DateTime));
            if (EventCalendar_State(EVENT_CALENDAR_EVENT_44, &when, 0) == EVENT_CALENDAR_OFF) {
                objects->unk_2f24[SKY_EVENT_44] = 0;
            }
        }
    }
    if (objects->unk_2f24[SKY_EVENT_44] == 0 || sky_events_in_session()) {
        return;
    }
    int minute = objects->time.minute;
    int ending = minute % 10;
    if (objects->last_time.minute == minute || (ending != 2 && ending != 7)) {
        return;
    }
    if (BesideSpot_WasServed(Block021d27ac_Part31(Block021d27ac_Get())) ||
        objects->entries[SKY_ENTRY_VISITOR].kind == SKY_OBJECT_KIND_6) {
        return;
    }
    if (sky_events_try_odds(&objects->unk_2f24[SKY_EVENT_ODDS_6])) {
        SkyObjects_Add(objects, SKY_OBJECT_KIND_6, SKY_ENTRY_VISITOR, NULL, 0);
        objects->unk_2f24[SKY_EVENT_ODDS_6] = 1;
    }
}
CLEAN_AS(func_020bd1c4, SkyEvents_AddKind6)

/* func_020bd2d0: outside a session, from 10:00 to 15:59, as the minute turns to one ending in
 * 4 and unless entry 45 holds kind 5: an object of kind 5 in entry 45 at growing odds. It is
 * the variant (parameter 1) one time in four when this system's player lacks flag 0x30 and has
 * counted 16 hits (SkyShots_HitCountFull); otherwise the palettes' part at 0x2eb8 is given a
 * new random pick (func_020bece0). */
void SkyEvents_AddKind5(SkyObjects *objects)
{
    if (sky_events_in_session()) {
        return;
    }
    int hour = objects->time.hour;
    int minute = objects->time.minute;
    if (hour < 10 || hour >= 16 || objects->last_time.minute == minute || minute % 10 != 4 ||
        objects->entries[SKY_ENTRY_VISITOR].kind == SKY_OBJECT_KIND_5) {
        return;
    }
    if (!sky_events_try_odds(&objects->unk_2f24[SKY_EVENT_ODDS_5])) {
        return;
    }
    if (!PlayerRecord_TestFlag(PlayerRecords_Current(), SKY_EVENTS_FLAG_30) && SkyShots_HitCountFull() &&
        func_020644cc(4) == 0) {
        SkyObjects_Add(objects, SKY_OBJECT_KIND_5, SKY_ENTRY_VISITOR, NULL, 1);
    } else {
        SkyObjects_Add(objects, SKY_OBJECT_KIND_5, SKY_ENTRY_VISITOR, NULL, 0);
        func_020bece0(objects->unk_2eb8);
    }
    objects->unk_2f24[SKY_EVENT_ODDS_5] = 1;
}
CLEAN_AS(func_020bd2d0, SkyEvents_AddKind5)

/* func_020bd688: the moon kept in entry 31 at night, taken down by day. */
void SkyEvents_UpdateMoon(SkyObjects *objects)
{
    int hour = objects->time.hour;
    int shown = objects->entries[SKY_ENTRY_MOON].kind == SKY_OBJECT_MOON;
    if (hour >= SKY_EVENTS_NIGHT_START || hour < SKY_EVENTS_NIGHT_END) {
        if (!shown) {
            SkyObjects_Add(objects, SKY_OBJECT_MOON, SKY_ENTRY_MOON, NULL, 0);
        }
    } else if (shown) {
        SkyObjects_RemoveKind(objects, SKY_OBJECT_MOON);
    }
}
CLEAN_AS(func_020bd688, SkyEvents_UpdateMoon)

/* func_020bd6d0: at night, at weather levels below 3 and while no show runs (no program, no
 * object of the show): as the second turns 30, one chance (1 in 4 on days of weather pattern
 * 0, else 1 in 256) to start a delay below 600 frames, at whose end an object of kind 3 is
 * added in entry 30. Otherwise the delay is dropped. */
void SkyEvents_AddKind3(SkyObjects *objects)
{
    int hour = objects->time.hour;
    int night = !(hour < SKY_EVENTS_NIGHT_START && hour >= SKY_EVENTS_NIGHT_END);
    s32 weather = data_021f75b0.weather;
    int clear = weather != SKY_WEATHER_RAIN && weather != SKY_WEATHER_HEAVY_RAIN;
    int idle = objects->program == 0 && SkyObjects_FindKind(objects, SKY_OBJECT_SHOW) == SKY_OBJECT_COUNT;
    if (!(night && clear && idle)) {
        objects->unk_2f4c = 0;
        return;
    }
    if (objects->unk_2f4c > 0) {
        objects->unk_2f4c--;
        if (objects->unk_2f4c == 0) {
            SkyObjects_Add(objects, SKY_OBJECT_KIND_3, SKY_ENTRY_KIND_3, NULL, 0);
        }
    } else if (objects->unk_2f1c == SKY_EVENTS_KIND_3_SECOND && objects->unk_2f1c != objects->unk_2f20) {
        if (func_020644cc(sky_events_pattern() == 0 ? 4 : 0x100) == 0) {
            objects->unk_2f4c = (s32) func_020644cc(SKY_EVENTS_KIND_3_DELAY);
        }
    }
}
CLEAN_AS(func_020bd6d0, SkyEvents_AddKind3)

/* The level of the rain or snow (1 to 4, 0: none) from the weather and the level it changes
 * to: 4 staying at heavy, 2 staying at level 3; changing down to 3: 3, to below it: 1;
 * changing up to 3: 1, to above it: 3. */
static int sky_events_fall_level(s32 weather, s32 next)
{
    if (weather == next) {
        return weather == SKY_WEATHER_RAIN ? 2 : weather == SKY_WEATHER_HEAVY_RAIN ? 4 : 0;
    }
    if (weather > next) {
        return next == SKY_WEATHER_RAIN ? 3 : next < SKY_WEATHER_RAIN ? 1 : 0;
    }
    return next == SKY_WEATHER_RAIN ? 1 : next > SKY_WEATHER_RAIN ? 3 : 0;
}

/* The rate (SkyObjects.unk_2f08) moved by 2 towards its most while the weather changes to a
 * level that falls, else towards 0. */
static void sky_events_step_rate(SkyObjects *objects, s32 next)
{
    if (next >= SKY_WEATHER_RAIN) {
        objects->unk_2f08 += SKY_EVENTS_FALL_STEP;
        if (objects->unk_2f08 > SKY_EVENTS_FALL_MAX) {
            objects->unk_2f08 = SKY_EVENTS_FALL_MAX;
        }
    } else {
        objects->unk_2f08 -= SKY_EVENTS_FALL_STEP;
        if (objects->unk_2f08 < 0) {
            objects->unk_2f08 = 0;
        }
    }
}

/* func_020bd7a4: snowflakes added: the rate (unk_2f08, at once at its most while the first two
 * intervals pass and the weather changes to a level that falls) adds up (unk_2f04) towards an
 * interval (unk_2f00, 1000 to start); each one reached adds a flake. The first interval after
 * is 11000, the second 9000, later ones random by the level (data_020d2424) with the count
 * started at 75 until 50 intervals were counted (unk_2f0c). Without snow the interval and the
 * count are cleared. */
void SkyEvents_Snow(SkyObjects *objects)
{
    s32 weather = data_021f75b0.weather;
    s32 next = data_021f75b0.next_weather;
    int level = sky_events_fall_level(weather, next);
    if (level == 0) {
        objects->unk_2f00 = 0;
        objects->unk_2f0c = 0;
        return;
    }
    const s32 *range = &data_020d2424[(level - 1) * 2];
    if (objects->unk_2f00 == 0) {
        objects->unk_2f00 = 1000;
    }
    if (objects->unk_2f0c <= 2 && next >= SKY_WEATHER_RAIN) {
        objects->unk_2f08 = SKY_EVENTS_FALL_MAX;
    } else {
        sky_events_step_rate(objects, next);
    }
    objects->unk_2f04 += objects->unk_2f08 >> 8;

    while (objects->unk_2f04 >= objects->unk_2f00) {
        SkyObjects_Add(objects, SKY_OBJECT_SNOW, SKY_ENTRY_ANY, NULL, 0);
        objects->unk_2f04 -= objects->unk_2f00;
        if (objects->unk_2f04 > objects->unk_2f00) {
            continue;
        }
        switch (objects->unk_2f0c) {
            case 0:
                objects->unk_2f00 = 11000;
                objects->unk_2f04 = 0;
                break;
            case 1:
                objects->unk_2f00 = 9000;
                objects->unk_2f04 = 0;
                break;
            default:
                objects->unk_2f00 = range[0] + (s32) func_020644cc(range[1]);
                objects->unk_2f04 = objects->unk_2f0c < SKY_EVENTS_FALL_GROWN ? 75 : 0;
                break;
        }
        objects->unk_2f0c++;
        if (objects->unk_2f0c > SKY_EVENTS_FALL_GROWN) {
            objects->unk_2f0c = SKY_EVENTS_FALL_GROWN;
        }
        break;
    }
}
CLEAN_AS(func_020bd7a4, SkyEvents_Snow)

/* func_020bd938: raindrops added like the snow's flakes, the intervals random by the level
 * (data_020d2404), at least 0x23; without rain the rate is cleared. At the heavy level the
 * thunder runs (SkyEvents_HeavyThunder); the word at 0x2f54 moves by 2 towards 0x1000 while
 * the weather changes to heavy, else towards 0x800. */
void SkyEvents_Rain(SkyObjects *objects)
{
    s32 weather = data_021f75b0.weather;
    s32 next = data_021f75b0.next_weather;
    int level = sky_events_fall_level(weather, next);
    if (level == 0) {
        objects->unk_2f08 = 0;
    } else {
        const s32 *range = &data_020d2404[(level - 1) * 2];
        if (objects->unk_2f00 == 0) {
            objects->unk_2f00 = range[0] + (s32) func_020644cc(range[1]);
        }
        sky_events_step_rate(objects, next);
        objects->unk_2f04 += objects->unk_2f08 >> 8;
        while (objects->unk_2f04 >= objects->unk_2f00) {
            SkyObjects_Add(objects, SKY_OBJECT_RAIN, SKY_ENTRY_ANY, NULL, 0);
            objects->unk_2f04 -= objects->unk_2f00;
            if (objects->unk_2f04 > objects->unk_2f00) {
                continue;
            }
            objects->unk_2f00 = range[0] + (s32) func_020644cc(range[1]);
            if (objects->unk_2f00 < SKY_EVENTS_RAIN_MIN_INTERVAL) {
                objects->unk_2f00 = SKY_EVENTS_RAIN_MIN_INTERVAL;
            }
            objects->unk_2f04 = 0;
            break;
        }
    }
    if (level == 4) {
        SkyEvents_HeavyThunder(objects);
    }
    Approach_S32((int *) (void *) &objects->unk_2f54, next == SKY_WEATHER_HEAVY_RAIN ? 0x1000 : 0x800, 2);
}
CLEAN_AS(func_020bd938, SkyEvents_Rain)

/* The thunder's timer run down (50 frames when it has none); 1 when it ran out. */
static int sky_events_thunder_due(SkyObjects *objects)
{
    if (objects->thunder_timer <= 0) {
        objects->thunder_timer = SKY_EVENTS_THUNDER_START;
    }
    objects->thunder_timer--;
    return objects->thunder_timer <= 0;
}

/* func_020bda88: the thunder: heard (func_02065268) when its timer runs out, then again 10 to
 * 209 frames later. */
void SkyEvents_Thunder(SkyObjects *objects)
{
    if (!sky_events_thunder_due(objects)) {
        return;
    }
    func_02065268(SKY_EVENTS_THUNDER_SOUND);
    objects->thunder_timer = (s32) func_020644cc(SKY_EVENTS_THUNDER_SPREAD) + SKY_EVENTS_THUNDER_MIN;
}
CLEAN_AS(func_020bda88, SkyEvents_Thunder)

/* func_020bdac8: the same, one time in eight with an object of kind 8 in entry 59. */
void SkyEvents_HeavyThunder(SkyObjects *objects)
{
    if (!sky_events_thunder_due(objects)) {
        return;
    }
    if (func_020644cc(SKY_EVENTS_ODDS) == 0) {
        SkyObjects_Add(objects, SKY_OBJECT_KIND_8, SKY_ENTRY_KIND_8, NULL, 0);
    }
    func_02065268(SKY_EVENTS_THUNDER_SOUND);
    objects->thunder_timer = (s32) func_020644cc(SKY_EVENTS_THUNDER_SPREAD) + SKY_EVENTS_THUNDER_MIN;
}
CLEAN_AS(func_020bdac8, SkyEvents_HeavyThunder)

/* func_020bdb24: at weather level 3 or 4 the rain or snow already falling: the rate at its
 * most, the count grown, 15 drops or flakes (20 at level 4) added with parameter 1 and the word
 * at 0x2f54 set to 0x800 (0x1000 at level 4); at other levels all three cleared. */
void SkyEvents_StartFalling(SkyObjects *objects)
{
    int moderate = data_021f75b0.weather == SKY_WEATHER_RAIN;
    int heavy = data_021f75b0.weather == SKY_WEATHER_HEAVY_RAIN;
    if (!moderate && !heavy) {
        objects->unk_2f08 = 0;
        objects->unk_2f0c = 0;
        objects->unk_2f54 = 0;
        return;
    }
    int kind = SKY_OBJECT_UNDRAWN; /* none */
    if (data_021f75b0.precipitation == SKY_FALLING_RAIN) {
        kind = SKY_OBJECT_RAIN;
    } else if (data_021f75b0.precipitation == SKY_FALLING_SNOW) {
        kind = SKY_OBJECT_SNOW;
    }
    objects->unk_2f08 = SKY_EVENTS_FALL_MAX;
    objects->unk_2f0c = SKY_EVENTS_FALL_GROWN;
    if (kind != SKY_OBJECT_UNDRAWN) {
        int count = moderate ? 15 : 20;
        for (int i = 0; i < count; i++) {
            SkyObjects_Add(objects, kind, SKY_ENTRY_ANY, NULL, 1);
        }
    }
    objects->unk_2f54 = moderate ? 0x800 : 0x1000;
}
CLEAN_AS(func_020bdb24, SkyEvents_StartFalling)

/* func_020bde98: each of the four players of the town whose record has flag 0x32 is sent a
 * letter (one of three messages at random, from the arguments at data_020e7ad0) carrying an
 * item drawn from list 0 of group 4; the flag is cleared once the letter is posted. */
void SkyEvents_PostFlag32Letters(SkyObjects *objects)
{
    (void) objects;
    for (int player = 0; player < SKY_EVENTS_THIS_PLAYERS; player++) {
        u8 *record = PlayerRecords_TownRecord(data_021dc7a8.players, player);
        if (record == NULL || !PlayerRecord_TestFlag(record, SKY_EVENTS_FLAG_32)) {
            continue;
        }
        MailLetter letter;
        u8 message;
        u16 item;
        SkyEventsItemList list;
        SkyEventsItemList copy;
        func_02066694(&letter);
        message = (u8) func_020644cc(3);
        func_02066024(&letter, &message, data_020e7ad0, data_020e5970, data_020e596c, PlayerRecord_Player(record));
        func_02063ccc(&list, 0, 4);
        copy = list;
        func_020638d4(&item, &copy, 0, 0, 1, 1, 0);
        func_02063cc8(&copy);
        func_02065ed0(&letter, item, 1);
        if (Mail_Post(&letter)) {
            PlayerRecord_ClearFlag(record, SKY_EVENTS_FLAG_32);
        }
        func_02063cc8(&list);
        func_02066688(&letter);
    }
}
CLEAN_AS(func_020bde98, SkyEvents_PostFlag32Letters)

/* func_020bdfd8: when `refresh` is set, flag 9 of the state block cleared, the calendar's
 * events read again and the letters of flag 0x32 sent. */
void SkyEvents_Refresh(SkyObjects *objects, int refresh)
{
    if (refresh == 0) {
        return;
    }
    StateBlock_ClearFlag((u32 *) (void *) &data_021dc7a8, SKY_EVENTS_STATE_FLAG_9);
    SkyEvents_ReadCalendar(objects);
    SkyEvents_PostFlag32Letters(objects);
}
CLEAN_AS(func_020bdfd8, SkyEvents_Refresh)

/* func_020be000: which of today's open events are on now: 0x44 (SKY_EVENT_44), 0x45
 * (SKY_EVENT_45), 0x13 or 0xf (SKY_EVENT_SHOW). */
void SkyEvents_ReadCalendar(SkyObjects *objects)
{
    objects->unk_2f24[SKY_EVENT_44] = 0;
    objects->unk_2f24[SKY_EVENT_45] = 0;
    objects->unk_2f24[SKY_EVENT_SHOW] = 0;
    DateTime now = {0};
    DateTime when;
    EventCalendarEvent events[EVENT_CALENDAR_DAY_EVENTS];
    DateTime_Now(&now);
    MI_CpuCopy8(&now, &when, sizeof(DateTime));
    int count = EventCalendar_ListOpen(events, &when, 0);
    for (int i = 0; i < count; i++) {
        int id = events[i].id;
        MI_CpuCopy8(&now, &when, sizeof(DateTime));
        if (EventCalendar_State(id, &when, 0) == EVENT_CALENDAR_OFF) {
            continue;
        }
        if (id == EVENT_CALENDAR_EVENT_44) {
            objects->unk_2f24[SKY_EVENT_44] = 1;
        } else if (id == EVENT_CALENDAR_EVENT_45) {
            objects->unk_2f24[SKY_EVENT_45] = 1;
        } else if (id == 0x13 || id == 0xf) {
            objects->unk_2f24[SKY_EVENT_SHOW] = 1;
        }
    }
}
CLEAN_AS(func_020be000, SkyEvents_ReadCalendar)
