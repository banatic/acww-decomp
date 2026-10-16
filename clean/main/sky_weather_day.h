/* The day's weather patterns in the state block (SkyWeatherDay, sky.h; at 0x1737e of
 * data_021dc7a8): the day they are for, today's pattern and tomorrow's.
 *
 * A day of the weather starts at 6:00. When the clock reaches a day other than the one kept
 * (SkyWeatherDay_Update), the patterns move on: a day later, today's is tomorrow's and a new
 * tomorrow is drawn; a day earlier, tomorrow's is today's and a new today is drawn; two days
 * or more either way, both are drawn. A pattern is drawn from the odds of the date's period of
 * the year (SkyWeatherDay_DrawPattern). The day's wet flag is then moved to data_021fbbd8
 * (SkyWeatherDay_LastWet) and cleared. Today's pattern is 4 whenever the game is started
 * (StartKind_IsSet), this system's player has flag 1 or today has calendar event 9 or 10
 * listed, outside scene 0x3f. In a session nothing changes. */
#ifndef CLEAN_MAIN_SKY_WEATHER_DAY_H
#define CLEAN_MAIN_SKY_WEATHER_DAY_H

#include "calendar.h"
#include "sky.h"
#include "types.h"

#define SKY_WEATHER_DAY_PATTERNS 32 /* the patterns a period's odds are given for */
#define SKY_WEATHER_DAY_FORCED 4    /* today's pattern on the days that force one */

unsigned char SkyWeatherDay_LastWet(void);
int SkyWeatherDay_DrawPattern(SkyWeatherDay *day, const DateTime *date);
int SkyWeatherDay_Update(SkyWeatherDay *day, const DateTime *now);
void SkyWeatherDay_Refresh(SkyWeatherDay *day);
void SkyWeatherDay_SetToday(SkyWeatherDay *day);
void SkyWeatherDay_Reset(SkyWeatherDay *day);
void SkyWeatherDay_Destruct(SkyWeatherDay *day);
void SkyWeatherDay_Construct(SkyWeatherDay *day);

#endif
