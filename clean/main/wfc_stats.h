/* The town's game statistics record (0x238 bytes; the state block's copy is data_021f3278,
 * the one fetched over the Nintendo Wi-Fi Connection data_021f40a4, wfc_session.h): its last
 * bytes hold a checksum that makes its halfwords sum to 0, a status and a byte overlay 74
 * hands on with the record. */
#ifndef CLEAN_MAIN_WFC_STATS_H
#define CLEAN_MAIN_WFC_STATS_H

#include "types.h"

#define WFC_STATS_SIZE 0x238

/* The status (byte 0x236). */
enum WfcStatsRecordStatus {
    WFC_STATS_STATUS_NONE = 0,     /* to be fetched */
    WFC_STATS_STATUS_RECEIVED = 1, /* fetched and checked (WfcSession_ApplyStats) */
    WFC_STATS_STATUS_IN_USE = 2,   /* received, and the date has moved on since (func_0204714c) */
    WFC_STATS_STATUS_TO_SEND = 3,  /* to be sent */
};

typedef struct WfcStats {
    u8 data[0x234]; /* 0x000 */
    u16 checksum;   /* 0x234 */
    u8 status;      /* 0x236: enum WfcStatsRecordStatus */
    u8 byte_237;    /* 0x237: what overlay 74 passes on with the record */
} WfcStats;

u16 WfcStats_Checksum(const WfcStats *stats);
void WfcStats_SetChecksum(WfcStats *stats, u16 checksum);
int WfcStats_IsInUse(const WfcStats *stats);
u8 WfcStats_Byte237(const WfcStats *stats);

#endif
