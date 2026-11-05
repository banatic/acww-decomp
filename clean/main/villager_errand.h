/* A villager's errand, a record of 12 bytes: what a villager asks of a player or a player was
 * asked to do for a villager or a shop (the "q.." text sets of the talks name them). The
 * villagers' records keep them (the villager's own errand at 0x24 of the record at 0x734,
 * villager_object.h; the two blocks, the entry and the handover of a player's villager part,
 * villager_part.h; the state table's entries, villager_errands.h; the sickness record; system
 * commands, system_command.c):
 *
 *   0x00  a date: when the errand was given or is due (VillagerErrand_StampNow sets it to now
 *         plus some minutes; constructing the errand zeroes it)
 *   0x08  an item (0xfff1: none): what is to be fetched, delivered or caught
 *   0x0a  the errand's type: 0-21, 22 for none (VillagerErrand_IsInUse)
 *   0x0b  two fields: bits 0-4 the errand's progress (VillagerErrand_Progress: 0 when given,
 *         raised as the errand's steps are done, e.g. HOUSE_VISITOR_VISIT_* of ov068's house
 *         visit, CAMEL_ERRAND_* of ov078) and bits 5-7 the place of the wait a villager's request
 *         was given (VillagerErrand_WaitPlace, villager_talk_request.h)
 *
 * Types 0-4 are the villager's own errands that go through steps (villager_object.h: 0 catch an
 * insect, 1 a fish, 2 a fossil, 3 clothes, 4 furniture); 9 is the sick villager's medicine
 * (villager_sickness_record.h); 10-19 are the step types of a block of the player's villager
 * part (10 an item to take to another villager, 11-18 the steps of the part-time job at Nook's,
 * 19 a letter to deliver); 20 is the part's entry (villager_part_entry.h); 21 the visit to the
 * player's house (ov068 house_visitor.h).
 *
 * The types fall into groups in two ways:
 *   - groups 0 (types 0-4) and 1 (types 5-21), 2 for none (VillagerErrand_GroupOfType), with a
 *     place within the group from the group's first type (data_020d1a40: 0, 5);
 *   - classes 0 (types 0-9), 1 (10-19), 2 (20) and 3 (21), 4 for none (VillagerErrand_ClassOfType),
 *     with a place from the class's first type (data_020d1a6c: 0, 10, 20, 21). Class 1 is split
 *     further by VillagerErrand_StepBandOfType and VillagerErrand_Class1SplitOfType. */
#ifndef CLEAN_MAIN_VILLAGER_ERRAND_H
#define CLEAN_MAIN_VILLAGER_ERRAND_H

#include "calendar.h"
#include "types.h"

#define VILLAGER_ERRAND_NO_ITEM 0xfff1
#define VILLAGER_ERRAND_TYPE_NONE 22

typedef struct VillagerErrand {
    DateTime date; /* 0x00 */
    u16 item;      /* 0x08 */
    u8 type;       /* 0x0a */
    u8 bits;       /* 0x0b: bits 0-4 and 5-7 */
} VillagerErrand;

void VillagerErrand_SetItem(VillagerErrand *object, const u16 *item);
u16 *VillagerErrand_Item(VillagerErrand *object);
void VillagerErrand_SetWaitPlace(VillagerErrand *object, u32 value);
int VillagerErrand_WaitPlace(VillagerErrand *object);
void VillagerErrand_SetProgress(VillagerErrand *object, int value);
int VillagerErrand_Progress(VillagerErrand *object);
int VillagerErrand_StepBand(VillagerErrand *object);
int VillagerErrand_StepBandOfType(u32 type);
u8 VillagerErrand_Class1Split(VillagerErrand *object);
int VillagerErrand_Class1SplitOfType(u32 type);
DateTime *VillagerErrand_Date(VillagerErrand *object);
void VillagerErrand_StampNow(VillagerErrand *object, int minutes);
int VillagerErrand_Type(VillagerErrand *object);
int VillagerErrand_PlaceInClass(VillagerErrand *object, int *place);
int VillagerErrand_PlaceInClassOfType(int *place, int type);
int VillagerErrand_Class(VillagerErrand *object);
int VillagerErrand_ClassOfType(u32 type);
int VillagerErrand_IsClass(u32 class_);
int VillagerErrand_PlaceInGroup(VillagerErrand *object, int *place);
int VillagerErrand_PlaceInGroupOfType(int *place, int type);
int VillagerErrand_Group(VillagerErrand *object);
int VillagerErrand_GroupOfType(u32 type);
int VillagerErrand_IsGroup(u32 group);
void VillagerErrand_Set(VillagerErrand *object, u8 type, const u16 *item, u8 progress);
int VillagerErrand_IsInUse(VillagerErrand *object);
int VillagerErrand_IsType(u32 type);
void VillagerErrand_Clear(VillagerErrand *object);
void VillagerErrand_Destruct(VillagerErrand *object);
void VillagerErrand_Construct(VillagerErrand *object);

#endif
