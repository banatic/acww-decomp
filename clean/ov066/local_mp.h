/* The MP communication of the local wireless library of overlay 66 (local_wireless.h): starting
 * and ending WM's MP communication, the table of the players' MAC addresses by AID that the
 * parent keeps and sends to its children, the library's own messages on WM's port 12, and what
 * the game reads of the session. */
#ifndef CLEAN_OV066_LOCAL_MP_H
#define CLEAN_OV066_LOCAL_MP_H

#include "types.h"

#include "local_wireless.h"

/* The header of the library's own messages (8 bytes, sent through LocalSession.send_message). */
typedef struct LocalMessage {
    u16 kind;  /* LOCAL_MESSAGE_ */
    u16 size;  /* the message's bytes, the header included */
    u32 nonce; /* random */
} LocalMessage;

#define LOCAL_MESSAGE_MEMBERS 0 /* parent to children: the member table follows */
#define LOCAL_MESSAGE_HELLO 2   /* a child to its parent once the MP communication started */

#define LOCAL_MEMBER_COUNT 16 /* LocalSession.members */
#define LOCAL_AIDS_ALL 0xffff /* LocalSession.send_message's `to`: every AID */
#define LOCAL_AIDS_PARENT 0x1

/* What WM_StartMPEx's callback is handed (WMStartMPCallback): the fields this code reads. */
typedef struct LocalMpResult {
    LocalWmResult base;
    u16 state; /* LOCAL_WM_STATE_ */
} LocalMpResult;

/* What a port's receive callback is handed (WMPortRecvCallback): the fields this code reads. */
typedef struct LocalPortReceive {
    LocalWmResult base;
    u8 unk_04[8];
    const u8 *data; /* a LocalMessage first */
    u16 length;
    u16 aid; /* the sender's */
} LocalPortReceive;

/* The library's random numbers (data_ov066_0226bdf8, seeded from the MAC address). The ROM
 * computes the step in place each time; LocalMp_NextRandom is the same step as a function. */
extern u32 data_ov066_0226bdf8;

static inline u32 local_next_random(void)
{
    data_ov066_0226bdf8 = data_ov066_0226bdf8 * 0x5eedf715u + 0x1b0cb173u;
    return data_ov066_0226bdf8;
}

u32 LocalMp_PlayerCount(void);
u32 LocalMp_ReadBigEndian32(const u8 *bytes);
void LocalMp_OnEnd(LocalWmResult *result);
void LocalMp_End(void);
void LocalMp_OnMp(LocalMpResult *result);
void LocalMp_Start(void);
int LocalMp_EndIfAsked(void);
void LocalMp_AskEnd(void);
void LocalMp_OnMembers(const void *message);
void LocalMp_ReceiveAsChild(LocalPortReceive *received);
void LocalMp_OnHello(int aid, const void *message);
void LocalMp_ReceiveAsParent(LocalPortReceive *received);
void LocalMp_TellPeerLeft(int aid);
void LocalMp_OnReceive(LocalPortReceive *received);
void LocalMp_ClearMembers(void);
void LocalMp_CountMembers(void);
void LocalMp_UpdateMembers(u8 (*members)[6], const u8 (*received)[6]);
void LocalMp_OnMembersSent(void);
void LocalMp_SendMembers(void);
void LocalMp_SendHello(void);
void LocalMp_SetMember(int aid, const u8 *mac);
int LocalMp_Send(const void *buffer, u32 size, int to, void (*on_sent)(void *));
int LocalMp_CanSend(void);
u16 LocalMp_ConnectedAids(void);
int LocalMp_GetAid(void);
u32 LocalMp_NextRandom(void);

#endif
