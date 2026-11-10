/* The field actors' accessory, the "/PGls/" models (accessory_look.h). */
#include "accessory_look.h"

#include "clean.h"
#include "scene_heaps.h"
#include "session.h"
#include "vram_copy_task.h"
#include "c_library.h"
#include "rom_file.h"

/* The ModelLoaderTask.state of a task that is queued. */
#define ACCESSORY_LOOK_TASK_QUEUED 1

/* The sizes of an entry's file buffer and of its texture's VRAM: plain textures, 4x4
 * compressed textures, palettes. */
#define ACCESSORY_LOOK_FILE_SIZE 3188
#define ACCESSORY_LOOK_TEXTURE_SIZE 1536
#define ACCESSORY_LOOK_TEXTURE_4X4_SIZE 0
#define ACCESSORY_LOOK_PALETTE_SIZE 96
/* The file buffers' alignment. */
#define ACCESSORY_LOOK_ALIGN 4

static_assert(offsetof(AccessoryLookTable, region) == 0x10, "AccessoryLookTable.region");
static_assert(offsetof(AccessoryLookTable, task) == 0x60, "AccessoryLookTable.task");
static_assert(offsetof(AccessoryLookTable, kind) == 0xd0, "AccessoryLookTable.kind");

extern AccessoryLookTable data_021c9e68; /* the looks' table */
extern Heap *data_021c9adc;              /* the file buffers' heap (SceneHeaps_Create021c9adc) */
extern NetSession *data_020ccf94;        /* the session */
extern const u8 data_020cc7e0[];         /* the kinds of items 0x1431 and up: 0 to 63 */
extern const u8 data_020cc7d4[];         /* the kinds of items 0x1471 and up: 64 to 74 */

extern G3dResTex *func_021077e8(void *file); /* the file's texture resource */

/* The VRAM regions' constructor and destructor, handed to __cxa_vec_ctor and
 * __cxa_vec_cleanup (VramRegion_Construct, VramRegion_Destruct). */
extern void *func_02055cf4(void *region);
extern void func_02055ce8(void *region);
extern void __cxa_vec_ctor(void *array, int count, int size, void (*construct)(void *), void (*destruct)(void *));
extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));

/* func_0205ddc0: the entry `look` names takes `kind`. */
void AccessoryLook_SetKind(unsigned char *look, int kind)
{
    AccessoryLook_SetEntryKind(&data_021c9e68, *look, kind);
}
CLEAN_AS(func_0205ddc0, AccessoryLook_SetKind)

/* func_0205ddd4: the kind of the entry `look` names. */
int AccessoryLook_Kind(unsigned char *look)
{
    return AccessoryLook_EntryKind(&data_021c9e68, *look);
}
CLEAN_AS(func_0205ddd4, AccessoryLook_Kind)

/* func_0205dde8: the task of the entry `look` names. */
ModelLoaderTask *AccessoryLook_Task(unsigned char *look)
{
    return AccessoryLook_EntryTask(&data_021c9e68, *look);
}
CLEAN_AS(func_0205dde8, AccessoryLook_Task)

/* func_0205ddfc: the VRAM region of the entry `look` names. */
VramRegion *AccessoryLook_Region(unsigned char *look)
{
    return AccessoryLook_EntryRegion(&data_021c9e68, *look);
}
CLEAN_AS(func_0205ddfc, AccessoryLook_Region)

/* func_0205de10: the model file of the entry `look` names, as an address. */
unsigned long AccessoryLook_File(unsigned char *look)
{
    return AccessoryLook_EntryFile(&data_021c9e68, *look);
}
CLEAN_AS(func_0205de10, AccessoryLook_File)

/* func_0205de24: whether the look's texture is in VRAM (its task done); when the task is
 * neither done nor queued, the file's texture is queued (FALSE until it is done). */
int AccessoryLook_PollUpload(void *look)
{
    ModelLoaderTask *task = AccessoryLook_Task(look);
    u8 state = task->state;
    if (state == MODEL_LOADER_TASK_DONE) {
        return 1;
    }
    if (state != ACCESSORY_LOOK_TASK_QUEUED) {
        void *file = (void *) (uintptr_t) AccessoryLook_File(look);
        VramCopyTask_QueueTexture((VramCopyTask *) task, func_021077e8(file), 1);
    }
    return 0;
}
CLEAN_AS(func_0205de24, AccessoryLook_PollUpload)

/* func_0205de70: the look's texture placed in its VRAM region (its keys given to the texture
 * resource). */
void AccessoryLook_PlaceTexture(unsigned char *look)
{
    G3dResTex *texture = func_021077e8((void *) (uintptr_t) AccessoryLook_File(look));
    VramRegion_PlaceTexture(AccessoryLook_Region(look), texture);
}
CLEAN_AS(func_0205de70, AccessoryLook_PlaceTexture)

/* func_0205de94: the entry `look` names takes `kind`, and unless it is none (or above) the
 * kind's model file is read into its buffer, at most AccessoryLook_FileSize bytes. */
void AccessoryLook_Load(unsigned char *look, int kind)
{
    unsigned long file = AccessoryLook_File(look);
    AccessoryLook_SetKind(look, kind);
    if (kind >= ACCESSORY_LOOK_NO_KIND) {
        return;
    }
    char *path = AccessoryLook_Path((unsigned int) kind);
    RomFile_Read(path, (void *) (uintptr_t) file, AccessoryLook_FileSize());
}
CLEAN_AS(func_0205de94, AccessoryLook_Load)

/* func_0205dec8: the task of the entry `look` names ended when it is queued, else reset. */
void AccessoryLook_StopUpload(void *look)
{
    if (AccessoryLook_Task(look)->state == ACCESSORY_LOOK_TASK_QUEUED) {
        VramCopyTask_End((VramCopyTask *) AccessoryLook_Task(look));
    } else {
        VramCopyTask_Reset((VramCopyTask *) AccessoryLook_Task(look));
    }
}
CLEAN_AS(func_0205dec8, AccessoryLook_StopUpload)

/* func_0205defc: the look's upload stopped and its entry holding no kind. */
void AccessoryLook_Unload(unsigned char *look)
{
    AccessoryLook_StopUpload(look);
    AccessoryLook_SetKind(look, ACCESSORY_LOOK_NO_KIND);
}
CLEAN_AS(func_0205defc, AccessoryLook_Unload)

/* func_0205df14: the look byte set to name entry `entry`. */
void AccessoryLook_SetLook(unsigned char *look, int entry)
{
    *look = (unsigned char) entry;
}
CLEAN_AS(func_0205df14, AccessoryLook_SetLook)

/* func_0205df18: a look byte's destructor, which does nothing. */
void AccessoryLook_DestructLook(void *look)
{
    (void) look;
}
CLEAN_AS(func_0205df18, AccessoryLook_DestructLook)

/* func_0205df1c: a look byte's constructor: it names none. */
void AccessoryLook_ConstructLook(unsigned char *look)
{
    *look = ACCESSORY_LOOK_COUNT;
}
CLEAN_AS(func_0205df1c, AccessoryLook_ConstructLook)

/* func_0205df24 */
void AccessoryLook_SetEntryKind(AccessoryLookTable *table, int entry, int kind)
{
    table->kind[entry] = (u8) kind;
}
CLEAN_AS(func_0205df24, AccessoryLook_SetEntryKind)

/* func_0205df2c */
int AccessoryLook_EntryKind(AccessoryLookTable *table, int entry)
{
    return table->kind[entry];
}
CLEAN_AS(func_0205df2c, AccessoryLook_EntryKind)

/* func_0205df34 */
ModelLoaderTask *AccessoryLook_EntryTask(AccessoryLookTable *table, int entry)
{
    return &table->task[entry];
}
CLEAN_AS(func_0205df34, AccessoryLook_EntryTask)

/* func_0205df40 */
VramRegion *AccessoryLook_EntryRegion(AccessoryLookTable *table, int entry)
{
    return &table->region[entry];
}
CLEAN_AS(func_0205df40, AccessoryLook_EntryRegion)

/* func_0205df4c: the entry's file buffer, as an address. */
unsigned long AccessoryLook_EntryFile(AccessoryLookTable *table, int entry)
{
    return (unsigned long) (uintptr_t) table->file[entry];
}
CLEAN_AS(func_0205df4c, AccessoryLook_EntryFile)

/* func_0205df54: every entry's VRAM region cleared and file buffer forgotten; then the
 * buffers' heap, if there is one, emptied; then every entry holding no kind. */
void AccessoryLook_Clear(AccessoryLookTable *table)
{
    for (int i = 0; i < ACCESSORY_LOOK_COUNT; i++) {
        VramRegion_Clear(&table->region[i]);
    }
    for (int i = 0; i < ACCESSORY_LOOK_COUNT; i++) {
        table->file[i] = NULL;
    }
    Heap *heap = data_021c9adc;
    if (heap != NULL) {
        Heap_FreeAll(heap);
    }
    for (int i = 0; i < ACCESSORY_LOOK_COUNT; i++) {
        table->kind[i] = ACCESSORY_LOOK_NO_KIND;
    }
}
CLEAN_AS(func_0205df54, AccessoryLook_Clear)

/* func_0205dfa8: for each of the session's players, the entry's VRAM region allocated, then
 * the entry's file buffer taken from the heap at data_021c9adc.
 * REQUIRES: the session has at most ACCESSORY_LOOK_COUNT players (its count is 0-4). */
void AccessoryLook_AllocEntries(AccessoryLookTable *table)
{
    unsigned int count = data_020ccf94->player_count;
    for (unsigned int i = 0; i < count; i++) {
        int texture_size = AccessoryLook_TextureSize();
        int texture_4x4_size = AccessoryLook_Texture4x4Size();
        int palette_size = AccessoryLook_PaletteSize();
        VramRegion_Alloc(&table->region[i], (u32) texture_size, (u32) texture_4x4_size, (u32) palette_size);
    }
    Heap *heap = data_021c9adc;
    for (unsigned int i = 0; i < count; i++) {
        table->file[i] = Heap_AllocAligned(heap, AccessoryLook_FileSize(), ACCESSORY_LOOK_ALIGN);
    }
}
CLEAN_AS(func_0205dfa8, AccessoryLook_AllocEntries)

/* func_0205e018: the table's destructor (registered by __sinit_020c58f8): the VRAM regions
 * destroyed. Returns the table. */
AccessoryLookTable *AccessoryLook_DestructTable(AccessoryLookTable *table)
{
    __cxa_vec_cleanup(table->region, ACCESSORY_LOOK_COUNT, sizeof(VramRegion), func_02055ce8);
    return table;
}
CLEAN_AS(func_0205e018, AccessoryLook_DestructTable)

/* func_0205e034: the table's constructor (__sinit_020c58f8): the VRAM regions, the tasks,
 * then every entry without a buffer and holding no kind. Returns the table. */
AccessoryLookTable *AccessoryLook_ConstructTable(AccessoryLookTable *table)
{
    __cxa_vec_ctor(table->region, ACCESSORY_LOOK_COUNT, sizeof(VramRegion), (void (*)(void *))(uintptr_t) func_02055cf4,
                   func_02055ce8);
    for (int i = 0; i < ACCESSORY_LOOK_COUNT; i++) {
        VramCopyTask_Construct((VramCopyTask *) &table->task[i]);
    }
    for (int i = 0; i < ACCESSORY_LOOK_COUNT; i++) {
        table->file[i] = NULL;
        table->kind[i] = ACCESSORY_LOOK_NO_KIND;
    }
    return table;
}
CLEAN_AS(func_0205e034, AccessoryLook_ConstructTable)

/* func_0205e088 */
int AccessoryLook_PaletteSize(void)
{
    return ACCESSORY_LOOK_PALETTE_SIZE;
}
CLEAN_AS(func_0205e088, AccessoryLook_PaletteSize)

/* func_0205e08c */
int AccessoryLook_Texture4x4Size(void)
{
    return ACCESSORY_LOOK_TEXTURE_4X4_SIZE;
}
CLEAN_AS(func_0205e08c, AccessoryLook_Texture4x4Size)

/* func_0205e090 */
int AccessoryLook_TextureSize(void)
{
    return ACCESSORY_LOOK_TEXTURE_SIZE;
}
CLEAN_AS(func_0205e090, AccessoryLook_TextureSize)

/* func_0205e098: the kind of the item with index `index` among items 0x1471 and up (the
 * callers check index < data_020cc7d0). */
unsigned char AccessoryLook_SecondKind(unsigned int index)
{
    return data_020cc7d4[index];
}
CLEAN_AS(func_0205e098, AccessoryLook_SecondKind)

/* func_0205e0a4: the kind of item 0x1431 + `index` (the callers check index <
 * data_020cc7cc). */
unsigned char AccessoryLook_FirstKind(unsigned int index)
{
    return data_020cc7e0[index];
}
CLEAN_AS(func_0205e0a4, AccessoryLook_FirstKind)

/* func_0205e0b0 */
int AccessoryLook_FileSize(void)
{
    return ACCESSORY_LOOK_FILE_SIZE;
}
CLEAN_AS(func_0205e0b0, AccessoryLook_FileSize)

/* The path buffer of AccessoryLook_Path, "/PGls/%d/%d.nsbmd" (the kind / 32, then the kind). */
extern char data_021c9e54[];
extern const char data_020dd718[];

/* func_0205e0b8: the path of the accessory kind `kind`'s model file, written into one shared buffer
 * (each call overwrites the last one's path). */
char *AccessoryLook_Path(unsigned int kind)
{
    CLib_SPrintf(data_021c9e54, data_020dd718, kind >> 5, kind);
    return data_021c9e54;
}
CLEAN_AS(func_0205e0b8, AccessoryLook_Path)

/* func_0205e0d8: when the scene ends, the table cleared and the buffers' heap destroyed. */
void AccessoryLook_EndScene(void)
{
    AccessoryLook_Clear(&data_021c9e68);
    SceneHeaps_Destroy021c9adc();
}
CLEAN_AS(func_0205e0d8, AccessoryLook_EndScene)

/* func_0205e0f0: when the scene starts, the buffers' heap made from `parent`, the entries
 * allocated, and the heap, if made, shrunk to them. */
void AccessoryLook_StartScene(Heap *parent)
{
    SceneHeaps_Create021c9adc(parent);
    AccessoryLook_AllocEntries(&data_021c9e68);
    Heap *heap = data_021c9adc;
    if (heap != NULL) {
        Heap_Adjust(heap);
    }
}
CLEAN_AS(func_0205e0f0, AccessoryLook_StartScene)
