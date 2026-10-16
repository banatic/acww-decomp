/* The town's shops as the players share them (shops.h). */
#include "shops.h"

#include <assert.h>
#include <stddef.h>

#include "clean.h"
#include "main/mail.h"
#include "main/session.h"

/* Message 39, the answer to message 38. */
#define SHOPS_MESSAGE_ANSWER 0x27

#define SHOPS_PLACE_MASK 0x3fu
#define SHOPS_AMOUNT_SHIFT 6
#define SHOPS_AMOUNT_MASK 0x7ffffu
#define SHOPS_FLAG_SHIFT 25
#define SHOPS_KIND_SHIFT 26

#define SHOPS_RANDOM_ITEMS 12

extern NetSession *data_020ccf94;
extern u32 data_021f395c[]; /* Nook's store; its first word the amount spent there */
extern u8 data_021f3b44[];
extern u8 data_021f3b30[];
/* The answers to wait for (byte 0) and those come (byte 1). */
extern u8 data_021f49ec[];
/* The pending state Shops_ApplyPending looks at. */
extern int data_021f4a04;
/* The items Shops_PickRandomItem picks from. */
extern const u16 data_020d1e5c[SHOPS_RANDOM_ITEMS];
/* "sp_npc_raccoon" and the two values func_02066024 takes with it */
extern const char data_020e4180[];
extern const u8 data_020e415c[];
extern const u8 data_020e4158[];

extern int func_020b6660(void);
extern int func_020aea84(void);
extern void func_020af3a0(u32 *store, int a);
extern void func_0209def4(u8 *now);  /* the minute, then the hour */
extern u32 func_020644cc(int range); /* a random number below `range` */
extern int func_020b01dc(u8 *answers);
extern void func_020b0200(u8 *answers);
extern int func_020afc5c(void);
extern void func_020adb70(int place, int amount, int kind, int flag, int mode, u8 send, int g);
extern int func_020b6744(u32 kind); /* whether the kind is one of Nook's */
extern void *func_ov004_02245ff8(int a, int b);
extern u16 *func_ov004_022460c8(int a, int b);
extern int func_020adf8c(u8 *list, int item);  /* the place of an item in data_021f3b30, or -1 */
extern int func_020ae8cc(u8 *list, u16 *item); /* the same in data_021f3b44 */
extern int func_020ada14(void);                /* not linked and the post office has room */
extern void func_02061e2c(u16 *out, const u16 *item);
extern void *func_02062f90(void *object, u16 *item);
extern void *func_02062f4c(void *object);
extern int func_0203d7c4(int index, void *object);
extern void func_02066694(MailLetter *letter); /* an empty letter */
extern void func_02066688(MailLetter *letter);
extern int func_020984e8(void); /* the current player */
extern int func_02099870(int player);
extern u32 func_020af028(u32 *store); /* the store's level */
extern void func_02066024(MailLetter *letter, void *sender, const char *name, const void *a, const void *b, int c);
extern u16 func_02065ed0(MailLetter *letter, u16 item, int a);
extern int func_0204c7f0(u16 *item); /* the item's price */
extern void func_020af750(u32 *store, u32 amount, u32 a);
extern u32 func_020996a0(u32 player);
extern u16 *func_020adf50(void *record);
extern void func_020ade0c(int record, int amount);

/* func_020ad74c: when func_020b6660 allows it, a pending state of 2 is carried out (unless
 * linked to other systems) and the state cleared. */
void Shops_ApplyPending(void)
{
    if (func_020b6660() == 0) {
        return;
    }
    if (Shops_PendingState() == 2) {
        if (Session_IsLinked(data_020ccf94) == 0) {
            func_020aea84();
            func_020af3a0(data_021f395c, 0);
        }
    }
    Shops_SetPendingState(0);
}
CLEAN_AS(func_020ad74c, Shops_ApplyPending)

/* func_020ad78c */
void Shops_SetPendingState(int state)
{
    data_021f4a04 = state;
}
CLEAN_AS(func_020ad78c, Shops_SetPendingState)

/* func_020ad798 */
int Shops_PendingState(void)
{
    return data_021f4a04;
}
CLEAN_AS(func_020ad798, Shops_PendingState)

/* func_020ad7a4: whether the clock's hour is 8 to 22. */
int Shops_IsHour8To22(void)
{
    u8 now[4];
    func_0209def4(now);
    u8 hour = now[1];
    return hour >= 8 && hour < 23;
}
CLEAN_AS(func_020ad7a4, Shops_IsHour8To22)

/* func_020ad7c8: one of twelve items at random. */
void Shops_PickRandomItem(u16 *out)
{
    *out = data_020d1e5c[func_020644cc(SHOPS_RANDOM_ITEMS)];
}
CLEAN_AS(func_020ad7c8, Shops_PickRandomItem)

/* func_020ad7e4: message 39 came; counts it. Returns whether all have come.
 * QUIRK: the sender's slot is not looked at. */
int Shops_CountAnswer(int slot)
{
    (void) slot;
    return func_020b01dc(data_021f49ec);
}
CLEAN_AS(func_020ad7e4, Shops_CountAnswer)

/* func_020ad7f4: applies message 38 from the system in `slot` without sending it on, and
 * answers it with message 39 unless it had no place. The flag goes to Nook's store's change
 * only; the others are given 1. A kind that is neither list's nor Nook's is not applied. */
void Shops_ApplyMessage(const u32 *payload, int slot)
{
    u32 word = *payload;
    int place = (int) (word & SHOPS_PLACE_MASK);
    int kind = (int) (word >> SHOPS_KIND_SHIFT);
    int flag = (int) ((word >> SHOPS_FLAG_SHIFT) & 1);

    if (kind == SHOPS_KIND_LIST_A) {
        func_020adb70(place, 0, kind, 1, 1, 0, 1);
    } else if (kind == SHOPS_KIND_LIST_B) {
        Shops_SetListBPlace(place, kind, 0, 1);
    } else if (func_020b6744((u32) kind) != 0) {
        int amount = (int) ((*payload >> SHOPS_AMOUNT_SHIFT) & SHOPS_AMOUNT_MASK);
        func_020adb70(place, amount, kind, flag, 0, 0, 1);
    }

    if (place != SHOPS_NO_PLACE) {
        NetSession *session = data_020ccf94;
        Session_BeginMessage(session);
        Session_EndMessage(session, SHOPS_MESSAGE_ANSWER, (u32) slot);
    }
}
CLEAN_AS(func_020ad7f4, Shops_ApplyMessage)

/* func_020ad888: whether every answer came (always, when not linked). */
int Shops_AllAnsweredA(void)
{
    return func_020afc5c();
}
CLEAN_AS(func_020ad888, Shops_AllAnsweredA)

/* func_020ad890: the item func_ov004_02245ff8 gives for (a, b) taken from data_021f3b30, sent
 * to the other systems, when it is there. */
void Shops_TakeFromListB(int a, int b, int kind)
{
    void *item = func_ov004_02245ff8(a, b);
    int place = func_020adf8c(data_021f3b30, (int) (uintptr_t) item);
    if (place != -1) {
        func_020b0200(data_021f49ec);
        Shops_SetListBPlace(place, kind, 1, 0);
    }
}
CLEAN_AS(func_020ad890, Shops_TakeFromListB)

/* func_020ad8d0 */
void Shops_SetListBPlace(int place, int kind, int send, int g)
{
    func_020adb70(place, 0, kind, 1, 2, (u8) send, g);
}
CLEAN_AS(func_020ad8d0, Shops_SetListBPlace)

/* func_020ad8f0: the same as Shops_AllAnsweredA. */
int Shops_AllAnsweredB(void)
{
    return func_020afc5c();
}
CLEAN_AS(func_020ad8f0, Shops_AllAnsweredB)

/* func_020ad8f8: the item func_ov004_022460c8 gives for (a, b) taken from data_021f3b44, sent
 * to the other systems, when it is there. */
void Shops_TakeFromListA(int a, int b, int kind)
{
    u16 item = *func_ov004_022460c8(a, b);
    int place = func_020ae8cc(data_021f3b44, &item);
    if (place != -1) {
        func_020b0200(data_021f49ec);
        func_020adb70(place, 0, kind, 1, 1, 1, 0);
    }
}
CLEAN_AS(func_020ad8f8, Shops_TakeFromListA)

/* func_020ad944: when not linked and the post office has room, a letter from Tom Nook
 * ("sp_npc_raccoon") carrying `item`, which waits at the post office; then the item's price
 * counts as spent at Nook's store and in the current player's record. Returns whether the
 * letter was posted. */
int Shops_MailNookItem(const u16 *item)
{
    struct {
        u8 store_level;
        u8 pad;
        u16 item;
    } sender;
    u8 object[0x28];
    MailLetter letter;

    if (func_020ada14() == 0) {
        return 0;
    }
    func_02061e2c(&sender.item, item);
    func_02062f90(object, &sender.item);
    func_0203d7c4(1, object);

    func_02066694(&letter);
    int player = func_020984e8();
    sender.store_level = (u8) func_020af028(data_021f395c);
    int c = func_02099870(player);
    func_02066024(&letter, &sender, data_020e4180, data_020e415c, data_020e4158, c);
    func_02065ed0(&letter, sender.item, 1);
    int price = func_0204c7f0(&sender.item);

    if (Mail_HoldAtPostOffice(&letter, 0) != 0) {
        func_020af750(data_021f395c, (u32) price, 1);
        u16 *record = func_020adf50((void *) (uintptr_t) func_020996a0((u32) func_020984e8()));
        func_020ade0c((int) (uintptr_t) record, price);
        func_02066688(&letter);
        func_02062f4c(object);
        return 1;
    }
    func_02066688(&letter);
    func_02062f4c(object);
    return 0;
}
CLEAN_AS(func_020ad944, Shops_MailNookItem)
