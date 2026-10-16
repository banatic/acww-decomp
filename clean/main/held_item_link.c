/* A link from an actor to a held item (held_item_link.h). */
#include "held_item_link.h"

#include "clean.h"

static_assert(offsetof(HeldItem, scale) == 0x04, "HeldItem layout");
static_assert(offsetof(HeldItemLink, link) == 0x04, "HeldItemLink layout");
static_assert(offsetof(HeldItemLink, hand) == 0x0c, "HeldItemLink layout");
static_assert(offsetof(HeldItemLink, follows_hand) == 0x3c, "HeldItemLink layout");

#define HELD_ITEM_LINK_NONE 0xfff1

/* The joint of the owner's model whose matrix the item follows. */
#define HELD_ITEM_LINK_HAND_JOINT 14

/* The owner's model (an object whose func_02055d0c reads a joint's matrix) and the word it
 * hands to the item's record. */
#define HELD_ITEM_LINK_OWNER_MODEL 0xec
#define HELD_ITEM_LINK_OWNER_VALUE 0x198
#define HELD_ITEM_LINK_OWNER_MOTION 0x334

/* In a held item's pool record (func_0205e8e4): the word HeldItemLink_SetRecordValue sets. */
#define HELD_ITEM_LINK_RECORD_VALUE (0x9c + 0x10)

extern int func_02082c98(void *link);
extern void func_0205eac4(unsigned char *item, int value);
extern int func_0205e8e4(const unsigned char *item);
extern void func_0205e954(HeldItem *item, void *matrix);
extern int func_02055d0c(char *model, int matrix, int joint);
extern void func_0205ea60(HeldItem *item);
extern void func_02083068(void *link);
extern void func_0205eae0(u8 *item, int action, int a, int b);
extern void func_0205eb8c(void *item, void *code, int c);
extern void func_02016638(int motion, char *owner, unsigned short *code, int p3, unsigned short p4);
extern int func_0208308c(void *link);
extern int func_02082cb8(void *link, int arg);
extern void *func_02082d04(void *link);
extern void *func_02082d1c(void *link);

/* The held item the link stands for, or null. */
static HeldItem *held_item_link_item(HeldItemLink *link)
{
    return (HeldItem *) (uintptr_t) (u32) func_02082c98(link->link);
}

/* The item codes the actions 0 and 15 to 18 are for. */
static int held_item_link_is_1376(u16 item)
{
    return item == 0x1376 || item == 0x1377;
}

/* func_020121a8: the word at 0xac of the item's pool record (func_0205eac4) becomes `value`. */
void HeldItemLink_SetRecordValue(HeldItemLink *link, int value)
{
    HeldItem *item = held_item_link_item(link);
    if (item != NULL) {
        func_0205eac4(&item->index, value);
    }
}
CLEAN_AS(func_020121a8, HeldItemLink_SetRecordValue)

/* func_020121c4: the item's pool record (func_0205e8e4), or 0 without an item. */
int HeldItemLink_Record(HeldItemLink *link)
{
    HeldItem *item = held_item_link_item(link);
    if (item != NULL) {
        return func_0205e8e4(&item->index);
    }
    return 0;
}
CLEAN_AS(func_020121c4, HeldItemLink_Record)

/* func_020121e0: sets the item's scale; returns the item (null without one). */
HeldItem *HeldItemLink_SetScale(HeldItemLink *link, fx32 scale)
{
    HeldItem *item = held_item_link_item(link);
    if (item != NULL) {
        item->scale = scale;
    }
    return item;
}
CLEAN_AS(func_020121e0, HeldItemLink_SetScale)

/* func_020121f8: the item's scale, 0 without an item. */
fx32 HeldItemLink_Scale(HeldItemLink *link)
{
    HeldItem *item = held_item_link_item(link);
    if (item != NULL) {
        return item->scale;
    }
    return 0;
}
CLEAN_AS(func_020121f8, HeldItemLink_Scale)

/* func_02012214: when the link follows the hand, the matrix of joint 14 of the owner's model
 * (func_02055d0c; only with an owner) goes to `hand`, and the item is placed at `hand`
 * (func_0205e954). The item is looked up before the matrix is read. */
void HeldItemLink_FollowHand(HeldItemLink *link, void *owner)
{
    if (link->follows_hand == 0) {
        return;
    }
    HeldItem *item = held_item_link_item(link);
    if (owner != NULL) {
        func_02055d0c((char *) owner + HELD_ITEM_LINK_OWNER_MODEL, (int) (uintptr_t) link->hand, HELD_ITEM_LINK_HAND_JOINT);
    }
    if (item != NULL) {
        func_0205e954(item, link->hand);
    }
}
CLEAN_AS(func_02012214, HeldItemLink_FollowHand)

/* func_02012250: the word at 0x198 of the owner goes to the word at 0xac of the item's pool
 * record, then the item is updated (func_0205ea60). */
void HeldItemLink_UpdateFromOwner(HeldItemLink *link, void *owner)
{
    HeldItem *item = held_item_link_item(link);
    if (item != NULL) {
        int value = *(int *) ((u8 *) owner + HELD_ITEM_LINK_OWNER_VALUE);
        u8 *record = (u8 *) (uintptr_t) (u32) func_0205e8e4(&item->index);
        *(int *) (record + HELD_ITEM_LINK_RECORD_VALUE) = value;
        func_0205ea60(item);
    }
}
CLEAN_AS(func_02012250, HeldItemLink_UpdateFromOwner)

/* func_02012280: the link lets go of its item (func_02083068). */
void HeldItemLink_Release(HeldItemLink *link)
{
    func_02083068(link->link);
}
CLEAN_AS(func_02012280, HeldItemLink_Release)

/* func_020122ac: action 18 when `item` is 0x1376 or 0x1377. */
void HeldItemLink_Action18ByItem(HeldItemLink *link, const u16 *item, int a, int b)
{
    if (held_item_link_is_1376(*item)) {
        HeldItemLink_Act(link, 18, a, b);
    }
}
CLEAN_AS(func_020122ac, HeldItemLink_Action18ByItem)

/* func_0201228c: action 18 for the link's own item, unless it has none. */
void HeldItemLink_Action18(HeldItemLink *link, int a, int b)
{
    if (link->item != HELD_ITEM_LINK_NONE) {
        HeldItemLink_Action18ByItem(link, &link->item, a, b);
    }
}
CLEAN_AS(func_0201228c, HeldItemLink_Action18)

/* func_02012304: action 17 when `item` is 0x1376 or 0x1377. */
void HeldItemLink_Action17ByItem(HeldItemLink *link, const u16 *item, int a, int b)
{
    if (held_item_link_is_1376(*item)) {
        HeldItemLink_Act(link, 17, a, b);
    }
}
CLEAN_AS(func_02012304, HeldItemLink_Action17ByItem)

/* func_020122e4 */
void HeldItemLink_Action17(HeldItemLink *link, int a, int b)
{
    if (link->item != HELD_ITEM_LINK_NONE) {
        HeldItemLink_Action17ByItem(link, &link->item, a, b);
    }
}
CLEAN_AS(func_020122e4, HeldItemLink_Action17)

/* func_0201235c: action 16 when `item` is 0x1376 or 0x1377. */
void HeldItemLink_Action16ByItem(HeldItemLink *link, const u16 *item, int a, int b)
{
    if (held_item_link_is_1376(*item)) {
        HeldItemLink_Act(link, 16, a, b);
    }
}
CLEAN_AS(func_0201235c, HeldItemLink_Action16ByItem)

/* func_0201233c */
void HeldItemLink_Action16(HeldItemLink *link, int a, int b)
{
    if (link->item != HELD_ITEM_LINK_NONE) {
        HeldItemLink_Action16ByItem(link, &link->item, a, b);
    }
}
CLEAN_AS(func_0201233c, HeldItemLink_Action16)

/* func_020123b4: action 15 when `item` is 0x1376 or 0x1377. */
void HeldItemLink_Action15ByItem(HeldItemLink *link, const u16 *item, int a, int b)
{
    if (held_item_link_is_1376(*item)) {
        HeldItemLink_Act(link, 15, a, b);
    }
}
CLEAN_AS(func_020123b4, HeldItemLink_Action15ByItem)

/* func_02012394 */
void HeldItemLink_Action15(HeldItemLink *link, int a, int b)
{
    if (link->item != HELD_ITEM_LINK_NONE) {
        HeldItemLink_Action15ByItem(link, &link->item, a, b);
    }
}
CLEAN_AS(func_02012394, HeldItemLink_Action15)

/* func_0201240c: action 1 when `item` is 0x1376 or 0x1377. */
void HeldItemLink_Action1ByItem(HeldItemLink *link, const u16 *item, int a, int b)
{
    if (held_item_link_is_1376(*item)) {
        HeldItemLink_Act(link, 1, a, b);
    }
}
CLEAN_AS(func_0201240c, HeldItemLink_Action1ByItem)

/* func_020123ec */
void HeldItemLink_Action1(HeldItemLink *link, int a, int b)
{
    if (link->item != HELD_ITEM_LINK_NONE) {
        HeldItemLink_Action1ByItem(link, &link->item, a, b);
    }
}
CLEAN_AS(func_020123ec, HeldItemLink_Action1)

/* func_02012464: action 0 (with `a` and `b`) for 0x1376 and 0x1377, action 0x13 for 0x1374
 * and 0x1375 and action 0x25 for 0x1380 to 0x139f (both with 0 and 0). */
void HeldItemLink_Action0ByItem(HeldItemLink *link, const u16 *item, int a, int b)
{
    u16 code = *item;
    if (held_item_link_is_1376(code)) {
        HeldItemLink_Act(link, 0, a, b);
    } else if (code == 0x1374 || code == 0x1375) {
        HeldItemLink_Act(link, 0x13, 0, 0);
    } else if (code >= 0x1380 && code <= 0x139f) {
        HeldItemLink_Act(link, 0x25, 0, 0);
    }
}
CLEAN_AS(func_02012464, HeldItemLink_Action0ByItem)

/* func_02012444 */
void HeldItemLink_Action0(HeldItemLink *link, int a, int b)
{
    if (link->item != HELD_ITEM_LINK_NONE) {
        HeldItemLink_Action0ByItem(link, &link->item, a, b);
    }
}
CLEAN_AS(func_02012444, HeldItemLink_Action0)

/* func_020124e4: the item, if there is one, takes the action (func_0205eae0). */
void HeldItemLink_Act(HeldItemLink *link, int action, int a, int b)
{
    HeldItem *item = held_item_link_item(link);
    if (item != NULL) {
        func_0205eae0(&item->index, action, a, b);
    }
}
CLEAN_AS(func_020124e4, HeldItemLink_Act)

/* func_02012508: with an item, it becomes the item of code `*item` (func_0205eb8c), the owner's
 * motion at 0x334 is told (func_02016638 with the other arguments), the link takes the code and
 * the answer is 1; without an item, 0. */
int HeldItemLink_Take(HeldItemLink *link, void *owner, u16 *item, void *p3, u16 p4)
{
    HeldItem *held = held_item_link_item(link);
    if (held == NULL) {
        return 0;
    }
    func_0205eb8c(held, item, 0);
    func_02016638((int) (uintptr_t) ((u8 *) owner + HELD_ITEM_LINK_OWNER_MOTION), (char *) owner, item, (int) (uintptr_t) p3,
                  p4);
    link->item = *item;
    return 1;
}
CLEAN_AS(func_02012508, HeldItemLink_Take)

/* func_02012550: the link gets a number in its pool if it has none (func_0208308c), then is
 * opened with `arg` (func_02082cb8); when both succeed the link holds no item code and the
 * answer is 1, else 0. */
int HeldItemLink_Open(HeldItemLink *link, void *arg)
{
    if (!func_0208308c(link->link)) {
        return 0;
    }
    if (!func_02082cb8(link->link, (int) (uintptr_t) arg)) {
        return 0;
    }
    link->item = HELD_ITEM_LINK_NONE;
    return 1;
}
CLEAN_AS(func_02012550, HeldItemLink_Open)

/* func_02012588: the constructor; only the link object is built (the code stays as it was). */
HeldItemLink *HeldItemLink_Construct(HeldItemLink *link)
{
    func_02082d04(link->link);
    return link;
}
CLEAN_AS(func_02012588, HeldItemLink_Construct)

/* func_0201259c: the destructor: no item code, the link object destroyed (func_02082d1c). */
HeldItemLink *HeldItemLink_Destruct(HeldItemLink *link)
{
    link->item = HELD_ITEM_LINK_NONE;
    func_02082d1c(link->link);
    link->item = HELD_ITEM_LINK_NONE;
    return link;
}
CLEAN_AS(func_0201259c, HeldItemLink_Destruct)
