/* The program's start-up, before the game's first scene.
 *
 * NitroSDK calls NitroStartUp (Startup_Begin) before main: it initialises the OS, gives VRAM
 * bank D to the ARM7 for the wireless library and waits for that library to start
 * (Startup_OnWirelessStarted raises the flag it waits on), sets the top of the main arena,
 * starts the file system, fills the overlays' memory with traps and creates the root heap.
 *
 * The game's own start-up (func_020b1b84, Startup_InitGame) then sets up the interrupts (the
 * HBlank and VBlank handlers of itcm/interrupts.h), the backup memory, overlay 69 (loaded and
 * ended at once), the auxiliary heap, sound, the process profiles, and loads overlay 68. */
#ifndef CLEAN_MAIN_STARTUP_H
#define CLEAN_MAIN_STARTUP_H

#include "types.h"

/* NitroSDK's interrupt bits (OS_IE_V_BLANK, OS_IE_H_BLANK). */
#define STARTUP_IRQ_VBLANK 1
#define STARTUP_IRQ_HBLANK 2

void Startup_Begin(void);
void Startup_TrapOverlayArea(void);
void Startup_SetArenaTop(void);
void Startup_OnWirelessStarted(void *argument, int result);
void Startup_InitGame(void);
void Startup_FirstStep(void);
void Startup_InitFrameWait(void);

#endif
