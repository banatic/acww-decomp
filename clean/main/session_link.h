/* Starting, running and ending the multiplayer session (session.h) over the network library
 * (autoload_2/network.h).
 *
 * Session_Start starts the library for play with others (the local wireless library when its
 * mode is 1 or 2, the Wi-Fi Connection otherwise) and allocates the session's buffers from the
 * network heap; Session_StartExchange starts it for the wireless exchange of data, without
 * buffers. Session_End and Session_EndExchange end it. Once a frame Session_Update fills and
 * sends the packets (session.h) and Session_Deliver hands what was received to its handlers;
 * Session_OnReceived is the library's receive callback.
 *
 * Next to the session, a link state table (data_021f4320) keeps for each slot a status number
 * (func_020a6f64 reads it, func_020a6f74 sets it) and a 3-byte entry (func_020a7394). Slot 3
 * stands for this system while it has no slot. A status of 5 or 6 is one the host still has
 * to tell its slot (Session_WriteStatusPacket); the host then sets it to 7.
 *
 * A system packet (session.h, top bit of the first byte) carries in bits 2-6 of its first byte
 * a kind: below 24 the handler of system_packet.c that takes its payload; 24 gives only
 * credits back. */
#ifndef CLEAN_MAIN_SESSION_LINK_H
#define CLEAN_MAIN_SESSION_LINK_H

#include "session.h"
#include "types.h"

/* The error flags (NetSession.error_flags). */
enum {
    SESSION_ERROR_PEER_SILENT = 0x01,  /* a peer has not been heard for too long */
    SESSION_ERROR_OUTBOX_FULL = 0x02,  /* the send buffer could not move to the outbox */
    SESSION_ERROR_PEER_MISSING = 0x04, /* host: a peer's AID is not connected */
    SESSION_ERROR_CONNECTION = 0x08,   /* guest: the connection's update failed */
    SESSION_ERROR_SEND_TIMEOUT = 0x40  /* Session_IsLinkLost was true (Session_RaiseSendTimeout) */
};

#define SESSION_UNLINKED_SLOT 3   /* the link state slot of this system while it has no slot */
#define SESSION_SYSTEM_CREDITS 24 /* the system packet kind that only gives credits back */

void Session_Reset(NetSession *session);
void Session_ResetPlayer(NetSession *session);
void Session_Init(NetSession *session);
void Session_Destroy(NetSession *session);
NetSession *Session_Construct(NetSession *session);

int Session_IsLinkLost(int expected_aids);
void Session_RaiseSendTimeout(void);
void Session_Close(void);
unsigned int Session_GetMemberMask(void);
int Session_GetPeerMask(void);

void Session_FinishLocalStatus(void);
int Session_GetLocalStatus(void);
int Session_SendLocalStatus(int status);

void Session_SetReceiveBuffers(u32 local_aid);
void Session_ResetLinkStatus(void);
void Session_StopTransfer(u32 local_aid);
void Session_Host(void);
void Session_SetHostReceiveBuffers(void);
int Session_SendNothing(void);

void Session_Update(int keep_frame);
void Session_Deliver(int skip);

void Session_FreeHeap(void);
void Session_EndExchange(void);
int Session_End(void);
void Session_StartExchange(void);
void Session_Start(int mode, int players, int connect_mode);
void Session_CreateHeap(void *parent);

void Session_RemovePlayer(int slot);
int Session_WriteStatusPacket(int slot);
int Session_IsStatusPending(int slot);
int Session_CollectMessages(u8 *dst, int slot);
int Session_WriteRecords(u8 *dst, const u8 *copy, int size);
void Session_WriteOwedCredits(void);

int Session_HasReachedSequence(int sequence);
int Session_IsSequenceReached(int sequence, int current);

void Session_OnReceived(int aid, char *packet, unsigned int size);
void Session_EnableInterrupts(void);
void Session_DisableInterrupts(void);
void Session_OnPlayersChanged(int change);

#endif
