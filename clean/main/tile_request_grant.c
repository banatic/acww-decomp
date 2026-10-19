/* How a tile request is granted or refused (tile_request_grant.h). */
#include "tile_request_grant.h"

#include "acre_tile.h"
#include "clean.h"
#include "link_global.h"
#include "player_actor_ops.h"
#include "map_item.h"
#include "scene_query.h"
#include "session.h"
#include "tile_changes.h"
#include "item_lists.h"
#include "ov003/growth_model.h"
#include "ov003/tile_event.h"
#include "session_players.h"
#include "town_tile_put.h"

static_assert(sizeof(TileRequestMessage) == 8, "TileRequestMessage");
static_assert(sizeof(TileRequestAnswer) == TILE_REQUEST_ANSWER_SIZE, "TileRequestAnswer");
static_assert(offsetof(TileRequestAnswer, extra_tiles) == offsetof(TileRequestsActionMessage, extra_tiles),
              "TileRequestAnswer.extra_tiles");
static_assert(offsetof(TileRequestAnswer, extra_item) == 0x0c, "TileRequestAnswer.extra_item");

extern TileRequests data_021c7c48;
extern AcreMap *data_021c80bc; /* the scene's map */
extern NetSession *data_020ccf94;
extern TileChanges data_021c7880;
extern TileChange data_021c7884[TILE_CHANGES_COUNT];

/* The neighbours of a tile, each a byte: x + 8 in the high four bits, z + 8 in the low. */
extern const u8 data_020ca640[9];
/* The neighbour (of data_020ca640) each drop starts from. */
extern const int data_020ca67c[];
/* For each drop, the eight neighbours of its first tile (of data_020ca640) to try in turn. */
extern const int data_020cb488[][8];
/* The item a grown code of each line of eight (MapItem_EightLine) drops. */
extern const u16 data_020ca670[];
/* The codes the items 0x1518-0x151c become. */
extern const u16 data_020ca658[];

extern fx32 FX_MulFunc(fx32 a, fx32 b);

#define TILE_REQUEST_GRANT_MESSAGE_ASK 0x31
#define TILE_REQUEST_GRANT_MESSAGE_ASK_KIND 6
#define TILE_REQUEST_GRANT_MESSAGE_ANSWER 0x32
#define TILE_REQUEST_GRANT_MESSAGE_ANSWER_KIND 4
#define TILE_REQUEST_GRANT_PLACE 4 /* func_02046024's place for the request's own tile */
#define TILE_REQUEST_GRANT_BAG 0x1492
#define TILE_REQUEST_GRANT_NEAR 0x1000 /* a squared distance below 1.0 */
#define TILE_REQUEST_GRANT_PLAYERS 4
#define TILE_REQUEST_GRANT_TRIES 8

static int TileRequestGrant_InRange(u32 code, u32 first, u32 last)
{
    return code >= first && code <= last;
}

/* An arithmetic shift right, as the ARM's. */
static int TileRequestGrant_ShiftRight(int value, int shift)
{
    return value >= 0 ? value >> shift : ~(~value >> shift);
}

/* The ARM's 32-bit sum and difference. */
static s32 TileRequestGrant_Add(s32 a, s32 b)
{
    return (s32) ((u32) a + (u32) b);
}

static s32 TileRequestGrant_Sub(s32 a, s32 b)
{
    return (s32) ((u32) a - (u32) b);
}

/* The code on the tile (x, z) of `map` (layer 0), or NULL. */
static u16 *TileRequestGrant_CodeAt(AcreMap *map, int x, int z)
{
    return AcreTile_ItemInAcre(map, (u32) TileRequestGrant_ShiftRight(x, 4), (u32) TileRequestGrant_ShiftRight(z, 4), x & 0xf,
                               z & 0xf, 0);
}

static TileRequestTile TileRequestGrant_TileOf(u16 packed)
{
    TileRequestTile tile = {packed >> 8, packed & 0xff};
    return tile;
}

/* The neighbour `neighbour` (of data_020ca640) of a packed tile. */
static TileRequestTile TileRequestGrant_Near(u16 packed, int neighbour)
{
    u8 offset = data_020ca640[neighbour];
    TileRequestTile tile = {(packed >> 8) + ((offset >> 4) - 8), (packed & 0xff) + ((offset & 0xf) - 8)};
    return tile;
}

/* Drop `index`'s tile noted in the answer, its high byte (x) written first as the original
 * does. */
static void TileRequestGrant_SetExtraTile(TileRequestAnswer *answer, int index, const TileRequestTile *tile)
{
    u8 *bytes = (u8 *) &answer->extra_tiles[index];
    bytes[1] = (u8) tile->x;
    bytes[0] = (u8) tile->z;
}

static int TileRequestGrant_AnswerKind(const TileRequestAnswer *answer)
{
    return answer->who >> 3;
}

static int TileRequestGrant_AnswerSlot(const TileRequestAnswer *answer)
{
    return (answer->who >> 1) & 3;
}

static int TileRequestGrant_AnswerLayer(const TileRequestAnswer *answer)
{
    return answer->what >> 7;
}

/* The kinds of request with nothing put on the map: 0xc, 0xd, 0xf (changes around) and 0x17. */
static int TileRequestGrant_PutsNothing(int kind)
{
    return kind == 0xc || kind == 0xd || kind == TILE_REQUEST_CHANGE_AROUND || kind == 0x17;
}

/* func_02044e28: an answer received (message 50, from a system in `scene`). This system's own
 * request is noted granted or refused, and carried out when granted. Another system's granted
 * request is carried out when it was asked in the current scene while other systems' actions
 * are taken in (TileChanges.active): with the asker's action noted too
 * (TileRequests_ReceiveAction) while this system's player's actor has flag 10, else its tiles
 * let go of afterwards; in another scene only its items are put on that scene's map. */
void TileRequestGrant_ReceiveAnswer(const TileRequestAnswer *answer, int scene)
{
    int granted = (answer->what & TILE_REQUEST_ANSWER_GRANTED) != 0;
    if (data_020ccf94->local_slot == TileRequestGrant_AnswerSlot(answer)) {
        TileRequest *request = &data_021c7c48.requests[answer->what & 3];
        if (!granted) {
            request->state = TILE_REQUEST_REFUSED;
        } else {
            request->state = TILE_REQUEST_GRANTED;
            TileRequestGrant_Apply(answer);
        }
        return;
    }
    if (!granted) {
        return;
    }
    if (scene == SceneQuery_Current() && data_021c7880.active != 0) {
        if (PlayerActorOps_TestFlag(10, 4)) {
            TileRequests_ReceiveAction((const TileRequestsActionMessage *) answer);
            TileRequestGrant_Apply(answer);
        } else {
            TileRequestGrant_Apply(answer);
            TileRequestGrant_LetGo(answer);
        }
    } else {
        TileRequestGrant_PutOnScene(answer, scene);
    }
}
CLEAN_AS(func_02044e28, TileRequestGrant_ReceiveAnswer)

/* func_02044ec4: the answer's item put on its tile of the map of `scene` (func_0204a2a4, the
 * flag from the answer's unk_1d), and the item dropped on each extra tile, unless the kind puts
 * nothing on the map.
 * QUIRK: the extra tiles are not checked for 0xffff (none) here. */
void TileRequestGrant_PutOnScene(const TileRequestAnswer *answer, int scene)
{
    if (TileRequestGrant_PutsNothing(TileRequestGrant_AnswerKind(answer))) {
        return;
    }
    TownTilePut_OnScene(scene, answer->tile >> 8, answer->tile & 0xff, answer->item, (answer->what >> 3) & 3);
    if ((answer->who & TILE_REQUEST_ANSWER_EXTRAS) == 0) {
        return;
    }
    u16 dropped = answer->extra_item;
    for (int i = 0; i < 3; i++) {
        TownTilePut_OnScene(scene, answer->extra_tiles[i] >> 8, answer->extra_tiles[i] & 0xff, dropped, 0);
    }
}
CLEAN_AS(func_02044ec4, TileRequestGrant_PutOnScene)

/* func_02044f3c: the answer's tile let go of (TileChanges_LetGoAt in its layer), and each
 * extra tile, unless the kind puts nothing on the map.
 * QUIRK: the tile's code is looked up on the scene's map and not used. */
void TileRequestGrant_LetGo(const TileRequestAnswer *answer)
{
    int x = answer->tile >> 8;
    int z = answer->tile & 0xff;
    if (TileRequestGrant_PutsNothing(TileRequestGrant_AnswerKind(answer))) {
        return;
    }
    AcreMap *map = data_021c80bc;
    if (map != NULL) {
        TileRequestGrant_CodeAt(map, x, z);
    }
    TileChangesTile tile = {x, z};
    TileChanges_LetGoAt(&tile, TileRequestGrant_AnswerLayer(answer));
    if ((answer->who & TILE_REQUEST_ANSWER_EXTRAS) == 0) {
        return;
    }
    for (int i = 0; i < 3; i++) {
        u16 extra = answer->extra_tiles[i];
        if (extra != TILE_CHANGES_NO_TILE) {
            TileChangesTile at = {extra >> 8, extra & 0xff};
            TileChanges_LetGoAt(&at, TileRequestGrant_AnswerLayer(answer));
        }
    }
}
CLEAN_AS(func_02044f3c, TileRequestGrant_LetGo)

/* func_02044fe8: a granted request carried out: kinds 0x18 and 0x1a shown by
 * func_ov003_02221118 first; the item put on the tile over its code (func_02045f24), and the
 * dropped item on each extra tile (their place the drop's number); nothing for the kinds that
 * put nothing on the map.
 * REQUIRES: with a scene's map, the tile is on it (the original reads its code through the
 * pointer it is given, NULL or not). */
void TileRequestGrant_Apply(const TileRequestAnswer *answer)
{
    int x = answer->tile >> 8;
    int z = answer->tile & 0xff;
    int kind = TileRequestGrant_AnswerKind(answer);
    if (TileRequestGrant_PutsNothing(kind)) {
        return;
    }
    if (kind == TILE_REQUEST_SPLIT_DROP || kind == TILE_REQUEST_DROP_A7) {
        TileRequestTile shown = {x, z};
        TileEvent_StartKind4(TileRequestGrant_AnswerSlot(answer), answer->item, (const TileChangesTile *) &shown);
    }
    u16 code = ITEM_CODE_NONE;
    AcreMap *map = data_021c80bc;
    if (map != NULL) {
        code = *TileRequestGrant_CodeAt(map, x, z);
    }
    TileRequestTile tile = {x, z};
    TileChanges_Replace(TileRequestGrant_AnswerSlot(answer), (const TileChangesTile *) &tile, answer->item, code, (u8) kind,
                        (answer->what >> 3) & 3, (answer->what >> 5) & 3, TILE_REQUEST_GRANT_PLACE,
                        (u8) TileRequestGrant_AnswerLayer(answer), -1);
    if ((answer->who & TILE_REQUEST_ANSWER_EXTRAS) == 0) {
        return;
    }
    u16 dropped = answer->extra_item;
    for (int i = 0; i < 3; i++) {
        u16 extra = answer->extra_tiles[i];
        if (extra != TILE_CHANGES_NO_TILE) {
            TileRequestTile at = TileRequestGrant_TileOf(extra);
            TileChanges_Replace(TileRequestGrant_AnswerSlot(answer), (const TileChangesTile *) &at, dropped, ITEM_CODE_NONE, 0,
                                0, 0, (u8) i, (u8) TileRequestGrant_AnswerLayer(answer), -1);
        }
    }
}
CLEAN_AS(func_02044fe8, TileRequestGrant_Apply)

/* func_0204510c: the holder's answer to a request from `slot`, sent to every system as message
 * 50. Granted, the request is carried out here: the item put on the tile (over its code, or
 * over nothing for kinds 0x18 and 0x1a, which func_ov003_02221118 also shows: for 0x1a only
 * when the asker is another system) and, for other kinds, what it drops (TileRequestGrant_Drops,
 * which makes the answer the long one). The asker's request slot, when the asker is this
 * system, notes the answer; else the asker's action is noted (TileRequests_ReceiveAction). */
void TileRequestGrant_Answer(const TileRequestMessage *request, int granted, int slot)
{
    TileRequestAnswer answer = {0};
    int size = TILE_REQUEST_ANSWER_SHORT;
    int kind = request->what & TILE_REQUEST_MESSAGE_KIND_MASK;
    answer.who = (u8) (((slot & 3) << 1) | (kind << 3));
    answer.what = (u8) (((request->who >> 2) & 3) | ((granted & 1) << 2) | (((request->who >> 4) & 3) << 3) |
                        (((request->what >> 5) & 3) << 5) | ((request->what >> 7) << 7));
    answer.tile = request->tile;
    answer.item = request->item;
    for (int i = 0; i < 3; i++) {
        answer.extra_tiles[i] = TILE_CHANGES_NO_TILE;
    }
    TileRequestTile tile = TileRequestGrant_TileOf(answer.tile);
    u8 unk_1d = (answer.what >> 3) & 3;
    u8 unk_20 = (answer.what >> 5) & 3;
    u8 layer = (u8) TileRequestGrant_AnswerLayer(&answer);

    if (granted != 0) {
        TileRequestTile at = tile;
        switch (kind) {
            case TILE_REQUEST_SPLIT_DROP:
                TileChanges_Put((u8) slot, (const TileChangesTile *) &at, answer.item, ITEM_CODE_NONE, (u8) kind, unk_1d,
                                unk_20, TILE_REQUEST_GRANT_PLACE, layer, -1);
                at = tile;
                TileEvent_StartKind4(slot, answer.item, (const TileChangesTile *) &at);
                break;
            case TILE_REQUEST_DROP_A7:
                TileChanges_Put((u8) slot, (const TileChangesTile *) &at, answer.item, ITEM_CODE_NONE, (u8) kind, unk_1d,
                                unk_20, TILE_REQUEST_GRANT_PLACE, layer, -1);
                if (TileRequests_MayAsk(slot) == 0) {
                    at = tile;
                    TileEvent_StartKind4(slot, answer.item, (const TileChangesTile *) &at);
                }
                break;
            case 0xc:
            case 0xd:
            case TILE_REQUEST_CHANGE_AROUND:
            case 0x17:
                break;
            default: {
                u16 code = request->code;
                TileChanges_Put((u8) slot, (const TileChangesTile *) &at, answer.item, code, (u8) kind, unk_1d, unk_20,
                                TILE_REQUEST_GRANT_PLACE, layer, -1);
                if (TileRequestGrant_Drops(&answer, request, slot) != 0) {
                    answer.who |= TILE_REQUEST_ANSWER_EXTRAS;
                    size = TILE_REQUEST_ANSWER_SIZE;
                }
                break;
            }
        }
        if (TileRequests_MayAsk(slot) != 0) {
            data_021c7c48.requests[(request->who >> 2) & 3].state = TILE_REQUEST_GRANTED;
        } else {
            TileRequests_ReceiveAction((const TileRequestsActionMessage *) &answer);
        }
    } else if (TileRequests_MayAsk(slot) != 0) {
        data_021c7c48.requests[(request->who >> 2) & 3].state = TILE_REQUEST_REFUSED;
    }

    NetSession *session = data_020ccf94;
    Session_BeginMessage(session);
    Session_AppendMessage(session, &answer, size);
    Session_EndMessage(session, TILE_REQUEST_GRANT_MESSAGE_ANSWER, TILE_REQUEST_GRANT_MESSAGE_ANSWER_KIND);
}
CLEAN_AS(func_0204510c, TileRequestGrant_Answer)

/* func_02045380: for kinds 1 and 6, the drops of the request's code noted in the answer (the
 * extra tiles none first): a grown code of the lines 0x2f-0x5b and 0xc8-0xcf drops several
 * (TileRequestGrant_DropMany), 0x66-0x6c one (0x67 and 0x6b only when an item may drop);
 * whether it drops anything. */
int TileRequestGrant_Drops(TileRequestAnswer *answer, const TileRequestMessage *request, int slot)
{
    int kind = request->what & TILE_REQUEST_MESSAGE_KIND_MASK;
    if (kind != 1 && kind != 6) {
        return 0;
    }
    for (int i = 0; i < 3; i++) {
        answer->extra_tiles[i] = TILE_CHANGES_NO_TILE;
    }
    u16 code = request->code;
    if (TileRequestGrant_InRange(code, 0x2f, 0x56) || TileRequestGrant_InRange(code, 0xc8, 0xcf) ||
        TileRequestGrant_InRange(code, 0x57, 0x5b)) {
        if (MapItem_IsGrown(&code) == 0) {
            return 0;
        }
        TileRequestGrant_DropMany(answer, slot, request->code);
        return 1;
    }
    if (code == 0x67 || code == 0x6b) {
        if (TileRequests_ItemDropAllowed() == 0) {
            return 0;
        }
        TileRequestGrant_DropOne(answer, request, slot);
        return 1;
    }
    if (TileRequestGrant_InRange(code, 0x66, 0x68) || TileRequestGrant_InRange(code, 0x6a, 0x6c)) {
        TileRequestGrant_DropOne(answer, request, slot);
        return 1;
    }
    return 0;
}
CLEAN_AS(func_02045380, TileRequestGrant_Drops)

/* func_02045440: one item dropped next to the answer's tile, on the side func_ov003_02223078
 * picks from the request's tile: a bag of bells (0x1492) for 0x68, 0x6c and codes outside
 * 0x66-0x6c, else an item drawn by func_020638d4. Its tile (or none) and the item go to the
 * answer. */
void TileRequestGrant_DropOne(TileRequestAnswer *answer, const TileRequestMessage *request, int slot)
{
    AcreMap *town = (AcreMap *) (uintptr_t) AcreMap_Town();
    if (town == NULL) {
        return;
    }
    u16 item = TILE_REQUEST_GRANT_BAG;
    u16 code = request->code;
    if ((TileRequestGrant_InRange(code, 0x66, 0x68) || TileRequestGrant_InRange(code, 0x6a, 0x6c)) && request->code != 0x68 &&
        request->code != 0x6c) {
        int drawer[2];
        u16 drawn;
        ItemList_Construct((ItemList *) drawer, 0, 0);
        ItemLists_Draw(&drawn, (ItemList *) drawer, 0, 0, 1, 1, 0);
        item = drawn;
        ItemList_Destruct(drawer);
    }
    u16 packed = request->tile;
    Vec3 centre;
    AcreTile_TileCentre(&centre, (u32) (packed >> 8), (u32) (packed & 0xff));
    int side = GrowthModel_PlayerSide(slot, &centre);
    TileRequestTile at = TileRequestGrant_Near(answer->tile, data_020ca67c[side]);
    if (TileRequestGrant_FindDropTile(answer, &at, side, town) != 0) {
        TileRequestTile to = at;
        TileChanges_Put((u8) slot, (const TileChangesTile *) &to, item, ITEM_CODE_NONE, 0, 0, 0, 0, 0, -1);
        TileRequestGrant_SetExtraTile(answer, 0, &at);
    } else {
        answer->extra_tiles[0] = TILE_CHANGES_NO_TILE;
    }
    answer->extra_item = item;
}
CLEAN_AS(func_02045440, TileRequestGrant_DropOne)

/* func_0204558c: the item of a grown `code` (TileRequestGrant_DropItemOf) dropped three times
 * (twice for 0xcc) on tiles around the answer's tile, each from its own neighbour; the tiles
 * (or none) and the item go to the answer. */
void TileRequestGrant_DropMany(TileRequestAnswer *answer, int slot, int code)
{
    AcreMap *town = (AcreMap *) (uintptr_t) AcreMap_Town();
    if (town == NULL) {
        return;
    }
    int count = code == 0xcc ? 2 : 3;
    u16 item = TileRequestGrant_DropItemOf((int) (uintptr_t) answer, code);
    for (int i = 0; i < count; i++) {
        TileRequestTile at = TileRequestGrant_Near(answer->tile, data_020ca67c[i]);
        if (TileRequestGrant_FindDropTile(answer, &at, i, town) != 0) {
            TileRequestTile to = at;
            TileChanges_Put((u8) slot, (const TileChangesTile *) &to, item, ITEM_CODE_NONE, 0, 0, 0, (u8) i, 0, -1);
            TileRequestGrant_SetExtraTile(answer, i, &at);
        } else {
            answer->extra_tiles[i] = TILE_CHANGES_NO_TILE;
        }
    }
    answer->extra_item = item;
}
CLEAN_AS(func_0204558c, TileRequestGrant_DropMany)

/* func_02045670: the item a grown code drops: 0x14b8 (a bag of bells) for 0x5b, 0x1548 for
 * 0xcc, else data_020ca670's for its line of eight. */
u16 TileRequestGrant_DropItemOf(int unused, int code)
{
    (void) unused;
    if (code == 0x5b) {
        return 0x14b8;
    }
    if (code == 0xcc) {
        return 0x1548;
    }
    u16 key = (u16) code;
    return data_020ca670[MapItem_EightLine(&key)];
}
CLEAN_AS(func_02045670, TileRequestGrant_DropItemOf)

/* func_020456b0: from `tile`, the first of the eight neighbours data_020cb488 gives for drop
 * `index` that is empty, allowed (AcreTile_UnitByte04) and has no change under way in layer 0;
 * it goes to `tile`, 1. When there is none, 0.
 * QUIRK: then `tile` still moves to the first of the eight. */
int TileRequestGrant_FindDropTile(void *unused, TileRequestTile *tile, int index, AcreMap *town)
{
    (void) unused;
    const int *order = data_020cb488[index];
    for (int i = 0; i < TILE_REQUEST_GRANT_TRIES; i++) {
        u8 offset = data_020ca640[order[i]];
        int x = tile->x + ((offset >> 4) - 8);
        int z = tile->z + ((offset & 0xf) - 8);
        u16 *code = TileRequestGrant_CodeAt(town, x, z);
        if (code == NULL || *code != ITEM_CODE_NONE) {
            continue;
        }
        if (AcreTile_UnitByte04(town, x, z) == 0) {
            continue;
        }
        TileChangesTile at = {x, z};
        if (TileChanges_IndexAt(&at, 0) < 0) {
            tile->x = x;
            tile->z = z;
            return 1;
        }
    }
    u8 offset = data_020ca640[order[0]];
    tile->x = tile->x + ((offset >> 4) - 8);
    tile->z = tile->z + ((offset & 0xf) - 8);
    return 0;
}
CLEAN_AS(func_020456b0, TileRequestGrant_FindDropTile)

/* func_02045770: request `index` of data_021c7c48 handed on (`unk_20` kept with it). It is
 * refused when there is no scene's map or tile, or the tile is not free for it
 * (TileRequestGrant_TileFree). While linked the system holding the scene answers it here, any
 * other sends it there (message 49). Not linked it is granted and carried out:
 * TileRequestGrant_Prepare first (which may finish it), then the item put on the tile (refused
 * when that fails) and what it drops.
 * BUG: bits 6-7 of the message's first byte are left as the stack held them, and sent; nothing
 * reads them. Clean sends 0. */
void TileRequestGrant_Submit(u8 index, int unk_20)
{
    AcreMap *map = data_021c80bc;
    TileRequest *request = &data_021c7c48.requests[index];
    if (map == NULL) {
        request->state = TILE_REQUEST_REFUSED;
        return;
    }
    int x = request->tile.x;
    int z = request->tile.z;
    u16 *code = TileRequestGrant_CodeAt(map, x, z);
    if (code == NULL) {
        request->state = TILE_REQUEST_REFUSED;
        return;
    }
    TileRequestTile at = {x, z};
    if (TileRequestGrant_TileFree(index, &at) == 0) {
        request->state = TILE_REQUEST_REFUSED;
        return;
    }

    TileRequestMessage message;
    message.who = (u8) ((request->player & 3) | ((index & 3) << 2) | ((request->unk_1d & 3) << 4));
    message.what = (u8) ((request->kind & TILE_REQUEST_MESSAGE_KIND_MASK) | ((unk_20 & 3) << 5) | ((request->layer & 1) << 7));
    message.tile = (u16) (((x & 0xff) << 8) | (z & 0xff));
    message.code = *code;
    message.item = request->item;

    NetSession *session = data_020ccf94;
    if (Session_IsLinked(session)) {
        if (LinkGlobal_HoldsScene()) {
            TileRequestGrant_Answer(&message, 1, session->local_slot);
            return;
        }
        session = data_020ccf94;
        Session_BeginMessage(session);
        Session_AppendMessage(session, &message, sizeof(message));
        Session_EndMessage(session, TILE_REQUEST_GRANT_MESSAGE_ASK, TILE_REQUEST_GRANT_MESSAGE_ASK_KIND);
        return;
    }

    request->state = TILE_REQUEST_GRANTED;
    if (TileRequestGrant_Prepare(&message, request) != 0) {
        return;
    }
    s8 unk_1e = request->unk_1e;
    TileRequestTile to = request->tile;
    if (TileChanges_Put(0, (const TileChangesTile *) &to, message.item, message.code,
                        message.what & TILE_REQUEST_MESSAGE_KIND_MASK, (message.who >> 4) & 3, (message.what >> 5) & 3,
                        TILE_REQUEST_GRANT_PLACE, message.what >> 7, unk_1e) == 0) {
        request->state = TILE_REQUEST_REFUSED;
        return;
    }
    TileRequestAnswer drops;
    drops.tile = (u16) (((request->tile.x & 0xff) << 8) | (request->tile.z & 0xff));
    TileRequestGrant_Drops(&drops, &message, 0);
}
CLEAN_AS(func_02045770, TileRequestGrant_Submit)

/* func_0204590c: what a request does before its item is put down. Kind 0x13 puts the code an
 * item becomes in its place (data_020ca658 for 0x1518-0x151c, 0xc8 for 0x1548, 0x26 for
 * 0x151d, 0x5d for 0x151e); kind 0xf changes the codes around the tile
 * (TileRequests_ChangeCodesAround) and kind 0xe hits the money rock. Whether the request is
 * then done: for kinds 0xf, 0xc, 0xd and 0x17. */
int TileRequestGrant_Prepare(TileRequestMessage *message, const TileRequest *request)
{
    u16 item = message->item;
    switch (message->what & TILE_REQUEST_MESSAGE_KIND_MASK) {
        case TILE_REQUEST_KIND_13:
            if (TileRequestGrant_InRange(item, 0x1518, 0x151c)) {
                message->item = data_020ca658[item - 0x1518];
            } else if (item == 0x1548) {
                message->item = 0xc8;
            } else if (item == 0x151d) {
                message->item = 0x26;
            } else if (item == 0x151e) {
                message->item = 0x5d;
            }
            return 0;
        case TILE_REQUEST_CHANGE_AROUND: {
            int player = TileRequests_PlayerOf(request->player);
            TileRequestTile at = request->tile;
            TileRequests_ChangeCodesAround(player, &at);
            return 1;
        }
        case 0xc:
        case 0xd:
        case 0x17:
            return 1;
        case 0xe: {
            TileRequestTile at = request->tile;
            TileRequests_HitRock(&data_021c7c48.rock, &at);
            return 0;
        }
        default:
            return 0;
    }
}
CLEAN_AS(func_0204590c, TileRequestGrant_Prepare)

/* func_020459f0: whether request `index` may go on at `tile`: with no change under way there
 * (in the request's layer), when no other player stands near (TileRequestGrant_NoOtherNear);
 * else when that change is held by the request's player with the request's unk_1e. */
int TileRequestGrant_TileFree(int index, const TileRequestTile *tile)
{
    const TileRequest *request = &data_021c7c48.requests[index];
    TileChangesTile at = {tile->x, tile->z};
    int found = TileChanges_IndexAt(&at, request->layer);
    if (found < 0) {
        TileRequestTile copy = *tile;
        return TileRequestGrant_NoOtherNear(&copy) != 0;
    }
    const TileChange *change = &data_021c7884[found];
    int number = (change->flags >> 2) & 0xf;
    if (number >= 8) {
        number -= 16;
    }
    return (change->who & TILE_CHANGE_SLOT_MASK) == (request->player & 3) && number == request->unk_1e &&
           (change->state & TILE_CHANGE_HELD) != 0;
}
CLEAN_AS(func_020459f0, TileRequestGrant_TileFree)

/* func_02045a80: TileRequestGrant_NoOneNear but for this system's player. */
int TileRequestGrant_NoOtherNear(const TileRequestTile *tile)
{
    int self = data_020ccf94->local_player;
    TileRequestTile at = *tile;
    return TileRequestGrant_NoOneNear(&at, self);
}
CLEAN_AS(func_02045a80, TileRequestGrant_NoOtherNear)

/* func_02045aa4: TileRequestGrant_NoOneNear but for the player of `slot`
 * (TileRequests_PlayerOf). */
int TileRequestGrant_NoOtherNearFor(const TileRequestTile *tile, int slot)
{
    TileRequestTile at = *tile;
    return TileRequestGrant_NoOneNear(&at, TileRequests_PlayerOf(slot));
}
CLEAN_AS(func_02045aa4, TileRequestGrant_NoOtherNearFor)

/* func_02045ac4: whether no player's actor but `skip`'s stands within 1.0 of the tile's centre
 * (always when not linked). */
int TileRequestGrant_NoOneNear(const TileRequestTile *tile, int skip)
{
    if (!Session_IsLinked(data_020ccf94)) {
        return 1;
    }
    Vec3 centre;
    AcreTile_TileCentre(&centre, (u32) tile->x, (u32) tile->z);
    for (int i = 0; i < TILE_REQUEST_GRANT_PLAYERS; i++) {
        if (i == skip) {
            continue;
        }
        TileRequestsActor *actor = SessionPlayers_ActorOf(i);
        if (actor == NULL) {
            continue;
        }
        fx32 dx = TileRequestGrant_Sub(centre.x, actor->position.x);
        fx32 dz = TileRequestGrant_Sub(centre.z, actor->position.z);
        fx32 x2 = FX_MulFunc(dx, dx);
        fx32 z2 = FX_MulFunc(dz, dz);
        if (TileRequestGrant_Add(x2, z2) < TILE_REQUEST_GRANT_NEAR) {
            return 0;
        }
    }
    return 1;
}
CLEAN_AS(func_02045ac4, TileRequestGrant_NoOneNear)
