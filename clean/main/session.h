/* The multiplayer session (data_020ccf94): up to four systems in slots 0-3, this system's slot
 * at 0x64 (4 when it has none). Each other system is a peer, numbered 0-2 by func_02077b58
 * (the slots in order, without this system's).
 *
 * Every frame each peer is sent one packet from its block in send_blocks and its packets are
 * received into a queue of three blocks in recv_blocks (Session_SendBlocks, func_02074330; the
 * receive callback func_02075050). A packet starts with a byte whose low two bits give credits
 * back and whose top bit marks a system packet (func_02077b20, func_02077b28), then the shared
 * records that changed (an id below 70 and the record's bytes, ended by an id of 70 or more),
 * then messages. A peer is sent a data packet only while it has a credit, one per free entry of
 * its receive queue; each packet this system takes from a peer's queue is a credit owed back.
 *
 * A message is a 5-byte header and its payload:
 *   bytes 0-1  the payload's length (little-endian, read by func_02077868);
 *   byte 2     the handler: an index into the table func_02076168 calls through;
 *   byte 3     a kind the handler receives (6 and 7 select where Session_ProcessReceived
 *              delivers it);
 *   byte 4     the sender's scene (low 6 bits) and slot (top 2 bits), split by func_02077a34.
 * A handler reads its payload with Session_ReadMessage, from the cursor func_02076168 sets.
 * A message is built in the send buffer (Session_BeginMessage, Session_AppendMessage,
 * Session_EndMessage); once a frame the send buffer moves to the outbox, from which the
 * packets are filled.
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

#define SESSION_RECV_ENTRIES 3    /* the blocks of a peer's receive queue */
#define SESSION_BLOCK_SIZE 0x1000 /* a send or receive block */
#define SESSION_RECORDS 70        /* the shared records (sizes data_020ccfa8, offsets data_020cd050) */
#define SESSION_SEND_SIZE 0x91a   /* the send buffer and the outbox */

/* The transfer mode (0x06). */
enum {
    SESSION_MODE_NONE = 0,
    SESSION_MODE_CREDITS = 1, /* only credits are given back */
    SESSION_MODE_DATA = 2     /* records and messages are exchanged */
};

typedef struct NetSession {
    u8 slot_taken[SESSION_SLOTS];                         /* 0x00 */
    u16 frame_count;                                      /* 0x04: its low 15 bits make a sequence number */
    u8 mode;                                              /* 0x06: SESSION_MODE_* */
    u8 mode_request;                                      /* 0x07: 3 for none; 1 asks for SESSION_MODE_CREDITS */
    u8 *send_blocks;                                      /* 0x08: one block per peer */
    int credits[SESSION_PEERS];                           /* 0x0c: packets each peer can still take */
    int owed_credits[SESSION_PEERS];                      /* 0x18: packets taken from each peer, not given back */
    u8 *recv_blocks;                                      /* 0x24: SESSION_RECV_ENTRIES blocks per peer */
    u32 recv_length[SESSION_PEERS][SESSION_RECV_ENTRIES]; /* 0x28: each received packet's length */
    u32 recv_head[SESSION_PEERS];                         /* 0x4c: the oldest entry of each receive queue */
    u32 recv_count[SESSION_PEERS];                        /* 0x58: the entries in each receive queue */
    int local_slot;                                       /* 0x64: this system's slot; 4 when it has none */
    int local_player;                                     /* 0x68: the player number at this system */
    u8 player_count;                                      /* 0x6c: 0-4 */
    u8 unk_06d[0x78 - 0x6d];
    u8 *record_table;                 /* 0x78: the shared records (0x6a0 bytes) */
    u8 record_flags[SESSION_RECORDS]; /* 0x7c: set for a record to send */
    u8 unk_0c2[2];
    u8 *send_buffer;                 /* 0xc4: SESSION_SEND_SIZE bytes */
    u32 send_length;                 /* 0xc8: the bytes of finished messages */
    u8 *send_end;                    /* 0xcc: where the next message starts */
    u8 *message_start;               /* 0xd0: the message being built */
    u8 *message_cursor;              /* 0xd4: where its next byte goes */
    u8 *outbox;                      /* 0xd8: SESSION_SEND_SIZE bytes */
    u32 outbox_length;               /* 0xdc */
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

int Session_QueueOutgoing(NetSession *ignored, const u8 *data, int size);
u32 Session_GetOutboxLength(NetSession *session);
void Session_SetOutboxLength(NetSession *session, u32 length);
void Session_ClearOutbox(NetSession *session);
void Session_SetOutbox(NetSession *session, u8 *buffer);
u8 *Session_GetOutbox(NetSession *session);

void Session_EndMessage(NetSession *session, u32 handler, u32 kind);
void Session_AppendMessage(NetSession *session, const void *data, int size);
void Session_BeginMessage(NetSession *session);
u32 Session_GetSendLength(NetSession *session);
void Session_SetSendLength(NetSession *session, u32 length);
void Session_ClearSendBuffer(NetSession *session);
void Session_SetSendBuffer(NetSession *session, u8 *buffer);
u8 *Session_GetSendBuffer(NetSession *session);

void Session_ClearRecordFlags(NetSession *session);
void Session_SetRecordFlag(NetSession *session, int id, int value);
int Session_GetRecordFlag(NetSession *session, int id);
u8 *Session_GetRecord(NetSession *session, int id);
void Session_SetRecordTable(NetSession *session, u8 *table);
u8 *Session_GetRecordTable(NetSession *session);

void Session_ClearPlayerCount(NetSession *session);
void Session_SetPlayerCount(NetSession *session, u32 count);
int Session_IsLocalPlayer(NetSession *session, int player);
int Session_IsLocalSlot(NetSession *session, int slot);

int Session_GetRecvWriteEntry(NetSession *session, int slot);
int Session_GetRecvReadEntry(NetSession *session, int slot);
void Session_PopRecvEntry(NetSession *session, int slot);
void Session_PushRecvEntry(NetSession *session, int slot);
void Session_ClearRecvQueues(NetSession *session);
void Session_ProcessReceived(NetSession *session);
void Session_ClearRecv(NetSession *session);
void Session_ClearRecvLength(NetSession *session, int slot, int entry);
void Session_SetRecvLength(NetSession *session, int slot, int entry, int length);
u32 Session_GetRecvLength(NetSession *session, int slot, int entry);
void Session_SetRecvBlocks(NetSession *session, u8 *blocks);
u8 *Session_GetPeerRecvBlock(NetSession *session, int peer, int entry);
u8 *Session_GetRecvBlock(NetSession *session, int slot, int entry);

void Session_ClearOwedCredits(NetSession *session);
void Session_OweCredit(NetSession *session, int slot);
void Session_SetOwedCredits(NetSession *session, int slot, int count);
int Session_GetOwedCredits(NetSession *session, int slot);
void Session_ResetCredits(NetSession *session);
void Session_ResetCredit(NetSession *session, int slot);
void Session_SpendCredits(NetSession *session, int slot, int count);
void Session_AddCredits(NetSession *session, int slot, int count);
int Session_GetCredits(NetSession *session, int slot);

u8 *Session_GetSendBlock(NetSession *session, int slot);
void Session_SetSendBlocks(NetSession *session, u8 *blocks);
int Session_GetModeRequest(NetSession *session);
void Session_SetModeRequest(NetSession *session, int request);
int Session_GetMode(NetSession *session);
void Session_SetMode(NetSession *session, int mode);
void Session_CountFrame(NetSession *session);
s16 Session_GetFrameSequence(NetSession *session);
int Session_IsLinked(NetSession *session);
void Session_ClearSlots(NetSession *session);
u8 Session_IsSlotTaken(const NetSession *session, int slot);
void Session_SetSlotTaken(NetSession *session, int slot, int taken);
int Session_IsSendReady(NetSession *session);
int Session_SendBlocks(NetSession *session, const u8 *block0, int size0, int to0, const u8 *block1, int size1, u16 to1,
                       const u8 *block2, int size2, u16 to2);

#endif
