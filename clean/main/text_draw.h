/* Drawing the text boxes: a box's text, rendered glyph by glyph in a font (text_font.h), into
 * graphics tiles of VRAM or of a buffer in RAM.
 *
 * A box (TextDrawBox, 0x7c bytes, class data_020dcf28: its constructors are in text_box.h) is
 * `cells` 8-pixel tiles wide and `rows` tiles high. Its text is drawn one strip of 8 pixel rows
 * at a time (TextDraw_Draw): the strip is cleared to the background colour in the 32-tile buffer
 * data_021c8344 (4 bits per pixel), the derived class's layout (vtable slot 2) calls
 * TextDraw_DrawChar for each character, and the strip is sent to its destination
 * (TextDraw_UploadStrip): the tiles of BG0-BG3 or of the objects on the main screen, the sub
 * screen or both (through GX_Load...Char, from `first_tile` on), or a buffer in RAM.
 *
 * Two ranges of characters (by their index in the text) can be marked with colours of their
 * own; the gap left between glyphs is painted with the mark's background too.
 *
 * Boxes are allocated in an expanded heap of 0x1800 bytes (data_021c8194) and kept in a list
 * (data_021c81bc). A box asked to redraw or to clear (TextDraw_RequestDraw, TextDraw_RequestClear)
 * does it at once when its update mode is 2, else when its group is flushed: group 1 every frame
 * by the process that owns the fonts and the heap (vtable data_020dcf40, profile data_020dcf18),
 * group 0 by func_0206e5fc. */
#ifndef CLEAN_MAIN_TEXT_DRAW_H
#define CLEAN_MAIN_TEXT_DRAW_H

#include "text_font.h"
#include "types.h"

/* Where a box's strips go (TextDrawBox.screens). */
enum TextDrawScreens {
    TEXT_DRAW_TO_RAM = 0,  /* copied to `ram_dest` */
    TEXT_DRAW_TO_SUB = 1,  /* the sub screen's tiles */
    TEXT_DRAW_TO_MAIN = 2, /* the main screen's tiles */
    TEXT_DRAW_TO_BOTH = 3,
};

/* When a box's requests are carried out (TextDrawBox.update_mode). */
enum TextDrawUpdate {
    TEXT_DRAW_GROUP_0 = 0, /* when func_02050e68 flushes group 0 */
    TEXT_DRAW_GROUP_1 = 1, /* each frame, by the text process */
    TEXT_DRAW_AT_ONCE = 2,
};

/* A marked range of characters and its colours. */
typedef struct TextDrawMarkColors {
    u8 color;
    u8 background;
} TextDrawMarkColors;

typedef struct TextDrawMarkRange {
    u32 first; /* the index of its first character */
    u32 count;
} TextDrawMarkRange;

typedef struct TextDrawBox {
    const u32 *vtable; /* slot 2: draw a strip; slot 3: measure the text, in pixels */
    u32 unk_04;
    u32 link[2];      /* 0x08: in the list of boxes */
    const char *text; /* 0x10 */
    u32 unk_14;
    s32 first_tile;                    /* 0x18: the first VRAM tile, or -1 */
    u32 ram_dest;                      /* 0x1c: the RAM the strips go to (TEXT_DRAW_TO_RAM) */
    u32 cells;                         /* 0x20: width in tiles */
    u32 rows;                          /* 0x24: height in tiles */
    TextFont *font;                    /* 0x28 */
    s32 layer;                         /* 0x2c: 0-3 BG0-BG3, 4 objects (the GX_Load...Char tables' index) */
    u32 offset;                        /* 0x30: where the text starts, in pixels */
    u32 spacing;                       /* 0x34: pixels between glyphs */
    u8 color;                          /* 0x38: the text's colour */
    u8 background;                     /* 0x39 */
    TextDrawMarkColors mark_colors[2]; /* 0x3a */
    u8 pad_3e[2];
    TextDrawMarkRange marks[2]; /* 0x40 */
    u32 screens;                /* 0x50: TextDrawScreens */
    u8 pending;                 /* 0x54: a redraw was asked for */
    u8 rows_full_width;         /* 0x55: the destination's rows are 32 tiles apart */
    u8 merge;                   /* 0x56: in RAM, only the destination's background is replaced */
    u8 underline;               /* 0x57 */
    u32 update_mode;            /* 0x58: TextDrawUpdate */
    s32 clear_cells;            /* 0x5c: a clear asked for, of this many tiles (0: all); -1 none */
    u32 row_bytes;              /* 0x60: 32 bytes per tile */
    s32 glyph;                  /* 0x64: the glyph being drawn */
    u32 pen;                    /* 0x68: x of the next glyph, in pixels */
    u32 strip_y;                /* 0x6c: the first pixel row of the strip */
    u32 dest_offset;            /* 0x70: the strip's offset in the destination, in bytes */
    u8 start_color;             /* 0x74: the colour each strip starts with */
    u8 last_strip;              /* 0x75 */
    u8 pad_76[2];
    u32 char_index; /* 0x78: of the character being drawn */
} TextDrawBox;

void TextDraw_FreeBoxes(void);
void TextDraw_FlushGroup0(void);
unsigned char TextDraw_BackgroundColor(TextDrawBox *box);
unsigned char TextDraw_TextColor(TextDrawBox *box);
int TextDraw_InMark2(TextDrawBox *box);
int TextDraw_InMark1(TextDrawBox *box);
void TextDraw_ClearRows(TextDrawBox *box);
void TextDraw_Underline(TextDrawBox *box, unsigned int start);
void TextDraw_FillSpacing(TextDrawBox *box);
u32 TextDraw_DrawGlyph(TextDrawBox *box);
void TextDraw_UploadStrip(TextDrawBox *box);
void TextDraw_DrawChar(TextDrawBox *box, int code);
void TextDraw_BeginStrip(TextDrawBox *box);
void TextDraw_Draw(TextDrawBox *box);
void TextDraw_Flush(int update_mode);
void TextDraw_FillBackground(TextDrawBox *box);
void TextDraw_ReleaseBoxes(void);
void TextDraw_FlushGroup1(void);
void TextDraw_Shutdown(void);
void TextDraw_Init(void);
void TextDraw_EndMeasureStrip(void);
void TextDraw_MeasureChar(TextDrawBox *box, int code);
void TextDraw_BeginMeasure(TextDrawBox *box);
unsigned int TextDraw_WidthInCells(TextDrawBox *box);
void TextDraw_SetMarks(TextDrawBox *box, unsigned char color_1, unsigned char background_1, unsigned int first_1,
                       unsigned int count_1, unsigned char color_2, unsigned char background_2, unsigned int first_2,
                       unsigned int count_2);
void TextDraw_SetMark(TextDrawBox *box, unsigned char color, unsigned char background, int first, int count);
void TextDraw_AlignRight(TextDrawBox *box);
void TextDraw_Center(TextDrawBox *box);
void TextDraw_RequestClear(TextDrawBox *box, int cells);
void TextDraw_RequestDraw(TextDrawBox *box);
int TextDraw_ProcessDelete(void);
int TextDraw_ProcessExecute(void);
int TextDraw_ProcessCreate(void);
void *TextDraw_ProcessDestructFree(void *process);
void *TextDraw_ProcessDestruct(void *process);
void *TextDraw_ProcessConstruct(void *process);
void TextDraw_ProcessNew(void);

#endif
