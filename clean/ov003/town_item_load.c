/* Overlay 3's loading of the town's map code models (town_item_load.h). */
#include "town_item_load.h"

#include "autoload_2/heap.h"
#include "clean.h"
#include "growth_model.h"
#include "growth_part.h"
#include "main/animated_model.h"
#include "main/town_day.h"
#include "main/town_record.h"
#include "main/vram_region.h"
#include "main/rom_file.h"
#include "main/item_info.h"

static_assert(sizeof(ModelObject) == 0x9c, "model object");
static_assert(offsetof(TileEventProcess, models_0174) == 0x174, "models_0174");
static_assert(offsetof(TileEventProcess, models_0c6c) == 0xc6c, "models_0c6c");
static_assert(offsetof(TileEventProcess, models_1014) == 0x1014, "models_1014");
static_assert(offsetof(TileEventProcess, models_11e8) == 0x11e8, "models_11e8");
static_assert(offsetof(TileEventProcess, models_1590) == 0x1590, "models_1590");
static_assert(offsetof(TileEventProcess, models_2df0) == 0x2df0, "models_2df0");
static_assert(offsetof(TileEventProcess, unk_3060) == 0x3060, "unk_3060");
static_assert(offsetof(TileEventProcess, models_3068) == 0x3068, "models_3068");
static_assert(offsetof(TileEventProcess, models_43e8) == 0x43e8, "models_43e8");
static_assert(offsetof(TileEventProcess, models_4708) == 0x4708, "models_4708");
static_assert(offsetof(TileEventProcess, models_4840) == 0x4840, "models_4840");
static_assert(offsetof(TileEventProcess, models_49a8) == 0x49a8, "models_49a8");
static_assert(offsetof(TileEventProcess, sets) == 0x4ae0, "sets");
static_assert(offsetof(TileEventProcess, member_4b20) == 0x4b20, "member_4b20");
static_assert(offsetof(GrowthModels, line_5d) == 0xf90, "line_5d");
static_assert(offsetof(GrowthModels, line_c8) == 0x18a4, "line_c8");
static_assert(offsetof(GrowthModel, model) == 8, "a growth model's model");
static_assert(offsetof(AnimatedModel, object) == 0, "an animated model's holder");

/* The process (NULL while there is none), its two heaps, and the scene's heap (the texture
 * files are read into it). */
extern TileEventProcess *data_ov003_0223cf70;
extern Heap *data_ov003_0223cf74;
extern Heap *data_ov003_0223cf78;
extern Heap *data_021fbe94;
/* The overlay's memory block the first heap is made over (up to data_ov003_0225f0b4,
 * 0x21400 bytes). */
extern u8 data_ov003_0223dcb4[];
extern u8 data_ov003_0225f0b4[];
/* The growth models' parts and the tile events' table. */
extern GrowthParts data_ov003_0223cfa0;
extern TileEventEntry data_ov003_0223cfe4[];

/* The nine loaders TownItemLoad_RunLoaders runs. */
#define TOWN_ITEM_LOAD_LOADERS 9
extern int (*const data_ov003_0223b8a4[TOWN_ITEM_LOAD_LOADERS])(void);

/* The town's periods of the year (TownRecord_Period). */
#define TOWN_ITEM_LOAD_PERIODS 23
/* The look of each tree variant, by period: 0, 1 or 2 (the files named 'w', 'f' and 's'). */
extern const int data_ov003_02236e64[TOWN_ITEM_LOAD_PERIODS][TOWN_ITEM_LOAD_VARIANTS];
/* The palettes the trees' materials take, by period: the first material's (0-22) and 22. */
extern const u32 data_ov003_02236dac[TOWN_ITEM_LOAD_PERIODS][2];
/* The palette of the grass, by period. */
extern const u32 data_ov003_02236cf4[TOWN_ITEM_LOAD_PERIODS];
/* The palette of the first hole and crack holders, by period (3, 2, 1 or 0). */
extern const u32 data_ov003_02236d50[TOWN_ITEM_LOAD_PERIODS];
/* The palette of the second hole and crack holders (4). */
extern const u32 data_ov003_02237284;
extern const u32 data_ov003_02237288;

/* Trees: the texture files of each look (six: sapling, stages 1-4, dead), the palette files of
 * the grown trees and of saplings and dead trees (one per variant), the model files and the
 * growth models' files of each look ('/fg/tree/...', '/fg/eff_tree/anm_t...'). */
extern const char *const *const data_ov003_02239f44[3];
extern const char *const data_ov003_02239f80[TOWN_ITEM_LOAD_VARIANTS];
extern const char *const data_ov003_02239f08[TOWN_ITEM_LOAD_VARIANTS];
extern const char *const *const data_ov003_02239f20[3];
extern const char *const *const data_ov003_02239f8c[3];
/* Cedars: the texture files, model files and growth models' files of each look, and the two
 * palette files (grown; sapling and dead). */
extern const char *const *const data_ov003_02239f14[3];
extern const char *const *const data_ov003_02239f50[3];
extern const char *const *const data_ov003_02239f38[3];
extern const char *const data_ov003_02239c78;
extern const char *const data_ov003_02239c84;
/* Palms: the same (they have no palette files of their own). */
extern const char *const *const data_ov003_02239f74[3];
extern const char *const *const data_ov003_02239ee4[3];
extern const char *const *const data_ov003_02239efc[3];
/* The cedar with lights ('obj_x_cedar'): its texture, palette and model files. */
extern const char *const data_ov003_02239c80;
extern const char *const data_ov003_02239c7c;
extern const char *const data_ov003_02239c8c;
/* The flower families (tulip, pansy, cosmos, rose): texture, palette and model files, and the
 * holders each has. */
#define TOWN_ITEM_LOAD_FAMILIES 4
#define TOWN_ITEM_LOAD_PER_FAMILY 10
extern const char *const data_ov003_0223a208[TOWN_ITEM_LOAD_FAMILIES];
extern const char *const data_ov003_0223a058[TOWN_ITEM_LOAD_FAMILIES];
extern const char *const data_ov003_0223a068[TOWN_ITEM_LOAD_FAMILIES];
extern const int data_ov003_02236afc[TOWN_ITEM_LOAD_FAMILIES];
/* The two flowers of two holders each (suzuran, rafflesia): texture, palette and model files. */
#define TOWN_ITEM_LOAD_PAIRS 2
extern const char *const data_ov003_02239db8[TOWN_ITEM_LOAD_PAIRS];
extern const char *const data_ov003_0223a088[TOWN_ITEM_LOAD_PAIRS];
extern const char *const data_ov003_02239d28[TOWN_ITEM_LOAD_PAIRS];
/* The dandelions' model set file and the names of its two models. */
extern const char data_ov003_0223bd58[];
extern const char *const data_ov003_02239d60[2];
/* Grass: the palette file and the five model files (grass A-D, clover). */
extern const char *const data_ov003_02239c90;
extern const char *const data_ov003_0223a218[5];
/* Holes and cracks: palette and model files. */
extern const char *const data_ov003_02239c94;
extern const char *const data_ov003_02239c74;
extern const char *const data_ov003_02239c70;
extern const char *const data_ov003_02239c88;
/* The red turnips' two model files, and the design model file. */
extern const char *const data_ov003_02239dc8[2];
extern const char data_ov003_0223bd44[];

/* The process's words outside the parts tile_event.h names. */
#define TOWN_ITEM_LOAD_CLOCK 0x6a6c /* the draw's frames, 0-59 */

/* The players and their designs drawn on the ground. */
#define TOWN_ITEM_LOAD_PLAYERS 4
#define TOWN_ITEM_LOAD_DESIGNS 8

/* The holder of growth model `model` (its animated model's). */
static ModelObject *town_item_load_growth(GrowthModel *model)
{
    return &((AnimatedModel *) (void *) model->model)->object;
}

static GrowthModels *town_item_load_growth_models(TileEventProcess *process)
{
    return (GrowthModels *) (void *) process->member_4b20;
}

/* Heap_Free of the scene's heap for a file there is (then forgotten). */
static void town_item_load_free(Heap *heap, void **file)
{
    if (*file != NULL) {
        Heap_Free(heap, *file);
        *file = NULL;
    }
}

/* func_ov003_02225e98 (vtable slot 6 of 0x0223bc7c, the per-frame work): the tile events
 * stepped, the growth models updated. Done (1). */
int TownItemLoad_StepProcess(TileEventProcess *process)
{
    TileEvent_StepAll(data_ov003_0223cfe4);
    GrowthModels_UpdateAll(town_item_load_growth_models(process));
    return 1;
}
CLEAN_AS(func_ov003_02225e98, TownItemLoad_StepProcess)

/* func_ov003_02225ebc (vtable slot 0, the INIT phase's work): the heaps made when there are
 * none (an expanded heap over the overlay's block, one of 0x8c00 bytes from the scene's heap);
 * with the icon set and the item holders loaded, the process is the current one and the nine
 * loaders run; when they all succeed the clock starts at 0, the growth models are set up, the
 * growth parts and tile events cleared and the town's day entered: 1. Otherwise the process is
 * not kept (when the loaders failed) and 0.
 * QUIRK: on failure the heaps stay, and what was loaded stays in them. */
int TownItemLoad_InitProcess(TileEventProcess *process)
{
    int ok = 0;
    if (data_ov003_0223cf74 == NULL) {
        u32 size = (u32) ((uintptr_t) data_ov003_0225f0b4 - (uintptr_t) data_ov003_0223dcb4);
        data_ov003_0223cf74 = ExpHeap_CreateAt(data_ov003_0223dcb4, size);
    }
    if (data_ov003_0223cf78 == NULL) {
        data_ov003_0223cf78 = ExpHeap_Create(0x8c00, data_021fbe94);
    }
    if (TownItemLoad_LoadIcons(process)) {
        data_ov003_0223cf70 = process;
        if (TownItemLoad_RunLoaders(process)) {
            *(int *) (void *) ((u8 *) process + TOWN_ITEM_LOAD_CLOCK) = 0;
            GrowthModels_SetupAll(town_item_load_growth_models(process));
            GrowthPart_InitAll(&data_ov003_0223cfa0);
            TileEvent_InitAll(data_ov003_0223cfe4);
            TownDay_Enter();
            ok = 1;
        } else {
            data_ov003_0223cf70 = NULL;
        }
    }
    return ok;
}
CLEAN_AS(func_ov003_02225ebc, TownItemLoad_InitProcess)

/* func_ov003_02225f68: the loaders of data_ov003_0223b8a4 run in order (trees, flowers, grass,
 * func_ov003_022271f8, holes, cracks, stamps, red turnips, designs) until one fails: 0; 1 when
 * all succeed. They work on the current process, not on `process`. */
int TownItemLoad_RunLoaders(TileEventProcess *process)
{
    (void) process;
    for (int i = 0; i < TOWN_ITEM_LOAD_LOADERS; i++) {
        if (data_ov003_0223b8a4[i]() == 0) {
            return 0;
        }
    }
    return 1;
}
CLEAN_AS(func_ov003_02225f68, TownItemLoad_RunLoaders)

/* func_ov003_02225f94: the current process's design holders loaded. */
int TownItemLoad_LoadDesigns(void)
{
    return TownItemLoad_LoadDesignModels(data_ov003_0223cf70);
}
CLEAN_AS(func_ov003_02225f94, TownItemLoad_LoadDesigns)

/* func_ov003_02225fa4: the 32 holders at 0x3068 (codes 0xa7-0xc6), eight per player, each the
 * design model with that player's design; 0 at the first that fails. */
int TownItemLoad_LoadDesignModels(TileEventProcess *process)
{
    ModelObject *model = process->models_3068;
    for (int player = 0; player < TOWN_ITEM_LOAD_PLAYERS; player++) {
        for (int design = 0; design < TOWN_ITEM_LOAD_DESIGNS; design++) {
            if (ModelObject_LoadWithDesign(model, data_ov003_0223bd44, player, design) == 0) {
                return 0;
            }
            model++;
        }
    }
    return 1;
}
CLEAN_AS(func_ov003_02225fa4, TownItemLoad_LoadDesignModels)

/* func_ov003_02225ff0: the red turnips loaded (TownItemLoad_LoadTurnipModels). */
int TownItemLoad_LoadTurnips(void)
{
    return TownItemLoad_LoadTurnipModels();
}
CLEAN_AS(func_ov003_02225ff0, TownItemLoad_LoadTurnips)

/* func_ov003_02225ff8: the two holders at 0x49a8 (codes 0xd4-0xe2) loaded from the red turnip
 * model files into the second heap; 0 at the first that fails. */
int TownItemLoad_LoadTurnipModels(void)
{
    for (int i = 0; i < 2; i++) {
        if (ModelObject_Load(&data_ov003_0223cf70->models_49a8[i], data_ov003_02239dc8[i], data_ov003_0223cf78) == 0) {
            return 0;
        }
    }
    return 1;
}
CLEAN_AS(func_ov003_02225ff8, TownItemLoad_LoadTurnipModels)

/* func_ov003_02226048: the cracks' palette file read, the crack holders loaded with it, the
 * file freed (when it was read); 1 when both succeeded. */
int TownItemLoad_LoadCracks(void)
{
    int ok = 0;
    void *palettes = NULL;
    void *file = NULL;
    if (TownItemLoad_LoadCrackPalettes(data_ov003_0223cf70, &palettes, &file) != 0) {
        if (TownItemLoad_LoadCrackModels(data_ov003_0223cf70, palettes) != 0) {
            ok = 1;
        }
    }
    if (file != NULL) {
        Heap_Free(data_021fbe94, file);
    }
    return ok;
}
CLEAN_AS(func_ov003_02226048, TownItemLoad_LoadCracks)

/* func_ov003_02226094: the two holders at 0x4840 (codes 0xa6 and 0xfe) from the crack model
 * file, with its own textures and `palettes`: the first with the period's palette
 * (TownItemLoad_HolePalette), the second with palette 4. 0 when one fails. */
int TownItemLoad_LoadCrackModels(TileEventProcess *process, void *palettes)
{
    u32 palette = (u32) TownItemLoad_HolePalette(process);
    if (ModelObject_LoadWithPalettes(&process->models_4840[0], data_ov003_02239c88, data_ov003_0223cf74, NULL, palettes,
                                     &palette, 1) == 0) {
        return 0;
    }
    if (ModelObject_LoadWithPalettes(&process->models_4840[1], data_ov003_02239c88, data_ov003_0223cf74, NULL, palettes,
                                     &data_ov003_02237284, 1) != 0) {
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov003_02226094, TownItemLoad_LoadCrackModels)

/* func_ov003_02226108: the cracks' palette file read (func_ov003_022272c0). */
int TownItemLoad_LoadCrackPalettes(TileEventProcess *process, void **palettes, void **file)
{
    return TownItemLoad_LoadPaletteFiles(process, palettes, file, &data_ov003_02239c70, 1);
}
CLEAN_AS(func_ov003_02226108, TownItemLoad_LoadCrackPalettes)

/* func_ov003_02226120: the holes' palette file read, the hole holders loaded with it, the
 * file freed (when it was read); 1 when both succeeded. */
int TownItemLoad_LoadHoles(void)
{
    int ok = 0;
    void *palettes = NULL;
    void *file = NULL;
    if (TownItemLoad_LoadHolePalettes(data_ov003_0223cf70, &palettes, &file) != 0) {
        if (TownItemLoad_LoadHoleModels(data_ov003_0223cf70, palettes) != 0) {
            ok = 1;
        }
    }
    if (file != NULL) {
        Heap_Free(data_021fbe94, file);
    }
    return ok;
}
CLEAN_AS(func_ov003_02226120, TownItemLoad_LoadHoles)

/* func_ov003_0222616c: the two holders at 0x4708 (codes 0xfc and 0xfd) from the hole model
 * file, with its own textures and `palettes`: the first with the period's palette
 * (TownItemLoad_HolePalette), the second with palette 4. 0 when one fails. */
int TownItemLoad_LoadHoleModels(TileEventProcess *process, void *palettes)
{
    u32 palette = (u32) TownItemLoad_HolePalette(process);
    if (ModelObject_LoadWithPalettes(&process->models_4708[0], data_ov003_02239c74, data_ov003_0223cf74, NULL, palettes,
                                     &palette, 1) == 0) {
        return 0;
    }
    if (ModelObject_LoadWithPalettes(&process->models_4708[1], data_ov003_02239c74, data_ov003_0223cf74, NULL, palettes,
                                     &data_ov003_02237288, 1) != 0) {
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov003_0222616c, TownItemLoad_LoadHoleModels)

/* func_ov003_022261e0: the holes' palette file read (func_ov003_022272c0). */
int TownItemLoad_LoadHolePalettes(TileEventProcess *process, void **palettes, void **file)
{
    return TownItemLoad_LoadPaletteFiles(process, palettes, file, &data_ov003_02239c94, 1);
}
CLEAN_AS(func_ov003_022261e0, TownItemLoad_LoadHolePalettes)

/* func_ov003_022261f8: the palette of the first hole and crack holders in the town's period. */
int TownItemLoad_HolePalette(TileEventProcess *process)
{
    (void) process;
    return (int) data_ov003_02236d50[TownRecord_Period()];
}
CLEAN_AS(func_ov003_022261f8, TownItemLoad_HolePalette)

/* func_ov003_02226210: the grass palette file read, the grass holders loaded with it, the file
 * freed (when it was read); 1 when both succeeded. */
int TownItemLoad_LoadGrass(void)
{
    int ok = 0;
    void *palettes = NULL;
    void *file = NULL;
    if (TownItemLoad_LoadGrassPalettes(data_ov003_0223cf70, &palettes, &file) != 0) {
        if (TownItemLoad_LoadGrassModels(data_ov003_0223cf70, palettes) != 0) {
            ok = 1;
        }
    }
    if (file != NULL) {
        Heap_Free(data_021fbe94, file);
    }
    return ok;
}
CLEAN_AS(func_ov003_02226210, TownItemLoad_LoadGrass)

/* func_ov003_0222625c: the five holders at 0x43e8 (codes 0x1f-0x24) from the grass model files,
 * with their own textures and `palettes`, all with the grass palette of the town's period. 0 at
 * the first that fails. */
int TownItemLoad_LoadGrassModels(TileEventProcess *process, void *palettes)
{
    const u32 *palette = &data_ov003_02236cf4[TownRecord_Period()];
    for (int i = 0; i < 5; i++) {
        if (ModelObject_LoadWithPalettes(&process->models_43e8[i], data_ov003_0223a218[i], data_ov003_0223cf74, NULL, palettes,
                                         palette, 1) == 0) {
            return 0;
        }
    }
    return 1;
}
CLEAN_AS(func_ov003_0222625c, TownItemLoad_LoadGrassModels)

/* func_ov003_022262c0: the grass palette file read (func_ov003_022272c0). */
int TownItemLoad_LoadGrassPalettes(TileEventProcess *process, void **palettes, void **file)
{
    return TownItemLoad_LoadPaletteFiles(process, palettes, file, &data_ov003_02239c90, 1);
}
CLEAN_AS(func_ov003_022262c0, TownItemLoad_LoadGrassPalettes)

/* func_ov003_022262d8: the flowers: the families' texture and palette files read and their
 * holders loaded, the same for the two flowers of two holders, every file read freed, then the
 * dandelions loaded. 1 when all of it succeeded. */
int TownItemLoad_LoadFlowers(void)
{
    void *pair_textures[TOWN_ITEM_LOAD_PAIRS] = {NULL};
    void *pair_texture_files[TOWN_ITEM_LOAD_PAIRS] = {NULL};
    void *pair_palettes[TOWN_ITEM_LOAD_PAIRS] = {NULL};
    void *pair_palette_files[TOWN_ITEM_LOAD_PAIRS] = {NULL};
    void *family_textures[TOWN_ITEM_LOAD_FAMILIES] = {NULL};
    void *family_texture_files[TOWN_ITEM_LOAD_FAMILIES] = {NULL};
    void *family_palettes[TOWN_ITEM_LOAD_FAMILIES] = {NULL};
    void *family_palette_files[TOWN_ITEM_LOAD_FAMILIES] = {NULL};
    int families_ok = 0;
    int pairs_ok = 0;

    if (TownItemLoad_LoadFlowerFamilyTextures(data_ov003_0223cf70, family_textures, family_texture_files) &&
        TownItemLoad_LoadFlowerFamilyPalettes(data_ov003_0223cf70, family_palettes, family_palette_files) &&
        TownItemLoad_LoadFlowerFamilyModels(data_ov003_0223cf70, family_textures, family_palettes)) {
        families_ok = 1;
    }
    if (TownItemLoad_LoadFlowerPairTextures(data_ov003_0223cf70, pair_textures, pair_texture_files) &&
        TownItemLoad_LoadFlowerPairPalettes(data_ov003_0223cf70, pair_palettes, pair_palette_files) &&
        TownItemLoad_LoadFlowerPairModels(data_ov003_0223cf70, pair_textures, pair_palettes)) {
        pairs_ok = 1;
    }
    TownItemLoad_FreeFlowerFiles(data_ov003_0223cf70, family_texture_files, family_palette_files, pair_texture_files,
                                 pair_palette_files);
    int dandelions_ok = TownItemLoad_LoadDandelions(data_ov003_0223cf70);
    return families_ok && pairs_ok && dandelions_ok;
}
CLEAN_AS(func_ov003_022262d8, TownItemLoad_LoadFlowers)

/* func_ov003_022263b4: the flowers' files freed from the scene's heap and forgotten: each
 * family's texture then palette file, then each pair's. */
void TownItemLoad_FreeFlowerFiles(TileEventProcess *process, void **family_texture_files, void **family_palette_files,
                                  void **pair_texture_files, void **pair_palette_files)
{
    (void) process;
    Heap *heap = data_021fbe94;
    for (int i = 0; i < TOWN_ITEM_LOAD_FAMILIES; i++) {
        town_item_load_free(heap, &family_texture_files[i]);
        town_item_load_free(heap, &family_palette_files[i]);
    }
    for (int i = 0; i < TOWN_ITEM_LOAD_PAIRS; i++) {
        town_item_load_free(heap, &pair_texture_files[i]);
        town_item_load_free(heap, &pair_palette_files[i]);
    }
}
CLEAN_AS(func_ov003_022263b4, TownItemLoad_FreeFlowerFiles)

/* func_ov003_02226438: model set 1 loaded from the dandelions' file into the first heap, and
 * the pointers at 0x3060 (codes 0x1d and 0x1e) set to its two models by name; 0 when the set
 * could not be loaded. */
int TownItemLoad_LoadDandelions(TileEventProcess *process)
{
    if (ModelSet_Load(&process->sets[1], data_ov003_0223bd58, data_ov003_0223cf74) == 0) {
        return 0;
    }
    ModelObject **dandelions = (ModelObject **) (void *) process->unk_3060;
    for (int i = 0; i < 2; i++) {
        dandelions[i] = ModelSet_Find(&process->sets[1], data_ov003_02239d60[i]);
    }
    return 1;
}
CLEAN_AS(func_ov003_02226438, TownItemLoad_LoadDandelions)

/* func_ov003_02226490: the four holders at 0x2df0, two per flower of the pair, from its model
 * file with its texture and palettes, holder j with palette j. 0 at the first that fails. */
int TownItemLoad_LoadFlowerPairModels(TileEventProcess *process, void **textures, void **palettes)
{
    for (int pair = 0; pair < TOWN_ITEM_LOAD_PAIRS; pair++) {
        for (u32 j = 0; j < 2; j++) {
            if (ModelObject_LoadWithPalettes(&process->models_2df0[pair * 2 + (int) j], data_ov003_02239d28[pair],
                                             data_ov003_0223cf74, textures[pair], palettes[pair], &j, 1) == 0) {
                return 0;
            }
        }
    }
    return 1;
}
CLEAN_AS(func_ov003_02226490, TownItemLoad_LoadFlowerPairModels)

/* func_ov003_02226514: the pair's two palette files read (func_ov003_022272c0). */
int TownItemLoad_LoadFlowerPairPalettes(TileEventProcess *process, void **palettes, void **files)
{
    return TownItemLoad_LoadPaletteFiles(process, palettes, files, data_ov003_0223a088, TOWN_ITEM_LOAD_PAIRS);
}
CLEAN_AS(func_ov003_02226514, TownItemLoad_LoadFlowerPairPalettes)

/* func_ov003_0222652c: the pair's two texture files read (func_ov003_02227324). */
int TownItemLoad_LoadFlowerPairTextures(TileEventProcess *process, void **textures, void **files)
{
    return TownItemLoad_LoadTextureFiles(process, textures, files, data_ov003_02239db8, TOWN_ITEM_LOAD_PAIRS);
}
CLEAN_AS(func_ov003_0222652c, TownItemLoad_LoadFlowerPairTextures)

/* func_ov003_02226544: the families' holders at 0x1590, ten per family of which the first 7,
 * 7, 7 and 10 are loaded, each from its family's model file with its texture and palettes,
 * holder j with palette j. 0 at the first that fails. */
int TownItemLoad_LoadFlowerFamilyModels(TileEventProcess *process, void **textures, void **palettes)
{
    for (int family = 0; family < TOWN_ITEM_LOAD_FAMILIES; family++) {
        ModelObject *first = &process->models_1590[family * TOWN_ITEM_LOAD_PER_FAMILY];
        for (u32 j = 0; (int) j < data_ov003_02236afc[family]; j++) {
            if (ModelObject_LoadWithPalettes(&first[j], data_ov003_0223a068[family], data_ov003_0223cf74, textures[family],
                                             palettes[family], &j, 1) == 0) {
                return 0;
            }
        }
    }
    return 1;
}
CLEAN_AS(func_ov003_02226544, TownItemLoad_LoadFlowerFamilyModels)

/* func_ov003_022265d4: the families' four palette files read (func_ov003_022272c0). */
int TownItemLoad_LoadFlowerFamilyPalettes(TileEventProcess *process, void **palettes, void **files)
{
    return TownItemLoad_LoadPaletteFiles(process, palettes, files, data_ov003_0223a058, TOWN_ITEM_LOAD_FAMILIES);
}
CLEAN_AS(func_ov003_022265d4, TownItemLoad_LoadFlowerFamilyPalettes)

/* func_ov003_022265ec: the families' four texture files read (func_ov003_02227324). */
int TownItemLoad_LoadFlowerFamilyTextures(TileEventProcess *process, void **textures, void **files)
{
    return TownItemLoad_LoadTextureFiles(process, textures, files, data_ov003_0223a208, TOWN_ITEM_LOAD_FAMILIES);
}
CLEAN_AS(func_ov003_022265ec, TownItemLoad_LoadFlowerFamilyTextures)

/* func_ov003_02226604: the trees, in four groups, each with its files read, its holders
 * loaded and its files freed: the plain and fruit trees, the cedars, the cedar with lights and
 * the palms. The materials take the palettes of the town's period (data_ov003_02236dac). 1
 * when every group succeeded.
 * QUIRK: the cedar with lights sets the cedars' success flag: when it loads, a failure of the
 * cedars is not seen.
 * QUIRK: the palms are loaded with the cedars' palette files. */
int TownItemLoad_LoadTrees(void)
{
    void *cedar_palette, *cedar_palette_file, *cedar_sapling_palette, *cedar_sapling_palette_file;
    void *x_texture, *x_texture_file, *x_palette, *x_palette_file;
    void *palm_palette, *palm_palette_file, *palm_sapling_palette, *palm_sapling_palette_file;
    void *tree_palettes[TOWN_ITEM_LOAD_VARIANTS], *tree_palette_files[TOWN_ITEM_LOAD_VARIANTS];
    void *tree_sapling_palettes[TOWN_ITEM_LOAD_VARIANTS], *tree_sapling_palette_files[TOWN_ITEM_LOAD_VARIANTS];
    void *cedar_textures[TOWN_ITEM_LOAD_STAGES], *cedar_texture_files[TOWN_ITEM_LOAD_STAGES];
    void *palm_textures[TOWN_ITEM_LOAD_STAGES], *palm_texture_files[TOWN_ITEM_LOAD_STAGES];
    void *tree_textures[3 * TOWN_ITEM_LOAD_STAGES], *tree_texture_files[3 * TOWN_ITEM_LOAD_STAGES];

    int period = TownRecord_Period();
    int trees_ok = 0;
    int cedars_ok = 0;
    int palms_ok = 0;
    const u32 *palettes = data_ov003_02236dac[period];

    TownItemLoad_ClearTreeFiles(data_ov003_0223cf70, tree_textures, tree_texture_files, tree_palettes, tree_palette_files,
                                tree_sapling_palettes, tree_sapling_palette_files);
    if (TownItemLoad_LoadTreeTextures(data_ov003_0223cf70, tree_textures, tree_texture_files) &&
        TownItemLoad_LoadTreePalettes(data_ov003_0223cf70, tree_palettes, tree_palette_files, tree_sapling_palettes,
                                      tree_sapling_palette_files) &&
        TownItemLoad_LoadTreeSaplingModels(data_ov003_0223cf70, tree_textures, tree_sapling_palettes, palettes) &&
        TownItemLoad_LoadTreeModels(data_ov003_0223cf70, tree_textures, tree_palettes, palettes) &&
        TownItemLoad_LoadDeadTreeModels(data_ov003_0223cf70, tree_textures, tree_sapling_palettes, palettes)) {
        trees_ok = 1;
    }
    TownItemLoad_FreeTreeFiles(data_ov003_0223cf70, tree_texture_files, tree_palette_files, tree_sapling_palette_files);

    TownItemLoad_ClearKindFiles(data_ov003_0223cf70, cedar_textures, cedar_texture_files, &cedar_palette, &cedar_palette_file,
                                &cedar_sapling_palette, &cedar_sapling_palette_file);
    if (TownItemLoad_LoadCedarTextures(data_ov003_0223cf70, cedar_textures, cedar_texture_files) &&
        TownItemLoad_LoadCedarPalettes(data_ov003_0223cf70, &cedar_palette, &cedar_palette_file, &cedar_sapling_palette,
                                       &cedar_sapling_palette_file) &&
        TownItemLoad_LoadCedarSaplingModel(data_ov003_0223cf70, cedar_textures, &cedar_sapling_palette, palettes) &&
        TownItemLoad_LoadCedarModels(data_ov003_0223cf70, cedar_textures, &cedar_palette, palettes) &&
        TownItemLoad_LoadDeadCedarModel(data_ov003_0223cf70, cedar_textures, &cedar_sapling_palette, palettes)) {
        cedars_ok = 1;
    }
    TownItemLoad_FreeCedarFiles(data_ov003_0223cf70, cedar_texture_files, &cedar_palette_file, &cedar_sapling_palette_file);

    TownItemLoad_ClearXCedarFiles(data_ov003_0223cf70, &x_texture, &x_texture_file, &x_palette, &x_palette_file);
    if (TownItemLoad_LoadXCedarTexture(data_ov003_0223cf70, &x_texture, &x_texture_file) &&
        TownItemLoad_LoadXCedarPalette(data_ov003_0223cf70, &x_palette, &x_palette_file) &&
        TownItemLoad_LoadXCedarModels(data_ov003_0223cf70, &x_texture, &x_palette)) {
        cedars_ok = 1;
    }
    TownItemLoad_FreeXCedarFiles(data_ov003_0223cf70, &x_texture_file, &x_palette_file);

    TownItemLoad_ClearKindFiles(data_ov003_0223cf70, palm_textures, palm_texture_files, &palm_palette, &palm_palette_file,
                                &palm_sapling_palette, &palm_sapling_palette_file);
    if (TownItemLoad_LoadPalmTextures(data_ov003_0223cf70, palm_textures, palm_texture_files) &&
        TownItemLoad_LoadCedarPalettes(data_ov003_0223cf70, &palm_palette, &palm_palette_file, &palm_sapling_palette,
                                       &palm_sapling_palette_file) &&
        TownItemLoad_LoadPalmSaplingModel(data_ov003_0223cf70, palm_textures, &palm_sapling_palette, palettes) &&
        TownItemLoad_LoadPalmModels(data_ov003_0223cf70, palm_textures, &palm_palette, palettes) &&
        TownItemLoad_LoadDeadPalmModel(data_ov003_0223cf70, palm_textures, &palm_sapling_palette, palettes)) {
        palms_ok = 1;
    }
    TownItemLoad_FreePalmFiles(data_ov003_0223cf70, palm_texture_files, &palm_palette_file, &palm_sapling_palette_file);

    return trees_ok && cedars_ok && palms_ok;
}
CLEAN_AS(func_ov003_02226604, TownItemLoad_LoadTrees)

/* func_ov003_0222681c: the palms' files freed from the scene's heap and forgotten: the six
 * texture files, then the two palette files. */
void TownItemLoad_FreePalmFiles(TileEventProcess *process, void **texture_files, void **palette_file,
                                void **sapling_palette_file)
{
    (void) process;
    Heap *heap = data_021fbe94;
    for (int i = 0; i < TOWN_ITEM_LOAD_STAGES; i++) {
        town_item_load_free(heap, &texture_files[i]);
    }
    town_item_load_free(heap, palette_file);
    town_item_load_free(heap, sapling_palette_file);
}
CLEAN_AS(func_ov003_0222681c, TownItemLoad_FreePalmFiles)

/* func_ov003_02226874: the cedar with lights' texture and palette files freed and forgotten. */
void TownItemLoad_FreeXCedarFiles(TileEventProcess *process, void **texture_file, void **palette_file)
{
    (void) process;
    Heap *heap = data_021fbe94;
    town_item_load_free(heap, texture_file);
    town_item_load_free(heap, palette_file);
}
CLEAN_AS(func_ov003_02226874, TownItemLoad_FreeXCedarFiles)

/* func_ov003_022268a8: the cedars' files freed from the scene's heap and forgotten: the six
 * texture files, then the two palette files. */
void TownItemLoad_FreeCedarFiles(TileEventProcess *process, void **texture_files, void **palette_file,
                                 void **sapling_palette_file)
{
    (void) process;
    Heap *heap = data_021fbe94;
    for (int i = 0; i < TOWN_ITEM_LOAD_STAGES; i++) {
        town_item_load_free(heap, &texture_files[i]);
    }
    town_item_load_free(heap, palette_file);
    town_item_load_free(heap, sapling_palette_file);
}
CLEAN_AS(func_ov003_022268a8, TownItemLoad_FreeCedarFiles)

/* func_ov003_02226900: the trees' files freed from the scene's heap and forgotten: the
 * eighteen texture files (six per look), then per variant its palette file and its sapling
 * palette file. */
void TownItemLoad_FreeTreeFiles(TileEventProcess *process, void **texture_files, void **palette_files,
                                void **sapling_palette_files)
{
    (void) process;
    Heap *heap = data_021fbe94;
    for (int i = 0; i < 3 * TOWN_ITEM_LOAD_STAGES; i++) {
        town_item_load_free(heap, &texture_files[i]);
    }
    for (int i = 0; i < TOWN_ITEM_LOAD_VARIANTS; i++) {
        town_item_load_free(heap, &palette_files[i]);
        town_item_load_free(heap, &sapling_palette_files[i]);
    }
}
CLEAN_AS(func_ov003_02226900, TownItemLoad_FreeTreeFiles)

/* func_ov003_02226978: the cedar with lights' texture, palette and their files cleared. */
void TownItemLoad_ClearXCedarFiles(TileEventProcess *process, void **texture, void **texture_file, void **palette,
                                   void **palette_file)
{
    (void) process;
    *texture = NULL;
    *texture_file = NULL;
    *palette = NULL;
    *palette_file = NULL;
}
CLEAN_AS(func_ov003_02226978, TownItemLoad_ClearXCedarFiles)

/* func_ov003_0222698c: a kind's six textures and texture files, its two palettes and their
 * files cleared (cedars, palms). */
void TownItemLoad_ClearKindFiles(TileEventProcess *process, void **textures, void **texture_files, void **palette,
                                 void **palette_file, void **sapling_palette, void **sapling_palette_file)
{
    (void) process;
    for (int i = 0; i < TOWN_ITEM_LOAD_STAGES; i++) {
        textures[i] = NULL;
        texture_files[i] = NULL;
    }
    *palette = NULL;
    *palette_file = NULL;
    *sapling_palette = NULL;
    *sapling_palette_file = NULL;
}
CLEAN_AS(func_ov003_0222698c, TownItemLoad_ClearKindFiles)

/* func_ov003_022269b0: the trees' eighteen textures and texture files, and per variant the two
 * palettes and their files cleared. */
void TownItemLoad_ClearTreeFiles(TileEventProcess *process, void **textures, void **texture_files, void **palettes,
                                 void **palette_files, void **sapling_palettes, void **sapling_palette_files)
{
    (void) process;
    for (int i = 0; i < 3 * TOWN_ITEM_LOAD_STAGES; i++) {
        textures[i] = NULL;
        texture_files[i] = NULL;
    }
    for (int i = 0; i < TOWN_ITEM_LOAD_VARIANTS; i++) {
        palettes[i] = NULL;
        palette_files[i] = NULL;
        sapling_palettes[i] = NULL;
        sapling_palette_files[i] = NULL;
    }
}
CLEAN_AS(func_ov003_022269b0, TownItemLoad_ClearTreeFiles)

/* func_ov003_022269f8: the dead palm (holder 5 at 0x11e8) with texture 5 and `palette`, one
 * material. */
int TownItemLoad_LoadDeadPalmModel(TileEventProcess *process, void **textures, void **palette, const u32 *palette_of_material)
{
    const char *path = TownItemLoad_PalmModelPath(process, 5);
    return ModelObject_LoadWithPalettes(&process->models_11e8[5], path, data_ov003_0223cf74, textures[5], *palette,
                                        palette_of_material, 1) != 0;
}
CLEAN_AS(func_ov003_022269f8, TownItemLoad_LoadDeadPalmModel)

/* func_ov003_02226a40: the dead cedar (holder 5 at 0xc6c) with texture 5 and `palette`, one
 * material. */
int TownItemLoad_LoadDeadCedarModel(TileEventProcess *process, void **textures, void **palette, const u32 *palette_of_material)
{
    const char *path = TownItemLoad_CedarModelPath(process, 5);
    return ModelObject_LoadWithPalettes(&process->models_0c6c[5], path, data_ov003_0223cf74, textures[5], *palette,
                                        palette_of_material, 1) != 0;
}
CLEAN_AS(func_ov003_02226a40, TownItemLoad_LoadDeadCedarModel)

/* func_ov003_02226a88: the dead tree of each variant (holder 5 of its six at 0x174), with
 * texture 5 of its look and its sapling palettes, one material. 0 at the first that fails. */
int TownItemLoad_LoadDeadTreeModels(TileEventProcess *process, void **textures, void **palettes,
                                    const u32 *palette_of_material)
{
    for (int variant = 0; variant < TOWN_ITEM_LOAD_VARIANTS; variant++) {
        int look = TownItemLoad_TreeLook(process, variant);
        const char *path = TownItemLoad_TreeModelPath(process, variant, 5);
        if (ModelObject_LoadWithPalettes(&process->models_0174[variant * TOWN_ITEM_LOAD_STAGES + 5], path, data_ov003_0223cf74,
                                         textures[look * TOWN_ITEM_LOAD_STAGES + 5], palettes[variant], palette_of_material,
                                         1) == 0) {
            return 0;
        }
    }
    return 1;
}
CLEAN_AS(func_ov003_02226a88, TownItemLoad_LoadDeadTreeModels)

/* func_ov003_02226b04: the palms of stages 1-4 (holders 1-4 at 0x11e8), then the palms'
 * growth models of stages 1-4, each with the texture of its stage and `palette`, two
 * materials. 0 at the first that fails. */
int TownItemLoad_LoadPalmModels(TileEventProcess *process, void **textures, void **palette, const u32 *palette_of_material)
{
    for (int stage = 1; stage <= 4; stage++) {
        const char *path = TownItemLoad_PalmModelPath(process, stage);
        if (ModelObject_LoadWithPalettes(&process->models_11e8[stage], path, data_ov003_0223cf74, textures[stage], *palette,
                                         palette_of_material, 2) == 0) {
            return 0;
        }
    }
    GrowthModels *growth = town_item_load_growth_models(process);
    for (int i = 0; i < 4; i++) {
        const char *path = TownItemLoad_PalmGrowthPath(process, i);
        if (ModelObject_LoadWithPalettes(town_item_load_growth(&growth->line_c8[i]), path, data_ov003_0223cf74,
                                         textures[i + 1], *palette, palette_of_material, 2) == 0) {
            return 0;
        }
    }
    return 1;
}
CLEAN_AS(func_ov003_02226b04, TownItemLoad_LoadPalmModels)

/* func_ov003_02226bb4: the cedar with lights' three frames (holders at 0x1014, code 0x6d), one
 * model file with `texture` and `palette`, frame i with palette i. 0 at the first that
 * fails. */
int TownItemLoad_LoadXCedarModels(TileEventProcess *process, void **texture, void **palette)
{
    for (u32 i = 0; i < 3; i++) {
        if (ModelObject_LoadWithPalettes(&process->models_1014[i], data_ov003_02239c8c, data_ov003_0223cf74, *texture,
                                         *palette, &i, 1) == 0) {
            return 0;
        }
    }
    return 1;
}
CLEAN_AS(func_ov003_02226bb4, TownItemLoad_LoadXCedarModels)

/* func_ov003_02226c14: the cedars of stages 1-4 (holders 1-4 at 0xc6c), then the cedars'
 * growth models of stages 1-4, each with the texture of its stage and `palette`, two
 * materials. 0 at the first that fails. */
int TownItemLoad_LoadCedarModels(TileEventProcess *process, void **textures, void **palette, const u32 *palette_of_material)
{
    for (int stage = 1; stage <= 4; stage++) {
        const char *path = TownItemLoad_CedarModelPath(process, stage);
        if (ModelObject_LoadWithPalettes(&process->models_0c6c[stage], path, data_ov003_0223cf74, textures[stage], *palette,
                                         palette_of_material, 2) == 0) {
            return 0;
        }
    }
    GrowthModels *growth = town_item_load_growth_models(process);
    for (int i = 0; i < 4; i++) {
        const char *path = TownItemLoad_CedarGrowthPath(process, i);
        if (ModelObject_LoadWithPalettes(town_item_load_growth(&growth->line_5d[i]), path, data_ov003_0223cf74,
                                         textures[i + 1], *palette, palette_of_material, 2) == 0) {
            return 0;
        }
    }
    return 1;
}
CLEAN_AS(func_ov003_02226c14, TownItemLoad_LoadCedarModels)

/* func_ov003_02226cc4: per variant the trees of stages 1-4 (holders 1-4 of its six at 0x174),
 * then per variant its growth models of stages 1-4, each with the texture of its look and
 * stage and the variant's palettes, two materials. 0 at the first that fails. */
int TownItemLoad_LoadTreeModels(TileEventProcess *process, void **textures, void **palettes, const u32 *palette_of_material)
{
    for (int variant = 0; variant < TOWN_ITEM_LOAD_VARIANTS; variant++) {
        void **look_textures = &textures[TownItemLoad_TreeLook(process, variant) * TOWN_ITEM_LOAD_STAGES];
        ModelObject *models = &process->models_0174[variant * TOWN_ITEM_LOAD_STAGES];
        for (int stage = 1; stage <= 4; stage++) {
            const char *path = TownItemLoad_TreeModelPath(process, variant, stage);
            if (ModelObject_LoadWithPalettes(&models[stage], path, data_ov003_0223cf74, look_textures[stage],
                                             palettes[variant], palette_of_material, 2) == 0) {
                return 0;
            }
        }
    }
    GrowthModels *growth = town_item_load_growth_models(process);
    for (int variant = 0; variant < TOWN_ITEM_LOAD_VARIANTS; variant++) {
        void **look_textures = &textures[TownItemLoad_TreeLook(process, variant) * TOWN_ITEM_LOAD_STAGES];
        for (int i = 0; i < 4; i++) {
            const char *path = TownItemLoad_TreeGrowthPath(process, variant, i);
            if (ModelObject_LoadWithPalettes(town_item_load_growth(&growth->sets[variant][i]), path, data_ov003_0223cf74,
                                             look_textures[i + 1], palettes[variant], palette_of_material, 2) == 0) {
                return 0;
            }
        }
    }
    return 1;
}
CLEAN_AS(func_ov003_02226cc4, TownItemLoad_LoadTreeModels)

/* func_ov003_02226de8: the palm sapling (holder 0 at 0x11e8) with texture 0 and `palette`, one
 * material. */
int TownItemLoad_LoadPalmSaplingModel(TileEventProcess *process, void **textures, void **palette,
                                      const u32 *palette_of_material)
{
    const char *path = TownItemLoad_PalmModelPath(process, 0);
    return ModelObject_LoadWithPalettes(&process->models_11e8[0], path, data_ov003_0223cf74, textures[0], *palette,
                                        palette_of_material, 1) != 0;
}
CLEAN_AS(func_ov003_02226de8, TownItemLoad_LoadPalmSaplingModel)

/* func_ov003_02226e30: the cedar sapling (holder 0 at 0xc6c) with texture 0 and `palette`, one
 * material. */
int TownItemLoad_LoadCedarSaplingModel(TileEventProcess *process, void **textures, void **palette,
                                       const u32 *palette_of_material)
{
    const char *path = TownItemLoad_CedarModelPath(process, 0);
    return ModelObject_LoadWithPalettes(&process->models_0c6c[0], path, data_ov003_0223cf74, textures[0], *palette,
                                        palette_of_material, 1) != 0;
}
CLEAN_AS(func_ov003_02226e30, TownItemLoad_LoadCedarSaplingModel)

/* func_ov003_02226e78: the sapling of each variant (holder 0 of its six at 0x174), with texture
 * 0 of its look and its sapling palettes, one material. 0 at the first that fails. */
int TownItemLoad_LoadTreeSaplingModels(TileEventProcess *process, void **textures, void **palettes,
                                       const u32 *palette_of_material)
{
    for (int variant = 0; variant < TOWN_ITEM_LOAD_VARIANTS; variant++) {
        int look = TownItemLoad_TreeLook(process, variant);
        const char *path = TownItemLoad_TreeModelPath(process, variant, 0);
        if (ModelObject_LoadWithPalettes(&process->models_0174[variant * TOWN_ITEM_LOAD_STAGES], path, data_ov003_0223cf74,
                                         textures[look * TOWN_ITEM_LOAD_STAGES], palettes[variant], palette_of_material,
                                         1) == 0) {
            return 0;
        }
    }
    return 1;
}
CLEAN_AS(func_ov003_02226e78, TownItemLoad_LoadTreeSaplingModels)

/* func_ov003_02226ef4: the cedar with lights' palette file read (func_ov003_022272c0). */
int TownItemLoad_LoadXCedarPalette(TileEventProcess *process, void **palette, void **file)
{
    return TownItemLoad_LoadPaletteFiles(process, palette, file, &data_ov003_02239c7c, 1) != 0;
}
CLEAN_AS(func_ov003_02226ef4, TownItemLoad_LoadXCedarPalette)

/* func_ov003_02226f18: the cedars' palette file (grown), then their sapling palette file read
 * (func_ov003_022272c0); 0 when one fails. */
int TownItemLoad_LoadCedarPalettes(TileEventProcess *process, void **palette, void **palette_file, void **sapling_palette,
                                   void **sapling_palette_file)
{
    if (TownItemLoad_LoadPaletteFiles(process, palette, palette_file, &data_ov003_02239c78, 1) == 0) {
        return 0;
    }
    return TownItemLoad_LoadPaletteFiles(process, sapling_palette, sapling_palette_file, &data_ov003_02239c84, 1) != 0;
}
CLEAN_AS(func_ov003_02226f18, TownItemLoad_LoadCedarPalettes)

/* func_ov003_02226f5c: the trees' three palette files (grown), then their three sapling
 * palette files read (func_ov003_022272c0); 0 when one fails. */
int TownItemLoad_LoadTreePalettes(TileEventProcess *process, void **palettes, void **palette_files, void **sapling_palettes,
                                  void **sapling_palette_files)
{
    if (TownItemLoad_LoadPaletteFiles(process, palettes, palette_files, data_ov003_02239f80, TOWN_ITEM_LOAD_VARIANTS) == 0) {
        return 0;
    }
    return TownItemLoad_LoadPaletteFiles(process, sapling_palettes, sapling_palette_files, data_ov003_02239f08,
                                         TOWN_ITEM_LOAD_VARIANTS) != 0;
}
CLEAN_AS(func_ov003_02226f5c, TownItemLoad_LoadTreePalettes)

/* func_ov003_02226fa0: the palms' six texture files of the fruit trees' look read
 * (func_ov003_02227324). */
int TownItemLoad_LoadPalmTextures(TileEventProcess *process, void **textures, void **files)
{
    int look = TownItemLoad_TreeLook(process, 2);
    return TownItemLoad_LoadTextureFiles(process, textures, files, data_ov003_02239f74[look], TOWN_ITEM_LOAD_STAGES) != 0;
}
CLEAN_AS(func_ov003_02226fa0, TownItemLoad_LoadPalmTextures)

/* func_ov003_02226fdc: the cedar with lights' texture file read (func_ov003_02227324). */
int TownItemLoad_LoadXCedarTexture(TileEventProcess *process, void **texture, void **file)
{
    return TownItemLoad_LoadTextureFiles(process, texture, file, &data_ov003_02239c80, 1) != 0;
}
CLEAN_AS(func_ov003_02226fdc, TownItemLoad_LoadXCedarTexture)

/* func_ov003_02227000: the cedars' six texture files of the fruit trees' look read
 * (func_ov003_02227324). */
int TownItemLoad_LoadCedarTextures(TileEventProcess *process, void **textures, void **files)
{
    int look = TownItemLoad_TreeLook(process, 2);
    return TownItemLoad_LoadTextureFiles(process, textures, files, data_ov003_02239f14[look], TOWN_ITEM_LOAD_STAGES) != 0;
}
CLEAN_AS(func_ov003_02227000, TownItemLoad_LoadCedarTextures)

/* func_ov003_0222703c: the six texture files of each look a variant has read once
 * (func_ov003_02227324), into the look's six textures and files; 0 when one fails. */
int TownItemLoad_LoadTreeTextures(TileEventProcess *process, void **textures, void **files)
{
    int done[3] = {0, 0, 0};
    for (int variant = 0; variant < TOWN_ITEM_LOAD_VARIANTS; variant++) {
        int look = TownItemLoad_TreeLook(process, variant);
        if (done[look] == 0) {
            if (!TownItemLoad_LoadTextureFiles(process, &textures[look * TOWN_ITEM_LOAD_STAGES],
                                               &files[look * TOWN_ITEM_LOAD_STAGES],
                                               TownItemLoad_TreeTexturePaths(process, look), TOWN_ITEM_LOAD_STAGES)) {
                return 0;
            }
            done[look] = 1;
        }
    }
    return 1;
}
CLEAN_AS(func_ov003_0222703c, TownItemLoad_LoadTreeTextures)

/* func_ov003_022270ac: the six texture file paths of tree look `look`. */
const char *const *TownItemLoad_TreeTexturePaths(TileEventProcess *process, int look)
{
    (void) process;
    return data_ov003_02239f44[look];
}
CLEAN_AS(func_ov003_022270ac, TownItemLoad_TreeTexturePaths)

/* func_ov003_022270b8: the palm growth model file of stage `stage` + 1, in the fruit trees'
 * look. */
const char *TownItemLoad_PalmGrowthPath(TileEventProcess *process, int stage)
{
    return data_ov003_02239efc[TownItemLoad_TreeLook(process, 2)][stage];
}
CLEAN_AS(func_ov003_022270b8, TownItemLoad_PalmGrowthPath)

/* func_ov003_022270d8: the palm model file of `stage` (0 sapling, 1-4, 5 dead), in the fruit
 * trees' look. */
const char *TownItemLoad_PalmModelPath(TileEventProcess *process, int stage)
{
    return data_ov003_02239ee4[TownItemLoad_TreeLook(process, 2)][stage];
}
CLEAN_AS(func_ov003_022270d8, TownItemLoad_PalmModelPath)

/* func_ov003_022270f8: the cedar growth model file of stage `stage` + 1, in the fruit trees'
 * look. */
const char *TownItemLoad_CedarGrowthPath(TileEventProcess *process, int stage)
{
    return data_ov003_02239f38[TownItemLoad_TreeLook(process, 2)][stage];
}
CLEAN_AS(func_ov003_022270f8, TownItemLoad_CedarGrowthPath)

/* func_ov003_02227118: the cedar model file of `stage` (0 sapling, 1-4, 5 dead), in the fruit
 * trees' look. */
const char *TownItemLoad_CedarModelPath(TileEventProcess *process, int stage)
{
    return data_ov003_02239f50[TownItemLoad_TreeLook(process, 2)][stage];
}
CLEAN_AS(func_ov003_02227118, TownItemLoad_CedarModelPath)

/* func_ov003_02227138: the tree growth model file of stage `stage` + 1, in the look of
 * `variant`. */
const char *TownItemLoad_TreeGrowthPath(TileEventProcess *process, int variant, int stage)
{
    return data_ov003_02239f8c[TownItemLoad_TreeLook(process, variant)][stage];
}
CLEAN_AS(func_ov003_02227138, TownItemLoad_TreeGrowthPath)

/* func_ov003_02227154: the tree model file of `stage` (0 sapling, 1-4, 5 dead), in the look of
 * `variant`. */
const char *TownItemLoad_TreeModelPath(TileEventProcess *process, int variant, int stage)
{
    return data_ov003_02239f20[TownItemLoad_TreeLook(process, variant)][stage];
}
CLEAN_AS(func_ov003_02227154, TownItemLoad_TreeModelPath)

/* func_ov003_02227170: the look of tree variant `variant` in the town's period. */
int TownItemLoad_TreeLook(TileEventProcess *process, int variant)
{
    (void) process;
    return data_ov003_02236e64[TownRecord_Period()][variant];
}
CLEAN_AS(func_ov003_02227170, TownItemLoad_TreeLook)

/* func_ov003_02227190: the stamps loaded into the current process (func_ov003_022271a0). */
int TownItemLoad_LoadStamps(void)
{
    return TownItemLoad_LoadStampModels(data_ov003_0223cf70);
}
CLEAN_AS(func_ov003_02227190, TownItemLoad_LoadStamps)

/* The stumps' model set file ('/fg/tree/stamp/stamp.nsbmd') and the names of its twelve models
 * (tree, cedar and palm stumps, four each); the stones' model set files by look (one 'w', two
 * 's') and the names of each one's five models; the icons' model set file. */
#define TOWN_ITEM_LOAD_STAMPS 12
#define TOWN_ITEM_LOAD_STONES 5
#define TOWN_ITEM_LOAD_ICONS 0x49
extern const char data_ov003_0223bd74[];
extern const char *const data_ov003_0223bc44[TOWN_ITEM_LOAD_STAMPS];
extern const char *const data_ov003_02239ef0[3];
extern const char *const *const data_ov003_02239f2c[3];
extern const char data_ov003_0223bd90[];
/* A texture file's texture block (NNS_G3dGetTex). */
extern void *func_021077e8(void *file);

/* func_ov003_022271a0: model set 3 loaded from the stumps' file into the first heap, and the
 * twelve pointers at 0x4978 set to its models by name; 0 when the set could not be loaded. */
int TownItemLoad_LoadStampModels(TileEventProcess *process)
{
    if (ModelSet_Load(&process->sets[3], data_ov003_0223bd74, data_ov003_0223cf74) == 0) {
        return 0;
    }
    ModelObject **stamps = (ModelObject **) (void *) process->unk_4978;
    for (int i = 0; i < TOWN_ITEM_LOAD_STAMPS; i++) {
        stamps[i] = ModelSet_Find(&process->sets[3], data_ov003_0223bc44[i]);
    }
    return 1;
}
CLEAN_AS(func_ov003_022271a0, TownItemLoad_LoadStampModels)

/* func_ov003_022271f8: the stones loaded into the current process. */
int TownItemLoad_LoadStones(void)
{
    return TownItemLoad_LoadStoneModels(data_ov003_0223cf70);
}
CLEAN_AS(func_ov003_022271f8, TownItemLoad_LoadStones)

/* func_ov003_02227208: model set 2 loaded from the stones' file of the look of variant 2 into
 * the second heap, and the five pointers at 0x46f4 set to its models by name; 0 when the set
 * could not be loaded. */
int TownItemLoad_LoadStoneModels(TileEventProcess *process)
{
    int look = TownItemLoad_TreeLook(process, 2);
    if (ModelSet_Load(&process->sets[2], data_ov003_02239ef0[look], data_ov003_0223cf78) == 0) {
        return 0;
    }
    const char *const *names = data_ov003_02239f2c[look];
    ModelObject **stones = (ModelObject **) (void *) process->unk_46f4;
    for (int i = 0; i < TOWN_ITEM_LOAD_STONES; i++) {
        stones[i] = ModelSet_Find(&process->sets[2], names[i]);
    }
    return 1;
}
CLEAN_AS(func_ov003_02227208, TownItemLoad_LoadStoneModels)

/* func_ov003_0222726c: model set 0 loaded from the icons' file into the first heap, and the
 * item holders' 0x49 pointers at 0x50 set to its models by the name of each look outdoors
 * (ItemInfo_LookModelName); 0 when the set could not be loaded. */
int TownItemLoad_LoadIcons(TileEventProcess *process)
{
    if (ModelSet_Load(&process->sets[0], data_ov003_0223bd90, data_ov003_0223cf74) == 0) {
        return 0;
    }
    ModelObject **holders = (ModelObject **) (void *) process->unk_0050;
    for (int i = 0; i < TOWN_ITEM_LOAD_ICONS; i++) {
        holders[i] = ModelSet_Find(&process->sets[0], ItemInfo_LookModelName(i, 1));
    }
    return 1;
}
CLEAN_AS(func_ov003_0222726c, TownItemLoad_LoadIcons)

/* func_ov003_022272c0: `count` texture files of `paths` read into the scene's heap (`files`),
 * their texture blocks (`resources`) with the palettes placed in VRAM; 0 when one could not be
 * read (those before it stay). */
int TownItemLoad_LoadPaletteFiles(TileEventProcess *process, void **resources, void **files, const char *const *paths,
                                  int count)
{
    (void) process;
    for (int i = 0; i < count; i++) {
        files[i] = RomFile_Load(paths[i], data_021fbe94, -4, NULL);
        if (files[i] == NULL) {
            return 0;
        }
        resources[i] = func_021077e8(files[i]);
        VramRegion_LoadPalettes(resources[i], NULL);
    }
    return 1;
}
CLEAN_AS(func_ov003_022272c0, TownItemLoad_LoadPaletteFiles)

/* func_ov003_02227324: the same with the textures (not the palettes) placed in VRAM; a NULL
 * path gives a NULL resource and leaves its file alone. */
int TownItemLoad_LoadTextureFiles(TileEventProcess *process, void **resources, void **files, const char *const *paths,
                                  int count)
{
    (void) process;
    for (int i = 0; i < count; i++) {
        if (paths[i] == NULL) {
            resources[i] = NULL;
            continue;
        }
        files[i] = RomFile_Load(paths[i], data_021fbe94, -4, NULL);
        if (files[i] == NULL) {
            return 0;
        }
        resources[i] = func_021077e8(files[i]);
        VramRegion_LoadImages(resources[i], NULL);
    }
    return 1;
}
CLEAN_AS(func_ov003_02227324, TownItemLoad_LoadTextureFiles)
