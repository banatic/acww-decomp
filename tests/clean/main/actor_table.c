#include "../../../clean/main/actor_table.h"
#include "diffcheck.h"

#include <stddef.h>

#define TABLE DIFF_SCRATCH
#define GAME_TABLE 0x021d1d4cu
#define KEY (DIFF_SCRATCH + 0x100)
#define OUT_X (DIFF_SCRATCH + 0x110)
#define OUT_Z (DIFF_SCRATCH + 0x114)
#define POSITION (DIFF_SCRATCH + 0x120)
/* The actors: one for each entry and a few more, each with its position at 0x5c. */
#define ACTORS (DIFF_SCRATCH + 0x1000)
#define ACTOR_SIZE 0x100
#define ACTOR_COUNT 16

/* Tiles near each other so that actors share them and the searches find them. */
#define TILES 6

static uint32_t actor(int i)
{
    return ACTORS + (uint32_t) i * ACTOR_SIZE;
}

static void place_actors(DiffRng *rng)
{
    for (int i = 0; i < ACTOR_COUNT; i++) {
        Position *p = (Position *) (uintptr_t) (actor(i) + ACTOR_POSITION_OFFSET);
        p->x = diff_range(rng, 0, TILES - 1) * 0x2000 + diff_range(rng, 0, 0x1fff);
        p->y = diff_range(rng, 0, 0x8000);
        p->z = diff_range(rng, 0, TILES - 1) * 0x2000 + diff_range(rng, 0, 0x1fff);
    }
}

/* The code an entry of this kind holds: a few indexes so that lookups hit, now and then a code
 * of kind 3 or 4 (compared by its item) or of the other kind. */
static ItemCode entry_code(DiffRng *rng, int kind)
{
    switch (diff_range(rng, 0, 11)) {
        case 0:
            return (ItemCode) diff_range(rng, 0x3000, 0x3010);
        case 1:
            return (ItemCode) ((kind == 0xe ? 0xd : 0xe) << 12 | diff_range(rng, 0, 7));
        default:
            return (ItemCode) (kind << 12 | diff_range(rng, 0, 7));
    }
}

static void fill_entries(DiffRng *rng, ActorEntry *entries, int count, int kind, int first_actor)
{
    for (int i = 0; i < count; i++) {
        ActorEntry *e = &entries[i];
        e->unused = 0;
        int choice = diff_range(rng, 0, 9);
        if (choice < 4) {
            e->actor = NULL;
            e->code = ITEM_CODE_NONE;
            continue;
        }
        e->code = entry_code(rng, kind);
        /* rarely an entry with a code and no actor */
        e->actor = choice == 4 ? NULL : (void *) (uintptr_t) actor(first_actor + i);
        /* the game adds a code once: keep the first entry under it */
        for (int j = 0; j < i; j++) {
            if (entries[j].code == e->code) {
                e->actor = NULL;
                e->code = ITEM_CODE_NONE;
                break;
            }
        }
    }
}

static ActorTable *build_table(DiffRng *rng, uint32_t address)
{
    ActorTable *table = (ActorTable *) (uintptr_t) address;
    place_actors(rng);
    fill_entries(rng, table->kind_e, ACTOR_TABLE_KIND_E_ENTRIES, 0xe, 0);
    fill_entries(rng, table->kind_d, ACTOR_TABLE_KIND_D_ENTRIES, 0xd, ACTOR_TABLE_KIND_E_ENTRIES);
    return table;
}

/* A code to look for: one in the table, another variant of one, a code of kind 0xe or 0xd
 * that may be missing, or "nothing". */
static ItemCode random_key(DiffRng *rng, const ActorTable *table)
{
    switch (diff_range(rng, 0, 5)) {
        case 0:
            return table->kind_e[diff_range(rng, 0, ACTOR_TABLE_KIND_E_ENTRIES - 1)].code;
        case 1:
            return table->kind_d[diff_range(rng, 0, ACTOR_TABLE_KIND_D_ENTRIES - 1)].code;
        case 2:
            return (ItemCode) diff_range(rng, 0x3000, 0x3010);
        case 3:
            return (ItemCode) (0xe000 | diff_range(rng, 0, 9));
        case 4:
            return (ItemCode) (0xd000 | diff_range(rng, 0, 9));
        default:
            return ITEM_CODE_NONE;
    }
}

static void put_key(DiffRng *rng, const ActorTable *table)
{
    *(ItemCode *) (uintptr_t) KEY = random_key(rng, table);
}

static void table_only(DiffRng *rng, uint32_t args[4])
{
    build_table(rng, TABLE);
    args[0] = TABLE;
}

static void table_entry(DiffRng *rng, uint32_t args[4])
{
    ActorTable *table = build_table(rng, TABLE);
    int i = diff_range(rng, 0, ACTOR_TABLE_KIND_E_ENTRIES + ACTOR_TABLE_KIND_D_ENTRIES - 1);
    args[0] = TABLE;
    args[1] = (uint32_t) (uintptr_t) (i < ACTOR_TABLE_KIND_E_ENTRIES ? &table->kind_e[i]
                                                                     : &table->kind_d[i - ACTOR_TABLE_KIND_E_ENTRIES]);
}

/* The calls func_02082ba0 makes: all eight kind 0xe entries, all four kind 0xd ones; fewer
 * now and then. */
static void table_e_entries(DiffRng *rng, uint32_t args[4])
{
    ActorTable *table = build_table(rng, TABLE);
    args[0] = TABLE;
    args[1] = (uint32_t) (uintptr_t) table->kind_e;
    args[2] = (uint32_t) (diff_range(rng, 0, 1) ? ACTOR_TABLE_KIND_E_ENTRIES : diff_range(rng, 0, 8));
}

static void table_d_entries(DiffRng *rng, uint32_t args[4])
{
    ActorTable *table = build_table(rng, TABLE);
    args[0] = TABLE;
    args[1] = (uint32_t) (uintptr_t) table->kind_d;
    args[2] = (uint32_t) (diff_range(rng, 0, 1) ? ACTOR_TABLE_KIND_D_ENTRIES : diff_range(rng, 0, 4));
}

static void table_key(DiffRng *rng, uint32_t args[4])
{
    ActorTable *table = build_table(rng, TABLE);
    put_key(rng, table);
    args[0] = TABLE;
    args[1] = KEY;
}

static void table_actor_key(DiffRng *rng, uint32_t args[4])
{
    ActorTable *table = build_table(rng, TABLE);
    put_key(rng, table);
    args[0] = TABLE;
    args[1] = actor(diff_range(rng, 0, ACTOR_COUNT - 1));
    args[2] = KEY;
}

/* An index, usually of a code that may be in the table, now and then a whole code. */
static uint32_t random_index(DiffRng *rng)
{
    return (uint32_t) (diff_range(rng, 0, 4) == 0 ? diff_range(rng, 0, 0xffff) : diff_range(rng, 0, 9));
}

static void table_index(DiffRng *rng, uint32_t args[4])
{
    build_table(rng, TABLE);
    args[0] = TABLE;
    args[1] = random_index(rng);
}

static void table_slot(DiffRng *rng, uint32_t args[4])
{
    build_table(rng, TABLE);
    args[0] = TABLE;
    args[1] = (uint32_t) diff_range(rng, -2, 9);
}

static void table_tile(DiffRng *rng, uint32_t args[4])
{
    build_table(rng, TABLE);
    args[0] = TABLE;
    args[1] = (uint32_t) diff_range(rng, -1, TILES);
    args[2] = (uint32_t) diff_range(rng, -1, TILES);
}

static void a_position(DiffRng *rng, uint32_t args[4])
{
    Position *p = (Position *) (uintptr_t) POSITION;
    p->x = diff_range(rng, 0, 0x100000);
    p->y = diff_range(rng, -0x8000, 0x8000);
    p->z = diff_range(rng, 0, 0x100000);
    args[0] = OUT_X;
    args[1] = OUT_Z;
    args[2] = POSITION;
}

static void a_slot_number(DiffRng *rng, uint32_t args[4])
{
    args[0] = (uint32_t) diff_range(rng, -3, 12);
}

/* The game's table, as the functions without a table argument use it. */
static void game_table(DiffRng *rng, uint32_t args[4])
{
    (void) args;
    build_table(rng, GAME_TABLE);
}

static void game_key(DiffRng *rng, uint32_t args[4])
{
    put_key(rng, build_table(rng, GAME_TABLE));
    args[0] = KEY;
}

static void game_actor_key(DiffRng *rng, uint32_t args[4])
{
    put_key(rng, build_table(rng, GAME_TABLE));
    args[0] = actor(diff_range(rng, 0, ACTOR_COUNT - 1));
    args[1] = KEY;
}

static void game_index(DiffRng *rng, uint32_t args[4])
{
    build_table(rng, GAME_TABLE);
    args[0] = random_index(rng);
}

static void game_group_index(DiffRng *rng, uint32_t args[4])
{
    build_table(rng, GAME_TABLE);
    args[0] = (uint32_t) diff_range(rng, 0, 4);
    args[1] = random_index(rng);
}

static void game_tile(DiffRng *rng, uint32_t args[4])
{
    build_table(rng, GAME_TABLE);
    args[0] = (uint32_t) diff_range(rng, -1, TILES);
    args[1] = (uint32_t) diff_range(rng, -1, TILES);
}

static void game_slot(DiffRng *rng, uint32_t args[4])
{
    build_table(rng, GAME_TABLE);
    args[0] = (uint32_t) diff_range(rng, -2, 13);
}

#define TABLE_ARG ((ActorTable *) (uintptr_t) args[0])
#define PTR(i) ((void *) (uintptr_t) args[i])
#define RESULT(p) ((uint32_t) (uintptr_t) (p))

static uint32_t position_tile(const uint32_t args[4])
{
    Position_Tile((int *) PTR(0), (int *) PTR(1), (const Position *) PTR(2));
    return 0;
}

static uint32_t is_kind_e_slot(const uint32_t args[4])
{
    return (uint32_t) ActorTable_IsKindESlot(args[0]);
}

static uint32_t is_used_e(const uint32_t args[4])
{
    return (uint32_t) ActorTable_IsUsedE(TABLE_ARG, (const ActorEntry *) PTR(1));
}

static uint32_t is_used_d(const uint32_t args[4])
{
    return (uint32_t) ActorTable_IsUsedD(TABLE_ARG, (const ActorEntry *) PTR(1));
}

static uint32_t clear_e(const uint32_t args[4])
{
    ActorTable_ClearE(TABLE_ARG, (ActorEntry *) PTR(1), (int) args[2]);
    return 0;
}

static uint32_t clear_d(const uint32_t args[4])
{
    ActorTable_ClearD(TABLE_ARG, (ActorEntry *) PTR(1), (int) args[2]);
    return 0;
}

static uint32_t init(const uint32_t args[4])
{
    ActorTable_Init(TABLE_ARG);
    return 0;
}

static uint32_t find_e(const uint32_t args[4])
{
    return (uint32_t) ActorTable_FindE(TABLE_ARG, (const ItemCode *) PTR(1));
}

static uint32_t find_d(const uint32_t args[4])
{
    return (uint32_t) ActorTable_FindD(TABLE_ARG, (const ItemCode *) PTR(1));
}

static uint32_t remove_e(const uint32_t args[4])
{
    return (uint32_t) ActorTable_RemoveE(TABLE_ARG, (const ItemCode *) PTR(1));
}

static uint32_t remove_d(const uint32_t args[4])
{
    return (uint32_t) ActorTable_RemoveD(TABLE_ARG, (const ItemCode *) PTR(1));
}

static uint32_t add_e(const uint32_t args[4])
{
    return (uint32_t) ActorTable_AddE(TABLE_ARG, PTR(1), (const ItemCode *) PTR(2));
}

static uint32_t add_d(const uint32_t args[4])
{
    return (uint32_t) ActorTable_AddD(TABLE_ARG, PTR(1), (const ItemCode *) PTR(2));
}

static uint32_t get_e(const uint32_t args[4])
{
    return RESULT(ActorTable_GetE(TABLE_ARG, (const ItemCode *) PTR(1)));
}

static uint32_t get_d(const uint32_t args[4])
{
    return RESULT(ActorTable_GetD(TABLE_ARG, (const ItemCode *) PTR(1)));
}

static uint32_t get_e_by_index(const uint32_t args[4])
{
    return RESULT(ActorTable_GetEByIndex(TABLE_ARG, args[1]));
}

static uint32_t get_d_by_index(const uint32_t args[4])
{
    return RESULT(ActorTable_GetDByIndex(TABLE_ARG, args[1]));
}

static uint32_t slot_e(const uint32_t args[4])
{
    return RESULT(ActorTable_SlotE(TABLE_ARG, (int) args[1]));
}

static uint32_t slot_d(const uint32_t args[4])
{
    return RESULT(ActorTable_SlotD(TABLE_ARG, (int) args[1]));
}

static uint32_t find_e_at(const uint32_t args[4])
{
    return RESULT(ActorTable_FindEAt(TABLE_ARG, (int) args[1], (int) args[2]));
}

static uint32_t find_d_at(const uint32_t args[4])
{
    return RESULT(ActorTable_FindDAt(TABLE_ARG, (int) args[1], (int) args[2]));
}

static uint32_t actors_init(const uint32_t args[4])
{
    (void) args;
    Actors_Init();
    return 0;
}

static uint32_t actors_remove_d(const uint32_t args[4])
{
    Actors_RemoveD((const ItemCode *) PTR(0));
    return 0;
}

static uint32_t actors_add_d(const uint32_t args[4])
{
    return (uint32_t) Actors_AddD(PTR(0), (const ItemCode *) PTR(1));
}

static uint32_t actors_remove_e(const uint32_t args[4])
{
    return (uint32_t) Actors_RemoveE((const ItemCode *) PTR(0));
}

static uint32_t actors_add_e(const uint32_t args[4])
{
    return (uint32_t) Actors_AddE(PTR(0), (const ItemCode *) PTR(1));
}

static uint32_t actors_get_d(const uint32_t args[4])
{
    return RESULT(Actors_GetD((const ItemCode *) PTR(0)));
}

static uint32_t actors_get_e(const uint32_t args[4])
{
    return RESULT(Actors_GetE((const ItemCode *) PTR(0)));
}

static uint32_t actors_get(const uint32_t args[4])
{
    return RESULT(Actors_Get((const ItemCode *) PTR(0)));
}

static uint32_t actors_get_d_by_index(const uint32_t args[4])
{
    return RESULT(Actors_GetDByIndex(args[0]));
}

static uint32_t actors_get_e_by_index(const uint32_t args[4])
{
    return RESULT(Actors_GetEByIndex(args[0]));
}

static uint32_t actors_get_by_index(const uint32_t args[4])
{
    return RESULT(Actors_GetByIndex((int) args[0], args[1]));
}

static uint32_t actors_find_at(const uint32_t args[4])
{
    return RESULT(Actors_FindAt((int) args[0], (int) args[1]));
}

static uint32_t actors_slot_count(const uint32_t args[4])
{
    (void) args;
    return (uint32_t) Actors_SlotCount();
}

static uint32_t actors_slot(const uint32_t args[4])
{
    return RESULT(Actors_Slot((int) args[0]));
}

static uint32_t actors_slot_e(const uint32_t args[4])
{
    return RESULT(Actors_SlotE((int) args[0]));
}

DIFF_CHECK(func_0204f818, "main", 0x0204f818 | 1, 0, 0, a_position, position_tile)
DIFF_CHECK(func_0207cf74, "main", 0x0207cf74 | 1, 32, 0, a_slot_number, is_kind_e_slot)
DIFF_CHECK(func_02082b60, "main", 0x02082b60 | 1, 32, 0, table_entry, is_used_e)
DIFF_CHECK(func_020828c0, "main", 0x020828c0 | 1, 32, 0, table_entry, is_used_d)
DIFF_CHECK(func_02082b80, "main", 0x02082b80 | 1, 0, 0, table_e_entries, clear_e)
DIFF_CHECK(func_020828e0, "main", 0x020828e0 | 1, 0, 0, table_d_entries, clear_d)
DIFF_CHECK(func_02082ba0, "main", 0x02082ba0 | 1, 0, 1, table_only, init)
DIFF_CHECK(func_02082afc, "main", 0x02082afc | 1, 32, 1, table_key, find_e)
DIFF_CHECK(func_02082854, "main", 0x02082854 | 1, 32, 1, table_key, find_d)
DIFF_CHECK(func_02082a84, "main", 0x02082a84 | 1, 32, 1, table_key, remove_e)
DIFF_CHECK(func_020827dc, "main", 0x020827dc | 1, 32, 1, table_key, remove_d)
DIFF_CHECK(func_02082ab0, "main", 0x02082ab0 | 1, 32, 1, table_actor_key, add_e)
DIFF_CHECK(func_02082808, "main", 0x02082808 | 1, 32, 1, table_actor_key, add_d)
DIFF_CHECK(func_020829b8, "main", 0x020829b8 | 1, 32, 1, table_key, get_e)
DIFF_CHECK(func_0208270c, "main", 0x0208270c | 1, 32, 1, table_key, get_d)
DIFF_CHECK(func_02082a44, "main", 0x02082a44 | 1, 32, 1, table_index, get_e_by_index)
DIFF_CHECK(func_02082798, "main", 0x02082798 | 1, 32, 1, table_index, get_d_by_index)
DIFF_CHECK(func_0208298c, "main", 0x0208298c | 1, 32, 1, table_slot, slot_e)
DIFF_CHECK(func_020826e0, "main", 0x020826e0 | 1, 32, 1, table_slot, slot_d)
DIFF_CHECK(func_020829ec, "main", 0x020829ec | 1, 32, 1, table_tile, find_e_at)
DIFF_CHECK(func_02082740, "main", 0x02082740 | 1, 32, 1, table_tile, find_d_at)
DIFF_CHECK(func_020826d0, "main", 0x020826d0 | 1, 0, 1, game_table, actors_init)
DIFF_CHECK(func_02082544, "main", 0x02082544 | 1, 0, 1, game_key, actors_remove_d)
DIFF_CHECK(func_02082554, "main", 0x02082554 | 1, 32, 1, game_actor_key, actors_add_d)
DIFF_CHECK(func_02082568, "main", 0x02082568 | 1, 32, 1, game_key, actors_remove_e)
DIFF_CHECK(func_02082578, "main", 0x02082578 | 1, 32, 1, game_actor_key, actors_add_e)
DIFF_CHECK(func_020825c8, "main", 0x020825c8 | 1, 32, 1, game_key, actors_get_d)
DIFF_CHECK(func_020825d8, "main", 0x020825d8 | 1, 32, 1, game_key, actors_get_e)
DIFF_CHECK(func_020825e8, "main", 0x020825e8 | 1, 32, 1, game_key, actors_get)
DIFF_CHECK(func_02082644, "main", 0x02082644 | 1, 32, 1, game_index, actors_get_d_by_index)
DIFF_CHECK(func_02082654, "main", 0x02082654 | 1, 32, 1, game_index, actors_get_e_by_index)
DIFF_CHECK(func_02082618, "main", 0x02082618 | 1, 32, 1, game_group_index, actors_get_by_index)
DIFF_CHECK(func_0208259c, "main", 0x0208259c | 1, 32, 1, game_tile, actors_find_at)
DIFF_CHECK(func_020826cc, "main", 0x020826cc | 1, 32, 0, game_table, actors_slot_count)
DIFF_CHECK(func_02082664, "main", 0x02082664 | 1, 32, 1, game_slot, actors_slot)
DIFF_CHECK(func_020826a8, "main", 0x020826a8 | 1, 32, 1, game_slot, actors_slot_e)
