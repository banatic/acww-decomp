/* The design editor's drawing (design_editor_canvas.h): the design's 32x32 pixels of four bits,
 * eight to a word and four words to a row (the low nibble is the leftmost pixel), and the tools
 * that paint them: pens of three sizes, two stamps, lines, rectangles, ellipses, a flood fill,
 * a pattern and a clear. */
#include "design_editor_canvas.h"

#include <stdint.h>

#include "clean.h"
#include "design_editor.h"
#include "main/tile_convert.h"

/* The two stamps: sixteen rows of sixteen bits, the top bit leftmost. */
extern const u16 *const data_ov123_0229cf8c[2];

/* The pattern of DESIGN_EDITOR_TOOL_PATTERN: two words for each of sixteen rows (for the
 * left and the right half of the design's 32 rows, twice), a nibble 1 where it paints. */
extern const u32 data_ov123_0229cb2c[32];

/* A sine table in 1/256 (cos(a) at a + 0x40), 0x40 steps for a quarter turn. */
extern const u16 data_ov123_0229cbac[];

/* The flood fill's queue of runs to look from, a function-local static: its guard (bit 0) is
 * set on the first use, and `mask` (0x3f) wraps the queue's indices. */
typedef struct DesignEditorRun {
    u8 left;
    u8 right;
    u8 y;
    u8 unused;
} DesignEditorRun;
extern u32 data_ov123_0229d2e4;
extern DesignEditorRun data_ov123_0229d3b4[];
extern const int data_ov123_0229ce2c;

/* A word of the current pixels' row `py`. */
static u32 *de_row(DesignEditor *self, int py)
{
    return DesignEditor_Pixels(self) + py * 4;
}

/* func_ov123_0229a5cc: stamp `stamp` (0 or 1) put down in `colour` with its pixel (7, 8) at
 * (px, py); every set bit paints one pixel (DesignEditor_SetPixel drops those outside). */
void DesignEditor_Stamp(DesignEditor *self, int px, int py, int colour, int stamp)
{
    const u16 *rows = data_ov123_0229cf8c[stamp];
    int y = py - 8;
    for (int row = 0; row < 16; row++) {
        unsigned int mask = 0x8000;
        int x = px - 7;
        for (int column = 0; column < 16; column++) {
            if (mask & rows[row]) {
                DesignEditor_SetPixel(self, (u8) x, (u8) y, colour);
            }
            mask >>= 1;
            x++;
        }
        y++;
    }
}
CLEAN_AS(func_ov123_0229a5cc, DesignEditor_Stamp)

/* func_ov123_0229a63c: a word of pixels with the nibbles that are 1 in `mask` set to
 * `colour`. */
unsigned int DesignEditor_PaintWord(unsigned int unused, unsigned int word, unsigned int mask, unsigned int colour)
{
    (void) unused;
    return (word & ~(mask * 15)) | (mask * colour);
}
CLEAN_AS(func_ov123_0229a63c, DesignEditor_PaintWord)

/* func_ov123_0229a654: a flood fill of the pixels of (px, py)'s colour that touch it, with
 * `colour`, nothing when it already has that colour. The fill takes runs of a row from its
 * queue: a run whose left pixel already has the new colour is skipped; else it is stretched
 * left and right over the old colour, painted, and every run of the old colour in the rows
 * above and below between its ends is queued.
 * QUIRK: the queue holds 64 runs and wraps without a check; a design whose fill queues more
 * at once overwrites the oldest. */
void DesignEditor_Fill(DesignEditor *self, u8 px, u8 py, int colour)
{
    DesignEditor_Pixels(self);
    int old = DesignEditor_PixelAt(self, px, py);
    if (old == colour) {
        return;
    }
    if ((data_ov123_0229d2e4 & 1) == 0) {
        data_ov123_0229d2e4 |= 1;
    }
    int head = 0;
    int tail = 1;
    data_ov123_0229d3b4[0].left = px;
    data_ov123_0229d3b4[0].right = px;
    data_ov123_0229d3b4[0].y = py;
    int mask = data_ov123_0229ce2c;
    do {
        int x = data_ov123_0229d3b4[head].left;
        int right_end = data_ov123_0229d3b4[head].right;
        int y = data_ov123_0229d3b4[head].y;
        head = (head + 1) & mask;
        if (colour == DesignEditor_PixelAt(self, (u8) x, (u8) y)) {
            continue;
        }
        int left = DesignEditor_RunLeft(self, x, y, old);
        int right = DesignEditor_RunRight(self, right_end, y, old);
        for (int i = left; i <= right; i++) {
            DesignEditor_SetPixel(self, (u8) i, (u8) y, colour);
        }
        /* the rows above and below, in that order */
        for (int side = 0; side < 2; side++) {
            int row;
            if (side == 0) {
                if (y <= 0) {
                    continue;
                }
                row = y - 1;
            } else {
                if (y >= 0x1f) {
                    continue;
                }
                row = y + 1;
            }
            int at = left;
            do {
                int start = DesignEditor_FindInRow(self, at, right, row, old);
                if (start < 0) {
                    at = 0xff;
                } else {
                    int end = DesignEditor_RunRight(self, start, row, old);
                    data_ov123_0229d3b4[tail].left = (u8) start;
                    data_ov123_0229d3b4[tail].right = (u8) end;
                    data_ov123_0229d3b4[tail].y = (u8) row;
                    tail = (tail + 1) & mask;
                    at = end + 2;
                }
            } while (at <= right);
        }
    } while (head != tail);
}
CLEAN_AS(func_ov123_0229a654, DesignEditor_Fill)

/* func_ov123_0229a7d4: the last x of row `py` from px on whose pixels have `colour`, going
 * right: px when the next one differs, 31 at the end of the row (and for px 31 or more). */
int DesignEditor_RunRight(DesignEditor *self, int px, int py, int colour)
{
    if (px >= 31) {
        return 31;
    }
    int x = px + 1;
    const u32 *word = de_row(self, py) + (x >> 3);
    int shift = (x & 7) * 4;
    while (x <= 31) {
        if (colour != (int) ((*word >> shift) & 0xf)) {
            return x - 1;
        }
        shift += 4;
        if (shift > 28) {
            shift = 0;
            word++;
        }
        x++;
    }
    return 31;
}
CLEAN_AS(func_ov123_0229a7d4, DesignEditor_RunRight)

/* func_ov123_0229a82c: the first x of row `py` up to px whose pixels have `colour`, going
 * left: px when the one before differs, 0 at the start of the row (and for px 0 or less). */
int DesignEditor_RunLeft(DesignEditor *self, int px, int py, int colour)
{
    if (px <= 0) {
        return 0;
    }
    int x = px - 1;
    const u32 *word = de_row(self, py) + (x >> 3);
    int shift = (x & 7) * 4;
    while (x >= 0) {
        if (colour != (int) ((*word >> shift) & 0xf)) {
            return x + 1;
        }
        shift -= 4;
        if (shift < 0) {
            shift = 28;
            word--;
        }
        x--;
    }
    return 0;
}
CLEAN_AS(func_ov123_0229a82c, DesignEditor_RunLeft)

/* func_ov123_0229a884: the first x from `left` to `right` of row `py` whose pixel has
 * `colour`, or -1. */
int DesignEditor_FindInRow(DesignEditor *self, int left, int right, int py, int colour)
{
    const u32 *word = de_row(self, py) + (left >> 3);
    int shift = (left & 7) * 4;
    for (int x = left; x <= right; x++) {
        if (colour == (int) ((*word >> shift) & 0xf)) {
            return x;
        }
        shift += 4;
        if (shift >= 32) {
            shift = 0;
            word++;
        }
    }
    return -1;
}
CLEAN_AS(func_ov123_0229a884, DesignEditor_FindInRow)

/* func_ov123_0229a8dc: the colour of pixel (px, py); 1 outside the design. */
unsigned char DesignEditor_PixelAt(DesignEditor *self, unsigned int px, unsigned int py)
{
    if (px >= DESIGN_EDITOR_SIZE || py >= DESIGN_EDITOR_SIZE) {
        return 1;
    }
    const u32 *row = de_row(self, (int) py);
    return (unsigned char) ((row[px >> 3] >> ((px & 7) * 4)) & 0xf);
}
CLEAN_AS(func_ov123_0229a8dc, DesignEditor_PixelAt)

/* func_ov123_0229a918: the whole design painted with `colour` through the pattern, its sixteen
 * rows twice, each row's two words for the left half and again for the right. */
void DesignEditor_PaintPattern(DesignEditor *self, int colour)
{
    u32 *p = DesignEditor_Pixels(self);
    for (int pass = 0; pass < 2; pass++) {
        const u32 *q = data_ov123_0229cb2c;
        for (int row = 0; row < 16; row++) {
            p[0] = DesignEditor_PaintWord((unsigned int) (uintptr_t) self, p[0], q[0], (unsigned int) colour);
            p[1] = DesignEditor_PaintWord((unsigned int) (uintptr_t) self, p[1], q[1], (unsigned int) colour);
            p[2] = DesignEditor_PaintWord((unsigned int) (uintptr_t) self, p[2], q[0], (unsigned int) colour);
            p[3] = DesignEditor_PaintWord((unsigned int) (uintptr_t) self, p[3], q[1], (unsigned int) colour);
            p += 4;
            q += 2;
        }
    }
}
CLEAN_AS(func_ov123_0229a918, DesignEditor_PaintPattern)

/* func_ov123_0229a988: every pixel of the design `colour` (its low four bits repeated in each
 * nibble). */
void DesignEditor_Clear(DesignEditor *self, int colour)
{
    u32 *p = DesignEditor_Pixels(self);
    u32 word = (u32) colour * 0x11111111u;
    for (int row = 0; row < DESIGN_EDITOR_SIZE; row++) {
        p[0] = word;
        p[1] = word;
        p[2] = word;
        p[3] = word;
        p += 4;
    }
}
CLEAN_AS(func_ov123_0229a988, DesignEditor_Clear)

/* func_ov123_0229a9b0: an ellipse in `colour` inside the box from (left, top) to (right,
 * bottom): from the angle 0 to a quarter turn in steps that shrink with its size, the four
 * points of each angle (`filled` 0), or the two rows between them (else). An even width or
 * height puts the right or lower points one further. */
void DesignEditor_Ellipse(DesignEditor *self, int left, int top, int right, unsigned char bottom, int colour, int filled)
{
    int width = right - left;
    int height = bottom - top;
    int half_w = width >> 1;
    int half_h = height >> 1;
    int cx = left + half_w;
    int cy = top + half_h;
    int diff = half_w - half_h;
    if (diff < 0) {
        diff = -diff;
    }
    int sum = half_w + half_h;
    /* about the quarter's length in pixels, odd */
    int length = sum - (((sum >> 1) - (sum >> 3)) - (diff >> 1) - 5);
    int step = 0x40 / (short) (length | 1);
    int odd_h = height & 1;
    int odd_w = width & 1;
    for (int angle = 0; angle < 0x40; angle = (short) (angle + step)) {
        int dx = (data_ov123_0229cbac[angle + 0x40] * half_w + 0x2d) >> 8;
        int dy = (data_ov123_0229cbac[angle] * half_h + 0x2d) >> 8;
        if (filled != 0) {
            int upper = cy - dy;
            int lower = odd_h + (cy + dy);
            int end = odd_w + (cx + dx);
            for (int x = cx - dx; x <= end; x++) {
                DesignEditor_SetPixel(self, (u8) x, (u8) upper, colour);
                DesignEditor_SetPixel(self, (u8) x, (u8) lower, colour);
            }
        } else {
            int x_right = odd_w + (cx + dx);
            int y_lower = odd_h + (cy + dy);
            DesignEditor_SetPixel(self, (u8) x_right, (u8) y_lower, colour);
            int y_upper = cy - dy;
            DesignEditor_SetPixel(self, (u8) x_right, (u8) y_upper, colour);
            int x_left = cx - dx;
            DesignEditor_SetPixel(self, (u8) x_left, (u8) y_lower, colour);
            DesignEditor_SetPixel(self, (u8) x_left, (u8) y_upper, colour);
        }
    }
}
CLEAN_AS(func_ov123_0229a9b0, DesignEditor_Ellipse)

/* func_ov123_0229ab18: a rectangle's outline in `colour` from (left, top) to (right, bottom):
 * the top and bottom rows, then the left and right columns.
 * The matching source declares the first parameter (the editor) unsigned char; the ROM's code
 * passes it on whole, as this does. */
void DesignEditor_Rectangle(DesignEditor *self, unsigned char left, unsigned char top, unsigned int right, unsigned int bottom,
                            int colour)
{
    for (u8 x = left; x <= right; x++) {
        DesignEditor_SetPixel(self, x, top, colour);
        DesignEditor_SetPixel(self, x, (int) bottom, colour);
    }
    for (u8 y = top; y <= bottom; y++) {
        DesignEditor_SetPixel(self, left, y, colour);
        DesignEditor_SetPixel(self, (int) right, y, colour);
    }
}
CLEAN_AS(func_ov123_0229ab18, DesignEditor_Rectangle)

/* func_ov123_0229ab80: a line from (x0, y0) to (x1, y1) by Bresenham's steps, each point
 * painted with DesignEditor_PaintBrush (`brush` the tool, 3 for preview dots). Answers 1 when
 * any pixel changed. */
int DesignEditor_Line(DesignEditor *self, unsigned int x0, unsigned int y0, unsigned int x1, unsigned char y1, int colour,
                      int brush)
{
    int changed = 0;
    unsigned int x = x0;
    unsigned int y = y0;
    int step_x;
    int dx;
    if (x1 > x) {
        step_x = 1;
        dx = (int) (x1 - x);
    } else {
        step_x = -1;
        dx = (int) (x - x1);
    }
    int step_y;
    int dy;
    if (y1 > y) {
        step_y = 1;
        dy = (int) (y1 - y);
    } else {
        step_y = -1;
        dy = (int) (y - y1);
    }
    if (dx >= dy) {
        int error = -dx;
        for (int i = 0; i <= dx; i++) {
            changed |= DesignEditor_PaintBrush(self, (u8) x, (u8) y, colour, brush, 0);
            x += (unsigned int) step_x;
            error += dy * 2;
            if (error >= 0) {
                y += (unsigned int) step_y;
                error -= dx * 2;
            }
        }
    } else {
        int error = -dy;
        for (int i = 0; i <= dy; i++) {
            changed |= DesignEditor_PaintBrush(self, (u8) x, (u8) y, colour, brush, 0);
            y += (unsigned int) step_y;
            error += dx * 2;
            if (error >= 0) {
                x += (unsigned int) step_x;
                error -= dy * 2;
            }
        }
    }
    return changed;
}
CLEAN_AS(func_ov123_0229ab80, DesignEditor_Line)

/* func_ov123_0229ac80: one dab of a brush at (px, py): pen 1 the pixel; pen 2 it and the ones
 * left, above and up-left; pen 3 the nine around it, row by row; 3 only a preview dot
 * (DESIGN_EDITOR_TOOL_DOTS). Answers 1 when a pixel changed; 0 for any other brush. The last
 * parameter is not read. */
int DesignEditor_PaintBrush(DesignEditor *self, u8 px, u8 py, int colour, int brush, int unused)
{
    (void) unused;
    int changed = 0;
    if (brush < 0 || brush > 3) {
        return 0;
    }
    u8 left = (u8) (px - 1);
    u8 right = (u8) (px + 1);
    u8 up = (u8) (py - 1);
    u8 down = (u8) (py + 1);
    switch (brush) {
        case DESIGN_EDITOR_TOOL_PEN_1:
            changed |= DesignEditor_SetPixel(self, px, py, colour);
            break;
        case DESIGN_EDITOR_TOOL_PEN_2:
            changed |= DesignEditor_SetPixel(self, px, py, colour);
            changed |= DesignEditor_SetPixel(self, left, py, colour);
            changed |= DesignEditor_SetPixel(self, px, up, colour);
            changed |= DesignEditor_SetPixel(self, left, up, colour);
            break;
        case DESIGN_EDITOR_TOOL_PEN_3:
            changed |= DesignEditor_SetPixel(self, left, up, colour);
            changed |= DesignEditor_SetPixel(self, px, up, colour);
            changed |= DesignEditor_SetPixel(self, right, up, colour);
            changed |= DesignEditor_SetPixel(self, left, py, colour);
            changed |= DesignEditor_SetPixel(self, px, py, colour);
            changed |= DesignEditor_SetPixel(self, right, py, colour);
            changed |= DesignEditor_SetPixel(self, left, down, colour);
            changed |= DesignEditor_SetPixel(self, px, down, colour);
            changed |= DesignEditor_SetPixel(self, right, down, colour);
            break;
        case DESIGN_EDITOR_TOOL_DOTS:
            DesignEditor_DrawPreviewDot(self, px, py);
            break;
    }
    return changed;
}
CLEAN_AS(func_ov123_0229ac80, DesignEditor_PaintBrush)

/* func_ov123_0229adc8: pixel (px, py) set to `colour`; answers 1 when it changed, 0 when it
 * already had it or is outside the design. The word is written twice: cleared, then or-ed.
 * QUIRK: `colour` is not masked; one above 15 also sets bits of the pixels to its right. */
int DesignEditor_SetPixel(DesignEditor *self, int px, int py, int colour)
{
    if ((unsigned int) px >= DESIGN_EDITOR_SIZE || (unsigned int) py >= DESIGN_EDITOR_SIZE) {
        return 0;
    }
    u32 *row = DesignEditor_Pixels(self) + py * 4;
    int shift = (px & 7) * 4;
    u32 *word = &row[px >> 3];
    u32 mask = 0xfu << shift;
    u32 data = *word;
    if (((data & mask) >> shift) == (u32) colour) {
        return 0;
    }
    *word = data & ~mask;
    *word |= (u32) colour << shift;
    return 1;
}
CLEAN_AS(func_ov123_0229adc8, DesignEditor_SetPixel)

/* func_ov123_0229b228: the pixels four times bigger (each one 4x4 in a 128x128 bitmap at
 * `zoomed`), then made 16x16 characters at `zoomed_chars`. */
void DesignEditor_ZoomPixels(DesignEditor *self)
{
    const u32 *src = DesignEditor_Pixels(self);
    u32 *dst = self->zoomed;
    for (int y = 0; y < DESIGN_EDITOR_SIZE; y++) {
        for (int word = 0; word < 4; word++) {
            int shift = 0;
            for (int pair = 0; pair < 4; pair++) {
                u32 a = (*src >> shift) & 0xf;
                u32 b = (*src >> (shift + 4)) & 0xf;
                shift += 8;
                u32 value = (b << 28) | (b << 24) | (b << 20) | (b << 16) | (a << 12) | (a << 8) | (a << 4) | a;
                /* the same word in the four rows of the bigger bitmap (16 words a row) */
                for (int row = 0; row < 4; row++) {
                    dst[word * 4 + pair + row * 0x10] = value;
                }
            }
            src++;
        }
        dst += 0x40;
    }
    TileConvert_BitmapToChars(self->zoomed, self->zoomed_chars, 0x10, 0x10);
}
CLEAN_AS(func_ov123_0229b228, DesignEditor_ZoomPixels)

/* func_ov123_0229b364: the current pixels made 4x4 characters at `chars`. */
void DesignEditor_MakeChars(DesignEditor *self)
{
    TileConvert_BitmapToChars(DesignEditor_Pixels(self), self->chars, 4, 4);
}
CLEAN_AS(func_ov123_0229b364, DesignEditor_MakeChars)
