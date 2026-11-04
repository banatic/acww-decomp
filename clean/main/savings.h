/* The post office's savings and the town's donations: each player's account (at 0x23e0 of the
 * player's record) and the letters the post office ("sp_npc_pelican") writes about them.
 *
 * When the game is played again on a later day (func_020991d4), the account earns interest for
 * each month since the last play (Savings_PayInterest, message 0), the player gets a letter for
 * the highest savings step reached, once each (Savings_SendMilestoneLetter, messages 0x15-0x19),
 * and a thank-you letter for the donations' rank when it has risen (Savings_SendDonationLetter,
 * messages 1-20, with a present at some ranks).
 *
 * The rank is the step (1-20) that the bells the town's players have donated (Savings_Donations,
 * at data_021ef8a8 + 0x40) have reached: overlay 54's clerk takes a donation in bells, adds it,
 * and sets the donor's rank and flag SAVINGS_FLAG_DONATION_LETTER of the player's record. */
#ifndef CLEAN_MAIN_SAVINGS_H
#define CLEAN_MAIN_SAVINGS_H

#include "types.h"

/* The most bells an account or the town's donations hold. */
#define SAVINGS_MAX 999999999

/* A player's account (8 bytes at 0x23e0 of the record). */
typedef struct SavingsAccount {
    int balance;
    u8 donation_rank; /* the rank of the town's donations last thanked for */
} SavingsAccount;

/* The flags of the player's record (func_02099020) these letters use: one for each savings
 * step's letter sent (SAVINGS_FLAG_MILESTONE + step), and one for a donation letter to write. */
#define SAVINGS_FLAG_MILESTONE 0x11
#define SAVINGS_FLAG_DONATION_LETTER 0x16

void Savings_SendDonationLetter(int days);
void Savings_SendMilestoneLetter(int days);
void Savings_PayInterest(int months);
void Savings_SetDonationRank(SavingsAccount *account, int rank);
int Savings_DonationRank(SavingsAccount *account);
void Savings_SetDonations(int total);
u32 Savings_Donations(void);
void Savings_SetBalance(SavingsAccount *account, int balance);
int Savings_Balance(SavingsAccount *account);
void Savings_InitAccount(SavingsAccount *account);
void Savings_DestructAccount(SavingsAccount *account);
void Savings_ConstructAccount(SavingsAccount *account);

#endif
