/* HBlank functions of line handlers (interrupts.h): each changes display registers for the
 * line about to be drawn.
 *
 * The gradient screen (set up by func_020ba540 on either screen) colours the backdrop of each
 * line from a gradient between two colours (func_020bb090 computes it into the table not
 * shown, then shows it), and moves background 3 (its affine X, Y and horizontal scale) and the
 * blending of each line from tables of their own, also two of each. Near the bottom it hides
 * background 1, on the main screen background 3 too. A shift of the lines read
 * (data_021f8ac4) is added to VCOUNT. */
#ifndef CLEAN_ITCM_LINE_EFFECTS_H
#define CLEAN_ITCM_LINE_EFFECTS_H

#include "types.h"

#define SCREEN_LINES 192

/* data_021f6f70: the backdrop colours. */
typedef struct LineGradient {
    u32 shown;                   /* which of the two tables is shown */
    u16 colors[2][SCREEN_LINES]; /* 0x004 */
    u16 top_color;               /* 0x304: the colour down to `top_line` */
    u16 bottom_color;            /* 0x306: the colour from `bottom_line` on */
    int top_line;                /* 0x308 */
    int bottom_line;             /* 0x30c */
} LineGradient;

/* A line's affine parameters of background 3 (BG3X, BG3Y, BG3PA). */
typedef struct LineAffine {
    s32 x;
    s32 y;
    s16 scale_x;
    s16 unk_0A;
} LineAffine;

/* data_021f75b0: the lines' background 3 and blending. */
typedef struct LineLayers {
    u32 screen;                         /* the screen last set up (func_020ba540) */
    u32 shown;                          /* which of the two sets of tables is shown */
    LineAffine affine[2][SCREEN_LINES]; /* 0x0008 */
    u8 unk_1208[8];
    u16 blend_alpha[2][SCREEN_LINES]; /* 0x1210: BLDALPHA */
} LineLayers;

/* data_021f85b0: the object whose field picks the shift of the lines read. */
typedef struct LineShiftOwner {
    u8 unk_000[0x51c];
    u32 shift_index; /* 0x51c: an index in data_021f8ac4 */
} LineShiftOwner;

void LineFx_Window1Edge(void);
void LineFx_Nothing(void);
void LineFx_GradientMain(void);
void LineFx_GradientSub(void);

#endif
