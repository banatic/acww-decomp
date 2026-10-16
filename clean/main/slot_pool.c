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
