/* Links to the entries of the game's slot pools (pool_link.h). */
#include "pool_link.h"

#include "autoload_2/heap.h"
#include "clean.h"
#include "slot_pool.h"

static_assert(offsetof(PoolLink, index) == 0x04, "link entry number");
static_assert(sizeof(PoolLink) == 0x08, "link size");
static_assert(offsetof(SlotPool, count) == 0x04, "pool size");

extern const PoolLinkVtable data_020e19dc; /* the part link's vtable */
extern const PoolLinkVtable data_020e1a40; /* the held item link's vtable */
extern const PoolLinkVtable data_020e1a68; /* the animation set link's vtable */

/* The pool of a link, from its vtable entry 2. */
static SlotPool *pool_link_pool(PoolLink *link)
{
    return link->vtable->pool(link);
}

/* ---- The pools of the classes of link (vtable entry 2)
 *
 * QUIRK: the matching source declares these without a result; in the ROM each is a tail call, so
 * the caller gets the pool. */

/* func_02082c0c (vtable data_020e1a18) */
void PoolLink_Pool1E48(void)
{
    SlotPool_Speakers();
}
CLEAN_AS(func_02082c0c, PoolLink_Pool1E48)

/* func_02082c14 (vtable data_020e1a04) */
void PoolLink_Heap8Pool(void)
{
    SlotPool_Heap8();
}
CLEAN_AS(func_02082c14, PoolLink_Heap8Pool)

/* func_02082c1c (vtable data_020e19f0) */
void PoolLink_Heap4Pool(void)
{
    SlotPool_Heap4();
}
CLEAN_AS(func_02082c1c, PoolLink_Heap4Pool)

/* func_02082c24 (vtable data_020e1a54) */
void PoolLink_Pool1E20(void)
{
    SlotPool_Clothes();
}
CLEAN_AS(func_02082c24, PoolLink_Pool1E20)

/* func_02082c2c (vtable data_020e1a7c) */
void PoolLink_BlockPool(void)
{
    SlotPool_Blocks();
}
CLEAN_AS(func_02082c2c, PoolLink_BlockPool)

/* func_02082c34 (vtable data_020e1a68) */
void PoolLink_AnimSetPool(void)
{
    SlotPool_AnimSets();
}
CLEAN_AS(func_02082c34, PoolLink_AnimSetPool)

/* func_02082c3c (vtable data_020e19dc) */
void PoolLink_PartPool(void)
{
    SlotPool_Parts();
}
CLEAN_AS(func_02082c3c, PoolLink_PartPool)

/* func_02082c44 (vtable data_020e1a40) */
void PoolLink_ItemPool(void)
{
    SlotPool_Items();
}
CLEAN_AS(func_02082c44, PoolLink_ItemPool)

/* ---- Giving back every entry */

/* func_02082c4c: PoolLink_FreeAll, when a scene ends (func_020b6ae0). */
void PoolLink_FreeAllAtSceneEnd(void)
{
    PoolLink_FreeAll();
}
CLEAN_AS(func_02082c4c, PoolLink_FreeAllAtSceneEnd)

/* func_02082c54: PoolLink_FreeAll, when a scene starts (func_020b6dcc). */
void PoolLink_FreeAllAtSceneStart(void)
{
    PoolLink_FreeAll();
}
CLEAN_AS(func_02082c54, PoolLink_FreeAllAtSceneStart)

/* func_02082c5c: every entry of the pools data_021d1e48, data_021d1e20, the block slots, the
 * animation sets, the parts and the held items given back, in that order. */
void PoolLink_FreeAll(void)
{
    SlotPool_GiveBackAll((SlotPool *) SlotPool_Speakers());
    SlotPool_GiveBackAll((SlotPool *) SlotPool_Clothes());
    SlotPool_GiveBackAll((SlotPool *) SlotPool_Blocks());
    SlotPool_GiveBackAll((SlotPool *) SlotPool_AnimSets());
    SlotPool_GiveBackAll((SlotPool *) SlotPool_Parts());
    SlotPool_GiveBackAll((SlotPool *) SlotPool_Items());
}
CLEAN_AS(func_02082c5c, PoolLink_FreeAll)

/* ---- The held item link (vtable data_020e1a40) */

/* func_02082c98: the held item the link's entry holds, or null (no pool, or no entry). */
int PoolLink_Item(PoolLink *link)
{
    SlotPool *pool = pool_link_pool(link);
    if (pool == NULL) {
        return 0;
    }
    return (int) (uintptr_t) SlotPool_Item((SlotPoolItems *) pool, (u32) link->index);
}
CLEAN_AS(func_02082c98, PoolLink_Item)

/* func_02082cb8: the held item of the link's entry set up from `arg` (func_02083148); whether
 * the link has an entry. */
int PoolLink_ItemOpen(PoolLink *link, int arg)
{
    SlotPool *pool = pool_link_pool(link);
    if (pool == NULL) {
        return 0;
    }
    return SlotPool_ItemTakeWith((SlotPoolItems *) pool, (u32) link->index, (const u16 *) (uintptr_t) arg);
}
CLEAN_AS(func_02082cb8, PoolLink_ItemOpen)

/* func_02082ce4 (vtable entry 1) */
PoolLink *PoolLink_ItemDestructDelete(PoolLink *link)
{
    link->vtable = &data_020e1a40;
    PoolLink_BaseDestruct(link);
    Heap_OperatorDeleteB(link);
    return link;
}
CLEAN_AS(func_02082ce4, PoolLink_ItemDestructDelete)

/* func_02082d04 (vtable entry 0) */
PoolLink *PoolLink_ItemDestruct(PoolLink *link)
{
    link->vtable = &data_020e1a40;
    PoolLink_BaseDestruct(link);
    return link;
}
CLEAN_AS(func_02082d04, PoolLink_ItemDestruct)

/* func_02082d1c: a held item link with no entry. */
PoolLink *PoolLink_ItemConstruct(PoolLink *link)
{
    PoolLink_BaseConstruct(link);
    link->vtable = &data_020e1a40;
    return link;
}
CLEAN_AS(func_02082d1c, PoolLink_ItemConstruct)

/* ---- The part link (vtable data_020e19dc) */

/* func_02082d34: the part the link's entry holds, or null. */
int PoolLink_Part(PoolLink *link)
{
    SlotPool *pool = pool_link_pool(link);
    if (pool == NULL) {
        return 0;
    }
    return (int) (uintptr_t) SlotPool_Part((SlotPoolBytes *) pool, (u32) link->index);
}
CLEAN_AS(func_02082d34, PoolLink_Part)

/* func_02082d58 (vtable entry 1) */
PoolLink *PoolLink_PartDestructDelete(PoolLink *link)
{
    link->vtable = &data_020e19dc;
    PoolLink_BaseDestruct(link);
    Heap_OperatorDeleteB(link);
    return link;
}
CLEAN_AS(func_02082d58, PoolLink_PartDestructDelete)

/* func_02082d78 (vtable entry 0) */
PoolLink *PoolLink_PartDestruct(PoolLink *link)
{
    link->vtable = &data_020e19dc;
    PoolLink_BaseDestruct(link);
    return link;
}
CLEAN_AS(func_02082d78, PoolLink_PartDestruct)

/* func_02082d90: a part link with no entry. */
PoolLink *PoolLink_PartConstruct(PoolLink *link)
{
    PoolLink_BaseConstruct(link);
    link->vtable = &data_020e19dc;
    return link;
}
CLEAN_AS(func_02082d90, PoolLink_PartConstruct)

/* ---- The animation set link (vtable data_020e1a68) */

/* func_02082da8: the animation set the link's entry holds, or null. */
int PoolLink_AnimSet(PoolLink *link)
{
    SlotPool *pool = pool_link_pool(link);
    if (pool == NULL) {
        return 0;
    }
    return (int) (uintptr_t) SlotPool_AnimSet((SlotPoolBytes *) pool, (u32) link->index);
}
CLEAN_AS(func_02082da8, PoolLink_AnimSet)

/* func_02082dcc (vtable entry 1) */
PoolLink *PoolLink_AnimSetDestructDelete(PoolLink *link)
{
    link->vtable = &data_020e1a68;
    PoolLink_BaseDestruct(link);
    Heap_OperatorDeleteB(link);
    return link;
}
CLEAN_AS(func_02082dcc, PoolLink_AnimSetDestructDelete)

/* func_02082dec (vtable entry 0) */
PoolLink *PoolLink_AnimSetDestruct(PoolLink *link)
{
    link->vtable = &data_020e1a68;
    PoolLink_BaseDestruct(link);
    return link;
}
CLEAN_AS(func_02082dec, PoolLink_AnimSetDestruct)

/* func_02082e04: an animation set link with no entry. */
PoolLink *PoolLink_AnimSetConstruct(PoolLink *link)
{
    PoolLink_BaseConstruct(link);
    link->vtable = &data_020e1a68;
    return link;
}
CLEAN_AS(func_02082e04, PoolLink_AnimSetConstruct)

/* The entries of the pools the remaining classes of link stand for, by number, past their
 * "taken" byte; null for a number past the pool. */
extern int func_02083544(SlotPool *pool, u32 index); /* a block slot */

extern const PoolLinkVtable data_020e1a7c; /* the block slot link's vtable */
extern const PoolLinkVtable data_020e1a54; /* the data_021d1e20 link's vtable */
extern const PoolLinkVtable data_020e19f0; /* the heap4 slot link's vtable */
extern const PoolLinkVtable data_020e1a04; /* the heap8 slot link's vtable */
extern const PoolLinkVtable data_020e1a18; /* the data_021d1e48 link's vtable */
extern const PoolLinkVtable data_020e1a2c; /* the link base class's vtable */

/* ---- The block slot link (vtable data_020e1a7c) */

/* func_02082e1c: the block slot the link's entry holds, or null. */
int PoolLink_Block(PoolLink *link)
{
    SlotPool *pool = pool_link_pool(link);
    if (pool == NULL) {
        return 0;
    }
    return (int) (uintptr_t) SlotPool_BlockSlot((SlotPoolBlocks *) pool, (u32) link->index);
}
CLEAN_AS(func_02082e1c, PoolLink_Block)

/* func_02082e40 (vtable entry 1) */
PoolLink *PoolLink_BlockDestructDelete(PoolLink *link)
{
    link->vtable = &data_020e1a7c;
    PoolLink_BaseDestruct(link);
    Heap_OperatorDeleteB(link);
    return link;
}
CLEAN_AS(func_02082e40, PoolLink_BlockDestructDelete)

/* func_02082e60 (vtable entry 0) */
PoolLink *PoolLink_BlockDestruct(PoolLink *link)
{
    link->vtable = &data_020e1a7c;
    PoolLink_BaseDestruct(link);
    return link;
}
CLEAN_AS(func_02082e60, PoolLink_BlockDestruct)

/* func_02082e78: a block slot link with no entry. */
PoolLink *PoolLink_BlockConstruct(PoolLink *link)
{
    PoolLink_BaseConstruct(link);
    link->vtable = &data_020e1a7c;
    return link;
}
CLEAN_AS(func_02082e78, PoolLink_BlockConstruct)

/* ---- The data_021d1e20 link (vtable data_020e1a54) */

/* func_02082e90: the entry of data_021d1e20 the link's entry holds, or null. */
int PoolLink_Pool1E20Entry(PoolLink *link)
{
    SlotPool *pool = pool_link_pool(link);
    if (pool == NULL) {
        return 0;
    }
    return (int) (uintptr_t) SlotPool_Cloth((SlotPoolBytes *) pool, (u32) link->index);
}
CLEAN_AS(func_02082e90, PoolLink_Pool1E20Entry)

/* func_02082eb4 (vtable entry 1) */
PoolLink *PoolLink_Pool1E20DestructDelete(PoolLink *link)
{
    link->vtable = &data_020e1a54;
    PoolLink_BaseDestruct(link);
    Heap_OperatorDeleteB(link);
    return link;
}
CLEAN_AS(func_02082eb4, PoolLink_Pool1E20DestructDelete)

/* func_02082ed4 (vtable entry 0) */
PoolLink *PoolLink_Pool1E20Destruct(PoolLink *link)
{
    link->vtable = &data_020e1a54;
    PoolLink_BaseDestruct(link);
    return link;
}
CLEAN_AS(func_02082ed4, PoolLink_Pool1E20Destruct)

/* func_02082eec: a data_021d1e20 link with no entry. */
PoolLink *PoolLink_Pool1E20Construct(PoolLink *link)
{
    PoolLink_BaseConstruct(link);
    link->vtable = &data_020e1a54;
    return link;
}
CLEAN_AS(func_02082eec, PoolLink_Pool1E20Construct)

/* ---- The heap4 slot link (vtable data_020e19f0) */

/* func_02082f04: the heap4 slot the link's entry holds, or null. */
int PoolLink_Heap4(PoolLink *link)
{
    SlotPool *pool = pool_link_pool(link);
    if (pool == NULL) {
        return 0;
    }
    return (int) (uintptr_t) SlotPool_Heap4Slot((SlotPoolHeap4 *) pool, (u32) link->index);
}
CLEAN_AS(func_02082f04, PoolLink_Heap4)

/* func_02082f28 (vtable entry 1) */
PoolLink *PoolLink_Heap4DestructDelete(PoolLink *link)
{
    link->vtable = &data_020e19f0;
    PoolLink_BaseDestruct(link);
    Heap_OperatorDeleteB(link);
    return link;
}
CLEAN_AS(func_02082f28, PoolLink_Heap4DestructDelete)

/* func_02082f48 (vtable entry 0) */
PoolLink *PoolLink_Heap4Destruct(PoolLink *link)
{
    link->vtable = &data_020e19f0;
    PoolLink_BaseDestruct(link);
    return link;
}
CLEAN_AS(func_02082f48, PoolLink_Heap4Destruct)

/* func_02082f60: a heap4 slot link with no entry. */
PoolLink *PoolLink_Heap4Construct(PoolLink *link)
{
    PoolLink_BaseConstruct(link);
    link->vtable = &data_020e19f0;
    return link;
}
CLEAN_AS(func_02082f60, PoolLink_Heap4Construct)

/* ---- The heap8 slot link (vtable data_020e1a04) */

/* func_02082f78: the heap8 slot the link's entry holds, or null. */
int PoolLink_Heap8(PoolLink *link)
{
    SlotPool *pool = pool_link_pool(link);
    if (pool == NULL) {
        return 0;
    }
    return (int) (uintptr_t) SlotPool_Heap8Slot((SlotPoolHeap8 *) pool, (u32) link->index);
}
CLEAN_AS(func_02082f78, PoolLink_Heap8)

/* func_02082f9c (vtable entry 1) */
PoolLink *PoolLink_Heap8DestructDelete(PoolLink *link)
{
    link->vtable = &data_020e1a04;
    PoolLink_BaseDestruct(link);
    Heap_OperatorDeleteB(link);
    return link;
}
CLEAN_AS(func_02082f9c, PoolLink_Heap8DestructDelete)

/* func_02082fbc (vtable entry 0) */
PoolLink *PoolLink_Heap8Destruct(PoolLink *link)
{
    link->vtable = &data_020e1a04;
    PoolLink_BaseDestruct(link);
    return link;
}
CLEAN_AS(func_02082fbc, PoolLink_Heap8Destruct)

/* func_02082fd4: a heap8 slot link with no entry. */
PoolLink *PoolLink_Heap8Construct(PoolLink *link)
{
    PoolLink_BaseConstruct(link);
    link->vtable = &data_020e1a04;
    return link;
}
CLEAN_AS(func_02082fd4, PoolLink_Heap8Construct)

/* ---- The data_021d1e48 link (vtable data_020e1a18)
 *
 * An entry of data_021d1e48 is four bytes: its "taken" byte, then three values (an actor's
 * speaking animations, speaker_anim.h). */

/* func_02082fec: the address of value `which` of the link's entry, or null. */
int PoolLink_Pool1E48Byte(PoolLink *link, int which)
{
    SlotPool *pool = pool_link_pool(link);
    if (pool == NULL) {
        return 0;
    }
    return (int) (uintptr_t) (SlotPool_SpeakerAnim((SlotPoolSpeakers *) pool, (u32) link->index, (u32) which));
}
CLEAN_AS(func_02082fec, PoolLink_Pool1E48Byte)

/* func_02083018 (vtable entry 1) */
PoolLink *PoolLink_Pool1E48DestructDelete(PoolLink *link)
{
    link->vtable = &data_020e1a18;
    PoolLink_BaseDestruct(link);
    Heap_OperatorDeleteB(link);
    return link;
}
CLEAN_AS(func_02083018, PoolLink_Pool1E48DestructDelete)

/* func_02083038 (vtable entry 0) */
PoolLink *PoolLink_Pool1E48Destruct(PoolLink *link)
{
    link->vtable = &data_020e1a18;
    PoolLink_BaseDestruct(link);
    return link;
}
CLEAN_AS(func_02083038, PoolLink_Pool1E48Destruct)

/* func_02083050: a data_021d1e48 link with no entry. */
PoolLink *PoolLink_Pool1E48Construct(PoolLink *link)
{
    PoolLink_BaseConstruct(link);
    link->vtable = &data_020e1a18;
    return link;
}
CLEAN_AS(func_02083050, PoolLink_Pool1E48Construct)

/* ---- The link base class (vtable data_020e1a2c) */

/* func_02083068: gives the link's entry back to its pool (pool vtable entry 3) and leaves the
 * link with none. A link with no entry hands the pool POOL_LINK_NONE, which every pool's entry 3
 * ignores as a number past its end. */
void PoolLink_Release(PoolLink *link)
{
    SlotPool *pool = pool_link_pool(link);
    if (pool == NULL) {
        return;
    }
    pool->vtable->give_back(pool, link->index);
    link->index = POOL_LINK_NONE;
}
CLEAN_AS(func_02083068, PoolLink_Release)

/* func_0208308c: makes sure the link has an entry: one that has none takes the first free entry
 * of its pool and sets it up (pool vtable entry 2). Whether the link has an entry now; 0 when it
 * has no pool or the pool is full. */
int PoolLink_Take(PoolLink *link)
{
    SlotPool *pool = pool_link_pool(link);
    if (pool == NULL) {
        return 0;
    }
    if (link->index != POOL_LINK_NONE) {
        return 1;
    }
    int free_index = SlotPool_FirstFree(pool);
    if ((u32) free_index >= pool->count) {
        return 0;
    }
    link->index = (s8) free_index;
    pool->vtable->take(pool, link->index);
    return 1;
}
CLEAN_AS(func_0208308c, PoolLink_Take)

/* func_020830d0: the base class's part of every link's destructor. */
void PoolLink_BaseDestruct(PoolLink *link)
{
    link->vtable = &data_020e1a2c;
}
CLEAN_AS(func_020830d0, PoolLink_BaseDestruct)

/* func_020830dc (base vtable entry 1) */
PoolLink *PoolLink_BaseDestructDelete(PoolLink *link)
{
    link->vtable = &data_020e1a2c;
    Heap_OperatorDeleteB(link);
    return link;
}
CLEAN_AS(func_020830dc, PoolLink_BaseDestructDelete)

/* func_020830f4 (base vtable entry 0) */
void PoolLink_BaseDestructVirtual(PoolLink *link)
{
    link->vtable = &data_020e1a2c;
}
CLEAN_AS(func_020830f4, PoolLink_BaseDestructVirtual)

/* func_02083100: the base class's part of every link's constructor: no entry. */
void PoolLink_BaseConstruct(PoolLink *link)
{
    link->vtable = &data_020e1a2c;
    link->index = POOL_LINK_NONE;
}
CLEAN_AS(func_02083100, PoolLink_BaseConstruct)
