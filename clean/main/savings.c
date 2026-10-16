/* The post office's savings (savings.h). */
#include "savings.h"

#include "clean.h"
#include "mail.h"

#define NO_ITEM 0xfff1

/* The message entries the letters fill in. */
#define TOWN_NAME_ENTRY 0
#define INTEREST_ENTRY 1

/* The interest letter's message, and the first of the savings steps' letters. */
#define INTEREST_MESSAGE 0
#define MILESTONE_MESSAGE 0x15

/* Interest: 10 bells for every 2000 in the account, each month, at most 99,999 at a time. */
#define INTEREST_UNIT 2000
#define INTEREST_PER_UNIT 10
#define INTEREST_MAX 99999

/* The town-wide amount behind the ranks. */
typedef struct SavingsTotals {
    u8 unk_00[0x40];
    u32 total;
} SavingsTotals;

/* An 8-bit text object (0x20 bytes) the town's name is put in. */
typedef struct SavingsText8 {
    u8 bytes[0x20];
} SavingsText8;

/* A number written as text (0x40 bytes). */
typedef struct SavingsNumberText {
    u8 bytes[0x40];
} SavingsNumberText;

extern SavingsTotals data_021ef8a8;
extern const u8 data_021dc7aa[];   /* the town's name */
extern const char data_020e3118[]; /* "sp_npc_pelican" */
/* The letters' kind bytes and papers: the rank letter's, the steps' and the interest's. */
extern u8 data_020e3100[], data_020e3114[];
extern u8 data_020e3108[], data_020e3104[];
extern u8 data_020e3110[], data_020e310c[];

extern void *func_020984e8(void);                   /* the current player's record */
extern SavingsAccount *func_020992fc(void *player); /* its account (0x23e0) */
extern void *func_02099870(void *player);           /* its name (0x247e) */
extern int func_02099020(void *player, u32 flag);   /* a flag of its record */
extern void func_02098fd0(void *player, u32 flag);  /* clear it */
extern void func_02098ff8(void *player, u32 flag);  /* set it */
extern int func_0206f798(void);                     /* global flag 0x20 (func_0206fec8): no interest */
extern void func_02066694(MailLetter *letter);      /* construct */
extern void func_02066688(MailLetter *letter);      /* destruct */
/* Write the letter: message `*message` of template `name`; *kind goes to byte 0xfb, *paper to
 * byte 0xf9. */
extern void func_02066024(MailLetter *letter, u8 *message, const char *name, u8 *kind, u8 *paper, void *player_name);
extern u16 func_02065ed0(MailLetter *letter, u16 item, int arg); /* attach an item */
extern void *func_020641c8(SavingsText8 *text);                  /* construct */
extern void *func_020641b0(SavingsText8 *text);                  /* destruct */
extern void func_02064210(const u8 *town, SavingsText8 *text);
extern int func_0203d7c4(int entry, void *text); /* set a message entry */
extern void *func_020b5630(SavingsNumberText *text);
extern void *func_020b5618(SavingsNumberText *text);
extern int func_020b45d0(SavingsNumberText *text, int value, int base, int a3, int a4, u8 a5);

/* The present of a rank's letter, NO_ITEM for none. */
static u16 savings_rank_present(int rank)
{
    switch (rank) {
        case 1:
            return 0x13fe;
        case 4:
            return 0x13ff;
        case 7:
            return 0x1400;
        case 10:
            return 0x1401;
        case 13:
            return 0x1402;
        case 16:
            return 0x1403;
        case 20:
            return 0x1404;
        default:
            return NO_ITEM;
    }
}

/* func_020980f0: `days` days on, with SAVINGS_FLAG_RANK_LETTER set, write the letter for the
 * account's rank (with its present) and post it; once it is posted, the flag is cleared. */
void Savings_SendRankLetter(int days)
{
    void *player = func_020984e8();
    SavingsAccount *account = func_020992fc(player);
    if (days <= 0 || func_02099020(player, SAVINGS_FLAG_RANK_LETTER) == 0) {
        return;
    }
    int rank = Savings_Rank(account);
    MailLetter letter;
    func_02066694(&letter);
    u8 message = (u8) rank;
    func_02066024(&letter, &message, data_020e3118, data_020e3100, data_020e3114, func_02099870(player));
    u16 present = savings_rank_present(rank);
    if (present != NO_ITEM) {
        func_02065ed0(&letter, present, 1);
    }
    if (Mail_Post(&letter) != 0) {
        func_02098fd0(player, SAVINGS_FLAG_RANK_LETTER);
    }
    func_02066688(&letter);
}
CLEAN_AS(func_020980f0, Savings_SendRankLetter)

/* func_020981f4: `days` days on, the letter for the highest savings step the balance has
 * reached (1, 10, 100 and 500 million, and the full SAVINGS_MAX), with its present and the
 * town's name, unless that step's letter was sent before; once posted, the step is marked sent.
 * QUIRK: only the highest step is looked at; a lower one whose letter never came is skipped. */
void Savings_SendMilestoneLetter(int days)
{
    void *player = func_020984e8();
    SavingsAccount *account = func_020992fc(player);
    if (days <= 0) {
        return;
    }
    int balance = Savings_Balance(account);
    if (balance < 1000000) {
        return;
    }
    int step;
    u16 present;
    if (balance == SAVINGS_MAX) {
        step = 4;
        present = 0x3874;
    } else if (balance >= 500000000) {
        step = 3;
        present = 0x4a44;
    } else if (balance >= 100000000) {
        step = 2;
        present = 0x4a40;
    } else if (balance >= 10000000) {
        step = 1;
        present = 0x3700;
    } else {
        step = 0;
        present = 0x37dc;
    }
    u32 flag = (u32) (SAVINGS_FLAG_MILESTONE + step);
    if (func_02099020(player, flag) != 0) {
        return;
    }
    u8 message = (u8) (MILESTONE_MESSAGE + step);
    MailLetter letter;
    SavingsText8 town;
    func_02066694(&letter);
    func_020641c8(&town);
    func_02064210(data_021dc7aa, &town);
    func_0203d7c4(TOWN_NAME_ENTRY, &town);
    func_02066024(&letter, &message, data_020e3118, data_020e3108, data_020e3104, func_02099870(player));
    func_02065ed0(&letter, present, 1);
    if (Mail_Post(&letter) != 0) {
        func_02098ff8(player, flag);
    }
    func_020641b0(&town);
    func_02066688(&letter);
}
CLEAN_AS(func_020981f4, Savings_SendMilestoneLetter)

/* The interest for `months` months on `balance`.
 * BUG: the product wraps past 2^31 (a full account after more than 429 months), and a wrapped
 * amount can be negative, which then lowers the balance. BUGFIX: compute it in 64 bits. */
static int savings_interest(int balance, int months)
{
#ifdef BUGFIX
    long long interest = (long long) (balance / INTEREST_UNIT) * months * INTEREST_PER_UNIT;
    return interest > INTEREST_MAX ? INTEREST_MAX : (int) interest;
#else
    int interest = (int) ((u32) (balance / INTEREST_UNIT) * (u32) months * INTEREST_PER_UNIT);
    return interest > INTEREST_MAX ? INTEREST_MAX : interest;
#endif
}

/* func_020982f8: `months` months on (unless global flag 0x20 is set), add the interest to the
 * account, up to SAVINGS_MAX, and send a letter with the amount. Nothing when the interest is 0
 * or the account is full.
 * QUIRK: the interest is added whether the letter could be posted or not. */
void Savings_PayInterest(int months)
{
    void *player = func_020984e8();
    SavingsAccount *account = func_020992fc(player);
    if (func_0206f798() != 0 || months <= 0) {
        return;
    }
    int balance = Savings_Balance(account);
    int interest = savings_interest(balance, months);
    if (interest == 0 || balance == SAVINGS_MAX) {
        return;
    }
    int total = balance + interest;
    if (total > SAVINGS_MAX) {
        total = SAVINGS_MAX;
    }
    Savings_SetBalance(account, total);

    MailLetter letter;
    SavingsNumberText amount;
    func_02066694(&letter);
    u8 message = INTEREST_MESSAGE;
    func_020b5630(&amount);
    func_020b45d0(&amount, interest, 10, 0, 0, 0);
    func_0203d7c4(INTEREST_ENTRY, &amount);
    func_02066024(&letter, &message, data_020e3118, data_020e3110, data_020e310c, func_02099870(player));
    Mail_Post(&letter);
    func_020b5618(&amount);
    func_02066688(&letter);
}
CLEAN_AS(func_020982f8, Savings_PayInterest)

/* func_020983c0 */
void Savings_SetRank(SavingsAccount *account, int rank)
{
    account->rank = (u8) rank;
}
CLEAN_AS(func_020983c0, Savings_SetRank)

/* func_020983c4 */
int Savings_Rank(SavingsAccount *account)
{
    return account->rank;
}
CLEAN_AS(func_020983c4, Savings_Rank)

/* func_020983c8: set the town-wide amount, at most SAVINGS_MAX. */
void Savings_SetTotal(int total)
{
    if (total > SAVINGS_MAX) {
        total = SAVINGS_MAX;
    }
    data_021ef8a8.total = (u32) total;
}
CLEAN_AS(func_020983c8, Savings_SetTotal)

/* func_020983e0 */
u32 Savings_Total(void)
{
    return data_021ef8a8.total;
}
CLEAN_AS(func_020983e0, Savings_Total)

/* func_020983ec */
void Savings_SetBalance(SavingsAccount *account, int balance)
{
    account->balance = balance;
}
CLEAN_AS(func_020983ec, Savings_SetBalance)

/* func_020983f0 */
int Savings_Balance(SavingsAccount *account)
{
    return account->balance;
}
CLEAN_AS(func_020983f0, Savings_Balance)

/* func_020983f4: no bells, no rank. */
void Savings_InitAccount(SavingsAccount *account)
{
    account->balance = 0;
    account->rank = 0;
}
CLEAN_AS(func_020983f4, Savings_InitAccount)

/* func_020983fc: the destructor (of a player record, func_02099ad0): nothing to do. */
void Savings_DestructAccount(SavingsAccount *account)
{
    (void) account;
}
CLEAN_AS(func_020983fc, Savings_DestructAccount)

/* func_02098400: the constructor (of a player record, func_02099bc8): nothing to do. */
void Savings_ConstructAccount(SavingsAccount *account)
{
    (void) account;
}
CLEAN_AS(func_02098400, Savings_ConstructAccount)

static_assert(offsetof(SavingsAccount, rank) == 4, "SavingsAccount layout");
static_assert(offsetof(SavingsTotals, total) == 0x40, "SavingsTotals layout");
