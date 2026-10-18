/* The bottle with a letter (bottle_mail.h). */
#include "bottle_mail.h"

#include "clean.h"
#include "mail.h"
#include "player_messages.h"
#include "session.h"
#include "acre_map.h"
#include "acre_tile.h"
#include "current_pockets.h"
#include "exchange_block.h"
#include "letter.h"
#include "main_random.h"
#include "player_record.h"
#include "player_records.h"
#include "town_beach.h"
#include "town_day.h"

/* The bottle's letter is not drawn for counts past this (it always arrives). */
#define DRIFT_DRAWS 5
/* BottleMail_DailyCheck's chance: this one of ten. */
#define NEW_BOTTLE_DRAW 7
/* The item marked in the player's record of items when the bottle is opened. */
#define MARKED_ITEM 0x1033

/* The bottle's letter and the bits of the game's messages used (func_02097e38, func_02097edc). */
extern BottleState data_021f36ec;
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

/* Set (`set`) or clear an item's bit in a record of items; mode 0 refuses some items. The
 * symbol's name is wrong: this is the game's code. */
extern int OSi_DoUnlockByWord__main_0203cd2c(void *items, u16 *item, int mode, int set);

/* func_02096c88: the letter in a bottle from another console arrives: at once with its flag,
 * else from count 1 on, by a draw of one in data_020d18c8[count] up to count 4 and always
 * after. It becomes the bottle's letter, and a bottle is put on the map if there is none. */
void BottleMail_ReceiveDrifting(void)
{
    u8 *pending = data_021ee418;
    if (ExchangeBlock_IsSendable((ExchangeBlock *) (void *) pending) == 0) {
        return;
    }
    MailLetter *letter = ExchangeBlock_BottleLetter((ExchangeBlock *) (void *) pending);
    if (Letter_State((const Letter *) letter) == 0) {
        return;
    }
    if (ExchangeBlock_ArrivesAtOnce((ExchangeBlock *) (void *) pending) == 0) {
        int count = ExchangeBlock_Drifts((ExchangeBlock *) (void *) pending);
        if (count == 0) {
            return;
        }
        if (count < DRIFT_DRAWS && MainRandom_Below(data_020d18c8[count]) != 1) {
            return;
        }
    }
    ExchangeBlock_ClearDrifts((ExchangeBlock *) (void *) pending);
    Letter_AdvanceWritten((Letter *) letter);
    Letter_Assign((Letter *) BottleMail_Letter(&data_021f36ec), (const Letter *) letter);
    Letter_Clear((Letter *) letter);
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
    BottleState *bottle = &data_021f36ec;
    if (Letter_State((const Letter *) BottleMail_Letter(bottle)) != 0) {
        BottleMail_PlaceOnMap();
        return;
    }
    if (MainRandom_Below(10) != NEW_BOTTLE_DRAW) {
        return;
    }
    int message = BottleMail_DrawMessage(bottle);
    u8 number = (u8) message;
    if (BottleMail_Write(&number) != 0) {
        BottleMail_MarkMessageUsed(bottle, message);
    }
}
CLEAN_AS(func_02096d10, BottleMail_DailyCheck)

/* func_02096d78: whether a bottle lies anywhere on the town's map. */
int BottleMail_IsOnMap(void)
{
    BottleMap *map = (BottleMap *) (uintptr_t) AcreMap_Town();
    for (int z = 0; z < map->height; z++) {
        for (int x = 0; x < map->width; x++) {
            u16 *item = AcreTile_ItemInAcre((AcreMap *) map, x >> 4, z >> 4, x & 15, z & 15, 0);
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
    return TownBeach_PutBottle(TownDay_Object());
}
CLEAN_AS(func_02096de0, BottleMail_PlaceOnMap)

/* func_02096df4: with no letter in the bottle, put a bottle on the map and, if that worked,
 * write message `*message` of "ev_bottle" as its letter; whether it was written. */
int BottleMail_Write(const u8 *message)
{
    MailLetter *bottle = BottleMail_Letter(&data_021f36ec);
    if (Letter_State((const Letter *) bottle) != 0) {
        return 0;
    }
    if (BottleMail_PlaceOnMap() == 0) {
        return 0;
    }
    Letter_WriteBottle((Letter *) bottle, message, data_020e3070);
    return 1;
}
CLEAN_AS(func_02096df4, BottleMail_Write)

/* func_02096e38: the bottle is opened: its letter goes to the current player's free place
 * (marking item 0x1033 in the player's record of items) and the bottle is emptied; a guest of
 * a linked session tells the host (player 0) to empty its own. 0 when the player has no room. */
int BottleMail_Open(void)
{
    MailLetter *place = CurrentPockets_FreeLetter();
    if (place == NULL) {
        return 0;
    }
    MailLetter *bottle = BottleMail_Letter(&data_021f36ec);
    if (Letter_State((const Letter *) bottle) == 0) {
        Letter_Clear((Letter *) bottle);
        return 1;
    }
    u16 item = MARKED_ITEM;
    OSi_DoUnlockByWord__main_0203cd2c(PlayerRecord_ItemRecord(PlayerRecords_Current()), &item, 0, 1);
    Letter_Assign((Letter *) place, (const Letter *) bottle);
    Letter_Clear((Letter *) bottle);
    NetSession *session = data_020ccf94;
    if (Session_IsLinked(session) && session->local_slot != 0) {
        PlayerMessages_Send(PLAYER_MESSAGE_CLEAR_RECORD, 0);
    }
    return 1;
}
CLEAN_AS(func_02096e38, BottleMail_Open)

/* ---- The bottle's letter and its used messages ---- */

extern void func_02066694(void *letter); /* a letter's constructor */

/* func_02097e38: one of the messages not used yet, at random; when all are used, all become
 * unused first. */
int BottleMail_DrawMessage(BottleState *bottle)
{
    int unused = 0;
    for (int i = 0; i < BOTTLE_MESSAGES; i++) {
        if (BottleMail_IsMessageUsed(bottle, i) == 0) {
            unused++;
        }
    }
    if (unused == 0) {
        BottleMail_ClearUsed(bottle);
        unused = BOTTLE_MESSAGES;
    }
    int skip = (int) MainRandom_Below(unused);
    for (int i = 0; i < BOTTLE_MESSAGES; i++) {
        if (BottleMail_IsMessageUsed(bottle, i) != 0) {
            continue;
        }
        if (skip <= 0) {
            return i;
        }
        skip--;
    }
    return 0;
}
CLEAN_AS(func_02097e38, BottleMail_DrawMessage)

/* func_02097e94: every message unused. */
void BottleMail_ClearUsed(BottleState *bottle)
{
    for (int i = 0; i < BOTTLE_USED_BYTES; i++) {
        bottle->used[i] = 0;
    }
}
CLEAN_AS(func_02097e94, BottleMail_ClearUsed)

/* func_02097eb0 */
int BottleMail_IsMessageUsed(BottleState *bottle, int message)
{
    return (bottle->used[message >> 3] & (1 << (message & 7))) != 0;
}
CLEAN_AS(func_02097eb0, BottleMail_IsMessageUsed)

/* func_02097edc */
void BottleMail_MarkMessageUsed(BottleState *bottle, int message)
{
    bottle->used[message >> 3] |= (u8) (1 << (message & 7));
}
CLEAN_AS(func_02097edc, BottleMail_MarkMessageUsed)

/* func_02097f00: no letter, every message unused. */
void BottleMail_InitState(BottleState *bottle)
{
    Letter_Clear((Letter *) &bottle->letter);
    BottleMail_ClearUsed(bottle);
}
CLEAN_AS(func_02097f00, BottleMail_InitState)

/* func_02097f14 */
MailLetter *BottleMail_Letter(BottleState *bottle)
{
    return &bottle->letter;
}
CLEAN_AS(func_02097f14, BottleMail_Letter)

/* func_02097f18: the destructor. */
BottleState *BottleMail_DestructState(BottleState *bottle)
{
    Letter_Destruct((Letter *) &bottle->letter);
    return bottle;
}
CLEAN_AS(func_02097f18, BottleMail_DestructState)

/* func_02097f28: the constructor. */
BottleState *BottleMail_ConstructState(BottleState *bottle)
{
    Letter_Construct((Letter *) &bottle->letter);
    return bottle;
}
CLEAN_AS(func_02097f28, BottleMail_ConstructState)

static_assert(offsetof(BottleState, used) == 0x100, "BottleState layout");
