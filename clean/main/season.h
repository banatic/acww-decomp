/* The town's season: one of twelve parts of the year (0-11), from the date by the table of
 * their ends (data_020d21ec): 0 from February 25 to March 31, 1 from April 1 to July 22, ...,
 * 9 from December 11 to February 3, 10 and 11 in the rest of February. Seasons 9 and later
 * have snow (scene_query.h). It is kept in bits 2-7 of the town layout's settings
 * (town_layout.h); each season has a color. */
#ifndef CLEAN_MAIN_SEASON_H
#define CLEAN_MAIN_SEASON_H

#include "types.h"

#define SEASON_COUNT 12

unsigned short Season_Color(void);
u32 Season_FromDate(void);

#endif
