/* A player's shop points (shop_points.h). */
#include "shop_points.h"

#include "clean.h"
#include "main/mail.h"
#include "main/session.h"

/* The first letter's flag in the player's record; the others follow it. */
#define SHOP_POINTS_LETTER_FLAG 0x1c
#define SHOP_POINTS_LETTERS 4

extern NetSession *data_020ccf94;
/* The lowest count of each level. */
extern const u16 data_020d1e3c[SHOP_POINTS_LEVELS];
/* The item each level's letter carries (for levels 1 to 4). */
extern const u16 data_020d1e34[SHOP_POINTS_LETTERS];
/* "sp_npc_atm", the letters' sender, and the two values func_02066024 takes with it. */
extern const char data_020e4190[];
extern const u8 data_020e4150[];
extern const u8 data_020e4154[];
/* Nook's store (shops.h). */
extern u32 data_021f395c[];

extern int func_020afb24(u32 *store);              /* whether today's points count five times */
extern void *func_020984e8(void);                  /* this system's player record, or NULL */
extern u16 *func_020996a0(void *player);           /* the record's shop points */
extern void *func_02099870(void *player);          /* the record's name */
extern int func_02099020(void *player, int flag);  /* whether the record has `flag` */
extern void func_02098ff8(void *player, int flag); /* sets `flag` in the record */
extern void func_02066694(MailLetter *letter);     /* an empty letter */
extern void func_02066688(MailLetter *letter);
extern void func_02066024(MailLetter *letter, u8 *message, const char *name, const void *a, const void *b, void *player_name);
extern u16 func_02065ed0(MailLetter *letter, u16 item, int a); /* puts the item in the letter */

/* func_020adda8: what is left to reach the next level, 0 at the top level. */
u16 ShopPoints_ToNextLevel(u16 *count)
{
    int level = ShopPoints_Level(*count);
    if (level == SHOP_POINTS_TOP_LEVEL) {
        return 0;
    }
    return (u16) (ShopPoints_Threshold((unsigned) level + 1) - *count);
}
CLEAN_AS(func_020adda8, ShopPoints_ToNextLevel)

/* func_020addd0: the lowest count of `level`, 0 past the last. */
u16 ShopPoints_Threshold(unsigned level)
{
    if (level < SHOP_POINTS_LEVELS) {
        return data_020d1e3c[level];
    }
    return 0;
}
CLEAN_AS(func_020addd0, ShopPoints_Threshold)

/* func_020adde4: the highest level whose threshold `count` reaches. */
int ShopPoints_Level(unsigned int count)
{
    for (int level = SHOP_POINTS_TOP_LEVEL; level >= 0; level--) {
        if (count >= ShopPoints_Threshold((unsigned) level)) {
            return level;
        }
    }
    return 0;
}
CLEAN_AS(func_020adde4, ShopPoints_Level)

/* func_020ade0c: the points for `spent` at Nook's store, one per 100, five times that on the
 * days func_020afb24 picks.
 * QUIRK: both the points and the multiplied points are cut to 16 bits. */
void ShopPoints_AddSpent(u16 *count, int spent)
{
    u16 points = (u16) (spent / 100);
    if (func_020afb24(data_021f395c) != 0) {
        points = (u16) (points * 5);
    }
    ShopPoints_Add(count, points);
}
CLEAN_AS(func_020ade0c, ShopPoints_AddSpent)

/* func_020ade44: adds `points` up to SHOP_POINTS_MAX; a new level sends its letters.
 * QUIRK: a sum below 0 is not held at 0, it wraps to 16 bits. */
void ShopPoints_Add(u16 *count, int points)
{
    int before = ShopPoints_Level(*count);
    int sum = points + *count;
    if (sum >= SHOP_POINTS_MAX) {
        sum = SHOP_POINTS_MAX;
    }
    *count = (u16) sum;
    if (before != ShopPoints_Level(*count)) {
        ShopPoints_SendLevelLetters();
    }
}
CLEAN_AS(func_020ade44, ShopPoints_Add)

/* func_020ade78: when not linked, the letter of each level from 1 up to the player's that has
 * not gone out yet, held at the post office; one that found room there is marked sent. Level
 * n's letter is message n - 1 of "sp_npc_atm". */
void ShopPoints_SendLevelLetters(void)
{
    if (Session_IsLinked(data_020ccf94) != 0) {
        return;
    }
    void *player = func_020984e8();
    if (player == NULL) {
        return;
    }
    unsigned level = (unsigned) ShopPoints_Level(*ShopPoints_Count(func_020996a0(player)));
    if (level == 0) {
        return;
    }
    for (unsigned i = 0; i < level; i++) {
        int flag = (int) i + SHOP_POINTS_LETTER_FLAG;
        if (i < SHOP_POINTS_LETTERS && func_02099020(player, flag) == 0) {
            MailLetter letter;
            u8 message;
            func_02066694(&letter);
            message = (u8) i;
            func_02066024(&letter, &message, data_020e4190, data_020e4150, data_020e4154, func_02099870(player));
            func_02065ed0(&letter, data_020d1e34[i], 1);
            if (Mail_HoldAtPostOffice(&letter, 0) != 0) {
                func_02098ff8(player, flag);
            }
            func_02066688(&letter);
        }
    }
}
CLEAN_AS(func_020ade78, ShopPoints_SendLevelLetters)

/* func_020adf34 */
void ShopPoints_Clear(u16 *count)
{
    *count = 0;
}
CLEAN_AS(func_020adf34, ShopPoints_Clear)

/* func_020adf3c */
void ShopPoints_DoNothing(void) {}
CLEAN_AS(func_020adf3c, ShopPoints_DoNothing)

/* func_020adf40: the constructor: the count starts at 0. Returns the count's address. */
u32 ShopPoints_Construct(u32 count)
{
    ShopPoints_Clear((u16 *) (uintptr_t) count);
    return count;
}
CLEAN_AS(func_020adf40, ShopPoints_Construct)

/* func_020adf50: the count of the points. */
u16 *ShopPoints_Count(void *points)
{
    return points;
}
CLEAN_AS(func_020adf50, ShopPoints_Count)

/* func_020adf54 */
void ShopPoints_ResetA(void *count)
{
    ShopPoints_ResetB(count);
}
CLEAN_AS(func_020adf54, ShopPoints_ResetA)

/* func_020adf5c */
void ShopPoints_ResetB(void *count)
{
    ShopPoints_Clear(count);
}
CLEAN_AS(func_020adf5c, ShopPoints_ResetB)

/* func_020adf64: the destructor, which does nothing. Returns the count's address. */
u32 ShopPoints_Destruct(u32 count)
{
    ShopPoints_DoNothing();
    return count;
}
CLEAN_AS(func_020adf64, ShopPoints_Destruct)

/* func_020adf74: constructs the count, then clears it again. */
int ShopPoints_ConstructAndReset(int count)
{
    ShopPoints_Construct((u32) count);
    ShopPoints_ResetA((void *) (uintptr_t) count);
    return count;
}
CLEAN_AS(func_020adf74, ShopPoints_ConstructAndReset)
