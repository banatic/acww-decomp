/* A link from an actor to a held item: the item's code, and a link object (class 0x020e1a40,
 * PoolLink_ItemConstruct builds it) whose func_02082c98 gives the held item it stands for, or null.
 * The held items are kept in a pool at data_021ca16c and the functions 0x0205e8e4 to 0x0205f1bc
 * work on them (the first byte of one is its number in the pool, func_0205f130 its record).
 *
 * A field actor keeps a pointer to one at 0x628 (func_0201b910, func_02019144, func_02017258);
 * the actors of overlay 68 have one in them at 0x9b4. The functions here pass on to the held
 * item, many of them only for some item codes: 0x1376 and 0x1377, 0x1374 and 0x1375, and
 * 0x1380 to 0x139f. */
#ifndef CLEAN_MAIN_HELD_ITEM_LINK_H
#define CLEAN_MAIN_HELD_ITEM_LINK_H

#include "types.h"

/* What the link object's func_02082c98 gives: the first byte is the item's number in the pool,
 * the word at 4 its scale (func_0205e954 scales the item's model by it on all three axes). */
typedef struct HeldItem {
    u8 index;
    u8 unk_01[3];
    fx32 scale;
} HeldItem;

typedef struct HeldItemLink {
    u16 item; /* 0x00: the item's code, 0xfff1 for none */
    u16 unk_02;
    u8 link[8];      /* 0x04: the link object (a vtable and the number in its pool) */
    u8 hand[0x30];   /* 0x0c: the matrix the item is drawn at (an Mtx43) */
    u8 follows_hand; /* 0x3c: whether HeldItemLink_FollowHand updates it */
} HeldItemLink;

void HeldItemLink_SetRecordValue(HeldItemLink *link, int value);
int HeldItemLink_Record(HeldItemLink *link);
HeldItem *HeldItemLink_SetScale(HeldItemLink *link, fx32 scale);
fx32 HeldItemLink_Scale(HeldItemLink *link);
void HeldItemLink_FollowHand(HeldItemLink *link, void *owner);
void HeldItemLink_UpdateFromOwner(HeldItemLink *link, void *owner);
void HeldItemLink_Release(HeldItemLink *link);
void HeldItemLink_Action18(HeldItemLink *link, int a, int b);
void HeldItemLink_Action18ByItem(HeldItemLink *link, const u16 *item, int a, int b);
void HeldItemLink_Action17(HeldItemLink *link, int a, int b);
void HeldItemLink_Action17ByItem(HeldItemLink *link, const u16 *item, int a, int b);
void HeldItemLink_Action16(HeldItemLink *link, int a, int b);
void HeldItemLink_Action16ByItem(HeldItemLink *link, const u16 *item, int a, int b);
void HeldItemLink_Action15(HeldItemLink *link, int a, int b);
void HeldItemLink_Action15ByItem(HeldItemLink *link, const u16 *item, int a, int b);
void HeldItemLink_Action1(HeldItemLink *link, int a, int b);
void HeldItemLink_Action1ByItem(HeldItemLink *link, const u16 *item, int a, int b);
void HeldItemLink_Action0(HeldItemLink *link, int a, int b);
void HeldItemLink_Action0ByItem(HeldItemLink *link, const u16 *item, int a, int b);
void HeldItemLink_Act(HeldItemLink *link, int action, int a, int b);
int HeldItemLink_Take(HeldItemLink *link, void *owner, u16 *item, void *p3, u16 p4);
int HeldItemLink_Open(HeldItemLink *link, void *arg);
HeldItemLink *HeldItemLink_Destruct(HeldItemLink *link);
HeldItemLink *HeldItemLink_Construct(HeldItemLink *link);

#endif
