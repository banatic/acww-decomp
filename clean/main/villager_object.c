/* A villager's record at 0x734 and the villager's object in it (villager_object.h). */
#include "villager_object.h"

#include "clean.h"

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

/* The mode record: a new mode drawn (its scores taken from `a`, func_0209c470 run when `b` is
 * not 0, both dates set to now), its mode, emptied, destroyed and constructed. */
extern void func_0209c334(VillagerModeRecord *record, int a, int b);
extern int func_0209c330(const VillagerModeRecord *record);
extern void func_0209c398(VillagerModeRecord *record);
extern VillagerModeRecord *func_0209c3c8(VillagerModeRecord *record);
extern VillagerModeRecord *func_0209c3e4(VillagerModeRecord *record);
/* The villager's object: emptied, destroyed and constructed. */
extern void func_0209baf4(VillagerObject *object);
extern VillagerObject *func_0209bb30(VillagerObject *object);
extern VillagerObject *func_0209bb48(VillagerObject *object);
/* An object: whether it holds something, its type, and its date (the object itself). */
extern int func_0209bd44(const u8 *object);
extern int func_0209bc40(const u8 *object);
extern DateTime *func_0209bc20(u8 *object);
/* A type's group (0 for 0-4, 1 for 5-21, 2 for none) and its place in the group. */
extern int func_0209bd10(int type);
extern int func_0209bcd4(int *place, int type);

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
    func_0209c334(&record->mode, a, b);
    func_0209c330(&record->mode);
}
CLEAN_AS(func_0209b5f0, VillagerObject_DrawRecordMode)

/* func_0209b604: the mode record and the object emptied. */
void VillagerObject_ClearRecord(VillagerRecord *record)
{
    func_0209c398(&record->mode);
    func_0209baf4(&record->object);
}
CLEAN_AS(func_0209b604, VillagerObject_ClearRecord)

/* func_0209b61c: the record's destructor. */
VillagerRecord *VillagerObject_DestructRecord(VillagerRecord *record)
{
    func_0209bb30(&record->object);
    func_0209c3c8(&record->mode);
    return record;
}
CLEAN_AS(func_0209b61c, VillagerObject_DestructRecord)

/* func_0209b634: the record's constructor. */
VillagerRecord *VillagerObject_ConstructRecord(VillagerRecord *record)
{
    func_0209c3e4(&record->mode);
    func_0209bb48(&record->object);
    return record;
}
CLEAN_AS(func_0209b634, VillagerObject_ConstructRecord)

/* func_0209b64c: whether the object holds type 4 at a step below 6 whose count has reached the
 * step's figure. */
int VillagerObject_IsCountReached(VillagerObject *object)
{
    u8 *held = VillagerObject_Base(object);
    if (func_0209bd44(held) == 0 || func_0209bc40(held) != VILLAGER_OBJECT_COUNTED_TYPE) {
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
    return func_0209bc20(object->object);
}
CLEAN_AS(func_0209b8c8, VillagerObject_Date)

/* func_0209b8d0: how many steps type `type` goes through (data_020d1a7c: 5, 5, 5, 7, 7 for
 * types 0-4); 0 for the types of the other groups. */
int VillagerObject_StepsForType(int type)
{
    if (func_0209bd10(type) == 0) {
        int place = 0;
        if (func_0209bcd4(&place, type) != 0) {
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
