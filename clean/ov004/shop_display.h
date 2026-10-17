/* A process of overlay 4 (vtable data_ov004_022568c4, 0x58 bytes, on the scene class of
 * autoload_2, data_020da13c; profile ShopDisplay_New) that puts a shop's stock on its room's
 * map (data_021c80bc, the acre (0, 0), layer 0) when the shop is entered, and the questions
 * about what is on sale there that main's shops.c asks.
 *
 * The shops: Nook's scenes 0x1a-0x1f (Nook's store, nook_store.h, 37 places; none in scene
 * 0x1f), scene 0xa (shop list A, shop_list_a.h, and eight fixed items 0x3e04-0x3e20) and
 * scene 0xf (the fox's shop, fox_shop.h).
 *
 * Each shop has a layout (ShopDisplay_Layout): a spot kind for each tile of the room, 16 rows of
 * 16. An item goes on the first empty tile, row by row, whose kind is the item's
 * (ShopDisplay_SpotKind): 0x19 for an item with variants, 0x42 for one held with a model (and
 * item 0x156c), 9 for 0x13a8-0x13c7, else the item's class. Two items of one kind take that
 * kind's tiles in their order. */
#ifndef CLEAN_OV004_SHOP_DISPLAY_H
#define CLEAN_OV004_SHOP_DISPLAY_H

#include "autoload_2/process.h"
#include "types.h"

/* ShopDisplay.kind: the shop the creation stocks. */
enum ShopDisplayKind {
    SHOP_DISPLAY_NOOK = 0,   /* one of Nook's scenes */
    SHOP_DISPLAY_LIST_A = 1, /* scene 0xa */
    SHOP_DISPLAY_FOX = 2,    /* scene 0xf */
    SHOP_DISPLAY_OTHER = 3,  /* nothing to stock */
    SHOP_DISPLAY_KINDS = 4,
};

#define SHOP_DISPLAY_ROWS 16
#define SHOP_DISPLAY_COLUMNS 16

typedef struct ShopDisplay {
    Process base;   /* vtable data_ov004_022568c4 */
    int nook_index; /* 0x50: the scene's index among Nook's (-1 outside them); not read here */
    int kind;       /* 0x54: ShopDisplayKind */
} ShopDisplay;

int ShopDisplay_StockOther(void);
u16 *ShopDisplay_FoxItemAt(int x, int z);
int ShopDisplay_StockFox(ShopDisplay *self);
void ShopDisplay_PlaceFox(ShopDisplay *self);
u16 *ShopDisplay_ListAItemAt(int x, int z);
int ShopDisplay_StockListA(ShopDisplay *self);
void ShopDisplay_PlaceListA(ShopDisplay *self);
int ShopDisplay_FindNookPlace(int *x, int *z, int place);
int ShopDisplay_PairedIndex(int x, int z);
u16 *ShopDisplay_ItemAt(int x, int z);
int ShopDisplay_IsOnSale(u16 *item);
int ShopDisplay_StockNook(ShopDisplay *self);
void ShopDisplay_PlaceNook(ShopDisplay *self);
int ShopDisplay_PlaceItem(ShopDisplay *self, u16 *item, int kind);
int ShopDisplay_Delete(void);
int ShopDisplay_Draw(void);
int ShopDisplay_Execute(void);
int ShopDisplay_Create(ShopDisplay *self);
ShopDisplay *ShopDisplay_DestructFree(ShopDisplay *self);
ShopDisplay *ShopDisplay_Destruct(ShopDisplay *self);
ShopDisplay *ShopDisplay_Construct(ShopDisplay *self);
int ShopDisplay_SpotKind(u16 *item);
const s32 *ShopDisplay_Layout(void);
void ShopDisplay_New(void);

#endif
