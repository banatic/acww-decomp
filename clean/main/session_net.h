/* Small pieces of the multiplayer session (session.h): the network heap its buffers come from
 * (data_021c9b30), the first byte of a packet, the peer index of a slot and two questions about
 * the link.
 *
 * A packet's first byte: bits 0-1 the credits it gives back, bit 7 set for a system packet,
 * whose kind (system_packet.h) is in bits 2-6. */
#ifndef CLEAN_MAIN_SESSION_NET_H
#define CLEAN_MAIN_SESSION_NET_H

#include "types.h"

int SessionNet_IsWifiGame(void);
int SessionNet_AllPeersHaveCredit(void);
int SessionNet_PeersHaveCredit(u16 slots);
void SessionNet_Free(void *block);
void *SessionNet_Alloc(int size, int align);
int SessionNet_GetSystemKind(const u8 *packet);
int SessionNet_GetCredits(const u8 *packet);
int SessionNet_IsSystemPacket(const u8 *packet);
void SessionNet_WriteSystemHeader(u8 *packet, int credits, int kind);
void SessionNet_WriteDataHeader(u8 *packet, int credits);
int SessionNet_PeerIndex(int slot);

#endif
