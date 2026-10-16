/* The town's season (season.h). */
#include "season.h"

#include "clean.h"
#include "main/clock.h"

/* The day a season ends on: the season up to and including `last_day` of `month`, after the
 * entries before it. */
typedef struct SeasonEnd {
    u8 month;
    u8 last_day;
    u8 unused[2];
    u32 season;
} SeasonEnd;

static_assert(sizeof(SeasonEnd) == 8, "season end");

#define SEASON_ENDS 13

/* The ends of the seasons, in the order of the year. */
extern const SeasonEnd data_020d21ec[SEASON_ENDS];
/* Each season's color (RGB555). */
extern const u16 data_020d20d0[SEASON_COUNT];
/* The town layout; bits 2-7 of its byte 8 are the season. */
extern u8 data_021ebcc8[];

/* func_020b7074: the town's season's color; the first season's for a season of 12 or more. */
unsigned short Season_Color(void)
{
    unsigned int season = (unsigned int) (data_021ebcc8[8] >> 2);
    if (season < SEASON_COUNT) {
        return data_020d20d0[season];
    }
    return data_020d20d0[0];
}
CLEAN_AS(func_020b7074, Season_Color)

/* func_020b7098: the season of today's date (the first end not before it); 0 when it is after
 * every end (the table's last one is December 31). */
u32 Season_FromDate(void)
{
    u8 day_month[8];
    Clock_GetDayMonth(day_month);
    u8 day = day_month[0];
    u8 month = day_month[1];

    for (int i = 0; i < SEASON_ENDS; i++) {
        const SeasonEnd *end = &data_020d21ec[i];
        if (month < end->month || (month == end->month && day <= end->last_day)) {
            return end->season;
        }
    }
    return 0;
}
CLEAN_AS(func_020b7098, Season_FromDate)
