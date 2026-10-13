/* func_ov066_02267958 @ 0x02267958, 0x200 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

#include "types.h"

typedef struct Msg {
    u16 id;
    u8 body[6];
} Msg;

typedef struct Link {
    u8 pad_00[0x3c];
    u16 state;
    u8 pad_3E[0x4b - 0x3e];
    u8 flags;
    u8 pad_4C[0x50 - 0x4c];
    u8 data[8];
} Link;

typedef struct UnkStruct_02267958 {
    u8 pad_00[4];
    Link *link;
    void *objs;
    int f0 : 1;
    int pad0c : 31;
    u8 pad_10[0x3c - 0x10];
    int queue;
} UnkStruct_02267958;

typedef struct Flags {
    u8 pad_00[0x3c];
    int pad3c : 3;
    int f3 : 1;
    int f4 : 1;
    int pad3c2 : 27;
} Flags;

typedef struct UnkStruct_02267958_2 {
    u8 pad_00[0x95];
    u8 index;
} UnkStruct_02267958_2;

typedef struct Peer {
    u8 pad_00[0xa];
    u8 name[8];
    u16 tag;
} Peer;

extern UnkStruct_02267958 *data_ov066_0226bdf0;
extern Flags *data_ov066_0226bdec;
extern UnkStruct_02267958_2 *data_ov066_0226bdf4;

extern void DC_InvalidateRange(void *p, int n);
extern void MI_CpuCopy8(const void *src, void *dest, u32 size);
extern void DC_StoreRange(void *p, int n);
extern void OS_CancelAlarm(void *q);
extern void OS_SetAlarm(void *q, int a, int b, void (*cb)(void), int e);
extern int func_ov066_0226783c(Peer *p, Msg *m);
extern void func_ov066_02267908(void);
extern void func_ov066_0226794c(void);
extern void func_ov066_0226a494(void *obj, int a, void *name, int tag, int id, void *link);

void func_ov066_02267958(Peer *peer)
{
    Msg msg;

    DC_InvalidateRange(data_ov066_0226bdf0->link, 0xc0);

    if (data_ov066_0226bdf0->link->state == 0) {
        if (data_ov066_0226bdec->f4) {
            return;
        }
        func_ov066_0226a494((char *) data_ov066_0226bdf0->objs + data_ov066_0226bdf4->index * 16, 0xfa0, peer->name, 0xacce,
                            peer->tag, data_ov066_0226bdf0->link);
        return;
    }

    if ((data_ov066_0226bdf0->link->flags & 1) == 0) {
        return;
    }

    MI_CpuCopy8(data_ov066_0226bdf0->link->data, &msg, 8);
    DC_StoreRange(&msg, 8);

    if (!func_ov066_0226783c(peer, &msg)) {
        return;
    }

    func_ov066_0226a494((char *) data_ov066_0226bdf0->objs + data_ov066_0226bdf4->index * 16, 0xfa0, peer->name, msg.id,
                        peer->tag, data_ov066_0226bdf0->link);

    if (!data_ov066_0226bdec->f3) {
        return;
    }
    // msg.id is read again from the stack for each compare.
    if (*(volatile u16 *) &msg == 0xbd8a) {
        func_ov066_02267908();
        return;
    }
    if (*(volatile u16 *) &msg != 0x2348) {
        return;
    }
    if (data_ov066_0226bdf0->f0) {
        return;
    }
    OS_CancelAlarm(&data_ov066_0226bdf0->queue);
    OS_SetAlarm(&data_ov066_0226bdf0->queue, 0x3d5d, 0, func_ov066_0226794c, 0);
    data_ov066_0226bdf0->f0 = 1;
}
