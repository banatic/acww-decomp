/* The post office's savings: each player's account (at 0x23e0 of the player's record) and the
 * letters the post office ("sp_npc_pelican") writes about it.
 *
 * When the game is played again on a later day (func_020991d4), the account earns interest for
 * each month since the last play (Savings_PayInterest, message 0), the player gets a letter for
 * the highest savings step reached, once each (Savings_SendMilestoneLetter, messages 0x15-0x19),
 * and a letter for the account's rank when it has risen (Savings_SendRankLetter, messages 1-20,
 * with a present at some ranks).
 *
 * The rank is the step (1-20) that a town-wide amount (Savings_Total, at data_021ef8a8 + 0x40)
 * has reached; overlay 54 adds amounts to it, sets the rank and flag SAVINGS_FLAG_RANK_LETTER of
 * the player's record. What that amount stands for in the game is not known yet. */
#ifndef CLEAN_MAIN_SAVINGS_H
#define CLEAN_MAIN_SAVINGS_H

#include "types.h"

/* The most bells an account or the town-wide amount holds. */
#define SAVINGS_MAX 999999999

/* A player's account (8 bytes at 0x23e0 of the record). */
typedef struct SavingsAccount {
    int balance;
    u8 rank;
} SavingsAccount;

/* The flags of the player's record (func_02099020) these letters use: one for each savings
 * step's letter sent (SAVINGS_FLAG_MILESTONE + step), and one for a rank letter to write. */
#define SAVINGS_FLAG_MILESTONE 0x11
#define SAVINGS_FLAG_RANK_LETTER 0x16

void Savings_SendRankLetter(int days);
void Savings_SendMilestoneLetter(int days);
void Savings_PayInterest(int months);
void Savings_SetRank(SavingsAccount *account, int rank);
int Savings_Rank(SavingsAccount *account);
void Savings_SetTotal(int total);
u32 Savings_Total(void);
void Savings_SetBalance(SavingsAccount *account, int balance);
int Savings_Balance(SavingsAccount *account);
void Savings_InitAccount(SavingsAccount *account);
void Savings_DestructAccount(SavingsAccount *account);
void Savings_ConstructAccount(SavingsAccount *account);

#endif
