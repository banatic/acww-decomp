/* The child's search for parents (local_search.h). */
#include "local_search.h"

#include <assert.h>
#include <stddef.h>
#include <stdint.h>

#include "clean.h"
#include "local_wireless.h"

static_assert(sizeof(LocalGameHeader) == 8, "the header copied from a beacon");
static_assert(offsetof(LocalBssDesc, game_info_length) == 0x3c, "WMBssDesc.gameInfoLength");
static_assert(offsetof(LocalBssDesc, ggid) == 0x44, "WMGameInfo.ggid");
static_assert(offsetof(LocalBssDesc, attribute) == 0x4b, "WMGameInfo.attribute");
static_assert(offsetof(LocalBssDesc, header) == 0x50, "WMGameInfo.userGameInfo");
static_assert(sizeof(LocalBssDesc) == 0xc0, "WMBssDesc");
static_assert(sizeof(LocalScanParam) == 0x10, "WMScanParam");
static_assert(offsetof(LocalScanResult, state) == 0x08, "WMStartScanCallback.state");
static_assert(offsetof(LocalScanResult, mac) == 0x0a, "WMStartScanCallback.macAddress");
static_assert(offsetof(LocalScanResult, link_level) == 0x12, "WMStartScanCallback.linkLevel");
static_assert(offsetof(LocalParent, bss) == 0x20, "a parent's beacon");
static_assert(offsetof(LocalParent, bss.game_info_length) == 0x5c, "read by the game's network layer");
static_assert(offsetof(LocalParent, bss.header.data_size) == 0x77, "read by the game's network layer");
static_assert(offsetof(LocalParent, bss.data) == 0x78, "read by the game's network layer");
static_assert(sizeof(LocalParent) == 0xe0, "a parent");
static_assert(sizeof(LocalParentList) == 0x10, "a parent list");
static_assert(offsetof(LocalSearch, timeout_alarm) == 0x10, "timeout alarm");
static_assert(offsetof(LocalSearch, stop_alarm) == 0x3c, "stop alarm");
static_assert(offsetof(LocalSearch, filter) == 0x6c, "filter");
static_assert(sizeof(LocalSearch) == 0x70, "the size LocalSearch_Create allocates");

extern LocalControl *data_ov066_0226bdec;
extern LocalSession *data_ov066_0226bdf4;
/* The search, NULL outside LocalSearch_Create and LocalSearch_Destroy. */
extern LocalSearch *data_ov066_0226bdf0;

/* The game's symbols of the callbacks below, handed to WM and to alarms. */
extern void func_ov066_0226763c(void *result);
extern void func_ov066_022676a0(void *result);
extern void func_ov066_0226794c(void *argument);
extern void func_ov066_02267c74(void);

extern int WM_StartScan(void (*callback)(void *), const LocalScanParam *param);
extern int WM_EndScan(void (*callback)(void *));
extern void OS_CreateAlarm(LocalAlarm *alarm);
extern void OS_CancelAlarm(LocalAlarm *alarm);
extern void OS_SetAlarm(LocalAlarm *alarm, s64 ticks, void (*handler)(void *), void *argument);
extern u32 OS_DisableInterrupts(void);
extern u32 OS_RestoreInterrupts(u32 state);
extern void DC_InvalidateRange(void *start, u32 size);
extern void DC_StoreRange(void *start, u32 size);
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);

/* The parent lists. */
extern void func_ov066_0226a810(LocalParentList *list, u8 tag, int capacity); /* sets one up */
extern void func_ov066_0226a7d8(LocalParentList *list);                       /* frees one */
extern void func_ov066_0226a3b0(LocalParentList *list);                       /* empties one */
/* the listed parents' expiry set to `milliseconds` from now */
extern void func_ov066_0226a2e8(LocalParentList *list, int milliseconds);
extern void func_ov066_0226a404(LocalParentList *list);          /* its expiry alarms cancelled */
extern u32 func_ov066_0226a418(LocalParentList *list, u32 slot); /* the parent in `slot` */
extern u8 func_ov066_0226a434(LocalParentList *list);            /* the parents listed */
/* `mac` listed (or updated) with `id`, `link_level` and the beacon `bss`, to expire after
 * `lifetime` milliseconds; FALSE when the list is full. */
extern int func_ov066_0226a494(LocalParentList *list, int lifetime, const u8 *mac, u16 id, u16 link_level, const void *bss);
/* The next channel after `channel` that WM allows (1 to 14, round), `channel` when none. */
extern u16 func_ov066_0226a1b0(u16 channel);

/* A parent stays listed this long after its last beacon. */
#define LOCAL_PARENT_LIFETIME_MS 4000
/* At the start of a search the parents already listed expire after this long (unless
 * LOCAL_FLAG_08 empties the list instead). */
#define LOCAL_SEARCH_KEEP_MS 500
/* The search ends this long after a parent of id LOCAL_GAME_2348. */
#define LOCAL_SEARCH_STOP_MS 30

/* OS_MilliSecondsToTicks (the tick runs at 33.514 MHz / 64).
 * QUIRK: computed in 32 bits, so it wraps past 128 seconds. */
static s64 ms_to_ticks(int milliseconds)
{
    int32_t scaled = (int32_t) ((uint32_t) milliseconds * 33514u);
    return (s64) (scaled / 64);
}

/* The parent list of the channel being searched. */
static LocalParentList *current_list(void)
{
    return &data_ov066_0226bdf0->lists[data_ov066_0226bdf4->channel_index];
}

/* func_ov066_02266c7c: a parent's state (1 while listed); 0 for NULL. */
u16 LocalSearch_ParentState(LocalParent *parent)
{
    if (parent != NULL) {
        return parent->state;
    }
    return 0;
}
CLEAN_AS(func_ov066_02266c7c, LocalSearch_ParentState)

/* func_ov066_02266c8c: the data a parent's beacon carries after its header; NULL for NULL, a
 * beacon without game info or no data. */
void *LocalSearch_ParentData(LocalParent *parent)
{
    if (parent != NULL && parent->bss.game_info_length != 0 && LocalSearch_ParentDataSize(parent) != 0) {
        return parent->bss.data;
    }
    return NULL;
}
CLEAN_AS(func_ov066_02266c8c, LocalSearch_ParentData)

/* func_ov066_02266cc8: the size of that data; 0 for NULL or a beacon without game info. */
u8 LocalSearch_ParentDataSize(LocalParent *parent)
{
    if (parent != NULL && parent->bss.game_info_length != 0) {
        return parent->bss.header.data_size;
    }
    return 0;
}
CLEAN_AS(func_ov066_02266cc8, LocalSearch_ParentDataSize)

/* func_ov066_0226763c: WM_EndScan's callback: unless a reset takes over, the radio is idle and
 * the request goes on. */
void LocalSearch_OnEndScan(LocalWmResult *result)
{
    if (LocalWireless_CheckReset()) {
        return;
    }
    if (result->result == LOCAL_WM_RESULT_SUCCESS) {
        data_ov066_0226bdec->state = LOCAL_STATE_WM_IDLE;
        LocalWireless_Continue();
        return;
    }
    LocalWireless_Fail(result->result);
}
CLEAN_AS(func_ov066_0226763c, LocalSearch_OnEndScan)

/* func_ov066_0226768c: WM_EndScan, LocalSearch_OnEndScan following.
 * QUIRK: unlike the library's other WM calls, a refusal is not checked. */
void LocalSearch_EndScan(void)
{
    WM_EndScan(func_ov066_0226763c);
}
CLEAN_AS(func_ov066_0226768c, LocalSearch_EndScan)

/* func_ov066_022676a0: WM_StartScan's callback, once per channel scanned: a parent found is
 * listed, then the next channel is scanned while the search is on; once it is off the list's
 * expiry alarms are cancelled and the scan ends. A WM error stops the library. */
void LocalSearch_OnScan(LocalScanResult *result)
{
    if (LocalWireless_CheckReset()) {
        return;
    }
    if (result->base.result != LOCAL_WM_RESULT_SUCCESS) {
        LocalWireless_Fail(result->base.result);
        return;
    }
    switch (result->state) {
        case LOCAL_SCAN_PARENT_NOT_FOUND:
            break;
        case LOCAL_SCAN_PARENT_FOUND:
            LocalSearch_OnParentFound(result);
            break;
        default:
            return;
    }
    if (data_ov066_0226bdf0->flags & LOCAL_SEARCH_ACTIVE) {
        LocalSearch_ScanNextChannel();
        return;
    }
    func_ov066_0226a404(current_list());
    LocalSearch_EndScan();
}
CLEAN_AS(func_ov066_022676a0, LocalSearch_OnScan)

/* func_ov066_02267740: WM_StartScan with the scan parameters, LocalSearch_OnScan following;
 * the library stops on WM's error unless it is OPERATING. */
void LocalSearch_StartScan(void)
{
    int status = WM_StartScan(func_ov066_022676a0, data_ov066_0226bdf0->scan_param);
    if (status == LOCAL_WM_RESULT_OPERATING) {
        return;
    }
    LocalWireless_Fail(status);
}
CLEAN_AS(func_ov066_02267740, LocalSearch_StartScan)

/* func_ov066_02267784: the parent in `slot` of the list of search index `list`; NULL without
 * a search, for a list past the channels' count or a slot past the list's capacity. */
void *LocalSearch_ParentAt(u32 list, int slot)
{
    if (data_ov066_0226bdf0 == NULL || list >= data_ov066_0226bdec->channel_count) {
        return NULL;
    }
    return (void *) (uintptr_t) func_ov066_0226a418(&data_ov066_0226bdf0->lists[list], (u32) slot);
}
CLEAN_AS(func_ov066_02267784, LocalSearch_ParentAt)

/* func_ov066_022677e0: the parents listed for search index `list`; 0 without a search or for a
 * list past the channels' count. */
u32 LocalSearch_CountParents(u32 list)
{
    if (data_ov066_0226bdf0 == NULL || list >= data_ov066_0226bdec->channel_count) {
        return 0;
    }
    return func_ov066_0226a434(&data_ov066_0226bdf0->lists[list]);
}
CLEAN_AS(func_ov066_022677e0, LocalSearch_CountParents)

/* func_ov066_0226783c: TRUE when the parent of `header` (in the search's beacon) passes the
 * checks the flags ask for (its game group id, the search index and kind its header names)
 * and the game's filter, if one is set. */
int LocalSearch_AcceptParent(LocalScanResult *parent, LocalGameHeader *header)
{
    LocalControl *control = data_ov066_0226bdec;
    if ((control->flags & LOCAL_FLAG_MATCH_GGID) && data_ov066_0226bdf0->bss->ggid != control->ggid) {
        return FALSE;
    }
    if ((control->flags & LOCAL_FLAG_MATCH_CHANNEL) && header->channel_index != data_ov066_0226bdf4->channel_index) {
        return FALSE;
    }
    if ((control->flags & LOCAL_FLAG_MATCH_KIND_5) && header->kind != 5) {
        return FALSE;
    }
    if (data_ov066_0226bdf0->filter == 0) {
        return TRUE;
    }
    return ((LocalParentFilter *) (uintptr_t) data_ov066_0226bdf0->filter)(parent);
}
CLEAN_AS(func_ov066_0226783c, LocalSearch_AcceptParent)

/* func_ov066_02267908: the search ends now: the session told, the delayed stop cancelled. */
void LocalSearch_StopNow(void)
{
    data_ov066_0226bdf4->flags |= LOCAL_SESSION_SEARCH_STOPPED;
    OS_CancelAlarm(&data_ov066_0226bdf0->stop_alarm);
    LocalSearch_Stop();
}
CLEAN_AS(func_ov066_02267908, LocalSearch_StopNow)

/* func_ov066_0226794c: the stop alarm's handler. */
void LocalSearch_OnStopAlarm(void *argument)
{
    (void) argument;
    LocalSearch_StopNow();
}
CLEAN_AS(func_ov066_0226794c, LocalSearch_OnStopAlarm)

/* func_ov066_02267958: a parent found: listed for the channel being searched. A beacon without
 * game info is listed with LOCAL_GAME_NO_INFO (unless LOCAL_FLAG_SKIP_NO_GAME_INFO); one with
 * game info only when the parent takes children and LocalSearch_AcceptParent agrees. Then, with
 * LOCAL_FLAG_08, a parent of LOCAL_GAME_BD8A ends the search at once and the first of
 * LOCAL_GAME_2348 ends it LOCAL_SEARCH_STOP_MS later.
 * QUIRK: the header is copied to the stack and that copy's cache lines stored (DC_StoreRange),
 * which does nothing for it. */
void LocalSearch_OnParentFound(LocalScanResult *parent)
{
    DC_InvalidateRange(data_ov066_0226bdf0->bss, sizeof(LocalBssDesc));
    LocalBssDesc *bss = data_ov066_0226bdf0->bss;
    if (bss->game_info_length == 0) {
        if (data_ov066_0226bdec->flags & LOCAL_FLAG_SKIP_NO_GAME_INFO) {
            return;
        }
        func_ov066_0226a494(current_list(), LOCAL_PARENT_LIFETIME_MS, parent->mac, LOCAL_GAME_NO_INFO, parent->link_level,
                            bss);
        return;
    }
    if ((bss->attribute & LOCAL_ATTR_ENTRY) == 0) {
        return;
    }
    LocalGameHeader header;
    MI_CpuCopy8(&bss->header, &header, sizeof(header));
    DC_StoreRange(&header, sizeof(header));
    if (!LocalSearch_AcceptParent(parent, &header)) {
        return;
    }
    func_ov066_0226a494(current_list(), LOCAL_PARENT_LIFETIME_MS, parent->mac, header.id, parent->link_level,
                        data_ov066_0226bdf0->bss);
    if ((data_ov066_0226bdec->flags & LOCAL_FLAG_08) == 0) {
        return;
    }
    if (header.id == LOCAL_GAME_BD8A) {
        LocalSearch_StopNow();
        return;
    }
    if (header.id != LOCAL_GAME_2348) {
        return;
    }
    if (data_ov066_0226bdf0->flags & LOCAL_SEARCH_STOP_SET) {
        return;
    }
    OS_CancelAlarm(&data_ov066_0226bdf0->stop_alarm);
    OS_SetAlarm(&data_ov066_0226bdf0->stop_alarm, ms_to_ticks(LOCAL_SEARCH_STOP_MS), func_ov066_0226794c, NULL);
    data_ov066_0226bdf0->flags |= LOCAL_SEARCH_STOP_SET;
}
CLEAN_AS(func_ov066_02267958, LocalSearch_OnParentFound)

/* func_ov066_02267b58: the scan parameters for the search index's channel: the session's
 * channel set from it, the search's beacon buffer, the time per channel, any parent. */
void LocalSearch_SetScanParam(void)
{
    LocalScanParam *param = data_ov066_0226bdf0->scan_param;
    data_ov066_0226bdf4->channel = (u8) LocalSearch_ChannelAt(data_ov066_0226bdf4->channel_index);
    param->bss = data_ov066_0226bdf0->bss;
    param->channel = data_ov066_0226bdf4->channel;
    param->max_channel_time = data_ov066_0226bdec->scan_time;
    for (int i = 0; i < 6; i++) {
        param->bssid[i] = 0xff;
    }
}
CLEAN_AS(func_ov066_02267b58, LocalSearch_SetScanParam)

/* func_ov066_02267be0: the search is off (the scan ends after the channel being scanned) and
 * its timeout cancelled. */
void LocalSearch_Stop(void)
{
    data_ov066_0226bdf0->flags &= ~LOCAL_SEARCH_ACTIVE;
    OS_CancelAlarm(&data_ov066_0226bdf0->timeout_alarm);
}
CLEAN_AS(func_ov066_02267be0, LocalSearch_Stop)

/* func_ov066_02267c0c: the next channel scanned (the state LOCAL_STATE_SEARCHING), the search
 * index moving on round the channels. */
void LocalSearch_ScanNextChannel(void)
{
    data_ov066_0226bdec->state = LOCAL_STATE_SEARCHING;
    LocalSearch_SetScanParam();
    LocalSearch_StartScan();
    data_ov066_0226bdf4->channel_index++;
    if (data_ov066_0226bdf4->channel_index >= data_ov066_0226bdec->channel_count) {
        data_ov066_0226bdf4->channel_index = 0;
    }
}
CLEAN_AS(func_ov066_02267c0c, LocalSearch_ScanNextChannel)

/* func_ov066_02267c74: the timeout alarm's handler: the search stops, unless a delayed stop is
 * already set. */
void LocalSearch_OnTimeout(void)
{
    if (data_ov066_0226bdf0->flags & LOCAL_SEARCH_STOP_SET) {
        return;
    }
    LocalSearch_Stop();
}
CLEAN_AS(func_ov066_02267c74, LocalSearch_OnTimeout)

/* func_ov066_02267cb0: a search started on the current search index, to stop after
 * `milliseconds` (0: until stopped). With LOCAL_FLAG_08 its parent list is emptied; otherwise
 * the parents listed expire after LOCAL_SEARCH_KEEP_MS and the game's filter is cleared. */
void LocalSearch_Start(int milliseconds)
{
    if (data_ov066_0226bdec->flags & LOCAL_FLAG_08) {
        func_ov066_0226a3b0(current_list());
    } else {
        func_ov066_0226a2e8(current_list(), LOCAL_SEARCH_KEEP_MS);
        LocalSearch_SetFilter(0);
    }
    data_ov066_0226bdf0->flags |= LOCAL_SEARCH_ACTIVE;
    data_ov066_0226bdf0->flags &= ~LOCAL_SEARCH_STOP_SET;
    if (milliseconds != 0) {
        OS_CancelAlarm(&data_ov066_0226bdf0->timeout_alarm);
        OS_SetAlarm(&data_ov066_0226bdf0->timeout_alarm, ms_to_ticks(milliseconds), (void (*)(void *)) func_ov066_02267c74,
                    NULL);
    }
    LocalSearch_ScanNextChannel();
}
CLEAN_AS(func_ov066_02267cb0, LocalSearch_Start)

/* func_ov066_02267db4: the channel of search index `index`: from the control block's table,
 * or without one the next channel WM allows after the session's.
 * QUIRK: without a table `index` is not used. REQUIRES: with a table, index is within it. */
int LocalSearch_ChannelAt(int index)
{
    if (data_ov066_0226bdec->channels != NULL) {
        return data_ov066_0226bdec->channels[index];
    }
    return func_ov066_0226a1b0(data_ov066_0226bdf4->channel);
}
CLEAN_AS(func_ov066_02267db4, LocalSearch_ChannelAt)

/* func_ov066_02267e00: the game's parent filter set (0 for none), with the interrupts
 * disabled. */
void LocalSearch_SetFilter(u32 filter)
{
    u32 interrupts = OS_DisableInterrupts();
    data_ov066_0226bdf0->filter = filter;
    OS_RestoreInterrupts(interrupts);
}
CLEAN_AS(func_ov066_02267e00, LocalSearch_SetFilter)

/* func_ov066_02267e28: the search freed: its parent lists (last first), its buffers, its alarms
 * cancelled. */
void LocalSearch_Destroy(void)
{
    for (int i = data_ov066_0226bdec->channel_count - 1; i >= 0; i--) {
        func_ov066_0226a7d8(&data_ov066_0226bdf0->lists[i]);
    }
    LocalWireless_Free(data_ov066_0226bdf0->lists);
    LocalWireless_Free(data_ov066_0226bdf0->bss);
    LocalWireless_Free(data_ov066_0226bdf0->scan_param);
    data_ov066_0226bdf0->filter = 0;
    data_ov066_0226bdf0->flags &= ~LOCAL_SEARCH_STOP_SET;
    OS_CancelAlarm(&data_ov066_0226bdf0->stop_alarm);
    OS_CancelAlarm(&data_ov066_0226bdf0->timeout_alarm);
    LocalWireless_Free(data_ov066_0226bdf0);
    data_ov066_0226bdf0 = NULL;
}
CLEAN_AS(func_ov066_02267e28, LocalSearch_Destroy)

/* func_ov066_02267ef8: the search allocated: its scan parameters and beacon buffer (aligned to
 * the cache's 32 bytes, as WM writes them), one parent list per channel of
 * LocalControl.parents_per_list parents, and its alarms.
 * REQUIRES: the allocations succeed (the ROM writes through the NULL it is given). */
void LocalSearch_Create(void)
{
    data_ov066_0226bdf0 = LocalWireless_Alloc(sizeof(LocalSearch), 4);
    data_ov066_0226bdf0->scan_param = LocalWireless_Alloc(0x20, 0x20);
    data_ov066_0226bdf0->bss = LocalWireless_Alloc(sizeof(LocalBssDesc), 0x20);
    data_ov066_0226bdf0->lists = LocalWireless_Alloc(data_ov066_0226bdec->channel_count * (int) sizeof(LocalParentList), 4);
    for (int i = 0; i < data_ov066_0226bdec->channel_count; i++) {
        func_ov066_0226a810(&data_ov066_0226bdf0->lists[i], (u8) i, data_ov066_0226bdec->parents_per_list);
    }
    OS_CreateAlarm(&data_ov066_0226bdf0->timeout_alarm);
    OS_CreateAlarm(&data_ov066_0226bdf0->stop_alarm);
}
CLEAN_AS(func_ov066_02267ef8, LocalSearch_Create)

/* func_ov066_022682cc: LOCAL_REQUEST_SEARCH from an idle radio: a search started until it is
 * stopped, and the request goes on (it is reached once the search is on). */
void LocalSearch_Begin(void)
{
    LocalSearch_Start(0);
    LocalWireless_Continue();
}
CLEAN_AS(func_ov066_022682cc, LocalSearch_Begin)
