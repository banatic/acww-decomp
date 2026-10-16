/* What the designs (design.h) are built from and shown with: the files of default designs, the
 * 16 palettes, the file of 50 designs' information, and the textures of the players' and the
 * shop's designs, all held by one object (DesignManager, data_021d0504).
 *
 * The textures: for each design a copy of the model of item 0x11a8 whose image and palette are
 * replaced by the design's (func_0203cff8), and a texture handle taken from that model
 * (func_02056160). Players' textures exist for 4 players by 8 designs, the shop's for its 8
 * designs in scene 10 only. */
#ifndef CLEAN_MAIN_DESIGN_ASSETS_H
#define CLEAN_MAIN_DESIGN_ASSETS_H

#include "design.h"
#include "types.h"

#define DESIGN_PALETTES 16
#define DESIGN_PALETTE_SIZE 0x20 /* 16 colours */
#define DESIGN_PLAYERS 4

/* The palettes, read from one file; each points into it. */
typedef struct DesignPalettes {
    u8 *file;
    u16 *palettes[DESIGN_PALETTES];
} DesignPalettes;

/* The object that holds the palettes and owns the textures (whose state is in globals). */
typedef struct DesignManager {
    u8 unk_00[4];
    DesignPalettes palettes;
} DesignManager;

/* A file of fixed-size records (func_0206e890 opens one; 0x1c bytes). */
typedef struct RecordFile {
    u32 words[7];
} RecordFile;

/* A copy of the design item's model (0x2c4 bytes) and what sends a texture from it (0x38). */
typedef struct DesignModel {
    u32 words[0xb1];
} DesignModel;

typedef struct DesignTexture {
    u32 words[0xe];
} DesignTexture;

int DesignTextures_UpdateShop(unsigned int index);
int DesignTextures_UpdatePlayer(int player, int index);
int DesignSampleImage_ToBitmap(u32 *chars, u32 *pixels);
int DesignSampleImage_Load(void *image, int sample);
void DesignSampleImage_Construct(void);
int DesignBlankImage_ToBitmap(u32 *chars, u32 *pixels);
void DesignBlankImage_Load(void *image);
void DesignBlankImage_Construct(void);
int DesignBuSheet_ToBitmap(u32 *sheet, u32 *pixels, int slot);
void DesignBuSheet_Load(unsigned char *sheet);
void DesignBuSheet_Construct(void);
int DesignMySheet_ToBitmap(u32 *sheet, u32 *pixels, int slot);
void DesignMySheet_Load(void *sheet);
void DesignMySheet_Construct(void);
int DesignArchive_Get(void);
int DesignArchive_ReadInfo(RecordFile *archive, DesignInfo *info, int entry);
void DesignArchive_Close(RecordFile *archive);
void DesignArchive_Open(RecordFile *archive);
int DesignArchive_Destruct(RecordFile *archive);
int DesignArchive_Construct(RecordFile *archive);
int DesignTextures_Shop(DesignManager *manager, unsigned int index);
int DesignTextures_Player(DesignManager *manager, int player, int index);
void DesignTextures_Release(DesignManager *manager);
void DesignTextures_Build(DesignManager *manager);
void DesignTextures_Clear(DesignManager *manager);
void DesignTextures_Destruct(DesignManager *manager);
int DesignTextures_Construct(DesignManager *manager);
unsigned int DesignPalettes_Get(DesignPalettes *set, unsigned int index);
void DesignPalettes_Free(DesignPalettes *set);
void DesignPalettes_Load(DesignPalettes *set);
void DesignPalettes_Destruct(DesignPalettes *set);
DesignPalettes *DesignPalettes_Construct(DesignPalettes *set);
void DesignPalettes_Reset(DesignPalettes *set);
int DesignManager_Get(void);
unsigned int DesignManager_Palette(DesignManager *manager, unsigned int index);
int DesignManager_ShopTexture(DesignManager *manager, unsigned int index);
int DesignManager_PlayerTexture(DesignManager *manager, int player, int index);
void DesignManager_Shutdown(DesignManager *manager);
void DesignManager_Startup(DesignManager *manager);

#endif
