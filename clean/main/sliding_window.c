/* main's sliding window (sliding_window.h). */
#include "sliding_window.h"

#include "cell_anim.h"
#include "clean.h"
#include "text_string.h" /* TextString_ClearBytes */

static_assert(offsetof(SlidingWindow, state) == 0x34 && offsetof(SlidingWindow, priority) == 0x44, "SlidingWindow");
static_assert(offsetof(SlidingWindow, open_request) == 0x54 && offsetof(SlidingWindow, center_text) == 0x5c, "SlidingWindow");
static_assert(offsetof(SlidingWindow, lines) == 0x60 && offsetof(SlidingWindow, boxes) == 0xc0, "SlidingWindow");
static_assert(sizeof(SlidingWindow) == 0xcc, "SlidingWindow");

#define SCREEN_WIDTH 0x100
#define SCREEN_CENTER_X 0x80

/* The text boxes: 20 tiles wide, 2 rows, from these OBJ tiles. */
#define BOX_FIRST_TILE_0 0x41
#define BOX_FIRST_TILE_1 0x61
#define BOX_CELLS 0x14
#define BOX_ROWS 2
#define BOX_LAYER_OBJ 4
#define BOX_COLOR 3

#define OPENING_FRAMES 3
#define CLOSING_FRAMES 2

extern const CellAnimData data_020d71a4; /* the body's animation */
extern const CellAnimData data_020d71ac; /* the extra animation */
extern TextFont data_021c828c;           /* the font of a two-line window */
extern TextFont data_021c8230;           /* the font of a one-line window */

extern TextDrawBox *func_020a9034(int first_tile, int cells, int rows); /* a text box made */
extern void func_020a8fb8(TextDrawBox *box);                            /* a text box freed */
extern int func_0208aef0(SlidingWindow *window);                        /* the base class's x */
extern int func_0208aeec(SlidingWindow *window);                        /* the base class's y */

/* A line's characters, through its vtable (slot 3). */
static const char *line_chars(SlidingWindowText *line)
{
    typedef char *TextBufferMethod(SlidingWindowText * line);
    return ((TextBufferMethod *) (uintptr_t) line->vtable->buffer)(line);
}

/* A text box's text width in pixels, through its vtable (slot 3). */
static u32 box_text_width(TextDrawBox *box)
{
    typedef u32 TextMeasureMethod(TextDrawBox * box);
    return ((TextMeasureMethod *) (uintptr_t) box->vtable[3])(box);
}

/* func_0208a490: when `keep_on_screen` is set, the sideways move that brings a window that
 * would cross the screen's left or right edge back in; else none. */
void SlidingWindow_KeepOnScreen(SlidingWindow *window)
{
    if (window->keep_on_screen == 0) {
        window->screen_shift = 0;
        return;
    }
    int half_width = CellAnim_Frame(&window->body) * 4 + 0xc;
    int center = window->x + window->slide_x;
    int left = center - half_width + SCREEN_CENTER_X;
    int right_over = half_width + center - (SCREEN_WIDTH - SCREEN_CENTER_X);
    if (left < 0) {
        window->screen_shift = -left;
    } else if (right_over > 0) {
        window->screen_shift = -right_over;
    } else {
        window->screen_shift = 0;
    }
}
CLEAN_AS(func_0208a490, SlidingWindow_KeepOnScreen)

/* func_0208a4dc: the lines' text boxes freed. */
void SlidingWindow_FreeBoxes(SlidingWindow *window)
{
    if (window->boxes[0] != NULL) {
        func_020a8fb8(window->boxes[0]);
        window->boxes[0] = NULL;
    }
    if (window->boxes[1] != NULL) {
        func_020a8fb8(window->boxes[1]);
        window->boxes[1] = NULL;
    }
}
CLEAN_AS(func_0208a4dc, SlidingWindow_FreeBoxes)

/* A new box set up to show `line` in `font` among the OBJs, and asked to draw. */
static void setup_box(SlidingWindow *window, TextDrawBox *box, SlidingWindowText *line, TextFont *font)
{
    box->layer = BOX_LAYER_OBJ;
    box->text = line_chars(line);
    box->update_mode = TEXT_DRAW_GROUP_1;
    if (window->on_main != 0) {
        box->screens = TEXT_DRAW_TO_MAIN;
    }
    box->font = font;
    box->rows_full_width = 1;
    box->background = 0;
    box->color = BOX_COLOR;
    TextDraw_RequestDraw(box);
}

/* func_0208a510: the text boxes made that are missing: the first line's, and with two lines
 * the second's. */
void SlidingWindow_MakeBoxes(SlidingWindow *window)
{
    int two_lines = window->line_count == 2;
    if (window->boxes[0] == NULL) {
        window->boxes[0] = func_020a9034(BOX_FIRST_TILE_0, BOX_CELLS, BOX_ROWS);
        if (window->boxes[0] != NULL) {
            setup_box(window, window->boxes[0], &window->lines[0], two_lines ? &data_021c828c : &data_021c8230);
        }
    }
    if (window->boxes[1] == NULL && two_lines) {
        window->boxes[1] = func_020a9034(BOX_FIRST_TILE_1, BOX_CELLS, BOX_ROWS);
        if (window->boxes[1] != NULL) {
            setup_box(window, window->boxes[1], &window->lines[1], &data_021c828c);
        }
    }
}
CLEAN_AS(func_0208a510, SlidingWindow_MakeBoxes)

/* func_0208a664: both animations put on the frame that fits the wider line (one frame per
 * 8-pixel tile, within the body's frames), and the lines centred in it when `center_text` is
 * set, else started at its left. */
void SlidingWindow_FitText(SlidingWindow *window)
{
    u32 width_0 = window->boxes[0] != NULL ? box_text_width(window->boxes[0]) : 0;
    u32 width_1 = window->boxes[1] != NULL ? box_text_width(window->boxes[1]) : 0;
    u32 tiles_0 = (width_0 + 7) >> 3;
    u32 tiles_1 = (width_1 + 7) >> 3;
    int tiles = (int) (tiles_0 > tiles_1 ? tiles_0 : tiles_1);
    int last = CellAnim_Data(&window->body)->count - 1;
    int frame = tiles - 1;
    if (frame < 0) {
        frame = 0;
    } else if (frame > last) {
        frame = last;
    }
    CellAnim_SetFrame(&window->body, frame, 0);
    CellAnim_SetFrame(&window->extra, frame, 0);

    if (window->center_text != 0) {
        u32 inside = (u32) tiles << 3;
        if (window->boxes[0] != NULL) {
            window->boxes[0]->offset = inside > width_0 ? (inside - width_0) >> 1 : 0;
        }
        if (window->boxes[1] != NULL) {
            window->boxes[1]->offset = inside > width_1 ? (inside - width_1) >> 1 : 0;
        }
    } else {
        if (window->boxes[0] != NULL) {
            window->boxes[0]->offset = 0;
        }
        if (window->boxes[1] != NULL) {
            window->boxes[1]->offset = 0;
        }
    }
}
CLEAN_AS(func_0208a664, SlidingWindow_FitText)

/* An animation given its data, held still. */
static void load_anim(CellAnim *anim, const CellAnimData *data)
{
    CellAnim_SetData(anim, data);
    CellAnim_SetHold(anim, 1);
    CellAnim_SetSpeed(anim, 0);
}

/* func_0208a738: the window's two animations loaded, held still. */
void SlidingWindow_LoadAnims(SlidingWindow *window)
{
    load_anim(&window->body, &data_020d71a4);
    load_anim(&window->extra, &data_020d71ac);
}
CLEAN_AS(func_0208a738, SlidingWindow_LoadAnims)

/* func_0208a784: closed and at its place, nothing asked, the lines emptied and their boxes
 * freed. The screen (`on_main`) stays. */
void SlidingWindow_Reset(SlidingWindow *window)
{
    window->state = SLIDING_WINDOW_CLOSED;
    window->timer = 0;
    window->x = 0;
    window->y = 0;
    window->priority = -1;
    window->slide_x = 0;
    window->slide_y = 0;
    window->screen_shift = 0;
    window->open_request = 0;
    window->close_request = 0;
    window->keep_on_screen = 0;
    window->unk_58 = 0;
    window->instant = 0;
    window->slide_y_flipped = 0;
    window->show_extra = 0;
    window->center_text = 0;
    TextString_ClearBytes((TextObject *) &window->lines[0]);
    TextString_ClearBytes((TextObject *) &window->lines[1]);
    window->line_count = 0;
    SlidingWindow_FreeBoxes(window);
}
CLEAN_AS(func_0208a784, SlidingWindow_Reset)

/* func_0208a7f0: the window's width in pixels, by the body's frame. */
int SlidingWindow_Width(SlidingWindow *window)
{
    return (CellAnim_Frame(&window->body) << 3) + 0x18;
}
CLEAN_AS(func_0208a7f0, SlidingWindow_Width)

/* func_0208a804 */
int SlidingWindow_Y(SlidingWindow *window)
{
    return window->y;
}
CLEAN_AS(func_0208a804, SlidingWindow_Y)

/* func_0208a808 */
int SlidingWindow_X(SlidingWindow *window)
{
    return window->x;
}
CLEAN_AS(func_0208a808, SlidingWindow_X)

/* func_0208a80c: the y it is drawn at: the base class's, its own and the slide's. */
int SlidingWindow_DrawY(SlidingWindow *window)
{
    int base_y = func_0208aeec(window);
    return window->slide_y + window->y + base_y;
}
CLEAN_AS(func_0208a80c, SlidingWindow_DrawY)

/* func_0208a824: the x it is drawn at: the base class's, its own, the slide's and the move that
 * keeps it on the screen. */
int SlidingWindow_DrawX(SlidingWindow *window)
{
    int base_x = func_0208aef0(window);
    return window->x + base_x + window->slide_x + window->screen_shift;
}
CLEAN_AS(func_0208a824, SlidingWindow_DrawX)

/* func_0208a840 */
CellAnim *SlidingWindow_Body(SlidingWindow *window)
{
    return &window->body;
}
CLEAN_AS(func_0208a840, SlidingWindow_Body)

/* func_0208a844 */
int SlidingWindow_State(SlidingWindow *window)
{
    return (int) window->state;
}
CLEAN_AS(func_0208a844, SlidingWindow_State)

/* func_0208a848: a frame of closing: sliding away by 11 pixels in x and y, unless instant; at
 * the end the text boxes are freed and the window is closed. */
void SlidingWindow_StepClosing(SlidingWindow *window)
{
    if (window->instant == 0) {
        window->slide_x -= 11;
        window->slide_y += window->slide_y_flipped != 0 ? -11 : 11;
    }
    window->timer--;
    if (window->timer <= 0) {
        SlidingWindow_FreeBoxes(window);
        SlidingWindow_SetClosed(window);
    }
}
CLEAN_AS(func_0208a848, SlidingWindow_StepClosing)

/* func_0208a890 */
void SlidingWindow_StartClosing(SlidingWindow *window)
{
    window->timer = window->instant != 0 ? 1 : CLOSING_FRAMES;
    window->state = SLIDING_WINDOW_CLOSING;
}
CLEAN_AS(func_0208a890, SlidingWindow_StartClosing)

/* func_0208a8ac: open: closing once asked to. */
void SlidingWindow_StepOpen(SlidingWindow *window)
{
    if (window->close_request != 0) {
        window->close_request = 0;
        SlidingWindow_StartClosing(window);
    }
}
CLEAN_AS(func_0208a8ac, SlidingWindow_StepOpen)

/* func_0208a8cc */
void SlidingWindow_SetOpen(SlidingWindow *window)
{
    window->state = SLIDING_WINDOW_OPEN;
}
CLEAN_AS(func_0208a8cc, SlidingWindow_SetOpen)

/* func_0208a8d4: a frame of opening, unless instant: 6 pixels in x and y, then a pixel back on
 * each of the last two frames; at the end the slide is cleared and the window is open. */
void SlidingWindow_StepOpening(SlidingWindow *window)
{
    if (window->instant == 0) {
        if (window->timer > 2) {
            window->slide_x += 6;
            window->slide_y += window->slide_y_flipped != 0 ? 6 : -6;
        } else {
            window->slide_x -= 1;
            window->slide_y += window->slide_y_flipped != 0 ? -1 : 1;
        }
    }
    window->timer--;
    if (window->timer > 0) {
        return;
    }
    window->slide_x = 0;
    window->slide_y = 0;
    SlidingWindow_SetOpen(window);
}
CLEAN_AS(func_0208a8d4, SlidingWindow_StepOpening)

/* func_0208a944: opening started 5 pixels off its place in x and y, or at it when instant. */
void SlidingWindow_StartOpening(SlidingWindow *window)
{
    if (window->instant != 0) {
        window->timer = 1;
        window->slide_x = 0;
        window->slide_y = 0;
    } else {
        window->timer = OPENING_FRAMES;
        window->slide_x = -5;
        window->slide_y = window->slide_y_flipped == 0 ? 5 : -5;
    }
    window->state = SLIDING_WINDOW_OPENING;
}
CLEAN_AS(func_0208a944, SlidingWindow_StartOpening)

/* func_0208a978: closed: once asked to open, the text boxes made, the window fitted to the text
 * and opening. */
void SlidingWindow_StepClosed(SlidingWindow *window)
{
    if (window->open_request != 0) {
        window->open_request = 0;
        SlidingWindow_MakeBoxes(window);
        SlidingWindow_FitText(window);
        SlidingWindow_StartOpening(window);
    }
}
CLEAN_AS(func_0208a978, SlidingWindow_StepClosed)

/* func_0208a9a4 */
void SlidingWindow_SetClosed(SlidingWindow *window)
{
    window->state = SLIDING_WINDOW_CLOSED;
}
CLEAN_AS(func_0208a9a4, SlidingWindow_SetClosed)

/* func_0208a9ac: an open window asked to close; 1 when it was open, else 0, returned in a
 * pointer as the original declares its result. */
void *SlidingWindow_RequestClose(SlidingWindow *window)
{
    int open = window->state == SLIDING_WINDOW_OPEN;
    if (open) {
        window->close_request = 1;
    }
    return (void *) (uintptr_t) open;
}
CLEAN_AS(func_0208a9ac, SlidingWindow_RequestClose)

/* func_0208a9c8: a closed window asked to open; 1 when it was closed, else 0, returned in a
 * pointer as the original declares its result. */
void *SlidingWindow_RequestOpen(SlidingWindow *window)
{
    int closed = window->state == SLIDING_WINDOW_CLOSED;
    if (closed) {
        window->open_request = 1;
    }
    return (void *) (uintptr_t) closed;
}
CLEAN_AS(func_0208a9c8, SlidingWindow_RequestOpen)

/* func_0208a9e4: the boxes there given their lines' characters again and asked to redraw; with
 * `fit`, the window fitted to the text again. */
void SlidingWindow_RefreshText(SlidingWindow *window, int fit)
{
    if (window->boxes[0] != NULL) {
        TextDrawBox *box = window->boxes[0];
        box->text = line_chars(&window->lines[0]);
        TextDraw_RequestDraw(window->boxes[0]);
    }
    if (window->boxes[1] != NULL) {
        TextDrawBox *box = window->boxes[1];
        box->text = line_chars(&window->lines[1]);
        TextDraw_RequestDraw(window->boxes[1]);
    }
    if (fit != 0) {
        SlidingWindow_FitText(window);
    }
}
CLEAN_AS(func_0208a9e4, SlidingWindow_RefreshText)

/* func_0208aa38 */
void SlidingWindow_SetKeepOnScreen(SlidingWindow *window, u8 keep)
{
    window->keep_on_screen = keep;
}
CLEAN_AS(func_0208aa38, SlidingWindow_SetKeepOnScreen)
