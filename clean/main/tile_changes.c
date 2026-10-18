/* The changes to tiles under way (tile_changes.h). */
#include "tile_changes.h"

#include "acre_tile.h"
#include "clean.h"
#include "scene_query.h"
#include "session.h"
#include "tile_requests.h"
#include "ov003/growth_model.h"
#include "ov003/tile_event.h"
#include "ov004/dropped_items.h"

static_assert(sizeof(TileChange) == 0x10, "TileChange");
static_assert(offsetof(TileChange, tile) == 0x08, "TileChange.tile");
static_assert(offsetof(TileChanges, changes) == 0x04, "TileChanges.changes");

extern TileChanges data_021c7880;
extern TileChange data_021c7884[TILE_CHANGES_COUNT]; /* data_021c7880.changes */
extern NetSession *data_020ccf94;

static int TileChanges_Slot(const TileChange *change)
{
    return change->who & TILE_CHANGE_SLOT_MASK;
}

static int TileChanges_Kind(const TileChange *change)
{
    return change->who >> TILE_CHANGE_KIND_SHIFT;
}

static int TileChanges_IsHeld(const TileChange *change)
{
    return (change->state & TILE_CHANGE_HELD) != 0;
}

static int TileChanges_Layer(const TileChange *change)
{
    return (change->flags & TILE_CHANGE_LAYER) != 0;
}

/* Whether the change is at the tile. */
static int TileChanges_IsAt(const TileChange *change, const TileChangesTile *tile)
{
    u16 at = change->tile;
    return tile->x == (at >> 8) && tile->z == (at & 0xff);
}

/* The kinds of change that stay when let go of. */
static int TileChanges_Stays(int kind)
{
    return kind == 4 || kind == 10 || kind == 22 || kind == 25;
}

/* func_02045b3c: every record set free. */
void TileChanges_Init(TileChanges *changes)
{
    for (int i = 0; i < TILE_CHANGES_COUNT; i++) {
        TileChanges_InitRecord(&changes->changes[i]);
    }
}
CLEAN_AS(func_02045b3c, TileChanges_Init)

/* func_02045b5c: the tile of the first change `slot` (0 when not linked) holds, or NULL. */
u16 *TileChanges_HeldTileOf(int slot)
{
    if (!Session_IsLinked(data_020ccf94)) {
        slot = 0;
    }
    for (int i = 0; i < TILE_CHANGES_COUNT; i++) {
        TileChange *change = &data_021c7884[i];
        if (slot == TileChanges_Slot(change) && TileChanges_IsHeld(change)) {
            return &change->tile;
        }
    }
    return NULL;
}
CLEAN_AS(func_02045b5c, TileChanges_HeldTileOf)

/* func_02045bac: the address of record `index`. */
int TileChanges_At(int index)
{
    return (int) (uintptr_t) &data_021c7884[index];
}
CLEAN_AS(func_02045bac, TileChanges_At)

/* func_02045bb8: the first change of `slot` (0 when not linked) with tag `tag`, or -1. */
int TileChanges_FindByTag(int slot, int tag)
{
    if (!Session_IsLinked(data_020ccf94)) {
        slot = 0;
    }
    for (int i = 0; i < TILE_CHANGES_COUNT; i++) {
        const TileChange *change = &data_021c7884[i];
        if (slot == TileChanges_Slot(change) && tag == ((change->state >> TILE_CHANGE_TAG_SHIFT) & 7)) {
            return i;
        }
    }
    return TILE_CHANGES_NONE;
}
CLEAN_AS(func_02045bb8, TileChanges_FindByTag)

/* func_02045c08: the first change held by `slot` (its low two bits), or -1. */
int TileChanges_FindHeld(int slot)
{
    slot &= 3;
    for (int i = 0; i < TILE_CHANGES_COUNT; i++) {
        const TileChange *change = &data_021c7884[i];
        if (slot == TileChanges_Slot(change) && TileChanges_IsHeld(change)) {
            return i;
        }
    }
    return TILE_CHANGES_NONE;
}
CLEAN_AS(func_02045c08, TileChanges_FindHeld)

/* func_02045c48: a free record (at the tile 0xff, 0xff, layer 0), or -1. */
int TileChanges_FindFree(void)
{
    TileChangesTile none = {0xff, 0xff};
    return TileChanges_FindAt(&none, 0);
}
CLEAN_AS(func_02045c48, TileChanges_FindFree)

/* func_02045c60: TileChanges_FindOwnAt for `player`'s slot (TileRequests_SlotOf). */
int TileChanges_FindOwnAtFor(u32 player, const TileChangesTile *tile, u32 layer)
{
    u32 slot = (u32) TileRequests_SlotOf((int) player);
    TileChangesTile at = *tile;
    return TileChanges_FindOwnAt(slot, &at, layer);
}
CLEAN_AS(func_02045c60, TileChanges_FindOwnAtFor)

/* func_02045c84: the first change of `slot` at the tile and layer, or -1. */
int TileChanges_FindOwnAt(u32 slot, const TileChangesTile *tile, u32 layer)
{
    for (int i = 0; i < TILE_CHANGES_COUNT; i++) {
        const TileChange *change = &data_021c7884[i];
        if (slot == (u32) TileChanges_Slot(change) && TileChanges_IsAt(change, tile) &&
            layer == (u32) TileChanges_Layer(change)) {
            return i;
        }
    }
    return TILE_CHANGES_NONE;
}
CLEAN_AS(func_02045c84, TileChanges_FindOwnAt)

/* func_02045cec: the first change at the tile and layer, or -1. */
int TileChanges_FindAt(const TileChangesTile *tile, int layer)
{
    for (int i = 0; i < TILE_CHANGES_COUNT; i++) {
        const TileChange *change = &data_021c7884[i];
        if (TileChanges_IsAt(change, tile) && layer == TileChanges_Layer(change)) {
            return i;
        }
    }
    return TILE_CHANGES_NONE;
}
CLEAN_AS(func_02045cec, TileChanges_FindAt)

/* func_02045d44: every change done with (func_020461e0); other systems' actions are no longer
 * taken in. */
void TileChanges_FinishAll(void)
{
    TileChange *change = (TileChange *) (uintptr_t) TileChanges_At(0);
    for (int i = 0; i < TILE_CHANGES_COUNT; i++) {
        TileChanges_Done(&change[i]);
    }
    data_021c7880.active = 0;
}
CLEAN_AS(func_02045d44, TileChanges_FinishAll)

/* func_02045d74: other systems' actions are taken in. */
void TileChanges_Activate(void)
{
    data_021c7880.active = 1;
}
CLEAN_AS(func_02045d74, TileChanges_Activate)

/* func_02045d80: TileChanges_FindAt with a copy of the tile. */
int TileChanges_IndexAt(const TileChangesTile *tile, int layer)
{
    TileChangesTile at = *tile;
    return TileChanges_FindAt(&at, layer);
}
CLEAN_AS(func_02045d80, TileChanges_IndexAt)

/* func_02045d98: the record of the change `slot` holds set free. */
void TileChanges_FreeHeld(int slot)
{
    int index = TileChanges_FindHeld(slot);
    if (index >= 0) {
        TileChanges_Free(&data_021c7884[index]);
    }
}
CLEAN_AS(func_02045d98, TileChanges_FreeHeld)

/* func_02045db8: no change of the change's slot held any more, then the change let go of
 * (func_0204622c). */
void TileChanges_Release(TileChange *change)
{
    for (int i = 0; i < TILE_CHANGES_COUNT; i++) {
        TileChange *other = &data_021c7884[i];
        if (TileChanges_Slot(other) == TileChanges_Slot(change) && TileChanges_IsHeld(other)) {
            other->state &= (u8) ~TILE_CHANGE_HELD;
        }
    }
    TileChanges_LetGo(change);
}
CLEAN_AS(func_02045db8, TileChanges_Release)

/* func_02045df8: TileChanges_Release for the change at the tile and layer, if there is one. */
void TileChanges_ReleaseAt(const TileChangesTile *tile, int layer)
{
    TileChangesTile at = *tile;
    int index = TileChanges_FindAt(&at, layer);
    if (index >= 0) {
        TileChanges_Release(&data_021c7884[index]);
    }
}
CLEAN_AS(func_02045df8, TileChanges_ReleaseAt)

/* func_02045e24: the change at the tile and layer, unless its slot's actor is at the tile
 * (func_ov003_02221340): released for kinds 4, 10, 22 and 25, else finished. */
void TileChanges_LetGoAt(const TileChangesTile *tile, int layer)
{
    TileChangesTile at = *tile;
    int index = TileChanges_FindAt(&at, layer);
    if (index < 0) {
        return;
    }
    TileChange *change = &data_021c7884[index];
    u16 packed = change->tile;
    TileChangesTile on = {packed >> 8, packed & 0xff};
    if (TileEvent_EndAt(TileChanges_Slot(change), &on) != 0) {
        return;
    }
    if (TileChanges_Stays(TileChanges_Kind(change))) {
        TileChanges_Release(change);
    } else {
        TileChanges_Finish(change);
    }
}
CLEAN_AS(func_02045e24, TileChanges_LetGoAt)

/* func_02045ea8: the change at the tile and layer finished when it is `slot`'s (its low two
 * bits). */
void TileChanges_FinishOwnAt(const TileChangesTile *tile, int slot, int layer)
{
    TileChangesTile at = *tile;
    int index = TileChanges_FindAt(&at, layer);
    if (index < 0) {
        return;
    }
    if ((slot & 3) == TileChanges_Slot(&data_021c7884[index])) {
        TileChanges_Finish(&data_021c7884[index]);
    }
}
CLEAN_AS(func_02045ea8, TileChanges_FinishOwnAt)

/* func_02045eec: change `index` finished, unless it is -1. */
void TileChanges_FinishAt(int index)
{
    if (index >= 0) {
        TileChanges_Finish(&data_021c7884[index]);
    }
}
CLEAN_AS(func_02045eec, TileChanges_FinishAt)

/* Putting a change in a record, finishing it and freeing it. A change is put by the request's
 * fields (tile_request_grant.c names them): the slot, the item and the tile's code, the kind,
 * the result (bits 0-1 of `state`), TileRequest.unk_20 (bits 5-6), the tag (bits 2-4), the
 * layer and a signed number (bits 2-5 of `flags`). */

#define TILE_CHANGE_RESULT_MASK 0x03
#define TILE_CHANGE_UNK_20_SHIFT 5
#define TILE_CHANGE_TAG_MASK (7 << TILE_CHANGE_TAG_SHIFT)
#define TILE_CHANGE_UNK_20_MASK (3 << TILE_CHANGE_UNK_20_SHIFT)
#define TILE_CHANGE_SET 0x01       /* flags: the record is filled */
#define TILE_CHANGE_NUMBER_SHIFT 2 /* flags: 4 bits, signed */
#define TILE_CHANGE_NUMBER_MASK (0xf << TILE_CHANGE_NUMBER_SHIFT)
#define TILE_CHANGES_NO_ITEM 0xfff1

/* data_021c7c48 (tile_requests.h): the marks of the town's tiles. */
extern TileRequests data_021c7c48;
/* data_021c776c (block_02042200.h): two flags of main. */
extern u8 data_021c776c[2];

/* func_02045f08: the change at the tile and layer finished (TileChanges_FinishAt). */
void TileChanges_FinishAtTile(const TileChangesTile *tile, int layer)
{
    TileChanges_FinishAt(TileChanges_FindAt(tile, layer));
}
CLEAN_AS(func_02045f08, TileChanges_FinishAtTile)

/* func_02045f24: as TileChanges_Put, but a change already at the tile and layer is taken over:
 * when no one holds it, it is finished first (for the hitting kinds 1, 2, 6 and 7, after
 * func_ov003_02222d8c on its code and its own slot), and the record is then filled again. */
int TileChanges_Replace(int slot, const TileChangesTile *tile, u32 item, int code, u8 kind, u8 result, u8 unk_20, u8 tag,
                        u8 layer, s8 number)
{
    int index = TileChanges_FindAt(tile, layer);
    if (index < 0) {
        return TileChanges_PutNew(slot, tile, (int) item, code, kind, result, unk_20, tag, layer, number);
    }
    TileChange *change = &data_021c7884[index];
    if (!TileChanges_IsHeld(change)) {
        switch (TileChanges_Kind(change)) {
            case 1:
            case 2:
            case 6:
            case 7: {
                u16 old_code = change->unk_0c;
                TileChangesTile at = *tile;
                GrowthModel_Drop(&old_code, TileChanges_Slot(change), &at);
                break;
            }
        }
        TileChanges_Finish(change);
    }
    return TileChanges_FillAt((u32) index, (u32) slot, tile, item, (u16) code, kind, result, unk_20, tag, layer, number);
}
CLEAN_AS(func_02045f24, TileChanges_Replace)

/* func_02046024: the item put on the tile through a change; whether it was. With no change at
 * the tile and layer, a new one (TileChanges_PutNew); with one that `slot` (its low two bits)
 * holds, that record filled again; with anyone else's, nothing. */
int TileChanges_Put(int slot, const TileChangesTile *tile, u32 item, u32 code, u8 kind, u8 result, u8 unk_20, u8 tag, u8 layer,
                    s8 number)
{
    int index = TileChanges_FindAt(tile, layer);
    if (index < 0) {
        return TileChanges_PutNew(slot, tile, (int) item, (int) code, kind, result, unk_20, tag, layer, number);
    }
    const TileChange *change = &data_021c7884[index];
    if ((slot & 3) == TileChanges_Slot(change) && TileChanges_IsHeld(change)) {
        TileChanges_FillAt((u32) index, (u32) slot, tile, item, (u16) code, kind, result, unk_20, tag, layer, number);
        return 1;
    }
    return 0;
}
CLEAN_AS(func_02046024, TileChanges_Put)

/* func_020460ec: a free record filled with the change, once the tile is clear of changes
 * (TileChanges_MakeRoomAt); whether it was. */
int TileChanges_PutNew(int slot, const TileChangesTile *tile, int item, int code, u8 kind, u8 result, u8 unk_20, u8 tag,
                       u8 layer, s8 number)
{
    if (!TileChanges_MakeRoomAt(tile)) {
        return 0;
    }
    int index = TileChanges_FindFree();
    if (index < 0) {
        return 0;
    }
    TileChanges_FillAt((u32) index, (u32) slot, tile, (u32) item, (u16) code, kind, result, unk_20, tag, layer, number);
    return 1;
}
CLEAN_AS(func_020460ec, TileChanges_PutNew)

/* func_02046154: whether the tile (layer 0) is clear of changes: a change of kind 0x1a found
 * there is finished, any other keeps it. */
int TileChanges_MakeRoomAt(const TileChangesTile *tile)
{
    int index = TileChanges_FindAt(tile, 0);
    if (index < 0) {
        return 1;
    }
    const TileChange *change = (const TileChange *) (uintptr_t) TileChanges_At(index);
    if (TileChanges_Kind(change) != TILE_REQUEST_DROP_A7) {
        return 0;
    }
    TileChanges_FinishAt(index);
    return 1;
}
CLEAN_AS(func_02046154, TileChanges_MakeRoomAt)

/* func_02046194: record `index` filled (TileChanges_Fill) at the tile, x in the high byte. */
int TileChanges_FillAt(u32 index, u32 slot, const TileChangesTile *tile, u32 item, u16 code, u8 kind, u8 result, u8 unk_20,
                       u8 tag, u8 layer, s8 number)
{
    u16 packed = (u16) (((u8) tile->x << 8) | (u8) tile->z);
    return TileChanges_Fill(&data_021c7884[index], slot, packed, item, code, kind, result, unk_20, tag, layer, number);
}
CLEAN_AS(func_02046194, TileChanges_FillAt)

/* func_020461e0: a change done with: kinds 4, 10, 22 and 25 freed, the others finished;
 * nothing for a free record. */
void TileChanges_Done(TileChange *change)
{
    if (change->tile == TILE_CHANGES_NO_TILE) {
        return;
    }
    if (TileChanges_Stays(TileChanges_Kind(change))) {
        TileChanges_Free(change);
    } else {
        TileChanges_Finish(change);
    }
}
CLEAN_AS(func_020461e0, TileChanges_Done)

/* func_02046224: the record set free, as the initial state does it. */
void TileChanges_InitRecord(TileChange *change)
{
    TileChanges_Free(change);
}
CLEAN_AS(func_02046224, TileChanges_InitRecord)

/* func_0204622c: a change let go of. Kinds 4, 22 and 25 stay: reported (TileChanges_Report),
 * then held and their `flags` bit 0 cleared; kind 10 the same, and it also takes its code as
 * its item and the result 1. The other kinds are finished. */
void TileChanges_LetGo(TileChange *change)
{
    switch (TileChanges_Kind(change)) {
        case 4:
        case 22:
        case 25:
            TileChanges_Report(change);
            change->state |= TILE_CHANGE_HELD;
            change->flags &= (u8) ~TILE_CHANGE_SET;
            break;
        case 10:
            TileChanges_Report(change);
            change->state |= TILE_CHANGE_HELD;
            change->flags &= (u8) ~TILE_CHANGE_SET;
            change->item = change->unk_0c;
            change->state = (u8) ((change->state & ~TILE_CHANGE_RESULT_MASK) | 1);
            break;
        default:
            TileChanges_Finish(change);
            break;
    }
}
CLEAN_AS(func_0204622c, TileChanges_LetGo)

static int TileChanges_InRange(unsigned int code, unsigned int first, unsigned int last)
{
    return code >= first && code <= last;
}

/* Whether a put item does not stay on a tile of this code: family A (and 0x1a, 0x1c, 0x1d),
 * family C (and 0xa4, 0xa5), and the growth lines (map_item.h). */
static int TileChanges_CodeTakesNoItem(unsigned int code)
{
    return code <= 0x19 || code == 0x1c || TileChanges_InRange(code, 0x8a, 0xa3) || code == 0xa5 || code == 0x1a ||
           code == 0xa4 || code == 0x1d || TileChanges_InRange(code, 0x26, 0x2a) || TileChanges_InRange(code, 0x5d, 0x61) ||
           TileChanges_InRange(code, 0x2f, 0x5b) || TileChanges_InRange(code, 0x66, 0x6d) ||
           TileChanges_InRange(code, 0xc8, 0xcf);
}

/* The code on the tile (x, z) of the town's map (its first layer), or NULL outside scene 0 or
 * without the map. */
static const u16 *TileChanges_TownCodeAt(int x, int z)
{
    if (SceneQuery_CurrentIs0() == 0) {
        return NULL;
    }
    AcreMap *town = (AcreMap *) (uintptr_t) AcreMap_Town();
    if (town == NULL) {
        return NULL;
    }
    return AcreTile_ItemInAcre(town, (u32) (x >> 4), (u32) (z >> 4), x & 15, z & 15, 0);
}

/* func_0204629c: a change finished. In scene 0 with the town's map, by its kind:
 * - 0x12 (the held change of its slot freed first), 0x11, 0x13, 0x18 and 0x1a: the result
 *   stays (as 1) only when the tile's code takes items (TileChanges_CodeTakesNoItem);
 * - 6 and 7: unless bits 5-6 of `state` are 2, the tile's mark (TileRequests_SetMark) set to
 *   the result + 1;
 * - 10: the result kept;
 * - 0x19: the item cleared when the signed number is 0 or more.
 * Every other case ends with the result 0. The change is then reported and freed. */
void TileChanges_Finish(TileChange *change)
{
    int result = 0;
    int x = change->tile >> 8;
    int z = change->tile & 0xff;
    const u16 *code = TileChanges_TownCodeAt(x, z);
    if (code != NULL) {
        switch (TileChanges_Kind(change)) {
            case TILE_REQUEST_DROP_12:
                TileChanges_FreeHeld(TileChanges_Slot(change));
                /* fall through */
            case TILE_REQUEST_ACTOR_TILE:
            case TILE_REQUEST_KIND_13:
            case TILE_REQUEST_SPLIT_DROP:
            case TILE_REQUEST_DROP_A7:
                /* read after TileChanges_FreeHeld, which may have freed this very change */
                if (!TileChanges_CodeTakesNoItem(*code) && (change->state & TILE_CHANGE_RESULT_MASK) != 0) {
                    result = 1;
                }
                break;
            case 6:
            case 7:
                if (((change->state & TILE_CHANGE_UNK_20_MASK) >> TILE_CHANGE_UNK_20_SHIFT) != 2) {
                    TileRequestTile tile = {x, z};
                    TileRequests_SetMark(&data_021c7c48, &tile, ((change->state & TILE_CHANGE_RESULT_MASK) + 1) & 3);
                }
                break;
            case 10:
                result = change->state & TILE_CHANGE_RESULT_MASK;
                break;
            case TILE_REQUEST_MARKED_1566:
                /* bit 5 of `flags` is the number's sign */
                if ((change->flags & 0x20) == 0) {
                    change->item = TILE_CHANGES_NO_ITEM;
                }
                break;
        }
    }
    change->state = (u8) ((change->state & ~TILE_CHANGE_RESULT_MASK) | result);
    TileChanges_Report(change);
    TileChanges_Free(change);
}
CLEAN_AS(func_0204629c, TileChanges_Finish)

/* func_02046490: data_021c776c's flag 1 set when the change's item is one of 0x154a-0x1553,
 * flag 0 when it is one of 0x1320-0x1322. */
void TileChanges_NoteItem(const TileChange *change)
{
    u16 item = change->item;
    if (item >= 0x154a && item <= 0x1553) {
        data_021c776c[1] = 1;
    } else if (item >= 0x1320 && item <= 0x1322) {
        data_021c776c[0] = 1;
    }
}
CLEAN_AS(func_02046490, TileChanges_NoteItem)

/* func_020464d4: the change reported to the scene's overlay: in scene 0 to the town's field
 * (with its result), then its item noted (TileChanges_NoteItem); elsewhere to the room's (with
 * its layer). */
void TileChanges_Report(TileChange *change)
{
    int x = change->tile >> 8;
    int z = change->tile & 0xff;
    if (SceneQuery_CurrentIs0() != 0) {
        TileEvent_SetTownItem(x, z, change->item, change->state & TILE_CHANGE_RESULT_MASK);
        TileChanges_NoteItem(change);
    } else {
        DroppedItems_PutOnMap(x, z, change->item, TileChanges_Layer(change));
    }
}
CLEAN_AS(func_020464d4, TileChanges_Report)

/* func_02046518: the record filled and marked set; the answer is its new `flags` byte. The
 * other bits of `state` and `flags` (held, bits 6-7) are kept. */
int TileChanges_Fill(TileChange *change, u32 slot, u16 tile, u32 item, u16 code, u8 kind, u8 result, u8 unk_20, u8 tag,
                     u8 layer, s8 number)
{
    change->who = (u8) (((kind & 0x1f) << TILE_CHANGE_KIND_SHIFT) | (slot & TILE_CHANGE_SLOT_MASK));
    change->tile = tile;
    change->item = (u16) item;
    change->unk_0c = code;
    change->state = (u8) ((change->state & ~(TILE_CHANGE_RESULT_MASK | TILE_CHANGE_UNK_20_MASK | TILE_CHANGE_TAG_MASK)) |
                          (result & 3) | ((unk_20 & 3) << TILE_CHANGE_UNK_20_SHIFT) | ((tag & 7) << TILE_CHANGE_TAG_SHIFT));
    change->flags = (u8) ((change->flags & ~(TILE_CHANGE_LAYER | TILE_CHANGE_NUMBER_MASK)) | ((layer & 1) << 1) |
                          ((number & 0xf) << TILE_CHANGE_NUMBER_SHIFT) | TILE_CHANGE_SET);
    return change->flags;
}
CLEAN_AS(func_02046518, TileChanges_Fill)

/* func_020465b0: the record set free: slot 7, no tile, no item, result 0, not held, tag 7, the
 * first layer and the number -1. The kind, the code and bits 5-6 of `state` stay. */
void TileChanges_Free(TileChange *change)
{
    change->who |= TILE_CHANGE_SLOT_MASK;
    change->tile = TILE_CHANGES_NO_TILE;
    change->item = TILE_CHANGES_NO_ITEM;
    change->state = (u8) ((change->state & TILE_CHANGE_UNK_20_MASK) | TILE_CHANGE_TAG_MASK);
    change->flags = (u8) ((change->flags & 0xc0) | TILE_CHANGE_NUMBER_MASK);
}
CLEAN_AS(func_020465b0, TileChanges_Free)
