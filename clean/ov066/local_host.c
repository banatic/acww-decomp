/* The parent side of the library (local_host.h). */
#include "local_host.h"

#include <assert.h>
#include <stddef.h>
#include <stdint.h>

#include "clean.h"
#include "local_mp.h"
#include "local_search.h"
#include "local_wireless.h"

static_assert(offsetof(LocalParentParam, ggid) == 0x08, "WMParentParam.ggid");
static_assert(offsetof(LocalParentParam, tgid) == 0x0c, "WMParentParam.tgid");
static_assert(offsetof(LocalParentParam, max_entry) == 0x10, "WMParentParam.maxEntry");
static_assert(offsetof(LocalParentParam, beacon_period) == 0x18, "WMParentParam.beaconPeriod");
static_assert(offsetof(LocalParentParam, channel) == 0x32, "WMParentParam.channel");
static_assert(offsetof(LocalParentParam, child_max_size) == 0x36, "WMParentParam.childMaxSize");
static_assert(sizeof(LocalParentParam) == 0x40, "WMParentParam");
static_assert(offsetof(LocalParentResult, state) == 0x08, "WMStartParentCallback.state");
static_assert(offsetof(LocalParentResult, mac) == 0x0a, "WMStartParentCallback.macAddress");
static_assert(offsetof(LocalParentResult, aid) == 0x10, "WMStartParentCallback.aid");
static_assert(offsetof(LocalControl, beacons_per_turn) == 0x14, "beacons per turn");
static_assert(offsetof(LocalControl, parent_max_size) == 0x1a, "parent max size");
static_assert(offsetof(LocalControl, child_max_size) == 0x1e, "child max size");
static_assert(offsetof(LocalSession, beacons_sent) == 0x96, "beacons sent");

extern LocalControl *data_ov066_0226bdec;
extern LocalSession *data_ov066_0226bdf4;

/* The game's symbols of the callbacks below, handed to WM. */
extern void func_ov066_02268458(void *result);
extern void func_ov066_02268798(void *result);
extern void func_ov066_02268a60(void *result);
extern void func_ov066_02268b04(void *result);
extern void func_ov066_02268c18(void *result);

/* The rest of the library. */
extern void func_ov066_0226a00c(void); /* measures the channels, then the request goes on */
extern void func_ov066_02269dcc(void); /* the session back to no connection */

extern int WM_SetEntry(void (*callback)(void *), u32 open);
extern int WM_SetGameInfo(void (*callback)(void *), const void *info, u32 length, u32 ggid, u32 tgid, u32 attribute);
extern int WM_EndParent(void (*callback)(void *));
extern int WM_StartParent(void (*callback)(void *));
extern int WM_SetParentParameter(void (*callback)(void *), const LocalParentParam *param);
extern u32 WM_GetDispersionBeaconPeriod(void);
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);

/* The most data a beacon's game info carries after its header (LocalBssDesc.data). */
#define LOCAL_GAME_DATA_MAX 0x68

/* 1 << aid as ARM shifts: by the low byte of the count, 0 from 32 on. */
static u32 aid_bit(int aid)
{
    u32 shift = (u32) aid & 0xff;
    return shift < 32 ? 1u << shift : 0;
}

/* func_ov066_02268370: a parent started with the header id `game_id`, or first the channels
 * measured when the session asks for it.
 * QUIRK: the measuring forgets `game_id`; once it is over the request goes on from an idle
 * radio, which starts the parent again (LocalWireless_StepIdle, LocalJoin_StepAuto). */
void LocalHost_Start(int game_id)
{
    if (data_ov066_0226bdf4->flags & LOCAL_SESSION_MEASURE_FIRST) {
        func_ov066_0226a00c();
    } else {
        LocalHost_StartNow(game_id);
    }
}
CLEAN_AS(func_ov066_02268370, LocalHost_Start)

/* func_ov066_02268458: WM_SetEntry's callback: unless a reset takes over, an error stops the
 * library. */
void LocalHost_OnSetEntry(LocalWmResult *result)
{
    if (LocalWireless_CheckReset()) {
        return;
    }
    if (result->result == LOCAL_WM_RESULT_SUCCESS) {
        return;
    }
    LocalWireless_Fail(result->result);
}
CLEAN_AS(func_ov066_02268458, LocalHost_OnSetEntry)

/* func_ov066_0226848c: the parent's entry opened (`open` TRUE) or closed to new children
 * (WM_SetEntry); the library stops on WM's error unless it is OPERATING. */
void LocalHost_SetEntry(int open)
{
    int status = WM_SetEntry(func_ov066_02268458, (u32) open);
    if (status == LOCAL_WM_RESULT_OPERATING) {
        return;
    }
    LocalWireless_Fail(status);
}
CLEAN_AS(func_ov066_0226848c, LocalHost_SetEntry)

/* func_ov066_02268798: WM_SetGameInfo's callback: unless a reset takes over, the MP
 * communication starts if that waited for the game info; an error stops the library. */
void LocalHost_OnSetGameInfo(LocalWmResult *result)
{
    if (LocalWireless_CheckReset()) {
        return;
    }
    if (result->result != LOCAL_WM_RESULT_SUCCESS) {
        LocalWireless_Fail(result->result);
        return;
    }
    if (data_ov066_0226bdf4->flags & LOCAL_SESSION_START_MP) {
        LocalMp_Start();
    }
}
CLEAN_AS(func_ov066_02268798, LocalHost_OnSetGameInfo)

/* func_ov066_022687f4: the beacon's game info set again (WM_SetGameInfo), with the entry flag
 * while the players are fewer than the most; the library stops on WM's error unless it is
 * OPERATING. */
void LocalHost_SetGameInfo(void)
{
    u32 attribute = data_ov066_0226bdf4->player_count < data_ov066_0226bdec->max_players ? LOCAL_ATTR_ENTRY : 0;
    int status = WM_SetGameInfo(func_ov066_02268798, data_ov066_0226bdf4->game_info, data_ov066_0226bdf4->game_info_length,
                                data_ov066_0226bdec->ggid, data_ov066_0226bdf4->tgid, attribute);
    if (status == LOCAL_WM_RESULT_OPERATING) {
        return;
    }
    LocalWireless_Fail(status);
}
CLEAN_AS(func_ov066_022687f4, LocalHost_SetGameInfo)

/* func_ov066_02268a60: WM_EndParent's callback: unless a reset takes over, the radio is idle,
 * the session is reset when the MP communication was ending, and the request goes on; an
 * error stops the library. */
void LocalHost_OnEnd(LocalWmResult *result)
{
    if (LocalWireless_CheckReset()) {
        return;
    }
    if (result->result != LOCAL_WM_RESULT_SUCCESS) {
        LocalWireless_Fail(result->result);
        return;
    }
    data_ov066_0226bdec->state = LOCAL_STATE_WM_IDLE;
    if (data_ov066_0226bdf4->flags & LOCAL_SESSION_ENDING_MP) {
        func_ov066_02269dcc();
    }
    LocalWireless_Continue();
}
CLEAN_AS(func_ov066_02268a60, LocalHost_OnEnd)

/* func_ov066_02268ad0: the parent ended (WM_EndParent), LocalHost_OnEnd following; the library
 * stops on WM's error unless it is OPERATING. */
void LocalHost_End(void)
{
    int status = WM_EndParent(func_ov066_02268a60);
    if (status == LOCAL_WM_RESULT_OPERATING) {
        return;
    }
    LocalWireless_Fail(status);
}
CLEAN_AS(func_ov066_02268ad0, LocalHost_End)

/* func_ov066_02268b04: WM_StartParent's callback: unless a reset takes over, a beacon sent, a
 * child joined or a child gone (back to an idle radio instead when the MP communication is to
 * end); other states are ignored and an error stops the library. */
void LocalHost_OnParent(LocalParentResult *result)
{
    if (LocalWireless_CheckReset()) {
        return;
    }
    if (result->base.result != LOCAL_WM_RESULT_SUCCESS) {
        LocalWireless_Fail(result->base.result);
        return;
    }
    switch (result->state) {
        case LOCAL_WM_STATE_BEACON_SENT:
            LocalHost_OnBeaconSent(result);
            break;
        case LOCAL_WM_STATE_CONNECTED:
            LocalHost_OnChildJoined(result);
            break;
        case LOCAL_WM_STATE_DISCONNECTED:
            if (data_ov066_0226bdf4->flags & LOCAL_SESSION_END_MP) {
                LocalWireless_StepReset();
            } else {
                LocalHost_OnChildLeft(result);
            }
            break;
    }
}
CLEAN_AS(func_ov066_02268b04, LocalHost_OnParent)

/* func_ov066_02268be4: WM_StartParent, LocalHost_OnParent following; the library stops on
 * WM's error unless it is OPERATING. */
void LocalHost_StartParent(void)
{
    int status = WM_StartParent(func_ov066_02268b04);
    if (status == LOCAL_WM_RESULT_OPERATING) {
        return;
    }
    LocalWireless_Fail(status);
}
CLEAN_AS(func_ov066_02268be4, LocalHost_StartParent)

/* func_ov066_02268c18: WM_SetParentParameter's callback: the parent starts; an error stops the
 * library.
 * QUIRK: unlike the other callbacks, a reset under way is not checked. */
void LocalHost_OnSetParentParam(LocalWmResult *result)
{
    if (result->result == LOCAL_WM_RESULT_SUCCESS) {
        LocalHost_StartParent();
    } else {
        LocalWireless_Fail(result->result);
    }
}
CLEAN_AS(func_ov066_02268c18, LocalHost_OnSetParentParam)

/* func_ov066_02268c4c: the session's parent parameters handed to WM (WM_SetParentParameter),
 * LocalHost_OnSetParentParam following; the library stops on WM's error unless it is
 * OPERATING. */
void LocalHost_SetParentParam(void)
{
    int status = WM_SetParentParameter(func_ov066_02268c18, data_ov066_0226bdf4->parent_param);
    if (status == LOCAL_WM_RESULT_OPERATING) {
        return;
    }
    LocalWireless_Fail(status);
}
CLEAN_AS(func_ov066_02268c4c, LocalHost_SetParentParam)

/* func_ov066_02268f98: a child gone: the entry reopened if the players were at their most, the
 * child forgotten (its member slot, its hello) and LOCAL_EVENT_DISCONNECTED posted. With other
 * children left the session's handler is told, the member table sent and the beacon's game
 * info marked due; with the parent alone, unless the MP communication is to end, the session's
 * MP start handler is called again and the sending freed. */
void LocalHost_OnChildLeft(LocalParentResult *result)
{
    if (data_ov066_0226bdf4->player_count == data_ov066_0226bdec->max_players) {
        LocalHost_SetEntry(TRUE);
    }
    data_ov066_0226bdf4->greeted = (u16) (data_ov066_0226bdf4->greeted & ~aid_bit(result->aid));
    LocalMp_SetMember(result->aid, NULL);
    LocalWireless_PostEvent(LOCAL_EVENT_DISCONNECTED, (u8) result->aid);
    if (data_ov066_0226bdf4->player_count > 1) {
        LocalMp_TellPeerLeft(result->aid);
        LocalMp_SendMembers();
        data_ov066_0226bdf4->flags |= LOCAL_SESSION_GAME_INFO_DUE;
        return;
    }
    if (data_ov066_0226bdf4->flags & LOCAL_SESSION_END_MP) {
        return;
    }
    data_ov066_0226bdf4->on_mp_start();
    data_ov066_0226bdf4->flags &= ~LOCAL_SESSION_SEND_BUSY;
    data_ov066_0226bdf4->flags &= ~LOCAL_SESSION_SEND_AGAIN;
}
CLEAN_AS(func_ov066_02268f98, LocalHost_OnChildLeft)

/* func_ov066_0226908c: a child joined. The beacon's game info is marked due; for the first
 * child of a starting parent the parent becomes LOCAL_STATE_MP_STARTING with AID 0, its member
 * table emptied, and the game info set again with the id LOCAL_GAME_BD8A, the MP communication
 * starting after it. The child takes its member slot, LOCAL_EVENT_CONNECTED is posted, and the
 * entry closes once the players are at their most.
 * QUIRK: a parent of the automatic pairing (LOCAL_GAME_2348) turns LOCAL_GAME_BD8A at its first
 * child, so searching children then stop at once on it. */
void LocalHost_OnChildJoined(LocalParentResult *result)
{
    data_ov066_0226bdf4->flags |= LOCAL_SESSION_GAME_INFO_DUE;
    if (data_ov066_0226bdec->state == LOCAL_STATE_PARENT_STARTING) {
        data_ov066_0226bdec->state = LOCAL_STATE_MP_STARTING;
        data_ov066_0226bdf4->aid = 0;
        LocalMp_ClearMembers();
        data_ov066_0226bdf4->flags |= LOCAL_SESSION_START_MP;
        LocalHost_UpdateGameInfo(LOCAL_GAME_BD8A, data_ov066_0226bdf4->player_count);
        LocalHost_SetGameInfo();
    }
    LocalMp_SetMember(result->aid, result->mac);
    LocalWireless_PostEvent(LOCAL_EVENT_CONNECTED, (u8) result->aid);
    if (data_ov066_0226bdf4->player_count >= data_ov066_0226bdec->max_players) {
        LocalHost_SetEntry(FALSE);
    }
}
CLEAN_AS(func_ov066_0226908c, LocalHost_OnChildJoined)

/* func_ov066_02269154: a beacon sent: the game info set again if it is due (the id kept, the
 * player count new); a starting parent counts its beacons and the request goes on after
 * LocalControl.beacons_per_turn of them. */
void LocalHost_OnBeaconSent(LocalParentResult *result)
{
    (void) result;
    if (data_ov066_0226bdf4->flags & LOCAL_SESSION_GAME_INFO_DUE) {
        LocalHost_UpdateGameInfo(LOCAL_GAME_KEEP, data_ov066_0226bdf4->player_count);
        LocalHost_SetGameInfo();
        data_ov066_0226bdf4->flags &= ~LOCAL_SESSION_GAME_INFO_DUE;
    }
    if (data_ov066_0226bdec->state != LOCAL_STATE_PARENT_STARTING) {
        return;
    }
    data_ov066_0226bdf4->beacons_sent++;
    if (data_ov066_0226bdf4->beacons_sent < data_ov066_0226bdec->beacons_per_turn) {
        return;
    }
    LocalWireless_Continue();
}
CLEAN_AS(func_ov066_02269154, LocalHost_OnBeaconSent)

/* func_ov066_02269638: `length` bytes of `data` put in the beacon's game info after its header
 * (the game info's length rounded up to even), and the game info marked due; FALSE without a
 * session or for more than LOCAL_GAME_DATA_MAX bytes. */
int LocalHost_SetGameData(const void *data, u32 length)
{
    LocalSession *session = data_ov066_0226bdf4;
    if (session == NULL || length > LOCAL_GAME_DATA_MAX) {
        return FALSE;
    }
    u8 *info = session->game_info;
    session->flags |= LOCAL_SESSION_GAME_INFO_DUE;
    MI_CpuCopy8(data, info + sizeof(LocalGameHeader), length);
    ((LocalGameHeader *) info)->data_size = (u8) length;
    data_ov066_0226bdf4->game_info_length = (u16) ((length + sizeof(LocalGameHeader) + 1) & ~1u);
    return TRUE;
}
CLEAN_AS(func_ov066_02269638, LocalHost_SetGameData)

/* func_ov066_02269748: a parent started now with the header id `game_id`: the state
 * LOCAL_STATE_PARENT_STARTING, no beacon sent yet, the parent parameters filled and handed to
 * WM. */
void LocalHost_StartNow(int game_id)
{
    data_ov066_0226bdec->state = LOCAL_STATE_PARENT_STARTING;
    data_ov066_0226bdf4->beacons_sent = 0;
    LocalHost_FillParentParam((u32) game_id);
    LocalHost_SetParentParam();
}
CLEAN_AS(func_ov066_02269748, LocalHost_StartNow)

/* func_ov066_0226978c: the parent parameters for a parent alone with the header id `game_id`:
 * one player, the game info set, the control block's game group id, a new random tgid, the
 * entry open, no multiboot, key sharing or continuous sending, WM's dispersed beacon period,
 * the session's channel and the control block's children and sizes. */
void LocalHost_FillParentParam(u32 game_id)
{
    LocalParentParam *param = data_ov066_0226bdf4->parent_param;
    data_ov066_0226bdf4->player_count = 1;
    LocalHost_UpdateGameInfo(game_id, 1);
    param->user_game_info = data_ov066_0226bdf4->game_info;
    param->user_game_info_length = data_ov066_0226bdf4->game_info_length;
    param->ggid = data_ov066_0226bdec->ggid;
    data_ov066_0226bdf4->tgid = (u16) local_next_random();
    param->tgid = data_ov066_0226bdf4->tgid;
    param->entry = 1;
    param->multiboot = 0;
    param->key_sharing = 0;
    param->continuous = 0;
    param->max_entry = data_ov066_0226bdec->max_children;
    param->beacon_period = (u16) WM_GetDispersionBeaconPeriod();
    param->channel = data_ov066_0226bdf4->parent_channel;
    param->parent_max_size = data_ov066_0226bdec->parent_max_size;
    param->child_max_size = data_ov066_0226bdec->child_max_size;
}
CLEAN_AS(func_ov066_0226978c, LocalHost_FillParentParam)

/* func_ov066_0226987c: the beacon's game info header: the id `id` (kept for LOCAL_GAME_KEEP),
 * a new random nonce, the search index, `players` and the kind LOCAL_HEADER_KIND. */
void LocalHost_UpdateGameInfo(u32 id, u8 players)
{
    LocalGameHeader *header = (LocalGameHeader *) data_ov066_0226bdf4->game_info;
    if (id != LOCAL_GAME_KEEP) {
        header->id = (u16) id;
    }
    header->nonce = (u16) local_next_random();
    header->channel_index = data_ov066_0226bdf4->channel_index;
    header->players = players;
    header->kind = LOCAL_HEADER_KIND;
}
CLEAN_AS(func_ov066_0226987c, LocalHost_UpdateGameInfo)
