/* The town's pests: two flags of main (data_021c776c) taken from bits 7 and 6 of byte 0x30 of
 * data_021c79c4, the town summary's totals (TOWN_TOTALS_HAS_TRASH and
 * TOWN_TOTALS_HAS_SPOILED_TURNIP, town_acre_count.h): an inner acre holds trash (items
 * 0x1320-0x1322) and one holds spoiled turnips on an unmarked tile. In scenes 0 and 0x31 they
 * are handed to overlay 3's insects (town_insect.h): either lets flies (kind 0x33, item 0x12e3)
 * come to them, and the turnips also bring the event insect of kind 0x3b, the ants (caught as
 * kind 0x18, item 0x12c8). */
#ifndef CLEAN_MAIN_TOWN_PESTS_H
#define CLEAN_MAIN_TOWN_PESTS_H

#include "types.h"

void TownPests_Update(void);
void TownPests_Apply(u8 *flags);
void TownPests_ReadFlags(u8 *flags);

#endif
