/* func_0205b270 @ 0x0205b270, 0x5f8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern "C" {

typedef struct UnkStruct_0205b270_2 UnkStruct_0205b270_2;
typedef struct UnkStruct_0205b270 UnkStruct_0205b270;

struct Half {
    u16 value;
    Half() {}
};
struct UnkStruct_0205b270 {
    virtual int f0(int);
    virtual Half f4(int);
    virtual Half f8(int);
};
struct UnkStruct_0205b270_2 {
    int f0;
    int f4;
    int f8;
    int unk_0C;
    u16 unk_10;
    u16 unk_12;
};

extern int data_021c9854[];
extern int data_021c997c[];
extern int data_021c9a7c[];
extern int data_021c9774;
extern int data_021f3b70;
extern int data_021ebcd4;

extern void MI_CpuFill8(int *a, int b, int c);
extern void MIi_CpuClearFast(int a, int *b, int c);
extern int func_0205a370(UnkStruct_0205b270_2 *a, int *b, int *c, int *d, int e);
extern int func_0205bd90(u16 *a);
extern void func_0205bbf4(u16 *a, int b);
extern int func_0205affc(UnkStruct_0205b270_2 *a, int b, int c);
extern int func_0205aec0(UnkStruct_0205b270_2 *a, int b);
extern int func_0205adc0(UnkStruct_0205b270_2 *a, int b);
extern void func_0205a65c(UnkStruct_0205b270_2 *a, int b);
extern void func_0205ad00(UnkStruct_0205b270_2 *a, int b);
extern int func_0205ac84(UnkStruct_0205b270_2 *a, int b);
extern int func_0205ac5c(UnkStruct_0205b270_2 *a, u16 *b);
extern int func_0205ab10(UnkStruct_0205b270_2 *a, int b);
extern int func_0205a87c(UnkStruct_0205b270_2 *a, int b, int *c, int *d);
extern int func_0205a7d4(UnkStruct_0205b270_2 *a, int b, int *c);
extern int func_0205a6f0(UnkStruct_0205b270_2 *a, int b, u8 *c, u8 *d);
extern void func_0205bd8c(u16 *a);
extern int func_020622a0(int a);
extern int func_020644cc(int a);
extern int func_0205ba70(int *a);
extern int func_0205be9c(int *a);
extern short *func_0209d358(int a, int b);
extern int func_02060e78(int *a);
extern void func_020348ec(int a);
extern void func_020348e0(int a);
extern int func_0205a554(UnkStruct_0205b270_2 *a, int b, int c, int d, int e);
extern void func_0205a41c(UnkStruct_0205b270_2 *a, int b);
extern void func_0205be64(int *a);

int func_0205b270(UnkStruct_0205b270_2 *selfp, u16 *fl, int *p2, int *p3, int *p5, UnkStruct_0205b270 *p6, int p7, int p8,
                  u8 p9)
{
    int sel1;
    int a0, a1, a2, a3, a4, a5, a6;
    int f1, f2;
    int i;
    int sel2;
    int c0, c1;
    unsigned int j;
    int r1v;
    int n1;
    int r2v;
    int n2;
    int ex2;
    int bse;
    int outv;
    int t;
    int z1, z2;
    UnkStruct_0205b270_2 *self;

    u8 sb0, sb1;
    u8 item[6];
    volatile int wc;
    int total;
    int ex;
    int e;
    int found;
    unsigned int k, m, q, b;
    int cnt, cnt2;
    int v;
    unsigned int ok;
    int x;
    u16 fl5;

    self = selfp;
    *fl = 0;
    *p2 = 0;
    *p3 = 0;
    *p5 = 0;
    MI_CpuFill8(data_021c9854, 0, 0x128);
    wc = 0;
    MIi_CpuClearFast(wc, &data_021c9774, 0xe0);
    k = 0;
    for (k = 0; k < 0x4a; k++) {
        data_021c997c[k] = 0;
    }
    data_021c9a7c[10] = 0;
    total = 0;
    a0 = 0;
    a1 = 0;
    a2 = 0;
    a3 = 0;
    a4 = 0;
    a5 = 0;
    a6 = 0;
    f1 = 0;
    f2 = 0;
    for (i = 0; i < p7; i++) {
        t = p8 + i;
        e = p6->f0(t);
        Half roomA = p6->f4(t);
        self->unk_10 = roomA.value;
        Half roomB = p6->f8(t);
        self->unk_12 = roomB.value;
        func_0205a370(self, &self->f8, &self->f4, &self->unk_0C, e);
        func_0205bd90((u16 *) item);
        func_0205bbf4((u16 *) item, e);
        func_0205affc(self, e, 0);
        func_0205aec0(self, e);
        func_0205adc0(self, e);
        func_0205a65c(self, e);
        func_0205ad00(self, e);
        a0 = a0 + func_0205ac84(self, e);
        a1 = a1 + func_0205ac5c(self, (u16 *) item);
        a2 = a2 + func_0205ab10(self, e);
        a3 = a3 + func_0205a87c(self, e, p3, p5);
        a4 = a4 + func_0205a7d4(self, e, p2);
        sb0 = 0;
        sb1 = 0;
        a5 = a5 - func_0205a6f0(self, e, &sb0, &sb1);
        if (sb0 != 0) {
            f1 = 1;
        }
        if (sb1 != 0) {
            f2 = 1;
        }
        func_0205bd8c((u16 *) item);
    }
    total += a0;
    total += a1;
    total += a2;
    total += a3;
    total += a4;
    total += a5;
    sel1 = 0;
    sel2 = 0;
    c0 = 0;
    c1 = 0;
    for (j = 0; j < 0x4a; j++) {
        if ((int) j < 0x4a) {
            v = data_021c9854[j];
        } else {
            v = sel1;
        }
        if (v != 0) {
            switch (func_020622a0(j)) {
                case 0:
                    c0 = c0 + 1;
                    break;
                case 1:
                    if ((unsigned int) v > 0xbb8) {
                        c1 = c1 + 1;
                    }
                    break;
                case 2:
                    a6 = a6 + v;
                    break;
            }
        }
        total = total + v;
    }
    if (c0 != 0) {
        r1v = func_020644cc(c0);
        n1 = 0;
        z1 = 0;
        for (m = 0; m < 0x4a; m++) {
            if ((int) m < 0x4a) {
                v = data_021c9854[m];
            } else {
                v = z1;
            }
            if (v != 0) {
                if (func_020622a0(m) == 0) {
                    if (n1 == r1v) {
                        sel1 = m;
                        break;
                    }
                    n1 = n1 + 1;
                }
            }
        }
    }
    if (c1 != 0) {
        r2v = func_020644cc(c1);
        n2 = 0;
        z2 = 0;
        for (m = 0; m < 0x4a; m++) {
            if ((int) m < 0x4a) {
                v = data_021c9854[m];
            } else {
                v = z2;
            }
            if (v != 0) {
                if (func_020622a0(m) == 1) {
                    if (n2 == r2v) {
                        sel2 = m;
                        break;
                    }
                    n2 = n2 + 1;
                }
            }
        }
    }
    ex = 0;
    if ((data_021c9a7c[10] & 0xf) == 0xf) {
        found = 0;
        for (q = 0; q < 0x4a; q++) {
            if ((data_021c997c[q] & 0xf) == 0xf) {
                found = 1;
                break;
            }
        }
        if (found != 0) {
            ex = ex + 0x1388;
        } else {
            ex = ex + 0x3e8;
        }
        total = total + ex;
    }
    ex2 = func_0205ba70(&data_021c9774);
    total = total + ex2;
    if (total < 0) {
        total = 0;
    }
    if (fl != 0) {
        if (c0 != 0) {
            if ((int) sel1 < 0x4a) {
                v = data_021c9854[sel1];
            } else {
                v = 0;
            }
            if (v == 0x7530) {
                *fl |= 1;
            } else if (v == 0x61a8) {
                *fl |= 2;
            } else {
                *fl |= 4;
            }
        }
        if (c1 != 0) {
            *fl |= 8;
        }
        if (a6 >= 0xbb8) {
            *fl |= 0x10;
        }
        if (ex > 0) {
            *fl |= 0x20;
        }
        if (a1 >= 0x1f4) {
            *fl |= 0x40;
        }
        if (a2 >= 0x7d0) {
            *fl |= 0x80;
        }
        if (a3 >= 0x7d0) {
            *fl |= 0x100;
        }
        if (a4 >= 0xbb8) {
            *fl |= 0x200;
        }
        if ((unsigned int) ex2 >= 0x1b58) {
            *fl |= 0x400;
        }
    }
    if (p9 == 0) {
        goto finish_score;
    }
    if (func_0205be9c(&data_021f3b70) == 0) {
        if (*func_0209d358(0, 0x22) == 0) {
            goto finish_score;
        }
    }
    bse = func_02060e78(&data_021ebcd4);
    outv = 0;
    fl5 = 0;
    if (c0 != 0) {
        if ((int) sel1 < 0x4a) {
            v = data_021c9854[sel1];
        } else {
            v = fl5;
        }
        if (v == 0x7530) {
            fl5 |= 1;
        } else if (v == 0x61a8) {
            fl5 |= 2;
        } else {
            fl5 |= 4;
        }
    }
    if (c1 != 0) {
        fl5 |= 8;
    }
    if (a6 >= 0x1388) {
        fl5 |= 0x10;
    }
    if (ex > 0) {
        fl5 |= 0x20;
    }
    if (a1 >= 0x7d0) {
        fl5 |= 0x40;
    }
    if (a2 >= 0x1770) {
        fl5 |= 0x80;
    }
    if (a3 >= 0x1770) {
        fl5 |= 0x100;
    }
    if (a4 >= 0xc80) {
        fl5 |= 0x200;
    }
    if ((unsigned int) ex2 >= 0x1b58) {
        fl5 |= 0x400;
    }
    if (f1 != 0) {
        fl5 |= 0x1000;
    }
    if (f2 != 0) {
        fl5 |= 0x800;
    }
    cnt = 0;
    for (b = 0; b < 0xd; b++) {
        if ((fl5 & (1 << b)) != 0) {
            cnt = cnt + 1;
        }
    }
    func_020348ec(total);
    func_020348e0(fl5);
    ok = cnt != 0 ? (func_020644cc(2) != 0 ? 0 : 1) : 1;
    if (ok > 0) {
        if (total == 0) {
            outv = 0;
        } else if (total <= 0x4e1f) {
            outv = bse + 1;
        } else if (total <= 0x1116f) {
            outv = 8;
        } else if (total <= 0x1869f) {
            outv = 9;
        } else {
            outv = 0xa;
        }
    } else {
        x = func_020644cc(cnt);
        cnt2 = 0;
        for (b = 0; b < 0xd; b++) {
            if ((fl5 & (1 << b)) != 0) {
                if (x == cnt2) {
                    outv = b;
                    outv = b + 0xb;
                    break;
                }
                cnt2 = cnt2 + 1;
            }
        }
    }
    if ((unsigned int) outv - 0xbu > 2u) {
        sel1 = sel2;
    }
    if (func_0205a554(self, outv, total, sel1, *p2) != 0) {
        func_0205a41c(self, total);
        func_0205be64(&data_021f3b70);
    }
finish_score:
    return total;
}
}
