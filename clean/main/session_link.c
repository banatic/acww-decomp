/* Starting, running and ending the multiplayer session (session_link.h). */
#include "session_link.h"

#include <stddef.h>

#include "autoload_2/heap.h"
#include "autoload_2/network.h"
#include "clean.h"
#include "main/library_overlay.h"
#include "main/packed_bytes.h"
#include "main/player_messages.h"
#include "main/session_net.h"
#include "main/system_packet.h"
#include "main/wifi_friends.h"
#include "block_021d27ac.h"
#include "caution_window.h"
#include "field_label.h"
#include "fox_shop.h"
#include "link_global.h"
#include "link_scene.h"
#include "link_state.h"
#include "map_code.h"
#include "object_claim.h"
#include "place_claim.h"
#include "player_id.h"
#include "player_record.h"
#include "player_records.h"
#include "room_cells.h"
#include "room_object_state.h"
#include "scene_claim.h"
#include "scene_heaps.h"
#include "scene_query.h"
#include "session_players.h"
#include "session_record.h"
#include "town_name.h"
#include "town_objects.h"
#include "villager_state.h"

static_assert(offsetof(NetSession, max_record_size) == 0x6d, "max record size");
static_assert(offsetof(NetSession, record_scratch) == 0x70, "record scratch");
static_assert(offsetof(NetSession, active) == 0x74, "active");

#define NO_SLOT 4     /* NetSession.local_slot without a slot */
#define NO_PLAYER 4   /* NetSession.local_player without a player */
#define NO_REQUEST 3  /* NetSession.mode_request without a request */
#define SHARE_BLOCK 4 /* Session_GetSendBlock(session, 4): the start of the send blocks */
#define ALL_PLAYERS 4 /* Session_OnPlayersChanged: every slot at once */
#define BLOCK_ALIGN 4 /* the alignment of the session's buffers */

/* The bytes of a message header (session.h). */
#define HEADER_KIND 3
#define HEADER_SOURCE 4

/* The link state statuses this file sets or tests (session_link.h). */
#define STATUS_WAITING 4
#define STATUS_PENDING_FIRST 5 /* 5 and 6: to be told by the host */
#define STATUS_DONE 7

/* System packet kinds sent here (system_packet.c). */
#define SYSTEM_SET_SENDER_STATUS 5
#define SYSTEM_SET_OWN_STATUS 6

/* The network library's start parameters: the game code "KMDA" and the game ids of play and of
 * the wireless exchange, and the timeout in ticks. */
#define GAME_CODE 0x41444d4b
#define GAME_ID_PLAY 0x00c0001b
#define GAME_ID_EXCHANGE 0x00c0001c
#define NET_TIMEOUT 0x004fe752
#define EXCHANGE_PLAYERS 2

#define NET_HEAP_SIZE 0x4b000

extern NetSession *data_020ccf94; /* the session */
extern Heap *data_021c9b30;       /* the network heap */
extern u8 data_021d0a34[];        /* a 1-byte credits packet for each peer */
extern u8 data_021dc7a8[];        /* the state block (state_block.h) */

extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
extern void MI_CpuFill8(void *dst, u8 value, u32 size);
extern void DC_FlushAll(void);
extern u32 OS_EnableInterrupts(void);
extern u32 OS_DisableInterrupts(void);

/* The network heap's allocator and its free (SessionNet_Alloc, SessionNet_Free) at the game's
 * addresses, as the library is handed them. */
extern void *func_02077afc(int size, int align);
extern void func_02077ae8(void *block);

extern void func_02099e78(void); /* does nothing; the friend-deleted callback */
/* The receive callback handed to the library: Session_OnReceived. */
extern void func_02075050(int aid, char *buffer, unsigned int size);

/* -value as the ARM computes it: the most negative int stays itself. */
static int negate(int value)
{
    return (int) (0u - (u32) value);
}

/* Whether `slot` holds another system: taken, and not this system's. */
static int is_peer(NetSession *session, int slot)
{
    return Session_IsSlotTaken(session, slot) != 0 && Session_IsLocalSlot(session, slot) == 0;
}

/* func_02073f00: empties the session: no slots, no mode, no credits, nothing queued or
 * received, no sequence, no waits and no connect mode. */
void Session_Reset(NetSession *session)
{
    Session_ClearSlots(session);
    Session_SetMode(session, SESSION_MODE_NONE);
    Session_SetModeRequest(session, NO_REQUEST);
    Session_ResetCredits(session);
    Session_ClearOwedCredits(session);
    Session_ClearRecv(session);
    session->local_slot = NO_SLOT;
    Session_ClearRecordFlags(session);
    Session_ClearSendBuffer(session);
    Session_ClearOutbox(session);
    Session_ClearHeldQueue(session);
    Session_ClearSceneQueue(session);
    Session_ClearLocalQueue(session);
    Session_ClearBundle15Length(session);
    Session_ClearBundle16Length(session);
    Session_ClearPendingSequence(session);
    Session_ClearSequence(session);
    Session_ClearPeerSilence(session);
    Session_SetSendWait(session, 0);
    Session_SetSendWaitLimit(session, 0);
    Session_SetConnectMode(session, 0);
}
CLEAN_AS(func_02073f00, Session_Reset)

/* func_02073f90: no player at this system, no players and no errors. */
void Session_ResetPlayer(NetSession *session)
{
    session->local_player = NO_PLAYER;
    Session_ClearPlayerCount(session);
    Session_SetShownErrorFlags(session, 0);
    Session_SetErrorFlags(session, 0);
}
CLEAN_AS(func_02073f90, Session_ResetPlayer)

/* func_02073fb4 */
void Session_Init(NetSession *session)
{
    Session_ResetPlayer(session);
    Session_Reset(session);
}
CLEAN_AS(func_02073fb4, Session_Init)

/* func_02073fc8: the session's destructor, registered for the global session (data_021d0a44). */
void Session_Destroy(NetSession *session)
{
    (void) session;
}
CLEAN_AS(func_02073fc8, Session_Destroy)

/* func_02073fcc: the session's constructor. */
NetSession *Session_Construct(NetSession *session)
{
    Session_Init(session);
    return session;
}
CLEAN_AS(func_02073fcc, Session_Construct)

/* func_02073fdc: whether the link is lost. First, while a send wait runs: it ends when this
 * frame's packets may be sent, and the link is lost once it has lasted its limit (else it is
 * counted). Then by `expected_aids`: when negative, the link is lost without any connected
 * system; as the host (AID 0), when one of the AIDs it gives is not connected; as a guest, with
 * expected_aids above 0, when the connection's update fails. */
int Session_IsLinkLost(int expected_aids)
{
    NetSession *session = data_020ccf94;
    u16 limit = Session_GetSendWaitLimit(session);
    if (limit != 0) {
        if (Session_IsSendReady(session) != 0) {
            Session_SetSendWait(session, 0);
            Session_SetSendWaitLimit(session, 0);
        } else {
            u16 waited = Session_GetSendWait(session);
            if (waited >= limit) {
                return 1;
            }
            Session_SetSendWait(session, (u16) (waited + 1));
        }
    }

    if (expected_aids < 0) {
        return Net_GetConnectedMask() == 0;
    }
    u16 expected = (u16) expected_aids;
    if (Net_GetMyAid() == 0) {
        return (expected & Net_GetConnectedMask()) != expected;
    }
    if (expected_aids == 0) {
        return 0;
    }
    LibraryOverlay_RequireAny();
    return Net_UpdateConnection() == 0;
}
CLEAN_AS(func_02073fdc, Session_IsLinkLost)

/* func_02074078 */
void Session_RaiseSendTimeout(void)
{
    NetSession *session = data_020ccf94;
    u32 flags = Session_GetErrorFlags(session);
    if ((flags & SESSION_ERROR_SEND_TIMEOUT) == 0) {
        Session_SetErrorFlags(session, (int) (flags | SESSION_ERROR_SEND_TIMEOUT));
    }
}
CLEAN_AS(func_02074078, Session_RaiseSendTimeout)

/* func_020740a0: resets the link state and ends the session. */
void Session_Close(void)
{
    Session_ResetLinkStatus();
    Session_End();
}
CLEAN_AS(func_020740a0, Session_Close)

/* func_020740b4: one bit per member slot: the peers' and this system's.
 * REQUIRES: the local slot is not negative (it is 0-4). */
unsigned int Session_GetMemberMask(void)
{
    unsigned int mask = (unsigned int) Session_GetPeerMask();
    int local_slot = data_020ccf94->local_slot;
    if (local_slot < SESSION_SLOTS) {
        mask |= (u16) (1 << local_slot);
    }
    return mask;
}
CLEAN_AS(func_020740b4, Session_GetMemberMask)

/* func_020740dc: one bit per peer's slot. */
int Session_GetPeerMask(void)
{
    NetSession *session = data_020ccf94;
    int mask = 0;
    for (int slot = SESSION_SLOTS - 1; slot >= 0; slot--) {
        if (is_peer(session, slot)) {
            mask |= 1 << slot;
        }
    }
    return mask;
}
CLEAN_AS(func_020740dc, Session_GetPeerMask)

/* func_02074120: sets this system's link status (slot 3's without a slot) to 7. */
void Session_FinishLocalStatus(void)
{
    NetSession *session = data_020ccf94;
    int slot = session->local_slot;
    if (Session_IsSlotTaken(session, slot) == 0) {
        LinkGlobal_SetStatus(SESSION_UNLINKED_SLOT, STATUS_DONE);
    } else {
        LinkGlobal_SetStatus(slot, STATUS_DONE);
    }
}
CLEAN_AS(func_02074120, Session_FinishLocalStatus)

/* func_02074150: this system's link status (slot 3's without a slot). */
int Session_GetLocalStatus(void)
{
    NetSession *session = data_020ccf94;
    int slot = session->local_slot;
    if (Session_IsSlotTaken(session, slot) == 0) {
        return LinkGlobal_Status(SESSION_UNLINKED_SLOT);
    }
    return LinkGlobal_Status(slot);
}
CLEAN_AS(func_02074150, Session_GetLocalStatus)

/* func_0207417c: makes `status` this system's link status. The host sets it; a guest sets 4
 * and sends `status` to the host in a message (handler 0, kind 0). Without a slot, slot 3's
 * status becomes 4 and a system packet "set the sender's status" is sent to AID 0 at once,
 * with the result of that send.
 * QUIRK: without a slot the packet carries status 0, not `status`. */
int Session_SendLocalStatus(int status)
{
    NetSession *session = data_020ccf94;
    int slot = session->local_slot;
    if (Session_IsSlotTaken(session, slot) == 0) {
        LinkGlobal_SetStatus(SESSION_UNLINKED_SLOT, STATUS_WAITING);
        u8 *packet = Session_GetSendBlock(session, SHARE_BLOCK);
        SessionNet_WriteSystemHeader(packet, 0, SYSTEM_SET_SENDER_STATUS);
        packet[1] = 0;
        return Session_SendBlocks(session, Session_GetSendBlock(session, SHARE_BLOCK), 2, 1, NULL, 0, 0, NULL, 0, 0);
    }
    if (Session_IsLocalSlot(session, 0) != 0) {
        LinkGlobal_SetStatus(slot, status);
    } else {
        LinkGlobal_SetStatus(slot, STATUS_WAITING);
        u8 byte = (u8) status;
        session = data_020ccf94;
        Session_BeginMessage(session);
        Session_AppendMessage(session, &byte, 1);
        Session_EndMessage(session, 0, 0);
    }
    return 1;
}
CLEAN_AS(func_0207417c, Session_SendLocalStatus)

/* func_02074228: gives the library each other AID's receive buffer: the first block of the
 * peer's receive queue (AIDs above this system's are one peer lower). */
void Session_SetReceiveBuffers(u32 local_aid)
{
    NetSession *session = data_020ccf94;
    for (int aid = SESSION_SLOTS - 1; aid >= 0; aid--) {
        if ((u32) aid < local_aid) {
            u8 *block = Session_GetPeerRecvBlock(session, aid, 0);
            LibraryOverlay_RequireAny();
            Net_SetReceiveBuffer(aid, block, SESSION_BLOCK_SIZE);
        } else if ((u32) aid > local_aid) {
            u8 *block = Session_GetPeerRecvBlock(session, aid - 1, 0);
            LibraryOverlay_RequireAny();
            Net_SetReceiveBuffer(aid, block, SESSION_BLOCK_SIZE);
        }
    }
}
CLEAN_AS(func_02074228, Session_SetReceiveBuffers)

/* func_0207428c */
void Session_ResetLinkStatus(void)
{
    LinkState_GlobalReset();
}
CLEAN_AS(func_0207428c, Session_ResetLinkStatus)

/* func_02074294: no transfer for now, and the receive buffers for this AID. */
void Session_StopTransfer(u32 local_aid)
{
    Session_SetMode(data_020ccf94, SESSION_MODE_NONE);
    Session_SetReceiveBuffers(local_aid);
}
CLEAN_AS(func_02074294, Session_StopTransfer)

/* func_020742b4: this system hosts: data mode, slot 0 taken by itself, the receive buffers of
 * AID 0, and its link state entry set to the current scene. */
void Session_Host(void)
{
    NetSession *session = data_020ccf94;
    Session_SetMode(session, SESSION_MODE_DATA);
    session->local_slot = 0;
    Session_SetSlotTaken(session, session->local_slot, 1);
    Session_SetReceiveBuffers(0);
    LinkScene_Empty6C8C();
    LinkGlobal_SetPlace(0, SceneQuery_Current(), 1, 0, 7);
}
CLEAN_AS(func_020742b4, Session_Host)

/* func_020742fc */
void Session_SetHostReceiveBuffers(void)
{
    Session_SetReceiveBuffers(0);
}
CLEAN_AS(func_020742fc, Session_SetHostReceiveBuffers)

/* func_02074308: a send of no packets, which restarts the send wait. */
int Session_SendNothing(void)
{
    return Session_SendBlocks(data_020ccf94, NULL, 0, 0, NULL, 0, 0, NULL, 0, 0);
}
CLEAN_AS(func_02074308, Session_SendNothing)

/* The packets of one send: for each peer index a block, its size and the AIDs it goes to. */
typedef struct Sends {
    const u8 *block[SESSION_PEERS];
    int size[SESSION_PEERS];
    u16 to[SESSION_PEERS];
} Sends;

static int send_all(NetSession *session, const Sends *sends)
{
    return Session_SendBlocks(session, sends->block[0], sends->size[0], sends->to[0], sends->block[1], sends->size[1],
                              sends->to[1], sends->block[2], sends->size[2], sends->to[2]);
}

/* The send buffer moves to the outbox; SESSION_ERROR_OUTBOX_FULL says whether it could. */
static void flush_send_buffer(NetSession *session)
{
    u32 length = Session_GetSendLength(session);
    if (length == 0) {
        return;
    }
    u32 flags = Session_GetErrorFlags(session);
    if (Session_QueueOutgoing(session, Session_GetSendBuffer(session), (int) length) != 0) {
        Session_ClearSendBuffer(session);
        if ((flags & SESSION_ERROR_OUTBOX_FULL) != 0 && CautionWindow_IsShuttingDown() == 0) {
            Session_SetErrorFlags(session, (int) (flags ^ SESSION_ERROR_OUTBOX_FULL));
        }
    } else if ((flags & SESSION_ERROR_OUTBOX_FULL) == 0) {
        Session_SetErrorFlags(session, (int) (flags | SESSION_ERROR_OUTBOX_FULL));
    }
}

/* SESSION_MODE_DATA with a credit for every peer: each peer's packet is its credits back, the
 * changed shared records (written once, copied for the next peers) and the outbox's messages
 * for it; messages for this system go to the local queue. The host also sends a pending link
 * status to each free slot. When the send fails with other players, the messages the outbox
 * gave the held queue are dropped again and everything stays for the next frame. */
static void send_data(NetSession *session)
{
    u32 held_length = Session_GetHeldQueueLength(session);
    Session_WriteOwedCredits();
    const u8 *records = NULL;
    int records_size = 0;
    Sends sends = {{NULL}, {0}, {0}};

    for (int slot = SESSION_SLOTS - 1; slot >= 0; slot--) {
        if (Session_IsSlotTaken(session, slot) != 0) {
            if (Session_IsLocalSlot(session, slot) == 0) {
                u8 *data = Session_GetSendBlock(session, slot) + 1;
                int size = 1;
                if (records == NULL) {
                    records = data;
                    records_size = Session_WriteRecords(data, NULL, 0);
                } else {
                    Session_WriteRecords(data, records, records_size);
                }
                data += records_size;
                size += records_size;
                size += Session_CollectMessages(data, slot);
                int peer = SessionNet_PeerIndex(slot);
                sends.block[peer] = Session_GetSendBlock(session, slot);
                sends.size[peer] = size;
                sends.to[peer] = (u16) (1 << slot);
            } else {
                u32 length = Session_GetLocalQueueLength(session);
                u8 *queue = Session_GetLocalQueue(session);
                int added = Session_CollectMessages(queue + length, slot);
                if (added != 0) {
                    Session_SetLocalQueueLength(session, length + (u32) added);
                }
            }
        } else if (Session_IsLocalSlot(session, 0) != 0) {
            /* Slot 0 is this system's here, so slot - 1 is a peer index. */
            int size = Session_WriteStatusPacket(slot);
            if (size != 0) {
                sends.block[slot - 1] = Session_GetSendBlock(session, slot);
                sends.size[slot - 1] = size;
                sends.to[slot - 1] = (u16) (1 << slot);
            }
        }
    }

    int sent = send_all(session, &sends);
    if (sent == 0 && session->player_count > 1) {
        Session_SetHeldQueueLength(session, held_length);
        return;
    }
    Session_SetPendingSequence(session, (u16) Session_GetFrameSequence(session));
    Session_ClearRecordFlags(session);
    Session_ClearOutbox(session);
    for (int slot = SESSION_SLOTS - 1; slot >= 0; slot--) {
        if (Session_IsSlotTaken(session, slot) != 0) {
            if (Session_IsLocalSlot(session, slot) == 0) {
                Session_DisableInterrupts();
                Session_SpendCredits(session, slot, 1);
                Session_EnableInterrupts();
                Session_SetOwedCredits(session, slot, 0);
            }
        } else if (sent != 0 && Session_IsLocalSlot(session, 0) != 0 && Session_IsStatusPending(slot) != 0) {
            LinkGlobal_SetStatus(slot, STATUS_DONE);
        }
    }
    if (LinkScene_GlobalPhase() == 7) {
        LinkScene_GlobalSetPhase(8);
    }
}

/* SESSION_MODE_DATA while a peer has no credit: only the packets that give credits back are
 * sent, 1 byte each. Without any, the host with fewer than four players sends nothing, which
 * restarts the send wait. */
static void send_credits(NetSession *session)
{
    Session_WriteOwedCredits();
    Sends sends = {{NULL}, {0}, {0}};
    int count = 0;
    for (int slot = SESSION_SLOTS - 1; slot >= 0; slot--) {
        if (is_peer(session, slot)) {
            u8 *block = Session_GetSendBlock(session, slot);
            if (SessionNet_GetCredits(block) != 0) {
                sends.block[count] = block;
                sends.size[count] = 1;
                sends.to[count] = (u16) (1 << slot);
                count++;
            }
        }
    }
    if (count == 0) {
        if (Session_IsLocalSlot(session, 0) != 0 && session->player_count != SESSION_SLOTS) {
            Session_SendNothing();
        }
        return;
    }
    if (send_all(session, &sends) == 0 && session->player_count > 1) {
        return;
    }
    for (int slot = SESSION_SLOTS - 1; slot >= 0; slot--) {
        if (is_peer(session, slot)) {
            Session_SetOwedCredits(session, slot, 0);
        }
    }
}

/* SESSION_MODE_CREDITS: each peer owed credits is sent a system packet that gives them back. */
static void send_credit_packets(NetSession *session)
{
    if (Session_IsLinked(session) == 0) {
        return;
    }
    LibraryOverlay_RequireAny();
    if (Net_CanSend() == 0) {
        return;
    }
    Sends sends = {{NULL}, {0}, {0}};
    for (int slot = SESSION_SLOTS - 1; slot >= 0; slot--) {
        if (is_peer(session, slot)) {
            int owed = Session_GetOwedCredits(session, slot);
            int peer = SessionNet_PeerIndex(slot);
            if (owed != 0) {
                u8 *packet = &data_021d0a34[peer];
                SessionNet_WriteSystemHeader(packet, owed, SESSION_SYSTEM_CREDITS);
                sends.block[peer] = packet;
                sends.size[peer] = 1;
                sends.to[peer] = (u16) (1 << slot);
            }
        }
    }
    if (send_all(session, &sends) == 0) {
        return;
    }
    for (int slot = SESSION_SLOTS - 1; slot >= 0; slot--) {
        if (is_peer(session, slot)) {
            Session_SetOwedCredits(session, slot, 0);
        }
    }
}

/* The error flags of SESSION_MODE_DATA: a silent peer; for the host a peer whose AID is not
 * connected, for a guest a failed connection update. Flags 1 and 2 are cleared only while
 * func_02038a30 is false; the others stay. */
static void check_link(NetSession *session, int local_slot)
{
    Session_DisableInterrupts();
    Session_AgePeerSilence(session);
    Session_EnableInterrupts();
    Session_DisableInterrupts();
    int silent = Session_AnyPeerSilent(session);
    Session_EnableInterrupts();

    u32 flags = Session_GetErrorFlags(session);
    if (silent != 0) {
        if ((flags & SESSION_ERROR_PEER_SILENT) == 0) {
            Session_SetErrorFlags(session, (int) (flags | SESSION_ERROR_PEER_SILENT));
        }
    } else if ((flags & SESSION_ERROR_PEER_SILENT) != 0 && CautionWindow_IsShuttingDown() == 0) {
        Session_SetErrorFlags(session, (int) (flags ^ SESSION_ERROR_PEER_SILENT));
    }

    if (local_slot == 0) {
        u16 peers = 0;
        for (int slot = SESSION_SLOTS - 1; slot >= 0; slot--) {
            if (is_peer(session, slot)) {
                peers |= (u16) (1 << slot);
            }
        }
        if (peers != (peers & Net_GetConnectedMask())) {
            flags = Session_GetErrorFlags(session);
            if ((flags & SESSION_ERROR_PEER_MISSING) == 0) {
                Session_SetErrorFlags(session, (int) (flags | SESSION_ERROR_PEER_MISSING));
            }
        }
    } else {
        LibraryOverlay_RequireAny();
        if (Net_UpdateConnection() == 0) {
            flags = Session_GetErrorFlags(session);
            if ((flags & SESSION_ERROR_CONNECTION) == 0) {
                Session_SetErrorFlags(session, (int) (flags | SESSION_ERROR_CONNECTION));
            }
        }
    }
}

/* func_02074330: the session's frame, while this system has a slot. When the packets may be
 * sent, the pending sequence number is taken over and a request for SESSION_MODE_CREDITS is
 * granted. In any mode the send buffer moves to the outbox. When the packets may be sent they
 * are filled and sent for the mode; in SESSION_MODE_DATA the link is checked. Then the frame is
 * counted unless keep_frame is set. */
void Session_Update(int keep_frame)
{
    NetSession *session = data_020ccf94;
    int local_slot = session->local_slot;
    if (Session_IsSlotTaken(session, local_slot) == 0) {
        return;
    }

    int ready = Session_IsSendReady(session);
    if (ready != 0) {
        s16 pending = Session_GetPendingSequence(session);
        if (pending >= 0) {
            Session_SetSequence(session, (u16) pending);
            Session_ClearPendingSequence(session);
        }
        if (Session_GetModeRequest(session) == SESSION_MODE_CREDITS) {
            Session_SetMode(session, SESSION_MODE_CREDITS);
            Session_SetModeRequest(session, NO_REQUEST);
        }
    }

    int mode = Session_GetMode(session);
    if (mode != SESSION_MODE_NONE) {
        flush_send_buffer(session);
    }

    if (ready != 0) {
        if (mode == SESSION_MODE_DATA) {
            if (SessionNet_AllPeersHaveCredit() != 0) {
                send_data(session);
            } else {
                send_credits(session);
            }
        } else if (mode == SESSION_MODE_CREDITS) {
            send_credit_packets(session);
        }
    }

    if (mode == SESSION_MODE_DATA) {
        check_link(session, local_slot);
    }
    if (keep_frame == 0) {
        Session_CountFrame(session);
    }
}
CLEAN_AS(func_02074330, Session_Update)

/* func_02074904: unless skipped, hands the scene queue, the local queue and the received
 * packets to their handlers while this system has a slot and a mode. */
void Session_Deliver(int skip)
{
    if (skip != 0) {
        return;
    }
    NetSession *session = data_020ccf94;
    if (Session_IsSlotTaken(session, session->local_slot) == 0) {
        return;
    }
    if (Session_GetMode(session) == SESSION_MODE_NONE) {
        return;
    }
    Session_DeliverSceneQueue(session);
    Session_DeliverLocalQueue(session);
    Session_ProcessReceived(session);
}
CLEAN_AS(func_02074904, Session_Deliver)

/* func_02074944 */
void Session_FreeHeap(void)
{
    Net_Empty020ecf1c();
    SceneHeaps_DestroyNetwork();
}
CLEAN_AS(func_02074944, Session_FreeHeap)

/* Ends the network library with the network heap usable from any mode meanwhile; 0 when it
 * could not end (func_020b8d6c is told). */
static int end_library(void)
{
    int ended = 1;
    Heap *heap = data_021c9b30;
    int flags = Heap_SetFlags(heap, HEAP_FLAGS_READ_ONLY);
    Heap_SetFlags(heap, flags | HEAP_ANY_MODE);
    LibraryOverlay_RequireAny();
    if (Net_End() == 0) {
        FieldLabel_RaiseEndFailure();
        ended = 0;
    }
    Heap_SetFlags(heap, flags);
    return ended;
}

/* func_02074958: ends the wireless exchange (Session_StartExchange). */
void Session_EndExchange(void)
{
    if (data_020ccf94->active == 0) {
        return;
    }
    end_library();
    NetSession *session = data_020ccf94;
    Session_Reset(session);
    session->active = 0;
}
CLEAN_AS(func_02074958, Session_EndExchange)

/* func_020749c4: ends the session (Session_Start) and frees its buffers; 0 when the library
 * could not end, else 1 (also when nothing was started). */
int Session_End(void)
{
    int ended = 1;
    if (data_020ccf94->active != 0) {
        ended = end_library();
        NetSession *session = data_020ccf94;
        SessionNet_Free(Session_GetBundle16Buffer(session));
        Session_SetBundle16Buffer(session, NULL);
        SessionNet_Free(Session_GetBundle15Buffer(session));
        Session_SetBundle15Buffer(session, NULL);
        SessionNet_Free(Session_GetLocalQueue(session));
        Session_SetLocalQueueBuffer(session, NULL);
        SessionNet_Free(Session_GetSceneQueue(session));
        Session_SetSceneQueueBuffer(session, NULL);
        SessionNet_Free(Session_GetHeldQueue(session));
        Session_SetHeldQueueBuffer(session, NULL);
        SessionNet_Free(Session_GetOutbox(session));
        Session_SetOutbox(session, NULL);
        SessionNet_Free(Session_GetSendBuffer(session));
        Session_SetSendBuffer(session, NULL);
        SessionNet_Free(Session_GetRecvBlock(session, SESSION_SLOTS, 0));
        Session_SetRecvBlocks(session, NULL);
        SessionNet_Free(Session_GetSendBlock(session, SHARE_BLOCK));
        Session_SetSendBlocks(session, NULL);
        SessionNet_Free(session->record_scratch);
        session->record_scratch = NULL;
        SessionNet_Free(Session_GetRecordTable(session));
        Session_SetRecordTable(session, NULL);
        Session_Reset(session);
        session->active = 0;
    }
    return ended;
}
CLEAN_AS(func_020749c4, Session_End)

/* func_02074af8: starts the network library for the wireless exchange, for two systems. */
void Session_StartExchange(void)
{
    data_020ccf94->active = 1;
    LibraryOverlay_RequireAny();
    Net_Init(GAME_CODE, GAME_ID_EXCHANGE, 1, NET_TIMEOUT, EXCHANGE_PLAYERS, func_02077afc, func_02077ae8);
}
CLEAN_AS(func_02074af8, Session_StartExchange)

/* func_02074b44: allocates the shared records and the session's buffers, starts the network
 * library for `players` systems and sets it up for `mode`: the local wireless library for mode
 * 1 or 2; otherwise the Wi-Fi Connection, handed the friend list and a user block built from
 * this system's player record and the state block. Then the connect mode is kept.
 * QUIRK: only the low byte of `mode` chooses the library. */
void Session_Start(int mode, int players, int connect_mode)
{
    NetSession *session = data_020ccf94;
    session->active = 1;
    SessionRecord_Init();
    session->record_scratch = SessionNet_Alloc(session->max_record_size, BLOCK_ALIGN);
    Session_SetSendBlocks(session, SessionNet_Alloc(SESSION_PEERS * SESSION_BLOCK_SIZE, BLOCK_ALIGN));
    Session_SetRecvBlocks(session, SessionNet_Alloc(SESSION_PEERS * SESSION_RECV_ENTRIES * SESSION_BLOCK_SIZE, BLOCK_ALIGN));
    Session_SetSendBuffer(session, SessionNet_Alloc(SESSION_SEND_SIZE, BLOCK_ALIGN));
    Session_SetOutbox(session, SessionNet_Alloc(SESSION_SEND_SIZE, BLOCK_ALIGN));
    Session_SetHeldQueueBuffer(session, SessionNet_Alloc(SESSION_SEND_SIZE, BLOCK_ALIGN));
    Session_SetSceneQueueBuffer(session, SessionNet_Alloc(SESSION_SEND_SIZE, BLOCK_ALIGN));
    Session_SetLocalQueueBuffer(session, SessionNet_Alloc(SESSION_SEND_SIZE, BLOCK_ALIGN));
    Session_SetBundle15Buffer(session, SessionNet_Alloc(0xc00, BLOCK_ALIGN));
    Session_SetBundle16Buffer(session, SessionNet_Alloc(0xc00, BLOCK_ALIGN));
    LibraryOverlay_RequireAny();
    Net_Init(GAME_CODE, GAME_ID_PLAY, 1, NET_TIMEOUT, (u8) players, func_02077afc, func_02077ae8);

    if ((u8) mode == 1 || (u8) mode == 2) {
        LibraryOverlay_Require66();
        Local_Setup(mode, func_02075050);
    } else {
        NetSession *state = data_020ccf94;
        FriendList *friends = (FriendList *) Session_GetStartTable(state);
        u8 *user_block = Session_GetStartHeader(state);
        MI_CpuFill8(friends, 0, sizeof(FriendList));
        MI_CpuFill8(user_block, 0, sizeof(state->start_header));
        u8 *record = PlayerRecords_Current();
        WifiFriend *friend_record = WifiFriendList_GetEntries((WifiFriendList *) PlayerRecord_WifiFriends(record));
        for (int i = 0; i < FRIEND_COUNT; i++) {
            MI_CpuCopy8(WifiFriendData_GetData(WifiFriend_GetFriendData(friend_record)), friends->friend_data[i],
                        FRIEND_DATA_SIZE);
            friend_record++;
        }
        MI_CpuCopy8((const void *) (uintptr_t) PlayerId_Name((int) (uintptr_t) PlayerRecord_Player(record)), user_block, 0xc);
        MI_CpuCopy8((const void *) (uintptr_t) TownName_Name((int) (uintptr_t) (data_021dc7a8 + 2)), user_block + 0x10, 0xc);
        MI_CpuCopy8(WifiAccount_GetUserData((WifiAccount *) PlayerRecord_WifiAccount(record)), user_block + 0x20, 0x40);
        LibraryOverlay_Require65();
        Wfc_Setup(mode, func_02075050, (void (*)(int)) func_02099e78, user_block, friends);
    }
    Session_SetConnectMode(session, connect_mode);
}
CLEAN_AS(func_02074b44, Session_Start)

/* func_02074d24: notes the largest shared record's size (kept in a byte) and creates the
 * network heap. */
void Session_CreateHeap(void *parent)
{
    u32 largest = 0;
    for (int record = SESSION_RECORDS - 1; record >= 0; record--) {
        u32 size = SessionRecord_GetSize((u32) record);
        if (size > largest) {
            largest = size;
        }
    }
    data_020ccf94->max_record_size = (u8) largest;
    SceneHeaps_CreateNetwork(NET_HEAP_SIZE, parent);
    Net_Empty020ecf20();
}
CLEAN_AS(func_02074d24, Session_CreateHeap)

/* func_02074d60: the player at `slot` has left. Each taken slot's entry gets its second byte
 * set (1 for slot 0, else 0); the slot's entry becomes scene 63, 0, 0; the slot is freed, the
 * players counted one fewer, its credits and link state reset, and the game told. */
void Session_RemovePlayer(int slot)
{
    NetSession *session = data_020ccf94;
    for (int i = SESSION_SLOTS - 1; i >= 0; i--) {
        if (Session_IsSlotTaken(session, i) != 0) {
            if (i == 0) {
                LinkGlobal_SetPlace(0, 0x3f, 1, 0, 2);
            } else {
                LinkGlobal_SetPlace(i, 0x3f, 0, 0, 2);
            }
        }
    }
    LinkGlobal_SetPlace(slot, 0x3f, 0, 0, 7);

    session = data_020ccf94;
    Session_SetSlotTaken(session, slot, 0);
    Session_SetPlayerCount(session, (u8) (session->player_count - 1));
    Session_ResetCredit(session, slot);
    Session_SetOwedCredits(session, slot, 0);
    LinkState_GlobalForgetSlot(slot);
    Session_OnPlayersChanged(negate(slot));
}
CLEAN_AS(func_02074d60, Session_RemovePlayer)

/* func_02074dfc: when `slot`'s link status is pending, writes into its send block a system
 * packet "set your status" (status in bits 0-2, the member slots in bits 4-7); its size, 2,
 * else 0. */
int Session_WriteStatusPacket(int slot)
{
    if (Session_IsStatusPending(slot) == 0) {
        return 0;
    }
    u8 *packet = Session_GetSendBlock(data_020ccf94, slot);
    SessionNet_WriteSystemHeader(packet, 0, SYSTEM_SET_OWN_STATUS);
    int status = LinkGlobal_Status(slot);
    unsigned int members = Session_GetMemberMask();
    packet[1] = (u8) ((status & 7) | ((members << 4) & 0xf0));
    return 2;
}
CLEAN_AS(func_02074dfc, Session_WriteStatusPacket)

/* func_02074e48: whether `slot`'s link status is 5 or 6. */
int Session_IsStatusPending(int slot)
{
    u32 status = (u32) LinkGlobal_Status(slot);
    return status - STATUS_PENDING_FIRST <= 1;
}
CLEAN_AS(func_02074e48, Session_IsStatusPending)

/* func_02074e64: walks the outbox: each message that must wait is added to the held queue,
 * each message for `slot` copied to `dst`; the bytes copied to `dst`.
 * QUIRK: func_020b65c4 is called for each message and its answer not used. */
int Session_CollectMessages(u8 *dst, int slot)
{
    NetSession *session = data_020ccf94;
    u32 taken = 0;
    u32 outbox_length = Session_GetOutboxLength(session);
    const u8 *message = Session_GetOutbox(session);
    for (u32 offset = 0; offset < outbox_length;) {
        u8 header[MESSAGE_HEADER_SIZE];
        MI_CpuCopy8(message, header, MESSAGE_HEADER_SIZE);
        u8 kind = header[HEADER_KIND];
        u8 scene;
        u8 sender;
        PackedBytes_SplitScene(&header[HEADER_SOURCE], &scene, &sender);
        u32 size = MESSAGE_HEADER_SIZE + (u32) PackedBytes_ReadU16(header);
        SceneQuery_Current();
        u8 hold;
        int to = LinkGlobal_MessageTarget(slot, kind, scene, &hold);
        if (hold != 0) {
            u32 held = Session_GetHeldQueueLength(session);
            u8 *queue = Session_GetHeldQueue(session);
            MI_CpuCopy8(message, queue + held, size);
            Session_SetHeldQueueLength(session, held + size);
        } else if (to == slot) {
            MI_CpuCopy8(message, dst, size);
            dst += size;
            taken += size;
        }
        message += size;
        offset += size;
    }
    return (int) taken;
}
CLEAN_AS(func_02074e64, Session_CollectMessages)

/* func_02074f28: the shared records part of a packet at `dst`, and its size. Given `copy`, the
 * `size` bytes there (the part written for another peer). Else each record to send (from the
 * last) as its id and its bytes, then an end id of 70. */
int Session_WriteRecords(u8 *dst, const u8 *copy, int size)
{
    if (copy != NULL) {
        MI_CpuCopy8(copy, dst, (u32) size);
        return size;
    }
    NetSession *session = data_020ccf94;
    int written = 0;
    for (int id = SESSION_RECORDS - 1; id >= 0; id--) {
        if (Session_GetRecordFlag(session, id) != 0) {
            u8 tag = (u8) id;
            MI_CpuCopy8(&tag, dst, 1);
            dst++;
            written++;
            const u8 *record = Session_GetRecord(session, id);
            u32 length = SessionRecord_GetSize((u32) id);
            MI_CpuCopy8(record, dst, length);
            dst += length;
            written += (int) length;
        }
    }
    *dst = SESSION_RECORDS;
    return written + 1;
}
CLEAN_AS(func_02074f28, Session_WriteRecords)

/* func_02074fa0: starts each peer's packet with the credits owed back to it. */
void Session_WriteOwedCredits(void)
{
    NetSession *session = data_020ccf94;
    for (int slot = SESSION_SLOTS - 1; slot >= 0; slot--) {
        if (is_peer(session, slot)) {
            u8 *packet = Session_GetSendBlock(session, slot);
            int owed = Session_GetOwedCredits(session, slot);
            SessionNet_WriteDataHeader(packet, owed);
        }
    }
}
CLEAN_AS(func_02074fa0, Session_WriteOwedCredits)

/* func_02074fec */
int Session_HasReachedSequence(int sequence)
{
    return Session_IsSequenceReached(sequence, Session_GetSequence(data_020ccf94));
}
CLEAN_AS(func_02074fec, Session_HasReachedSequence)

/* func_0207500c: whether `current` has reached `sequence`, 15-bit numbers that wrap: never
 * without a current number (negative), always for no sequence (negative).
 * QUIRK: a difference past half the range is wrapped by 0x7fff, not 0x8000, and a large
 * negative one mirrored (0x7fff - diff) rather than shifted; only the sign is used, which comes
 * out the same for 15-bit numbers. */
int Session_IsSequenceReached(int sequence, int current)
{
    if (current < 0) {
        return 0;
    }
    if (sequence < 0) {
        return 1;
    }
    int diff = sequence - current;
    if (diff == 0) {
        return 1;
    }
    if (diff > 0x3fff) {
        diff -= 0x7fff;
    } else if (diff < -0x3fff) {
        diff = (int) (0x7fffu - (u32) diff);
    }
    return diff <= 0;
}
CLEAN_AS(func_0207500c, Session_IsSequenceReached)

/* func_02075050: the receive callback (Net_SetReceiveBuffer's buffers). The credits the packet
 * gives back are added. A system packet goes to its handler (kinds below 24). A data packet
 * shows the peer is there and, with more than its first byte, takes the next entry of its
 * receive queue; the library then receives into the entry after it.
 * HW: the data cache is flushed before the packet is read.
 * REQUIRES: aid is 0-3 (the library's AIDs). */
void Session_OnReceived(int aid, char *packet, unsigned int size)
{
    const u8 *bytes = (const u8 *) packet;
    DC_FlushAll();
    int credits = SessionNet_GetCredits(bytes);
    if (credits != 0) {
        Session_AddCredits(data_020ccf94, aid, credits);
    }
    if (SessionNet_IsSystemPacket(bytes) != 0) {
        int kind = SessionNet_GetSystemKind(bytes);
        if (kind < SESSION_SYSTEM_CREDITS) {
            SystemPacket_Dispatch((u8 *) packet + 1, size - 1, aid, kind);
        }
        return;
    }
    Session_ResetPeerSilence(data_020ccf94, aid);
    if (size > 1) {
        NetSession *session = data_020ccf94;
        Session_SetRecvLength(session, aid, Session_GetRecvWriteEntry(session, aid), (int) size);
        Session_PushRecvEntry(session, aid);
        u8 *block = Session_GetRecvBlock(session, aid, Session_GetRecvWriteEntry(session, aid));
        LibraryOverlay_RequireAny();
        Net_SetReceiveBuffer((u16) aid, block, SESSION_BLOCK_SIZE);
    }
}
CLEAN_AS(func_02075050, Session_OnReceived)

/* func_020750f4
 * HW: enables the CPU's interrupts (the receive callback runs from them). */
void Session_EnableInterrupts(void)
{
    OS_EnableInterrupts();
}
CLEAN_AS(func_020750f4, Session_EnableInterrupts)

/* func_020750fc
 * HW: disables the CPU's interrupts. */
void Session_DisableInterrupts(void)
{
    OS_DisableInterrupts();
}
CLEAN_AS(func_020750fc, Session_DisableInterrupts)

/* func_02075104: tells the game the players changed: `change` is a slot that joined, minus a
 * slot that left, or 4 / -4 for all of them. Leaving is cleaned up after (for the host, or
 * without a slot): the 34 ids from 0x5000, func_02051e38 and the 51 indexes of func_0209d57c
 * for the slot (slots 1-3 for -4), then func_02096204 for it (slots 0-3 for -4). The peer of a
 * single slot is then counted as heard. */
void Session_OnPlayersChanged(int change)
{
    if (change == ALL_PLAYERS) {
        VillagerState_Clear();
        Block021d27ac_Reset(Block021d27ac_Get());
    }
    RoomCells_ResetAll();
    RoomObjectState_Clear();
    TownObjects_ResetRecordedModes();
    ObjectClaim_Reset();
    PlayerMessages_ClearReply();

    if (change < 0) {
        NetSession *session = data_020ccf94;
        if (Session_IsLocalSlot(session, 0) != 0 || Session_IsLocalSlot(session, NO_SLOT) != 0) {
            if (change == -ALL_PLAYERS) {
                for (u32 i = 0; i < 34; i++) {
                    u16 id = MapCode_Building(i);
                    TownObjects_Leave(id, 1);
                    TownObjects_Leave(id, 2);
                    TownObjects_Leave(id, 3);
                }
                PlaceClaim_Release(1);
                PlaceClaim_Release(2);
                PlaceClaim_Release(3);
                for (u32 i = 0; i < 51; i++) {
                    SceneClaim_Release((u8) i, 1);
                    SceneClaim_Release((u8) i, 2);
                    SceneClaim_Release((u8) i, 3);
                }
            } else {
                int slot = negate(change);
                for (u32 i = 0; i < 34; i++) {
                    TownObjects_Leave(MapCode_Building(i), slot);
                }
                PlaceClaim_Release(slot);
                for (u32 i = 0; i < 51; i++) {
                    SceneClaim_Release((u8) i, slot);
                }
            }
        }
        if (change == -ALL_PLAYERS) {
            for (u32 slot = 0; slot < SESSION_SLOTS; slot++) {
                SessionPlayers_ClearSaved(slot);
            }
        } else {
            SessionPlayers_ClearSaved((u32) negate(change));
        }
    }
    if (change == -ALL_PLAYERS) {
        FoxPassword_ClearVisitor();
    }
    int slot = change < 0 ? negate(change) : change;
    if (slot < ALL_PLAYERS) {
        Session_ResetPeerSilence(data_020ccf94, slot);
    }
}
CLEAN_AS(func_02075104, Session_OnPlayersChanged)
