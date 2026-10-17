/* The data relay of the local wireless library of overlay 66 (local_wireless.h): the layer the
 * game sends its blocks through once connected, on WM's port 13, installed in the session's
 * handlers by LocalRelay_Start.
 *
 * Every player owns a slice of LocalRelay.slice_size bytes in each MP turn. A block the game
 * sends (LocalRelay_SendBlock) is cut into fragments that fit a slice, the first carrying the
 * AIDs it is for and its size. A child sends its fragment to the parent after each MP
 * acknowledgement; the parent collects the fragments of every player, its own included, and at
 * the end of each MP turn sends them to all the children as one relay packet with a 4-bit
 * sequence number. Every player, the parent too, takes each slice of a relay packet as a
 * fragment from that AID and fills the receive buffer the game gave for it
 * (LocalRelay_SetReceiveBuffer); a block complete goes to the session's receive handler.
 *
 * The parent keeps its last relay packets in a ring of three: a new one is built only when the
 * one sent two before was acknowledged by every child that greeted it. A child acknowledges
 * each relay packet in order, asks for the one it missed when it sees a gap of one, and stops
 * sending fragments for the turn after a larger gap. */
#ifndef CLEAN_OV066_LOCAL_RELAY_H
#define CLEAN_OV066_LOCAL_RELAY_H

#include "types.h"

#include "local_wireless.h"

/* What the game hands LocalRelay_Start (8 bytes). */
typedef struct LocalRelayParams {
    u32 ggid;            /* the parents' game group id */
    u8 players;          /* the players, the parent included */
    u8 parents_per_list; /* LocalControl.parents_per_list */
    u8 slice_size;       /* the bytes each player sends in one MP turn */
    u8 mp_frequency;     /* LocalControl.mp_frequency */
} LocalRelayParams;

/* The head of a relay packet: its sequence number and the AIDs whose slice follows, each
 * slice_size bytes, in AID order. */
typedef struct LocalRelayHeader {
    u8 seq;
    u8 unk_01;
    u16 slices;
} LocalRelayHeader;

/* A node of the relay's rings: a packet with what the parent knows of it. A ring's nodes are
 * allocated together, each large enough for a relay packet. */
typedef struct LocalRelayNode {
    struct LocalRelayNode *prev;
    struct LocalRelayNode *next;
    u16 size;    /* the packet's bytes */
    u16 pending; /* the AIDs that are to acknowledge it */
    u16 acked;   /* the AIDs that did */
    u8 unk_0e[0x12];
    /* The packet: a relay packet, or a child's fragment (its LocalRelayFragment flags byte at
     * header.seq). */
    LocalRelayHeader header;
    u8 data[]; /* the parent's collecting ring: the slice of AID n at n * slice_size */
} LocalRelayNode;

/* A fragment, as a player sends it: the flags byte, the data bytes that follow and, for the
 * first fragment of a block only, the block's AIDs and size, its data from byte 8. A later
 * fragment's data follow from byte 2. */
typedef struct LocalRelayFragment {
    u8 flags;  /* LOCAL_FRAGMENT_ */
    u8 length; /* the data bytes in this fragment */
    u16 to;    /* the AIDs the block is for */
    u16 size_low;
    u16 size_high;
} LocalRelayFragment;

/* LocalRelayFragment.flags: its kind, whether it ends its block, and an acknowledgement or a
 * request with the sequence number of a relay packet in the high four bits. */
#define LOCAL_FRAGMENT_KIND 0x3
#define LOCAL_FRAGMENT_FIRST 0    /* the first fragment of a block */
#define LOCAL_FRAGMENT_NEXT 1     /* a later one */
#define LOCAL_FRAGMENT_ACK_ONLY 2 /* no data: an acknowledgement alone */
#define LOCAL_FRAGMENT_RESEND 3   /* no data: the relay packet of the high bits is asked again */
#define LOCAL_FRAGMENT_LAST 0x4   /* the fragment ends its block */
#define LOCAL_FRAGMENT_ACK 0x8    /* the relay packet of the high bits was received */
#define LOCAL_FRAGMENT_FIRST_HEAD 8
#define LOCAL_FRAGMENT_NEXT_HEAD 2

/* The game's receive buffer for the blocks of one AID (16 bytes). */
typedef struct LocalRelaySlot {
    u8 *buffer;
    u32 capacity;
    u32 expected; /* the size of the block being received */
    u32 received; /* its bytes so far */
} LocalRelaySlot;

/* The relay (data_ov066_0226be08, 0x34 bytes). */
typedef struct LocalRelay {
    u8 slice_size;
    /* Low four bits: the parent's next sequence number, a child's last one received. High four
     * bits: the sequence number a child asks again. */
    u8 sequence;
    s8 in_flight;   /* packets handed to WM whose sending did not end yet */
    s8 own_pending; /* this DS's fragments sent and not yet seen in a relay packet */
    u8 flags;       /* LOCAL_RELAY_ */
    u8 unk_05[3];
    /* Three nodes. The parent's relay packets; a child's own packets to send. */
    LocalRelayNode *packets;
    /* Three nodes. The parent collects each AID's fragments in them; a child queues there the
     * sequence numbers it has to acknowledge (written at per_aid[0], read at per_aid[1]). */
    LocalRelayNode *collected;
    LocalRelayNode *cursor; /* in packets: the next to build or send */
    LocalRelayNode *resend; /* the parent's: the next relay packet to send again, or NULL */
    LocalRelayNode **per_aid;
    u16 receiving; /* by AID: a block being received */
    u16 block_to;  /* the block being sent: its AIDs, data, size and bytes cut so far */
    const u8 *block;
    u32 block_size;
    u32 block_sent; /* 0xffffffff without a block */
    void (*on_block_sent)(void *argument);
    LocalRelaySlot *slots; /* by AID */
} LocalRelay;

/* LocalRelay.flags */
#define LOCAL_RELAY_RESYNC 0x1     /* a child takes the next relay packet whatever its number */
#define LOCAL_RELAY_GAP 0x2        /* a child saw a gap: no fragment of its own this turn */
#define LOCAL_RELAY_ASK_RESEND 0x4 /* a child asks for the relay packet it missed */
#define LOCAL_RELAY_SENDING 0x8    /* a block is being sent */
#define LOCAL_RELAY_LAST_OUT 0x10  /* the block's last fragment is cut */

/* The nodes of each of the relay's rings. */
#define LOCAL_RELAY_RING 3

/* WM's ports: the library's messages and the relay. */
#define LOCAL_PORT_MESSAGES 12
#define LOCAL_PORT_RELAY 13
/* WM_SetMPDataToPortEx's priority. */
#define LOCAL_RELAY_PRIORITY 2

/* WM_ERRCODE_NO_CHILD: a parent sent with no child, which is not an error here. */
#define LOCAL_WM_RESULT_NO_CHILD 7
/* WM_STATECODE_PORT_RECV, in a port's receive callback. */
#define LOCAL_WM_STATE_PORT_RECV 21

/* More LocalControl.flags: cleared by LocalRelay_Configure; no other part of the library reads
 * or sets it. */
#define LOCAL_FLAG_200 0x200

/* What a port's receive callback is handed (WMPortRecvCallback): the fields this code reads. */
typedef struct LocalPortEvent {
    LocalWmResult base;
    u16 state; /* LOCAL_WM_STATE_ */
    u16 port;
    u8 unk_08[4];
    u8 *data;
    u16 length;
    u16 aid; /* the sender's */
} LocalPortEvent;

/* What WM_SetMPDataToPortEx's callback is handed (WMPortSendCallback): the fields this code
 * reads. */
typedef struct LocalPortSent {
    LocalWmResult base;
    u8 unk_04[0x10];
    u8 *data; /* what was sent */
    u8 unk_18[8];
    void (*callback)(void *result); /* the argument WM was handed: called with this */
} LocalPortSent;

int LocalRelay_SetReceiveBuffer(int aid, void *buffer, u32 capacity);
u32 LocalRelay_Reset(void);
void LocalRelay_OnPortReceive(LocalPortEvent *event);
void LocalRelay_OnPeerDisconnected(LocalPortEvent *event);
void LocalRelay_OnData(LocalPortEvent *event);
void LocalRelay_OnChildPacket(int aid, u8 *packet, int length);
LocalRelayNode *LocalRelay_FindPacket(u8 seq, LocalRelayNode *cursor);
void LocalRelay_OnPortSent(LocalPortSent *result);
void LocalRelay_SendMessage(void *buffer, u32 size, u32 to, void (*on_sent)(void *));
int LocalRelay_SendToPort(int port, const void *data, u32 size, u32 to, void (*callback)(void *));
void LocalRelay_ForgetPeer(int aid);
void LocalRelay_OnMpAck(void);
void LocalRelay_OnMpEnd(void);
int LocalRelay_Collect(LocalRelayNode *relay, LocalRelayNode *collected);
void LocalRelay_Deliver(LocalRelayHeader *relay);
void LocalRelay_ReceiveFragment(int aid, u8 *fragment);
void LocalRelay_SendFromChild(void);
void LocalRelay_AddOwnFragment(LocalRelayNode *collected);
u16 LocalRelay_NextFragment(u8 *fragment);
void LocalRelay_OnRelaySent(void);
void LocalRelay_OnChildPacketSent(LocalPortSent *result);
void LocalRelay_FinishBlock(void);
void LocalRelay_OnIndication(void);
int LocalRelay_SendBlock(const void *buffer, u32 size, int to, void (*on_sent)(void *));
int LocalRelay_CanSend(void);
void LocalRelay_Shutdown(void);
int LocalRelay_Start(LocalRelayParams *params);
void LocalRelay_ClearRing(LocalRelayNode *node, int count);
LocalRelayNode *LocalRelay_CreateRing(int count);
void LocalRelay_Configure(LocalRelayParams *params);

#endif
