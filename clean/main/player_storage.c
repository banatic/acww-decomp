/* A player's storage of 90 items (player_storage.h). */
#include "player_storage.h"

#include "clean.h"

static_assert(sizeof(PlayerStorage) == 0xb4, "a storage");

/* func_0203a674: the storage's first item. */
u16 *PlayerStorage_Items(PlayerStorage *storage)
{
    return storage->items;
}
CLEAN_AS(func_0203a674, PlayerStorage_Items)

/* func_0203a678: every place emptied. */
void PlayerStorage_Clear(u16 *items)
{
    for (int i = 0; i < PLAYER_STORAGE_ITEMS; i++) {
        items[i] = PLAYER_STORAGE_NONE;
    }
}
CLEAN_AS(func_0203a678, PlayerStorage_Clear)

/* func_0203a68c: the destructor (of each of the four, __cxa_vec_cleanup), which does nothing. */
void PlayerStorage_Destruct(PlayerStorage *storage)
{
    (void) storage;
}
CLEAN_AS(func_0203a68c, PlayerStorage_Destruct)

/* func_0203a690: the constructor (of each of the four, __cxa_vec_ctor), which does nothing. */
void PlayerStorage_Construct(PlayerStorage *storage)
{
    (void) storage;
}
CLEAN_AS(func_0203a690, PlayerStorage_Construct)
