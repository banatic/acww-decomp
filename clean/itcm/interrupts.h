/* The game's VBlank and HBlank interrupt handlers (installed by func_020b1c78 and
 * func_020b1b84), and the line handlers the HBlank one runs.
 *
 * A line handler (func_0205c024 adds one to the list at data_021c9aa8) has a function run in
 * every HBlank of the visible lines, one run in every VBlank and one run once a frame by the
 * main loop (func_0205c080). A change of its HBlank and VBlank functions (func_0205bfd0) is
 * asked for with state LINE_HANDLER_CHANGE and made by the main loop. */
#ifndef CLEAN_ITCM_INTERRUPTS_H
#define CLEAN_ITCM_INTERRUPTS_H

#include "types.h"

enum LineHandlerState {
    LINE_HANDLER_NEW = 0,    /* added: started by the main loop */
    LINE_HANDLER_ACTIVE = 1, /* its VBlank function runs */
    LINE_HANDLER_CHANGE = 2, /* its next functions wait for the main loop */
};

/* The functions are the game's (DS addresses), NULL when there is none. */
typedef struct LineHandler {
    u8 state; /* LineHandlerState */
    u8 unk_01[3];
    u32 frame_function;       /* 0x04: run once a frame by the main loop */
    u32 vblank_function;      /* 0x08 */
    u32 hblank_function;      /* 0x0c */
    u32 next_hblank_function; /* 0x10 */
    u32 next_vblank_function; /* 0x14 */
    struct LineHandler *next; /* 0x18 */
} LineHandler;

void Irq_InitNothing(void);
void Irq_HBlank(void);
void Irq_VBlank(void);

#endif
