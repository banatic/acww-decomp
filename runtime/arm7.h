/* The ARM7 side of the DS, simulated at the protocol level. The ARM7 runs its own copy of
 * the SDK, which the ARM9 talks to over IPCSYNC and the IPC FIFO (PXI in SDK terms) and
 * through the shared area at the top of main RAM. There is no ARM7 code here: arm7_step
 * answers what the ARM9's SDK is known to wait for, as the ARM7's SDK would.
 */
#ifndef RUNTIME_ARM7_H
#define RUNTIME_ARM7_H

#include <stdint.h>
#include <stdio.h>

void arm7_init(void);

/* Runs the ARM7 for a moment: the IPCSYNC handshake, the lock-word initialisation, and one
 * answer per FIFO word the ARM9 sent. Called between slices of ARM9 execution. */
void arm7_step(void);

/* The PXI traffic seen so far: every tag, what was sent on it and what was answered. */
void arm7_report(FILE *out);

/* The save chip's image (ARM7_BACKUP_SIZE bytes, as RUN_SAVE loads it) and, in *writes, how
 * many writes the game has made to it so far: a front end (runtime/play.c) writes the image
 * back to its save file when the count moves. */
#define ARM7_BACKUP_SIZE 0x40000u
const uint8_t *arm7_backup(uint64_t *writes);

#endif
