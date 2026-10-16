/* The list of line handlers (line_handlers.h). */
#include "line_handlers.h"

#include "clean.h"

static_assert(offsetof(LineHandler, frame_function) == 0x04, "the frame function");
static_assert(offsetof(LineHandler, next_vblank_function) == 0x14, "the next VBlank function");
static_assert(offsetof(LineHandler, next) == 0x18, "the next handler");

/* The first and the last handler of the list; NULL when it is empty. */
extern LineHandler *data_021c9aa8;
extern LineHandler *data_021c9aac;

/* A game function at a DS address, called with nothing. */
static void LineHandlers_Call(u32 function)
{
    ((void (*)(void))(uintptr_t) function)();
}

/* func_0205bfd0: the handler is to take `hblank_function` and `vblank_function` (DS addresses,
 * 0 for none) when the main loop next runs (LineHandlers_RunFrame); 1. */
void *LineHandlers_RequestChange(LineHandler *handler, int hblank_function, int vblank_function)
{
    handler->next_vblank_function = (u32) vblank_function;
    handler->next_hblank_function = (u32) hblank_function;
    handler->state = LINE_HANDLER_CHANGE;
    return (void *) (uintptr_t) 1;
}
CLEAN_AS(func_0205bfd0, LineHandlers_RequestChange)

/* func_0205bfdc: the handler taken out of the list; whether it was in it. */
int LineHandlers_Remove(LineHandler *handler)
{
    if (handler == data_021c9aa8) {
        data_021c9aa8 = handler->next;
        if (data_021c9aac == handler) {
            data_021c9aac = NULL;
        }
        return 1;
    }
    for (LineHandler *prev = data_021c9aa8; prev != NULL; prev = prev->next) {
        if (prev->next == handler) {
            prev->next = handler->next;
            if (data_021c9aac == handler) {
                data_021c9aac = prev;
            }
            return 1;
        }
    }
    return 0;
}
CLEAN_AS(func_0205bfdc, LineHandlers_Remove)

/* func_0205c024: the handler added at the end of the list, new: the main loop starts it and
 * gives it `hblank_function` then. Its functions are DS addresses, 0 for none; 1. */
int LineHandlers_Add(LineHandler *handler, int hblank_function, int vblank_function, int frame_function)
{
    handler->next_hblank_function = (u32) hblank_function;
    handler->hblank_function = 0;
    handler->vblank_function = (u32) vblank_function;
    handler->frame_function = (u32) frame_function;
    handler->next = NULL;
    handler->state = LINE_HANDLER_NEW;
    if (data_021c9aac != NULL) {
        data_021c9aac->next = handler;
        data_021c9aac = handler;
    } else {
        data_021c9aac = handler;
        data_021c9aa8 = handler;
    }
    return 1;
}
CLEAN_AS(func_0205c024, LineHandlers_Add)

/* func_0205c054: from the VBlank interrupt, the VBlank function of each started handler (active
 * or waiting for a change), in order. */
void LineHandlers_RunVBlank(void)
{
    for (LineHandler *handler = data_021c9aa8; handler != NULL; handler = handler->next) {
        if (handler->state == LINE_HANDLER_ACTIVE || handler->state == LINE_HANDLER_CHANGE) {
            if (handler->vblank_function != 0) {
                LineHandlers_Call(handler->vblank_function);
            }
        }
    }
}
CLEAN_AS(func_0205c054, LineHandlers_RunVBlank)

/* func_0205c080: once a frame, each handler in order: a new one started (its HBlank function
 * set and its VBlank function run once), its frame function run, then a change it asked for
 * made (both functions set and the new VBlank function run once). */
void LineHandlers_RunFrame(void)
{
    for (LineHandler *handler = data_021c9aa8; handler != NULL; handler = handler->next) {
        if (handler->state == LINE_HANDLER_NEW) {
            handler->state = LINE_HANDLER_ACTIVE;
            handler->hblank_function = handler->next_hblank_function;
            if (handler->vblank_function != 0) {
                LineHandlers_Call(handler->vblank_function);
            }
        }
        if (handler->frame_function != 0) {
            LineHandlers_Call(handler->frame_function);
        }
        if (handler->state == LINE_HANDLER_CHANGE) {
            handler->state = LINE_HANDLER_ACTIVE;
            handler->hblank_function = handler->next_hblank_function;
            handler->vblank_function = handler->next_vblank_function;
            if (handler->vblank_function != 0) {
                LineHandlers_Call(handler->vblank_function);
            }
        }
    }
}
CLEAN_AS(func_0205c080, LineHandlers_RunFrame)

/* func_0205c0d4: the start-up's: the list emptied. */
void LineHandlers_Init(void)
{
    LineHandlers_Clear();
}
CLEAN_AS(func_0205c0d4, LineHandlers_Init)

/* func_0205c0dc: the list emptied (the handlers are left as they are). */
void LineHandlers_Clear(void)
{
    data_021c9aa8 = NULL;
    data_021c9aac = NULL;
}
CLEAN_AS(func_0205c0dc, LineHandlers_Clear)
