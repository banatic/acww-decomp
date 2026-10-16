/* The bottle with a letter (bottle_mail.h). */
#include "bottle_mail.h"

#include "clean.h"
#include "mail.h"
#include "player_messages.h"
#include "session.h"

/* The bottle's letter is not drawn for counts past this (it always arrives). */
#define DRIFT_DRAWS 5
/* BottleMail_DailyCheck's chance: this one of ten. */
#define NEW_BOTTLE_DRAW 7
/* The item marked in the player's record of items when the bottle is opened. */
#define MARKED_ITEM 0x1033

/* The bottle's letter and the bits of the game's messages used (func_02097e38, func_02097edc). */
extern MailLetter data_021f36ec;
/* The letter in a bottle from another console (0x100 bytes), with a count at 0x938
 * (func_020900f4, func_02090100) and a flag in bit 0 of byte 0x939 (func_02090130). */
extern u8 data_021ee418[];
/* For each count 1-4, one in this many draws lets the letter arrive. */
extern const u8 data_020d18c8[DRIFT_DRAWS];
extern const char data_020e3070[]; /* "ev_bottle" */
extern u8 data_021c779c[];
extern NetSession *data_020ccf94; /* the session */

/* The town's items: blocks (0x28 bytes) of 16 by 16 items. */
typedef struct BottleMap {
    void *blocks;
    int blocks_wide;
    int blocks_high;
    int width; /* in items */
    int height;
} BottleMap;

extern u32 func_020644cc(int bound);               /* a random number below `bound` */
extern u8 func_02065ec0(const MailLetter *letter); /* its state; 0: no letter */
extern void func_02066650(MailLetter *letter);     /* empty it */
extern int func_02066830(MailLetter *dst, const MailLetter *src);
extern void func_020664e0(MailLetter *letter); /* move its state on */
extern MailLetter *func_02097f14(MailLetter *letter);
extern int func_02090158(u8 *pending);
extern MailLetter *func_020900f0(u8 *pending);
extern int func_02090130(u8 *pending);
extern u8 func_020900f4(u8 *pending);
extern void func_02090100(u8 *pending);
extern int func_02097e38(MailLetter *bottle);               /* an unused message, at random (all used: all freed) */
extern void func_02097edc(MailLetter *bottle, int message); /* mark it used */
extern u32 func_0204e414(void);                             /* the town's BottleMap */
extern u16 *func_0204f5e0(BottleMap *map, int block_x, int block_z, int x, int z, int layer);
extern u8 *func_0204677c(void);
extern int func_02046ebc(u8 *place); /* put a bottle on the map; whether it was */
/* Write the letter: message `*message` of template `name`. */
extern void func_02065f88(MailLetter *letter, const u8 *message, const char *name);
extern MailLetter *func_0209a1d0(void);   /* the current player's free place for a letter, or NULL */
extern void *func_020984e8(void);         /* the current player's record */
extern void *func_020996ac(void *player); /* its record of items (0x1c18) */
/* Set (`set`) or clear an item's bit in a record of items; mode 0 refuses some items. The
 * symbol's name is wrong: this is the game's code. */
extern int OSi_DoUnlockByWord__main_0203cd2c(void *items, u16 *item, int mode, int set);

/* func_02096c88: the letter in a bottle from another console arrives: at once with its flag,
 * else from count 1 on, by a draw of one in data_020d18c8[count] up to count 4 and always
 * after. It becomes the bottle's letter, and a bottle is put on the map if there is none. */
void BottleMail_ReceiveDrifting(void)
{
    u8 *pending = data_021ee418;
    if (func_02090158(pending) == 0) {
        return;
    }
    MailLetter *letter = func_020900f0(pending);
    if (func_02065ec0(letter) == 0) {
        return;
    }
    if (func_02090130(pending) == 0) {
        int count = func_020900f4(pending);
        if (count == 0) {
            return;
        }
        if (count < DRIFT_DRAWS && func_020644cc(data_020d18c8[count]) != 1) {
            return;
        }
    }
    func_02090100(pending);
    func_020664e0(letter);
    func_02066830(func_02097f14(&data_021f36ec), letter);
    func_02066650(letter);
    if (BottleMail_IsOnMap() != 0) {
        return;
    }
    BottleMail_PlaceOnMap();
}
CLEAN_AS(func_02096c88, BottleMail_ReceiveDrifting)

/* func_02096d10: the day's update, `days` days on: with no bottle on the map, put one there
 * for the bottle's letter; with no letter, one time in ten write one of the game's messages
 * not used yet and mark it used. */
void BottleMail_DailyCheck(int days)
{
    if (days <= 0) {
        return;
    }
    if (BottleMail_IsOnMap() != 0) {
        return;
    }
    MailLetter *bottle = &data_021f36ec;
    if (func_02065ec0(func_02097f14(bottle)) != 0) {
        BottleMail_PlaceOnMap();
        return;
    }
    if (func_020644cc(10) != NEW_BOTTLE_DRAW) {
        return;
    }
    int message = func_02097e38(bottle);
    u8 number = (u8) message;
    if (BottleMail_Write(&number) != 0) {
        func_02097edc(bottle, message);
    }
}
CLEAN_AS(func_02096d10, BottleMail_DailyCheck)

/* func_02096d78: whether a bottle lies anywhere on the town's map. */
int BottleMail_IsOnMap(void)
{
    BottleMap *map = (BottleMap *) (uintptr_t) func_0204e414();
    for (int z = 0; z < map->height; z++) {
        for (int x = 0; x < map->width; x++) {
            u16 *item = func_0204f5e0(map, x >> 4, z >> 4, x & 15, z & 15, 0);
            if (item != NULL && *item == BOTTLE_ITEM) {
                return 1;
            }
        }
    }
    return 0;
}
CLEAN_AS(func_02096d78, BottleMail_IsOnMap)

/* func_02096de0: put a bottle on the map; whether one was. */
int BottleMail_PlaceOnMap(void)
{
    return func_02046ebc(func_0204677c());
}
CLEAN_AS(func_02096de0, BottleMail_PlaceOnMap)

/* func_02096df4: with no letter in the bottle, put a bottle on the map and, if that worked,
 * write message `*message` of "ev_bottle" as its letter; whether it was written. */
int BottleMail_Write(const u8 *message)
{
    MailLetter *bottle = func_02097f14(&data_021f36ec);
    if (func_02065ec0(bottle) != 0) {
        return 0;
    }
    if (BottleMail_PlaceOnMap() == 0) {
        return 0;
    }
    func_02065f88(bottle, message, data_020e3070);
    return 1;
}
CLEAN_AS(func_02096df4, BottleMail_Write)

/* func_02096e38: the bottle is opened: its letter goes to the current player's free place
 * (marking item 0x1033 in the player's record of items) and the bottle is emptied; a guest of
 * a linked session tells the host (player 0) to empty its own. 0 when the player has no room. */
int BottleMail_Open(void)
{
    MailLetter *place = func_0209a1d0();
    if (place == NULL) {
        return 0;
    }
    MailLetter *bottle = func_02097f14(&data_021f36ec);
    if (func_02065ec0(bottle) == 0) {
        func_02066650(bottle);
        return 1;
    }
    u16 item = MARKED_ITEM;
    OSi_DoUnlockByWord__main_0203cd2c(func_020996ac(func_020984e8()), &item, 0, 1);
    func_02066830(place, bottle);
    func_02066650(bottle);
    NetSession *session = data_020ccf94;
    if (Session_IsLinked(session) && session->local_slot != 0) {
        PlayerMessages_Send(PLAYER_MESSAGE_CLEAR_RECORD, 0);
    }
    return 1;
}
CLEAN_AS(func_02096e38, BottleMail_Open)
