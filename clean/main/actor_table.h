/* The table of actors by item code: the game keeps one (at 0x021d1d4c, cleared by
 * func_020b6ae0 through func_020826d0) that maps the item code of an actor to the
 * actor. An actor adds itself under the code at 0xea in it (func_0202e1fc) and removes itself
 * the same way (func_0202e1dc, func_0202ec38).
 *
 * There are eight entries for codes of kind 0xe and four for codes of kind 0xd; a free entry
 * holds a null actor and the code 0xfff1. The functions on the table take it as their first
 * argument; the ones without it act on the game's table. The entries are also numbered as one
 * list of twelve: 0-7 the kind 0xe entries, 8-11 the kind 0xd ones. */
#ifndef CLEAN_MAIN_ACTOR_TABLE_H
#define CLEAN_MAIN_ACTOR_TABLE_H

#include "item_code.h"
#include "types.h"

#define ACTOR_TABLE_KIND_E_ENTRIES 8
#define ACTOR_TABLE_KIND_D_ENTRIES 4

typedef struct ActorEntry {
    void *actor;
    ItemCode code;
    u16 unused;
} ActorEntry;

typedef struct ActorTable {
    ActorEntry kind_e[ACTOR_TABLE_KIND_E_ENTRIES];
    ActorEntry kind_d[ACTOR_TABLE_KIND_D_ENTRIES];
} ActorTable;

/* What func_0204f818 reads: an actor's position, at 0x5c in it. */
typedef struct Position {
    fx32 x;
    fx32 y;
    fx32 z;
} Position;

#define ACTOR_POSITION_OFFSET 0x5c

/* func_0204f818 */
void Position_Tile(int *x, int *z, const Position *position);
/* func_0207cf74 */
BOOL ActorTable_IsKindESlot(u32 slot);

/* func_02082b60 */
BOOL ActorTable_IsUsedE(const ActorTable *table, const ActorEntry *entry);
/* func_020828c0 */
BOOL ActorTable_IsUsedD(const ActorTable *table, const ActorEntry *entry);
/* func_02082b80 */
void ActorTable_ClearE(ActorTable *table, ActorEntry *entries, int count);
/* func_020828e0 */
void ActorTable_ClearD(ActorTable *table, ActorEntry *entries, int count);
/* func_02082ba0 */
void ActorTable_Init(ActorTable *table);
/* func_02082afc */
int ActorTable_FindE(const ActorTable *table, const ItemCode *code);
/* func_02082854 */
int ActorTable_FindD(const ActorTable *table, const ItemCode *code);
/* func_02082a84 */
BOOL ActorTable_RemoveE(ActorTable *table, const ItemCode *code);
/* func_020827dc */
BOOL ActorTable_RemoveD(ActorTable *table, const ItemCode *code);
/* func_02082ab0 */
BOOL ActorTable_AddE(ActorTable *table, void *actor, const ItemCode *code);
/* func_02082808 */
BOOL ActorTable_AddD(ActorTable *table, void *actor, const ItemCode *code);
/* func_020829b8 */
void *ActorTable_GetE(const ActorTable *table, const ItemCode *code);
/* func_0208270c */
void *ActorTable_GetD(const ActorTable *table, const ItemCode *code);
/* func_02082a44 */
void *ActorTable_GetEByIndex(const ActorTable *table, u16 index);
/* func_02082798 */
void *ActorTable_GetDByIndex(const ActorTable *table, u16 index);
/* func_0208298c */
void *ActorTable_SlotE(const ActorTable *table, int slot);
/* func_020826e0 */
void *ActorTable_SlotD(const ActorTable *table, int slot);
/* func_020829ec */
void *ActorTable_FindEAt(const ActorTable *table, int x, int z);
/* func_02082740 */
void *ActorTable_FindDAt(const ActorTable *table, int x, int z);

/* The game's table. */
/* func_020826d0 */
void Actors_Init(void);
/* func_02082544 */
void Actors_RemoveD(const ItemCode *code);
/* func_02082554 */
BOOL Actors_AddD(void *actor, const ItemCode *code);
/* func_02082568 */
BOOL Actors_RemoveE(const ItemCode *code);
/* func_02082578 */
BOOL Actors_AddE(void *actor, const ItemCode *code);
/* func_020825c8 */
void *Actors_GetD(const ItemCode *code);
/* func_020825d8 */
void *Actors_GetE(const ItemCode *code);
/* func_020825e8 */
void *Actors_Get(const ItemCode *code);
/* func_02082644 */
void *Actors_GetDByIndex(int index);
/* func_02082654 */
void *Actors_GetEByIndex(int index);
/* func_02082618 */
void *Actors_GetByIndex(int group, int index);
/* func_0208259c */
void *Actors_FindAt(int x, int z);
/* func_020826cc */
int Actors_SlotCount(void);
/* func_02082664 */
void *Actors_Slot(int slot);
/* func_020826a8 */
void *Actors_SlotE(int slot);

#endif
