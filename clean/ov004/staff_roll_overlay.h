/* Overlay 4's handling of overlay 93's staff roll (ov093/staff_roll.h; 0x2520 bytes, from the
 * scenes' heap data_021c9b28), which the cafe guest's music show (ov068/cafe_guest.c) rolls:
 * overlay 93 is loaded and the object made and started by StaffRollOverlay_Open, stopped,
 * destructed, freed and the overlay released by StaffRollOverlay_Close. In between, while it
 * exists (bit 0 of data_ov004_0225ff50), the other functions hand it on to overlay 93's: its
 * update and the upload of its two buffers each frame, a restart at a speed, the switch to the
 * logo, and the test of bit 8 of its flags (the show's end). */
#ifndef CLEAN_OV004_STAFF_ROLL_OVERLAY_H
#define CLEAN_OV004_STAFF_ROLL_OVERLAY_H

#include "types.h"

int StaffRollOverlay_HasEnded(void);
void StaffRollOverlay_ShowLogo(void);
void StaffRollOverlay_Restart(int speed);
void StaffRollOverlay_Close(void);
void StaffRollOverlay_Upload(void);
void StaffRollOverlay_Update(void);
void StaffRollOverlay_Open(void);

#endif
