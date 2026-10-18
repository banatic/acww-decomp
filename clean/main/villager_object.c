/* A villager's record at 0x734 and the villager's object in it (villager_object.h). */
#include "villager_object.h"

#include "clean.h"
#include "furniture_info.h"
#include "item_attributes.h"
#include "item_object.h"
#include "date_time.h"
#include "player_id.h"
#include "villager_mode_record.h"

static_assert(sizeof(VillagerModeRecord) == 0x24, "mode record");
static_assert(offsetof(VillagerObject, player) == 0x0c, "player");
static_assert(offsetof(VillagerObject, step) == 0x2a, "step");
static_assert(offsetof(VillagerObject, item) == 0x2c, "item");
static_assert(offsetof(VillagerObject, count) == 0x2e, "count");
static_assert(offsetof(VillagerObject, kind) == 0x2f, "kind");
static_assert(offsetof(VillagerObject, flags) == 0x30, "flags");
static_assert(sizeof(VillagerObject) == 0x34, "object");
static_assert(offsetof(VillagerRecord, object) == 0x24, "record");

/* The type whose steps need a count, and how many steps have a figure. */
#define VILLAGER_OBJECT_COUNTED_TYPE 4
#define VILLAGER_OBJECT_COUNTED_STEPS 6

extern const u8 data_020d1a30[VILLAGER_OBJECT_COUNTED_STEPS]; /* the count each step of type 4 needs */
extern const int data_020d1a7c[];                             /* the steps of types 0-4 */

/* Bit `bit` of a byte, as the ARM shifts: by the low byte of `bit`, nothing from 8 on. */
static u8 villager_object_bit(int bit)
{
    u32 amount = (u32) bit & 0xff;
    return amount < 8 ? (u8) (1u << amount) : 0;
}

/* func_0209b5e8 */
VillagerObject *VillagerObject_OfRecord(VillagerRecord *record)
{
    return &record->object;
}
CLEAN_AS(func_0209b5e8, VillagerObject_OfRecord)

/* func_0209b5ec */
VillagerModeRecord *VillagerObject_RecordMode(VillagerRecord *record)
{
    return &record->mode;
}
CLEAN_AS(func_0209b5ec, VillagerObject_RecordMode)

/* func_0209b5f0: a new mode drawn for the record (func_0209c334), then its mode read and
 * dropped. */
void VillagerObject_DrawRecordMode(VillagerRecord *record, int a, int b)
{
    VillagerModeRecord_Redraw(&record->mode, (const u8 *) (uintptr_t) a, b);
    VillagerModeRecord_Mode(&record->mode);
}
CLEAN_AS(func_0209b5f0, VillagerObject_DrawRecordMode)

/* func_0209b604: the mode record and the object emptied. */
void VillagerObject_ClearRecord(VillagerRecord *record)
{
    VillagerModeRecord_Init(&record->mode);
    VillagerObject_Clear(&record->object);
}
CLEAN_AS(func_0209b604, VillagerObject_ClearRecord)

/* func_0209b61c: the record's destructor. */
VillagerRecord *VillagerObject_DestructRecord(VillagerRecord *record)
{
    VillagerObject_Destruct(&record->object);
    VillagerModeRecord_Destruct(&record->mode);
    return record;
}
CLEAN_AS(func_0209b61c, VillagerObject_DestructRecord)

/* func_0209b634: the record's constructor. */
VillagerRecord *VillagerObject_ConstructRecord(VillagerRecord *record)
{
    VillagerModeRecord_Construct(&record->mode);
    VillagerObject_Construct(&record->object);
    return record;
}
CLEAN_AS(func_0209b634, VillagerObject_ConstructRecord)

/* func_0209b64c: whether the object holds type 4 at a step below 6 whose count has reached the
 * step's figure. */
int VillagerObject_IsCountReached(VillagerObject *object)
{
    u8 *held = VillagerObject_Base(object);
    if (ItemObject_IsInUse((ItemObject *) (void *) held) == 0 ||
        ItemObject_Type((ItemObject *) (void *) held) != VILLAGER_OBJECT_COUNTED_TYPE) {
        return 0;
    }
    int step = VillagerObject_Step(object);
    if (step >= VILLAGER_OBJECT_COUNTED_STEPS) {
        return 0;
    }
    return VillagerObject_Count(object) >= data_020d1a30[step];
}
CLEAN_AS(func_0209b64c, VillagerObject_IsCountReached)

/* func_0209b69c: `amount` added to the count, at most 14; the new count.
 * QUIRK: there is no lower bound: a sum below 0 is kept as its low byte. */
u8 VillagerObject_AddCount(VillagerObject *object, int amount)
{
    int count = object->count + amount;
    if (count > VILLAGER_OBJECT_COUNT_MAX) {
        count = VILLAGER_OBJECT_COUNT_MAX;
    }
    object->count = (u8) count;
    return object->count;
}
CLEAN_AS(func_0209b69c, VillagerObject_AddCount)

/* func_0209b6b8 */
u8 VillagerObject_Count(VillagerObject *object)
{
    return object->count;
}
CLEAN_AS(func_0209b6b8, VillagerObject_Count)

/* func_0209b870 */
void VillagerObject_ClearFlags(VillagerObject *object)
{
    object->flags = 0;
}
CLEAN_AS(func_0209b870, VillagerObject_ClearFlags)

/* func_0209b878: whether flag `flag` (0-2) is set; never for others. */
int VillagerObject_TestFlag(VillagerObject *object, u32 flag)
{
    return flag < VILLAGER_OBJECT_FLAGS && ((object->flags >> flag) & 1) != 0;
}
CLEAN_AS(func_0209b878, VillagerObject_TestFlag)

/* func_0209b890: flag `flag` set (bits 3-7 of the byte too, for 3-7; nothing from 8 on). */
void VillagerObject_SetFlag(VillagerObject *object, int flag)
{
    object->flags |= villager_object_bit(flag);
}
CLEAN_AS(func_0209b890, VillagerObject_SetFlag)

/* func_0209b8a4: the flags cleared and the kind set. */
void VillagerObject_SetKind(VillagerObject *object, u8 kind)
{
    VillagerObject_ClearFlags(object);
    object->kind = kind;
}
CLEAN_AS(func_0209b8a4, VillagerObject_SetKind)

/* func_0209b8bc */
u8 VillagerObject_Kind(VillagerObject *object)
{
    return object->kind;
}
CLEAN_AS(func_0209b8bc, VillagerObject_Kind)

/* func_0209b8c4 */
u16 *VillagerObject_Item(VillagerObject *object)
{
    return &object->item;
}
CLEAN_AS(func_0209b8c4, VillagerObject_Item)

/* func_0209b8c8: the date of the object (func_0209bc20). */
DateTime *VillagerObject_Date(VillagerObject *object)
{
    return ItemObject_Date((ItemObject *) (void *) object->object);
}
CLEAN_AS(func_0209b8c8, VillagerObject_Date)

/* func_0209b8d0: how many steps type `type` goes through (data_020d1a7c: 5, 5, 5, 7, 7 for
 * types 0-4); 0 for the types of the other groups. */
int VillagerObject_StepsForType(int type)
{
    if (ItemObject_GroupOfType(type) == 0) {
        int place = 0;
        if (ItemObject_PlaceInGroupOfType(&place, type) != 0) {
            return data_020d1a7c[place];
        }
    }
    return 0;
}
CLEAN_AS(func_0209b8d0, VillagerObject_StepsForType)

/* func_0209b908 */
DesignCreator *VillagerObject_Player(VillagerObject *object)
{
    return &object->player;
}
CLEAN_AS(func_0209b908, VillagerObject_Player)

/* func_0209b90c */
void VillagerObject_SetStep(VillagerObject *object, u8 step)
{
    object->step = step;
}
CLEAN_AS(func_0209b90c, VillagerObject_SetStep)

/* func_0209b914 */
u8 VillagerObject_Step(VillagerObject *object)
{
    return object->step;
}
CLEAN_AS(func_0209b914, VillagerObject_Step)

/* func_0209b91c: the object at the start of the villager's object. */
u8 *VillagerObject_Base(VillagerObject *object)
{
    return object->object;
}
CLEAN_AS(func_0209b91c, VillagerObject_Base)

/* The type and step at which an item given to the object also sets its kind (an item
 * 0x450c-0x45db), and the step VillagerObject_Clear leaves. */
#define VILLAGER_OBJECT_KIND_TYPE 2
#define VILLAGER_OBJECT_KIND_STEP 2
#define VILLAGER_OBJECT_STEP_CLEARED 7
#define VILLAGER_OBJECT_NO_ITEM 0xfff1

/* The object at the start of the villager's object, as an ItemObject. */
static ItemObject *villager_object_held(VillagerObject *object)
{
    return (ItemObject *) VillagerObject_Base(object);
}

/* func_0209b920: a group 0 type in the object goes on a step: the item is taken
 * (VillagerObject_ClearItem), and the step goes up by one unless the type is 4 and its count has
 * not reached the step's figure. Nothing for an empty object, a type of another group, or the
 * last step of the type. */
void VillagerObject_NextStep(VillagerObject *object)
{
    ItemObject *held = villager_object_held(object);
    if (ItemObject_IsInUse(held) == 0 || ItemObject_Group(held) != 0) {
        return;
    }
    int steps = VillagerObject_StepsForType(ItemObject_Type(held));
    int step = VillagerObject_Step(object);
    if (step >= steps - 1) {
        return;
    }
    int advance = 1;
    if (ItemObject_Type(held) == VILLAGER_OBJECT_COUNTED_TYPE) {
        advance = VillagerObject_IsCountReached(object);
    }
    VillagerObject_ClearItem(object);
    if (advance != 0) {
        VillagerObject_SetStep(object, (u8) (step + 1));
    }
}
CLEAN_AS(func_0209b920, VillagerObject_NextStep)

/* func_0209b998: a group 0 type whose low five bits of byte 0x0b are 1 gets 2 there. */
void VillagerObject_SetLow5From1To2(VillagerObject *object)
{
    ItemObject *held = villager_object_held(object);
    if (ItemObject_IsInUse(held) != 0 && ItemObject_Group(held) == 0 && ItemObject_Low5(held) == 1) {
        ItemObject_SetLow5(held, 2);
    }
}
CLEAN_AS(func_0209b998, VillagerObject_SetLow5From1To2)

/* func_0209b9cc: an item given to the object. With `fresh` set, the object starts over with type
 * `type` and the item (VillagerObject_Start); otherwise the low five bits of byte 0x0b are
 * cleared and the item kept, and at step 2 of type 2 an item 0x450c-0x45db also sets the kind
 * (its museum kind, the flags cleared). Then, with a player, the player is copied, the date set
 * to now and bits 5-7 of byte 0x0b cleared; without one the player is cleared. */
void VillagerObject_Set(VillagerObject *object, u32 type, const u16 *item, const DesignCreator *player, u8 fresh)
{
    if (fresh != 0) {
        VillagerObject_Start(object, (int) type, item);
    } else {
        ItemObject_SetLow5(villager_object_held(object), 0);
        ItemObject_SetItem(villager_object_held(object), item);
        if (ItemObject_Type(villager_object_held(object)) == VILLAGER_OBJECT_KIND_TYPE &&
            VillagerObject_Step(object) == VILLAGER_OBJECT_KIND_STEP && *item >= ITEM_ATTRIBUTES_KIND_ITEM_FIRST &&
            *item <= ITEM_ATTRIBUTES_KIND_ITEM_LAST) {
            VillagerObject_SetKind(object, (u8) FurnitureInfo_MuseumKind(item));
        }
    }
    if (player != NULL) {
        PlayerId_Copy(VillagerObject_Player(object), player);
        DateTime_Now(ItemObject_Date(villager_object_held(object)));
        ItemObject_SetHigh3(villager_object_held(object), 0);
    } else {
        PlayerId_Clear(VillagerObject_Player(object));
    }
}
CLEAN_AS(func_0209b9cc, VillagerObject_Set)

/* func_0209ba7c: the item taken: the low five bits of byte 0x0b cleared, no item in the object,
 * the player cleared and no item at 0x2c either. */
void VillagerObject_ClearItem(VillagerObject *object)
{
    ItemObject_SetLow5(villager_object_held(object), 0);
    u16 none = VILLAGER_OBJECT_NO_ITEM;
    ItemObject_SetItem(villager_object_held(object), &none);
    PlayerId_Clear(VillagerObject_Player(object));
    *VillagerObject_Item(object) = VILLAGER_OBJECT_NO_ITEM;
}
CLEAN_AS(func_0209ba7c, VillagerObject_ClearItem)

/* func_0209bac0: the object emptied, then set to type `type` with the item, at step 0. Gives 0. */
int VillagerObject_Start(VillagerObject *object, int type, const u16 *item)
{
    VillagerObject_Clear(object);
    VillagerObject_SetObject(object, type, item);
    object->step = 0;
    return 0;
}
CLEAN_AS(func_0209bac0, VillagerObject_Start)

/* func_0209bae4: the object's type and item set, the low five bits of byte 0x0b cleared. */
void VillagerObject_SetObject(VillagerObject *object, int type, const u16 *item)
{
    ItemObject_Set(villager_object_held(object), (u8) type, item, 0);
}
CLEAN_AS(func_0209bae4, VillagerObject_SetObject)

/* func_0209baf4: emptied: no type or item, no player, step 7, no item at 0x2c, the count 0, no
 * kind and the flags cleared. */
void VillagerObject_Clear(VillagerObject *object)
{
    ItemObject_Clear(villager_object_held(object));
    PlayerId_Clear(&object->player);
    object->step = VILLAGER_OBJECT_STEP_CLEARED;
    object->item = VILLAGER_OBJECT_NO_ITEM;
    object->count = 0;
    object->kind = VILLAGER_OBJECT_KIND_NONE;
    object->flags = 0;
}
CLEAN_AS(func_0209baf4, VillagerObject_Clear)

/* func_0209bb30: the destructor. */
VillagerObject *VillagerObject_Destruct(VillagerObject *object)
{
    PlayerId_Destruct(&object->player);
    ItemObject_Destruct(villager_object_held(object));
    return object;
}
CLEAN_AS(func_0209bb30, VillagerObject_Destruct)

/* func_0209bb48: the constructor: the object constructed (date zeroed, no item or type), the
 * player constructed, and no item at 0x2c. */
VillagerObject *VillagerObject_Construct(VillagerObject *object)
{
    ItemObject_Construct(villager_object_held(object));
    PlayerId_Construct(&object->player);
    object->item = VILLAGER_OBJECT_NO_ITEM;
    return object;
}
CLEAN_AS(func_0209bb48, VillagerObject_Construct)
