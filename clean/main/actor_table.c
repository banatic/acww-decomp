/* The table of actors by item code: see actor_table.h. */
#include "actor_table.h"
#include "clean.h"

#include <assert.h>
#include <stddef.h>

#define ITEM_KIND_D 0xd
#define ITEM_KIND_E 0xe
#define ITEM_INDEX_MASK 0x0fff
#define ITEM_KIND(code) ((code) >> 12)

extern ActorTable data_021d1d4c;

/* An arithmetic shift right, as the ARM's ASR does it, for negative values too. */
static int shift_right(int value, int bits)
{
    return value >= 0 ? value >> bits : ~(~value >> bits);
}

/* func_0204f818: the tile a position is on, x and z over 0x2000 rounded down (func_0204811c
 * takes the acre as the tile over 16). */
void Position_Tile(int *x, int *z, const Position *position)
{
    *x = shift_right(position->x, 13);
    *z = shift_right(position->z, 13);
}
CLEAN_AS(func_0204f818, Position_Tile)

/* func_0207cf74: a number of a kind 0xe entry, as one list of twelve numbers them. */
BOOL ActorTable_IsKindESlot(u32 slot)
{
    return slot < ACTOR_TABLE_KIND_E_ENTRIES;
}
CLEAN_AS(func_0207cf74, ActorTable_IsKindESlot)

/* func_02082b60: an entry with an actor under a kind 0xe code. */
BOOL ActorTable_IsUsedE(const ActorTable *table, const ActorEntry *entry)
{
    (void) table;
    return entry->actor != NULL && ITEM_KIND(entry->code) == ITEM_KIND_E;
}
CLEAN_AS(func_02082b60, ActorTable_IsUsedE)

/* func_020828c0: an entry with an actor under a kind 0xd code. */
BOOL ActorTable_IsUsedD(const ActorTable *table, const ActorEntry *entry)
{
    (void) table;
    return entry->actor != NULL && ITEM_KIND(entry->code) == ITEM_KIND_D;
}
CLEAN_AS(func_020828c0, ActorTable_IsUsedD)

static void clear(ActorEntry *entries, int count)
{
    for (int i = 0; i < count; i++) {
        entries[i].actor = NULL;
        entries[i].code = ITEM_CODE_NONE;
    }
}

/* func_02082b80 */
void ActorTable_ClearE(ActorTable *table, ActorEntry *entries, int count)
{
    (void) table;
    clear(entries, count);
}
CLEAN_AS(func_02082b80, ActorTable_ClearE)

/* func_020828e0 */
void ActorTable_ClearD(ActorTable *table, ActorEntry *entries, int count)
{
    (void) table;
    clear(entries, count);
}
CLEAN_AS(func_020828e0, ActorTable_ClearD)

/* func_02082ba0 */
void ActorTable_Init(ActorTable *table)
{
    ActorTable_ClearE(table, table->kind_e, ACTOR_TABLE_KIND_E_ENTRIES);
    ActorTable_ClearD(table, table->kind_d, ACTOR_TABLE_KIND_D_ENTRIES);
}
CLEAN_AS(func_02082ba0, ActorTable_Init)

/* Whether an entry is under `code`. QUIRK: an entry under a code of kind 3 or 4 is under every
 * variant of its item: only the codes' items are compared, and the code looked for is taken as
 * one of kind 3 or 4 whatever its kind. */
static BOOL entry_is_under(const ActorEntry *entry, const ItemCode *code)
{
    if (ItemCode_HasVariant(&entry->code)) {
        return ItemCode_VariantItem(&entry->code) == ItemCode_VariantItem(code);
    }
    return entry->code == *code;
}

static int find(const ActorEntry *entries, int count, const ItemCode *code)
{
    for (int i = 0; i < count; i++) {
        if (entry_is_under(&entries[i], code)) {
            return i;
        }
    }
    return -1;
}

/* func_02082afc: the first kind 0xe entry under `code`, or -1; looking for 0xfff1 finds a free
 * entry. */
int ActorTable_FindE(const ActorTable *table, const ItemCode *code)
{
    return find(table->kind_e, ACTOR_TABLE_KIND_E_ENTRIES, code);
}
CLEAN_AS(func_02082afc, ActorTable_FindE)

/* func_02082854: as ActorTable_FindE, among the kind 0xd entries. */
int ActorTable_FindD(const ActorTable *table, const ItemCode *code)
{
    return find(table->kind_d, ACTOR_TABLE_KIND_D_ENTRIES, code);
}
CLEAN_AS(func_02082854, ActorTable_FindD)

/* func_02082a84: frees the entry under `code`; FALSE when there is none. */
BOOL ActorTable_RemoveE(ActorTable *table, const ItemCode *code)
{
    int i = ActorTable_FindE(table, code);
    if (i < 0) {
        return FALSE;
    }
    table->kind_e[i].actor = NULL;
    table->kind_e[i].code = ITEM_CODE_NONE;
    return TRUE;
}
CLEAN_AS(func_02082a84, ActorTable_RemoveE)

/* func_020827dc */
BOOL ActorTable_RemoveD(ActorTable *table, const ItemCode *code)
{
    int i = ActorTable_FindD(table, code);
    if (i < 0) {
        return FALSE;
    }
    table->kind_d[i].actor = NULL;
    table->kind_d[i].code = ITEM_CODE_NONE;
    return TRUE;
}
CLEAN_AS(func_020827dc, ActorTable_RemoveD)

/* func_02082ab0: puts the actor in a free entry under `code`; FALSE when an entry is already
 * under it or none is free.
 * QUIRK: the kind of the code is not checked; an entry under a code of another kind is never
 * seen by ActorTable_GetE, ActorTable_SlotE or ActorTable_FindEAt. */
BOOL ActorTable_AddE(ActorTable *table, void *actor, const ItemCode *code)
{
    ItemCode none = ITEM_CODE_NONE;
    if (ActorTable_FindE(table, code) != -1) {
        return FALSE;
    }
    int i = ActorTable_FindE(table, &none);
    if (i < 0) {
        return FALSE;
    }
    table->kind_e[i].actor = actor;
    table->kind_e[i].code = *code;
    return TRUE;
}
CLEAN_AS(func_02082ab0, ActorTable_AddE)

/* func_02082808: as ActorTable_AddE, among the kind 0xd entries. */
BOOL ActorTable_AddD(ActorTable *table, void *actor, const ItemCode *code)
{
    ItemCode none = ITEM_CODE_NONE;
    if (ActorTable_FindD(table, code) != -1) {
        return FALSE;
    }
    int i = ActorTable_FindD(table, &none);
    if (i < 0) {
        return FALSE;
    }
    table->kind_d[i].actor = actor;
    table->kind_d[i].code = *code;
    return TRUE;
}
CLEAN_AS(func_02082808, ActorTable_AddD)

/* func_020829b8: the actor under a kind 0xe code, or null. */
void *ActorTable_GetE(const ActorTable *table, const ItemCode *code)
{
    if (ITEM_KIND(*code) != ITEM_KIND_E) {
        return NULL;
    }
    int i = ActorTable_FindE(table, code);
    return i >= 0 ? table->kind_e[i].actor : NULL;
}
CLEAN_AS(func_020829b8, ActorTable_GetE)

/* func_0208270c: the actor under a kind 0xd code, or null. */
void *ActorTable_GetD(const ActorTable *table, const ItemCode *code)
{
    if (ITEM_KIND(*code) != ITEM_KIND_D) {
        return NULL;
    }
    int i = ActorTable_FindD(table, code);
    return i >= 0 ? table->kind_d[i].actor : NULL;
}
CLEAN_AS(func_0208270c, ActorTable_GetD)

/* func_02082a44: the actor under the kind 0xe code with this index (its low 12 bits). */
void *ActorTable_GetEByIndex(const ActorTable *table, u16 index)
{
    ItemCode code = (ItemCode) (ITEM_KIND_E << 12 | (index & ITEM_INDEX_MASK));
    int i = ActorTable_FindE(table, &code);
    return i >= 0 ? table->kind_e[i].actor : NULL;
}
CLEAN_AS(func_02082a44, ActorTable_GetEByIndex)

/* func_02082798: the actor under the kind 0xd code with this index (its low 12 bits). */
void *ActorTable_GetDByIndex(const ActorTable *table, u16 index)
{
    ItemCode code = (ItemCode) (ITEM_KIND_D << 12 | (index & ITEM_INDEX_MASK));
    int i = ActorTable_FindD(table, &code);
    return i >= 0 ? table->kind_d[i].actor : NULL;
}
CLEAN_AS(func_02082798, ActorTable_GetDByIndex)

/* func_0208298c: the actor in kind 0xe entry `slot` (0-7), or null. */
void *ActorTable_SlotE(const ActorTable *table, int slot)
{
    if (!ActorTable_IsKindESlot((u32) slot)) {
        return NULL;
    }
    const ActorEntry *entry = &table->kind_e[slot];
    return ActorTable_IsUsedE(table, entry) ? entry->actor : NULL;
}
CLEAN_AS(func_0208298c, ActorTable_SlotE)

/* func_020826e0: the actor in kind 0xd entry `slot` (0-3), or null. */
void *ActorTable_SlotD(const ActorTable *table, int slot)
{
    if (slot < 0 || slot >= ACTOR_TABLE_KIND_D_ENTRIES) {
        return NULL;
    }
    const ActorEntry *entry = &table->kind_d[slot];
    return ActorTable_IsUsedD(table, entry) ? entry->actor : NULL;
}
CLEAN_AS(func_020826e0, ActorTable_SlotD)

/* The first actor of the kind 0xe entries (or the kind 0xd ones) standing on tile (x, z). */
static void *find_at(const ActorTable *table, BOOL kind_d, int x, int z)
{
    const ActorEntry *entries = kind_d ? table->kind_d : table->kind_e;
    int count = kind_d ? ACTOR_TABLE_KIND_D_ENTRIES : ACTOR_TABLE_KIND_E_ENTRIES;
    for (int i = 0; i < count; i++) {
        const ActorEntry *entry = &entries[i];
        if (kind_d ? ActorTable_IsUsedD(table, entry) : ActorTable_IsUsedE(table, entry)) {
            int tile_x;
            int tile_z;
            Position_Tile(&tile_x, &tile_z, (const Position *) ((const u8 *) entry->actor + ACTOR_POSITION_OFFSET));
            if (tile_x == x && tile_z == z) {
                return entry->actor;
            }
        }
    }
    return NULL;
}

/* func_020829ec: the first kind 0xe actor standing on tile (x, z), or null. */
void *ActorTable_FindEAt(const ActorTable *table, int x, int z)
{
    return find_at(table, FALSE, x, z);
}
CLEAN_AS(func_020829ec, ActorTable_FindEAt)

/* func_02082740: the first kind 0xd actor standing on tile (x, z), or null. */
void *ActorTable_FindDAt(const ActorTable *table, int x, int z)
{
    return find_at(table, TRUE, x, z);
}
CLEAN_AS(func_02082740, ActorTable_FindDAt)

/* func_020826d0 */
void Actors_Init(void)
{
    ActorTable_Init(&data_021d1d4c);
}
CLEAN_AS(func_020826d0, Actors_Init)

/* func_02082544. QUIRK: whether there was an entry is dropped, unlike Actors_RemoveE. */
void Actors_RemoveD(const ItemCode *code)
{
    (void) ActorTable_RemoveD(&data_021d1d4c, code);
}
CLEAN_AS(func_02082544, Actors_RemoveD)

/* func_02082554 */
BOOL Actors_AddD(void *actor, const ItemCode *code)
{
    return ActorTable_AddD(&data_021d1d4c, actor, code);
}
CLEAN_AS(func_02082554, Actors_AddD)

/* func_02082568 */
BOOL Actors_RemoveE(const ItemCode *code)
{
    return ActorTable_RemoveE(&data_021d1d4c, code);
}
CLEAN_AS(func_02082568, Actors_RemoveE)

/* func_02082578 */
BOOL Actors_AddE(void *actor, const ItemCode *code)
{
    return ActorTable_AddE(&data_021d1d4c, actor, code);
}
CLEAN_AS(func_02082578, Actors_AddE)

/* func_020825c8 */
void *Actors_GetD(const ItemCode *code)
{
    return ActorTable_GetD(&data_021d1d4c, code);
}
CLEAN_AS(func_020825c8, Actors_GetD)

/* func_020825d8 */
void *Actors_GetE(const ItemCode *code)
{
    return ActorTable_GetE(&data_021d1d4c, code);
}
CLEAN_AS(func_020825d8, Actors_GetE)

/* func_020825e8: the actor under a code of kind 0xe or 0xd, or null. */
void *Actors_Get(const ItemCode *code)
{
    switch (ITEM_KIND(*code)) {
        case ITEM_KIND_E:
            return Actors_GetE(code);
        case ITEM_KIND_D:
            return Actors_GetD(code);
        default:
            return NULL;
    }
}
CLEAN_AS(func_020825e8, Actors_Get)

/* func_02082644: QUIRK: only the low 12 bits of `index` count. */
void *Actors_GetDByIndex(int index)
{
    return ActorTable_GetDByIndex(&data_021d1d4c, (u16) index);
}
CLEAN_AS(func_02082644, Actors_GetDByIndex)

/* func_02082654: QUIRK: only the low 12 bits of `index` count. */
void *Actors_GetEByIndex(int index)
{
    return ActorTable_GetEByIndex(&data_021d1d4c, (u16) index);
}
CLEAN_AS(func_02082654, Actors_GetEByIndex)

/* func_02082618: group 2 is the kind 0xe codes, group 3 the kind 0xd ones; other groups give
 * null. */
void *Actors_GetByIndex(int group, int index)
{
    switch (group) {
        case 2:
            return Actors_GetEByIndex(index);
        case 3:
            return Actors_GetDByIndex(index);
        default:
            return NULL;
    }
}
CLEAN_AS(func_02082618, Actors_GetByIndex)

/* func_0208259c: the kind 0xe actors are searched first. */
void *Actors_FindAt(int x, int z)
{
    void *actor = ActorTable_FindEAt(&data_021d1d4c, x, z);
    if (actor != NULL) {
        return actor;
    }
    return ActorTable_FindDAt(&data_021d1d4c, x, z);
}
CLEAN_AS(func_0208259c, Actors_FindAt)

/* func_020826cc */
int Actors_SlotCount(void)
{
    return ACTOR_TABLE_KIND_E_ENTRIES + ACTOR_TABLE_KIND_D_ENTRIES;
}
CLEAN_AS(func_020826cc, Actors_SlotCount)

/* func_02082664: the actor in entry `slot` of the list of twelve, or null. */
void *Actors_Slot(int slot)
{
    if (slot < 0) {
        return NULL;
    }
    if (ActorTable_IsKindESlot((u32) slot)) {
        return ActorTable_SlotE(&data_021d1d4c, slot);
    }
    if (slot >= Actors_SlotCount()) {
        return NULL;
    }
    return ActorTable_SlotD(&data_021d1d4c, slot - ACTOR_TABLE_KIND_E_ENTRIES);
}
CLEAN_AS(func_02082664, Actors_Slot)

/* func_020826a8: QUIRK: the slot is checked here and again in ActorTable_SlotE. */
void *Actors_SlotE(int slot)
{
    if (!ActorTable_IsKindESlot((u32) slot)) {
        return NULL;
    }
    return ActorTable_SlotE(&data_021d1d4c, slot);
}
CLEAN_AS(func_020826a8, Actors_SlotE)

static_assert(sizeof(ActorEntry) == 8, "ActorEntry layout");
static_assert(offsetof(ActorTable, kind_d) == 0x40 && sizeof(ActorTable) == 0x60, "ActorTable layout");
static_assert(sizeof(Position) == 12, "Position layout");
