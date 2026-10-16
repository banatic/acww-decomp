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
#include "resource_pools.h"
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

SlotPoolByteEntry *SlotPool_AnimSetEntryConstruct(SlotPoolByteEntry *entry);

/* Five more of the game's slot pools, built on the same base class:
 *
 *   data_021d1e8c  vtable data_020e1ac8  5 block slots (resource_pools.h), entry n takes block n
 *   data_021d1e20  vtable data_020e1ae4  5 clothes (a field actor's clothes at 0x774,
 *                                        field_actor_parts.h), entry n stands for clothes 5 + n
 *   data_021d1e64  vtable data_020e1b1c  4 heap4 slots, entry n takes heap n
 *   data_021d1ebc  vtable data_020e1aac  8 heap8 slots, entry n takes heap n
 *   data_021d1e48  vtable data_020e1b54  5 speaker animation triples (speaker_anim.h): entry n
 *                                        holds the animation sets 4 + n, 13 + n and 18 + n
 *
 * Every one but the clothes uses the base class's vtable entry 3 (SlotPool_BaseGiveBack). The
 * base class's own vtable (data_020e1b70) has no entries 2 and 4.
 *
 * The same QUIRK as above: the functions that read or set up an entry check `index` against
 * the pool they are given but use the game's own pool. */

typedef struct SlotPoolResourceEntry {
    u8 taken;
    u8 unused_01[3];
    ResourceSlot slot; /* 0x04 */
} SlotPoolResourceEntry;

typedef struct SlotPoolBlocks {
    SlotPool base;
    SlotPoolResourceEntry entries[RESOURCE_POOLS_BLOCK_COUNT]; /* 0x08 */
} SlotPoolBlocks;

typedef struct SlotPoolHeap4 {
    SlotPool base;
    SlotPoolResourceEntry entries[RESOURCE_POOLS_HEAP4_COUNT]; /* 0x08 */
} SlotPoolHeap4;

typedef struct SlotPoolHeap8 {
    SlotPool base;
    SlotPoolResourceEntry entries[RESOURCE_POOLS_HEAP8_COUNT]; /* 0x08 */
} SlotPoolHeap8;

#define SLOT_POOL_FIRST_CLOTH 5   /* the clothes entry 0 stands for */
#define SLOT_POOL_SPEAKER_ANIMS 3 /* body, held item pose, talking (speaker_anim.h) */

typedef struct SlotPoolSpeakerEntry {
    u8 taken;
    u8 anim_sets[SLOT_POOL_SPEAKER_ANIMS]; /* 0x01 */
} SlotPoolSpeakerEntry;

typedef struct SlotPoolSpeakers {
    SlotPool base;
    SlotPoolSpeakerEntry entries[SLOT_POOL_ENTRIES]; /* 0x08 */
} SlotPoolSpeakers;

ResourceSlot *SlotPool_BlockSlot(SlotPoolBlocks *pool, u32 index);
SlotPoolResourceEntry *SlotPool_BlockEntry(SlotPoolBlocks *pool, u32 index);
void SlotPool_BlockTake(SlotPoolBlocks *pool, u32 index);
SlotPoolBlocks *SlotPool_Blocks(void);
SlotPoolBlocks *SlotPool_BlocksDestructDelete(SlotPoolBlocks *pool);
SlotPoolBlocks *SlotPool_BlocksDestruct(SlotPoolBlocks *pool);
SlotPoolBlocks *SlotPool_BlocksConstruct(SlotPoolBlocks *pool);
void SlotPool_BlockEntrySet(SlotPoolResourceEntry *entry, int number);
SlotPoolResourceEntry *SlotPool_BlockEntryDestruct(SlotPoolResourceEntry *entry);
SlotPoolResourceEntry *SlotPool_BlockEntryConstruct(SlotPoolResourceEntry *entry);

u8 *SlotPool_Cloth(SlotPoolBytes *pool, u32 index);
SlotPoolByteEntry *SlotPool_ClothEntry(SlotPoolBytes *pool, u32 index);
u32 SlotPool_ClothGiveBack(SlotPoolBytes *pool, u32 index);
void SlotPool_ClothTake(SlotPoolBytes *pool, u32 index);
SlotPoolBytes *SlotPool_Clothes(void);
SlotPoolBytes *SlotPool_ClothesDestructDelete(SlotPoolBytes *pool);
SlotPoolBytes *SlotPool_ClothesDestruct(SlotPoolBytes *pool);
SlotPoolBytes *SlotPool_ClothesConstruct(SlotPoolBytes *pool);
int SlotPool_ClothEntryClear(SlotPoolByteEntry *entry);
void SlotPool_ClothEntrySet(SlotPoolByteEntry *entry, int number);
SlotPoolByteEntry *SlotPool_ClothEntryDestruct(SlotPoolByteEntry *entry);
SlotPoolByteEntry *SlotPool_ClothEntryConstruct(SlotPoolByteEntry *entry);

ResourceSlot *SlotPool_Heap4Slot(SlotPoolHeap4 *pool, u32 index);
SlotPoolResourceEntry *SlotPool_Heap4Entry(SlotPoolHeap4 *pool, u32 index);
void SlotPool_Heap4Take(SlotPoolHeap4 *pool, u32 index);
SlotPoolHeap4 *SlotPool_Heap4(void);
SlotPoolHeap4 *SlotPool_Heap4DestructDelete(SlotPoolHeap4 *pool);
SlotPoolHeap4 *SlotPool_Heap4Destruct(SlotPoolHeap4 *pool);
SlotPoolHeap4 *SlotPool_Heap4Construct(SlotPoolHeap4 *pool);
void SlotPool_Heap4EntrySet(SlotPoolResourceEntry *entry, int number);
SlotPoolResourceEntry *SlotPool_Heap4EntryDestruct(SlotPoolResourceEntry *entry);
SlotPoolResourceEntry *SlotPool_Heap4EntryConstruct(SlotPoolResourceEntry *entry);

ResourceSlot *SlotPool_Heap8Slot(SlotPoolHeap8 *pool, u32 index);
SlotPoolResourceEntry *SlotPool_Heap8Entry(SlotPoolHeap8 *pool, u32 index);
void SlotPool_Heap8Take(SlotPoolHeap8 *pool, u32 index);
SlotPoolHeap8 *SlotPool_Heap8(void);
SlotPoolHeap8 *SlotPool_Heap8DestructDelete(SlotPoolHeap8 *pool);
SlotPoolHeap8 *SlotPool_Heap8Destruct(SlotPoolHeap8 *pool);
SlotPoolHeap8 *SlotPool_Heap8Construct(SlotPoolHeap8 *pool);
void SlotPool_Heap8EntrySet(SlotPoolResourceEntry *entry, int number);
SlotPoolResourceEntry *SlotPool_Heap8EntryDestruct(SlotPoolResourceEntry *entry);
SlotPoolResourceEntry *SlotPool_Heap8EntryConstruct(SlotPoolResourceEntry *entry);

u8 *SlotPool_SpeakerAnim(SlotPoolSpeakers *pool, u32 index, u32 which);
SlotPoolSpeakerEntry *SlotPool_SpeakerEntry(SlotPoolSpeakers *pool, u32 index);
void SlotPool_SpeakerTake(SlotPoolSpeakers *pool, u32 index);
SlotPoolSpeakers *SlotPool_Speakers(void);
SlotPoolSpeakers *SlotPool_SpeakersDestructDelete(SlotPoolSpeakers *pool);
SlotPoolSpeakers *SlotPool_SpeakersDestruct(SlotPoolSpeakers *pool);
SlotPoolSpeakers *SlotPool_SpeakersConstruct(SlotPoolSpeakers *pool);
void SlotPool_SpeakerEntrySetAnim(SlotPoolSpeakerEntry *entry, int number, int which);
SlotPoolSpeakerEntry *SlotPool_SpeakerEntryDestruct(SlotPoolSpeakerEntry *entry);
SlotPoolSpeakerEntry *SlotPool_SpeakerEntryConstruct(SlotPoolSpeakerEntry *entry);

int SlotPool_FirstFree(SlotPool *pool);
void SlotPool_BaseGiveBack(SlotPool *pool, u32 index);
void SlotPool_GiveBackAll(SlotPool *pool);
void SlotPool_BaseDestruct(SlotPool *pool);
SlotPool *SlotPool_BaseDestructDelete(SlotPool *pool);
void SlotPool_BaseDestructVirtual(SlotPool *pool);
void SlotPool_BaseConstruct(SlotPool *pool, u32 count);

#endif
