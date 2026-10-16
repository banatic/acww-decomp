/* Links to the entries of the game's slot pools.
 *
 * A slot pool (a vtable, then its number of entries at 4) hands out its entries by number; its
 * vtable entry 4 gives the address of an entry's "taken" byte (or null). The game keeps eight
 * of them, each behind a function that returns it:
 *
 *   data_021d1e48 (func_02083b00)  data_021d1e20 (func_02083708)
 *   data_021d1e8c (func_020835a0)  the block slots (resource_pools.h)
 *   data_021d1e0c (func_02083460)  2-byte entries: animation sets (scene_face.c)
 *   data_021d1e34 (func_02083320)  2-byte entries: parts (scene_face.c)
 *   data_021d1f04 (func_020831c0)  0x6c-byte entries: held items (held_item_link.h)
 *   data_021d1e64 (func_0208385c)  the heap4 slots (resource_pools.h)
 *   data_021d1ebc (func_0208399c)  the heap8 slots (resource_pools.h)
 *
 * A link (8 bytes) holds the number of the entry it took, -1 for none. All links derive from
 * one base class (vtable data_020e1a2c: func_02083100 constructs it, func_020830d0 destroys
 * it, func_0208308c takes an entry, func_02083068 gives it back); each class of link adds as
 * its vtable entry 2 the function that returns its pool:
 *
 *   vtable          pool           entry 2
 *   data_020e19dc   parts          PoolLink_PartPool
 *   data_020e19f0   heap4 slots    PoolLink_Heap4Pool
 *   data_020e1a04   heap8 slots    PoolLink_Heap8Pool
 *   data_020e1a18   data_021d1e48  PoolLink_Pool1E48
 *   data_020e1a40   held items     PoolLink_ItemPool
 *   data_020e1a54   data_021d1e20  PoolLink_Pool1E20
 *   data_020e1a68   animation sets PoolLink_AnimSetPool
 *   data_020e1a7c   block slots    PoolLink_BlockPool
 *
 * At the start and at the end of a scene every entry of six of the pools (all but the heap
 * slots) is given back at once (PoolLink_FreeAll). */
#ifndef CLEAN_MAIN_POOL_LINK_H
#define CLEAN_MAIN_POOL_LINK_H

#include "types.h"

#define POOL_LINK_NONE (-1)

typedef struct SlotPool SlotPool;

typedef struct SlotPoolVtable {
    u32 destruct;
    u32 destruct_delete;
    void (*take)(SlotPool *pool, int index);      /* sets entry `index` up as taken */
    void (*give_back)(SlotPool *pool, int index); /* clears entry `index`'s "taken" byte */
    u8 *(*taken)(SlotPool *pool, int index);      /* the entry's "taken" byte, or null */
} SlotPoolVtable;

struct SlotPool {
    const SlotPoolVtable *vtable;
    u32 count; /* 0x04 */
};

typedef struct PoolLink PoolLink;

typedef struct PoolLinkVtable {
    u32 destruct;        /* returns the link */
    u32 destruct_delete; /* destructs and frees the link */
    SlotPool *(*pool)(PoolLink *link);
} PoolLinkVtable;

struct PoolLink {
    const PoolLinkVtable *vtable;
    s8 index; /* 0x04: the entry taken, POOL_LINK_NONE for none */
    u8 unused_05[3];
};

void PoolLink_Pool1E48(void);
void PoolLink_Heap8Pool(void);
void PoolLink_Heap4Pool(void);
void PoolLink_Pool1E20(void);
void PoolLink_BlockPool(void);
void PoolLink_AnimSetPool(void);
void PoolLink_PartPool(void);
void PoolLink_ItemPool(void);
void PoolLink_FreeAllAtSceneEnd(void);
void PoolLink_FreeAllAtSceneStart(void);
void PoolLink_FreeAll(void);

int PoolLink_Item(PoolLink *link);
int PoolLink_ItemOpen(PoolLink *link, int arg);
PoolLink *PoolLink_ItemDestructDelete(PoolLink *link);
PoolLink *PoolLink_ItemDestruct(PoolLink *link);
PoolLink *PoolLink_ItemConstruct(PoolLink *link);
int PoolLink_Part(PoolLink *link);
PoolLink *PoolLink_PartDestructDelete(PoolLink *link);
PoolLink *PoolLink_PartDestruct(PoolLink *link);
PoolLink *PoolLink_PartConstruct(PoolLink *link);
int PoolLink_AnimSet(PoolLink *link);
PoolLink *PoolLink_AnimSetDestructDelete(PoolLink *link);
PoolLink *PoolLink_AnimSetDestruct(PoolLink *link);
PoolLink *PoolLink_AnimSetConstruct(PoolLink *link);
int PoolLink_Block(PoolLink *link);
PoolLink *PoolLink_BlockDestructDelete(PoolLink *link);
PoolLink *PoolLink_BlockDestruct(PoolLink *link);
PoolLink *PoolLink_BlockConstruct(PoolLink *link);
int PoolLink_Pool1E20Entry(PoolLink *link);
PoolLink *PoolLink_Pool1E20DestructDelete(PoolLink *link);
PoolLink *PoolLink_Pool1E20Destruct(PoolLink *link);
PoolLink *PoolLink_Pool1E20Construct(PoolLink *link);
int PoolLink_Heap4(PoolLink *link);
PoolLink *PoolLink_Heap4DestructDelete(PoolLink *link);
PoolLink *PoolLink_Heap4Destruct(PoolLink *link);
PoolLink *PoolLink_Heap4Construct(PoolLink *link);
int PoolLink_Heap8(PoolLink *link);
PoolLink *PoolLink_Heap8DestructDelete(PoolLink *link);
PoolLink *PoolLink_Heap8Destruct(PoolLink *link);
PoolLink *PoolLink_Heap8Construct(PoolLink *link);
int PoolLink_Pool1E48Byte(PoolLink *link, int which);
PoolLink *PoolLink_Pool1E48DestructDelete(PoolLink *link);
PoolLink *PoolLink_Pool1E48Destruct(PoolLink *link);
PoolLink *PoolLink_Pool1E48Construct(PoolLink *link);
void PoolLink_Release(PoolLink *link);
int PoolLink_Take(PoolLink *link);
void PoolLink_BaseDestruct(PoolLink *link);
PoolLink *PoolLink_BaseDestructDelete(PoolLink *link);
void PoolLink_BaseDestructVirtual(PoolLink *link);
void PoolLink_BaseConstruct(PoolLink *link);

#endif
