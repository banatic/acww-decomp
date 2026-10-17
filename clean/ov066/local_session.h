/* The session of the local wireless library of overlay 66 (LocalSession, local_wireless.h): its
 * allocation with WM's work buffer and WM_Init, the buffers it sizes from the control block,
 * its set-up once the radio is on, its return to no connection, its end with WM_Finish, and
 * the channels WM allows. */
#ifndef CLEAN_OV066_LOCAL_SESSION_H
#define CLEAN_OV066_LOCAL_SESSION_H

#include "types.h"

#include "local_wireless.h"

/* The session's work buffer for WM_Init. */
#define LOCAL_WM_WORK_SIZE 0xf00

/* WM's channels are 1 to 14; LocalSession.allowed_channels has bit (channel - 1) for each. */
#define LOCAL_CHANNEL_COUNT 14

/* More LocalSession.flags: cleared by LocalSession_Disconnected; no other part of the library
 * reads or sets it. */
#define LOCAL_SESSION_400 0x400

void LocalSession_OnRadioOn(void);
void LocalSession_Destroy(void);
void LocalSession_Create(void);
void LocalSession_AllocBuffers(void);
void LocalSession_Disconnected(void);
u16 LocalSession_NextAllowedChannel(u16 channel);
void LocalSession_ReadAllowedChannels(void);

#endif
