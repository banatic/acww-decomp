/* The OBJ graphics of /a_mes/ (a_mes_obj.h). */
#include "a_mes_obj.h"

#include <assert.h>
#include <stddef.h>
#include <stdint.h>

#include "autoload_2/heap.h"
#include "clean.h"

static_assert(offsetof(AMesObj, palettes) == 0x48, "AMesObj layout");
static_assert(offsetof(AMesObj, chars) == 0x4c, "AMesObj layout");
static_assert(offsetof(AMesObj, extra_chars) == 0x50, "AMesObj layout");
static_assert(offsetof(AMesObj, pending_screens) == 0x250, "AMesObj layout");
static_assert(offsetof(AMesObj, ready) == 0x254, "AMesObj layout");
static_assert(offsetof(AMesObj, variant) == 0x255, "AMesObj layout");

/* The game's object. The symbols data_021c1484 and data_021c14c4 the original also reads
 * point into it (at 0x200 and 0x240). */
extern AMesObj data_021c1284;

/* The character files: the plain one, its variants, and the variant 2 the icons and the
 * extra characters also read. */
extern const char data_020d849c[]; /* "/a_mes/a_mes_obj_ncg.bin" */
extern const char data_020d843c[]; /* "/a_mes/a_mes_ten0_obj_ncg.bin" */
extern const char data_020d845c[]; /* "/a_mes/a_mes_ten1_obj_ncg.bin" */
extern const char data_020c8098[]; /* "/a_mes/a_mes_ten2_obj_ncg.bin" */
extern const char data_020d847c[]; /* "/a_mes/a_mes_ten3_obj_ncg.bin" */
/* The palette files. */
extern const char data_020d8518[]; /* "/a_mes/a_mes_obj_ncl.bin" */
extern const char data_020d84b8[]; /* "/a_mes/a_mes_ten0_obj_ncl.bin" */
extern const char data_020d84d8[]; /* "/a_mes/a_mes_ten1_obj_ncl.bin" */
extern const char data_020d84f8[]; /* "/a_mes/a_mes_ten2_obj_ncl.bin" */

/* Where ScreenIcon's variant (0 to 4) starts in its file: 0x28c0, 0x100, 0x140, 0x180, 0x1c0. */
extern const u32 data_020d8428[];
/* The window style (0 to 3) of each scene. */
extern const u8 data_020c80b8[];

extern u8 func_020b65c4(void);  /* the current scene */
extern int func_0208ff98(void); /* the touch screen controls the game (control_mode.h) */
extern void func_02039800(void);

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
extern void MI_CpuFill8(void *dst, u8 value, u32 size);

#define FS_SEEK_SET 0
#define FS_READ_FAILED (-1)

/* Rows of characters, in the files as in VRAM: 32 characters of 0x20 bytes. */
#define ROW 0x400
#define ROWS 2

#define SCREEN_ICON_VRAM 0x38c0
#define SCREEN_ICON_ROW 0x40 /* 2 characters */
#define WIRELESS_ICON_VRAM 0x3300
#define WIRELESS_ICON_ROW 0x100 /* 8 characters */
#define EXTRA_VRAM 0x1180
#define EXTRA_ROW 0x100 /* 8 characters */
#define WINDOW_VRAM 0x1000
#define WINDOW_ROW 0x280 /* 20 characters */
#define SHEET_SIZE 0x3000
#define PALETTES_SIZE 0x180
#define PALETTES_VRAM 0x80      /* palette 4 */
#define PALETTES_FIRST 0x100    /* palettes 4 to 11 */
#define PALETTE_LAST_FROM 0x160 /* palette 11 of the file ... */
#define PALETTE_LAST_VRAM 0x1e0 /* ... goes to palette 15 */
#define PALETTE_SIZE 0x20

static int to_main(u32 screens)
{
    return screens == AMES_SCREENS_BOTH || screens == AMES_SCREENS_MAIN;
}

static int to_sub(u32 screens)
{
    return screens == AMES_SCREENS_BOTH || screens == AMES_SCREENS_SUB;
}

/* Row `i` of `row_size` bytes from `base`, worked out on the address so that a NULL `base`
 * (see AMesObj_LoadScreenIcon) gives the addresses the original uses. */
static u8 *row_at(u8 *base, u32 i, u32 row_size)
{
    return (u8 *) ((uintptr_t) base + i * row_size);
}

/* Reads ROWS rows of `row_size` bytes, ROW apart from `offset` on in the open file, into
 * `dst` one after the other; whether every seek and read worked (each one is tried). */
static int read_rows(AMesObj *obj, u8 *dst, s32 offset, s32 row_size)
{
    int ok = 1;
    for (u32 i = 0; i < ROWS; i++) {
        if (!FS_SeekFile(obj->file, offset, FS_SEEK_SET)) {
            ok = 0;
        }
        if (FS_ReadFile(obj->file, row_at(dst, i, (u32) row_size), row_size) == FS_READ_FAILED) {
            ok = 0;
        }
        offset += ROW;
    }
    return ok;
}

/* func_020116b4 */
void AMesObj_FreeScreenIcon(AMesObj *obj)
{
    AMesObj_FreeChars(obj);
}
CLEAN_AS(func_020116b4, AMesObj_FreeScreenIcon)

/* func_020116bc: both rows to both screens. */
void AMesObj_UploadScreenIcon(AMesObj *obj)
{
    DC_FlushRange(obj->chars, ROWS * SCREEN_ICON_ROW);
    u32 offset = SCREEN_ICON_VRAM;
    for (u32 i = 0; i < ROWS; i++) {
        const u8 *row = row_at(obj->chars, i, SCREEN_ICON_ROW);
        GX_LoadOBJ(row, offset, SCREEN_ICON_ROW);
        GXS_LoadOBJ(row, offset, SCREEN_ICON_ROW);
        offset += ROW;
    }
}
CLEAN_AS(func_020116bc, AMesObj_UploadScreenIcon)

/* func_02011704: ScreenIcon's variant `mode` into the current heap: variant 0 from the file
 * of kind 1, the others from ten2; whether the file opened, read and closed.
 * REQUIRES: `mode` is 0 to 4 (ScreenIcon's variants), the entries of the table of offsets.
 * BUG: the block from the heap is not checked; without one the rows are read to address 0
 * (BUGFIX: the load fails instead). */
int AMesObj_LoadScreenIcon(AMesObj *obj, int mode)
{
    const char *path = mode == 0 ? AMesObj_CharsPath(obj, 1) : data_020c8098;
    int opened = FS_OpenFile(obj->file, path);
    obj->chars = Heap_AllocCurrentBack(ROWS * SCREEN_ICON_ROW);
#ifdef BUGFIX
    int read = obj->chars != NULL && read_rows(obj, obj->chars, (s32) data_020d8428[mode], SCREEN_ICON_ROW);
#else
    int read = read_rows(obj, obj->chars, (s32) data_020d8428[mode], SCREEN_ICON_ROW);
#endif
    int closed = FS_CloseFile(obj->file);
    return opened && read && closed;
}
CLEAN_AS(func_02011704, AMesObj_LoadScreenIcon)

/* func_020117a0 */
void AMesObj_FreeWirelessIcon(AMesObj *obj)
{
    AMesObj_FreeChars(obj);
}
CLEAN_AS(func_020117a0, AMesObj_FreeWirelessIcon)

/* func_020117a8: both rows to both screens. */
void AMesObj_UploadWirelessIcon(AMesObj *obj)
{
    DC_FlushRange(obj->chars, ROWS * WIRELESS_ICON_ROW);
    u32 offset = WIRELESS_ICON_VRAM;
    for (u32 i = 0; i < ROWS; i++) {
        const u8 *row = row_at(obj->chars, i, WIRELESS_ICON_ROW);
        GX_LoadOBJ(row, offset, WIRELESS_ICON_ROW);
        GXS_LoadOBJ(row, offset, WIRELESS_ICON_ROW);
        offset += ROW;
    }
}
CLEAN_AS(func_020117a8, AMesObj_UploadWirelessIcon)

/* func_020117f8: the wireless icon into the current heap: with `wfc` from ten2 at 0x200, else
 * from the file of the scene's kind at 0x2300; whether the file opened, read and closed.
 * BUG: as AMesObj_LoadScreenIcon, the block from the heap is not checked. */
int AMesObj_LoadWirelessIcon(AMesObj *obj, int wfc)
{
    const char *path = wfc != 0 ? data_020c8098 : AMesObj_CharsPath(obj, AMES_KIND_SCENE);
    int opened = FS_OpenFile(obj->file, path);
    obj->chars = Heap_AllocCurrentBack(ROWS * WIRELESS_ICON_ROW);
    s32 offset = wfc != 0 ? 0x200 : 0x2300;
#ifdef BUGFIX
    int read = obj->chars != NULL && read_rows(obj, obj->chars, offset, WIRELESS_ICON_ROW);
#else
    int read = read_rows(obj, obj->chars, offset, WIRELESS_ICON_ROW);
#endif
    int closed = FS_CloseFile(obj->file);
    return opened && read && closed;
}
CLEAN_AS(func_020117f8, AMesObj_LoadWirelessIcon)

/* func_020118a0: the extra characters to the screens asked for. */
void AMesObj_UploadExtraChars(AMesObj *obj, int screens)
{
    DC_FlushRange(obj->extra_chars, sizeof obj->extra_chars);
    int on_main = to_main((u32) screens);
    int on_sub = to_sub((u32) screens);
    u32 offset = EXTRA_VRAM;
    for (u32 i = 0; i < ROWS; i++) {
        const u8 *row = obj->extra_chars + i * EXTRA_ROW;
        if (on_main) {
            GX_LoadOBJ(row, offset, EXTRA_ROW);
        }
        if (on_sub) {
            GXS_LoadOBJ(row, offset, EXTRA_ROW);
        }
        offset += ROW;
    }
}
CLEAN_AS(func_020118a0, AMesObj_UploadExtraChars)

/* func_02011924: the extra characters into the object: with `alternate` from ten2 at 0, else
 * from the file of kind 2 at 0x180; whether the file opened, read and closed. */
int AMesObj_LoadExtraChars(AMesObj *obj, int alternate)
{
    const char *path = alternate != 0 ? data_020c8098 : AMesObj_CharsPath(obj, 2);
    int opened = FS_OpenFile(obj->file, path);
    int read = read_rows(obj, obj->extra_chars, alternate != 0 ? 0 : 0x180, EXTRA_ROW);
    int closed = FS_CloseFile(obj->file);
    return opened && read && closed;
}
CLEAN_AS(func_02011924, AMesObj_LoadExtraChars)

/* func_020119c4: the window's characters to the screens asked for. */
void AMesObj_UploadWindowChars(AMesObj *obj, int screens)
{
    DC_FlushRange(obj->chars, ROWS * WINDOW_ROW);
    int on_main = to_main((u32) screens);
    int on_sub = to_sub((u32) screens);
    u32 offset = WINDOW_VRAM;
    for (u32 i = 0; i < ROWS; i++) {
        const u8 *row = obj->chars + i * WINDOW_ROW;
        if (on_main) {
            GX_LoadOBJ(row, offset, WINDOW_ROW);
        }
        if (on_sub) {
            GXS_LoadOBJ(row, offset, WINDOW_ROW);
        }
        offset += ROW;
    }
}
CLEAN_AS(func_020119c4, AMesObj_UploadWindowChars)

/* func_02011a50 */
void AMesObj_FreeWindowChars(AMesObj *obj)
{
    AMesObj_FreeChars(obj);
}
CLEAN_AS(func_02011a50, AMesObj_FreeWindowChars)

/* func_02011a58: the window's characters of `kind` into the current heap (the first two rows
 * of the file); whether there was room and the file opened, read and closed. */
int AMesObj_LoadWindowChars(AMesObj *obj, int kind)
{
    int opened = FS_OpenFile(obj->file, AMesObj_CharsPath(obj, kind));
    obj->chars = Heap_AllocCurrentBack(ROWS * WINDOW_ROW);
    int read = 1;
    if (obj->chars != NULL) {
        read = read_rows(obj, obj->chars, 0, WINDOW_ROW);
    }
    int closed = FS_CloseFile(obj->file);
    return opened && read && closed && obj->chars != NULL;
}
CLEAN_AS(func_02011a58, AMesObj_LoadWindowChars)

/* func_02011af8: the whole sheet to the screens asked for. */
void AMesObj_UploadSheet(AMesObj *obj, u32 screens)
{
    DC_FlushRange(obj->chars, SHEET_SIZE);
    if (to_main(screens)) {
        GX_LoadOBJ(obj->chars, WINDOW_VRAM, SHEET_SIZE);
    }
    if (to_sub(screens)) {
        GXS_LoadOBJ(obj->chars, WINDOW_VRAM, SHEET_SIZE);
    }
}
CLEAN_AS(func_02011af8, AMesObj_UploadSheet)

/* func_02011b38: the file's palettes 0 to 7 to palettes 4 to 11, and its palette 11 to
 * palette 15, of the screens asked for. */
void AMesObj_UploadPalettes(AMesObj *obj, u32 screens)
{
    DC_FlushRange(obj->palettes, PALETTES_SIZE);
    const u8 *first = obj->palettes;
    const u8 *last = first + PALETTE_LAST_FROM;
    if (to_main(screens)) {
        GX_LoadOBJPltt(first, PALETTES_VRAM, PALETTES_FIRST);
        GX_LoadOBJPltt(last, PALETTE_LAST_VRAM, PALETTE_SIZE);
    }
    if (to_sub(screens)) {
        GXS_LoadOBJPltt(first, PALETTES_VRAM, PALETTES_FIRST);
        GXS_LoadOBJPltt(last, PALETTE_LAST_VRAM, PALETTE_SIZE);
    }
}
CLEAN_AS(func_02011b38, AMesObj_UploadPalettes)

/* func_02011b98 */
void AMesObj_FreeChars(AMesObj *obj)
{
    if (obj->chars != NULL) {
        Heap_FreeCurrent(obj->chars);
        obj->chars = NULL;
    }
}
CLEAN_AS(func_02011b98, AMesObj_FreeChars)

/* func_02011bb0 */
void AMesObj_FreePalettes(AMesObj *obj)
{
    if (obj->palettes != NULL) {
        Heap_FreeCurrent(obj->palettes);
        obj->palettes = NULL;
    }
}
CLEAN_AS(func_02011bb0, AMesObj_FreePalettes)

/* func_02011bc8: the whole sheet of the scene's kind into the current heap; whether there was
 * room and the file opened, read and closed. */
int AMesObj_LoadSheet(AMesObj *obj)
{
    int opened = FS_OpenFile(obj->file, AMesObj_CharsPath(obj, AMES_KIND_SCENE));
    obj->chars = Heap_AllocCurrentBack(SHEET_SIZE);
    int read = 0;
    if (obj->chars != NULL) {
        read = FS_ReadFile(obj->file, obj->chars, SHEET_SIZE) != FS_READ_FAILED;
    }
    int closed = FS_CloseFile(obj->file);
    return opened && read && closed && obj->chars != NULL;
}
CLEAN_AS(func_02011bc8, AMesObj_LoadSheet)

/* func_02011c28: the palettes of `kind` into the current heap; whether there was room and the
 * file opened, read and closed. */
int AMesObj_LoadPalettes(AMesObj *obj, int kind)
{
    int opened = FS_OpenFile(obj->file, AMesObj_PalettesPath(obj, kind));
    obj->palettes = Heap_AllocCurrentBack(PALETTES_SIZE);
    int read = 0;
    if (obj->palettes != NULL) {
        read = FS_ReadFile(obj->file, obj->palettes, PALETTES_SIZE) != FS_READ_FAILED;
    }
    int closed = FS_CloseFile(obj->file);
    return opened && read && closed && obj->palettes != NULL;
}
CLEAN_AS(func_02011c28, AMesObj_LoadPalettes)

/* func_02011c88: the character file of `kind` (AMES_KIND_SCENE and up: the scene's style):
 * 2 is ten1, 3 ten0, others ten3 with the variant set, else the plain file. */
const char *AMesObj_CharsPath(const AMesObj *obj, int kind)
{
    if (kind >= AMES_KIND_SCENE) {
        kind = AMesObj_Style();
    }
    if (kind == 2) {
        return data_020d845c;
    }
    if (kind == 3) {
        return data_020d843c;
    }
    return obj->variant != 0 ? data_020d847c : data_020d849c;
}
CLEAN_AS(func_02011c88, AMesObj_CharsPath)

/* func_02011cd8: the palette file of `kind`, as AMesObj_CharsPath: 2 is ten1, 3 ten0, others
 * ten2 with the variant set, else the plain file. */
const char *AMesObj_PalettesPath(const AMesObj *obj, int kind)
{
    if (kind >= AMES_KIND_SCENE) {
        kind = AMesObj_Style();
    }
    if (kind == 2) {
        return data_020d84d8;
    }
    if (kind == 3) {
        return data_020d84b8;
    }
    return obj->variant != 0 ? data_020d84f8 : data_020d8518;
}
CLEAN_AS(func_02011cd8, AMesObj_PalettesPath)

/* func_02011d28: NitroSDK's FS_InitFile on the object's file. */
void AMesObj_InitFile(void *file)
{
    FS_InitFile(file);
}
CLEAN_AS(func_02011d28, AMesObj_InitFile)

/* func_02011d30: ScreenIcon's variant `mode` loaded into the game's object, uploaded when that
 * worked, and freed; the freeing is done on `obj` (the game passes its object). */
void AMesObj_ShowScreenIcon(AMesObj *obj, int mode)
{
    AMesObj *game = &data_021c1284;
    AMesObj_InitFile(game->file);
    if (AMesObj_LoadScreenIcon(game, mode)) {
        AMesObj_UploadScreenIcon(game);
    }
    AMesObj_FreeScreenIcon(obj);
}
CLEAN_AS(func_02011d30, AMesObj_ShowScreenIcon)

/* func_02011d60: as AMesObj_ShowScreenIcon, for the wireless icon. */
void AMesObj_ShowWirelessIcon(AMesObj *obj, int wfc)
{
    AMesObj *game = &data_021c1284;
    AMesObj_InitFile(game->file);
    if (AMesObj_LoadWirelessIcon(game, wfc)) {
        AMesObj_UploadWirelessIcon(game);
    }
    AMesObj_FreeWirelessIcon(obj);
}
CLEAN_AS(func_02011d60, AMesObj_ShowWirelessIcon)

/* func_02011d90: the extra characters loaded into the game's object; with `defer` the screens
 * are only noted in `obj` for AMesObj_UploadPending (whether the load worked or not), else
 * they are uploaded now when the load worked. */
void AMesObj_ShowExtraChars(AMesObj *obj, int alternate, int defer, int screens)
{
    AMesObj *game = &data_021c1284;
    AMesObj_InitFile(game->file);
    int loaded = AMesObj_LoadExtraChars(game, alternate);
    if (defer != 0) {
        obj->pending_screens = (u32) screens;
    } else if (loaded) {
        AMesObj_UploadExtraChars(game, screens);
    }
}
CLEAN_AS(func_02011d90, AMesObj_ShowExtraChars)

/* func_02011dd0: the palettes and the window's characters of `kind`, each loaded into the game's
 * object, uploaded when that worked and freed; for a window of style 2 (kind 2, or the scene's
 * when that is 2) while the touch screen controls the game, the extra characters of ten2
 * too. */
void AMesObj_ShowWindow(AMesObj *obj, int kind, int screens)
{
    AMesObj *game = &data_021c1284;
    AMesObj_InitFile(game->file);
    if (AMesObj_LoadPalettes(game, kind)) {
        AMesObj_UploadPalettes(game, (u32) screens);
    }
    AMesObj_FreePalettes(game);
    if (AMesObj_LoadWindowChars(game, kind)) {
        AMesObj_UploadWindowChars(game, screens);
    }
    AMesObj_FreeWindowChars(game);
    if ((kind == 2 || (kind == AMES_KIND_SCENE && AMesObj_Style() == 2)) && func_0208ff98()) {
        AMesObj_ShowExtraChars(obj, 1, 0, screens);
    }
}
CLEAN_AS(func_02011dd0, AMesObj_ShowWindow)

/* func_02011e48: as AMesObj_ShowWindow for the scene's kind, with the whole sheet. */
void AMesObj_ShowSheet(AMesObj *obj, int screens)
{
    AMesObj *game = &data_021c1284;
    AMesObj_InitFile(game->file);
    if (AMesObj_LoadPalettes(game, AMES_KIND_SCENE)) {
        AMesObj_UploadPalettes(game, (u32) screens);
    }
    AMesObj_FreePalettes(game);
    if (AMesObj_LoadSheet(game)) {
        AMesObj_UploadSheet(game, (u32) screens);
    }
    AMesObj_FreeChars(game);
    if (AMesObj_Style() == 2 && func_0208ff98()) {
        AMesObj_ShowExtraChars(obj, 1, 0, screens);
    }
}
CLEAN_AS(func_02011e48, AMesObj_ShowSheet)

/* func_02011eb0: set by func_020a9bd8 after it loaded the scene's graphics, cleared by
 * func_020a9bb8. */
void AMesObj_ClearReady(void)
{
    data_021c1284.ready = 0;
}
CLEAN_AS(func_02011eb0, AMesObj_ClearReady)

/* func_02011ebc */
void AMesObj_SetReady(void)
{
    data_021c1284.ready = 1;
}
CLEAN_AS(func_02011ebc, AMesObj_SetReady)

/* func_02011ec8 */
u8 AMesObj_IsReady(void)
{
    return data_021c1284.ready;
}
CLEAN_AS(func_02011ec8, AMesObj_IsReady)

/* func_02011ed4: the window style (0 to 3) of the current scene. */
u8 AMesObj_Style(void)
{
    return data_020c80b8[func_020b65c4()];
}
CLEAN_AS(func_02011ed4, AMesObj_Style)

/* func_02011eec: the extra characters to the screens noted by AMesObj_ShowExtraChars, if
 * any. */
void AMesObj_UploadPending(void)
{
    AMesObj *game = &data_021c1284;
    if (game->pending_screens != AMES_SCREENS_NONE) {
        AMesObj_UploadExtraChars(game, (int) game->pending_screens);
        game->pending_screens = AMES_SCREENS_NONE;
    }
}
CLEAN_AS(func_02011eec, AMesObj_UploadPending)

/* func_02011f1c */
void AMesObj_SetScreenIcon(int mode)
{
    AMesObj_ShowScreenIcon(&data_021c1284, mode);
}
CLEAN_AS(func_02011f1c, AMesObj_SetScreenIcon)

/* func_02011f2c */
void AMesObj_SetWirelessIcon(int wfc)
{
    AMesObj_ShowWirelessIcon(&data_021c1284, wfc);
}
CLEAN_AS(func_02011f2c, AMesObj_SetWirelessIcon)

/* func_02011f3c */
u8 AMesObj_Variant(void)
{
    return data_021c1284.variant;
}
CLEAN_AS(func_02011f3c, AMesObj_Variant)

/* func_02011f48 */
void AMesObj_SetVariant(u8 variant)
{
    data_021c1284.variant = variant;
}
CLEAN_AS(func_02011f48, AMesObj_SetVariant)

/* func_02011f54 */
void AMesObj_SetExtraChars(int alternate, int defer, int screens)
{
    AMesObj_ShowExtraChars(&data_021c1284, alternate, defer, screens);
}
CLEAN_AS(func_02011f54, AMesObj_SetExtraChars)

/* func_02011f74 */
void AMesObj_SetWindow(int kind, int screens)
{
    AMesObj_ShowWindow(&data_021c1284, kind, screens);
}
CLEAN_AS(func_02011f74, AMesObj_SetWindow)

/* func_02011f88: the sheet to the sub screen, then func_02039800. */
void AMesObj_SetSheetSub(void)
{
    AMesObj_ShowSheet(&data_021c1284, AMES_SCREENS_SUB);
    func_02039800();
}
CLEAN_AS(func_02011f88, AMesObj_SetSheetSub)

/* func_02011fa4: the sheet to both screens, then func_02039800. */
void AMesObj_SetSheetBoth(void)
{
    AMesObj_ShowSheet(&data_021c1284, AMES_SCREENS_BOTH);
    func_02039800();
}
CLEAN_AS(func_02011fa4, AMesObj_SetSheetBoth)

/* func_02011fc0: the destructor (registered by __sinit_020c4248); frees what is still loaded
 * and returns the object. */
AMesObj *AMesObj_Destruct(AMesObj *obj)
{
    AMesObj_FreePalettes(obj);
    AMesObj_FreeChars(obj);
    return obj;
}
CLEAN_AS(func_02011fc0, AMesObj_Destruct)

/* func_02011fd8: nothing loaded or pending, no flags, the extra characters cleared. */
AMesObj *AMesObj_Construct(AMesObj *obj)
{
    obj->palettes = NULL;
    obj->chars = NULL;
    obj->pending_screens = AMES_SCREENS_NONE;
    obj->ready = 0;
    obj->variant = 0;
    MI_CpuFill8(obj->extra_chars, 0, sizeof obj->extra_chars);
    return obj;
}
CLEAN_AS(func_02011fd8, AMesObj_Construct)
