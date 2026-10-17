/* Overlay 3's loading of the models the tile events' process (tile_event.h, data_ov003_0223cf70)
 * draws the town's map codes with (town_item_models.h), and the process's INIT and per-frame
 * work (vtable 0x0223bc7c slots 0 and 6).
 *
 * TownItemLoad_InitProcess makes the process's two heaps (one over the overlay's block at
 * data_ov003_0223dcb4, one of 0x8c00 bytes from the scene's heap), loads the icon set and the
 * item holders (func_ov003_0222726c), then runs the nine loaders of data_ov003_0223b8a4:
 *
 *   - trees (TownItemLoad_LoadTrees): the plain trees (two variants, by the tile's parity) and
 *     the fruit trees at 0x174, cedars at 0xc6c, the cedar with lights at 0x1014 (code 0x6d's
 *     three frames), palms at 0x11e8, six holders a kind (sapling, stages 1-4, dead), and the
 *     growth models' animated trees (growth_model.h);
 *   - flowers: the four families at 0x1590, the two flowers at 0x2df0 and the dandelions of
 *     model set 1 (pointers at 0x3060);
 *   - grass, holes, cracks, func_ov003_022271f8, stamps (func_ov003_022271a0), red turnips and
 *     the players' designs on the ground (0x3068).
 *
 * A model is read from a model file (.nsbmd) with the textures and palettes of a texture file
 * (.nsbtx) read and placed in VRAM for it; the texture files are freed again once the models
 * hold them. The trees' and the flowers' palettes are chosen by the town's period of the year
 * (TownRecord_Period, 0-22), and each tree variant has a look by period (TownItemLoad_TreeLook):
 * 0, 1 or 2, for the files named 'w', 'f' and 's'. */
#ifndef CLEAN_OV003_TOWN_ITEM_LOAD_H
#define CLEAN_OV003_TOWN_ITEM_LOAD_H

#include "main/model_object.h"
#include "tile_event.h"
#include "types.h"

/* The holders a tree kind has: the sapling, stages 1-4 and the dead tree. */
#define TOWN_ITEM_LOAD_STAGES 6
/* The tree variants: two plain (by the tile's parity) and the fruit trees. */
#define TOWN_ITEM_LOAD_VARIANTS 3

int TownItemLoad_StepProcess(TileEventProcess *process);
int TownItemLoad_InitProcess(TileEventProcess *process);
int TownItemLoad_RunLoaders(TileEventProcess *process);
int TownItemLoad_LoadDesigns(void);
int TownItemLoad_LoadDesignModels(TileEventProcess *process);
int TownItemLoad_LoadTurnips(void);
int TownItemLoad_LoadTurnipModels(void);
int TownItemLoad_LoadCracks(void);
int TownItemLoad_LoadCrackModels(TileEventProcess *process, void *palettes);
int TownItemLoad_LoadCrackPalettes(TileEventProcess *process, void **palettes, void **file);
int TownItemLoad_LoadHoles(void);
int TownItemLoad_LoadHoleModels(TileEventProcess *process, void *palettes);
int TownItemLoad_LoadHolePalettes(TileEventProcess *process, void **palettes, void **file);
int TownItemLoad_HolePalette(TileEventProcess *process);
int TownItemLoad_LoadGrass(void);
int TownItemLoad_LoadGrassModels(TileEventProcess *process, void *palettes);
int TownItemLoad_LoadGrassPalettes(TileEventProcess *process, void **palettes, void **file);
int TownItemLoad_LoadFlowers(void);
void TownItemLoad_FreeFlowerFiles(TileEventProcess *process, void **family_texture_files, void **family_palette_files,
                                  void **pair_texture_files, void **pair_palette_files);
int TownItemLoad_LoadDandelions(TileEventProcess *process);
int TownItemLoad_LoadFlowerPairModels(TileEventProcess *process, void **textures, void **palettes);
int TownItemLoad_LoadFlowerPairPalettes(TileEventProcess *process, void **palettes, void **files);
int TownItemLoad_LoadFlowerPairTextures(TileEventProcess *process, void **textures, void **files);
int TownItemLoad_LoadFlowerFamilyModels(TileEventProcess *process, void **textures, void **palettes);
int TownItemLoad_LoadFlowerFamilyPalettes(TileEventProcess *process, void **palettes, void **files);
int TownItemLoad_LoadFlowerFamilyTextures(TileEventProcess *process, void **textures, void **files);
int TownItemLoad_LoadTrees(void);
void TownItemLoad_FreePalmFiles(TileEventProcess *process, void **texture_files, void **palette_file,
                                void **sapling_palette_file);
void TownItemLoad_FreeXCedarFiles(TileEventProcess *process, void **texture_file, void **palette_file);
void TownItemLoad_FreeCedarFiles(TileEventProcess *process, void **texture_files, void **palette_file,
                                 void **sapling_palette_file);
void TownItemLoad_FreeTreeFiles(TileEventProcess *process, void **texture_files, void **palette_files,
                                void **sapling_palette_files);
void TownItemLoad_ClearXCedarFiles(TileEventProcess *process, void **texture, void **texture_file, void **palette,
                                   void **palette_file);
void TownItemLoad_ClearKindFiles(TileEventProcess *process, void **textures, void **texture_files, void **palette,
                                 void **palette_file, void **sapling_palette, void **sapling_palette_file);
void TownItemLoad_ClearTreeFiles(TileEventProcess *process, void **textures, void **texture_files, void **palettes,
                                 void **palette_files, void **sapling_palettes, void **sapling_palette_files);
int TownItemLoad_LoadDeadPalmModel(TileEventProcess *process, void **textures, void **palette, const u32 *palette_of_material);
int TownItemLoad_LoadDeadCedarModel(TileEventProcess *process, void **textures, void **palette,
                                    const u32 *palette_of_material);
int TownItemLoad_LoadDeadTreeModels(TileEventProcess *process, void **textures, void **palettes,
                                    const u32 *palette_of_material);
int TownItemLoad_LoadPalmModels(TileEventProcess *process, void **textures, void **palette, const u32 *palette_of_material);
int TownItemLoad_LoadXCedarModels(TileEventProcess *process, void **texture, void **palette);
int TownItemLoad_LoadCedarModels(TileEventProcess *process, void **textures, void **palette, const u32 *palette_of_material);
int TownItemLoad_LoadTreeModels(TileEventProcess *process, void **textures, void **palettes, const u32 *palette_of_material);
int TownItemLoad_LoadPalmSaplingModel(TileEventProcess *process, void **textures, void **palette,
                                      const u32 *palette_of_material);
int TownItemLoad_LoadCedarSaplingModel(TileEventProcess *process, void **textures, void **palette,
                                       const u32 *palette_of_material);
int TownItemLoad_LoadTreeSaplingModels(TileEventProcess *process, void **textures, void **palettes,
                                       const u32 *palette_of_material);
int TownItemLoad_LoadXCedarPalette(TileEventProcess *process, void **palette, void **file);
int TownItemLoad_LoadCedarPalettes(TileEventProcess *process, void **palette, void **palette_file, void **sapling_palette,
                                   void **sapling_palette_file);
int TownItemLoad_LoadTreePalettes(TileEventProcess *process, void **palettes, void **palette_files, void **sapling_palettes,
                                  void **sapling_palette_files);
int TownItemLoad_LoadPalmTextures(TileEventProcess *process, void **textures, void **files);
int TownItemLoad_LoadXCedarTexture(TileEventProcess *process, void **texture, void **file);
int TownItemLoad_LoadCedarTextures(TileEventProcess *process, void **textures, void **files);
int TownItemLoad_LoadTreeTextures(TileEventProcess *process, void **textures, void **files);
const char *const *TownItemLoad_TreeTexturePaths(TileEventProcess *process, int look);
const char *TownItemLoad_PalmGrowthPath(TileEventProcess *process, int stage);
const char *TownItemLoad_PalmModelPath(TileEventProcess *process, int stage);
const char *TownItemLoad_CedarGrowthPath(TileEventProcess *process, int stage);
const char *TownItemLoad_CedarModelPath(TileEventProcess *process, int stage);
const char *TownItemLoad_TreeGrowthPath(TileEventProcess *process, int variant, int stage);
const char *TownItemLoad_TreeModelPath(TileEventProcess *process, int variant, int stage);
int TownItemLoad_TreeLook(TileEventProcess *process, int variant);
int TownItemLoad_LoadStamps(void);

#endif
