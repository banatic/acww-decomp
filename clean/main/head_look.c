/* The field actors' head, part B, the "/PHead/" models (head_look.h). */
#include "head_look.h"

#include "clean.h"
#include "cloth_slots.h"
#include "scene_heaps.h"
#include "session.h"
#include "vram_copy_task.h"

/* The ModelLoaderTask.state of a task that is queued. */
#define HEAD_LOOK_TASK_QUEUED 1

/* The sizes of an entry's buffer (both files) and of the first model's texture VRAM: plain
 * textures, 4x4 compressed textures, palettes. */
#define HEAD_LOOK_BLOCK_SIZE 10340
#define HEAD_LOOK_TEXTURE_SIZE 4640
#define HEAD_LOOK_TEXTURE_4X4_SIZE 0
#define HEAD_LOOK_PALETTE_SIZE 192
/* The buffers' alignment, also that of the second file in the buffer. */
#define HEAD_LOOK_ALIGN 4

/* The items worn on the head, by the models they give. */
#define HEAD_LOOK_ITEM_A_FIRST 0x13a8 /* the first model, instead of the hair */
#define HEAD_LOOK_ITEM_A_LAST 0x13c7
#define HEAD_LOOK_ITEM_B_FIRST 0x13c8 /* the second model, over the hair */
#define HEAD_LOOK_ITEM_B_LAST 0x1407
#define HEAD_LOOK_ITEM_C_FIRST 0x1408 /* the second model, by func_0204bff4's index */
#define HEAD_LOOK_ITEM_C_LAST 0x1428
#define HEAD_LOOK_DESIGN_FIRST 0x1429 /* the second model, wearing the design */
#define HEAD_LOOK_DESIGN_LAST 0x1430
/* The number of items 0x1408 and up that have a model. */
#define HEAD_LOOK_ITEM_C_COUNT 0x16
/* The second model of a design item, by the flag HeadLook_ChooseModels is given. */
#define HEAD_LOOK_DESIGN_MODEL 0x80
#define HEAD_LOOK_DESIGN_MODEL_FLAGGED 0x81
/* The model of items 0x1408 and up that is never shown, and the one shown instead. */
#define HEAD_LOOK_SKIPPED_MODEL 0x9c
#define HEAD_LOOK_SKIPPED_MODEL_SHOWN 0x9d

static_assert(offsetof(HeadLookTable, region) == 0x10, "HeadLookTable.region");
static_assert(offsetof(HeadLookTable, task) == 0xb0, "HeadLookTable.task");
static_assert(offsetof(HeadLookTable, model) == 0x190, "HeadLookTable.model");
static_assert(offsetof(HeadLookTable, kind) == 0x1b0, "HeadLookTable.kind");

extern HeadLookTable data_021c9f5c; /* the looks' table */
extern Heap *data_021c9ae4;         /* the buffers' heap (SceneHeaps_Create021c9ae4) */
extern NetSession *data_020ccf94;   /* the session */
/* The path buffer of HeadLook_Path, "/PHead/%d/%d.nsbmd" (the kind / 32, then the kind). */
extern char data_021c9f48[];
extern const char data_020dd738[];
/* The names of the texture a design is copied from ("cloth", in the clothes' file) and to
 * ("myD", in the head's second model). */
extern const char data_020dd72c[];
extern const char data_020dd734[];

/* The models by hair kind, by hair kind under a hat, and by item. */
extern const u8 data_020cc820[];
extern const u8 data_020cc830[];
extern const u8 data_020cc840[];
extern const u8 data_020cc858[];
extern const u8 data_020cc878[];

extern G3dResTex *func_021077e8(int file);                          /* the file's texture resource */
extern int func_02064328(char *buffer, const char *format, ...);    /* sprintf */
extern int func_02064af4(const char *path, void *buffer, int size); /* read a file: its size, 0 on failure */
/* A texture resource's named image (func_0206439c) and named palette (func_0206435c) copied
 * over another's. */
extern void func_0206439c(G3dResTex *from, G3dResTex *to, const char *from_name, const char *to_name);
extern void func_0206435c(G3dResTex *from, G3dResTex *to, const char *from_name, const char *to_name);
/* The item's attribute bit 2 (byte 9 of its record): the hair is shown whole under it. */
extern int func_020624d4(ItemCode *item);
/* Whether an item 0x1408 to 0x1428 is one of those with an index (func_0204bff4, -1 for none). */
extern int func_0204be38(ItemCode *item);
extern int func_0204bff4(ItemCode *item);

/* NitroSystem: the VRAM sizes of a texture resource's plain textures, 4x4 compressed textures
 * and palettes. */
extern u32 NNS_G3dTexGetRequiredSize(const void *texture);
extern u32 NNS_G3dTex4x4GetRequiredSize(const void *texture);
extern u32 NNS_G3dPlttGetRequiredSize(const void *texture);

/* The VRAM regions' constructor and destructor, handed to __cxa_vec_ctor and
 * __cxa_vec_cleanup (VramRegion_Construct, VramRegion_Destruct). */
extern void *func_02055cf4(void *region);
extern void func_02055ce8(void *region);
extern void __cxa_vec_ctor(void *array, int count, int size, void (*construct)(void *), void (*destruct)(void *));
extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));

static int head_look_in(ItemCode item, ItemCode first, ItemCode last)
{
    return item >= first && item <= last;
}

static ModelLoaderTask *head_look_task(unsigned char *look, int model)
{
    return (ModelLoaderTask *) (uintptr_t) HeadLook_Task(look, model);
}

/* func_0205e118: model `model` of the entry `look` names takes `kind`. */
void HeadLook_SetKind(unsigned char *look, int model, int kind)
{
    HeadLook_SetEntryKind(&data_021c9f5c, *look, model, (unsigned char) kind);
}
CLEAN_AS(func_0205e118, HeadLook_SetKind)

/* func_0205e138: the kind of model `model` of the entry `look` names. */
int HeadLook_Kind(const unsigned char *look, int model)
{
    return HeadLook_EntryKind(&data_021c9f5c, *look, model);
}
CLEAN_AS(func_0205e138, HeadLook_Kind)

/* func_0205e14c: the task of model `model` of the entry `look` names, as an address. */
int HeadLook_Task(unsigned char *look, int model)
{
    return (int) (uintptr_t) HeadLook_EntryTask(&data_021c9f5c, *look, model);
}
CLEAN_AS(func_0205e14c, HeadLook_Task)

/* func_0205e160: the VRAM region of model `model` of the entry `look` names, as an address. */
int HeadLook_Region(unsigned char *look, int model)
{
    return (int) (uintptr_t) HeadLook_EntryRegion(&data_021c9f5c, *look, model);
}
CLEAN_AS(func_0205e160, HeadLook_Region)

/* func_0205e174: model `model` of the entry `look` names starts at `file`. */
void HeadLook_SetModel(unsigned char *look, int model, u8 *file)
{
    HeadLook_SetEntryModel(&data_021c9f5c, *look, model, file);
}
CLEAN_AS(func_0205e174, HeadLook_SetModel)

/* func_0205e194: the file of model `model` of the entry `look` names, as an address. */
int HeadLook_Model(unsigned char *look, unsigned int model)
{
    return HeadLook_EntryModel(&data_021c9f5c, *look, (int) model);
}
CLEAN_AS(func_0205e194, HeadLook_Model)

/* func_0205e1a8: the buffer of the entry `look` names, as an address. */
int HeadLook_File(unsigned char *look)
{
    return (int) HeadLook_EntryFile(&data_021c9f5c, *look);
}
CLEAN_AS(func_0205e1a8, HeadLook_File)

/* func_0205e1bc: whether the textures of both models are in VRAM (a second model that is not
 * there counts as done); a texture whose task is neither done nor queued is queued (the first
 * model's, then the second's). */
int HeadLook_PollUpload(unsigned char *look)
{
    int first_done = 1;
    ModelLoaderTask *task = head_look_task(look, 0);
    if (task->state != MODEL_LOADER_TASK_DONE) {
        first_done = 0;
        if (task->state != HEAD_LOOK_TASK_QUEUED) {
            VramCopyTask_QueueTexture((VramCopyTask *) task, func_021077e8(HeadLook_Model(look, 0)), 1);
        }
    }
    int second_done = 1;
    if (HeadLook_Kind(look, 1) < HEAD_LOOK_NO_KIND) {
        /* The second model's file is looked up before its task. */
        int file = HeadLook_Model(look, 1);
        task = head_look_task(look, 1);
        if (task->state != MODEL_LOADER_TASK_DONE) {
            second_done = 0;
            if (task->state != HEAD_LOOK_TASK_QUEUED) {
                VramCopyTask_QueueTexture((VramCopyTask *) task, func_021077e8(file), 1);
            }
        }
    }
    return first_done && second_done;
}
CLEAN_AS(func_0205e1bc, HeadLook_PollUpload)

/* func_0205e274: the first model's texture placed in its region; then, with a second model, the
 * second model's region given the keys right after the first's texture in the first's region
 * (for its plain textures, 4x4 compressed textures and palettes) and its texture placed there. */
void HeadLook_PlaceTextures(unsigned char *look)
{
    G3dResTex *first = func_021077e8(HeadLook_Model(look, 0));
    VramRegion *first_region = (VramRegion *) (uintptr_t) HeadLook_Region(look, 0);
    VramRegion_PlaceTexture(first_region, first);
    if (HeadLook_Kind(look, 1) >= HEAD_LOOK_NO_KIND) {
        return;
    }
    int second_file = HeadLook_Model(look, 1);
    if (second_file == 0) {
        return;
    }

    u32 first_texture = NNS_G3dTexGetRequiredSize(first);
    u32 first_texture_4x4 = NNS_G3dTex4x4GetRequiredSize(first);
    u32 first_palette = NNS_G3dPlttGetRequiredSize(first);
    G3dResTex *second = func_021077e8(second_file);
    u32 second_texture = NNS_G3dTexGetRequiredSize(second);
    u32 second_texture_4x4 = NNS_G3dTex4x4GetRequiredSize(second);
    u32 second_palette = NNS_G3dPlttGetRequiredSize(second);
    VramRegion *second_region = (VramRegion *) (uintptr_t) HeadLook_Region(look, 1);

    VramKey texture = VramRegion_TexKey(first_region, first_texture);
    texture = VramRegion_TexKeyAfter(first_region, texture, second_texture);
    VramKey texture_4x4 = VramRegion_Tex4x4Key(first_region, first_texture_4x4);
    texture_4x4 = VramRegion_Tex4x4KeyAfter(first_region, texture_4x4, second_texture_4x4);
    u32 palette = VramRegion_PaletteKey(first_region, first_palette);
    palette = VramRegion_PaletteKeyAfter(first_region, palette, second_palette);
    VramRegion_SetKeys(second_region, texture, texture_4x4, palette);
    VramRegion_PlaceTexture(second_region, second);
}
CLEAN_AS(func_0205e274, HeadLook_PlaceTextures)

/* func_0205e348: model kind `first`'s file read into the entry's buffer, at most
 * HeadLook_BlockSize bytes; when that succeeds the first model starts at the buffer and the
 * entry takes both kinds, and unless `second` is none its file is read into the rest of the
 * buffer, after the first file (its size rounded up to a multiple of 4). When that fails the
 * second model is none; when it succeeds the second model starts there and, for a design item
 * `*item`, the design (from `record`, the player's record) is loaded into the clothes' scratch
 * slot and its texture "cloth" (image, then palette) copied over the second model's "myD".
 * Returns the sizes read (the first rounded up), 0 when the first file was not read. */
int HeadLook_Load(unsigned char *look, int first, int second, ItemCode *item, u8 *record)
{
    u8 *buffer = (u8 *) (uintptr_t) HeadLook_File(look);
    int room = HeadLook_BlockSize();
    int first_size = func_02064af4(HeadLook_Path((unsigned int) first), buffer, room);
    int second_size = 0;
    if (first_size == 0) {
        return 0;
    }
    first_size = (first_size + HEAD_LOOK_ALIGN - 1) & ~(HEAD_LOOK_ALIGN - 1);
    HeadLook_SetModel(look, 0, buffer);
    HeadLook_SetKind(look, 0, first);
    HeadLook_SetKind(look, 1, second);
    if (second < HEAD_LOOK_NO_KIND) {
        buffer += first_size;
        second_size = func_02064af4(HeadLook_Path((unsigned int) second), buffer, room - first_size);
        if (second_size != 0) {
            HeadLook_SetModel(look, 1, buffer);
            if (head_look_in(*item, HEAD_LOOK_DESIGN_FIRST, HEAD_LOOK_DESIGN_LAST)) {
                u8 *scratch = (u8 *) (uintptr_t) ClothSlots_ScratchSlot();
                ClothSlots_Load(scratch, item, record, 0, 0);
                G3dResTex *design = func_021077e8(ClothSlots_SlotFile(scratch));
                G3dResTex *texture = func_021077e8((int) (uintptr_t) buffer);
                func_0206439c(design, texture, data_020dd72c, data_020dd734);
                func_0206435c(design, texture, data_020dd72c, data_020dd734);
            }
        } else {
            HeadLook_SetKind(look, 1, HEAD_LOOK_NO_KIND);
        }
    }
    return first_size + second_size;
}
CLEAN_AS(func_0205e348, HeadLook_Load)

/* func_0205e444: each model's task ended when it is queued, else reset (the first model's, then
 * the second's). */
void HeadLook_StopUploads(unsigned char *look)
{
    for (int model = 0; model < HEAD_LOOK_MODELS; model++) {
        if (head_look_task(look, model)->state == HEAD_LOOK_TASK_QUEUED) {
            VramCopyTask_End((VramCopyTask *) head_look_task(look, model));
        } else {
            VramCopyTask_Reset((VramCopyTask *) head_look_task(look, model));
        }
    }
}
CLEAN_AS(func_0205e444, HeadLook_StopUploads)

/* func_0205e4b0: the uploads stopped, then both models without a file and none. */
void HeadLook_Unload(unsigned char *look)
{
    HeadLook_StopUploads(look);
    HeadLook_SetModel(look, 0, NULL);
    HeadLook_SetModel(look, 1, NULL);
    HeadLook_SetKind(look, 0, HEAD_LOOK_NO_KIND);
    HeadLook_SetKind(look, 1, HEAD_LOOK_NO_KIND);
}
CLEAN_AS(func_0205e4b0, HeadLook_Unload)

/* func_0205e4e8: the look byte set to name entry `entry`. */
void HeadLook_SetLook(unsigned char *look, int entry)
{
    *look = (unsigned char) entry;
}
CLEAN_AS(func_0205e4e8, HeadLook_SetLook)

/* func_0205e4ec: a look byte's destructor, which does nothing. */
void HeadLook_DestructLook(void *look)
{
    (void) look;
}
CLEAN_AS(func_0205e4ec, HeadLook_DestructLook)

/* func_0205e4f0: a look byte's constructor: it names none. */
void HeadLook_ConstructLook(unsigned char *look)
{
    *look = HEAD_LOOK_COUNT;
}
CLEAN_AS(func_0205e4f0, HeadLook_ConstructLook)

/* func_0205e4f8 */
void HeadLook_SetEntryKind(HeadLookTable *table, int entry, int model, unsigned char kind)
{
    table->kind[entry][model] = kind;
}
CLEAN_AS(func_0205e4f8, HeadLook_SetEntryKind)

/* func_0205e508 */
unsigned char HeadLook_EntryKind(HeadLookTable *table, int entry, int model)
{
    return table->kind[entry][model];
}
CLEAN_AS(func_0205e508, HeadLook_EntryKind)

/* func_0205e518 */
ModelLoaderTask *HeadLook_EntryTask(HeadLookTable *table, int entry, int model)
{
    return &table->task[entry][model];
}
CLEAN_AS(func_0205e518, HeadLook_EntryTask)

/* func_0205e528 */
VramRegion *HeadLook_EntryRegion(HeadLookTable *table, int entry, int model)
{
    return &table->region[entry][model];
}
CLEAN_AS(func_0205e528, HeadLook_EntryRegion)

/* func_0205e538 */
void HeadLook_SetEntryModel(HeadLookTable *table, int entry, int model, u8 *file)
{
    table->model[entry][model] = file;
}
CLEAN_AS(func_0205e538, HeadLook_SetEntryModel)

/* func_0205e54c: the model's file, as an address. */
int HeadLook_EntryModel(HeadLookTable *table, int entry, int model)
{
    return (int) (uintptr_t) table->model[entry][model];
}
CLEAN_AS(func_0205e54c, HeadLook_EntryModel)

/* func_0205e560: the entry's buffer, as an address. */
unsigned long HeadLook_EntryFile(HeadLookTable *table, int entry)
{
    return (unsigned long) (uintptr_t) table->file[entry];
}
CLEAN_AS(func_0205e560, HeadLook_EntryFile)

/* func_0205e568: every VRAM region cleared, every buffer and model file forgotten; then the
 * buffers' heap, if there is one, emptied; then every model none. */
void HeadLook_Clear(HeadLookTable *table)
{
    for (int i = 0; i < HEAD_LOOK_COUNT; i++) {
        VramRegion_Clear(&table->region[i][0]);
        VramRegion_Clear(&table->region[i][1]);
    }
    for (int i = 0; i < HEAD_LOOK_COUNT; i++) {
        table->file[i] = NULL;
        table->model[i][0] = NULL;
        table->model[i][1] = NULL;
    }
    Heap *heap = data_021c9ae4;
    if (heap != NULL) {
        Heap_FreeAll(heap);
    }
    for (int i = 0; i < HEAD_LOOK_COUNT; i++) {
        table->kind[i][0] = HEAD_LOOK_NO_KIND;
        table->kind[i][1] = HEAD_LOOK_NO_KIND;
    }
}
CLEAN_AS(func_0205e568, HeadLook_Clear)

/* func_0205e5ec: for each of the session's players, the first model's VRAM region allocated
 * (the second's keys are taken from it, HeadLook_PlaceTextures), then the entry's buffer taken
 * from the heap at data_021c9ae4.
 * REQUIRES: the session has at most HEAD_LOOK_COUNT players (its count is 0-4). */
void HeadLook_AllocEntries(HeadLookTable *table)
{
    unsigned int count = data_020ccf94->player_count;
    for (unsigned int i = 0; i < count; i++) {
        int texture_size = HeadLook_TextureSize();
        int texture_4x4_size = HeadLook_Texture4x4Size();
        int palette_size = HeadLook_PaletteSize();
        VramRegion_Alloc(&table->region[i][0], (u32) texture_size, (u32) texture_4x4_size, (u32) palette_size);
    }
    Heap *heap = data_021c9ae4;
    for (unsigned int i = 0; i < count; i++) {
        table->file[i] = Heap_AllocAligned(heap, HeadLook_BlockSize(), HEAD_LOOK_ALIGN);
    }
}
CLEAN_AS(func_0205e5ec, HeadLook_AllocEntries)

/* func_0205e65c: the table's destructor: the VRAM regions destroyed. Returns the table. */
HeadLookTable *HeadLook_DestructTable(HeadLookTable *table)
{
    __cxa_vec_cleanup(table->region, HEAD_LOOK_COUNT * HEAD_LOOK_MODELS, sizeof(VramRegion), func_02055ce8);
    return table;
}
CLEAN_AS(func_0205e65c, HeadLook_DestructTable)

/* func_0205e678: the table's constructor: the VRAM regions, the tasks, then every entry without
 * a buffer or model files and its models none. Returns the table. */
HeadLookTable *HeadLook_ConstructTable(HeadLookTable *table)
{
    __cxa_vec_ctor(table->region, HEAD_LOOK_COUNT * HEAD_LOOK_MODELS, sizeof(VramRegion),
                   (void (*)(void *))(uintptr_t) func_02055cf4, func_02055ce8);
    for (int i = 0; i < HEAD_LOOK_COUNT; i++) {
        for (int j = 0; j < HEAD_LOOK_MODELS; j++) {
            VramCopyTask_Construct((VramCopyTask *) &table->task[i][j]);
        }
    }
    for (int i = 0; i < HEAD_LOOK_COUNT; i++) {
        table->file[i] = NULL;
        table->model[i][0] = NULL;
        table->model[i][1] = NULL;
        table->kind[i][0] = HEAD_LOOK_NO_KIND;
        table->kind[i][1] = HEAD_LOOK_NO_KIND;
    }
    return table;
}
CLEAN_AS(func_0205e678, HeadLook_ConstructTable)

/* func_0205e6f0 */
int HeadLook_PaletteSize(void)
{
    return HEAD_LOOK_PALETTE_SIZE;
}
CLEAN_AS(func_0205e6f0, HeadLook_PaletteSize)

/* func_0205e6f4 */
int HeadLook_Texture4x4Size(void)
{
    return HEAD_LOOK_TEXTURE_4X4_SIZE;
}
CLEAN_AS(func_0205e6f4, HeadLook_Texture4x4Size)

/* func_0205e6f8 */
int HeadLook_TextureSize(void)
{
    return HEAD_LOOK_TEXTURE_SIZE;
}
CLEAN_AS(func_0205e6f8, HeadLook_TextureSize)

/* func_0205e700 */
int HeadLook_BlockSize(void)
{
    return HEAD_LOOK_BLOCK_SIZE;
}
CLEAN_AS(func_0205e700, HeadLook_BlockSize)

/* func_0205e708: the two models of a head with hair kind `hair` wearing `*item` (head_look.h):
 * the first is the item's for items 0x13a8 to 0x13c7, the hair under a hat for items 0x13c8 to
 * 0x1407 and the design items unless the item's attribute bit shows the hair whole
 * (func_020624d4), else the hair. The second is the design model (by `flag`) for a design
 * item, the item's for items 0x13c8 to 0x1407 and for those of items 0x1408 to 0x1428 with an
 * index below HEAD_LOOK_ITEM_C_COUNT, else none.
 * QUIRK: model 0x9c of items 0x1408 and up is shown as 0x9d. */
void HeadLook_ChooseModels(int flag, int hair, ItemCode *item, int *first, int *second)
{
    int first_model;
    int second_model = HEAD_LOOK_NO_KIND;
    ItemCode code = *item;
    if (head_look_in(code, HEAD_LOOK_ITEM_A_FIRST, HEAD_LOOK_ITEM_A_LAST)) {
        first_model = HeadLook_ItemAModel((unsigned int) (code - HEAD_LOOK_ITEM_A_FIRST));
    } else if ((head_look_in(code, HEAD_LOOK_ITEM_B_FIRST, HEAD_LOOK_ITEM_B_LAST) ||
                head_look_in(code, HEAD_LOOK_DESIGN_FIRST, HEAD_LOOK_DESIGN_LAST)) &&
               func_020624d4(item) == 0) {
        first_model = HeadLook_CoveredHairModel((unsigned char) hair);
    } else {
        first_model = HeadLook_HairModel((unsigned int) hair);
    }

    code = *item;
    if (head_look_in(code, HEAD_LOOK_DESIGN_FIRST, HEAD_LOOK_DESIGN_LAST)) {
        second_model = flag == 0 ? HEAD_LOOK_DESIGN_MODEL : HEAD_LOOK_DESIGN_MODEL_FLAGGED;
    } else if (head_look_in(code, HEAD_LOOK_ITEM_B_FIRST, HEAD_LOOK_ITEM_B_LAST)) {
        second_model = HeadLook_ItemBModel((unsigned int) (code - HEAD_LOOK_ITEM_B_FIRST));
    } else if (head_look_in(code, HEAD_LOOK_ITEM_C_FIRST, HEAD_LOOK_ITEM_C_LAST) && func_0204be38(item) != 0) {
        int index = func_0204bff4(item);
        if (index >= 0 && index < HEAD_LOOK_ITEM_C_COUNT) {
            second_model = HeadLook_ItemCModel((unsigned int) index);
            if (second_model == HEAD_LOOK_SKIPPED_MODEL) {
                second_model = HEAD_LOOK_SKIPPED_MODEL_SHOWN;
            }
        }
    }
    *first = first_model;
    *second = second_model;
}
CLEAN_AS(func_0205e708, HeadLook_ChooseModels)

/* func_0205e83c: the second model of the item with index `index` among items 0x1408 and up. */
unsigned char HeadLook_ItemCModel(unsigned int index)
{
    return data_020cc840[index];
}
CLEAN_AS(func_0205e83c, HeadLook_ItemCModel)

/* func_0205e848: the first model of item 0x13a8 + `index`. */
unsigned char HeadLook_ItemAModel(unsigned int index)
{
    return data_020cc858[index];
}
CLEAN_AS(func_0205e848, HeadLook_ItemAModel)

/* func_0205e854: the second model of item 0x13c8 + `index`. */
unsigned char HeadLook_ItemBModel(unsigned int index)
{
    return data_020cc878[index];
}
CLEAN_AS(func_0205e854, HeadLook_ItemBModel)

/* func_0205e860: the first model of hair kind `hair` under a hat. */
unsigned char HeadLook_CoveredHairModel(unsigned char hair)
{
    return data_020cc830[hair];
}
CLEAN_AS(func_0205e860, HeadLook_CoveredHairModel)

/* func_0205e86c: the first model of hair kind `hair`. */
unsigned char HeadLook_HairModel(unsigned int hair)
{
    return data_020cc820[hair];
}
CLEAN_AS(func_0205e86c, HeadLook_HairModel)

/* func_0205e878: the path of model kind `kind`'s file, written into one shared buffer (each call
 * overwrites the last one's path). */
char *HeadLook_Path(unsigned int kind)
{
    func_02064328(data_021c9f48, data_020dd738, kind >> 5, kind);
    return data_021c9f48;
}
CLEAN_AS(func_0205e878, HeadLook_Path)

/* func_0205e898: when the scene ends, the table cleared and the buffers' heap destroyed. */
void HeadLook_EndScene(void)
{
    HeadLook_Clear(&data_021c9f5c);
    SceneHeaps_Destroy021c9ae4();
}
CLEAN_AS(func_0205e898, HeadLook_EndScene)

/* func_0205e8b0: when the scene starts, the buffers' heap made from `parent`, the entries
 * allocated, and the heap, if made, shrunk to them. */
void HeadLook_StartScene(Heap *parent)
{
    SceneHeaps_Create021c9ae4(parent);
    HeadLook_AllocEntries(&data_021c9f5c);
    Heap *heap = data_021c9ae4;
    if (heap != NULL) {
        Heap_Adjust(heap);
    }
}
CLEAN_AS(func_0205e8b0, HeadLook_StartScene)
