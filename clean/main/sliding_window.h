/* main's sliding window (vtable data_020e20ac, 0xcc bytes; constructor func_0208ade8): a
 * window drawn as two cell animations (cell_anim.h) with up to two lines of text over it, that
 * slides a few pixels as it opens and closes. The menu scenes' message windows and popups
 * (ov002/message_window.h, ov002/popup.h) and the field's label window
 * (field_label_window.h) derive from it.
 *
 * It derives from main's screen sprite base (vtable data_020e20c8), whose place is kept relative
 * to the screen's centre (0x80, 0x60). Its states, stepped by its update (func_0208aaa0):
 * - closed: asked to open (SlidingWindow_RequestOpen), it makes the text boxes of its lines,
 *   picks the body frame that fits the wider line and starts opening;
 * - opening: three frames (one when `instant`), sliding into its place;
 * - open: asked to close (SlidingWindow_RequestClose), it starts closing;
 * - closing: two frames (one when `instant`), sliding away, then the text boxes are freed.
 *
 * The body animation's frame N is a window (N + 3) * 8 pixels wide; when `keep_on_screen` is
 * set, the window is moved sideways to stay within the screen's 256 pixels. */
#ifndef CLEAN_MAIN_SLIDING_WINDOW_H
#define CLEAN_MAIN_SLIDING_WINDOW_H

#include "screen_icon.h" /* CellAnim */
#include "text_draw.h"   /* TextDrawBox */
#include "text_label.h"  /* TextVtable */
#include "types.h"

enum SlidingWindowState {
    SLIDING_WINDOW_CLOSED = 0,
    SLIDING_WINDOW_OPENING = 1,
    SLIDING_WINDOW_OPEN = 2,
    SLIDING_WINDOW_CLOSING = 3,
};

/* A line's text (vtable data_020e2094, 0x30 bytes, constructed by func_0208aecc); its vtable's
 * slot 3 gives its characters. */
typedef struct SlidingWindowText {
    const TextVtable *vtable;
    u8 unk_04[0x2c];
} SlidingWindowText;

typedef struct SlidingWindow {
    const u32 *vtable;  /* data_020e20ac, or a derived class's */
    int base_x;         /* 0x04: the base class's place (func_0208aef0, func_0208aeec) */
    int base_y;         /* 0x08 */
    CellAnim body;      /* 0x0c: data_020d71a4, its frame by the text's width */
    CellAnim extra;     /* 0x20: data_020d71ac, on the same frame */
    u32 state;          /* 0x34: SlidingWindowState */
    int timer;          /* 0x38: frames left of opening or closing */
    int x;              /* 0x3c: the window's place, added to the base class's */
    int y;              /* 0x40 */
    int priority;       /* 0x44: the OBJs' priority, -1 for the cells' own */
    int slide_x;        /* 0x48: the slide's offset */
    int slide_y;        /* 0x4c */
    int screen_shift;   /* 0x50: the move that keeps the window on the screen */
    u8 open_request;    /* 0x54 */
    u8 close_request;   /* 0x55 */
    u8 on_main;         /* 0x56: drawn on the main screen, else on the sub screen */
    u8 keep_on_screen;  /* 0x57 */
    u8 unk_58;          /* 0x58: the cells are drawn a second time as OBJ windows */
    u8 instant;         /* 0x59: opens and closes without sliding */
    u8 slide_y_flipped; /* 0x5a: the slide goes the other way in y */
    u8 show_extra;      /* 0x5b: `extra` is drawn */
    u8 center_text;     /* 0x5c: the lines are centred in the window */
    u8 pad_5d[3];
    SlidingWindowText lines[2]; /* 0x60 */
    TextDrawBox *boxes[2];      /* 0xc0: the lines' text boxes while not closed */
    int line_count;             /* 0xc8: 2 for two lines, else one */
} SlidingWindow;

void SlidingWindow_KeepOnScreen(SlidingWindow *window);
void SlidingWindow_FreeBoxes(SlidingWindow *window);
void SlidingWindow_MakeBoxes(SlidingWindow *window);
void SlidingWindow_FitText(SlidingWindow *window);
void SlidingWindow_LoadAnims(SlidingWindow *window);
void SlidingWindow_Reset(SlidingWindow *window);
int SlidingWindow_Width(SlidingWindow *window);
int SlidingWindow_Y(SlidingWindow *window);
int SlidingWindow_X(SlidingWindow *window);
int SlidingWindow_DrawY(SlidingWindow *window);
int SlidingWindow_DrawX(SlidingWindow *window);
CellAnim *SlidingWindow_Body(SlidingWindow *window);
int SlidingWindow_State(SlidingWindow *window);
void SlidingWindow_StepClosing(SlidingWindow *window);
void SlidingWindow_StartClosing(SlidingWindow *window);
void SlidingWindow_StepOpen(SlidingWindow *window);
void SlidingWindow_SetOpen(SlidingWindow *window);
void SlidingWindow_StepOpening(SlidingWindow *window);
void SlidingWindow_StartOpening(SlidingWindow *window);
void SlidingWindow_StepClosed(SlidingWindow *window);
void SlidingWindow_SetClosed(SlidingWindow *window);
void *SlidingWindow_RequestClose(SlidingWindow *window);
void *SlidingWindow_RequestOpen(SlidingWindow *window);
void SlidingWindow_RefreshText(SlidingWindow *window, int fit);
void SlidingWindow_SetKeepOnScreen(SlidingWindow *window, u8 keep);

#endif
