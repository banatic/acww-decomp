/* The ARM7's sound sequencer, as the ARM7's SDK runs it (runtime/sequencer.c): the sequence
 * players and their tracks, stepped by the sound driver's periodic alarm, and what they report
 * to the ARM9 (the shared work's player status and variables, and the driver's state on
 * request). No sound is made: notes take no channel.
 *
 * It is off unless RUN_SEQUENCER is set to a nonzero number (tools/run.py --sequencer). Off,
 * the ARM7 only counts the sound command lists (runtime/arm7.c), as before.
 */
#ifndef RUNTIME_SEQUENCER_H
#define RUNTIME_SEQUENCER_H

#include <stdint.h>
#include <stdio.h>

/* Reads RUN_SEQUENCER; returns whether the sequencer runs. */
int sequencer_init(void);

/* One command of a sound command list (its id and four arguments); `shared_work` is the
 * address of the shared work the ARM9 named (SND_COMMAND_SHARED_WORK), or 0. */
void sequencer_command(uint32_t id, const uint32_t args[4], uint32_t shared_work);

/* The sound thread's pass after a command list: the players' channels updated (no sequence
 * steps) and the shared work's status written. */
void sequencer_after_list(uint32_t shared_work);

/* The periodic passes due by the bus clock: each steps the sequences. */
void sequencer_advance(uint32_t shared_work);

void sequencer_report(FILE *out);

#endif
