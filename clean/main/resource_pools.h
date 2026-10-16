/* Three pools of memory that the game sets up together (func_02078da4, from the heap at
 * data_021fbe94) and takes down together (func_02078d88):
 *
 *   heap4   four frame heaps of 0x7ac bytes (data_021d12a4), as many created as
 *           func_02085f08 counts, from the heap data_021c9abc (func_0205c2a0);
 *   heap8   eight frame heaps of 0x7ac bytes (data_021d1310), from the heap data_021c9ac0
 *           (func_0205c300);
 *   block   blocks of 0x2f88 bytes (data_021d12dc, five cleared), as many allocated as
 *           func_02082240 (or the scene's two counts) and func_02085f08 add up to, from the heap
 *           data_021c9ac4 (func_0205c35c); a file is read into one.
 *
 * A slot (ResourceSlot) holds the number of the pool entry it was given; a new slot holds the
 * pool's size, which names no entry. The slots of the heap pools sit in the entries of the
 * tables at data_021d1e64 (heap4) and data_021d1ebc (heap8), those of the block pool at
 * data_021d1e8c. A model takes its heap from a heap slot (func_0202ee10, func_0202e318), and
 * func_0201a304 reads a file into the block of a block slot.
 *
 * ResourcePools_Startup makes, from the heap data_021fbe94, the unit heap data_021c9ab8
 * (func_0205c200) and then the block, heap8 and heap4 pools; ResourcePools_Shutdown destroys
 * the unit heap (func_0205c1e0) and then takes the pools down in the same order. */
#ifndef CLEAN_MAIN_RESOURCE_POOLS_H
#define CLEAN_MAIN_RESOURCE_POOLS_H

#include "autoload_2/heap.h"
#include "types.h"

#define RESOURCE_POOLS_HEAP4_COUNT 4
#define RESOURCE_POOLS_HEAP8_COUNT 8
#define RESOURCE_POOLS_BLOCK_COUNT 5
#define RESOURCE_POOLS_HEAP_SIZE 0x7ac   /* each frame heap's own bytes */
#define RESOURCE_POOLS_BLOCK_SIZE 0x2f88 /* each block */

/* The number of the pool entry a slot was given. */
typedef s32 ResourceSlot;

u32 ResourcePools_Heap4SlotHeap(const ResourceSlot *slot);
void ResourcePools_Heap4SlotBind(ResourceSlot *slot, int entry);
void ResourcePools_Heap4SlotDestruct(ResourceSlot *slot);
void ResourcePools_Heap4SlotConstruct(ResourceSlot *slot);
u32 ResourcePools_Heap8SlotHeap(const ResourceSlot *slot);
void ResourcePools_Heap8SlotBind(ResourceSlot *slot, int entry);
void ResourcePools_Heap8SlotDestruct(ResourceSlot *slot);
void ResourcePools_Heap8SlotConstruct(ResourceSlot *slot);
int ResourcePools_BlockSlotBlock(const ResourceSlot *slot);
void ResourcePools_BlockSlotLoad(const ResourceSlot *slot, const char *path);
void ResourcePools_BlockSlotSet(ResourceSlot *slot, int entry);
void ResourcePools_BlockSlotBind(ResourceSlot *slot, int entry);
void ResourcePools_BlockSlotDestruct(ResourceSlot *slot);
void ResourcePools_BlockSlotConstruct(ResourceSlot *slot);

void ResourcePools_Heap4Release(Heap **heaps);
void ResourcePools_Heap4Create(Heap **heaps);
u32 ResourcePools_Heap4At(Heap *const *heaps, int entry);
void ResourcePools_Heap4Shutdown(void);
void ResourcePools_Heap4Startup(Heap *parent);
void ResourcePools_Heap4Destruct(Heap **heaps);
void ResourcePools_Heap4Construct(Heap **heaps);

void ResourcePools_Heap8Release(Heap **heaps);
void ResourcePools_Heap8Create(Heap **heaps);
u32 ResourcePools_Heap8At(Heap *const *heaps, int entry);
void ResourcePools_Heap8Shutdown(void);
void ResourcePools_Heap8Startup(Heap *parent);
void ResourcePools_Heap8Destruct(Heap **heaps);
void ResourcePools_Heap8Construct(Heap **heaps);

void ResourcePools_BlockRelease(u8 **blocks);
void ResourcePools_BlockCreate(u8 **blocks);
u32 ResourcePools_BlockAt(u8 *const *blocks, int entry);
void ResourcePools_BlockShutdown(void);
void ResourcePools_BlockStartup(Heap *parent);
void ResourcePools_BlockDestruct(u8 **blocks);
void ResourcePools_BlockConstruct(u8 **blocks);

int ResourcePools_UnitSize31EC(void);
int ResourcePools_UnitSize2BCC(void);

void ResourcePools_Shutdown(void);
void ResourcePools_Startup(void);
int ResourcePools_SceneHeapCount(void);

#endif
