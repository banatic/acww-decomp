/* The channel measurement (local_channel.h). */
#include "local_channel.h"

#include <assert.h>
#include <stddef.h>
#include <stdint.h>

#include "clean.h"
#include "local_mp.h"
#include "local_session.h"
#include "local_wireless.h"

static_assert(offsetof(LocalMeasureResult, channel) == 0x08, "WMMeasureChannelCallback.channel");
static_assert(offsetof(LocalMeasureResult, busy_ratio) == 0x0a, "WMMeasureChannelCallback.ccaBusyRatio");

extern LocalControl *data_ov066_0226bdec;
extern LocalSession *data_ov066_0226bdf4;
/* The measurement so far: how many channels share the least busy ratio, their bits
 * (bit channel - 1) and that ratio. */
extern u8 data_ov066_0226bdfc;
extern u16 data_ov066_0226be00;
extern u16 data_ov066_0226be04;

/* The game's symbol of the callback below, handed to WM. */
extern void func_ov066_0226a074(void *result);

extern int WM_MeasureChannel(void (*callback)(void *), u16 cca_mode, u16 ed_threshold, u16 channel, u16 milliseconds);

/* 1 << n as ARM shifts: by the low byte of the count, 0 from 32 on. */
static u32 arm_bit(u32 n)
{
    n &= 0xff;
    return n < 32 ? 1u << n : 0;
}

/* func_ov066_02269f6c: after the channel `measured` (1 to 14; 0 before any), the next channel
 * WM allows is measured; when there is none left, the parent's channel is drawn at random
 * among the least busy ones and TRUE returned. FALSE while a measurement goes on, or when no
 * channel was measured. */
int LocalChannel_Choose(u32 measured)
{
    if (LocalChannel_MeasureFrom(measured)) {
        return FALSE;
    }
    if (data_ov066_0226bdfc == 0) {
        return FALSE;
    }
    u8 skip = (u8) (LocalMp_NextRandom() % data_ov066_0226bdfc);
    u16 least_busy = data_ov066_0226be00;
    for (u8 i = 0; i < LOCAL_CHANNEL_COUNT; i++) {
        if (least_busy & (1u << i)) {
            if (skip == 0) {
                data_ov066_0226bdf4->parent_channel = (u8) (i + 1);
                return TRUE;
            }
            skip--;
        }
    }
    return FALSE;
}
CLEAN_AS(func_ov066_02269f6c, LocalChannel_Choose)

/* func_ov066_0226a00c: the measurement started (LOCAL_STATE_MEASURING) from the first channel,
 * with nothing measured yet. */
void LocalChannel_Measure(void)
{
    data_ov066_0226bdec->state = LOCAL_STATE_MEASURING;
    data_ov066_0226bdfc = 0;
    data_ov066_0226be00 = 0;
    data_ov066_0226be04 = LOCAL_MEASURE_NONE;
    data_ov066_0226bdf4->parent_channel = 0;
    LocalChannel_Choose(0);
}
CLEAN_AS(func_ov066_0226a00c, LocalChannel_Measure)

/* func_ov066_0226a074: WM_MeasureChannel's callback. The channel joins the least busy ones, or
 * replaces them when it is less busy; once a channel is chosen the radio is idle again, with
 * LOCAL_CHANNEL_MEASURE_ONCE no later parent measures first, and the request goes on. WM's
 * error stops the library. */
void LocalChannel_OnMeasure(LocalMeasureResult *result)
{
    if (result->base.result != LOCAL_WM_RESULT_SUCCESS) {
        LocalWireless_Fail(result->base.result);
        return;
    }
    u16 busy = result->busy_ratio;
    u16 channel = result->channel;
    /* QUIRK: the bit of channel 0 would be a shift by -1, none. */
    if (data_ov066_0226be04 > busy) {
        data_ov066_0226be04 = busy;
        data_ov066_0226be00 = (u16) arm_bit((u32) channel - 1);
        data_ov066_0226bdfc = 1;
    } else if (data_ov066_0226be04 == busy) {
        data_ov066_0226be00 = (u16) (data_ov066_0226be00 | arm_bit((u32) channel - 1));
        data_ov066_0226bdfc = (u8) (data_ov066_0226bdfc + 1);
    }
    if (!LocalChannel_Choose(channel)) {
        return;
    }
    data_ov066_0226bdec->state = LOCAL_STATE_WM_IDLE;
    if (data_ov066_0226bdec->parent_channel == LOCAL_CHANNEL_MEASURE_ONCE) {
        data_ov066_0226bdf4->flags &= ~LOCAL_SESSION_MEASURE_FIRST;
    }
    LocalWireless_Continue();
}
CLEAN_AS(func_ov066_0226a074, LocalChannel_OnMeasure)

/* func_ov066_0226a160: `channel` measured (WM_MeasureChannel), LocalChannel_OnMeasure
 * following; TRUE when WM took the call, otherwise the library stops on WM's error. */
int LocalChannel_MeasureOne(int channel)
{
    int status = WM_MeasureChannel(func_ov066_0226a074, LOCAL_MEASURE_CCA_MODE, LOCAL_MEASURE_ED_THRESHOLD, (u16) channel,
                                   LOCAL_MEASURE_MS);
    if (status == LOCAL_WM_RESULT_OPERATING) {
        return TRUE;
    }
    LocalWireless_Fail(status);
    return FALSE;
}
CLEAN_AS(func_ov066_0226a160, LocalChannel_MeasureOne)

/* func_ov066_0226a278: the first channel WM allows from bit `index` on (channel index + 1)
 * measured; TRUE when one is, FALSE when none is left or WM refused. */
int LocalChannel_MeasureFrom(u32 index)
{
    while (index < LOCAL_CHANNEL_COUNT) {
        if (data_ov066_0226bdf4->allowed_channels & (1u << index)) {
            if (LocalChannel_MeasureOne((u16) (index + 1))) {
                return TRUE;
            }
        }
        index = (u16) (index + 1);
    }
    return FALSE;
}
CLEAN_AS(func_ov066_0226a278, LocalChannel_MeasureFrom)
