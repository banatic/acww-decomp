/* Two sets of files overlay 3 loads for the houses of the town, kept in its globals (made by
 * __sinit_ov003_02237a44, loaded and released with the field by func_ov003_022207e0 and
 * func_ov003_0222079c):
 *
 *   - data_ov003_0223ce58 (HousePalette): the palettes "/str/house_pl/house_pl_<letter>.nsbtx"
 *     (the letter overlay 3 picks, func_ov003_022203dc), loaded into VRAM and kept as a copy in
 *     main's heap; overlay 9's scene actors bind their models' palettes to it;
 *   - data_ov003_0223ce80 (HouseXFiles, villager_house.h's X files): from "/str/npcHsX.arc",
 *     loaded only while the town takes part in event 0x11, five models "obj_x_house<kind>",
 *     their texture "obj_x_house0" and the texture pattern animation "obj_x_deco". */
#ifndef CLEAN_OV003_HOUSE_FILES_H
#define CLEAN_OV003_HOUSE_FILES_H

#include "types.h"

#define HOUSE_X_FILES_MODELS 5

typedef struct HousePalette {
    void *texture; /* the copy of the palettes' texture resource in main's heap, NULL before */
} HousePalette;

typedef struct HouseXFiles {
    void *texture;                    /* 0x00: "obj_x_house0.nsbtx", its texture resource */
    u8 *models[HOUSE_X_FILES_MODELS]; /* 0x04: "obj_x_house<kind>.nsbmd", each first model */
    void *deco;                       /* 0x18: "obj_x_deco.nsbtp", its first animation */
    u8 loaded;                        /* 0x1c: the archive was loaded */
    u8 pad_1d[3];
} HouseXFiles;

int HousePalette_Texture(HousePalette *palette);
void HousePalette_Release(HousePalette *palette);
int HousePalette_Load(HousePalette *palette);
void HousePalette_Destruct(void);
void HousePalette_Construct(HousePalette *palette);
int HouseXFiles_Loaded(HouseXFiles *files);
int HouseXFiles_Deco(HouseXFiles *files);
void *HouseXFiles_Model(HouseXFiles *files, unsigned int kind);
int HouseXFiles_Texture(HouseXFiles *files);
void HouseXFiles_Release(HouseXFiles *files);
int HouseXFiles_Load(HouseXFiles *files);
void HouseXFiles_Clear(HouseXFiles *files);
void HouseXFiles_Destruct(void);

/* The third set, data_ov003_0223cea0 (HouseTextures): for each of the four house looks of the
 * town (main/house_looks.h) the house's and the light's textures from "/str/npcHsTex/", copied
 * into main's heap, and the houses' two joint animations "/str/obj_house_i.nsbca" and
 * "/str/obj_house_o.nsbca" (villager_house.h's textures). */
#define HOUSE_TEXTURES_LOOKS 4

typedef struct HouseTextures {
    void *house[HOUSE_TEXTURES_LOOKS]; /* 0x00: "house_<set><variant><season>.nsbtx", texture resources */
    void *light[HOUSE_TEXTURES_LOOKS]; /* 0x10: "light_<set><variant>.nsbtx", texture resources */
    void *anim_i;                      /* 0x20: "obj_house_i.nsbca", its first joint animation */
    void *anim_o;                      /* 0x24: "obj_house_o.nsbca", its first joint animation */
} HouseTextures;

HouseXFiles *HouseXFiles_Construct(HouseXFiles *files);
void *HouseTextures_AnimO(HouseTextures *textures);
void *HouseTextures_AnimI(HouseTextures *textures);
void *HouseTextures_Light(HouseTextures *textures, int look);
void *HouseTextures_House(HouseTextures *textures, int look);
void HouseTextures_Clear(HouseTextures *textures);
int HouseTextures_Load(HouseTextures *textures);
void HouseTextures_Destruct(void);
HouseTextures *HouseTextures_Construct(HouseTextures *textures);
HouseXFiles *HouseFiles_XFiles(void);
HouseTextures *HouseFiles_Textures(void);
HousePalette *HouseFiles_Palette(void);
signed char HouseFiles_SeasonLetter(void);

#endif
