/* What a player asks to do to a tile of the map (tile_requests.h). */
#include "tile_requests.h"

#include "acre_tile.h"
#include "actor_table.h"
#include "clean.h"
#include "link_global.h"
#include "map_item.h"
#include "room_score.h"
#include "room_sync.h"
#include "scene_query.h"
#include "session.h"
#include "villager_events.h"

static_assert(sizeof(TileRequest) == 0x24, "TileRequest");
static_assert(offsetof(TileRequest, tile) == 0x14, "TileRequest.tile");
static_assert(offsetof(TileRequest, unk_20) == 0x20, "TileRequest.unk_20");
static_assert(offsetof(TileRequests, marks) == 0x6c, "TileRequests.marks");
static_assert(offsetof(TileRequests, rock) == 0x46c, "TileRequests.rock");
static_assert(sizeof(TileRequestsAction) == 4, "TileRequestsAction");
static_assert(offsetof(TileRequestsActionMessage, extra_tiles) == 6, "TileRequestsActionMessage");
static_assert(offsetof(TileRequestsActor, facing) == 0x8e, "TileRequestsActor.facing");

extern TileRequests data_021c7c48;
extern u8 data_021c7cb4[TILE_REQUESTS_MARK_BYTES]; /* data_021c7c48.marks */
extern AcreMap *data_021c80bc;                     /* the scene's map */
extern TileRequestsAction data_021c7788[TILE_REQUESTS_ACTIONS];
extern u8 data_021c779c[]; /* the town's object */
extern NetSession *data_020ccf94;
extern u8 data_020e54a8; /* 0 outdoors, 1 in a room */

/* The neighbours of a tile, each a byte: x + 8 in the high four bits, z + 8 in the low. */
extern const u8 data_020ca5d4[8];
extern const u8 data_020ca634[];
/* For each facing (func_020644e4), nine entries of data_020ca634: the tiles to try for a drop,
 * the nearest first. */
extern const int data_020cb638[][9];
/* The offsets of the five tiles of a cross: the tile, left, right, up, down. */
extern const s8 data_020ca584[5];
extern const s8 data_020ca58c[5];
/* The bag of bells the money rock drops at each hit (0x1492 for the first). */
extern const u16 data_020cab3c[];
extern const u16 data_020ca664[];

/* The session slot to use for `player`: itself while linked, else 0. */
extern int func_02044858(int player);
/* Whether `slot` may ask: 1 when not linked, else Session_IsLocalSlot. */
extern int func_0204482c(int slot);
/* The tile record (a halfword: x high, z low) of the actor of `slot`, or NULL. */
extern u16 *func_02045b5c(int slot);
/* The index of the actor standing on a tile, or a negative number. */
extern int func_02045cec(const TileRequestTile *tile, int flag);
extern int func_02045d80(const TileRequestTile *tile, int flag);
extern int func_02045ac4(const TileRequestTile *tile, int player);
extern void func_02045e24(const TileRequestTile *tile, int flag);
extern void func_02045f08(const TileRequestTile *tile, int arg);
extern void func_02045770(u8 index, int arg);
extern TileRequestsActor *func_020961a8(int player);
extern int func_020644e4(int facing);
extern int func_020317c4(int from_x, int from_z, int x, int z, u8 flag);
extern int func_020445c0(u16 *item, u16 *tile_item, u16 code);
extern int func_02043db4(int slot, const TileRequestTile *tile, int operation, int arg, u16 item);
/* The item `item` put on the tile (x, z) of the town (whose code becomes `code`). */
extern int func_02046024(int unk, const TileRequestTile *tile, u32 item, u32 code, u8 a, u8 b, u8 c, u8 d, u8 e, s8 f);
extern void func_0204a330(int x, int z, int code, int flag);
extern void func_0204811c(u8 *town, const Vec3 *position);
/* The code a code of family B (and 0x88, 0xd4-0xda) changes into, 0xfff1 for none; `alternative`
 * changes 0x86 into 0xa5. */
extern u16 func_020475b0(u8 *town, const u16 *code, int alternative);
extern void func_0205f9d4(u8 x, u8 z, int scene, int code, int flag);
/* The item the actor of `player` holds (0xfff1 for none). */
extern int func_02044808(int player);

extern void *CurrentPockets_FreeLetter(void);
extern int CurrentPockets_FreeSlot(void);

extern int func_ov003_02221118(int player, int item, const TileRequestTile *tile);
extern int func_ov003_02221304(int player, int item, const TileRequestTile *tile, const Vec3 *position);
extern int func_ov003_02220e20(int player, int item, const TileRequestTile *tile, const Vec3 *position);
extern int func_ov004_022335b8(int player, int item, const TileRequestTile *tile, const Vec3 *position, int layer);

extern void MI_CpuFill8(void *dst, u8 value, u32 size);

#define TILE_REQUESTS_PLAYER_ACTOR 4 /* func_020961a8's number for this system's player */
#define TILE_REQUESTS_BOTTLE 0x1520  /* the bottle with a letter: it needs a letter's place */
#define TILE_REQUESTS_ITEM_1379 0x1379
#define TILE_REQUESTS_MARKED_ITEM 0x1566
#define TILE_REQUESTS_ROCK_HITS 8
#define TILE_REQUESTS_ROCK_TIME 150
#define TILE_REQUESTS_ROCK 0xe3       /* the rock's codes after it, 0xe3-0xe7 */
#define TILE_REQUESTS_MONEY_ROCK 0xe8 /* its codes before, from 0xe8, five to a cycle */
#define TILE_REQUESTS_ROCKS 5
#define TILE_REQUESTS_NO_TILE 0xffff
#define TILE_REQUESTS_MARK_EDGE 16

/* An arithmetic shift right, as the ARM's. */
static int TileRequests_ShiftRight(int value, int shift)
{
    return value >= 0 ? value >> shift : ~(~value >> shift);
}

/* The code on the tile (x, z) of `map` (layer 0 or 1), or NULL. */
static u16 *TileRequests_CodeAt(AcreMap *map, int x, int z, u8 layer)
{
    return AcreTile_ItemInAcre(map, (u32) TileRequests_ShiftRight(x, 4), (u32) TileRequests_ShiftRight(z, 4), x & 0xf, z & 0xf,
                               layer);
}

static int TileRequests_InRange(u32 code, u32 first, u32 last)
{
    return code >= first && code <= last;
}

/* The codes of family A of map_item.h, with 0x1c. */
static int TileRequests_IsFamilyA(u32 code)
{
    return code <= 0x05 || TileRequests_InRange(code, 0x06, 0x0b) || TileRequests_InRange(code, 0x0c, 0x11) ||
           TileRequests_InRange(code, 0x12, 0x19) || code == 0x1c;
}

/* The codes of family B. */
static int TileRequests_IsFamilyB(u32 code)
{
    return TileRequests_InRange(code, 0x6e, 0x73) || TileRequests_InRange(code, 0x74, 0x79) ||
           TileRequests_InRange(code, 0x7a, 0x7f) || TileRequests_InRange(code, 0x80, 0x87);
}

/* The codes of family C, with 0xa5. */
static int TileRequests_IsFamilyC(u32 code)
{
    return TileRequests_InRange(code, 0x8a, 0x8f) || TileRequests_InRange(code, 0x90, 0x95) ||
           TileRequests_InRange(code, 0x96, 0x9b) || TileRequests_InRange(code, 0x9c, 0xa3) || code == 0xa5;
}

static TileRequestTile TileRequests_TileOf(u16 packed)
{
    TileRequestTile tile = {packed >> 8, packed & 0xff};
    return tile;
}

/* ---- What other systems' players did */

/* func_02042a5c: the action of `player`'s slot, if there is one, copied out and taken (1);
 * else 0. */
int TileRequests_TakeAction(TileRequestsAction *out, int player)
{
    TileRequestsAction *action = &data_021c7788[func_02044858(player)];
    if (action->kind == 0) {
        return 0;
    }
    out->kind = action->kind;
    out->tile = action->tile;
    out->sub = action->sub;
    action->kind = 0;
    return 1;
}
CLEAN_AS(func_02042a5c, TileRequests_TakeAction)

/* func_02042a9c: an action received. The slot's action still pending has its tile let go
 * (func_02045e24, with the message's extra tiles when it has them) before the new one takes
 * its place. Kinds 0x10-0x12 and 0x13 (unless its item is 0xfff1) are shown at once by overlay
 * 3 (or overlay 4 for 0x10-0x12 in a room), given the position of this system's player; kind
 * 0xf changes the codes around the tile. */
void TileRequests_ReceiveAction(const TileRequestsActionMessage *message)
{
    int slot = (message->bits >> 1) & 3;
    int kind = message->bits >> 3;
    TileRequestsAction *action = &data_021c7788[slot];
    if (action->kind != 0) {
        TileRequestTile old = TileRequests_TileOf(action->tile);
        func_02045e24(&old, 0);
        if ((message->bits & 1) == 1) {
            for (int i = 0; i < 3; i++) {
                if (message->extra_tiles[i] != TILE_REQUESTS_NO_TILE) {
                    TileRequestTile extra = TileRequests_TileOf(message->extra_tiles[i]);
                    func_02045e24(&extra, 0);
                }
            }
        }
    }
    action->kind = (u8) kind;
    action->tile = message->tile;
    action->sub = (message->bits2 >> 5) & 3;

    TileRequestTile tile = TileRequests_TileOf(message->tile);
    TileRequestsActor *player;
    Vec3 position;
    switch (kind) {
        case TILE_REQUEST_DROP:
        case TILE_REQUEST_ACTOR_TILE:
        case TILE_REQUEST_DROP_12:
            player = func_020961a8(slot);
            if (player == NULL) {
                break;
            }
            position = player->position;
            if (data_020e54a8 == 0) {
                func_ov003_02221304(slot, message->item, &tile, &position);
            } else {
                func_ov004_022335b8(slot, message->item, &tile, &position, 0);
            }
            break;
        case TILE_REQUEST_CHANGE_AROUND:
            TileRequests_ChangeCodesAround(slot, &tile);
            break;
        case TILE_REQUEST_KIND_13:
            if (message->item == ITEM_CODE_NONE) {
                break;
            }
            player = func_020961a8(slot);
            if (player == NULL) {
                break;
            }
            position = player->position;
            func_ov003_02220e20(slot, message->item, &tile, &position);
            break;
        default:
            break;
    }
}
CLEAN_AS(func_02042a9c, TileRequests_ReceiveAction)

/* func_02042c28: no action for any slot. */
void TileRequests_InitActions(TileRequestsAction *actions)
{
    for (int i = 0; i < TILE_REQUESTS_ACTIONS; i++) {
        actions[i].kind = 0;
        actions[i].tile = TILE_REQUESTS_NO_TILE;
    }
}
CLEAN_AS(func_02042c28, TileRequests_InitActions)

/* ---- The tiles' marks */

/* func_02042c40: every mark cleared.
 * QUIRK: the marks of data_021c7c48 are cleared, whatever object is handed (the callers hand
 * that one). */
void TileRequests_ClearMarks(TileRequests *requests)
{
    (void) requests;
    MI_CpuFill8(data_021c7cb4, 0, TILE_REQUESTS_MARK_BYTES);
}
CLEAN_AS(func_02042c40, TileRequests_ClearMarks)

/* Where a tile's mark is: four tiles to a byte, the first in bits 0-1. A tile outside the inner
 * 64 x 64 tiles uses the bits of the first. */
static u8 *TileRequests_MarkAt(TileRequests *requests, const TileRequestTile *tile, int *shift)
{
    int x = tile->x;
    int index = TileRequests_ShiftRight(x - TILE_REQUESTS_MARK_EDGE, 2) + (tile->z - TILE_REQUESTS_MARK_EDGE) * 16;
    *shift = (x & 3) * 2;
    if (index < 0 || index >= TILE_REQUESTS_MARK_BYTES) {
        index = 0;
        *shift = 0;
    }
    return &requests->marks[index];
}

/* func_02042c58: the tile's mark set to `value`.
 * QUIRK: `value` is not cut to two bits; more would spill into the next tiles' marks. */
void TileRequests_SetMark(TileRequests *requests, const TileRequestTile *tile, int value)
{
    int shift;
    u8 *mark = TileRequests_MarkAt(requests, tile, &shift);
    *mark = (u8) ((u32) value << shift | (*mark & ~(3u << shift)));
}
CLEAN_AS(func_02042c58, TileRequests_SetMark)

/* func_02042c9c: the tile's mark (0-3). */
int TileRequests_Mark(TileRequests *requests, const TileRequestTile *tile)
{
    int shift;
    const u8 *mark = TileRequests_MarkAt(requests, tile, &shift);
    return (*mark >> shift) & 3;
}
CLEAN_AS(func_02042c9c, TileRequests_Mark)

/* ---- The money rock */

/* func_02042cd8: the money rock's frame (`requests` is the TileRequests' address). */
void TileRequests_UpdateRock(u32 requests)
{
    TileRequests_RockUpdate((TileRequestsRock *) (uintptr_t) (requests + offsetof(TileRequests, rock)));
}
CLEAN_AS(func_02042cd8, TileRequests_UpdateRock)

/* func_02042ce8: every request slot freed and the money rock set up for the day. */
void TileRequests_Reset(TileRequests *requests)
{
    for (int i = 0; i < TILE_REQUESTS_SLOTS; i++) {
        TileRequests_Clear(requests->requests, i);
    }
    TileRequests_RockReset(&requests->rock);
}
CLEAN_AS(func_02042ce8, TileRequests_Reset)

/* func_02042d14: the bag of the rock's hits put on the tile of the town `map` when it is empty
 * and AcreTile_UnitByte04 allows it; whether it was. */
int TileRequests_DropBagAt(TileRequestsRock *rock, AcreMap *map, const TileRequestTile *tile)
{
    u16 *code = TileRequests_CodeAt(map, tile->x, tile->z, 0);
    if (code == NULL || *code != ITEM_CODE_NONE) {
        return 0;
    }
    if (AcreTile_UnitByte04(map, tile->x, tile->z) == 0) {
        return 0;
    }
    TileRequestTile at = *tile;
    func_02046024(0, &at, data_020cab3c[rock->hits], ITEM_CODE_NONE, 0, 0, 0, 3, 0, -1);
    return 1;
}
CLEAN_AS(func_02042d14, TileRequests_DropBagAt)

/* func_02042d94: the bag dropped on the first of the rock's eight neighbours (data_020ca5d4)
 * inside the town that takes it. */
void TileRequests_DropBag(TileRequestsRock *rock, const TileRequestTile *tile)
{
    AcreMap *town = (AcreMap *) (uintptr_t) AcreMap_Town();
    if (town == NULL) {
        return;
    }
    int wide = town->acres_wide * 16;
    int high = town->acres_high * 16;
    for (int i = 0; i < 8; i++) {
        u8 offset = data_020ca5d4[i];
        TileRequestTile at = {tile->x - ((offset >> 4) - 8), tile->z - ((offset & 0xf) - 8)};
        if (at.x < 0 || at.x >= wide || at.z < 0 || at.z >= high) {
            continue;
        }
        if (at.x == tile->x && at.z == tile->z) {
            continue;
        }
        if (TileRequests_DropBagAt(rock, town, &at)) {
            return;
        }
    }
}
CLEAN_AS(func_02042d94, TileRequests_DropBag)

/* func_02042e10: the rock on `tile` hit: the first hit notes the tile and starts the timer
 * (150 frames and up to 59 more: the byte RoomScore_HouseLowX gives, times 960 / 4096), each
 * hit counts (8 at most) and drops a bag. */
void TileRequests_HitRock(TileRequestsRock *rock, const TileRequestTile *tile)
{
    if (rock->timer < 0) {
        rock->x = (u8) tile->x;
        rock->z = (u8) tile->z;
        rock->timer = (s16) (((int) RoomScore_HouseLowX() * 960 >> 12) + TILE_REQUESTS_ROCK_TIME);
    }
    rock->hits++;
    if (rock->hits >= TILE_REQUESTS_ROCK_HITS) {
        rock->hits = TILE_REQUESTS_ROCK_HITS;
    }
    TileRequestTile at = *tile;
    TileRequests_DropBag(rock, &at);
}
CLEAN_AS(func_02042e10, TileRequests_HitRock)

/* func_02042e64: the rock's timer counted down, when not linked; when it has run out and no one
 * stands on the rock, its code 0xe8 + n becomes 0xe3 + n % 5 (0xe3 when the town or the
 * code is missing) and the timer stops.
 * QUIRK: a code below 0xe8 gives a remainder below 0, and a code below 0xe3. */
void TileRequests_RockUpdate(TileRequestsRock *rock)
{
    if (Session_IsLinked(data_020ccf94)) {
        return;
    }
    if (rock->timer > 0) {
        rock->timer--;
    }
    if (rock->timer != 0) {
        return;
    }
    TileRequestTile tile = {rock->x, rock->z};
    if (func_02045cec(&tile, 0) >= 0) {
        return;
    }
    int code = TILE_REQUESTS_ROCK;
    AcreMap *town = (AcreMap *) (uintptr_t) AcreMap_Town();
    rock->timer = -1;
    if (town != NULL) {
        u16 *on_map = TileRequests_CodeAt(town, tile.x, tile.z, 0);
        if (on_map != NULL) {
            code = (u16) ((*on_map - TILE_REQUESTS_MONEY_ROCK) % TILE_REQUESTS_ROCKS + TILE_REQUESTS_ROCK);
        }
    }
    func_0204a330(rock->x, rock->z, code, 0);
}
CLEAN_AS(func_02042e64, TileRequests_RockUpdate)

/* func_02042efc: no hit yet, no timer. */
void TileRequests_RockInit(TileRequestsRock *rock)
{
    rock->hits = 0;
    rock->timer = -1;
}
CLEAN_AS(func_02042efc, TileRequests_RockInit)

/* func_02042f08 */
void TileRequests_RockReset(TileRequestsRock *rock)
{
    TileRequests_RockInit(rock);
}
CLEAN_AS(func_02042f08, TileRequests_RockReset)

/* ---- The request slots */

/* func_02042f10: slot `index` freed. */
void TileRequests_Clear(TileRequest *requests, int index)
{
    requests[index].state = TILE_REQUEST_FREE;
    requests[index].kind = 0;
}
CLEAN_AS(func_02042f10, TileRequests_Clear)

/* func_02042f20: a request put in the first free slot of three and handed to func_02045770;
 * the slot, or -1 when none is free. The kinds 3, 9 and 0x15 become the next kind when the
 * pockets have no room: for the bottle (0x1520) no place for a letter, else no free slot. */
int TileRequests_Add(TileRequest *requests, int player, int kind, const TileRequestTile *tile, u16 item, u16 tile_item,
                     u8 unk_1d, u8 layer, int unk_20, s8 unk_1e)
{
    for (int i = 0; i < TILE_REQUESTS_SLOTS; i++) {
        TileRequest *request = &requests[i];
        if (request->state != TILE_REQUEST_FREE || request->kind != 0) {
            continue;
        }
        if (kind == TILE_REQUEST_TAKE || kind == TILE_REQUEST_KIND_9 || kind == TILE_REQUEST_KIND_15) {
            if (tile_item == TILE_REQUESTS_BOTTLE) {
                if (CurrentPockets_FreeLetter() == NULL) {
                    kind++;
                }
            } else if (CurrentPockets_FreeSlot() < 0) {
                kind++;
            }
        }
        request->player = player;
        request->holder = LinkGlobal_SceneHolder(SceneQuery_Current());
        request->state = TILE_REQUEST_ASKED;
        request->kind = kind;
        request->item = item;
        request->tile_item = tile_item;
        request->tile = *tile;
        request->layer = layer;
        request->unk_1d = unk_1d;
        request->unk_20 = unk_20;
        request->unk_1e = unk_1e;
        func_02045770((u8) i, unk_20);
        return i;
    }
    return TILE_REQUESTS_NONE;
}
CLEAN_AS(func_02042f20, TileRequests_Add)

/* func_02042fc4: slot `index`. */
TileRequest *TileRequests_At(int index)
{
    return &data_021c7c48.requests[index];
}
CLEAN_AS(func_02042fc4, TileRequests_At)

/* func_02042fd4: the tile under a position (where an actor was just made) emptied by
 * func_0204811c when it holds 0xfc or 0xfd and no one stands there. */
void TileRequests_ClearSpawnTile(const Vec3 *position)
{
    Vec3 copy = *position;
    func_0204811c(data_021c779c, &copy);
}
CLEAN_AS(func_02042fd4, TileRequests_ClearSpawnTile)

/* func_02042ff8: on the five tiles of a cross around `tile` where no one stands, each code that
 * func_020475b0 changes (0x86 the other way when `player` holds item 0x1379) takes its new code
 * (func_0205f9d4). When one did, or a tile holds a code of families A-C (map_item.h, with 0x1c
 * and 0xa5), 0x1a, 0x1d, 0x1e, 0x88 or 0xa4, and this system is not linked, the
 * villagers hear of it at the tile (VillagerEvent_Report5). */
void TileRequests_ChangeCodesAround(int player, const TileRequestTile *tile)
{
    AcreMap *town = (AcreMap *) (uintptr_t) AcreMap_Town();
    TileRequestsActor *self = func_020961a8(TILE_REQUESTS_PLAYER_ACTOR);
    if (town == NULL || self == NULL) {
        return;
    }
    int holds_1379 = func_02044808(player) == TILE_REQUESTS_ITEM_1379;
    int found = 0;
    for (int i = 0; i < 5; i++) {
        int x = tile->x + data_020ca584[i];
        int z = tile->z + data_020ca58c[i];
        TileRequestTile at = {x, z};
        if (func_02045cec(&at, 0) >= 0) {
            continue;
        }
        u16 *code = TileRequests_CodeAt(town, x, z, 0);
        if (code == NULL) {
            continue;
        }
        u16 changed = func_020475b0(data_021c779c, code, holds_1379);
        if (changed != ITEM_CODE_NONE) {
            found = 1;
            func_0205f9d4((u8) x, (u8) z, SceneQuery_Current(), changed, 0);
        }
        u32 now = *code;
        if (TileRequests_IsFamilyA(now) || TileRequests_IsFamilyC(now) || TileRequests_IsFamilyB(now) || now == 0x1a ||
            now == 0x88 || now == 0xa4 || now == 0x1d || now == 0x1e) {
            found = 1;
        }
    }
    if (found && !Session_IsLinked(data_020ccf94)) {
        Vec3 centre;
        AcreTile_TileCentre(&centre, (u32) tile->x, (u32) tile->z);
        VillagerEvent_Report5(&centre);
    }
}
CLEAN_AS(func_02042ff8, TileRequests_ChangeCodesAround)

/* func_020431b8: slot `index` of data_021c7c48 freed. */
void TileRequests_Release(int index)
{
    TileRequests_Clear(data_021c7c48.requests, index);
}
CLEAN_AS(func_020431b8, TileRequests_Release)

/* func_020431c8: a granted request carried out by the overlays, given the position of this
 * system's player: 1 when that worked, 0 when not (or not granted yet), 2 when refused.
 * Outdoors, a code of families A and C, 0x1a, 0x1d, 0x1e, 0xa4 or 0xa7-0xc6 goes
 * to func_ov003_02221118, other items to func_ov003_02221304; in a room,
 * func_ov004_022335b8. */
int TileRequests_Carry(int index)
{
    TileRequest *request = &data_021c7c48.requests[index];
    if (data_021c80bc == NULL) {
        return 0;
    }
    switch (request->state) {
        case TILE_REQUEST_GRANTED: {
            TileRequestsActor *self = func_020961a8(TILE_REQUESTS_PLAYER_ACTOR);
            if (self == NULL) {
                return 0;
            }
            TileRequestTile tile = request->tile;
            Vec3 position;
            if (data_020e54a8 != 0) {
                position = self->position;
                return func_ov004_022335b8(request->player, request->item, &tile, &position, request->layer) != 0;
            }
            u32 item = request->item;
            if (TileRequests_IsFamilyA(item) || TileRequests_IsFamilyC(item) || item == 0x1a || item == 0xa4 || item == 0x1d ||
                TileRequests_InRange(item, 0xa7, 0xc6) || item == 0x1e) {
                return func_ov003_02221118(request->player, request->item, &tile) != 0;
            }
            position = self->position;
            return func_ov003_02221304(request->player, request->item, &tile, &position) != 0;
        }
        case TILE_REQUEST_REFUSED:
            return 2;
        default:
            return 0;
    }
}
CLEAN_AS(func_020431c8, TileRequests_Carry)

/* func_02043368: a tile to put something of `kind` on, near the player of this system: from
 * the player's tile (written to `tile` first), the nine tiles data_020cb638 gives for the
 * player's facing, the first that is empty and allowed (TileRequests_DropTileFor), has no one
 * on it (func_02045d80) and passes func_02045ac4 for the local player; out of the town also
 * the first free top of a room's tile. The tile goes to `tile` and its place (0 the map, 1 a
 * room's top) to `place` when one is given; whether one was found. */
int TileRequests_FindDropTile(int kind, TileRequestTile *tile, u8 *place)
{
    AcreMap *map = data_021c80bc;
    TileRequestsActor *self = func_020961a8(TILE_REQUESTS_PLAYER_ACTOR);
    if (map == NULL || self == NULL) {
        return 0;
    }
    const int *order = data_020cb638[func_020644e4(self->facing)];
    Position_Tile(&tile->x, &tile->z, (const Position *) &self->position);
    NetSession *session = data_020ccf94;
    for (int i = 0; i < 9; i++) {
        u8 offset = data_020ca634[order[i]];
        int x = tile->x + ((offset >> 4) - 8);
        int z = tile->z + ((offset & 0xf) - 8);
        TileRequestTile from = *tile;
        u16 *code = TileRequests_DropTileFor(kind, map, x, z, &from);
        if (code != NULL && *code == ITEM_CODE_NONE) {
            TileRequestTile at = {x, z};
            if (func_02045d80(&at, 0) < 0 && func_02045ac4(&at, session->local_player)) {
                tile->x = x;
                tile->z = z;
                if (place != NULL) {
                    *place = 0;
                }
                return 1;
            }
        }
        if (!SceneQuery_CurrentIs0() && RoomSync_IsFreeTopAt(x, z)) {
            tile->x = x;
            tile->z = z;
            if (place != NULL) {
                *place = 1;
            }
            return 1;
        }
    }
    return 0;
}
CLEAN_AS(func_02043368, TileRequests_FindDropTile)

/* func_02043484: the code of the tile (x, z) when it is empty and something of `kind` may go
 * there, else NULL: kinds 0x10-0x12 when func_020317c4 allows it from `from`, 0x1a when it
 * allows it with its flag, 0x18 on a tile whose AcreTile_UnitWord06 is 0 or 1. */
u16 *TileRequests_DropTileFor(int kind, AcreMap *map, int x, int z, const TileRequestTile *from)
{
    u16 *code = TileRequests_CodeAt(map, x, z, 0);
    if (code == NULL) {
        return NULL;
    }
    if (*code != ITEM_CODE_NONE) {
        return NULL;
    }
    switch (kind) {
        case TILE_REQUEST_DROP:
        case TILE_REQUEST_ACTOR_TILE:
        case TILE_REQUEST_DROP_12:
            if (func_020317c4(from->x, from->z, x, z, 0) == 0) {
                return NULL;
            }
            break;
        case TILE_REQUEST_SPLIT_DROP: {
            int unit = AcreTile_UnitWord06(map, x, z);
            if (unit != 0 && unit != 1) {
                return NULL;
            }
            break;
        }
        case TILE_REQUEST_DROP_A7:
            if (func_020317c4(from->x, from->z, x, z, 1) == 0) {
                return NULL;
            }
            break;
        default:
            break;
    }
    return code;
}
CLEAN_AS(func_02043484, TileRequests_DropTileFor)

/* func_02043540: TileRequests_AskAtActorTile for `player`'s slot. */
int TileRequests_AskAtActorTileFor(int player, int item)
{
    return TileRequests_AskAtActorTile(func_02044858(player), item);
}
CLEAN_AS(func_02043540, TileRequests_AskAtActorTileFor)

/* func_02043554: TileRequests_AskDrop for `player`'s slot. */
int TileRequests_AskDropFor(int player, int item)
{
    return TileRequests_AskDrop(func_02044858(player), (u16) item);
}
CLEAN_AS(func_02043554, TileRequests_AskDropFor)

/* func_02043568: `item` put down by `slot` as kind 0x12 when its actor has a tile record, else
 * 0x10; -1 when the slot may not ask. */
int TileRequests_AskDrop12(int slot, int item)
{
    if (func_0204482c(slot) == 0) {
        return TILE_REQUESTS_NONE;
    }
    int kind = func_02045b5c(slot) != NULL ? TILE_REQUEST_DROP_12 : TILE_REQUEST_DROP;
    return TileRequests_AskPut(slot, kind, (u16) item);
}
CLEAN_AS(func_02043568, TileRequests_AskDrop12)

/* func_020435a0: a request of kind 0x11 for `item` at the tile of `slot`'s actor record; -1 when
 * the slot may not ask or has no record. */
int TileRequests_AskAtActorTile(int slot, int item)
{
    if (func_0204482c(slot) == 0) {
        return TILE_REQUESTS_NONE;
    }
    u16 *record = func_02045b5c(slot);
    if (record == NULL) {
        return TILE_REQUESTS_NONE;
    }
    TileRequestTile tile = TileRequests_TileOf(*record);
    return TileRequests_Add(data_021c7c48.requests, slot, TILE_REQUEST_ACTOR_TILE, &tile, (u16) item, (u16) item, 0, 0, 0, -1);
}
CLEAN_AS(func_020435a0, TileRequests_AskAtActorTile)

/* func_020435fc: `item` put down: kind 0x1a for 0xa7-0xc6, else 0x10. */
int TileRequests_AskDrop(int slot, u16 item)
{
    int kind = TileRequests_InRange(item, 0xa7, 0xc6) ? TILE_REQUEST_DROP_A7 : TILE_REQUEST_DROP;
    return TileRequests_AskPut(slot, kind, item);
}
CLEAN_AS(func_020435fc, TileRequests_AskDrop)

/* func_02043634: a request of `kind` for `item` on a tile found near the player
 * (TileRequests_FindDropTile); kind 0x18 splits the item in two codes (func_020445c0). -1 when
 * no tile or no slot was found. */
int TileRequests_AskPut(int slot, int kind, u16 item)
{
    TileRequestTile tile = {0, 0};
    u8 place;
    u16 first;
    u16 second;
    if (!TileRequests_FindDropTile(kind, &tile, &place)) {
        return TILE_REQUESTS_NONE;
    }
    if (kind == TILE_REQUEST_SPLIT_DROP) {
        func_020445c0(&first, &second, item);
    } else {
        first = item;
        second = item;
    }
    TileRequestTile at = tile;
    return TileRequests_Add(data_021c7c48.requests, slot, kind, &at, first, second, 0, place, 0, -1);
}
CLEAN_AS(func_02043634, TileRequests_AskPut)

/* func_020436a8: what came of a request: 2 when the slot is free, or (while linked) another
 * system's; 0 while there is no map or tile, or no answer yet; 1 when it was done, 2 when it was
 * refused. A granted request of kind 0x13 (unless its item is 0xfff1) is shown by
 * func_ov003_02220e20 (a code of the growth lines 0x2f-0x56 at stage 0 as the item of data_020ca664 for its line,
 * 0xc8 as 0x1548); 3 and 0x15 give 2 and func_02045f08 when the tile is empty, else 1; 0x18
 * and 0x1a are shown by func_ov003_02221118 when not linked. */
int TileRequests_Answer(u32 index)
{
    AcreMap *map = data_021c80bc;
    TileRequest *request = &data_021c7c48.requests[index];
    NetSession *session = data_020ccf94;
    if (request->state == TILE_REQUEST_FREE || request->kind == 0 ||
        (Session_IsLinked(session) && request->player != session->local_slot)) {
        return 2;
    }
    if (map == NULL) {
        return 0;
    }
    u16 *code = TileRequests_CodeAt(map, request->tile.x, request->tile.z, 0);
    if (code == NULL) {
        return 0;
    }
    switch (request->state) {
        case TILE_REQUEST_GRANTED:
            switch (request->kind) {
                case TILE_REQUEST_KIND_13:
                    if (request->item != ITEM_CODE_NONE) {
                        TileRequestsActor *self = func_020961a8(TILE_REQUESTS_PLAYER_ACTOR);
                        if (self != NULL) {
                            int shown = request->tile_item;
                            u16 item = request->item;
                            if (MapItem_IsStage0(&item)) {
                                if (TileRequests_InRange(item, 0x2f, 0x56)) {
                                    shown = data_020ca664[MapItem_EightLine(&item)];
                                } else if (request->item == 0xc8) {
                                    shown = 0x1548;
                                }
                            }
                            Vec3 position = self->position;
                            TileRequestTile tile = request->tile;
                            func_ov003_02220e20(request->player, shown, &tile, &position);
                        }
                    }
                    return 1;
                case TILE_REQUEST_TAKE:
                case TILE_REQUEST_KIND_15:
                    if (*code == ITEM_CODE_NONE) {
                        TileRequestTile tile = request->tile;
                        func_02045f08(&tile, request->layer);
                        return 2;
                    }
                    return 1;
                case TILE_REQUEST_SPLIT_DROP:
                case TILE_REQUEST_DROP_A7:
                    if (!Session_IsLinked(session)) {
                        TileRequestTile tile = request->tile;
                        func_ov003_02221118(request->player, request->item, &tile);
                    }
                    return 1;
                default:
                    return 1;
            }
        case TILE_REQUEST_REFUSED:
            return 2;
        default:
            return 0;
    }
}
CLEAN_AS(func_020436a8, TileRequests_Answer)

/* A request of kind 0x19 for the tile of the town holding item 0x1566 with AcreTile_IsMarked:
 * code 0xfd when AcreTile_UnitByte09 is set there, else 0xfc. Only in scene 0; -1 when not
 * made. `player` is asked for after AcreTile_IsMarked (func_02044858) when `for_player`. */
static int TileRequests_AskMarked(int player, int for_player, const TileRequestTile *tile, s8 unk_1e)
{
    if (SceneQuery_CurrentIs0() == 0) {
        return TILE_REQUESTS_NONE;
    }
    AcreMap *town = (AcreMap *) (uintptr_t) AcreMap_Town();
    if (town == NULL) {
        return TILE_REQUESTS_NONE;
    }
    u16 *code = TileRequests_CodeAt(town, tile->x, tile->z, 0);
    if (code == NULL || *code != TILE_REQUESTS_MARKED_ITEM) {
        return TILE_REQUESTS_NONE;
    }
    if (AcreTile_IsMarked(town, tile->x, tile->z) == 0) {
        return TILE_REQUESTS_NONE;
    }
    int slot = for_player ? func_02044858(player) : 0;
    u16 made = AcreTile_UnitByte09(town, tile->x, tile->z) != 0 ? 0xfd : 0xfc;
    TileRequestTile at = *tile;
    return TileRequests_Add(data_021c7c48.requests, slot, TILE_REQUEST_MARKED_1566, &at, made, ITEM_CODE_NONE, 0, 0, 0,
                            unk_1e);
}

/* func_02043830: TileRequests_AskMarked for slot 0, `unk_1e` kept in the request. */
int TileRequests_AskMarked1566(int unk_1e, const TileRequestTile *tile)
{
    return TileRequests_AskMarked(0, 0, tile, (s8) unk_1e);
}
CLEAN_AS(func_02043830, TileRequests_AskMarked1566)

/* func_020438dc: TileRequests_AskMarked for `player`'s slot. */
int TileRequests_AskMarked1566For(int player, const TileRequestTile *tile, int unused)
{
    (void) unused;
    return TileRequests_AskMarked(player, 1, tile, -1);
}
CLEAN_AS(func_020438dc, TileRequests_AskMarked1566For)

/* func_02043990: TileRequests_AskFcFd for `player`'s slot. */
int TileRequests_AskFcFdFor(u32 player, const TileRequestTile *tile, u32 mode)
{
    int slot = func_02044858((int) player);
    TileRequestTile at = *tile;
    return TileRequests_AskFcFd(slot, &at, (int) mode);
}
CLEAN_AS(func_02043990, TileRequests_AskFcFdFor)

/* func_020439b4: a request of kind 0x14 for a tile of code 0xfc or 0xfd, unless `mode` is 2;
 * -1 when not made. */
int TileRequests_AskFcFd(int slot, const TileRequestTile *tile, int mode)
{
    AcreMap *map = data_021c80bc;
    if (map == NULL) {
        return TILE_REQUESTS_NONE;
    }
    u16 *code = TileRequests_CodeAt(map, tile->x, tile->z, 0);
    if (code == NULL) {
        return TILE_REQUESTS_NONE;
    }
    if (!TileRequests_InRange(*code, 0xfc, 0xfd) || mode == 2) {
        return TILE_REQUESTS_NONE;
    }
    TileRequestTile at = *tile;
    return TileRequests_Add(data_021c7c48.requests, slot, TILE_REQUEST_FC_FD, &at, ITEM_CODE_NONE, ITEM_CODE_NONE, 1, 0, 0,
                            -1);
}
CLEAN_AS(func_020439b4, TileRequests_AskFcFd)

/* func_02043a4c: TileRequests_AskForTool0 for `player`'s slot. */
int TileRequests_AskForTool0For(int player, const TileRequestTile *tile, int unused)
{
    int slot = func_02044858(player);
    TileRequestTile at = *tile;
    return TileRequests_AskForTool0(slot, &at, unused);
}
CLEAN_AS(func_02043a4c, TileRequests_AskForTool0For)

/* func_02043a70: a request to take a pile (an item of kind 1) from the tile: the code of layer
 * 0, else of layer 1; -1 when there is none. */
int TileRequests_AskPile(int slot, const TileRequestTile *tile)
{
    AcreMap *map = data_021c80bc;
    if (map == NULL) {
        return TILE_REQUESTS_NONE;
    }
    u16 *code = TileRequests_CodeAt(map, tile->x, tile->z, 0);
    if (code == NULL) {
        return TILE_REQUESTS_NONE;
    }
    u16 pile;
    u8 layer;
    if ((*code & 0xf000) >> 12 == 1) {
        pile = *code;
        layer = 0;
    } else {
        u16 *second = TileRequests_CodeAt(map, tile->x, tile->z, 1);
        if (second == NULL || (*second & 0xf000) >> 12 != 1) {
            return TILE_REQUESTS_NONE;
        }
        pile = *second;
        layer = 1;
    }
    TileRequestTile at = *tile;
    return TileRequests_Add(data_021c7c48.requests, slot, TILE_REQUEST_TAKE, &at, ITEM_CODE_NONE, pile, 0, layer, 0, -1);
}
CLEAN_AS(func_02043a70, TileRequests_AskPile)

/* func_02043b40: in the town, what the tile holds decides the request: kind 5 for 0x1f,
 * 0x21-0x24, the codes of families B and C, 0x88 and 0xa4; kind 3 (take it) for a pile or an
 * item of kinds 3 and 4 not on a marked tile (AcreTile_IsMarked), a code of family A, 0x1a,
 * 0x1d, 0x1e and 0xa7-0xc6; kind 0x15 for 0x20. The tile's code goes with it; -1 when none is
 * made (an empty tile, a marked pile). */
int TileRequests_AskInTown(int slot, const TileRequestTile *tile)
{
    AcreMap *map = data_021c80bc;
    if (map == NULL) {
        return TILE_REQUESTS_NONE;
    }
    u16 *on_map = TileRequests_CodeAt(map, tile->x, tile->z, 0);
    if (on_map == NULL) {
        return TILE_REQUESTS_NONE;
    }
    u32 code = *on_map;
    int high = (int) (code & 0xf000) >> 12;
    int kind = 0;
    if (code == ITEM_CODE_NONE) {
        kind = 0;
    } else if (TileRequests_InRange(code, 0x21, 0x24) || code == 0x1f) {
        kind = TILE_REQUEST_KIND_5;
    } else if (high == 1) {
        if (AcreTile_IsMarked(map, tile->x, tile->z) == 0) {
            kind = TILE_REQUEST_TAKE;
        }
    } else if (TileRequests_IsFamilyA(code) || code == 0x1a || code == 0x1d || code == 0x1e) {
        kind = TILE_REQUEST_TAKE;
    } else if ((high == 3 || high == 4) && AcreTile_IsMarked(map, tile->x, tile->z) == 0) {
        kind = TILE_REQUEST_TAKE;
    } else if (TileRequests_InRange(code, 0xa7, 0xc6)) {
        kind = TILE_REQUEST_TAKE;
    } else if (TileRequests_IsFamilyB(code) || TileRequests_IsFamilyC(code) || code == 0x88 || code == 0xa4) {
        kind = TILE_REQUEST_KIND_5;
    } else if (code == 0x20) {
        kind = TILE_REQUEST_KIND_15;
    }
    if (kind == 0) {
        return TILE_REQUESTS_NONE;
    }
    TileRequestTile at = *tile;
    return TileRequests_Add(data_021c7c48.requests, slot, kind, &at, ITEM_CODE_NONE, (u16) code, 0, 0, 0, -1);
}
CLEAN_AS(func_02043b40, TileRequests_AskInTown)

/* func_02043cdc: in scene 0 (the town) TileRequests_AskInTown, else TileRequests_AskPile. */
int TileRequests_AskForTool0(int slot, const TileRequestTile *tile, int unused)
{
    (void) unused;
    TileRequestTile at = *tile;
    if (SceneQuery_CurrentIs0()) {
        return TileRequests_AskInTown(slot, &at);
    }
    return TileRequests_AskPile(slot, &at);
}
CLEAN_AS(func_02043cdc, TileRequests_AskForTool0)

/* func_02043d18: TileRequests_AskAtActorTileOp for `player`'s slot. */
int TileRequests_AskAtActorTileOpFor(int player, int operation, int arg, int item)
{
    return TileRequests_AskAtActorTileOp(func_02044858(player), operation, arg, item);
}
CLEAN_AS(func_02043d18, TileRequests_AskAtActorTileOpFor)

/* func_02043d34: func_02043db4's request at the tile of `slot`'s actor record; -1 when the slot
 * may not ask or has no record. */
int TileRequests_AskAtActorTileOp(int slot, int operation, int arg, int item)
{
    if (func_0204482c(slot) == 0) {
        return TILE_REQUESTS_NONE;
    }
    u16 *record = func_02045b5c(slot);
    if (record == NULL) {
        return TILE_REQUESTS_NONE;
    }
    TileRequestTile tile = TileRequests_TileOf(*record);
    return func_02043db4(slot, &tile, operation, arg, (u16) item);
}
CLEAN_AS(func_02043d34, TileRequests_AskAtActorTileOp)

/* func_02043d84: func_02043db4's request for `player`'s slot. */
int TileRequests_AskOpFor(int player, const TileRequestTile *tile, int operation, int arg, u16 item)
{
    int slot = func_02044858(player);
    TileRequestTile at = *tile;
    return func_02043db4(slot, &at, operation, arg, item);
}
CLEAN_AS(func_02043d84, TileRequests_AskOpFor)

/* ---- The operations on a tile (TileRequests_AskOp) */

#include "player_record.h"
#include "player_records.h"
#include "state_block.h"

extern StateBlock data_021dc7a8;
/* The hits a growth line code takes at each stage (from 1) before it becomes a short line code. */
extern const int data_020caaf8[];
/* The codes the items 0x1518-0x151c become. */
extern const u16 data_020ca64c[];

/* A code that is not taken out of the tile but stands for something else to take there. */
extern int func_0204a034(const u16 *code);
/* Whether the current player has not done it today, in the board's part of the state block;
 * func_0204cb2c notes it done. */
extern int func_0204cafc(void *part);
extern void func_0204cb2c(int part);
/* The bells a bag holds. */
extern int func_0204c878(void *bag);
/* A random number below `range`. */
extern int func_020644cc(int range);

#define TILE_REQUESTS_TOWN_DROP_BLOCK 0x1c /* data_021c779c's byte: no item may drop */
#define TILE_REQUESTS_BAG_SHOVEL 0x136a    /* the item to hold for a bag of bells to grow */
#define TILE_REQUESTS_BAG_FIRST 0x1492     /* the bags of bells */
#define TILE_REQUESTS_BAG_LAST 0x14fd
#define TILE_REQUESTS_BAG_CODE 0x26       /* the code a bag of bells becomes */
#define TILE_REQUESTS_BAG_GROWN_CODE 0x57 /* and when its chance came up */
#define TILE_REQUESTS_BAG_CHANCE_MAX 100

/* The codes of the growth lines and 0x66-0x6d (MapItem_Grows). */
static int TileRequests_IsGrowthCode(u32 code)
{
    return TileRequests_InRange(code, 0x26, 0x2a) || TileRequests_InRange(code, 0x5d, 0x61) ||
           TileRequests_InRange(code, 0x2f, 0x56) || TileRequests_InRange(code, 0x57, 0x5b) ||
           TileRequests_InRange(code, 0x66, 0x6d) || TileRequests_InRange(code, 0xc8, 0xcf);
}

/* The codes of the four short lines. */
static int TileRequests_IsShortLineCode(u32 code)
{
    return TileRequests_InRange(code, 0x2b, 0x2e) || TileRequests_InRange(code, 0xff, 0x102) ||
           TileRequests_InRange(code, 0x62, 0x65) || TileRequests_InRange(code, 0xd0, 0xd3);
}

/* The bare code at `stage` (from 0) of a growth line code: on the line 0x27 for the lines
 * 0x26-0x2a and 0x57-0x5b and the codes 0x66-0x69, else on the line 0x5e. */
static u16 TileRequests_BareCode(u32 code, int stage)
{
    if (TileRequests_InRange(code, 0x26, 0x2a) || TileRequests_InRange(code, 0x57, 0x5b) ||
        TileRequests_InRange(code, 0x66, 0x69)) {
        return (u16) (stage + 0x27);
    }
    return (u16) (stage + 0x5e);
}

/* The money rock codes 0xe8-0xfb come five to each player's number. */
static int TileRequests_IsOwnMoneyRock(const u16 *code)
{
    return (*code - TILE_REQUESTS_MONEY_ROCK) / TILE_REQUESTS_ROCKS == PlayerRecords_CurrentNumber();
}

/* func_02043db4: a request for `operation` (TILE_REQUESTS_OP_*) on a tile of the town, from what
 * the tile holds; -1 when there is no town, no such tile or nothing to ask. `item` is what is
 * put in a hole (TileRequests_AskHole). */
int TileRequests_AskOp(int slot, const TileRequestTile *tile, int operation, int arg, u16 item)
{
    AcreMap *town = (AcreMap *) (uintptr_t) AcreMap_Town();
    if (town == NULL) {
        return TILE_REQUESTS_NONE;
    }
    u16 *code = TileRequests_CodeAt(town, tile->x, tile->z, 0);
    if (code == NULL) {
        return TILE_REQUESTS_NONE;
    }
    TileRequestTile at = *tile;
    switch (operation) {
        case TILE_REQUESTS_OP_STRIP:
            return TileRequests_AskStrip(slot, code, &at, arg);
        case TILE_REQUESTS_OP_HIT:
            return TileRequests_AskHit(slot, code, &at, arg);
        case TILE_REQUESTS_OP_HOLE:
            return TileRequests_AskHole(slot, town, code, &at, item, arg);
        case TILE_REQUESTS_OP_AROUND:
            return TileRequests_AskAround(slot, code, &at, arg);
        default:
            return TILE_REQUESTS_NONE;
    }
}
CLEAN_AS(func_02043db4, TileRequests_AskOp)

/* func_02043e88: a request of kind 0xf (the codes around the tile changed) with the tile's
 * code; -1 when the slot may not ask. */
int TileRequests_AskAround(int slot, const u16 *code, const TileRequestTile *tile, int arg)
{
    if (TileRequests_MayAsk(slot) == 0) {
        return TILE_REQUESTS_NONE;
    }
    u16 now = *code;
    TileRequestTile at = *tile;
    return TileRequests_Add(data_021c7c48.requests, slot, TILE_REQUEST_CHANGE_AROUND, &at, now, now, 0, 0, arg, -1);
}
CLEAN_AS(func_02043e88, TileRequests_AskAround)

/* func_02043ed8: what the tile's code calls for with operation 2. The request's item is the
 * hole the tile would get (0xfd when AcreTile_UnitByte09 is set there, else 0xfc) unless said
 * otherwise, its second code the tile's code:
 *
 *   - an empty tile: kind 8 when AcreTile_UnitByte09 (asked again) gives 0 or 1, kind 0xc for
 *     2 and 0x17 for 3, both with the empty code as the item; 0x17 for other values;
 *   - the rocks 0xe3-0xe7: kind 0xd; the money rocks 0xe8-0xfb: kind 0xc, 0xe for the current
 *     player's rock when not linked; both with the code as the item;
 *   - a hole: kind 0x13 for `item` put in it (TileRequests_HoleCodes gives the codes it becomes
 *     unless it is 0xfff1);
 *   - a short line code, 0x25, 0x5c, 0xc7 or a growth line code at stage 0: kind 0xb;
 *   - what func_0204a034 accepts, 0x1b and 0x89: kind 0xc with the code as the item;
 *   - a code of the families (MapItem_InFamilies), 0x1f-0x24 and 0xe2: kind 8;
 *   - on a marked tile (AcreTile_IsMarked) or for 0xd4-0xe1: kind 9, the second code the
 *     code + 0x1467 for 0xd4-0xda, else + 0x1460;
 *   - an item of kinds 1, 3 and 4: kind 0xc with the code as the item; else kind 0x17. */
int TileRequests_AskHole(int slot, AcreMap *town, const u16 *code, const TileRequestTile *tile, u16 item, int arg)
{
    u16 ask_item = AcreTile_UnitByte09(town, tile->x, tile->z) != 0 ? 0xfd : 0xfc;
    u16 ask_code = *code;
    u8 unchanged = 0;
    int kind = 0x17;
    u32 now = *code;

    if (now == ITEM_CODE_NONE) {
        switch (AcreTile_UnitByte09(town, tile->x, tile->z)) {
            case 0:
            case 1:
                kind = 8;
                break;
            case 2:
                kind = 0xc;
                ask_item = (u16) now;
                break;
            case 3:
                kind = 0x17;
                ask_item = (u16) now;
                break;
            default:
                break;
        }
    } else if (TileRequests_InRange(now, TILE_REQUESTS_ROCK, TILE_REQUESTS_MONEY_ROCK - 1)) {
        kind = 0xd;
        ask_item = (u16) now;
    } else if (TileRequests_InRange(now, TILE_REQUESTS_MONEY_ROCK, 0xfb)) {
        kind = 0xc;
        ask_item = (u16) now;
        if (!Session_IsLinked(data_020ccf94) && TileRequests_IsOwnMoneyRock(code)) {
            kind = 0xe;
        }
    } else if (TileRequests_InRange(now, 0xfc, 0xfd)) {
        ask_item = item;
        ask_code = item;
        kind = TILE_REQUEST_KIND_13;
        if (item != ITEM_CODE_NONE) {
            TileRequests_HoleCodes(slot, &ask_item, &ask_code, &unchanged, item);
        }
    } else if (TileRequests_IsShortLineCode(now)) {
        kind = 0xb;
    } else if (func_0204a034(code) != 0 || now == 0x1b || now == 0x89) {
        kind = 0xc;
        ask_item = (u16) now;
    } else if (now == 0x25 || now == 0x5c || now == 0xc7 || (TileRequests_IsGrowthCode(now) && MapItem_IsStage0(code))) {
        kind = 0xb;
    } else if (MapItem_InFamilies(code) || TileRequests_InRange(now, 0x21, 0x24) || TileRequests_InRange(now, 0x1f, 0x20) ||
               now == 0xe2) {
        kind = 8;
    } else if (AcreTile_IsMarked(town, tile->x, tile->z) != 0 || TileRequests_InRange(now, 0xd4, 0xe1)) {
        kind = TILE_REQUEST_KIND_9;
        ask_code = (u16) (now + (TileRequests_InRange(now, 0xd4, 0xda) ? 0x1467 : 0x1460));
    } else {
        int high = (int) (now & 0xf000) >> 12;
        if (high == 1 || high == 3 || high == 4) {
            kind = 0xc;
            ask_item = (u16) now;
        }
    }
    TileRequestTile at = *tile;
    return TileRequests_Add(data_021c7c48.requests, slot, kind, &at, ask_item, ask_code, unchanged, 0, arg, -1);
}
CLEAN_AS(func_02043ed8, TileRequests_AskHole)

/* func_02044168: what the tile's code calls for with operation 1, the tile's code going with
 * the request:
 *
 *   - a growth line code past stage 0: kind 6, its mark (the hits so far) kept in the request.
 *     Unless `arg` is 2, the item is the code it becomes: with as many hits as data_020caaf8
 *     gives for its stage, the code of its stage (less one) on the short line 0xd0 (for
 *     0xc8-0xcf), 0x62 (0x5d-0x61, 0x6d), 0xff (0x2f-0x56) or else 0x2b; with fewer, its bare
 *     code, except that 0x67 and 0x6b give kind 7 when an item may drop (else stay), 0x2f-0x56
 *     and 0xc8-0xcf go one code on when grown (else stay), and 0x6d stays;
 *   - the rocks 0xe3-0xe7: kind 0xd; the money rocks: kind 0xc, or 0xe for the current player's
 *     rock when not linked and `arg` is not 2;
 *   - 0x1b and 0x89: kind 0x17; an item of kinds 1, 3 and 4: kind 0xc.
 * The item is the tile's code where nothing else is said; -1 when there is nothing to ask. */
int TileRequests_AskHit(int slot, const u16 *code, const TileRequestTile *tile, int arg)
{
    int kind = 0;
    int hits = 0;
    u16 ask_item = *code;
    u32 now = *code;

    if (TileRequests_IsGrowthCode(now) && MapItem_IsStage0(code) == 0) {
        int stage = MapItem_GrowthStage(code) - 1;
        kind = 6;
        TileRequestTile at = *tile;
        hits = (u8) TileRequests_Mark(&data_021c7c48, &at);
        if (arg != 2) {
            now = *code;
            if (hits >= data_020caaf8[stage]) {
                if (TileRequests_InRange(now, 0xc8, 0xcf)) {
                    ask_item = (u16) (stage + 0xd0);
                } else if (TileRequests_InRange(now, 0x5d, 0x61) || now == 0x6d) {
                    ask_item = (u16) (stage + 0x62);
                } else if (TileRequests_InRange(now, 0x2f, 0x56)) {
                    ask_item = (u16) (stage + 0xff);
                } else {
                    ask_item = (u16) (stage + 0x2b);
                }
            } else {
                ask_item = TileRequests_BareCode(now, stage);
                if (now == 0x67 || now == 0x6b) {
                    if (TileRequests_ItemDropAllowed() != 0) {
                        kind = 7;
                    } else {
                        ask_item = *code;
                    }
                } else if (TileRequests_InRange(now, 0x2f, 0x56) || TileRequests_InRange(now, 0xc8, 0xcf)) {
                    ask_item = MapItem_IsGrown(code) ? (u16) (*code + 1) : *code;
                } else if (now == 0x6d) {
                    ask_item = (u16) now;
                }
            }
        }
    } else if (TileRequests_InRange(now, TILE_REQUESTS_ROCK, TILE_REQUESTS_MONEY_ROCK - 1)) {
        kind = 0xd;
    } else if (TileRequests_InRange(now, TILE_REQUESTS_MONEY_ROCK, 0xfb)) {
        kind = 0xc;
        if (!Session_IsLinked(data_020ccf94) && TileRequests_IsOwnMoneyRock(code) && arg != 2) {
            kind = 0xe;
        }
    } else {
        switch ((now & 0xf000) >> 12) {
            case 0:
                if (now == 0x1b || now == 0x89) {
                    kind = 0x17;
                }
                break;
            case 1:
            case 3:
            case 4:
                kind = 0xc;
                break;
            default:
                break;
        }
    }
    if (kind == 0) {
        return TILE_REQUESTS_NONE;
    }
    TileRequestTile at = *tile;
    return TileRequests_Add(data_021c7c48.requests, slot, kind, &at, ask_item, *code, (u8) hits, 0, arg, -1);
}
CLEAN_AS(func_02044168, TileRequests_AskHit)

/* func_02044390: with operation 0, a growth line code past stages 0 and 1 asks for kind 1, the
 * item being the code it becomes: its bare code, except that 0x67 and 0x6b give kind 2 when an
 * item may drop (else stay), 0x2f-0x56 and 0xc8-0xcf go one code on when grown (else stay),
 * 0x57-0x5b stay unless grown and 0x6d stays. The tile's code goes with it; -1 for other
 * codes. */
int TileRequests_AskStrip(int slot, const u16 *code, const TileRequestTile *tile, int arg)
{
    if (!TileRequests_IsGrowthCode(*code)) {
        return TILE_REQUESTS_NONE;
    }
    if (MapItem_IsStage0(code) != 0 || MapItem_IsStage1(code) != 0) {
        return TILE_REQUESTS_NONE;
    }
    int kind = 1;
    int stage = MapItem_GrowthStage(code) - 1;
    u32 now = *code;
    u16 ask_item = TileRequests_BareCode(now, stage);
    if (now == 0x67 || now == 0x6b) {
        if (TileRequests_ItemDropAllowed() != 0) {
            kind = 2;
        } else {
            ask_item = *code;
        }
    } else if (TileRequests_InRange(now, 0x2f, 0x56) || TileRequests_InRange(now, 0xc8, 0xcf)) {
        ask_item = MapItem_IsGrown(code) ? (u16) (*code + 1) : *code;
    } else if (TileRequests_InRange(now, 0x57, 0x5b)) {
        if (MapItem_IsGrown(code) == 0) {
            ask_item = *code;
        }
    } else if (now == 0x6d) {
        ask_item = (u16) now;
    }
    TileRequestTile at = *tile;
    return TileRequests_Add(data_021c7c48.requests, slot, kind, &at, ask_item, *code, 0, 0, arg, -1);
}
CLEAN_AS(func_02044390, TileRequests_AskStrip)

/* func_02044528: items may drop again (TileRequests_ItemDropAllowed). */
void TileRequests_AllowItemDrop(void)
{
    data_021c779c[TILE_REQUESTS_TOWN_DROP_BLOCK] = 0;
}
CLEAN_AS(func_02044528, TileRequests_AllowItemDrop)

/* func_02044534: no item may drop. */
void TileRequests_ForbidItemDrop(void)
{
    data_021c779c[TILE_REQUESTS_TOWN_DROP_BLOCK] = 1;
}
CLEAN_AS(func_02044534, TileRequests_ForbidItemDrop)

/* func_02044540: whether an item may drop from 0x67 and 0x6b: when this system's slot is not
 * taken (Session_IsSlotTaken), the current player's flag 1 is clear and none is forbidden. */
int TileRequests_ItemDropAllowed(void)
{
    NetSession *session = data_020ccf94;
    if (Session_IsSlotTaken(session, session->local_slot) != 0) {
        return 0;
    }
    if (PlayerRecord_TestFlag(PlayerRecords_Current(), 1) != 0) {
        return 0;
    }
    return data_021c779c[TILE_REQUESTS_TOWN_DROP_BLOCK] == 0;
}
CLEAN_AS(func_02044540, TileRequests_ItemDropAllowed)

/* func_0204457c: the codes `put` makes in a hole: `item` and `code` as TileRequests_SplitItem
 * gives them, `unchanged` then 0; else `item` is `put` itself and `unchanged` 1, unless (for a
 * slot that may ask) TileRequests_BagCodes makes a bag of bells grow. */
void TileRequests_HoleCodes(int slot, u16 *item, u16 *code, u8 *unchanged, u16 put)
{
    *item = put;
    *unchanged = 1;
    if (TileRequests_SplitItem(item, code, put) != 0) {
        *unchanged = 0;
        return;
    }
    if (TileRequests_MayAsk(slot) != 0) {
        TileRequests_BagCodes(item, unchanged, put);
    }
}
CLEAN_AS(func_0204457c, TileRequests_HoleCodes)

/* func_020445c0: the codes an item becomes when put down, written to `item` (and to
 * `tile_item` for some); whether `code` is such an item:
 *
 *   0x1408-0x1428 and 0x1471-0x1491: their number in the range; 0x137c: 0x1e;
 *   0x14fe-0x1517: their number, and 0x1408 + that number as the second;
 *   0x151d: 0x26 twice; 0x151e: 0x5d twice;
 *   a growth line code at stage 0: 0xc8 for 0xc8-0xcf, else 0x26;
 *   0x1518-0x151c: the code data_020ca64c gives; 0x1548: 0xc8; 0x1567: 0xd4 and 0x1408. */
int TileRequests_SplitItem(u16 *item, u16 *tile_item, u16 code)
{
    u16 copy = code;
    if (TileRequests_InRange(code, 0x1408, 0x1428)) {
        *item = (u16) (code - 0x1408);
    } else if (TileRequests_InRange(code, 0x1471, 0x1491)) {
        *item = (u16) (code - 0x1471);
    } else if (code == 0x137c) {
        *item = 0x1e;
    } else if (TileRequests_InRange(code, 0x14fe, 0x1517)) {
        *item = (u16) (code - 0x14fe);
        *tile_item = (u16) (code - 0x14fe + 0x1408);
    } else if (code == 0x151d) {
        *item = 0x26;
        *tile_item = 0x26;
    } else if (code == 0x151e) {
        *item = 0x5d;
        *tile_item = 0x5d;
    } else if (MapItem_IsStage0(&copy)) {
        *item = TileRequests_InRange(copy, 0xc8, 0xcf) ? 0xc8 : 0x26;
    } else if (TileRequests_InRange(copy, 0x1518, 0x151c)) {
        *item = data_020ca64c[copy - 0x1518];
    } else if (code == 0x1548) {
        *item = 0xc8;
    } else if (code == 0x1567) {
        *item = 0xd4;
        *tile_item = 0x1408;
    } else {
        return 0;
    }
    return 1;
}
CLEAN_AS(func_020445c0, TileRequests_SplitItem)

/* func_02044750: a bag of bells put in a hole while this system's player holds item 0x136a
 * becomes code 0x26 (`unchanged` 0). Once a day for the current player (func_0204cafc) it
 * becomes 0x57 instead, with a chance in 100 of the bag's bells / 1000 + the byte
 * RoomScore_HouseLowX gives / 25 (100 at most); that uses the day's turn up. */
void TileRequests_BagCodes(u16 *item, u8 *unchanged, u16 put)
{
    if (TileRequests_HeldItem(data_020ccf94->local_player) != TILE_REQUESTS_BAG_SHOVEL) {
        return;
    }
    u16 bag = put;
    if (!TileRequests_InRange(bag, TILE_REQUESTS_BAG_FIRST, TILE_REQUESTS_BAG_LAST)) {
        return;
    }
    *item = TILE_REQUESTS_BAG_CODE;
    *unchanged = 0;
    u8 *part = data_021dc7a8.part_17254;
    if (func_0204cafc(part) == 0) {
        return;
    }
    int chance = func_0204c878(&bag) / 1000;
    chance += (int) RoomScore_HouseLowX() / 25;
    if (chance > TILE_REQUESTS_BAG_CHANCE_MAX) {
        chance = TILE_REQUESTS_BAG_CHANCE_MAX;
    }
    if (func_020644cc(TILE_REQUESTS_BAG_CHANCE_MAX) < chance) {
        *item = TILE_REQUESTS_BAG_GROWN_CODE;
        func_0204cb2c((int) (uintptr_t) part);
    }
}
CLEAN_AS(func_02044750, TileRequests_BagCodes)

/* func_02044808: the item `player` holds (PlayerRecord_HeldItem), 0xfff1 for none. */
int TileRequests_HeldItem(int player)
{
    u8 *record = PlayerRecords_OfPlayer(player);
    if (record == NULL) {
        return ITEM_CODE_NONE;
    }
    u16 *held = PlayerRecord_HeldItem(record);
    if (held == NULL) {
        return ITEM_CODE_NONE;
    }
    return *held;
}
CLEAN_AS(func_02044808, TileRequests_HeldItem)

/* func_0204482c: whether `slot` may ask: always when not linked, else when it is this system's
 * (Session_IsLocalSlot). */
int TileRequests_MayAsk(int slot)
{
    NetSession *session = data_020ccf94;
    if (!Session_IsLinked(session)) {
        return 1;
    }
    return Session_IsLocalSlot(session, slot);
}
CLEAN_AS(func_0204482c, TileRequests_MayAsk)

/* func_02044858: the session slot of `player`: itself while linked, else 0. */
int TileRequests_SlotOf(int player)
{
    return Session_IsLinked(data_020ccf94) ? player : 0;
}
CLEAN_AS(func_02044858, TileRequests_SlotOf)

/* func_02044878: the player of `slot`: itself while linked, else this system's player. */
int TileRequests_PlayerOf(int slot)
{
    NetSession *session = data_020ccf94;
    if (Session_IsLinked(session)) {
        return slot;
    }
    return session->local_player;
}
CLEAN_AS(func_02044878, TileRequests_PlayerOf)
