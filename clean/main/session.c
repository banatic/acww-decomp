/* The multiplayer session's queues, bundles, counters and flags (session.h). */
#include "session.h"

#include <assert.h>
#include <stddef.h>

#include "clean.h"

static_assert(offsetof(NetSession, local_slot) == 0x64, "local slot");
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

/* The block func_02073d28 returns for "slot" 4: this system's shared data. */
#define SHARE_BLOCK 4

#define NO_SEQUENCE (-1)

/* The bytes of a message header (session.h). */
#define HEADER_HANDLER 2
#define HEADER_KIND 3
#define HEADER_SOURCE 4

extern NetSession *data_020ccf94; /* the session */

extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
extern u8 func_02073dd4(const NetSession *session, int slot); /* whether a slot is taken */
extern int func_02073918(NetSession *session, int slot);      /* whether it is this system's */
extern u8 *func_02073d28(NetSession *session, int slot);      /* a slot's shared-data block */
extern int func_02077b58(int slot);                           /* the peer index of a slot */
extern int func_02077a64(void);                               /* whether the link is in mode 3 or 4 */
extern u8 func_020b65c4(void);                                /* the current scene */
extern int func_020a71ec(int scene);                          /* the slot owning a scene, 4 for none */
/* Splits a header's source byte into the sender's scene and slot. */
extern void func_02077a34(const u8 *source, u8 *scene, u8 *slot);
extern u16 func_02077868(const u8 *bytes); /* a little-endian u16 (a message's length) */
/* Hands a message to its handler: sets the read cursor to `payload`, then calls the handler. */
extern void func_02076168(int handler, const u8 *payload, int size, int kind, u8 scene, u32 slot);
extern void func_02073820(NetSession *message);                             /* begin a message */
extern void func_020737f0(NetSession *message, const void *data, int size); /* append */
extern void func_02073770(NetSession *message, u32 handler, u32 kind);      /* end and send */

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
    session->peer_silence[func_02077b58(slot)] = 0;
}
CLEAN_AS(func_020731a4, Session_ResetPeerSilence)

/* func_020731c4: whether a peer has not been heard for more than PEER_SILENCE_LIMIT frames.
 * QUIRK: the argument is ignored; the session is read through data_020ccf94.
 * QUIRK: the results of the first func_02077b58 call and of func_02077a64 are not used. */
int Session_AnyPeerSilent(NetSession *ignored)
{
    NetSession *session = data_020ccf94;
    (void) ignored;

    for (int slot = SESSION_SLOTS - 1; slot >= 0; slot--) {
        if (func_02073dd4(session, slot) == 0 || func_02073918(session, slot) != 0) {
            continue;
        }
        func_02077b58(slot);
        u16 silence = Session_GetPeerSilence(session, (u32) slot);
        func_02077a64();
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
    return session->peer_silence[func_02077b58((int) slot)];
}
CLEAN_AS(func_02073220, Session_GetPeerSilence)

/* func_0207323c: once a frame, counts a frame of silence for every peer, up to one past the
 * limit.
 * QUIRK: which slots are peers is read through data_020ccf94, the counters written through the
 * argument (the only caller passes data_020ccf94). The result of func_02077a64 is not used. */
void Session_AgePeerSilence(NetSession *session)
{
    NetSession *current = data_020ccf94;

    for (int slot = SESSION_SLOTS - 1; slot >= 0; slot--) {
        if (func_02073dd4(current, slot) == 0 || func_02073918(current, slot) != 0) {
            continue;
        }
        int peer = func_02077b58(slot);
        u16 silence = Session_GetPeerSilence(current, (u32) slot);
        func_02077a64();
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
    u8 *dst = func_02073d28(session, SHARE_BLOCK) + session->share_length;
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
        func_02077a34(&header[HEADER_SOURCE], &scene, &slot);
        u16 size = func_02077868(header);
        func_02076168(header[HEADER_HANDLER], message, size, header[HEADER_KIND], scene, slot);
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
    func_02077a34(&header[HEADER_SOURCE], &scene, &slot);
    if (scene != func_020b65c4()) {
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
    if (func_02073dd4(session, local_slot) == 0) {
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
    func_02077a34(&header[HEADER_SOURCE], &scene, &slot);

    int owner = func_020a71ec(scene);
    if (owner >= SESSION_SLOTS) {
        return;
    }

    if (owner == local_slot) {
        u32 local_length = Session_GetLocalQueueLength(session);
        u8 *dst = Session_GetLocalQueue(session) + local_length;
        for (u32 done = 0; done < length;) {
            MI_CpuCopy8(message, header, MESSAGE_HEADER_SIZE);
            u32 whole = (u32) func_02077868(header) + MESSAGE_HEADER_SIZE;
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
            u16 size = func_02077868(header);
            func_02073820(session);
            func_020737f0(session, message, size);
            func_02073770(session, header[HEADER_HANDLER], header[HEADER_KIND]);
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
