/* What the game does when the console's lid closes and opens (LidSleep_Update, each frame).
 *
 * Closing the lid (bit 15 of the ARM7's button word at 0x027fffa8) saves both screens'
 * backlights and turns them off, powers the screens down and mutes the sound. Opening it
 * restores the backlights, then powers the screens up (tried again each frame until it works)
 * and turns the sound back up, unless LidSleep_KeepSoundOff asked to leave it muted.
 *
 * State (data_021f4ad0): 0 open, 1 closed, 2 waking. Flags (data_021f4acc): bit 0 the
 * backlights are saved (top in data_021f4ad8, bottom in data_021f4ad4) and off, bit 1 the sound
 * stays muted on waking. */
#ifndef CLEAN_MAIN_LID_SLEEP_H
#define CLEAN_MAIN_LID_SLEEP_H

#include "types.h"

void LidSleep_ClearFlags(u8 flags);
void LidSleep_SetFlags(u32 flags);
int LidSleep_HasFlags(u8 flags);
void LidSleep_Wake(void);
void LidSleep_RestoreBacklights(void);
void LidSleep_BacklightsOff(void);
void LidSleep_KeepSoundOff(void);
void LidSleep_Update(void);
void LidSleep_Reset(void);

#endif
