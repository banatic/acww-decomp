/* The 2D layers by number: showing and hiding them, their scrolling, background control and
 * priority, and loading their characters, screens and palettes into VRAM, from memory or from
 * a file. The main screen's background 0 shows the 3D and has no number. */
#ifndef CLEAN_MAIN_DISPLAY_LAYERS_H
#define CLEAN_MAIN_DISPLAY_LAYERS_H

#include "autoload_2/heap.h"
#include "types.h"

enum DisplayLayer {
    LAYER_MAIN_BG1 = 0,
    LAYER_MAIN_BG2 = 1,
    LAYER_MAIN_BG3 = 2,
    LAYER_SUB_BG0 = 3,
    LAYER_SUB_BG1 = 4,
    LAYER_SUB_BG2 = 5,
    LAYER_SUB_BG3 = 6,
    LAYER_MAIN_OBJ = 7,
    LAYER_SUB_OBJ = 8
};

void DisplayLayer_Show(unsigned int layer);
void DisplayLayer_Hide(unsigned int layer);
void DisplayLayer_HideAndResetScroll(int layer);
void DisplayLayer_SetScroll(unsigned int layer, int x, int y);
void DisplayLayer_SetBgControl(unsigned int layer, int size, int colors_256, int char_base);
void DisplayLayer_SetPriority(int layer, int priority);
int DisplayLayer_LoadChars(u32 data, int layer, u32 data_first, u32 first, u32 last);
int DisplayLayer_LoadScreen(void *data, int layer, int size, int offset);
int DisplayLayer_LoadPalettes(u8 *data, unsigned int layer, int data_first, int first, u8 last);
int DisplayLayer_LoadChars256FromFile(const char *path, Heap *heap, int layer, int file_first, int first, int last);
int DisplayLayer_LoadCharsFromFile(const char *path, Heap *heap, int layer, int file_first, int first, int last);
int DisplayLayer_LoadScreenFromFile(const char *path, Heap *heap, int layer);
int DisplayLayer_LoadPaletteFromFile(const char *path, Heap *heap, int layer, int file_palette, u8 palette);
int DisplayLayer_LoadPalettesFromFile(const char *path, Heap *heap, int layer, int file_first, u8 first, u8 last);
u8 DisplayLayer_PlaneMask(unsigned int layer);
int DisplayLayer_PlaneMaskInt(unsigned int layer);
int DisplayLayer_PlaneNumber(unsigned int layer);
int DisplayLayer_IsMainScreen(unsigned int layer);

#endif
