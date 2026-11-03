/* local_search_4: 9 functions, module ov066
 * mwccarm 1.2/base -O4,p
 * func_ov066_0226a810 @ 0x0226a810, 0xb4 bytes, ARM
 * func_ov066_0226a7d8 @ 0x0226a7d8, 0x38 bytes, ARM
 * func_ov066_0226a494 @ 0x0226a494, 0x344 bytes, ARM
 * func_ov066_0226a43c @ 0x0226a43c, 0x58 bytes, ARM
 * func_ov066_0226a434 @ 0x0226a434, 0x8 bytes, ARM
 * func_ov066_0226a418 @ 0x0226a418, 0x1c bytes, ARM
 * func_ov066_0226a404 @ 0x0226a404, 0x14 bytes, ARM
 * func_ov066_0226a3b0 @ 0x0226a3b0, 0x54 bytes, ARM
 * func_ov066_0226a2e8 @ 0x0226a2e8, 0xc8 bytes, ARM
 */

#include "types.h"

typedef struct UnkStruct_0226a810 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 pad_03;
    void *unk_04;
    void *unk_08;
    u32 unk_0C;
} UnkStruct_0226a810;

struct func_ov066_0226a7d8_arg {
    unsigned char unk_00;
    unsigned char unk_01;
    unsigned char unk_02;
    int unk_04;
    int unk_08;
};

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

struct UnkStruct_0226a43c;

typedef struct UnkStruct_0226a43c_2 {
    unsigned char pad_00;
    unsigned char unk_01;
    unsigned char pad_02[10];
    void (*unk_0C)(struct UnkStruct_0226a43c *);
} UnkStruct_0226a43c_2;

typedef struct UnkStruct_0226a43c {
    unsigned short unk_00;
    unsigned char pad_02[0x12];
    UnkStruct_0226a43c_2 *unk_14;
} UnkStruct_0226a43c;

typedef struct {
    unsigned char pad_00[1];
    unsigned char unk_01;
} UnkStruct_0226a434;

struct func_ov066_0226a418_s {
    unsigned char pad_00[2];
    unsigned char count;
    unsigned int unk_04;
};

typedef struct UnkStruct_0226a3b0 {
    u8 pad_00;
    u8 unk_01;
    volatile u8 unk_02; // page count; volatile on purpose
    u8 pad_03;
    void *unk_04; // page buffer
} UnkStruct_0226a3b0;

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

extern void *func_ov066_02266908(u32 size, u32 type);
extern void MIi_CpuClearFast(u32 data, void *dest, u32 size);
extern void DC_StoreRange(void *dest, u32 size);
extern void OS_CreateAlarm(void *ptr);
extern void func_ov066_022668c4(int);
extern void OS_CancelAlarms(int);
extern int func_ov066_022683b4(const u8 *a, const u8 *b);
extern void OS_CancelAlarm(OSAlarm *a);
extern u32 OS_DisableInterrupts(void);
extern unsigned int OS_RestoreInterrupts(u32 s);
extern void MIi_CpuCopyFast(const void *src, void *dst, u32 n);
extern void OS_SetAlarm(OSAlarm *a, s64 tick, OSAlarmHandler h, void *arg);
extern void OS_SetAlarmTag(OSAlarm *a, u32 tag);

void func_ov066_0226a43c(UnkStruct_0226a43c *p);

void func_ov066_0226a810(UnkStruct_0226a810 *self, u8 b, int count)
{
    u32 size;
    int i, off;

    size = count * 0xe0;

    self->unk_00 = b;
    self->unk_01 = 0;
    self->unk_02 = (u8) count;
    self->unk_0C = 0;

    self->unk_04 = func_ov066_02266908(size, 0x20);
    self->unk_08 = func_ov066_02266908(count * 0x2c, 0x20);

    {
        volatile u32 d = 0;
        MIi_CpuClearFast(d, self->unk_04, size);
    }
    DC_StoreRange(self->unk_04, size);

    i = 0;
    if (count <= 0) {
        return;
    }
    off = i;
    do {
        OS_CreateAlarm((char *) self->unk_08 + off);
        i++;
        off += 0x2c;
    } while (i < count);
}

void func_ov066_0226a7d8(struct func_ov066_0226a7d8_arg *p)
{
    p->unk_01 = 0;
    p->unk_02 = 0;
    OS_CancelAlarms(p->unk_00 + 0x80);
    func_ov066_022668c4(p->unk_08);
    func_ov066_022668c4(p->unk_04);
}

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
                OS_SetAlarm(&m->alarms[i], (s64) ((s32) (interval * 33514) / 64), (void (*)(void *)) func_ov066_0226a43c, &m->entries[i]);
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
            OS_SetAlarm(&m->alarms[i], (s64) ((s32) (interval * 33514) / 64), (void (*)(void *)) func_ov066_0226a43c, &m->entries[i]);
            OS_SetAlarmTag(&m->alarms[i], (u32) (m->tag + 0x80));
            if (m->cb != 0) {
                m->cb(&m->entries[i]);
            }
            return 1;
        }
    }
    return 0;
}

void func_ov066_0226a43c(UnkStruct_0226a43c *p)
{
    UnkStruct_0226a43c_2 *q = p->unk_14;
    if (p->unk_00 != 1) {
        return;
    }
    q->unk_01--;
    p->unk_00 = 0;
    if (q->unk_0C) {
        q->unk_0C(p);
    }
}

unsigned char func_ov066_0226a434(UnkStruct_0226a434 *p)
{
    return p->unk_01;
}

unsigned int func_ov066_0226a418(struct func_ov066_0226a418_s *self, unsigned int value)
{
    if (value < self->count) {
        return value * 224 + self->unk_04;
    } else {
        return 0;
    }
}

void func_ov066_0226a404(const unsigned char *p)
{
    OS_CancelAlarms(*p + 0x80);
}

static inline void MI_CpuFillFast(void *dest, u32 data, u32 size)
{
    volatile u32 d = data;
    MIi_CpuClearFast(d, dest, size);
}

static inline void MI_CpuClearFast(void *dest, u32 size)
{
    MI_CpuFillFast(dest, 0, size);
}

void func_ov066_0226a3b0(UnkStruct_0226a3b0 *p)
{
    func_ov066_0226a404((const unsigned char *) p);
    p->unk_01 = 0;
    MI_CpuClearFast(p->unk_04, p->unk_02 * 0xe0);
    DC_StoreRange(p->unk_04, p->unk_02 * 0xe0);
}

void func_ov066_0226a2e8(UnkStruct_0226a2e8 *self, int msec)
{
    int i;
    for (i = 0; i < self->count; i++) {
        if (self->slots[i].state == 1) {
            OS_CancelAlarm((OSAlarm *) (&self->alarms[i]));
            OS_SetAlarm((OSAlarm *) (&self->alarms[i]), (u64) ((long long) (msec * 0x82ea / 64)), (OSAlarmHandler) ((void *) (void (*)(void *)) func_ov066_0226a43c), &self->slots[i]);
            OS_SetAlarmTag((OSAlarm *) (&self->alarms[i]), self->unk_00 + 0x80);
        }
    }
}
