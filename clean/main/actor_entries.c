/* The entries of the table of actors by item code (actor_entries.h). */
#include "actor_entries.h"

#include "clean.h"

static_assert(sizeof(ActorEntry) == 0x08, "entry size");
static_assert(offsetof(ActorEntry, code) == 0x04, "entry code");
static_assert(offsetof(ActorTable, kind_d) == 0x40, "kind 0xd entries");
static_assert(offsetof(ActorEntriesVtable, vfunc_a8) == 0xa8, "vtable entry 0xa8");

#define ACTOR_ENTRIES_NO_CODE 0xfff1 /* a free entry's code */

extern ActorTable data_021d1d4c; /* the game's table */

/* Whether a kind 0xe entry of the table holds an actor (ActorTable_IsUsedE). */
extern int func_02082b60(const ActorTable *table, const ActorEntry *entry);
extern u32 func_020644cc(int bound); /* a random number below `bound` */
extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));
/* The entry destructors, as the game hands them to __cxa_vec_cleanup. */
extern void func_02082bec(void *entry);
extern void func_02082bfc(void *entry);

/* Whether entry `entry` holds an actor that may be picked. */
static int actor_entries_pickable(ActorTable *table, ActorEntry *entry)
{
    if (func_02082b60(table, entry) == 0) {
        return 0;
    }
    ActorEntriesActor *actor = entry->actor;
    return actor->vtable->vfunc_a8(actor) != 0;
}

/* func_0208258c: ActorEntries_PickE on the game's table. */
void *ActorEntries_PickGameE(int *index)
{
    return ActorEntries_PickE(&data_021d1d4c, index);
}
CLEAN_AS(func_0208258c, ActorEntries_PickGameE)

/* func_02082904: a random one of the actors of the kind 0xe entries that may be picked (their
 * vtable entry 0xa8 says so), its entry's number in `*index` when `index` is not null; null
 * (and `*index` untouched) when none may.
 * QUIRK: each actor is asked twice, once while counting and again while picking; an actor that
 * answers otherwise the second time shifts the pick, and none is picked when the count ran
 * out. */
void *ActorEntries_PickE(ActorTable *table, int *index)
{
    int count = 0;
    for (int i = 0; i < ACTOR_TABLE_KIND_E_ENTRIES; i++) {
        if (actor_entries_pickable(table, &table->kind_e[i])) {
            count++;
        }
    }
    if (count <= 0) {
        return NULL;
    }
    int left = (int) func_020644cc(count);
    for (int i = 0; i < ACTOR_TABLE_KIND_E_ENTRIES; i++) {
        ActorEntry *entry = &table->kind_e[i];
        if (actor_entries_pickable(table, entry)) {
            if (left == 0) {
                if (index != NULL) {
                    *index = i;
                }
                return entry->actor;
            }
            left--;
        }
    }
    return NULL;
}
CLEAN_AS(func_02082904, ActorEntries_PickE)

/* func_02082bc0: the table's destructor: the four kind 0xd entries, then the eight kind 0xe
 * entries, each from its last to its first (the game's own entry destructors). */
ActorTable *ActorEntries_DestructTable(ActorTable *table)
{
    __cxa_vec_cleanup(table->kind_d, ACTOR_TABLE_KIND_D_ENTRIES, sizeof(ActorEntry), func_02082bec);
    __cxa_vec_cleanup(table->kind_e, ACTOR_TABLE_KIND_E_ENTRIES, sizeof(ActorEntry), func_02082bfc);
    return table;
}
CLEAN_AS(func_02082bc0, ActorEntries_DestructTable)

/* func_02082bec: a kind 0xd entry's destructor: nothing to do. */
void ActorEntries_DestructD(ActorEntry *entry)
{
    (void) entry;
}
CLEAN_AS(func_02082bec, ActorEntries_DestructD)

/* func_02082bf0: a kind 0xd entry's constructor: no code. The actor is left as it is. */
void ActorEntries_ConstructD(ActorEntry *entry)
{
    entry->code = ACTOR_ENTRIES_NO_CODE;
}
CLEAN_AS(func_02082bf0, ActorEntries_ConstructD)

/* func_02082bfc: a kind 0xe entry's destructor: nothing to do. */
void ActorEntries_DestructE(ActorEntry *entry)
{
    (void) entry;
}
CLEAN_AS(func_02082bfc, ActorEntries_DestructE)

/* func_02082c00: a kind 0xe entry's constructor: no code. The actor is left as it is. */
void ActorEntries_ConstructE(ActorEntry *entry)
{
    entry->code = ACTOR_ENTRIES_NO_CODE;
}
CLEAN_AS(func_02082c00, ActorEntries_ConstructE)
