/* The villagers' objects of 12 bytes (item_object.h). */
#include "item_object.h"

#include "clean.h"

static_assert(offsetof(ItemObject, item) == 0x08, "item");
static_assert(offsetof(ItemObject, type) == 0x0a, "type");
static_assert(offsetof(ItemObject, bits) == 0x0b, "bits");
static_assert(sizeof(ItemObject) == 12, "size");

#define ITEM_OBJECT_LOW5_MASK 0x1f
#define ITEM_OBJECT_HIGH3_MASK 0xe0
#define ITEM_OBJECT_HIGH3_SHIFT 5

#define ITEM_OBJECT_CLASSES 4
#define ITEM_OBJECT_GROUPS 2

/* The first type of each class and of each group. */
extern const int data_020d1a6c[ITEM_OBJECT_CLASSES]; /* 0, 10, 20, 21 */
extern const int data_020d1a40[ITEM_OBJECT_GROUPS];  /* 0, 5 */

/* The date set to now (func_0209e474), and minutes added to a date, carrying into the hours
 * (func_0209e234). */
extern void func_0209e474(DateTime *date);
extern void func_0209e234(DateTime *date, int minutes);

/* func_0209bb68 */
void ItemObject_SetItem(ItemObject *object, const u16 *item)
{
    object->item = *item;
}
CLEAN_AS(func_0209bb68, ItemObject_SetItem)

/* func_0209bb70 */
u16 *ItemObject_Item(ItemObject *object)
{
    return &object->item;
}
CLEAN_AS(func_0209bb70, ItemObject_Item)

/* func_0209bb74: bits 5-7 of byte 0x0b become the low three bits of `value`. */
void ItemObject_SetHigh3(ItemObject *object, u32 value)
{
    object->bits = (u8) ((object->bits & ~ITEM_OBJECT_HIGH3_MASK) | ((value & 7u) << ITEM_OBJECT_HIGH3_SHIFT));
}
CLEAN_AS(func_0209bb74, ItemObject_SetHigh3)

/* func_0209bb88 */
int ItemObject_High3(ItemObject *object)
{
    return object->bits >> ITEM_OBJECT_HIGH3_SHIFT;
}
CLEAN_AS(func_0209bb88, ItemObject_High3)

/* func_0209bb90: bits 0-4 of byte 0x0b become the low five bits of `value`. */
void ItemObject_SetLow5(ItemObject *object, int value)
{
    object->bits = (u8) ((object->bits & ~ITEM_OBJECT_LOW5_MASK) | (value & ITEM_OBJECT_LOW5_MASK));
}
CLEAN_AS(func_0209bb90, ItemObject_SetLow5)

/* func_0209bba0 */
int ItemObject_Low5(ItemObject *object)
{
    return object->bits & ITEM_OBJECT_LOW5_MASK;
}
CLEAN_AS(func_0209bba0, ItemObject_Low5)

/* func_0209bba8: the band of the object's type (ItemObject_StepBandOfType). */
int ItemObject_StepBand(ItemObject *object)
{
    return ItemObject_StepBandOfType(object->type);
}
CLEAN_AS(func_0209bba8, ItemObject_StepBand)

/* func_0209bbb4: for the types of class 1, 0 for type 10, 1 for 11-18 and 2 for 19; 4 for the
 * types of the other classes.
 * QUIRK: the code also gives 3 for type 20 of class 1, which no type of class 1 can be. */
int ItemObject_StepBandOfType(u32 type)
{
    if (ItemObject_ClassOfType(type) != 1) {
        return 4;
    }
    if (type < 11) {
        return 0;
    }
    if (type < 19) {
        return 1;
    }
    if (type < 20) {
        return 2;
    }
    if (type < 21) {
        return 3;
    }
    return 4;
}
CLEAN_AS(func_0209bbb4, ItemObject_StepBandOfType)

/* func_0209bbec: the split of the object's type (ItemObject_Class1SplitOfType), as a byte. */
u8 ItemObject_Class1Split(ItemObject *object)
{
    return (u8) ItemObject_Class1SplitOfType(object->type);
}
CLEAN_AS(func_0209bbec, ItemObject_Class1Split)

/* func_0209bbf8: for the types of class 1, 0 for types 10-18 and 1 for 19; 2 for the types of
 * the other classes. */
int ItemObject_Class1SplitOfType(u32 type)
{
    if (ItemObject_ClassOfType(type) != 1) {
        return 2;
    }
    if (type < 19) {
        return 0;
    }
    if (type < 20) {
        return 1;
    }
    return 2;
}
CLEAN_AS(func_0209bbf8, ItemObject_Class1SplitOfType)

/* func_0209bc20: the date, at the start of the object. */
DateTime *ItemObject_Date(ItemObject *object)
{
    return &object->date;
}
CLEAN_AS(func_0209bc20, ItemObject_Date)

/* func_0209bc24: the date set to now, then `minutes` added to it. */
void ItemObject_StampNow(ItemObject *object, int minutes)
{
    func_0209e474(&object->date);
    func_0209e234(&object->date, minutes);
}
CLEAN_AS(func_0209bc24, ItemObject_StampNow)

/* func_0209bc40 */
int ItemObject_Type(ItemObject *object)
{
    return object->type;
}
CLEAN_AS(func_0209bc40, ItemObject_Type)

/* func_0209bc44: the place of the object's type within its class (ItemObject_PlaceInClassOfType). */
int ItemObject_PlaceInClass(ItemObject *object, int *place)
{
    return ItemObject_PlaceInClassOfType(place, object->type);
}
CLEAN_AS(func_0209bc44, ItemObject_PlaceInClass)

/* func_0209bc54: whether `type` is in one of the four classes; if so `*place` is set to its
 * place within the class (left as it was otherwise). */
int ItemObject_PlaceInClassOfType(int *place, int type)
{
    int class_ = ItemObject_ClassOfType((u32) type);
    if (!ItemObject_IsClass((u32) class_)) {
        return 0;
    }
    *place = type - data_020d1a6c[class_];
    return 1;
}
CLEAN_AS(func_0209bc54, ItemObject_PlaceInClassOfType)

/* func_0209bc88 */
int ItemObject_Class(ItemObject *object)
{
    return ItemObject_ClassOfType(object->type);
}
CLEAN_AS(func_0209bc88, ItemObject_Class)

/* func_0209bc94: 0 for types 0-9, 1 for 10-19, 2 for 20, 3 for 21, 4 for the others. */
int ItemObject_ClassOfType(u32 type)
{
    if (type < 10) {
        return 0;
    }
    if (type < 20) {
        return 1;
    }
    if (type < 21) {
        return 2;
    }
    if (type < 22) {
        return 3;
    }
    return 4;
}
CLEAN_AS(func_0209bc94, ItemObject_ClassOfType)

/* func_0209bcb8 */
int ItemObject_IsClass(u32 class_)
{
    return class_ < ITEM_OBJECT_CLASSES;
}
CLEAN_AS(func_0209bcb8, ItemObject_IsClass)

/* func_0209bcc4: the place of the object's type within its group (ItemObject_PlaceInGroupOfType). */
int ItemObject_PlaceInGroup(ItemObject *object, int *place)
{
    return ItemObject_PlaceInGroupOfType(place, object->type);
}
CLEAN_AS(func_0209bcc4, ItemObject_PlaceInGroup)

/* func_0209bcd4: whether `type` is in one of the two groups; if so `*place` is set to its place
 * within the group (left as it was otherwise). */
int ItemObject_PlaceInGroupOfType(int *place, int type)
{
    int group = ItemObject_GroupOfType((u32) type);
    if (!ItemObject_IsGroup((u32) group)) {
        return 0;
    }
    *place = type - data_020d1a40[group];
    return 1;
}
CLEAN_AS(func_0209bcd4, ItemObject_PlaceInGroupOfType)

/* func_0209bd04 */
int ItemObject_Group(ItemObject *object)
{
    return ItemObject_GroupOfType(object->type);
}
CLEAN_AS(func_0209bd04, ItemObject_Group)

/* func_0209bd10: 0 for types 0-4, 1 for 5-21, 2 for the others. */
int ItemObject_GroupOfType(u32 type)
{
    if (type < 5) {
        return 0;
    }
    if (type < ITEM_OBJECT_TYPE_NONE) {
        return 1;
    }
    return 2;
}
CLEAN_AS(func_0209bd10, ItemObject_GroupOfType)

/* func_0209bd24 */
int ItemObject_IsGroup(u32 group)
{
    return group < ITEM_OBJECT_GROUPS;
}
CLEAN_AS(func_0209bd24, ItemObject_IsGroup)

/* func_0209bd30: the type, the item and bits 0-4 of byte 0x0b set. */
void ItemObject_Set(ItemObject *object, u8 type, const u16 *item, u8 low5)
{
    object->type = type;
    object->item = *item;
    object->bits = (u8) ((object->bits & ~ITEM_OBJECT_LOW5_MASK) | (low5 & ITEM_OBJECT_LOW5_MASK));
}
CLEAN_AS(func_0209bd30, ItemObject_Set)

/* func_0209bd44: whether the object holds a type (0-21). */
int ItemObject_IsInUse(ItemObject *object)
{
    return ItemObject_IsType(object->type);
}
CLEAN_AS(func_0209bd44, ItemObject_IsInUse)

/* func_0209bd50 */
int ItemObject_IsType(u32 type)
{
    return type < ITEM_OBJECT_TYPE_NONE;
}
CLEAN_AS(func_0209bd50, ItemObject_IsType)

/* func_0209bd5c: no type, no item, and byte 0x0b cleared; the date stays. */
void ItemObject_Clear(ItemObject *object)
{
    object->type = ITEM_OBJECT_TYPE_NONE;
    object->item = ITEM_OBJECT_NO_ITEM;
    object->bits = 0;
}
CLEAN_AS(func_0209bd5c, ItemObject_Clear)

/* func_0209bd7c: the destructor, which does nothing. */
void ItemObject_Destruct(ItemObject *object)
{
    (void) object;
}
CLEAN_AS(func_0209bd7c, ItemObject_Destruct)

/* func_0209bd80: the constructor: the date zeroed, no item and no type; byte 0x0b is left as
 * it was. QUIRK: the original stores the item twice, around the type. */
void ItemObject_Construct(ItemObject *object)
{
    object->date = (DateTime){0};
    object->item = ITEM_OBJECT_NO_ITEM;
    object->type = ITEM_OBJECT_TYPE_NONE;
}
CLEAN_AS(func_0209bd80, ItemObject_Construct)
