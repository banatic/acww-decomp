/* The ARM7's wireless manager (WM), simulated at the level of the ARM9's WM library: the
 * commands it sends on PXI tag 0xa and the callbacks and notifications it waits for, and the
 * radio between consoles as messages exchanged once a frame (docs/multi-console.md).
 *
 * It is off unless RUN_WIRELESS is set to a nonzero number (tools/run.py --wireless). Off, the
 * ARM7 leaves tag 0xa unanswered and the firmware has no MAC address, as before: the game's
 * local wireless library then finds no channel it may use. On, the console has a MAC address
 * and the channels local play uses, and answers WM's commands; with RUN_LINK it shares the air
 * with the other consoles of the run (runtime/wm.c, wm_link_open).
 */
#ifndef RUNTIME_WM_H
#define RUNTIME_WM_H

#include <stdint.h>
#include <stdio.h>

/* Reads RUN_WIRELESS and RUN_LINK; with the wireless on, writes the console's MAC address and
 * allowed channels where the ARM7 publishes them, and into the firmware image `nvram` (the
 * header's MAC address at 0x36 and channels at 0x3c). Returns whether the wireless is on. */
int wm_init(uint8_t *nvram);

/* One word the ARM9 sent on tag 0xa: the address of a WM command buffer. */
void wm_command(uint32_t data);

/* Called with every arm7_step: callbacks whose time has come, and the radio's exchange with
 * the other consoles at the start of each frame. */
void wm_step(void);

void wm_report(FILE *out);

#endif
