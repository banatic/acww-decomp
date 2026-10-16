/* The forms an item takes. An item carried (in pockets, kind 1 codes 0x11a8-0x155c) is put in
 * a room as a code of kind 3 or 4 (four codes per item, the low two bits a variant), and a few
 * of them outdoors as a code of kind 0; ItemForm_ToPlaced and ItemForm_ToCarried convert
 * between them by these ranges:
 *
 *   carried           in a room             outdoors
 *   0x11a8-0x12a7     0x3984-0x3d83         -
 *   0x12b0-0x12e7     0x42a4-0x4383         -       (the insects)
 *   0x12e8-0x131f     0x4384-0x4463         -       (the fish)
 *   0x1380-0x139f     0x3e24-0x3ea3         -
 *   0x13c8-0x1407     0x3fa4-0x40a3         -
 *   0x13a8-0x13c7     0x40a4-0x4123         -
 *   0x1431-0x1470     0x4124-0x4223         -
 *   0x1408-0x1428     0x4464-0x44e7         0x00-0x20
 *   0x1471-0x1491     0x4464-0x44e7         0x00-0x20
 *   0x137c            0x44dc                0x1e
 *   0x1554-0x155c     0x44e8-0x450b         -
 *   0x153b-0x1541     -                     0xd4-0xda (and 0xdb-0xe1 back)
 *
 * The items 0x1408-0x1428 and 0x1471-0x1491 share their placed codes; converted back, a code
 * is the first of the two the item tests accept (func_0204be38, func_0204bd84), else 0x137c.
 *
 * Also here: the 20 room items 0x38e4-0x3933 are replaced by the 20 after them (0x3934-0x3983,
 * variant 0), everywhere items are kept (ItemForm_ReplaceEverywhere, which func_0204714c
 * calls right after the house's extension is built). */
#ifndef CLEAN_MAIN_ITEM_FORM_H
#define CLEAN_MAIN_ITEM_FORM_H

#include "acre_map.h" /* AcreMap */
#include "types.h"

void ItemForm_ReplaceEverywhere(void);
void ItemForm_ReplaceOnMap(AcreMap *map);
void ItemForm_Replacement(u16 *out, const u16 *item);
void ItemForm_ToPlaced(u16 *out, u16 *item, int in_room);
void ItemForm_ToCarried(u16 *out, u16 *item);

#endif
