/* The local wireless library's control: its set-up and shutdown, the requests and the steps
 * that carry them out, WM's reset and power calls, and the events (local_wireless.h). */
#include "local_wireless.h"

#include <assert.h>
#include <stddef.h>
#include <stdint.h>

#include "clean.h"
#include "local_host.h"
#include "local_join.h"
#include "local_mp.h"
#include "local_search.h"

static_assert(offsetof(LocalControl, channel_count) == 0x09, "channel count");
static_assert(offsetof(LocalControl, wm_dma) == 0x0d, "WM_Init's DMA channel");
static_assert(offsetof(LocalControl, channels) == 0x10, "channel table");
static_assert(offsetof(LocalControl, reset_retries) == 0x15, "reset retries");
static_assert(offsetof(LocalControl, reset_requested) == 0x16, "reset requested");
static_assert(offsetof(LocalControl, scan_time) == 0x22, "scan time");
static_assert(offsetof(LocalControl, ggid) == 0x28, "ggid");
static_assert(offsetof(LocalControl, on_done) == 0x30, "done handler");
static_assert(offsetof(LocalControl, on_event) == 0x38, "event handler");
static_assert(offsetof(LocalControl, flags) == 0x3c, "flags");
static_assert(sizeof(LocalControl) == 0x40, "the size LocalWireless_Init allocates");
static_assert(offsetof(LocalSession, channel) == 0x8e, "session channel");
static_assert(offsetof(LocalSession, channel_index) == 0x95, "session channel index");
static_assert(offsetof(LocalSession, on_received) == 0xb8, "receive handler");
static_assert(offsetof(LocalSession, flags) == 0xc0, "session flags");

/* The control block, NULL before LocalWireless_Init and after LocalWireless_Shutdown. */
extern LocalControl *data_ov066_0226bdec;
/* The session. */
extern LocalSession *data_ov066_0226bdf4;
/* The game's allocator, free function and error handler (LocalWireless_Init). */
extern LocalAllocator *data_ov066_0226bde8;
extern LocalFree *data_ov066_0226bde4;
extern LocalErrorHandler *data_ov066_0226bde0;
/* WM_Enable, WM_Disable, WM_PowerOn and WM_PowerOff, by LocalWireless_CallWm's index. */
extern int (*data_ov066_0226bdc0[4])(void (*callback)(void *));

/* The game's symbols of the WM callbacks below, handed to WM. */
extern void func_ov066_0226696c(void *result);
extern void func_ov066_02266b94(void *result);

extern int WM_Reset(void (*callback)(void *));
extern int WM_GetLinkLevel(void);
extern int WM_IsExistAllowedChannel(void);
extern void OS_InitTick(void);
extern void OS_InitAlarm(void);
extern u32 OS_DisableInterrupts(void);
extern u32 OS_RestoreInterrupts(u32 state);

/* The steps of the other parts of the library. */
extern void func_ov066_02269a14(void); /* sets up the session once the radio is on */

/* func_ov066_022667e0: `handler` set as the event handler; FALSE without a control block. */
int LocalWireless_SetEventHandler(LocalEventHandler *handler)
{
    if (data_ov066_0226bdec == NULL) {
        return FALSE;
    }
    data_ov066_0226bdec->on_event = handler;
    return TRUE;
}
CLEAN_AS(func_ov066_022667e0, LocalWireless_SetEventHandler)

/* func_ov066_02266800: the event `kind` (LocalEventKind) of `aid` handed to the handler. */
void LocalWireless_PostEvent(u8 kind, u8 aid)
{
    u8 event[2];
    event[0] = kind;
    event[1] = aid;
    LocalWireless_DispatchEvent(event);
}
CLEAN_AS(func_ov066_02266800, LocalWireless_PostEvent)

/* func_ov066_02266824: `event` handed to the event handler, if there is one. */
void LocalWireless_DispatchEvent(u8 *event)
{
    LocalControl *control = data_ov066_0226bdec;
    if (control == NULL || control->on_event == NULL) {
        return;
    }
    control->on_event(event);
}
CLEAN_AS(func_ov066_02266824, LocalWireless_DispatchEvent)

/* func_ov066_0226686c: the library stopped on the error `code`: the state holds it, the request
 * is no longer carried out, and the game's error handler is told. */
void LocalWireless_Fail(int code)
{
    data_ov066_0226bdec->state = (u32) (code | LOCAL_STATE_ERROR);
    data_ov066_0226bdec->flags &= ~LOCAL_FLAG_BUSY;
    if (data_ov066_0226bde0 != NULL) {
        data_ov066_0226bde0(code);
    }
}
CLEAN_AS(func_ov066_0226686c, LocalWireless_Fail)

/* func_ov066_022668c4: `block` handed to the game's free function (nothing for NULL). */
void LocalWireless_Free(void *block)
{
    if (data_ov066_0226bde4 == NULL || block == NULL) {
        return;
    }
    data_ov066_0226bde4(block);
}
CLEAN_AS(func_ov066_022668c4, LocalWireless_Free)

/* func_ov066_02266908: `size` bytes aligned to `align` from the game's allocator; NULL, and the
 * library stopped on LOCAL_ERROR_NO_MEMORY, when it gives nothing.
 * BUG: LocalWireless_Fail writes to the control block, which LocalWireless_Init's own
 * allocation does not have yet (see there). */
void *LocalWireless_Alloc(int size, int align)
{
    if (data_ov066_0226bde8 != NULL) {
        void *block = data_ov066_0226bde8(size, align);
        if (block != NULL) {
            return block;
        }
    }
    LocalWireless_Fail(LOCAL_ERROR_NO_MEMORY);
    return NULL;
}
CLEAN_AS(func_ov066_02266908, LocalWireless_Alloc)

/* func_ov066_02266950: the reset is over. */
void LocalWireless_ClearResetting(void)
{
    data_ov066_0226bdec->flags &= ~LOCAL_FLAG_RESETTING;
}
CLEAN_AS(func_ov066_02266950, LocalWireless_ClearResetting)

/* func_ov066_0226696c: WM_Reset's callback. On success the radio is idle and the request goes
 * on; on failure WM_Reset is tried again, up to LOCAL_RESET_RETRIES times in a row before the
 * library stops on WM's error. */
void LocalWireless_OnReset(LocalWmResult *result)
{
    data_ov066_0226bdec->reset_requested = 0;
    LocalWireless_ClearResetting();
    if (result->result == LOCAL_WM_RESULT_SUCCESS) {
        data_ov066_0226bdec->reset_retries = 0;
        data_ov066_0226bdec->state = LOCAL_STATE_WM_IDLE;
        LocalWireless_Continue();
        return;
    }
    data_ov066_0226bdec->reset_retries++;
    if (data_ov066_0226bdec->reset_retries > LOCAL_RESET_RETRIES) {
        LocalWireless_Fail(result->result);
    } else {
        LocalWireless_StartReset(func_ov066_0226696c);
    }
}
CLEAN_AS(func_ov066_0226696c, LocalWireless_OnReset)

/* func_ov066_02266a08: WM_Reset with `callback` (the game's symbol); a reset is then under way
 * even when WM refused it, and the library stops on WM's error unless it is OPERATING. */
void LocalWireless_StartReset(void (*callback)(void *))
{
    int status = WM_Reset(callback);
    data_ov066_0226bdec->flags |= LOCAL_FLAG_RESETTING;
    if (status == LOCAL_WM_RESULT_OPERATING) {
        return;
    }
    LocalWireless_Fail(status);
}
CLEAN_AS(func_ov066_02266a08, LocalWireless_StartReset)

/* func_ov066_02266a4c: WM_PowerOff's callback: the radio is off. */
void LocalWireless_OnPowerOff(LocalWmResult *result)
{
    if (result->result == LOCAL_WM_RESULT_SUCCESS) {
        data_ov066_0226bdec->state = LOCAL_STATE_WM_STOP;
        return;
    }
    LocalWireless_Fail(result->result);
}
CLEAN_AS(func_ov066_02266a4c, LocalWireless_OnPowerOff)

/* func_ov066_02266a8c: WM_PowerOn's callback: the radio is on and the session is set up. */
void LocalWireless_OnPowerOn(LocalWmResult *result)
{
    if (result->result == LOCAL_WM_RESULT_SUCCESS) {
        data_ov066_0226bdec->state = LOCAL_STATE_WM_IDLE;
        func_ov066_02269a14();
    } else {
        LocalWireless_Fail(result->result);
    }
}
CLEAN_AS(func_ov066_02266a8c, LocalWireless_OnPowerOn)

/* func_ov066_02266ad4: WM_Disable's callback. */
void LocalWireless_OnDisable(LocalWmResult *result)
{
    if (result->result == LOCAL_WM_RESULT_SUCCESS) {
        data_ov066_0226bdec->state = LOCAL_STATE_WM_READY;
        return;
    }
    LocalWireless_Fail(result->result);
}
CLEAN_AS(func_ov066_02266ad4, LocalWireless_OnDisable)

/* func_ov066_02266b14: WM_Enable's callback. */
void LocalWireless_OnEnable(LocalWmResult *result)
{
    if (result->result == LOCAL_WM_RESULT_SUCCESS) {
        data_ov066_0226bdec->state = LOCAL_STATE_WM_STOP;
        return;
    }
    LocalWireless_Fail(result->result);
}
CLEAN_AS(func_ov066_02266b14, LocalWireless_OnEnable)

/* func_ov066_02266b54: WM_Enable, WM_Disable, WM_PowerOn or WM_PowerOff (`index` 0 to 3 in
 * the table) with LocalWireless_OnWmCall as the callback. REQUIRES: index is 0 to 3. */
void LocalWireless_CallWm(int index)
{
    int status = data_ov066_0226bdc0[index](func_ov066_02266b94);
    if (status == LOCAL_WM_RESULT_OPERATING) {
        return;
    }
    LocalWireless_Fail(status);
}
CLEAN_AS(func_ov066_02266b54, LocalWireless_CallWm)

/* func_ov066_02266b94: the callback of LocalWireless_CallWm's calls: the one of the call, then
 * the request goes on.
 * QUIRK: it goes on after an error too; with the error in the state, LocalWireless_Step then
 * resets WM (LocalWireless_StepReset) when the radio was on. */
void LocalWireless_OnWmCall(void *result)
{
    LocalWmResult *wm = result;
    switch (wm->api) {
        case LOCAL_WM_API_ENABLE:
            LocalWireless_OnEnable(wm);
            break;
        case LOCAL_WM_API_DISABLE:
            LocalWireless_OnDisable(wm);
            break;
        case LOCAL_WM_API_POWER_ON:
            LocalWireless_OnPowerOn(wm);
            break;
        case LOCAL_WM_API_POWER_OFF:
            LocalWireless_OnPowerOff(wm);
            break;
    }
    LocalWireless_Continue();
}
CLEAN_AS(func_ov066_02266b94, LocalWireless_OnWmCall)

/* func_ov066_02266bf4: the request goes on. Once its target is reached it is no longer carried
 * out, its done handler is called (and forgotten) and the request becomes LOCAL_REQUEST_NONE;
 * the handler may shut the library down, so the control block is looked up again after it.
 * Otherwise the next step is taken. */
void LocalWireless_Continue(void)
{
    if (!LocalWireless_IsRequestDone()) {
        LocalWireless_Step();
        return;
    }
    data_ov066_0226bdec->flags &= ~LOCAL_FLAG_BUSY;
    if (data_ov066_0226bdec->on_done != NULL) {
        data_ov066_0226bdec->on_done(data_ov066_0226bdec->on_done_argument);
        if (data_ov066_0226bdec != NULL) {
            data_ov066_0226bdec->on_done = NULL;
        }
    }
    if (data_ov066_0226bdec != NULL) {
        data_ov066_0226bdec->request = LOCAL_REQUEST_NONE;
    }
}
CLEAN_AS(func_ov066_02266bf4, LocalWireless_Continue)

/* func_ov066_02266ce8: the link level while communicating: WM_GetLinkLevel's 0 to 3; 4 while
 * measuring, starting or connecting (states 5 to 9), 5 otherwise (and for a level WM_GetLinkLevel
 * does not give). */
int LocalWireless_GetLinkLevel(void)
{
    switch (data_ov066_0226bdec->state) {
        case LOCAL_STATE_PARENT:
        case LOCAL_STATE_CHILD: {
            int level = WM_GetLinkLevel();
            if (level >= 0 && level <= 3) {
                return level;
            }
            break;
        }
        case LOCAL_STATE_MEASURING:
        case LOCAL_STATE_PARENT_STARTING:
        case LOCAL_STATE_SEARCHING:
        case LOCAL_STATE_CONNECTING:
        case LOCAL_STATE_MP_STARTING:
            return 4;
    }
    return 5;
}
CLEAN_AS(func_ov066_02266ce8, LocalWireless_GetLinkLevel)

/* func_ov066_02266dbc: WM reset (LocalWireless_OnReset follows) unless the radio is not on yet
 * (states 0 to 3). */
void LocalWireless_ResetIfPowered(void)
{
    u32 state = data_ov066_0226bdec->state;
    if (state <= LOCAL_STATE_WM_STOP) {
        return;
    }
    LocalWireless_StartReset(func_ov066_0226696c);
}
CLEAN_AS(func_ov066_02266dbc, LocalWireless_ResetIfPowered)

/* func_ov066_02266e08: TRUE when a WM callback is to be ignored: a reset is under way, or one
 * was asked for (and is started here). */
int LocalWireless_CheckReset(void)
{
    LocalControl *control = data_ov066_0226bdec;
    if (control->flags & LOCAL_FLAG_RESETTING) {
        return TRUE;
    }
    if (control->reset_requested == 1) {
        LocalWireless_ResetIfPowered();
        return TRUE;
    }
    return FALSE;
}
CLEAN_AS(func_ov066_02266e08, LocalWireless_CheckReset)

/* func_ov066_02266e64: the step back to an idle radio: a WM reset. */
void LocalWireless_StepReset(void)
{
    LocalWireless_ResetIfPowered();
}
CLEAN_AS(func_ov066_02266e64, LocalWireless_StepReset)

/* func_ov066_02266e70: the next step towards the request, by the state. A request that needs
 * WM initialised fails in states 0 and 1; in state 9, and after an error, WM is reset. */
void LocalWireless_Step(void)
{
    switch (data_ov066_0226bdec->state) {
        case LOCAL_STATE_WM_READY:
            LocalWireless_StepReady();
            break;
        case LOCAL_STATE_WM_STOP:
            LocalWireless_StepStop();
            break;
        case LOCAL_STATE_WM_IDLE:
            LocalWireless_StepIdle();
            break;
        case LOCAL_STATE_PARENT_STARTING:
            LocalWireless_StepParentStarting();
            break;
        case LOCAL_STATE_SEARCHING:
            LocalWireless_StepSearching();
            break;
        case LOCAL_STATE_CONNECTING:
            LocalWireless_StepConnecting();
            break;
        case LOCAL_STATE_MEASURING:
            LocalWireless_StepMeasuring();
            break;
        case LOCAL_STATE_PARENT:
            LocalWireless_StepParent();
            break;
        case LOCAL_STATE_CHILD:
            LocalWireless_StepChild();
            break;
        case LOCAL_STATE_NONE:
        case LOCAL_STATE_SET_UP:
            LocalWireless_Fail(LOCAL_ERROR_WRONG_STATE);
            break;
        default:
            LocalWireless_StepReset();
            break;
    }
}
CLEAN_AS(func_ov066_02266e70, LocalWireless_Step)

/* func_ov066_02266f78: as a child: back to an idle radio, or for a parent the communication
 * ended first. */
void LocalWireless_StepChild(void)
{
    switch (data_ov066_0226bdec->request) {
        case LOCAL_REQUEST_WM_READY:
        case LOCAL_REQUEST_WM_STOP:
        case LOCAL_REQUEST_WM_IDLE:
        case LOCAL_REQUEST_SEARCH:
        case LOCAL_REQUEST_CONNECTED:
            LocalWireless_StepReset();
            break;
        case LOCAL_REQUEST_PARENT:
            LocalMp_AskEnd();
            break;
    }
}
CLEAN_AS(func_ov066_02266f78, LocalWireless_StepChild)

/* func_ov066_02266fd8: as a parent: back to an idle radio, or for a child the communication
 * ended first. */
void LocalWireless_StepParent(void)
{
    switch (data_ov066_0226bdec->request) {
        case LOCAL_REQUEST_WM_READY:
        case LOCAL_REQUEST_WM_STOP:
        case LOCAL_REQUEST_WM_IDLE:
        case LOCAL_REQUEST_SEARCH:
        case LOCAL_REQUEST_CONNECTED:
            LocalWireless_StepReset();
            break;
        case LOCAL_REQUEST_CHILD:
            LocalMp_AskEnd();
            break;
    }
}
CLEAN_AS(func_ov066_02266fd8, LocalWireless_StepParent)

/* func_ov066_02267038: while measuring: back to an idle radio for the requests below it. */
void LocalWireless_StepMeasuring(void)
{
    switch (data_ov066_0226bdec->request) {
        case LOCAL_REQUEST_WM_READY:
        case LOCAL_REQUEST_WM_STOP:
        case LOCAL_REQUEST_WM_IDLE:
            LocalWireless_StepReset();
            break;
    }
}
CLEAN_AS(func_ov066_02267038, LocalWireless_StepMeasuring)

/* func_ov066_02267088: while connecting: back to an idle radio unless a child is asked for. */
void LocalWireless_StepConnecting(void)
{
    switch (data_ov066_0226bdec->request) {
        case LOCAL_REQUEST_WM_READY:
        case LOCAL_REQUEST_WM_STOP:
        case LOCAL_REQUEST_WM_IDLE:
        case LOCAL_REQUEST_PARENT:
        case LOCAL_REQUEST_SEARCH:
        case LOCAL_REQUEST_CONNECTED:
            LocalWireless_StepReset();
            break;
    }
}
CLEAN_AS(func_ov066_02267088, LocalWireless_StepConnecting)

/* func_ov066_022670d8: while searching: for a child the search stops; back to an idle radio
 * unless the search itself is asked for. */
void LocalWireless_StepSearching(void)
{
    switch (data_ov066_0226bdec->request) {
        case LOCAL_REQUEST_WM_READY:
        case LOCAL_REQUEST_WM_STOP:
        case LOCAL_REQUEST_WM_IDLE:
        case LOCAL_REQUEST_PARENT:
        case LOCAL_REQUEST_CONNECTED:
            LocalWireless_StepReset();
            break;
        case LOCAL_REQUEST_CHILD:
            LocalSearch_Stop();
            break;
    }
}
CLEAN_AS(func_ov066_022670d8, LocalWireless_StepSearching)

/* func_ov066_02267138: while a parent starts: back to an idle radio unless a parent is asked
 * for. */
void LocalWireless_StepParentStarting(void)
{
    switch (data_ov066_0226bdec->request) {
        case LOCAL_REQUEST_WM_READY:
        case LOCAL_REQUEST_WM_STOP:
        case LOCAL_REQUEST_WM_IDLE:
        case LOCAL_REQUEST_SEARCH:
        case LOCAL_REQUEST_CHILD:
        case LOCAL_REQUEST_CONNECTED:
            LocalWireless_StepReset();
            break;
    }
}
CLEAN_AS(func_ov066_02267138, LocalWireless_StepParentStarting)

/* func_ov066_02267188: with the radio idle: power it off, or start what is asked for. */
void LocalWireless_StepIdle(void)
{
    switch (data_ov066_0226bdec->request) {
        case LOCAL_REQUEST_WM_READY:
        case LOCAL_REQUEST_WM_STOP:
            LocalWireless_CallWm(3); /* WM_PowerOff */
            break;
        case LOCAL_REQUEST_PARENT:
            LocalHost_Start(LOCAL_GAME_BD8A);
            break;
        case LOCAL_REQUEST_SEARCH:
            LocalSearch_Begin();
            break;
        case LOCAL_REQUEST_CHILD:
            LocalJoin_ConnectChosen();
            break;
        case LOCAL_REQUEST_CONNECTED:
            LocalJoin_StepAuto();
            break;
    }
}
CLEAN_AS(func_ov066_02267188, LocalWireless_StepIdle)

/* func_ov066_02267224: WM enabled, the radio off: disable WM for LOCAL_REQUEST_WM_READY,
 * power the radio on for anything past LOCAL_REQUEST_WM_STOP. */
void LocalWireless_StepStop(void)
{
    int request = (int) data_ov066_0226bdec->request;
    if (request < LOCAL_REQUEST_WM_STOP) {
        LocalWireless_CallWm(1); /* WM_Disable */
    } else if (request > LOCAL_REQUEST_WM_STOP) {
        LocalWireless_CallWm(2); /* WM_PowerOn */
    }
}
CLEAN_AS(func_ov066_02267224, LocalWireless_StepStop)

/* func_ov066_0226727c: WM ready: enable it for anything past LOCAL_REQUEST_WM_READY. */
void LocalWireless_StepReady(void)
{
    int request = (int) data_ov066_0226bdec->request;
    if (request <= LOCAL_REQUEST_WM_READY) {
        return;
    }
    LocalWireless_CallWm(0); /* WM_Enable */
}
CLEAN_AS(func_ov066_0226727c, LocalWireless_StepReady)

/* func_ov066_022672b8: `request` (LocalRequest) asked for, with `on_done` called with
 * `argument` once it is reached; the first step is taken now unless a request is already
 * being carried out (that one then goes on towards the new target). FALSE without a control
 * block, for a request past the last or for the one already asked for.
 * QUIRK: compared signed, so a negative request is taken. */
int LocalWireless_Request(int request, LocalDoneHandler *on_done, void *argument)
{
    if (data_ov066_0226bdec == NULL) {
        return FALSE;
    }
    if (request >= LOCAL_REQUEST_COUNT || (u32) request == data_ov066_0226bdec->request) {
        return FALSE;
    }
    data_ov066_0226bdec->request = (u32) request;
    data_ov066_0226bdec->on_done = on_done;
    data_ov066_0226bdec->on_done_argument = argument;
    if ((data_ov066_0226bdec->flags & LOCAL_FLAG_BUSY) == 0) {
        data_ov066_0226bdec->flags |= LOCAL_FLAG_BUSY;
        LocalWireless_Step();
    }
    return TRUE;
}
CLEAN_AS(func_ov066_022672b8, LocalWireless_Request)

/* func_ov066_02267348: TRUE when the state is the request's target. */
int LocalWireless_IsRequestDone(void)
{
    LocalControl *control = data_ov066_0226bdec;
    u32 state = control->state;
    switch (control->request) {
        case LOCAL_REQUEST_WM_READY:
            return state == LOCAL_STATE_WM_READY;
        case LOCAL_REQUEST_WM_STOP:
            return state == LOCAL_STATE_WM_STOP;
        case LOCAL_REQUEST_WM_IDLE:
            return state == LOCAL_STATE_WM_IDLE;
        case LOCAL_REQUEST_PARENT:
            return state == LOCAL_STATE_PARENT;
        case LOCAL_REQUEST_SEARCH:
            return state == LOCAL_STATE_SEARCHING;
        case LOCAL_REQUEST_CHILD:
            return state == LOCAL_STATE_CHILD;
        case LOCAL_REQUEST_CONNECTED:
            return state == LOCAL_STATE_PARENT || state == LOCAL_STATE_CHILD;
    }
    return FALSE;
}
CLEAN_AS(func_ov066_02267348, LocalWireless_IsRequestDone)

/* func_ov066_02267404: the control block freed and the game's functions forgotten, once WM is
 * finished (state LOCAL_STATE_SET_UP); otherwise the library stops on
 * LOCAL_ERROR_WRONG_STATE. TRUE when shut down. */
int LocalWireless_Shutdown(void)
{
    if (data_ov066_0226bdec->state != LOCAL_STATE_SET_UP) {
        LocalWireless_Fail(LOCAL_ERROR_WRONG_STATE);
        return FALSE;
    }
    data_ov066_0226bdec->state = LOCAL_STATE_NONE;
    LocalWireless_Free(data_ov066_0226bdec);
    data_ov066_0226bde8 = NULL;
    data_ov066_0226bde4 = NULL;
    data_ov066_0226bde0 = NULL;
    data_ov066_0226bdec = NULL;
    return TRUE;
}
CLEAN_AS(func_ov066_02267404, LocalWireless_Shutdown)

/* func_ov066_0226748c: the library set up with the game's allocator, free function and error
 * handler, and the DMA channel WM is to use: the control block allocated, the tick and alarm
 * systems started, and the control block reset. FALSE when it was set up already, when the
 * allocation failed, or when no channel is allowed (then the library stops on
 * LOCAL_ERROR_NO_CHANNEL and the control block is freed).
 * BUG: when the allocation fails, LocalWireless_Alloc's LocalWireless_Fail writes through the
 * control block pointer, which is NULL then (the ROM writes to addresses 4 and 0x3c).
 * REQUIRES: the allocator gives the control block.
 * BUG: when no channel is allowed, the freed control block stays in data_ov066_0226bdec, so
 * every later call takes the library as set up. */
int LocalWireless_Init(int wm_dma, LocalAllocator *alloc, LocalFree *release, LocalErrorHandler *on_error)
{
    if (data_ov066_0226bdec != NULL) {
        return FALSE;
    }
    data_ov066_0226bde8 = alloc;
    data_ov066_0226bde4 = release;
    data_ov066_0226bde0 = on_error;
    data_ov066_0226bdec = LocalWireless_Alloc(sizeof(LocalControl), 4);
    if (data_ov066_0226bdec == NULL) {
        return FALSE;
    }
    OS_InitTick();
    OS_InitAlarm();
    if (WM_IsExistAllowedChannel()) {
        LocalWireless_ResetControl((u8) wm_dma);
        return TRUE;
    }
    LocalWireless_Fail(LOCAL_ERROR_NO_CHANNEL);
    LocalWireless_Free(data_ov066_0226bdec);
#ifdef BUGFIX
    data_ov066_0226bdec = NULL;
#endif
    return FALSE;
}
CLEAN_AS(func_ov066_0226748c, LocalWireless_Init)

/* func_ov066_02267530: the control block at its start: no request, set up, one channel, WM to
 * use DMA channel `wm_dma`, no handlers and no flags of a request or a reset. The fields not
 * written keep their values. */
void LocalWireless_ResetControl(u8 wm_dma)
{
    LocalControl *control = data_ov066_0226bdec;
    control->request = LOCAL_REQUEST_NONE;
    control->state = LOCAL_STATE_SET_UP;
    control->parent_channel = LOCAL_CHANNEL_MEASURE_ONCE;
    control->channel_count = 1;
    control->max_children = 0;
    control->max_players = 0;
    control->parents_per_list = 0;
    control->wm_dma = wm_dma;
    control->channels = NULL;
    control->reset_retries = 0;
    control->reset_requested = 0;
    control->on_done = NULL;
    control->on_done_argument = NULL;
    control->on_event = NULL;
    control->flags &= ~(LOCAL_FLAG_BUSY | LOCAL_FLAG_RESETTING | LOCAL_FLAG_1000);
}
CLEAN_AS(func_ov066_02267530, LocalWireless_ResetControl)

/* func_ov066_0226760c: the state (LocalState, or an error | LOCAL_STATE_ERROR), read with the
 * interrupts disabled; 0 without a control block. */
int LocalWireless_GetState(void)
{
    int state = 0;
    u32 interrupts = OS_DisableInterrupts();
    if (data_ov066_0226bdec != NULL) {
        state = (int) data_ov066_0226bdec->state;
    }
    OS_RestoreInterrupts(interrupts);
    return state;
}
CLEAN_AS(func_ov066_0226760c, LocalWireless_GetState)

/* func_ov066_02267fe8: `handler` set as the handler of the data received, with the interrupts
 * disabled; nothing without a session. */
void LocalWireless_SetReceiveHandler(LocalReceiveHandler *handler)
{
    if (data_ov066_0226bdf4 == NULL) {
        return;
    }
    u32 interrupts = OS_DisableInterrupts();
    data_ov066_0226bdf4->on_received = handler;
    OS_RestoreInterrupts(interrupts);
}
CLEAN_AS(func_ov066_02267fe8, LocalWireless_SetReceiveHandler)

/* func_ov066_02268024: TRUE when the 6-byte MAC address `mac` is not all zero (a peer's slot
 * in use). */
int LocalWireless_IsMacSet(const u8 *mac)
{
    for (int i = 0; i < 6; i++) {
        if (mac[i] != 0) {
            return TRUE;
        }
    }
    return FALSE;
}
CLEAN_AS(func_ov066_02268024, LocalWireless_IsMacSet)
