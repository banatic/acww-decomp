/* The record of items a player has had (the catalog), kept in the player's record at 0x1c18
 * (PlayerRecord_ItemRecord): one bit per item, in five parts by kind of item code.
 *
 *   0x000-0x0ff  the items with variants (codes 0x3000-0x4fff), by ItemCode_VariantItem
 *   0x100-0x108  the items 0x1100-0x1143 (wallpaper; 68 bits)
 *   0x109-0x111  the carpets 0x1144-0x1187 (68 bits)
 *   0x112-0x11a  the songs 0x1323-0x1368 (70 bits)
 *   0x11b-0x122  the items in piles 0x1000-0x10ff, by ItemCode_PileItem (64 bits)
 *
 * Within a byte, bit n is the item 8 * byte + n of its part. Items of any other code have no
 * bit. The insects (0x12b0-0x12e7) and the fish (0x12e8-0x131f) are counted against their
 * whole list (ItemRecord_CountHad). */
#ifndef CLEAN_MAIN_ITEM_RECORD_H
#define CLEAN_MAIN_ITEM_RECORD_H

#include "lookups.h" /* ItemCode */
#include "types.h"

#define ITEM_RECORD_INSECT_FIRST 0x12b0
#define ITEM_RECORD_FISH_FIRST 0x12e8
#define ITEM_RECORD_CREATURE_KINDS 56

typedef struct ItemRecord {
    u8 variant_items[0x100]; /* 0x000 */
    u8 wallpaper[9];         /* 0x100 */
    u8 carpets[9];           /* 0x109 */
    u8 songs[9];             /* 0x112 */
    u8 pile_items[8];        /* 0x11b */
} ItemRecord;

/* How an item is marked: checked (the insects, the fish and the variant items 0x42a4-0x4463
 * are refused) or any item. */
enum ItemRecordMarkMode { ITEM_RECORD_MARK_CHECKED = 0, ITEM_RECORD_MARK_ANY = 1 };

int ItemRecord_MarkHadByCurrent(const ItemCode *item);
int ItemRecord_CountInsects(void);
int ItemRecord_CountFish(void);
int ItemRecord_InsectKinds(void);
int ItemRecord_FishKinds(void);
int ItemRecord_HasAllInsects(void);
int ItemRecord_HasAllFish(void);
int ItemRecord_CountHad(int first, int count);
int ItemRecord_Mark(ItemRecord *record, const ItemCode *item, int mode);
int ItemRecord_SetBit(ItemRecord *record, const ItemCode *item, int mode, int set);
int ItemRecord_Has(ItemRecord *record, const ItemCode *item);
u8 *ItemRecord_BitOf(ItemRecord *record, u8 *mask, const ItemCode *item);
void ItemRecord_Reset(ItemRecord *record);
void ItemRecord_Clear(ItemRecord *record);
void ItemRecord_Destruct(ItemRecord *record);
void ItemRecord_Construct(ItemRecord *record);

#endif
