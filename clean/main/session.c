/* The multiplayer session's queues, bundles, counters and flags (session.h). */
#include "session.h"

#include <assert.h>
#include <stddef.h>

#include "autoload_2/network.h"
#include "clean.h"
#include "main/library_overlay.h"
#include "main/packed_bytes.h"
#include "main/session_net.h"
#include "link_global.h"
#include "link_scene.h"
#include "scene_query.h"
#include "session_link.h"
#include "session_message.h"
#include "session_record.h"

static_assert(offsetof(NetSession, frame_count) == 0x04, "frame count");
static_assert(offsetof(NetSession, mode) == 0x06, "mode");
static_assert(offsetof(NetSession, mode_request) == 0x07, "mode request");
static_assert(offsetof(NetSession, send_blocks) == 0x08, "send blocks");
static_assert(offsetof(NetSession, credits) == 0x0c, "credits");
static_assert(offsetof(NetSession, owed_credits) == 0x18, "owed credits");
static_assert(offsetof(NetSession, recv_blocks) == 0x24, "receive blocks");
static_assert(offsetof(NetSession, recv_length) == 0x28, "receive lengths");
static_assert(offsetof(NetSession, recv_head) == 0x4c, "receive heads");
static_assert(offsetof(NetSession, recv_count) == 0x58, "receive counts");
static_assert(offsetof(NetSession, local_slot) == 0x64, "local slot");
static_assert(offsetof(NetSession, local_player) == 0x68, "local player");
static_assert(offsetof(NetSession, player_count) == 0x6c, "player count");
static_assert(offsetof(NetSession, record_table) == 0x78, "record table");
static_assert(offsetof(NetSession, record_flags) == 0x7c, "record flags");
static_assert(offsetof(NetSession, send_buffer) == 0xc4, "send buffer");
static_assert(offsetof(NetSession, send_length) == 0xc8, "send length");
static_assert(offsetof(NetSession, send_end) == 0xcc, "send end");
static_assert(offsetof(NetSession, message_start) == 0xd0, "message start");
static_assert(offsetof(NetSession, message_cursor) == 0xd4, "message cursor");
static_assert(offsetof(NetSession, outbox) == 0xd8, "outbox");
static_assert(offsetof(NetSession, outbox_length) == 0xdc, "outbox length");
static_assert(offsetof(NetSession, read_cursor) == 0xe0, "read cursor");
static_assert(offsetof(NetSession, held_queue) == 0xe4, "held queue");
static_assert(offsetof(NetSession, scene_queue) == 0xec, "scene queue");
static_assert(offsetof(NetSession, local_queue) == 0xf4, "local queue");
static_assert(offsetof(NetSession, bundle15) == 0xfc, "bundle 15");
static_assert(offsetof(NetSession, bundle16) == 0x108, "bundle 16");
static_assert(offsetof(NetSession, pending_sequence) == 0x114, "pending sequence");
static_assert(offsetof(NetSession, sequence) == 0x116, "sequence");
static_assert(offsetof(NetSession, share_length) == 0x118, "share length");
static_assert(offsetof(NetSession, shown_error_flags) == 0x11c, "shown error flags");
static_assert(offsetof(NetSession, error_flags) == 0x120, "error flags");
static_assert(offsetof(NetSession, connect_mode) == 0x124, "connect mode");
static_assert(offsetof(NetSession, peer_silence) == 0x128, "peer silence");
static_assert(offsetof(NetSession, send_wait) == 0x12e, "send wait");
static_assert(offsetof(NetSession, send_wait_limit) == 0x130, "send wait limit");
static_assert(offsetof(NetSession, slot_mask) == 0x132, "slot mask");
static_assert(offsetof(NetSession, start_table) == 0x134, "start table");
static_assert(offsetof(NetSession, start_header) == 0x714, "start header");

/* A peer not heard for more than this many frames (10 seconds) has gone silent; its counter
 * stops one past it. */
#define PEER_SILENCE_LIMIT 600

/* The block Session_GetSendBlock returns for "slot" 4, the start of the send blocks: this
 * system's shared data. */
#define SHARE_BLOCK 4

#define NO_SEQUENCE (-1)

/* The bytes of a message header (session.h). */
#define HEADER_HANDLER 2
#define HEADER_KIND 3
#define HEADER_SOURCE 4

extern NetSession *data_020ccf94; /* the session */

extern void MI_CpuCopy8(const void *src, void *dst, u32 size);

/* func_02073138 */
u8 *Session_GetStartHeader(NetSession *session)
{
    return session->start_header;
}
CLEAN_AS(func_02073138, Session_GetStartHeader)

/* func_02073144 */
u8 *Session_GetStartTable(NetSession *session)
{
    return session->start_table;
}
CLEAN_AS(func_02073144, Session_GetStartTable)

/* func_02073150 */
void Session_SetSlotMask(NetSession *session, u16 mask)
{
    session->slot_mask = mask;
}
CLEAN_AS(func_02073150, Session_SetSlotMask)

/* func_0207315c */
u16 Session_GetSendWaitLimit(NetSession *session)
{
    return session->send_wait_limit;
}
CLEAN_AS(func_0207315c, Session_GetSendWaitLimit)

/* func_02073168 */
void Session_SetSendWaitLimit(NetSession *session, u16 frames)
{
    session->send_wait_limit = frames;
}
CLEAN_AS(func_02073168, Session_SetSendWaitLimit)

/* func_02073174 */
u16 Session_GetSendWait(NetSession *session)
{
    return session->send_wait;
}
CLEAN_AS(func_02073174, Session_GetSendWait)

/* func_02073180 */
void Session_SetSendWait(NetSession *session, u16 frames)
{
    session->send_wait = frames;
}
CLEAN_AS(func_02073180, Session_SetSendWait)

/* func_0207318c */
void Session_ClearPeerSilence(NetSession *session)
{
    for (int peer = 0; peer < SESSION_PEERS; peer++) {
        session->peer_silence[peer] = 0;
    }
}
CLEAN_AS(func_0207318c, Session_ClearPeerSilence)

/* func_020731a4: a message came from `slot`.
 * REQUIRES: `slot` is another system's slot, so that its peer index is 0-2. */
void Session_ResetPeerSilence(NetSession *session, int slot)
{
    session->peer_silence[SessionNet_PeerIndex(slot)] = 0;
}
CLEAN_AS(func_020731a4, Session_ResetPeerSilence)

/* func_020731c4: whether a peer has not been heard for more than PEER_SILENCE_LIMIT frames.
 * QUIRK: the argument is ignored; the session is read through data_020ccf94.
 * QUIRK: the results of the first SessionNet_PeerIndex call and of SessionNet_IsWifiGame are
 * not used. */
int Session_AnyPeerSilent(NetSession *ignored)
{
    NetSession *session = data_020ccf94;
    (void) ignored;

    for (int slot = SESSION_SLOTS - 1; slot >= 0; slot--) {
        if (Session_IsSlotTaken(session, slot) == 0 || Session_IsLocalSlot(session, slot) != 0) {
            continue;
        }
        SessionNet_PeerIndex(slot);
        u16 silence = Session_GetPeerSilence(session, (u32) slot);
        SessionNet_IsWifiGame();
        if (silence > PEER_SILENCE_LIMIT) {
            return 1;
        }
    }
    return 0;
}
CLEAN_AS(func_020731c4, Session_AnyPeerSilent)

/* func_02073220
 * REQUIRES: `slot` is another system's slot (peer index 0-2). */
u16 Session_GetPeerSilence(NetSession *session, u32 slot)
{
    return session->peer_silence[SessionNet_PeerIndex((int) slot)];
}
CLEAN_AS(func_02073220, Session_GetPeerSilence)

/* func_0207323c: once a frame, counts a frame of silence for every peer, up to one past the
 * limit.
 * QUIRK: which slots are peers is read through data_020ccf94, the counters written through the
 * argument (the only caller passes data_020ccf94). The result of SessionNet_IsWifiGame is not used. */
void Session_AgePeerSilence(NetSession *session)
{
    NetSession *current = data_020ccf94;

    for (int slot = SESSION_SLOTS - 1; slot >= 0; slot--) {
        if (Session_IsSlotTaken(current, slot) == 0 || Session_IsLocalSlot(current, slot) != 0) {
            continue;
        }
        int peer = SessionNet_PeerIndex(slot);
        u16 silence = Session_GetPeerSilence(current, (u32) slot);
        SessionNet_IsWifiGame();
        if (silence <= PEER_SILENCE_LIMIT) {
            session->peer_silence[peer]++;
        }
    }
}
CLEAN_AS(func_0207323c, Session_AgePeerSilence)

/* func_020732a8 */
u32 Session_GetConnectMode(NetSession *session)
{
    return session->connect_mode;
}
CLEAN_AS(func_020732a8, Session_GetConnectMode)

/* func_020732b4 */
void Session_SetConnectMode(NetSession *session, int mode)
{
    session->connect_mode = (u32) mode;
}
CLEAN_AS(func_020732b4, Session_SetConnectMode)

/* func_020732c0 */
u32 Session_GetErrorFlags(NetSession *session)
{
    return session->error_flags;
}
CLEAN_AS(func_020732c0, Session_GetErrorFlags)

/* func_020732cc */
void Session_SetErrorFlags(NetSession *session, int flags)
{
    session->error_flags = (u32) flags;
}
CLEAN_AS(func_020732cc, Session_SetErrorFlags)

/* func_020732d8 */
u32 Session_GetShownErrorFlags(NetSession *session)
{
    return session->shown_error_flags;
}
CLEAN_AS(func_020732d8, Session_GetShownErrorFlags)

/* func_020732e4 */
void Session_SetShownErrorFlags(NetSession *session, int flags)
{
    session->shown_error_flags = (u32) flags;
}
CLEAN_AS(func_020732e4, Session_SetShownErrorFlags)

/* func_020732f0: appends `size` bytes to this system's shared-data block. Nothing checks the
 * block's size. */
void Session_AppendShareData(NetSession *session, const void *data, int size)
{
    u8 *dst = Session_GetSendBlock(session, SHARE_BLOCK) + session->share_length;
    MI_CpuCopy8(data, dst, (u32) size);
    session->share_length += (u32) size;
}
CLEAN_AS(func_020732f0, Session_AppendShareData)

/* func_02073320 */
void Session_ClearShareLength(NetSession *session)
{
    session->share_length = 0;
}
CLEAN_AS(func_02073320, Session_ClearShareLength)

/* func_0207332c */
u32 Session_GetShareLength(NetSession *session)
{
    return session->share_length;
}
CLEAN_AS(func_0207332c, Session_GetShareLength)

/* func_02073338 */
void Session_SetShareLength(NetSession *session, int length)
{
    session->share_length = (u32) length;
}
CLEAN_AS(func_02073338, Session_SetShareLength)

/* func_02073344 */
void Session_ClearSequence(NetSession *session)
{
    session->sequence = NO_SEQUENCE;
}
CLEAN_AS(func_02073344, Session_ClearSequence)

/* func_02073354 */
void Session_ClearPendingSequence(NetSession *session)
{
    session->pending_sequence = NO_SEQUENCE;
}
CLEAN_AS(func_02073354, Session_ClearPendingSequence)

/* func_02073364 */
int Session_GetSequence(NetSession *session)
{
    return session->sequence;
}
CLEAN_AS(func_02073364, Session_GetSequence)

/* func_02073370 */
s16 Session_GetPendingSequence(NetSession *session)
{
    return session->pending_sequence;
}
CLEAN_AS(func_02073370, Session_GetPendingSequence)

/* func_0207337c */
void Session_SetSequence(NetSession *session, u16 sequence)
{
    session->sequence = (s16) sequence;
}
CLEAN_AS(func_0207337c, Session_SetSequence)

/* func_02073388 */
void Session_SetPendingSequence(NetSession *session, u16 sequence)
{
    session->pending_sequence = (s16) sequence;
}
CLEAN_AS(func_02073388, Session_SetPendingSequence)

/* func_02073394 */
u32 Session_GetBundle16Length(NetSession *session)
{
    return session->bundle16_length;
}
CLEAN_AS(func_02073394, Session_GetBundle16Length)

/* func_020733a0 */
void Session_SetBundle16Length(NetSession *session, int length)
{
    session->bundle16_length = (u32) length;
}
CLEAN_AS(func_020733a0, Session_SetBundle16Length)

/* func_020733ac */
void Session_ClearBundle16Length(NetSession *session)
{
    Session_SetBundle16Length(session, 0);
}
CLEAN_AS(func_020733ac, Session_ClearBundle16Length)

/* func_020733b8 */
void Session_SetBundle16Buffer(NetSession *session, u8 *buffer)
{
    session->bundle16 = buffer;
}
CLEAN_AS(func_020733b8, Session_SetBundle16Buffer)

/* func_020733c4 */
u8 *Session_GetBundle16Buffer(NetSession *session)
{
    return session->bundle16;
}
CLEAN_AS(func_020733c4, Session_GetBundle16Buffer)

/* func_020733d0: appends to the section of the category 15 bundle being built. Nothing checks
 * the bundle's size. */
void Session_AppendBundle15(NetSession *session, const void *data, u32 size)
{
    MI_CpuCopy8(data, session->bundle15_cursor, size);
    session->bundle15_cursor += size;
}
CLEAN_AS(func_020733d0, Session_AppendBundle15)

/* func_020733f8 */
u32 Session_GetBundle15Length(NetSession *session)
{
    return session->bundle15_length;
}
CLEAN_AS(func_020733f8, Session_GetBundle15Length)

/* func_02073404 */
void Session_SetBundle15Length(NetSession *session, int length)
{
    session->bundle15_length = (u32) length;
}
CLEAN_AS(func_02073404, Session_SetBundle15Length)

/* func_02073410 */
void Session_ClearBundle15Length(NetSession *session)
{
    Session_SetBundle15Length(session, 0);
}
CLEAN_AS(func_02073410, Session_ClearBundle15Length)

/* func_0207341c */
void Session_SetBundle15Buffer(NetSession *session, u8 *buffer)
{
    session->bundle15 = buffer;
}
CLEAN_AS(func_0207341c, Session_SetBundle15Buffer)

/* func_02073424 */
u8 *Session_GetBundle15Buffer(NetSession *session)
{
    return session->bundle15;
}
CLEAN_AS(func_02073424, Session_GetBundle15Buffer)

/* Hands every message of a queue to its handler (func_0207342c and func_020734d0). */
static void deliver_all(const u8 *message, u32 length)
{
    u32 done = 0;
    while (done < length) {
        u8 header[MESSAGE_HEADER_SIZE];
        u8 scene;
        u8 slot;

        MI_CpuCopy8(message, header, MESSAGE_HEADER_SIZE);
        message += MESSAGE_HEADER_SIZE;
        done += MESSAGE_HEADER_SIZE;
        PackedBytes_SplitScene(&header[HEADER_SOURCE], &scene, &slot);
        u16 size = PackedBytes_ReadU16(header);
        SessionMessage_Dispatch(header[HEADER_HANDLER], message, size, header[HEADER_KIND], scene, slot);
        message += size;
        done += size;
    }
}

/* func_0207342c: hands the messages this system sent to itself to their handlers, then empties
 * the queue. */
void Session_DeliverLocalQueue(NetSession *session)
{
    u32 length = Session_GetLocalQueueLength(session);
    if (length == 0) {
        return;
    }
    deliver_all(Session_GetLocalQueue(session), length);
    Session_ClearLocalQueue(session);
}
CLEAN_AS(func_0207342c, Session_DeliverLocalQueue)

/* func_020734a4 */
u32 Session_GetLocalQueueLength(NetSession *session)
{
    return session->local_length;
}
CLEAN_AS(func_020734a4, Session_GetLocalQueueLength)

/* func_020734ac */
void Session_SetLocalQueueLength(NetSession *session, u32 length)
{
    session->local_length = length;
}
CLEAN_AS(func_020734ac, Session_SetLocalQueueLength)

/* func_020734b4 */
void Session_ClearLocalQueue(NetSession *session)
{
    Session_SetLocalQueueLength(session, 0);
}
CLEAN_AS(func_020734b4, Session_ClearLocalQueue)

/* func_020734c0 */
void Session_SetLocalQueueBuffer(NetSession *session, u8 *buffer)
{
    session->local_queue = buffer;
}
CLEAN_AS(func_020734c0, Session_SetLocalQueueBuffer)

/* func_020734c8 */
u8 *Session_GetLocalQueue(NetSession *session)
{
    return session->local_queue;
}
CLEAN_AS(func_020734c8, Session_GetLocalQueue)

/* func_020734d0: once this system is in the scene of the first waiting message, hands every
 * waiting message to its handler and empties the queue.
 * QUIRK: only the first message's scene is checked; the others go with it. */
void Session_DeliverSceneQueue(NetSession *session)
{
    u32 length = Session_GetSceneQueueLength(session);
    if (length == 0) {
        return;
    }
    const u8 *first = Session_GetSceneQueue(session);

    u8 header[MESSAGE_HEADER_SIZE];
    u8 scene;
    u8 slot;
    MI_CpuCopy8(first, header, MESSAGE_HEADER_SIZE);
    PackedBytes_SplitScene(&header[HEADER_SOURCE], &scene, &slot);
    if (scene != SceneQuery_Current()) {
        return;
    }

    deliver_all(first, length);
    Session_ClearSceneQueue(session);
}
CLEAN_AS(func_020734d0, Session_DeliverSceneQueue)

/* func_0207356c */
u32 Session_GetSceneQueueLength(NetSession *session)
{
    return session->scene_length;
}
CLEAN_AS(func_0207356c, Session_GetSceneQueueLength)

/* func_02073574 */
void Session_SetSceneQueueLength(NetSession *session, u32 length)
{
    session->scene_length = length;
}
CLEAN_AS(func_02073574, Session_SetSceneQueueLength)

/* func_0207357c */
void Session_ClearSceneQueue(NetSession *session)
{
    Session_SetSceneQueueLength(session, 0);
}
CLEAN_AS(func_0207357c, Session_ClearSceneQueue)

/* func_02073588 */
void Session_SetSceneQueueBuffer(NetSession *session, u8 *buffer)
{
    session->scene_queue = buffer;
}
CLEAN_AS(func_02073588, Session_SetSceneQueueBuffer)

/* func_02073590 */
u8 *Session_GetSceneQueue(NetSession *session)
{
    return session->scene_queue;
}
CLEAN_AS(func_02073590, Session_GetSceneQueue)

/* func_02073598: finds which slot owns the scene of the first held message (func_020a71ec).
 * When this system does, all held messages move, headers unchanged, to the end of the local
 * queue; when another system does, each is sent again (as a new message from this system, in
 * the current scene). Either way the held queue is emptied; when no slot owns the scene, or
 * this system has no slot, the messages stay.
 * QUIRK: only the first message's scene is looked at; the others go with it.
 * QUIRK: nothing checks that the local queue has room. */
void Session_RouteHeldMessages(NetSession *session)
{
    int local_slot = session->local_slot;
    if (Session_IsSlotTaken(session, local_slot) == 0) {
        return;
    }
    u32 length = Session_GetHeldQueueLength(session);
    if (length == 0) {
        return;
    }
    const u8 *message = Session_GetHeldQueue(session);

    u8 header[MESSAGE_HEADER_SIZE];
    u8 scene;
    u8 slot;
    MI_CpuCopy8(message, header, MESSAGE_HEADER_SIZE);
    PackedBytes_SplitScene(&header[HEADER_SOURCE], &scene, &slot);

    int owner = LinkGlobal_SceneOwner(scene);
    if (owner >= SESSION_SLOTS) {
        return;
    }

    if (owner == local_slot) {
        u32 local_length = Session_GetLocalQueueLength(session);
        u8 *dst = Session_GetLocalQueue(session) + local_length;
        for (u32 done = 0; done < length;) {
            MI_CpuCopy8(message, header, MESSAGE_HEADER_SIZE);
            u32 whole = (u32) PackedBytes_ReadU16(header) + MESSAGE_HEADER_SIZE;
            MI_CpuCopy8(message, dst, whole);
            dst += whole;
            local_length += whole;
            message += whole;
            done += whole;
        }
        Session_SetLocalQueueLength(session, local_length);
    } else {
        for (u32 done = 0; done < length;) {
            MI_CpuCopy8(message, header, MESSAGE_HEADER_SIZE);
            message += MESSAGE_HEADER_SIZE;
            done += MESSAGE_HEADER_SIZE;
            u16 size = PackedBytes_ReadU16(header);
            Session_BeginMessage(session);
            Session_AppendMessage(session, message, size);
            Session_EndMessage(session, header[HEADER_HANDLER], header[HEADER_KIND]);
            message += size;
            done += size;
        }
    }
    Session_ClearHeldQueue(session);
}
CLEAN_AS(func_02073598, Session_RouteHeldMessages)

/* func_02073690 */
u32 Session_GetHeldQueueLength(NetSession *session)
{
    return session->held_length;
}
CLEAN_AS(func_02073690, Session_GetHeldQueueLength)

/* func_02073698 */
void Session_SetHeldQueueLength(NetSession *session, u32 length)
{
    session->held_length = length;
}
CLEAN_AS(func_02073698, Session_SetHeldQueueLength)

/* func_020736a0 */
void Session_ClearHeldQueue(NetSession *session)
{
    Session_SetHeldQueueLength(session, 0);
}
CLEAN_AS(func_020736a0, Session_ClearHeldQueue)

/* func_020736ac */
void Session_SetHeldQueueBuffer(NetSession *session, u8 *buffer)
{
    session->held_queue = buffer;
}
CLEAN_AS(func_020736ac, Session_SetHeldQueueBuffer)

/* func_020736b4 */
u8 *Session_GetHeldQueue(NetSession *session)
{
    return session->held_queue;
}
CLEAN_AS(func_020736b4, Session_GetHeldQueue)

/* func_020736bc: a handler reads the next `size` bytes of its message's payload. */
void Session_ReadMessage(NetSession *session, void *dst, int size)
{
    const u8 *src = Session_GetReadCursor(session);
    MI_CpuCopy8(src, dst, (u32) size);
    Session_SetReadCursor(session, src + size);
}
CLEAN_AS(func_020736bc, Session_ReadMessage)

/* func_020736e4 */
const u8 *Session_GetReadCursor(NetSession *session)
{
    return session->read_cursor;
}
CLEAN_AS(func_020736e4, Session_GetReadCursor)

/* func_020736ec */
void Session_SetReadCursor(NetSession *session, const u8 *cursor)
{
    session->read_cursor = cursor;
}
CLEAN_AS(func_020736ec, Session_SetReadCursor)

/* The block `index` of an array of SESSION_BLOCK_SIZE blocks, computed as the original does,
 * modulo 2^32. */
static u8 *block_at(u8 *blocks, u32 index)
{
    return (u8 *) ((uintptr_t) blocks + index * SESSION_BLOCK_SIZE);
}

/* ---- The outbox: finished messages waiting to be put into packets */

/* func_020736f4: moves `size` bytes (the send buffer's finished messages) to the end of the
 * outbox when they fit; 1 when they were moved, 0 when the outbox has no room.
 * QUIRK: the argument is ignored; the session is read through data_020ccf94. */
int Session_QueueOutgoing(NetSession *ignored, const u8 *data, int size)
{
    (void) ignored;
    u32 length = Session_GetOutboxLength(data_020ccf94);
    if (SESSION_SEND_SIZE - length < (u32) size) {
        return 0;
    }
    NetSession *session = data_020ccf94;
    MI_CpuCopy8(data, Session_GetOutbox(session) + length, (u32) size);
    Session_SetOutboxLength(session, length + (u32) size);
    return 1;
}
CLEAN_AS(func_020736f4, Session_QueueOutgoing)

/* func_02073744 */
u32 Session_GetOutboxLength(NetSession *session)
{
    return session->outbox_length;
}
CLEAN_AS(func_02073744, Session_GetOutboxLength)

/* func_0207374c */
void Session_SetOutboxLength(NetSession *session, u32 length)
{
    session->outbox_length = length;
}
CLEAN_AS(func_0207374c, Session_SetOutboxLength)

/* func_02073754 */
void Session_ClearOutbox(NetSession *session)
{
    Session_SetOutboxLength(session, 0);
}
CLEAN_AS(func_02073754, Session_ClearOutbox)

/* func_02073760 */
void Session_SetOutbox(NetSession *session, u8 *buffer)
{
    session->outbox = buffer;
}
CLEAN_AS(func_02073760, Session_SetOutbox)

/* func_02073768 */
u8 *Session_GetOutbox(NetSession *session)
{
    return session->outbox;
}
CLEAN_AS(func_02073768, Session_GetOutbox)

/* ---- The send buffer: the messages built this frame */

/* func_02073770: ends the message being built: writes its header (session.h) in front of the
 * payload, from this system's slot in the current scene, and adds it to the finished messages.
 * Nothing happens unless the session is linked.
 * QUIRK: for kinds 6 and 7 func_020a6c98 is asked about the current scene; its answer is not
 * used. */
void Session_EndMessage(NetSession *session, u32 handler, u32 kind)
{
    if (!Session_IsLinked(session)) {
        return;
    }
    if (kind == 6 || kind == 7) {
        LinkScene_IsLinkingScene(SceneQuery_Current());
    }
    u32 whole = (u32) ((uintptr_t) session->message_cursor - (uintptr_t) session->message_start);

    u8 header[MESSAGE_HEADER_SIZE];
    PackedBytes_WriteU16(header, (PackedBytesHalf){.value = (u16) (whole - MESSAGE_HEADER_SIZE)});
    header[HEADER_HANDLER] = (u8) handler;
    header[HEADER_KIND] = (u8) kind;
    PackedBytes_JoinScene(&header[HEADER_SOURCE], SceneQuery_Current(), (u8) session->local_slot);
    MI_CpuCopy8(header, session->message_start, MESSAGE_HEADER_SIZE);

    session->send_length += whole;
    session->send_end = session->message_cursor;
}
CLEAN_AS(func_02073770, Session_EndMessage)

/* func_020737f0: appends to the payload of the message being built, when the session is
 * linked. Nothing checks the send buffer's size. */
void Session_AppendMessage(NetSession *session, const void *data, int size)
{
    if (Session_IsLinked(session)) {
        MI_CpuCopy8(data, session->message_cursor, (u32) size);
        session->message_cursor = (u8 *) ((uintptr_t) session->message_cursor + (u32) size);
    }
}
CLEAN_AS(func_020737f0, Session_AppendMessage)

/* func_02073820: starts a message after the finished ones, leaving room for its header, when
 * the session is linked. */
void Session_BeginMessage(NetSession *session)
{
    if (Session_IsLinked(session)) {
        session->message_start = session->send_end;
        session->message_cursor = (u8 *) ((uintptr_t) session->send_end + MESSAGE_HEADER_SIZE);
    }
}
CLEAN_AS(func_02073820, Session_BeginMessage)

/* func_0207384c */
u32 Session_GetSendLength(NetSession *session)
{
    return session->send_length;
}
CLEAN_AS(func_0207384c, Session_GetSendLength)

/* func_02073854 */
void Session_SetSendLength(NetSession *session, u32 length)
{
    session->send_length = length;
}
CLEAN_AS(func_02073854, Session_SetSendLength)

/* func_0207385c: empties the send buffer. */
void Session_ClearSendBuffer(NetSession *session)
{
    Session_SetSendLength(session, 0);
    session->send_end = Session_GetSendBuffer(session);
}
CLEAN_AS(func_0207385c, Session_ClearSendBuffer)

/* func_02073878 */
void Session_SetSendBuffer(NetSession *session, u8 *buffer)
{
    session->send_buffer = buffer;
    session->send_end = buffer;
}
CLEAN_AS(func_02073878, Session_SetSendBuffer)

/* func_02073884 */
u8 *Session_GetSendBuffer(NetSession *session)
{
    return session->send_buffer;
}
CLEAN_AS(func_02073884, Session_GetSendBuffer)

/* ---- The shared records: SESSION_RECORDS records in one table, each flagged to be sent */

/* func_0207388c */
void Session_ClearRecordFlags(NetSession *session)
{
    for (int id = SESSION_RECORDS - 1; id >= 0; id--) {
        Session_SetRecordFlag(session, id, 0);
    }
}
CLEAN_AS(func_0207388c, Session_ClearRecordFlags)

/* func_020738ac
 * REQUIRES: 0 <= id < SESSION_RECORDS. */
void Session_SetRecordFlag(NetSession *session, int id, int value)
{
    session->record_flags[id] = (u8) value;
}
CLEAN_AS(func_020738ac, Session_SetRecordFlag)

/* func_020738b4
 * REQUIRES: 0 <= id < SESSION_RECORDS. */
int Session_GetRecordFlag(NetSession *session, int id)
{
    return session->record_flags[id];
}
CLEAN_AS(func_020738b4, Session_GetRecordFlag)

/* func_020738bc: a shared record in the table; NULL while there is no table.
 * REQUIRES: 0 <= id < SESSION_RECORDS (func_02077620 reads the whole register). */
u8 *Session_GetRecord(NetSession *session, int id)
{
    u8 *table = Session_GetRecordTable(session);
    if (table == NULL) {
        return NULL;
    }
    return table + SessionRecord_GetOffset((u16) id);
}
CLEAN_AS(func_020738bc, Session_GetRecord)

/* func_020738e0 */
void Session_SetRecordTable(NetSession *session, u8 *table)
{
    session->record_table = table;
}
CLEAN_AS(func_020738e0, Session_SetRecordTable)

/* func_020738e4 */
u8 *Session_GetRecordTable(NetSession *session)
{
    return session->record_table;
}
CLEAN_AS(func_020738e4, Session_GetRecordTable)

/* ---- Players and slots */

/* func_020738e8 */
void Session_ClearPlayerCount(NetSession *session)
{
    Session_SetPlayerCount(session, 0);
}
CLEAN_AS(func_020738e8, Session_ClearPlayerCount)

/* func_020738f4
 * QUIRK: a count above 4 is stored as 0 (so is one that a caller's subtraction wrapped below
 * 0). */
void Session_SetPlayerCount(NetSession *session, u32 count)
{
    session->player_count = count > SESSION_SLOTS ? 0 : (u8) count;
}
CLEAN_AS(func_020738f4, Session_SetPlayerCount)

/* func_02073908 */
int Session_IsLocalPlayer(NetSession *session, int player)
{
    return player == session->local_player;
}
CLEAN_AS(func_02073908, Session_IsLocalPlayer)

/* func_02073918 */
int Session_IsLocalSlot(NetSession *session, int slot)
{
    return slot == session->local_slot;
}
CLEAN_AS(func_02073918, Session_IsLocalSlot)

/* ---- The receive queues: SESSION_RECV_ENTRIES blocks per peer, filled by the receive
 * callback (func_02075050).
 *
 * The functions here that take a slot index their arrays by its peer index (SessionNet_PeerIndex).
 * REQUIRES: the slot is another system's, so that its peer index is 0-2. */

/* func_02073928: the entry the next packet from `slot` is received into.
 * QUIRK: when the queue is full this is its oldest entry. */
int Session_GetRecvWriteEntry(NetSession *session, int slot)
{
    int peer = SessionNet_PeerIndex(slot);
    u32 count = session->recv_count[peer];
    if (count >= SESSION_RECV_ENTRIES) {
        return (int) session->recv_head[peer];
    }
    u32 entry = count + session->recv_head[peer];
    if (entry >= SESSION_RECV_ENTRIES) {
        entry -= SESSION_RECV_ENTRIES;
    }
    return (int) entry;
}
CLEAN_AS(func_02073928, Session_GetRecvWriteEntry)

/* func_02073950: the oldest entry received from `slot`; SESSION_RECV_ENTRIES when there is
 * none. */
int Session_GetRecvReadEntry(NetSession *session, int slot)
{
    int peer = SessionNet_PeerIndex(slot);
    if (session->recv_count[peer] == 0) {
        return SESSION_RECV_ENTRIES;
    }
    return (int) session->recv_head[peer];
}
CLEAN_AS(func_02073950, Session_GetRecvReadEntry)

/* func_02073970: drops the oldest entry received from `slot`. */
void Session_PopRecvEntry(NetSession *session, int slot)
{
    int peer = SessionNet_PeerIndex(slot);
    session->recv_count[peer]--;
    u32 head = session->recv_head[peer] + 1;
    if (head >= SESSION_RECV_ENTRIES) {
        head = 0;
    }
    session->recv_head[peer] = head;
}
CLEAN_AS(func_02073970, Session_PopRecvEntry)

/* func_0207399c: keeps the entry just received from `slot`. */
void Session_PushRecvEntry(NetSession *session, int slot)
{
    session->recv_count[SessionNet_PeerIndex(slot)]++;
}
CLEAN_AS(func_0207399c, Session_PushRecvEntry)

/* func_020739b8 */
void Session_ClearRecvQueues(NetSession *session)
{
    for (int peer = 0; peer < SESSION_PEERS; peer++) {
        session->recv_head[peer] = 0;
        session->recv_count[peer] = 0;
    }
}
CLEAN_AS(func_020739b8, Session_ClearRecvQueues)

/* Kinds of message that are only for systems in the sender's scene (session.h). */
#define KIND_SAME_SCENE 6
#define KIND_SCENE_QUEUED 7

/* func_020739d0: up to SESSION_RECV_ENTRIES times, takes the oldest packet received from every
 * peer and handles it: copies its shared records into the table, then hands its messages to
 * their handlers. A message of kind 7 from another scene waits in the scene queue when
 * func_020a72d0 says so for this system's slot; otherwise messages of kinds 6 and 7 from
 * another scene, and those of kind 6 while func_020a7278 says 0, are dropped. With interrupts
 * off (the receive callback writes the same queue) the packet's entry is then cleared and
 * dropped, and a credit is owed to the peer.
 * QUIRK: the packet is read through the argument, the receive queue updated through
 * data_020ccf94 (the only caller passes data_020ccf94).
 * QUIRK: the first record id is read even from a packet with nothing after its first byte;
 * when the records end past the packet's length, the bytes left wrap around to a 16-bit count
 * and that many bytes are read as messages.
 * QUIRK: nothing checks that the scene queue has room. */
void Session_ProcessReceived(NetSession *session)
{
    NetSession *queues = data_020ccf94;

    for (int pass = 0; pass < SESSION_RECV_ENTRIES; pass++) {
        for (int slot = 0; slot < SESSION_SLOTS; slot++) {
            if (Session_IsLocalSlot(session, slot)) {
                continue;
            }
            u32 entry = (u32) Session_GetRecvReadEntry(session, slot);
            if (entry >= SESSION_RECV_ENTRIES) {
                continue;
            }
            /* The packet's first byte gives credits back; the receive callback took them. */
            u32 length = Session_GetRecvLength(session, slot, (int) entry) - 1;
            const u8 *read = Session_GetRecvBlock(session, slot, (int) entry) + 1;

            u16 used = 0;
            do {
                u8 id;
                MI_CpuCopy8(read, &id, 1);
                read++;
                used++;
                if (id >= SESSION_RECORDS) {
                    break;
                }
                u8 size = SessionRecord_GetSize(id);
                MI_CpuCopy8(read, Session_GetRecord(session, id), size);
                read += size;
                used = (u16) (used + size);
            } while (used < length);

            u32 messages = (u16) (length - used);
            for (u32 done = 0; done < messages;) {
                u8 header[MESSAGE_HEADER_SIZE];
                u8 scene;
                u8 sender;

                MI_CpuCopy8(read, header, MESSAGE_HEADER_SIZE);
                read += MESSAGE_HEADER_SIZE;
                done += MESSAGE_HEADER_SIZE;
                u8 kind = header[HEADER_KIND];
                PackedBytes_SplitScene(&header[HEADER_SOURCE], &scene, &sender);
                u8 current_scene = SceneQuery_Current();
                u16 size = PackedBytes_ReadU16(header);

                if (LinkGlobal_PlaceMoving(session->local_slot) != 0 && kind == KIND_SCENE_QUEUED && scene != current_scene) {
                    u32 queued = Session_GetSceneQueueLength(session);
                    u8 *dst = Session_GetSceneQueue(session) + queued;
                    MI_CpuCopy8(read - MESSAGE_HEADER_SIZE, dst, (u32) size + MESSAGE_HEADER_SIZE);
                    Session_SetSceneQueueLength(session, queued + size + MESSAGE_HEADER_SIZE);
                } else {
                    int ready = LinkGlobal_HoldsScene();
                    int drop = (kind == KIND_SAME_SCENE && (ready == 0 || scene != current_scene)) ||
                               (kind == KIND_SCENE_QUEUED && scene != current_scene);
                    if (!drop) {
                        SessionMessage_Dispatch(header[HEADER_HANDLER], read, size, kind, scene, sender);
                    }
                }
                read += size;
                done += size;
            }

            Session_DisableInterrupts();
            Session_ClearRecvLength(queues, slot, (int) entry);
            Session_PopRecvEntry(queues, slot);
            Session_OweCredit(queues, slot);
            Session_EnableInterrupts();
        }
    }
}
CLEAN_AS(func_020739d0, Session_ProcessReceived)

/* func_02073b84
 * QUIRK: only the first five of the nine received lengths are cleared (the first peer's three
 * and the second peer's first two). */
void Session_ClearRecv(NetSession *session)
{
    for (int i = 0; i < 5; i++) {
        session->recv_length[i / SESSION_RECV_ENTRIES][i % SESSION_RECV_ENTRIES] = 0;
    }
    Session_ClearRecvQueues(session);
}
CLEAN_AS(func_02073b84, Session_ClearRecv)

/* func_02073b9c */
void Session_ClearRecvLength(NetSession *session, int slot, int entry)
{
    Session_SetRecvLength(session, slot, entry, 0);
}
CLEAN_AS(func_02073b9c, Session_ClearRecvLength)

/* func_02073bac
 * REQUIRES: 0 <= entry < SESSION_RECV_ENTRIES. */
void Session_SetRecvLength(NetSession *session, int slot, int entry, int length)
{
    session->recv_length[SessionNet_PeerIndex(slot)][entry] = (u32) length;
}
CLEAN_AS(func_02073bac, Session_SetRecvLength)

/* func_02073bcc
 * REQUIRES: 0 <= entry < SESSION_RECV_ENTRIES. */
u32 Session_GetRecvLength(NetSession *session, int slot, int entry)
{
    return session->recv_length[SessionNet_PeerIndex(slot)][entry];
}
CLEAN_AS(func_02073bcc, Session_GetRecvLength)

/* func_02073bf0 */
void Session_SetRecvBlocks(NetSession *session, u8 *blocks)
{
    session->recv_blocks = blocks;
}
CLEAN_AS(func_02073bf0, Session_SetRecvBlocks)

/* func_02073bf4: the receive block of a peer's queue entry. */
u8 *Session_GetPeerRecvBlock(NetSession *session, int peer, int entry)
{
    return block_at(session->recv_blocks, (u32) peer * SESSION_RECV_ENTRIES + (u32) entry);
}
CLEAN_AS(func_02073bf4, Session_GetPeerRecvBlock)

/* func_02073c04: the receive block of a slot's queue entry; NULL for this system's slot, the
 * start of the receive blocks for a slot of 4 or more. The peer index is worked out here from
 * this system's slot rather than by SessionNet_PeerIndex. */
u8 *Session_GetRecvBlock(NetSession *session, int slot, int entry)
{
    if (slot >= SESSION_SLOTS) {
        return session->recv_blocks;
    }
    if (Session_IsLocalSlot(session, slot)) {
        return NULL;
    }
    int peer = slot < session->local_slot ? slot : slot - 1;
    return block_at(session->recv_blocks, (u32) peer * SESSION_RECV_ENTRIES + (u32) entry);
}
CLEAN_AS(func_02073c04, Session_GetRecvBlock)

/* ---- Credits */

/* func_02073c48 */
void Session_ClearOwedCredits(NetSession *session)
{
    for (int peer = 0; peer < SESSION_PEERS; peer++) {
        session->owed_credits[peer] = 0;
    }
}
CLEAN_AS(func_02073c48, Session_ClearOwedCredits)

/* func_02073c58 */
void Session_OweCredit(NetSession *session, int slot)
{
    session->owed_credits[SessionNet_PeerIndex(slot)]++;
}
CLEAN_AS(func_02073c58, Session_OweCredit)

/* func_02073c74 */
void Session_SetOwedCredits(NetSession *session, int slot, int count)
{
    session->owed_credits[SessionNet_PeerIndex(slot)] = count;
}
CLEAN_AS(func_02073c74, Session_SetOwedCredits)

/* func_02073c90 */
int Session_GetOwedCredits(NetSession *session, int slot)
{
    return session->owed_credits[SessionNet_PeerIndex(slot)];
}
CLEAN_AS(func_02073c90, Session_GetOwedCredits)

/* func_02073ca8: every peer can take a whole queue. */
void Session_ResetCredits(NetSession *session)
{
    for (int peer = 0; peer < SESSION_PEERS; peer++) {
        session->credits[peer] = SESSION_RECV_ENTRIES;
    }
}
CLEAN_AS(func_02073ca8, Session_ResetCredits)

/* func_02073cb8 */
void Session_ResetCredit(NetSession *session, int slot)
{
    session->credits[SessionNet_PeerIndex(slot)] = SESSION_RECV_ENTRIES;
}
CLEAN_AS(func_02073cb8, Session_ResetCredit)

/* func_02073cd0 */
void Session_SpendCredits(NetSession *session, int slot, int count)
{
    session->credits[SessionNet_PeerIndex(slot)] -= count;
}
CLEAN_AS(func_02073cd0, Session_SpendCredits)

/* func_02073cf0 */
void Session_AddCredits(NetSession *session, int slot, int count)
{
    session->credits[SessionNet_PeerIndex(slot)] += count;
}
CLEAN_AS(func_02073cf0, Session_AddCredits)

/* func_02073d10 */
int Session_GetCredits(NetSession *session, int slot)
{
    return session->credits[SessionNet_PeerIndex(slot)];
}
CLEAN_AS(func_02073d10, Session_GetCredits)

/* ---- Send blocks, mode, frame count and slots */

/* func_02073d28: the send block of a slot's peer; NULL for this system's slot, the start of
 * the send blocks for a slot of 4 or more. */
u8 *Session_GetSendBlock(NetSession *session, int slot)
{
    if (slot >= SESSION_SLOTS) {
        return session->send_blocks;
    }
    if (Session_IsLocalSlot(session, slot)) {
        return NULL;
    }
    int peer = slot < session->local_slot ? slot : slot - 1;
    return block_at(session->send_blocks, (u32) peer);
}
CLEAN_AS(func_02073d28, Session_GetSendBlock)

/* func_02073d64 */
void Session_SetSendBlocks(NetSession *session, u8 *blocks)
{
    session->send_blocks = blocks;
}
CLEAN_AS(func_02073d64, Session_SetSendBlocks)

/* func_02073d68 */
int Session_GetModeRequest(NetSession *session)
{
    return session->mode_request;
}
CLEAN_AS(func_02073d68, Session_GetModeRequest)

/* func_02073d6c */
void Session_SetModeRequest(NetSession *session, int request)
{
    session->mode_request = (u8) request;
}
CLEAN_AS(func_02073d6c, Session_SetModeRequest)

/* func_02073d70 */
int Session_GetMode(NetSession *session)
{
    return session->mode;
}
CLEAN_AS(func_02073d70, Session_GetMode)

/* func_02073d74 */
void Session_SetMode(NetSession *session, int mode)
{
    session->mode = (u8) mode;
}
CLEAN_AS(func_02073d74, Session_SetMode)

/* func_02073d78 */
void Session_CountFrame(NetSession *session)
{
    session->frame_count++;
}
CLEAN_AS(func_02073d78, Session_CountFrame)

/* func_02073d80: the frame count as a 15-bit sequence number. */
s16 Session_GetFrameSequence(NetSession *session)
{
    return (s16) (session->frame_count & 0x7fff);
}
CLEAN_AS(func_02073d80, Session_GetFrameSequence)

/* func_02073d90: whether this system has a slot and at least two players are in the session. */
int Session_IsLinked(NetSession *session)
{
    return Session_IsSlotTaken(session, session->local_slot) != 0 && session->player_count >= 2;
}
CLEAN_AS(func_02073d90, Session_IsLinked)

/* func_02073db4 */
void Session_ClearSlots(NetSession *session)
{
    for (int slot = SESSION_SLOTS - 1; slot >= 0; slot--) {
        Session_SetSlotTaken(session, slot, 0);
    }
}
CLEAN_AS(func_02073db4, Session_ClearSlots)

/* func_02073dd4: 0 for a slot of 4 or more.
 * REQUIRES: slot >= 0. */
u8 Session_IsSlotTaken(const NetSession *session, int slot)
{
    if (slot >= SESSION_SLOTS) {
        return 0;
    }
    return session->slot_taken[slot];
}
CLEAN_AS(func_02073dd4, Session_IsSlotTaken)

/* func_02073de0
 * REQUIRES: 0 <= slot < SESSION_SLOTS. */
void Session_SetSlotTaken(NetSession *session, int slot, int taken)
{
    session->slot_taken[slot] = (u8) taken;
}
CLEAN_AS(func_02073de0, Session_SetSlotTaken)

/* func_02073de4: whether this frame's packets may be sent: always when this system has no
 * slot, or when it is slot 0 with at most one player connected; otherwise when the network
 * can send. */
int Session_IsSendReady(NetSession *session)
{
    int local_slot = session->local_slot;
    if (Session_IsSlotTaken(session, local_slot) == 0) {
        return 1;
    }
    if (local_slot == 0 && (u32) Net_CountPlayers() <= 1) {
        return 1;
    }
    LibraryOverlay_RequireAny();
    return Net_CanSend() != 0;
}
CLEAN_AS(func_02073de4, Session_IsSendReady)

/* func_02073e30: sends up to three packets (each a block, its size and the AIDs it goes to)
 * without callbacks; 1 when they were queued. Then the send wait restarts: outside
 * SESSION_MODE_DATA, after a send with a block and a size, with a limit of 600 frames; in
 * SESSION_MODE_DATA, with none.
 * QUIRK: SessionNet_IsSystemPacket is asked about every packet with a block and a size, and
 * SessionNet_IsWifiGame once; their answers are not used. */
int Session_SendBlocks(NetSession *session, const u8 *block0, int size0, int to0, const u8 *block1, int size1, u16 to1,
                       const u8 *block2, int size2, u16 to2)
{
    LibraryOverlay_RequireAny();
    if (!Net_SendBlocks(block0, size0, to0, NULL, block1, size1, to1, NULL, block2, size2, to2, NULL)) {
        return 0;
    }
    if (Session_GetMode(session) == SESSION_MODE_DATA) {
        Session_SetSendWait(session, 0);
        Session_SetSendWaitLimit(session, 0);
        return 1;
    }
    int any_block = block0 != NULL || block1 != NULL || block2 != NULL;
    int any_size = size0 != 0 || size1 != 0 || size2 != 0;
    if (any_block && any_size) {
        if (block0 != NULL && size0 != 0) {
            SessionNet_IsSystemPacket(block0);
        }
        if (block1 != NULL && size1 != 0) {
            SessionNet_IsSystemPacket(block1);
        }
        if (block2 != NULL && size2 != 0) {
            SessionNet_IsSystemPacket(block2);
        }
        Session_SetSendWait(session, 0);
        SessionNet_IsWifiGame();
        Session_SetSendWaitLimit(session, 600);
    }
    return 1;
}
CLEAN_AS(func_02073e30, Session_SendBlocks)
