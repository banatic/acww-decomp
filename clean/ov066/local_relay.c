/* The data relay (local_relay.h). */
#include "local_relay.h"

#include <assert.h>
#include <stddef.h>
#include <stdint.h>

#include "clean.h"
#include "local_mp.h"
#include "local_session.h"
#include "local_wireless.h"

static_assert(sizeof(LocalRelayParams) == 8, "the parameters");
static_assert(sizeof(LocalRelayHeader) == 4, "a relay packet's head");
static_assert(offsetof(LocalRelayNode, size) == 0x08, "node size");
static_assert(offsetof(LocalRelayNode, pending) == 0x0a, "node pending");
static_assert(offsetof(LocalRelayNode, acked) == 0x0c, "node acked");
static_assert(offsetof(LocalRelayNode, header) == 0x20, "node packet");
static_assert(offsetof(LocalRelayNode, data) == 0x24, "node slices");
static_assert(sizeof(LocalRelayFragment) == LOCAL_FRAGMENT_FIRST_HEAD, "a first fragment's head");
static_assert(sizeof(LocalRelaySlot) == 0x10, "a receive slot");
static_assert(offsetof(LocalRelay, flags) == 0x04, "relay flags");
static_assert(offsetof(LocalRelay, packets) == 0x08, "relay packets");
static_assert(offsetof(LocalRelay, per_aid) == 0x18, "relay per AID");
static_assert(offsetof(LocalRelay, receiving) == 0x1c, "relay receiving");
static_assert(offsetof(LocalRelay, block) == 0x20, "relay block");
static_assert(offsetof(LocalRelay, on_block_sent) == 0x2c, "relay block handler");
static_assert(offsetof(LocalRelay, slots) == 0x30, "relay slots");
static_assert(sizeof(LocalRelay) == 0x34, "the size LocalRelay_Start allocates");
static_assert(offsetof(LocalPortEvent, state) == 0x04, "WMPortRecvCallback.state");
static_assert(offsetof(LocalPortEvent, data) == 0x0c, "WMPortRecvCallback.data");
static_assert(offsetof(LocalPortEvent, aid) == 0x12, "WMPortRecvCallback.aid");
static_assert(offsetof(LocalPortSent, data) == 0x14, "WMPortSendCallback.data");
static_assert(offsetof(LocalPortSent, callback) == 0x20, "WMPortSendCallback.arg");
static_assert(offsetof(LocalControl, max_players) == 0x0b, "players");
static_assert(offsetof(LocalControl, beacons_per_turn) == 0x14, "beacons per turn");
static_assert(offsetof(LocalControl, unk_24) == 0x24, "unk_24");
static_assert(offsetof(LocalSession, unk_a8) == 0xa8, "relay shutdown");

extern LocalControl *data_ov066_0226bdec;
extern LocalSession *data_ov066_0226bdf4;
/* The relay, NULL outside LocalRelay_Start and LocalRelay_Shutdown. */
extern LocalRelay *data_ov066_0226be08;

/* The game's symbols of the functions below that are handed to WM and to the session. */
extern u32 func_ov066_0226a960(void);
extern void func_ov066_0226aab8(void *event);
extern void func_ov066_0226adcc(void *result);
extern void func_ov066_0226ae1c(void *buffer, u32 size, u32 to, void (*on_sent)(void *));
extern void func_ov066_0226aeb8(int aid);
extern void func_ov066_0226af04(void);
extern void func_ov066_0226af3c(void);
extern void func_ov066_0226b71c(void *result);
extern void func_ov066_0226b738(void *result);
extern int func_ov066_0226b81c(const void *buffer, u32 size, int to, void (*on_sent)(void *));
extern int func_ov066_0226b8bc(void);
extern void func_ov066_0226b90c(void);
extern void func_ov066_0226b818(void *indication);
/* LocalMp_OnReceive, the receive callback of the library's messages. */
extern void func_ov066_0226923c(void *received);

extern int WM_SetMPDataToPortEx(void (*callback)(void *), void *argument, const void *data, u16 size, u16 to, u16 port,
                                u16 priority);
extern int WM_SetPortCallback(u16 port, void (*callback)(void *), void *argument);
extern int WM_SetIndCallback(void (*callback)(void *));
extern u32 OS_DisableInterrupts(void);
extern u32 OS_RestoreInterrupts(u32 state);
extern void OS_Terminate(void);
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
extern void MI_CpuFill8(void *dst, u8 value, u32 size);

/* 1 << n as ARM shifts: by the low byte of the count, 0 from 32 on. */
static u32 arm_bit(u32 n)
{
    n &= 0xff;
    return n < 32 ? 1u << n : 0;
}

/* func_ov066_0226a8c4: `buffer` of `capacity` bytes set as the receive buffer of the blocks of
 * `aid`, with the interrupts disabled; FALSE without a relay or a session, for an AID past
 * the players, or while a block of that AID is being received.
 * REQUIRES: aid is not negative. */
int LocalRelay_SetReceiveBuffer(int aid, void *buffer, u32 capacity)
{
    int done = FALSE;
    u32 interrupts = OS_DisableInterrupts();
    LocalRelay *relay = data_ov066_0226be08;
    if (relay != NULL && relay->slots != NULL && data_ov066_0226bdf4 != NULL && aid < data_ov066_0226bdec->max_players &&
        (relay->receiving & arm_bit((u32) aid)) == 0) {
        relay->slots[aid].buffer = buffer;
        relay->slots[aid].capacity = capacity;
        done = TRUE;
    }
    OS_RestoreInterrupts(interrupts);
    return done;
}
CLEAN_AS(func_ov066_0226a8c4, LocalRelay_SetReceiveBuffer)

/* func_ov066_0226a960: the session's MP start handler: with the interrupts disabled, the relay
 * starts over, its rings cleared, every AID collecting into the first node, the next relay
 * packet taken whatever its number, and no block sent or received.
 * QUIRK: LOCAL_RELAY_LAST_OUT is left as it is. Returns OS_RestoreInterrupts's result. */
u32 LocalRelay_Reset(void)
{
    u32 interrupts = OS_DisableInterrupts();
    data_ov066_0226be08->cursor = data_ov066_0226be08->packets;
    LocalRelay_ClearRing(data_ov066_0226be08->packets, LOCAL_RELAY_RING);
    LocalRelay_ClearRing(data_ov066_0226be08->collected, LOCAL_RELAY_RING);
    for (u16 i = 0; i < data_ov066_0226bdec->max_players; i++) {
        data_ov066_0226be08->per_aid[i] = data_ov066_0226be08->collected;
    }
    data_ov066_0226be08->sequence &= ~0x0f;
    data_ov066_0226be08->sequence &= ~0xf0;
    data_ov066_0226be08->in_flight = 0;
    data_ov066_0226be08->own_pending = 0;
    data_ov066_0226be08->flags |= LOCAL_RELAY_RESYNC;
    data_ov066_0226be08->flags &= ~LOCAL_RELAY_GAP;
    data_ov066_0226be08->flags &= ~LOCAL_RELAY_ASK_RESEND;
    data_ov066_0226be08->flags &= ~LOCAL_RELAY_SENDING;
    data_ov066_0226be08->resend = NULL;
    data_ov066_0226be08->receiving = 0;
    data_ov066_0226be08->block_to = 0;
    data_ov066_0226be08->block = NULL;
    data_ov066_0226be08->block_size = 0;
    data_ov066_0226be08->block_sent = 0xffffffff;
    data_ov066_0226be08->on_block_sent = NULL;
    return OS_RestoreInterrupts(interrupts);
}
CLEAN_AS(func_ov066_0226a960, LocalRelay_Reset)

/* func_ov066_0226aab8: the receive callback of WM's port 13: unless a reset takes over or WM
 * reports an error, data received is taken; a disconnection goes to
 * LocalRelay_OnPeerDisconnected. */
void LocalRelay_OnPortReceive(LocalPortEvent *event)
{
    if (LocalWireless_CheckReset()) {
        return;
    }
    if (event->base.result != LOCAL_WM_RESULT_SUCCESS) {
        return;
    }
    switch (event->state) {
        case LOCAL_WM_STATE_CONNECTED:
            return;
        case LOCAL_WM_STATE_DISCONNECTED:
            LocalRelay_OnPeerDisconnected(event);
            return;
        case LOCAL_WM_STATE_PORT_RECV:
            LocalRelay_OnData(event);
            return;
    }
}
CLEAN_AS(func_ov066_0226aab8, LocalRelay_OnPortReceive)

/* func_ov066_0226ab24: a disconnection on port 13: nothing to do (LocalRelay_ForgetPeer does
 * it when the session learns of it). */
void LocalRelay_OnPeerDisconnected(LocalPortEvent *event)
{
    (void) event;
}
CLEAN_AS(func_ov066_0226ab24, LocalRelay_OnPeerDisconnected)

/* func_ov066_0226ab28: a packet received on port 13. From a child it is the parent's
 * (LocalRelay_OnChildPacket); from the parent it is a relay packet. A child takes the one that
 * follows its last (or any after a reset): its number queued to be acknowledged and its
 * slices delivered. For a gap of one it asks for the missed packet again; after a larger gap
 * it holds its own fragment for the turn. */
void LocalRelay_OnData(LocalPortEvent *event)
{
    if (event->length == 0) {
        return;
    }
    if (event->aid != 0) {
        LocalRelay_OnChildPacket(event->aid, event->data, event->length);
        return;
    }
    u8 *packet = event->data;
    LocalRelay *relay = data_ov066_0226be08;
    u8 flags = relay->flags;
    u8 last = relay->sequence & 0x0f;
    if ((flags & LOCAL_RELAY_RESYNC) || packet[0] == ((last + 1) & 0x0f)) {
        LocalRelayNode *queued = relay->per_aid[0];
        queued->header.seq = packet[0];
        data_ov066_0226be08->per_aid[0] = queued->next;
        LocalRelay_Deliver((LocalRelayHeader *) packet);
        data_ov066_0226be08->flags &= ~LOCAL_RELAY_RESYNC;
        data_ov066_0226be08->flags &= ~LOCAL_RELAY_ASK_RESEND;
        data_ov066_0226be08->sequence = (u8) ((data_ov066_0226be08->sequence & 0xf0) | (packet[0] & 0x0f));
        return;
    }
    if (packet[0] != ((last + 2) & 0x0f)) {
        relay->flags = flags | LOCAL_RELAY_GAP;
        return;
    }
    relay->flags = flags | LOCAL_RELAY_ASK_RESEND;
    u8 sequence = data_ov066_0226be08->sequence;
    data_ov066_0226be08->sequence = (u8) ((sequence & 0x0f) | (((sequence + 1) & 0x0f) << 4));
}
CLEAN_AS(func_ov066_0226ab28, LocalRelay_OnData)

/* func_ov066_0226ac68: as the parent, `length` bytes of `packet` from the child `aid`. An
 * acknowledgement marks the relay packet it names as received by that child; a request to
 * send one again starts the resending from it (unless one is under way); a fragment is
 * collected in the child's slice of its next collecting node. */
void LocalRelay_OnChildPacket(int aid, u8 *packet, int length)
{
    u8 head[2];
    MI_CpuCopy8(packet, head, sizeof(head));
    if (head[0] & LOCAL_FRAGMENT_ACK) {
        LocalRelayNode *acked = LocalRelay_FindPacket(head[0] >> 4, data_ov066_0226be08->cursor);
        if (acked != NULL) {
            acked->acked |= (u16) (acked->pending & arm_bit((u32) aid));
        }
    }
    u8 kind = head[0] & LOCAL_FRAGMENT_KIND;
    if (kind == LOCAL_FRAGMENT_RESEND) {
        if (data_ov066_0226be08->resend != NULL) {
            return;
        }
        LocalRelayNode *asked = LocalRelay_FindPacket(head[0] >> 4, data_ov066_0226be08->cursor);
        if (asked != NULL) {
            data_ov066_0226be08->resend = asked;
        }
        return;
    }
    if (kind == LOCAL_FRAGMENT_ACK_ONLY) {
        return;
    }
    LocalRelayNode *collecting = data_ov066_0226be08->per_aid[aid];
    MI_CpuCopy8(packet, collecting->data + aid * data_ov066_0226be08->slice_size, (u32) length);
    collecting->header.slices |= (u16) arm_bit((u32) aid);
    data_ov066_0226be08->per_aid[aid] = collecting->next;
}
CLEAN_AS(func_ov066_0226ac68, LocalRelay_OnChildPacket)

/* func_ov066_0226ad9c: the relay packet numbered `seq` among those before `cursor`, newest
 * first; NULL when none is. */
LocalRelayNode *LocalRelay_FindPacket(u8 seq, LocalRelayNode *cursor)
{
    for (LocalRelayNode *node = cursor->prev; node != cursor; node = node->prev) {
        if (node->header.seq == seq) {
            return node;
        }
    }
    return NULL;
}
CLEAN_AS(func_ov066_0226ad9c, LocalRelay_FindPacket)

/* func_ov066_0226adcc: WM_SetMPDataToPortEx's callback: the sender's callback, if any, is
 * called with WM's result.
 * QUIRK: a failed send stops the library on WM's error and then the game (OS_Terminate). */
void LocalRelay_OnPortSent(LocalPortSent *result)
{
    if (result->base.result == LOCAL_WM_RESULT_SUCCESS) {
        if (result->callback != NULL) {
            result->callback(result);
        }
        return;
    }
    LocalWireless_Fail(result->base.result);
    OS_Terminate();
}
CLEAN_AS(func_ov066_0226adcc, LocalRelay_OnPortSent)

/* func_ov066_0226ae1c: the session's message sender: `size` bytes of `buffer` to the AIDs `to`
 * on WM's port 12, `on_sent` called with WM's result once sent. */
void LocalRelay_SendMessage(void *buffer, u32 size, u32 to, void (*on_sent)(void *))
{
    LocalRelay_SendToPort(LOCAL_PORT_MESSAGES, buffer, size, to, on_sent);
}
CLEAN_AS(func_ov066_0226ae1c, LocalRelay_SendMessage)

/* func_ov066_0226ae50: `size` bytes of `data` handed to WM for the AIDs `to` on `port`
 * (WM_SetMPDataToPortEx), `callback` called through LocalRelay_OnPortSent once sent; TRUE
 * when WM took them (or there is no child), otherwise the library stops on WM's error. */
int LocalRelay_SendToPort(int port, const void *data, u32 size, u32 to, void (*callback)(void *))
{
    int status = WM_SetMPDataToPortEx(func_ov066_0226adcc, (void *) (uintptr_t) callback, data, (u16) size, (u16) to,
                                      (u16) port, LOCAL_RELAY_PRIORITY);
    if (status != LOCAL_WM_RESULT_OPERATING && status != LOCAL_WM_RESULT_NO_CHILD) {
        LocalWireless_Fail(status);
        return FALSE;
    }
    return TRUE;
}
CLEAN_AS(func_ov066_0226ae50, LocalRelay_SendToPort)

/* func_ov066_0226aeb8: the session's handler of a child gone: no relay packet waits for its
 * acknowledgement any more. */
void LocalRelay_ForgetPeer(int aid)
{
    u16 keep = (u16) ~arm_bit((u32) aid);
    LocalRelayNode *cursor = data_ov066_0226be08->cursor;
    LocalRelayNode *node = cursor;
    do {
        node->pending &= keep;
        node->acked &= keep;
        node = node->prev;
    } while (node != cursor);
}
CLEAN_AS(func_ov066_0226aeb8, LocalRelay_ForgetPeer)

/* func_ov066_0226af04: the session's MP acknowledgement handler (a child's): its next packet
 * sent, unless two are still being sent. */
void LocalRelay_OnMpAck(void)
{
    if (data_ov066_0226be08->in_flight >= 2) {
        return;
    }
    LocalRelay_SendFromChild();
}
CLEAN_AS(func_ov066_0226af04, LocalRelay_OnMpAck)

/* func_ov066_0226af3c: the session's MP end handler (the parent's), unless a relay packet is
 * still being sent. A packet asked again is sent first, the resending going on to the newest.
 * Otherwise, once the packet sent two before is acknowledged by all (or waited for no one),
 * the parent's own fragment joins the first collecting node and, if any slice was collected,
 * a new relay packet is built at the cursor. A packet is sent to the children that are to
 * acknowledge it, when there is one. */
void LocalRelay_OnMpEnd(void)
{
    LocalRelay *relay = data_ov066_0226be08;
    if (relay->in_flight >= 1) {
        return;
    }
    LocalRelayNode *own = relay->per_aid[0];
    LocalRelayNode *send = NULL;
    if (relay->resend != NULL) {
        send = relay->resend;
        relay->resend = send->next == relay->cursor ? NULL : send->next;
    } else {
        LocalRelayNode *oldest = relay->cursor->prev->prev;
        if (oldest->pending == 0 || oldest->pending == oldest->acked) {
            if (relay->flags & LOCAL_RELAY_SENDING) {
                LocalRelay_AddOwnFragment(own);
                own->header.slices |= 1;
                data_ov066_0226be08->own_pending = (s8) (data_ov066_0226be08->own_pending + 1);
            }
            if (LocalRelay_Collect(data_ov066_0226be08->cursor, own)) {
                send = data_ov066_0226be08->cursor;
                data_ov066_0226be08->cursor = send->next;
            }
        }
    }
    if (send == NULL || send->pending == 0) {
        return;
    }
    data_ov066_0226be08->in_flight = (s8) (data_ov066_0226be08->in_flight + 1);
    LocalRelay_SendToPort(LOCAL_PORT_RELAY, &send->header, send->size, send->pending, func_ov066_0226b71c);
}
CLEAN_AS(func_ov066_0226af3c, LocalRelay_OnMpEnd)

/* func_ov066_0226b088: the relay packet `relay` built from the slices collected in
 * `collected`, packed in AID order after a header with the next sequence number; the AIDs
 * still collecting into that node move on, the node is emptied, and the packet waits for the
 * acknowledgement of every child that greeted the parent. The parent then delivers it to
 * itself. FALSE, with nothing done, when no slice was collected. */
int LocalRelay_Collect(LocalRelayNode *relay, LocalRelayNode *collected)
{
    u16 slices = collected->header.slices;
    if (slices == 0) {
        return FALSE;
    }
    u8 slice_size = data_ov066_0226be08->slice_size;
    const u8 *from = collected->data;
    u8 *to = relay->data;
    u16 size = sizeof(LocalRelayHeader);
    relay->header.slices = slices;
    u8 sequence = data_ov066_0226be08->sequence;
    data_ov066_0226be08->sequence = (u8) ((sequence & 0xf0) | ((sequence + 1) & 0x0f));
    relay->header.seq = sequence & 0x0f;
    for (u16 i = 0; i < data_ov066_0226bdec->max_players; i++) {
        if (slices & arm_bit(i)) {
            MI_CpuCopy8(from + slice_size * i, to, slice_size);
            to += slice_size;
            size = (u16) (size + slice_size);
        }
        if (data_ov066_0226be08->per_aid[i] == collected) {
            data_ov066_0226be08->per_aid[i] = collected->next;
        }
    }
    collected->header.slices = 0;
    relay->pending = data_ov066_0226bdf4->greeted;
    relay->acked = 0;
    relay->size = size;
    LocalRelay_Deliver(&relay->header);
    return TRUE;
}
CLEAN_AS(func_ov066_0226b088, LocalRelay_Collect)

/* func_ov066_0226b1d0: each slice of the relay packet `relay` taken as a fragment from its
 * AID; a slice of this DS's own is no longer pending.
 * QUIRK: the slices are stepped by slice_size rounded down to even, while LocalRelay_Collect
 * packs them by slice_size. */
void LocalRelay_Deliver(LocalRelayHeader *relay)
{
    u8 *slice = (u8 *) (relay + 1);
    for (u16 i = 0; i < data_ov066_0226bdec->max_players; i++) {
        if ((relay->slices & arm_bit(i)) == 0) {
            continue;
        }
        if (i == LocalMp_GetAid()) {
            data_ov066_0226be08->own_pending = (s8) (data_ov066_0226be08->own_pending - 1);
        }
        LocalRelay_ReceiveFragment(i, slice);
        slice += data_ov066_0226be08->slice_size & ~1;
    }
}
CLEAN_AS(func_ov066_0226b1d0, LocalRelay_Deliver)

/* func_ov066_0226b27c: a fragment from `aid`. The first fragment of a block for this DS starts
 * receiving one of its size; its data, and those of the later fragments, are added to the
 * AID's receive buffer while they fit. Once the block is complete it goes to the session's
 * receive handler, if there is one.
 * QUIRK: only the first fragment's own data are capped to the slice; a block's data that do not
 * fit the buffer are dropped, so it never completes.
 * REQUIRES: the fragment is FIRST or NEXT (LocalRelay_Deliver's slices are). The ROM leaves its
 * data pointer unset for the others: from LocalRelay_Deliver it holds the fragment's address,
 * as here. */
void LocalRelay_ReceiveFragment(int aid, u8 *fragment)
{
    LocalRelaySlot *slot = &data_ov066_0226be08->slots[aid];
    const u8 *data = fragment;
    u32 length = 0;
    switch (fragment[0] & LOCAL_FRAGMENT_KIND) {
        case LOCAL_FRAGMENT_FIRST: {
            LocalRelayFragment *first = (LocalRelayFragment *) fragment;
            data = fragment + LOCAL_FRAGMENT_FIRST_HEAD;
            if ((first->to & arm_bit((u32) LocalMp_GetAid())) == 0) {
                break;
            }
            data_ov066_0226be08->receiving |= (u16) arm_bit((u32) aid);
            slot->received = 0;
            slot->expected = (u32) first->size_low | (u32) first->size_high << 16;
            length = slot->expected;
            u32 room = (u32) (data_ov066_0226be08->slice_size - LOCAL_FRAGMENT_FIRST_HEAD);
            if (length > room) {
                length = room;
            }
            break;
        }
        case LOCAL_FRAGMENT_NEXT:
            length = fragment[1];
            data = fragment + LOCAL_FRAGMENT_NEXT_HEAD;
            break;
    }
    u32 bit = arm_bit((u32) aid);
    if ((data_ov066_0226be08->receiving & bit) == 0) {
        return;
    }
    if (slot->received + length <= slot->capacity) {
        MI_CpuCopy8(data, slot->buffer + slot->received, length);
        slot->received += length;
    }
    if (slot->expected != slot->received) {
        return;
    }
    data_ov066_0226be08->receiving ^= (u16) bit;
    if (data_ov066_0226bdf4->on_received != NULL) {
        data_ov066_0226bdf4->on_received(aid, (char *) slot->buffer, slot->expected);
    }
}
CLEAN_AS(func_ov066_0226b27c, LocalRelay_ReceiveFragment)

/* func_ov066_0226b3d0: a child's packet to the parent, at the cursor of its packets: a request
 * for the relay packet it missed, or else the next fragment of its block (unless two are
 * pending, the last is out or it saw a gap this turn). The oldest relay packet it has not
 * acknowledged yet is acknowledged in it, as an acknowledgement alone when there is nothing
 * else. A packet is sent to the parent and the cursor moves on; the gap is then forgotten. */
void LocalRelay_SendFromChild(void)
{
    LocalRelay *relay = data_ov066_0226be08;
    u8 flags = relay->flags;
    u8 *packet = &relay->cursor->header.seq;
    u16 size = 0;
    if (flags & LOCAL_RELAY_ASK_RESEND) {
        packet[0] = (u8) ((packet[0] & ~LOCAL_FRAGMENT_KIND) | LOCAL_FRAGMENT_RESEND);
        size = LOCAL_FRAGMENT_NEXT_HEAD;
        packet[0] = (u8) ((packet[0] & 0x0f) | (data_ov066_0226be08->sequence & 0xf0));
    } else if ((flags & LOCAL_RELAY_SENDING) && relay->own_pending < 2 && (flags & LOCAL_RELAY_LAST_OUT) == 0 &&
               (flags & LOCAL_RELAY_GAP) == 0) {
        size = LocalRelay_NextFragment(packet);
        data_ov066_0226be08->own_pending = (s8) (data_ov066_0226be08->own_pending + 1);
    }
    LocalRelayNode **queue = data_ov066_0226be08->per_aid;
    if (queue[0] != queue[1]) {
        if (size == 0) {
            packet[0] = (u8) ((packet[0] & ~LOCAL_FRAGMENT_KIND) | LOCAL_FRAGMENT_ACK_ONLY);
            size = LOCAL_FRAGMENT_NEXT_HEAD;
            packet[0] &= (u8) ~LOCAL_FRAGMENT_LAST;
        }
        packet[0] |= LOCAL_FRAGMENT_ACK;
        queue = data_ov066_0226be08->per_aid;
        packet[0] = (u8) ((packet[0] & 0x0f) | ((queue[1]->header.seq & 0x0f) << 4));
        queue = data_ov066_0226be08->per_aid;
        queue[1] = queue[1]->next;
    } else {
        packet[0] &= (u8) ~LOCAL_FRAGMENT_ACK;
    }
    if (size != 0) {
        data_ov066_0226be08->in_flight = (s8) (data_ov066_0226be08->in_flight + 1);
        LocalRelay_SendToPort(LOCAL_PORT_RELAY, packet, size, LOCAL_AIDS_PARENT, func_ov066_0226b738);
        data_ov066_0226be08->cursor = data_ov066_0226be08->cursor->next;
    }
    data_ov066_0226be08->flags &= ~LOCAL_RELAY_GAP;
}
CLEAN_AS(func_ov066_0226b3d0, LocalRelay_SendFromChild)

/* func_ov066_0226b594: the parent's own fragment cut into its slice of the collecting node
 * `collected`; the block is finished when that was its last. */
void LocalRelay_AddOwnFragment(LocalRelayNode *collected)
{
    LocalRelay_NextFragment(collected->data);
    if ((collected->data[0] & LOCAL_FRAGMENT_LAST) == 0) {
        return;
    }
    LocalRelay_FinishBlock();
}
CLEAN_AS(func_ov066_0226b594, LocalRelay_AddOwnFragment)

/* func_ov066_0226b5c4: the next fragment of the block being sent written at `fragment`: the
 * first with the block's AIDs and size, as much data as fits the slice after its head, marked
 * LAST when it ends the block. Returns the packet's size, the head included, rounded up to
 * even. */
u16 LocalRelay_NextFragment(u8 *fragment)
{
    LocalRelay *relay = data_ov066_0226be08;
    u32 sent = relay->block_sent;
    u32 rest = relay->block_size - sent;
    const u8 *from = relay->block + sent;
    u8 *to;
    u8 length;
    u16 size;
    if (sent == 0) {
        LocalRelayFragment *first = (LocalRelayFragment *) fragment;
        fragment[0] = (u8) ((fragment[0] & ~LOCAL_FRAGMENT_KIND) | LOCAL_FRAGMENT_FIRST);
        to = fragment + LOCAL_FRAGMENT_FIRST_HEAD;
        first->to = data_ov066_0226be08->block_to;
        first->size_low = (u16) data_ov066_0226be08->block_size;
        first->size_high = (u16) (data_ov066_0226be08->block_size >> 16);
        u32 room = (u32) (data_ov066_0226be08->slice_size - LOCAL_FRAGMENT_FIRST_HEAD);
        u32 count = data_ov066_0226be08->block_size;
        if (count > room) {
            count = room;
        }
        length = (u8) count;
        size = (u16) ((length + LOCAL_FRAGMENT_FIRST_HEAD + 1) & ~1);
    } else {
        fragment[0] = (u8) ((fragment[0] & ~LOCAL_FRAGMENT_KIND) | LOCAL_FRAGMENT_NEXT);
        to = fragment + LOCAL_FRAGMENT_NEXT_HEAD;
        u32 room = (u32) (data_ov066_0226be08->slice_size - LOCAL_FRAGMENT_NEXT_HEAD);
        if (rest > room) {
            rest = room;
        }
        length = (u8) rest;
        size = (u16) ((length + LOCAL_FRAGMENT_NEXT_HEAD + 1) & ~1);
    }
    data_ov066_0226be08->block_sent += length;
    fragment[1] = length;
    int last = data_ov066_0226be08->block_sent == data_ov066_0226be08->block_size;
    fragment[0] = (u8) ((fragment[0] & ~LOCAL_FRAGMENT_LAST) | (last ? LOCAL_FRAGMENT_LAST : 0));
    u8 flags = data_ov066_0226be08->flags & (u8) ~LOCAL_RELAY_LAST_OUT;
    data_ov066_0226be08->flags = (u8) (flags | ((fragment[0] & LOCAL_FRAGMENT_LAST) ? LOCAL_RELAY_LAST_OUT : 0));
    MI_CpuCopy8(from, to, length);
    return size;
}
CLEAN_AS(func_ov066_0226b5c4, LocalRelay_NextFragment)

/* func_ov066_0226b71c: the parent's relay packet sent (LocalRelay_OnPortSent). */
void LocalRelay_OnRelaySent(void)
{
    data_ov066_0226be08->in_flight = (s8) (data_ov066_0226be08->in_flight - 1);
}
CLEAN_AS(func_ov066_0226b71c, LocalRelay_OnRelaySent)

/* func_ov066_0226b738: a child's packet sent (LocalRelay_OnPortSent): a fragment that ended
 * its block loses that mark and the block is finished. */
void LocalRelay_OnChildPacketSent(LocalPortSent *result)
{
    u8 *packet = result->data;
    data_ov066_0226be08->in_flight = (s8) (data_ov066_0226be08->in_flight - 1);
    u8 kind = packet[0] & LOCAL_FRAGMENT_KIND;
    if (kind != LOCAL_FRAGMENT_FIRST && kind != LOCAL_FRAGMENT_NEXT) {
        return;
    }
    if ((packet[0] & LOCAL_FRAGMENT_LAST) == 0) {
        return;
    }
    packet[0] &= (u8) ~LOCAL_FRAGMENT_LAST;
    LocalRelay_FinishBlock();
}
CLEAN_AS(func_ov066_0226b738, LocalRelay_OnChildPacketSent)

/* func_ov066_0226b7ac: the block sent: the relay free for the next, and the block's handler,
 * if any, called.
 * QUIRK: the handler is given the block's size as its argument. */
void LocalRelay_FinishBlock(void)
{
    LocalRelay *relay = data_ov066_0226be08;
    void (*on_sent)(void *) = relay->on_block_sent;
    u32 size = relay->block_size;
    relay->flags &= ~LOCAL_RELAY_SENDING;
    data_ov066_0226be08->block_to = 0;
    data_ov066_0226be08->block = NULL;
    data_ov066_0226be08->block_size = 0;
    data_ov066_0226be08->block_sent = 0xffffffff;
    data_ov066_0226be08->on_block_sent = NULL;
    if (on_sent != NULL) {
        on_sent((void *) (uintptr_t) size);
    }
}
CLEAN_AS(func_ov066_0226b7ac, LocalRelay_FinishBlock)

/* func_ov066_0226b818: WM's indication callback: nothing to do. */
void LocalRelay_OnIndication(void) {}
CLEAN_AS(func_ov066_0226b818, LocalRelay_OnIndication)

/* func_ov066_0226b81c: the session's data sender: `size` bytes of `buffer` to be sent to the
 * AIDs `to`, `on_sent` called once they are; with the interrupts disabled. FALSE when the relay
 * cannot take a block now (LocalRelay_CanSend). */
int LocalRelay_SendBlock(const void *buffer, u32 size, int to, void (*on_sent)(void *))
{
    int taken = FALSE;
    u32 interrupts = OS_DisableInterrupts();
    if (LocalRelay_CanSend()) {
        taken = TRUE;
        data_ov066_0226be08->flags |= LOCAL_RELAY_SENDING;
        data_ov066_0226be08->flags &= ~LOCAL_RELAY_LAST_OUT;
        data_ov066_0226be08->block = buffer;
        data_ov066_0226be08->block_size = size;
        data_ov066_0226be08->block_sent = 0;
        data_ov066_0226be08->block_to = (u16) to;
        data_ov066_0226be08->on_block_sent = on_sent;
    }
    OS_RestoreInterrupts(interrupts);
    return taken;
}
CLEAN_AS(func_ov066_0226b81c, LocalRelay_SendBlock)

/* func_ov066_0226b8bc: the session's answer to whether a block can be sent: a relay, a parent
 * or child communicating, and no block being sent. */
int LocalRelay_CanSend(void)
{
    LocalRelay *relay = data_ov066_0226be08;
    if (relay == NULL) {
        return FALSE;
    }
    u32 state = data_ov066_0226bdec->state;
    if (state != LOCAL_STATE_PARENT && state != LOCAL_STATE_CHILD) {
        return FALSE;
    }
    return (relay->flags & LOCAL_RELAY_SENDING) == 0;
}
CLEAN_AS(func_ov066_0226b8bc, LocalRelay_CanSend)

/* func_ov066_0226b90c: the relay ended, if there is one: the receive callbacks of ports 12 and
 * 13 removed, its buffers and itself freed, then the session (LocalSession_Destroy). */
void LocalRelay_Shutdown(void)
{
    if (data_ov066_0226be08 == NULL) {
        return;
    }
    WM_SetPortCallback(LOCAL_PORT_MESSAGES, NULL, NULL);
    WM_SetPortCallback(LOCAL_PORT_RELAY, NULL, NULL);
    LocalWireless_Free(data_ov066_0226be08->per_aid);
    LocalWireless_Free(data_ov066_0226be08->collected);
    LocalWireless_Free(data_ov066_0226be08->packets);
    LocalWireless_Free(data_ov066_0226be08->slots);
    LocalWireless_Free(data_ov066_0226be08);
    LocalSession_Destroy();
    data_ov066_0226be08 = NULL;
}
CLEAN_AS(func_ov066_0226b90c, LocalRelay_Shutdown)

/* func_ov066_0226b9b8: the relay started with `params`, unless there is one: the control block
 * configured, the session created, the relay's functions set as the session's handlers, the
 * relay allocated with its receive slots, rings and per-AID nodes, WM's receive callbacks of
 * ports 12 and 13 and its indication callback set, and the relay reset. Returns what
 * LocalRelay_Reset does.
 * QUIRK: with a relay already, returns the address `params`.
 * REQUIRES: the allocations succeed. */
int LocalRelay_Start(LocalRelayParams *params)
{
    if (data_ov066_0226be08 != NULL) {
        return (int) (uintptr_t) params;
    }
    LocalRelay_Configure(params);
    LocalSession_Create();
    data_ov066_0226bdf4->on_mp_start = func_ov066_0226a960;
    data_ov066_0226bdf4->on_mp_end = func_ov066_0226af3c;
    data_ov066_0226bdf4->on_mp_ack = func_ov066_0226af04;
    data_ov066_0226bdf4->send_message = func_ov066_0226ae1c;
    data_ov066_0226bdf4->send = func_ov066_0226b81c;
    data_ov066_0226bdf4->can_send = func_ov066_0226b8bc;
    data_ov066_0226bdf4->unk_a8 = func_ov066_0226b90c;
    data_ov066_0226bdf4->on_peer_left = func_ov066_0226aeb8;

    data_ov066_0226be08 = LocalWireless_Alloc(sizeof(LocalRelay), 4);
    u32 size = (u32) data_ov066_0226bdec->max_players * sizeof(LocalRelaySlot);
    data_ov066_0226be08->slots = LocalWireless_Alloc((int) size, 4);
    MI_CpuFill8(data_ov066_0226be08->slots, 0, size);
    data_ov066_0226be08->packets = LocalRelay_CreateRing(LOCAL_RELAY_RING);
    data_ov066_0226be08->collected = LocalRelay_CreateRing(LOCAL_RELAY_RING);
    size = (u32) data_ov066_0226bdec->max_players * sizeof(LocalRelayNode *);
    data_ov066_0226be08->per_aid = LocalWireless_Alloc((int) size, 4);
    MI_CpuFill8(data_ov066_0226be08->per_aid, 0, size);
    data_ov066_0226be08->slice_size = params->slice_size;

    WM_SetPortCallback(LOCAL_PORT_MESSAGES, func_ov066_0226923c, NULL);
    WM_SetPortCallback(LOCAL_PORT_RELAY, func_ov066_0226aab8, NULL);
    WM_SetIndCallback(func_ov066_0226b818);
    return (int) LocalRelay_Reset();
}
CLEAN_AS(func_ov066_0226b9b8, LocalRelay_Start)

/* func_ov066_0226bb7c: `count` nodes from `node` on emptied (size and acknowledgements). */
void LocalRelay_ClearRing(LocalRelayNode *node, int count)
{
    for (u16 i = 0; i < count; i++) {
        node->size = 0;
        node->pending = 0;
        node->acked = 0;
        node = node->next;
    }
}
CLEAN_AS(func_ov066_0226bb7c, LocalRelay_ClearRing)

/* func_ov066_0226bbb4: a ring of `count` nodes allocated in one zeroed block (aligned to the
 * cache's 32 bytes), each large enough for its header and a relay packet of the parent's
 * maximum size, rounded up to 32 bytes; the nodes numbered 0 on (header.seq) and linked both
 * ways. Returns the first.
 * REQUIRES: the allocation succeeds and count is at least 1. */
LocalRelayNode *LocalRelay_CreateRing(int count)
{
    u32 stride = (data_ov066_0226bdec->parent_max_size + 0x43) & ~0x1fu;
    u32 size = stride * (u32) count;
    LocalRelayNode *first = LocalWireless_Alloc((int) size, 0x20);
    MI_CpuFill8(first, 0, size);
    LocalRelayNode *node = first;
    int last = count - 1;
    for (u16 i = 0; i < last; i++) {
        node->header.seq = (u8) i;
        node->next = (LocalRelayNode *) ((u8 *) node + stride);
        LocalRelayNode *previous = node;
        node = node->next;
        node->prev = previous;
    }
    node->header.seq = (u8) last;
    node->next = first;
    first->prev = node;
    return first;
}
CLEAN_AS(func_ov066_0226bbb4, LocalRelay_CreateRing)

/* func_ov066_0226bc4c: the control block configured for the relay from `params`: its game group
 * id, the parents filtered by it, the search index and the kind; WM's single-packet mode and
 * fatal errors ignored; the parent's channel measured once, one search index; the players and
 * children; and the MP sizes from the slice: a child sends one slice, the parent the header
 * and a slice for every player. Search and scan times and four beacons per turn follow. */
void LocalRelay_Configure(LocalRelayParams *params)
{
    u16 slice = params->slice_size;
    u16 packet = (u16) (slice * params->players + sizeof(LocalRelayHeader));
    data_ov066_0226bdec->ggid = params->ggid;
    data_ov066_0226bdec->flags &= ~LOCAL_FLAG_08;
    data_ov066_0226bdec->flags &= ~LOCAL_FLAG_MIN_POLL_BMP;
    data_ov066_0226bdec->flags |= LOCAL_FLAG_MATCH_GGID;
    data_ov066_0226bdec->flags |= LOCAL_FLAG_MATCH_CHANNEL;
    data_ov066_0226bdec->flags |= LOCAL_FLAG_MATCH_KIND_5;
    data_ov066_0226bdec->flags &= ~LOCAL_FLAG_200;
    data_ov066_0226bdec->flags &= ~LOCAL_FLAG_FORGET_PARENT;
    data_ov066_0226bdec->flags |= LOCAL_FLAG_IGNORE_FATAL;
    data_ov066_0226bdec->flags |= LOCAL_FLAG_SINGLE_PACKET;
    data_ov066_0226bdec->mp_frequency = params->mp_frequency;
    data_ov066_0226bdec->parent_channel = LOCAL_CHANNEL_MEASURE_ONCE;
    data_ov066_0226bdec->channel_count = 1;
    data_ov066_0226bdec->max_children = (u8) (params->players - 1);
    data_ov066_0226bdec->max_players = params->players;
    data_ov066_0226bdec->parents_per_list = params->parents_per_list;
    data_ov066_0226bdec->unk_18 = slice;
    data_ov066_0226bdec->parent_max_size = packet;
    data_ov066_0226bdec->unk_1c = packet;
    data_ov066_0226bdec->child_max_size = slice;
    data_ov066_0226bdec->scan_time = 30;
    data_ov066_0226bdec->search_time = 90;
    data_ov066_0226bdec->unk_24 = 200;
    data_ov066_0226bdec->beacons_per_turn = 4;
}
CLEAN_AS(func_ov066_0226bc4c, LocalRelay_Configure)
