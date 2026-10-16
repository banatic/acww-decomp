/* The list of line handlers (LineHandler, itcm/interrupts.h): handlers added at its end
 * (LineHandlers_Add), taken out (LineHandlers_Remove), given new HBlank and VBlank functions
 * (LineHandlers_RequestChange); their VBlank functions run from the VBlank interrupt
 * (LineHandlers_RunVBlank) and the main loop starts them, makes their changes and runs their
 * frame functions (LineHandlers_RunFrame).
 *
 * The list starts at data_021c9aa8 and its last handler is kept at data_021c9aac. */
#ifndef CLEAN_MAIN_LINE_HANDLERS_H
#define CLEAN_MAIN_LINE_HANDLERS_H

#include "itcm/interrupts.h"
#include "types.h"

void *LineHandlers_RequestChange(LineHandler *handler, int hblank_function, int vblank_function);
int LineHandlers_Remove(LineHandler *handler);
int LineHandlers_Add(LineHandler *handler, int hblank_function, int vblank_function, int frame_function);
void LineHandlers_RunVBlank(void);
void LineHandlers_RunFrame(void);
void LineHandlers_Init(void);
void LineHandlers_Clear(void);

#endif
