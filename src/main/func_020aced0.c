/* func_020aced0 @ 0x020aced0, 0x1f0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_020aced0 {
    int unk_00;
    int unk_04;
    int unk_08;
    u16 unk_0C;
    u16 unk_0E;
    u8 pad_10[4];
    u8 unk_14;
} UnkStruct_020aced0;

typedef struct UnkStruct_020aced0_2 {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    unsigned int unk_14;
    int unk_18;
    int *unk_1C;
    int unk_20;
    int unk_24;
    int *unk_28;
    int *unk_2C;
    UnkStruct_020aced0 *unk_30;
} UnkStruct_020aced0_2;

typedef struct UnkStruct_020aced0_3 {
    int unk_00;
    int pad_04;
    int unk_08;
} UnkStruct_020aced0_3;

typedef struct V3I {
    int a;
    int b;
    int c;
} V3I;

extern int func_020ad2d4(UnkStruct_020aced0_3 *st, int n); // 0x020ad2d4
extern void NNS_G3dGeFlushBuffer(void);                    // 0x01ff8ccc
extern void G3_LoadMtx43(const void *m);                   // 0x02112134
extern int FX_MulFunc(int a, int b);                       // 0x01ffcb0c
extern int func_020310c8(int a);                           // 0x020310c8
extern int func_0203f844(void *a, void *b);                // 0x0203f844
extern int func_02065604(void);                            // 0x02065604

extern int data_020d1e0c; // data_020d1e0c
extern int data_021f47d0; // data_021f47d0

#define REG_A4 (*(volatile u32 *) 0x040004a4)
#define REG_A8 (*(volatile u32 *) 0x040004a8)
#define REG_AC (*(volatile u32 *) 0x040004ac)
#define REG_440 (*(volatile u32 *) 0x04000440)
#define REG_480 (*(volatile u32 *) 0x04000480)
#define REG_488 (*(volatile u32 *) 0x04000488)
#define REG_48C (*(volatile u32 *) 0x0400048c)
#define REG_500 (*(volatile u32 *) 0x04000500)
#define REG_504 (*(volatile u32 *) 0x04000504)
#define REG_448 (*(volatile u32 *) 0x04000448)

extern unsigned char data_021f486c[];

void func_020aced0(UnkStruct_020aced0_2 *p, UnkStruct_020aced0_3 *st)
{
    unsigned int res;
    int *q;
    int *pp;
    int cached;
    unsigned int i;
    int v_lo;
    int v_hi;
    int neg;
    int shift;
    int zx;
    int zy;
    volatile u16 col;
    volatile u16 col2;
    unsigned short p0;
    unsigned short g0;
    unsigned short v0;
    int sy;
    V3I t;
    V3I *cur;

    if (p->unk_30 == 0) {
        return;
    }
    if (p->unk_30->unk_00 == 0) {
        return;
    }
    res = func_020ad2d4(st, p->unk_10);
    if (res <= 1) {
        return;
    }
    NNS_G3dGeFlushBuffer();
    REG_A8 = p->unk_30->unk_04;
    REG_AC = p->unk_30->unk_08;
    REG_440 = 1;
    G3_LoadMtx43((const void *) data_021f486c);
    REG_A4 = (res << 16) | ((p->unk_30->unk_14 << 24) | 0x8080);
    q = p->unk_1C;
    pp = p->unk_28;
    cur = (V3I *) p->unk_2C;
    REG_500 = 3;
    cached = p->unk_1C[1];
    i = 0;
    shift = data_020d1e0c;
    zx = i;
    zy = i;
    while (i < p->unk_14) {
        int v1;
        int tb;

        if (i != 0) {
            v1 = cached;
        } else {
            v1 = *q;
        }
        tb = FX_MulFunc(data_021f47d0, v1);
        v_lo = tb + (st->unk_00 - p->unk_0C);
        v_hi = tb + (st->unk_00 + p->unk_0C);
        if (st->unk_08 != p->unk_18) {
            neg = -*q;
            tb = func_020310c8(zx);
            t.a = zy;
            t.b = tb;
            t.c = neg;
            t.c = t.c + st->unk_08;
            func_0203f844(cur, &t);
            cur->b = cur->b >> shift;
            cur->c = cur->c >> shift;
        }
        col = func_02065604();
        col2 = col;
        REG_480 = col2;
        p0 = (u16) ((p->unk_20 << 8) >> 16);
        g0 = (u16) ((*pp << 8) >> 16);
        REG_488 = (u32) p0 | ((u32) g0 << 16);
        sy = (s16) cur->c;
        v0 = (u16) ((v_lo << 11) >> 16);
        REG_48C = (u32) v0 | ((u32) (u16) (s16) cur->b << 16);
        REG_48C = (u16) sy;
        p0 = (u16) ((p->unk_24 << 8) >> 16);
        g0 = (u16) ((*pp << 8) >> 16);
        REG_488 = (u32) p0 | ((u32) g0 << 16);
        sy = (s16) cur->c;
        v0 = (u16) ((v_hi << 11) >> 16);
        REG_48C = (u32) v0 | ((u32) (u16) (s16) cur->b << 16);
        REG_48C = (u16) sy;
        q++;
        pp++;
        cur++;
        i++;
    }
    REG_504 = 0;
    REG_448 = 1;
    p->unk_18 = st->unk_08;
}
