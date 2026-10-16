/* Links to the entries of the game's slot pools (pool_link.h). */
#include "pool_link.h"

#include "autoload_2/heap.h"
#include "clean.h"

static_assert(offsetof(PoolLink, index) == 0x04, "link entry number");
static_assert(sizeof(PoolLink) == 0x08, "link size");
static_assert(offsetof(SlotPool, count) == 0x04, "pool size");

extern const PoolLinkVtable data_020e19dc; /* the part link's vtable */
extern const PoolLinkVtable data_020e1a40; /* the held item link's vtable */
extern const PoolLinkVtable data_020e1a68; /* the animation set link's vtable */

/* The pools. */
extern SlotPool *func_02083b00(void); /* data_021d1e48 */
extern SlotPool *func_0208399c(void); /* data_021d1ebc, the heap8 slots */
extern SlotPool *func_0208385c(void); /* data_021d1e64, the heap4 slots */
extern SlotPool *func_02083708(void); /* data_021d1e20 */
extern SlotPool *func_020835a0(void); /* data_021d1e8c, the block slots */
extern SlotPool *func_02083460(void); /* data_021d1e0c, the animation sets */
extern SlotPool *func_02083320(void); /* data_021d1e34, the parts */
extern SlotPool *func_020831c0(void); /* data_021d1f04, the held items */
/* Every entry of a pool given back: each "taken" byte cleared. */
extern void func_02083c50(SlotPool *pool);
/* An entry of a pool by number, past its "taken" byte; null for a number past the pool. */
extern int func_02083110(SlotPool *pool, u32 index);          /* a held item */
extern int func_020832c4(SlotPool *pool, u32 index);          /* a part */
extern int func_02083404(SlotPool *pool, u32 index);          /* an animation set */
extern int func_02083148(SlotPool *pool, u32 index, int arg); /* a held item set up from `arg` */

/* The link base class's constructor (no entry) and destructor. */
extern void func_02083100(PoolLink *link);
extern void func_020830d0(PoolLink *link);

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
    func_02083b00();
}
CLEAN_AS(func_02082c0c, PoolLink_Pool1E48)

/* func_02082c14 (vtable data_020e1a04) */
void PoolLink_Heap8Pool(void)
{
    func_0208399c();
}
CLEAN_AS(func_02082c14, PoolLink_Heap8Pool)

/* func_02082c1c (vtable data_020e19f0) */
void PoolLink_Heap4Pool(void)
{
    func_0208385c();
}
CLEAN_AS(func_02082c1c, PoolLink_Heap4Pool)

/* func_02082c24 (vtable data_020e1a54) */
void PoolLink_Pool1E20(void)
{
    func_02083708();
}
CLEAN_AS(func_02082c24, PoolLink_Pool1E20)

/* func_02082c2c (vtable data_020e1a7c) */
void PoolLink_BlockPool(void)
{
    func_020835a0();
}
CLEAN_AS(func_02082c2c, PoolLink_BlockPool)

/* func_02082c34 (vtable data_020e1a68) */
void PoolLink_AnimSetPool(void)
{
    func_02083460();
}
CLEAN_AS(func_02082c34, PoolLink_AnimSetPool)

/* func_02082c3c (vtable data_020e19dc) */
void PoolLink_PartPool(void)
{
    func_02083320();
}
CLEAN_AS(func_02082c3c, PoolLink_PartPool)

/* func_02082c44 (vtable data_020e1a40) */
void PoolLink_ItemPool(void)
{
    func_020831c0();
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
    func_02083c50(func_02083b00());
    func_02083c50(func_02083708());
    func_02083c50(func_020835a0());
    func_02083c50(func_02083460());
    func_02083c50(func_02083320());
    func_02083c50(func_020831c0());
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
    return func_02083110(pool, (u32) link->index);
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
    return func_02083148(pool, (u32) link->index, arg);
}
CLEAN_AS(func_02082cb8, PoolLink_ItemOpen)

/* func_02082ce4 (vtable entry 1) */
PoolLink *PoolLink_ItemDestructDelete(PoolLink *link)
{
    link->vtable = &data_020e1a40;
    func_020830d0(link);
    Heap_OperatorDeleteB(link);
    return link;
}
CLEAN_AS(func_02082ce4, PoolLink_ItemDestructDelete)

/* func_02082d04 (vtable entry 0) */
PoolLink *PoolLink_ItemDestruct(PoolLink *link)
{
    link->vtable = &data_020e1a40;
    func_020830d0(link);
    return link;
}
CLEAN_AS(func_02082d04, PoolLink_ItemDestruct)

/* func_02082d1c: a held item link with no entry. */
PoolLink *PoolLink_ItemConstruct(PoolLink *link)
{
    func_02083100(link);
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
    return func_020832c4(pool, (u32) link->index);
}
CLEAN_AS(func_02082d34, PoolLink_Part)

/* func_02082d58 (vtable entry 1) */
PoolLink *PoolLink_PartDestructDelete(PoolLink *link)
{
    link->vtable = &data_020e19dc;
    func_020830d0(link);
    Heap_OperatorDeleteB(link);
    return link;
}
CLEAN_AS(func_02082d58, PoolLink_PartDestructDelete)

/* func_02082d78 (vtable entry 0) */
PoolLink *PoolLink_PartDestruct(PoolLink *link)
{
    link->vtable = &data_020e19dc;
    func_020830d0(link);
    return link;
}
CLEAN_AS(func_02082d78, PoolLink_PartDestruct)

/* func_02082d90: a part link with no entry. */
PoolLink *PoolLink_PartConstruct(PoolLink *link)
{
    func_02083100(link);
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
    return func_02083404(pool, (u32) link->index);
}
CLEAN_AS(func_02082da8, PoolLink_AnimSet)

/* func_02082dcc (vtable entry 1) */
PoolLink *PoolLink_AnimSetDestructDelete(PoolLink *link)
{
    link->vtable = &data_020e1a68;
    func_020830d0(link);
    Heap_OperatorDeleteB(link);
    return link;
}
CLEAN_AS(func_02082dcc, PoolLink_AnimSetDestructDelete)
