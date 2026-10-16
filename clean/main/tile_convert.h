/* Converting 16-colour images between character order (each 8x8 character's 8 lines of 4
 * bytes in a row) and bitmap order (whole pixel lines). One u32 is one character line. */
#ifndef CLEAN_MAIN_TILE_CONVERT_H
#define CLEAN_MAIN_TILE_CONVERT_H

#include "types.h"

void TileConvert_CharsToBitmap(u32 *chars, u32 *bitmap, int width, int height);
void TileConvert_BitmapToChars(u32 *bitmap, u32 *chars, int width, int height);
void TileConvert_BitmapToSheet(u32 *bitmap, u32 *sheet, int first, int width, int height);
void TileConvert_SheetToBitmap(u32 *sheet, u32 *bitmap, int first, int width, int height);
void TileConvert_BitmapToCharsBytes(u8 *bitmap, u8 *chars, int width, int height);

#endif
