/* The changes to tiles under way (tile_changes.h). */
#include "tile_changes.h"

#include "clean.h"
#include "session.h"
#include "tile_requests.h"

static_assert(sizeof(TileChange) == 0x10, "TileChange");
static_assert(offsetof(TileChange, tile) == 0x08, "TileChange.tile");
static_assert(offsetof(TileChanges, changes) == 0x04, "TileChanges.changes");

extern TileChanges data_021c7880;
extern TileChange data_021c7884[TILE_CHANGES_COUNT]; /* data_021c7880.changes */
extern NetSession *data_020ccf94;

/* A record set free (tile 0xffff, item 0xfff1, slot 7). */
extern void func_020465b0(TileChange *change);
/* A change finished: its effect on the map carried out, then its record freed. */
extern void func_0204629c(TileChange *change);
/* A change done with: kinds 4, 10, 22 and 25 freed, the others finished; nothing for a free
 * record. */
extern void func_020461e0(TileChange *change);
/* A change let go of: kinds 4, 10, 22 and 25 kept, the others finished. */
extern void func_0204622c(TileChange *change);
/* func_020465b0, as the initial state calls it. */
extern void func_02046224(TileChange *change);
/* Whether the actor of `slot` is at the tile (overlay 3). */
extern int func_ov003_02221340(int slot, TileChangesTile *tile);

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
        func_02046224(&changes->changes[i]);
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
        func_020461e0(&change[i]);
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
        func_020465b0(&data_021c7884[index]);
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
    func_0204622c(change);
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
    if (func_ov003_02221340(TileChanges_Slot(change), &on) != 0) {
        return;
    }
    if (TileChanges_Stays(TileChanges_Kind(change))) {
        TileChanges_Release(change);
    } else {
        func_0204629c(change);
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
        func_0204629c(&data_021c7884[index]);
    }
}
CLEAN_AS(func_02045ea8, TileChanges_FinishOwnAt)

/* func_02045eec: change `index` finished, unless it is -1. */
void TileChanges_FinishAt(int index)
{
    if (index >= 0) {
        func_0204629c(&data_021c7884[index]);
    }
}
CLEAN_AS(func_02045eec, TileChanges_FinishAt)
