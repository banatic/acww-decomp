/* The houses' palettes and X files (house_files.h). */
#include "house_files.h"

#include "autoload_2/heap.h" /* Heap, Heap_FreeCurrent */
#include "clean.h"
#include "main/c_library.h" /* CLib_SPrintf */
#include "main/house_looks.h"
#include "main/model_cache.h"
#include "main/rom_file.h"
#include "main/scene_query.h"
#include "main/town_record.h"
#include "main/vram_region.h"

static_assert(offsetof(HouseXFiles, models) == 0x04, "models");
static_assert(offsetof(HouseXFiles, deco) == 0x18, "deco");
static_assert(offsetof(HouseXFiles, loaded) == 0x1c, "loaded");

/* The event the town takes part in for which the X files are loaded. */
#define HOUSE_X_FILES_EVENT 0x11
/* RomFile_LoadFormattedOn's alignment that takes the block from the heap's end. */
#define HOUSE_PALETTE_FROM_END (-4)
#define HOUSE_X_FILES_ALIGN 4

/* The heap files are loaded on, and main's heap. */
extern Heap *data_021fbe94;
extern Heap *data_021c9b1c;
/* The town's record (its events, TownRecord_FindEvent). */
extern TownRecord data_021f39fc;
/* "/str/house_pl/house_pl_%c.nsbtx" */
extern const char data_ov003_02239b74[];
/* "/str/npcHsX.arc", its name "STR", "STR:a/obj_x_house%d.nsbmd", "STR:a/obj_x_house0.nsbtx",
 * "STR:a/obj_x_deco.nsbtp", and the buffer the models' paths are formatted in. */
extern const char data_ov003_02239b94[];
extern const char data_ov003_02239ba4[];
extern const char data_ov003_02239ba8[];
extern const char data_ov003_02239bc4[];
extern const char data_ov003_02239be0[];
extern char data_ov003_0223cec8[];

/* NitroSystem's archive (NNSFndArchive, 0x6c bytes): mounted over a file in memory, a file of
 * it by path, and unmounted. */
typedef struct HouseFilesArchive {
    u32 words[0x1b];
} HouseFilesArchive;
extern int NNS_FndMountArchive(HouseFilesArchive *archive, const char *name, void *data);
extern u8 *NNS_FndGetArchiveFileByName(const char *path);
extern int func_0210285c(HouseFilesArchive *archive);
/* NitroSystem's 3D files: a .nsbmd's model set, a file's texture resource, a .nsbtp's set of
 * texture pattern animations and the animation `index` of such a set. */
extern u8 *func_02107828(u8 *file);
extern void *func_021077e8(u8 *file);
extern void *NNS_G3dGetTexPatAnmSet(u8 *file);
extern void *func_02107bf8(void *set, int index);

/* The first model of a model set (NNSG3dResMdlSet): its dictionary's first entry. */
static u8 *house_files_first_model(u8 *set)
{
    u16 entries = *(const u16 *) (const void *) (set + 0x0e);
    return set + *(const u32 *) (const void *) (set + entries + 0x0c);
}

/* func_ov003_0221fe2c: the palettes' texture resource. */
int HousePalette_Texture(HousePalette *palette)
{
    return (int) (uintptr_t) palette->texture;
}
CLEAN_AS(func_ov003_0221fe2c, HousePalette_Texture)

/* func_ov003_0221fe30: when the field is left, nothing happens to the palettes.
 * QUIRK: their copy stays in main's heap and the pointer is kept. */
void HousePalette_Release(HousePalette *palette)
{
    (void) palette;
}
CLEAN_AS(func_ov003_0221fe30, HousePalette_Release)

/* func_ov003_0221fe34: loads "/str/house_pl/house_pl_<letter>.nsbtx" from the end of the heap
 * files are loaded on, sends its palettes to VRAM and keeps a copy of its texture resource in
 * main's heap; the file is freed. 0 when it could not be loaded, else 1. */
int HousePalette_Load(HousePalette *palette)
{
    Heap *heap = data_021fbe94;
    int letter = HouseFiles_SeasonLetter();
    u8 *file = RomFile_LoadFormattedOn(heap, HOUSE_PALETTE_FROM_END, data_ov003_02239b74, letter);
    if (file == NULL) {
        return 0;
    }
    palette->texture = func_021077e8(file);
    VramRegion_LoadPalettes(palette->texture, NULL);
    palette->texture = ModelCache_CopyTexture(palette->texture, data_021c9b1c);
    Heap_FreeCurrent(file);
    return 1;
}
CLEAN_AS(func_ov003_0221fe34, HousePalette_Load)

/* func_ov003_0221fe90: the palettes' destructor, registered for data_ov003_0223ce58; does
 * nothing. */
void HousePalette_Destruct(void) {}
CLEAN_AS(func_ov003_0221fe90, HousePalette_Destruct)

/* func_ov003_0221fe94: the palettes' constructor: none yet. */
void HousePalette_Construct(HousePalette *palette)
{
    palette->texture = NULL;
}
CLEAN_AS(func_ov003_0221fe94, HousePalette_Construct)

/* func_ov003_0221fe9c */
int HouseXFiles_Loaded(HouseXFiles *files)
{
    return files->loaded;
}
CLEAN_AS(func_ov003_0221fe9c, HouseXFiles_Loaded)

/* func_ov003_0221fea0 */
int HouseXFiles_Deco(HouseXFiles *files)
{
    return (int) (uintptr_t) files->deco;
}
CLEAN_AS(func_ov003_0221fea0, HouseXFiles_Deco)

/* func_ov003_0221fea4: the model of house kind `kind`, NULL from kind 5 on. */
void *HouseXFiles_Model(HouseXFiles *files, unsigned int kind)
{
    if (kind < HOUSE_X_FILES_MODELS) {
        return files->models[kind];
    }
    return NULL;
}
CLEAN_AS(func_ov003_0221fea4, HouseXFiles_Model)

/* func_ov003_0221feb4 */
int HouseXFiles_Texture(HouseXFiles *files)
{
    return (int) (uintptr_t) files->texture;
}
CLEAN_AS(func_ov003_0221feb4, HouseXFiles_Texture)

/* func_ov003_0221feb8: when the field is left, the files are forgotten (their memory goes with
 * main's heap). */
void HouseXFiles_Release(HouseXFiles *files)
{
    HouseXFiles_Clear(files);
}
CLEAN_AS(func_ov003_0221feb8, HouseXFiles_Release)

/* func_ov003_0221fec0: forgets the files; then, only while the town takes part in event 0x11
 * (else 0), loads "/str/npcHsX.arc" into main's heap and, when it mounts, keeps its five
 * models, sends its texture to VRAM and keeps it, keeps the decoration's animation, and says
 * the archive was loaded. 1. */
int HouseXFiles_Load(HouseXFiles *files)
{
    HouseFilesArchive archive;

    HouseXFiles_Clear(files);
    if (TownRecord_FindEvent((int) (uintptr_t) &data_021f39fc, HOUSE_X_FILES_EVENT) == -1) {
        return 0;
    }

    void *data = RomFile_Load(data_ov003_02239b94, data_021c9b1c, HOUSE_X_FILES_ALIGN, NULL);
    if (NNS_FndMountArchive(&archive, data_ov003_02239ba4, data) != 0) {
        for (unsigned int i = 0; i < HOUSE_X_FILES_MODELS; i++) {
            CLib_SPrintf(data_ov003_0223cec8, data_ov003_02239ba8, i);
            files->models[i] = house_files_first_model(func_02107828(NNS_FndGetArchiveFileByName(data_ov003_0223cec8)));
        }
        files->texture = func_021077e8(NNS_FndGetArchiveFileByName(data_ov003_02239bc4));
        VramRegion_LoadTexture(files->texture, NULL);
        files->deco = func_02107bf8(NNS_G3dGetTexPatAnmSet(NNS_FndGetArchiveFileByName(data_ov003_02239be0)), 0);
        files->loaded = 1;
        func_0210285c(&archive);
    }
    return 1;
}
CLEAN_AS(func_ov003_0221fec0, HouseXFiles_Load)

/* func_ov003_0221ff80: nothing loaded. */
void HouseXFiles_Clear(HouseXFiles *files)
{
    for (unsigned int i = 0; i < HOUSE_X_FILES_MODELS; i++) {
        files->models[i] = NULL;
    }
    files->texture = NULL;
    files->deco = NULL;
    files->loaded = 0;
}
CLEAN_AS(func_ov003_0221ff80, HouseXFiles_Clear)

/* func_ov003_0221ff98: the X files' destructor, registered for data_ov003_0223ce80; does
 * nothing. */
void HouseXFiles_Destruct(void) {}
CLEAN_AS(func_ov003_0221ff98, HouseXFiles_Destruct)

/* func_ov003_0221ff9c: the X files' constructor (for data_ov003_0223ce80): nothing loaded. */
HouseXFiles *HouseXFiles_Construct(HouseXFiles *files)
{
    HouseXFiles_Clear(files);
    return files;
}
CLEAN_AS(func_ov003_0221ff9c, HouseXFiles_Construct)

/* ---- The house textures (HouseTextures) ---- */

static_assert(offsetof(HouseTextures, light) == 0x10, "light");
static_assert(offsetof(HouseTextures, anim_i) == 0x20, "anim_i");
static_assert(offsetof(HouseTextures, anim_o) == 0x24, "anim_o");

/* The houses' look is a number 0-24: set (look / 5, a letter from 'A') and variant (look % 5). */
#define HOUSE_TEXTURES_VARIANTS 5
#define HOUSE_TEXTURES_FIRST_SET 'A'

/* The town's record of the houses' looks. */
extern HouseLooksRecord data_021f34b0;
/* "/str/npcHsTex/%c/house_%c%d%c.nsbtx" (set, set, variant, season letter),
 * "/str/npcHsTex/%c/light_%c%d.nsbtx" (set, set, variant), "/str/obj_house_i.nsbca" and
 * "/str/obj_house_o.nsbca". */
extern const char data_ov003_02239bf8[];
extern const char data_ov003_02239c1c[];
extern const char data_ov003_02239c40[];
extern const char data_ov003_02239c58[];
/* The season letters, 's' and 'w', by SceneQuery_IsSnowSeason. */
extern const signed char data_ov003_0223666c[];
/* The three sets of files (house_files.h). */
extern HousePalette data_ov003_0223ce58;
extern HouseXFiles data_ov003_0223ce80;
extern HouseTextures data_ov003_0223cea0;
/* NitroSystem's 3D files: a .nsbca's set of joint animations, and the animation `index` of
 * such a set. */
extern void *NNS_G3dGetJntAnmSet(u8 *file);
extern u8 *func_02107b44(void *set, u32 index);

/* func_ov003_0221ffac */
void *HouseTextures_AnimO(HouseTextures *textures)
{
    return textures->anim_o;
}
CLEAN_AS(func_ov003_0221ffac, HouseTextures_AnimO)

/* func_ov003_0221ffb0 */
void *HouseTextures_AnimI(HouseTextures *textures)
{
    return textures->anim_i;
}
CLEAN_AS(func_ov003_0221ffb0, HouseTextures_AnimI)

/* func_ov003_0221ffb4: the light's texture of house look `look`, taken modulo 4. */
void *HouseTextures_Light(HouseTextures *textures, int look)
{
    return textures->light[look & (HOUSE_TEXTURES_LOOKS - 1)];
}
CLEAN_AS(func_ov003_0221ffb4, HouseTextures_Light)

/* func_ov003_0221ffc0: the house's texture of house look `look`, taken modulo 4. */
void *HouseTextures_House(HouseTextures *textures, int look)
{
    return textures->house[look & (HOUSE_TEXTURES_LOOKS - 1)];
}
CLEAN_AS(func_ov003_0221ffc0, HouseTextures_House)

/* func_ov003_0221ffcc: nothing loaded. */
void HouseTextures_Clear(HouseTextures *textures)
{
    for (unsigned int i = 0; i < HOUSE_TEXTURES_LOOKS; i++) {
        textures->house[i] = NULL;
        textures->light[i] = NULL;
    }
    textures->anim_o = NULL;
    textures->anim_i = NULL;
}
CLEAN_AS(func_ov003_0221ffcc, HouseTextures_Clear)

/* func_ov003_0221ffec: for each of the town's four house looks, loads the house's texture (in
 * the season's letter) and the light's from the end of the heap files are loaded on; each one's
 * texture resource is kept, and when its images go to VRAM (VramRegion_LoadImages and
 * VramRegion_LoadTexture say nonzero) a copy of it in main's heap is kept instead; the files are
 * freed. Then the two joint animations are loaded into main's heap and their first animations
 * kept. 1.
 * QUIRK: main's heap is read once at the start for the lights and the animations, but again
 * for each house's copy. */
int HouseTextures_Load(HouseTextures *textures)
{
    Heap *heap = data_021c9b1c;

    for (u8 i = 0; i < HOUSE_TEXTURES_LOOKS; i++) {
        int look = HouseLooks_Look(HouseLooks_Looks(&data_021f34b0), i);
        signed char set = (signed char) (look / HOUSE_TEXTURES_VARIANTS + HOUSE_TEXTURES_FIRST_SET);
        int variant = look % HOUSE_TEXTURES_VARIANTS;

        int season = HouseFiles_SeasonLetter();
        u8 *file =
            RomFile_LoadFormattedOn(data_021fbe94, HOUSE_PALETTE_FROM_END, data_ov003_02239bf8, set, set, variant, season);
        textures->house[i] = func_021077e8(file);
        if (VramRegion_LoadImages(textures->house[i], NULL) != 0) {
            textures->house[i] = ModelCache_CopyTexture(textures->house[i], data_021c9b1c);
        }
        Heap_FreeCurrent(file);

        file = RomFile_LoadFormattedOn(data_021fbe94, HOUSE_PALETTE_FROM_END, data_ov003_02239c1c, set, set, variant);
        textures->light[i] = func_021077e8(file);
        if (VramRegion_LoadTexture(textures->light[i], NULL) != 0) {
            textures->light[i] = ModelCache_CopyTexture(textures->light[i], heap);
        }
        Heap_FreeCurrent(file);
    }
    textures->anim_i =
        func_02107b44(NNS_G3dGetJntAnmSet(RomFile_Load(data_ov003_02239c40, heap, HOUSE_X_FILES_ALIGN, NULL)), 0);
    textures->anim_o =
        func_02107b44(NNS_G3dGetJntAnmSet(RomFile_Load(data_ov003_02239c58, heap, HOUSE_X_FILES_ALIGN, NULL)), 0);
    return 1;
}
CLEAN_AS(func_ov003_0221ffec, HouseTextures_Load)

/* func_ov003_0222010c: the textures' destructor, registered for data_ov003_0223cea0; does
 * nothing. */
void HouseTextures_Destruct(void) {}
CLEAN_AS(func_ov003_0222010c, HouseTextures_Destruct)

/* func_ov003_02220110: the textures' constructor: nothing loaded. */
HouseTextures *HouseTextures_Construct(HouseTextures *textures)
{
    HouseTextures_Clear(textures);
    return textures;
}
CLEAN_AS(func_ov003_02220110, HouseTextures_Construct)

/* ---- The sets themselves ---- */

/* func_ov003_022203b8 */
HouseXFiles *HouseFiles_XFiles(void)
{
    return &data_ov003_0223ce80;
}
CLEAN_AS(func_ov003_022203b8, HouseFiles_XFiles)

/* func_ov003_022203c0 */
HouseTextures *HouseFiles_Textures(void)
{
    return &data_ov003_0223cea0;
}
CLEAN_AS(func_ov003_022203c0, HouseFiles_Textures)

/* func_ov003_022203c8 */
HousePalette *HouseFiles_Palette(void)
{
    return &data_ov003_0223ce58;
}
CLEAN_AS(func_ov003_022203c8, HouseFiles_Palette)

/* func_ov003_022203dc: the letter of the season in the houses' file names: 'w' while it is the
 * snow season (SceneQuery_IsSnowSeason), else 's'. */
signed char HouseFiles_SeasonLetter(void)
{
    return data_ov003_0223666c[SceneQuery_IsSnowSeason()];
}
CLEAN_AS(func_ov003_022203dc, HouseFiles_SeasonLetter)
