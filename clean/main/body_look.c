/* The field actors' body looks (body_look.h). */
#include "body_look.h"

#include "clean.h"
#include "scene_heaps.h"
#include "session.h"
#include "vram_copy_task.h"
#include "rom_file.h"

/* The ModelLoaderTask.state of a task that is queued. */
#define BODY_LOOK_TASK_QUEUED 1

extern u8 data_021c9c2c[]; /* the looks' table */
#define BODY_LOOK_TABLE ((BodyLookTable *) data_021c9c2c)

extern void *func_021077e8(u8 *file); /* the file's texture resource */

/* func_0205cfac: the task of the entry `look` names. */
ModelLoaderTask *BodyLook_Task(unsigned char *look)
{
    return BodyLook_EntryTask(BODY_LOOK_TABLE, *look);
}
CLEAN_AS(func_0205cfac, BodyLook_Task)

/* func_0205cfc0: the VRAM region of the entry `look` names. */
VramRegion *BodyLook_Region(unsigned char *look)
{
    return BodyLook_EntryRegion(BODY_LOOK_TABLE, *look);
}
CLEAN_AS(func_0205cfc0, BodyLook_Region)

/* func_0205cfd4: the texture file of the entry `look` names, as an address. */
int BodyLook_File(unsigned char *look)
{
    return (int) BodyLook_EntryFile(BODY_LOOK_TABLE, *look);
}
CLEAN_AS(func_0205cfd4, BodyLook_File)

/* func_0205cfe8: whether the look's texture is in VRAM (its task done); when the task is
 * neither done nor queued, the file's texture is queued (FALSE until it is done). */
int BodyLook_PollUpload(void *look)
{
    ModelLoaderTask *task = BodyLook_Task(look);
    u8 state = task->state;
    if (state == MODEL_LOADER_TASK_DONE) {
        return 1;
    }
    if (state != BODY_LOOK_TASK_QUEUED) {
        u8 *file = (u8 *) (uintptr_t) BodyLook_File(look);
        VramCopyTask_QueueTexture((VramCopyTask *) task, func_021077e8(file), 1);
    }
    return 0;
}
CLEAN_AS(func_0205cfe8, BodyLook_PollUpload)

/* func_0205d034: the look's texture placed in its VRAM region (its keys given to the texture
 * resource). */
void BodyLook_PlaceTexture(void *look)
{
    void *texture = func_021077e8((u8 *) (uintptr_t) BodyLook_File(look));
    VramRegion_PlaceTexture(BodyLook_Region(look), texture);
}
CLEAN_AS(func_0205d034, BodyLook_PlaceTexture)

/* The sizes of an entry's file buffer and of its texture's VRAM: plain textures, 4x4
 * compressed textures, palettes. */
#define BODY_LOOK_FILE_SIZE 9088
#define BODY_LOOK_TEXTURE_SIZE 1088
#define BODY_LOOK_TEXTURE_4X4_SIZE 0
#define BODY_LOOK_PALETTE_SIZE 96
/* The file buffers' alignment. */
#define BODY_LOOK_ALIGN 4

extern Heap *data_021c9ae8;               /* the file buffers' heap (SceneHeaps_Create021c9ae8) */
extern NetSession *data_020ccf94;         /* the session */
extern const char *const data_020dd6c0[]; /* "/PBody/boy.nsbmd", "/PBody/grl.nsbmd" */

static_assert(offsetof(BodyLookTable, region) == 0x10, "BodyLookTable.region");
static_assert(offsetof(BodyLookTable, task) == 0x60, "BodyLookTable.task");
static_assert(sizeof(BodyLookTable) == 0xd0, "BodyLookTable");

/* The VRAM regions' constructor and destructor, handed to __cxa_vec_ctor and
 * __cxa_vec_cleanup (VramRegion_Construct, VramRegion_Destruct). */
extern void *func_02055cf4(void *region);
extern void func_02055ce8(void *region);
extern void __cxa_vec_ctor(void *array, int count, int size, void (*construct)(void *), void (*destruct)(void *));
extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));

/* func_0205d058: the body model file (the girl's when `girl`, else the boy's) read into the
 * buffer of the entry `look` names, at most BodyLook_FileSize bytes. */
void BodyLook_LoadModel(unsigned char *look, int girl)
{
    int file = BodyLook_File(look);
    const char *path = (const char *) (uintptr_t) BodyLook_ModelPath((unsigned int) girl);
    RomFile_Read(path, (void *) (uintptr_t) file, BodyLook_FileSize());
}
CLEAN_AS(func_0205d058, BodyLook_LoadModel)

/* func_0205d084: the task of the entry `look` names ended when it is queued, else reset. */
void BodyLook_StopUpload(unsigned char *look)
{
    if (BodyLook_Task(look)->state == BODY_LOOK_TASK_QUEUED) {
        VramCopyTask_End((VramCopyTask *) BodyLook_Task(look));
    } else {
        VramCopyTask_Reset((VramCopyTask *) BodyLook_Task(look));
    }
}
CLEAN_AS(func_0205d084, BodyLook_StopUpload)

/* func_0205d0b8: the look byte set to name entry `entry`. */
void BodyLook_SetLook(unsigned char *look, int entry)
{
    *look = (unsigned char) entry;
}
CLEAN_AS(func_0205d0b8, BodyLook_SetLook)

/* func_0205d0bc: a look byte's destructor, which does nothing. */
void BodyLook_DestructLook(void *look)
{
    (void) look;
}
CLEAN_AS(func_0205d0bc, BodyLook_DestructLook)

/* func_0205d0c0: a look byte's constructor: it names none. */
void BodyLook_ConstructLook(unsigned char *look)
{
    *look = BODY_LOOK_COUNT;
}
CLEAN_AS(func_0205d0c0, BodyLook_ConstructLook)

/* func_0205d0c8 */
ModelLoaderTask *BodyLook_EntryTask(BodyLookTable *table, int entry)
{
    return &table->task[entry];
}
CLEAN_AS(func_0205d0c8, BodyLook_EntryTask)

/* func_0205d0d4 */
VramRegion *BodyLook_EntryRegion(BodyLookTable *table, int entry)
{
    return &table->region[entry];
}
CLEAN_AS(func_0205d0d4, BodyLook_EntryRegion)

/* func_0205d0e0: the entry's file buffer, as an address. */
unsigned long BodyLook_EntryFile(BodyLookTable *table, int entry)
{
    return (unsigned long) (uintptr_t) table->file[entry];
}
CLEAN_AS(func_0205d0e0, BodyLook_EntryFile)

/* func_0205d0e8: every entry's VRAM region cleared and file buffer forgotten; then the
 * buffers' heap, if there is one, emptied. */
void BodyLook_Clear(BodyLookTable *table)
{
    for (int i = 0; i < BODY_LOOK_COUNT; i++) {
        VramRegion_Clear(&table->region[i]);
    }
    for (int i = 0; i < BODY_LOOK_COUNT; i++) {
        table->file[i] = NULL;
    }
    Heap *heap = data_021c9ae8;
    if (heap != NULL) {
        Heap_FreeAll(heap);
    }
}
CLEAN_AS(func_0205d0e8, BodyLook_Clear)

/* func_0205d12c: for each of the session's players, the entry's VRAM region allocated, then
 * the entry's file buffer taken from the heap at data_021c9ae8.
 * REQUIRES: the session has at most BODY_LOOK_COUNT players (its count is 0-4). */
void BodyLook_AllocEntries(BodyLookTable *table)
{
    unsigned int count = data_020ccf94->player_count;
    for (unsigned int i = 0; i < count; i++) {
        int texture_size = BodyLook_TextureSize();
        int texture_4x4_size = BodyLook_Texture4x4Size();
        int palette_size = BodyLook_PaletteSize();
        VramRegion_Alloc(&table->region[i], (u32) texture_size, (u32) texture_4x4_size, (u32) palette_size);
    }
    Heap *heap = data_021c9ae8;
    for (unsigned int i = 0; i < count; i++) {
        table->file[i] = Heap_AllocAligned(heap, BodyLook_FileSize(), BODY_LOOK_ALIGN);
    }
}
CLEAN_AS(func_0205d12c, BodyLook_AllocEntries)

/* func_0205d19c: the table's destructor (registered by its static initialiser): the VRAM
 * regions destroyed. Returns the table. */
BodyLookTable *BodyLook_DestructTable(BodyLookTable *table)
{
    __cxa_vec_cleanup(table->region, BODY_LOOK_COUNT, sizeof(VramRegion), func_02055ce8);
    return table;
}
CLEAN_AS(func_0205d19c, BodyLook_DestructTable)

/* func_0205d1b8: the table's constructor: the VRAM regions, then the tasks. Returns the
 * table. */
BodyLookTable *BodyLook_ConstructTable(BodyLookTable *table)
{
    __cxa_vec_ctor(table->region, BODY_LOOK_COUNT, sizeof(VramRegion), (void (*)(void *))(uintptr_t) func_02055cf4,
                   func_02055ce8);
    for (int i = 0; i < BODY_LOOK_COUNT; i++) {
        VramCopyTask_Construct((VramCopyTask *) &table->task[i]);
    }
    return table;
}
CLEAN_AS(func_0205d1b8, BodyLook_ConstructTable)

/* func_0205d1f8 */
int BodyLook_PaletteSize(void)
{
    return BODY_LOOK_PALETTE_SIZE;
}
CLEAN_AS(func_0205d1f8, BodyLook_PaletteSize)

/* func_0205d1fc */
int BodyLook_Texture4x4Size(void)
{
    return BODY_LOOK_TEXTURE_4X4_SIZE;
}
CLEAN_AS(func_0205d1fc, BodyLook_Texture4x4Size)

/* func_0205d200 */
int BodyLook_TextureSize(void)
{
    return BODY_LOOK_TEXTURE_SIZE;
}
CLEAN_AS(func_0205d200, BodyLook_TextureSize)

/* func_0205d208 */
int BodyLook_FileSize(void)
{
    return BODY_LOOK_FILE_SIZE;
}
CLEAN_AS(func_0205d208, BodyLook_FileSize)

/* func_0205d210: the path of the body model file, the girl's when `girl` is 1, as an address
 * (the callers pass 0 or 1). */
unsigned int BodyLook_ModelPath(unsigned int girl)
{
    return (unsigned int) (uintptr_t) data_020dd6c0[girl];
}
CLEAN_AS(func_0205d210, BodyLook_ModelPath)

/* func_0205d21c: when the scene ends, the table cleared and the buffers' heap destroyed. */
void BodyLook_EndScene(void)
{
    BodyLook_Clear(BODY_LOOK_TABLE);
    SceneHeaps_Destroy021c9ae8();
}
CLEAN_AS(func_0205d21c, BodyLook_EndScene)

/* func_0205d234: when the scene starts, the buffers' heap made from `parent`, the entries
 * allocated, and the heap, if made, shrunk to them. */
void BodyLook_StartScene(Heap *parent)
{
    SceneHeaps_Create021c9ae8(parent);
    BodyLook_AllocEntries(BODY_LOOK_TABLE);
    Heap *heap = data_021c9ae8;
    if (heap != NULL) {
        Heap_Adjust(heap);
    }
}
CLEAN_AS(func_0205d234, BodyLook_StartScene)
