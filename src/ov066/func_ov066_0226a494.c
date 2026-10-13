/* func_ov066_0226a494 @ 0x0226a494, 0x344 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

#include "types.h"

typedef struct {
    u8 pad_00[0x2c];
} OSAlarm;
typedef void (*OSAlarmHandler)(void *);

typedef struct Entry {
    u16 state;
    u8 unk_02[6];
    u16 chan;
    u8 avg;
    u8 idx;
    u8 hist[6];
    u8 pad_12[2];
    struct Mgr *owner;
    u8 pad_18[8];
    u8 payload[0xc0];
} Entry;

typedef struct Mgr {
    u8 tag;
    u8 num_active;
    volatile u8 capacity;
    u8 pad_03;
    Entry *entries;
    OSAlarm *alarms;
    void (*cb)(Entry *);
} Mgr;

extern int func_ov066_022683b4(const u8 *a, const u8 *b);
extern void OS_CancelAlarm(OSAlarm *a);
extern u32 OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(u32 s);
extern void MIi_CpuCopyFast(const void *src, void *dst, u32 n);
extern void DC_StoreRange(void *p, u32 n);
extern void OS_SetAlarm(OSAlarm *a, s64 tick, OSAlarmHandler h, void *arg);
extern void OS_SetAlarmTag(OSAlarm *a, u32 tag);
extern void func_ov066_0226a43c(void *arg);

BOOL func_ov066_0226a494(Mgr *m, int interval, const u8 *mac, u16 chan, u16 level, const void *payload)
{
    int i, k, sum;
    u8 t;
    Entry *e;
    u32 lv;
    u8 lvl;
    u32 en;

    lv = level;
    if (lv > 0xff) {
        lv = 0xff;
    }
    lvl = (u8) lv;

    if (m->num_active != 0) {
        for (i = 0; i < m->capacity; i++) {
            if (m->entries[i].state == 1 && func_ov066_022683b4(m->entries[i].unk_02, mac) == 0) {
                OS_CancelAlarm(&m->alarms[i]);
                en = OS_DisableInterrupts();
                m->entries[i].chan = chan;
                t = (u8) (m->entries[i].idx + 1) % 6;
                m->entries[i].idx = t;
                m->entries[i].hist[t] = lvl;
                sum = 0;
                for (k = 0; k < 6; k++) {
                    sum += m->entries[i].hist[k];
                }
                m->entries[i].avg = (u8) (sum / 6);
                MIi_CpuCopyFast(payload, m->entries[i].payload, 0xc0);
                DC_StoreRange(m->entries[i].payload, 0xc0);
                OS_RestoreInterrupts(en);
                OS_SetAlarm(&m->alarms[i], (s64) ((s32) (interval * 33514) / 64), func_ov066_0226a43c, &m->entries[i]);
                OS_SetAlarmTag(&m->alarms[i], (u32) (m->tag + 0x80));
                return 1;
            }
        }
    }

    for (i = 0; i < m->capacity; i++) {
        e = &m->entries[i];
        if (e->state == 0) {
            en = OS_DisableInterrupts();
            m->num_active++;
            e->state = 1;
            e->unk_02[0] = mac[0];
            e->unk_02[1] = mac[1];
            e->unk_02[2] = mac[2];
            e->unk_02[3] = mac[3];
            e->unk_02[4] = mac[4];
            e->unk_02[5] = mac[5];
            e->chan = chan;
            e->owner = m;
            e->idx = 0;
            for (k = 0; k < 6; k++) {
                e->hist[k] = lvl;
            }
            e->avg = lvl;
            MIi_CpuCopyFast(payload, e->payload, 0xc0);
            DC_StoreRange(e->payload, 0xc0);
            OS_RestoreInterrupts(en);
            OS_CancelAlarm(&m->alarms[i]);
            OS_SetAlarm(&m->alarms[i], (s64) ((s32) (interval * 33514) / 64), func_ov066_0226a43c, &m->entries[i]);
            OS_SetAlarmTag(&m->alarms[i], (u32) (m->tag + 0x80));
            if (m->cb != 0) {
                m->cb(&m->entries[i]);
            }
            return 1;
        }
    }
    return 0;
}
