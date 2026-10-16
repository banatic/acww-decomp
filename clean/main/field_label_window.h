/* The window of the field's label (field_label.h): main's sliding window (vtable 0x020e20ac,
 * constructor func_0208ade8, destructor func_0208ad24; see ov002/message_window.h) with a
 * marker of its own drawn over it, under vtable data_020e5858 (slot 2 draws, slot 3 updates).
 *
 * The marker (a cell animation, data_020d71d4) shows once the window is asked to (`request`)
 * and while the window is open. Its frame count runs from 0: on frame 0 sound effect 0x3d
 * plays; in a blinking mode (`mode` not 0) the count goes round 0-29 and the marker is drawn on
 * frames 0-24, the sound playing again at each round; otherwise the count stays at 1 after the
 * first frame. While FieldLabelWindow_MarkerSuppressed holds the count is held at 25: the
 * marker is not drawn and no sound plays. */
#ifndef CLEAN_MAIN_FIELD_LABEL_WINDOW_H
#define CLEAN_MAIN_FIELD_LABEL_WINDOW_H

#include "screen_icon.h" /* CellAnim */
#include "types.h"

/* The marker is drawn while the frame count is under this. */
#define FIELD_LABEL_WINDOW_HIDDEN_FRAME 25
/* The frames of a blink round. */
#define FIELD_LABEL_WINDOW_BLINK_FRAMES 30

typedef struct FieldLabelWindow {
    const u32 *vtable; /* 0x00: data_020e5858 */
    u8 base_04[0xc8];  /* main's sliding window; its own animation at 0x0c (func_0208a840) */
    CellAnim marker;   /* 0xcc */
    int frames;        /* 0xe0: the marker's frame count */
    u8 request;        /* 0xe4: asked to show the marker */
    u8 shown;          /* 0xe5: the marker is shown */
    u8 drawn;          /* 0xe6: the marker was drawn by the last draw */
    u8 drawn_before;   /* 0xe7: `drawn` as it was before this frame's update */
    u8 mode;           /* 0xe8: not 0 for a blinking marker */
    u8 pad_e9[3];
} FieldLabelWindow;

int FieldLabelWindow_MarkerSuppressed(void);
void FieldLabelWindow_UpdateMarker(FieldLabelWindow *window);
void FieldLabelWindow_StartMarker(FieldLabelWindow *window);
int FieldLabelWindow_MarkerBlinkShown(FieldLabelWindow *window);
int FieldLabelWindow_MarkerBlinkLast(FieldLabelWindow *window);
void FieldLabelWindow_SetMode(FieldLabelWindow *window, u8 mode);
void FieldLabelWindow_Reset(FieldLabelWindow *window);
void FieldLabelWindow_RequestMarker(FieldLabelWindow *window);
void FieldLabelWindow_Update(FieldLabelWindow *window);
void FieldLabelWindow_Draw(FieldLabelWindow *window);
FieldLabelWindow *FieldLabelWindow_Delete(FieldLabelWindow *window);
FieldLabelWindow *FieldLabelWindow_Destroy(FieldLabelWindow *window);
FieldLabelWindow *FieldLabelWindow_Construct(FieldLabelWindow *window);

#endif
