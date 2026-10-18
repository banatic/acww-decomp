/* The day's weather patterns (sky_weather_day.h). */
#include "sky_weather_day.h"

#include "clean.h"
#include "date_time.h"
#include "event_calendar.h"
#include "player_record.h"
#include "player_records.h"
#include "scene_query.h"
#include "session.h"
#include "start_kind.h"
#include "main_random.h"

#define SKY_WEATHER_DAY_START_HOUR 6
#define SKY_WEATHER_DAY_HOURS 24
#define SKY_WEATHER_DAY_MINUTES (24 * 60)
#define SKY_WEATHER_DAY_SCENE 0x3f     /* the scene that keeps the patterns as they are */
#define SKY_WEATHER_DAY_PLAYER_FLAG 1  /* a player flag that forces the pattern */
#define SKY_WEATHER_DAY_TODAY_EVENTS 7 /* the events listed for today */
#define SKY_WEATHER_DAY_EVENT_9 9      /* events that force the pattern */
#define SKY_WEATHER_DAY_EVENT_10 10

extern NetSession *data_020ccf94;
extern u8 data_021fbbd8;                                   /* the wet flag of the day before, as it was moved on */
extern s32 data_021fbbdc;                                  /* the day was moved on when the game started (scene 0x3f) */
extern const u8 data_020d2ef0[][SKY_WEATHER_DAY_PATTERNS]; /* the patterns' odds in 100, by period */

extern void MI_CpuCopy8(const void *src, void *dst, u32 size);

/* func_020c15bc: the wet flag of the day before. */
unsigned char SkyWeatherDay_LastWet(void)
{
    return data_021fbbd8;
}
CLEAN_AS(func_020c15bc, SkyWeatherDay_LastWet)

/* func_020c15c8: a pattern drawn for the date by the odds (in 100) of its period of the year;
 * 0 when the odds come to less than a draw. */
int SkyWeatherDay_DrawPattern(SkyWeatherDay *day, const DateTime *date)
{
    (void) day;
    int period = Calendar_PeriodAOf(date);
    int draw = (int) MainRandom_Below(100);
    for (int i = 0; i < SKY_WEATHER_DAY_PATTERNS; i++) {
        draw -= data_020d2ef0[period][i];
        if (draw < 0) {
            return (u8) i;
        }
    }
    return 0;
}
CLEAN_AS(func_020c15c8, SkyWeatherDay_DrawPattern)

/* Today's pattern, drawn, and tomorrow's: `date` is moved on to tomorrow. */
static void sky_weather_day_draw_both(SkyWeatherDay *day, DateTime *date)
{
    day->pattern = (u8) SkyWeatherDay_DrawPattern(day, date);
    DateTime_AddDays(date, 1);
    day->next_pattern = (u8) SkyWeatherDay_DrawPattern(day, date);
}

/* func_020c1608: the patterns moved on to the weather's day of `now` (sky_weather_day.h),
 * then today's forced to 4 when it must be. 1 when the day changed; 0 in a session. */
int SkyWeatherDay_Update(SkyWeatherDay *day, const DateTime *now)
{
    int changed = 0;
    if (Session_IsLinked(data_020ccf94)) {
        return changed;
    }
    DateTime today = {0};
    MI_CpuCopy8(now, &today, sizeof(DateTime));
    DateTime_SubtractHours(&today, SKY_WEATHER_DAY_START_HOUR);
    today.hour = 0;
    today.minute = 0;
    if (day->year != today.year || day->month != today.month || day->day != today.day) {
        DateTime kept = {0};
        changed = 1;
        kept.year = day->year;
        kept.month = day->month;
        kept.day = day->day;
        day->year = today.year;
        day->month = today.month;
        day->day = today.day;
        int days = DateTime_MinutesBetween(&kept, &today) / SKY_WEATHER_DAY_MINUTES;
        if (days > 0) {
            if (days >= 2) {
                sky_weather_day_draw_both(day, &today);
            } else {
                day->pattern = day->next_pattern;
                DateTime_AddDays(&today, 1);
                day->next_pattern = (u8) SkyWeatherDay_DrawPattern(day, &today);
            }
        } else if (days < 0) {
            if (days <= -2) {
                sky_weather_day_draw_both(day, &today);
            } else {
                day->next_pattern = day->pattern;
                day->pattern = (u8) SkyWeatherDay_DrawPattern(day, &today);
            }
        }
        data_021fbbd8 = day->wet;
        day->wet = 0;
    }
    if (SceneQuery_Current() == SKY_WEATHER_DAY_SCENE) {
        return changed;
    }
    if (StartKind_IsSet()) {
        day->pattern = SKY_WEATHER_DAY_FORCED;
        return changed;
    }
    u8 *record = PlayerRecords_Current();
    if (record != NULL && PlayerRecord_TestFlag(record, SKY_WEATHER_DAY_PLAYER_FLAG)) {
        day->pattern = SKY_WEATHER_DAY_FORCED;
        return changed;
    }
    const EventCalendarEvent *event = EventCalendar_Today();
    for (int i = 0; i < SKY_WEATHER_DAY_TODAY_EVENTS; i++) {
        if (event->id == SKY_WEATHER_DAY_EVENT_9 || event->id == SKY_WEATHER_DAY_EVENT_10) {
            day->pattern = SKY_WEATHER_DAY_FORCED;
        }
        event++;
    }
    return changed;
}
CLEAN_AS(func_020c1608, SkyWeatherDay_Update)

/* func_020c176c: the patterns moved on to the clock's day (StateBlock_FinishStart). In scene
 * 0x3f, data_021fbbdc keeps whether the day changed and, when it did not, the day's wet flag
 * is taken as the day before's; elsewhere, after such a change, the wet flag of the day before
 * is kept from what this update would set. The hour of the weather asked for is set to the
 * clock's, from 6:00. */
void SkyWeatherDay_Refresh(SkyWeatherDay *day)
{
    DateTime now = {0};
    DateTime_Now(&now);
    if (SceneQuery_Current() == SKY_WEATHER_DAY_SCENE) {
        data_021fbbdc = SkyWeatherDay_Update(day, &now);
        if (data_021fbbdc == 0) {
            data_021fbbd8 = day->wet;
        }
    } else {
        if (data_021fbbdc != 0) {
            u8 last_wet = data_021fbbd8;
            if (SkyWeatherDay_Update(day, &now)) {
                data_021fbbd8 = last_wet;
            }
        } else {
            SkyWeatherDay_Update(day, &now);
        }
        data_021fbbdc = 0;
    }
    day->hour = (s8) (now.hour - SKY_WEATHER_DAY_START_HOUR);
    if (day->hour < 0) {
        day->hour = (s8) (day->hour + SKY_WEATHER_DAY_HOURS);
    }
}
CLEAN_AS(func_020c176c, SkyWeatherDay_Refresh)

/* func_020c17f0: the day kept set to today. */
void SkyWeatherDay_SetToday(SkyWeatherDay *day)
{
    Calendar_Today((Date *) (void *) day);
}
CLEAN_AS(func_020c17f0, SkyWeatherDay_SetToday)

/* func_020c17f8: the patterns set up with the state block (state_block.c): the wet flag of
 * the day before and the day's cleared, the date set to 1 January of year 0, then refreshed to
 * the clock (SkyWeatherDay_Refresh).
 * QUIRK: the day is set to 0 after the date is written, so the date kept before the refresh is
 * day 0 of January. */
void SkyWeatherDay_Reset(SkyWeatherDay *day)
{
    data_021fbbd8 = 0;
    day->wet = 0;
    day->day = 1;
    day->month = 1;
    day->year = 0;
    day->unk_03 = 0;
    day->day = 0;
    SkyWeatherDay_Refresh(day);
}
CLEAN_AS(func_020c17f8, SkyWeatherDay_Reset)

/* func_020c1818: the destructor, which does nothing. */
void SkyWeatherDay_Destruct(SkyWeatherDay *day)
{
    (void) day;
}
CLEAN_AS(func_020c1818, SkyWeatherDay_Destruct)

/* func_020c181c: the constructor, which does nothing. */
void SkyWeatherDay_Construct(SkyWeatherDay *day)
{
    (void) day;
}
CLEAN_AS(func_020c181c, SkyWeatherDay_Construct)
