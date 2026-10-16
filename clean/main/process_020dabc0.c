/* The process of vtable data_020dabc0 (process_020dabc0.h). */
#include "process_020dabc0.h"

#include "backup_card.h"
#include "clean.h"
#include "event_calendar.h"
#include "event_schedule.h"
#include "player_record.h"
#include "player_records.h"
#include "session.h"
#include "start_kind.h"

/* This class's vtable and the base class's (Process). */
extern const u32 data_020dabc0[];
extern const u32 data_020da13c[];

/* func_0203fa9c (vtable slot 0x40): the destructor. */
Process *Process020dabc0_Destruct(Process *process)
{
    process->vtable = data_020dabc0;
    process->vtable = data_020da13c;
    Process_Destruct(process);
    return process;
}
CLEAN_AS(func_0203fa9c, Process020dabc0_Destruct)

/* func_0203fabc (vtable slot 0x44): the destructor that also frees the process. */
Process *Process020dabc0_DestructFree(Process *process)
{
    process->vtable = data_020dabc0;
    process->vtable = data_020da13c;
    Process_Destruct(process);
    Heap_FreeAux(process);
    return process;
}
CLEAN_AS(func_0203fabc, Process020dabc0_DestructFree)

/* func_0203fae4 (asked before the date checks; 1 skips them): 1 while the game is being started
 * (a start kind is set), without a current player, or when the current player's flag 1 is
 * set. */
int Process020dabc0_IsHeldBack(void)
{
    if (StartKind_IsSet()) {
        return 1;
    }
    u8 *record = PlayerRecords_Current();
    if (record == NULL || PlayerRecord_TestFlag(record, 1)) {
        return 1;
    }
    return 0;
}
CLEAN_AS(func_0203fae4, Process020dabc0_IsHeldBack)

/* Whether a session was linked when the process was last created. */
extern int data_021c74b4;
extern NetSession *data_020ccf94;
extern BackupCard data_021c8188;

/* func_0203fb3c (vtable slot 0x00): the calendar's list of today's events made again when a
 * session is linked or was at the last creation; always 1. */
int Process020dabc0_Create(void)
{
    if (!Session_IsLinked(data_020ccf94)) {
        if (data_021c74b4) {
            EventCalendar_Refresh(0);
        }
        data_021c74b4 = 0;
    } else {
        EventCalendar_Refresh(0);
        data_021c74b4 = 1;
    }
    return 1;
}
CLEAN_AS(func_0203fb3c, Process020dabc0_Create)

/* func_0203fb10 (vtable slot 0x0c): always 1. */
int Process020dabc0_Delete(void)
{
    return 1;
}
CLEAN_AS(func_0203fb10, Process020dabc0_Delete)

/* func_0203fb18 (vtable slot 0x18): unless the save memory is busy, the calendar's list of
 * today's events kept to the date and the schedule checked for the hour; always 1. */
int Process020dabc0_Execute(Process *process)
{
    if (BackupCard_Status(&data_021c8188) != BACKUP_CARD_BUSY) {
        EventCalendar_RefreshIfStale((int) (uintptr_t) process);
        EventSchedule_HourlyCheck();
    }
    return 1;
}
CLEAN_AS(func_0203fb18, Process020dabc0_Execute)

/* func_0203fb14 (vtable slot 0x24): always 1. */
int Process020dabc0_Draw(void)
{
    return 1;
}
CLEAN_AS(func_0203fb14, Process020dabc0_Draw)

/* func_0204087c: a new process of this class (0x50 bytes from the auxiliary heap, cleared),
 * NULL when there is no room. */
Process *Process020dabc0_New(void)
{
    Process *process = Heap_AllocAuxZeroed(0x50);
    if (process != NULL) {
        Process_Construct(process);
        process->vtable = data_020da13c;
        process->vtable = data_020dabc0;
    }
    return process;
}
CLEAN_AS(func_0204087c, Process020dabc0_New)
