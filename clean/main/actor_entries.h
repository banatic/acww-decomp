/* The entries of the table of actors by item code (actor_table.h): their constructors and
 * destructors, the table's destructor, and a random pick among the actors of kind 0xe.
 *
 * The game's table (data_021d1d4c) is built when the game starts: its eight kind 0xe entries
 * by ActorEntries_ConstructE, its four kind 0xd entries by ActorEntries_ConstructD. */
#ifndef CLEAN_MAIN_ACTOR_ENTRIES_H
#define CLEAN_MAIN_ACTOR_ENTRIES_H

#include "actor_table.h"
#include "types.h"

/* What ActorEntries_PickE asks each actor: its vtable entry at 0xa8. */
typedef struct ActorEntriesActor ActorEntriesActor;

typedef struct ActorEntriesVtable {
    u8 unknown_00[0xa8];
    int (*vfunc_a8)(ActorEntriesActor *actor); /* whether the actor may be picked */
} ActorEntriesVtable;

struct ActorEntriesActor {
    const ActorEntriesVtable *vtable;
};

void *ActorEntries_PickGameE(int *index);
void *ActorEntries_PickE(ActorTable *table, int *index);
ActorTable *ActorEntries_DestructTable(ActorTable *table);
void ActorEntries_DestructD(ActorEntry *entry);
void ActorEntries_ConstructD(ActorEntry *entry);
void ActorEntries_DestructE(ActorEntry *entry);
void ActorEntries_ConstructE(ActorEntry *entry);

#endif
