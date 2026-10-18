/* The players', the shop's, the sample's and the holder's designs (design_sets.h). */
#include "design_sets.h"

#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "autoload_2/heap.h"
#include "clean.h"
#include "design_info.h"
#include "player_id.h"
#include "town_name.h"

static_assert(offsetof(PlayerDesigns, order) == 0x11a0, "order");
static_assert(sizeof(ShopDesigns) == 0x11a0, "shop");

#define SAMPLE_IMAGE_SIZE 0x200
#define SHEET_SIZE 0x1000

/* The records of "/myOrg/myD.bin" each set's information comes from. */
#define PLAYER_ENTRY_FIRST 0
#define SHOP_ENTRY_FIRST 8
#define HOLDER_ENTRY 0x10
#define SAMPLE_ENTRY_FIRST 0x12

/* A town: its number and name, the first 0xe bytes of a creator. */
#define TOWN_NAME_SIZE 12

/* The manager's flags: bit n says the shop's design n changed. */
extern u8 data_021d0468;
extern u8 data_021d0478[4];  /* four bytes cleared with them, not read by name elsewhere */
extern Design data_021d0800; /* the sample */

/* The creators the defaults are given. */
extern const u16 data_020ccb64; /* no town: 0xffff */
extern const u16 data_020d1858; /* the shop's player number: 0x7ffd */
extern const u16 data_020d185c; /* a sample's: 0x7fff */
extern const u16 data_020d1860; /* the holder's: 0x7ffc */
extern u8 data_021dc7aa[];      /* this town (number and name) */

extern void __cxa_vec_ctor(void *array, int count, int size, void (*construct)(void *), void (*destruct)(void *));
extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));
/* Design_Construct and Design_Destruct at the game's addresses, declared as the vector helpers
 * take them (their results are not used). */
extern void func_02072dbc(void *design);
extern void func_02072da4(void *design);

static Design *design_at(unsigned int address)
{
    return (Design *) (uintptr_t) address;
}

static unsigned int address_of(const void *pointer)
{
    return (unsigned int) (uintptr_t) pointer;
}

static DesignInfo *info_of(unsigned int design)
{
    return (DesignInfo *) (uintptr_t) Design_Info(design);
}

static RecordFile *archive(void)
{
    return (RecordFile *) (uintptr_t) DesignArchive_Get();
}

/* The bit of a shop design's flag.
 * QUIRK: the index is used as the ARM shifts by a register do: its low byte only, and 32 or
 * more gives no bit. */
static unsigned int flag_bit(int index)
{
    unsigned int shift = (unsigned int) index & 0xff;
    return shift < 32 ? 1u << shift : 0;
}

/* func_0207277c: whether the shop's design `index` changed since the last call, forgetting
 * it. */
int DesignManager_TakeShopChanged(DesignManager *manager, int index)
{
    (void) manager;
    unsigned int bit = flag_bit(index);
    int changed = (data_021d0468 & bit) != 0;
    data_021d0468 = (u8) (data_021d0468 & ~bit);
    return changed;
}
CLEAN_AS(func_0207277c, DesignManager_TakeShopChanged)

/* func_020727a4: notes that the shop's design `index` changed (Design_Changed). */
void DesignManager_MarkShopChanged(DesignManager *manager, int index)
{
    (void) manager;
    data_021d0468 = (u8) (data_021d0468 | flag_bit(index));
}
CLEAN_AS(func_020727a4, DesignManager_MarkShopChanged)

/* func_020727b8 */
void DesignManager_ClearChanged(DesignManager *manager)
{
    (void) manager;
    for (int i = 0; i < 4; i++) {
        data_021d0478[i] = 0;
    }
    data_021d0468 = 0;
}
CLEAN_AS(func_020727b8, DesignManager_ClearChanged)

/* func_020727d4: the manager's destructor (registered by __sinit_020c5c94). */
char *DesignManager_Destruct(char *manager)
{
    DesignManager *self = (DesignManager *) manager;
    DesignPalettes_Destruct(&self->palettes);
    DesignTextures_Destruct(self);
    return manager;
}
CLEAN_AS(func_020727d4, DesignManager_Destruct)

/* func_020727ec: its constructor. */
char *DesignManager_Construct(char *manager)
{
    DesignManager *self = (DesignManager *) manager;
    DesignTextures_Construct(self);
    DesignPalettes_Construct(&self->palettes);
    DesignManager_Reset(self);
    return manager;
}
CLEAN_AS(func_020727ec, DesignManager_Construct)

/* func_02072808: forgets the palettes, the textures and the flags. */
void DesignManager_Reset(DesignManager *manager)
{
    DesignPalettes_Reset(&manager->palettes);
    DesignTextures_Clear(manager);
    DesignManager_ClearChanged(manager);
}
CLEAN_AS(func_02072808, DesignManager_Reset)

/* func_02072824: the one place a sample is read into. */
int DesignSample_Get(void)
{
    return (int) address_of(&data_021d0800);
}
CLEAN_AS(func_02072824, DesignSample_Get)

/* func_0207282c */
Design *DesignSample_Design(Design *sample)
{
    return sample;
}
CLEAN_AS(func_0207282c, DesignSample_Design)

/* func_02072830: reads sample `index` (0-31) into a design: its image, and its information
 * from record 18 + index, made by no town and the player number 0x7fff. 0 for other
 * indices.
 * QUIRK: without memory for the image (from the current heap) nothing is read, and the result
 * is 1 all the same. */
int DesignSample_Load(Design *sample, unsigned int index)
{
    if (index >= DESIGN_SAMPLES) {
        return 0;
    }
    void *image = Heap_AllocCurrent(SAMPLE_IMAGE_SIZE);
    if (image == NULL) {
        return 1;
    }
    DesignSampleImage_Construct();
    DesignSampleImage_Load(image, (int) index);
    DesignSampleImage_ToBitmap(image, Design_Pixels(DesignSample_Design(sample)));
    RecordFile *file = archive();
    DesignArchive_ReadInfo(file, info_of(address_of(DesignSample_Design(sample))), (int) (index + SAMPLE_ENTRY_FIRST));
    TownName_SetNumber((u16 *) (PlayerId_Town(DesignInfo_Creator(info_of(address_of(DesignSample_Design(sample)))))),
                       data_020ccb64);
    PlayerId_SetNumber((u16 *) (DesignInfo_Creator(info_of(address_of(DesignSample_Design(sample))))), data_020d185c);
    Heap_FreeCurrent(image);
    return 1;
}
CLEAN_AS(func_02072830, DesignSample_Load)

/* func_020728d8: the sample's destructor (registered by __sinit_020c5c94). */
int DesignSample_Destruct(Design *sample)
{
    Design_Destruct(sample);
    return (int) address_of(sample);
}
CLEAN_AS(func_020728d8, DesignSample_Destruct)

/* func_020728e8: its constructor. */
int DesignSample_Construct(Design *sample)
{
    Design_Construct((char *) sample);
    return (int) address_of(sample);
}
CLEAN_AS(func_020728e8, DesignSample_Construct)

/* func_02072994 */
Design *DesignHolder_Design(Design *holder)
{
    return holder;
}
CLEAN_AS(func_02072994, DesignHolder_Design)

/* func_02072998: resets the design to "obj0.bch" with record 16's information, made in this
 * town by the player number 0x7ffc. Nothing without memory for the image (from the current
 * heap). */
void DesignHolder_Reset(Design *holder)
{
    void *image = Heap_AllocCurrent(SAMPLE_IMAGE_SIZE);
    if (image == NULL) {
        return;
    }
    DesignBlankImage_Construct();
    DesignBlankImage_Load(image);
    DesignBlankImage_ToBitmap(image, Design_Pixels(DesignHolder_Design(holder)));
    RecordFile *file = archive();
    DesignArchive_ReadInfo(file, info_of(address_of(DesignHolder_Design(holder))), HOLDER_ENTRY);
    TownName_Copy(PlayerId_Town(DesignInfo_Creator(info_of(address_of(DesignHolder_Design(holder))))),
                  (const TownName *) (void *) data_021dc7aa);
    PlayerId_SetNumber((u16 *) (DesignInfo_Creator(info_of(address_of(DesignHolder_Design(holder))))), data_020d1860);
    Heap_FreeCurrent(image);
}
CLEAN_AS(func_02072998, DesignHolder_Reset)

/* func_02072a28: the holder's destructor. */
int DesignHolder_Destruct(Design *holder)
{
    Design_Destruct(holder);
    return (int) address_of(holder);
}
CLEAN_AS(func_02072a28, DesignHolder_Destruct)

/* func_02072a38: its constructor. */
Design *DesignHolder_Construct(Design *holder)
{
    Design_Construct((char *) holder);
    return holder;
}
CLEAN_AS(func_02072a38, DesignHolder_Construct)

/* func_02072a48: the shop's design `index`, cut to 0-7. */
unsigned int ShopDesigns_At(unsigned int designs, unsigned int index)
{
    return address_of(&((ShopDesigns *) (uintptr_t) designs)->designs[index & 7]);
}
CLEAN_AS(func_02072a48, ShopDesigns_At)

/* func_02072a58: resets the shop's designs to the eight of "b_myd_bu_obj.bch" with records
 * 8-15's information, made by no town and the player number 0x7ffd. Nothing without memory
 * for the sheet (from the current heap). */
void ShopDesigns_Reset(ShopDesigns *designs)
{
    void *sheet = Heap_AllocCurrent(SHEET_SIZE);
    if (sheet == NULL) {
        return;
    }
    DesignBuSheet_Construct();
    DesignBuSheet_Load(sheet);
    int town = data_020ccb64;
    int player = data_020d1858;
    unsigned int set = address_of(designs);
    for (int i = 0; i < DESIGNS_PER_SET; i++) {
        DesignBuSheet_ToBitmap(sheet, Design_Pixels(design_at(ShopDesigns_At(set, (u8) i))), i);
        RecordFile *file = archive();
        DesignArchive_ReadInfo(file, info_of(ShopDesigns_At(set, (u8) i)), i + SHOP_ENTRY_FIRST);
        TownName_SetNumber((u16 *) (PlayerId_Town(DesignInfo_Creator(info_of(ShopDesigns_At(set, (u8) i))))), town);
        PlayerId_SetNumber((u16 *) (DesignInfo_Creator(info_of(ShopDesigns_At(set, (u8) i)))), player);
    }
    Heap_FreeCurrent(sheet);
}
CLEAN_AS(func_02072a58, ShopDesigns_Reset)

/* func_02072b18: the shop's designs' destructor (func_0209f1a8). */
ShopDesigns *ShopDesigns_Destruct(ShopDesigns *designs)
{
    __cxa_vec_cleanup(designs, DESIGNS_PER_SET, DESIGN_SIZE, func_02072da4);
    return designs;
}
CLEAN_AS(func_02072b18, ShopDesigns_Destruct)

/* func_02072b38: their constructor (__sinit_020c64e8). */
ShopDesigns *ShopDesigns_Construct(ShopDesigns *designs)
{
    __cxa_vec_ctor(designs, DESIGNS_PER_SET, DESIGN_SIZE, func_02072dbc, func_02072da4);
    return designs;
}
CLEAN_AS(func_02072b38, ShopDesigns_Construct)

/* func_02072b64: the design (0-7) at a place, both cut to 0-7. */
unsigned char DesignOrder_Get(unsigned char *order, int place)
{
    return order[place & 7] & 7;
}
CLEAN_AS(func_02072b64, DesignOrder_Get)

/* func_02072b74: swaps the designs at two places (cut to 0-7). */
void DesignOrder_Swap(unsigned char *order, int place_a, int place_b)
{
    unsigned char design = order[place_a & 7];
    order[place_a & 7] = order[place_b & 7];
    order[place_b & 7] = design;
}
CLEAN_AS(func_02072b74, DesignOrder_Swap)

/* func_02072b8c: each design at its own place. */
void DesignOrder_Reset(unsigned char *order)
{
    for (unsigned char i = 0; i < DESIGNS_PER_SET; i++) {
        order[i] = i;
    }
}
CLEAN_AS(func_02072b8c, DesignOrder_Reset)

/* func_02072b9c */
void DesignOrder_Destruct(DesignOrder *order)
{
    (void) order;
}
CLEAN_AS(func_02072b9c, DesignOrder_Destruct)

/* func_02072ba0 */
void DesignOrder_Construct(DesignOrder *order)
{
    (void) order;
}
CLEAN_AS(func_02072ba0, DesignOrder_Construct)

/* func_02072ba4 */
int PlayerDesigns_Order(PlayerDesigns *designs)
{
    return (int) address_of(&designs->order);
}
CLEAN_AS(func_02072ba4, PlayerDesigns_Order)

/* func_02072bb0: the design shown at a place (0-7). */
int PlayerDesigns_InOrder(PlayerDesigns *designs, int place)
{
    unsigned char design = DesignOrder_Get(designs->order.design, place);
    return (int) address_of(&designs->designs[design]);
}
CLEAN_AS(func_02072bb0, PlayerDesigns_InOrder)

/* func_02072bd0: the design `index`, cut to 0-7. */
int PlayerDesigns_At(PlayerDesigns *designs, int index)
{
    return (int) address_of(&designs->designs[index & 7]);
}
CLEAN_AS(func_02072bd0, PlayerDesigns_At)

/* func_02072be0: the player's town changed (func_0209e974): each design the player made in the
 * old town (number and name) gets the player's new town. */
void PlayerDesigns_UpdateTown(PlayerDesigns *designs, DesignCreator *player, u8 *old_town)
{
    for (int i = 0; i < DESIGNS_PER_SET; i++) {
        unsigned int info = Design_Info((unsigned int) PlayerDesigns_At(designs, i));
        DesignCreator *creator = DesignInfo_Creator((DesignInfo *) (uintptr_t) info);
        u16 *town = (u16 *) PlayerId_Town(creator);
        u16 old_number;
        memcpy(&old_number, old_town, sizeof(old_number));
        if (town[0] != old_number || memcmp(town + 1, old_town + 2, TOWN_NAME_SIZE) != 0) {
            continue;
        }
        if (PlayerId_SamePlayer(creator, player) != 0) {
            DesignCreator *target = DesignInfo_Creator((DesignInfo *) (uintptr_t) info);
            PlayerId_SetTown(target, PlayerId_Town(player));
        }
    }
}
CLEAN_AS(func_02072be0, PlayerDesigns_UpdateTown)

/* func_02072c50: resets a player's designs to the eight of "b_myd_my_obj.bch" with records
 * 0-7's information, all made by the player, and shown in their own order. Without memory for
 * the sheet (from the current heap) only the order is reset. */
void PlayerDesigns_Reset(PlayerDesigns *designs, DesignCreator *player)
{
    void *sheet = Heap_AllocCurrent(SHEET_SIZE);
    if (sheet != NULL) {
        DesignMySheet_Construct();
        DesignMySheet_Load(sheet);
        for (int i = 0; i < DESIGNS_PER_SET; i++) {
            DesignMySheet_ToBitmap(sheet, Design_Pixels(design_at((unsigned int) PlayerDesigns_At(designs, (u8) i))), i);
            RecordFile *file = archive();
            DesignArchive_ReadInfo(file, info_of((unsigned int) PlayerDesigns_At(designs, (u8) i)), i + PLAYER_ENTRY_FIRST);
            DesignInfo_SetCreator(info_of((unsigned int) PlayerDesigns_At(designs, (u8) i)), player);
        }
        Heap_FreeCurrent(sheet);
    }
    DesignOrder_Reset(designs->order.design);
}
CLEAN_AS(func_02072c50, PlayerDesigns_Reset)

/* func_02072ce8: the destructor (of a player record, func_02099ad0). */
PlayerDesigns *PlayerDesigns_Destruct(PlayerDesigns *designs)
{
    DesignOrder_Destruct(&designs->order);
    __cxa_vec_cleanup(designs, DESIGNS_PER_SET, DESIGN_SIZE, func_02072da4);
    return designs;
}
CLEAN_AS(func_02072ce8, PlayerDesigns_Destruct)

/* func_02072d14: the constructor. */
PlayerDesigns *PlayerDesigns_Construct(PlayerDesigns *designs)
{
    __cxa_vec_ctor(designs, DESIGNS_PER_SET, DESIGN_SIZE, func_02072dbc, func_02072da4);
    DesignOrder_Construct(&designs->order);
    return designs;
}
CLEAN_AS(func_02072d14, PlayerDesigns_Construct)
