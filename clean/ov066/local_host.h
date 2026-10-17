/* The parent side of the local wireless library of overlay 66 (local_wireless.h): the parent
 * parameters and the beacon's game info, WM_StartParent and its callback (children joining and
 * leaving, beacons sent), the entry opened and closed by the player count, and the parent's
 * end. */
#ifndef CLEAN_OV066_LOCAL_HOST_H
#define CLEAN_OV066_LOCAL_HOST_H

#include "types.h"

#include "local_wireless.h"

/* WM's parent parameters (WMParentParam, 0x40 bytes). */
typedef struct LocalParentParam {
    u8 *user_game_info;
    u16 user_game_info_length;
    u16 padding;
    u32 ggid;
    u16 tgid;
    u16 entry;       /* entryFlag: children may connect */
    u16 max_entry;   /* the children */
    u16 multiboot;   /* multiBootFlag */
    u16 key_sharing; /* KS_Flag */
    u16 continuous;  /* CS_Flag */
    u16 beacon_period;
    u8 unk_1a[0x18];
    u16 channel;
    u16 parent_max_size;
    u16 child_max_size;
    u8 unk_38[8];
} LocalParentParam;

/* What WM_StartParent's callback is handed (WMStartParentCallback): the fields this code
 * reads. */
typedef struct LocalParentResult {
    LocalWmResult base;
    u8 unk_04[4];
    u16 state; /* LOCAL_WM_STATE_ */
    u8 mac[6]; /* the child's */
    u16 aid;   /* the child's */
} LocalParentResult;

/* The beacon kind this library's parents send (LocalGameHeader.kind). */
#define LOCAL_HEADER_KIND 5

void LocalHost_Start(int game_id);
void LocalHost_OnSetEntry(LocalWmResult *result);
void LocalHost_SetEntry(int open);
void LocalHost_OnSetGameInfo(LocalWmResult *result);
void LocalHost_SetGameInfo(void);
void LocalHost_OnEnd(LocalWmResult *result);
void LocalHost_End(void);
void LocalHost_OnParent(LocalParentResult *result);
void LocalHost_StartParent(void);
void LocalHost_OnSetParentParam(LocalWmResult *result);
void LocalHost_SetParentParam(void);
void LocalHost_OnChildLeft(LocalParentResult *result);
void LocalHost_OnChildJoined(LocalParentResult *result);
void LocalHost_OnBeaconSent(LocalParentResult *result);
int LocalHost_SetGameData(const void *data, u32 length);
void LocalHost_StartNow(int game_id);
void LocalHost_FillParentParam(u32 game_id);
void LocalHost_UpdateGameInfo(u32 id, u8 players);

#endif
