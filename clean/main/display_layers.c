/* The 2D layers by number (display_layers.h). */
#include "display_layers.h"

#include "clean.h"
#include "display_shadow.h"
#include "rom_file.h"

#define REG16(addr) (*(volatile u16 *) (addr))

#define CHAR_UNIT 32    /* a 16-colour character; a 256-colour one is two */
#define PALETTE_SIZE 32 /* 16 colours */
#define ALIGN_BACK -4   /* allocate from the heap's end */
#define LAYER_COUNT 9

/* The background control registers (BGxCNT) of the background layers, and the screen base
 * block each layer's screen is fixed at. */
static const u32 bg_control_regs[LAYER_SUB_BG3 + 1] = {0x0400000a, 0x0400000c, 0x0400000e, 0x04001008,
                                                       0x0400100a, 0x0400100c, 0x0400100e};
static const u8 screen_bases[LAYER_SUB_BG3 + 1] = {5, 6, 7, 12, 13, 14, 15};

#define BGCNT_KEEP 0x43 /* the priority and the mosaic bit */
#define BGCNT_PRIORITY 0x3

extern void DC_FlushRange(const void *start, u32 size);
extern void GX_LoadBG2Char(const void *src, u32 offset, u32 size);
extern void GX_LoadOBJ(const void *src, u32 offset, u32 size);
extern void GXS_LoadOBJ(const void *src, u32 offset, u32 size);
extern void GX_LoadBG2Scr(const void *src, u32 offset, u32 size);
extern void GX_LoadBGPltt(const void *src, u32 offset, u32 size);
extern void GXS_LoadBGPltt(const void *src, u32 offset, u32 size);
extern void GX_LoadOBJPltt(const void *src, u32 offset, u32 size);
extern void GXS_LoadOBJPltt(const void *src, u32 offset, u32 size);
/* The other background layers' character and screen loaders, as GX_LoadBG2Char and
 * GX_LoadBG2Scr for theirs. */
extern void func_02112d48(const void *src, u32 offset, u32 size); /* characters: main BG1 */
extern void func_02112ba8(const void *src, u32 offset, u32 size); /* main BG3 */
extern void func_02112db0(const void *src, u32 offset, u32 size); /* sub BG0 */
extern void func_02112ce0(const void *src, u32 offset, u32 size); /* sub BG1 */
extern void func_02112c10(const void *src, u32 offset, u32 size); /* sub BG2 */
extern void func_02112b40(const void *src, u32 offset, u32 size); /* sub BG3 */
extern void func_02113088(const void *src, u32 offset, u32 size); /* screen: main BG1 */
extern void func_02112ee8(const void *src, u32 offset, u32 size); /* main BG3 */
extern void func_021130f0(const void *src, u32 offset, u32 size); /* sub BG0 */
extern void func_02113020(const void *src, u32 offset, u32 size); /* sub BG1 */
extern void func_02112f50(const void *src, u32 offset, u32 size); /* sub BG2 */
extern void func_02112e80(const void *src, u32 offset, u32 size); /* sub BG3 */

/* The layer's bit in its screen's plane masks, and its number there (backgrounds 0-3, the
 * OBJ 4). */
static const u8 layer_planes[LAYER_COUNT] = {0x02, 0x04, 0x08, 0x01, 0x02, 0x04, 0x08, 0x10, 0x10};
static const u8 layer_plane_numbers[LAYER_COUNT] = {1, 2, 3, 0, 1, 2, 3, 4, 4};

static int is_main_screen(unsigned int layer)
{
    return layer <= LAYER_MAIN_BG3 || layer == LAYER_MAIN_OBJ;
}

/* func_02002708: numbers that are no layer do nothing. */
void DisplayLayer_Show(unsigned int layer)
{
    if (layer >= LAYER_COUNT) {
        return;
    }
    if (is_main_screen(layer)) {
        DisplayShadow_ShowMainPlanes(layer_planes[layer]);
    } else {
        DisplayShadow_ShowSubPlanes(layer_planes[layer]);
    }
}
CLEAN_AS(func_02002708, DisplayLayer_Show)

/* func_0200277c */
void DisplayLayer_Hide(unsigned int layer)
{
    if (layer >= LAYER_COUNT) {
        return;
    }
    if (is_main_screen(layer)) {
        DisplayShadow_HideMainPlanes(layer_planes[layer]);
    } else {
        DisplayShadow_HideSubPlanes(layer_planes[layer]);
    }
}
CLEAN_AS(func_0200277c, DisplayLayer_Hide)

/* func_020027f0 */
void DisplayLayer_HideAndResetScroll(int layer)
{
    DisplayLayer_Hide((unsigned int) layer);
    DisplayLayer_SetScroll((unsigned int) layer, 0, 0);
}
CLEAN_AS(func_020027f0, DisplayLayer_HideAndResetScroll)

/* func_0200284c: a background layer's scrolling (an affine one's x and y); the OBJ layers
 * have none. */
void DisplayLayer_SetScroll(unsigned int layer, int x, int y)
{
    switch (layer) {
        case LAYER_MAIN_BG1:
            DisplayShadow_SetMainBg1Scroll((u16) x, (u16) y);
            break;
        case LAYER_MAIN_BG2:
            DisplayShadow_SetMainBg2Scroll((unsigned int) x, (unsigned int) y);
            break;
        case LAYER_MAIN_BG3:
            DisplayShadow_SetMainBg3Scroll((unsigned int) x, (unsigned int) y);
            break;
        case LAYER_SUB_BG0:
            DisplayShadow_SetSubBg0Scroll((u16) x, (u16) y);
            break;
        case LAYER_SUB_BG1:
            DisplayShadow_SetSubBg1Scroll((u16) x, (u16) y);
            break;
        case LAYER_SUB_BG2:
            DisplayShadow_SetSubBg2Scroll(x, y);
            break;
        case LAYER_SUB_BG3:
            DisplayShadow_SetSubBg3Scroll(x, y);
            break;
    }
}
CLEAN_AS(func_0200284c, DisplayLayer_SetScroll)

/* func_020028bc: a background layer's screen size (BGxCNT's bits 14-15), colour mode (1 for
 * 256 colours) and character base block, with the screen at the layer's fixed base block and
 * no wrap-around; the priority and the mosaic bit are kept. Other layers do nothing.
 * QUIRK: the values are not masked to their fields. */
void DisplayLayer_SetBgControl(unsigned int layer, int size, int colors_256, int char_base)
{
    u32 reg;

    if (layer > LAYER_SUB_BG3) {
        return;
    }
    reg = bg_control_regs[layer];
    REG16(reg) = (u16) ((u32) char_base << 2 | (u32) colors_256 << 7 | (REG16(reg) & BGCNT_KEEP) | (u32) size << 14 |
                        (u32) screen_bases[layer] << 8);
}
CLEAN_AS(func_020028bc, DisplayLayer_SetBgControl)

/* func_020029e8: a background layer's priority; other layers do nothing.
 * QUIRK: a priority above 3 sets BGxCNT's other bits. */
void DisplayLayer_SetPriority(int layer, int priority)
{
    u32 reg;

    if ((unsigned int) layer > LAYER_SUB_BG3) {
        return;
    }
    reg = bg_control_regs[layer];
    REG16(reg) = (u16) ((REG16(reg) & ~BGCNT_PRIORITY) | priority);
}
CLEAN_AS(func_020029e8, DisplayLayer_SetPriority)

/* func_02002a88: load characters `first` to `last` (16-colour units) of a layer, from `data`
 * holding the characters from `data_first` on; returns 1. */
int DisplayLayer_LoadChars(u32 data, int layer, u32 data_first, u32 first, u32 last)
{
    const void *src = (const void *) (data + (first - data_first) * CHAR_UNIT);
    u32 size = (last - first + 1) * CHAR_UNIT;
    u32 offset = first * CHAR_UNIT;

    DC_FlushRange(src, size);
    switch (layer) {
        case LAYER_MAIN_BG1:
            func_02112d48(src, offset, size);
            break;
        case LAYER_MAIN_BG2:
            GX_LoadBG2Char(src, offset, size);
            break;
        case LAYER_MAIN_BG3:
            func_02112ba8(src, offset, size);
            break;
        case LAYER_SUB_BG0:
            func_02112db0(src, offset, size);
            break;
        case LAYER_SUB_BG1:
            func_02112ce0(src, offset, size);
            break;
        case LAYER_SUB_BG2:
            func_02112c10(src, offset, size);
            break;
        case LAYER_SUB_BG3:
            func_02112b40(src, offset, size);
            break;
        case LAYER_MAIN_OBJ:
            GX_LoadOBJ(src, offset, size);
            break;
        case LAYER_SUB_OBJ:
            GXS_LoadOBJ(src, offset, size);
            break;
    }
    return 1;
}
CLEAN_AS(func_02002a88, DisplayLayer_LoadChars)

/* func_02002b40: load `size` bytes of a background layer's screen at byte `offset`; returns 1. */
int DisplayLayer_LoadScreen(void *data, int layer, int size, int offset)
{
    DC_FlushRange(data, (u32) size);
    switch (layer) {
        case LAYER_MAIN_BG1:
            func_02113088(data, (u32) offset, (u32) size);
            break;
        case LAYER_MAIN_BG2:
            GX_LoadBG2Scr(data, (u32) offset, (u32) size);
            break;
        case LAYER_MAIN_BG3:
            func_02112ee8(data, (u32) offset, (u32) size);
            break;
        case LAYER_SUB_BG0:
            func_021130f0(data, (u32) offset, (u32) size);
            break;
        case LAYER_SUB_BG1:
            func_02113020(data, (u32) offset, (u32) size);
            break;
        case LAYER_SUB_BG2:
            func_02112f50(data, (u32) offset, (u32) size);
            break;
        case LAYER_SUB_BG3:
            func_02112e80(data, (u32) offset, (u32) size);
            break;
    }
    return 1;
}
CLEAN_AS(func_02002b40, DisplayLayer_LoadScreen)

/* func_02002bd0: load 16-colour palettes `first` to `last` of a layer's screen, from `data`
 * holding the palettes from `data_first` on; returns 1.
 * QUIRK: for the backgrounds, a load starting at palette 0 leaves out its colour 0, the
 * backdrop. */
int DisplayLayer_LoadPalettes(u8 *data, unsigned int layer, int data_first, int first, u8 last)
{
    u8 *src = data + (first - data_first) * PALETTE_SIZE;
    int size = (last - first + 1) * PALETTE_SIZE;
    int offset = first * PALETTE_SIZE;

    DC_FlushRange(src, (u32) size);
    if (layer == LAYER_MAIN_OBJ) {
        GX_LoadOBJPltt(src, (u32) offset, (u32) size);
    } else if (layer == LAYER_SUB_OBJ) {
        GXS_LoadOBJPltt(src, (u32) offset, (u32) size);
    } else if (layer <= LAYER_SUB_BG3) {
        if (offset == 0) {
            offset = sizeof(u16);
            size -= sizeof(u16);
            src += sizeof(u16);
        }
        if (layer <= LAYER_MAIN_BG3) {
            GX_LoadBGPltt(src, (u32) offset, (u32) size);
        } else {
            GXS_LoadBGPltt(src, (u32) offset, (u32) size);
        }
    }
    return 1;
}
CLEAN_AS(func_02002bd0, DisplayLayer_LoadPalettes)

/* func_02002c4c: as DisplayLayer_LoadCharsFromFile, counting in 256-colour characters. */
int DisplayLayer_LoadChars256FromFile(const char *path, Heap *heap, int layer, int file_first, int first, int last)
{
    return DisplayLayer_LoadCharsFromFile(path, heap, layer, file_first * 2, first * 2, last * 2 + 1);
}
CLEAN_AS(func_02002c4c, DisplayLayer_LoadChars256FromFile)

/* The file loads at the end of `heap` and is freed after the upload.
 * QUIRK: in each ...FromFile function a file that fails to load is not noticed: the upload
 * reads from the offset it computes from address 0, and Heap_Free is given NULL. */

/* func_02002c6c: load characters `first` to `last` of a layer from the file at `path`, whose
 * first character is number `file_first`; returns 1. */
int DisplayLayer_LoadCharsFromFile(const char *path, Heap *heap, int layer, int file_first, int first, int last)
{
    u32 file_size;
    void *data = RomFile_Load(path, heap, ALIGN_BACK, &file_size);
    int result = DisplayLayer_LoadChars((u32) data, layer, (u32) file_first, (u32) first, (u32) last);

    Heap_Free(heap, data);
    return result;
}
CLEAN_AS(func_02002c6c, DisplayLayer_LoadCharsFromFile)

/* func_02002ca4: load the whole file at `path` as a background layer's screen; returns 1. */
int DisplayLayer_LoadScreenFromFile(const char *path, Heap *heap, int layer)
{
    u32 file_size;
    void *data = RomFile_Load(path, heap, ALIGN_BACK, &file_size);
    int result = DisplayLayer_LoadScreen(data, layer, (int) file_size, 0);

    Heap_Free(heap, data);
    return result;
}
CLEAN_AS(func_02002ca4, DisplayLayer_LoadScreenFromFile)

/* func_02002cd8: load palette `file_palette` of the file at `path` as a layer's palette
 * `palette`; returns 1. */
int DisplayLayer_LoadPaletteFromFile(const char *path, Heap *heap, int layer, int file_palette, u8 palette)
{
    u32 file_size;
    u8 *data = RomFile_Load(path, heap, ALIGN_BACK, &file_size);
    int result =
        DisplayLayer_LoadPalettes(data + file_palette * PALETTE_SIZE, (unsigned int) layer, palette, palette, palette);

    Heap_Free(heap, data);
    return result;
}
CLEAN_AS(func_02002cd8, DisplayLayer_LoadPaletteFromFile)

/* func_02002d14: load palettes `first` to `last` of a layer from the file at `path`, whose
 * first palette is number `file_first`; returns 1. */
int DisplayLayer_LoadPalettesFromFile(const char *path, Heap *heap, int layer, int file_first, u8 first, u8 last)
{
    u8 *data = RomFile_Load(path, heap, ALIGN_BACK, NULL);
    int result = DisplayLayer_LoadPalettes(data, (unsigned int) layer, file_first, first, last);

    Heap_Free(heap, data);
    return result;
}
CLEAN_AS(func_02002d14, DisplayLayer_LoadPalettesFromFile)

/* func_02002d50: the layer's bit in its screen's plane masks.
 * QUIRK: a number that is no layer gives 1. */
u8 DisplayLayer_PlaneMask(unsigned int layer)
{
    return layer < LAYER_COUNT ? layer_planes[layer] : 1;
}
CLEAN_AS(func_02002d50, DisplayLayer_PlaneMask)

/* func_02002d8c: the same as an int. */
int DisplayLayer_PlaneMaskInt(unsigned int layer)
{
    return layer < LAYER_COUNT ? layer_planes[layer] : 1;
}
CLEAN_AS(func_02002d8c, DisplayLayer_PlaneMaskInt)

/* func_02002dc8: the layer's plane number in its screen (backgrounds 0-3, the OBJ 4); 0 for
 * a number that is no layer. */
int DisplayLayer_PlaneNumber(unsigned int layer)
{
    return layer < LAYER_COUNT ? layer_plane_numbers[layer] : 0;
}
CLEAN_AS(func_02002dc8, DisplayLayer_PlaneNumber)

/* func_02002e04 */
int DisplayLayer_IsMainScreen(unsigned int layer)
{
    return is_main_screen(layer);
}
CLEAN_AS(func_02002e04, DisplayLayer_IsMainScreen)
