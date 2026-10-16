/* Pools of frame heaps and file blocks, and the slots that name their entries
 * (resource_pools.h). */
#include "resource_pools.h"

#include "clean.h"

#define BLOCK_ALIGN 4

extern Heap *data_021d12a4[]; /* the heap4 pool */
extern Heap *data_021d1310[]; /* the heap8 pool */
extern u8 *data_021d12dc[];   /* the block pool */
extern Heap *data_021c9abc;   /* the heap the heap4 pool's heaps come from */
extern Heap *data_021c9ac0;   /* the heap the heap8 pool's heaps come from */
extern Heap *data_021c9ac4;   /* the heap the blocks come from */
extern u8 data_020e54a8;      /* 0: func_02082240 counts the blocks, else the scene's counts */

/* Create, and destroy, the heaps the pools come from, sized for them. */
extern unsigned int func_0205c2a0(int parent);
extern void func_0205c284(void);
extern unsigned int func_0205c300(int parent);
extern void func_0205c2e4(void);
extern unsigned int func_0205c35c(int parent);
extern void func_0205c340(void);

extern int func_02085f08(void);                                           /* the number of heap4 heaps and of some blocks */
extern int func_02082240(void);                                           /* 0 or 4 */
extern u8 func_020b65c4(void);                                            /* the current scene */
extern u8 func_020b5df8(unsigned int);                                    /* a scene's first count */
extern u8 func_020b5e04(unsigned int);                                    /* a scene's second count */
extern int func_02064af4(const void *path, const void *buffer, int size); /* reads a file */

/* Create, and destroy, the unit heap data_021c9ab8: as many units of
 * ResourcePools_UnitSize2BCC bytes as blocks are counted, and as many of
 * ResourcePools_UnitSize31EC bytes as func_02085f08 counts. */
extern unsigned int func_0205c200(int parent);
extern void func_0205c1e0(void);

extern Heap *data_021fbe94; /* the heap all the pools are made from */

/* ---- Slots */

/* func_02078a1c: the heap of the heap4 entry the slot names. */
u32 ResourcePools_Heap4SlotHeap(const ResourceSlot *slot)
{
    return ResourcePools_Heap4At(data_021d12a4, *slot);
}
CLEAN_AS(func_02078a1c, ResourcePools_Heap4SlotHeap)

/* func_02078a30: the slot is given heap4 entry `entry`, whose heap is emptied. */
void ResourcePools_Heap4SlotBind(ResourceSlot *slot, int entry)
{
    Heap_FreeAll((Heap *) (uintptr_t) ResourcePools_Heap4At(data_021d12a4, entry));
    *slot = entry;
}
CLEAN_AS(func_02078a30, ResourcePools_Heap4SlotBind)

/* func_02078a50: the destructor: does nothing. */
void ResourcePools_Heap4SlotDestruct(ResourceSlot *slot)
{
    (void) slot;
}
CLEAN_AS(func_02078a50, ResourcePools_Heap4SlotDestruct)

/* func_02078a54: a new slot names no entry. */
void ResourcePools_Heap4SlotConstruct(ResourceSlot *slot)
{
    *slot = RESOURCE_POOLS_HEAP4_COUNT;
}
CLEAN_AS(func_02078a54, ResourcePools_Heap4SlotConstruct)

/* func_02078a5c: the heap of the heap8 entry the slot names. */
u32 ResourcePools_Heap8SlotHeap(const ResourceSlot *slot)
{
    return ResourcePools_Heap8At(data_021d1310, *slot);
}
CLEAN_AS(func_02078a5c, ResourcePools_Heap8SlotHeap)

/* func_02078a70: the slot is given heap8 entry `entry`, whose heap is emptied. */
void ResourcePools_Heap8SlotBind(ResourceSlot *slot, int entry)
{
    Heap_FreeAll((Heap *) (uintptr_t) ResourcePools_Heap8At(data_021d1310, entry));
    *slot = entry;
}
CLEAN_AS(func_02078a70, ResourcePools_Heap8SlotBind)

/* func_02078a90: the destructor: does nothing. */
void ResourcePools_Heap8SlotDestruct(ResourceSlot *slot)
{
    (void) slot;
}
CLEAN_AS(func_02078a90, ResourcePools_Heap8SlotDestruct)

/* func_02078a94: a new slot names no entry. */
void ResourcePools_Heap8SlotConstruct(ResourceSlot *slot)
{
    *slot = RESOURCE_POOLS_HEAP8_COUNT;
}
CLEAN_AS(func_02078a94, ResourcePools_Heap8SlotConstruct)

/* func_02078a9c: the block of the entry the slot names. */
int ResourcePools_BlockSlotBlock(const ResourceSlot *slot)
{
    return (int) ResourcePools_BlockAt(data_021d12dc, *slot);
}
CLEAN_AS(func_02078a9c, ResourcePools_BlockSlotBlock)

/* func_02078ab0: the file `path` is read into the block of the entry the slot names. */
void ResourcePools_BlockSlotLoad(const ResourceSlot *slot, const char *path)
{
    u32 block = ResourcePools_BlockAt(data_021d12dc, *slot);
    func_02064af4(path, (const void *) (uintptr_t) block, RESOURCE_POOLS_BLOCK_SIZE);
}
CLEAN_AS(func_02078ab0, ResourcePools_BlockSlotLoad)

/* func_02078ad8 */
void ResourcePools_BlockSlotSet(ResourceSlot *slot, int entry)
{
    *slot = entry;
}
CLEAN_AS(func_02078ad8, ResourcePools_BlockSlotSet)

/* func_02078adc: the slot is given entry `entry`; the block keeps what it holds. */
void ResourcePools_BlockSlotBind(ResourceSlot *slot, int entry)
{
    ResourcePools_BlockSlotSet(slot, entry);
}
CLEAN_AS(func_02078adc, ResourcePools_BlockSlotBind)

/* func_02078ae4: the destructor: does nothing. */
void ResourcePools_BlockSlotDestruct(ResourceSlot *slot)
{
    (void) slot;
}
CLEAN_AS(func_02078ae4, ResourcePools_BlockSlotDestruct)

/* func_02078ae8: a new slot names no entry. */
void ResourcePools_BlockSlotConstruct(ResourceSlot *slot)
{
    *slot = RESOURCE_POOLS_BLOCK_COUNT;
}
CLEAN_AS(func_02078ae8, ResourcePools_BlockSlotConstruct)

/* ---- The heap4 pool */

/* Each heap that is there emptied and forgotten, then the heap they came from emptied. */
static void release_heaps(Heap **heaps, int count, Heap *parent)
{
    for (int i = 0; i < count; i++) {
        if (heaps[i] != NULL) {
            Heap_FreeAll(heaps[i]);
            heaps[i] = NULL;
        }
    }
    if (parent != NULL) {
        Heap_FreeAll(parent);
    }
}

/* func_02078af0: the heaps released, with the heap they came from (read first). */
void ResourcePools_Heap4Release(Heap **heaps)
{
    release_heaps(heaps, RESOURCE_POOLS_HEAP4_COUNT, data_021c9abc);
}
CLEAN_AS(func_02078af0, ResourcePools_Heap4Release)

/* func_02078b2c: as many heaps as func_02085f08 counts, from data_021c9abc (read first). */
void ResourcePools_Heap4Create(Heap **heaps)
{
    Heap *parent = data_021c9abc;
    int count = func_02085f08();
    for (int i = 0; i < count; i++) {
        heaps[i] = FrameHeap_Create(RESOURCE_POOLS_HEAP_SIZE, parent);
    }
}
CLEAN_AS(func_02078b2c, ResourcePools_Heap4Create)

/* func_02078b64 */
u32 ResourcePools_Heap4At(Heap *const *heaps, int entry)
{
    return (u32) (uintptr_t) heaps[entry];
}
CLEAN_AS(func_02078b64, ResourcePools_Heap4At)

/* func_02078b6c: the pool released, then the heap it came from destroyed. */
void ResourcePools_Heap4Shutdown(void)
{
    ResourcePools_Heap4Release(data_021d12a4);
    func_0205c284();
}
CLEAN_AS(func_02078b6c, ResourcePools_Heap4Shutdown)

/* func_02078b84: the heap data_021c9abc made from `parent`, the pool's heaps from it, and then
 * it shrunk to them. */
void ResourcePools_Heap4Startup(Heap *parent)
{
    func_0205c2a0((int) (uintptr_t) parent);
    ResourcePools_Heap4Create(data_021d12a4);
    if (data_021c9abc != NULL) {
        Heap_Adjust(data_021c9abc);
    }
}
CLEAN_AS(func_02078b84, ResourcePools_Heap4Startup)

/* func_02078bac: the destructor: does nothing. */
void ResourcePools_Heap4Destruct(Heap **heaps)
{
    (void) heaps;
}
CLEAN_AS(func_02078bac, ResourcePools_Heap4Destruct)

/* func_02078bb0: the constructor: no heaps. */
void ResourcePools_Heap4Construct(Heap **heaps)
{
    for (int i = 0; i < RESOURCE_POOLS_HEAP4_COUNT; i++) {
        heaps[i] = NULL;
    }
}
CLEAN_AS(func_02078bb0, ResourcePools_Heap4Construct)

/* ---- The heap8 pool */

/* func_02078bc0: the heaps released, with the heap they came from (read first). */
void ResourcePools_Heap8Release(Heap **heaps)
{
    release_heaps(heaps, RESOURCE_POOLS_HEAP8_COUNT, data_021c9ac0);
}
CLEAN_AS(func_02078bc0, ResourcePools_Heap8Release)

/* func_02078bfc: eight heaps from data_021c9ac0 (read first). */
void ResourcePools_Heap8Create(Heap **heaps)
{
    Heap *parent = data_021c9ac0;
    for (int i = 0; i < RESOURCE_POOLS_HEAP8_COUNT; i++) {
        heaps[i] = FrameHeap_Create(RESOURCE_POOLS_HEAP_SIZE, parent);
    }
}
CLEAN_AS(func_02078bfc, ResourcePools_Heap8Create)

/* func_02078c2c */
u32 ResourcePools_Heap8At(Heap *const *heaps, int entry)
{
    return (u32) (uintptr_t) heaps[entry];
}
CLEAN_AS(func_02078c2c, ResourcePools_Heap8At)

/* func_02078c34: the pool released, then the heap it came from destroyed. */
void ResourcePools_Heap8Shutdown(void)
{
    ResourcePools_Heap8Release(data_021d1310);
    func_0205c2e4();
}
CLEAN_AS(func_02078c34, ResourcePools_Heap8Shutdown)

/* func_02078c4c: the heap data_021c9ac0 made from `parent`, the pool's heaps from it, and then
 * it shrunk to them. */
void ResourcePools_Heap8Startup(Heap *parent)
{
    func_0205c300((int) (uintptr_t) parent);
    ResourcePools_Heap8Create(data_021d1310);
    if (data_021c9ac0 != NULL) {
        Heap_Adjust(data_021c9ac0);
    }
}
CLEAN_AS(func_02078c4c, ResourcePools_Heap8Startup)

/* func_02078c74: the destructor: does nothing. */
void ResourcePools_Heap8Destruct(Heap **heaps)
{
    (void) heaps;
}
CLEAN_AS(func_02078c74, ResourcePools_Heap8Destruct)

/* func_02078c78: the constructor: no heaps. */
void ResourcePools_Heap8Construct(Heap **heaps)
{
    for (int i = 0; i < RESOURCE_POOLS_HEAP8_COUNT; i++) {
        heaps[i] = NULL;
    }
}
CLEAN_AS(func_02078c78, ResourcePools_Heap8Construct)

/* ---- The block pool */

/* func_02078c88: the five blocks forgotten, and the heap they came from (read first) emptied.
 * QUIRK: five entries are cleared here and by ResourcePools_BlockConstruct, while
 * ResourcePools_BlockCreate fills as many as it counts. */
void ResourcePools_BlockRelease(u8 **blocks)
{
    Heap *heap = data_021c9ac4;
    for (int i = 0; i < RESOURCE_POOLS_BLOCK_COUNT; i++) {
        blocks[i] = NULL;
    }
    if (heap != NULL) {
        Heap_FreeAll(heap);
    }
}
CLEAN_AS(func_02078c88, ResourcePools_BlockRelease)

/* func_02078cb0: blocks from data_021c9ac4 (read first), aligned to 4: while data_020e54a8 is
 * 0 as many as func_02082240 gives, else the current scene's first count less its second; and
 * as many again as func_02085f08 counts. */
void ResourcePools_BlockCreate(u8 **blocks)
{
    Heap *heap = data_021c9ac4;
    int count;
    if (data_020e54a8 == 0) {
        count = func_02082240();
    } else {
        int first = func_020b5df8(func_020b65c4());
        count = first - func_020b5e04(func_020b65c4());
    }
    count += func_02085f08();
    for (int i = 0; i < count; i++) {
        blocks[i] = Heap_AllocAligned(heap, RESOURCE_POOLS_BLOCK_SIZE, BLOCK_ALIGN);
    }
}
CLEAN_AS(func_02078cb0, ResourcePools_BlockCreate)

/* func_02078d1c */
u32 ResourcePools_BlockAt(u8 *const *blocks, int entry)
{
    return (u32) (uintptr_t) blocks[entry];
}
CLEAN_AS(func_02078d1c, ResourcePools_BlockAt)

/* func_02078d24: the pool released, then the heap it came from destroyed. */
void ResourcePools_BlockShutdown(void)
{
    ResourcePools_BlockRelease(data_021d12dc);
    func_0205c340();
}
CLEAN_AS(func_02078d24, ResourcePools_BlockShutdown)

/* func_02078d3c: the heap data_021c9ac4 made from `parent`, the blocks from it, and then it
 * shrunk to them. */
void ResourcePools_BlockStartup(Heap *parent)
{
    func_0205c35c((int) (uintptr_t) parent);
    ResourcePools_BlockCreate(data_021d12dc);
    if (data_021c9ac4 != NULL) {
        Heap_Adjust(data_021c9ac4);
    }
}
CLEAN_AS(func_02078d3c, ResourcePools_BlockStartup)

/* func_02078d64: the destructor: does nothing. */
void ResourcePools_BlockDestruct(u8 **blocks)
{
    (void) blocks;
}
CLEAN_AS(func_02078d64, ResourcePools_BlockDestruct)

/* func_02078d68: the constructor: no blocks. */
void ResourcePools_BlockConstruct(u8 **blocks)
{
    for (int i = 0; i < RESOURCE_POOLS_BLOCK_COUNT; i++) {
        blocks[i] = NULL;
    }
}
CLEAN_AS(func_02078d68, ResourcePools_BlockConstruct)

/* func_02078d78: 12780 (0x31ec), the bytes func_0205c200 reserves for each of the units
 * func_02085f08 counts (next to ResourcePools_UnitSize2BCC's 11212 for the others). */
int ResourcePools_UnitSize31EC(void)
{
    return 0x31ec;
}
CLEAN_AS(func_02078d78, ResourcePools_UnitSize31EC)

/* func_02078d80: 11212 (0x2bcc), the bytes func_0205c200 reserves for each block counted. */
int ResourcePools_UnitSize2BCC(void)
{
    return 0x2bcc;
}
CLEAN_AS(func_02078d80, ResourcePools_UnitSize2BCC)

/* ---- All of them */

/* func_02078d88: the unit heap destroyed, then the pools taken down in the order they were made. */
void ResourcePools_Shutdown(void)
{
    func_0205c1e0();
    ResourcePools_BlockShutdown();
    ResourcePools_Heap8Shutdown();
    ResourcePools_Heap4Shutdown();
}
CLEAN_AS(func_02078d88, ResourcePools_Shutdown)

/* func_02078da4: the unit heap and the three pools made from the heap data_021fbe94. */
void ResourcePools_Startup(void)
{
    func_0205c200((int) (uintptr_t) data_021fbe94);
    ResourcePools_BlockStartup(data_021fbe94);
    ResourcePools_Heap8Startup(data_021fbe94);
    ResourcePools_Heap4Startup(data_021fbe94);
}
CLEAN_AS(func_02078da4, ResourcePools_Startup)
