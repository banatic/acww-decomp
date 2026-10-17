/* The child side of the library and the automatic pairing (local_join.h). */
#include "local_join.h"

#include <assert.h>
#include <stddef.h>
#include <stdint.h>

#include "clean.h"
#include "local_host.h"
#include "local_mp.h"
#include "local_search.h"
#include "local_wireless.h"

static_assert(offsetof(LocalConnectResult, state) == 0x08, "WMStartConnectCallback.state");
static_assert(offsetof(LocalConnectResult, aid) == 0x0a, "WMStartConnectCallback.aid");
static_assert(offsetof(LocalParent, id) == 0x08, "a parent's id");
static_assert(offsetof(LocalSession, turn) == 0x94, "pairing turn");

extern LocalControl *data_ov066_0226bdec;
extern LocalSession *data_ov066_0226bdf4;

/* The game's symbols of the callbacks below, handed to WM. */
extern void func_ov066_02268410(void *result);
extern void func_ov066_02268878(void *result);
extern void func_ov066_0226890c(void *result);

extern void func_ov066_02269dcc(void); /* the session back to no connection */

extern int WM_Disconnect(void (*callback)(void *), u32 aid);
extern int WM_StartConnectEx(void (*callback)(void *), const LocalBssDesc *bss, const u8 *ssid, int power_save, u32 auth_mode);

/* func_ov066_02268098: the step of the automatic pairing from an idle radio, or as it goes on.
 * When a search stopped on a wanted parent and its list holds parents, the best one is
 * connected to. Otherwise, in the turn that searches, a starting parent ends and an idle or
 * searching child searches for LocalControl.search_time; in the other turns an idle radio
 * starts a parent of LOCAL_GAME_2348. Each search and each parent started moves to the next
 * turn, as does a starting parent outside the turn that searches. */
void LocalJoin_StepAuto(void)
{
    int connecting = FALSE;
    if ((data_ov066_0226bdf4->flags & LOCAL_SESSION_SEARCH_STOPPED) &&
        (int) LocalSearch_CountParents(data_ov066_0226bdf4->channel_index) > 0) {
        connecting = LocalJoin_ConnectToBest();
    }
    if (connecting) {
        return;
    }
    if (data_ov066_0226bdf4->turn == data_ov066_0226bdf4->search_turn) {
        switch (data_ov066_0226bdec->state) {
            case LOCAL_STATE_PARENT_STARTING:
                LocalHost_End();
                break;
            case LOCAL_STATE_WM_IDLE:
            case LOCAL_STATE_SEARCHING:
                LocalJoin_NextTurn();
                LocalSearch_Start(data_ov066_0226bdec->search_time);
                break;
        }
    } else {
        switch (data_ov066_0226bdec->state) {
            case LOCAL_STATE_WM_IDLE:
                LocalHost_Start(LOCAL_GAME_2348);
                LocalJoin_NextTurn();
                break;
            case LOCAL_STATE_PARENT_STARTING:
                LocalJoin_NextTurn();
                break;
        }
    }
}
CLEAN_AS(func_ov066_02268098, LocalJoin_StepAuto)

/* func_ov066_0226818c: the parent to connect to from the search index's list: the first one of
 * LOCAL_GAME_BD8A, else one of LOCAL_GAME_2348; connected to with a retry on failure. FALSE
 * when there is none.
 * QUIRK: only whether the MAC addresses differ is used, not which is greater, so the last
 * parent of LOCAL_GAME_2348 listed is the one taken.
 * REQUIRES: the session's search index is within the channels (every slot then has a parent). */
int LocalJoin_ConnectToBest(void)
{
    LocalParent *best = NULL;
    for (u8 slot = 0; slot < data_ov066_0226bdec->parents_per_list; slot++) {
        LocalParent *parent = LocalSearch_ParentAt(data_ov066_0226bdf4->channel_index, slot);
        if (parent->state == 0) {
            continue;
        }
        if (parent->id == LOCAL_GAME_BD8A) {
            best = parent;
            break;
        }
        if (parent->id == LOCAL_GAME_2348) {
            if (best == NULL || LocalJoin_CompareMac(parent->mac, best->mac) != 0) {
                best = parent;
            }
        }
    }
    if (best == NULL) {
        return FALSE;
    }
    LocalJoin_Start(best, TRUE);
    return TRUE;
}
CLEAN_AS(func_ov066_0226818c, LocalJoin_ConnectToBest)

/* func_ov066_02268268: the next turn of the automatic pairing; after the last a new random
 * turn of four is the one that searches. */
void LocalJoin_NextTurn(void)
{
    data_ov066_0226bdf4->turn++;
    if (data_ov066_0226bdf4->turn < LOCAL_PAIRING_TURNS) {
        return;
    }
    data_ov066_0226bdf4->turn = 0;
    data_ov066_0226bdf4->search_turn = (u8) (local_next_random() & (LOCAL_PAIRING_TURNS - 1));
}
CLEAN_AS(func_ov066_02268268, LocalJoin_NextTurn)

/* func_ov066_022682ec: the listed `parent` chosen (one of LOCAL_GAME_BD8A or LOCAL_GAME_2348)
 * and LOCAL_REQUEST_CHILD asked for, with `on_done` and `argument`; FALSE for NULL, a parent
 * not listed or of another id. */
int LocalJoin_Select(LocalParent *parent, LocalDoneHandler *on_done, void *argument)
{
    if (parent == NULL || parent->state == 0) {
        return FALSE;
    }
    if (parent->id != LOCAL_GAME_2348 && parent->id != LOCAL_GAME_BD8A) {
        return FALSE;
    }
    data_ov066_0226bdf4->chosen_parent = parent;
    data_ov066_0226bdf4->flags |= LOCAL_SESSION_PARENT_CHOSEN;
    return LocalWireless_Request(LOCAL_REQUEST_CHILD, on_done, argument);
}
CLEAN_AS(func_ov066_022682ec, LocalJoin_Select)

/* func_ov066_022683b4: the 6-byte MAC addresses compared byte by byte: 1 when `a` is greater,
 * -1 when it is less, 0 when equal. */
int LocalJoin_CompareMac(const u8 *a, const u8 *b)
{
    for (int i = 0; i < 6; i++) {
        if (a[i] > b[i]) {
            return 1;
        }
        if (a[i] < b[i]) {
            return -1;
        }
    }
    return 0;
}
CLEAN_AS(func_ov066_022683b4, LocalJoin_CompareMac)

/* func_ov066_02268410: the callback of the WM reset after a failed connection: the reset is
 * over and, on success, the radio is idle and a search of LOCAL_RETRY_SEARCH_MS starts; an
 * error stops the library.
 * QUIRK: unlike LocalWireless_OnReset, a failure is not retried and the reset flags of the
 * control block are not cleared. */
void LocalJoin_OnRetryReset(LocalWmResult *result)
{
    LocalWireless_ClearResetting();
    if (result->result != LOCAL_WM_RESULT_SUCCESS) {
        LocalWireless_Fail(result->result);
        return;
    }
    data_ov066_0226bdec->state = LOCAL_STATE_WM_IDLE;
    LocalSearch_Start(LOCAL_RETRY_SEARCH_MS);
}
CLEAN_AS(func_ov066_02268410, LocalJoin_OnRetryReset)

/* func_ov066_02268878: WM_Disconnect's callback: unless a reset takes over, the radio is idle,
 * the session reset and the request goes on; an error stops the library. */
void LocalJoin_OnDisconnect(LocalWmResult *result)
{
    if (LocalWireless_CheckReset()) {
        return;
    }
    if (result->result != LOCAL_WM_RESULT_SUCCESS) {
        LocalWireless_Fail(result->result);
        return;
    }
    data_ov066_0226bdec->state = LOCAL_STATE_WM_IDLE;
    func_ov066_02269dcc();
    LocalWireless_Continue();
}
CLEAN_AS(func_ov066_02268878, LocalJoin_OnDisconnect)

/* func_ov066_022688cc: the connection of `aid` (0: a child's to its parent) ended
 * (WM_Disconnect), LocalJoin_OnDisconnect following; TRUE when WM took the call, otherwise the
 * library stops on WM's error. */
int LocalJoin_Disconnect(int aid)
{
    int status = WM_Disconnect(func_ov066_02268878, (u32) aid);
    if (status == LOCAL_WM_RESULT_OPERATING) {
        return TRUE;
    }
    LocalWireless_Fail(status);
    return FALSE;
}
CLEAN_AS(func_ov066_022688cc, LocalJoin_Disconnect)

/* func_ov066_0226890c: WM_StartConnectEx's callback. Unless a reset takes over: connected, the
 * beacon lost, or disconnected (back to an idle radio instead when the MP communication is to
 * end); the start of the connection is ignored and another state stops the library on
 * LOCAL_ERROR_CONNECT_STATE. A failed connection resets WM and searches again when it is to be
 * retried, otherwise goes back to an idle radio; another error stops the library. */
void LocalJoin_OnConnect(LocalConnectResult *result)
{
    if (LocalWireless_CheckReset()) {
        return;
    }
    u16 code = result->base.result;
    if (code == LOCAL_WM_RESULT_SUCCESS) {
        switch (result->state) {
            case LOCAL_WM_STATE_CONNECTED:
                LocalJoin_OnConnected(result);
                return;
            case LOCAL_WM_STATE_BEACON_LOST:
                LocalJoin_OnBeaconLost(result);
                return;
            case LOCAL_WM_STATE_DISCONNECTED:
                if (data_ov066_0226bdf4->flags & LOCAL_SESSION_END_MP) {
                    LocalWireless_StepReset();
                } else {
                    LocalJoin_OnDisconnected(result);
                }
                return;
            case LOCAL_WM_STATE_CONNECT_START:
                return;
            default:
                LocalWireless_Fail(LOCAL_ERROR_CONNECT_STATE);
                return;
        }
    }
    if (code == LOCAL_WM_RESULT_FAILED) {
        if (data_ov066_0226bdf4->flags & LOCAL_SESSION_RETRY_CONNECT) {
            LocalWireless_StartReset(func_ov066_02268410);
        } else {
            LocalWireless_StepReset();
        }
        return;
    }
    LocalWireless_Fail(code);
}
CLEAN_AS(func_ov066_0226890c, LocalJoin_OnConnect)

/* func_ov066_02268a1c: a connection to the parent of the beacon `bss` (WM_StartConnectEx with
 * no SSID, power saving and open authentication), LocalJoin_OnConnect following; the library
 * stops on WM's error unless it is OPERATING. */
void LocalJoin_Connect(const LocalBssDesc *bss)
{
    int status = WM_StartConnectEx(func_ov066_0226890c, bss, NULL, TRUE, 0);
    if (status == LOCAL_WM_RESULT_OPERATING) {
        return;
    }
    LocalWireless_Fail(status);
}
CLEAN_AS(func_ov066_02268a1c, LocalJoin_Connect)

/* func_ov066_02268e14: the child disconnected from its parent: the radio idle, the session's MP
 * handler called, the parent's member slot freed when the control block asks for it, back to
 * an idle radio unless the MP communication is to end, and LOCAL_EVENT_ENDED posted. */
void LocalJoin_OnDisconnected(LocalConnectResult *result)
{
    (void) result;
    data_ov066_0226bdec->state = LOCAL_STATE_WM_IDLE;
    data_ov066_0226bdf4->on_mp_start();
    if (data_ov066_0226bdec->flags & LOCAL_FLAG_FORGET_PARENT) {
        LocalMp_SetMember(0, NULL);
    }
    if ((data_ov066_0226bdf4->flags & LOCAL_SESSION_END_MP) == 0) {
        LocalWireless_StepReset();
    }
    LocalWireless_PostEvent(LOCAL_EVENT_ENDED, 0);
}
CLEAN_AS(func_ov066_02268e14, LocalJoin_OnDisconnected)

/* func_ov066_02268e9c: the parent's beacon lost: nothing (WM goes on to disconnect). */
void LocalJoin_OnBeaconLost(LocalConnectResult *result)
{
    (void) result;
}
CLEAN_AS(func_ov066_02268e9c, LocalJoin_OnBeaconLost)

/* func_ov066_02268ea0: connected: the state LOCAL_STATE_MP_STARTING with the AID the parent
 * gave, and the MP communication started. */
void LocalJoin_OnConnected(LocalConnectResult *result)
{
    data_ov066_0226bdec->state = LOCAL_STATE_MP_STARTING;
    data_ov066_0226bdf4->aid = result->aid;
    LocalMp_Start();
}
CLEAN_AS(func_ov066_02268ea0, LocalJoin_OnConnected)

/* func_ov066_022696b4: with the radio idle, a connection to `parent` (LOCAL_STATE_CONNECTING),
 * retried after a failure when `retry`'s low bit is set; nothing in another state or for
 * NULL. */
void LocalJoin_Start(LocalParent *parent, int retry)
{
    if (data_ov066_0226bdec->state != LOCAL_STATE_WM_IDLE) {
        return;
    }
    if (parent == NULL) {
        return;
    }
    data_ov066_0226bdec->state = LOCAL_STATE_CONNECTING;
    data_ov066_0226bdf4->flags =
        (data_ov066_0226bdf4->flags & ~LOCAL_SESSION_RETRY_CONNECT) | (((u32) retry & 1) ? LOCAL_SESSION_RETRY_CONNECT : 0);
    LocalJoin_Connect(&parent->bss);
}
CLEAN_AS(func_ov066_022696b4, LocalJoin_Start)

/* func_ov066_02269728: a connection to the parent chosen (LocalJoin_Select), not retried. */
void LocalJoin_ConnectChosen(void)
{
    LocalJoin_Start(data_ov066_0226bdf4->chosen_parent, FALSE);
}
CLEAN_AS(func_ov066_02269728, LocalJoin_ConnectChosen)
