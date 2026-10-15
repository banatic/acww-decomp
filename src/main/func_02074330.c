/* func_02074330 @ 0x02074330, 0x5d4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_02074330 {
    u8 pad_00[0x64];
    int unk_64;
    u8 pad_68[0x6c - 0x68];
    u8 unk_6C;
} UnkStruct_02074330;

extern UnkStruct_02074330 *data_020ccf94;
extern u8 data_021d0a34[];

extern int func_02073dd4(UnkStruct_02074330 *a, int b);
extern int func_02073de4(UnkStruct_02074330 *a);
extern int func_02073370(UnkStruct_02074330 *a);
extern void func_0207337c(UnkStruct_02074330 *a, int b);
extern void func_02073354(UnkStruct_02074330 *a);
extern int func_02073d68(UnkStruct_02074330 *a);
extern void func_02073d74(UnkStruct_02074330 *a, int b);
extern void func_02073d6c(UnkStruct_02074330 *a, int b);
extern int func_02073d70(UnkStruct_02074330 *a);
extern int func_0207384c(UnkStruct_02074330 *a);
extern int func_020732c0(UnkStruct_02074330 *a);
extern int func_02073884(UnkStruct_02074330 *a);
extern int func_020736f4(UnkStruct_02074330 *a, int b, int c);
extern void func_0207385c(UnkStruct_02074330 *a);
extern int func_02038a30(void);
extern void func_020732cc(UnkStruct_02074330 *a, int b);
extern int func_02077a80(void);
extern int func_02073690(UnkStruct_02074330 *a);
extern void func_02074fa0(void);
extern char *func_02137550(void *a, int b);
extern int func_02073918(UnkStruct_02074330 *a, int b);
extern int func_02073d28(UnkStruct_02074330 *a, int b);
extern int func_02074f28(int a, int b, int c);
extern int func_02074e64(int a, int b);
extern int func_02077b58(int a);
extern int func_020734a4(UnkStruct_02074330 *a);
extern int func_020734c8(UnkStruct_02074330 *a);
extern void func_020734ac(UnkStruct_02074330 *a, int b);
extern int func_02074dfc(int a);
extern int func_02073e30(UnkStruct_02074330 *a, int b, int c, int d, int e, int f, int g, int h, int i, int j);
extern int func_02073d80(UnkStruct_02074330 *a);
extern void func_02073388(UnkStruct_02074330 *a, int b);
extern void func_0207388c(UnkStruct_02074330 *a);
extern void func_02073754(UnkStruct_02074330 *a);
extern void func_020750fc(void);
extern void func_02073cd0(UnkStruct_02074330 *a, int b, int c);
extern void func_020750f4(void);
extern void func_02073c74(UnkStruct_02074330 *a, int b, int c);
extern int func_02074e48(int a);
extern void func_020a6f74(int a, int b);
extern int func_020a6ea0(void);
extern void func_020a6eb0(int a);
extern void func_02073698(UnkStruct_02074330 *a, int b);
extern int func_02077b20(int a);
extern int func_02074308(void);
extern int func_02073d90(UnkStruct_02074330 *a);
extern int func_02073044(void);
extern int func_020ebf70(void);
extern int func_02073c90(UnkStruct_02074330 *a, int b);
extern void func_02077b3c(u8 *a, int b, int c);
extern void func_0207323c(UnkStruct_02074330 *a);
extern int func_020731c4(UnkStruct_02074330 *a);
extern int func_020ec1f8(void);
extern int func_020ec920(void);
extern void func_02073d78(UnkStruct_02074330 *a);

void func_02074330(int p0)
{
    int s1c;
    int s20;
    int s24;
    int s28;
    int s2c;
    int s30;
    int s34;
    int s38;
    int s3c;

    u16 h40[3];
    u16 h46[3];
    u16 h4c[3];
    int w54[3];
    int w60[3];
    int w6c[3];
    int w78[3];
    int w84[3];
    int w90[3];

    UnkStruct_02074330 *self;
    int on;
    int i;
    int r;
    int u;
    int v;
    int n;
    int q;
    int idx;
    u16 mask;
    UnkStruct_02074330 *g;
    int aa, bb, cc;

    self = data_020ccf94;
    s1c = self->unk_64;
    if (func_02073dd4(self, s1c) == 0) {
        return;
    }
    on = func_02073de4(self);
    if (on != 0) {
        r = func_02073370(self);
        if (r >= 0) {
            g = data_020ccf94;
            func_0207337c(g, r);
            func_02073354(g);
        }
    }
    if (on != 0) {
        if (func_02073d68(self) == 1) {
            g = data_020ccf94;
            func_02073d74(g, 1);
            func_02073d6c(g, 3);
        }
    }
    s20 = func_02073d70(self);
    if (s20 != 0) {
        s34 = func_0207384c(self);
        if (s34 != 0) {
            g = data_020ccf94;
            v = func_020732c0(g);
            if (func_020736f4(g, func_02073884(g), s34) != 0) {
                func_0207385c(self);
                if ((v & 2) != 0) {
                    if (func_02038a30() == 0) {
                        v = v ^ 2;
                        func_020732cc(self, v);
                    }
                }
            } else {
                if ((v & 2) == 0) {
                    v = v | 2;
                    func_020732cc(self, v);
                }
            }
        }
    }
    if (on == 0) {
        goto tail;
    }
    if (s20 != 2) {
        goto other;
    }
    if (func_02077a80() == 0) {
        goto second;
    }
    s24 = func_02073690(self);
    func_02074fa0();
    s28 = 0;
    s2c = 0;
    func_02137550(w54, 0xc);
    func_02137550(w60, 0xc);
    func_02137550(h40, 6);
    for (i = 3; i >= 0; i--) {
        if (func_02073dd4(self, i) != 0) {
            if (func_02073918(self, i) == 0) {
                u = func_02073d28(self, i) + 1;
                n = 0;
                n = n + 1;
                if (s28 == 0) {
                    s28 = u;
                    s2c = func_02074f28(u, 0, 0);
                    u = u + s2c;
                    n = n + s2c;
                } else {
                    func_02074f28(u, s28, s2c);
                    u = u + s2c;
                    n = n + s2c;
                }
                n = n + func_02074e64(u, i);
                s38 = func_02077b58(i);
                w54[s38] = func_02073d28(self, i);
                w60[s38] = n;
                h40[s38] = (u16) (1 << i);
            } else {
                aa = func_020734a4(self);
                bb = func_020734c8(self);
                cc = bb + aa;
                cc = func_02074e64(cc, i);
                if (cc == 0) {
                    continue;
                }
                aa = aa + cc;
                func_020734ac(self, aa);
            }
        } else {
            if (func_02073918(self, 0) != 0) {
                s3c = func_02074dfc(i);
                if (s3c != 0) {
                    q = i - 1;
                    w54[q] = func_02073d28(self, i);
                    w60[q] = s3c;
                    h40[q] = (u16) (1 << i);
                }
            }
        }
    }
    r = func_02073e30(self, w54[0], w60[0], h40[0], w54[1], w60[1], h40[1], w54[2], w60[2], h40[2]);
    if (r == 0 && self->unk_6C > 1) {
        goto far;
    }
    g = data_020ccf94;
    func_02073388(g, func_02073d80(g));
    func_0207388c(g);
    func_02073754(g);
    for (i = 3; i >= 0; i--) {
        if (func_02073dd4(self, i) != 0) {
            if (func_02073918(self, i) == 0) {
                func_020750fc();
                func_02073cd0(self, i, 1);
                func_020750f4();
                func_02073c74(self, i, 0);
            }
        } else {
            if (r != 0) {
                if (func_02073918(self, 0) != 0) {
                    if (func_02074e48(i) != 0) {
                        func_020a6f74(i, 7);
                    }
                }
            }
        }
    }
    if (func_020a6ea0() != 7) {
        goto tail;
    }
    func_020a6eb0(8);
    goto tail;

far:
    func_02073698(self, s24);
    goto tail;

second:
    if (on == 0) {
        goto lastb;
    }
    func_02074fa0();
    func_02137550(w6c, 0xc);
    func_02137550(w78, 0xc);
    func_02137550(h46, 6);
    n = 0;
    for (i = 3; i >= 0; i--) {
        if (func_02073dd4(self, i) != 0) {
            if (func_02073918(self, i) == 0) {
                u = func_02073d28(self, i);
                if (func_02077b20(u) != 0) {
                    w6c[n] = u;
                    w78[n] = 1;
                    h46[n] = (u16) (1 << i);
                    n = n + 1;
                }
            }
        }
    }
    if (n == 0) {
        goto emptyb;
    }
    r = func_02073e30(self, w6c[0], w78[0], h46[0], w6c[1], w78[1], h46[1], w6c[2], w78[2], h46[2]);
    if (r == 0 && self->unk_6C > 1) {
        goto tail;
    }
    for (i = 3; i >= 0; i--) {
        if (func_02073dd4(self, i) != 0) {
            if (func_02073918(self, i) == 0) {
                func_02073c74(self, i, 0);
            }
        }
    }
    goto tail;

emptyb:
    if (func_02073918(self, 0) != 0) {
        if (self->unk_6C != 4) {
            func_02074308();
        }
    }
    goto tail;

lastb:
    if (func_02073918(self, 0) != 0) {
        if (self->unk_6C != 4) {
            func_02074308();
        }
    }
    goto tail;

other:
    if (s20 != 1) {
        goto tail;
    }
    if (func_02073d90(self) == 0) {
        goto tail;
    }
    if ((func_02073044(), func_020ebf70()) == 0) {
        goto tail;
    }
    func_02137550(w84, 0xc);
    func_02137550(h4c, 6);
    func_02137550(w90, 0xc);
    for (i = 3; i >= 0; i--) {
        if (func_02073dd4(self, i) != 0) {
            if (func_02073918(self, i) == 0) {
                u = func_02073c90(self, i);
                idx = func_02077b58(i);
                if (u != 0) {
                    s30 = (int) &data_021d0a34[idx];
                    func_02077b3c(&data_021d0a34[idx], u, 0x18);
                    w90[idx] = s30;
                    w84[idx] = w84[idx] + 1;
                    h4c[idx] = (u16) (1 << i);
                }
            }
        }
    }
    if (func_02073e30(self, w90[0], w84[0], h4c[0], w90[1], w84[1], h4c[1], w90[2], w84[2], h4c[2]) == 0) {
        goto tail;
    }
    for (i = 3; i >= 0; i--) {
        if (func_02073dd4(self, i) != 0) {
            if (func_02073918(self, i) == 0) {
                func_02073c74(self, i, 0);
            }
        }
    }

tail:
    if (s20 == 2) {
        func_020750fc();
        g = data_020ccf94;
        func_0207323c(g);
        func_020750f4();
        func_020750fc();
        r = func_020731c4(g);
        func_020750f4();
        v = func_020732c0(g);
        if (r != 0) {
            if ((v & 1) == 0) {
                v = v | 1;
                func_020732cc(self, v);
            }
        } else {
            if ((v & 1) != 0) {
                if (func_02038a30() == 0) {
                    v = v ^ 1;
                    func_020732cc(self, v);
                }
            }
        }
        if (s1c == 0) {
            mask = 0;
            for (i = 3; i >= 0; i--) {
                if (func_02073dd4(self, i) != 0) {
                    if (func_02073918(self, i) == 0) {
                        mask = mask | (1 << i);
                    }
                }
            }
            if (mask != (mask & func_020ec1f8())) {
                v = func_020732c0(self);
                if ((v & 4) == 0) {
                    func_020732cc(self, v | 4);
                }
            }
        } else {
            if ((func_02073044(), func_020ec920()) == 0) {
                v = func_020732c0(self);
                if ((v & 8) == 0) {
                    func_020732cc(self, v | 8);
                }
            }
        }
    }
    if (p0 == 0) {
        func_02073d78(self);
    }
}
