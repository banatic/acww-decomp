/* Converting 16-colour images between character and bitmap order (tile_convert.h).
 *
 * An image is `width` characters wide and `height` characters tall. In character order its
 * characters follow each other row by row; in bitmap order its pixel lines do. A sheet is an
 * image in character order 32 characters wide, of which a part is converted, starting at
 * character `first` of its first row. */
#include "tile_convert.h"

#include "clean.h"

#define CHAR_LINES 8   /* lines in a character, words in character order */
#define SHEET_WIDTH 32 /* characters in a sheet's row */

extern void MI_CpuCopy8(const void *src, void *dst, u32 size);

/* The index of line `line` of character (`col`, `row`) of an image `width` characters wide
 * in character order. */
static int char_line(int width, int col, int row, int line)
{
    return (row * width + col) * CHAR_LINES + line;
}

/* func_020024f0 */
void TileConvert_CharsToBitmap(u32 *chars, u32 *bitmap, int width, int height)
{
    int out = 0;

    for (int row = 0; row < height; row++) {
        for (int line = 0; line < CHAR_LINES; line++) {
            for (int col = 0; col < width; col++) {
                bitmap[out++] = chars[char_line(width, col, row, line)];
            }
        }
    }
}
CLEAN_AS(func_020024f0, TileConvert_CharsToBitmap)

/* func_0200255c */
void TileConvert_BitmapToChars(u32 *bitmap, u32 *chars, int width, int height)
{
    int in = 0;

    for (int row = 0; row < height; row++) {
        for (int line = 0; line < CHAR_LINES; line++) {
            for (int col = 0; col < width; col++) {
                chars[char_line(width, col, row, line)] = bitmap[in++];
            }
        }
    }
}
CLEAN_AS(func_0200255c, TileConvert_BitmapToChars)

/* func_020025c4 */
void TileConvert_BitmapToSheet(u32 *bitmap, u32 *sheet, int first, int width, int height)
{
    int in = 0;

    for (int row = 0; row < height; row++) {
        for (int line = 0; line < CHAR_LINES; line++) {
            for (int col = 0; col < width; col++) {
                sheet[char_line(SHEET_WIDTH, first + col, row, line)] = bitmap[in++];
            }
        }
    }
}
CLEAN_AS(func_020025c4, TileConvert_BitmapToSheet)

/* func_02002628 */
void TileConvert_SheetToBitmap(u32 *sheet, u32 *bitmap, int first, int width, int height)
{
    int out = 0;

    for (int row = 0; row < height; row++) {
        for (int line = 0; line < CHAR_LINES; line++) {
            for (int col = 0; col < width; col++) {
                bitmap[out++] = sheet[char_line(SHEET_WIDTH, first + col, row, line)];
            }
        }
    }
}
CLEAN_AS(func_02002628, TileConvert_SheetToBitmap)

/* func_0200268c: as TileConvert_BitmapToChars on bytes, one MI_CpuCopy8 of 4 bytes per
 * character line, in character order. */
void TileConvert_BitmapToCharsBytes(u8 *bitmap, u8 *chars, int width, int height)
{
    int out = 0;

    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            for (int line = 0; line < CHAR_LINES; line++) {
                int in = ((row * CHAR_LINES + line) * width + col) * 4;
                MI_CpuCopy8(bitmap + in, chars + out, 4);
                out += 4;
            }
        }
    }
}
CLEAN_AS(func_0200268c, TileConvert_BitmapToCharsBytes)
