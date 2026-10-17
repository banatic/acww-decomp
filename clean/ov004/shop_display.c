/* The process that puts a shop's stock in its room, and what is on sale there
 * (shop_display.h). */
#include "shop_display.h"

#include "autoload_2/heap.h" /* Heap_AllocAuxZeroed, Heap_FreeAux */
#include "clean.h"
#include "main/acre_map.h"
#include "main/acre_tile.h"
#include "main/fox_shop.h"
#include "main/item_code.h"
#include "main/item_form.h"
#include "main/item_traits.h"
#include "main/nook_store.h"
#include "main/scene_query.h"
#include "main/shop_list_a.h"
#include "member_pointer.h"
#include "room_object_body.h" /* RoomObject_Number */

static_assert(sizeof(ShopDisplay) == 0x58, "the process");

/* The scenes. */
#define SHOP_DISPLAY_SCENE_LIST_A 0xa
#define SHOP_DISPLAY_SCENE_FOX 0xf
#define SHOP_DISPLAY_SCENE_NOOK_UNSTOCKED 0x1f /* the last of Nook's: nothing put out */

/* The eight fixed items of scene 0xa, four codes apart, put on the tiles (6-9, 10-11); with
 * their variants they are 0x3e04-0x3e23. */
#define SHOP_DISPLAY_FIXED_FIRST 0x3e04
#define SHOP_DISPLAY_FIXED_LAST 0x3e23
#define SHOP_DISPLAY_FIXED_STEP 4
#define SHOP_DISPLAY_FIXED_X 6
#define SHOP_DISPLAY_FIXED_Z 10
#define SHOP_DISPLAY_FIXED_COLUMNS 4
#define SHOP_DISPLAY_FIXED_ROWS 2

/* Spot kinds that are not an item's class. */
#define SHOP_DISPLAY_SPOT_VARIANTS 0x19
#define SHOP_DISPLAY_SPOT_HELD 0x42
#define SHOP_DISPLAY_SPOT_13A8 9
#define SHOP_DISPLAY_SPOT_PAIRED 0x22 /* the pair of shops.c's scene 0x1d */
#define SHOP_DISPLAY_HELD_ITEM 0x156c
#define SHOP_DISPLAY_13A8_FIRST 0x13a8
#define SHOP_DISPLAY_13A8_LAST 0x13c7

/* An item of kind 1 that is never on sale in the room. */
#define SHOP_DISPLAY_NOT_SHOWN 0x1547

/* The layer the stock is put on. */
#define SHOP_DISPLAY_LAYER 0

/* The vtables: this class's and the scene class of autoload_2. */
extern const u32 data_ov004_022568c4[];
extern const u32 data_020da13c[];

/* The layouts: one per Nook's scene, scene 0xa's, and the other shops'. */
extern const s32 data_ov004_0224c664[][SHOP_DISPLAY_ROWS * SHOP_DISPLAY_COLUMNS];
extern const s32 data_ov004_0224be64[SHOP_DISPLAY_ROWS * SHOP_DISPLAY_COLUMNS];
extern const s32 data_ov004_0224c264[SHOP_DISPLAY_ROWS * SHOP_DISPLAY_COLUMNS];

/* The creation's stocking functions by kind, filled from four constants the first time
 * (Create's function-local static). */
extern u32 data_ov004_0225ff0c;
extern MemberPointer data_ov004_0225ff30[SHOP_DISPLAY_KINDS];
extern const MemberPointer data_ov004_02256894; /* ShopDisplay_StockNook */
extern const MemberPointer data_ov004_0225689c; /* ShopDisplay_StockListA */
extern const MemberPointer data_ov004_022568b4; /* ShopDisplay_StockFox */
extern const MemberPointer data_ov004_022568a4; /* ShopDisplay_StockOther */

/* ItemAt's two item codes: function-local statics of the game's, built and registered for
 * destruction (with func_020051b0) the first time, a guard bit each. */
extern u16 data_ov004_0225ff04; /* the empty code: "nothing on sale here" */
extern u16 data_ov004_0225ff08; /* the code of the room object on the tile */
extern u32 data_ov004_0225ff14;
extern u32 data_ov004_0225ff10;
extern u8 data_ov004_0225ff24[];
extern u8 data_ov004_0225ff18[];

extern AcreMap *data_021c80bc; /* the room's map */
extern NookStore data_021f395c;
extern ShopListA data_021f3b44;
extern FoxShop data_021f3b30;

extern void __register_global_object(void *object, void *destruct, void *record);
/* The destructor of an item code (TrivialObject_DestructItemCode), as the game registers it. */
extern void func_020051b0(void *item);

/* The room's objects on their cells (room_sync.h). */
extern void *func_ov004_0223cd50(void);
extern RoomObject *func_ov004_0223cc10(void *grid, int x, int y, int layer);

/* Whether `item` is the code `code`: for an item with variants, the same item (the item's
 * variant item read first). */
static int ShopDisplay_is_code(u16 *item, u16 code)
{
    if (ItemCode_HasVariant(item)) {
        u16 other = code;
        int mine = ItemCode_VariantItem(item);
        return mine == ItemCode_VariantItem(&other);
    }
    return *item == code;
}

/* A list's accessor: what its entry `index` shows (or a marker), the entry's item in `out`. */
typedef u16 *(*ShopDisplayItemOf)(u32 index, u16 *out);

/* Each of a list's `count` entries taken out (into an empty code), and put on a tile of the
 * item's kind when both what it shows and the item are not empty. */
static void ShopDisplay_place_all(ShopDisplay *self, u32 count, ShopDisplayItemOf item_of)
{
    for (u32 i = 0; i < count; ++i) {
        u16 item = ITEM_CODE_NONE;
        u16 *shown = item_of(i, &item);
        if (!ShopDisplay_is_code(shown, ITEM_CODE_NONE) && !ShopDisplay_is_code(&item, ITEM_CODE_NONE)) {
            ShopDisplay_PlaceItem(self, shown, ShopDisplay_SpotKind(&item));
        }
    }
}

static u16 *ShopDisplay_fox_item(u32 index, u16 *out)
{
    return FoxShop_Item(&data_021f3b30, (int) index, out);
}

static u16 *ShopDisplay_list_a_item(u32 index, u16 *out)
{
    return ShopListA_Item(&data_021f3b44, index, out);
}

static u16 *ShopDisplay_nook_item(u32 index, u16 *out)
{
    return NookStore_Item(&data_021f395c, index, out);
}

/* func_ov004_02245ff4 (stocking of SHOP_DISPLAY_OTHER): nothing. */
int ShopDisplay_StockOther(void)
{
    return 1;
}
CLEAN_AS(func_ov004_02245ff4, ShopDisplay_StockOther)

/* func_ov004_02245ff8: what is on sale at tile (x, z) of the fox's shop (main's shops.c asks). */
u16 *ShopDisplay_FoxItemAt(int x, int z)
{
    return ShopDisplay_ItemAt(x, z);
}
CLEAN_AS(func_ov004_02245ff8, ShopDisplay_FoxItemAt)

/* func_ov004_02246000 (stocking of SHOP_DISPLAY_FOX) */
int ShopDisplay_StockFox(ShopDisplay *self)
{
    ShopDisplay_PlaceFox(self);
    return 1;
}
CLEAN_AS(func_ov004_02246000, ShopDisplay_StockFox)

/* func_ov004_02246010: the fox's three items put out. */
void ShopDisplay_PlaceFox(ShopDisplay *self)
{
    ShopDisplay_place_all(self, FOX_SHOP_ITEMS, ShopDisplay_fox_item);
}
CLEAN_AS(func_ov004_02246010, ShopDisplay_PlaceFox)

/* func_ov004_022460c8: what is on sale at tile (x, z) of the shop of list A (main's shops.c
 * asks). */
u16 *ShopDisplay_ListAItemAt(int x, int z)
{
    return ShopDisplay_ItemAt(x, z);
}
CLEAN_AS(func_ov004_022460c8, ShopDisplay_ListAItemAt)

/* func_ov004_022460d0 (stocking of SHOP_DISPLAY_LIST_A): list A's six items put out, then the
 * eight fixed items on their tiles, row by row.
 * REQUIRES: the room has a map. */
int ShopDisplay_StockListA(ShopDisplay *self)
{
    ShopDisplay_PlaceListA(self);
    AcreMap *map = data_021c80bc;
    u16 item = SHOP_DISPLAY_FIXED_FIRST;
    for (int z = 0; z < SHOP_DISPLAY_FIXED_ROWS; z++) {
        for (int x = 0; x < SHOP_DISPLAY_FIXED_COLUMNS; x++) {
            u16 code = item;
            AcreTile_SetItem(map, &code, SHOP_DISPLAY_FIXED_X + x, SHOP_DISPLAY_FIXED_Z + z, SHOP_DISPLAY_LAYER);
            item = (u16) (item + SHOP_DISPLAY_FIXED_STEP);
        }
    }
    return 1;
}
CLEAN_AS(func_ov004_022460d0, ShopDisplay_StockListA)

/* func_ov004_022461c4: list A's six items put out. */
void ShopDisplay_PlaceListA(ShopDisplay *self)
{
    ShopDisplay_place_all(self, SHOP_LIST_A_ITEMS, ShopDisplay_list_a_item);
}
CLEAN_AS(func_ov004_022461c4, ShopDisplay_PlaceListA)

/* func_ov004_0224627c: the tile (*x, *z) of Nook's store's `place`: the item's spot kind, and
 * the tile of that kind as many places on as the places before it holding an item of that
 * kind; 1, or 0 with both -1 when there is none.
 * QUIRK: the places before it are read up to and including `place` itself. */
int ShopDisplay_FindNookPlace(int *x, int *z, int place)
{
    const s32 *layout = ShopDisplay_Layout();
    u16 item = ITEM_CODE_NONE;
    NookStore_Item(&data_021f395c, (u32) place, &item);
    int kind = ShopDisplay_SpotKind(&item);

    int before = 0;
    for (u32 k = 0; k < NOOK_STORE_PLACES; k++) {
        u16 other = ITEM_CODE_NONE;
        NookStore_Item(&data_021f395c, k, &other);
        if ((u32) place == k) {
            break;
        }
        if (kind == ShopDisplay_SpotKind(&other)) {
            before++;
        }
    }

    int seen = 0;
    for (int row = 0; row < SHOP_DISPLAY_ROWS; row++) {
        for (int column = 0; column < SHOP_DISPLAY_COLUMNS; column++) {
            if (kind != layout[row * SHOP_DISPLAY_COLUMNS + column]) {
                continue;
            }
            if (seen == before) {
                *x = column;
                *z = row;
                return 1;
            }
            seen++;
        }
    }
    *z = -1;
    *x = *z;
    return 0;
}
CLEAN_AS(func_ov004_0224627c, ShopDisplay_FindNookPlace)

/* func_ov004_0224632c: how many tiles of the paired spot kind come before (x, z), row by row,
 * when (x, z) is one; else -1. */
int ShopDisplay_PairedIndex(int x, int z)
{
    const s32 *layout = ShopDisplay_Layout();
    int n = 0;
    for (int row = 0; row < SHOP_DISPLAY_ROWS; row++) {
        for (int column = 0; column < SHOP_DISPLAY_COLUMNS; column++) {
            if (layout[row * SHOP_DISPLAY_COLUMNS + column] != SHOP_DISPLAY_SPOT_PAIRED) {
                continue;
            }
            if (column == x && row == z) {
                return n;
            }
            n++;
        }
    }
    return -1;
}
CLEAN_AS(func_ov004_0224632c, ShopDisplay_PairedIndex)

/* func_ov004_02246378: what is on sale at tile (x, z) of the room: for a room object standing
 * there (ItemCode_IsF031OrVariant) the code of its number (in a static), for another item of
 * kind 1 but 0x1547 the tile's item itself, when the shop sells it (ShopDisplay_IsOnSale); else
 * the static empty code (also when the room has no map, the tile none or empty, or the cell no
 * room object). */
u16 *ShopDisplay_ItemAt(int x, int z)
{
    if ((data_ov004_0225ff14 & 1) == 0) {
        data_ov004_0225ff04 = ITEM_CODE_NONE;
        __register_global_object(&data_ov004_0225ff04, (void *) (uintptr_t) func_020051b0, data_ov004_0225ff24);
        data_ov004_0225ff14 |= 1;
    }
    if (data_021c80bc == NULL) {
        return &data_ov004_0225ff04;
    }
    int acre_x = x >> 4;
    int acre_z = z >> 4;
    u16 *item = AcreTile_ItemInAcre(data_021c80bc, (u32) acre_x, (u32) acre_z, x - (acre_x << 4), z - (acre_z << 4),
                                    SHOP_DISPLAY_LAYER);
    if (item == NULL || ShopDisplay_is_code(item, ITEM_CODE_NONE)) {
        return &data_ov004_0225ff04;
    }
    if (ItemCode_IsF031OrVariant(item)) {
        RoomObject *object = func_ov004_0223cc10(func_ov004_0223cd50(), x, z, 0);
        if (object == NULL) {
            return &data_ov004_0225ff04;
        }
        if ((data_ov004_0225ff10 & 1) == 0) {
            data_ov004_0225ff08 = ITEM_CODE_NONE;
            __register_global_object(&data_ov004_0225ff08, (void *) (uintptr_t) func_020051b0, data_ov004_0225ff18);
            data_ov004_0225ff10 |= 1;
        }
        data_ov004_0225ff08 = ItemCode_MakeVariant(RoomObject_Number(object), 0);
        if (ShopDisplay_IsOnSale(&data_ov004_0225ff08)) {
            return &data_ov004_0225ff08;
        }
    } else if (ItemCode_IsKind1(item)) {
        if (!ShopDisplay_is_code(item, SHOP_DISPLAY_NOT_SHOWN) && ShopDisplay_IsOnSale(item)) {
            return item;
        }
    }
    return &data_ov004_0225ff04;
}
CLEAN_AS(func_ov004_02246378, ShopDisplay_ItemAt)

/* func_ov004_022464f0: whether the shop of the current scene sells `item`: Nook's store in
 * Nook's scenes, list A or the fixed items in scene 0xa, the fox's shop elsewhere. */
int ShopDisplay_IsOnSale(u16 *item)
{
    int scene = SceneQuery_Current();
    if (SceneQuery_InNook((unsigned int) scene)) {
        return NookStore_FindItem(&data_021f395c, item) != -1;
    }
    if (scene == SHOP_DISPLAY_SCENE_LIST_A) {
        if (*item >= SHOP_DISPLAY_FIXED_FIRST && *item <= SHOP_DISPLAY_FIXED_LAST) {
            return 1;
        }
        return ShopListA_FindItem(&data_021f3b44, item) != -1;
    }
    return FoxShop_FindItem(&data_021f3b30, item) != -1;
}
CLEAN_AS(func_ov004_022464f0, ShopDisplay_IsOnSale)

/* func_ov004_0224657c (stocking of SHOP_DISPLAY_NOOK): Nook's store put out, but in scene
 * 0x1f. */
int ShopDisplay_StockNook(ShopDisplay *self)
{
    if (SceneQuery_Current() != SHOP_DISPLAY_SCENE_NOOK_UNSTOCKED) {
        ShopDisplay_PlaceNook(self);
    }
    return 1;
}
CLEAN_AS(func_ov004_0224657c, ShopDisplay_StockNook)

/* func_ov004_02246598: Nook's store's 37 places put out. */
void ShopDisplay_PlaceNook(ShopDisplay *self)
{
    ShopDisplay_place_all(self, NOOK_STORE_PLACES, ShopDisplay_nook_item);
}
CLEAN_AS(func_ov004_02246598, ShopDisplay_PlaceNook)

/* func_ov004_02246650: `item` put on the first empty tile of the room, row by row, whose spot
 * kind is `kind` and that takes it; whether one did (0 also when the room has no map). */
int ShopDisplay_PlaceItem(ShopDisplay *self, u16 *item, int kind)
{
    (void) self;
    const s32 *layout = ShopDisplay_Layout();
    AcreMap *map = data_021c80bc;
    if (map == NULL) {
        return 0;
    }
    for (int z = 0; z < SHOP_DISPLAY_ROWS; ++z) {
        for (int x = 0; x < SHOP_DISPLAY_COLUMNS; ++x) {
            int acre_x = x >> 4;
            int acre_z = z >> 4;
            u16 *tile =
                AcreTile_ItemInAcre(map, (u32) acre_x, (u32) acre_z, x - (acre_x << 4), z - (acre_z << 4), SHOP_DISPLAY_LAYER);
            if (tile == NULL || !ShopDisplay_is_code(tile, ITEM_CODE_NONE) || kind != layout[z * SHOP_DISPLAY_COLUMNS + x]) {
                continue;
            }
            if (AcreTile_SetItem(map, item, x, z, SHOP_DISPLAY_LAYER)) {
                return 1;
            }
        }
    }
    return 0;
}
CLEAN_AS(func_ov004_02246650, ShopDisplay_PlaceItem)

/* func_ov004_0224671c (vtable slot 3, the deletion): done at once. */
int ShopDisplay_Delete(void)
{
    return 1;
}
CLEAN_AS(func_ov004_0224671c, ShopDisplay_Delete)

/* func_ov004_02246720 (vtable slot 9, the drawing): nothing. */
int ShopDisplay_Draw(void)
{
    return 1;
}
CLEAN_AS(func_ov004_02246720, ShopDisplay_Draw)

/* func_ov004_02246724 (vtable slot 6, the execution): nothing. */
int ShopDisplay_Execute(void)
{
    return 1;
}
CLEAN_AS(func_ov004_02246724, ShopDisplay_Execute)

/* func_ov004_02246728 (vtable slot 0, the creation): the scene's index among Nook's kept, the
 * shop's kind found (Nook's, scene 0xa, scene 0xf or other) and its stocking run, through the
 * table. */
int ShopDisplay_Create(ShopDisplay *self)
{
    static const MemberPointer *const stockings[SHOP_DISPLAY_KINDS] = {&data_ov004_02256894, &data_ov004_0225689c,
                                                                       &data_ov004_022568b4, &data_ov004_022568a4};
    self->nook_index = SceneQuery_CurrentIndexInNook();
    if (SceneQuery_CurrentInNook() != 0) {
        self->kind = SHOP_DISPLAY_NOOK;
    } else if (SceneQuery_Current() == SHOP_DISPLAY_SCENE_LIST_A) {
        self->kind = SHOP_DISPLAY_LIST_A;
    } else if (SceneQuery_Current() == SHOP_DISPLAY_SCENE_FOX) {
        self->kind = SHOP_DISPLAY_FOX;
    } else {
        self->kind = SHOP_DISPLAY_OTHER;
    }
    MemberTable_InitOnce(&data_ov004_0225ff0c, data_ov004_0225ff30, stockings, SHOP_DISPLAY_KINDS);
    MemberPointer_CallVoid(&data_ov004_0225ff30[self->kind], self);
    return 1;
}
CLEAN_AS(func_ov004_02246728, ShopDisplay_Create)

/* func_ov004_022467e0 (vtable slot 17): the destructor, and the process freed. */
ShopDisplay *ShopDisplay_DestructFree(ShopDisplay *self)
{
    self->base.vtable = data_ov004_022568c4;
    self->base.vtable = data_020da13c;
    Process_Destruct(&self->base);
    Heap_FreeAux(self);
    return self;
}
CLEAN_AS(func_ov004_022467e0, ShopDisplay_DestructFree)

/* func_ov004_02246808 (vtable slot 16): the destructor. */
ShopDisplay *ShopDisplay_Destruct(ShopDisplay *self)
{
    self->base.vtable = data_ov004_022568c4;
    self->base.vtable = data_020da13c;
    Process_Destruct(&self->base);
    return self;
}
CLEAN_AS(func_ov004_02246808, ShopDisplay_Destruct)

/* func_ov004_02246828: the constructor. */
ShopDisplay *ShopDisplay_Construct(ShopDisplay *self)
{
    Process_Construct(&self->base);
    self->base.vtable = data_020da13c;
    self->base.vtable = data_ov004_022568c4;
    return self;
}
CLEAN_AS(func_ov004_02246828, ShopDisplay_Construct)

/* func_ov004_02246848: the spot kind of `item` (in its carried form): 0x19 for an item with
 * variants, 0x42 for one held with a model and for 0x156c, 9 for 0x13a8-0x13c7, else the
 * item's class. */
int ShopDisplay_SpotKind(u16 *item)
{
    u16 carried[2];
    ItemForm_ToCarried(carried, item);
    if (ItemCode_HasVariant(carried)) {
        return SHOP_DISPLAY_SPOT_VARIANTS;
    }
    if (ItemTraits_HasHeldModel(carried) || carried[0] == SHOP_DISPLAY_HELD_ITEM) {
        return SHOP_DISPLAY_SPOT_HELD;
    }
    if (carried[0] >= SHOP_DISPLAY_13A8_FIRST && carried[0] <= SHOP_DISPLAY_13A8_LAST) {
        return SHOP_DISPLAY_SPOT_13A8;
    }
    return ItemTraits_Class(carried);
}
CLEAN_AS(func_ov004_02246848, ShopDisplay_SpotKind)

/* func_ov004_022468b0: the layout of the current scene: its own in Nook's scenes, scene 0xa's,
 * else the other shops'. */
const s32 *ShopDisplay_Layout(void)
{
    if (SceneQuery_CurrentInNook() != 0) {
        return data_ov004_0224c664[SceneQuery_CurrentIndexInNook()];
    }
    if (SceneQuery_Current() == SHOP_DISPLAY_SCENE_LIST_A) {
        return data_ov004_0224be64;
    }
    return data_ov004_0224c264;
}
CLEAN_AS(func_ov004_022468b0, ShopDisplay_Layout)

/* func_ov004_022468e8 (the profile): a process from the auxiliary heap. */
void ShopDisplay_New(void)
{
    ShopDisplay *self = Heap_AllocAuxZeroed(sizeof(ShopDisplay));
    if (self == NULL) {
        return;
    }
    ShopDisplay_Construct(self);
}
CLEAN_AS(func_ov004_022468e8, ShopDisplay_New)
