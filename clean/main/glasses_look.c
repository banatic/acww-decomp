/* The field actors' part C, the "/PGls/" models (glasses_look.h). */
#include "glasses_look.h"

#include "clean.h"
#include "scene_heaps.h"
#include "session.h"
#include "vram_copy_task.h"
#include "c_library.h"
#include "rom_file.h"

/* The ModelLoaderTask.state of a task that is queued. */
#define GLASSES_LOOK_TASK_QUEUED 1

/* The sizes of an entry's file buffer and of its texture's VRAM: plain textures, 4x4
 * compressed textures, palettes. */
#define GLASSES_LOOK_FILE_SIZE 3188
#define GLASSES_LOOK_TEXTURE_SIZE 1536
#define GLASSES_LOOK_TEXTURE_4X4_SIZE 0
#define GLASSES_LOOK_PALETTE_SIZE 96
/* The file buffers' alignment. */
#define GLASSES_LOOK_ALIGN 4

static_assert(offsetof(GlassesLookTable, region) == 0x10, "GlassesLookTable.region");
static_assert(offsetof(GlassesLookTable, task) == 0x60, "GlassesLookTable.task");
static_assert(offsetof(GlassesLookTable, kind) == 0xd0, "GlassesLookTable.kind");

extern GlassesLookTable data_021c9e68; /* the looks' table */
extern Heap *data_021c9adc;            /* the file buffers' heap (SceneHeaps_Create021c9adc) */
extern NetSession *data_020ccf94;      /* the session */
extern const u8 data_020cc7e0[];       /* the kinds of items 0x1431 and up: 0 to 63 */
extern const u8 data_020cc7d4[];       /* the kinds of items 0x1471 and up: 64 to 74 */

extern G3dResTex *func_021077e8(void *file); /* the file's texture resource */

/* The VRAM regions' constructor and destructor, handed to __cxa_vec_ctor and
 * __cxa_vec_cleanup (VramRegion_Construct, VramRegion_Destruct). */
extern void *func_02055cf4(void *region);
extern void func_02055ce8(void *region);
extern void __cxa_vec_ctor(void *array, int count, int size, void (*construct)(void *), void (*destruct)(void *));
extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));

/* func_0205ddc0: the entry `look` names takes `kind`. */
void GlassesLook_SetKind(unsigned char *look, int kind)
{
    GlassesLook_SetEntryKind(&data_021c9e68, *look, kind);
}
CLEAN_AS(func_0205ddc0, GlassesLook_SetKind)

/* func_0205ddd4: the kind of the entry `look` names. */
int GlassesLook_Kind(unsigned char *look)
{
    return GlassesLook_EntryKind(&data_021c9e68, *look);
}
CLEAN_AS(func_0205ddd4, GlassesLook_Kind)

/* func_0205dde8: the task of the entry `look` names. */
ModelLoaderTask *GlassesLook_Task(unsigned char *look)
{
    return GlassesLook_EntryTask(&data_021c9e68, *look);
}
CLEAN_AS(func_0205dde8, GlassesLook_Task)

/* func_0205ddfc: the VRAM region of the entry `look` names. */
VramRegion *GlassesLook_Region(unsigned char *look)
{
    return GlassesLook_EntryRegion(&data_021c9e68, *look);
}
CLEAN_AS(func_0205ddfc, GlassesLook_Region)

/* func_0205de10: the model file of the entry `look` names, as an address. */
unsigned long GlassesLook_File(unsigned char *look)
{
    return GlassesLook_EntryFile(&data_021c9e68, *look);
}
CLEAN_AS(func_0205de10, GlassesLook_File)

/* func_0205de24: whether the look's texture is in VRAM (its task done); when the task is
 * neither done nor queued, the file's texture is queued (FALSE until it is done). */
int GlassesLook_PollUpload(void *look)
{
    ModelLoaderTask *task = GlassesLook_Task(look);
    u8 state = task->state;
    if (state == MODEL_LOADER_TASK_DONE) {
        return 1;
    }
    if (state != GLASSES_LOOK_TASK_QUEUED) {
        void *file = (void *) (uintptr_t) GlassesLook_File(look);
        VramCopyTask_QueueTexture((VramCopyTask *) task, func_021077e8(file), 1);
    }
    return 0;
}
CLEAN_AS(func_0205de24, GlassesLook_PollUpload)

/* func_0205de70: the look's texture placed in its VRAM region (its keys given to the texture
 * resource). */
void GlassesLook_PlaceTexture(unsigned char *look)
{
    G3dResTex *texture = func_021077e8((void *) (uintptr_t) GlassesLook_File(look));
    VramRegion_PlaceTexture(GlassesLook_Region(look), texture);
}
CLEAN_AS(func_0205de70, GlassesLook_PlaceTexture)

/* func_0205de94: the entry `look` names takes `kind`, and unless it is none (or above) the
 * kind's model file is read into its buffer, at most GlassesLook_FileSize bytes. */
void GlassesLook_Load(unsigned char *look, int kind)
{
    unsigned long file = GlassesLook_File(look);
    GlassesLook_SetKind(look, kind);
    if (kind >= GLASSES_LOOK_NO_KIND) {
        return;
    }
    char *path = GlassesLook_Path((unsigned int) kind);
    RomFile_Read(path, (void *) (uintptr_t) file, GlassesLook_FileSize());
}
CLEAN_AS(func_0205de94, GlassesLook_Load)

/* func_0205dec8: the task of the entry `look` names ended when it is queued, else reset. */
void GlassesLook_StopUpload(void *look)
{
    if (GlassesLook_Task(look)->state == GLASSES_LOOK_TASK_QUEUED) {
        VramCopyTask_End((VramCopyTask *) GlassesLook_Task(look));
    } else {
        VramCopyTask_Reset((VramCopyTask *) GlassesLook_Task(look));
    }
}
CLEAN_AS(func_0205dec8, GlassesLook_StopUpload)

/* func_0205defc: the look's upload stopped and its entry holding no kind. */
void GlassesLook_Unload(unsigned char *look)
{
    GlassesLook_StopUpload(look);
    GlassesLook_SetKind(look, GLASSES_LOOK_NO_KIND);
}
CLEAN_AS(func_0205defc, GlassesLook_Unload)

/* func_0205df14: the look byte set to name entry `entry`. */
void GlassesLook_SetLook(unsigned char *look, int entry)
{
    *look = (unsigned char) entry;
}
CLEAN_AS(func_0205df14, GlassesLook_SetLook)

/* func_0205df18: a look byte's destructor, which does nothing. */
void GlassesLook_DestructLook(void *look)
{
    (void) look;
}
CLEAN_AS(func_0205df18, GlassesLook_DestructLook)

/* func_0205df1c: a look byte's constructor: it names none. */
void GlassesLook_ConstructLook(unsigned char *look)
{
    *look = GLASSES_LOOK_COUNT;
}
CLEAN_AS(func_0205df1c, GlassesLook_ConstructLook)

/* func_0205df24 */
void GlassesLook_SetEntryKind(GlassesLookTable *table, int entry, int kind)
{
    table->kind[entry] = (u8) kind;
}
CLEAN_AS(func_0205df24, GlassesLook_SetEntryKind)

/* func_0205df2c */
int GlassesLook_EntryKind(GlassesLookTable *table, int entry)
{
    return table->kind[entry];
}
CLEAN_AS(func_0205df2c, GlassesLook_EntryKind)

/* func_0205df34 */
ModelLoaderTask *GlassesLook_EntryTask(GlassesLookTable *table, int entry)
{
    return &table->task[entry];
}
CLEAN_AS(func_0205df34, GlassesLook_EntryTask)

/* func_0205df40 */
VramRegion *GlassesLook_EntryRegion(GlassesLookTable *table, int entry)
{
    return &table->region[entry];
}
CLEAN_AS(func_0205df40, GlassesLook_EntryRegion)

/* func_0205df4c: the entry's file buffer, as an address. */
unsigned long GlassesLook_EntryFile(GlassesLookTable *table, int entry)
{
    return (unsigned long) (uintptr_t) table->file[entry];
}
CLEAN_AS(func_0205df4c, GlassesLook_EntryFile)

/* func_0205df54: every entry's VRAM region cleared and file buffer forgotten; then the
 * buffers' heap, if there is one, emptied; then every entry holding no kind. */
void GlassesLook_Clear(GlassesLookTable *table)
{
    for (int i = 0; i < GLASSES_LOOK_COUNT; i++) {
        VramRegion_Clear(&table->region[i]);
    }
    for (int i = 0; i < GLASSES_LOOK_COUNT; i++) {
        table->file[i] = NULL;
    }
    Heap *heap = data_021c9adc;
    if (heap != NULL) {
        Heap_FreeAll(heap);
    }
    for (int i = 0; i < GLASSES_LOOK_COUNT; i++) {
        table->kind[i] = GLASSES_LOOK_NO_KIND;
    }
}
CLEAN_AS(func_0205df54, GlassesLook_Clear)

/* func_0205dfa8: for each of the session's players, the entry's VRAM region allocated, then
 * the entry's file buffer taken from the heap at data_021c9adc.
 * REQUIRES: the session has at most GLASSES_LOOK_COUNT players (its count is 0-4). */
void GlassesLook_AllocEntries(GlassesLookTable *table)
{
    unsigned int count = data_020ccf94->player_count;
    for (unsigned int i = 0; i < count; i++) {
        int texture_size = GlassesLook_TextureSize();
        int texture_4x4_size = GlassesLook_Texture4x4Size();
        int palette_size = GlassesLook_PaletteSize();
        VramRegion_Alloc(&table->region[i], (u32) texture_size, (u32) texture_4x4_size, (u32) palette_size);
    }
    Heap *heap = data_021c9adc;
    for (unsigned int i = 0; i < count; i++) {
        table->file[i] = Heap_AllocAligned(heap, GlassesLook_FileSize(), GLASSES_LOOK_ALIGN);
    }
}
CLEAN_AS(func_0205dfa8, GlassesLook_AllocEntries)

/* func_0205e018: the table's destructor (registered by __sinit_020c58f8): the VRAM regions
 * destroyed. Returns the table. */
GlassesLookTable *GlassesLook_DestructTable(GlassesLookTable *table)
{
    __cxa_vec_cleanup(table->region, GLASSES_LOOK_COUNT, sizeof(VramRegion), func_02055ce8);
    return table;
}
CLEAN_AS(func_0205e018, GlassesLook_DestructTable)

/* func_0205e034: the table's constructor (__sinit_020c58f8): the VRAM regions, the tasks,
 * then every entry without a buffer and holding no kind. Returns the table. */
GlassesLookTable *GlassesLook_ConstructTable(GlassesLookTable *table)
{
    __cxa_vec_ctor(table->region, GLASSES_LOOK_COUNT, sizeof(VramRegion), (void (*)(void *))(uintptr_t) func_02055cf4,
                   func_02055ce8);
    for (int i = 0; i < GLASSES_LOOK_COUNT; i++) {
        VramCopyTask_Construct((VramCopyTask *) &table->task[i]);
    }
    for (int i = 0; i < GLASSES_LOOK_COUNT; i++) {
        table->file[i] = NULL;
        table->kind[i] = GLASSES_LOOK_NO_KIND;
    }
    return table;
}
CLEAN_AS(func_0205e034, GlassesLook_ConstructTable)

/* func_0205e088 */
int GlassesLook_PaletteSize(void)
{
    return GLASSES_LOOK_PALETTE_SIZE;
}
CLEAN_AS(func_0205e088, GlassesLook_PaletteSize)

/* func_0205e08c */
int GlassesLook_Texture4x4Size(void)
{
    return GLASSES_LOOK_TEXTURE_4X4_SIZE;
}
CLEAN_AS(func_0205e08c, GlassesLook_Texture4x4Size)

/* func_0205e090 */
int GlassesLook_TextureSize(void)
{
    return GLASSES_LOOK_TEXTURE_SIZE;
}
CLEAN_AS(func_0205e090, GlassesLook_TextureSize)

/* func_0205e098: the kind of the item with index `index` among items 0x1471 and up (the
 * callers check index < data_020cc7d0). */
unsigned char GlassesLook_SecondKind(unsigned int index)
{
    return data_020cc7d4[index];
}
CLEAN_AS(func_0205e098, GlassesLook_SecondKind)

/* func_0205e0a4: the kind of item 0x1431 + `index` (the callers check index <
 * data_020cc7cc). */
unsigned char GlassesLook_FirstKind(unsigned int index)
{
    return data_020cc7e0[index];
}
CLEAN_AS(func_0205e0a4, GlassesLook_FirstKind)

/* func_0205e0b0 */
int GlassesLook_FileSize(void)
{
    return GLASSES_LOOK_FILE_SIZE;
}
CLEAN_AS(func_0205e0b0, GlassesLook_FileSize)

/* The path buffer of GlassesLook_Path, "/PGls/%d/%d.nsbmd" (the kind / 32, then the kind). */
extern char data_021c9e54[];
extern const char data_020dd718[];

/* func_0205e0b8: the path of part C kind `kind`'s model file, written into one shared buffer
 * (each call overwrites the last one's path). */
char *GlassesLook_Path(unsigned int kind)
{
    CLib_SPrintf(data_021c9e54, data_020dd718, kind >> 5, kind);
    return data_021c9e54;
}
CLEAN_AS(func_0205e0b8, GlassesLook_Path)

/* func_0205e0d8: when the scene ends, the table cleared and the buffers' heap destroyed. */
void GlassesLook_EndScene(void)
{
    GlassesLook_Clear(&data_021c9e68);
    SceneHeaps_Destroy021c9adc();
}
CLEAN_AS(func_0205e0d8, GlassesLook_EndScene)

/* func_0205e0f0: when the scene starts, the buffers' heap made from `parent`, the entries
 * allocated, and the heap, if made, shrunk to them. */
void GlassesLook_StartScene(Heap *parent)
{
    SceneHeaps_Create021c9adc(parent);
    GlassesLook_AllocEntries(&data_021c9e68);
    Heap *heap = data_021c9adc;
    if (heap != NULL) {
        Heap_Adjust(heap);
    }
}
CLEAN_AS(func_0205e0f0, GlassesLook_StartScene)
