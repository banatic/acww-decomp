/* Small pieces of the multiplayer session (session_net.h). */
#include "session_net.h"

#include "autoload_2/heap.h"
#include "autoload_2/network.h"
#include "clean.h"
#include "main/session.h"

#define MODE_HOSTING 3 /* Net_GetMode: hosting a game friends join over the Wi-Fi Connection */
#define MODE_JOINING 4 /* joining a friend's game */

#define ALL_SLOTS 0xf /* the mask of slots 0-3 */

#define PACKET_CREDITS 0x03 /* bits 0-1 of a packet's first byte */
#define PACKET_KIND 0x1f    /* bits 2-6, the kind of a system packet */
#define PACKET_KIND_SHIFT 2
#define PACKET_SYSTEM 0x80 /* bit 7 */

extern NetSession *data_020ccf94; /* the session */
extern Heap *data_021c9b30;       /* the network heap */

/* func_02077a64: whether the session runs over the Wi-Fi Connection (hosting or joining). */
int SessionNet_IsWifiGame(void)
{
    int mode = Net_GetMode();
    return mode == MODE_HOSTING || mode == MODE_JOINING;
}
CLEAN_AS(func_02077a64, SessionNet_IsWifiGame)

/* func_02077a80: whether every other system in the session has a credit. */
int SessionNet_AllPeersHaveCredit(void)
{
    return SessionNet_PeersHaveCredit(ALL_SLOTS);
}
CLEAN_AS(func_02077a80, SessionNet_AllPeersHaveCredit)

/* func_02077a8c: 0 when one of the slots in the mask `slots` (bit n for slot n) is taken by
 * another system that has no credit left, else 1. The slots are asked from 3 down to 0. */
int SessionNet_PeersHaveCredit(u16 slots)
{
    NetSession *session = data_020ccf94;

    for (int slot = SESSION_SLOTS - 1; slot >= 0; slot--) {
        if (Session_IsSlotTaken(session, slot) == 0) {
            continue;
        }
        if (Session_IsLocalSlot(session, slot) != 0) {
            continue;
        }
        if ((slots & (1u << slot)) == 0) {
            continue;
        }
        if (Session_GetCredits(session, slot) == 0) {
            return 0;
        }
    }
    return 1;
}
CLEAN_AS(func_02077a8c, SessionNet_PeersHaveCredit)

/* func_02077ae8: gives `block` back to the network heap. */
void SessionNet_Free(void *block)
{
    Heap_Free(data_021c9b30, block);
}
CLEAN_AS(func_02077ae8, SessionNet_Free)

/* func_02077afc: `size` bytes from the network heap, aligned to `align`. */
void *SessionNet_Alloc(int size, int align)
{
    return Heap_AllocAligned(data_021c9b30, size, align);
}
CLEAN_AS(func_02077afc, SessionNet_Alloc)

/* func_02077b14: a system packet's kind. */
int SessionNet_GetSystemKind(const u8 *packet)
{
    return *packet >> PACKET_KIND_SHIFT & PACKET_KIND;
}
CLEAN_AS(func_02077b14, SessionNet_GetSystemKind)

/* func_02077b20: the credits a packet gives back. */
int SessionNet_GetCredits(const u8 *packet)
{
    return *packet & PACKET_CREDITS;
}
CLEAN_AS(func_02077b20, SessionNet_GetCredits)

/* func_02077b28: whether a packet is a system packet. */
int SessionNet_IsSystemPacket(const u8 *packet)
{
    return (*packet & PACKET_SYSTEM) != 0;
}
CLEAN_AS(func_02077b28, SessionNet_IsSystemPacket)

/* func_02077b3c: the first byte of a system packet of `kind` giving back `credits`. */
void SessionNet_WriteSystemHeader(u8 *packet, int credits, int kind)
{
    *packet = (u8) (((u32) kind & PACKET_KIND) << PACKET_KIND_SHIFT | PACKET_SYSTEM | ((u32) credits & PACKET_CREDITS));
}
CLEAN_AS(func_02077b3c, SessionNet_WriteSystemHeader)

/* func_02077b50: the first byte of a data packet giving back `credits`. */
void SessionNet_WriteDataHeader(u8 *packet, int credits)
{
    *packet = (u8) (credits & PACKET_CREDITS);
}
CLEAN_AS(func_02077b50, SessionNet_WriteDataHeader)

/* func_02077b58: the peer index of a slot: the slots in order without this system's AID (its
 * own slot gets the index of the one below it). */
int SessionNet_PeerIndex(int slot)
{
    if (slot >= Net_GetMyAid()) {
        return slot - 1;
    }
    return slot;
}
CLEAN_AS(func_02077b58, SessionNet_PeerIndex)
