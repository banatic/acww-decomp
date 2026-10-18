/* The handlers of system packets (system_packet.h). */
#include "system_packet.h"

#include "autoload_2/network.h"
#include "clean.h"
#include "main/calendar.h"
#include "main/library_overlay.h"
#include "main/session.h"
#include "main/session_link.h"
#include "main/session_net.h"
#include "activity.h"
#include "date_time.h"
#include "exchange_block.h"
#include "link_global.h"
#include "link_parts.h"
#include "link_scene.h"
#include "link_state.h"
#include "player_record.h"
#include "player_records.h"
#include "scene_query.h"
#include "session_players.h"
#include "system_command.h"
#include "town_pack.h"

/* The scenes (func_020b65c4) the activity handlers act in. */
#define SCENE_09 9
#define SCENE_0C 12
#define SCENE_0D 13
#define SCENE_2E 46
#define SCENE_2F 47

#define UNLINKED_SLOT 3 /* the link state slot of this system while it has no slot */
#define SHARE_BLOCK 4   /* Session_GetSendBlock(session, 4): where system packets are built */
#define TO_HOST 1       /* the AID mask of the host (AID 0) */
#define OWN_BLOCK 4     /* func_02090040(4): this system's 0x950-byte block */
#define SLOT_BLOCK_SIZE 0x950
#define PLAYER_RECORD_SIZE 0x249c   /* a player record (func_0209847c) */
#define RECORD_BLOCK_SIZE 0x3200    /* the block func_020989e0 gives for a player record */
#define SHARED_RECORDS_SIZE 0x6a0   /* the session's shared records (Session_GetRecordTable) */
#define ACTIVITY_BUFFER_MAX 0x17400 /* the activity buffer's size while its first word is 0 */

/* The system packet kinds sent here. */
enum {
    SYSTEM_SET_ACTIVITY_MEMBERS = 0,
    SYSTEM_WRITE_ACTIVITY_BUFFER = 1,
    SYSTEM_WRITE_SLOT_BLOCK = 2,
    SYSTEM_SET_OWN_BLOCK = 3,
    SYSTEM_WRITE_SENDER_BLOCK = 4,
    SYSTEM_SET_LINK_FLAG_C4 = 7,
    SYSTEM_REQUEST_MODE = 8,
    SYSTEM_SET_ACTIVITY_FLAG_D9 = 9,
    SYSTEM_SET_ACTIVITY_DATA_DC = 10,
    SYSTEM_SET_ACTIVITY_FLAG_E4 = 11,
    SYSTEM_WRITE_SHARED_RECORDS = 12,
    SYSTEM_SET_ACTIVITY_PLAYER_EF = 14,
    SYSTEM_SET_LINK_ENTRIES = 15,
    SYSTEM_SET_ACTIVITY_PLAYER_F8 = 16,
    SYSTEM_SET_ACTIVITY_PLAYER_FC = 17,
    SYSTEM_SET_ACTIVITY_FLAG_E5 = 18,
    SYSTEM_SET_ACTIVITY_PLAYER_F4 = 19,
    SYSTEM_SET_ACTIVITY_PLAYER_100 = 20,
    SYSTEM_WRITE_OWN_RECORD = 21,
    SYSTEM_WRITE_RECORD_BLOCK = 22,
    SYSTEM_SET_ACTIVITY_FLAG_101 = 23
};

/* SystemPacket_SendSlotBlocks: what a guest's packet carries. */
enum {
    SLOT_BLOCK_KEEP = 0,  /* the byte 0: the guest keeps its block */
    SLOT_BLOCK_CLEAR = 1, /* the byte 1: the guest clears its block */
    SLOT_BLOCK_COPY = 2,  /* the block itself */
    SLOT_BLOCK_NONE = 3   /* no packet */
};
#define NO_REQUEST 3 /* NetSession.mode_request without a request */

extern NetSession *data_020ccf94;                  /* the session */
extern SystemPacketHandler *const data_020ccff0[]; /* the handlers, by kind */

extern void MI_CpuCopy8(const void *src, void *dst, u32 size);

extern void *func_02137550(void *dst, u32 size); /* clears size bytes (none for NULL) */

/* Whether every peer among the AIDs of `to` can take a packet (has a credit). */

/* func_02075240
 * REQUIRES: kind < 24 (Session_OnReceived checks). */
void SystemPacket_Dispatch(u8 *payload, u32 length, int sender, int kind)
{
    data_020ccff0[kind](payload, length, sender);
}
CLEAN_AS(func_02075240, SystemPacket_Dispatch)

/* func_02075254 */
void SystemPacket_SetActivityFlag101(u8 *payload, u32 length, int sender)
{
    (void) payload;
    (void) length;
    (void) sender;
    if (SceneQuery_Current() == SCENE_2E && Activity_Current() != NULL) {
        Activity_SetFlag101(Activity_Current(), 1);
    }
}
CLEAN_AS(func_02075254, SystemPacket_SetActivityFlag101)

/* func_02075278: the payload's offset (4 bytes) and data, written into the block of this
 * system's player record that func_020989e0 gives. */
void SystemPacket_WriteRecordBlock(u8 *payload, u32 length, int sender)
{
    (void) sender;
    u32 offset;
    MI_CpuCopy8(payload, &offset, 4);
    u8 *block = (u8 *) PlayerRecord_KeptLetters(PlayerRecords_Current());
    MI_CpuCopy8(payload + 4, block + offset, length - 4);
}
CLEAN_AS(func_02075278, SystemPacket_WriteRecordBlock)

/* func_020752a8: in scene 46 with an activity: the payload's offset (4 bytes) and data,
 * written into this system's player record, after func_020962a4 is given player 0 and the
 * activity's byte 0x102.
 * QUIRK: the session's local player becomes 0 on the way. */
void SystemPacket_WriteOwnRecord(u8 *payload, u32 length, int sender)
{
    (void) sender;
    if (SceneQuery_Current() != SCENE_2E) {
        return;
    }
    if (Activity_Current() == NULL) {
        return;
    }
    int offset;
    MI_CpuCopy8(payload, &offset, 4);
    u8 value = Activity_Byte102(Activity_Current());
    NetSession *session = data_020ccf94;
    session->local_player = 0;
    SessionPlayers_SetRecordNumber(session->local_player, value);
    u8 *record = PlayerRecords_Current();
    MI_CpuCopy8(payload + 4, record + offset, length - 4);
}
CLEAN_AS(func_020752a8, SystemPacket_WriteOwnRecord)

/* func_02075300 */
void SystemPacket_SetActivityPlayer100(u8 *payload, u32 length, int sender)
{
    (void) payload;
    (void) length;
    Activity_SetCurrentSlot100((u8) sender);
}
CLEAN_AS(func_02075300, SystemPacket_SetActivityPlayer100)

/* func_0207530c */
void SystemPacket_SetActivityPlayerF4(u8 *payload, u32 length, int sender)
{
    (void) payload;
    (void) length;
    if (SceneQuery_Current() == SCENE_2E && Activity_Current() != NULL) {
        Activity_SetSlotAck(Activity_Current(), sender, 1);
    }
}
CLEAN_AS(func_0207530c, SystemPacket_SetActivityPlayerF4)

/* func_02075334 */
void SystemPacket_SetActivityFlagE5(u8 *payload, u32 length, int sender)
{
    (void) payload;
    (void) length;
    (void) sender;
    if (SceneQuery_Current() == SCENE_2E && Activity_Current() != NULL) {
        Activity_SetFlagE5(Activity_Current(), 1);
    }
}
CLEAN_AS(func_02075334, SystemPacket_SetActivityFlagE5)

/* func_02075358 */
void SystemPacket_SetActivityPlayerFC(u8 *payload, u32 length, int sender)
{
    (void) payload;
    (void) length;
    if (SceneQuery_Current() == SCENE_2E && Activity_Current() != NULL) {
        Activity_SetSlotFC(Activity_Current(), sender, 1);
    }
}
CLEAN_AS(func_02075358, SystemPacket_SetActivityPlayerFC)

/* func_02075380 */
void SystemPacket_SetActivityPlayerF8(u8 *payload, u32 length, int sender)
{
    (void) payload;
    (void) length;
    if (SceneQuery_Current() == SCENE_2E && Activity_Current() != NULL) {
        Activity_SetSlotReported(Activity_Current(), sender, 1);
    }
}
CLEAN_AS(func_02075380, SystemPacket_SetActivityPlayerF8)

/* func_020753a8: the four slots' link state entries, 2 bytes each. */
void SystemPacket_SetLinkEntries(u8 *payload, u32 length, int sender)
{
    (void) length;
    (void) sender;
    for (u32 slot = 0; slot < 4; slot++) {
        u8 entry[2];
        u8 byte0;
        u8 byte1;
        u8 byte2;
        u32 fields;
        LinkPart_MakeEntryB(entry);
        MI_CpuCopy8(payload, entry, 2);
        LinkPart_ReadEntryChange(entry, &byte0, &byte1, &byte2, (s32 *) &fields);
        LinkGlobal_SetPlace((int) slot, byte0, byte1, byte2, (int) fields);
        payload += 2;
        LinkPart_EndEntryB(entry);
    }
}
CLEAN_AS(func_020753a8, SystemPacket_SetLinkEntries)

/* func_02075404: in scene 46 or 9 with an activity: its byte 0xef + player becomes the
 * payload's byte, for the sender's player as the host (AID 0), else for player 0. */
void SystemPacket_SetActivityPlayerEF(u8 *payload, u32 length, int sender)
{
    (void) length;
    if (SceneQuery_Current() == SCENE_2E || SceneQuery_Current() == SCENE_09) {
        u8 *activity = (u8 *) Activity_Current();
        if (activity != NULL) {
            if (Net_GetMyAid() == 0) {
                Activity_SetSlotAnswer((Activity *) (void *) activity, sender, *payload);
            } else {
                Activity_SetSlotAnswer((Activity *) (void *) activity, 0, *payload);
            }
        }
    }
}
CLEAN_AS(func_02075404, SystemPacket_SetActivityPlayerEF)

/* func_02075448 */
void SystemPacket_RunCommands(u8 *payload, u32 length, int sender)
{
    (void) sender;
    SystemCommand_RunList(payload, length);
}
CLEAN_AS(func_02075448, SystemPacket_RunCommands)

/* func_02075450: the payload's offset (4 bytes) and data, written into the shared records. */
void SystemPacket_WriteSharedRecords(u8 *payload, u32 length, int sender)
{
    (void) sender;
    int offset;
    MI_CpuCopy8(payload, &offset, 4);
    u8 *records = Session_GetRecordTable(data_020ccf94);
    MI_CpuCopy8(payload + 4, records + offset, length - 4);
}
CLEAN_AS(func_02075450, SystemPacket_WriteSharedRecords)

/* func_02075484 */
void SystemPacket_SetActivityFlagE4(u8 *payload, u32 length, int sender)
{
    (void) payload;
    (void) length;
    (void) sender;
    if (SceneQuery_Current() == SCENE_0D || SceneQuery_Current() == SCENE_2F) {
        if (Activity_Current() != NULL) {
            Activity_SetFlagE4(Activity_Current(), 1);
        }
    }
}
CLEAN_AS(func_02075484, SystemPacket_SetActivityFlagE4)

/* func_020754b0: in scene 12 with an activity: the payload's 8 bytes into its bytes from 0xdc,
 * and its flag 0xda set. */
void SystemPacket_SetActivityDataDC(u8 *payload, u32 length, int sender)
{
    (void) length;
    (void) sender;
    if (SceneQuery_Current() != SCENE_0C) {
        return;
    }
    if (Activity_Current() == NULL) {
        return;
    }
    MI_CpuCopy8(payload, Activity_DateTime(Activity_Current()), 8);
    Activity_SetFlagDA(Activity_Current(), 1);
}
CLEAN_AS(func_020754b0, SystemPacket_SetActivityDataDC)

/* func_020754e8 */
void SystemPacket_SetActivityFlagD9(u8 *payload, u32 length, int sender)
{
    (void) payload;
    (void) length;
    (void) sender;
    if (SceneQuery_Current() == SCENE_0D || SceneQuery_Current() == SCENE_2F) {
        if (Activity_Current() != NULL) {
            Activity_SetFlagD9(Activity_Current(), 1);
        }
    }
}
CLEAN_AS(func_020754e8, SystemPacket_SetActivityFlagD9)

/* func_02075514: the payload's byte becomes the mode request, unless one is pending. */
void SystemPacket_RequestMode(u8 *payload, u32 length, int sender)
{
    (void) length;
    (void) sender;
    NetSession *session = data_020ccf94;
    if (Session_GetModeRequest(session) == NO_REQUEST) {
        Session_SetModeRequest(session, *payload);
    }
}
CLEAN_AS(func_02075514, SystemPacket_RequestMode)

/* func_0207553c */
void SystemPacket_SetLinkFlagC4(u8 *payload, u32 length, int sender)
{
    (void) payload;
    (void) length;
    (void) sender;
    LinkState_GlobalSetByteC4(1);
}
CLEAN_AS(func_0207553c, SystemPacket_SetLinkFlagC4)

/* func_02075548: from the host to a system without a slot (Session_WriteStatusPacket): its
 * link status (slot 3's) from bits 0-2 and the member slots from bits 4-7. */
void SystemPacket_SetOwnStatus(u8 *payload, u32 length, int sender)
{
    (void) length;
    (void) sender;
    u8 byte = *payload;
    LinkGlobal_SetStatus(UNLINKED_SLOT, byte & 7);
    LinkGlobal_SetMemberMask((u16) ((byte >> 4) & 0xf));
}
CLEAN_AS(func_02075548, SystemPacket_SetOwnStatus)

/* func_0207556c: the sender's link status becomes the payload's byte. */
void SystemPacket_SetSenderStatus(u8 *payload, u32 length, int sender)
{
    (void) length;
    LinkGlobal_SetStatus(sender, *payload);
}
CLEAN_AS(func_0207556c, SystemPacket_SetSenderStatus)

/* func_0207557c: the payload's offset (4 bytes) and data, written into the block
 * func_0209847c gives for sender + 3; then func_020962a4 is told the sender and that number. */
void SystemPacket_WriteSenderBlock(u8 *payload, u32 length, int sender)
{
    int offset;
    MI_CpuCopy8(payload, &offset, 4);
    int which = sender + 3;
    u8 *record = PlayerRecords_Get(which);
    MI_CpuCopy8(payload + 4, record + offset, length - 4);
    SessionPlayers_SetRecordNumber(sender, which);
}
CLEAN_AS(func_0207557c, SystemPacket_WriteSenderBlock)

/* func_020755b4: from the host (SystemPacket_SendSlotBlocks): this system's 0x950-byte block,
 * cleared when the payload is the single byte 1 and left as it is for the byte 0; then in
 * scene 46 the activity's flag 0x107 + this system's slot is set.
 * QUIRK: any payload longer than one byte is copied as 0x950 bytes whatever its length. */
void SystemPacket_SetOwnBlock(u8 *payload, u32 length, int sender)
{
    (void) sender;
    if (length == 1) {
        if (*payload != SLOT_BLOCK_KEEP) {
            ExchangeBlock_Clear((ExchangeBlock *) (uintptr_t) ExchangeBlock_OfSlot(OWN_BLOCK));
        }
    } else {
        MI_CpuCopy8(payload, (void *) (uintptr_t) ExchangeBlock_OfSlot(OWN_BLOCK), SLOT_BLOCK_SIZE);
    }
    if (SceneQuery_Current() != SCENE_2E) {
        return;
    }
    if (Activity_Current() == NULL) {
        return;
    }
    Activity_SetSlot107(Activity_Current(), data_020ccf94->local_slot, 1);
}
CLEAN_AS(func_020755b4, SystemPacket_SetOwnBlock)

/* func_0207560c: a chunk of the sender's 0x950-byte block (its offset and bytes), or with no
 * payload the block cleared; then in scene 13 or 47 the activity's flag 0x107 + sender is set.
 * REQUIRES: length is 0 or at least 4. */
void SystemPacket_WriteSlotBlock(u8 *payload, u32 length, int sender)
{
    if (length != 0) {
        int offset;
        MI_CpuCopy8(payload, &offset, 4);
        u8 *block = (u8 *) (uintptr_t) ExchangeBlock_OfSlot(sender);
        MI_CpuCopy8(payload + 4, block + offset, length - 4);
    } else {
        ExchangeBlock_Clear((ExchangeBlock *) (uintptr_t) ExchangeBlock_OfSlot(sender));
    }
    if (SceneQuery_Current() == SCENE_0D || SceneQuery_Current() == SCENE_2F) {
        if (Activity_Current() != NULL) {
            Activity_SetSlot107(Activity_Current(), sender, 1);
        }
    }
}
CLEAN_AS(func_0207560c, SystemPacket_WriteSlotBlock)

/* func_02075670: in scene 12, a chunk (offset and bytes) of the activity's buffer; once the
 * chunk reaches the end of the data the buffer expects (its first word + 4, or 0x17400 while
 * that word is 0), the activity's thread is started.
 * REQUIRES: length >= 4 and an activity with a buffer. */
void SystemPacket_WriteActivityBuffer(u8 *payload, u32 length, int sender)
{
    (void) sender;
    if (SceneQuery_Current() != SCENE_0C) {
        return;
    }
    u32 offset;
    MI_CpuCopy8(payload, &offset, 4);
    u8 *buffer = (u8 *) Activity_CurrentPackBuffer();
    MI_CpuCopy8(payload + 4, buffer + offset, length - 4);
    u32 expected = TownPack_PackedSize((TownPackBuffer *) (void *) buffer);
    u32 end = expected == 0 ? ACTIVITY_BUFFER_MAX : expected + 4;
    if (offset + (length - 4) < end) {
        return;
    }
    TownPack_StartThread(Activity_CurrentPackThread(), NULL);
}
CLEAN_AS(func_02075670, SystemPacket_WriteActivityBuffer)

/* func_020756cc: in scene 12 with an activity: the payload's byte gives the activity's slot
 * mask (bits 0-3) and its byte 0xd7 (bits 6-7; SystemPacket_SendActivityMembers). */
void SystemPacket_SetActivityMembers(u8 *payload, u32 length, int sender)
{
    (void) length;
    (void) sender;
    if (SceneQuery_Current() != SCENE_0C) {
        return;
    }
    if (Activity_Current() == NULL) {
        return;
    }
    u8 byte = *payload;
    Activity_SetSlotMask(Activity_Current(), byte & 0xf);
    Activity_SetByteD7(Activity_Current(), (byte >> 6) & 3);
}
CLEAN_AS(func_020756cc, SystemPacket_SetActivityMembers)

/* ---- Senders */

/* Whether the network can send now. */
static int system_packet_network_ready(void)
{
    LibraryOverlay_RequireAny();
    return Net_CanSend() != 0;
}

/* Whether a system packet can go to the AIDs of `to` now: the network can send and each of
 * those peers has a credit. */
static int system_packet_can_send(u32 to)
{
    if (!system_packet_network_ready()) {
        return 0;
    }
    return SessionNet_PeersHaveCredit(to) != 0;
}

/* Sends the packet built in the share block, `length` bytes, to the AIDs of `to`. */
static int system_packet_send(NetSession *session, int length, int to)
{
    return Session_SendBlocks(session, Session_GetSendBlock(session, SHARE_BLOCK), length, to, NULL, 0, 0, NULL, 0, 0);
}

/* Sends a packet of only its first byte, of `kind`, to the AIDs of `to`; 0 when it cannot go.
 * QUIRK: with `ask_slot0` it first asks whether slot 0 is this system's (Session_IsLocalSlot)
 * and does not use the answer. */
static int system_packet_send_kind(int kind, int to, int ask_slot0)
{
    if (!system_packet_can_send((u32) to)) {
        return 0;
    }
    NetSession *session = data_020ccf94;
    if (ask_slot0) {
        Session_IsLocalSlot(session, 0);
    }
    SessionNet_WriteSystemHeader(Session_GetSendBlock(session, SHARE_BLOCK), 0, kind);
    return system_packet_send(session, 1, to);
}

/* func_0207570c */
int SystemPacket_SendActivityFlag101(void)
{
    return system_packet_send_kind(SYSTEM_SET_ACTIVITY_FLAG_101, TO_HOST, 1);
}
CLEAN_AS(func_0207570c, SystemPacket_SendActivityFlag101)

/* func_02075774: the next chunk of the block func_020989e0 gives for this system's player
 * record, to the host. */
int SystemPacket_SendRecordBlock(u8 *chunks_sent)
{
    u8 *record = PlayerRecords_Get(SessionPlayers_RecordNumber(data_020ccf94->local_player));
    u8 *block = (u8 *) PlayerRecord_KeptLetters(record);
    return SystemPacket_SendInChunks(chunks_sent, block, RECORD_BLOCK_SIZE, SYSTEM_WRITE_RECORD_BLOCK, TO_HOST);
}
CLEAN_AS(func_02075774, SystemPacket_SendRecordBlock)

/* func_020757ac: the next chunk of this system's player record, to the host. */
int SystemPacket_SendOwnRecord(u8 *chunks_sent)
{
    u8 *record = PlayerRecords_Get(SessionPlayers_RecordNumber(data_020ccf94->local_player));
    return SystemPacket_SendInChunks(chunks_sent, record, PLAYER_RECORD_SIZE, SYSTEM_WRITE_OWN_RECORD, TO_HOST);
}
CLEAN_AS(func_020757ac, SystemPacket_SendOwnRecord)

/* func_020757e0 */
int SystemPacket_SendActivityPlayer100(void)
{
    return system_packet_send_kind(SYSTEM_SET_ACTIVITY_PLAYER_100, TO_HOST, 1);
}
CLEAN_AS(func_020757e0, SystemPacket_SendActivityPlayer100)

/* func_02075848
 * QUIRK: asks for the peer mask (Session_GetPeerMask) after writing the packet and does not
 * use it. */
int SystemPacket_SendActivityPlayerF4(void)
{
    if (!system_packet_can_send(TO_HOST)) {
        return 0;
    }
    NetSession *session = data_020ccf94;
    SessionNet_WriteSystemHeader(Session_GetSendBlock(session, SHARE_BLOCK), 0, SYSTEM_SET_ACTIVITY_PLAYER_F4);
    Session_GetPeerMask();
    return system_packet_send(session, 1, TO_HOST);
}
CLEAN_AS(func_02075848, SystemPacket_SendActivityPlayerF4)

/* func_020758ac */
int SystemPacket_SendActivityFlagE5(int to)
{
    return system_packet_send_kind(SYSTEM_SET_ACTIVITY_FLAG_E5, to, 1);
}
CLEAN_AS(func_020758ac, SystemPacket_SendActivityFlagE5)

/* func_02075918 */
int SystemPacket_SendActivityPlayerFC(void)
{
    return system_packet_send_kind(SYSTEM_SET_ACTIVITY_PLAYER_FC, TO_HOST, 0);
}
CLEAN_AS(func_02075918, SystemPacket_SendActivityPlayerFC)

/* func_02075978 */
int SystemPacket_SendActivityPlayerF8(void)
{
    return system_packet_send_kind(SYSTEM_SET_ACTIVITY_PLAYER_F8, TO_HOST, 1);
}
CLEAN_AS(func_02075978, SystemPacket_SendActivityPlayerF8)

/* func_020759e0: the four slots' link state entries, 2 bytes each, to the system in `slot`.
 * REQUIRES: 0 <= slot < 32. */
int SystemPacket_SendLinkEntries(int slot)
{
    u16 to = (u16) (1u << slot);
    if (!system_packet_can_send(to)) {
        return 0;
    }
    u8 *packet = Session_GetSendBlock(data_020ccf94, SHARE_BLOCK);
    SessionNet_WriteSystemHeader(packet, 0, SYSTEM_SET_LINK_ENTRIES);
    u8 *write = packet + 1;
    int length = 1;
    for (u32 i = 0; i < 4; i++) {
        u8 byte0;
        u8 byte1;
        u8 byte2;
        u8 entry[2];
        LinkScene_GlobalPlace((int) i, &byte0, &byte1, &byte2);
        LinkPart_MakeEntryB(entry);
        LinkPart_WriteEntryChange(entry, byte0, byte1, byte2, 7);
        MI_CpuCopy8(entry, write, 2);
        write += 2;
        length += 2;
        LinkPart_EndEntryB(entry);
    }
    return system_packet_send(data_020ccf94, length, to);
}
CLEAN_AS(func_020759e0, SystemPacket_SendLinkEntries)

/* func_02075aa4: the byte `value`; 1 at once when `to` is empty. */
int SystemPacket_SendActivityPlayerEF(int value, int to)
{
    if (to == 0) {
        return 1;
    }
    if (!system_packet_can_send((u32) to)) {
        return 0;
    }
    NetSession *session = data_020ccf94;
    u8 *packet = Session_GetSendBlock(session, SHARE_BLOCK);
    SessionNet_WriteSystemHeader(packet, 0, SYSTEM_SET_ACTIVITY_PLAYER_EF);
    packet[1] = (u8) value;
    return system_packet_send(session, 2, to);
}
CLEAN_AS(func_02075aa4, SystemPacket_SendActivityPlayerEF)

/* func_02075b14: the clock's date and time (8 bytes, SystemPacket_SetActivityDataDC). */
int SystemPacket_SendDateTime(int to)
{
    if (!system_packet_can_send((u32) to)) {
        return 0;
    }
    NetSession *session = data_020ccf94;
    Session_IsLocalSlot(session, 0); /* QUIRK: the answer is not used */
    u8 *packet = Session_GetSendBlock(session, SHARE_BLOCK);
    SessionNet_WriteSystemHeader(packet, 0, SYSTEM_SET_ACTIVITY_DATA_DC);
    DateTime now = {0};
    DateTime_Now(&now);
    MI_CpuCopy8(&now, packet + 1, sizeof(now));
    return system_packet_send(session, 1 + (int) sizeof(now), to);
}
CLEAN_AS(func_02075b14, SystemPacket_SendDateTime)

/* func_02075b98 */
int SystemPacket_SendActivityFlagD9(void)
{
    return system_packet_send_kind(SYSTEM_SET_ACTIVITY_FLAG_D9, TO_HOST, 1);
}
CLEAN_AS(func_02075b98, SystemPacket_SendActivityFlagD9)

/* func_02075c00 */
int SystemPacket_SendActivityFlagE4(int to)
{
    return system_packet_send_kind(SYSTEM_SET_ACTIVITY_FLAG_E4, to, 0);
}
CLEAN_AS(func_02075c00, SystemPacket_SendActivityFlagE4)

/* func_02075c64 */
int SystemPacket_SendLinkFlagC4(void)
{
    return system_packet_send_kind(SYSTEM_SET_LINK_FLAG_C4, TO_HOST, 0);
}
CLEAN_AS(func_02075c64, SystemPacket_SendLinkFlagC4)

/* func_02075cc4: asks every peer for SESSION_MODE_CREDITS (SystemPacket_RequestMode); 1 at
 * once when there is no peer. */
int SystemPacket_SendModeRequest(void)
{
    int to = Session_GetPeerMask();
    if (to == 0) {
        return 1;
    }
    if (!system_packet_can_send((u32) to)) {
        return 0;
    }
    NetSession *session = data_020ccf94;
    Session_IsLocalSlot(session, 0); /* QUIRK: the answer is not used */
    u8 *packet = Session_GetSendBlock(session, SHARE_BLOCK);
    SessionNet_WriteSystemHeader(packet, 0, SYSTEM_REQUEST_MODE);
    packet[1] = SESSION_MODE_CREDITS;
    return system_packet_send(session, 2, to);
}
CLEAN_AS(func_02075cc4, SystemPacket_SendModeRequest)

/* func_02075d40: the share block as it is, with the length written to it so far
 * (Session_GetShareLength). */
int SystemPacket_SendShareData(int to)
{
    if (!system_packet_can_send((u32) to)) {
        return 0;
    }
    NetSession *session = data_020ccf94;
    u8 *block = Session_GetSendBlock(session, SHARE_BLOCK);
    u32 length = Session_GetShareLength(session);
    return Session_SendBlocks(session, block, (int) length, to, NULL, 0, 0, NULL, 0, 0);
}
CLEAN_AS(func_02075d40, SystemPacket_SendShareData)

/* func_02075d9c: the next chunk of the session's shared records. */
int SystemPacket_SendSharedRecords(u8 *chunks_sent, int to)
{
    u8 *records = Session_GetRecordTable(data_020ccf94);
    return SystemPacket_SendInChunks(chunks_sent, records, SHARED_RECORDS_SIZE, SYSTEM_WRITE_SHARED_RECORDS, (u16) to);
}
CLEAN_AS(func_02075d9c, SystemPacket_SendSharedRecords)

/* func_02075dcc: the next chunk of this system's player record (SystemPacket_WriteSenderBlock). */
int SystemPacket_SendSenderBlock(u8 *chunks_sent, u32 to)
{
    u8 *record = PlayerRecords_Get(SessionPlayers_RecordNumber(data_020ccf94->local_player));
    return SystemPacket_SendInChunks(chunks_sent, record, PLAYER_RECORD_SIZE, SYSTEM_WRITE_SENDER_BLOCK, (u16) to);
}
CLEAN_AS(func_02075dcc, SystemPacket_SendSenderBlock)

/* func_02075e00: from the host, one packet to each of the systems in slots 1-3 (AIDs 1-3),
 * whose content (SLOT_BLOCK_*) and 0x950-byte block (func_02090040) the arguments give in
 * order, all in one send; 1 when no slot gets a packet. */
int SystemPacket_SendSlotBlocks(int content1, int block1, int content2, int block2, int content3, int block3)
{
    if (!system_packet_network_ready()) {
        return 0;
    }
    int contents[3] = {content1, content2, content3};
    int blocks[3] = {block1, block2, block3};
    u8 *packets[3];
    int lengths[3];
    u16 to[3];
    func_02137550(packets, sizeof(packets));
    func_02137550(lengths, sizeof(lengths));
    func_02137550(to, sizeof(to));
    NetSession *session = data_020ccf94;
    for (u32 i = 0; i < 3; i++) {
        int content = contents[i];
        if (content == SLOT_BLOCK_NONE) {
            continue;
        }
        u8 *packet = Session_GetSendBlock(session, (int) i + 1);
        packets[i] = packet;
        SessionNet_WriteSystemHeader(packet, 0, SYSTEM_SET_OWN_BLOCK);
        lengths[i] += 1;
        if (content == SLOT_BLOCK_KEEP) {
            packet[1] = SLOT_BLOCK_KEEP;
            lengths[i] += 1;
        } else if (content == SLOT_BLOCK_CLEAR) {
            packet[1] = SLOT_BLOCK_CLEAR;
            lengths[i] += 1;
        } else {
            MI_CpuCopy8((const void *) (uintptr_t) ExchangeBlock_OfSlot(blocks[i]), packet + 1, SLOT_BLOCK_SIZE);
            lengths[i] += SLOT_BLOCK_SIZE;
        }
        to[i] = (u16) (1u << (i + 1));
    }
    if (content1 == SLOT_BLOCK_NONE && content2 == SLOT_BLOCK_NONE && content3 == SLOT_BLOCK_NONE) {
        return 1;
    }
    if (SessionNet_PeersHaveCredit((u16) (to[0] | to[1] | to[2])) == 0) {
        return 0;
    }
    return Session_SendBlocks(session, packets[0], lengths[0], to[0], packets[1], lengths[1], to[1], packets[2], lengths[2],
                              to[2]);
}
CLEAN_AS(func_02075e00, SystemPacket_SendSlotBlocks)

/* func_02075f3c: the next chunk of this system's 0x950-byte block, to the host; were the block
 * not to be sent (func_02090158 always lets it), a packet without payload, which clears the
 * host's copy. */
int SystemPacket_SendOwnBlock(u8 *chunks_sent)
{
    u8 *block = (u8 *) (uintptr_t) ExchangeBlock_OfSlot(OWN_BLOCK);
    if (ExchangeBlock_IsSendable((ExchangeBlock *) (void *) block) != 0) {
        return SystemPacket_SendInChunks(chunks_sent, block, SLOT_BLOCK_SIZE, SYSTEM_WRITE_SLOT_BLOCK, TO_HOST);
    }
    return system_packet_send_kind(SYSTEM_WRITE_SLOT_BLOCK, TO_HOST, 0);
}
CLEAN_AS(func_02075f3c, SystemPacket_SendOwnBlock)

/* func_02075fc4: the next chunk of the activity's buffer: its first word + 4 bytes, or
 * 0x17400 while that word is 0. */
int SystemPacket_SendActivityBuffer(u8 *chunks_sent, int to)
{
    u8 *buffer = (u8 *) Activity_CurrentPackBuffer();
    u32 expected = TownPack_PackedSize((TownPackBuffer *) (void *) buffer);
    u32 size = expected == 0 ? ACTIVITY_BUFFER_MAX : expected + 4;
    return SystemPacket_SendInChunks(chunks_sent, buffer, size, SYSTEM_WRITE_ACTIVITY_BUFFER, (u16) to);
}
CLEAN_AS(func_02075fc4, SystemPacket_SendActivityBuffer)

/* func_02075ff8: sends chunk number *chunks_sent of the `size` bytes of `data` (its offset and
 * up to SYSTEM_PACKET_CHUNK bytes) as a packet of `kind`, counting it once it goes; whether
 * every chunk has gone. */
int SystemPacket_SendInChunks(u8 *chunks_sent, const u8 *data, u32 size, int kind, u16 to)
{
    u32 chunks = size / SYSTEM_PACKET_CHUNK;
    if (size % SYSTEM_PACKET_CHUNK != 0) {
        chunks++;
    }
    if (system_packet_can_send(to)) {
        int offset = *chunks_sent * SYSTEM_PACKET_CHUNK;
        u32 length = size - (u32) offset;
        if (length > SYSTEM_PACKET_CHUNK) {
            length = SYSTEM_PACKET_CHUNK;
        }
        NetSession *session = data_020ccf94;
        u8 *packet = Session_GetSendBlock(session, SHARE_BLOCK);
        SessionNet_WriteSystemHeader(packet, 0, kind);
        MI_CpuCopy8(&offset, packet + 1, 4);
        MI_CpuCopy8(data + offset, packet + 5, length);
        if (system_packet_send(session, (int) length + 5, to) != 0) {
            (*chunks_sent)++;
        }
    }
    return *chunks_sent >= chunks;
}
CLEAN_AS(func_02075ff8, SystemPacket_SendInChunks)

/* func_020760bc: which slots are taken (bits 0-3) and the record number of player 0 (bits
 * 6-7), in one byte (SystemPacket_SetActivityMembers). */
int SystemPacket_SendActivityMembers(int to)
{
    if (!system_packet_can_send((u32) to)) {
        return 0;
    }
    NetSession *session = data_020ccf94;
    Session_IsLocalSlot(session, 0); /* QUIRK: the answer is not used */
    u8 *packet = Session_GetSendBlock(session, SHARE_BLOCK);
    SessionNet_WriteSystemHeader(packet, 0, SYSTEM_SET_ACTIVITY_MEMBERS);
    u32 taken = 0;
    for (int slot = 0; slot < SESSION_SLOTS; slot++) {
        if (Session_IsSlotTaken(session, slot) != 0) {
            taken |= 1u << slot;
        }
    }
    u8 byte = (u8) (taken & 0xf);
    byte |= (u8) ((SessionPlayers_RecordNumber(0) << 6) & 0xc0);
    packet[1] = byte;
    return system_packet_send(data_020ccf94, 2, to);
}
CLEAN_AS(func_020760bc, SystemPacket_SendActivityMembers)
