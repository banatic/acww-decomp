/* What a shop's room shows of a change of its stock (Shops_ChangePlace, shops.h): while the
 * field is a room (data_020e54a8 1) and the player is in the shop of that kind, the item taken
 * from the stock goes from its tile of the room's map (data_021c80bc): an item standing as a
 * room object is taken off through overlay 4, any other item of kind 1 (func_0204bd08) becomes
 * the sold marker, except the items that stay on sale (0x1000-0x10ff and 0x151f). */
#ifndef CLEAN_MAIN_SHOP_FIELD_H
#define CLEAN_MAIN_SHOP_FIELD_H

#include "types.h"

void ShopField_ShowItemTaken(u16 *item, int kind, int sound);
void ShopField_ShowTakenAt(int x, int z, int kind, int sound);

#endif
