/* The game's stop (game_halt.h). */
#include "game_halt.h"

#include <stdint.h>
#include <string.h>

#include "clean.h"

#define PXI_FIFO_TAG_CARD 14
#define HALT_COMMAND 1 /* the card library's terminate command */
#define HALT_WAIT 1    /* the wait between tries, in WaitByLoop's units */
#define CONTEXT_PC_UNKNOWN 0xffffffffu

extern u8 data_021cfb64;                /* the stop flag */
extern ExceptionContext *data_0213fde0; /* the context the debug screen shows */
extern u8 OSi_LauncherThread[];

extern u32 OS_DisableInterrupts(void);
extern void OS_Halt(void);
extern int PXI_SendWordByFifo(int tag, u32 data, int error);
extern void WaitByLoop(int count);
extern void OS_SetUserExceptionHandler(int handler, int argument);

/* func_0206e3c0: the stop's entry. HW: the ROM's code (ARM assembly) pushes r0-r15 and the CPSR
 * on the stack as the first 17 words of an exception context, with the caller's stack pointer
 * as SP and -1 as PC, and jumps to GameHalt_Halt with it. C cannot read the registers: here they
 * are 0, SP is the address just past those 17 words, and the rest of the context is 0 where the
 * ROM leaves the caller's stack. Never returns. */
void GameHalt_SaveContextAndHalt(void)
{
    ExceptionContext context;
    memset(&context, 0, sizeof(context));
    context.regs[14] = (u32) (uintptr_t) &context.regs[17];
    context.regs[16] = CONTEXT_PC_UNKNOWN;
    GameHalt_Halt(&context);
}
CLEAN_AS(func_0206e3c0, GameHalt_SaveContextAndHalt)

/* OS_Terminate: the game stopped. Never returns. */
void GameHalt_Terminate(void)
{
    GameHalt_SaveContextAndHalt();
}
CLEAN_AS(OS_Terminate, GameHalt_Terminate)

/* func_0206e3f4: interrupts disabled and the ARM7 told; unless the game had already stopped, the
 * stop flag raised and the debug screen run on `context`. HW: then the processor is halted with
 * interrupts disabled for as long as the flag is set: for good, as nothing clears it. */
void GameHalt_Halt(ExceptionContext *context)
{
    OS_DisableInterrupts();
    GameHalt_SendToArm7(HALT_COMMAND, HALT_WAIT);
    if (data_021cfb64 == 0) {
        data_021cfb64 = 1;
        GameHalt_ShowDebugScreen(context, OSi_LauncherThread);
    }
    while (data_021cfb64 != 0) {
        OS_DisableInterrupts();
        OS_Halt();
    }
}
CLEAN_AS(func_0206e3f4, GameHalt_Halt)

/* func_0206e438: `data` sent to the ARM7 on the card's PXI tag, waiting `wait` between tries
 * until the FIFO takes it. HW: a busy wait on the FIFO. */
void GameHalt_SendToArm7(int data, int wait)
{
    while (PXI_SendWordByFifo(PXI_FIFO_TAG_CARD, (u32) data, 0) != 0) {
        WaitByLoop(wait);
    }
}
CLEAN_AS(func_0206e438, GameHalt_SendToArm7)

/* func_0206e6c4: the user's exception handler removed, `context` given to the debug screen and
 * the screen run. The launcher thread is not used. */
void GameHalt_ShowDebugScreen(ExceptionContext *context, void *launcher)
{
    (void) launcher;
    OS_SetUserExceptionHandler(0, 0);
    data_0213fde0 = context;
    DebugScreen_Run();
}
CLEAN_AS(func_0206e6c4, GameHalt_ShowDebugScreen)
