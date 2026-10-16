/* The town's layout (town_layout.h). */
#include "town_layout.h"

#include "clean.h"

extern u8 data_021f3b56[]; /* handed to func_020b0698 */

/* The game's constructors and destructors of the layout's members, handed to the C++ runtime. */
extern void func_020051b0(void *item);   /* an item code's destructor: nothing */
extern void func_02034ce0(void *item);   /* an item code's constructor: empty */
extern void func_02037d0c(void *record); /* an acre record's destructor: nothing */
extern void *func_0204e6d8(void *items); /* an acre's items' destructor (TownLayout_DestructBlock) */
extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));
extern void __cxa_vec_ctor(void *array, int count, int size, void (*construct)(void *), void (*destruct)(void *));

extern int func_020644cc(int range);     /* a random number below `range` */
extern void func_0209c574(void *layout); /* lays the acres' models out */
extern void func_02037d00(void *record); /* zeroes an acre record */
/* Fills `items` from item template `template_set` / `variant` (acre_map.h); 0 without templates. */
extern int func_0204d7f8(void *items, int template_set, int variant, int heap);
/* `count` AcreMapSource records from the back of `heap`, or 0. */
extern AcreMapSource *func_0204f86c(int count, int heap);
extern u32 func_020b7098(void);
extern void func_020b0698(u8 *data);

/* func_0204e6b8: an acre's items are the block itself; returns its argument. */
void *TownLayout_BlockItems(void *block)
{
    return block;
}
CLEAN_AS(func_0204e6b8, TownLayout_BlockItems)

/* func_0204e6bc: empties an acre's 256 item codes. */
void TownLayout_ClearBlock(unsigned short *items)
{
    for (int i = 0; i < TOWN_LAYOUT_ACRE_ITEMS; i++) {
        items[i] = ACRE_MAP_ITEM_NONE;
    }
}
CLEAN_AS(func_0204e6bc, TownLayout_ClearBlock)

/* func_0204e6d8: destroys an acre's 256 item codes (func_020051b0 on each, last first). */
void *TownLayout_DestructBlock(void *items)
{
    __cxa_vec_cleanup(items, TOWN_LAYOUT_ACRE_ITEMS, sizeof(u16), func_020051b0);
    return items;
}
CLEAN_AS(func_0204e6d8, TownLayout_DestructBlock)

/* func_0204e6f8: constructs an acre's 256 item codes (func_02034ce0 on each). */
int TownLayout_ConstructBlock(int items)
{
    __cxa_vec_ctor((void *) (uintptr_t) items, TOWN_LAYOUT_ACRE_ITEMS, sizeof(u16), func_02034ce0, func_020051b0);
    return items;
}
CLEAN_AS(func_0204e6f8, TownLayout_ConstructBlock)

/* func_0204e724: the layout (its acres' model numbers come first); returns its argument. */
void *TownLayout_Get(void *layout)
{
    return layout;
}
CLEAN_AS(func_0204e724, TownLayout_Get)

/* func_0204e728: lays a new town out: clears the layout and chooses its setting 0-2, then lays
 * the acres out (func_0209c574) and fills their items from the templates until the town has
 * at least nine tiles of 0x500a and five of 0xe3-0xe7. */
void TownLayout_Generate(void *layout, void *heap)
{
    TownLayout *self = layout;

    TownLayout_Clear(layout);
    int setting = func_020644cc(3);
    self->settings = (u8) ((self->settings & ~3) | (setting & 3));
    for (;;) {
        func_0209c574(layout);
        TownLayout_FillFromTemplates(layout, (int) (uintptr_t) heap);
        if (TownLayout_HasNine500a(layout) && TownLayout_HasFiveE3ToE7(layout)) {
            break;
        }
    }
}
CLEAN_AS(func_0204e728, TownLayout_Generate)

/* func_0204e77c: fills each inner acre's items from template set 0, variant the acre's model
 * number. */
void TownLayout_FillFromTemplates(u8 *layout, int heap)
{
    TownLayout *self = (TownLayout *) layout;
    TownLayoutAcre acre;

    for (acre.z = 0; acre.z < TOWN_LAYOUT_SIDE; acre.z++) {
        for (acre.x = 0; acre.x < TOWN_LAYOUT_SIDE; acre.x++) {
            int items = TownLayout_AcreItems(layout, &acre.x);
            if (items != 0) {
                func_0204d7f8((void *) (uintptr_t) items, 0, self->models[acre.z * TOWN_LAYOUT_SIDE + acre.x], heap);
            }
        }
    }
}
CLEAN_AS(func_0204e77c, TownLayout_FillFromTemplates)

/* The number of tiles of the inner acres whose item is in [first, last]. */
static int town_layout_count_items(void *layout, u16 first, u16 last)
{
    TownLayoutAcre acre;
    int count = 0;

    for (acre.z = 0; acre.z < TOWN_LAYOUT_SIDE; acre.z++) {
        for (acre.x = 0; acre.x < TOWN_LAYOUT_SIDE; acre.x++) {
            const u16 *items = (const u16 *) (uintptr_t) TownLayout_AcreItems(layout, &acre.x);
            if (items == NULL) {
                continue;
            }
            for (int i = 0; i < TOWN_LAYOUT_ACRE_ITEMS; i++) {
                if (items[i] >= first && items[i] <= last) {
                    count++;
                }
            }
        }
    }
    return count;
}

/* func_0204e7dc: whether at least five tiles hold an item 0xe3-0xe7. */
int TownLayout_HasFiveE3ToE7(void *layout)
{
    return town_layout_count_items(layout, 0xe3, 0xe7) >= 5;
}
CLEAN_AS(func_0204e7dc, TownLayout_HasFiveE3ToE7)

/* func_0204e854: whether at least nine tiles hold item 0x500a. */
int TownLayout_HasNine500a(void *layout)
{
    return town_layout_count_items(layout, 0x500a, 0x500a) >= 9;
}
CLEAN_AS(func_0204e854, TownLayout_HasNine500a)

/* func_0204e8c4: what AcreMap_BuildTown builds each of the 36 acres from, row by row: its model
 * number, and for an inner acre its items and record (0 for a border acre). 0 when the array
 * cannot be allocated from the back of `heap`. */
AcreMapSource *TownLayout_MakeSources(unsigned char *layout, int heap)
{
    AcreMapSource *sources = func_0204f86c(TOWN_LAYOUT_ACRES, heap);

    if (sources == NULL) {
        return NULL;
    }
    AcreMapSource *source = sources;
    TownLayoutAcre acre;
    for (acre.z = 0; acre.z < TOWN_LAYOUT_SIDE; acre.z++) {
        for (acre.x = 0; acre.x < TOWN_LAYOUT_SIDE; acre.x++) {
            source->model = layout[acre.z * TOWN_LAYOUT_SIDE + acre.x];
            source->items = (u16 *) (uintptr_t) TownLayout_AcreItems(layout, &acre.x);
            source->unk_08 = 0;
            source->extra = TownLayout_AcreRecord(layout, &acre.x);
            source++;
        }
    }
    return sources;
}
CLEAN_AS(func_0204e8c4, TownLayout_MakeSources)

/* func_0204e938: sets the settings' bits 2-7 from func_020b7098 (its low six bits), then calls
 * func_020b0698. */
void TownLayout_SetUpperSettings(unsigned int layout)
{
    TownLayout *self = (TownLayout *) (uintptr_t) layout;
    u32 value = func_020b7098();

    self->settings = (u8) ((self->settings & 3) | ((value & 0x3f) << 2));
    func_020b0698(data_021f3b56);
}
CLEAN_AS(func_0204e938, TownLayout_SetUpperSettings)

/* func_0204e96c: the setting chosen at random (bits 0-1). */
unsigned int TownLayout_RandomSetting(TownLayout *layout)
{
    return layout->settings & 3;
}
CLEAN_AS(func_0204e96c, TownLayout_RandomSetting)

/* func_0204e97c: the inner acre number (0-3 on each axis) of acre `acre`, when it is inner. */
int TownLayout_InnerAcre(int unused, TownLayoutAcre *inner, TownLayoutAcre *acre)
{
    if (!TownLayout_IsInnerAcre(unused, acre->x, acre->z)) {
        return 0;
    }
    inner->x = acre->x - 1;
    inner->z = acre->z - 1;
    return 1;
}
CLEAN_AS(func_0204e97c, TownLayout_InnerAcre)

/* func_0204e9a8: whether acre (x, z) is an inner one (1-4 on both axes). */
int TownLayout_IsInnerAcre(int unused, int x, int z)
{
    (void) unused;
    return x > 0 && x < 1 + TOWN_LAYOUT_INNER_SIDE && z > 0 && z < 1 + TOWN_LAYOUT_INNER_SIDE;
}
CLEAN_AS(func_0204e9a8, TownLayout_IsInnerAcre)

/* func_0204e9c0: the record of acre (acre[0], acre[1]), or 0 for a border acre. */
void *TownLayout_AcreRecord(void *layout, int *acre)
{
    TownLayoutAcre inner = {0, 0};
    TownLayoutAcre outer = {acre[0], acre[1]};

    if (!TownLayout_InnerAcre((int) (uintptr_t) layout, &inner, &outer)) {
        return NULL;
    }
    return &((TownLayout *) layout)->records[inner.z * TOWN_LAYOUT_INNER_SIDE + inner.x];
}
CLEAN_AS(func_0204e9c0, TownLayout_AcreRecord)

/* func_0204ea00: the items of acre (acre[0], acre[1]), or 0 for a border acre. */
int TownLayout_AcreItems(void *layout, int *acre)
{
    TownLayoutAcre inner = {0, 0};
    TownLayoutAcre outer = {acre[0], acre[1]};

    if (!TownLayout_InnerAcre((int) (uintptr_t) layout, &inner, &outer)) {
        return 0;
    }
    TownLayout *self = layout;
    return (int) (uintptr_t) TownLayout_BlockItems(self->items[inner.z * TOWN_LAYOUT_INNER_SIDE + inner.x]);
}
CLEAN_AS(func_0204ea00, TownLayout_AcreItems)

/* func_0204ea40: every acre's model 0x86, every item empty, every record zero, setting 0. */
void TownLayout_Clear(unsigned char *layout)
{
    TownLayout *self = (TownLayout *) layout;

    for (int i = 0; i < TOWN_LAYOUT_ACRES; i++) {
        self->models[i] = TOWN_LAYOUT_MODEL_DEFAULT;
    }
    for (int i = 0; i < TOWN_LAYOUT_INNER_ACRES; i++) {
        TownLayout_ClearBlock(self->items[i]);
        func_02037d00(&self->records[i]);
    }
    self->settings &= ~3;
}
CLEAN_AS(func_0204ea40, TownLayout_Clear)

/* func_0204ea98: the layout's destructor: its records (func_02037d0c), then its acres' items
 * (func_0204e6d8), each array last first. */
void *TownLayout_Destruct(void *layout)
{
    TownLayout *self = layout;

    __cxa_vec_cleanup(self->records, TOWN_LAYOUT_INNER_ACRES, sizeof(TownLayoutAcreRecord), func_02037d0c);
    __cxa_vec_cleanup(self->items, TOWN_LAYOUT_INNER_ACRES, sizeof(self->items[0]),
                      (void (*)(void *))(uintptr_t) func_0204e6d8);
    return layout;
}
CLEAN_AS(func_0204ea98, TownLayout_Destruct)

static_assert(offsetof(TownLayout, items) == 0x24, "TownLayout items");
static_assert(offsetof(TownLayout, records) == 0x2024, "TownLayout records");
static_assert(offsetof(TownLayout, settings) == 0x2224, "TownLayout settings");

/* The constructors handed to the C++ runtime by TownLayout_Construct. */
extern int func_0204e6f8(void *items);   /* an acre's items' constructor (TownLayout_ConstructBlock) */
extern void func_02037d10(void *record); /* an acre record's constructor: nothing */

/* func_0204ead0: the layout's constructor: its acres' items (func_0204e6f8), then its records
 * (func_02037d10). The models and the settings are left alone. */
void *TownLayout_Construct(void *layout)
{
    TownLayout *self = layout;

    __cxa_vec_ctor(self->items, TOWN_LAYOUT_INNER_ACRES, sizeof(self->items[0]), (void (*)(void *))(uintptr_t) func_0204e6f8,
                   (void (*)(void *))(uintptr_t) func_0204e6d8);
    __cxa_vec_ctor(self->records, TOWN_LAYOUT_INNER_ACRES, sizeof(TownLayoutAcreRecord), func_02037d10, func_02037d0c);
    return layout;
}
CLEAN_AS(func_0204ead0, TownLayout_Construct)
