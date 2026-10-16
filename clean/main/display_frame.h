/* The display's part of the main loop (func_0206e560): the work before each frame, after its
 * drawing and after the VBlank, through the hooks of the scene that is running; and the
 * display's set-up and reset. */
#ifndef CLEAN_MAIN_DISPLAY_FRAME_H
#define CLEAN_MAIN_DISPLAY_FRAME_H

#include "types.h"

struct DisplayFrameHooks;

/* The hooks' vtable (data_020e550c is one whose first two hooks do nothing). */
typedef struct DisplayFrameHooksVtable {
    void (*begin)(struct DisplayFrameHooks *hooks);        /* 0x00: before the frame's work */
    void (*end_draw)(struct DisplayFrameHooks *hooks);     /* 0x04: after its drawing */
    void (*after_vblank)(struct DisplayFrameHooks *hooks); /* 0x08 */
} DisplayFrameHooksVtable;

/* A scene's display hooks (data_021f693c is the one set while a scene runs). */
typedef struct DisplayFrameHooks {
    const DisplayFrameHooksVtable *vtable;
} DisplayFrameHooks;

void DisplayFrame_Reset2D(void);
void DisplayFrame_ReleaseVram(void);
void DisplayFrame_AfterVBlank(void);
void DisplayFrame_EndDraw(void);
void DisplayFrame_NoEndDraw(void);
void DisplayFrame_Begin(void);
void DisplayFrame_NoBegin(void);
void DisplayFrame_ResetState(void);
void DisplayFrame_Init(void);

#endif
