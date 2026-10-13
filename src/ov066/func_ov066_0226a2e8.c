/* func_ov066_0226a2e8 @ 0x0226a2e8, 0xc8 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

#include "types.h"

typedef struct Slot {
    u16 state; // 0x00
    unsigned char pad_02[0xe0 - 2];
} Slot;

typedef struct Alarm {
    unsigned char pad_00[0x2c];
} Alarm;

typedef struct UnkStruct_0226a2e8 {
    u8 unk_00; // 0x00
    u8 pad_01;
    u8 count; // 0x02
    u8 pad_03;
    Slot *slots;   // 0x04
    Alarm *alarms; // 0x08
} UnkStruct_0226a2e8;

void OS_CancelAlarm(Alarm *alarm);
void OS_SetAlarm(Alarm *alarm, u64 tick, void *handler, void *arg);
void OS_SetAlarmTag(Alarm *alarm, u32 v);
void func_ov066_0226a43c(void *arg);

void func_ov066_0226a2e8(UnkStruct_0226a2e8 *self, int msec)
{
    int i;
    for (i = 0; i < self->count; i++) {
        if (self->slots[i].state == 1) {
            OS_CancelAlarm(&self->alarms[i]);
            OS_SetAlarm(&self->alarms[i], (long long) (msec * 0x82ea / 64), (void *) func_ov066_0226a43c, &self->slots[i]);
            OS_SetAlarmTag(&self->alarms[i], self->unk_00 + 0x80);
        }
    }
}
