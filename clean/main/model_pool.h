/* A pool of entries that models load their files into (ModelPool, 0x18 bytes; fish_disp.h keeps
 * one), and the files of one model (ModelPoolFiles, 0x40 bytes).
 *
 * Each entry (0x1c bytes) has a heap of its own, made inside one parent heap that the pool's
 * `allocate` hook gives at creation, and VRAM for textures and palettes (at 0x08,
 * func_0209d320). A model takes an entry by its slot (a u16, 0xffff for none): the entry the
 * slot names, or a free one. The entry released last is handed out only when no other is free.
 *
 * ModelPoolFiles is a model resource (constructor func_02055b00, destructor func_02055af4;
 * func_020559d0 loads it step by step, 3 when done) that remembers the entry it loads into and
 * whether it is loaded. */
#ifndef CLEAN_MAIN_MODEL_POOL_H
#define CLEAN_MAIN_MODEL_POOL_H

#include "autoload_2/heap.h"
#include "types.h"

#define MODEL_POOL_NO_SLOT 0xffff

typedef struct ModelPoolEntry {
    u8 taken; /* 0x00 */
    u8 pad_01[3];
    Heap *heap;    /* 0x04: its heap, or NULL */
    u8 vram[0x14]; /* 0x08: its VRAM (constructor func_02055cf4) */
} ModelPoolEntry;

typedef struct ModelPool {
    u16 released; /* 0x00: the entry released last, or MODEL_POOL_NO_SLOT */
    u8 pad_02[2];
    u32 count;                             /* 0x04: entries */
    s32 taken;                             /* 0x08: entries taken */
    ModelPoolEntry *entries;               /* 0x0c: from the current heap */
    int (*allocate)(int size, int unused); /* 0x10: gives the parent heap of the entries' heaps */
    void (*release)(void);                 /* 0x14: called when the pool is destroyed */
} ModelPool;

typedef struct ModelPoolFiles {
    u8 resource[0x34]; /* 0x00: the model resource */
    u8 loaded;         /* 0x34 */
    u8 pad_35[3];
    ModelPoolEntry *entry; /* 0x38: the entry loaded into, kept from the first load */
    u32 unk_3c;            /* 0x3c: cleared on release */
} ModelPoolFiles;

int ModelPoolFiles_Model(ModelPoolFiles *files);
void ModelPoolFiles_Release(ModelPoolFiles *files);
void ModelPoolFiles_Reset(ModelPoolFiles *files);
unsigned char ModelPoolFiles_Load(ModelPoolFiles *files, ModelPoolEntry *entry, const char *path);
int ModelPoolFiles_Destruct(ModelPoolFiles *files);
ModelPoolFiles *ModelPoolFiles_Construct(ModelPoolFiles *files);
int ModelPool_Destroy(ModelPool *pool);
int ModelPool_Create(ModelPool *pool, u32 count, int texture_size, int palette_size, int heap_size, int (*allocate)(int, int),
                     void (*release)(void), void *unused);
void ModelPool_Release(ModelPool *pool, unsigned short *slot);
ModelPoolEntry *ModelPool_Take(ModelPool *pool, unsigned short *slot);
void ModelPool_Destruct(void *pool);
void ModelPool_Init(ModelPool *pool);

int ModelPoolEntry_Empty(ModelPoolEntry *entry);
int ModelPoolEntry_Setup(ModelPoolEntry *entry, int texture_size, int palette_size, int heap_size, int parent);
int ModelPoolEntry_Vram(ModelPoolEntry *entry);
int ModelPoolEntry_Heap(ModelPoolEntry *entry);
ModelPoolEntry *ModelPoolEntry_Construct(ModelPoolEntry *entry);
void ModelPoolSlot_Destruct(unsigned short *slot);
void ModelPoolSlot_Construct(unsigned short *slot);

#endif
