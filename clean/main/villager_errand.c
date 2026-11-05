/* The villagers' errands, records of 12 bytes (villager_errand.h). */
#include "villager_errand.h"

#include "clean.h"
#include "date_time.h"

static_assert(offsetof(VillagerErrand, item) == 0x08, "item");
static_assert(offsetof(VillagerErrand, type) == 0x0a, "type");
static_assert(offsetof(VillagerErrand, bits) == 0x0b, "bits");
static_assert(sizeof(VillagerErrand) == 12, "size");

#define VILLAGER_ERRAND_PROGRESS_MASK 0x1f
#define VILLAGER_ERRAND_WAIT_PLACE_MASK 0xe0
#define VILLAGER_ERRAND_WAIT_PLACE_SHIFT 5

#define VILLAGER_ERRAND_CLASSES 4
#define VILLAGER_ERRAND_GROUPS 2

/* The first type of each class and of each group. */
extern const int data_020d1a6c[VILLAGER_ERRAND_CLASSES]; /* 0, 10, 20, 21 */
extern const int data_020d1a40[VILLAGER_ERRAND_GROUPS];  /* 0, 5 */

/* func_0209bb68 */
void VillagerErrand_SetItem(VillagerErrand *object, const u16 *item)
{
    object->item = *item;
}
CLEAN_AS(func_0209bb68, VillagerErrand_SetItem)

/* func_0209bb70 */
u16 *VillagerErrand_Item(VillagerErrand *object)
{
    return &object->item;
}
CLEAN_AS(func_0209bb70, VillagerErrand_Item)

/* func_0209bb74: bits 5-7 of byte 0x0b become the low three bits of `value`. */
void VillagerErrand_SetWaitPlace(VillagerErrand *object, u32 value)
{
    object->bits =
        (u8) ((object->bits & ~VILLAGER_ERRAND_WAIT_PLACE_MASK) | ((value & 7u) << VILLAGER_ERRAND_WAIT_PLACE_SHIFT));
}
CLEAN_AS(func_0209bb74, VillagerErrand_SetWaitPlace)

/* func_0209bb88 */
int VillagerErrand_WaitPlace(VillagerErrand *object)
{
    return object->bits >> VILLAGER_ERRAND_WAIT_PLACE_SHIFT;
}
CLEAN_AS(func_0209bb88, VillagerErrand_WaitPlace)

/* func_0209bb90: bits 0-4 of byte 0x0b become the low five bits of `value`. */
void VillagerErrand_SetProgress(VillagerErrand *object, int value)
{
    object->bits = (u8) ((object->bits & ~VILLAGER_ERRAND_PROGRESS_MASK) | (value & VILLAGER_ERRAND_PROGRESS_MASK));
}
CLEAN_AS(func_0209bb90, VillagerErrand_SetProgress)

/* func_0209bba0 */
int VillagerErrand_Progress(VillagerErrand *object)
{
    return object->bits & VILLAGER_ERRAND_PROGRESS_MASK;
}
CLEAN_AS(func_0209bba0, VillagerErrand_Progress)

/* func_0209bba8: the band of the object's type (VillagerErrand_StepBandOfType). */
int VillagerErrand_StepBand(VillagerErrand *object)
{
    return VillagerErrand_StepBandOfType(object->type);
}
CLEAN_AS(func_0209bba8, VillagerErrand_StepBand)

/* func_0209bbb4: for the types of class 1, 0 for type 10, 1 for 11-18 and 2 for 19; 4 for the
 * types of the other classes.
 * QUIRK: the code also gives 3 for type 20 of class 1, which no type of class 1 can be. */
int VillagerErrand_StepBandOfType(u32 type)
{
    if (VillagerErrand_ClassOfType(type) != 1) {
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
CLEAN_AS(func_0209bbb4, VillagerErrand_StepBandOfType)

/* func_0209bbec: the split of the object's type (VillagerErrand_Class1SplitOfType), as a byte. */
u8 VillagerErrand_Class1Split(VillagerErrand *object)
{
    return (u8) VillagerErrand_Class1SplitOfType(object->type);
}
CLEAN_AS(func_0209bbec, VillagerErrand_Class1Split)

/* func_0209bbf8: for the types of class 1, 0 for types 10-18 and 1 for 19; 2 for the types of
 * the other classes. */
int VillagerErrand_Class1SplitOfType(u32 type)
{
    if (VillagerErrand_ClassOfType(type) != 1) {
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
CLEAN_AS(func_0209bbf8, VillagerErrand_Class1SplitOfType)

/* func_0209bc20: the date, at the start of the object. */
DateTime *VillagerErrand_Date(VillagerErrand *object)
{
    return &object->date;
}
CLEAN_AS(func_0209bc20, VillagerErrand_Date)

/* func_0209bc24: the date set to now, then `minutes` added to it. */
void VillagerErrand_StampNow(VillagerErrand *object, int minutes)
{
    DateTime_Now(&object->date);
    DateTime_AddMinutes(&object->date, minutes);
}
CLEAN_AS(func_0209bc24, VillagerErrand_StampNow)

/* func_0209bc40 */
int VillagerErrand_Type(VillagerErrand *object)
{
    return object->type;
}
CLEAN_AS(func_0209bc40, VillagerErrand_Type)

/* func_0209bc44: the place of the object's type within its class (VillagerErrand_PlaceInClassOfType). */
int VillagerErrand_PlaceInClass(VillagerErrand *object, int *place)
{
    return VillagerErrand_PlaceInClassOfType(place, object->type);
}
CLEAN_AS(func_0209bc44, VillagerErrand_PlaceInClass)

/* func_0209bc54: whether `type` is in one of the four classes; if so `*place` is set to its
 * place within the class (left as it was otherwise). */
int VillagerErrand_PlaceInClassOfType(int *place, int type)
{
    int class_ = VillagerErrand_ClassOfType((u32) type);
    if (!VillagerErrand_IsClass((u32) class_)) {
        return 0;
    }
    *place = type - data_020d1a6c[class_];
    return 1;
}
CLEAN_AS(func_0209bc54, VillagerErrand_PlaceInClassOfType)

/* func_0209bc88 */
int VillagerErrand_Class(VillagerErrand *object)
{
    return VillagerErrand_ClassOfType(object->type);
}
CLEAN_AS(func_0209bc88, VillagerErrand_Class)

/* func_0209bc94: 0 for types 0-9, 1 for 10-19, 2 for 20, 3 for 21, 4 for the others. */
int VillagerErrand_ClassOfType(u32 type)
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
CLEAN_AS(func_0209bc94, VillagerErrand_ClassOfType)

/* func_0209bcb8 */
int VillagerErrand_IsClass(u32 class_)
{
    return class_ < VILLAGER_ERRAND_CLASSES;
}
CLEAN_AS(func_0209bcb8, VillagerErrand_IsClass)

/* func_0209bcc4: the place of the object's type within its group (VillagerErrand_PlaceInGroupOfType). */
int VillagerErrand_PlaceInGroup(VillagerErrand *object, int *place)
{
    return VillagerErrand_PlaceInGroupOfType(place, object->type);
}
CLEAN_AS(func_0209bcc4, VillagerErrand_PlaceInGroup)

/* func_0209bcd4: whether `type` is in one of the two groups; if so `*place` is set to its place
 * within the group (left as it was otherwise). */
int VillagerErrand_PlaceInGroupOfType(int *place, int type)
{
    int group = VillagerErrand_GroupOfType((u32) type);
    if (!VillagerErrand_IsGroup((u32) group)) {
        return 0;
    }
    *place = type - data_020d1a40[group];
    return 1;
}
CLEAN_AS(func_0209bcd4, VillagerErrand_PlaceInGroupOfType)

/* func_0209bd04 */
int VillagerErrand_Group(VillagerErrand *object)
{
    return VillagerErrand_GroupOfType(object->type);
}
CLEAN_AS(func_0209bd04, VillagerErrand_Group)

/* func_0209bd10: 0 for types 0-4, 1 for 5-21, 2 for the others. */
int VillagerErrand_GroupOfType(u32 type)
{
    if (type < 5) {
        return 0;
    }
    if (type < VILLAGER_ERRAND_TYPE_NONE) {
        return 1;
    }
    return 2;
}
CLEAN_AS(func_0209bd10, VillagerErrand_GroupOfType)

/* func_0209bd24 */
int VillagerErrand_IsGroup(u32 group)
{
    return group < VILLAGER_ERRAND_GROUPS;
}
CLEAN_AS(func_0209bd24, VillagerErrand_IsGroup)

/* func_0209bd30: the type, the item and bits 0-4 of byte 0x0b set. */
void VillagerErrand_Set(VillagerErrand *object, u8 type, const u16 *item, u8 progress)
{
    object->type = type;
    object->item = *item;
    object->bits = (u8) ((object->bits & ~VILLAGER_ERRAND_PROGRESS_MASK) | (progress & VILLAGER_ERRAND_PROGRESS_MASK));
}
CLEAN_AS(func_0209bd30, VillagerErrand_Set)

/* func_0209bd44: whether the object holds a type (0-21). */
int VillagerErrand_IsInUse(VillagerErrand *object)
{
    return VillagerErrand_IsType(object->type);
}
CLEAN_AS(func_0209bd44, VillagerErrand_IsInUse)

/* func_0209bd50 */
int VillagerErrand_IsType(u32 type)
{
    return type < VILLAGER_ERRAND_TYPE_NONE;
}
CLEAN_AS(func_0209bd50, VillagerErrand_IsType)

/* func_0209bd5c: no type, no item, and byte 0x0b cleared; the date stays. */
void VillagerErrand_Clear(VillagerErrand *object)
{
    object->type = VILLAGER_ERRAND_TYPE_NONE;
    object->item = VILLAGER_ERRAND_NO_ITEM;
    object->bits = 0;
}
CLEAN_AS(func_0209bd5c, VillagerErrand_Clear)

/* func_0209bd7c: the destructor, which does nothing. */
void VillagerErrand_Destruct(VillagerErrand *object)
{
    (void) object;
}
CLEAN_AS(func_0209bd7c, VillagerErrand_Destruct)

/* func_0209bd80: the constructor: the date zeroed, no item and no type; byte 0x0b is left as
 * it was. QUIRK: the original stores the item twice, around the type. */
void VillagerErrand_Construct(VillagerErrand *object)
{
    object->date = (DateTime){0};
    object->item = VILLAGER_ERRAND_NO_ITEM;
    object->type = VILLAGER_ERRAND_TYPE_NONE;
}
CLEAN_AS(func_0209bd80, VillagerErrand_Construct)
