/* The town's game statistics record (wfc_stats.h). */
#include "wfc_stats.h"

#include "clean.h"
#include "state_block.h"

static_assert(offsetof(WfcStats, checksum) == 0x234 && offsetof(WfcStats, status) == 0x236, "stats");
static_assert(sizeof(WfcStats) == WFC_STATS_SIZE, "stats");

/* The state block flag that keeps the record from being used. */
#define WFC_STATS_STATE_FLAG_13 0x13

extern u32 data_021dc7a8[]; /* the state block (state_block.h) */

/* func_020881ac */
u16 WfcStats_Checksum(const WfcStats *stats)
{
    return stats->checksum;
}
CLEAN_AS(func_020881ac, WfcStats_Checksum)

/* func_020881b8 */
void WfcStats_SetChecksum(WfcStats *stats, u16 checksum)
{
    stats->checksum = checksum;
}
CLEAN_AS(func_020881b8, WfcStats_SetChecksum)

/* func_020881c4: whether the record is in use (status 2) while the state block's flag 0x13 is
 * clear; the flag is asked first. */
int WfcStats_IsInUse(const WfcStats *stats)
{
    return StateBlock_TestFlag(data_021dc7a8, WFC_STATS_STATE_FLAG_13) == 0 && stats->status == WFC_STATS_STATUS_IN_USE;
}
CLEAN_AS(func_020881c4, WfcStats_IsInUse)

/* func_020881f0 */
u8 WfcStats_Byte237(const WfcStats *stats)
{
    return stats->byte_237;
}
CLEAN_AS(func_020881f0, WfcStats_Byte237)
