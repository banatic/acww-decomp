/* The channel measurement of the local wireless library of overlay 66 (local_wireless.h):
 * before a parent starts with LOCAL_CHANNEL_MEASURE_ONCE or _ALWAYS, each channel WM allows is
 * measured in turn (WM_MeasureChannel) and the parent's channel is drawn at random among the
 * least busy ones. */
#ifndef CLEAN_OV066_LOCAL_CHANNEL_H
#define CLEAN_OV066_LOCAL_CHANNEL_H

#include "types.h"

#include "local_wireless.h"

/* What WM_MeasureChannel's callback is handed (WMMeasureChannelCallback). */
typedef struct LocalMeasureResult {
    LocalWmResult base;
    u16 command;   /* wlCmdID */
    u16 wl_result; /* wlResult */
    u16 channel;
    u16 busy_ratio; /* ccaBusyRatio: the percentage of the time the channel was busy */
} LocalMeasureResult;

/* WM_MeasureChannel's parameters: the CCA mode, the energy detection threshold and the
 * milliseconds each channel is measured. */
#define LOCAL_MEASURE_CCA_MODE 3
#define LOCAL_MEASURE_ED_THRESHOLD 17
#define LOCAL_MEASURE_MS 30

/* The least busy ratio so far starts above any percentage. */
#define LOCAL_MEASURE_NONE 101

int LocalChannel_Choose(u32 measured);
void LocalChannel_Measure(void);
void LocalChannel_OnMeasure(LocalMeasureResult *result);
int LocalChannel_MeasureOne(int channel);
int LocalChannel_MeasureFrom(u32 index);

#endif
