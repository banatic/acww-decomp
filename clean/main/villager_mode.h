/* The mode record each of the town's villagers keeps at 0x734 (VillagerTown, villager_town.h),
 * and the day-to-day updates of it.
 *
 *   0x00  the date and time the mode was set
 *   0x08  the day up to which the counts below have been taken into the scores
 *   0x10  the mode: 0-7 one of the eight kinds of event (villager_events.h) the villager took
 *         to, 8 none yet, 9 about to leave (villager_residents.h), 10 just moved in, 11 a mode
 *         that turns into a kind the next day; 12 and above: the record is not in use
 *   0x11  a score for each kind, from which a new mode is drawn (func_0209c4a8: one of the
 *         highest at random)
 *   0x19  a count for each kind of the events seen (0-10, func_0209bee8)
 *   0x21  bit 0: set when the record leaves mode 2 (or mode 8 reached from mode 2)
 *   0x24  an object (the villager's object, as in villager_kinds.h)
 *
 * Each villager's data (data_020cd884, at 0x3a, func_02080814) holds eight weights (4.12
 * fixed point) that scale its counts into its scores.
 *
 * A villager also keeps at 0x7d7 a number 0-5 that steps on each time an object of type 4 is
 * done with (VillagerMode_FinishObject). */
#ifndef CLEAN_MAIN_VILLAGER_MODE_H
#define CLEAN_MAIN_VILLAGER_MODE_H

#include "calendar.h"
#include "types.h"

#define VILLAGER_MODE_KINDS 8
#define VILLAGER_MODE_NONE_YET 8
#define VILLAGER_MODE_LEAVING 9
#define VILLAGER_MODE_ARRIVED 10
#define VILLAGER_MODE_11 11
/* What the mode functions give when nothing changed, and the first mode of a record not in use. */
#define VILLAGER_MODE_UNCHANGED 12

/* Bit 0 of byte 0x21. */
#define VILLAGER_MODE_FROM_2 0x01

typedef struct VillagerModeRecord {
    DateTime since;                 /* 0x00 */
    DateTime counted;               /* 0x08 */
    u8 mode;                        /* 0x10 */
    u8 scores[VILLAGER_MODE_KINDS]; /* 0x11 */
    u8 counts[VILLAGER_MODE_KINDS]; /* 0x19 */
    u8 flags;                       /* 0x21: VILLAGER_MODE_FROM_2 */
    u8 unknown_22[2];               /* 0x22 */
} VillagerModeRecord;               /* the object follows at 0x24 */

void VillagerMode_FinishObject(u8 *villager);
int VillagerMode_Update(u8 *villager, DateTime *latest, DateTime *left, const DateTime *now);
int VillagerMode_UpdateDaily(u8 *villager, const DateTime *now);
void VillagerMode_KeepCountedDate(u8 *villager, const DateTime *now);
void VillagerMode_KeepSinceDate(u8 *villager, const DateTime *now);
void VillagerMode_CatchUpScores(u8 *villager, const DateTime *now);
void VillagerMode_AddCount(u8 *villager, int kind, int amount);
void VillagerMode_LearnFrom(u8 *villager, u8 *other);
int VillagerMode_IsWakeTimePast(u8 *villager, const DateTime *now);
void VillagerMode_SetArrived(u8 *villager, const DateTime *now);
void VillagerMode_SetLeaving(u8 *villager, const DateTime *now);
void VillagerMode_StepCounter7D7(u8 *villager);
u8 VillagerMode_Counter7D7(u8 *villager);

#endif
