/* The heaps of a scene's systems (scene_heaps.h). */
#include "scene_heaps.h"

#include "clean.h"
#include "item_texture.h"
#include "npc_lookup.h"
#include "resource_pools.h"
#include "scene_query.h"
#include "scene_tables.h"
#include "session.h"

/* What a unit that is a frame heap costs besides its own bytes: the heap object (0x18) and
 * NNS's frame heap header (0x30). */
#define SCENE_HEAPS_FRAME_HEAP_COST 0x48
/* What an expanded heap's block costs besides its own bytes, before alignment. */
#define SCENE_HEAPS_EXP_BLOCK_COST 16
/* The field actors the field actors' heap has room for. */
#define SCENE_HEAPS_FIELD_ACTORS 4
/* The heap8 pool's heaps. */
#define SCENE_HEAPS_HEAP8_COUNT 8

/* The heaps, by the system they serve. */
extern Heap *data_021c9b34; /* the rooms' acre data (acre_map.c) */
extern Heap *data_021c9ab0; /* the town's acre data (acre_map.c) */
extern Heap *data_021c9ab4; /* the field actors (field_actor.c), an expanded heap */
extern Heap *data_021c9ab8; /* the units of resource_pools.h */
extern Heap *data_021c9abc; /* the heap4 pool's heaps */
extern Heap *data_021c9ac0; /* the heap8 pool's heaps */
extern Heap *data_021c9ac4; /* the block pool's blocks */
extern Heap *data_021c9ac8; /* func_02060754's data_021cad80 (func_0206094c) */
extern Heap *data_021c9acc; /* the held items' pool data_021ca16c, func_0205f3b4 (func_0205f6f8) */
extern Heap *data_021c9ad0; /* func_0205f7bc's data_021cacd0 (func_0205f820) */
extern Heap *data_021c9ad4; /* func_0205dbb8's data_021c9df4 (func_0205dc58) */
extern Heap *data_021c9ad8; /* the held items' pool data_021ca16c, func_0205f434 (func_0205f6f8) */
extern Heap *data_021c9adc; /* func_0205dfa8's data_021c9e68 (func_0205e0f0) */
extern Heap *data_021c9ae0; /* func_0205f910's data_021cacec (func_0205f9ac) */
extern Heap *data_021c9ae4; /* func_0205e5ec's data_021c9f5c (func_0205e8b0) */
extern Heap *data_021c9ae8; /* func_0205d12c's data_021c9c2c (func_0205d234) */
extern Heap *data_021c9aec; /* func_0205d9ec's data_021c9d7c (func_0205db10) */
extern Heap *data_021c9af0; /* func_0205dd10's data_021c9e24 (func_0205dd98) */
extern Heap *data_021c9af4; /* the clothing textures, func_0205d5f0's data_021c9d1c (func_0205d724) */
extern Heap *data_021c9af8; /* func_0205cda0's data_021c9b58 (func_0205cf84) */
extern Heap *data_021c9afc; /* a model pool of overlay 4 (func_ov004_0223507c), an expanded heap */
extern Heap *data_021c9b00; /* the fish display's model pool (fish_disp.c), an expanded heap */

/* The bytes of the rooms' and of the town's acre data (0x7c8 and 0x3648). */
extern u32 data_020c9fcc;
extern u32 data_020c9fd0;
/* The heap4 and heap8 pools' heaps: their alignment (4) and size (0x7ac); the blocks' size
 * (0x2f88). */
extern u32 data_020cd410;
extern u32 data_020cd414;
extern u32 data_020cd41c;
extern u32 data_020cd420;
extern u32 data_020cd418;

extern u8 data_020e54a8;          /* 0: NpcLookup_FourUnlessSlotTaken counts the blocks, else the scene's counts */
extern NetSession *data_020ccf94; /* the session */

/* A field actor's size (3232) and alignment (4). */
extern int func_020952e4(void);
extern int func_020952e0(void);
/* The unit sizes of the systems that have no names yet. */
extern int func_020608fc(void); /* 1240 */
extern int func_0205f63c(void); /* 2204 */
extern int func_0205f800(void); /* 1896 */
extern int func_0205dc3c(void); /* 80 */
extern int func_0205f644(void); /* 3876 */
extern int func_0205e0b0(void); /* 3188 */
extern int func_0205f958(void);
extern int func_0205e700(void); /* 10340 */
extern int func_0205d208(void); /* 9088 */
extern int func_0205dab8(void);
extern int func_0205dd58(void); /* 11824 */
extern int func_0205cf44(void); /* 5568 */
extern int func_0205cf3c(void); /* 624 */
extern int func_0205cf34(void); /* 624 */

static u32 SceneHeaps_AlignTo(u32 size, u32 align)
{
    return (size + align - 1) & ~(align - 1);
}

static u32 SceneHeaps_Align4(u32 size)
{
    return SceneHeaps_AlignTo(size, 4);
}

/* What a unit of `size` bytes made like a frame heap takes. */
static u32 SceneHeaps_FrameUnit(u32 size)
{
    return SceneHeaps_Align4(SceneHeaps_Align4(size) + SCENE_HEAPS_FRAME_HEAP_COST);
}

/* A frame heap of `size` bytes from `parent`. */
static Heap *SceneHeaps_NewFrameHeap(u32 size, Heap *parent)
{
    return FrameHeap_Create((int) size, parent);
}

/* The blocks counted as ResourcePools_BlockCreate counts them before the scene's heaps: while
 * data_020e54a8 is 0 NpcLookup_FourUnlessSlotTaken, else the scene's first count less its
 * second. */
static u32 SceneHeaps_BlockCount(void)
{
    if (data_020e54a8 == 0) {
        return (u32) NpcLookup_FourUnlessSlotTaken();
    }
    u32 first = SceneTables_FirstCount(SceneQuery_Current());
    return first - SceneTables_SecondCount(SceneQuery_Current());
}

/* The scene's first count and its count of heaps. */
static u32 SceneHeaps_SceneCount(void)
{
    u32 first = SceneTables_FirstCount(SceneQuery_Current());
    return first + (u32) ResourcePools_SceneHeapCount();
}

/* The session's number of players. */
static u32 SceneHeaps_Players(void)
{
    return data_020ccf94->player_count;
}

/* ---- The acre data */

/* func_0205c0f0 */
void SceneHeaps_DestroyAcreRooms(void)
{
    Heap_Delete(data_021c9b34);
    data_021c9b34 = NULL;
}
CLEAN_AS(func_0205c0f0, SceneHeaps_DestroyAcreRooms)

/* func_0205c10c: room for the rooms' acre data, as one frame heap. */
void SceneHeaps_CreateAcreRooms(Heap *parent)
{
    data_021c9b34 = SceneHeaps_NewFrameHeap(SceneHeaps_FrameUnit(data_020c9fcc), parent);
}
CLEAN_AS(func_0205c10c, SceneHeaps_CreateAcreRooms)

/* func_0205c13c */
void SceneHeaps_DestroyAcreTown(void)
{
    Heap_Delete(data_021c9ab0);
    data_021c9ab0 = NULL;
}
CLEAN_AS(func_0205c13c, SceneHeaps_DestroyAcreTown)

/* func_0205c158: room for the town's acre data, as one frame heap. */
void SceneHeaps_CreateAcreTown(Heap *parent)
{
    data_021c9ab0 = SceneHeaps_NewFrameHeap(SceneHeaps_FrameUnit(data_020c9fd0), parent);
}
CLEAN_AS(func_0205c158, SceneHeaps_CreateAcreTown)

/* ---- The field actors */

/* func_0205c188 */
void SceneHeaps_DestroyFieldActors(void)
{
    Heap_Delete(data_021c9ab4);
    data_021c9ab4 = NULL;
}
CLEAN_AS(func_0205c188, SceneHeaps_DestroyFieldActors)

/* func_0205c1a4: an expanded heap with room for four field actors, each with its block's cost
 * rounded up to their alignment. */
void SceneHeaps_CreateFieldActors(unsigned int parent)
{
    u32 actor = SceneHeaps_Align4((u32) func_020952e4());
    u32 align = (u32) func_020952e0();
    u32 size = (actor + SceneHeaps_AlignTo(SCENE_HEAPS_EXP_BLOCK_COST, align)) * SCENE_HEAPS_FIELD_ACTORS;
    data_021c9ab4 = ExpHeap_Create((int) size, (Heap *) (uintptr_t) parent);
}
CLEAN_AS(func_0205c1a4, SceneHeaps_CreateFieldActors)

/* ---- The resource pools (resource_pools.h) */

/* func_0205c1e0: the unit heap destroyed when there is one. */
void SceneHeaps_DestroyUnits(void)
{
    if (data_021c9ab8 != NULL) {
        Heap_Delete(data_021c9ab8);
    }
    data_021c9ab8 = NULL;
}
CLEAN_AS(func_0205c1e0, SceneHeaps_DestroyUnits)

/* func_0205c200: the unit heap, with room for a unit of ResourcePools_UnitSize2BCC bytes for
 * each block counted and one of ResourcePools_UnitSize31EC for each of the scene's heaps;
 * made only when that is not 0. The unit heap (it stays as it was when nothing is made). */
unsigned int SceneHeaps_CreateUnits(Heap *parent)
{
    u32 blocks = SceneHeaps_BlockCount();
    u32 heaps = (u32) ResourcePools_SceneHeapCount();
    u32 size = SceneHeaps_FrameUnit((u32) ResourcePools_UnitSize2BCC()) * blocks;
    size += SceneHeaps_FrameUnit((u32) ResourcePools_UnitSize31EC()) * heaps;
    if (size != 0) {
        data_021c9ab8 = SceneHeaps_NewFrameHeap(size, parent);
    }
    return (unsigned int) (uintptr_t) data_021c9ab8;
}
CLEAN_AS(func_0205c200, SceneHeaps_CreateUnits)

/* func_0205c284 */
void SceneHeaps_DestroyHeap4Pool(void)
{
    Heap_Delete(data_021c9abc);
    data_021c9abc = NULL;
}
CLEAN_AS(func_0205c284, SceneHeaps_DestroyHeap4Pool)

/* A pool heap's frame heap of `size` bytes aligned to `align`, with its cost. */
static u32 SceneHeaps_PoolHeapUnit(u32 size, u32 align)
{
    return SceneHeaps_AlignTo(SceneHeaps_AlignTo(size, align) + SCENE_HEAPS_FRAME_HEAP_COST, align);
}

/* func_0205c2a0: room for a heap4 heap for each of the scene's heaps; the new heap. */
unsigned int SceneHeaps_CreateHeap4Pool(Heap *parent)
{
    u32 count = (u32) ResourcePools_SceneHeapCount();
    u32 size = SceneHeaps_PoolHeapUnit(data_020cd414, data_020cd410) * count;
    data_021c9abc = SceneHeaps_NewFrameHeap(size, parent);
    return (unsigned int) (uintptr_t) data_021c9abc;
}
CLEAN_AS(func_0205c2a0, SceneHeaps_CreateHeap4Pool)

/* func_0205c2e4 */
void SceneHeaps_DestroyHeap8Pool(void)
{
    Heap_Delete(data_021c9ac0);
    data_021c9ac0 = NULL;
}
CLEAN_AS(func_0205c2e4, SceneHeaps_DestroyHeap8Pool)

/* func_0205c300: room for the eight heap8 heaps; the new heap. */
unsigned int SceneHeaps_CreateHeap8Pool(Heap *parent)
{
    u32 size = SceneHeaps_PoolHeapUnit(data_020cd420, data_020cd41c) * SCENE_HEAPS_HEAP8_COUNT;
    data_021c9ac0 = SceneHeaps_NewFrameHeap(size, parent);
    return (unsigned int) (uintptr_t) data_021c9ac0;
}
CLEAN_AS(func_0205c300, SceneHeaps_CreateHeap8Pool)

/* func_0205c340 */
void SceneHeaps_DestroyBlockPool(void)
{
    Heap_Delete(data_021c9ac4);
    data_021c9ac4 = NULL;
}
CLEAN_AS(func_0205c340, SceneHeaps_DestroyBlockPool)

/* func_0205c35c: room for the blocks ResourcePools_BlockCreate allocates (no cost each: they
 * are allocated from a frame heap); the new heap. */
unsigned int SceneHeaps_CreateBlockPool(Heap *parent)
{
    u32 count = SceneHeaps_BlockCount();
    count += (u32) ResourcePools_SceneHeapCount();
    u32 size = SceneHeaps_Align4(data_020cd418) * count;
    data_021c9ac4 = SceneHeaps_NewFrameHeap(size, parent);
    return (unsigned int) (uintptr_t) data_021c9ac4;
}
CLEAN_AS(func_0205c35c, SceneHeaps_CreateBlockPool)

/* ---- The systems of the scene's loaders (scene_process.c) */

/* func_0205c3c8 */
void SceneHeaps_Destroy021c9ac8(void)
{
    Heap_Delete(data_021c9ac8);
    data_021c9ac8 = NULL;
}
CLEAN_AS(func_0205c3c8, SceneHeaps_Destroy021c9ac8)

/* func_0205c3e4: room for a unit of func_020608fc bytes for the scene's first count and each
 * of its heaps. */
void SceneHeaps_Create021c9ac8(Heap *parent)
{
    u32 unit = SceneHeaps_Align4((u32) func_020608fc());
    u32 count = SceneHeaps_SceneCount();
    data_021c9ac8 = SceneHeaps_NewFrameHeap(unit * count, parent);
}
CLEAN_AS(func_0205c3e4, SceneHeaps_Create021c9ac8)

/* func_0205c424 */
void SceneHeaps_Destroy021c9acc(void)
{
    Heap_Delete(data_021c9acc);
    data_021c9acc = NULL;
}
CLEAN_AS(func_0205c424, SceneHeaps_Destroy021c9acc)

/* func_0205c440: room for a frame heap of func_0205f63c bytes for the scene's first count and
 * each of its heaps; the new heap. */
unsigned int SceneHeaps_Create021c9acc(Heap *parent)
{
    u32 unit = SceneHeaps_FrameUnit((u32) func_0205f63c());
    u32 count = SceneHeaps_SceneCount();
    data_021c9acc = SceneHeaps_NewFrameHeap(unit * count, parent);
    return (unsigned int) (uintptr_t) data_021c9acc;
}
CLEAN_AS(func_0205c440, SceneHeaps_Create021c9acc)

/* func_0205c488 */
void SceneHeaps_Destroy021c9ad0(void)
{
    Heap_Delete(data_021c9ad0);
    data_021c9ad0 = NULL;
}
CLEAN_AS(func_0205c488, SceneHeaps_Destroy021c9ad0)

/* func_0205c4a4: room for a frame heap of func_0205f800 bytes for each player; the new heap. */
unsigned int SceneHeaps_Create021c9ad0(Heap *parent)
{
    u32 players = SceneHeaps_Players();
    u32 unit = SceneHeaps_FrameUnit((u32) func_0205f800());
    data_021c9ad0 = SceneHeaps_NewFrameHeap(unit * players, parent);
    return (unsigned int) (uintptr_t) data_021c9ad0;
}
CLEAN_AS(func_0205c4a4, SceneHeaps_Create021c9ad0)

/* func_0205c4e0 */
void SceneHeaps_Destroy021c9ad4(void)
{
    Heap_Delete(data_021c9ad4);
    data_021c9ad4 = NULL;
}
CLEAN_AS(func_0205c4e0, SceneHeaps_Destroy021c9ad4)

/* func_0205c4fc: room for a frame heap of func_0205dc3c bytes for the scene's first count and
 * each of its heaps; the new heap. */
unsigned int SceneHeaps_Create021c9ad4(Heap *parent)
{
    u32 unit = SceneHeaps_FrameUnit((u32) func_0205dc3c());
    u32 count = SceneHeaps_SceneCount();
    data_021c9ad4 = SceneHeaps_NewFrameHeap(unit * count, parent);
    return (unsigned int) (uintptr_t) data_021c9ad4;
}
CLEAN_AS(func_0205c4fc, SceneHeaps_Create021c9ad4)

/* func_0205c544 */
void SceneHeaps_Destroy021c9ad8(void)
{
    Heap_Delete(data_021c9ad8);
    data_021c9ad8 = NULL;
}
CLEAN_AS(func_0205c544, SceneHeaps_Destroy021c9ad8)

/* func_0205c560: room for a unit of func_0205f644 bytes for the scene's first count and each
 * of its heaps. */
void SceneHeaps_Create021c9ad8(Heap *parent)
{
    u32 unit = SceneHeaps_Align4((u32) func_0205f644());
    u32 count = SceneHeaps_SceneCount();
    data_021c9ad8 = SceneHeaps_NewFrameHeap(unit * count, parent);
}
CLEAN_AS(func_0205c560, SceneHeaps_Create021c9ad8)

/* func_0205c5a0 */
void SceneHeaps_Destroy021c9adc(void)
{
    Heap_Delete(data_021c9adc);
    data_021c9adc = NULL;
}
CLEAN_AS(func_0205c5a0, SceneHeaps_Destroy021c9adc)

/* func_0205c5bc: room for a unit of func_0205e0b0 bytes for each player; the new heap. */
unsigned int SceneHeaps_Create021c9adc(Heap *parent)
{
    u32 players = SceneHeaps_Players();
    u32 unit = SceneHeaps_Align4((u32) func_0205e0b0());
    data_021c9adc = SceneHeaps_NewFrameHeap(unit * players, parent);
    return (unsigned int) (uintptr_t) data_021c9adc;
}
CLEAN_AS(func_0205c5bc, SceneHeaps_Create021c9adc)

/* func_0205c5f4 */
void SceneHeaps_Destroy021c9ae0(void)
{
    Heap_Delete(data_021c9ae0);
    data_021c9ae0 = NULL;
}
CLEAN_AS(func_0205c5f4, SceneHeaps_Destroy021c9ae0)

/* func_0205c610: func_0205f958 bytes for each player, not rounded; the new heap. */
unsigned int SceneHeaps_Create021c9ae0(Heap *parent)
{
    u32 players = SceneHeaps_Players();
    u32 unit = (u32) func_0205f958();
    data_021c9ae0 = SceneHeaps_NewFrameHeap(unit * players, parent);
    return (unsigned int) (uintptr_t) data_021c9ae0;
}
CLEAN_AS(func_0205c610, SceneHeaps_Create021c9ae0)

/* func_0205c640 */
void SceneHeaps_Destroy021c9ae4(void)
{
    Heap_Delete(data_021c9ae4);
    data_021c9ae4 = NULL;
}
CLEAN_AS(func_0205c640, SceneHeaps_Destroy021c9ae4)

/* func_0205c65c: room for a unit of func_0205e700 bytes for each player; the new heap. */
unsigned int SceneHeaps_Create021c9ae4(Heap *parent)
{
    u32 players = SceneHeaps_Players();
    u32 unit = SceneHeaps_Align4((u32) func_0205e700());
    data_021c9ae4 = SceneHeaps_NewFrameHeap(unit * players, parent);
    return (unsigned int) (uintptr_t) data_021c9ae4;
}
CLEAN_AS(func_0205c65c, SceneHeaps_Create021c9ae4)

/* func_0205c694 */
void SceneHeaps_Destroy021c9ae8(void)
{
    Heap_Delete(data_021c9ae8);
    data_021c9ae8 = NULL;
}
CLEAN_AS(func_0205c694, SceneHeaps_Destroy021c9ae8)

/* func_0205c6b0: room for a unit of func_0205d208 bytes for each player; the new heap. */
unsigned int SceneHeaps_Create021c9ae8(Heap *parent)
{
    u32 players = SceneHeaps_Players();
    u32 unit = SceneHeaps_Align4((u32) func_0205d208());
    data_021c9ae8 = SceneHeaps_NewFrameHeap(unit * players, parent);
    return (unsigned int) (uintptr_t) data_021c9ae8;
}
CLEAN_AS(func_0205c6b0, SceneHeaps_Create021c9ae8)

/* func_0205c6e8 */
void SceneHeaps_Destroy021c9aec(void)
{
    Heap_Delete(data_021c9aec);
    data_021c9aec = NULL;
}
CLEAN_AS(func_0205c6e8, SceneHeaps_Destroy021c9aec)

/* func_0205c704: room for a unit of func_0205dab8 bytes for the scene's first count and each
 * of its heaps. */
void SceneHeaps_Create021c9aec(Heap *parent)
{
    u32 unit = SceneHeaps_Align4((u32) func_0205dab8());
    u32 count = SceneHeaps_SceneCount();
    data_021c9aec = SceneHeaps_NewFrameHeap(unit * count, parent);
}
CLEAN_AS(func_0205c704, SceneHeaps_Create021c9aec)

/* func_0205c744 */
void SceneHeaps_Destroy021c9af0(void)
{
    Heap_Delete(data_021c9af0);
    data_021c9af0 = NULL;
}
CLEAN_AS(func_0205c744, SceneHeaps_Destroy021c9af0)

/* func_0205c760: room for a unit of func_0205dd58 bytes for each player; the new heap. */
unsigned int SceneHeaps_Create021c9af0(Heap *parent)
{
    u32 players = SceneHeaps_Players();
    u32 unit = SceneHeaps_Align4((u32) func_0205dd58());
    data_021c9af0 = SceneHeaps_NewFrameHeap(unit * players, parent);
    return (unsigned int) (uintptr_t) data_021c9af0;
}
CLEAN_AS(func_0205c760, SceneHeaps_Create021c9af0)

/* func_0205c798 */
void SceneHeaps_DestroyClothTextures(void)
{
    Heap_Delete(data_021c9af4);
    data_021c9af4 = NULL;
}
CLEAN_AS(func_0205c798, SceneHeaps_DestroyClothTextures)

/* func_0205c7b4: room for a clothing texture file for the scene's first count, each of its
 * heaps and one more. */
void SceneHeaps_CreateClothTextures(Heap *parent)
{
    u32 unit = SceneHeaps_Align4((u32) ClothTexture_Size());
    u32 count = SceneHeaps_SceneCount() + 1;
    data_021c9af4 = SceneHeaps_NewFrameHeap(unit * count, parent);
}
CLEAN_AS(func_0205c7b4, SceneHeaps_CreateClothTextures)

/* func_0205c7f8 */
void SceneHeaps_Destroy021c9af8(void)
{
    Heap_Delete(data_021c9af8);
    data_021c9af8 = NULL;
}
CLEAN_AS(func_0205c7f8, SceneHeaps_Destroy021c9af8)

/* func_0205c814: room for units of three sizes. With `shared` the smaller of the players and
 * the scene's second count, and `rest` the scene's first count and heaps less `shared` (less
 * 1 when `shared` is 0): a unit of func_0205cf44 and one of func_0205cf3c bytes for each of
 * `shared` + `rest`, and one of func_0205cf34 bytes for each of `rest`. */
void SceneHeaps_Create021c9af8(Heap *parent)
{
    u32 players = SceneHeaps_Players();
    u32 shared = SceneTables_SecondCount(SceneQuery_Current());
    if (players < shared) {
        shared = players;
    }
    u32 at_least_one = shared != 0 ? shared : 1;
    u32 first = SceneTables_FirstCount(SceneQuery_Current());
    u32 rest = (u32) ResourcePools_SceneHeapCount() + first - at_least_one;
    u32 a = SceneHeaps_Align4((u32) func_0205cf44());
    u32 b = SceneHeaps_Align4((u32) func_0205cf3c());
    u32 c = SceneHeaps_Align4((u32) func_0205cf34());
    u32 size = a * (shared + rest) + b * (shared + rest) + c * rest;
    data_021c9af8 = SceneHeaps_NewFrameHeap(size, parent);
}
CLEAN_AS(func_0205c814, SceneHeaps_Create021c9af8)

/* ---- The model pools' heaps (func_0209d180's allocate and release functions) */

/* func_0205c8a8 */
void SceneHeaps_DestroyOv004Pool(void)
{
    Heap_Delete(data_021c9afc);
    data_021c9afc = NULL;
}
CLEAN_AS(func_0205c8a8, SceneHeaps_DestroyOv004Pool)

/* func_0205c8c4: an expanded heap of `size` bytes from `parent`; it, as an address. */
int SceneHeaps_CreateOv004Pool(int size, Heap *parent)
{
    data_021c9afc = ExpHeap_Create(size, parent);
    return (int) (uintptr_t) data_021c9afc;
}
CLEAN_AS(func_0205c8c4, SceneHeaps_CreateOv004Pool)

/* func_0205c8dc */
void SceneHeaps_DestroyFishPool(void)
{
    Heap_Delete(data_021c9b00);
    data_021c9b00 = NULL;
}
CLEAN_AS(func_0205c8dc, SceneHeaps_DestroyFishPool)

/* func_0205c8f8: an expanded heap of `size` bytes from `parent`; it, as an address. */
int SceneHeaps_CreateFishPool(int size, Heap *parent)
{
    data_021c9b00 = ExpHeap_Create(size, parent);
    return (int) (uintptr_t) data_021c9b00;
}
CLEAN_AS(func_0205c8f8, SceneHeaps_CreateFishPool)
