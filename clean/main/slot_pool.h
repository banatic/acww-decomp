/* Three of the game's slot pools (SlotPool, pool_link.h), each of five entries that start with
 * their "taken" byte:
 *
 *   data_021d1f04  vtable data_020e1b00  0x6c-byte entries: a held item at 4 (held_item_link.h)
 *   data_021d1e34  vtable data_020e1b38  2-byte entries: a part number at 1
 *   data_021d1e0c  vtable data_020e1a90  2-byte entries: an animation set number at 1
 *
 * They derive from the slot pool base class (vtable data_020e1b70: func_02083ca8 constructs it
 * with its number of entries, func_02083c78 destroys it, func_02083c30 gives an entry back,
 * func_02083cb8 and func_02083cb4 construct and destroy the base part of an entry). Taking entry
 * `index` (vtable entry 2) sets it up with the number 4 + `index`: the item, part or animation
 * set it then stands for (func_0205ec50, func_0205db4c, func_0205d8c4).
 *
 * QUIRK: the functions that read or set up an entry check `index` against the pool they are
 * given but then use the game's own pool, found through its function; they are only ever given
 * that pool. */
#ifndef CLEAN_MAIN_SLOT_POOL_H
#define CLEAN_MAIN_SLOT_POOL_H

#include "pool_link.h"
#include "types.h"

#define SLOT_POOL_ENTRIES 5
#define SLOT_POOL_FIRST_NUMBER 4 /* the number entry 0 stands for */
#define SLOT_POOL_NO_ITEM 0xfff1 /* the item code an item entry is taken with */

typedef struct SlotPoolItemEntry {
    u8 taken;
    u8 unused_01[3];
    u8 item[0x68]; /* 0x04: the held item (HeldItem, held_item_link.h) */
} SlotPoolItemEntry;

typedef struct SlotPoolItems {
    SlotPool base;
    SlotPoolItemEntry entries[SLOT_POOL_ENTRIES]; /* 0x08 */
} SlotPoolItems;

typedef struct SlotPoolByteEntry {
    u8 taken;
    u8 number; /* 0x01: the part or animation set */
} SlotPoolByteEntry;

typedef struct SlotPoolBytes {
    SlotPool base;
    SlotPoolByteEntry entries[SLOT_POOL_ENTRIES]; /* 0x08 */
} SlotPoolBytes;

u8 *SlotPool_Item(SlotPoolItems *pool, u32 index);
SlotPoolItemEntry *SlotPool_ItemEntry(SlotPoolItems *pool, u32 index);
int SlotPool_ItemTakeWith(SlotPoolItems *pool, u32 index, const u16 *item);
void SlotPool_ItemGiveBack(SlotPoolItems *pool, u32 index);
int SlotPool_ItemTake(SlotPoolItems *pool, int index);
SlotPoolItems *SlotPool_Items(void);
SlotPoolItems *SlotPool_ItemsDestructDelete(SlotPoolItems *pool);
SlotPoolItems *SlotPool_ItemsDestruct(SlotPoolItems *pool);
SlotPoolItems *SlotPool_ItemsConstruct(SlotPoolItems *pool);
void SlotPool_ItemEntryClear(SlotPoolItemEntry *entry);
void SlotPool_ItemEntrySet(SlotPoolItemEntry *entry, int number, const u16 *item);
SlotPoolItemEntry *SlotPool_ItemEntryDestruct(SlotPoolItemEntry *entry);
SlotPoolItemEntry *SlotPool_ItemEntryConstruct(SlotPoolItemEntry *entry);

u8 *SlotPool_Part(SlotPoolBytes *pool, u32 index);
SlotPoolByteEntry *SlotPool_PartEntry(SlotPoolBytes *pool, u32 index);
void SlotPool_PartTake(SlotPoolBytes *pool, u32 index);
SlotPoolBytes *SlotPool_Parts(void);
SlotPoolBytes *SlotPool_PartsDestructDelete(SlotPoolBytes *pool);
SlotPoolBytes *SlotPool_PartsDestruct(SlotPoolBytes *pool);
SlotPoolBytes *SlotPool_PartsConstruct(SlotPoolBytes *pool);
void SlotPool_PartEntrySet(SlotPoolByteEntry *entry, u8 number);
SlotPoolByteEntry *SlotPool_PartEntryDestruct(SlotPoolByteEntry *entry);
SlotPoolByteEntry *SlotPool_PartEntryConstruct(SlotPoolByteEntry *entry);

u8 *SlotPool_AnimSet(SlotPoolBytes *pool, u32 index);
SlotPoolByteEntry *SlotPool_AnimSetEntry(SlotPoolBytes *pool, u32 index);
void SlotPool_AnimSetTake(SlotPoolBytes *pool, u32 index);
SlotPoolBytes *SlotPool_AnimSets(void);
SlotPoolBytes *SlotPool_AnimSetsDestructDelete(SlotPoolBytes *pool);
SlotPoolBytes *SlotPool_AnimSetsDestruct(SlotPoolBytes *pool);
SlotPoolBytes *SlotPool_AnimSetsConstruct(SlotPoolBytes *pool);
void SlotPool_AnimSetEntrySet(SlotPoolByteEntry *entry, int number);
SlotPoolByteEntry *SlotPool_AnimSetEntryDestruct(SlotPoolByteEntry *entry);

#endif
