/* What the sky's objects draw with (sky_resources.h). */
#include "sky_resources.h"

#include "clean.h"
#include "main_random.h"

static_assert(sizeof(SkyResourceFile) == 16, "a resource");
static_assert(offsetof(SkyResourceFile, palette) == 0x0c, "the palette");
static_assert(sizeof(SkySlotLayout) == 16, "a layout");
static_assert(offsetof(SkyFiles, cells) == 0x448, "the cells");
static_assert(offsetof(SkyFiles, palettes) == 0x1048, "the palettes");
static_assert(offsetof(SkyFiles, magic) == 0x1348, "the magic word");
static_assert(sizeof(SkyFiles) == 0x134c, "the files");
static_assert(offsetof(SkyPalettes, override_mask) == 0x08, "the overrides' mask");
static_assert(offsetof(SkyPalettes, colors) == 0x28, "the colours");
static_assert(sizeof(SkyPalettes) == 0x48, "the palettes");

#define SKY_FILES_READ_PALETTES 14      /* of a_sky_obj_ncl.bin */
#define SKY_FILES_READ_MOON_PALETTES 10 /* of a_sky_moon_obj_ncl.bin */
#define SKY_SLOT_FIRST_TILE 0x94        /* the slots' cells' first tile in OBJ VRAM */
#define SKY_RESOURCE_UNUSED 0x34        /* SkyObjectSlot.kind: no resource */
#define SKY_PALETTE_BYTES 32

/* The paths of the palette files, as the game copies them. */
typedef struct SkyPalettePath {
    char name[23];
} SkyPalettePath;
typedef struct SkyMoonPalettePath {
    char name[28];
} SkyMoonPalettePath;

extern const SkyResourceFile data_020d2bac[];
extern const SkySlotLayout data_020d26a0[];
extern const char *const data_020d22d8[];              /* the cell files' paths */
extern const u8 data_020d2324[SKY_PALETTES_OVERRIDES]; /* per override: OBJ palette << 4 | colour */
extern const u16 data_020d22c0;                        /* an override's colour before it is set */
extern const SkyPalettePath data_020e6100;             /* "/sky/a_sky_obj_ncl.bin" */
extern const SkyMoonPalettePath data_020e6168;         /* "/sky/a_sky_moon_obj_ncl.bin" */
extern SkyPalettes data_021fba00;                      /* the objects' palettes */

extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
extern void MI_CpuFill8(void *dst, u8 value, u32 size);
extern void DC_FlushRange(const void *start, u32 size);
extern void GX_LoadOBJ(const void *src, u32 offset, u32 size);
extern void GXS_LoadOBJ(const void *src, u32 offset, u32 size);
extern void GX_LoadOBJPltt(const void *src, u32 offset, u32 size);
extern void GXS_LoadOBJPltt(const void *src, u32 offset, u32 size);
extern void FS_InitFile(void *file);
extern int FS_OpenFile(void *file, const char *path);
extern int FS_SeekFile(void *file, s32 offset, int whence);
extern s32 FS_ReadFile(void *file, void *dst, s32 size);
extern int FS_CloseFile(void *file);

/* 1 shifted left as the ARM shifts by a register: by its low byte, 0 from 32 on. */
static u32 sky_resources_bit(int n)
{
    u32 amount = (u32) n & 0xff;
    return amount < 32 ? 1u << amount : 0;
}

/* The byte of SkyPalettes.loaded for an OBJ palette, at the address the ARM computes. */
static s8 *sky_palettes_loaded_at(SkyPalettes *palettes, int obj_palette)
{
    return (s8 *) ((uintptr_t) palettes->loaded + (u32) (obj_palette - SKY_PALETTES_FIRST));
}

/* func_020bec14: override `index` set to `color`, and its OBJ palette's palette forgotten so
 * that it is loaded again.
 * REQUIRES: index is 0 to 14. */
void SkyPalettes_SetOverride(SkyPalettes *palettes, int index, const u16 *color)
{
    palettes->override_mask = (u16) (palettes->override_mask | sky_resources_bit(index));
    palettes->overrides[index] = *color;
    SkyPalettes_Forget(palettes, (data_020d2324[index] >> 4) & 0xf);
}
CLEAN_AS(func_020bec14, SkyPalettes_SetOverride)

/* func_020bec40: override `index` is set. */
int SkyPalettes_HasOverride(SkyPalettes *palettes, int index)
{
    return (palettes->override_mask & sky_resources_bit(index)) != 0;
}
CLEAN_AS(func_020bec40, SkyPalettes_HasOverride)

/* func_020bec54: override `index` cleared (its palette is not loaded again for it). */
void SkyPalettes_ClearOverride(SkyPalettes *palettes, int index)
{
    palettes->override_mask = (u16) (palettes->override_mask & ~sky_resources_bit(index));
}
CLEAN_AS(func_020bec54, SkyPalettes_ClearOverride)

/* func_020bec60: OBJ palette `obj_palette` noted as holding `palette`, when both are known. */
void SkyPalettes_SetLoaded(SkyPalettes *palettes, int obj_palette, s8 palette)
{
    if (obj_palette >= 0 && palette >= 0) {
        *sky_palettes_loaded_at(palettes, obj_palette) = palette;
    }
}
CLEAN_AS(func_020bec60, SkyPalettes_SetLoaded)

/* func_020bec70: `resource`'s palette is in its OBJ palette (or it has none of either). */
int SkyPalettes_IsLoaded(SkyPalettes *palettes, int resource)
{
    const SkyResourceFile *entry = &data_020d2bac[resource];
    int obj_palette = entry->obj_palette;
    int palette = entry->palette;
    if (obj_palette >= 0 && palette >= 0 && palette != *sky_palettes_loaded_at(palettes, obj_palette)) {
        return 0;
    }
    return 1;
}
CLEAN_AS(func_020bec70, SkyPalettes_IsLoaded)

/* func_020beca4: what `resource`'s OBJ palette holds forgotten. */
void SkyPalettes_ForgetResource(SkyPalettes *palettes, int resource)
{
    SkyPalettes_Forget(palettes, data_020d2bac[resource].obj_palette);
}
CLEAN_AS(func_020beca4, SkyPalettes_ForgetResource)

/* func_020becbc: what OBJ palette `obj_palette` holds forgotten; all four for a negative one. */
void SkyPalettes_Forget(SkyPalettes *palettes, int obj_palette)
{
    if (obj_palette < 0) {
        for (int i = 0; i < 4; i++) {
            palettes->loaded[i] = -1;
        }
    } else {
        *sky_palettes_loaded_at(palettes, obj_palette) = -1;
    }
}
CLEAN_AS(func_020becbc, SkyPalettes_Forget)

/* func_020bece0: a variant of resources 31 and 32's palette picked at random, and their OBJ
 * palette forgotten. */
void SkyPalettes_PickVariant(SkyPalettes *palettes)
{
    palettes->variant = (s32) MainRandom_Below(SKY_PALETTES_VARIANTS);
    SkyPalettes_Forget(palettes, data_020d2bac[SKY_RESOURCE_VARIANT_FIRST].obj_palette);
}
CLEAN_AS(func_020bece0, SkyPalettes_PickVariant)

/* func_020bed04: the overrides set for OBJ palette `obj_palette` written into the palette being
 * loaded; whether there was one. */
int SkyPalettes_ApplyOverrides(SkyPalettes *palettes, int obj_palette)
{
    int applied = 0;
    if (palettes->override_mask == 0) {
        return 0;
    }
    for (int i = 0; i < SKY_PALETTES_OVERRIDES; i++) {
        int set = SkyPalettes_HasOverride(palettes, i);
        u8 where = data_020d2324[i];
        if (set && ((where >> 4) & 0xf) == obj_palette) {
            palettes->colors[where & 0xf] = palettes->overrides[i];
            applied = 1;
        }
    }
    return applied;
}
CLEAN_AS(func_020bed04, SkyPalettes_ApplyOverrides)

/* func_020bed64: `resource`'s palette (for resources 31 and 32 moved on by the variant) taken
 * from the palette files, the overrides applied, and loaded into its OBJ palette, also the sub
 * engine's while the sky is on the sub screen. Noted as loaded unless an override was applied. */
void SkyPalettes_Load(SkyPalettes *palettes, SkyFiles *files, unsigned int resource)
{
    const SkyResourceFile *entry = &data_020d2bac[resource];
    int palette = entry->palette;
    if (resource == SKY_RESOURCE_VARIANT_FIRST || resource == SKY_RESOURCE_VARIANT_FIRST + 1) {
        palette += palettes->variant;
    }
    u32 offset = (u32) entry->obj_palette * SKY_PALETTE_BYTES;
    MI_CpuCopy8((const u8 *) files->palettes + (u32) palette * SKY_PALETTE_BYTES, palettes->colors, SKY_PALETTE_BYTES);
    int overridden = SkyPalettes_ApplyOverrides(palettes, entry->obj_palette);
    DC_FlushRange(palettes->colors, SKY_PALETTE_BYTES);
    GX_LoadOBJPltt(palettes->colors, offset, SKY_PALETTE_BYTES);
    if (data_021f75b0.screen == SKY_SCREEN_SUB) {
        GXS_LoadOBJPltt(palettes->colors, offset, SKY_PALETTE_BYTES);
    }
    if (!overridden) {
        SkyPalettes_SetLoaded(palettes, entry->obj_palette, (s8) palette);
    }
}
CLEAN_AS(func_020bed64, SkyPalettes_Load)

/* func_020bedf4: the constructor: no variant, no override (their colours data_020d22c0), the
 * OBJ palettes unknown, the palette being loaded cleared. */
SkyPalettes *SkyPalettes_Construct(SkyPalettes *palettes)
{
    palettes->variant = 0;
    palettes->override_mask = 0;
    SkyPalettes_Forget(palettes, -1);
    u16 unset = data_020d22c0;
    for (int i = 0; i < SKY_PALETTES_OVERRIDES; i++) {
        palettes->overrides[i] = unset;
    }
    MI_CpuFill8(palettes->colors, 0, sizeof(palettes->colors));
    return palettes;
}
CLEAN_AS(func_020bedf4, SkyPalettes_Construct)

/* The number of objects drawing from a slot (its word at 0x04). */
static s32 *sky_slot_users(SkyObjectSlot *slot)
{
    return (s32 *) (void *) slot->unk_04;
}

/* func_020bee3c: one object less draws from the slot (not below 0). */
void SkySlot_Release(SkyObjectSlot *slot)
{
    s32 users = *sky_slot_users(slot) - 1;
    *sky_slot_users(slot) = users > 0 ? users : 0;
}
CLEAN_AS(func_020bee3c, SkySlot_Release)

/* func_020bee4c: the slot to be loaded again, `resource`'s palette with it (the objects'
 * palettes, data_021fba00). */
void SkySlot_Reload(SkyObjectSlot *slot, int resource)
{
    slot->changed = 1;
    SkyPalettes_ForgetResource(&data_021fba00, resource);
}
CLEAN_AS(func_020bee4c, SkySlot_Reload)

/* func_020bee60: the slot given another resource, to be loaded. */
void SkySlot_SetResource(SkyObjectSlot *slot, unsigned int resource)
{
    if (resource != (u32) slot->kind) {
        slot->loaded = 0;
        slot->changed = 1;
        slot->kind = (s32) resource;
    }
}
CLEAN_AS(func_020bee60, SkySlot_SetResource)

/* func_020bee74: one object more draws from the slot, with `resource`: when the slot held
 * another, it is to be loaded and the resource's OBJ palette forgotten. */
void SkySlot_Use(SkyObjectSlot *slot, int resource, SkyPalettes *palettes)
{
    (*sky_slot_users(slot))++;
    if (resource != slot->kind) {
        slot->loaded = 0;
        SkyPalettes_ForgetResource(palettes, resource);
        slot->kind = resource;
    }
}
CLEAN_AS(func_020bee74, SkySlot_Use)

/* func_020bee9c: the slot's resource's cells, as read into the files, copied to its place in
 * OBJ VRAM: each row of the cell buffer (12 tiles) to a row of 32 tiles from tile 0x94, the
 * top four rows' and the bottom four's tiles where the slot's layout says; also into the sub
 * engine's while the sky is on the sub screen. */
void SkySlot_LoadCells(SkyObjectSlot *slot, SkyFiles *files)
{
    int sub = data_021f75b0.screen == SKY_SCREEN_SUB;
    SkyFiles_FlushCells(files);
    const SkySlotLayout *layout = &data_020d26a0[data_020d2bac[slot->kind].slot];
    for (int row = 0; row < SKY_FILES_ROWS; row++) {
        int top = row < SKY_FILES_ROWS / 2;
        s32 first = top ? layout->top_first : layout->bottom_first;
        s32 count = top ? layout->top_count : layout->bottom_count;
        if (count == 0) {
            continue;
        }
        const u8 *src = files->cells + (u32) (row * SKY_FILES_ROW_TILES + first) * SKY_FILES_TILE_BYTES;
        u32 offset = (u32) (SKY_SLOT_FIRST_TILE + row * SKY_FILES_FILE_ROW_TILES + first) * SKY_FILES_TILE_BYTES;
        u32 size = (u32) count * SKY_FILES_TILE_BYTES;
        GX_LoadOBJ(src, offset, size);
        if (sub) {
            GXS_LoadOBJ(src, offset, size);
        }
    }
}
CLEAN_AS(func_020bee9c, SkySlot_LoadCells)

/* func_020bef78: the constructor: no resource, no object, not loaded. */
void SkySlot_Construct(SkyObjectSlot *slot)
{
    slot->kind = SKY_RESOURCE_UNUSED;
    *sky_slot_users(slot) = 0;
    slot->loaded = 0;
    slot->changed = 0;
}
CLEAN_AS(func_020bef78, SkySlot_Construct)

/* func_020bef88: the cell buffer flushed from the data cache. */
void SkyFiles_FlushCells(SkyFiles *files)
{
    DC_FlushRange(files->cells, sizeof(files->cells));
}
CLEAN_AS(func_020bef88, SkyFiles_FlushCells)

/* func_020befa0: both palette files read whole (each opened, read and closed whatever went
 * before); whether every step succeeded. */
int SkyFiles_ReadPalettes(SkyFiles *files)
{
    SkyPalettePath path = data_020e6100;
    int opened = FS_OpenFile(files->file, path.name);
    int read = FS_ReadFile(files->file, files->palettes, SKY_FILES_READ_PALETTES * SKY_PALETTE_BYTES) > 0;
    int closed = FS_CloseFile(files->file);
    SkyMoonPalettePath moon_path = data_020e6168;
    int moon_opened = FS_OpenFile(files->file, moon_path.name);
    int moon_read = FS_ReadFile(files->file, files->palettes[SKY_FILES_READ_PALETTES],
                                SKY_FILES_READ_MOON_PALETTES * SKY_PALETTE_BYTES) > 0;
    int moon_closed = FS_CloseFile(files->file);
    return opened && read && closed && moon_opened && moon_read && moon_closed;
}
CLEAN_AS(func_020befa0, SkyFiles_ReadPalettes)

/* The four rows of one half of a resource read: from the row of 32 tiles holding `tile` on,
 * one row of the file each, `count` tiles from that tile copied to tile `first` of each row of
 * the cell buffer (none read without tiles to copy). Whether the seek succeeded; `reads` keeps
 * whether every read did. */
static int sky_files_read_half(SkyFiles *files, u32 tile, int first_row, s32 first, s32 count, int *reads)
{
    int sought = FS_SeekFile(files->file, (s32) ((tile & ~0x1fu) * SKY_FILES_TILE_BYTES), 0);
    for (int row = first_row; row < first_row + SKY_FILES_ROWS / 2; row++) {
        if (count == 0) {
            continue;
        }
        int read = FS_ReadFile(files->file, files->row, sizeof(files->row)) > 0;
        *reads = *reads & read;
        MI_CpuCopy8(files->row + (tile & 0x1f) * SKY_FILES_TILE_BYTES,
                    files->cells + (u32) (row * SKY_FILES_ROW_TILES + first) * SKY_FILES_TILE_BYTES,
                    (u32) count * SKY_FILES_TILE_BYTES);
    }
    return sought;
}

/* func_020bf064: `resource`'s cells read from its file into the cell buffer, its top rows and
 * its bottom rows (those it has), as its slot's layout places them; whether opening, every seek,
 * every read and closing succeeded. */
int SkyFiles_ReadCells(SkyFiles *files, int resource)
{
    const SkyResourceFile *entry = &data_020d2bac[resource];
    int opened = FS_OpenFile(files->file, data_020d22d8[entry->file]);
    int sought = 1;
    int reads = 1;
    const SkySlotLayout *layout = &data_020d26a0[entry->slot];
    if (entry->top_tile != SKY_RESOURCE_NO_TILE) {
        sought &= sky_files_read_half(files, entry->top_tile, 0, layout->top_first, layout->top_count, &reads);
    }
    if (entry->bottom_tile != SKY_RESOURCE_NO_TILE) {
        sought &= sky_files_read_half(files, entry->bottom_tile, SKY_FILES_ROWS / 2, layout->bottom_first,
                                      layout->bottom_count, &reads);
    }
    int closed = FS_CloseFile(files->file);
    return opened && sought && reads && closed;
}
CLEAN_AS(func_020bf064, SkyFiles_ReadCells)

/* func_020bf1b8: the file set up, the buffers cleared, the magic word set. */
void SkyFiles_Init(SkyFiles *files)
{
    FS_InitFile(files->file);
    MI_CpuFill8(files->row, 0, sizeof(files->row));
    MI_CpuFill8(files->cells, 0, sizeof(files->cells));
    MI_CpuFill8(files->palettes, 0, SKY_FILES_READ_PALETTES * SKY_PALETTE_BYTES);
    MI_CpuFill8(files->palettes[SKY_FILES_READ_PALETTES], 0, SKY_FILES_READ_MOON_PALETTES * SKY_PALETTE_BYTES);
    files->magic = SKY_FILES_MAGIC;
}
CLEAN_AS(func_020bf1b8, SkyFiles_Init)
