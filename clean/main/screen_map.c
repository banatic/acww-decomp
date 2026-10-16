/* Palettes in background screen maps, and the cells of a character sheet (screen_map.h). */
#include "screen_map.h"

#include "clean.h"

#define PALETTE_SHIFT 12
#define PALETTE_MASK 0xf000
#define TILE_MASK 0x0fff

/* The palette bits of an entry with palette `palette`; only its low four bits count. */
static u32 palette_bits(u32 palette)
{
    return (palette & 0xf) << PALETTE_SHIFT;
}

/* func_0206fd60: in the rectangle of columns left-right and rows top-bottom (both ends
 * included), give the entries with palette `from` palette `to`. */
void ScreenMap_ReplacePalette(u16 *map, int left, int top, int right, int bottom, u32 from, u32 to)
{
    for (int row = top; row <= bottom; row++) {
        for (int column = left; column <= right; column++) {
            u16 *entry = &map[row * SCREEN_MAP_WIDTH + column];
            if ((*entry & PALETTE_MASK) == palette_bits(from)) {
                *entry = (u16) (palette_bits(to) | (*entry & TILE_MASK));
            }
        }
    }
}
CLEAN_AS(func_0206fd60, ScreenMap_ReplacePalette)

/* func_0206fdd4: give every entry in the rectangle (both ends included) palette `palette`. */
void ScreenMap_SetPalette(u16 *map, int left, int top, int right, int bottom, u32 palette)
{
    for (int row = top; row <= bottom; row++) {
        for (int column = left; column <= right; column++) {
            u16 *entry = &map[row * SCREEN_MAP_WIDTH + column];
            *entry = (u16) (palette_bits(palette) | (*entry & TILE_MASK));
        }
    }
}
CLEAN_AS(func_0206fdd4, ScreenMap_SetPalette)

/* func_0206fe28: the first tile of cell `cell` in a sheet of 2 x 2-tile cells laid out 16 to a
 * row, the sheet being 32 tiles wide: two tiles a column, 64 a row of cells. QUIRK: the row is
 * the cell shifted right arithmetically, so a negative cell (no caller passes one) gives a row
 * rounded towards minus infinity, as in the original. */
int ScreenMap_CellTile(int cell)
{
    return (cell & 15) * 2 + (cell >> 4) * 64;
}
CLEAN_AS(func_0206fe28, ScreenMap_CellTile)
