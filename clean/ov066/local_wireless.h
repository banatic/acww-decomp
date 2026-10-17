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
    u32 request; /* LocalRequest */
    u32 state;   /* LocalState, or an error code | LOCAL_STATE_ERROR */
    /* the channel a parent uses, or LOCAL_CHANNEL_MEASURE_ONCE / _ALWAYS (0xfe on reset) */
    u8 parent_channel;
    u8 channel_count;    /* the channels searched, one parent list each */
    u8 max_children;     /* the children a parent takes (WMParentParam.maxEntry) */
    u8 max_players;      /* the players, the parent included: its entry closes at this count */
    u8 parents_per_list; /* the parents each list holds */
    u8 wm_dma;           /* the DMA channel handed to WM_Init */
    u8 unk_0e[2];
    const u8 *channels;  /* the channel of each search index; NULL for every allowed one */
    u8 beacons_per_turn; /* the beacons a starting parent sends before the request goes on */
    u8 reset_retries;    /* WM_Reset failures in a row */
    u8 reset_requested;  /* 1: a WM reset is due (LocalWireless_CheckReset) */
    u8 mp_frequency;     /* WM_StartMPEx's mpFreq */
    u16 unk_18;          /* sizes the parent's MP receive buffer */
    u16 parent_max_size; /* WMParentParam.parentMaxSize */
    u16 unk_1c;          /* sizes the child's MP receive buffer */
    u16 child_max_size;  /* WMParentParam.childMaxSize */
    u16 search_time;     /* the milliseconds each search of the automatic pairing lasts */
    u16 scan_time;       /* the time spent on each channel (WMScanParam.maxChannelTime) */
    u8 unk_24[4];
    u32 ggid; /* the parents' game group id (LOCAL_FLAG_MATCH_GGID) */
    u8 unk_2c[4];
    LocalDoneHandler *on_done; /* called once the request is reached */
    void *on_done_argument;
    LocalEventHandler *on_event;
    u32 flags; /* LOCAL_FLAG_ */
} LocalControl;

/* The session (data_ov066_0226bdf4, 0xc4 bytes): WM's buffers, the players and the handlers of
 * the communication layer above the library (set up outside this code). */
typedef struct LocalSession {
    struct LocalParentParam *parent_param; /* WM_SetParentParameter's (local_host.h) */
    void *wm_work;                         /* WM_Init's work buffer */
    u8 *game_info;                         /* the beacon's user game info: a LocalGameHeader, then the data */
    void *mp_receive_buffer;               /* WM_StartMPEx's */
    void *mp_send_buffer;                  /* WM_StartMPEx's */
    void *message_buffer;                  /* the library's own messages (LocalMessage, local_mp.h) */
    u16 game_info_length;                  /* the bytes of game_info in the beacon */
    u16 mp_receive_size;                   /* of mp_receive_buffer */
    u16 mp_send_size;                      /* of mp_send_buffer */
    u16 aid;                               /* 0 for the parent, a child's own; 0xffff before a connection */
    u16 tgid;                              /* WMParentParam.tgid, random for each parent started */
    u8 mac[6];                             /* this DS's MAC address */
    u8 members[16][6];                     /* by AID, the players' MAC addresses; all zero for a free AID */
    struct LocalParent *chosen_parent;     /* the parent a child connects to (local_search.h) */
    u8 player_count;                       /* the members set, the parent included */
    u8 parent_channel;                     /* the channel a parent uses (WMParentParam.channel) */
    u8 channel;                            /* the channel being searched */
    u8 unk_8f;
    u16 allowed_channels; /* WM_GetAllowedChannel's bits */
    u8 allowed_channel_count;
    u8 search_turn;   /* the turn of four in which the automatic pairing searches */
    u8 turn;          /* the turn of the automatic pairing, 0 to 3 */
    u8 channel_index; /* the channel's index in the search (LocalControl.channels) */
    u8 beacons_sent;  /* by a starting parent */
    u8 unk_97;
    u16 greeted; /* by AID: the children whose hello the parent received */
    u8 unk_9a[2];
    u32 (*on_mp_start)(void); /* called when the MP communication starts or ends */
    void (*on_mp_end)(void);  /* on WM's MP end indication */
    void (*on_mp_ack)(void);  /* on WM's MP acknowledgement indication */
    void (*unk_a8)(void);
    /* sends one of the library's messages to the AIDs of `to` (a bitmap); `on_sent` follows */
    void (*send_message)(void *buffer, u32 size, u32 to, void (*on_sent)(void *));
    int (*send)(const void *buffer, u32 size, int to, void (*on_sent)(void *)); /* the game's data */
    int (*can_send)(void);
    LocalReceiveHandler *on_received;
    void (*on_peer_left)(int aid); /* told of a child gone while others remain */
    u32 flags;                     /* LOCAL_SESSION_ */
} LocalSession;

#define LOCAL_SESSION_SEND_BUSY 0x1        /* a member table is being sent */
#define LOCAL_SESSION_SEND_AGAIN 0x2       /* and it is to be sent again once it is */
#define LOCAL_SESSION_END_MP 0x4           /* the MP communication is to end (LocalMp_AskEnd) */
#define LOCAL_SESSION_ENDING_MP 0x8        /* WM_EndMP was called */
#define LOCAL_SESSION_GAME_INFO_DUE 0x10   /* the beacon's game info is to be set again */
#define LOCAL_SESSION_START_MP 0x20        /* the MP communication starts once the game info is set */
#define LOCAL_SESSION_RETRY_CONNECT 0x40   /* a failed connection resets WM and searches again */
#define LOCAL_SESSION_MEASURE_FIRST 0x80   /* the channels are measured before a parent starts */
#define LOCAL_SESSION_SEARCH_STOPPED 0x100 /* set by LocalSearch_StopNow */
#define LOCAL_SESSION_PARENT_CHOSEN 0x200  /* set by LocalJoin_Select */

/* LocalControl.parent_channel: no channel, the parent measures them first; once (0xfe) or
 * before every start (0xff). */
#define LOCAL_CHANNEL_MEASURE_ONCE 0xfe
#define LOCAL_CHANNEL_MEASURE_ALWAYS 0xff

/* More LocalControl.flags: WM_StartMPEx's minPollBmpMode, singlePacketMode and
 * ignoreFatalError, and whether a child that loses its parent forgets the parent's member. */
#define LOCAL_FLAG_MIN_POLL_BMP 0x1
#define LOCAL_FLAG_SINGLE_PACKET 0x2
#define LOCAL_FLAG_IGNORE_FATAL 0x4
#define LOCAL_FLAG_FORGET_PARENT 0x100
#define LOCAL_FLAG_MP_STARTED LOCAL_FLAG_1000 /* set when the MP communication starts */

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
#define LOCAL_WM_RESULT_FAILED 1
#define LOCAL_WM_RESULT_TIMEOUT 9
#define LOCAL_WM_RESULT_INVALID_POLLBITMAP 13
#define LOCAL_WM_RESULT_SEND_FAILED 15

/* WM's state codes (WM_STATECODE_) in the callbacks of a parent, a connection and MP. */
#define LOCAL_WM_STATE_PARENT_START 0
#define LOCAL_WM_STATE_BEACON_SENT 2
#define LOCAL_WM_STATE_CONNECT_START 6
#define LOCAL_WM_STATE_CONNECTED 7
#define LOCAL_WM_STATE_BEACON_LOST 8
#define LOCAL_WM_STATE_DISCONNECTED 9
#define LOCAL_WM_STATE_MP_START 10
#define LOCAL_WM_STATE_MPEND_IND 11
#define LOCAL_WM_STATE_MP_IND 12
#define LOCAL_WM_STATE_MPACK_IND 13

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
