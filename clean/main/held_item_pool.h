/* The held items' pool (data_021ca16c, a global C++ object): nine entries, one per item held
 * in the scene (held_item.h). Each keeps the item's code (HELD_ITEM_POOL_NO_ITEM for none),
 * its model (a blended AnimatedModel) with the buffer its model file is read into
 * ("/PItm/Mdl<model / 32>/<model>.nsbmd"), the VRAM region its texture is placed in and the
 * queued task that takes the texture there, a frame heap for its animations, the buffers of
 * its joint animation ("/PItm/Anm...nsbca") and texture SRT animation ("/PItm/ItaAnm...nsbta")
 * and the material animation of the item that holds the entry.
 *
 * As with the field actors' other looks the first four entries are the players', the others
 * the scene's other actors'. The buffers and heaps come from the scene's heaps at
 * data_021c9ad8 (model files) and data_021c9acc (animation heaps). */
#ifndef CLEAN_MAIN_HELD_ITEM_POOL_H
#define CLEAN_MAIN_HELD_ITEM_POOL_H

#include "autoload_2/heap.h"
#include "main/animated_model.h"
#include "main/lookups.h"
#include "main/model_anim.h"
#include "main/model_loader.h"
#include "main/vram_region.h"
#include "types.h"

/* The number of entries. */
#define HELD_ITEM_POOL_COUNT 9
/* The code of an entry without an item. */
#define HELD_ITEM_POOL_NO_ITEM 0xfff1

typedef struct HeldItemPool {
    u8 *model_file[HELD_ITEM_POOL_COUNT];           /* 0x000: HeldItemPool_ModelFileSize bytes */
    Heap *heap[HELD_ITEM_POOL_COUNT];               /* 0x024: HeldItemPool_HeapSize bytes */
    u8 *joint_anim[HELD_ITEM_POOL_COUNT];           /* 0x048: the joint animation's buffer */
    u16 joint_anim_size[HELD_ITEM_POOL_COUNT];      /* 0x06c */
    u8 pad_7e[2];                                   /* 0x07e */
    u8 *texture_anim[HELD_ITEM_POOL_COUNT];         /* 0x080: the texture SRT animation's buffer */
    u16 texture_anim_size[HELD_ITEM_POOL_COUNT];    /* 0x0a4 */
    u8 pad_b6[2];                                   /* 0x0b6 */
    Heap *texture_anim_heap[HELD_ITEM_POOL_COUNT];  /* 0x0b8: the heap of its material animation */
    VramRegion region[HELD_ITEM_POOL_COUNT];        /* 0x0dc */
    ModelLoaderTask task[HELD_ITEM_POOL_COUNT];     /* 0x190: a VramCopyTask */
    AnimatedModel model[HELD_ITEM_POOL_COUNT];      /* 0x28c */
    ModelAnim *material_anim[HELD_ITEM_POOL_COUNT]; /* 0xb20: the holding item's (HeldItemObject.anim) */
    ItemCode code[HELD_ITEM_POOL_COUNT];            /* 0xb44 */
} HeldItemPool;

void HeldItemPool_PlaceTexture(HeldItemPool *pool, int index);
int HeldItemPool_LoadModel(HeldItemPool *pool, int index, int model);
void HeldItemPool_StopUpload(HeldItemPool *pool, int index);
ItemCode *HeldItemPool_Code(HeldItemPool *pool, int index);
int HeldItemPool_MaterialAnim(HeldItemPool *pool, int index);
void HeldItemPool_SetMaterialAnim(HeldItemPool *pool, int index, ModelAnim *anim);
int HeldItemPool_Model(HeldItemPool *pool, int index);
ModelLoaderTask *HeldItemPool_Task(HeldItemPool *pool, int index);
VramRegion *HeldItemPool_Region(HeldItemPool *pool, int index);
void HeldItemPool_StartTextureAnim(HeldItemPool *pool, int index, int number, int flags);
void HeldItemPool_PlayJointAnim(HeldItemPool *pool, int index, int action, int blend, unsigned char flags);
int HeldItemPool_LoadTextureAnim(HeldItemPool *pool, int index, int number);
int HeldItemPool_LoadJointAnim(HeldItemPool *pool, int index, int number);
void HeldItemPool_SetTextureAnimHeap(HeldItemPool *pool, int index, unsigned long heap);
unsigned long HeldItemPool_TextureAnimHeap(HeldItemPool *pool, int index);
unsigned short HeldItemPool_TextureAnimSize(HeldItemPool *pool, int index);
void HeldItemPool_SetTextureAnim(HeldItemPool *pool, int index, int buffer, short size);
unsigned long HeldItemPool_TextureAnim(HeldItemPool *pool, int index);
unsigned short HeldItemPool_JointAnimSize(HeldItemPool *pool, int index);
void HeldItemPool_SetJointAnim(HeldItemPool *pool, int index, int buffer, short size);
int HeldItemPool_JointAnim(HeldItemPool *pool, int index);
int HeldItemPool_Heap(HeldItemPool *pool, int index);
unsigned long HeldItemPool_ModelFile(HeldItemPool *pool, int index);
void HeldItemPool_Clear(HeldItemPool *pool);
void HeldItemPool_CreateHeaps(HeldItemPool *pool);
void HeldItemPool_AllocEntries(HeldItemPool *pool);
HeldItemPool *HeldItemPool_Destruct(HeldItemPool *pool);
HeldItemPool *HeldItemPool_Construct(HeldItemPool *pool);
char *HeldItemPool_TextureAnimPath(unsigned int number);
char *HeldItemPool_JointAnimPath(unsigned int number);
int HeldItemPool_PaletteSize(void);
int HeldItemPool_Texture4x4Size(void);
int HeldItemPool_TextureSize(void);
int HeldItemPool_HeapSize(void);
int HeldItemPool_ModelFileSize(void);
int HeldItemPool_ModelKind(ItemCode *item);
unsigned int HeldItemPool_ItemAnim(ItemCode *item);
unsigned char HeldItemPool_ModelNumber(ItemCode *item);
char *HeldItemPool_ModelPath(unsigned int model);
void HeldItemPool_EndScene(void);
void HeldItemPool_StartScene(Heap *parent);

#endif
