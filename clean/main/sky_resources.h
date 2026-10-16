/* What the sky's objects draw with (sky_objects.h): the files their cells and palettes are read
 * from (SkyFiles, at 0x1b6c of the objects), the five slots of OBJ VRAM those cells are loaded
 * into (SkyObjectSlot, sky.h) and the OBJ palettes 12 to 15 they use (SkyPalettes, at 0x2eb8).
 *
 * Each resource (data_020d2bac, 16 bytes; SkyResource in sky_objects.h is the same table from
 * its slot on) names a file, the tiles of its top four rows and of its bottom four rows in it,
 * the slot it needs, and a palette of the palette files with the OBJ palette it goes to.
 *
 * - The cells: SkyFiles_ReadCells reads a resource's eight rows of tiles into the files' cell
 *   buffer, as many tiles per row as its slot's layout (data_020d26a0) says, and
 *   SkySlot_LoadCells copies them to the slot's place in OBJ VRAM (rows of 32 tiles from tile
 *   0x94); with the sky on the sub screen, to the sub engine's OBJ VRAM too.
 * - The palettes: both palette files are read once (SkyFiles_ReadPalettes). A resource's
 *   palette is loaded (SkyPalettes_Load) unless the OBJ palette already holds it
 *   (SkyPalettes_IsLoaded). Up to 15 colours can be overridden (SkyPalettes_SetOverride); an
 *   OBJ palette loaded with an override is not remembered, so it is loaded again each time. */
#ifndef CLEAN_MAIN_SKY_RESOURCES_H
#define CLEAN_MAIN_SKY_RESOURCES_H

#include "sky.h"
#include "types.h"

#define SKY_RESOURCE_NO_TILE 0xffff   /* SkyResourceFile.top_tile, bottom_tile: no such rows */
#define SKY_PALETTES_FIRST 12         /* the first OBJ palette the objects use */
#define SKY_PALETTES_OVERRIDES 15     /* colours that can be overridden */
#define SKY_PALETTES_VARIANTS 5       /* SkyPalettes.variant: 0 to 4 */
#define SKY_RESOURCE_VARIANT_FIRST 31 /* resources 31 and 32 use the palette plus the variant */
#define SKY_FILES_ROWS 8              /* rows of a resource's cells: four top, four bottom */
#define SKY_FILES_ROW_TILES 12        /* tiles of a row in the cell buffer */
#define SKY_FILES_FILE_ROW_TILES 32   /* tiles of a row in a cell file and in OBJ VRAM */
#define SKY_FILES_TILE_BYTES 32
#define SKY_FILES_PALETTES 24 /* a_sky_obj_ncl.bin's 14, then a_sky_moon_obj_ncl.bin's 10 */
#define SKY_FILES_MAGIC 0x12345678

/* An entry of data_020d2bac: a resource of the objects. */
typedef struct SkyResourceFile {
    u32 file;        /* 0x00: in data_020d22d8: 0 a_sky_obj_ncg.bin, 1 a_sky_fly_obj_ncg.bin */
    u16 top_tile;    /* 0x04: its top rows' first tile in the file, or SKY_RESOURCE_NO_TILE */
    u16 bottom_tile; /* 0x06: its bottom rows' */
    s32 slot;        /* 0x08: the slot (and layout) it needs */
    s8 palette;      /* 0x0c: of the palette files, -1: none */
    s8 obj_palette;  /* 0x0d: the OBJ palette it goes to (12 to 15), -1: none */
    u8 unk_0e[2];
} SkyResourceFile;

/* An entry of data_020d26a0: where a slot's cells go in each row of 32 tiles. */
typedef struct SkySlotLayout {
    s32 top_first;    /* 0x00: the first tile of each of the four top rows */
    s32 top_count;    /* 0x04: and their number, 0: none */
    s32 bottom_first; /* 0x08: of the four bottom rows */
    s32 bottom_count; /* 0x0c */
} SkySlotLayout;

/* data_021fa6b4 (0x1b6c of the objects). */
typedef struct SkyFiles {
    u8 file[0x48];                                                         /* 0x0000: the FSFile reading them */
    u8 row[SKY_FILES_FILE_ROW_TILES * SKY_FILES_TILE_BYTES];               /* 0x0048: a row of a cell file */
    u8 cells[SKY_FILES_ROWS * SKY_FILES_ROW_TILES * SKY_FILES_TILE_BYTES]; /* 0x0448 */
    u16 palettes[SKY_FILES_PALETTES][16];                                  /* 0x1048 */
    u32 magic;                                                             /* 0x1348: SKY_FILES_MAGIC once set up */
} SkyFiles;

/* data_021fba00 (0x2eb8 of the objects). */
typedef struct SkyPalettes {
    s32 variant;                           /* 0x00: of resources 31 and 32's palette */
    s8 loaded[4];                          /* 0x04: the palette in OBJ palettes 12 to 15, -1: unknown */
    u16 override_mask;                     /* 0x08: the overrides set */
    u16 overrides[SKY_PALETTES_OVERRIDES]; /* 0x0a: their colours (data_020d2324 says where) */
    u16 colors[16];                        /* 0x28: a palette as it is loaded */
} SkyPalettes;

void SkyPalettes_SetOverride(SkyPalettes *palettes, int index, const u16 *color);
int SkyPalettes_HasOverride(SkyPalettes *palettes, int index);
void SkyPalettes_ClearOverride(SkyPalettes *palettes, int index);
void SkyPalettes_SetLoaded(SkyPalettes *palettes, int obj_palette, s8 palette);
int SkyPalettes_IsLoaded(SkyPalettes *palettes, int resource);
void SkyPalettes_ForgetResource(SkyPalettes *palettes, int resource);
void SkyPalettes_Forget(SkyPalettes *palettes, int obj_palette);
void SkyPalettes_PickVariant(SkyPalettes *palettes);
int SkyPalettes_ApplyOverrides(SkyPalettes *palettes, int obj_palette);
void SkyPalettes_Load(SkyPalettes *palettes, SkyFiles *files, unsigned int resource);
SkyPalettes *SkyPalettes_Construct(SkyPalettes *palettes);
void SkySlot_Release(SkyObjectSlot *slot);
void SkySlot_Reload(SkyObjectSlot *slot, int resource);
void SkySlot_SetResource(SkyObjectSlot *slot, unsigned int resource);
void SkySlot_Use(SkyObjectSlot *slot, int resource, SkyPalettes *palettes);
void SkySlot_LoadCells(SkyObjectSlot *slot, SkyFiles *files);
void SkySlot_Construct(SkyObjectSlot *slot);
void SkyFiles_FlushCells(SkyFiles *files);
int SkyFiles_ReadPalettes(SkyFiles *files);
int SkyFiles_ReadCells(SkyFiles *files, int resource);
void SkyFiles_Init(SkyFiles *files);

#endif
