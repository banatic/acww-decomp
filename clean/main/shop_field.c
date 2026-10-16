/* What a shop's room shows of a change of its stock (shop_field.h). */
#include "shop_field.h"

#include "clean.h"
#include "main/acre_map.h"
#include "main/acre_tile.h"
#include "main/sound.h"

/* A shop's room is one acre of 16 x 16 tiles. */
#define SHOP_FIELD_TILES 16
#define SHOP_FIELD_LAYER 0
/* The sound of an item leaving the shelf. */
#define SHOP_FIELD_SE_TAKEN 0x2e
/* Items that stay on sale (see NookStore_Sell). */
#define SHOP_FIELD_KEEP_FIRST 0x1000
#define SHOP_FIELD_KEEP_LAST 0x10ff
#define SHOP_FIELD_KEEP_ITEM 0x151f

/* 1 while the field is a room. */
extern u8 data_020e54a8;
/* The field's map. */
extern AcreMap *data_021c80bc;
/* What a sold place reads as (shop_stock.h). */
extern u16 data_021f49f4;

extern int func_020b65c4(void);                              /* the kind of the shop the player is in */
extern u16 *func_02037e0c(u8 *acre, int x, int z, u8 layer); /* the code of tile (x, z), or 0 */
extern int func_0204bcdc(u16 *item);                         /* whether the item is of the kinds compared by number */
extern int func_0204bc64(u16 *item);                         /* that number */
extern int func_0204bc90(u16 *item);                         /* whether the item stands as a room object */
extern int func_0204bd08(u16 *item);                         /* whether it is a code of kind 1 */
/* Overlay 4's room: its grid of objects, the object on a tile, the table of objects, an
 * object's index in it, and taking the object of an index off. */
extern void *func_ov004_0223cd50(void);
extern void *func_ov004_0223cc10(void *grid, int x, int z, int layer);
extern void *func_ov004_0223ce84(void);
extern int func_ov004_0223cd78(void *objects, void *object);
extern int func_ov004_0223bb14(int index);

/* func_020afdc8: shows `item` taken: the first tile of the room's acre, row by row, that holds
 * it (compared by number for the kinds func_0204bcdc accepts on the tile) goes through
 * ShopField_ShowTakenAt. Only while the field is a room, the player is in the shop of `kind`
 * and the map has an acre. */
void ShopField_ShowItemTaken(u16 *item, int kind, int sound)
{
    if (data_020e54a8 == 0) {
        return;
    }
    if (func_020b65c4() != kind) {
        return;
    }
    AcreMap *map = data_021c80bc;
    if (map == NULL) {
        return;
    }
    if ((u32) map->acres_wide == 0 || (u32) map->acres_high == 0 || map->acres == NULL) {
        return;
    }
    u8 *acre = map->acres;
    for (int z = 0; z < SHOP_FIELD_TILES; z++) {
        for (int x = 0; x < SHOP_FIELD_TILES; x++) {
            u16 *here = func_02037e0c(acre, x, z, SHOP_FIELD_LAYER);
            if (here == NULL) {
                continue;
            }
            int same;
            if (func_0204bcdc(here) != 0) {
                int a = func_0204bc64(here);
                same = a == func_0204bc64(item);
            } else {
                same = *here == *item;
            }
            if (same) {
                ShopField_ShowTakenAt(x, z, kind, sound);
                return;
            }
        }
    }
}
CLEAN_AS(func_020afdc8, ShopField_ShowItemTaken)

/* func_020afe94: shows the item on tile (x, z) of the field's map taken, with sound effect
 * 0x2e when `sound` is set. Only while the field is a room and the player is in the shop of
 * `kind`; nothing happens for an empty tile. */
void ShopField_ShowTakenAt(int x, int z, int kind, int sound)
{
    if (data_020e54a8 == 0) {
        return;
    }
    if (kind != func_020b65c4()) {
        return;
    }
    AcreMap *map = data_021c80bc;
    int acre_x = x >> 4;
    int acre_z = z >> 4;
    u16 *item = AcreTile_ItemInAcre(map, (u32) acre_x, (u32) acre_z, x - (acre_x << 4), z - (acre_z << 4), SHOP_FIELD_LAYER);
    if (item == NULL) {
        return;
    }

    if (func_0204bc90(item) != 0) {
        void *object = func_ov004_0223cc10(func_ov004_0223cd50(), x, z, 0);
        if (object != NULL) {
            func_ov004_0223bb14(func_ov004_0223cd78(func_ov004_0223ce84(), object));
        }
        if (sound != 0) {
            SoundSys_PlaySe(SHOP_FIELD_SE_TAKEN);
        }
        return;
    }

    if (func_0204bd08(item) == 0) {
        return;
    }
    u16 code = *item;
    int stays = (code >= SHOP_FIELD_KEEP_FIRST && code <= SHOP_FIELD_KEEP_LAST) || code == SHOP_FIELD_KEEP_ITEM;
    if (!stays) {
        AcreTile_SetItem(map, &data_021f49f4, x, z, SHOP_FIELD_LAYER);
    }
    if (sound != 0) {
        SoundSys_PlaySe(SHOP_FIELD_SE_TAKEN);
    }
}
CLEAN_AS(func_020afe94, ShopField_ShowTakenAt)
