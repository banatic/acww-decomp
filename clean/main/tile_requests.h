/* What a player asks to do to a tile of the map (data_021c7c48): to take what lies there, put an
 * item down, change a tile's code. A request takes one of three slots; TileRequests_Add fills
 * it and hands it to func_02045770, which carries it out here or, while linked with other
 * systems, sends it to the host. The slot's state then says what came of it, and the asker
 * polls it (TileRequests_Answer, TileRequests_Carry) and frees it (TileRequests_Release).
 *
 * The same object keeps two bits for each tile of the town's inner 64 x 64 tiles (the 16 tiles
 * at the map's edge left out), and the money rock of the day: each hit drops a bag of bells
 * next to it, a bigger one each time up to the eighth hit, until a timer started by the first
 * hit runs out and the rock's code goes from 0xe8 on back to 0xe3 on.
 *
 * What another system's player did is kept apart, one action for each session slot
 * (data_021c7788): set when its message arrives (TileRequests_ReceiveAction) and taken by that
 * player's actor (TileRequests_TakeAction). */
#ifndef CLEAN_MAIN_TILE_REQUESTS_H
#define CLEAN_MAIN_TILE_REQUESTS_H

#include "acre_map.h"
#include "autoload_2/vector.h"
#include "types.h"

#define TILE_REQUESTS_SLOTS 3
#define TILE_REQUESTS_NONE (-1) /* no slot */

/* TileRequest.state */
enum TileRequestState {
    TILE_REQUEST_FREE = 0,
    TILE_REQUEST_ASKED = 1,   /* handed to func_02045770, no answer yet */
    TILE_REQUEST_GRANTED = 2, /* may be carried out */
    TILE_REQUEST_REFUSED = 3
};

/* Some of the kinds of request, as the code here asks for them. */
enum TileRequestKind {
    TILE_REQUEST_TAKE = 3,   /* what lies on the tile into the pockets (4: no room for it) */
    TILE_REQUEST_KIND_5 = 5, /* the codes 0x1f, 0x21-0x24 and the codes of families B and C */
    TILE_REQUEST_KIND_9 = 9, /* 0xa with no room in the pockets */
    TILE_REQUEST_CHANGE_AROUND = 0xf,
    TILE_REQUEST_DROP = 0x10,       /* an item put down in front of the player */
    TILE_REQUEST_ACTOR_TILE = 0x11, /* at the tile of the player's actor record */
    TILE_REQUEST_DROP_12 = 0x12,    /* as 0x10, for a player with an actor record */
    TILE_REQUEST_KIND_13 = 0x13,
    TILE_REQUEST_FC_FD = 0x14,      /* on a tile of code 0xfc or 0xfd */
    TILE_REQUEST_KIND_15 = 0x15,    /* the code 0x20 (0x16: no room in the pockets) */
    TILE_REQUEST_SPLIT_DROP = 0x18, /* an item put down as two codes (func_020445c0) */
    TILE_REQUEST_MARKED_1566 = 0x19,
    TILE_REQUEST_DROP_A7 = 0x1a /* an item of 0xa7-0xc6 put down */
};

/* A tile of the map. */
typedef struct TileRequestTile {
    int x;
    int z;
} TileRequestTile;

typedef struct TileRequest {
    int player;           /* 0x00: the session slot asking */
    int holder;           /* 0x04: LinkGlobal_SceneHolder of the scene it was asked in */
    int state;            /* 0x08: TileRequestState */
    int kind;             /* 0x0c: TileRequestKind; 0 when free */
    u16 item;             /* 0x10 */
    u16 tile_item;        /* 0x12: the tile's code, or a second item */
    TileRequestTile tile; /* 0x14 */
    u8 layer;             /* 0x1c: which of the tile's two codes (1: the second), or where it was found */
    u8 unk_1d;            /* 0x1d */
    s8 unk_1e;            /* 0x1e */
    u8 unk_1f;
    int unk_20; /* 0x20: handed on to func_02045770 */
} TileRequest;

/* The money rock of the day. */
typedef struct TileRequestsRock {
    u8 z;      /* 0x00: the rock's tile */
    u8 x;      /* 0x01 */
    s16 hits;  /* 0x02: 0-8 */
    s16 timer; /* 0x04: frames left; -1 before the first hit */
    u16 unk_06;
} TileRequestsRock;

#define TILE_REQUESTS_MARK_BYTES 0x400

/* data_021c7c48; the scene's map (data_021c80bc) follows it. */
typedef struct TileRequests {
    TileRequest requests[TILE_REQUESTS_SLOTS]; /* 0x000 */
    u8 marks[TILE_REQUESTS_MARK_BYTES];        /* 0x06c: data_021c7cb4 */
    TileRequestsRock rock;                     /* 0x46c: data_021c80b4 */
} TileRequests;

/* What another system's player did to a tile (data_021c7788, one for each session slot). */
typedef struct TileRequestsAction {
    u8 kind; /* 0 for none */
    u8 sub;
    u16 tile; /* x in the high byte, z in the low */
} TileRequestsAction;

#define TILE_REQUESTS_ACTIONS 5

/* The message an action comes in (14 bytes). */
typedef struct TileRequestsActionMessage {
    u8 bits;            /* bit 0: the extra tiles are set; bits 1-2: the slot; bits 3-7: the kind */
    u8 bits2;           /* bits 5-6: TileRequestsAction.sub */
    u16 tile;           /* 0x02: x in the high byte, z in the low */
    u16 item;           /* 0x04 */
    u16 extra_tiles[3]; /* 0x06: 0xffff for none */
} TileRequestsActionMessage;

/* A player's actor, as far as it is read here. */
typedef struct TileRequestsActor {
    u8 unk_00[0x5c];
    Vec3 position; /* 0x5c */
    u8 unk_68[0x8e - 0x68];
    s16 facing; /* 0x8e */
} TileRequestsActor;

int TileRequests_TakeAction(TileRequestsAction *out, int player);
void TileRequests_ReceiveAction(const TileRequestsActionMessage *message);
void TileRequests_InitActions(TileRequestsAction *actions);
void TileRequests_ClearMarks(TileRequests *requests);
void TileRequests_SetMark(TileRequests *requests, const TileRequestTile *tile, int value);
int TileRequests_Mark(TileRequests *requests, const TileRequestTile *tile);
void TileRequests_UpdateRock(u32 requests);
void TileRequests_Reset(TileRequests *requests);
int TileRequests_DropBagAt(TileRequestsRock *rock, AcreMap *map, const TileRequestTile *tile);
void TileRequests_DropBag(TileRequestsRock *rock, const TileRequestTile *tile);
void TileRequests_HitRock(TileRequestsRock *rock, const TileRequestTile *tile);
void TileRequests_RockUpdate(TileRequestsRock *rock);
void TileRequests_RockInit(TileRequestsRock *rock);
void TileRequests_RockReset(TileRequestsRock *rock);
void TileRequests_Clear(TileRequest *requests, int index);
int TileRequests_Add(TileRequest *requests, int player, int kind, const TileRequestTile *tile, u16 item, u16 tile_item,
                     u8 unk_1d, u8 layer, int unk_20, s8 unk_1e);
TileRequest *TileRequests_At(int index);
void TileRequests_ClearSpawnTile(const Vec3 *position);
void TileRequests_ChangeCodesAround(int player, const TileRequestTile *tile);
void TileRequests_Release(int index);
int TileRequests_Carry(int index);
int TileRequests_FindDropTile(int kind, TileRequestTile *tile, u8 *place);
u16 *TileRequests_DropTileFor(int kind, AcreMap *map, int x, int z, const TileRequestTile *from);
int TileRequests_AskAtActorTileFor(int player, int item);
int TileRequests_AskDropFor(int player, int item);
int TileRequests_AskDrop12(int slot, int item);
int TileRequests_AskAtActorTile(int slot, int item);
int TileRequests_AskDrop(int slot, u16 item);
int TileRequests_AskPut(int slot, int kind, u16 item);
int TileRequests_Answer(u32 index);
int TileRequests_AskMarked1566(int unk_1e, const TileRequestTile *tile);
int TileRequests_AskMarked1566For(int player, const TileRequestTile *tile, int unused);
int TileRequests_AskFcFdFor(u32 player, const TileRequestTile *tile, u32 mode);
int TileRequests_AskFcFd(int slot, const TileRequestTile *tile, int mode);
int TileRequests_AskForTool0For(int player, const TileRequestTile *tile, int unused);
int TileRequests_AskPile(int slot, const TileRequestTile *tile);
int TileRequests_AskInTown(int slot, const TileRequestTile *tile);
int TileRequests_AskForTool0(int slot, const TileRequestTile *tile, int unused);
int TileRequests_AskAtActorTileOpFor(int player, int operation, int arg, int item);
int TileRequests_AskAtActorTileOp(int slot, int operation, int arg, int item);
int TileRequests_AskOpFor(int player, const TileRequestTile *tile, int operation, int arg, u16 item);

/* The operations of TileRequests_AskOp (func_02043db4), each a request of the kind the tile's
 * code calls for:
 *
 *   0  TileRequests_AskStrip: a code of the growth lines (map_item.h) past stage 1 gives up what
 *      it bears and takes its bare code (kind 1, or 2 for 0x67 and 0x6b when an item may drop);
 *   1  TileRequests_AskHit: the tile's mark (TileRequests_Mark) counts the hits on a growth line
 *      code, and enough of them make it a short line code (kind 6, or 7); the rocks 0xe3-0xe7
 *      give kind 0xd, the money rocks 0xe8-0xfb kind 0xc, or 0xe for the rock of the current
 *      player's number;
 *   2  TileRequests_AskHole: a hole (0xfc, 0xfd) made in an empty tile (kind 8), an item put in
 *      a hole (kind 0x13), and what other codes call for;
 *   4  TileRequests_AskAround: the codes around the tile changed (kind 0xf). */
#define TILE_REQUESTS_OP_STRIP 0
#define TILE_REQUESTS_OP_HIT 1
#define TILE_REQUESTS_OP_HOLE 2
#define TILE_REQUESTS_OP_AROUND 4

int TileRequests_AskOp(int slot, const TileRequestTile *tile, int operation, int arg, u16 item);
int TileRequests_AskAround(int slot, const u16 *code, const TileRequestTile *tile, int arg);
int TileRequests_AskHole(int slot, AcreMap *town, const u16 *code, const TileRequestTile *tile, u16 item, int arg);
int TileRequests_AskHit(int slot, const u16 *code, const TileRequestTile *tile, int arg);
int TileRequests_AskStrip(int slot, const u16 *code, const TileRequestTile *tile, int arg);
void TileRequests_AllowItemDrop(void);
void TileRequests_ForbidItemDrop(void);
int TileRequests_ItemDropAllowed(void);
void TileRequests_HoleCodes(int slot, u16 *item, u16 *code, u8 *unchanged, u16 put);
int TileRequests_SplitItem(u16 *item, u16 *tile_item, u16 code);
void TileRequests_BagCodes(u16 *item, u8 *unchanged, u16 put);
int TileRequests_HeldItem(int player);
int TileRequests_MayAsk(int slot);
int TileRequests_SlotOf(int player);
int TileRequests_PlayerOf(int slot);

#endif
