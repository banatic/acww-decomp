/* The session's life and the channels WM allows (local_session.h). */
#include "local_session.h"

#include <assert.h>
#include <stddef.h>
#include <stdint.h>

#include "clean.h"
#include "local_host.h"
#include "local_mp.h"
#include "local_search.h"
#include "local_wireless.h"

static_assert(offsetof(LocalSession, mp_receive_size) == 0x1a, "MP receive size");
static_assert(offsetof(LocalSession, mp_send_size) == 0x1c, "MP send size");
static_assert(offsetof(LocalSession, parent_channel) == 0x8d, "parent channel");
static_assert(offsetof(LocalSession, unk_8f) == 0x8f, "unk_8f");
static_assert(offsetof(LocalSession, allowed_channel_count) == 0x92, "allowed channel count");
static_assert(offsetof(LocalSession, turn) == 0x94, "turn");
static_assert(offsetof(LocalControl, parent_channel) == 0x08, "parent channel");
static_assert(offsetof(LocalControl, max_children) == 0x0a, "children");
static_assert(offsetof(LocalControl, unk_18) == 0x18, "unk_18");
static_assert(offsetof(LocalControl, parent_max_size) == 0x1a, "parent max size");
static_assert(offsetof(LocalControl, unk_1c) == 0x1c, "unk_1c");
static_assert(offsetof(LocalControl, child_max_size) == 0x1e, "child max size");

extern LocalControl *data_ov066_0226bdec;
/* The session, NULL outside LocalSession_Create and LocalSession_Destroy. */
extern LocalSession *data_ov066_0226bdf4;

extern int WM_Init(void *work, u16 dma);
extern int WM_Finish(void);
extern u16 WM_GetAllowedChannel(void);
extern u8 MATH_CountPopulation(u32 bits);
extern void OS_GetMacAddress(u8 *mac);
extern void MI_CpuFill8(void *dst, u8 value, u32 size);

/* 1 << n as ARM shifts: by the low byte of the count, 0 from 32 on. */
static u32 arm_bit(u32 n)
{
    n &= 0xff;
    return n < 32 ? 1u << n : 0;
}

/* func_ov066_02269a14: with the radio on (WM_PowerOn's callback), the session set up for a new
 * connection: no search filter, no MP end asked for, the session's MP start handler called
 * (it resets the data layer above, LocalRelay_Reset), the member table sending free, the turns
 * of the automatic pairing and the greetings cleared, the member table emptied and the channels
 * WM allows read. */
void LocalSession_OnRadioOn(void)
{
    LocalSearch_SetFilter(0);
    data_ov066_0226bdf4->flags &= ~LOCAL_SESSION_END_MP;
    data_ov066_0226bdf4->on_mp_start();
    data_ov066_0226bdf4->flags &= ~LOCAL_SESSION_SEND_BUSY;
    data_ov066_0226bdf4->flags &= ~LOCAL_SESSION_SEND_AGAIN;
    data_ov066_0226bdf4->search_turn = 0;
    data_ov066_0226bdf4->turn = 0;
    data_ov066_0226bdf4->channel_index = 0;
    data_ov066_0226bdf4->greeted = 0;
    LocalMp_ClearMembers();
    LocalSession_ReadAllowedChannels();
}
CLEAN_AS(func_ov066_02269a14, LocalSession_OnRadioOn)

/* func_ov066_02269aa4: with WM initialised and disabled (LOCAL_STATE_WM_READY), WM finished
 * (WM_Finish) and, if it agreed, the search and the session freed with its buffers; the state
 * goes back to LOCAL_STATE_SET_UP. In any other state the library stops on
 * LOCAL_ERROR_WRONG_STATE. */
void LocalSession_Destroy(void)
{
    if (data_ov066_0226bdec->state != LOCAL_STATE_WM_READY) {
        LocalWireless_Fail(LOCAL_ERROR_WRONG_STATE);
        return;
    }
    if (WM_Finish() != LOCAL_WM_RESULT_SUCCESS) {
        return;
    }
    LocalSearch_Destroy();
    LocalWireless_Free(data_ov066_0226bdf4->message_buffer);
    LocalWireless_Free(data_ov066_0226bdf4->mp_send_buffer);
    LocalWireless_Free(data_ov066_0226bdf4->mp_receive_buffer);
    LocalWireless_Free(data_ov066_0226bdf4->game_info);
    LocalWireless_Free(data_ov066_0226bdf4->parent_param);
    LocalWireless_Free(data_ov066_0226bdf4->wm_work);
    LocalWireless_Free(data_ov066_0226bdf4);
    data_ov066_0226bdf4 = NULL;
    data_ov066_0226bdec->state = LOCAL_STATE_SET_UP;
}
CLEAN_AS(func_ov066_02269aa4, LocalSession_Destroy)

/* func_ov066_02269b88: the session allocated, unless there is one, with WM's work buffer (aligned
 * to the cache's 32 bytes), and WM initialised on the control block's DMA channel; when it is,
 * the session's buffers follow (LocalSession_AllocBuffers).
 * BUG: when WM_Init fails, the work buffer is freed but the session keeps it and stays
 * allocated, its other fields unset.
 * REQUIRES: the allocations succeed (the ROM writes through the NULL it is given). */
void LocalSession_Create(void)
{
    if (data_ov066_0226bdf4 != NULL) {
        return;
    }
    data_ov066_0226bdf4 = LocalWireless_Alloc(sizeof(LocalSession), 4);
    data_ov066_0226bdf4->wm_work = LocalWireless_Alloc(LOCAL_WM_WORK_SIZE, 0x20);
    if (WM_Init(data_ov066_0226bdf4->wm_work, data_ov066_0226bdec->wm_dma) == LOCAL_WM_RESULT_SUCCESS) {
        LocalSession_AllocBuffers();
        return;
    }
    LocalWireless_Free(data_ov066_0226bdf4->wm_work);
}
CLEAN_AS(func_ov066_02269b88, LocalSession_Create)

/* func_ov066_02269c28: with WM initialised, the session's buffers allocated (all aligned to the
 * cache's 32 bytes): the parent parameters, the beacon's game info (its header alone at first),
 * the MP receive and send buffers, each large enough for a parent and for a child, and the
 * library's message buffer. Then the search is created, the MAC address read and the random
 * numbers seeded from its last four bytes, the state is LOCAL_STATE_WM_READY (and so is the
 * request), and the session starts without a connection.
 * The MP buffer sizes follow the control block: the parent's receive buffer from unk_18 and the
 * children, the child's from unk_1c, rounded to 32 bytes and doubled; the send buffers from
 * the parent's and the child's maximum sizes, rounded to 32 bytes.
 * QUIRK: each size is cut to 16 bits before the larger is taken.
 * REQUIRES: the allocations succeed. */
void LocalSession_AllocBuffers(void)
{
    LocalControl *control;

    data_ov066_0226bdf4->parent_param = LocalWireless_Alloc(sizeof(LocalParentParam), 0x20);
    data_ov066_0226bdf4->game_info = LocalWireless_Alloc(0x70, 0x20);
    data_ov066_0226bdf4->game_info_length = 8;

    control = data_ov066_0226bdec;
    u16 parent_receive = (u16) ((((control->unk_18 + 0xe) * control->max_children + 0x29) & ~0x1f) * 2);
    u16 child_receive = (u16) (((control->unk_1c + 0x55) & ~0x1f) * 2);
    data_ov066_0226bdf4->mp_receive_size = parent_receive > child_receive ? parent_receive : child_receive;
    data_ov066_0226bdf4->mp_receive_buffer = LocalWireless_Alloc(data_ov066_0226bdf4->mp_receive_size, 0x20);

    control = data_ov066_0226bdec;
    u16 parent_send = (u16) ((control->parent_max_size + 0x23) & ~0x1f);
    u16 child_send = (u16) ((control->child_max_size + 0x21) & ~0x1f);
    data_ov066_0226bdf4->mp_send_size = parent_send > child_send ? parent_send : child_send;
    data_ov066_0226bdf4->mp_send_buffer = LocalWireless_Alloc(data_ov066_0226bdf4->mp_send_size, 0x20);

    data_ov066_0226bdf4->message_buffer = LocalWireless_Alloc(data_ov066_0226bdec->child_max_size * 2, 0x20);
    data_ov066_0226bdf4->on_received = NULL;

    LocalSearch_Create();
    OS_GetMacAddress(data_ov066_0226bdf4->mac);
    data_ov066_0226bdf8 = LocalMp_ReadBigEndian32(&data_ov066_0226bdf4->mac[2]);
    data_ov066_0226bdec->state = LOCAL_STATE_WM_READY;
    data_ov066_0226bdec->request = LOCAL_REQUEST_WM_READY;
    LocalSession_Disconnected();
}
CLEAN_AS(func_ov066_02269c28, LocalSession_AllocBuffers)

/* func_ov066_02269dcc: the session back to no connection: no AID, one player (this DS), the
 * flags of the member table, the MP communication, the beacon and the connection cleared, and
 * the member table emptied (from a zeroed address, two bytes at a time). With
 * LOCAL_CHANNEL_MEASURE_ONCE or _ALWAYS the channels are to be measured before a parent starts;
 * otherwise the parent uses the control block's channel. */
void LocalSession_Disconnected(void)
{
    u8 none[6];

    data_ov066_0226bdf4->aid = 0xffff;
    data_ov066_0226bdf4->player_count = 1;
    data_ov066_0226bdf4->flags &= ~LOCAL_SESSION_SEND_BUSY;
    data_ov066_0226bdf4->flags &= ~LOCAL_SESSION_SEND_AGAIN;
    data_ov066_0226bdf4->flags &= ~LOCAL_SESSION_END_MP;
    data_ov066_0226bdf4->flags &= ~LOCAL_SESSION_ENDING_MP;
    data_ov066_0226bdf4->flags &= ~LOCAL_SESSION_GAME_INFO_DUE;
    data_ov066_0226bdf4->flags &= ~LOCAL_SESSION_START_MP;
    data_ov066_0226bdf4->flags &= ~LOCAL_SESSION_RETRY_CONNECT;
    data_ov066_0226bdf4->flags &= ~LOCAL_SESSION_400;
    u8 channel = data_ov066_0226bdec->parent_channel;
    if (channel == LOCAL_CHANNEL_MEASURE_ONCE || channel == LOCAL_CHANNEL_MEASURE_ALWAYS) {
        data_ov066_0226bdf4->flags |= LOCAL_SESSION_MEASURE_FIRST;
        data_ov066_0226bdf4->parent_channel = 0;
        data_ov066_0226bdf4->channel = 0;
        data_ov066_0226bdf4->unk_8f = 0;
    } else {
        data_ov066_0226bdf4->flags &= ~LOCAL_SESSION_MEASURE_FIRST;
        data_ov066_0226bdf4->parent_channel = data_ov066_0226bdec->parent_channel;
        data_ov066_0226bdf4->channel = 0;
        data_ov066_0226bdf4->unk_8f = data_ov066_0226bdec->parent_channel;
    }
    MI_CpuFill8(none, 0, sizeof(none));
    for (int i = 0; i < LOCAL_MEMBER_COUNT; i++) {
        for (int j = 0; j < 6; j += 2) {
            u8 first = none[j];
            u8 second = none[j + 1];
            data_ov066_0226bdf4->members[i][j] = first;
            data_ov066_0226bdf4->members[i][j + 1] = second;
        }
    }
}
CLEAN_AS(func_ov066_02269dcc, LocalSession_Disconnected)

/* func_ov066_0226a1b0: the next channel after `channel` that WM allows, 1 to 14 round; `channel`
 * itself when none is. */
u16 LocalSession_NextAllowedChannel(u16 channel)
{
    u16 allowed = data_ov066_0226bdf4->allowed_channels;
    u16 next = channel;
    for (u16 i = 0; i < LOCAL_CHANNEL_COUNT; i++) {
        next = (u16) (next + 1);
        if (next > LOCAL_CHANNEL_COUNT) {
            next = 1;
        }
        /* QUIRK: from 0xffff the channel wraps to 0, whose bit (a shift by -1) is none. */
        if (allowed & arm_bit((u32) next - 1)) {
            return next;
        }
    }
    return channel;
}
CLEAN_AS(func_ov066_0226a1b0, LocalSession_NextAllowedChannel)

/* func_ov066_0226a224: the channels WM allows read, with their count; the library stops on
 * LOCAL_ERROR_NO_CHANNEL when there are none. */
void LocalSession_ReadAllowedChannels(void)
{
    u16 allowed = WM_GetAllowedChannel();
    if (allowed == 0) {
        LocalWireless_Fail(LOCAL_ERROR_NO_CHANNEL);
        return;
    }
    data_ov066_0226bdf4->allowed_channels = allowed;
    data_ov066_0226bdf4->allowed_channel_count = MATH_CountPopulation(allowed);
}
CLEAN_AS(func_ov066_0226a224, LocalSession_ReadAllowedChannels)
