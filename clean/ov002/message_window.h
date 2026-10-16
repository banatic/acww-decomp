/* A window of the menu scenes that shows a message of "2d_menu": an object of main's sliding
 * window class (vtable 0x020e20ac, constructor func_0208ade8, destructor func_0208ad24; see
 * popup.h) with ov002's vtable 0x0220bdac over it, whose only own entry places the window by
 * screen coordinates (MessageWindow_SetPlace, vtable slot 4). Slot 2 is main's draw
 * (func_0208ab3c), slot 3 main's update (func_0208aaa0), which steps the window through
 * closed, opening, open and closing. The button panel and the paged choice keep one. */
#ifndef CLEAN_OV002_MESSAGE_WINDOW_H
#define CLEAN_OV002_MESSAGE_WINDOW_H

#include "types.h"

typedef struct MessageWindow {
    const void *vtable; /* data_ov002_0220bdac */
    u8 base_04[0xc8];   /* main's sliding window */
} MessageWindow;

void MessageWindow_Close(MessageWindow *window);
void MessageWindow_Open(MessageWindow *window, int message, int x, int y);
void MessageWindow_SetPlace(MessageWindow *window, int x, int y);
MessageWindow *MessageWindow_Delete(MessageWindow *window);
MessageWindow *MessageWindow_Destroy(MessageWindow *window);
MessageWindow *MessageWindow_Construct(MessageWindow *window);

#endif
