/* The ARM7's wireless manager at the ARM9 WM library's level; see wm.h and
 * docs/multi-console.md.
 *
 * What the ARM9 sends and expects was read from its WM library in the ROM (autoload_2:
 * WMi_SendCommand 0x021205d0 sends the address of a 256-byte command buffer on tag 0xa, the
 * API id in its first halfword and the arguments as words from offset 4, or a request
 * structure copied from fifo9to7; WmReceiveFifo 0x02120100 takes the address of a callback
 * structure back, calls the API's callback, the indication callback or a port's, and marks a
 * command buffer free again by setting bit 15 of its first halfword). A callback for a command
 * is written into that command's buffer; a notification that belongs to no command goes
 * through the shared fifo7to9 buffer, one at a time: bit 0 of the shared wm_callback_control
 * (0x027fff96) is set while the ARM9 has not taken it (WmClearFifoRecvFlag clears it).
 *
 * The status the ARM9 reads (WMStatus, 0x7bc bytes at the address WM_Enable names) is written
 * where its fields are; the offsets below are those the ROM's code reads (WM_SetMPDataToPortEx:
 * mp_readyBitmap 0x86, child_bitmap 0x17e, aid 0x184, mp_maxSendSize 0x18e; WM_StartMPEx:
 * mp_flag 0xc, pwrMgtMode 0xc2; WmReceiveFifo: mp_recvBufSize 0x46).
 */
#include "wm.h"

#include <stdlib.h>
#include <string.h>

#include "input.h"
#include "io.h"
#include "memory.h"
#include "wifi.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

/* The shared area */
#define SHARED_WM_CALLBACK_CONTROL 0x027fff96u
#define SHARED_MAC_ADDRESS 0x027ffcf4u     /* after the user settings: the MAC address (OS_GetMacAddress) */
#define SHARED_ALLOWED_CHANNEL 0x027ffcfau /* WM_GetAllowedChannel; WM_IsExistAllowedChannel reads 0x027ffcf4 */

/* The channels local play uses (1, 7 and 13), as WM_GetAllowedChannel gives them: bit n-1. */
#define ALLOWED_CHANNELS 0x1041u
/* The firmware's enabled channels (1 to 13) */
#define ENABLED_CHANNELS 0x3ffeu

/* WMStatus fields (ARM offsets) */
#define ST_STATE 0x000
#define ST_BUSY_APIID 0x002
#define ST_API_BUSY 0x004
#define ST_SCAN_CONTINUE 0x008
#define ST_DCF_FLAG 0x010
#define ST_MP_FLAG 0x00c
#define ST_MP_FREQ 0x034
#define ST_MP_RECV_BUF_SEL 0x044
#define ST_MP_RECV_BUF_SIZE 0x046
#define ST_MP_RECV_BUF 0x048
#define ST_MP_SEND_BUF 0x050
#define ST_MP_SEND_BUF_SIZE 0x054
#define ST_MP_READY_BITMAP 0x086
#define ST_CURR_TGID 0x0b6
#define ST_LINK_LEVEL 0x0b8
#define ST_BEACON_INDICATE 0x0be
#define ST_PWR_MGT_MODE 0x0c2
#define ST_MP_IGNORE_FATAL 0x0da
#define ST_MAC_ADDRESS 0x0dc
#define ST_PPARAM 0x0e4
#define ST_CHILD_MAC 0x124
#define ST_CHILD_BITMAP 0x17e
#define ST_AID 0x184
#define ST_PARENT_MAC 0x186
#define ST_SCAN_CHANNEL 0x18c
#define ST_MAX_SEND_SIZE 0x18e
#define ST_MAX_RECV_SIZE 0x190
#define ST_ENABLE_CHANNEL 0x1f0
#define ST_ALLOWED_CHANNEL 0x1f2
#define ST_SIZE 0x7bc

/* WMParentParam (0x40 bytes) */
#define PP_GAME_INFO 0x00
#define PP_GAME_INFO_LENGTH 0x04
#define PP_GGID 0x08
#define PP_TGID 0x0c
#define PP_ENTRY 0x0e
#define PP_MAX_ENTRY 0x10
#define PP_MULTIBOOT 0x12
#define PP_KS 0x14
#define PP_CS 0x16
#define PP_BEACON_PERIOD 0x18
#define PP_CHANNEL 0x32
#define PP_PARENT_MAX_SIZE 0x34
#define PP_CHILD_MAX_SIZE 0x36

/* WM's states, API ids, error and state codes */
enum {
    STATE_READY,
    STATE_STOP,
    STATE_IDLE,
    STATE_CLASS1,
    STATE_TESTMODE,
    STATE_SCAN,
    STATE_CONNECT,
    STATE_PARENT,
    STATE_CHILD,
    STATE_MP_PARENT,
    STATE_MP_CHILD,
    STATE_DCF_CHILD
};
enum {
    API_INITIALIZE = 0,
    API_RESET = 1,
    API_END = 2,
    API_ENABLE = 3,
    API_DISABLE = 4,
    API_POWER_ON = 5,
    API_POWER_OFF = 6,
    API_SET_P_PARAM = 7,
    API_START_PARENT = 8,
    API_END_PARENT = 9,
    API_START_SCAN = 10,
    API_END_SCAN = 11,
    API_START_CONNECT = 12,
    API_DISCONNECT = 13,
    API_START_MP = 14,
    API_SET_MP_DATA = 15,
    API_END_MP = 16,
    API_START_DCF = 17,
    API_SET_DCF_DATA = 18,
    API_END_DCF = 19,
    API_SET_GAMEINFO = 24,
    API_SET_BEACON_IND = 25,
    API_SET_LIFETIME = 29,
    API_MEASURE_CHANNEL = 30,
    API_SET_ENTRY = 33,
    API_START_SCAN_EX = 38,
    API_COUNT = 43,
    API_INDICATION = 0x80,
    API_PORT_SEND = 0x81,
    API_PORT_RECV = 0x82,
};
enum { ERR_SUCCESS = 0, ERR_FAILED = 1, ERR_ILLEGAL_STATE = 3, ERR_NO_CHILD = 7 };
enum {
    CODE_PARENT_START = 0,
    CODE_BEACON_SENT = 2,
    CODE_PARENT_NOT_FOUND = 4,
    CODE_PARENT_FOUND = 5,
    CODE_CONNECT_START = 6,
    CODE_CONNECTED = 7,
    CODE_BEACON_LOST = 8,
    CODE_DISCONNECTED = 9,
    CODE_MP_START = 10,
    CODE_MPEND_IND = 11,
    CODE_MP_IND = 12,
    CODE_MPACK_IND = 13,
    CODE_DCF_START = 14,
    CODE_DCF_IND = 15,
    CODE_PORT_SEND = 20,
    CODE_PORT_RECV = 21,
};
#define REQUEST_ACCEPTED 0x8000u

#define CYCLES_PER_MS 33514u /* the bus clock, 33.513982 MHz */
#define LINK_LEVEL 3         /* the best: the consoles side by side */
#define MAX_CHILDREN 15
#define QUEUE_SIZE 64
#define SEND_QUEUE_SIZE 32
#define LINK_MAX 4096 /* the bytes one console sends another in one frame */

static uint32_t rd8(uint32_t a)
{
    uint32_t v = 0;
    bus_read(a, 1, &v);
    return v;
}

static uint32_t rd16(uint32_t a)
{
    uint32_t v = 0;
    bus_read(a, 2, &v);
    return v;
}

static uint32_t rd32(uint32_t a)
{
    uint32_t v = 0;
    bus_read(a, 4, &v);
    return v;
}

static void wr8(uint32_t a, uint32_t v)
{
    bus_write(a, 1, v);
}

static void wr16(uint32_t a, uint32_t v)
{
    bus_write(a, 2, v);
}

static void wr32(uint32_t a, uint32_t v)
{
    bus_write(a, 4, v);
}

static void put16(uint8_t *p, uint32_t v)
{
    p[0] = (uint8_t) v;
    p[1] = (uint8_t) (v >> 8);
}

static void put32(uint8_t *p, uint32_t v)
{
    put16(p, v);
    put16(p + 2, v >> 16);
}

static uint32_t get16(const uint8_t *p)
{
    return (uint32_t) p[0] | (uint32_t) p[1] << 8;
}

static uint32_t get32(const uint8_t *p)
{
    return get16(p) | get16(p + 2) << 16;
}

/* A callback on its way to the ARM9: into a command buffer (`target`), or through fifo7to9
 * (`target` 0), once the clock reaches `at`. */
typedef struct Callback {
    uint32_t target;
    uint64_t at;
    uint16_t length;
    uint8_t data[0x100];
} Callback;

/* A WM_SetMPDataToPortEx request waiting for its MP turn. */
typedef struct Send {
    uint32_t buffer; /* the command buffer, where its PORT_SEND callback goes */
    uint32_t data, size, dest, port, callback, argument;
} Send;

/* What a parent's beacon carries (WMBssDesc / WMGameInfo). */
typedef struct Beacon {
    uint8_t mac[6];
    uint16_t channel, tgid, max_entry, parent_max, child_max, period, info_length;
    uint32_t ggid;
    uint8_t attribute;
    uint8_t info[112];
} Beacon;

static struct {
    int on;
    int trace; /* RUN_TRACE names wm: the commands and the radio's events on stderr */
    uint8_t mac[6];
    uint32_t wm7, status, fifo7to9;
    uint64_t commands[API_COUNT + 1], callbacks, notifications, exchanges, mp_turns;
    /* callbacks waiting */
    Callback queue[QUEUE_SIZE];
    int queue_head, queue_count;
    /* a parent */
    int parent;           /* WM_StartParent until WM_EndParent */
    uint32_t parent_req;  /* WM_StartParent's buffer */
    uint64_t next_beacon; /* when the next BEACON_SENT is due */
    Beacon beacon;        /* this console's, while a parent */
    uint16_t child_bitmap;
    uint8_t children[MAX_CHILDREN + 1][6];
    /* a scan */
    uint32_t scan_req, scan_buf;
    uint16_t scan_channel;
    uint64_t scan_end;
    /* a child */
    int connecting, connected;
    uint32_t connect_req;
    uint8_t parent_mac[6];
    uint16_t aid;
    int infra; /* connected (or connecting) to the access point of runtime/wifi.c */
    uint64_t connected_at;
    /* a scan of WM_StartScanEx */
    uint32_t scan_ex_req;
    uint64_t scan_ex_end;
    /* DCF (the access point's data frames) */
    int dcf;
    uint32_t dcf_buf, dcf_size;
    uint64_t dcf_sent, dcf_received;
    /* MP */
    int mp;
    uint32_t mp_req, recv_buf, recv_size, send_buf, send_size;
    int recv_half;
    Send sends[SEND_QUEUE_SIZE];
    int send_count;
    uint16_t seq[16];
    /* the radio: the other consoles (RUN_LINK) */
    int console, consoles;
    int linked;
#ifdef _WIN32
    HANDLE link_in, link_out;
#else
    int link_in, link_out;
#endif
    uint32_t exchanged_frame;
    int peer_beacon_valid;
    Beacon peer_beacon;
    /* what goes out with the next exchange */
    uint8_t out[LINK_MAX];
    uint32_t out_length;
} wm;

/* ---- callbacks ---- */

static void post_at(uint32_t target, const uint8_t *data, uint32_t length, uint64_t at)
{
    if (wm.queue_count == QUEUE_SIZE) {
        fprintf(stderr, "wm: callback queue full; one dropped\n");
        return;
    }
    Callback *c = &wm.queue[(wm.queue_head + wm.queue_count) % QUEUE_SIZE];
    c->target = target;
    c->at = at;
    c->length = (uint16_t) (length > sizeof(c->data) ? sizeof(c->data) : length);
    memcpy(c->data, data, c->length);
    wm.queue_count++;
}

/* The callback of the command in `buffer`, now: {apiid, errcode, ...}. */
static void reply(uint32_t buffer, const uint8_t *data, uint32_t length)
{
    post_at(buffer, data, length, 0);
}

static void reply_simple(uint32_t buffer, uint32_t api, uint32_t err)
{
    uint8_t cb[8] = {0};
    put16(cb, api);
    put16(cb + 2, err);
    reply(buffer, cb, sizeof(cb));
}

/* A notification through fifo7to9. */
static void notify(const uint8_t *data, uint32_t length)
{
    post_at(0, data, length, 0);
}

/* Hands the ARM9 what is due, in order: a notification waits until the ARM9 took the last. */
static void deliver(void)
{
    while (wm.queue_count > 0) {
        Callback *c = &wm.queue[wm.queue_head];
        if (c->at > io_cycles()) {
            return;
        }
        uint32_t target = c->target ? c->target : wm.fifo7to9;
        if (c->target == 0 && (wm.fifo7to9 == 0 || (rd16(SHARED_WM_CALLBACK_CONTROL) & 1))) {
            return;
        }
        for (uint32_t i = 0; i < c->length; i++) {
            wr8(target + i, c->data[i]);
        }
        if (!io_fifo_push_to_arm9(0xau | (target & 0x3ffffffu) << 6)) {
            return; /* the FIFO is full: again at the next step (the bytes are written again) */
        }
        if (c->target == 0) {
            wr16(SHARED_WM_CALLBACK_CONTROL, rd16(SHARED_WM_CALLBACK_CONTROL) | 1);
            wm.notifications++;
        } else {
            wm.callbacks++;
        }
        wm.queue_head = (wm.queue_head + 1) % QUEUE_SIZE;
        wm.queue_count--;
    }
}

/* ---- the status ---- */

static void set_state(uint32_t state)
{
    if (wm.status) {
        wr16(wm.status + ST_STATE, state);
    }
}

static uint32_t state(void)
{
    return wm.status ? rd16(wm.status + ST_STATE) : STATE_READY;
}

static void status_init(void)
{
    for (uint32_t i = 0; i < ST_SIZE; i += 4) {
        wr32(wm.status + i, 0);
    }
    for (int i = 0; i < 6; i++) {
        wr8(wm.status + ST_MAC_ADDRESS + (uint32_t) i, wm.mac[i]);
    }
    wr16(wm.status + ST_ENABLE_CHANNEL, ENABLED_CHANNELS);
    wr16(wm.status + ST_ALLOWED_CHANNEL, ALLOWED_CHANNELS);
    wr16(wm.status + ST_PWR_MGT_MODE, 1);
    set_state(STATE_STOP);
}

/* ---- the radio's messages ---- */

/* A message to the other consoles: a kind, a length and the bytes. */
enum { MSG_BEACON = 1, MSG_CONNECT = 2, MSG_ACCEPT = 3, MSG_DISCONNECT = 4, MSG_MP_PARENT = 5, MSG_MP_CHILD = 6 };

static void message(int kind, const uint8_t *data, uint32_t length)
{
    if (!wm.linked || wm.out_length + 3 + length > sizeof(wm.out)) {
        return;
    }
    wm.out[wm.out_length] = (uint8_t) kind;
    put16(wm.out + wm.out_length + 1, length);
    memcpy(wm.out + wm.out_length + 3, data, length);
    wm.out_length += 3 + length;
}

static void disconnect_peer(const uint8_t *mac, uint32_t aid)
{
    uint8_t m[8];
    memcpy(m, mac, 6);
    put16(m + 6, aid);
    message(MSG_DISCONNECT, m, sizeof(m));
}

/* ---- notifications ---- */

/* WMStartParentCallback: state 8, the child's MAC 0xa, its AID 0x10, the reason 0x12. */
static void parent_event(uint32_t code, const uint8_t *mac, uint32_t aid)
{
    uint8_t cb[0x30] = {0};
    put16(cb, API_START_PARENT);
    put16(cb + 8, code);
    if (mac != NULL) {
        memcpy(cb + 0xa, mac, 6);
    }
    put16(cb + 0x10, aid);
    notify(cb, sizeof(cb));
}

/* WMStartConnectCallback: state 8, the AID 0xa, the reason 0xc, the parent's MAC 0xe. (The
 * ROM's WmReceiveFifo reads it as a WMStartParentCallback for the ports' notification.) */
static void connect_event(uint32_t target, uint32_t err, uint32_t code, uint32_t aid)
{
    uint8_t cb[0x1c] = {0};
    put16(cb, API_START_CONNECT);
    put16(cb + 2, err);
    put16(cb + 8, code);
    put16(cb + 0xa, aid);
    memcpy(cb + 0xe, wm.parent_mac, 6);
    if (target) {
        reply(target, cb, sizeof(cb));
    } else {
        notify(cb, sizeof(cb));
    }
}

/* WMStartMPCallback: state 4, the receive buffer 8. */
static void mp_event(uint32_t code, uint32_t buffer)
{
    uint8_t cb[0x14] = {0};
    put16(cb, API_START_MP);
    put16(cb + 4, code);
    put32(cb + 8, buffer);
    notify(cb, sizeof(cb));
}

/* WMPortRecvCallback: state 4, port 6, the receive buffer 8, the data 0xc, its length 0x10,
 * the sender's AID 0x12 and MAC 0x14, the sequence number 0x1a, this console's AID 0x20. */
static void port_receive(uint32_t port, uint32_t buffer, uint32_t data, uint32_t length, uint32_t aid, const uint8_t *mac)
{
    uint8_t cb[0x3c] = {0};
    put16(cb, API_PORT_RECV);
    put16(cb + 4, CODE_PORT_RECV);
    put16(cb + 6, port);
    put32(cb + 8, buffer);
    put32(cb + 0xc, data);
    put16(cb + 0x10, length);
    put16(cb + 0x12, aid);
    memcpy(cb + 0x14, mac, 6);
    put16(cb + 0x1a, wm.seq[port & 15]++);
    put16(cb + 0x20, wm.aid);
    notify(cb, sizeof(cb));
}

/* WMPortSendCallback into the request's buffer: state 8, port 0xa, the bitmaps 0xc-0x11, the
 * data 0x14, its size 0x18, the callback 0x1c and its argument 0x20. */
static void port_sent(const Send *s, uint32_t err, uint32_t sent)
{
    uint8_t cb[0x24] = {0};
    put16(cb, API_PORT_SEND);
    put16(cb + 2, err);
    put16(cb + 8, CODE_PORT_SEND);
    put16(cb + 0xa, s->port);
    put16(cb + 0xc, s->dest);
    put16(cb + 0xe, s->dest & ~sent);
    put16(cb + 0x10, sent);
    put32(cb + 0x14, s->data);
    put16(cb + 0x18, s->size);
    put32(cb + 0x1c, s->callback);
    put32(cb + 0x20, s->argument);
    reply(s->buffer, cb, sizeof(cb));
}

/* ---- MP ---- */

static void mp_stop(uint32_t err)
{
    for (int i = 0; i < wm.send_count; i++) {
        port_sent(&wm.sends[i], err, 0);
    }
    wm.send_count = 0;
    wm.mp = 0;
    if (wm.status) {
        wr32(wm.status + ST_MP_FLAG, 0);
    }
}

/* The next half of the MP receive buffer. */
static uint32_t receive_half(void)
{
    uint32_t half = wm.recv_size / 2;
    uint32_t at = wm.recv_buf + (uint32_t) wm.recv_half * half;
    wm.recv_half ^= 1;
    if (wm.status) {
        wr16(wm.status + ST_MP_RECV_BUF_SEL, (uint32_t) wm.recv_half);
    }
    return at;
}

/* This console's MP data for the turn, as a message: the requests whose data fit, each as
 * port, destination bitmap, size and bytes. Returns the requests taken. */
static int mp_outgoing(int kind)
{
    uint8_t m[LINK_MAX / 2];
    uint32_t n = 2, room = wm.status ? rd16(wm.status + ST_MAX_SEND_SIZE) : 0, used = 0;
    int taken = 0;
    put16(m, wm.aid);
    while (taken < wm.send_count) {
        Send *s = &wm.sends[taken];
        if (used + s->size > room || n + 6 + s->size > sizeof(m)) {
            break;
        }
        put16(m + n, s->port);
        put16(m + n + 2, s->dest);
        put16(m + n + 4, s->size);
        for (uint32_t i = 0; i < s->size; i++) {
            m[n + 6 + i] = (uint8_t) rd8(s->data + i);
        }
        n += 6 + s->size;
        used += s->size;
        taken++;
    }
    message(kind, m, n);
    return taken;
}

static void mp_sent(int taken, uint16_t to)
{
    for (int i = 0; i < taken; i++) {
        port_sent(&wm.sends[i], ERR_SUCCESS, wm.sends[i].dest & to);
    }
    memmove(wm.sends, wm.sends + taken, (size_t) (wm.send_count - taken) * sizeof(Send));
    wm.send_count -= taken;
}

/* A turn's data from `aid` (the parent's for a child, a child's for the parent): each piece
 * for this console written to the receive buffer and handed to its port. */
static void mp_incoming(const uint8_t *m, uint32_t length, const uint8_t *mac)
{
    if (length < 2) {
        return;
    }
    uint32_t from = get16(m), buffer = receive_half(), at = buffer + 0x40;
    for (uint32_t n = 2; n + 6 <= length;) {
        uint32_t port = get16(m + n), dest = get16(m + n + 2), size = get16(m + n + 4);
        if (n + 6 + size > length) {
            break;
        }
        if ((dest & (1u << wm.aid)) && at + size <= wm.recv_buf + wm.recv_size) {
            for (uint32_t i = 0; i < size; i++) {
                wr8(at + i, m[n + 6 + i]);
            }
            port_receive(port, buffer, at, size, from, mac);
            at += (size + 3) & ~3u;
        }
        n += 6 + size;
    }
}

/* ---- the commands ---- */

static void start_parent(uint32_t buffer)
{
    uint32_t pp = wm.status + ST_PPARAM;
    Beacon *b = &wm.beacon;
    memcpy(b->mac, wm.mac, 6);
    b->ggid = rd32(pp + PP_GGID);
    b->tgid = (uint16_t) rd16(pp + PP_TGID);
    b->channel = (uint16_t) rd16(pp + PP_CHANNEL);
    b->max_entry = (uint16_t) rd16(pp + PP_MAX_ENTRY);
    b->parent_max = (uint16_t) rd16(pp + PP_PARENT_MAX_SIZE);
    b->child_max = (uint16_t) rd16(pp + PP_CHILD_MAX_SIZE);
    b->period = (uint16_t) rd16(pp + PP_BEACON_PERIOD);
    b->attribute = (uint8_t) ((rd16(pp + PP_ENTRY) ? 1 : 0) | (rd16(pp + PP_MULTIBOOT) ? 2 : 0) | (rd16(pp + PP_KS) ? 4 : 0) |
                              (rd16(pp + PP_CS) ? 8 : 0));
    b->info_length = (uint16_t) rd16(pp + PP_GAME_INFO_LENGTH);
    if (b->info_length > sizeof(b->info)) {
        b->info_length = sizeof(b->info);
    }
    uint32_t info = rd32(pp + PP_GAME_INFO);
    for (uint32_t i = 0; i < b->info_length; i++) {
        b->info[i] = (uint8_t) rd8(info + i);
    }
    wm.parent = 1;
    wm.parent_req = buffer;
    wm.child_bitmap = 0;
    memset(wm.children, 0, sizeof(wm.children));
    wm.aid = 0;
    wr16(wm.status + ST_AID, 0);
    wr16(wm.status + ST_CHILD_BITMAP, 0);
    wr16(wm.status + ST_CURR_TGID, b->tgid);
    wr16(wm.status + ST_MAX_SEND_SIZE, b->parent_max + 4u);
    wr16(wm.status + ST_MAX_RECV_SIZE, b->child_max + 2u);
    set_state(STATE_PARENT);
    uint8_t cb[0x30] = {0};
    put16(cb, API_START_PARENT);
    put16(cb + 8, CODE_PARENT_START);
    reply(buffer, cb, sizeof(cb));
    wm.next_beacon = io_cycles() + (uint64_t) (b->period ? b->period : 200) * CYCLES_PER_MS;
}

static void end_parent(void)
{
    if (!wm.parent) {
        return;
    }
    for (uint32_t aid = 1; aid <= MAX_CHILDREN; aid++) {
        if (wm.child_bitmap & (1u << aid)) {
            disconnect_peer(wm.children[aid], aid);
        }
    }
    wm.parent = 0;
    wm.child_bitmap = 0;
    if (wm.status) {
        wr16(wm.status + ST_CHILD_BITMAP, 0);
    }
}

static void end_child(void)
{
    if (wm.connected || wm.connecting) {
        disconnect_peer(wm.parent_mac, wm.aid);
    }
    wm.connected = wm.connecting = 0;
}

/* WM_StartScan's request (WMStartScanReq: the channel 2, the buffer 4, the time 8). The
 * result comes once the channel's time is over: the parent heard on it then, or none. */
static void start_scan(uint32_t buffer)
{
    wm.scan_req = buffer;
    wm.scan_channel = (uint16_t) rd16(buffer + 2);
    wm.scan_buf = rd32(buffer + 4);
    uint32_t ms = rd16(buffer + 8);
    wm.scan_end = io_cycles() + (uint64_t) (ms ? ms : 1) * CYCLES_PER_MS;
    wr16(wm.status + ST_SCAN_CHANNEL, wm.scan_channel);
    set_state(STATE_SCAN);
}

/* The parent's beacon as WMBssDesc at `at` (0xc0 bytes; the game info at 0x40). */
static void write_bss(uint32_t at, const Beacon *b)
{
    uint8_t d[0xc0] = {0};
    uint32_t info_length = 0x10u + b->info_length;
    put16(d, (0x40u + info_length + 1) / 2);
    put16(d + 2, 0xd0); /* rssi */
    memcpy(d + 4, b->mac, 6);
    put16(d + 0xa, 8); /* the SSID: ggid and tgid */
    put32(d + 0xc, b->ggid);
    put16(d + 0x10, b->tgid);
    put16(d + 0x2c, 0x21); /* capability: ESS, short preamble */
    put16(d + 0x2e, 3);
    put16(d + 0x30, 3);
    put16(d + 0x32, b->period);
    put16(d + 0x34, 1);
    put16(d + 0x36, b->channel);
    put16(d + 0x3c, info_length);
    uint8_t *g = d + 0x40;
    put16(g, 1); /* version */
    put32(g + 4, b->ggid);
    put16(g + 8, b->tgid);
    g[0xa] = (uint8_t) b->info_length;
    g[0xb] = b->attribute;
    put16(g + 0xc, b->parent_max);
    put16(g + 0xe, b->child_max);
    memcpy(g + 0x10, b->info, b->info_length);
    for (uint32_t i = 0; i < sizeof(d); i++) {
        wr8(at + i, d[i]);
    }
}

static void scan_done(void)
{
    uint8_t cb[0xc0] = {0};
    put16(cb, API_START_SCAN);
    const Beacon *b = wm.peer_beacon_valid && wm.peer_beacon.channel == wm.scan_channel ? &wm.peer_beacon : NULL;
    if (wm.trace) {
        fprintf(stderr, "wm: frame %u console %d scan of channel %u: %s\n", io_frame(), wm.console, wm.scan_channel,
                b                      ? "a parent"
                : wm.peer_beacon_valid ? "a parent on another channel"
                                       : "nobody");
    }
    put16(cb + 8, b ? CODE_PARENT_FOUND : CODE_PARENT_NOT_FOUND);
    put16(cb + 0x10, wm.scan_channel);
    if (b != NULL) {
        write_bss(wm.scan_buf, b);
        memcpy(cb + 0xa, b->mac, 6);
        put16(cb + 0x12, LINK_LEVEL);
        put16(cb + 0x14, 8);
        put32(cb + 0x16, b->ggid);
        put16(cb + 0x1a, b->tgid);
        put16(cb + 0x36, 0x10u + b->info_length);
        for (uint32_t i = 0; i < 0x80; i++) {
            cb[0x38 + i] = (uint8_t) rd8(wm.scan_buf + 0x40 + i);
        }
    }
    reply(wm.scan_req, cb, sizeof(cb));
    wm.scan_req = 0;
}

/* WM_StartScanEx's request in the command buffer: the channels 2, the buffer 4 and its size 8,
 * the time per channel 0xa, the BSSID 0xc, the scan type 0x12, the SSID's length 0x14, the SSID
 * 0x16 and the length to match 0x36 (for scan types 2 and 3). The result comes when the
 * channels' time is over: the access point (runtime/wifi.c) when it is on one of them and
 * matches; without it, on a console linked to another (local play), the other console's parent
 * when its beacon came on one of the channels then and its MAC is the BSSID asked for (or that
 * is ff:ff:ff:ff:ff:ff); else nobody. */
static void start_scan_ex(uint32_t buffer)
{
    uint32_t channels = rd16(buffer + 2), n = 0;
    for (uint32_t c = channels; c; c &= c - 1) {
        n++;
    }
    uint32_t ms = rd16(buffer + 0xa);
    wm.scan_ex_req = buffer;
    wm.scan_ex_end = io_cycles() + (uint64_t) (ms ? ms : 1) * (n ? n : 1) * CYCLES_PER_MS;
    set_state(STATE_SCAN);
}

/* WMStartScanExCallback: state 8, the channels scanned 0xa, the count 0xe, the descriptions'
 * addresses 0x10 (16 of them) and their link levels 0x50. */
static void scan_ex_done(void)
{
    uint32_t buffer = wm.scan_ex_req;
    uint32_t channels = rd16(buffer + 2), scan_buf = rd32(buffer + 4), size = rd16(buffer + 8);
    uint8_t bssid[6], ssid[32];
    for (int i = 0; i < 6; i++) {
        bssid[i] = (uint8_t) rd8(buffer + 0xc + (uint32_t) i);
    }
    uint32_t type = rd16(buffer + 0x12), ssid_length = rd16(buffer + 0x14), match = rd16(buffer + 0x36);
    for (int i = 0; i < 32; i++) {
        ssid[i] = (uint8_t) rd8(buffer + 0x16 + (uint32_t) i);
    }
    if (ssid_length > 32) {
        ssid_length = 32;
    }
    if (type < 2 || match > ssid_length) {
        match = ssid_length;
    }
    uint8_t d[WIFI_BSS_SIZE];
    int found = wifi_on() && size >= WIFI_BSS_SIZE && wifi_scan(channels, bssid, ssid, ssid_length, match, d);
    const Beacon *b = NULL; /* without the access point: the other console's parent */
    if (!wifi_on() && wm.peer_beacon_valid && wm.peer_beacon.channel >= 1 && wm.peer_beacon.channel <= 16 &&
        (channels & (1u << (wm.peer_beacon.channel - 1))) && size >= 0xc0) {
        static const uint8_t any[6] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
        if (memcmp(bssid, any, 6) == 0 || memcmp(bssid, wm.peer_beacon.mac, 6) == 0) {
            b = &wm.peer_beacon;
        }
    }
    uint8_t cb[0x70] = {0};
    put16(cb, API_START_SCAN_EX);
    put16(cb + 8, found || b ? CODE_PARENT_FOUND : CODE_PARENT_NOT_FOUND);
    put16(cb + 0xa, channels);
    if (found) {
        for (uint32_t i = 0; i < WIFI_BSS_SIZE; i++) {
            wr8(scan_buf + i, d[i]);
        }
    } else if (b != NULL) {
        write_bss(scan_buf, b);
    }
    if (found || b != NULL) {
        put16(cb + 0xe, 1);
        put32(cb + 0x10, scan_buf);
        put16(cb + 0x50, LINK_LEVEL);
    }
    if (wm.trace) {
        fprintf(stderr, "wm: frame %u console %d scan of channels %04x: %s\n", io_frame(), wm.console, channels,
                found ? "the access point" : b != NULL ? "a parent" : "nobody");
    }
    reply(buffer, cb, sizeof(cb));
    wm.scan_ex_req = 0; /* the state stays SCAN until WM_EndScan */
}

/* ---- DCF: the access point's data frames ---- */

static void dcf_stop(void)
{
    wm.dcf = 0;
    if (wm.status) {
        wr32(wm.status + ST_DCF_FLAG, 0);
    }
}

/* WMStartDCFCallback: state 4, the receive buffer 8. */
static void dcf_event(uint32_t target, uint32_t code)
{
    uint8_t cb[0xc] = {0};
    put16(cb, API_START_DCF);
    put16(cb + 4, code);
    put32(cb + 8, wm.dcf_buf);
    if (target) {
        reply(target, cb, sizeof(cb));
    } else {
        notify(cb, sizeof(cb));
    }
}

/* A frame the access point sends, once the ARM9 has taken everything before it: written into
 * the DCF receive buffer (WMDcfRecvBuf: the length 6, the rate and RSSI 0xe, the destination
 * 0x18, the source 0x1e, the frame's body 0x2c) and handed over with DCF_IND. */
static void dcf_receive(void)
{
    static uint8_t frame[WIFI_FRAME_MAX];
    uint8_t src[6], dst[6];
    if (!wm.dcf || wm.queue_count > 0 || (rd16(SHARED_WM_CALLBACK_CONTROL) & 1)) {
        return;
    }
    uint32_t room = wm.dcf_size > 0x2c ? wm.dcf_size - 0x2c : 0;
    uint32_t length = wifi_receive(io_cycles(), src, dst, frame, room < sizeof(frame) ? room : sizeof(frame));
    if (length == 0) {
        return;
    }
    for (uint32_t i = 0; i < 0x2c; i += 4) {
        wr32(wm.dcf_buf + i, 0);
    }
    wr16(wm.dcf_buf + 6, length);
    wr16(wm.dcf_buf + 0xe, 0xd0u << 8 | 0x14); /* RSSI 0xd0, 2 Mbps */
    for (int i = 0; i < 6; i++) {
        wr8(wm.dcf_buf + 0x18 + (uint32_t) i, dst[i]);
        wr8(wm.dcf_buf + 0x1e + (uint32_t) i, src[i]);
    }
    for (uint32_t i = 0; i < length; i++) {
        wr8(wm.dcf_buf + 0x2c + i, frame[i]);
    }
    wm.dcf_received++;
    dcf_event(0, CODE_DCF_IND);
    deliver();
}

static void reset(void)
{
    mp_stop(ERR_FAILED);
    end_parent();
    end_child();
    dcf_stop();
    if (wm.infra) {
        wifi_disconnect();
    }
    wm.infra = 0;
    wm.scan_req = 0;
    wm.scan_ex_req = 0;
    wm.aid = 0;
    if (wm.status) {
        wr16(wm.status + ST_AID, 0);
        wr16(wm.status + ST_CHILD_BITMAP, 0);
        wr16(wm.status + ST_LINK_LEVEL, 0);
    }
    set_state(STATE_IDLE);
}

void wm_command(uint32_t data)
{
    uint32_t buffer = data & 0x3ffffffu; /* a main RAM address fits the word's 26 bits */
    if (!wm.on) {
        return;
    }
    uint32_t api = rd16(buffer) & 0x7fff;
    uint32_t arg[10];
    for (int i = 0; i < 10; i++) {
        arg[i] = rd32(buffer + 4 + 4 * (uint32_t) i);
    }
    if (wm.trace) {
        fprintf(stderr, "wm: frame %u console %d command %u (%08x %08x %08x %08x)\n", io_frame(), wm.console, api, arg[0],
                arg[1], arg[2], arg[3]);
    }
    wm.commands[api < API_COUNT ? api : API_COUNT]++;
    switch (api) {
        case API_INITIALIZE: /* WM_Initialize: enabled and powered on in one */
        case API_ENABLE:
            wm.wm7 = arg[0];
            wm.status = arg[1];
            wm.fifo7to9 = arg[2];
            status_init();
            if (api == API_INITIALIZE) {
                set_state(STATE_IDLE);
            }
            reply_simple(buffer, api, ERR_SUCCESS);
            return;
        case API_DISABLE:
            set_state(STATE_READY);
            reply_simple(buffer, api, ERR_SUCCESS);
            return;
        case API_POWER_ON:
            set_state(STATE_IDLE);
            reply_simple(buffer, api, ERR_SUCCESS);
            return;
        case API_POWER_OFF:
            set_state(STATE_STOP);
            reply_simple(buffer, api, ERR_SUCCESS);
            return;
        case API_RESET:
            reset();
            reply_simple(buffer, api, ERR_SUCCESS);
            return;
        case API_END: /* WM_End: back to READY; the ARM9 then finishes (WM_Finish) */
            reset();
            set_state(STATE_READY);
            reply_simple(buffer, api, ERR_SUCCESS);
            return;
        case API_SET_P_PARAM:
            for (uint32_t i = 0; i < 0x40; i += 4) {
                wr32(wm.status + ST_PPARAM + i, rd32(arg[0] + i));
            }
            reply_simple(buffer, api, ERR_SUCCESS);
            return;
        case API_START_PARENT:
            start_parent(buffer);
            return;
        case API_END_PARENT:
            mp_stop(ERR_FAILED);
            end_parent();
            set_state(STATE_IDLE);
            reply_simple(buffer, api, ERR_SUCCESS);
            return;
        case API_START_SCAN:
            start_scan(buffer);
            return;
        case API_END_SCAN:
            if (wm.scan_req) {
                scan_done();
            }
            set_state(STATE_IDLE);
            reply_simple(buffer, api, ERR_SUCCESS);
            return;
        case API_START_CONNECT: { /* WMStartConnectReq: the parent's WMBssDesc at 4 */
            uint32_t bss = rd32(buffer + 4);
            for (int i = 0; i < 6; i++) {
                wm.parent_mac[i] = (uint8_t) rd8(bss + 4 + (uint32_t) i);
            }
            wm.connect_req = buffer;
            wm.connecting = 1;
            set_state(STATE_CONNECT);
            connect_event(buffer, ERR_SUCCESS, CODE_CONNECT_START, 0);
            if (wifi_is_ap(wm.parent_mac)) { /* the access point: associated after a while */
                wm.infra = 1;
                wm.connected_at = io_cycles() + (uint64_t) WIFI_ASSOCIATE_MS * CYCLES_PER_MS;
                return;
            }
            uint8_t m[12];
            memcpy(m, wm.mac, 6);
            memcpy(m + 6, wm.parent_mac, 6);
            message(MSG_CONNECT, m, sizeof(m));
            if (!wm.linked) { /* nobody to answer: the connection fails */
                wm.connecting = 0;
                set_state(STATE_IDLE);
                connect_event(0, ERR_FAILED, CODE_CONNECT_START, 0);
            }
            return;
        }
        case API_DISCONNECT: {
            uint32_t bitmap = arg[0];
            if (wm.infra) {
                dcf_stop();
                wifi_disconnect();
                wm.infra = wm.connected = wm.connecting = 0;
                wm.aid = 0;
                wr16(wm.status + ST_AID, 0);
                set_state(STATE_IDLE);
                reply_simple(buffer, api, ERR_SUCCESS);
                return;
            }
            if (wm.parent) {
                for (uint32_t aid = 1; aid <= MAX_CHILDREN; aid++) {
                    if ((bitmap & (1u << aid)) && (wm.child_bitmap & (1u << aid))) {
                        disconnect_peer(wm.children[aid], aid);
                        wm.child_bitmap &= (uint16_t) ~(1u << aid);
                        parent_event(CODE_DISCONNECTED, wm.children[aid], aid);
                    }
                }
                wr16(wm.status + ST_CHILD_BITMAP, wm.child_bitmap);
            } else {
                mp_stop(ERR_FAILED);
                end_child();
                set_state(STATE_IDLE);
            }
            reply_simple(buffer, api, ERR_SUCCESS);
            return;
        }
        case API_START_MP:
            wm.mp = 1;
            wm.mp_req = buffer;
            wm.recv_buf = arg[0];
            wm.recv_size = arg[1] * 2;
            wm.send_buf = arg[2];
            wm.send_size = arg[3];
            wm.recv_half = 0;
            wr32(wm.status + ST_MP_FLAG, 1);
            wr16(wm.status + ST_MP_FREQ, arg[4]);
            wr16(wm.status + ST_MP_RECV_BUF_SIZE, wm.recv_size / 2);
            wr32(wm.status + ST_MP_RECV_BUF, wm.recv_buf);
            wr32(wm.status + ST_MP_RECV_BUF + 4, wm.recv_buf + wm.recv_size / 2);
            wr32(wm.status + ST_MP_SEND_BUF, wm.send_buf);
            wr16(wm.status + ST_MP_SEND_BUF_SIZE, wm.send_size);
            wr16(wm.status + ST_MP_READY_BITMAP, wm.parent ? wm.child_bitmap : 1);
            wr16(wm.status + ST_MP_IGNORE_FATAL, arg[9]);
            set_state(wm.parent ? STATE_MP_PARENT : STATE_MP_CHILD);
            {
                uint8_t cb[0x14] = {0};
                put16(cb, API_START_MP);
                put16(cb + 4, CODE_MP_START);
                reply(buffer, cb, sizeof(cb));
            }
            return;
        case API_SET_MP_DATA:
            if (!wm.mp || wm.send_count == SEND_QUEUE_SIZE) {
                Send s = {buffer, arg[0], arg[1], arg[2], arg[3], arg[5], arg[6]};
                port_sent(&s, wm.mp ? 10u : ERR_ILLEGAL_STATE, 0);
                return;
            }
            wm.sends[wm.send_count++] = (Send){buffer, arg[0], arg[1], arg[2], arg[3], arg[5], arg[6]};
            return;
        case API_END_MP:
            mp_stop(ERR_FAILED);
            set_state(wm.parent ? STATE_PARENT : wm.connected ? STATE_CHILD : STATE_IDLE);
            reply_simple(buffer, api, ERR_SUCCESS);
            return;
        case API_SET_GAMEINFO: { /* the buffer, its size, ggid, tgid, attribute */
            Beacon *b = &wm.beacon;
            b->info_length = (uint16_t) (arg[1] > sizeof(b->info) ? sizeof(b->info) : arg[1]);
            for (uint32_t i = 0; i < b->info_length; i++) {
                b->info[i] = (uint8_t) rd8(arg[0] + i);
            }
            b->ggid = arg[2];
            b->tgid = (uint16_t) arg[3];
            b->attribute = (uint8_t) arg[4];
            reply_simple(buffer, api, ERR_SUCCESS);
            return;
        }
        case API_SET_ENTRY:
            wm.beacon.attribute = (uint8_t) ((wm.beacon.attribute & ~1u) | (arg[0] ? 1u : 0));
            reply_simple(buffer, api, ERR_SUCCESS);
            return;
        case API_MEASURE_CHANNEL: { /* WMMeasureChannelReq: channel 6, time 8; nothing busy */
            uint8_t cb[0xc] = {0};
            put16(cb, api);
            put16(cb + 8, rd16(buffer + 6));
            post_at(buffer, cb, sizeof(cb), io_cycles() + (uint64_t) rd16(buffer + 8) * CYCLES_PER_MS);
            return;
        }
        case API_START_SCAN_EX:
            if (!wifi_on() && !wm.linked) {
                break; /* without the access point or another console: taken, as before */
            }
            start_scan_ex(buffer);
            return;
        case API_START_DCF: /* the receive buffer and its size */
            wm.dcf = 1;
            wm.dcf_buf = arg[0];
            wm.dcf_size = arg[1];
            wr32(wm.status + ST_DCF_FLAG, 1);
            set_state(STATE_DCF_CHILD);
            dcf_event(buffer, CODE_DCF_START);
            return;
        case API_SET_DCF_DATA: { /* the destination's MAC in two words, the data and its size */
            static uint8_t frame[WIFI_FRAME_MAX];
            uint8_t dst[6];
            uint32_t size = arg[3] & 0xffff;
            put32(dst, arg[0]);
            put16(dst + 4, arg[1]);
            if (size > sizeof(frame)) {
                size = sizeof(frame);
            }
            for (uint32_t i = 0; i < size; i++) {
                frame[i] = (uint8_t) rd8(arg[2] + i);
            }
            if (wm.dcf && size > 0) {
                wm.dcf_sent++;
                wifi_send(io_cycles(), wm.mac, dst, frame, size);
            }
            /* the reply also covers the request's words, whose second's upper half the ARM9
             * leaves as its stack had it (a value Native code does not leave the same) */
            uint8_t cb[0x10] = {0};
            put16(cb, api);
            put16(cb + 2, wm.dcf ? ERR_SUCCESS : ERR_ILLEGAL_STATE);
            reply(buffer, cb, sizeof(cb));
            return;
        }
        case API_END_DCF:
            dcf_stop();
            set_state(STATE_CHILD);
            reply_simple(buffer, api, ERR_SUCCESS);
            return;
        case API_SET_BEACON_IND:
            wr16(wm.status + ST_BEACON_INDICATE, arg[0]);
            reply_simple(buffer, api, ERR_SUCCESS);
            return;
        default: /* the lifetimes and the rest: taken */
            break;
    }
    reply_simple(buffer, api, ERR_SUCCESS);
}

/* ---- the radio ---- */

static void beacon_message(void)
{
    const Beacon *b = &wm.beacon;
    uint8_t m[28 + sizeof(b->info)];
    memcpy(m, b->mac, 6);
    put16(m + 6, b->channel);
    put16(m + 8, b->tgid);
    put16(m + 10, b->max_entry);
    put16(m + 12, b->parent_max);
    put16(m + 14, b->child_max);
    put16(m + 16, b->period);
    put16(m + 18, b->info_length);
    put32(m + 20, b->ggid);
    m[24] = b->attribute;
    m[25] = m[26] = m[27] = 0;
    memcpy(m + 28, b->info, b->info_length);
    message(MSG_BEACON, m, 28u + b->info_length);
}

static void beacon_read(const uint8_t *m, uint32_t length)
{
    Beacon *b = &wm.peer_beacon;
    if (length < 28) {
        return;
    }
    memcpy(b->mac, m, 6);
    b->channel = (uint16_t) get16(m + 6);
    b->tgid = (uint16_t) get16(m + 8);
    b->max_entry = (uint16_t) get16(m + 10);
    b->parent_max = (uint16_t) get16(m + 12);
    b->child_max = (uint16_t) get16(m + 14);
    b->period = (uint16_t) get16(m + 16);
    b->info_length = (uint16_t) get16(m + 18);
    if (b->info_length > sizeof(b->info) || 28u + b->info_length > length) {
        b->info_length = 0;
    }
    b->ggid = get32(m + 20);
    b->attribute = m[24];
    memcpy(b->info, m + 28, b->info_length);
    wm.peer_beacon_valid = 1;
}

/* One message from another console. */
static void receive(int kind, const uint8_t *m, uint32_t length)
{
    switch (kind) {
        case MSG_BEACON:
            beacon_read(m, length);
            return;
        case MSG_CONNECT: { /* a child's MAC and the parent's it asks */
            if (length < 12 || !wm.parent || memcmp(m + 6, wm.mac, 6) != 0) {
                return;
            }
            uint32_t aid = 0, count = 0;
            for (uint32_t i = 1; i <= MAX_CHILDREN; i++) {
                if (wm.child_bitmap & (1u << i)) {
                    count++;
                } else if (aid == 0) {
                    aid = i;
                }
            }
            if (!(wm.beacon.attribute & 1) || count >= wm.beacon.max_entry) {
                aid = 0;
            }
            uint8_t a[8];
            memcpy(a, m, 6);
            put16(a + 6, aid);
            message(MSG_ACCEPT, a, sizeof(a));
            if (aid != 0) {
                memcpy(wm.children[aid], m, 6);
                wm.child_bitmap |= (uint16_t) (1u << aid);
                wr16(wm.status + ST_CHILD_BITMAP, wm.child_bitmap);
                for (int i = 0; i < 6; i++) {
                    wr8(wm.status + ST_CHILD_MAC + (aid - 1) * 6 + (uint32_t) i, m[i]);
                }
                if (wm.mp) {
                    wr16(wm.status + ST_MP_READY_BITMAP, wm.child_bitmap);
                }
                wr16(wm.status + ST_LINK_LEVEL, LINK_LEVEL);
                parent_event(CODE_CONNECTED, m, aid);
            }
            return;
        }
        case MSG_ACCEPT: { /* the child's MAC and its AID, 0 when refused */
            if (length < 8 || !wm.connecting || memcmp(m, wm.mac, 6) != 0) {
                return;
            }
            uint32_t aid = get16(m + 6);
            wm.connecting = 0;
            if (aid == 0) {
                set_state(STATE_IDLE);
                connect_event(0, ERR_FAILED, CODE_CONNECT_START, 0);
                return;
            }
            wm.connected = 1;
            wm.aid = (uint16_t) aid;
            wr16(wm.status + ST_AID, aid);
            for (int i = 0; i < 6; i++) {
                wr8(wm.status + ST_PARENT_MAC + (uint32_t) i, wm.parent_mac[i]);
            }
            wr16(wm.status + ST_MAX_SEND_SIZE, wm.peer_beacon.child_max + 2u);
            wr16(wm.status + ST_MAX_RECV_SIZE, wm.peer_beacon.parent_max + 4u);
            wr16(wm.status + ST_CURR_TGID, wm.peer_beacon.tgid);
            wr16(wm.status + ST_LINK_LEVEL, LINK_LEVEL);
            set_state(STATE_CHILD);
            connect_event(0, ERR_SUCCESS, CODE_CONNECTED, aid);
            return;
        }
        case MSG_DISCONNECT: { /* the MAC of the console sent away and its AID, or a child's leave:
                                  its parent's MAC and the child's AID (end_child) */
            if (length < 8) {
                return;
            }
            uint32_t aid = get16(m + 6);
            if (wm.parent && aid >= 1 && aid <= MAX_CHILDREN && (wm.child_bitmap & (1u << aid)) &&
                (memcmp(wm.children[aid], m, 6) == 0 || memcmp(wm.mac, m, 6) == 0)) {
                wm.child_bitmap &= (uint16_t) ~(1u << aid);
                wr16(wm.status + ST_CHILD_BITMAP, wm.child_bitmap);
                parent_event(CODE_DISCONNECTED, wm.children[aid], aid);
            } else if ((wm.connected || wm.connecting) && memcmp(m, wm.mac, 6) == 0) {
                /* the data still queued for the parent gone is handed back unsent, but not as
                   failed: the game stops (OS_Terminate) on a failed send, and the host ends a
                   link while its guests still send (the host's own "end the link") */
                mp_stop(ERR_SUCCESS);
                wm.connected = wm.connecting = 0;
                set_state(STATE_IDLE);
                connect_event(0, ERR_SUCCESS, CODE_BEACON_LOST, 0);
                connect_event(0, ERR_SUCCESS, CODE_DISCONNECTED, 0);
            } else if ((wm.connected || wm.connecting) && memcmp(m, wm.parent_mac, 6) == 0 && aid == wm.aid) {
                mp_stop(ERR_SUCCESS);
                wm.connected = wm.connecting = 0;
                set_state(STATE_IDLE);
                connect_event(0, ERR_SUCCESS, CODE_DISCONNECTED, 0);
            }
            return;
        }
        case MSG_MP_PARENT: /* a child's turn: the parent's data, then the acknowledgement */
            if (wm.connected && wm.mp) {
                mp_incoming(m, length, wm.parent_mac);
                mp_event(CODE_MP_IND, wm.recv_buf);
                mp_event(CODE_MPACK_IND, wm.recv_buf);
            }
            return;
        case MSG_MP_CHILD: /* the parent's turn: a child's data */
            if (wm.parent && wm.mp && length >= 2) {
                uint32_t aid = get16(m);
                if (aid >= 1 && aid <= MAX_CHILDREN && (wm.child_bitmap & (1u << aid))) {
                    mp_incoming(m, length, wm.children[aid]);
                }
            }
            return;
    }
}

#ifdef _WIN32
static int link_write(const void *p, uint32_t n)
{
    DWORD done = 0;
    return WriteFile(wm.link_out, p, n, &done, NULL) && done == n;
}

static int link_read(void *p, uint32_t n)
{
    uint8_t *q = p;
    while (n > 0) {
        DWORD done = 0;
        if (!ReadFile(wm.link_in, q, n, &done, NULL) || done == 0) {
            return 0;
        }
        q += done;
        n -= done;
    }
    return 1;
}
#else
static int link_write(const void *p, uint32_t n)
{
    const uint8_t *q = p;
    while (n > 0) {
        ssize_t done = write(wm.link_out, q, n);
        if (done <= 0) {
            return 0;
        }
        q += done;
        n -= (uint32_t) done;
    }
    return 1;
}

static int link_read(void *p, uint32_t n)
{
    uint8_t *q = p;
    while (n > 0) {
        ssize_t done = read(wm.link_in, q, n);
        if (done <= 0) {
            return 0;
        }
        q += done;
        n -= (uint32_t) done;
    }
    return 1;
}
#endif

/* The exchange at the start of frame `frame`: what this console sent during the last frame
 * (and its beacon and MP turn now) goes out, the other console's comes in. Console 0 writes
 * first and reads second, console 1 the other way round, so neither waits on a full pipe. */
static void exchange(uint32_t frame)
{
    int mp_taken = 0, parent_turn = 0;
    if (wm.parent && wm.beacon.period != 0) {
        beacon_message();
    }
    if (wm.mp && wm.parent && wm.child_bitmap) {
        mp_taken = mp_outgoing(MSG_MP_PARENT);
        parent_turn = 1;
    } else if (wm.mp && wm.connected) {
        mp_taken = mp_outgoing(MSG_MP_CHILD);
    }
    /* out of range (the recording's NORADIO): the consoles stay in step, but nothing goes out
       and nothing comes in */
    int out_of_range = (input_hardware() & 4u) != 0;
    if (out_of_range) {
        wm.out_length = 0;
    }
    uint8_t head[8];
    put32(head, frame);
    put32(head + 4, wm.out_length);
    static uint8_t in[LINK_MAX];
    uint32_t in_length = 0;
    int ok = 1;
    for (int pass = 0; pass < 2 && ok; pass++) {
        if ((pass == 0) == (wm.console == 0)) {
            ok = link_write(head, sizeof(head)) && link_write(wm.out, wm.out_length);
        } else {
            uint8_t peer[8];
            ok = link_read(peer, sizeof(peer));
            in_length = ok ? get32(peer + 4) : 0;
            if (ok && (get32(peer) != frame || in_length > sizeof(in))) {
                fprintf(stderr, "wm: the link is out of step (frame %u, the other console's %u)\n", frame, get32(peer));
                ok = 0;
            }
            ok = ok && link_read(in, in_length);
        }
    }
    wm.out_length = 0;
    if (out_of_range) {
        in_length = 0;
    }
    if (!ok) {
        fprintf(stderr, "wm: the other console left the link at frame %u\n", frame);
        wm.linked = 0;
        in_length = 0;
    }
    wm.exchanges++;
    wm.peer_beacon_valid = 0;
    for (uint32_t n = 0; n + 3 <= in_length;) {
        uint32_t length = get16(in + n + 1);
        if (n + 3 + length > in_length) {
            break;
        }
        receive(in[n], in + n + 3, length);
        n += 3 + length;
    }
    /* the turn's end: what this console sent was taken, and for the parent the turn ends */
    if (wm.mp && mp_taken > 0) {
        mp_sent(mp_taken, wm.parent ? wm.child_bitmap : 1);
    }
    if (parent_turn && wm.mp) {
        wm.mp_turns++;
        mp_event(CODE_MPEND_IND, wm.recv_buf);
    }
}

/* RUN_LINK="<console>,<consoles>,<in>,<out>": this console's number, how many share the air,
 * and the pipe ends (file descriptors; on Windows, inherited handles) from the others and to
 * them (tools/run.py). */
static void link_open(void)
{
    const char *text = getenv("RUN_LINK");
    unsigned long long in = 0, out = 0;
    int console = 0, consoles = 0;
    if (text == NULL || *text == 0) {
        return;
    }
    if (sscanf(text, "%d,%d,%llu,%llu", &console, &consoles, &in, &out) != 4 || consoles != 2 || console < 0 ||
        console >= consoles) {
        fprintf(stderr, "wm: RUN_LINK is '<console>,2,<in>,<out>'; no link\n");
        return;
    }
    wm.console = console;
    wm.consoles = consoles;
#ifdef _WIN32
    wm.link_in = (HANDLE) (uintptr_t) in;
    wm.link_out = (HANDLE) (uintptr_t) out;
#else
    wm.link_in = (int) in;
    wm.link_out = (int) out;
#endif
    wm.linked = 1;
}

int wm_init(uint8_t *nvram)
{
    memset(&wm, 0, sizeof(wm));
    const char *text = getenv("RUN_WIRELESS");
    wm.on = text != NULL && atoi(text) != 0;
    if (!wm.on) {
        return 0;
    }
    wm.trace = getenv("RUN_TRACE") != NULL && strstr(getenv("RUN_TRACE"), "wm") != NULL;
    link_open();
    /* A MAC address of Nintendo's block, the last byte the console's number. */
    static const uint8_t base[6] = {0x00, 0x09, 0xbf, 0x4e, 0x57, 0x10};
    memcpy(wm.mac, base, 6);
    wm.mac[5] = (uint8_t) (base[5] + wm.console);
    for (int i = 0; i < 6; i++) {
        wr8(SHARED_MAC_ADDRESS + (uint32_t) i, wm.mac[i]);
        nvram[0x36 + i] = wm.mac[i];
    }
    wr16(SHARED_ALLOWED_CHANNEL, ALLOWED_CHANNELS);
    nvram[0x3c] = (uint8_t) ENABLED_CHANNELS;
    nvram[0x3d] = (uint8_t) (ENABLED_CHANNELS >> 8);
    return 1;
}

void wm_step(void)
{
    if (!wm.on) {
        return;
    }
    if (wm.linked && io_frame() != wm.exchanged_frame) {
        wm.exchanged_frame = io_frame();
        exchange(wm.exchanged_frame);
    }
    if (wm.scan_req && io_cycles() >= wm.scan_end) {
        scan_done();
    }
    if (wm.scan_ex_req && io_cycles() >= wm.scan_ex_end) {
        scan_ex_done();
    }
    if (wm.infra && wm.connecting && io_cycles() >= wm.connected_at) {
        wm.connecting = 0;
        wm.connected = 1;
        wm.aid = 1;
        wr16(wm.status + ST_AID, 1);
        for (int i = 0; i < 6; i++) {
            wr8(wm.status + ST_PARENT_MAC + (uint32_t) i, wm.parent_mac[i]);
        }
        wr16(wm.status + ST_LINK_LEVEL, LINK_LEVEL);
        set_state(STATE_CHILD);
        wifi_connect(io_cycles());
        connect_event(0, ERR_SUCCESS, CODE_CONNECTED, 1);
    }
    if (wm.parent && io_cycles() >= wm.next_beacon) {
        parent_event(CODE_BEACON_SENT, NULL, 0);
        wm.next_beacon += (uint64_t) (wm.beacon.period ? wm.beacon.period : 200) * CYCLES_PER_MS;
    }
    deliver();
    dcf_receive();
}

void wm_report(FILE *out)
{
    if (!wm.on) {
        return;
    }
    fprintf(out, "wm: console %d%s, %llu callbacks, %llu notifications, %llu exchanges, %llu MP turns; commands:", wm.console,
            wm.linked ? " (linked)" : "", (unsigned long long) wm.callbacks, (unsigned long long) wm.notifications,
            (unsigned long long) wm.exchanges, (unsigned long long) wm.mp_turns);
    for (int i = 0; i <= API_COUNT; i++) {
        if (wm.commands[i]) {
            fprintf(out, " %d:%llu", i, (unsigned long long) wm.commands[i]);
        }
    }
    fprintf(out, "\n");
    if (wm.dcf_sent || wm.dcf_received) {
        fprintf(out, "wm: DCF %llu frames sent, %llu received\n", (unsigned long long) wm.dcf_sent,
                (unsigned long long) wm.dcf_received);
    }
    wifi_report(out);
}
