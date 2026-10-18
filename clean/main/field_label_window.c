/* The window of the field's label and its marker (field_label_window.h). */
#include "field_label_window.h"

#include "autoload_2/heap.h"
#include "clean.h"
#include "sound.h"
#include "state_flags.h"
#include "cell_anim.h"
#include "oam_buffer.h"
#include "sliding_window.h"

static_assert(offsetof(FieldLabelWindow, marker) == 0xcc, "FieldLabelWindow");
static_assert(offsetof(FieldLabelWindow, mode) == 0xe8, "FieldLabelWindow");
static_assert(sizeof(FieldLabelWindow) == 0xec, "FieldLabelWindow");

/* The sound effect played when the marker's count starts a round. */
#define FIELD_LABEL_WINDOW_MARKER_SE 0x3d
/* The last frame of a blink round. */
#define FIELD_LABEL_WINDOW_LAST_FRAME 29
/* StateFlags_ValueOrZero under this (1.0) lets state flag 4 hide the marker. */
#define FIELD_LABEL_WINDOW_VALUE_ONE 0x1000

/* The sliding window's states (func_0208a844). */
enum FieldLabelWindowState {
    FIELD_LABEL_WINDOW_CLOSED = 0,
    FIELD_LABEL_WINDOW_OPEN = 2,
};

extern const u32 data_020e5858[]; /* this class's vtable */
extern const u8 data_020d71d4[];  /* the marker's cells */

/* func_020b8edc: whether the marker is held hidden: state flag 0x10 is set, or state flag 4 is
 * set with a value under 1.0. The three are read every time. */
int FieldLabelWindow_MarkerSuppressed(void)
{
    BOOL flag_10 = StateFlags_Test10() != 0;
    BOOL flag_4 = StateFlags_Test4() != 0;
    fx32 value = StateFlags_ValueOrZero();

    return flag_10 || (flag_4 && value < FIELD_LABEL_WINDOW_VALUE_ONE);
}
CLEAN_AS(func_020b8edc, FieldLabelWindow_MarkerSuppressed)

/* func_020b8f20: one frame of the marker. A request shows it (frame 0, or 25 when held
 * hidden) and starts its animation. Shown, it goes when the window has closed; while the
 * window is open its count runs (field_label_window.h). */
void FieldLabelWindow_UpdateMarker(FieldLabelWindow *window)
{
    if (!window->shown) {
        if (window->request) {
            window->request = 0;
            window->shown = 1;
            window->frames = FieldLabelWindow_MarkerSuppressed() ? FIELD_LABEL_WINDOW_HIDDEN_FRAME : 0;
            FieldLabelWindow_StartMarker(window);
        }
        return;
    }

    int state = SlidingWindow_State((SlidingWindow *) window);
    if (state == FIELD_LABEL_WINDOW_CLOSED) {
        window->request = 0;
        window->shown = 0;
        window->frames = 0;
    } else if (state == FIELD_LABEL_WINDOW_OPEN) {
        if (window->frames == 0) {
            SoundSys_PlaySe(FIELD_LABEL_WINDOW_MARKER_SE);
        }
        if (FieldLabelWindow_MarkerSuppressed()) {
            window->frames = FIELD_LABEL_WINDOW_HIDDEN_FRAME;
        } else if (window->mode != 0) {
            window->frames++;
            if (window->frames >= FIELD_LABEL_WINDOW_BLINK_FRAMES) {
                window->frames = 0;
            }
        } else {
            window->frames = 1;
        }
    }
}
CLEAN_AS(func_020b8f20, FieldLabelWindow_UpdateMarker)

/* func_020b8fe0: the marker's animation set to its cells, held, stopped on the frame the
 * window's own animation shows, and advanced once. */
void FieldLabelWindow_StartMarker(FieldLabelWindow *window)
{
    int frame = CellAnim_Frame(SlidingWindow_Body((SlidingWindow *) window));

    CellAnim_SetData(&window->marker, (const CellAnimData *) (void *) data_020d71d4);
    CellAnim_SetHold(&window->marker, 1);
    CellAnim_SetSpeed(&window->marker, 0);
    CellAnim_SetFrame(&window->marker, frame, 0);
    CellAnim_Advance(&window->marker);
}
CLEAN_AS(func_020b8fe0, FieldLabelWindow_StartMarker)

/* func_020b9030: blinking, and the marker in the shown part of the round. */
int FieldLabelWindow_MarkerBlinkShown(FieldLabelWindow *window)
{
    return window->mode != 0 && window->frames < FIELD_LABEL_WINDOW_HIDDEN_FRAME;
}
CLEAN_AS(func_020b9030, FieldLabelWindow_MarkerBlinkShown)

/* func_020b904c: blinking, and on the round's last frame. */
int FieldLabelWindow_MarkerBlinkLast(FieldLabelWindow *window)
{
    return window->mode != 0 && window->frames == FIELD_LABEL_WINDOW_LAST_FRAME;
}
CLEAN_AS(func_020b904c, FieldLabelWindow_MarkerBlinkLast)

/* func_020b9068 */
void FieldLabelWindow_SetMode(FieldLabelWindow *window, u8 mode)
{
    window->mode = mode;
}
CLEAN_AS(func_020b9068, FieldLabelWindow_SetMode)

/* func_020b9070: the sliding window reset (func_0208a784), the marker gone. */
void FieldLabelWindow_Reset(FieldLabelWindow *window)
{
    SlidingWindow_Reset((SlidingWindow *) window);
    window->request = 0;
    window->shown = 0;
    window->frames = 0;
    window->drawn = 0;
    window->drawn_before = 0;
    window->mode = 0;
}
CLEAN_AS(func_020b9070, FieldLabelWindow_Reset)

/* func_020b90a4 */
void FieldLabelWindow_RequestMarker(FieldLabelWindow *window)
{
    window->request = 1;
}
CLEAN_AS(func_020b90a4, FieldLabelWindow_RequestMarker)

/* func_020b90ac (vtable slot 3): the sliding window's update, then the marker's. */
void FieldLabelWindow_Update(FieldLabelWindow *window)
{
    window->drawn_before = window->drawn;
    SlidingWindow_Update((SlidingWindow *) window);
    FieldLabelWindow_UpdateMarker(window);
}
CLEAN_AS(func_020b90ac, FieldLabelWindow_Update)

/* func_020b90cc (vtable slot 2): under frame 25 of the count, the marker (when shown) at the
 * window's place plus the offsets of the window's animation and its own, then the window; past
 * it, nothing. `drawn` says whether the marker was drawn. */
void FieldLabelWindow_Draw(FieldLabelWindow *window)
{
    u8 drawn = 0;

    if (window->frames < FIELD_LABEL_WINDOW_HIDDEN_FRAME) {
        if (window->shown) {
            int cell = (int) (uintptr_t) CellAnim_Cell(&window->marker);
            CellAnim *body = SlidingWindow_Body((SlidingWindow *) window);
            int x = SlidingWindow_DrawX((SlidingWindow *) window);
            int y = SlidingWindow_DrawY((SlidingWindow *) window);

            x += CellAnim_FrameX(body, -1);
            x += CellAnim_FrameX(&window->marker, -1);
            y += CellAnim_FrameY(body, -1);
            y += CellAnim_FrameY(&window->marker, -1);
            OamBuffer_DrawCell(0, (const OamEntry *) (uintptr_t) cell, x, y, -1, -1, 0x1000, 0x1000, 0, -1, 0, 0);
            drawn = 1;
        }
        SlidingWindow_Draw((SlidingWindow *) window);
    }
    window->drawn = drawn;
}
CLEAN_AS(func_020b90cc, FieldLabelWindow_Draw)

/* func_020b9178 (vtable slot 1): destroyed and freed. */
FieldLabelWindow *FieldLabelWindow_Delete(FieldLabelWindow *window)
{
    window->vtable = data_020e5858;
    CellAnim_Destruct(&window->marker);
    SlidingWindow_DestructBase((SlidingWindow *) window);
    Heap_OperatorDeleteB(window);
    return window;
}
CLEAN_AS(func_020b9178, FieldLabelWindow_Delete)

/* func_020b91a0 (vtable slot 0): the destructor. */
FieldLabelWindow *FieldLabelWindow_Destroy(FieldLabelWindow *window)
{
    window->vtable = data_020e5858;
    CellAnim_Destruct(&window->marker);
    SlidingWindow_DestructBase((SlidingWindow *) window);
    return window;
}
CLEAN_AS(func_020b91a0, FieldLabelWindow_Destroy)

/* func_020b91c4: the constructor (the sliding window's with 1). */
FieldLabelWindow *FieldLabelWindow_Construct(FieldLabelWindow *window)
{
    SlidingWindow_Construct((SlidingWindow *) window, 1);
    window->vtable = data_020e5858;
    CellAnim_Construct(&window->marker);
    window->frames = 0;
    window->request = 0;
    window->shown = 0;
    window->drawn = 0;
    window->drawn_before = 0;
    window->mode = 0;
    return window;
}
CLEAN_AS(func_020b91c4, FieldLabelWindow_Construct)
