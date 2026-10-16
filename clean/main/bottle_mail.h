/* The bottle with a letter (item 0x1520) that washes up in the town.
 *
 * Its letter is kept at data_021f36ec (0x100 bytes), followed by 40 bits, one for each of the
 * game's own bottle messages ("ev_bottle") already used. A letter in a bottle from another
 * console waits at data_021ee418 (a type 6 player message) until a draw lets it arrive
 * (BottleMail_ReceiveDrifting). While there is a letter and no bottle on the map, a bottle is
 * put there (BottleMail_PlaceOnMap); picking it up gives the player the letter
 * (BottleMail_Open). Each new day there is a chance in ten of a new bottle with one of the
 * game's messages (BottleMail_DailyCheck). */
#ifndef CLEAN_MAIN_BOTTLE_MAIL_H
#define CLEAN_MAIN_BOTTLE_MAIL_H

#include "types.h"

#define BOTTLE_ITEM 0x1520

void BottleMail_ReceiveDrifting(void);
void BottleMail_DailyCheck(int days);
int BottleMail_IsOnMap(void);
int BottleMail_PlaceOnMap(void);
int BottleMail_Write(const u8 *message);
int BottleMail_Open(void);

#endif
