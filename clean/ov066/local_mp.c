/* The MP communication and the member table (local_mp.h). */
#include "local_mp.h"

#include <assert.h>
#include <stddef.h>
#include <stdint.h>

#include "clean.h"
#include "local_host.h"
#include "local_join.h"
#include "local_wireless.h"

static_assert(sizeof(LocalMessage) == 8, "the message header");
static_assert(offsetof(LocalMpResult, state) == 0x04, "WMStartMPCallback.state");
static_assert(offsetof(LocalPortReceive, data) == 0x0c, "WMPortRecvCallback.data");
static_assert(offsetof(LocalPortReceive, length) == 0x10, "WMPortRecvCallback.length");
static_assert(offsetof(LocalPortReceive, aid) == 0x12, "WMPortRecvCallback.aid");
static_assert(offsetof(LocalSession, game_info) == 0x08, "game info");
static_assert(offsetof(LocalSession, message_buffer) == 0x14, "message buffer");
static_assert(offsetof(LocalSession, game_info_length) == 0x18, "game info length");
static_assert(offsetof(LocalSession, aid) == 0x1e, "AID");
static_assert(offsetof(LocalSession, mac) == 0x22, "MAC address");
static_assert(offsetof(LocalSession, members) == 0x28, "member table");
static_assert(offsetof(LocalSession, chosen_parent) == 0x88, "chosen parent");
static_assert(offsetof(LocalSession, player_count) == 0x8c, "player count");
static_assert(offsetof(LocalSession, allowed_channels) == 0x90, "allowed channels");
static_assert(offsetof(LocalSession, search_turn) == 0x93, "search turn");
static_assert(offsetof(LocalSession, greeted) == 0x98, "greeted");
static_assert(offsetof(LocalSession, on_mp_start) == 0x9c, "MP start handler");
static_assert(offsetof(LocalSession, send_message) == 0xac, "message sender");
static_assert(offsetof(LocalSession, send) == 0xb0, "data sender");
static_assert(offsetof(LocalSession, can_send) == 0xb4, "can send");
static_assert(offsetof(LocalSession, on_peer_left) == 0xbc, "peer left handler");
static_assert(sizeof(LocalSession) == 0xc4, "the size the session is allocated with");
static_assert(offsetof(LocalControl, mp_frequency) == 0x17, "MP frequency");
static_assert(offsetof(LocalControl, search_time) == 0x20, "search time");

extern LocalControl *data_ov066_0226bdec;
extern LocalSession *data_ov066_0226bdf4;

/* The game's symbols of the callbacks below, handed to WM and to the message sender. */
extern void func_ov066_022684c4(void *result);
extern void func_ov066_02268570(void *result);
extern void func_ov066_022693f0(void);

extern int WM_EndMP(void (*callback)(void *));
extern int WM_StartMPEx(void (*callback)(void *), void *receive_buffer, u32 receive_size, void *send_buffer, u32 send_size,
                        u32 frequency, u32 retries, int min_poll_bmp, int single_packet, int fixed_frequency,
                        int ignore_fatal);
extern u32 OS_DisableInterrupts(void);
extern u32 OS_RestoreInterrupts(u32 state);
extern void DC_InvalidateRange(void *start, u32 size);
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
extern void MI_CpuFill8(void *dst, u8 value, u32 size);

/* WM's status, reached through the second word of its work buffer: the word the game's network
 * layer reads as the AIDs connected. */
typedef struct LocalWmStatus {
    u8 unk_000[0x17e];
    u16 connected_aids;
} LocalWmStatus;

typedef struct LocalWmWork {
    void *unk_00;
    LocalWmStatus *status;
} LocalWmWork;

/* WM_StartMPEx's flags are BOOLs taken from one-bit signed fields of the control block.
 * QUIRK: a flag set is passed as -1, not 1. */
static int control_flag(u32 flag)
{
    return (data_ov066_0226bdec->flags & flag) ? -1 : 0;
}

/* 1 << aid as ARM shifts: by the low byte of the count, 0 from 32 on. */
static u32 aid_bit(int aid)
{
    u32 shift = (u32) aid & 0xff;
    return shift < 32 ? 1u << shift : 0;
}

/* func_ov066_0226807c: the players connected, the parent included; 0 without a session. */
u32 LocalMp_PlayerCount(void)
{
    if (data_ov066_0226bdf4 == NULL) {
        return 0;
    }
    return data_ov066_0226bdf4->player_count;
}
CLEAN_AS(func_ov066_0226807c, LocalMp_PlayerCount)

/* func_ov066_022683ec: the 32-bit big-endian number at `bytes` (the random seed from the last
 * four bytes of the MAC address). */
u32 LocalMp_ReadBigEndian32(const u8 *bytes)
{
    return ((u32) bytes[0] << 24) | ((u32) bytes[1] << 16) | ((u32) bytes[2] << 8) | bytes[3];
}
CLEAN_AS(func_ov066_022683ec, LocalMp_ReadBigEndian32)

/* func_ov066_022684c4: WM_EndMP's callback: unless a reset takes over, once the end was asked
 * for (LocalMp_EndIfAsked) the parent ends and a child disconnects. */
void LocalMp_OnEnd(LocalWmResult *result)
{
    if (LocalWireless_CheckReset()) {
        return;
    }
    if (result->result != LOCAL_WM_RESULT_SUCCESS) {
        LocalWireless_Fail(result->result);
        return;
    }
    if ((data_ov066_0226bdf4->flags & LOCAL_SESSION_ENDING_MP) == 0) {
        return;
    }
    if (data_ov066_0226bdf4->aid == 0) {
        LocalHost_End();
    } else {
        LocalJoin_Disconnect(0);
    }
}
CLEAN_AS(func_ov066_022684c4, LocalMp_OnEnd)

/* func_ov066_0226853c: WM_EndMP, LocalMp_OnEnd following; the library stops on WM's error
 * unless it is OPERATING. */
void LocalMp_End(void)
{
    int status = WM_EndMP(func_ov066_022684c4);
    if (status == LOCAL_WM_RESULT_OPERATING) {
        return;
    }
    LocalWireless_Fail(status);
}
CLEAN_AS(func_ov066_0226853c, LocalMp_End)

/* func_ov066_02268570: WM_StartMPEx's callback. When the MP communication starts the session's
 * handler is called and the sending is free; the parent then takes its own member slot (AID 0),
 * becomes LOCAL_STATE_PARENT, sends the member table and the request goes on, while a child
 * greets its parent. The MP indications end the communication if that was asked for and call
 * the session's handlers. WM's TIMEOUT, INVALID_POLLBITMAP and SEND_FAILED are ignored; another
 * error stops the library. */
void LocalMp_OnMp(LocalMpResult *result)
{
    if (LocalWireless_CheckReset()) {
        return;
    }
    u16 code = result->base.result;
    if (code != LOCAL_WM_RESULT_SUCCESS) {
        if (code == LOCAL_WM_RESULT_TIMEOUT || code == LOCAL_WM_RESULT_INVALID_POLLBITMAP ||
            code == LOCAL_WM_RESULT_SEND_FAILED) {
            return;
        }
        LocalWireless_Fail(code);
        return;
    }
    switch (result->state) {
        case LOCAL_WM_STATE_MP_START:
            data_ov066_0226bdf4->flags &= ~LOCAL_SESSION_START_MP;
            data_ov066_0226bdec->flags |= LOCAL_FLAG_MP_STARTED;
            data_ov066_0226bdf4->on_mp_start();
            data_ov066_0226bdf4->flags &= ~LOCAL_SESSION_SEND_BUSY;
            data_ov066_0226bdf4->flags &= ~LOCAL_SESSION_SEND_AGAIN;
            if (data_ov066_0226bdf4->aid != 0) {
                LocalMp_SendHello();
                return;
            }
            LocalMp_SetMember(0, data_ov066_0226bdf4->mac);
            if (data_ov066_0226bdec->state != LOCAL_STATE_PARENT) {
                data_ov066_0226bdec->state = LOCAL_STATE_PARENT;
            }
            LocalMp_SendMembers();
            LocalWireless_Continue();
            return;
        case LOCAL_WM_STATE_MPEND_IND:
            LocalMp_EndIfAsked();
            if (data_ov066_0226bdf4->on_mp_end != NULL) {
                data_ov066_0226bdf4->on_mp_end();
            }
            return;
        case LOCAL_WM_STATE_MP_IND:
            LocalMp_EndIfAsked();
            return;
        case LOCAL_WM_STATE_MPACK_IND:
            if (data_ov066_0226bdf4->on_mp_ack != NULL) {
                data_ov066_0226bdf4->on_mp_ack();
            }
            return;
    }
}
CLEAN_AS(func_ov066_02268570, LocalMp_OnMp)

/* func_ov066_022686f0: WM_StartMPEx with the session's buffers and the control block's
 * frequency and flags, 4 retries and a fixed frequency, LocalMp_OnMp following; the library
 * stops on WM's error unless it is OPERATING. */
void LocalMp_Start(void)
{
    int status =
        WM_StartMPEx(func_ov066_02268570, data_ov066_0226bdf4->mp_receive_buffer, data_ov066_0226bdf4->mp_receive_size,
                     data_ov066_0226bdf4->mp_send_buffer, data_ov066_0226bdf4->mp_send_size, data_ov066_0226bdec->mp_frequency,
                     4, control_flag(LOCAL_FLAG_MIN_POLL_BMP), control_flag(LOCAL_FLAG_SINGLE_PACKET), TRUE,
                     control_flag(LOCAL_FLAG_IGNORE_FATAL));
    if (status == LOCAL_WM_RESULT_OPERATING) {
        return;
    }
    LocalWireless_Fail(status);
}
CLEAN_AS(func_ov066_022686f0, LocalMp_Start)

/* func_ov066_02268c90: when the end was asked for and is not under way, WM_EndMP is called and
 * TRUE returned (the caller then ignores what it was handed). */
int LocalMp_EndIfAsked(void)
{
    u32 flags = data_ov066_0226bdf4->flags;
    if ((flags & LOCAL_SESSION_END_MP) == 0 || (flags & LOCAL_SESSION_ENDING_MP) != 0) {
        return FALSE;
    }
    LocalMp_End();
    data_ov066_0226bdf4->flags |= LOCAL_SESSION_ENDING_MP;
    data_ov066_0226bdf4->flags &= ~LOCAL_SESSION_END_MP;
    return TRUE;
}
CLEAN_AS(func_ov066_02268c90, LocalMp_EndIfAsked)

/* func_ov066_02268d08: the MP communication asked to end (at its next indication or data
 * received), unless it is ending already; with the interrupts disabled. */
void LocalMp_AskEnd(void)
{
    u32 interrupts = OS_DisableInterrupts();
    if ((data_ov066_0226bdf4->flags & LOCAL_SESSION_ENDING_MP) == 0) {
        data_ov066_0226bdf4->flags |= LOCAL_SESSION_END_MP;
    }
    OS_RestoreInterrupts(interrupts);
}
CLEAN_AS(func_ov066_02268d08, LocalMp_AskEnd)

/* func_ov066_02268d44: a child received the member table `message`: its own table updated (the
 * events of the players who came and went posted) and counted; a child still starting the MP
 * communication becomes LOCAL_STATE_CHILD, and the request goes on.
 * QUIRK: the message's header is copied to the stack and not used. */
void LocalMp_OnMembers(const void *message)
{
    LocalMessage header;
    MI_CpuCopy8(message, &header, sizeof(header));
    LocalMp_UpdateMembers(data_ov066_0226bdf4->members, (const u8(*)[6])((const u8 *) message + sizeof(header)));
    LocalMp_CountMembers();
    if (data_ov066_0226bdec->state == LOCAL_STATE_MP_STARTING) {
        data_ov066_0226bdec->state = LOCAL_STATE_CHILD;
    }
    LocalWireless_Continue();
}
CLEAN_AS(func_ov066_02268d44, LocalMp_OnMembers)

/* func_ov066_02268da4: a message received by a child: the member table is taken; nothing for
 * an empty one or another kind. */
void LocalMp_ReceiveAsChild(LocalPortReceive *received)
{
    if (received->length == 0) {
        return;
    }
    LocalMessage header;
    MI_CpuCopy8(received->data, &header, 4);
    if (header.kind == LOCAL_MESSAGE_MEMBERS) {
        LocalMp_OnMembers(received->data);
    }
}
CLEAN_AS(func_ov066_02268da4, LocalMp_ReceiveAsChild)

/* func_ov066_02268ed4: the parent received the hello `message` of the child `aid`: the child is
 * marked greeted and the member table sent to all.
 * QUIRK: the message's header is copied to the stack and not used. */
void LocalMp_OnHello(int aid, const void *message)
{
    LocalMessage header;
    MI_CpuCopy8(message, &header, sizeof(header));
    data_ov066_0226bdf4->greeted = (u16) (data_ov066_0226bdf4->greeted | aid_bit(aid));
    LocalMp_SendMembers();
}
CLEAN_AS(func_ov066_02268ed4, LocalMp_OnHello)

/* func_ov066_02268f1c: a message received by the parent: a child's hello is taken; nothing for
 * an empty one or another kind. */
void LocalMp_ReceiveAsParent(LocalPortReceive *received)
{
    if (received->length == 0) {
        return;
    }
    LocalMessage header;
    MI_CpuCopy8(received->data, &header, 4);
    if (header.kind == LOCAL_MESSAGE_HELLO) {
        LocalMp_OnHello(received->aid, received->data);
    }
}
CLEAN_AS(func_ov066_02268f1c, LocalMp_ReceiveAsParent)

/* func_ov066_02269204: the session's handler told that the child `aid` left, if there is one. */
void LocalMp_TellPeerLeft(int aid)
{
    if (data_ov066_0226bdf4->on_peer_left == NULL) {
        return;
    }
    data_ov066_0226bdf4->on_peer_left(aid);
}
CLEAN_AS(func_ov066_02269204, LocalMp_TellPeerLeft)

/* func_ov066_0226923c: the receive callback of WM's port 12 (the library's messages): ignored
 * while a reset takes over or when the MP communication ends now; otherwise taken as the parent
 * or as a child. */
void LocalMp_OnReceive(LocalPortReceive *received)
{
    if (LocalWireless_CheckReset()) {
        return;
    }
    if (LocalMp_EndIfAsked()) {
        return;
    }
    if (data_ov066_0226bdf4->aid == 0) {
        LocalMp_ReceiveAsParent(received);
    } else {
        LocalMp_ReceiveAsChild(received);
    }
}
CLEAN_AS(func_ov066_0226923c, LocalMp_OnReceive)

/* func_ov066_0226929c: every member slot freed (the count is left as it is). */
void LocalMp_ClearMembers(void)
{
    MI_CpuFill8(data_ov066_0226bdf4->members, 0, sizeof(data_ov066_0226bdf4->members));
}
CLEAN_AS(func_ov066_0226929c, LocalMp_ClearMembers)

/* func_ov066_022692c0: the players counted: the member slots set. */
void LocalMp_CountMembers(void)
{
    u8 count = 0;
    for (int i = 0; i < LOCAL_MEMBER_COUNT; i++) {
        if (LocalWireless_IsMacSet(data_ov066_0226bdf4->members[i])) {
            count++;
        }
    }
    data_ov066_0226bdf4->player_count = count;
}
CLEAN_AS(func_ov066_022692c0, LocalMp_CountMembers)

/* func_ov066_02269320: the member table `members` replaced by the one `received`, slot by slot,
 * posting LOCAL_EVENT_CONNECTED for a slot that becomes set and LOCAL_EVENT_DISCONNECTED for
 * one that becomes free. Each slot is copied two bytes at a time, as the ROM does. */
void LocalMp_UpdateMembers(u8 (*members)[6], const u8 (*received)[6])
{
    for (u16 i = 0; i < LOCAL_MEMBER_COUNT; i++) {
        u8 *slot = members[i];
        const u8 *mac = received[i];
        int was_set = LocalWireless_IsMacSet(slot);
        int is_set = LocalWireless_IsMacSet(mac);
        for (int j = 0; j < 6; j += 2) {
            u8 first = mac[j];
            u8 second = mac[j + 1];
            slot[j] = first;
            slot[j + 1] = second;
        }
        if (!was_set && is_set) {
            LocalWireless_PostEvent(LOCAL_EVENT_CONNECTED, (u8) i);
        }
        if (was_set && !is_set) {
            LocalWireless_PostEvent(LOCAL_EVENT_DISCONNECTED, (u8) i);
        }
    }
}
CLEAN_AS(func_ov066_02269320, LocalMp_UpdateMembers)

/* func_ov066_022693f0: the member table sent (LocalSession.send_message's callback): the
 * sending is free, and the table is sent again if it changed meanwhile. */
void LocalMp_OnMembersSent(void)
{
    data_ov066_0226bdf4->flags &= ~LOCAL_SESSION_SEND_BUSY;
    if ((data_ov066_0226bdf4->flags & LOCAL_SESSION_SEND_AGAIN) == 0) {
        return;
    }
    LocalMp_SendMembers();
}
CLEAN_AS(func_ov066_022693f0, LocalMp_OnMembersSent)

/* func_ov066_0226943c: the member table sent to every AID (the parent's), after a header with
 * a new random number; while one is being sent it is sent again once that is done. */
void LocalMp_SendMembers(void)
{
    if (data_ov066_0226bdf4->flags & LOCAL_SESSION_SEND_BUSY) {
        data_ov066_0226bdf4->flags |= LOCAL_SESSION_SEND_AGAIN;
        return;
    }
    data_ov066_0226bdf4->flags |= LOCAL_SESSION_SEND_BUSY;
    data_ov066_0226bdf4->flags &= ~LOCAL_SESSION_SEND_AGAIN;
    LocalMessage header;
    header.kind = LOCAL_MESSAGE_MEMBERS;
    header.size = sizeof(header) + sizeof(data_ov066_0226bdf4->members);
    header.nonce = local_next_random();
    MI_CpuCopy8(&header, data_ov066_0226bdf4->message_buffer, sizeof(header));
    MI_CpuCopy8(data_ov066_0226bdf4->members, (u8 *) data_ov066_0226bdf4->message_buffer + sizeof(header),
                sizeof(data_ov066_0226bdf4->members));
    data_ov066_0226bdf4->send_message(data_ov066_0226bdf4->message_buffer, header.size, LOCAL_AIDS_ALL,
                                      (void (*)(void *)) func_ov066_022693f0);
}
CLEAN_AS(func_ov066_0226943c, LocalMp_SendMembers)

/* func_ov066_02269528: a child's hello sent to its parent: the header alone, with a new random
 * number. */
void LocalMp_SendHello(void)
{
    LocalMessage header;
    header.nonce = local_next_random();
    header.kind = LOCAL_MESSAGE_HELLO;
    header.size = sizeof(header);
    MI_CpuCopy8(&header, data_ov066_0226bdf4->message_buffer, sizeof(header));
    data_ov066_0226bdf4->send_message(data_ov066_0226bdf4->message_buffer, sizeof(header), LOCAL_AIDS_PARENT, NULL);
}
CLEAN_AS(func_ov066_02269528, LocalMp_SendHello)

/* func_ov066_022695ac: the member slot `aid` set to the MAC address `mac` (freed for NULL),
 * then the players counted. REQUIRES: aid is 0 to 15. */
void LocalMp_SetMember(int aid, const u8 *mac)
{
    u8 copy[6];
    if (mac != NULL) {
        MI_CpuCopy8(mac, copy, sizeof(copy));
    } else {
        MI_CpuFill8(copy, 0, sizeof(copy));
    }
    for (int i = 0; i < 6; i++) {
        data_ov066_0226bdf4->members[aid][i] = copy[i];
    }
    LocalMp_CountMembers();
}
CLEAN_AS(func_ov066_022695ac, LocalMp_SetMember)

/* func_ov066_022698ec: the game's data `buffer` sent to the AIDs `to` through the session's
 * sender, `on_sent` following; FALSE without a session or a sender. */
int LocalMp_Send(const void *buffer, u32 size, int to, void (*on_sent)(void *))
{
    LocalSession *session = data_ov066_0226bdf4;
    if (session == NULL || session->send == NULL) {
        return FALSE;
    }
    return session->send(buffer, size, to, on_sent);
}
CLEAN_AS(func_ov066_022698ec, LocalMp_Send)

/* func_ov066_02269934: the session's answer to whether data can be sent; FALSE without a
 * session or its function. */
int LocalMp_CanSend(void)
{
    LocalSession *session = data_ov066_0226bdf4;
    if (session == NULL || session->can_send == NULL) {
        return FALSE;
    }
    return session->can_send();
}
CLEAN_AS(func_ov066_02269934, LocalMp_CanSend)

/* func_ov066_0226997c: as a communicating parent, the AIDs connected, read from WM's status
 * after its cache line is invalidated; 0 in any other state. */
u16 LocalMp_ConnectedAids(void)
{
    if (LocalWireless_GetState() != LOCAL_STATE_PARENT) {
        return 0;
    }
    LocalWmStatus *status = ((LocalWmWork *) data_ov066_0226bdf4->wm_work)->status;
    DC_InvalidateRange(&status->connected_aids, sizeof(status->connected_aids));
    return status->connected_aids;
}
CLEAN_AS(func_ov066_0226997c, LocalMp_ConnectedAids)

/* func_ov066_022699cc: this DS's AID (0 for the parent); 0xffff without a session. */
int LocalMp_GetAid(void)
{
    if (data_ov066_0226bdf4 == NULL) {
        return 0xffff;
    }
    return data_ov066_0226bdf4->aid;
}
CLEAN_AS(func_ov066_022699cc, LocalMp_GetAid)

/* func_ov066_022699ec: the next of the library's random numbers. */
u32 LocalMp_NextRandom(void)
{
    return local_next_random();
}
CLEAN_AS(func_ov066_022699ec, LocalMp_NextRandom)
