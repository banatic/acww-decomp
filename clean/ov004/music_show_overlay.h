/* Overlay 4's handling of overlay 93's object (0x2520 bytes, from the scenes' heap
 * data_021c9b28), which the cafe guest's music show (ov068/cafe_guest.c) uses: overlay 93 is
 * loaded and the object made and started by MusicShowOverlay_Open, stopped, destructed, freed
 * and the overlay released by MusicShowOverlay_Close. In between, while it exists (bit 0 of
 * data_ov004_0225ff50), the other functions hand it on to overlay 93's: its update and the
 * upload of its two buffers each frame, a restart with a value, a change of the display
 * registers, and the test of bit 8 of its flags (the show's end). */
#ifndef CLEAN_OV004_MUSIC_SHOW_OVERLAY_H
#define CLEAN_OV004_MUSIC_SHOW_OVERLAY_H

#include "types.h"

int MusicShowOverlay_HasEnded(void);
void MusicShowOverlay_SetDisplay(void);
void MusicShowOverlay_Restart(int value);
void MusicShowOverlay_Close(void);
void MusicShowOverlay_Upload(void);
void MusicShowOverlay_Update(void);
void MusicShowOverlay_Open(void);

#endif
