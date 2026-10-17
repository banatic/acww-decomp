/* The child's search for parents in the local wireless library of overlay 66
 * (local_wireless.h): WM_StartScan over the channels one at a time, each parent found kept in
 * the parent list of the channel's index with its link level and its beacon, and the lists
 * the game reads (Local_ListEntries in clean/autoload_2/network.c). */
#ifndef CLEAN_OV066_LOCAL_SEARCH_H
#define CLEAN_OV066_LOCAL_SEARCH_H

#include "types.h"

#include "local_wireless.h"

/* The first 8 bytes of the user game info this game's parents send in their beacons; the data
 * follows them. */
typedef struct LocalGameHeader {
    u16 id;           /* LOCAL_GAME_ */
    u16 nonce;        /* random, new each time the parent sets it */
    u8 channel_index; /* the search index it is meant for (LOCAL_FLAG_MATCH_CHANNEL) */
    u8 players;       /* the parent's player count */
    u8 kind;          /* compared with 5 (LOCAL_FLAG_MATCH_KIND_5) */
    u8 data_size;     /* the bytes of data that follow */
} LocalGameHeader;

/* Header ids with a meaning to the search (LocalSearch_OnParentFound). */
#define LOCAL_GAME_NO_INFO 0xacce /* recorded for a parent whose beacon has no game info */
#define LOCAL_GAME_BD8A 0xbd8a    /* the id LocalWireless_StepIdle starts a parent with */
#define LOCAL_GAME_2348 0x2348    /* the id the automatic pairing starts a parent with */
#define LOCAL_GAME_KEEP 0xe34d    /* to LocalHost_UpdateGameInfo: the id is kept */

/* A parent's beacon (WM's WMBssDesc, 0xc0 bytes): the fields this code reads. */
typedef struct LocalBssDesc {
    u8 unk_00[0x3c];
    u16 game_info_length; /* 0 for a beacon without game info */
    u8 unk_3e[6];
    u32 ggid; /* WMGameInfo.ggid */
    u8 unk_48[3];
    u8 attribute; /* WMGameInfo.attribute: LOCAL_ATTR_ENTRY */
    u8 unk_4c[4];
    LocalGameHeader header; /* WMGameInfo.userGameInfo */
    u8 data[0x68];
} LocalBssDesc;

#define LOCAL_ATTR_ENTRY 0x1 /* WM_ATTR_FLAG_ENTRY: the parent takes children */

/* What WM_StartScan scans (WMScanParam), 0x20 bytes allocated for it. */
typedef struct LocalScanParam {
    LocalBssDesc *bss; /* where WM writes the beacon found */
    u16 channel;
    u16 max_channel_time;
    u8 bssid[6]; /* all 0xff: any parent */
} LocalScanParam;

/* What WM_StartScan's callback is handed (WMStartScanCallback): the fields this code reads. */
typedef struct LocalScanResult {
    LocalWmResult base;
    u8 unk_04[4];
    u16 state; /* LOCAL_SCAN_ */
    u8 mac[6];
    u8 unk_10[2];
    u16 link_level;
} LocalScanResult;

#define LOCAL_SCAN_PARENT_NOT_FOUND 4 /* WM_STATECODE_PARENT_NOT_FOUND */
#define LOCAL_SCAN_PARENT_FOUND 5     /* WM_STATECODE_PARENT_FOUND */

typedef struct LocalParentList LocalParentList;

/* A parent in a list (0xe0 bytes). */
typedef struct LocalParent {
    u16 state; /* 1 while the parent is listed */
    u8 mac[6];
    u16 id;        /* its header's id, or LOCAL_GAME_NO_INFO */
    u8 link_level; /* the average of the last 6 */
    u8 history_index;
    u8 history[6];
    u8 unk_12[2];
    LocalParentList *owner;
    u8 unk_18[8];
    LocalBssDesc bss; /* its last beacon */
} LocalParent;

/* A list of the parents found on one search index (16 bytes). */
struct LocalParentList {
    u8 tag; /* its alarms' tag, less 0x80 */
    u8 count;
    u8 capacity;
    u8 unk_03;
    LocalParent *parents;
    void *alarms; /* one OSAlarm (0x2c bytes) each: the parent's expiry */
    void (*on_added)(LocalParent *parent);
};

/* An OSAlarm. */
typedef struct LocalAlarm {
    u8 unk_00[0x2c];
} LocalAlarm;

/* The search (data_ov066_0226bdf0), allocated by LocalSearch_Create. */
typedef struct LocalSearch {
    LocalScanParam *scan_param;
    LocalBssDesc *bss;
    LocalParentList *lists;   /* LocalControl.channel_count of them */
    u32 flags;                /* LOCAL_SEARCH_ */
    LocalAlarm timeout_alarm; /* ends the search (LocalSearch_Start) */
    LocalAlarm stop_alarm;    /* ends it 30 ms after a parent of id 0x2348 */
    u8 unk_68[4];
    u32 filter; /* a function of the game's that accepts a parent, or 0 */
} LocalSearch;

#define LOCAL_SEARCH_STOP_SET 0x1 /* stop_alarm is set */
#define LOCAL_SEARCH_ACTIVE 0x2   /* scanning one channel after the other */

/* A filter's prototype (LocalSearch.filter): TRUE to list the parent. */
typedef int LocalParentFilter(LocalScanResult *parent);

u16 LocalSearch_ParentState(LocalParent *parent);
void *LocalSearch_ParentData(LocalParent *parent);
u8 LocalSearch_ParentDataSize(LocalParent *parent);
void LocalSearch_OnEndScan(LocalWmResult *result);
void LocalSearch_EndScan(void);
void LocalSearch_OnScan(LocalScanResult *result);
void LocalSearch_StartScan(void);
void *LocalSearch_ParentAt(u32 list, int slot);
u32 LocalSearch_CountParents(u32 list);
int LocalSearch_AcceptParent(LocalScanResult *parent, LocalGameHeader *header);
void LocalSearch_StopNow(void);
void LocalSearch_OnStopAlarm(void *argument);
void LocalSearch_OnParentFound(LocalScanResult *parent);
void LocalSearch_SetScanParam(void);
void LocalSearch_Stop(void);
void LocalSearch_ScanNextChannel(void);
void LocalSearch_OnTimeout(void);
void LocalSearch_Start(int milliseconds);
int LocalSearch_ChannelAt(int index);
void LocalSearch_SetFilter(u32 filter);
void LocalSearch_Destroy(void);
void LocalSearch_Create(void);
void LocalSearch_Begin(void);

/* LocalParent.state while the parent is listed (0: a free slot). */
#define LOCAL_PARENT_LISTED 1
/* The link levels a listed parent averages (LocalParent.history). */
#define LOCAL_LINK_HISTORY 6
/* A list's alarms are tagged its tag plus this (OS_SetAlarmTag, OS_CancelAlarms). */
#define LOCAL_LIST_ALARM_TAG 0x80

void LocalSearch_RenewExpiry(LocalParentList *list, int milliseconds);
void LocalSearch_ClearList(LocalParentList *list);
void LocalSearch_CancelExpiry(LocalParentList *list);
u32 LocalSearch_ListParentAt(LocalParentList *list, u32 slot);
u8 LocalSearch_ListCount(LocalParentList *list);
void LocalSearch_OnParentExpired(LocalParent *parent);
int LocalSearch_ListParent(LocalParentList *list, int lifetime, const u8 *mac, u16 id, u16 link_level, const void *bss);
void LocalSearch_FreeList(LocalParentList *list);
void LocalSearch_InitList(LocalParentList *list, u8 tag, int capacity);

#endif
