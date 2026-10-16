/* The record each of the town's villagers keeps at 0x734 (func_0207f1c8): its mode record
 * (VillagerModeRecord, villager_mode.h) and, at 0x24, the villager's object.
 *
 * The villager's object (0x34 bytes):
 *
 *   0x00  an object (12 bytes: a date at 0, its item at 8, its type at 0x0a, five low bits of
 *         byte 0x0b); types 0-4 (group 0) go through steps, 5 or 7 of them
 *         (VillagerObject_StepsForType)
 *   0x0c  a player's id (DesignCreator)
 *   0x2a  the step reached (7 when emptied)
 *   0x2c  an item (0xfff1: none)
 *   0x2e  a count, at most 14; for type 4 a step is done once it reaches data_020d1a30's
 *         figure for the step (2, 4, 6, 8, 10, 13: VillagerObject_IsCountReached)
 *   0x2f  a kind of the items 0x450c-0x45db (item_attributes.h), 0x18 for none
 *   0x30  three flags, bits 0-2
 *
 * Session messages 60-63 carry changes to it to the other systems (session_villager.h). */
#ifndef CLEAN_MAIN_VILLAGER_OBJECT_H
#define CLEAN_MAIN_VILLAGER_OBJECT_H

#include "calendar.h"
#include "design.h"
#include "types.h"
#include "villager_mode.h"

#define VILLAGER_OBJECT_COUNT_MAX 14
#define VILLAGER_OBJECT_KIND_NONE 0x18
#define VILLAGER_OBJECT_FLAGS 3

typedef struct VillagerObject {
    u8 object[12];        /* 0x00 */
    DesignCreator player; /* 0x0c */
    u8 step;              /* 0x2a */
    u8 unused_2b;
    u16 item; /* 0x2c */
    u8 count; /* 0x2e */
    u8 kind;  /* 0x2f */
    u8 flags; /* 0x30 */
    u8 unused_31[3];
} VillagerObject;

typedef struct VillagerRecord {
    VillagerModeRecord mode; /* 0x00 */
    VillagerObject object;   /* 0x24 */
} VillagerRecord;

VillagerObject *VillagerObject_OfRecord(VillagerRecord *record);
VillagerModeRecord *VillagerObject_RecordMode(VillagerRecord *record);
void VillagerObject_DrawRecordMode(VillagerRecord *record, int a, int b);
void VillagerObject_ClearRecord(VillagerRecord *record);
VillagerRecord *VillagerObject_DestructRecord(VillagerRecord *record);
VillagerRecord *VillagerObject_ConstructRecord(VillagerRecord *record);
int VillagerObject_IsCountReached(VillagerObject *object);
u8 VillagerObject_AddCount(VillagerObject *object, int amount);
u8 VillagerObject_Count(VillagerObject *object);
void VillagerObject_ClearFlags(VillagerObject *object);
int VillagerObject_TestFlag(VillagerObject *object, u32 flag);
void VillagerObject_SetFlag(VillagerObject *object, int flag);
void VillagerObject_SetKind(VillagerObject *object, u8 kind);
u8 VillagerObject_Kind(VillagerObject *object);
u16 *VillagerObject_Item(VillagerObject *object);
DateTime *VillagerObject_Date(VillagerObject *object);
int VillagerObject_StepsForType(int type);
DesignCreator *VillagerObject_Player(VillagerObject *object);
void VillagerObject_SetStep(VillagerObject *object, u8 step);
u8 VillagerObject_Step(VillagerObject *object);
u8 *VillagerObject_Base(VillagerObject *object);
void VillagerObject_NextStep(VillagerObject *object);
void VillagerObject_SetLow5From1To2(VillagerObject *object);
void VillagerObject_Set(VillagerObject *object, u32 type, const u16 *item, const DesignCreator *player, u8 fresh);
void VillagerObject_ClearItem(VillagerObject *object);
int VillagerObject_Start(VillagerObject *object, int type, const u16 *item);
void VillagerObject_SetObject(VillagerObject *object, int type, const u16 *item);
void VillagerObject_Clear(VillagerObject *object);
VillagerObject *VillagerObject_Destruct(VillagerObject *object);
VillagerObject *VillagerObject_Construct(VillagerObject *object);

#endif
