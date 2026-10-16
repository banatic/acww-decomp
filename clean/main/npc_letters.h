/* Two kinds of letter a player is sent when the record is caught up (PlayerRecord_UpdateSinceLastPlay):
 * the insurance letters (archive "sp_npc_insurance"), which pay an item for the claims the
 * player's record holds, and the letter of archive "sp_npc_missing", which carries an item
 * from item list 0x1b. Each letter goes to the post office (Mail_HoldAtPostOffice); the claim
 * stays until a letter was taken. */
#ifndef CLEAN_MAIN_NPC_LETTERS_H
#define CLEAN_MAIN_NPC_LETTERS_H

#include "player_field_2416.h"
#include "types.h"

void NpcLetters_SendInsurance(PlayerField2416 *field);
int NpcLetters_SendInsuranceLetter(PlayerField2416 *field, int message, u16 *item);
void NpcLetters_SendMissing(void);

#endif
