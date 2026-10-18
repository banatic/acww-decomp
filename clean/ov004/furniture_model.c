/* The model files of a piece of furniture, and the room object's animations
 * (furniture_model.h). */
#include "furniture_model.h"

#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "autoload_2/heap.h"
#include "clean.h"
#include "main/item_code.h"
#include "main/c_library.h"
#include "main/model_anim.h"
#include "main/model_cache.h"
#include "main/model_loader.h"
#include "main/model_pool.h"
#include "main/rom_file.h"
#include "main/vram_region.h"

static_assert(offsetof(FurnitureModel, loader) == 0x10, "loader");
static_assert(offsetof(FurnitureModel, anims) == 0x44, "animations");
static_assert(offsetof(FurnitureModel, item) == 0x70, "item");
static_assert(offsetof(FurnitureModel, keep_texture_copy) == 0x72, "copy flag");
static_assert(sizeof(FurnitureModel) == 0x74, "furniture model");
static_assert(sizeof(FurnitureAnim) == 0x20, "animation");

#define LOADER_DONE 3   /* the texture loader's last state */
#define VARIANTS 2      /* the animation files "...0" and "...1" */
#define TAIL_ALIGN (-4) /* allocated from the end of the heap */

/* NitroSystem's archive (NNSFndArchive), mounted on the stack while the files are taken out. */
typedef struct Archive {
    u32 words[26];
} Archive;

/* The heap the texture file is read into. */
extern void *data_021fbe94;
/* The archive's name, "FTR", and its files: the model (a pointer to "FTR:a/bmd/bmd0") and the
 * animations, "FTR:a/<kind>/<kind>%d". */
extern const char data_ov004_0224ff90[];
extern const char *data_ov004_0224fd4c;
extern const char data_ov004_0224ff94[]; /* bca: joints */
extern const char data_ov004_0224ffa4[]; /* bma: material colours */
extern const char data_ov004_0224ffb4[]; /* bva: visibility */
extern const char data_ov004_0224ffc4[]; /* bta: texture coordinates */
extern const char data_ov004_0224ffd4[]; /* btp: texture patterns */
/* The paths' formats, "/ftr/%d/%d/%04x.nsbtx" and "/ftr/%d/%d/%04x.arc", and their buffers. */
extern const char data_ov004_0224ffe4[];
extern const char data_ov004_0224fffc[];
extern char data_ov004_02256ea4[];
extern char data_ov004_02256e7c[];
/* The vtable of FurnitureAnim. */
extern const u8 data_ov004_0224fe44[];

extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
/* The slot the furniture is loaded for: something at 8 for the texture, and a heap. */
extern int NNS_FndMountArchive(Archive *archive, const char *name, void *data);
extern u8 *NNS_FndGetArchiveFileByName(const char *path);
extern int func_0210285c(Archive *archive);
extern u8 *func_02107828(u8 *file);
extern void *NNS_G3dGetJntAnmSet(u8 *file);
extern void *NNS_G3dGetMatCAnmSet(u8 *file);
extern void *NNS_G3dGetVisAnmSet(u8 *file);
extern void *NNS_G3dGetTexSRTAnmSet(u8 *file);
extern void *NNS_G3dGetTexPatAnmSet(u8 *file);
extern u8 *func_02107b44(void *set, u32 index);
extern u8 *func_02107b80(void *set, u32 index);
extern u8 *func_02107cf0(void *set, u32 index);
extern u8 *func_02107bbc(void *set, u32 index);
extern u8 *func_02107bf8(void *set, u32 index);
extern void *func_021077e8(u8 *file);

/* An arithmetic shift right, for negative values too. */
static s32 shift_right(s32 value, int bits)
{
    return value >= 0 ? value >> bits : ~(~value >> bits);
}

static u16 read16(const u8 *p)
{
    u16 value;
    memcpy(&value, p, sizeof value);
    return value;
}

static u32 read32(const u8 *p)
{
    u32 value;
    memcpy(&value, p, sizeof value);
    return value;
}

static u32 address(const void *p)
{
    return (u32) (uintptr_t) p;
}

/* Whether two item codes are the same furniture; codes with variants are compared without
 * them. */
static int same_item(const ItemCode *a, const ItemCode *b)
{
    if (ItemCode_HasVariant(a)) {
        int item = ItemCode_VariantItem(a);
        return item == ItemCode_VariantItem(b);
    }
    return *a == *b;
}

/* func_ov004_0220e028: the end of a load: no furniture being loaded, the texture file freed
 * and the loader reset. Always 0. */
int FurnitureModel_EndLoad(FurnitureModel *files)
{
    files->item = ITEM_CODE_NONE;
    FurnitureModel_FreeTextureFile(files);
    ModelLoader_Release(&files->loader);
    files->keep_texture_copy = 0;
    return 0;
}
CLEAN_AS(func_ov004_0220e028, FurnitureModel_EndLoad)

/* func_ov004_0220e050: the texture, or none until it is loaded. */
u8 *FurnitureModel_Texture(FurnitureModel *files)
{
    if (FurnitureModel_IsLoaded(files)) {
        return files->texture;
    }
    return NULL;
}
CLEAN_AS(func_ov004_0220e050, FurnitureModel_Texture)

/* func_ov004_0220e068: the model, or none until the texture is loaded. */
u8 *FurnitureModel_Model(FurnitureModel *files)
{
    if (FurnitureModel_IsLoaded(files)) {
        return files->model;
    }
    return NULL;
}
CLEAN_AS(func_ov004_0220e068, FurnitureModel_Model)

/* func_ov004_0220e080: one step of loading furniture `number` (a step a frame): whether it is
 * loaded. It refuses (0) while another furniture is being loaded. */
int FurnitureModel_LoadStep(FurnitureModel *files, void *slot, int number, int keep_texture_copy)
{
    if (FurnitureModel_IsLoaded(files)) {
        return 1;
    }
    ItemCode none = ITEM_CODE_NONE;
    if (same_item(&files->item, &none)) {
        files->item = ItemCode_MakeVariant(number, 0);
        files->keep_texture_copy = (u8) keep_texture_copy;
    } else {
        ItemCode item = ItemCode_MakeVariant(number, 0);
        if (!same_item(&item, &files->item)) {
            return 0;
        }
    }
    FurnitureModel_LoadFiles(files, slot, number);
    if (files->texture == NULL) {
        void *texture = func_021077e8(files->texture_file);
        VramRegion *for_texture = (VramRegion *) (uintptr_t) ModelPoolEntry_Vram(slot);
        Heap *heap = (Heap *) (uintptr_t) ModelPoolEntry_Heap(slot);
        if (ModelLoader_StepTexture(&files->loader, texture, for_texture, heap) == LOADER_DONE) {
            files->texture = ModelLoader_Texture(&files->loader);
            FurnitureModel_EndLoad(files);
            return 1;
        }
    }
    return 0;
}
CLEAN_AS(func_ov004_0220e080, FurnitureModel_LoadStep)

/* func_ov004_0220e1a0: loads furniture `number` at once. Always 1.
 * QUIRK: the copy flag is set even when the model is already loaded. */
int FurnitureModel_Load(FurnitureModel *files, void *slot, int number, int keep_texture_copy)
{
    files->keep_texture_copy = (u8) keep_texture_copy;
    if (FurnitureModel_IsLoaded(files)) {
        return 1;
    }
    files->item = ItemCode_MakeVariant(number, 0);
    FurnitureModel_LoadFiles(files, slot, number);
    void *texture = func_021077e8(files->texture_file);
    VramRegion_LoadTexture(texture, (VramRegion *) (uintptr_t) ModelPoolEntry_Vram(slot));
    files->texture = ModelCache_CopyTexture(texture, (Heap *) (uintptr_t) ModelPoolEntry_Heap(slot));
    FurnitureModel_EndLoad(files);
    return 1;
}
CLEAN_AS(func_ov004_0220e1a0, FurnitureModel_Load)

/* func_ov004_0220e208: frees the texture file. Always 0. */
int FurnitureModel_FreeTextureFile(FurnitureModel *files)
{
    if (files->texture_file != NULL) {
        Heap_FreeCurrent(files->texture_file);
        files->texture_file = NULL;
    }
    return 0;
}
CLEAN_AS(func_ov004_0220e208, FurnitureModel_FreeTextureFile)

/* func_ov004_0220e220 */
AnimSet *FurnitureModel_Anims(FurnitureModel *files)
{
    return &files->anims;
}
CLEAN_AS(func_ov004_0220e220, FurnitureModel_Anims)

/* func_ov004_0220e224: reads the files of furniture `number` that are not read yet: the texture
 * file (with a copy into the slot's heap when one is to be kept), the archive, and from it the
 * model and the animations. Whether the texture file and the model are there. */
int FurnitureModel_LoadFiles(FurnitureModel *files, void *slot, int number)
{
    if (files->texture_file == NULL) {
        u32 size;
        files->texture_file = RomFile_Load(FurnitureModel_TexturePath(files, number), data_021fbe94, TAIL_ALIGN, &size);
        if (files->keep_texture_copy) {
            u8 *copy = Heap_Alloc((Heap *) (uintptr_t) ModelPoolEntry_Heap(slot), size);
            MI_CpuCopy8(files->texture_file, copy, size);
            AnimSet_SetFile28(&files->anims, address(copy));
        }
    }
    if (files->archive == NULL) {
        u32 size;
        char *path = FurnitureModel_ArchivePath(files, number);
        files->archive = RomFile_Load(path, (Heap *) (uintptr_t) ModelPoolEntry_Heap(slot), 4, &size);
    }
    if (files->model == NULL && files->archive != NULL) {
        Archive archive;
        if (NNS_FndMountArchive(&archive, data_ov004_0224ff90, files->archive)) {
            /* the model set's dictionary: its entries' offset at 0xe, the first model's offset
             * 4 bytes into the entries (8 from the dictionary at 8) */
            u8 *set = func_02107828(NNS_FndGetArchiveFileByName(data_ov004_0224fd4c));
            files->model = set + read32(set + read16(set + 0xe) + 0xc);
            for (unsigned int i = 0; i < VARIANTS; i++) {
                char name[32];
                u8 *file;
                CLib_SPrintf(name, data_ov004_0224ff94, i);
                file = NNS_FndGetArchiveFileByName(name);
                if (file != NULL) {
                    AnimSet_SetAnim00(&files->anims, address(func_02107b44(NNS_G3dGetJntAnmSet(file), 0)), (int) i);
                }
                CLib_SPrintf(name, data_ov004_0224ffa4, i);
                file = NNS_FndGetArchiveFileByName(name);
                if (file != NULL) {
                    AnimSet_SetAnim08(&files->anims, address(func_02107b80(NNS_G3dGetMatCAnmSet(file), 0)), (int) i);
                }
                CLib_SPrintf(name, data_ov004_0224ffb4, i);
                file = NNS_FndGetArchiveFileByName(name);
                if (file != NULL) {
                    AnimSet_SetAnim10(&files->anims, address(func_02107cf0(NNS_G3dGetVisAnmSet(file), 0)), (int) i);
                }
                CLib_SPrintf(name, data_ov004_0224ffc4, i);
                file = NNS_FndGetArchiveFileByName(name);
                if (file != NULL) {
                    AnimSet_SetAnim18(&files->anims, address(func_02107bbc(NNS_G3dGetTexSRTAnmSet(file), 0)), (int) i);
                }
                CLib_SPrintf(name, data_ov004_0224ffd4, i);
                file = NNS_FndGetArchiveFileByName(name);
                if (file != NULL) {
                    AnimSet_SetAnim20(&files->anims, address(func_02107bf8(NNS_G3dGetTexPatAnmSet(file), 0)), (int) i);
                }
            }
            func_0210285c(&archive);
        }
    }
    return files->texture_file != NULL && files->model != NULL;
}
CLEAN_AS(func_ov004_0220e224, FurnitureModel_LoadFiles)

/* func_ov004_0220e3f0: the texture file's path, in a static buffer. */
char *FurnitureModel_TexturePath(FurnitureModel *files, int number)
{
    (void) files;
    CLib_SPrintf(data_ov004_02256ea4, data_ov004_0224ffe4, shift_right(number, 8), (number & 0xff) >> 4, number);
    return data_ov004_02256ea4;
}
CLEAN_AS(func_ov004_0220e3f0, FurnitureModel_TexturePath)

/* func_ov004_0220e41c: the archive's path, in a static buffer. */
char *FurnitureModel_ArchivePath(FurnitureModel *files, int number)
{
    (void) files;
    CLib_SPrintf(data_ov004_02256e7c, data_ov004_0224fffc, shift_right(number, 8), (number & 0xff) >> 4, number);
    return data_ov004_02256e7c;
}
CLEAN_AS(func_ov004_0220e41c, FurnitureModel_ArchivePath)

/* func_ov004_0220e448 */
int FurnitureModel_IsLoaded(FurnitureModel *files)
{
    return files->texture != NULL;
}
CLEAN_AS(func_ov004_0220e448, FurnitureModel_IsLoaded)

/* func_ov004_0220e458 */
FurnitureModel *FurnitureModel_Destruct(FurnitureModel *files)
{
    AnimSet_Destruct(&files->anims);
    ModelLoader_Destruct(&files->loader);
    return files;
}
CLEAN_AS(func_ov004_0220e458, FurnitureModel_Destruct)

/* func_ov004_0220e474: nothing loaded.
 * QUIRK: the item code is written twice. */
FurnitureModel *FurnitureModel_Construct(FurnitureModel *files)
{
    ModelLoader_Construct(&files->loader);
    AnimSet_Construct(&files->anims);
    files->item = ITEM_CODE_NONE;
    files->texture_file = NULL;
    files->archive = NULL;
    files->model = NULL;
    files->texture = NULL;
    files->item = ITEM_CODE_NONE;
    files->keep_texture_copy = 0;
    return files;
}
CLEAN_AS(func_ov004_0220e474, FurnitureModel_Construct)

/* func_ov004_0220e4b0 */
AnimatedModelAnim *FurnitureAnim_Target(const FurnitureAnim *anim)
{
    return anim->base.anim;
}
CLEAN_AS(func_ov004_0220e4b0, FurnitureAnim_Target)

/* func_ov004_0220e4b4: the destructor that also frees the object (operator delete,
 * Heap_OperatorDeleteB). */
FurnitureAnim *FurnitureAnim_Delete(FurnitureAnim *anim)
{
    anim->base.ctrl.vtable = data_ov004_0224fe44;
    ModelAnim_Destruct(&anim->base);
    Heap_OperatorDeleteB(anim);
    return anim;
}
CLEAN_AS(func_ov004_0220e4b4, FurnitureAnim_Delete)

/* func_ov004_0220e4d4 */
FurnitureAnim *FurnitureAnim_Destruct(FurnitureAnim *anim)
{
    anim->base.ctrl.vtable = data_ov004_0224fe44;
    ModelAnim_Destruct(&anim->base);
    return anim;
}
CLEAN_AS(func_ov004_0220e4d4, FurnitureAnim_Destruct)

/* func_ov004_0220e4ec */
FurnitureAnim *FurnitureAnim_Construct(FurnitureAnim *anim)
{
    ModelAnim_ConstructBase(&anim->base);
    anim->base.ctrl.vtable = data_ov004_0224fe44;
    return anim;
}
CLEAN_AS(func_ov004_0220e4ec, FurnitureAnim_Construct)
