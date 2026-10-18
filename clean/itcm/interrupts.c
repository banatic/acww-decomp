/* The interrupt handlers (interrupts.h). */
#include "interrupts.h"

#include <assert.h>
#include <stddef.h>
#include <stdint.h>

#include "clean.h"
#include "main/line_handlers.h"
#include "main/transfer_queue.h"

static_assert(offsetof(LineHandler, hblank_function) == 0x0c, "the HBlank function");
static_assert(offsetof(LineHandler, next) == 0x18, "the next handler");

#define REG_VCOUNT (*(const volatile u16 *) 0x04000006)

/* NitroSDK's interrupt check flags (OS_SetIrqCheckFlag) at the end of the DTCM: a thread
 * waiting for an interrupt (OS_WaitIrq) looks for its bit there. */
extern u8 SDK_AUTOLOAD_DTCM_START[];
#define IRQ_CHECK_FLAGS_OFFSET 0x3ff8
#define IRQ_VBLANK 1

/* The line handlers, in the order they were added. */
extern LineHandler *data_021c9aa8;

/* The frame pacing: VBlanks counted since the last frame was started, the VBlanks a frame
 * takes (set to 3 by func_020b5a34), and whether the main loop waits for the next frame
 * (set around func_0206e6a0). */
extern int data_021cfb88;
extern int data_020dd828;
extern u16 data_021cfb6c;
/* The threads waiting for the next frame and those waiting for the next VBlank (OSThreadQueue,
 * cleared by func_020b1c78). */
extern u8 data_021cfb98[];
extern u8 data_021cfb90[];

extern void OS_WakeupThread(void *queue);

/* func_01ffcb28: does nothing; called once in the start-up (func_020b1b84) with the interrupt
 * set-up. */
void Irq_InitNothing(void) {}
CLEAN_AS(func_01ffcb28, Irq_InitNothing)

/* func_01ffcc30: the HBlank interrupt: in the visible lines (VCOUNT below 192), each line
 * handler's HBlank function, in order.
 * HW: VCOUNT is read once, before any handler runs. */
void Irq_HBlank(void)
{
    if (REG_VCOUNT >= 192) {
        return;
    }
    for (LineHandler *handler = data_021c9aa8; handler != NULL; handler = handler->next) {
        if (handler->hblank_function != 0) {
            ((void (*)(void))(uintptr_t) handler->hblank_function)();
        }
    }
}
CLEAN_AS(func_01ffcc30, Irq_HBlank)

/* func_01ffcc60: the VBlank interrupt. When a frame's VBlanks have passed and the main loop
 * waits, it is woken for the next frame, the count starts again and the spare-time tasks run;
 * while it does not wait the count goes on. Then the line handlers' VBlank functions run, the
 * threads waiting for a VBlank are woken and the VBlank is flagged for OS_WaitIrq. */
void Irq_VBlank(void)
{
    data_021cfb88 = (int) ((u32) data_021cfb88 + 1);
    if (data_021cfb88 >= data_020dd828 && data_021cfb6c != 0) {
        OS_WakeupThread(data_021cfb98);
        data_021cfb88 = 0;
        TransferQueue_RunVBlank();
    }
    LineHandlers_RunVBlank();
    OS_WakeupThread(data_021cfb90);
    *(u32 *) (SDK_AUTOLOAD_DTCM_START + IRQ_CHECK_FLAGS_OFFSET) |= IRQ_VBLANK;
}
CLEAN_AS(func_01ffcc60, Irq_VBlank)
