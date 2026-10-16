/* The heaps a scene's systems take their memory from: each made from a parent heap (the
 * scene's, data_021fbe94) at the size its system needs, kept in a word of its own, and
 * destroyed (the word cleared) when the scene ends.
 *
 * Most are frame heaps (FrameHeap_Create) sized for a number of units of a system's own size,
 * each rounded up to 4 bytes; for units that are themselves frame heaps, or blocks made like
 * them, 0x48 bytes more each (SCENE_HEAPS_FRAME_HEAP_COST: a heap object and NNS's frame heap
 * header). The counts come from the scene (SceneTables_FirstCount, _SecondCount,
 * ResourcePools_SceneHeapCount) or from the session's number of players. Four are expanded
 * heaps (ExpHeap_Create): the field actors', and two that model pools (func_0209d180) are
 * given as their allocate and release functions.
 *
 * Those whose system is not named yet are named after the word that keeps them; the loaders
 * that create them come in pairs with a release in scene_process.c. */
#ifndef CLEAN_MAIN_SCENE_HEAPS_H
#define CLEAN_MAIN_SCENE_HEAPS_H

#include "autoload_2/heap.h"
#include "types.h"

void SceneHeaps_DestroyAcreRooms(void);
void SceneHeaps_CreateAcreRooms(Heap *parent);
void SceneHeaps_DestroyAcreTown(void);
void SceneHeaps_CreateAcreTown(Heap *parent);
void SceneHeaps_DestroyFieldActors(void);
void SceneHeaps_CreateFieldActors(unsigned int parent);
void SceneHeaps_DestroyUnits(void);
unsigned int SceneHeaps_CreateUnits(Heap *parent);
void SceneHeaps_DestroyHeap4Pool(void);
unsigned int SceneHeaps_CreateHeap4Pool(Heap *parent);
void SceneHeaps_DestroyHeap8Pool(void);
unsigned int SceneHeaps_CreateHeap8Pool(Heap *parent);
void SceneHeaps_DestroyBlockPool(void);
unsigned int SceneHeaps_CreateBlockPool(Heap *parent);
void SceneHeaps_Destroy021c9ac8(void);
void SceneHeaps_Create021c9ac8(Heap *parent);
void SceneHeaps_Destroy021c9acc(void);
unsigned int SceneHeaps_Create021c9acc(Heap *parent);
void SceneHeaps_Destroy021c9ad0(void);
unsigned int SceneHeaps_Create021c9ad0(Heap *parent);
void SceneHeaps_Destroy021c9ad4(void);
unsigned int SceneHeaps_Create021c9ad4(Heap *parent);
void SceneHeaps_Destroy021c9ad8(void);
void SceneHeaps_Create021c9ad8(Heap *parent);
void SceneHeaps_Destroy021c9adc(void);
unsigned int SceneHeaps_Create021c9adc(Heap *parent);
void SceneHeaps_Destroy021c9ae0(void);
unsigned int SceneHeaps_Create021c9ae0(Heap *parent);
void SceneHeaps_Destroy021c9ae4(void);
unsigned int SceneHeaps_Create021c9ae4(Heap *parent);
void SceneHeaps_Destroy021c9ae8(void);
unsigned int SceneHeaps_Create021c9ae8(Heap *parent);
void SceneHeaps_Destroy021c9aec(void);
void SceneHeaps_Create021c9aec(Heap *parent);
void SceneHeaps_Destroy021c9af0(void);
unsigned int SceneHeaps_Create021c9af0(Heap *parent);
void SceneHeaps_DestroyClothTextures(void);
void SceneHeaps_CreateClothTextures(Heap *parent);
void SceneHeaps_Destroy021c9af8(void);
void SceneHeaps_Create021c9af8(Heap *parent);
void SceneHeaps_DestroyOv004Pool(void);
int SceneHeaps_CreateOv004Pool(int size, Heap *parent);
void SceneHeaps_DestroyFishPool(void);
int SceneHeaps_CreateFishPool(int size, Heap *parent);

#endif
