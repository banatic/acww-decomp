/* The letter view of main and its text lines (letter_view.h). */
#include "letter_view.h"

#include <stdint.h>

#include "autoload_2/heap.h"
#include "clean.h"
#include "main/display_layers.h"
#include "main/text_base.h"
#include "main/text_draw.h"
#include "main/text_string.h"
#include "ov002/paper.h"

static_assert(offsetof(LetterLine, text) == 0x12, "line characters");
static_assert(offsetof(LetterLine, box) == 0x64, "line box");
static_assert(offsetof(LetterLine, mark_first) == 0x6d, "line mark");
static_assert(offsetof(LetterLine, name_count) == 0x71, "line name mark");
static_assert(sizeof(LetterLine) == 0x74, "line size");
static_assert(offsetof(LetterWideText, text) == 0x0e, "wide text characters");
static_assert(sizeof(LetterWideText) == 0x60, "wide text size");
static_assert(offsetof(LetterView, body) == 0xe8, "view body");
static_assert(offsetof(LetterView, name) == 0x2b8, "view name");
static_assert(offsetof(LetterView, line_start) == 0x308, "view line starts");
static_assert(offsetof(LetterView, end_line) == 0x31c, "view end line");
static_assert(offsetof(LetterView, name_width) == 0x324, "view name width");
static_assert(sizeof(LetterView) == 0x328, "view size");
static_assert(offsetof(LetterViewLetter, greeting) == 0x44, "letter greeting");
static_assert(offsetof(LetterViewLetter, body) == 0x58, "letter body");
static_assert(offsetof(LetterViewLetter, signature) == 0xd8, "letter signature");
static_assert(offsetof(LetterViewLetter, name_position) == 0xf8, "letter name position");
static_assert(sizeof(LetterViewLetter) == 0x100, "letter size");

extern const TextVtable data_020df258; /* the line's vtable */
extern const TextVtable data_020df270; /* the wide text's vtable */
extern const char data_020df280[];     /* "menu/letter/b_ltr_a_bg.bsc" */
extern Heap *data_021fbe94;            /* the heap the screen file is read with */

/* The line's own functions next to these (main): clear the text and the marks (marking the line
 * dirty), set the marks, and set the text from a wide text. */
extern void func_0206db74(LetterLine *line);
extern void func_0206db50(LetterLine *line, u8 first, u8 count);
extern void func_0206db5c(LetterLine *line, u8 first, u8 count, int style);
extern void func_0206dba8(LetterLine *line, LetterWideText *text, int end_code);
extern void func_0206dbc0(LetterLine *line, LetterWideText *text);

/* The line's constructor and destructor, as the game hands them to the array helpers. */
extern void func_0206dd8c(void *line);
extern void func_0206dd6c(void *line);
extern void __cxa_vec_ctor(void *array, int count, int size, void (*construct)(void *), void (*destruct)(void *));
extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));

extern int func_02065f4c(const LetterViewLetter *letter, u16 *name); /* the addressee's name */
extern u8 func_02066648(const LetterViewLetter *letter);             /* the letter's paper */
extern int func_02051c8c_unk(u16 *text, int max);                    /* the characters before a 0, at most max */

/* The colours of a line's marks (text, background). */
#define MARK_COLOR 0xe
#define MARK_BACKGROUND 0xd
#define MARK_STYLED_COLOR 0xb
#define MARK_STYLED_BACKGROUND 0
#define NAME_COLOR 12
#define NAME_BACKGROUND 0

/* The first tile of each line's box. */
#define GREETING_FIRST_TILE 0x75
#define SIGNATURE_FIRST_TILE 0x180
#define BODY_FIRST_TILE 0x9d
#define BODY_TILES_PER_LINE (LETTER_LINE_CELLS * LETTER_LINE_ROWS)

/* How the body is broken: lines of at most 40 characters and 160 pixels. */
#define BODY_MAX_CHARS 40
#define BODY_WIDTH 160

typedef int LetterLineBuffer(int line);

/* ---- The wide text (its constructor and destructor are inline in the view's functions) */

static void wide_construct(LetterWideText *text)
{
    TextBase_WideConstruct(text);
    text->vtable = &data_020df270;
}

static void wide_destruct(LetterWideText *text)
{
    text->vtable = &data_020df270;
    TextBase_WideDestruct(text);
}

/* ---- A line */

/* func_0206dbd8: when the text changed, the box opened (if it can be) and given the text, put
 * against the right edge when `align_right` is set, and asked to redraw. */
void LetterLine_Show(LetterLine *line, int align_right)
{
    if (!line->dirty) {
        return;
    }
    LetterLine_OpenBox(line);
    if (line->box == NULL) {
        return;
    }
    line->dirty = 0;
    LetterLineBuffer *buffer = (LetterLineBuffer *) (uintptr_t) line->vtable->buffer;
    line->box->base.text = (const char *) (uintptr_t) buffer((int) (uintptr_t) line);
    if (align_right) {
        TextDraw_AlignRight(&line->box->base);
    }
    TextDraw_RequestDraw(&line->box->base);
}
CLEAN_AS(func_0206dbd8, LetterLine_Show)

/* func_0206dc1c: unless open, the box allocated in the line's VRAM tiles and set up: the
 * layer's background, its screen, colour 15 on 0, and the line's two marks. */
void LetterLine_OpenBox(LetterLine *line)
{
    if (line->box != NULL) {
        return;
    }
    line->box = LabelBox_NewInVram(line->first_tile, LETTER_LINE_CELLS, LETTER_LINE_ROWS);
    if (line->box == NULL) {
        return;
    }
    TextDrawBox *box = &line->box->base;
    box->layer = line->plane;
    box->screens = line->on_sub ? TEXT_DRAW_TO_SUB : TEXT_DRAW_TO_MAIN;
    box->rows_full_width = 0;
    box->background = 0;
    box->color = 0xf;

    int color = line->mark_style ? MARK_STYLED_COLOR : MARK_COLOR;
    int background = line->mark_style ? MARK_STYLED_BACKGROUND : MARK_BACKGROUND;
    if (line->mark_count != 0) {
        if (line->name_count != 0) {
            TextDraw_SetMarks(box, (u8) color, (u8) background, line->mark_first, line->mark_count, NAME_COLOR,
                              NAME_BACKGROUND, line->name_first, line->name_count);
        } else {
            TextDraw_SetMark(box, (u8) color, (u8) background, line->mark_first, line->mark_count);
        }
    } else if (line->name_count != 0) {
        TextDraw_SetMark(box, NAME_COLOR, NAME_BACKGROUND, line->name_first, line->name_count);
    }
}
CLEAN_AS(func_0206dc1c, LetterLine_OpenBox)

/* func_0206dcec: the box freed, if open. */
void LetterLine_CloseBox(LetterLine *line)
{
    if (line->box != NULL) {
        LabelBox_Free(line->box);
        line->box = NULL;
    }
}
CLEAN_AS(func_0206dcec, LetterLine_CloseBox)

/* func_0206dd04 (vtable entry 3): the address of the characters. */
int LetterLine_Buffer(int line)
{
    return (int) ((u32) line + offsetof(LetterLine, text));
}
CLEAN_AS(func_0206dd04, LetterLine_Buffer)

/* func_0206dd08: the box's first tile and the layer it shows on; the text not changed. */
void LetterLine_Place(LetterLine *line, unsigned short first_tile, int layer)
{
    line->first_tile = first_tile;
    line->dirty = 0;
    line->on_sub = !DisplayLayer_IsMainScreen((unsigned int) layer);
    line->plane = (u8) DisplayLayer_PlaneNumber((unsigned int) layer);
}
CLEAN_AS(func_0206dd08, LetterLine_Place)

/* func_0206dd44 (vtable entry 2) */
int LetterLine_Capacity(void)
{
    return LETTER_LINE_CAPACITY;
}
CLEAN_AS(func_0206dd44, LetterLine_Capacity)

/* func_0206dd48 (vtable entry 1) */
LetterLine *LetterLine_DestructDelete(LetterLine *line)
{
    line->vtable = &data_020df258;
    LetterLine_CloseBox(line);
    TextBase_Destruct((TextBase *) (void *) line);
    Heap_OperatorDeleteB(line);
    return line;
}
CLEAN_AS(func_0206dd48, LetterLine_DestructDelete)

/* func_0206dd6c (vtable entry 0): the box freed, then the base. */
LetterLine *LetterLine_Destruct(LetterLine *line)
{
    line->vtable = &data_020df258;
    LetterLine_CloseBox(line);
    TextBase_Destruct((TextBase *) (void *) line);
    return line;
}
CLEAN_AS(func_0206dd6c, LetterLine_Destruct)

/* func_0206dd8c: an empty line without a box or marks. QUIRK: the layer, `dirty` and
 * `mark_style` are left as they were. */
LetterLine *LetterLine_Construct(LetterLine *line)
{
    TextBase_Construct(line);
    line->vtable = &data_020df258;
    TextBase_Clear(line);
    line->box = NULL;
    line->first_tile = 0;
    line->mark_first = 0;
    line->mark_count = 0;
    line->name_first = 0;
    line->name_count = 0;
    return line;
}
CLEAN_AS(func_0206dd8c, LetterLine_Construct)

/* func_0206ddcc (the wide text's vtable entry 3): the address of the characters. */
int LetterWideText_Buffer(int text)
{
    return (int) ((u32) text + offsetof(LetterWideText, text));
}
CLEAN_AS(func_0206ddcc, LetterWideText_Buffer)

/* func_0206ddd0 (the wide text's vtable entry 2) */
int LetterWideText_Capacity(void)
{
    return LETTER_WIDE_CAPACITY;
}
CLEAN_AS(func_0206ddd0, LetterWideText_Capacity)

/* ---- The view */

/* func_0206ddd4: every changed line shown; the signature against the right edge. */
void LetterView_ShowLines(LetterView *view)
{
    LetterLine_Show(&view->greeting, 0);
    LetterLine_Show(&view->signature, 1);
    for (int i = 0; i < LETTER_VIEW_BODY_LINES; i++) {
        LetterLine_Show(&view->body[i], 0);
    }
}
CLEAN_AS(func_0206ddd4, LetterView_ShowLines)

/* func_0206de0c: every line's box freed. */
void LetterView_FreeBoxes(LetterView *view)
{
    LetterLine_CloseBox(&view->greeting);
    LetterLine_CloseBox(&view->signature);
    for (int i = 0; i < LETTER_VIEW_BODY_LINES; i++) {
        LetterLine_CloseBox(&view->body[i]);
    }
}
CLEAN_AS(func_0206de0c, LetterView_FreeBoxes)

/* func_0206de38: the body line that holds character `position`: the first of the lines ended
 * before the body's end whose next line starts after it; else the line after them, at most the
 * last. */
int LetterView_LineOf(LetterView *view, int position)
{
    int ended = view->end_line;
    for (int i = 0; i < ended; i++) {
        if (position < view->line_start[i + 1]) {
            return i;
        }
    }
    return ended < LETTER_VIEW_BODY_LINES ? ended : LETTER_VIEW_BODY_LINES - 1;
}
CLEAN_AS(func_0206de38, LetterView_LineOf)

/* func_0206de70 */
unsigned int LetterView_EndLine(LetterView *view)
{
    return (unsigned int) view->end_line;
}
CLEAN_AS(func_0206de70, LetterView_EndLine)

/* func_0206de7c: where each body line starts, then where the last one ends. */
s32 *LetterView_LineStarts(LetterView *view)
{
    return view->line_start;
}
CLEAN_AS(func_0206de7c, LetterView_LineStarts)

/* func_0206de88: `length` characters of `text` broken into `lines` lines of at most `max_chars`
 * characters and `width` pixels (a newline ends a line and stays on it). `line_start` gets where
 * each line starts and, after them, where the last ends; `end_line` counts the lines that ended
 * before the text did (full, too wide or by a newline). 1 when the whole text fits: every
 * character was placed, or a 0 ends the text where the lines stop. 0 when it does not, or when
 * the last line ends with a newline (the text would go on to a line more); `end_line` then does
 * not count that line. */
int LetterView_BreakLines(const u16 *text, s32 *line_start, s32 *end_line, int length, int max_chars, int width, int lines)
{
    int start = 0;
    int line;
    *end_line = 0;
    for (line = 0; line < lines; line++) {
        int count;
        if (max_chars > length - start) {
            max_chars = length - start;
        }
        int found = TextString_FitLine(text + start, max_chars, width, &count, 1);
        line_start[line] = start;
        start += count;
        if (found != TEXT_LINE_ENDED) {
            if (found == TEXT_LINE_NEWLINE && line == lines - 1) {
                line_start[line + 1] = start;
                return 0;
            }
            (*end_line)++;
        }
    }
    line_start[line] = start;
    return start == length || text[start] == 0;
}
CLEAN_AS(func_0206de88, LetterView_BreakLines)

/* func_0206df1c: the body's 64 characters broken into the view's four lines. The view itself is
 * not used. QUIRK: the ROM's code leaves LetterView_BreakLines's result in r0. */
void LetterView_BreakBody(LetterView *view, const u16 *body, s32 *line_start, s32 *end_line)
{
    (void) view;
    LetterView_BreakLines(body, line_start, end_line, LETTER_BODY_LENGTH, BODY_MAX_CHARS, BODY_WIDTH, LETTER_VIEW_BODY_LINES);
}
CLEAN_AS(func_0206df1c, LetterView_BreakBody)

/* func_0206df40: mark `count` characters of the signature from `first` (both their low byte). */
void LetterView_MarkSignature(LetterView *view, int first, int count, int style)
{
    func_0206db5c(&view->signature, (u8) first, (u8) count, style);
}
CLEAN_AS(func_0206df40, LetterView_MarkSignature)

/* func_0206df58: mark `count` characters of the body from `first`, on each line they cover: the
 * part on the line where `first` falls, then on with the next lines while some are left. A line
 * of no characters ends the search.
 * QUIRK: past the first line marked, `first` becomes the next line's start in its low byte. */
void LetterView_MarkBody(LetterView *view, unsigned int first, unsigned int count, int style)
{
    unsigned int line_first = 0;
    for (int i = 0; i < LETTER_VIEW_BODY_LINES; i++) {
        unsigned int length = (unsigned int) (view->line_start[i + 1] - view->line_start[i]);
        if (length == 0) {
            break;
        }
        unsigned int line_end = line_first + length;
        if (first >= line_first && first < line_end) {
            unsigned int marked;
            if (line_end > first + count) {
                marked = count;
            } else {
                marked = length - (first - line_first);
            }
            func_0206db5c(&view->body[i], (u8) (first - line_first), (u8) marked, style);
            first = (u8) line_end;
            count -= marked;
            if (count == 0) {
                break;
            }
        }
        line_first += length;
    }
}
CLEAN_AS(func_0206df58, LetterView_MarkBody)

/* func_0206dfe0: mark `count` characters of the greeting from `first` (both their low byte). */
void LetterView_MarkGreeting(LetterView *view, int first, int count, int style)
{
    func_0206db5c(&view->greeting, (u8) first, (u8) count, style);
}
CLEAN_AS(func_0206dfe0, LetterView_MarkGreeting)

/* func_0206dff8: the signature line set from the letter's 16 characters. */
void LetterView_SetSignature(LetterView *view, const u16 *signature)
{
    LetterWideText text;
    wide_construct(&text);
    func_0206db74(&view->signature);
    TextBase_SetWide(&text, signature, LETTER_SIGNATURE_LENGTH);
    func_0206dbc0(&view->signature, &text);
    wide_destruct(&text);
}
CLEAN_AS(func_0206dff8, LetterView_SetSignature)

/* func_0206e03c: the body broken into lines and each line set from its part (cleared first).
 * While `editing`, a line is set with the end code on the line where the body ends (the end
 * line), and an empty end line gets an empty text with it; other empty lines stay cleared. */
void LetterView_SetBody(LetterView *view, const u16 *body, int editing)
{
    u16 empty[1] = {0};
    LetterWideText text;

    LetterView_BreakBody(view, body, view->line_start, &view->end_line);
    wide_construct(&text);
    for (int i = 0; i < LETTER_VIEW_BODY_LINES; i++) {
        int length = view->line_start[i + 1] - view->line_start[i];
        LetterLine *line = &view->body[i];
        func_0206db74(line);
        if (length != 0) {
            TextBase_SetWide(&text, body + view->line_start[i], length);
            if (editing) {
                func_0206dba8(line, &text, i == view->end_line);
            } else {
                func_0206dbc0(line, &text);
            }
        } else if (editing && i == view->end_line) {
            TextBase_SetWide(&text, empty, 1);
            func_0206dba8(line, &text, 1);
        } else {
            func_0206db74(line);
        }
    }
    wide_destruct(&text);
}
CLEAN_AS(func_0206e03c, LetterView_SetBody)

/* func_0206e114: the greeting line set from 40 characters: the letter's greeting characters
 * before its name position, the addressee's name, the rest of the greeting, then zeros. They are
 * also written to `out` when not NULL. The name is marked when it has characters.
 * REQUIRES: name_position <= 10 and name_position + name_length <= 40. */
void LetterView_SetGreeting(LetterView *view, const LetterViewLetter *letter, u16 *out)
{
    u16 own[LETTER_WIDE_CAPACITY];
    u16 *chars = out != NULL ? out : own;
    LetterWideText text;
    int i = 0;
    int from = 0;

    func_0206db74(&view->greeting);
    for (; i < letter->name_position; i++, from++) {
        chars[i] = letter->greeting[from];
    }
    for (int k = 0; k < view->name_length; k++, i++) {
        chars[i] = view->name[k];
    }
    for (; i < LETTER_WIDE_CAPACITY; i++, from++) {
        chars[i] = from < LETTER_GREETING_LENGTH ? letter->greeting[from] : 0;
    }
    if (view->name_length > 0) {
        func_0206db50(&view->greeting, letter->name_position, (u8) view->name_length);
    }

    wide_construct(&text);
    TextBase_SetWide(&text, chars, LETTER_WIDE_CAPACITY);
    func_0206dbc0(&view->greeting, &text);
    wide_destruct(&text);
}
CLEAN_AS(func_0206e114, LetterView_SetGreeting)

/* func_0206e1d8: the addressee's name taken from the letter, with its length and width. */
void LetterView_SetName(LetterView *view, const LetterViewLetter *letter)
{
    TextString_ClearChars(view->name, LETTER_VIEW_NAME_LENGTH);
    func_02065f4c(letter, view->name);
    view->name_length = func_02051c8c_unk(view->name, LETTER_VIEW_NAME_LENGTH);
    view->name_width = TextString_Width(view->name, LETTER_VIEW_NAME_LENGTH);
}
CLEAN_AS(func_0206e1d8, LetterView_SetName)

/* func_0206e224 */
unsigned int LetterView_NameLength(LetterView *view)
{
    return (unsigned int) view->name_length;
}
CLEAN_AS(func_0206e224, LetterView_NameLength)

/* func_0206e230: a letter shown for reading: its paper on `paper_layer` (priority 1), its text on
 * `text_layer` (at `priority`), both hidden while they are set up and scrolled to 0. */
void LetterView_Show(LetterView *view, const LetterViewLetter *letter, int text_layer, int paper_layer, int priority)
{
    DisplayLayer_Hide((unsigned int) paper_layer);
    DisplayLayer_SetPriority(paper_layer, 1);
    DisplayLayer_SetBgControl((unsigned int) paper_layer, 0, 0, 0);
    Paper_LoadBackground(func_02066648(letter), paper_layer);
    DisplayLayer_SetScroll((unsigned int) paper_layer, 0, 0);

    DisplayLayer_Hide((unsigned int) text_layer);
    DisplayLayer_SetPriority(text_layer, priority);
    DisplayLayer_SetBgControl((unsigned int) text_layer, 0, 0, 0);
    LetterView_SetName(view, letter);
    LetterView_SetGreeting(view, letter, NULL);
    LetterView_SetBody(view, letter->body, 0);
    LetterView_SetSignature(view, letter->signature);
    LetterView_LoadScreen(view, text_layer);
    LetterView_Redraw(view);
    DisplayLayer_SetScroll((unsigned int) text_layer, 0, 0);
}
CLEAN_AS(func_0206e230, LetterView_Show)

/* func_0206e2d0: every box freed, then the changed lines shown in new ones. */
void LetterView_Redraw(LetterView *view)
{
    LetterView_FreeBoxes(view);
    LetterView_ShowLines(view);
}
CLEAN_AS(func_0206e2d0, LetterView_Redraw)

/* func_0206e2e4 */
void LetterView_ReleaseBoxes(LetterView *view)
{
    LetterView_FreeBoxes(view);
}
CLEAN_AS(func_0206e2e4, LetterView_ReleaseBoxes)

/* func_0206e2ec: every line placed on `layer` at its tiles; no name. */
void LetterView_Init(LetterView *view, int layer)
{
    LetterLine_Place(&view->greeting, GREETING_FIRST_TILE, layer);
    LetterLine_Place(&view->signature, SIGNATURE_FIRST_TILE, layer);
    for (int i = 0; i < LETTER_VIEW_BODY_LINES; i++) {
        LetterLine_Place(&view->body[i], (unsigned short) (BODY_FIRST_TILE + i * BODY_TILES_PER_LINE), layer);
    }
    view->name_length = 0;
}
CLEAN_AS(func_0206e2ec, LetterView_Init)

/* func_0206e344: the text layer's screen loaded from its file. The view is not used. */
void LetterView_LoadScreen(LetterView *view, int layer)
{
    (void) view;
    DisplayLayer_LoadScreenFromFile(data_020df280, data_021fbe94, layer);
}
CLEAN_AS(func_0206e344, LetterView_LoadScreen)

/* func_0206e35c: the destructor: the body lines, then the signature and the greeting. */
LetterView *LetterView_Destruct(LetterView *view)
{
    __cxa_vec_cleanup(view->body, LETTER_VIEW_BODY_LINES, sizeof(LetterLine), func_0206dd6c);
    LetterLine_Destruct(&view->signature);
    LetterLine_Destruct(&view->greeting);
    return view;
}
CLEAN_AS(func_0206e35c, LetterView_Destruct)

/* func_0206e388: the constructor. */
LetterView *LetterView_Construct(LetterView *view)
{
    LetterLine_Construct(&view->greeting);
    LetterLine_Construct(&view->signature);
    __cxa_vec_ctor(view->body, LETTER_VIEW_BODY_LINES, sizeof(LetterLine), func_0206dd8c, func_0206dd6c);
    return view;
}
CLEAN_AS(func_0206e388, LetterView_Construct)
