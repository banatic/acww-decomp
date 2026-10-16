/* HBlank functions of line handlers (line_effects.h). */
#include "line_effects.h"

#include <assert.h>
#include <stddef.h>
#include <stdint.h>

#include "clean.h"

static_assert(offsetof(LineGradient, top_color) == 0x304, "the top colour");
static_assert(offsetof(LineGradient, bottom_color) == 0x306, "the bottom colour");
static_assert(sizeof(LineAffine) == 12, "a line's affine parameters");
static_assert(offsetof(LineLayers, affine) == 0x8, "the affine tables");
static_assert(offsetof(LineLayers, blend_alpha) == 0x1210, "the blending tables");
static_assert(offsetof(LineShiftOwner, shift_index) == 0x51c, "the shift's index");

#define REG16(address) (*(volatile u16 *) (address))
#define REG32(address) (*(volatile u32 *) (address))
#define REG_DISPCNT REG32(0x04000000)
#define REG_DISPSTAT REG16(0x04000004)
#define REG_VCOUNT REG16(0x04000006)
#define REG_BG3PA REG16(0x04000030)
#define REG_BG3X REG32(0x04000038)
#define REG_BG3Y REG32(0x0400003c)
#define REG_WIN1H REG16(0x04000042)
#define REG_BLDCNT REG16(0x04000050)
#define REG_BLDALPHA REG16(0x04000052)
#define REG_DB_DISPCNT REG32(0x04001000)
#define REG_DB_BG3PA REG16(0x04001030)
#define REG_DB_BG3X REG32(0x04001038)
#define REG_DB_BG3Y REG32(0x0400103c)
#define REG_DB_BLDCNT REG16(0x04001050)
#define REG_DB_BLDALPHA REG16(0x04001052)
#define REG_BACKDROP REG16(0x05000000)    /* the main screen's palette colour 0 */
#define REG_DB_BACKDROP REG16(0x05000400) /* the sub screen's */

#define DISPSTAT_IN_HBLANK 0x0002
#define DISPCNT_BG1 0x0200
#define DISPCNT_BG3 0x0800
/* BLDCNT: alpha blending of nothing, or of background 3, over the backdrop */
#define BLEND_NONE_OVER_BACKDROP 0x2040
#define BLEND_BG3_OVER_BACKDROP 0x2048

/* The lines from which the gradient screen hides background 1, and background 3 too. */
#define LINE_HIDE_BG1 0x97
#define LINE_HIDE_BG3 0xa8

/* The edge of window 1: the line in the pattern (data_027e0434) and the left edges of the
 * pattern's first half (data_027e0438, filled by the game); both in the DTCM. */
extern u8 data_027e0434;
extern u8 data_027e0438[];
#define EDGE_HALF 24

extern LineGradient data_021f6f70;
extern LineLayers data_021f75b0;
extern LineShiftOwner data_021f85b0;
extern u32 data_021f8ac4[];

/* The entry `set`, `line` of a table of two sets: the address is computed as the ARM does, in
 * 32 bits, whatever the indices. */
static uintptr_t entry(const void *table, u32 set, u32 set_size, int line, u32 line_size)
{
    return (uintptr_t) table + set * set_size + (u32) line * line_size;
}

/* func_01ffccf4: window 1's left edge for the next line, from a pattern of 48 lines whose
 * second half mirrors the first; the window reaches the right edge of the screen. The edge is
 * written only while the HBlank lasts; the pattern moves on a line in any case.
 * QUIRK: a pattern line above 47 (never set) reads before the table and is brought back by 48
 * only once.
 * HW: DISPSTAT is read before WIN1H is written. */
void LineFx_Window1Edge(void)
{
    u32 line = data_027e0434;
    u32 index = line >= EDGE_HALF ? 2 * EDGE_HALF - 1 - line : line;
    u8 left = *(const u8 *) ((uintptr_t) data_027e0438 + index);
    if (REG_DISPSTAT & DISPSTAT_IN_HBLANK) {
        REG_WIN1H = (u16) ((left << 8) | 0xff);
    }
    line++;
    if (line >= 2 * EDGE_HALF) {
        line -= 2 * EDGE_HALF;
    }
    data_027e0434 = (u8) line;
}
CLEAN_AS(func_01ffccf4, LineFx_Window1Edge)

/* func_01ffcd4c: an HBlank function that does nothing (set by func_020ba518). */
void LineFx_Nothing(void) {}
CLEAN_AS(func_01ffcd4c, LineFx_Nothing)

/* The line about to be drawn, from VCOUNT and the shift, at most the last line.
 * REQUIRES: the shift keeps the line from being negative; a negative one is used as it is. */
static int gradient_line(void)
{
    u32 shift = *(const u32 *) ((uintptr_t) data_021f8ac4 + data_021f85b0.shift_index * 4);
    int line = (int) (REG_VCOUNT + shift);
    return line >= SCREEN_LINES ? SCREEN_LINES - 1 : line;
}

static u16 gradient_color(int line)
{
    return *(const u16 *) entry(data_021f6f70.colors, data_021f6f70.shown, sizeof(data_021f6f70.colors[0]), line, 2);
}

static const LineAffine *line_affine(int line)
{
    return (const LineAffine *) entry(data_021f75b0.affine, data_021f75b0.shown, sizeof(data_021f75b0.affine[0]), line,
                                      sizeof(LineAffine));
}

static u16 line_blend_alpha(int line)
{
    return *(const u16 *) entry(data_021f75b0.blend_alpha, data_021f75b0.shown, sizeof(data_021f75b0.blend_alpha[0]), line, 2);
}

/* func_01ffcd50: the gradient screen's HBlank function on the main screen. The sub screen's
 * backdrop is set to the gradient's top colour on each line.
 * HW: VCOUNT is read first; then the sub screen's backdrop, the main backdrop, BG3PA, BG3X,
 * BG3Y, DISPCNT (read and written) with BLDCNT, and BLDALPHA are written in this order. */
void LineFx_GradientMain(void)
{
    int line = gradient_line();
    REG_DB_BACKDROP = data_021f6f70.top_color;
    REG_BACKDROP = gradient_color(line);
    const LineAffine *affine = line_affine(line);
    REG_BG3PA = (u16) affine->scale_x;
    REG_BG3X = (u32) affine->x;
    REG_BG3Y = (u32) affine->y;
    if (line >= LINE_HIDE_BG3) {
        REG_DISPCNT &= ~(u32) (DISPCNT_BG1 | DISPCNT_BG3);
        REG_BLDCNT = BLEND_NONE_OVER_BACKDROP;
    } else if (line >= LINE_HIDE_BG1) {
        REG_DISPCNT &= ~(u32) DISPCNT_BG1;
        REG_BLDCNT = BLEND_BG3_OVER_BACKDROP;
    }
    REG_BLDALPHA = line_blend_alpha(line);
}
CLEAN_AS(func_01ffcd50, LineFx_GradientMain)

/* func_01ffceb8: the gradient screen's HBlank function on the sub screen. The main screen's
 * backdrop is set to the gradient's bottom colour on each line.
 * QUIRK: background 3's X and Y are written with their low 16 bits only (the main screen's get
 * all 32), and only background 1 is hidden near the bottom.
 * HW: VCOUNT is read first; then the sub screen's backdrop, the main backdrop, DB_BG3PA,
 * DB_BG3X, DB_BG3Y, DB_DISPCNT (read and written) with DB_BLDCNT, and DB_BLDALPHA are written in
 * this order. */
void LineFx_GradientSub(void)
{
    int line = gradient_line();
    REG_DB_BACKDROP = gradient_color(line);
    REG_BACKDROP = data_021f6f70.bottom_color;
    const LineAffine *affine = line_affine(line);
    REG_DB_BG3PA = (u16) affine->scale_x;
    REG_DB_BG3X = (u16) affine->x;
    REG_DB_BG3Y = (u16) affine->y;
    if (line >= LINE_HIDE_BG1) {
        REG_DB_DISPCNT &= ~(u32) DISPCNT_BG1;
        REG_DB_BLDCNT = BLEND_BG3_OVER_BACKDROP;
    }
    REG_DB_BLDALPHA = line_blend_alpha(line);
}
CLEAN_AS(func_01ffceb8, LineFx_GradientSub)
