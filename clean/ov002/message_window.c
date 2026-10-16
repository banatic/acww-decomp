/* The menu scenes' message window (message_window.h). */
#include "message_window.h"

#include <assert.h>
#include <stdint.h>

#include "clean.h"
#include "main/text_label.h"

static_assert(sizeof(MessageWindow) == 0xcc, "message window");

extern const u8 data_ov002_0220bdac[];  /* the window's vtable */
extern void func_020edb3c(void *block); /* operator delete */

/* main's sliding window */
extern void *func_0208ade8(MessageWindow *window, int param);       /* constructor */
extern void *func_0208ad24(MessageWindow *window);                  /* destructor */
extern void func_0208aef4(MessageWindow *window, int x, int y);     /* its place, from the screen's centre */
extern void func_0208aa60(MessageWindow *window, int x, int y);     /* words 0x3c and 0x40: an offset */
extern void func_0208aa48(MessageWindow *window, TextLabel *label); /* copies the label's text in */
extern void func_0208aa88(MessageWindow *window);                   /* byte 0x59 = 1 */
extern void *func_0208a9c8(MessageWindow *window);                  /* asks a closed window to open */
extern void *func_0208a9ac(MessageWindow *window);                  /* asks an open window to close */

/* The screen's centre, (0, 0) of main's places. */
#define CENTER_X 0x80
#define CENTER_Y 0x60

/* The vtable's entries called here. */
#define SLOT_UPDATE 3
#define SLOT_SET_PLACE 4

typedef void WindowMethod(MessageWindow *window);
typedef void WindowPlaceMethod(MessageWindow *window, int x, int y);

/* The function in vtable slot `slot` of the window. */
static uintptr_t virtual_slot(const MessageWindow *window, int slot)
{
    return ((const u32 *) window->vtable)[slot];
}

static void update(MessageWindow *window)
{
    ((WindowMethod *) virtual_slot(window, SLOT_UPDATE))(window);
}

/* func_ov002_0220b04c: asks the window to close when it is open, and updates it twice. */
void MessageWindow_Close(MessageWindow *window)
{
    func_0208a9ac(window);
    update(window);
    update(window);
}
CLEAN_AS(func_ov002_0220b04c, MessageWindow_Close)

/* func_ov002_0220b06c: places the window at (x, y) on the screen with no offset, gives it
 * message `message` of "2d_menu", asks it to open when it is closed, and updates it twice. */
void MessageWindow_Open(MessageWindow *window, int message, int x, int y)
{
    TextLabel label;

    ((WindowPlaceMethod *) virtual_slot(window, SLOT_SET_PLACE))(window, x, y);
    func_0208aa60(window, 0, 0);
    TextLabel_Construct(&label);
    TextLabel_LoadMenuMessage((int) (uintptr_t) &label, (char) message);
    func_0208aa48(window, &label);
    func_0208aa88(window);
    func_0208a9c8(window);
    update(window);
    update(window);
    TextLabel_Destruct(&label);
}
CLEAN_AS(func_ov002_0220b06c, MessageWindow_Open)

/* func_ov002_0220b0c8 (vtable slot 4): places the window at (x, y) on the screen. */
void MessageWindow_SetPlace(MessageWindow *window, int x, int y)
{
    func_0208aef4(window, x - CENTER_X, y - CENTER_Y);
}
CLEAN_AS(func_ov002_0220b0c8, MessageWindow_SetPlace)

/* func_ov002_0220b0d4 (vtable entry 1): destructs and frees the window. */
MessageWindow *MessageWindow_Delete(MessageWindow *window)
{
    window->vtable = data_ov002_0220bdac;
    func_0208ad24(window);
    func_020edb3c(window);
    return window;
}
CLEAN_AS(func_ov002_0220b0d4, MessageWindow_Delete)

/* func_ov002_0220b0f4 (vtable entry 0) */
MessageWindow *MessageWindow_Destroy(MessageWindow *window)
{
    window->vtable = data_ov002_0220bdac;
    func_0208ad24(window);
    return window;
}
CLEAN_AS(func_ov002_0220b0f4, MessageWindow_Destroy)

/* func_ov002_0220b10c */
MessageWindow *MessageWindow_Construct(MessageWindow *window)
{
    func_0208ade8(window, 0);
    window->vtable = data_ov002_0220bdac;
    func_0208aa88(window);
    return window;
}
CLEAN_AS(func_ov002_0220b10c, MessageWindow_Construct)
