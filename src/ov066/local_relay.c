/* local_relay: 25 functions, module ov066
 * mwccarm 1.2/base -O4,p
 * func_ov066_0226b8bc @ 0x0226b8bc, 0x50 bytes, ARM
 * func_ov066_0226b81c @ 0x0226b81c, 0xa0 bytes, ARM
 * func_ov066_0226b818 @ 0x0226b818, 0x4 bytes, ARM
 * func_ov066_0226b7ac @ 0x0226b7ac, 0x6c bytes, ARM
 * func_ov066_0226b738 @ 0x0226b738, 0x74 bytes, ARM
 * func_ov066_0226b71c @ 0x0226b71c, 0x1c bytes, ARM
 * func_ov066_0226b5c4 @ 0x0226b5c4, 0x158 bytes, ARM
 * func_ov066_0226b594 @ 0x0226b594, 0x30 bytes, ARM
 * func_ov066_0226b3d0 @ 0x0226b3d0, 0x1c4 bytes, ARM
 * func_ov066_0226b27c @ 0x0226b27c, 0x154 bytes, ARM
 * func_ov066_0226b1d0 @ 0x0226b1d0, 0xac bytes, ARM
 * func_ov066_0226b088 @ 0x0226b088, 0x148 bytes, ARM
 * func_ov066_0226af3c @ 0x0226af3c, 0x14c bytes, ARM
 * func_ov066_0226af04 @ 0x0226af04, 0x38 bytes, ARM
 * func_ov066_0226aeb8 @ 0x0226aeb8, 0x4c bytes, ARM
 * func_ov066_0226ae50 @ 0x0226ae50, 0x68 bytes, ARM
 * func_ov066_0226ae1c @ 0x0226ae1c, 0x34 bytes, ARM
 * func_ov066_0226adcc @ 0x0226adcc, 0x50 bytes, ARM
 * func_ov066_0226ad9c @ 0x0226ad9c, 0x30 bytes, ARM
 * func_ov066_0226ac68 @ 0x0226ac68, 0x134 bytes, ARM
 * func_ov066_0226ab28 @ 0x0226ab28, 0x140 bytes, ARM
 * func_ov066_0226ab24 @ 0x0226ab24, 0x4 bytes, ARM
 * func_ov066_0226aab8 @ 0x0226aab8, 0x6c bytes, ARM
 * func_ov066_0226a960 @ 0x0226a960, 0x158 bytes, ARM
 * func_ov066_0226a8c4 @ 0x0226a8c4, 0x9c bytes, ARM
 */

#include "types.h"

typedef struct UnkStruct_0226b8bc {
    unsigned char pad_00[4];
    unsigned char b0 : 3;
    unsigned char b3 : 1;
    unsigned char b4 : 4;
} UnkStruct_0226b8bc;

typedef struct UnkStruct_0226b8bc_2 {
    unsigned char pad_00[4];
    unsigned long unk_04;
} UnkStruct_0226b8bc_2;

typedef struct {
    unsigned char pad_00[4];
    unsigned char unk_04;
    unsigned char pad_05[0x1e - 0x05];
    unsigned short unk_1E;
    unsigned int unk_20;
    unsigned int unk_24;
    unsigned int unk_28;
    unsigned int unk_2C;
} UnkStruct_0226b81c;

typedef struct UnkStruct_0226b7ac UnkStruct_0226b7ac;

struct UnkStruct_0226b7ac {
    unsigned char pad_00[4];
    unsigned char unk_04;
    unsigned char pad_05[25];
    short unk_1E;
    int unk_20;
    int unk_24;
    int unk_28;
    void (*unk_2C)(void *);
};

typedef struct UnkStruct_0226b738_2 {
    u8 kind : 2;  // 0x00 bits 0..1
    u8 armed : 1; // bit 2
    u8 rest : 5;
} UnkStruct_0226b738_2;

typedef struct UnkStruct_0226b738 {
    unsigned char pad_00[0x14];
    UnkStruct_0226b738_2 *item; // 0x14
} UnkStruct_0226b738;

typedef struct Ctl {
    unsigned char pad_00[2];
    signed char count; // 0x02
} Ctl;

struct UnkStruct_0226b71c {
    char pad_00[2];
    signed char unk_02;
};

typedef struct Pkt {
    u8 kind : 2;
    u8 done : 1;
    u8 rest : 5;
    u8 unk_01;
    u16 unk_02;
    u16 unk_04;
    u16 unk_06;
    u8 data[4];
} Pkt;

typedef struct Ctl_0226b5c4 {
    u8 unk_00;
    char pad_01[3];
    u8 a : 1;
    u8 b : 1;
    u8 c : 1;
    u8 d : 1;
    u8 v : 1;
    u8 e : 3;
    char pad_05[0x1e - 5];
    u16 unk_1E;
    u8 *unk_20;
    u32 unk_24;
    u32 unk_28;
} Ctl_0226b5c4;

struct UnkStruct_0226b594 {
    char pad_00[0x24];
    union {
        unsigned char byte;
        struct {
            unsigned char b0 : 1;
            unsigned char b1 : 1;
            unsigned char b2 : 1;
        } bits;
    } u;
};

typedef union Attr {
    u8 raw;
    struct {
        u8 mode : 2;
        u8 f2 : 1;
        u8 f3 : 1;
        u8 idx : 4;
    };
} Attr;

typedef struct Node {
    struct Node *prev;
    struct Node *next;
    u8 pad[0x18];
    Attr attr;
} Node;

typedef struct Queue {
    Node *head;
    Node *tail;
} Queue;

typedef struct UnkStruct_0226b3d0 {
    u8 unk_00;
    struct {
        u8 lo : 4;
        u8 hi : 4;
    } unk_01;
    s8 unk_02;
    s8 unk_03;
    struct {
        u8 x0 : 1;
        u8 x1 : 1;
        u8 x2 : 1;
        u8 x3 : 1;
        u8 x4 : 1;
        u8 x5 : 1;
        u8 x6 : 1;
        u8 x7 : 1;
    } unk_04;
    u8 pad[0xb];
    Node *cur;
    u8 pad_14[4];
    Queue *q;
} UnkStruct_0226b3d0;

typedef struct Entry {
    u32 unk_00;
    u32 unk_04;
    u32 unk_08;
    u32 unk_0C;
} Entry;

typedef struct UnkStruct_0226b27c {
    u8 unk_00;
    u8 pad[0x1b];
    u16 flags;
    u8 pad_1E[0x12];
    Entry *entries;
} UnkStruct_0226b27c;

typedef struct UnkStruct_0226b27c_2 {
    u8 pad[0xb8];
    void (*cb)(int idx, char *buffer, u32 length);
} UnkStruct_0226b27c_2;

typedef struct {
    unsigned char pad[0xb];
    unsigned char count;
} UnkStruct_0226b1d0;

typedef struct {
    unsigned char unk_00;
    unsigned char pad[2];
    signed char slot3;
} UnkStruct_0226b1d0_2;

typedef struct {
    unsigned short unk_00;
    unsigned short flags;
} UnkStruct_0226b1d0_3;

typedef struct UnkStruct_0226b088 {
    struct UnkStruct_0226b088 **unk_00;
    struct UnkStruct_0226b088 *unk_04;
    u16 unk_08;
    u16 unk_0A;
    u16 unk_0C;
    char pad0[0x20 - 0xe];
    u8 unk_20;
    char pad_21[1];
    u16 unk_22;
    char data[4];
} UnkStruct_0226b088;

typedef struct Ctl_0226b088 {
    u8 unk_00;
    u8 lo : 4;
    u8 hi : 4;
    char pad0[0x18 - 2];
    UnkStruct_0226b088 **list; // 0x18
} Ctl_0226b088;

typedef struct Cfg {
    char pad0[0xb];
    u8 cnt; // 0x0b
} Cfg;

typedef struct Timer {
    char pad0[0x98];
    u16 unk_98;
} Timer;

typedef struct UnkStruct_0226af3c {
    struct UnkStruct_0226af3c **unk_00;
    struct UnkStruct_0226af3c *unk_04;
    u16 unk_08;
    u16 unk_0A;
    u16 unk_0C;
    char pad0[0x20 - 0xe];
    char data[4];
} UnkStruct_0226af3c;

typedef struct Node_0226af3c {
    char pad0[0x22];
    u16 unk_22;
} Node_0226af3c;

typedef struct Ctl_0226af3c {
    char pad0[2];
    signed char count;  // 0x02
    signed char unk_03; // 0x03
    u8 x : 1;           // 0x04 bit 0
    u8 y : 1;
    u8 z : 1;
    u8 w : 1; // bit 3
    u8 rest : 4;
    char pad_05[0x10 - 5];
    UnkStruct_0226af3c *unk_10; // 0x10
    UnkStruct_0226af3c *unk_14; // 0x14
    Node_0226af3c **list;                // 0x18
} Ctl_0226af3c;

typedef struct Node_0226aeb8 {
    struct Node_0226aeb8 *next;
    unsigned char pad[6];
    unsigned short flags1;
    unsigned short flags2;
} Node_0226aeb8;

typedef struct ListObj {
    unsigned char pad[0x10];
    Node_0226aeb8 *head;
} ListObj;

typedef struct {
    char pad_00[2];
    unsigned short flag;
    char pad_04[0x1c];
    void (*callback)(void *self);
} UnkStruct_0226adcc;

struct Node_0226ad9c {
    struct Node_0226ad9c *next;
    unsigned char pad_04[0x1c];
    unsigned char flag;
};

typedef struct {
    u8 k : 2;
    u8 b2 : 1;
    u8 b3 : 1;
    u8 idx : 4;
    u8 unk_01;
} Hdr;

typedef struct Node_0226ac68 {
    char pad0[4];
    struct Node_0226ac68 *unk_04;
    char pad_08[0x22 - 8];
    u16 unk_22;
    char data[2];
} Node_0226ac68;

typedef struct UnkStruct_0226ac68 {
    char pad0[0xa];
    u16 unk_0A;
    u16 unk_0C;
} UnkStruct_0226ac68;

typedef struct Ctl_0226ac68 {
    u8 unk_00;
    char pad0[0x10 - 1];
    int unk_10;
    UnkStruct_0226ac68 *unk_14;
    Node_0226ac68 **list;
} Ctl_0226ac68;

typedef struct Node_0226ab28 {
    char pad0[4];
    struct Node_0226ab28 *next; // 0x04
    char pad_08[0x20 - 8];
    u8 unk_20; // 0x20
} Node_0226ab28;

typedef struct Ctl_0226ab28 {
    u8 unk_00;
    u8 lo : 4;         // 0x01 bits 0..3
    u8 hi : 4;         // 0x01 bits 4..7
    signed char count; // 0x02
    u8 unk_03;
    u8 x : 1; // 0x04 bit 0
    u8 y : 1; // bit 1
    u8 z : 1; // bit 2
    u8 rest : 5;
    char pad0[0x18 - 5];
    Node_0226ab28 **list; // 0x18
} Ctl_0226ab28;

typedef struct UnkStruct_0226ab28 {
    char pad0[0xc];
    u8 *item; // 0x0c
    u16 unk_10;
    u16 unk_12;
} UnkStruct_0226ab28;

typedef struct UnkStruct_0226aab8 {
    unsigned short unk_00;
    unsigned short unk_02;
    unsigned short unk_04;
} UnkStruct_0226aab8;

typedef struct UnkStruct_0226a960 {
    u8 pad_00;
    u8 flag1;
    u8 flag2;
    u8 flag3;
    u8 flag4;
    u8 pad_05[3];
    u32 unk_08;
    u32 unk_0C;
    u32 unk_10;
    u32 unk_14;
    u32 *unk_18;
    u16 unk_1C;
    u16 unk_1E;
    u32 unk_20;
    u32 unk_24;
    u32 unk_28;
    u32 unk_2C;
} UnkStruct_0226a960;

typedef struct Count {
    u8 pad_00[0xb];
    u8 count;
} Count;

typedef struct UnkStruct_0226a8c4_2 {
    void *a;
    void *b;
    unsigned char pad_08[8];
} UnkStruct_0226a8c4_2;

typedef struct UnkStruct_0226a8c4 {
    unsigned char pad_00[0x1c];
    u16 mask; // 0x1c
    unsigned char pad_1E[0x30 - 0x1e];
    UnkStruct_0226a8c4_2 *tbl; // 0x30
} UnkStruct_0226a8c4;

typedef struct Lim {
    unsigned char pad_00[0xb];
    u8 count; // 0x0b
} Lim;

extern UnkStruct_0226b8bc *data_ov066_0226be08;
extern UnkStruct_0226b8bc_2 *data_ov066_0226bdec;
extern void MI_CpuCopy8(const void *src, void *dst, unsigned int len);
extern UnkStruct_0226b27c_2 *data_ov066_0226bdf4;
extern int func_ov066_022699cc(void);
extern void func_ov066_0226686c(int argument0);
extern int WM_SetMPDataToPortEx(void (*func)(void *), int e, int b, int c, int d, int a, int two);
extern void OS_Terminate(void);
extern int func_ov066_02266e08(void);
extern int OS_DisableInterrupts(void);
extern void func_ov066_0226bb7c(int value, int n);
extern unsigned int OS_RestoreInterrupts(int value);

int func_ov066_0226ae50(int a, int b, int c, int d, int e);
void func_ov066_0226adcc(UnkStruct_0226adcc *obj);

int func_ov066_0226b8bc(void)
{
    int result = 0;
    UnkStruct_0226b8bc *q = data_ov066_0226be08;
    if (q != 0) {
        unsigned long st = data_ov066_0226bdec->unk_04;
        if (st != 10) {
            if (st != 11) {
                return result;
            }
        }
        if (!q->b3) {
            result = 1;
        } else {
            result = 0;
        }
    }
    return result;
}

int func_ov066_0226b81c(int a, int b, int c, int d)
{
    int flag = 0;
    unsigned int handle = (unsigned int) OS_DisableInterrupts();
    if (func_ov066_0226b8bc() != 0) {
        int zero = flag;
        flag = 1;
        (*(UnkStruct_0226b81c * *) &data_ov066_0226be08)->unk_04 |= 8;
        (*(UnkStruct_0226b81c * *) &data_ov066_0226be08)->unk_04 &= ~0x10;
        (*(UnkStruct_0226b81c * *) &data_ov066_0226be08)->unk_20 = a;
        (*(UnkStruct_0226b81c * *) &data_ov066_0226be08)->unk_24 = b;
        (*(UnkStruct_0226b81c * *) &data_ov066_0226be08)->unk_28 = zero;
        (*(UnkStruct_0226b81c * *) &data_ov066_0226be08)->unk_1E = (unsigned short) c;
        (*(UnkStruct_0226b81c * *) &data_ov066_0226be08)->unk_2C = d;
    }
    OS_RestoreInterrupts(handle);
    return flag;
}

void func_ov066_0226b818(void) {}

void func_ov066_0226b7ac(void)
{
    unsigned char f4 = (*(UnkStruct_0226b7ac * *) &data_ov066_0226be08)->unk_04;
    void (*cb)(void *) = (*(UnkStruct_0226b7ac * *) &data_ov066_0226be08)->unk_2C;
    int arg = (*(UnkStruct_0226b7ac * *) &data_ov066_0226be08)->unk_24;
    f4 &= ~8;
    (*(UnkStruct_0226b7ac * *) &data_ov066_0226be08)->unk_04 = f4;
    (*(UnkStruct_0226b7ac * *) &data_ov066_0226be08)->unk_1E = 0;
    (*(UnkStruct_0226b7ac * *) &data_ov066_0226be08)->unk_20 = 0;
    (*(UnkStruct_0226b7ac * *) &data_ov066_0226be08)->unk_24 = 0;
    (*(UnkStruct_0226b7ac * *) &data_ov066_0226be08)->unk_28 = -1;
    (*(UnkStruct_0226b7ac * *) &data_ov066_0226be08)->unk_2C = 0;
    if (cb) {
        cb((void *) arg);
    }
}

void func_ov066_0226b738(UnkStruct_0226b738 *q)
{
    UnkStruct_0226b738_2 *it = q->item;
    (*(Ctl * *) &data_ov066_0226be08)->count--;
    switch (it->kind) {
        case 0:
        case 1:
            if (it->armed) {
                it->armed = 0;
                func_ov066_0226b7ac();
            }
            break;
    }
}

void func_ov066_0226b71c(void)
{
    (*(struct UnkStruct_0226b71c * *) &data_ov066_0226be08)->unk_02--;
}

u16 func_ov066_0226b5c4(Pkt *hdr)
{
    Ctl_0226b5c4 *g;
    u32 sent;
    u32 total;
    u32 rem;
    u8 *src;
    u8 *dst;
    u32 lim;
    u32 v;
    u8 n;
    u16 ret;

    g = (*(Ctl_0226b5c4 * *) &data_ov066_0226be08);
    sent = g->unk_28;
    total = g->unk_24;
    rem = total - sent;
    src = g->unk_20 + sent;
    if (sent == 0) {
        hdr->kind = 0;
        dst = (u8 *) hdr + 8;
        hdr->unk_02 = (*(Ctl_0226b5c4 * *) &data_ov066_0226be08)->unk_1E;
        hdr->unk_04 = (u16) (*(Ctl_0226b5c4 * *) &data_ov066_0226be08)->unk_24;
        hdr->unk_06 = (u16) ((*(Ctl_0226b5c4 * *) &data_ov066_0226be08)->unk_24 >> 16);
        lim = (*(Ctl_0226b5c4 * *) &data_ov066_0226be08)->unk_00 - 8;
        v = (*(Ctl_0226b5c4 * *) &data_ov066_0226be08)->unk_24;
        if (v > lim) {
            v = lim;
        }
        n = (u8) v;
        ret = (u16) ((n + 9) & ~1);
    } else {
        hdr->kind = 1;
        dst = (u8 *) hdr + 2;
        lim = (*(Ctl_0226b5c4 * *) &data_ov066_0226be08)->unk_00 - 2;
        if (rem > lim) {
            rem = lim;
        }
        n = (u8) rem;
        ret = (u16) ((n + 3) & ~1);
    }
    (*(Ctl_0226b5c4 * *) &data_ov066_0226be08)->unk_28 = (*(Ctl_0226b5c4 * *) &data_ov066_0226be08)->unk_28 + n;
    hdr->unk_01 = n;
    hdr->done = ((*(Ctl_0226b5c4 * *) &data_ov066_0226be08)->unk_28 == (*(Ctl_0226b5c4 * *) &data_ov066_0226be08)->unk_24);
    (*(Ctl_0226b5c4 * *) &data_ov066_0226be08)->v = hdr->done;
    MI_CpuCopy8(src, dst, n);
    return ret;
}

void func_ov066_0226b594(struct UnkStruct_0226b594 *self)
{
    func_ov066_0226b5c4((Pkt *) (&self->u.byte));
    if (!self->u.bits.b2) {
        return;
    }
    func_ov066_0226b7ac();
}

void func_ov066_0226b3d0(void)
{
    UnkStruct_0226b3d0 *p = (*(UnkStruct_0226b3d0 * *) &data_ov066_0226be08);
    Attr *a;
    int r = 0;

    a = &p->cur->attr;

    if (p->unk_04.x2) {
        a->mode = 3;
        r = 2;
        a->idx = (*(UnkStruct_0226b3d0 * *) &data_ov066_0226be08)->unk_01.hi;
    } else if (p->unk_04.x3) {
        if (p->unk_03 < 2) {
            if (!p->unk_04.x4) {
                if (!p->unk_04.x1) {
                    r = (int) func_ov066_0226b5c4((Pkt *) a);
                    (*(UnkStruct_0226b3d0 * *) &data_ov066_0226be08)->unk_03 = (s8) ((*(UnkStruct_0226b3d0 * *) &data_ov066_0226be08)->unk_03 + 1);
                }
            }
        }
    }

    if ((*(UnkStruct_0226b3d0 * *) &data_ov066_0226be08)->q->head != (*(UnkStruct_0226b3d0 * *) &data_ov066_0226be08)->q->tail) {
        if (r == 0) {
            a->mode = 2;
            r = 2;
            a->f2 = 0;
        }
        a->f3 = 1;
        a->idx = (*(UnkStruct_0226b3d0 * *) &data_ov066_0226be08)->q->tail->attr.raw;
        (*(UnkStruct_0226b3d0 * *) &data_ov066_0226be08)->q->tail = (*(UnkStruct_0226b3d0 * *) &data_ov066_0226be08)->q->tail->next;
    } else {
        a->f3 = 0;
    }

    if (r != 0) {
        (*(UnkStruct_0226b3d0 * *) &data_ov066_0226be08)->unk_02 = (s8) ((*(UnkStruct_0226b3d0 * *) &data_ov066_0226be08)->unk_02 + 1);
        func_ov066_0226ae50(0xd, (int) a, r, 1, (int) ((void (*)(void *)) func_ov066_0226b738));
        (*(UnkStruct_0226b3d0 * *) &data_ov066_0226be08)->cur = (*(UnkStruct_0226b3d0 * *) &data_ov066_0226be08)->cur->next;
    }

    (*(UnkStruct_0226b3d0 * *) &data_ov066_0226be08)->unk_04.x1 = 0;
}

void func_ov066_0226b27c(int idx, u8 *src)
{
    u32 r7 = 0;
    Entry *entry = &(*(UnkStruct_0226b27c * *) &data_ov066_0226be08)->entries[idx];
    Attr *attr = (Attr *) src;
    u8 *r5;
    u32 mask;

    switch (attr->mode) {
        case 0:
            r5 = src + 8;
            if (*(u16 *) (src + 2) & (1 << func_ov066_022699cc())) {
                u16 hi;
                u16 lo;
                (*(UnkStruct_0226b27c * *) &data_ov066_0226be08)->flags |= (1 << idx);
                entry->unk_0C = r7;
                hi = *(u16 *) (src + 6);
                lo = *(u16 *) (src + 4);
                entry->unk_08 = ((u32) hi << 16) | lo;
                r7 = entry->unk_08;
                if (r7 > (u32) ((*(UnkStruct_0226b27c * *) &data_ov066_0226be08)->unk_00 - 8)) {
                    r7 = (u32) ((*(UnkStruct_0226b27c * *) &data_ov066_0226be08)->unk_00 - 8);
                }
            }
            break;
        case 1:
            r5 = src + 2;
            r7 = src[1];
            break;
    }

    mask = 1 << idx;
    if (((*(UnkStruct_0226b27c * *) &data_ov066_0226be08)->flags & mask) == 0) {
        return;
    }

    if (entry->unk_0C + r7 <= entry->unk_04) {
        MI_CpuCopy8((const void *) r5, (void *) (entry->unk_00 + entry->unk_0C), r7);
        entry->unk_0C += r7;
    }

    if (entry->unk_08 != entry->unk_0C) {
        return;
    }

    (*(UnkStruct_0226b27c * *) &data_ov066_0226be08)->flags ^= mask;
    if (data_ov066_0226bdf4->cb != 0) {
        data_ov066_0226bdf4->cb(idx, (char *) entry->unk_00, entry->unk_08);
    }
}

void func_ov066_0226b1d0(UnkStruct_0226b1d0_3 *self)
{
    unsigned short i;
    unsigned char *p = (unsigned char *) self + 4;

    for (i = 0; i < (*(UnkStruct_0226b1d0 * *) &data_ov066_0226bdec)->count; i++) {
        if (self->flags & (1 << i)) {
            if (i == func_ov066_022699cc()) {
                (*(UnkStruct_0226b1d0_2 * *) &data_ov066_0226be08)->slot3--;
            }
            func_ov066_0226b27c(i, (u8 *) p);
            p += (*(UnkStruct_0226b1d0_2 * *) &data_ov066_0226be08)->unk_00 & ~1;
        }
    }
}

int func_ov066_0226b088(UnkStruct_0226b088 *e, UnkStruct_0226b088 *n)
{
    Ctl_0226b088 *g;
    u16 mask;
    u16 i;
    u8 stride;
    u16 total;
    u8 *src;
    u8 *dst;
    u8 old;
    int ret;

    ret = 0;
    mask = n->unk_22;
    if (mask != 0) {
        g = (*(Ctl_0226b088 * *) &data_ov066_0226be08);
        src = (u8 *) n + 0x24;
        total = 4;
        stride = g->unk_00;
        dst = (u8 *) e + 0x24;
        e->unk_22 = mask;

        old = (*(Ctl_0226b088 * *) &data_ov066_0226be08)->lo;
        (*(Ctl_0226b088 * *) &data_ov066_0226be08)->lo = old + 1;
        e->unk_20 = old;

        for (i = 0; i < (*(Cfg * *) &data_ov066_0226bdec)->cnt; i++) {
            if (mask & (1 << i)) {
                MI_CpuCopy8(src + stride * i, dst, stride);
                dst += stride;
                total = total + stride;
            }
            g = (*(Ctl_0226b088 * *) &data_ov066_0226be08);
            if (g->list[i] == n) {
                g->list[i] = n->unk_04;
            }
        }

        n->unk_22 = 0;
        e->unk_0A = (*(Timer * *) &data_ov066_0226bdf4)->unk_98;
        e->unk_0C = 0;
        e->unk_08 = total;
        func_ov066_0226b1d0((UnkStruct_0226b1d0_3 *) ((u8 *) e + 0x20));
        ret = 1;
    }
    return ret;
}

void func_ov066_0226af3c(void)
{
    Ctl_0226af3c *g;
    UnkStruct_0226af3c *cur;
    Node_0226af3c *nd;
    UnkStruct_0226af3c *e;

    g = (*(Ctl_0226af3c * *) &data_ov066_0226be08);
    if (g->count >= 1) {
        return;
    }
    cur = 0;
    nd = g->list[0];
    if (g->unk_14 != 0) {
        cur = g->unk_14;
        if (cur->unk_04 == g->unk_10) {
            g->unk_14 = 0;
        } else {
            g->unk_14 = cur->unk_04;
        }
    } else {
        e = *g->unk_10->unk_00;
        if (e->unk_0A == 0 || e->unk_0A == e->unk_0C) {
            if (g->w) {
                func_ov066_0226b594((struct UnkStruct_0226b594 *) nd);
                nd->unk_22 |= 1;
                (*(Ctl_0226af3c * *) &data_ov066_0226be08)->unk_03++;
            }
            if (func_ov066_0226b088((UnkStruct_0226b088 *) ((*(Ctl_0226af3c * *) &data_ov066_0226be08)->unk_10), (UnkStruct_0226b088 *) nd) != 0) {
                cur = (*(Ctl_0226af3c * *) &data_ov066_0226be08)->unk_10;
                (*(Ctl_0226af3c * *) &data_ov066_0226be08)->unk_10 = cur->unk_04;
            }
        }
    }
    if (cur == 0) {
        return;
    }
    if (cur->unk_0A == 0) {
        return;
    }
    (*(Ctl_0226af3c * *) &data_ov066_0226be08)->count++;
    func_ov066_0226ae50(0xd, (int) ((u8 *) cur + 0x20), cur->unk_08, cur->unk_0A, (int) ((void *) func_ov066_0226b71c));
}

void func_ov066_0226af04(void)
{
    if (*(signed char *) (*(int *) ((int *) &data_ov066_0226be08) + 2) >= 2) {
        return;
    }
    func_ov066_0226b3d0();
}

void func_ov066_0226aeb8(int bit)
{
    Node_0226aeb8 *head;
    Node_0226aeb8 *cur;
    unsigned short mask;

    mask = ~(1 << bit);
    head = (*(ListObj * *) &data_ov066_0226be08)->head;
    cur = head;
    do {
        cur->flags1 &= mask;
        cur->flags2 &= mask;
        cur = cur->next;
    } while (head != cur);
}

int func_ov066_0226ae50(int a, int b, int c, int d, int e)
{
    int result = WM_SetMPDataToPortEx((void (*)(void *)) func_ov066_0226adcc, e, b, c, d, a, 2);
    if (result != 2 && result != 7) {
        func_ov066_0226686c(result);
        return 0;
    }
    return 1;
}

void func_ov066_0226ae1c(int a1, int a2, int a3, int a4)
{
    func_ov066_0226ae50(0xc, a1, a2, a3, a4);
}

void func_ov066_0226adcc(UnkStruct_0226adcc *obj)
{
    if (obj->flag == 0) {
        if (obj->callback != 0) {
            obj->callback(obj);
        }
        return;
    } else {
        func_ov066_0226686c(obj->flag);
        OS_Terminate();
    }
}

struct Node_0226ad9c *func_ov066_0226ad9c(unsigned char key, struct Node_0226ad9c *sentinel)
{
    struct Node_0226ad9c *p;
    p = sentinel->next;
    if (sentinel != p) {
        do {
            if (p->flag == key) {
                return p;
            }
            p = p->next;
        } while (sentinel != p);
    }
    return 0;
}

void func_ov066_0226ac68(int a, u8 *b, int c)
{
    Hdr h;
    UnkStruct_0226ac68 *e;
    Node_0226ac68 *nd;

    MI_CpuCopy8(b, &h, 2);
    if (h.b3) {
        e = (UnkStruct_0226ac68 *) func_ov066_0226ad9c(h.idx, (struct Node_0226ad9c *) ((*(Ctl_0226ac68 * *) &data_ov066_0226be08)->unk_10));
        if (e != 0) {
            e->unk_0C |= e->unk_0A & (1 << a);
        }
    }
    if (h.k == 3) {
        if ((*(Ctl_0226ac68 * *) &data_ov066_0226be08)->unk_14 != 0) {
            return;
        }
        e = (UnkStruct_0226ac68 *) func_ov066_0226ad9c(h.idx, (struct Node_0226ad9c *) ((*(Ctl_0226ac68 * *) &data_ov066_0226be08)->unk_10));
        if (e != 0) {
            (*(Ctl_0226ac68 * *) &data_ov066_0226be08)->unk_14 = e;
        }
        return;
    }
    if (h.k == 2) {
        return;
    }
    nd = (*(Ctl_0226ac68 * *) &data_ov066_0226be08)->list[a];
    MI_CpuCopy8(b, (u8 *) nd + 0x24 + a * (*(Ctl_0226ac68 * *) &data_ov066_0226be08)->unk_00, c);
    nd->unk_22 |= 1 << a;
    (*(Ctl_0226ac68 * *) &data_ov066_0226be08)->list[a] = nd->unk_04;
}

void func_ov066_0226ab28(UnkStruct_0226ab28 *q)
{
    u8 *p;
    Node_0226ab28 *n;

    if (q->unk_10 == 0) {
        return;
    }
    if (q->unk_12 != 0) {
        func_ov066_0226ac68(q->unk_12, q->item, q->unk_10);
        return;
    }
    p = q->item;
    if ((*(Ctl_0226ab28 * *) &data_ov066_0226be08)->x || *p == (((*(Ctl_0226ab28 * *) &data_ov066_0226be08)->lo + 1) & 0xf)) {
        n = *(*(Ctl_0226ab28 * *) &data_ov066_0226be08)->list;
        n->unk_20 = *p;
        *(*(Ctl_0226ab28 * *) &data_ov066_0226be08)->list = n->next;
        func_ov066_0226b1d0((UnkStruct_0226b1d0_3 *) p);
        (*(Ctl_0226ab28 * *) &data_ov066_0226be08)->x = 0;
        (*(Ctl_0226ab28 * *) &data_ov066_0226be08)->z = 0;
        (*(Ctl_0226ab28 * *) &data_ov066_0226be08)->lo = *p;
        return;
    }
    if (*p != (((*(Ctl_0226ab28 * *) &data_ov066_0226be08)->lo + 2) & 0xf)) {
        (*(Ctl_0226ab28 * *) &data_ov066_0226be08)->y = 1;
        return;
    }
    (*(Ctl_0226ab28 * *) &data_ov066_0226be08)->z = 1;
    (*(Ctl_0226ab28 * *) &data_ov066_0226be08)->hi = ((*(Ctl_0226ab28 * *) &data_ov066_0226be08)->lo + 1) & 0xf;
}

void func_ov066_0226ab24(void *receiver) {}

void func_ov066_0226aab8(UnkStruct_0226aab8 *p)
{
    if (func_ov066_02266e08()) {
        return;
    }
    if (p->unk_02 != 0) {
        return;
    }
    if (p->unk_04 == 7) {
        return;
    }
    if (p->unk_04 != 9) {
        if (p->unk_04 != 0x15) {
            return;
        }
        func_ov066_0226ab28((UnkStruct_0226ab28 *) p);
        return;
    }
    func_ov066_0226ab24((void *) p);
}

unsigned int func_ov066_0226a960(void)
{
    int saved;
    u16 i;

    saved = OS_DisableInterrupts();

    (*(UnkStruct_0226a960 * *) &data_ov066_0226be08)->unk_10 = (*(UnkStruct_0226a960 * *) &data_ov066_0226be08)->unk_08;
    func_ov066_0226bb7c((*(UnkStruct_0226a960 * *) &data_ov066_0226be08)->unk_08, 3);
    func_ov066_0226bb7c((*(UnkStruct_0226a960 * *) &data_ov066_0226be08)->unk_0C, 3);

    i = 0;
    while (i < (*(Count * *) &data_ov066_0226bdec)->count) {
        (*(UnkStruct_0226a960 * *) &data_ov066_0226be08)->unk_18[i] = (*(UnkStruct_0226a960 * *) &data_ov066_0226be08)->unk_0C;
        i++;
    }

    (*(UnkStruct_0226a960 * *) &data_ov066_0226be08)->flag1 &= ~0xf;
    (*(UnkStruct_0226a960 * *) &data_ov066_0226be08)->flag1 &= ~0xf0;
    (*(UnkStruct_0226a960 * *) &data_ov066_0226be08)->flag2 = 0;
    (*(UnkStruct_0226a960 * *) &data_ov066_0226be08)->flag3 = 0;
    (*(UnkStruct_0226a960 * *) &data_ov066_0226be08)->flag4 = ((*(UnkStruct_0226a960 * *) &data_ov066_0226be08)->flag4 & ~1) | 1;
    (*(UnkStruct_0226a960 * *) &data_ov066_0226be08)->flag4 &= ~2;
    (*(UnkStruct_0226a960 * *) &data_ov066_0226be08)->flag4 &= ~4;
    (*(UnkStruct_0226a960 * *) &data_ov066_0226be08)->flag4 &= ~8;
    (*(UnkStruct_0226a960 * *) &data_ov066_0226be08)->unk_14 = 0;
    (*(UnkStruct_0226a960 * *) &data_ov066_0226be08)->unk_1C = 0;
    (*(UnkStruct_0226a960 * *) &data_ov066_0226be08)->unk_1E = 0;
    (*(UnkStruct_0226a960 * *) &data_ov066_0226be08)->unk_20 = 0;
    (*(UnkStruct_0226a960 * *) &data_ov066_0226be08)->unk_24 = 0;
    (*(UnkStruct_0226a960 * *) &data_ov066_0226be08)->unk_28 = -1;
    (*(UnkStruct_0226a960 * *) &data_ov066_0226be08)->unk_2C = 0;

    return OS_RestoreInterrupts(saved);
}

int func_ov066_0226a8c4(int idx, void *a, void *b)
{
    int ok = 0;
    int e = OS_DisableInterrupts();
    UnkStruct_0226a8c4 *q = (*(UnkStruct_0226a8c4 * *) &data_ov066_0226be08);
    if (q != 0) {
        UnkStruct_0226a8c4_2 *tbl = q->tbl;
        if (tbl != 0 && (*(void * *) &data_ov066_0226bdf4) != 0 && idx < (*(Lim * *) &data_ov066_0226bdec)->count && (q->mask & (1 << idx)) == 0) {
            tbl[idx].a = a;
            tbl[idx].b = b;
            ok = 1;
        }
    }
    OS_RestoreInterrupts(e);
    return ok;
}
