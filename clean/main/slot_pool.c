/* The held item, part and animation set slot pools (slot_pool.h). */
#include "slot_pool.h"

#include "autoload_2/heap.h"
#include "clean.h"

static_assert(sizeof(SlotPoolItemEntry) == 0x6c, "item entry size");
static_assert(offsetof(SlotPoolItemEntry, item) == 0x04, "item entry item");
static_assert(offsetof(SlotPoolItems, entries) == 0x08, "item pool entries");
static_assert(sizeof(SlotPoolByteEntry) == 0x02, "byte entry size");
static_assert(offsetof(SlotPoolBytes, entries) == 0x08, "byte pool entries");

extern SlotPoolItems data_021d1f04; /* the held items */
extern SlotPoolBytes data_021d1e34; /* the parts */
extern SlotPoolBytes data_021d1e0c; /* the animation sets */

extern const SlotPoolVtable data_020e1b00; /* the held item pool's vtable */
extern const SlotPoolVtable data_020e1b38; /* the part pool's vtable */
extern const SlotPoolVtable data_020e1a90; /* the animation set pool's vtable */

/* The slot pool base class. */
extern void func_02083c30(SlotPool *pool, u32 index); /* clears entry `index`'s "taken" byte */
extern void func_02083c78(SlotPool *pool);            /* destructor */
extern void func_02083ca8(SlotPool *pool, u32 count); /* constructor */
extern void func_02083cb4(void *entry);               /* an entry's destructor (does nothing) */
extern void func_02083cb8(void *entry);               /* an entry's constructor: not taken */

extern void __cxa_vec_ctor(void *array, int count, int size, void (*construct)(void *), void (*destruct)(void *));
extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));
/* The entry constructors and destructors, as the game hands them to __cxa_vec_ctor and
 * __cxa_vec_cleanup. */
extern void func_02083294(void *entry);
extern void func_020832ac(void *entry);
extern void func_020833d4(void *entry);
extern void func_020833ec(void *entry);
extern void func_02083514(void *entry);
extern void func_0208352c(void *entry);

/* The held items. */
extern void func_0205ec50(void *held, int number, void *actor, const u16 *item, void *record, int a);
extern void func_0205ebb4(void *held);
extern void *func_0205ef90(void *held); /* destructor */
extern void *func_0205efac(void *held); /* constructor */
/* The parts and animation sets. */
extern void func_0205db4c(u8 *part, u8 number);
extern void func_0205db6c(u8 *part); /* destructor (does nothing) */
extern void func_0205db70(u8 *part); /* constructor */
extern void func_0205d8c4(u8 *set, int number);
extern void func_0205d8e8(u8 *set); /* destructor (does nothing) */

/* ---- The held items (data_021d1f04, vtable data_020e1b00) */

/* func_02083110: the held item of entry `index`, or null for a number past the pool. */
u8 *SlotPool_Item(SlotPoolItems *pool, u32 index)
{
    if (index >= pool->base.count) {
        return NULL;
    }
    return SlotPool_Items()->entries[index].item;
}
CLEAN_AS(func_02083110, SlotPool_Item)

/* func_02083134 (vtable entry 4): entry `index`, or null for a number past the pool. */
SlotPoolItemEntry *SlotPool_ItemEntry(SlotPoolItems *pool, u32 index)
{
    if (index >= pool->base.count) {
        return NULL;
    }
    return &pool->entries[index];
}
CLEAN_AS(func_02083134, SlotPool_ItemEntry)

/* func_02083148: entry `index` taken, its held item set up as item number 4 + `index` with the
 * code at `item`. Whether `index` is in the pool. */
int SlotPool_ItemTakeWith(SlotPoolItems *pool, u32 index, const u16 *item)
{
    if (index >= pool->base.count) {
        return 0;
    }
    SlotPool_ItemEntrySet(&SlotPool_Items()->entries[index], (int) (SLOT_POOL_FIRST_NUMBER + index), item);
    return 1;
}
CLEAN_AS(func_02083148, SlotPool_ItemTakeWith)

/* func_02083178 (vtable entry 3): entry `index` given back and its held item cleared. */
void SlotPool_ItemGiveBack(SlotPoolItems *pool, u32 index)
{
    func_02083c30(&pool->base, index);
    if (index < pool->base.count) {
        SlotPool_ItemEntryClear(&SlotPool_Items()->entries[index]);
    }
}
CLEAN_AS(func_02083178, SlotPool_ItemGiveBack)

/* func_020831a4 (vtable entry 2): SlotPool_ItemTakeWith with no item code. */
int SlotPool_ItemTake(SlotPoolItems *pool, int index)
{
    u16 item = SLOT_POOL_NO_ITEM;
    return SlotPool_ItemTakeWith(pool, (u32) index, &item);
}
CLEAN_AS(func_020831a4, SlotPool_ItemTake)

/* func_020831c0 */
SlotPoolItems *SlotPool_Items(void)
{
    return &data_021d1f04;
}
CLEAN_AS(func_020831c0, SlotPool_Items)

/* func_020831c8 (vtable entry 1) */
SlotPoolItems *SlotPool_ItemsDestructDelete(SlotPoolItems *pool)
{
    pool->base.vtable = &data_020e1b00;
    __cxa_vec_cleanup(pool->entries, SLOT_POOL_ENTRIES, sizeof(SlotPoolItemEntry), func_02083294);
    func_02083c78(&pool->base);
    Heap_OperatorDeleteB(pool);
    return pool;
}
CLEAN_AS(func_020831c8, SlotPool_ItemsDestructDelete)

/* func_020831fc (vtable entry 0) */
SlotPoolItems *SlotPool_ItemsDestruct(SlotPoolItems *pool)
{
    pool->base.vtable = &data_020e1b00;
    __cxa_vec_cleanup(pool->entries, SLOT_POOL_ENTRIES, sizeof(SlotPoolItemEntry), func_02083294);
    func_02083c78(&pool->base);
    return pool;
}
CLEAN_AS(func_020831fc, SlotPool_ItemsDestruct)

/* func_02083228 */
SlotPoolItems *SlotPool_ItemsConstruct(SlotPoolItems *pool)
{
    func_02083ca8(&pool->base, SLOT_POOL_ENTRIES);
    pool->base.vtable = &data_020e1b00;
    __cxa_vec_ctor(pool->entries, SLOT_POOL_ENTRIES, sizeof(SlotPoolItemEntry), func_020832ac, func_02083294);
    return pool;
}
CLEAN_AS(func_02083228, SlotPool_ItemsConstruct)

/* func_02083260: the entry's held item cleared (func_0205ebb4), the entry no longer taken. */
void SlotPool_ItemEntryClear(SlotPoolItemEntry *entry)
{
    func_0205ebb4(entry->item);
    entry->taken = 0;
}
CLEAN_AS(func_02083260, SlotPool_ItemEntryClear)

/* func_02083274: the entry's held item set up as item `number` with the code at `item`, with no
 * actor or record; the entry taken. */
void SlotPool_ItemEntrySet(SlotPoolItemEntry *entry, int number, const u16 *item)
{
    func_0205ec50(entry->item, number, NULL, item, NULL, 0);
    entry->taken = 1;
}
CLEAN_AS(func_02083274, SlotPool_ItemEntrySet)

/* func_02083294 */
SlotPoolItemEntry *SlotPool_ItemEntryDestruct(SlotPoolItemEntry *entry)
{
    func_0205ef90(entry->item);
    func_02083cb4(entry);
    return entry;
}
CLEAN_AS(func_02083294, SlotPool_ItemEntryDestruct)

/* func_020832ac */
SlotPoolItemEntry *SlotPool_ItemEntryConstruct(SlotPoolItemEntry *entry)
{
    func_02083cb8(entry);
    func_0205efac(entry->item);
    return entry;
}
CLEAN_AS(func_020832ac, SlotPool_ItemEntryConstruct)

/* ---- The parts (data_021d1e34, vtable data_020e1b38; vtable entry 3 is the base class's) */

/* func_020832c4: the part number of entry `index`, or null for a number past the pool. */
u8 *SlotPool_Part(SlotPoolBytes *pool, u32 index)
{
    if (index >= pool->base.count) {
        return NULL;
    }
    return &SlotPool_Parts()->entries[index].number;
}
CLEAN_AS(func_020832c4, SlotPool_Part)

/* func_020832e4 (vtable entry 4): entry `index`, or null for a number past the pool. */
SlotPoolByteEntry *SlotPool_PartEntry(SlotPoolBytes *pool, u32 index)
{
    if (index >= pool->base.count) {
        return NULL;
    }
    return &pool->entries[index];
}
CLEAN_AS(func_020832e4, SlotPool_PartEntry)

/* func_020832f8 (vtable entry 2): entry `index` taken as part 4 + `index`. */
void SlotPool_PartTake(SlotPoolBytes *pool, u32 index)
{
    if (index < pool->base.count) {
        SlotPool_PartEntrySet(&SlotPool_Parts()->entries[index], (u8) (SLOT_POOL_FIRST_NUMBER + index));
    }
}
CLEAN_AS(func_020832f8, SlotPool_PartTake)

/* func_02083320 */
SlotPoolBytes *SlotPool_Parts(void)
{
    return &data_021d1e34;
}
CLEAN_AS(func_02083320, SlotPool_Parts)

/* func_02083328 (vtable entry 1) */
SlotPoolBytes *SlotPool_PartsDestructDelete(SlotPoolBytes *pool)
{
    pool->base.vtable = &data_020e1b38;
    __cxa_vec_cleanup(pool->entries, SLOT_POOL_ENTRIES, sizeof(SlotPoolByteEntry), func_020833d4);
    func_02083c78(&pool->base);
    Heap_OperatorDeleteB(pool);
    return pool;
}
CLEAN_AS(func_02083328, SlotPool_PartsDestructDelete)

/* func_0208335c (vtable entry 0) */
SlotPoolBytes *SlotPool_PartsDestruct(SlotPoolBytes *pool)
{
    pool->base.vtable = &data_020e1b38;
    __cxa_vec_cleanup(pool->entries, SLOT_POOL_ENTRIES, sizeof(SlotPoolByteEntry), func_020833d4);
    func_02083c78(&pool->base);
    return pool;
}
CLEAN_AS(func_0208335c, SlotPool_PartsDestruct)

/* func_02083388 */
SlotPoolBytes *SlotPool_PartsConstruct(SlotPoolBytes *pool)
{
    func_02083ca8(&pool->base, SLOT_POOL_ENTRIES);
    pool->base.vtable = &data_020e1b38;
    __cxa_vec_ctor(pool->entries, SLOT_POOL_ENTRIES, sizeof(SlotPoolByteEntry), func_020833ec, func_020833d4);
    return pool;
}
CLEAN_AS(func_02083388, SlotPool_PartsConstruct)

/* func_020833c0: the entry set to part `number` (func_0205db4c) and taken. */
void SlotPool_PartEntrySet(SlotPoolByteEntry *entry, u8 number)
{
    func_0205db4c(&entry->number, number);
    entry->taken = 1;
}
CLEAN_AS(func_020833c0, SlotPool_PartEntrySet)

/* func_020833d4 */
SlotPoolByteEntry *SlotPool_PartEntryDestruct(SlotPoolByteEntry *entry)
{
    func_0205db6c(&entry->number);
    func_02083cb4(entry);
    return entry;
}
CLEAN_AS(func_020833d4, SlotPool_PartEntryDestruct)

/* func_020833ec */
SlotPoolByteEntry *SlotPool_PartEntryConstruct(SlotPoolByteEntry *entry)
{
    func_02083cb8(entry);
    func_0205db70(&entry->number);
    return entry;
}
CLEAN_AS(func_020833ec, SlotPool_PartEntryConstruct)

/* ---- The animation sets (data_021d1e0c, vtable data_020e1a90; vtable entry 3 is the base
 * class's) */

/* func_02083404: the animation set number of entry `index`, or null for a number past the
 * pool. */
u8 *SlotPool_AnimSet(SlotPoolBytes *pool, u32 index)
{
    if (index >= pool->base.count) {
        return NULL;
    }
    return &SlotPool_AnimSets()->entries[index].number;
}
CLEAN_AS(func_02083404, SlotPool_AnimSet)

/* func_02083424 (vtable entry 4): entry `index`, or null for a number past the pool. */
SlotPoolByteEntry *SlotPool_AnimSetEntry(SlotPoolBytes *pool, u32 index)
{
    if (index >= pool->base.count) {
        return NULL;
    }
    return &pool->entries[index];
}
CLEAN_AS(func_02083424, SlotPool_AnimSetEntry)

/* func_02083438 (vtable entry 2): entry `index` taken as animation set 4 + `index`. */
void SlotPool_AnimSetTake(SlotPoolBytes *pool, u32 index)
{
    if (index < pool->base.count) {
        SlotPool_AnimSetEntrySet(&SlotPool_AnimSets()->entries[index], (int) (SLOT_POOL_FIRST_NUMBER + index));
    }
}
CLEAN_AS(func_02083438, SlotPool_AnimSetTake)

/* func_02083460 */
SlotPoolBytes *SlotPool_AnimSets(void)
{
    return &data_021d1e0c;
}
CLEAN_AS(func_02083460, SlotPool_AnimSets)

/* func_02083468 (vtable entry 1) */
SlotPoolBytes *SlotPool_AnimSetsDestructDelete(SlotPoolBytes *pool)
{
    pool->base.vtable = &data_020e1a90;
    __cxa_vec_cleanup(pool->entries, SLOT_POOL_ENTRIES, sizeof(SlotPoolByteEntry), func_02083514);
    func_02083c78(&pool->base);
    Heap_OperatorDeleteB(pool);
    return pool;
}
CLEAN_AS(func_02083468, SlotPool_AnimSetsDestructDelete)

/* func_0208349c (vtable entry 0) */
SlotPoolBytes *SlotPool_AnimSetsDestruct(SlotPoolBytes *pool)
{
    pool->base.vtable = &data_020e1a90;
    __cxa_vec_cleanup(pool->entries, SLOT_POOL_ENTRIES, sizeof(SlotPoolByteEntry), func_02083514);
    func_02083c78(&pool->base);
    return pool;
}
CLEAN_AS(func_0208349c, SlotPool_AnimSetsDestruct)

/* func_020834c8 */
SlotPoolBytes *SlotPool_AnimSetsConstruct(SlotPoolBytes *pool)
{
    func_02083ca8(&pool->base, SLOT_POOL_ENTRIES);
    pool->base.vtable = &data_020e1a90;
    __cxa_vec_ctor(pool->entries, SLOT_POOL_ENTRIES, sizeof(SlotPoolByteEntry), func_0208352c, func_02083514);
    return pool;
}
CLEAN_AS(func_020834c8, SlotPool_AnimSetsConstruct)

/* func_02083500: the entry set to animation set `number` (func_0205d8c4) and taken. */
void SlotPool_AnimSetEntrySet(SlotPoolByteEntry *entry, int number)
{
    func_0205d8c4(&entry->number, number);
    entry->taken = 1;
}
CLEAN_AS(func_02083500, SlotPool_AnimSetEntrySet)

/* func_02083514 */
SlotPoolByteEntry *SlotPool_AnimSetEntryDestruct(SlotPoolByteEntry *entry)
{
    func_0205d8e8(&entry->number);
    func_02083cb4(entry);
    return entry;
}
CLEAN_AS(func_02083514, SlotPool_AnimSetEntryDestruct)

extern void func_0205d8ec(u8 *set); /* constructor */

/* func_0208352c */
SlotPoolByteEntry *SlotPool_AnimSetEntryConstruct(SlotPoolByteEntry *entry)
{
    func_02083cb8(entry);
    func_0205d8ec(&entry->number);
    return entry;
}
CLEAN_AS(func_0208352c, SlotPool_AnimSetEntryConstruct)

/* ---- The other pools (slot_pool.h) */

static_assert(sizeof(SlotPoolResourceEntry) == 0x08, "resource entry size");
static_assert(offsetof(SlotPoolResourceEntry, slot) == 0x04, "resource entry slot");
static_assert(offsetof(SlotPoolBlocks, entries) == 0x08, "block pool entries");
static_assert(offsetof(SlotPoolHeap4, entries) == 0x08, "heap4 pool entries");
static_assert(offsetof(SlotPoolHeap8, entries) == 0x08, "heap8 pool entries");
static_assert(sizeof(SlotPoolSpeakerEntry) == 0x04, "speaker entry size");
static_assert(offsetof(SlotPoolSpeakers, entries) == 0x08, "speaker pool entries");

extern SlotPoolBlocks data_021d1e8c;   /* the block slots */
extern SlotPoolBytes data_021d1e20;    /* the clothes */
extern SlotPoolHeap4 data_021d1e64;    /* the heap4 slots */
extern SlotPoolHeap8 data_021d1ebc;    /* the heap8 slots */
extern SlotPoolSpeakers data_021d1e48; /* the speaker animation triples */

extern const SlotPoolVtable data_020e1ac8; /* the block slot pool's vtable */
extern const SlotPoolVtable data_020e1ae4; /* the clothes pool's vtable */
extern const SlotPoolVtable data_020e1b1c; /* the heap4 slot pool's vtable */
extern const SlotPoolVtable data_020e1aac; /* the heap8 slot pool's vtable */
extern const SlotPoolVtable data_020e1b54; /* the speaker pool's vtable */
extern const SlotPoolVtable data_020e1b70; /* the base class's vtable */

/* The entry constructors and destructors, as the game hands them to __cxa_vec_ctor and
 * __cxa_vec_cleanup. */
extern void func_02083654(void *entry);
extern void func_0208366c(void *entry);
extern void func_020837d0(void *entry);
extern void func_020837e8(void *entry);
extern void func_02083910(void *entry);
extern void func_02083928(void *entry);
extern void func_02083a50(void *entry);
extern void func_02083a68(void *entry);
extern void func_02083bac(void *entry);
extern void func_02083bd0(void *entry);

/* The clothes. */
extern void func_0205d4e8(u8 *cloth);             /* cleared */
extern void func_0205d4f0(u8 *cloth, int number); /* set up as clothes `number` */
extern void func_0205d51c(u8 *cloth);             /* destructor */
extern void func_0205d520(u8 *cloth);             /* constructor */
/* An animation set (as at a field actor's 0x700 and 0x701, field_actor_parts.h). */
extern void func_0205ccc4(u8 *set, int number); /* set up as set `number` */
extern void func_0205cce4(void *set);           /* destructor */
extern void func_0205cce8(void *set);           /* constructor */

/* The offsets of the three animation sets of a speaker entry from its number. */
extern const s32 data_020d0638[SLOT_POOL_SPEAKER_ANIMS];

/* ---- The block slots (data_021d1e8c, vtable data_020e1ac8) */

/* func_02083544: the block slot of entry `index`, or null for a number past the pool. */
ResourceSlot *SlotPool_BlockSlot(SlotPoolBlocks *pool, u32 index)
{
    if (index >= pool->base.count) {
        return NULL;
    }
    return &SlotPool_Blocks()->entries[index].slot;
}
CLEAN_AS(func_02083544, SlotPool_BlockSlot)

/* func_02083564 (vtable entry 4): entry `index`, or null for a number past the pool. */
SlotPoolResourceEntry *SlotPool_BlockEntry(SlotPoolBlocks *pool, u32 index)
{
    if (index >= pool->base.count) {
        return NULL;
    }
    return &pool->entries[index];
}
CLEAN_AS(func_02083564, SlotPool_BlockEntry)

/* func_02083578 (vtable entry 2): entry `index` taken with block `index`. */
void SlotPool_BlockTake(SlotPoolBlocks *pool, u32 index)
{
    if (index < pool->base.count) {
        SlotPool_BlockEntrySet(&SlotPool_Blocks()->entries[index], (int) index);
    }
}
CLEAN_AS(func_02083578, SlotPool_BlockTake)

/* func_020835a0 */
SlotPoolBlocks *SlotPool_Blocks(void)
{
    return &data_021d1e8c;
}
CLEAN_AS(func_020835a0, SlotPool_Blocks)

/* func_020835a8 (vtable entry 1) */
SlotPoolBlocks *SlotPool_BlocksDestructDelete(SlotPoolBlocks *pool)
{
    pool->base.vtable = &data_020e1ac8;
    __cxa_vec_cleanup(pool->entries, RESOURCE_POOLS_BLOCK_COUNT, sizeof(SlotPoolResourceEntry), func_02083654);
    SlotPool_BaseDestruct(&pool->base);
    Heap_OperatorDeleteB(pool);
    return pool;
}
CLEAN_AS(func_020835a8, SlotPool_BlocksDestructDelete)

/* func_020835dc (vtable entry 0) */
SlotPoolBlocks *SlotPool_BlocksDestruct(SlotPoolBlocks *pool)
{
    pool->base.vtable = &data_020e1ac8;
    __cxa_vec_cleanup(pool->entries, RESOURCE_POOLS_BLOCK_COUNT, sizeof(SlotPoolResourceEntry), func_02083654);
    SlotPool_BaseDestruct(&pool->base);
    return pool;
}
CLEAN_AS(func_020835dc, SlotPool_BlocksDestruct)

/* func_02083608 */
SlotPoolBlocks *SlotPool_BlocksConstruct(SlotPoolBlocks *pool)
{
    SlotPool_BaseConstruct(&pool->base, RESOURCE_POOLS_BLOCK_COUNT);
    pool->base.vtable = &data_020e1ac8;
    __cxa_vec_ctor(pool->entries, RESOURCE_POOLS_BLOCK_COUNT, sizeof(SlotPoolResourceEntry), func_0208366c, func_02083654);
    return pool;
}
CLEAN_AS(func_02083608, SlotPool_BlocksConstruct)

/* func_02083640: the entry's slot given block `number`; the entry taken. */
void SlotPool_BlockEntrySet(SlotPoolResourceEntry *entry, int number)
{
    ResourcePools_BlockSlotBind(&entry->slot, number);
    entry->taken = 1;
}
CLEAN_AS(func_02083640, SlotPool_BlockEntrySet)

/* func_02083654 */
SlotPoolResourceEntry *SlotPool_BlockEntryDestruct(SlotPoolResourceEntry *entry)
{
    ResourcePools_BlockSlotDestruct(&entry->slot);
    func_02083cb4(entry);
    return entry;
}
CLEAN_AS(func_02083654, SlotPool_BlockEntryDestruct)

/* func_0208366c */
SlotPoolResourceEntry *SlotPool_BlockEntryConstruct(SlotPoolResourceEntry *entry)
{
    func_02083cb8(entry);
    ResourcePools_BlockSlotConstruct(&entry->slot);
    return entry;
}
CLEAN_AS(func_0208366c, SlotPool_BlockEntryConstruct)

/* ---- The clothes (data_021d1e20, vtable data_020e1ae4) */

/* func_02083684: the clothes of entry `index`, or null for a number past the pool. */
u8 *SlotPool_Cloth(SlotPoolBytes *pool, u32 index)
{
    if (index >= pool->base.count) {
        return NULL;
    }
    return &SlotPool_Clothes()->entries[index].number;
}
CLEAN_AS(func_02083684, SlotPool_Cloth)

/* func_020836a4 (vtable entry 4): entry `index`, or null for a number past the pool. */
SlotPoolByteEntry *SlotPool_ClothEntry(SlotPoolBytes *pool, u32 index)
{
    if (index >= pool->base.count) {
        return NULL;
    }
    return &pool->entries[index];
}
CLEAN_AS(func_020836a4, SlotPool_ClothEntry)

/* func_020836b8 (vtable entry 3): entry `index` given back and its clothes cleared.
 * QUIRK: the result is 0, or the pool's number of entries for a number past the pool; the
 * callers, through the vtable, ignore it. */
u32 SlotPool_ClothGiveBack(SlotPoolBytes *pool, u32 index)
{
    SlotPool_BaseGiveBack(&pool->base, index);
    if (index >= pool->base.count) {
        return pool->base.count;
    }
    return (u32) SlotPool_ClothEntryClear(&SlotPool_Clothes()->entries[index]);
}
CLEAN_AS(func_020836b8, SlotPool_ClothGiveBack)

/* func_020836e0 (vtable entry 2): entry `index` taken as clothes 5 + `index`. */
void SlotPool_ClothTake(SlotPoolBytes *pool, u32 index)
{
    if (index < pool->base.count) {
        SlotPool_ClothEntrySet(&SlotPool_Clothes()->entries[index], (int) (SLOT_POOL_FIRST_CLOTH + index));
    }
}
CLEAN_AS(func_020836e0, SlotPool_ClothTake)

/* func_02083708 */
SlotPoolBytes *SlotPool_Clothes(void)
{
    return &data_021d1e20;
}
CLEAN_AS(func_02083708, SlotPool_Clothes)

/* func_02083710 (vtable entry 1) */
SlotPoolBytes *SlotPool_ClothesDestructDelete(SlotPoolBytes *pool)
{
    pool->base.vtable = &data_020e1ae4;
    __cxa_vec_cleanup(pool->entries, SLOT_POOL_ENTRIES, sizeof(SlotPoolByteEntry), func_020837d0);
    SlotPool_BaseDestruct(&pool->base);
    Heap_OperatorDeleteB(pool);
    return pool;
}
CLEAN_AS(func_02083710, SlotPool_ClothesDestructDelete)

/* func_02083744 (vtable entry 0) */
SlotPoolBytes *SlotPool_ClothesDestruct(SlotPoolBytes *pool)
{
    pool->base.vtable = &data_020e1ae4;
    __cxa_vec_cleanup(pool->entries, SLOT_POOL_ENTRIES, sizeof(SlotPoolByteEntry), func_020837d0);
    SlotPool_BaseDestruct(&pool->base);
    return pool;
}
CLEAN_AS(func_02083744, SlotPool_ClothesDestruct)

/* func_02083770 */
SlotPoolBytes *SlotPool_ClothesConstruct(SlotPoolBytes *pool)
{
    SlotPool_BaseConstruct(&pool->base, SLOT_POOL_ENTRIES);
    pool->base.vtable = &data_020e1ae4;
    __cxa_vec_ctor(pool->entries, SLOT_POOL_ENTRIES, sizeof(SlotPoolByteEntry), func_020837e8, func_020837d0);
    return pool;
}
CLEAN_AS(func_02083770, SlotPool_ClothesConstruct)

/* func_020837a8: the entry's clothes cleared (func_0205d4e8), the entry no longer taken.
 * Always 0. */
int SlotPool_ClothEntryClear(SlotPoolByteEntry *entry)
{
    func_0205d4e8(&entry->number);
    entry->taken = 0;
    return 0;
}
CLEAN_AS(func_020837a8, SlotPool_ClothEntryClear)

/* func_020837bc: the entry set up as clothes `number` (func_0205d4f0) and taken. */
void SlotPool_ClothEntrySet(SlotPoolByteEntry *entry, int number)
{
    func_0205d4f0(&entry->number, number);
    entry->taken = 1;
}
CLEAN_AS(func_020837bc, SlotPool_ClothEntrySet)

/* func_020837d0 */
SlotPoolByteEntry *SlotPool_ClothEntryDestruct(SlotPoolByteEntry *entry)
{
    func_0205d51c(&entry->number);
    func_02083cb4(entry);
    return entry;
}
CLEAN_AS(func_020837d0, SlotPool_ClothEntryDestruct)

/* func_020837e8 */
SlotPoolByteEntry *SlotPool_ClothEntryConstruct(SlotPoolByteEntry *entry)
{
    func_02083cb8(entry);
    func_0205d520(&entry->number);
    return entry;
}
CLEAN_AS(func_020837e8, SlotPool_ClothEntryConstruct)

/* ---- The heap4 slots (data_021d1e64, vtable data_020e1b1c) */

/* func_02083800: the heap4 slot of entry `index`, or null for a number past the pool. */
ResourceSlot *SlotPool_Heap4Slot(SlotPoolHeap4 *pool, u32 index)
{
    if (index >= pool->base.count) {
        return NULL;
    }
    return &SlotPool_Heap4()->entries[index].slot;
}
CLEAN_AS(func_02083800, SlotPool_Heap4Slot)

/* func_02083820 (vtable entry 4): entry `index`, or null for a number past the pool. */
SlotPoolResourceEntry *SlotPool_Heap4Entry(SlotPoolHeap4 *pool, u32 index)
{
    if (index >= pool->base.count) {
        return NULL;
    }
    return &pool->entries[index];
}
CLEAN_AS(func_02083820, SlotPool_Heap4Entry)

/* func_02083834 (vtable entry 2): entry `index` taken with heap `index`. */
void SlotPool_Heap4Take(SlotPoolHeap4 *pool, u32 index)
{
    if (index < pool->base.count) {
        SlotPool_Heap4EntrySet(&SlotPool_Heap4()->entries[index], (int) index);
    }
}
CLEAN_AS(func_02083834, SlotPool_Heap4Take)

/* func_0208385c */
SlotPoolHeap4 *SlotPool_Heap4(void)
{
    return &data_021d1e64;
}
CLEAN_AS(func_0208385c, SlotPool_Heap4)

/* func_02083864 (vtable entry 1) */
SlotPoolHeap4 *SlotPool_Heap4DestructDelete(SlotPoolHeap4 *pool)
{
    pool->base.vtable = &data_020e1b1c;
    __cxa_vec_cleanup(pool->entries, RESOURCE_POOLS_HEAP4_COUNT, sizeof(SlotPoolResourceEntry), func_02083910);
    SlotPool_BaseDestruct(&pool->base);
    Heap_OperatorDeleteB(pool);
    return pool;
}
CLEAN_AS(func_02083864, SlotPool_Heap4DestructDelete)

/* func_02083898 (vtable entry 0) */
SlotPoolHeap4 *SlotPool_Heap4Destruct(SlotPoolHeap4 *pool)
{
    pool->base.vtable = &data_020e1b1c;
    __cxa_vec_cleanup(pool->entries, RESOURCE_POOLS_HEAP4_COUNT, sizeof(SlotPoolResourceEntry), func_02083910);
    SlotPool_BaseDestruct(&pool->base);
    return pool;
}
CLEAN_AS(func_02083898, SlotPool_Heap4Destruct)

/* func_020838c4 */
SlotPoolHeap4 *SlotPool_Heap4Construct(SlotPoolHeap4 *pool)
{
    SlotPool_BaseConstruct(&pool->base, RESOURCE_POOLS_HEAP4_COUNT);
    pool->base.vtable = &data_020e1b1c;
    __cxa_vec_ctor(pool->entries, RESOURCE_POOLS_HEAP4_COUNT, sizeof(SlotPoolResourceEntry), func_02083928, func_02083910);
    return pool;
}
CLEAN_AS(func_020838c4, SlotPool_Heap4Construct)

/* func_020838fc: the entry's slot given heap4 heap `number` (which is emptied); the entry
 * taken. */
void SlotPool_Heap4EntrySet(SlotPoolResourceEntry *entry, int number)
{
    ResourcePools_Heap4SlotBind(&entry->slot, number);
    entry->taken = 1;
}
CLEAN_AS(func_020838fc, SlotPool_Heap4EntrySet)

/* func_02083910 */
SlotPoolResourceEntry *SlotPool_Heap4EntryDestruct(SlotPoolResourceEntry *entry)
{
    ResourcePools_Heap4SlotDestruct(&entry->slot);
    func_02083cb4(entry);
    return entry;
}
CLEAN_AS(func_02083910, SlotPool_Heap4EntryDestruct)

/* func_02083928 */
SlotPoolResourceEntry *SlotPool_Heap4EntryConstruct(SlotPoolResourceEntry *entry)
{
    func_02083cb8(entry);
    ResourcePools_Heap4SlotConstruct(&entry->slot);
    return entry;
}
CLEAN_AS(func_02083928, SlotPool_Heap4EntryConstruct)

/* ---- The heap8 slots (data_021d1ebc, vtable data_020e1aac) */

/* func_02083940: the heap8 slot of entry `index`, or null for a number past the pool. */
ResourceSlot *SlotPool_Heap8Slot(SlotPoolHeap8 *pool, u32 index)
{
    if (index >= pool->base.count) {
        return NULL;
    }
    return &SlotPool_Heap8()->entries[index].slot;
}
CLEAN_AS(func_02083940, SlotPool_Heap8Slot)

/* func_02083960 (vtable entry 4): entry `index`, or null for a number past the pool. */
SlotPoolResourceEntry *SlotPool_Heap8Entry(SlotPoolHeap8 *pool, u32 index)
{
    if (index >= pool->base.count) {
        return NULL;
    }
    return &pool->entries[index];
}
CLEAN_AS(func_02083960, SlotPool_Heap8Entry)

/* func_02083974 (vtable entry 2): entry `index` taken with heap `index`. */
void SlotPool_Heap8Take(SlotPoolHeap8 *pool, u32 index)
{
    if (index < pool->base.count) {
        SlotPool_Heap8EntrySet(&SlotPool_Heap8()->entries[index], (int) index);
    }
}
CLEAN_AS(func_02083974, SlotPool_Heap8Take)

/* func_0208399c */
SlotPoolHeap8 *SlotPool_Heap8(void)
{
    return &data_021d1ebc;
}
CLEAN_AS(func_0208399c, SlotPool_Heap8)

/* func_020839a4 (vtable entry 1) */
SlotPoolHeap8 *SlotPool_Heap8DestructDelete(SlotPoolHeap8 *pool)
{
    pool->base.vtable = &data_020e1aac;
    __cxa_vec_cleanup(pool->entries, RESOURCE_POOLS_HEAP8_COUNT, sizeof(SlotPoolResourceEntry), func_02083a50);
    SlotPool_BaseDestruct(&pool->base);
    Heap_OperatorDeleteB(pool);
    return pool;
}
CLEAN_AS(func_020839a4, SlotPool_Heap8DestructDelete)

/* func_020839d8 (vtable entry 0) */
SlotPoolHeap8 *SlotPool_Heap8Destruct(SlotPoolHeap8 *pool)
{
    pool->base.vtable = &data_020e1aac;
    __cxa_vec_cleanup(pool->entries, RESOURCE_POOLS_HEAP8_COUNT, sizeof(SlotPoolResourceEntry), func_02083a50);
    SlotPool_BaseDestruct(&pool->base);
    return pool;
}
CLEAN_AS(func_020839d8, SlotPool_Heap8Destruct)

/* func_02083a04 */
SlotPoolHeap8 *SlotPool_Heap8Construct(SlotPoolHeap8 *pool)
{
    SlotPool_BaseConstruct(&pool->base, RESOURCE_POOLS_HEAP8_COUNT);
    pool->base.vtable = &data_020e1aac;
    __cxa_vec_ctor(pool->entries, RESOURCE_POOLS_HEAP8_COUNT, sizeof(SlotPoolResourceEntry), func_02083a68, func_02083a50);
    return pool;
}
CLEAN_AS(func_02083a04, SlotPool_Heap8Construct)

/* func_02083a3c: the entry's slot given heap8 heap `number` (which is emptied); the entry
 * taken. */
void SlotPool_Heap8EntrySet(SlotPoolResourceEntry *entry, int number)
{
    ResourcePools_Heap8SlotBind(&entry->slot, number);
    entry->taken = 1;
}
CLEAN_AS(func_02083a3c, SlotPool_Heap8EntrySet)

/* func_02083a50 */
SlotPoolResourceEntry *SlotPool_Heap8EntryDestruct(SlotPoolResourceEntry *entry)
{
    ResourcePools_Heap8SlotDestruct(&entry->slot);
    func_02083cb4(entry);
    return entry;
}
CLEAN_AS(func_02083a50, SlotPool_Heap8EntryDestruct)

/* func_02083a68 */
SlotPoolResourceEntry *SlotPool_Heap8EntryConstruct(SlotPoolResourceEntry *entry)
{
    func_02083cb8(entry);
    ResourcePools_Heap8SlotConstruct(&entry->slot);
    return entry;
}
CLEAN_AS(func_02083a68, SlotPool_Heap8EntryConstruct)

/* ---- The speaker animation triples (data_021d1e48, vtable data_020e1b54) */

/* func_02083a80: the address of animation set `which` of entry `index`, or null for a number
 * past the pool. `which` is added unchecked; the callers pass 0, 1 or 2. */
u8 *SlotPool_SpeakerAnim(SlotPoolSpeakers *pool, u32 index, u32 which)
{
    if (index >= pool->base.count) {
        return NULL;
    }
    return (u8 *) ((uintptr_t) SlotPool_Speakers()->entries[index].anim_sets + which);
}
CLEAN_AS(func_02083a80, SlotPool_SpeakerAnim)

/* func_02083aa8 (vtable entry 4): entry `index`, or null for a number past the pool. */
SlotPoolSpeakerEntry *SlotPool_SpeakerEntry(SlotPoolSpeakers *pool, u32 index)
{
    if (index >= pool->base.count) {
        return NULL;
    }
    return &pool->entries[index];
}
CLEAN_AS(func_02083aa8, SlotPool_SpeakerEntry)

/* func_02083abc (vtable entry 2): entry `index` set up with the animation sets `index` + 4,
 * + 13 and + 18 (data_020d0638), and taken. QUIRK: the entry is marked taken again after each
 * of the three. */
void SlotPool_SpeakerTake(SlotPoolSpeakers *pool, u32 index)
{
    if (index >= pool->base.count) {
        return;
    }
    for (int which = 0; which < SLOT_POOL_SPEAKER_ANIMS; which++) {
        SlotPool_SpeakerEntrySetAnim(&SlotPool_Speakers()->entries[index], (int) index + data_020d0638[which], which);
        SlotPool_Speakers()->entries[index].taken = 1;
    }
}
CLEAN_AS(func_02083abc, SlotPool_SpeakerTake)

/* func_02083b00 */
SlotPoolSpeakers *SlotPool_Speakers(void)
{
    return &data_021d1e48;
}
CLEAN_AS(func_02083b00, SlotPool_Speakers)

/* func_02083b08 (vtable entry 1) */
SlotPoolSpeakers *SlotPool_SpeakersDestructDelete(SlotPoolSpeakers *pool)
{
    pool->base.vtable = &data_020e1b54;
    __cxa_vec_cleanup(pool->entries, SLOT_POOL_ENTRIES, sizeof(SlotPoolSpeakerEntry), func_02083bac);
    SlotPool_BaseDestruct(&pool->base);
    Heap_OperatorDeleteB(pool);
    return pool;
}
CLEAN_AS(func_02083b08, SlotPool_SpeakersDestructDelete)

/* func_02083b3c (vtable entry 0) */
SlotPoolSpeakers *SlotPool_SpeakersDestruct(SlotPoolSpeakers *pool)
{
    pool->base.vtable = &data_020e1b54;
    __cxa_vec_cleanup(pool->entries, SLOT_POOL_ENTRIES, sizeof(SlotPoolSpeakerEntry), func_02083bac);
    SlotPool_BaseDestruct(&pool->base);
    return pool;
}
CLEAN_AS(func_02083b3c, SlotPool_SpeakersDestruct)

/* func_02083b68 */
SlotPoolSpeakers *SlotPool_SpeakersConstruct(SlotPoolSpeakers *pool)
{
    SlotPool_BaseConstruct(&pool->base, SLOT_POOL_ENTRIES);
    pool->base.vtable = &data_020e1b54;
    __cxa_vec_ctor(pool->entries, SLOT_POOL_ENTRIES, sizeof(SlotPoolSpeakerEntry), func_02083bd0, func_02083bac);
    return pool;
}
CLEAN_AS(func_02083b68, SlotPool_SpeakersConstruct)

/* func_02083ba0: animation set `which` of the entry set up as set `number` (func_0205ccc4).
 * REQUIRES: `which` below SLOT_POOL_SPEAKER_ANIMS (only SlotPool_SpeakerTake calls it). */
void SlotPool_SpeakerEntrySetAnim(SlotPoolSpeakerEntry *entry, int number, int which)
{
    func_0205ccc4(&entry->anim_sets[which], number);
}
CLEAN_AS(func_02083ba0, SlotPool_SpeakerEntrySetAnim)

/* func_02083bac */
SlotPoolSpeakerEntry *SlotPool_SpeakerEntryDestruct(SlotPoolSpeakerEntry *entry)
{
    __cxa_vec_cleanup(entry->anim_sets, SLOT_POOL_SPEAKER_ANIMS, 1, func_0205cce4);
    func_02083cb4(entry);
    return entry;
}
CLEAN_AS(func_02083bac, SlotPool_SpeakerEntryDestruct)

/* func_02083bd0 */
SlotPoolSpeakerEntry *SlotPool_SpeakerEntryConstruct(SlotPoolSpeakerEntry *entry)
{
    func_02083cb8(entry);
    __cxa_vec_ctor(entry->anim_sets, SLOT_POOL_SPEAKER_ANIMS, 1, func_0205cce8, func_0205cce4);
    return entry;
}
CLEAN_AS(func_02083bd0, SlotPool_SpeakerEntryConstruct)

/* ---- The base class (vtable data_020e1b70) */

/* func_02083bfc: the number of the first entry that is not taken (whose "taken" byte, from
 * vtable entry 4, is there and 0), -1 when all are. */
int SlotPool_FirstFree(SlotPool *pool)
{
    for (int i = 0; i < (int) pool->count; i++) {
        const u8 *taken = pool->vtable->taken(pool, i);
        if (taken != NULL && *taken == 0) {
            return i;
        }
    }
    return -1;
}
CLEAN_AS(func_02083bfc, SlotPool_FirstFree)

/* func_02083c30 (vtable entry 3): entry `index` no longer taken; nothing for a number past the
 * pool. */
void SlotPool_BaseGiveBack(SlotPool *pool, u32 index)
{
    if (index >= pool->count) {
        return;
    }
    u8 *taken = pool->vtable->taken(pool, (int) index);
    if (taken != NULL) {
        *taken = 0;
    }
}
CLEAN_AS(func_02083c30, SlotPool_BaseGiveBack)

/* func_02083c50: every entry no longer taken. Only the "taken" bytes are cleared: what the
 * entries hold stays. */
void SlotPool_GiveBackAll(SlotPool *pool)
{
    for (int i = 0; i < (int) pool->count; i++) {
        u8 *taken = pool->vtable->taken(pool, i);
        if (taken != NULL) {
            *taken = 0;
        }
    }
}
CLEAN_AS(func_02083c50, SlotPool_GiveBackAll)

/* func_02083c78: the destructor the derived classes call. */
void SlotPool_BaseDestruct(SlotPool *pool)
{
    pool->vtable = &data_020e1b70;
}
CLEAN_AS(func_02083c78, SlotPool_BaseDestruct)

/* func_02083c84 (vtable entry 1) */
SlotPool *SlotPool_BaseDestructDelete(SlotPool *pool)
{
    pool->vtable = &data_020e1b70;
    Heap_OperatorDeleteB(pool);
    return pool;
}
CLEAN_AS(func_02083c84, SlotPool_BaseDestructDelete)

/* func_02083c9c (vtable entry 0) */
void SlotPool_BaseDestructVirtual(SlotPool *pool)
{
    pool->vtable = &data_020e1b70;
}
CLEAN_AS(func_02083c9c, SlotPool_BaseDestructVirtual)

/* func_02083ca8: a pool of `count` entries. */
void SlotPool_BaseConstruct(SlotPool *pool, u32 count)
{
    pool->vtable = &data_020e1b70;
    pool->count = count;
}
CLEAN_AS(func_02083ca8, SlotPool_BaseConstruct)

/* func_02083cb4: the destructor of an entry's base part; nothing to do. */
void SlotPool_BaseEntryDestruct(void *entry)
{
    (void) entry;
}
CLEAN_AS(func_02083cb4, SlotPool_BaseEntryDestruct)

/* func_02083cb8: the constructor of an entry's base part: not taken. */
void SlotPool_BaseEntryConstruct(u8 *taken)
{
    *taken = 0;
}
CLEAN_AS(func_02083cb8, SlotPool_BaseEntryConstruct)
