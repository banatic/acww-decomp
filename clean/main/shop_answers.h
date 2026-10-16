/* The answers a shop change waits for while linked (data_021f49ec, shops.h): a change taken
 * here is sent to the other systems (message 38) and each answers it (message 39). Before
 * sending, ShopAnswers_Expect sets how many answers to wait for (the session's players but
 * this one); ShopAnswers_Count counts each that comes, and the shops wait until
 * ShopAnswers_AllCame. */
#ifndef CLEAN_MAIN_SHOP_ANSWERS_H
#define CLEAN_MAIN_SHOP_ANSWERS_H

#include "types.h"

typedef struct ShopAnswers {
    u8 expected; /* the answers to wait for */
    u8 received; /* those that came */
} ShopAnswers;

int ShopAnswers_AllCameIfLinked(void);
int ShopAnswers_Count(ShopAnswers *answers);
int ShopAnswers_AllCame(ShopAnswers *answers);
void ShopAnswers_Expect(ShopAnswers *answers);
void ShopAnswers_Clear(ShopAnswers *answers);
int ShopAnswers_Destruct(ShopAnswers *answers);
ShopAnswers *ShopAnswers_Construct(ShopAnswers *answers);

#endif
