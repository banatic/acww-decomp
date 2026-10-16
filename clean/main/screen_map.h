/* Background screen maps: 32 entries a row, each a 16-bit entry whose top four bits are its
 * palette and whose low twelve bits are the tile and its flips. The helpers here change the
 * palette of the entries in a rectangle and number the cells of a character sheet. */
#ifndef CLEAN_MAIN_SCREEN_MAP_H
#define CLEAN_MAIN_SCREEN_MAP_H

#include "types.h"

#define SCREEN_MAP_WIDTH 32

void ScreenMap_ReplacePalette(u16 *map, int left, int top, int right, int bottom, u32 from, u32 to);
void ScreenMap_SetPalette(u16 *map, int left, int top, int right, int bottom, u32 palette);
int ScreenMap_CellTile(int cell);

#endif
