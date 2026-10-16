/* The last sale of overlay 52's seller (the state block's part at 0x17344, data_021f3aec):
 * the player who paid and the item handed over. Overlay 52 fills it after a sale and reads it
 * back to say who bought what; it is emptied when the town is set up and when the fox's shop
 * takes a new password (FoxPassword_Pick). */
#ifndef CLEAN_MAIN_LAST_SALE_H
#define CLEAN_MAIN_LAST_SALE_H

#include "design.h"
#include "types.h"

typedef struct LastSale {
    DesignCreator buyer; /* 0x00 */
    u16 item;            /* 0x1e: 0xfff1 when none */
} LastSale;

void LastSale_GetItem(u16 *item, const LastSale *sale);
void LastSale_SetItem(LastSale *sale, const u16 *item);
void LastSale_SetBuyer(LastSale *sale, const DesignCreator *buyer);
DesignCreator *LastSale_Buyer(LastSale *sale);
void LastSale_SetUp(LastSale *sale);
void LastSale_Clear(LastSale *sale);
LastSale *LastSale_Destruct(LastSale *sale);
LastSale *LastSale_Construct(LastSale *sale);

#endif
