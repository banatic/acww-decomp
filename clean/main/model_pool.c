/* The model pool and a model's files (model_pool.h). */
#include "model_pool.h"

#include "clean.h"

/* The bytes of an entry's heap added to its size, before rounding down to 4. */
#define MODEL_POOL_HEAP_OVERHEAD 0x5b
/* What func_020559d0 answers once the files are loaded. */
#define MODEL_POOL_FILES_LOADED 3

static_assert(sizeof(ModelPoolEntry) == 0x1c, "ModelPoolEntry is 0x1c bytes");
static_assert(sizeof(ModelPool) == 0x18, "ModelPool is 0x18 bytes");
static_assert(offsetof(ModelPoolFiles, loaded) == 0x34, "ModelPoolFiles.loaded is at 0x34");
static_assert(sizeof(ModelPoolFiles) == 0x40, "ModelPoolFiles is 0x40 bytes");

extern Heap *data_021fbe94; /* the current heap */

/* The model resource: its model, release, destructor, constructor and the step-by-step load of
 * `path` (VRAM `vram`, heap `heap`, files read on `parent`). */
extern int func_02055950(void *resource);
extern void func_02055aac(void *resource);
extern void func_02055af4(void *resource);
extern void *func_02055b00(void *resource);
extern u8 func_020559d0(void *resource, const char *path, void *vram, Heap *heap, Heap *parent);
/* An entry: emptied, constructed, set up (its heap of `heap_size` bytes inside `parent`, VRAM of
 * `texture_size` and `palette_size`), its VRAM and its heap. */
extern int func_0209d2d0(ModelPoolEntry *entry);
extern ModelPoolEntry *func_0209d328(ModelPoolEntry *entry);
extern int func_0209d2dc(ModelPoolEntry *entry, int texture_size, int palette_size, int heap_size, int parent);
extern void *func_0209d320(ModelPoolEntry *entry);
extern Heap *func_0209d324(ModelPoolEntry *entry);

/* func_0209d088: the model of the files. */
int ModelPoolFiles_Model(ModelPoolFiles *files)
{
    return func_02055950(files);
}
CLEAN_AS(func_0209d088, ModelPoolFiles_Model)

/* func_0209d090: the files released: not loaded, no entry. */
void ModelPoolFiles_Release(ModelPoolFiles *files)
{
    files->loaded = 0;
    files->entry = NULL;
    files->unk_3c = 0;
    func_02055aac(files);
}
CLEAN_AS(func_0209d090, ModelPoolFiles_Release)

/* func_0209d0a4 */
void ModelPoolFiles_Reset(ModelPoolFiles *files)
{
    ModelPoolFiles_Release(files);
}
CLEAN_AS(func_0209d0a4, ModelPoolFiles_Reset)

/* func_0209d0ac: one step of loading `path` into the VRAM and heap of `entry`, the current heap
 * reading the files; whether the files are loaded. The entry is kept the first time.
 * QUIRK: later steps load into the `entry` passed, not the one kept. */
unsigned char ModelPoolFiles_Load(ModelPoolFiles *files, ModelPoolEntry *entry, const char *path)
{
    if (files->entry == NULL) {
        files->entry = entry;
    }
    if (files->loaded == 0) {
        void *vram = func_0209d320(entry);
        Heap *heap = func_0209d324(entry);
        if (func_020559d0(files, path, vram, heap, data_021fbe94) == MODEL_POOL_FILES_LOADED) {
            files->loaded = 1;
        }
    }
    return files->loaded;
}
CLEAN_AS(func_0209d0ac, ModelPoolFiles_Load)

/* func_0209d104: the files' destructor: released, then the resource destroyed. */
int ModelPoolFiles_Destruct(ModelPoolFiles *files)
{
    ModelPoolFiles_Release(files);
    func_02055af4(files);
    return (int) (uintptr_t) files;
}
CLEAN_AS(func_0209d104, ModelPoolFiles_Destruct)

/* func_0209d11c: the files' constructor: not loaded, no entry. */
ModelPoolFiles *ModelPoolFiles_Construct(ModelPoolFiles *files)
{
    func_02055b00(files);
    files->loaded = 0;
    files->entry = NULL;
    return files;
}
CLEAN_AS(func_0209d11c, ModelPoolFiles_Construct)

/* func_0209d138: the pool destroyed: each entry emptied and the entries freed, the `release` hook
 * called, and the pool left empty. Always 1. */
int ModelPool_Destroy(ModelPool *pool)
{
    if (pool->entries != NULL) {
        ModelPoolEntry *entry = pool->entries;
        for (u32 i = 0; i < pool->count; i++) {
            func_0209d2d0(entry);
            entry++;
        }
        Heap_FreeCurrent(pool->entries);
    }
    if (pool->release != NULL) {
        pool->release();
    }
    pool->allocate = NULL;
    pool->release = NULL;
    pool->count = 0;
    pool->taken = 0;
    pool->released = MODEL_POOL_NO_SLOT;
    pool->entries = NULL;
    return 1;
}
CLEAN_AS(func_0209d138, ModelPool_Destroy)

/* func_0209d180: the pool created with `count` entries from the current heap, each with VRAM of
 * `texture_size` and `palette_size` bytes and a heap of `heap_size` bytes, made inside the
 * parent heap `allocate` gives for them all (asked only for a nonzero `heap_size`). 0 when an
 * entry cannot be set up, else 1 (also when the entries cannot be allocated).
 * QUIRK: the last argument is not used. */
int ModelPool_Create(ModelPool *pool, u32 count, int texture_size, int palette_size, int heap_size, int (*allocate)(int, int),
                     void (*release)(void), void *unused)
{
    (void) unused;
    pool->allocate = allocate;
    pool->release = release;
    int size = (int) (count * (((u32) heap_size + MODEL_POOL_HEAP_OVERHEAD) & ~3u));
    pool->count = count;
    int parent = 0;
    pool->taken = 0;
    if (heap_size != 0) {
        parent = pool->allocate(size, 0);
    }
    pool->entries = Heap_AllocCurrent((int) (sizeof(ModelPoolEntry) * pool->count));

    ModelPoolEntry *entry = pool->entries;
    if (entry == NULL) {
        return 1;
    }
    for (u32 i = 0; i < pool->count; i++) {
        /* Constructed in place; a C++ placement new tests the address first. */
        if (entry != NULL) {
            entry = func_0209d328(entry);
        }
        if (func_0209d2dc(entry, texture_size, palette_size, heap_size, parent) == 0) {
            return 0;
        }
        entry++;
    }
    return 1;
}
CLEAN_AS(func_0209d180, ModelPool_Create)

/* func_0209d200: the entry of `*slot` released (its heap emptied with Heap_FreeAll) and the slot
 * set to none; nothing for a slot of none. */
void ModelPool_Release(ModelPool *pool, unsigned short *slot)
{
    if (*slot == MODEL_POOL_NO_SLOT) {
        return;
    }
    ModelPoolEntry *entry = &pool->entries[*slot];
    entry->taken = 0;
    pool->released = *slot;
    *slot = MODEL_POOL_NO_SLOT;
    if (entry->heap != NULL) {
        Heap_FreeAll(entry->heap);
    }
    pool->taken--;
}
CLEAN_AS(func_0209d200, ModelPool_Release)

/* func_0209d238: the entry of `*slot`; for a slot of none, a free entry taken and the slot set
 * to it, the one released last only when no other is free. NULL when none is free, or (with the
 * slot set to none) for a slot past the entries.
 * BUG: before any release, the entry "released last" is number 0xffff, past the entries: when
 * all are taken it is read, and taken if its first byte is 0. */
ModelPoolEntry *ModelPool_Take(ModelPool *pool, unsigned short *slot)
{
    if (*slot != MODEL_POOL_NO_SLOT) {
        if (*slot < pool->count) {
            return &pool->entries[*slot];
        }
        *slot = MODEL_POOL_NO_SLOT;
        return NULL;
    }

    ModelPoolEntry *entry = pool->entries;
    u32 count = pool->count;
    for (u16 i = 0; i < count; i++) {
        if (entry->taken == 0 && i != pool->released) {
            entry->taken = 1;
            *slot = i;
            pool->taken++;
            return entry;
        }
        entry++;
    }
    entry = &pool->entries[pool->released];
    if (entry->taken == 0) {
        entry->taken = 1;
        *slot = pool->released;
        pool->taken++;
        return entry;
    }
    return NULL;
}
CLEAN_AS(func_0209d238, ModelPool_Take)

/* func_0209d2b4: the pool's destructor: nothing. */
void ModelPool_Destruct(void *pool)
{
    (void) pool;
}
CLEAN_AS(func_0209d2b4, ModelPool_Destruct)

/* func_0209d2b8: the pool empty. */
void ModelPool_Init(ModelPool *pool)
{
    pool->allocate = NULL;
    pool->release = NULL;
    pool->entries = NULL;
    pool->count = 0;
    pool->taken = 0;
    pool->released = MODEL_POOL_NO_SLOT;
}
CLEAN_AS(func_0209d2b8, ModelPool_Init)

/* ---- An entry and a model's slot */

/* What sets up an entry's VRAM (`vram` at 0x08): `texture_size` bytes of texture VRAM and
 * `palette_size` of palette VRAM; nonzero when it got them. And the VRAM's constructor. */
extern int func_02055c80(void *vram, int texture_size, int unused, int palette_size);
extern void *func_02055cf4(void *vram);

/* func_0209d2d0: the entry emptied: not taken, no heap (the heap itself is left alone). Always
 * 1. */
int ModelPoolEntry_Empty(ModelPoolEntry *entry)
{
    entry->taken = 0;
    entry->heap = NULL;
    return 1;
}
CLEAN_AS(func_0209d2d0, ModelPoolEntry_Empty)

/* func_0209d2dc: the entry set up: a frame heap of `heap_size` bytes (rounded up to 4) inside
 * `parent` when `heap_size` is nonzero, then its VRAM when either size is nonzero; 0 when the
 * VRAM could not be had, else 1. */
int ModelPoolEntry_Setup(ModelPoolEntry *entry, int texture_size, int palette_size, int heap_size, int parent)
{
    if (heap_size != 0) {
        entry->heap = FrameHeap_Create((int) (((u32) heap_size + 3) & ~3u), (Heap *) (uintptr_t) parent);
    }
    if (texture_size != 0 || palette_size != 0) {
        return func_02055c80(entry->vram, texture_size, 0, palette_size) != 0;
    }
    return 1;
}
CLEAN_AS(func_0209d2dc, ModelPoolEntry_Setup)

/* func_0209d320: the address of the entry's VRAM. */
int ModelPoolEntry_Vram(ModelPoolEntry *entry)
{
    return (int) (uintptr_t) entry->vram;
}
CLEAN_AS(func_0209d320, ModelPoolEntry_Vram)

/* func_0209d324: the entry's heap. */
int ModelPoolEntry_Heap(ModelPoolEntry *entry)
{
    return (int) (uintptr_t) entry->heap;
}
CLEAN_AS(func_0209d324, ModelPoolEntry_Heap)

/* func_0209d328: the entry's constructor: its VRAM constructed, then not taken and no heap. */
ModelPoolEntry *ModelPoolEntry_Construct(ModelPoolEntry *entry)
{
    func_02055cf4(entry->vram);
    entry->taken = 0;
    entry->heap = NULL;
    return entry;
}
CLEAN_AS(func_0209d328, ModelPoolEntry_Construct)

/* func_0209d340: a model's slot's destructor: set to none. */
void ModelPoolSlot_Destruct(unsigned short *slot)
{
    *slot = MODEL_POOL_NO_SLOT;
}
CLEAN_AS(func_0209d340, ModelPoolSlot_Destruct)

/* func_0209d34c: a model's slot's constructor: none. */
void ModelPoolSlot_Construct(unsigned short *slot)
{
    *slot = MODEL_POOL_NO_SLOT;
}
CLEAN_AS(func_0209d34c, ModelPoolSlot_Construct)
