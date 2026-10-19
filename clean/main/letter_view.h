/* The letter view of main: a letter's text shown on a 2D layer, over its paper on another
 * layer. Overlay 96 (the pockets screen) uses one to read a letter, overlay 122 to write one,
 * marking ranges of the text while it is edited.
 *
 * The view (0x328 bytes) holds six text lines, each a class of its own on the 8-bit text base
 * (text_base.h; vtable data_020df258, 0x74 bytes) that draws through a text box of 20 x 2 tiles
 * (LabelBox_NewInVram) on the view's layer:
 *
 *   - the greeting (tiles 0x75 on): the letter's ten greeting characters with the addressee's
 *     name put in at the letter's name position, the name marked in its own colour;
 *   - the signature (tiles 0x180 on), drawn against the right edge;
 *   - four lines of the body (tiles 0x9d, 0xc5, 0xed and 0x115 on): the body's 64 characters
 *     broken into lines of at most 40 characters and 160 pixels (LetterView_BreakLines).
 *
 * The text layer's screen comes from "menu/letter/b_ltr_a_bg.bsc"; the paper's picture is loaded
 * by Paper_LoadBackground (ov002/paper.h).
 *
 * A line keeps one marked range (`mark_first`, `mark_count`, in colour 14 on 13, or 11 on 0
 * when `mark_style` is set) and, on the greeting, the name's range (colour 12 on 0). Changing a
 * line sets `dirty`; LetterLine_Show then opens its box if needed and asks for a redraw.
 *
 * A wide text class of 40 characters (vtable data_020df270, 0x60 bytes) carries the 16-bit
 * characters into a line (TextBase_WideToBytes). */
#ifndef CLEAN_MAIN_LETTER_VIEW_H
#define CLEAN_MAIN_LETTER_VIEW_H

#include "main/label_box.h"
#include "main/letter.h"
#include "main/text_label.h"
#include "types.h"

#define LETTER_LINE_CAPACITY 82 /* 8-bit characters */
#define LETTER_LINE_CELLS 20    /* the box's width, in tiles */
#define LETTER_LINE_ROWS 2      /* and its height */
#define LETTER_WIDE_CAPACITY 40 /* 16-bit characters of the wide text */

#define LETTER_VIEW_BODY_LINES 4
#define LETTER_VIEW_NAME_LENGTH 40
#define LETTER_GREETING_LENGTH 10
#define LETTER_BODY_LENGTH 64
#define LETTER_SIGNATURE_LENGTH 16

/* One line of the view. Before `box` it is the 8-bit text base's layout, with its characters at
 * 0x12 (the class's buffer). */
typedef struct LetterLine {
    const TextVtable *vtable; /* 0x00: data_020df258 */
    u32 length;               /* 0x04: the text base's */
    u8 attributes[0x0a];      /* 0x08: the text base's */
    char text[LETTER_LINE_CAPACITY];
    LabelBox *box;  /* 0x64: or NULL while closed */
    u16 first_tile; /* 0x68 */
    u8 plane;       /* 0x6a: the layer's background number */
    u8 on_sub;      /* 0x6b: the layer is on the sub screen */
    u8 dirty;       /* 0x6c: the text changed since it was last shown */
    u8 mark_first;  /* 0x6d */
    u8 mark_count;  /* 0x6e: 0 for no mark */
    u8 mark_style;  /* 0x6f */
    u8 name_first;  /* 0x70 */
    u8 name_count;  /* 0x71: 0 for no name mark */
    u8 pad_72[2];
} LetterLine;

/* The wide text a line is set from. */
typedef struct LetterWideText {
    const TextVtable *vtable; /* data_020df270 */
    u8 attributes[0x0a];      /* 0x04: the wide text base's */
    u16 text[LETTER_WIDE_CAPACITY];
    u8 pad_5e[2];
} LetterWideText;

typedef struct LetterView {
    LetterLine greeting;                        /* 0x000 */
    LetterLine signature;                       /* 0x074 */
    LetterLine body[LETTER_VIEW_BODY_LINES];    /* 0x0e8 */
    u16 name[LETTER_VIEW_NAME_LENGTH];          /* 0x2b8: the addressee's name */
    s32 line_start[LETTER_VIEW_BODY_LINES + 1]; /* 0x308: where each body line starts, then the end */
    s32 end_line;                               /* 0x31c: the lines ended before the body's end */
    s32 name_length;                            /* 0x320: in characters */
    s32 name_width;                             /* 0x324: in pixels */
} LetterView;

void LetterLine_Show(LetterLine *line, int align_right);
void LetterLine_OpenBox(LetterLine *line);
void LetterLine_CloseBox(LetterLine *line);
int LetterLine_Buffer(int line);
void LetterLine_Place(LetterLine *line, unsigned short first_tile, int layer);
int LetterLine_Capacity(void);
LetterLine *LetterLine_DestructDelete(LetterLine *line);
LetterLine *LetterLine_Destruct(LetterLine *line);
LetterLine *LetterLine_Construct(LetterLine *line);
int LetterWideText_Buffer(int text);
int LetterWideText_Capacity(void);

void LetterView_ShowLines(LetterView *view);
void LetterView_FreeBoxes(LetterView *view);
int LetterView_LineOf(LetterView *view, int position);
unsigned int LetterView_EndLine(LetterView *view);
s32 *LetterView_LineStarts(LetterView *view);
int LetterView_BreakLines(const u16 *text, s32 *line_start, s32 *end_line, int length, int max_chars, int width, int lines);
void LetterView_BreakBody(LetterView *view, const u16 *body, s32 *line_start, s32 *end_line);
void LetterView_MarkSignature(LetterView *view, int first, int count, int style);
void LetterView_MarkBody(LetterView *view, unsigned int first, unsigned int count, int style);
void LetterView_MarkGreeting(LetterView *view, int first, int count, int style);
void LetterView_SetSignature(LetterView *view, const u16 *signature);
void LetterView_SetBody(LetterView *view, const u16 *body, int editing);
void LetterView_SetGreeting(LetterView *view, const Letter *letter, u16 *out);
void LetterView_SetName(LetterView *view, const Letter *letter);
unsigned int LetterView_NameLength(LetterView *view);
void LetterView_Show(LetterView *view, const Letter *letter, int text_layer, int paper_layer, int priority);
void LetterView_Redraw(LetterView *view);
void LetterView_ReleaseBoxes(LetterView *view);
void LetterView_Init(LetterView *view, int layer);
void LetterView_LoadScreen(LetterView *view, int layer);
LetterView *LetterView_Destruct(LetterView *view);
LetterView *LetterView_Construct(LetterView *view);

/* The wide text's destructors, and the line's marks and text (its own functions before
 * LetterLine_Show). */
LetterWideText *LetterWideText_Destruct(LetterWideText *text);
LetterWideText *LetterWideText_Delete(LetterWideText *text);
void LetterLine_SetNameMark(LetterLine *line, char first, char count);
void LetterLine_SetMark(LetterLine *line, char first, char count, char style);
void LetterLine_Clear(LetterLine *line);
void LetterLine_SetTextWithEnd(LetterLine *line, LetterWideText *text, int end_code);
void LetterLine_SetText(LetterLine *line, LetterWideText *text);

#endif
