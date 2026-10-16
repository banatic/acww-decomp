/* The screen the game falls back to when it stops: after a CPU exception (the handler stores
 * the exception's context and runs DebugScreen_Run) or a fatal error (Fatal_Printf, which ends
 * in OS_Terminate).
 *
 * Nothing is shown until a key sequence is entered: L+R+Left+A, release, Down+B, release,
 * Select+Start. Then both screens show text on background 1: the main screen the uptime, the
 * registers of the exception (or a saved SP and PC), the fatal error's file, line and message,
 * the current thread and the first stack overflow found; the sub screen a dump of the stack.
 * Select+A then reports one of three heaps (Left, Right, Up). */
#ifndef CLEAN_MAIN_DEBUG_SCREEN_H
#define CLEAN_MAIN_DEBUG_SCREEN_H

#include "types.h"

/* The context the exception handler stores (data_0213fde0): the registers as the SDK's
 * OSContext has them, then two words the screen labels SPSR and CP15. */
typedef struct ExceptionContext {
    u32 regs[18]; /* CPSR, R0-R12, SP, LR, PC+4, SP of supervisor mode */
    u8 unk_48[0x1c];
    u32 spsr; /* 0x64 */
    u32 cp15; /* 0x68 */
} ExceptionContext;

void DebugScreen_Run(void);
void DebugScreen_Frame(void);
void DebugScreen_WaitVBlank(void);
void DebugScreen_InitDisplay(void);
void DebugScreen_ClearScreens(void);
void DebugScreen_FillWords(u32 data, void *dest, u32 size);
void DebugScreen_DrawStatus(void);
void DebugScreen_DrawStack(void);
void DebugScreen_DumpWords(void *dest, void *src, u32 size);
int DebugScreen_IsReadable(void *start, u32 size);
void Fatal_Printf(const char *format, ...);
void Fatal_Report(const char *file, int line, const char *format, const void *args);
void DebugScreen_Nothing(void);

#endif
