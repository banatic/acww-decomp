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

/* The record's design, blanked when the record is reset. */
#include "design.h"
#include "design_info.h"

static_assert(sizeof(Design) == offsetof(WfcStats, checksum), "stats design");

#define WFC_STATS_BLANK_COLOUR 0xf
#define WFC_STATS_BLANK_PALETTE 0

/* func_020881fc */
void WfcStats_SetByte237(WfcStats *stats, u8 value)
{
    stats->byte_237 = value;
}
CLEAN_AS(func_020881fc, WfcStats_SetByte237)

/* func_02088208 */
u8 WfcStats_Status(const WfcStats *stats)
{
    return stats->status;
}
CLEAN_AS(func_02088208, WfcStats_Status)

/* func_02088214 */
void WfcStats_SetStatus(WfcStats *stats, u8 status)
{
    stats->status = status;
}
CLEAN_AS(func_02088214, WfcStats_SetStatus)

/* func_02088220: the design the record starts with (the record itself). */
Design *WfcStats_Design(WfcStats *stats)
{
    return (Design *) (void *) stats;
}
CLEAN_AS(func_02088220, WfcStats_Design)

/* func_02088224: the design blanked: every pixel colour 15, then palette 0. The design is
 * asked for once for each. */
void WfcStats_ClearDesign(WfcStats *stats)
{
    Design_Fill((unsigned int *) (void *) WfcStats_Design(stats)->pixels, WFC_STATS_BLANK_COLOUR);
    Design *design = WfcStats_Design(stats);
    DesignInfo_SetPalette((DesignInfo *) (uintptr_t) Design_Info((unsigned int) (uintptr_t) design), WFC_STATS_BLANK_PALETTE);
}
CLEAN_AS(func_02088224, WfcStats_ClearDesign)

/* func_02088248: the record set up: reset. */
void WfcStats_Init(WfcStats *stats)
{
    WfcStats_Reset(stats);
}
CLEAN_AS(func_02088248, WfcStats_Init)

/* func_02088250: back to WFC_STATS_STATUS_NONE with a blank design. */
void WfcStats_Reset(WfcStats *stats)
{
    stats->status = WFC_STATS_STATUS_NONE;
    WfcStats_ClearDesign(stats);
}
CLEAN_AS(func_02088250, WfcStats_Reset)

/* func_02088264: destructs the record's design. */
WfcStats *WfcStats_Destruct(WfcStats *stats)
{
    Design_Destruct((Design *) (void *) stats);
    return stats;
}
CLEAN_AS(func_02088264, WfcStats_Destruct)

/* func_02088274: constructs the record's design. */
WfcStats *WfcStats_Construct(WfcStats *stats)
{
    Design_Construct((char *) stats);
    return stats;
}
CLEAN_AS(func_02088274, WfcStats_Construct)
