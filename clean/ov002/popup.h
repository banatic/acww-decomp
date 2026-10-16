/* A popup the menu scenes of the overlays 096-125 keep (one per scene, at 0x218c in ov102's):
 * an object of main's sliding window class (vtable 0x020e20ac, constructor func_0208ade8),
 * which opens and closes by moving two sprites, with a small sequence on top that closes the
 * window before it shows it again and closes it on its own after a number of frames.
 *
 * The window's own states (func_0208a844), run by func_0208aaa0: closed, opening, open,
 * closing. It opens when asked while closed (func_0208a9c8) and closes when asked while open
 * (func_0208a9ac). */
#ifndef CLEAN_OV002_POPUP_H
#define CLEAN_OV002_POPUP_H

#include "types.h"

enum PopupWindowState { POPUP_WINDOW_CLOSED = 0, POPUP_WINDOW_OPENING = 1, POPUP_WINDOW_OPEN = 2, POPUP_WINDOW_CLOSING = 3 };

/* The popup's own sequence, in `step`. */
enum PopupStep {
    POPUP_IDLE = 0,
    POPUP_CLOSING_TO_SHOW = 1, /* closing the window before it opens again */
    POPUP_OPENING = 2,         /* asking the closed window to open */
    POPUP_SHOWN = 3,           /* open; `timer` closes it */
    POPUP_HIDING = 4           /* asking the window to close */
};

typedef struct Popup {
    const void *vtable; /* data_ov002_0220baa8 */
    u8 window[0xc8];    /* main's sliding window (func_0208ade8) */
    u8 step;            /* 0xcc: PopupStep */
    u8 queued;          /* 0xcd: set: the next Popup_ShowQueued shows the popup */
    u8 timer;           /* 0xce: frames until a shown popup hides, 0: it stays */
} Popup;

int Popup_IsUp(Popup *popup);
void Popup_SetTimer(Popup *popup, u8 frames);
void Popup_SetDrawValue(Popup *popup, int value);
void Popup_ClearQueued(Popup *popup);
void Popup_Queue(Popup *popup);
void Popup_ShowQueued(Popup *popup);
int Popup_Hide(Popup *popup, int drop_queued);
int Popup_Update(Popup *popup);
Popup *Popup_Delete(Popup *popup);
Popup *Popup_Destroy(Popup *popup);
Popup *Popup_Construct(Popup *popup);

#endif
