/* func_ov052_02260c1c @ 0x02260c1c, 0x438 bytes, Thumb, module ov052
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

// Wi-Fi connection screen: a state machine on self->state that fills {text, code}
// from the table at data_ov052_02261be0.

typedef struct {
    u8 pad_00[0xb0];
    int state;  // 0xb0
    u8 *d;      // 0xb4
    int unk_B8; // 0xb8
    int unk_BC; // 0xbc
} UnkStruct_02260c1c;

typedef struct {
    const char *text;
    u8 code;
} UnkStruct_02260c1c_2;

typedef struct {
    const char *text;
    u8 code;
} Entry;

extern Entry data_ov052_02261be0[];
extern u16 data_021f3aec;
extern void *data_020ccf94;

extern int func_020984e8(void);
extern int func_0204bcdc(u16 *p);
extern int func_0204bc64(u16 *p);
extern int func_02099020(int a, int b);
extern int func_02073d90(void *p);
extern int func_02099e9c(u16 *p);
extern int func_ov052_02261054(void *self);
extern int func_0202ea80(int a, int b);
extern u16 *func_02087228(void *record);
extern int func_020951bc(int a);
extern void func_020871cc(u16 *dst, u16 *src);
extern void func_02015de4(UnkStruct_02260c1c *self, u16 *p, int a, int b);
extern int func_02099870(int a);
extern int memcmp(void *a, void *b, int n);
extern int func_0209518c(int a, int b);
extern void func_02015e40(UnkStruct_02260c1c *self, int a, int b);
extern int func_020644cc(int a);
extern int func_0204c878(u16 *p);
extern void func_02015fb0(UnkStruct_02260c1c *self, int a, int b, int c, int d, int e);
extern int func_ov052_02261158(u8 *a, u8 *b, int n);
extern int func_ov052_0226118c(u8 *a, u8 *b, int n);
extern void MI_CpuFill8(u8 *p, int v, int n);

void func_ov052_02260c1c(UnkStruct_02260c1c *self, UnkStruct_02260c1c_2 *out)
{
    int t;
    int found;
    int t1, t2;
    int cond;
    int i;
    int k;
    u16 *p;
    u16 *pa;
    u16 *pb;
    int u, v;
    u16 s0, sB, r, sA, sE, sBB, sC;

    t = func_020984e8();

    if (self->state == 12) {
        out->code = data_ov052_02261be0[self->state].code;
        out->text = data_ov052_02261be0[self->state].text;
        return;
    }

    if (self->state != 0 && self->state != 1 && self->state != 2) {
        p = (u16 *) (self->d + 0x71e);
        if (func_0204bcdc(p) != 0) {
            sA = 0xfff1;
            t1 = func_0204bc64(p);
            t2 = func_0204bc64(&sA);
            cond = (t1 == t2) ? 1 : 0;
        } else {
            cond = (*p == 0xfff1) ? 1 : 0;
        }
        if (cond != 0) {
            if (func_02099020(t, 12) != 0) {
                if (func_02073d90(data_020ccf94) == 0) {
                    if (self->unk_BC == -1) {
                        s0 = 0x34a8;
                        self->unk_BC = func_02099e9c(&s0);
                    }
                }
                if (self->unk_BC >= 0) {
                    self->state = 5;
                } else if (func_ov052_02261054(self) != 0) {
                    self->state = 6;
                } else if (func_0202ea80(1, 1) == 0) {
                    self->state = 7;
                } else {
                    if (func_020951bc((int) func_02087228(&data_021f3aec)) != 0) {
                        func_020871cc(&sB, &data_021f3aec);
                        if (func_0204bcdc(&sB) != 0) {
                            sBB = 0xfff1;
                            t1 = func_0204bc64(&sB);
                            t2 = func_0204bc64(&sBB);
                            cond = (t1 == t2) ? 1 : 0;
                        } else {
                            cond = (sB == 0xfff1) ? 1 : 0;
                        }
                        if (cond == 0) {
                            func_020871cc(&r, &data_021f3aec);
                            func_02015de4(self, &r, 0, 7);
                            v = func_02099870(func_020984e8());
                            u = (int) func_02087228(&data_021f3aec);
                            if (*(u16 *) u != *(u16 *) v || memcmp((void *) (u + 2), (void *) (v + 2), 12) != 0 ||
                                func_0209518c(u, v) == 0) {
                                func_02015e40(self, (int) func_02087228(&data_021f3aec), 1);
                                self->state = 8;
                            } else {
                                func_02015e40(self, func_02099870(t), 1);
                                self->state = 9;
                            }
                            goto Ldfe;
                        }
                    }
                    self->state = 10;
                }
            }
        }
    }

Ldfe:
    if (self->state >= 0 && self->state < 13) {
        out->code = data_ov052_02261be0[self->state].code;
        if (func_02099020(t, 12) != 0) {
            if (self->state == 10) {
                out->code = (u8) (func_020644cc(4) + 0x17);
                if (out->code == 0x1a) {
                    out->code = 0x30;
                }
            }
            found = 0;
            p = (u16 *) (self->d + 0x71e);
            if (func_0204bcdc(p) != 0) {
                sC = 0xfff1;
                t1 = func_0204bc64(p);
                t2 = func_0204bc64(&sC);
                cond = (t1 == t2) ? 1 : 0;
            } else {
                cond = (*p == 0xfff1) ? 1 : 0;
            }
            if (cond == 0) {
                self->unk_B8 = func_0204c878((u16 *) (self->d + 0x71e)) * 2;
                func_02015de4(self, (u16 *) (self->d + 0x71e), 1, 7);
                func_02015fb0(self, self->unk_B8, 2, 10, 0, 0);
                for (i = 0; i < 3; i++) {
                    pb = (u16 *) (self->d + 0x720 + i * 2);
                    pa = (u16 *) (self->d + 0x71e);
                    if (func_0204bcdc(pa) != 0) {
                        t1 = func_0204bc64(pa);
                        t2 = func_0204bc64(pb);
                        cond = (t1 == t2) ? 1 : 0;
                    } else {
                        cond = (*pa == *pb) ? 1 : 0;
                    }
                    if (cond != 0) {
                        out->code = 0x1d;
                        goto Lafter;
                    }
                    pb = (u16 *) (self->d + 0x720 + i * 2);
                    if (func_0204bcdc(pb) != 0) {
                        sE = 0xfff1;
                        t1 = func_0204bc64(pb);
                        t2 = func_0204bc64(&sE);
                        cond = (t1 == t2) ? 1 : 0;
                    } else {
                        cond = (*pb == 0xfff1) ? 1 : 0;
                    }
                    if (cond != 0) {
                        found = i;
                    }
                }
            Lafter:
                if (out->code != 0x1d) {
                    k = func_ov052_02261158(self->d, self->d + 0x733, 5);
                    if ((self->d + 0x733)[k] == 0) {
                        (self->d + 0x733)[k] = 1;
                        *(u16 *) (self->d + found * 2 + 0x720) = *(u16 *) (self->d + 0x71e);
                    }
                    if (func_ov052_0226118c(self->d, self->d + 0x733, 5) == 0) {
                        MI_CpuFill8(self->d + 0x733, 0, 5);
                        (self->d + 0x733)[k] = 1;
                        *(u16 *) (self->d + found * 2 + 0x720) = *(u16 *) (self->d + 0x71e);
                    }
                    out->code = (u8) (k + 0x1e);
                }
            }
        }
        out->text = data_ov052_02261be0[self->state].text;
    }
}
