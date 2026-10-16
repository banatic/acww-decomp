/* The background models of the field (bg_models.h). */
#include "bg_models.h"

#include "clean.h"
#include "town_layout.h"

static_assert(sizeof(BgModel) == 0x30, "model size");
static_assert(offsetof(BgModels, data) == 0x5d0, "data");
static_assert(offsetof(BgModels, full) == 0x618, "full");
static_assert(offsetof(BgModels, heap_size) == 0x61c, "heap size");
static_assert(offsetof(BgModels, ground_texture) == 0x630, "ground texture");
static_assert(offsetof(BgModels, beb_texture) == 0x648, "beB texture");
static_assert(sizeof(BgModels) == 0x64c, "models size");
static_assert(sizeof(BgMark) == 0x0c, "mark size");

/* The bytes of an entry of "mgt0" after its count: the kind, a byte, then x and z as s16. */
#define BG_MARK_SIZE 6
/* The models with a texture of their own: 1 in bits 12-15. */
#define BG_MODEL_OWN_TEXTURE 1
/* The background heap's size (in KB) of the scenes data_020c9fd4 has no entry for. */
#define BG_HEAP_DEFAULT_KB 0xac
#define BG_HEAP_SCENES 0x33

/* NitroSystem's archive (NNSFndArchive), mounted on the stack while the files are taken out. */
typedef struct BgArchive {
    u32 words[26];
} BgArchive;

/* The models. */
extern BgModels data_021c52c0;
/* The background heap, and the current heap. */
extern Heap *data_021c9b24;
extern Heap *data_021fbe94;
/* The town's layout (town_layout.h). */
extern u8 data_021e9aac[];
/* The background heap's size in KB in each scene. */
extern const u8 data_020c9fd4[BG_HEAP_SCENES];

/* The paths and names: "/bg/a%d/%04x.arc", the archive's name "BG", "BG:a/bmd/bmd0",
 * "BG:a/bcl/bcl0", "BG:a/bsd/bsd0", "BG:a/bca/bca0", "BG:a/bma/bma0", "BG:a/bta/bta0",
 * "BG:a/mgt/mgt0", "/bg/t%d/%04x.nsbtx", "/bg/grd_anm.arc", "BG:a/grd_set.nsbma",
 * "BG:a/grd_set.nsbta", "BG:a/riv.nsbtp", "BG:a/riv_itp.nsbtx", "BG:a/beB.nsbtp",
 * "BG:a/beB_itp.nsbtx" and "/bg/ct%d/grd_set%d%c.nsbtx". */
extern const char data_020da37c[];
extern const char data_020da390[];
extern const char data_020da394[];
extern const char data_020da3a4[];
extern const char data_020da3b4[];
extern const char data_020da3c4[];
extern const char data_020da3d4[];
extern const char data_020da3e4[];
extern const char data_020da3f4[];
extern const char data_020da404[];
extern const char data_020da418[];
extern const char data_020da428[];
extern const char data_020da43c[];
extern const char data_020da450[];
extern const char data_020da460[];
extern const char data_020da474[];
extern const char data_020da484[];
extern const char data_020da498[];

/* sprintf. */
extern int func_02064328(char *buffer, const char *format, ...);
/* A file read whole into `heap` (from its end when `align` is negative); its size into *size
 * when `size` is not NULL. */
extern u8 *func_02064b2c(const char *path, Heap *heap, int align, u32 *size);
extern int NNS_FndMountArchive(BgArchive *archive, const char *name, void *data);
extern u8 *NNS_FndGetArchiveFileByName(const char *path);
/* The archive unmounted. */
extern int func_0210285c(BgArchive *archive);
/* The model set of a model file. */
extern u8 *func_02107828(u8 *file);
extern void *NNS_G3dGetJntAnmSet(u8 *file);
extern void *NNS_G3dGetMatCAnmSet(u8 *file);
extern void *NNS_G3dGetTexSRTAnmSet(u8 *file);
extern void *NNS_G3dGetTexPatAnmSet(u8 *file);
/* The animation `index` of a set. */
extern u8 *func_02107b44(void *set, u32 index);
extern u8 *func_02107b80(void *set, u32 index);
extern u8 *func_02107bbc(void *set, u32 index);
extern u8 *func_02107bf8(void *set, u32 index);
/* The texture of a texture file; the texture prepared, and copied to `heap`. */
extern void *func_021077e8(u8 *file);
extern int func_02056064(void *texture, void *for_texture);
extern void *func_020561cc(void *texture, Heap *heap);
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
/* The background heap destroyed; the background heap made, of `size` bytes. */
extern void func_0205cab0(void);
extern void func_0205cacc(u32 size, void *parent);
/* The current scene. */
extern u8 func_020b65c4(void);

static u16 read_u16(const u8 *p)
{
    return (u16) (p[0] | p[1] << 8);
}

static u32 read_u32(const u8 *p)
{
    return (u32) p[0] | (u32) p[1] << 8 | (u32) p[2] << 16 | (u32) p[3] << 24;
}

/* The first model of a model set (NNS_G3dGetMdlByIdx(set, 0)): the set's dictionary at 0x08
 * gives the offset of its entries at 0x0e, and the first entry the model's offset in the set. */
static u8 *first_model(u8 *set)
{
    u16 entries = read_u16(set + 0x0e);

    return set + read_u32(set + entries + 0x0c);
}

/* What both clears do to the models and their data: every slot free, every model number
 * BG_MODEL_NONE. The archives' sizes are left as they are. */
static void clear_slots(BgModels *self)
{
    for (int i = 0; i < BG_MODELS_SLOTS; i++) {
        BgModel *model = &self->models[i];

        model->key = BG_MODEL_NONE;
        model->archive = NULL;
        model->model = NULL;
        model->data = NULL;
        model->bsd = NULL;
        model->joint_anim = NULL;
        model->colour_anim = NULL;
        model->texture_anim = NULL;
        model->texture = NULL;
        model->marks = NULL;
        model->mark_count = 0;
    }
    for (int i = 0; i < BG_MODELS_DATA_SLOTS; i++) {
        self->data[i].key = BG_MODEL_NONE;
        self->data[i].data = NULL;
    }
}

/* func_0203750c: the address of the background models. */
int BgModels_Get(void)
{
    return (int) (uintptr_t) &data_021c52c0;
}
CLEAN_AS(func_0203750c, BgModels_Get)

/* func_02037514: mark `index` of a "mgt0" file (`marks` points at its count), its position
 * turned to fx32. The index is not checked; the callers loop up to BgModels_MarkCount. */
void BgModels_MarkAt(BgMark *out, const u8 *marks, int index)
{
    const u8 *entry = marks + 2 + index * BG_MARK_SIZE;

    out->kind = entry[0];
    out->x = (s16) read_u16(entry + 2) * 4096;
    out->z = (s16) read_u16(entry + 4) * 4096;
}
CLEAN_AS(func_02037514, BgModels_MarkAt)

/* func_02037544: the number of marks of a "mgt0" file. */
int BgModels_MarkCount(const s16 *marks)
{
    return marks[0];
}
CLEAN_AS(func_02037544, BgModels_MarkCount)

/* func_0203754c */
u32 BgModels_BebTexture(const BgModels *self)
{
    return (u32) (uintptr_t) self->beb_texture;
}
CLEAN_AS(func_0203754c, BgModels_BebTexture)

/* func_02037558 */
u32 BgModels_BebPatternAnim(const BgModels *self)
{
    return (u32) (uintptr_t) self->beb_pattern_anim;
}
CLEAN_AS(func_02037558, BgModels_BebPatternAnim)

/* func_02037564 */
u32 BgModels_RiverTexture(const BgModels *self)
{
    return (u32) (uintptr_t) self->river_texture;
}
CLEAN_AS(func_02037564, BgModels_RiverTexture)

/* func_02037570 */
int BgModels_RiverPatternAnim(const BgModels *self)
{
    return (int) (uintptr_t) self->river_pattern_anim;
}
CLEAN_AS(func_02037570, BgModels_RiverPatternAnim)

/* func_0203757c */
u32 BgModels_GroundTextureAnim(const BgModels *self)
{
    return (u32) (uintptr_t) self->ground_texture_anim;
}
CLEAN_AS(func_0203757c, BgModels_GroundTextureAnim)

/* func_02037588 */
u32 BgModels_GroundColourAnim(const BgModels *self)
{
    return (u32) (uintptr_t) self->ground_colour_anim;
}
CLEAN_AS(func_02037588, BgModels_GroundColourAnim)

/* func_02037594 */
u32 BgModels_GroundTexture(const BgModels *self)
{
    return (u32) (uintptr_t) self->ground_texture;
}
CLEAN_AS(func_02037594, BgModels_GroundTexture)

/* func_020375a0: when the field is left: every slot free, the ground's texture and the setup
 * forgotten, and the background heap destroyed; 1.
 * QUIRK: unlike BgModels_Clear it leaves the ground's animations, the water's textures and
 * animations and the words 0x620-0x62c as they are. */
int BgModels_Release(BgModels *self)
{
    clear_slots(self);
    self->ground_texture = NULL;
    self->full = 0;
    self->heap_size = 0;
    func_0205cab0();
    return 1;
}
CLEAN_AS(func_020375a0, BgModels_Release)

/* func_02037608: the slot of model `key`, loaded into the first free slot when no slot before it
 * holds the model (slots fill in order and are only freed all together); NULL when every slot
 * holds another. Loading reads the archive into the background heap and takes its files out,
 * then for models 0x1000-0x1fff reads their texture at the end of the current heap and copies
 * it to the background heap. */
BgModel *BgModels_Load(BgModels *self, int key)
{
    Heap *heap = data_021c9b24;

    for (int i = 0; i < BG_MODELS_SLOTS; i++) {
        BgModel *model = &self->models[i];

        if (model->archive != NULL) {
            if (model->key == (u32) key) {
                return model;
            }
            continue;
        }

        char path[0x20];
        BgArchive archive;
        int folder = key >> 4;

        func_02064328(path, data_020da37c, folder, key);
        model->archive = BgModels_LoadFile(path, &model->archive_size);
        if (NNS_FndMountArchive(&archive, data_020da390, model->archive) != 0) {
            u8 *file;

            model->model = first_model(func_02107828(NNS_FndGetArchiveFileByName(data_020da394)));
            model->data = NNS_FndGetArchiveFileByName(data_020da3a4);
            model->bsd = NNS_FndGetArchiveFileByName(data_020da3b4);
            if ((file = NNS_FndGetArchiveFileByName(data_020da3c4)) != NULL) {
                model->joint_anim = func_02107b44(NNS_G3dGetJntAnmSet(file), 0);
            }
            if ((file = NNS_FndGetArchiveFileByName(data_020da3d4)) != NULL) {
                model->colour_anim = func_02107b80(NNS_G3dGetMatCAnmSet(file), 0);
            }
            if ((file = NNS_FndGetArchiveFileByName(data_020da3e4)) != NULL) {
                model->texture_anim = func_02107bbc(NNS_G3dGetTexSRTAnmSet(file), 0);
            }
            if ((file = NNS_FndGetArchiveFileByName(data_020da3f4)) != NULL) {
                model->marks = file + 2;
                model->mark_count = (s16) read_u16(file);
            }
            func_0210285c(&archive);
        }
        if (((key & 0xf000) >> 12) == BG_MODEL_OWN_TEXTURE) {
            u8 *file;

            func_02064328(path, data_020da404, folder, key);
            file = func_02064b2c(path, data_021fbe94, -4, NULL);
            if (file != NULL) {
                void *texture = func_021077e8(file);

                func_02056064(texture, NULL);
                model->texture = func_020561cc(texture, heap);
                Heap_FreeCurrent(file);
            }
        }
        model->key = (u32) key;
        return model;
    }
    return NULL;
}
CLEAN_AS(func_02037608, BgModels_Load)

/* func_0203776c: the acre data of model `key`: the data slot that holds it, else the first free
 * data slot given the data of the loaded model `key` or, when no model slot holds it, the data
 * read from its archive into the background heap; 0 when every data slot holds another.
 * QUIRK: the model slots are searched by number alone, cleared ones (BG_MODEL_NONE) included. */
int BgModels_Data(BgModels *self, int key)
{
    u8 *loaded = NULL;

    for (int i = 0; i < BG_MODELS_SLOTS; i++) {
        if (self->models[i].key == (u32) key) {
            loaded = self->models[i].data;
            break;
        }
    }

    for (int i = 0; i < BG_MODELS_DATA_SLOTS; i++) {
        BgModelData *slot = &self->data[i];

        if (slot->data == NULL) {
            if (loaded != NULL) {
                slot->key = (u32) key;
                slot->data = loaded;
            } else {
                slot->data = BgModels_LoadData(key, data_021c9b24);
                slot->key = (u32) key;
            }
            return (int) (uintptr_t) slot->data;
        }
        if (slot->key == (u32) key) {
            return (int) (uintptr_t) slot->data;
        }
    }
    return 0;
}
CLEAN_AS(func_0203776c, BgModels_Data)

/* func_020377d8: the acre data ("bcl0") of model `key` copied into a block of `heap`, from its
 * archive read for the time at the end of the current heap; NULL when the archive does not
 * mount.
 * QUIRK: the data is copied after the archive is unmounted (the file is still loaded), and the
 * block is not checked before the copy. */
void *BgModels_LoadData(int key, Heap *heap)
{
    char path[0x20];
    BgArchive archive;
    u8 *file;
    void *data = NULL;

    func_02064328(path, data_020da37c, key >> 4, key);
    file = func_02064b2c(path, data_021fbe94, -4, NULL);
    if (NNS_FndMountArchive(&archive, data_020da390, file) != 0) {
        u8 *source = NNS_FndGetArchiveFileByName(data_020da3a4);

        func_0210285c(&archive);
        data = Heap_Alloc(heap, BG_MODEL_DATA_SIZE);
        MI_CpuCopy8(source, data, BG_MODEL_DATA_SIZE);
    }
    if (file != NULL) {
        Heap_FreeCurrent(file);
    }
    return data;
}
CLEAN_AS(func_020377d8, BgModels_LoadData)

/* func_02037858: the ground's and the water's animations and textures, from "/bg/grd_anm.arc"
 * read into the background heap (and kept there: they point into it). */
void BgModels_LoadGroundAnims(BgModels *self)
{
    BgArchive archive;

    if (NNS_FndMountArchive(&archive, data_020da390, BgModels_LoadFile(data_020da418, NULL)) == 0) {
        return;
    }
    self->ground_colour_anim = func_02107b80(NNS_G3dGetMatCAnmSet(NNS_FndGetArchiveFileByName(data_020da428)), 0);
    self->ground_texture_anim = func_02107bbc(NNS_G3dGetTexSRTAnmSet(NNS_FndGetArchiveFileByName(data_020da43c)), 0);
    self->river_pattern_anim = func_02107bf8(NNS_G3dGetTexPatAnmSet(NNS_FndGetArchiveFileByName(data_020da450)), 0);
    self->river_texture = func_021077e8(NNS_FndGetArchiveFileByName(data_020da460));
    self->beb_pattern_anim = func_02107bf8(NNS_G3dGetTexPatAnmSet(NNS_FndGetArchiveFileByName(data_020da474)), 0);
    self->beb_texture = func_021077e8(NNS_FndGetArchiveFileByName(data_020da484));
    func_0210285c(&archive);
}
CLEAN_AS(func_02037858, BgModels_LoadGroundAnims)

/* func_02037928: the ground's texture "/bg/ct<n>/grd_set<n><season>.nsbtx", with n the town's
 * random setting and the season 'a' + bits 2-7 of the layout's settings, read at the end of the
 * current heap and copied to the background heap.
 * QUIRK: the texture is taken out of the file even when the file could not be read. */
void BgModels_LoadGroundTexture(BgModels *self)
{
    u32 folder = BgModels_TownSetting(self);
    u32 set = BgModels_TownSetting(self);
    const TownLayout *layout = (const TownLayout *) (const void *) data_021e9aac;
    char path[0x20];
    u8 *file;

    func_02064328(path, data_020da498, folder, set, 'a' + (layout->settings >> 2));
    file = func_02064b2c(path, data_021fbe94, -4, NULL);
    self->ground_texture = func_021077e8(file);
    func_02056064(self->ground_texture, NULL);
    self->ground_texture = func_020561cc(self->ground_texture, data_021c9b24);
    if (file != NULL) {
        Heap_FreeCurrent(file);
    }
}
CLEAN_AS(func_02037928, BgModels_LoadGroundTexture)

/* func_020379ac: the town's random setting (bits 0-1 of the layout's settings). */
u32 BgModels_TownSetting(BgModels *self)
{
    (void) self;
    return TownLayout_RandomSetting((TownLayout *) (void *) data_021e9aac);
}
CLEAN_AS(func_020379ac, BgModels_TownSetting)

/* func_020379bc: the field's setup: in scene 0x2c the layout's upper settings chosen again;
 * every slot cleared; the background heap made at the scene's size (data_020c9fd4, in KB);
 * then the ground's texture loaded when `full` is set or in scenes 0x0b, 0x0c-0x0e and 0x2f,
 * and the ground's animations when `full` is set; 1. */
int BgModels_SetUp(BgModels *self, int full)
{
    u8 scene = func_020b65c4();
    u8 heap_kb;

    if (scene == 0x2c) {
        TownLayout_SetUpperSettings((unsigned int) (uintptr_t) data_021e9aac);
    }
    BgModels_Clear(self);
    self->full = (u8) full;

    scene = func_020b65c4();
    heap_kb = scene < BG_HEAP_SCENES ? data_020c9fd4[scene] : BG_HEAP_DEFAULT_KB;
    self->heap_size = (u32) heap_kb << 10;
    func_0205cacc(self->heap_size, NULL);

    if (full != 0 || scene == 0x0b || scene == 0x2f || (scene >= 0x0c && scene <= 0x0e)) {
        BgModels_LoadGroundTexture(self);
    }
    if (full != 0) {
        BgModels_LoadGroundAnims(self);
    }
    return 1;
}
CLEAN_AS(func_020379bc, BgModels_SetUp)

/* func_02037a40: every slot free, and the ground's texture and animations, the river's, the
 * setup and the words 0x620-0x62c cleared.
 * QUIRK: the texture and animation of "beB" (0x644, 0x648) are left as they are. */
void BgModels_Clear(BgModels *self)
{
    clear_slots(self);
    self->ground_texture = NULL;
    self->ground_colour_anim = NULL;
    self->ground_texture_anim = NULL;
    self->river_pattern_anim = NULL;
    self->river_texture = NULL;
    self->full = 0;
    self->heap_size = 0;
    for (int i = 0; i < 4; i++) {
        self->unk_620[i] = 0;
    }
}
CLEAN_AS(func_02037a40, BgModels_Clear)

/* func_02037ae4: its destructor: nothing. */
void BgModels_Destruct(BgModels *self)
{
    (void) self;
}
CLEAN_AS(func_02037ae4, BgModels_Destruct)

/* func_02037ae8: its constructor: the clear; its address. */
int BgModels_Construct(BgModels *self)
{
    BgModels_Clear(self);
    return (int) (uintptr_t) self;
}
CLEAN_AS(func_02037ae8, BgModels_Construct)

/* func_02037af8: a file read whole into the background heap (from its start); its size into
 * *size when `size` is not NULL. */
void *BgModels_LoadFile(const char *path, u32 *size)
{
    return func_02064b2c(path, data_021c9b24, 4, size);
}
CLEAN_AS(func_02037af8, BgModels_LoadFile)
