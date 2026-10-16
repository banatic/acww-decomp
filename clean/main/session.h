/* The multiplayer session (data_020ccf94): up to four systems in slots 0-3, this system's slot
 * at 0x64. This part covers its message queues, the two section bundles, the shared-data block
 * length, the sequence numbers, the error flags and the per-peer silence counters.
 *
 * A message is a 5-byte header and its payload:
 *   bytes 0-1  the payload's length (little-endian, read by func_02077868);
 *   byte 2     the handler: an index into the table func_02076168 calls through;
 *   byte 3     a kind the handler receives (6 and 7 select where func_020739d0 delivers it);
 *   byte 4     the sender's scene (low 6 bits) and slot (top 2 bits), split by func_02077a34.
 * A handler reads its payload with Session_ReadMessage, from the cursor func_02076168 sets.
 *
 * Three queues hold whole messages for later:
 *   held   (0xe4)  messages for a scene whose owner is not known; Session_RouteHeldMessages
 *                  moves them to the local queue or sends them on;
 *   scene  (0xec)  messages that wait until this system is in the sender's scene;
 *   local  (0xf4)  messages addressed to this system itself.
 *
 * The two bundles are messages of category 15 and 16 built from several sections (each a
 * 4-byte header and its data) behind a 2-byte total; func_020a75d4 and func_020a74bc build
 * them, func_020a753c and func_020a7454 hand their sections out. */
#ifndef CLEAN_MAIN_SESSION_H
#define CLEAN_MAIN_SESSION_H

#include "types.h"

#define SESSION_SLOTS 4
#define SESSION_PEERS 3 /* the other systems: slots without this system's */

#define MESSAGE_HEADER_SIZE 5

typedef struct NetSession {
    u8 unk_000[0x64];
    int local_slot; /* 0x64: this system's slot; 4 when it has none */
    u8 unk_068[0xe0 - 0x68];
    const u8 *read_cursor;           /* 0xe0: the payload of the message being handled */
    u8 *held_queue;                  /* 0xe4 */
    u32 held_length;                 /* 0xe8 */
    u8 *scene_queue;                 /* 0xec */
    u32 scene_length;                /* 0xf0 */
    u8 *local_queue;                 /* 0xf4 */
    u32 local_length;                /* 0xf8 */
    u8 *bundle15;                    /* 0xfc: the category 15 bundle (0xc00 bytes) */
    u32 bundle15_length;             /* 0x100 */
    u8 *bundle15_cursor;             /* 0x104: where the section being built writes */
    u8 *bundle16;                    /* 0x108: the category 16 bundle (0xc00 bytes) */
    u32 bundle16_length;             /* 0x10c */
    u8 *bundle16_cursor;             /* 0x110 */
    s16 pending_sequence;            /* 0x114: -1, or the sequence number to take over next frame */
    s16 sequence;                    /* 0x116: a 15-bit sequence number (compared by func_0207500c), or -1 */
    u32 share_length;                /* 0x118: bytes written to the shared-data block (func_02073d28(s, 4)) */
    u32 shown_error_flags;           /* 0x11c: the error flags the error screen shows */
    u32 error_flags;                 /* 0x120 */
    u32 connect_mode;                /* 0x124: the mode the session was started with (func_02074b44) */
    u16 peer_silence[SESSION_PEERS]; /* 0x128: frames since each peer was last heard */
    u16 send_wait;                   /* 0x12e: frames waited since the last shared-data send */
    u16 send_wait_limit;             /* 0x130: 0 when not waiting */
    u16 slot_mask;                   /* 0x132: one bit per slot (func_020740b4) */
    u8 start_table[0x5e0];           /* 0x134: handed to func_020ecba8 on start */
    u8 start_header[0x60];           /* 0x714: handed to func_020ecba8 on start */
} NetSession;

u8 *Session_GetStartHeader(NetSession *session);
u8 *Session_GetStartTable(NetSession *session);
void Session_SetSlotMask(NetSession *session, u16 mask);

u16 Session_GetSendWaitLimit(NetSession *session);
void Session_SetSendWaitLimit(NetSession *session, u16 frames);
u16 Session_GetSendWait(NetSession *session);
void Session_SetSendWait(NetSession *session, u16 frames);

void Session_ClearPeerSilence(NetSession *session);
void Session_ResetPeerSilence(NetSession *session, int slot);
int Session_AnyPeerSilent(NetSession *ignored);
u16 Session_GetPeerSilence(NetSession *session, u32 slot);
void Session_AgePeerSilence(NetSession *session);

u32 Session_GetConnectMode(NetSession *session);
void Session_SetConnectMode(NetSession *session, int mode);
u32 Session_GetErrorFlags(NetSession *session);
void Session_SetErrorFlags(NetSession *session, int flags);
u32 Session_GetShownErrorFlags(NetSession *session);
void Session_SetShownErrorFlags(NetSession *session, int flags);

void Session_AppendShareData(NetSession *session, const void *data, int size);
void Session_ClearShareLength(NetSession *session);
u32 Session_GetShareLength(NetSession *session);
void Session_SetShareLength(NetSession *session, int length);

void Session_ClearSequence(NetSession *session);
void Session_ClearPendingSequence(NetSession *session);
int Session_GetSequence(NetSession *session);
s16 Session_GetPendingSequence(NetSession *session);
void Session_SetSequence(NetSession *session, u16 sequence);
void Session_SetPendingSequence(NetSession *session, u16 sequence);

u32 Session_GetBundle16Length(NetSession *session);
void Session_SetBundle16Length(NetSession *session, int length);
void Session_ClearBundle16Length(NetSession *session);
void Session_SetBundle16Buffer(NetSession *session, u8 *buffer);
u8 *Session_GetBundle16Buffer(NetSession *session);
void Session_AppendBundle15(NetSession *session, const void *data, u32 size);
u32 Session_GetBundle15Length(NetSession *session);
void Session_SetBundle15Length(NetSession *session, int length);
void Session_ClearBundle15Length(NetSession *session);
void Session_SetBundle15Buffer(NetSession *session, u8 *buffer);
u8 *Session_GetBundle15Buffer(NetSession *session);

void Session_DeliverLocalQueue(NetSession *session);
u32 Session_GetLocalQueueLength(NetSession *session);
void Session_SetLocalQueueLength(NetSession *session, u32 length);
void Session_ClearLocalQueue(NetSession *session);
void Session_SetLocalQueueBuffer(NetSession *session, u8 *buffer);
u8 *Session_GetLocalQueue(NetSession *session);

void Session_DeliverSceneQueue(NetSession *session);
u32 Session_GetSceneQueueLength(NetSession *session);
void Session_SetSceneQueueLength(NetSession *session, u32 length);
void Session_ClearSceneQueue(NetSession *session);
void Session_SetSceneQueueBuffer(NetSession *session, u8 *buffer);
u8 *Session_GetSceneQueue(NetSession *session);

void Session_RouteHeldMessages(NetSession *session);
u32 Session_GetHeldQueueLength(NetSession *session);
void Session_SetHeldQueueLength(NetSession *session, u32 length);
void Session_ClearHeldQueue(NetSession *session);
void Session_SetHeldQueueBuffer(NetSession *session, u8 *buffer);
u8 *Session_GetHeldQueue(NetSession *session);

void Session_ReadMessage(NetSession *session, void *dst, int size);
const u8 *Session_GetReadCursor(NetSession *session);
void Session_SetReadCursor(NetSession *session, const u8 *cursor);

#endif
