/* The popup of the menu scenes (popup.h). */
#include "popup.h"

#include <stddef.h>

#include "clean.h"

static_assert(offsetof(Popup, step) == 0xcc && offsetof(Popup, timer) == 0xce, "popup fields");

extern const u8 data_ov002_0220baa8[]; /* the popup's vtable */

/* main's sliding window */
extern void *func_0208ade8(void *window, int param); /* constructor */
extern void *func_0208ad24(void *window);            /* destructor */
extern int func_0208a844(void *window);              /* its state: PopupWindowState */
extern void *func_0208a9ac(void *window);            /* close if open: whether it was */
extern void *func_0208a9c8(void *window);            /* open if closed: whether it was */
extern void func_0208aa38(void *window, u8 value);   /* sets its byte at 0x57 */
extern void func_0208aa40(void *window);             /* sets its byte at 0x5c */
extern void func_0208aaa0(void *window);             /* runs its state for a frame */
extern void func_020edb3c(void *block);              /* operator delete */

static int window_state(Popup *popup)
{
    return func_0208a844(popup);
}

/* func_ov002_02207cc0: whether the window is open or opening.
 * QUIRK: the state is read again for the second comparison. */
int Popup_IsUp(Popup *popup)
{
    if (window_state(popup) == POPUP_WINDOW_OPEN) {
        return 1;
    }
    return window_state(popup) == POPUP_WINDOW_OPENING;
}
CLEAN_AS(func_ov002_02207cc0, Popup_IsUp)

/* func_ov002_02207ce4 */
void Popup_SetTimer(Popup *popup, u8 frames)
{
    popup->timer = frames;
}
CLEAN_AS(func_ov002_02207ce4, Popup_SetTimer)

/* func_ov002_02207cec: the window's word at 0x44, which its drawing (func_0208ab3c) passes to
 * func_02088df8 as the sixth argument. */
void Popup_SetDrawValue(Popup *popup, int value)
{
    *(int *) (popup->window + 0x40) = value;
}
CLEAN_AS(func_ov002_02207cec, Popup_SetDrawValue)

/* func_ov002_02207cf0 */
void Popup_ClearQueued(Popup *popup)
{
    popup->queued = 0;
}
CLEAN_AS(func_ov002_02207cf0, Popup_ClearQueued)

/* func_ov002_02207cf8 */
void Popup_Queue(Popup *popup)
{
    popup->queued = 1;
}
CLEAN_AS(func_ov002_02207cf8, Popup_Queue)

/* func_ov002_02207d00: shows the popup if it was queued (closing the window first), and
 * stops the timer either way. */
void Popup_ShowQueued(Popup *popup)
{
    popup->timer = 0;
    if (popup->queued) {
        popup->step = POPUP_CLOSING_TO_SHOW;
    }
    popup->queued = 0;
}
CLEAN_AS(func_ov002_02207d00, Popup_ShowQueued)

/* func_ov002_02207d24: stops the timer and closes the window; with `drop_queued`, also
 * forgets a queued show. 1 when the window is already closed (the popup goes idle), else 0
 * (it closes over the next frames). */
int Popup_Hide(Popup *popup, int drop_queued)
{
    popup->timer = 0;
    if (drop_queued) {
        Popup_ClearQueued(popup);
    }
    if (window_state(popup) == POPUP_WINDOW_CLOSED) {
        popup->step = POPUP_IDLE;
        return 1;
    }
    popup->step = POPUP_HIDING;
    return 0;
}
CLEAN_AS(func_ov002_02207d24, Popup_Hide)

/* func_ov002_02207d5c: a frame of the popup, then of its window. 1 on the frame the window is
 * found closed on the way to showing it again (its contents can change then), else 0. */
int Popup_Update(Popup *popup)
{
    int closed_to_show = 0;

    if (popup->timer != 0) {
        popup->timer--;
        if (popup->timer == 0 && popup->step == POPUP_SHOWN) {
            Popup_Hide(popup, 0);
        }
    }

    switch (popup->step) {
        case POPUP_CLOSING_TO_SHOW:
            if (window_state(popup) != POPUP_WINDOW_CLOSED) {
                func_0208a9ac(popup);
            } else {
                closed_to_show = 1;
                popup->step = POPUP_OPENING;
            }
            break;
        case POPUP_OPENING:
            if (func_0208a9c8(popup) != NULL) {
                popup->step = POPUP_SHOWN;
            }
            break;
        case POPUP_HIDING:
            if (window_state(popup) == POPUP_WINDOW_CLOSED || func_0208a9ac(popup) != NULL) {
                popup->step = POPUP_IDLE;
            }
            break;
    }

    func_0208aaa0(popup);
    return closed_to_show;
}
CLEAN_AS(func_ov002_02207d5c, Popup_Update)

/* func_ov002_02207e08: the deleting destructor. */
Popup *Popup_Delete(Popup *popup)
{
    popup->vtable = data_ov002_0220baa8;
    func_0208ad24(popup);
    func_020edb3c(popup);
    return popup;
}
CLEAN_AS(func_ov002_02207e08, Popup_Delete)

/* func_ov002_02207e28 */
Popup *Popup_Destroy(Popup *popup)
{
    popup->vtable = data_ov002_0220baa8;
    func_0208ad24(popup);
    return popup;
}
CLEAN_AS(func_ov002_02207e28, Popup_Destroy)

/* func_ov002_02207e40 */
Popup *Popup_Construct(Popup *popup)
{
    func_0208ade8(popup, 0);
    popup->vtable = data_ov002_0220baa8;
    popup->step = POPUP_IDLE;
    func_0208aa38(popup, 1);
    func_0208aa40(popup);
    popup->queued = 0;
    popup->timer = 0;
    return popup;
}
CLEAN_AS(func_ov002_02207e40, Popup_Construct)
