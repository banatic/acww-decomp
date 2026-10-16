/* The local wireless library of overlay 66: the game's layer over NitroSDK's WM library for
 * DS-to-DS play, loaded into the library slot (LibraryOverlay_Switch66) and driven by the game's
 * network layer (clean/autoload_2/network.c, the Local_ functions).
 *
 * The caller asks for a target (LocalWireless_Request, one of LocalRequest) and the library
 * walks the WM states towards it one asynchronous WM call at a time: each WM callback records
 * the state reached and calls LocalWireless_Continue, which either reports the target reached
 * or takes the next step (LocalWireless_Step). An error leaves its code in the state with
 * LOCAL_STATE_ERROR set. Its work memory comes from the allocator the game hands in
 * (LocalWireless_Init), and it reports peers joining and leaving through an event handler. */
#ifndef CLEAN_OV066_LOCAL_WIRELESS_H
#define CLEAN_OV066_LOCAL_WIRELESS_H

#include "types.h"

/* The library's states (LocalControl.state). The names of 2 to 4 are WM's states after the WM
 * call that reaches them; 5 to 11 from the code that sets them. */
enum LocalState {
    LOCAL_STATE_NONE = 0,            /* shut down (LocalWireless_Shutdown) */
    LOCAL_STATE_SET_UP = 1,          /* the control block is set up, WM not initialised */
    LOCAL_STATE_WM_READY = 2,        /* WM initialised and disabled (WM_Disable) */
    LOCAL_STATE_WM_STOP = 3,         /* WM enabled, its radio off (WM_Enable, WM_PowerOff) */
    LOCAL_STATE_WM_IDLE = 4,         /* the radio on (WM_PowerOn, WM_Reset, WM_EndScan) */
    LOCAL_STATE_MEASURING = 5,       /* measuring the channels before starting a parent */
    LOCAL_STATE_PARENT_STARTING = 6, /* starting as a parent */
    LOCAL_STATE_SEARCHING = 7,       /* a child scanning the channels for parents */
    LOCAL_STATE_CONNECTING = 8,      /* a child connecting to a parent */
    LOCAL_STATE_MP_STARTING = 9,     /* starting the MP communication */
    LOCAL_STATE_PARENT = 10,         /* a parent, communicating */
    LOCAL_STATE_CHILD = 11,          /* a child, communicating */
};
/* Set with an error code in the low bits (LocalWireless_Fail). */
#define LOCAL_STATE_ERROR 0x80

/* The targets a caller asks for (LocalControl.request) and the state that reaches each
 * (LocalWireless_IsRequestDone). */
enum LocalRequest {
    LOCAL_REQUEST_WM_READY = 0,  /* LOCAL_STATE_WM_READY */
    LOCAL_REQUEST_WM_STOP = 1,   /* LOCAL_STATE_WM_STOP */
    LOCAL_REQUEST_WM_IDLE = 2,   /* LOCAL_STATE_WM_IDLE */
    LOCAL_REQUEST_PARENT = 3,    /* LOCAL_STATE_PARENT */
    LOCAL_REQUEST_SEARCH = 4,    /* LOCAL_STATE_SEARCHING */
    LOCAL_REQUEST_CHILD = 5,     /* LOCAL_STATE_CHILD */
    LOCAL_REQUEST_CONNECTED = 6, /* LOCAL_STATE_PARENT or LOCAL_STATE_CHILD */
    LOCAL_REQUEST_NONE = 7,      /* the last target was reached */
};
#define LOCAL_REQUEST_COUNT 7

/* The error codes the library itself sets (the others are WM's result codes). */
#define LOCAL_ERROR_NO_CHANNEL 0x41  /* WM_IsExistAllowedChannel found none */
#define LOCAL_ERROR_NO_MEMORY 0x42   /* the allocator gave nothing */
#define LOCAL_ERROR_WRONG_STATE 0x44 /* asked for something the state does not allow */
#define LOCAL_RESET_RETRIES 16       /* WM_Reset is retried this many times */

/* LocalControl.flags */
#define LOCAL_FLAG_08                                                                                                         \
    0x8                                   /* a search starts with an empty parent list, and a
                                          * parent's game id 0xbd8a or 0x2348 ends it
                                          * (LocalSearch_Start, LocalSearch_OnParentFound) */
#define LOCAL_FLAG_SKIP_NO_GAME_INFO 0x10 /* a parent without game info is not listed */
#define LOCAL_FLAG_MATCH_GGID 0x20        /* only parents of LocalControl.ggid are listed */
#define LOCAL_FLAG_MATCH_CHANNEL                                                                                              \
    0x40                             /* only parents whose header names the channel
                                          * searched (LocalGameHeader.channel_index) */
#define LOCAL_FLAG_MATCH_KIND_5 0x80 /* only parents whose header's kind is 5 */
#define LOCAL_FLAG_RESETTING 0x400   /* a WM_Reset is under way */
#define LOCAL_FLAG_BUSY 0x800        /* a request is being carried out */
#define LOCAL_FLAG_1000 0x1000       /* cleared by LocalWireless_ResetControl */

/* The events handed to the event handler (LocalWireless_PostEvent): a kind and an AID. */
enum LocalEventKind {
    LOCAL_EVENT_CONNECTED = 0,
    LOCAL_EVENT_DISCONNECTED = 1,
    LOCAL_EVENT_ENDED = 2,
};

typedef void LocalDoneHandler(void *argument);
typedef void LocalEventHandler(u8 *event);
typedef void LocalErrorHandler(int code);
typedef void LocalReceiveHandler(int aid, char *data, unsigned int size);
typedef void *LocalAllocator(int size, int align);
typedef void LocalFree(void *block);

/* The control block (data_ov066_0226bdec), allocated by LocalWireless_Init. */
typedef struct LocalControl {
    u32 request;      /* LocalRequest */
    u32 state;        /* LocalState, or an error code | LOCAL_STATE_ERROR */
    u8 unk_08;        /* 0xfe on reset */
    u8 channel_count; /* the channels searched, one parent list each */
    u8 unk_0a;
    u8 unk_0b;
    u8 parents_per_list; /* the parents each list holds */
    u8 wm_dma;           /* the DMA channel handed to WM_Init */
    u8 unk_0e[2];
    const u8 *channels; /* the channel of each search index; NULL for every allowed one */
    u8 unk_14;
    u8 reset_retries;   /* WM_Reset failures in a row */
    u8 reset_requested; /* 1: a WM reset is due (LocalWireless_CheckReset) */
    u8 unk_17[0x0b];
    u16 scan_time; /* the time spent on each channel (WMScanParam.maxChannelTime) */
    u8 unk_24[4];
    u32 ggid; /* the parents' game group id (LOCAL_FLAG_MATCH_GGID) */
    u8 unk_2c[4];
    LocalDoneHandler *on_done; /* called once the request is reached */
    void *on_done_argument;
    LocalEventHandler *on_event;
    u32 flags; /* LOCAL_FLAG_ */
} LocalControl;

/* The session (data_ov066_0226bdf4): only the fields this code uses. */
typedef struct LocalSession {
    u8 unk_00[0x8e];
    u8 channel; /* the channel being searched */
    u8 unk_8f[6];
    u8 channel_index; /* its index in the search (LocalControl.channels) */
    u8 unk_96[0x22];
    LocalReceiveHandler *on_received;
    u8 unk_bc[4];
    u32 flags; /* LOCAL_SESSION_ */
} LocalSession;

#define LOCAL_SESSION_SEARCH_STOPPED 0x100 /* set by LocalSearch_StopNow */

/* What WM hands its callbacks first (WMCallback). */
typedef struct LocalWmResult {
    u16 api;    /* the WM_APIID_ of the call */
    u16 result; /* its WM_ERRCODE_ */
} LocalWmResult;

/* WM's API ids and result codes this code compares with. */
#define LOCAL_WM_API_ENABLE 3
#define LOCAL_WM_API_DISABLE 4
#define LOCAL_WM_API_POWER_ON 5
#define LOCAL_WM_API_POWER_OFF 6
#define LOCAL_WM_RESULT_SUCCESS 0
#define LOCAL_WM_RESULT_OPERATING 2

int LocalWireless_SetEventHandler(LocalEventHandler *handler);
void LocalWireless_PostEvent(u8 kind, u8 aid);
void LocalWireless_DispatchEvent(u8 *event);
void LocalWireless_Fail(int code);
void LocalWireless_Free(void *block);
void *LocalWireless_Alloc(int size, int align);
void LocalWireless_ClearResetting(void);
void LocalWireless_OnReset(LocalWmResult *result);
void LocalWireless_StartReset(void (*callback)(void *));
void LocalWireless_OnPowerOff(LocalWmResult *result);
void LocalWireless_OnPowerOn(LocalWmResult *result);
void LocalWireless_OnDisable(LocalWmResult *result);
void LocalWireless_OnEnable(LocalWmResult *result);
void LocalWireless_CallWm(int index);
void LocalWireless_OnWmCall(void *result);
void LocalWireless_Continue(void);
int LocalWireless_GetLinkLevel(void);
void LocalWireless_ResetIfPowered(void);
int LocalWireless_CheckReset(void);
void LocalWireless_StepReset(void);
void LocalWireless_Step(void);
void LocalWireless_StepChild(void);
void LocalWireless_StepParent(void);
void LocalWireless_StepMeasuring(void);
void LocalWireless_StepConnecting(void);
void LocalWireless_StepSearching(void);
void LocalWireless_StepParentStarting(void);
void LocalWireless_StepIdle(void);
void LocalWireless_StepStop(void);
void LocalWireless_StepReady(void);
int LocalWireless_Request(int request, LocalDoneHandler *on_done, void *argument);
int LocalWireless_IsRequestDone(void);
int LocalWireless_Shutdown(void);
int LocalWireless_Init(int wm_dma, LocalAllocator *alloc, LocalFree *release, LocalErrorHandler *on_error);
void LocalWireless_ResetControl(u8 wm_dma);
int LocalWireless_GetState(void);
void LocalWireless_SetReceiveHandler(LocalReceiveHandler *handler);
int LocalWireless_IsMacSet(const u8 *mac);

#endif
