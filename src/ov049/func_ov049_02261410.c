/* func_ov049_02261410 @ 0x02261410, 0x25c bytes, Thumb, module ov049
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    char pad_00[0x734];
    u16 unk_734;
    u16 unk_736;
    u16 unk_738;
} UnkStruct_02261410;

typedef struct {
    char pad_00[0x40];
    int unk_40;
    char pad_44[0x6c];
    UnkStruct_02261410 *unk_B0;
    char pad_B4[8];
    int unk_BC;
} UnkStruct_02261410_2;

extern int func_020984e8(void);
extern int func_02099fe8(void);
extern int func_0201b43c(void *, int);
extern void func_0206844c(int, u8 *, void *);
extern void func_ov049_02260ac4(UnkStruct_02261410_2 *);
extern u16 *func_02099710(int);
extern u16 *func_020996e0(int);
extern u16 *func_020996f8(int);
extern int func_02095b58(u16 *);
extern int func_02095b40(u16 *);
extern void func_02095b4c(u16 *);
extern int func_0204c4c0(u16 *);
extern void func_02095eec(int, int);
extern void func_0203ae98(void);
extern void func_02068440(int);
extern void func_ov049_022610c4(UnkStruct_02261410_2 *, int);

extern void *data_ov049_02263298;

void func_ov049_02261410(UnkStruct_02261410_2 *p, int a1)
{
    struct {
        u8 b[3];
        volatile u16 h4;
        u16 h6;
        u16 h8;
        u16 ha;
        u16 hc;
        u16 he;
    } m;
    int h;

    h = func_020984e8();
    if (a1 == 0) {
        if (func_02099fe8() == -1) {
            m.b[0] = 0x2c;
            func_0206844c(p->unk_40, &m.b[0], data_ov049_02263298);
        } else if (func_0201b43c(p->unk_B0, p->unk_BC) == 0) {
            m.b[1] = 0x2b;
            func_0206844c(p->unk_40, &m.b[1], data_ov049_02263298);
        } else {
            m.b[2] = 0x29;
            func_0206844c(p->unk_40, &m.b[2], data_ov049_02263298);
            func_ov049_02260ac4(p);
        }
    } else if (a1 == 1) {
        unsigned int ok;
        UnkStruct_02261410 *q;
        u16 t;

        p->unk_B0->unk_736 = 0xfff1;
        q = p->unk_B0;
        ok = 0;
        t = q->unk_738;
        if (t >= 0x11a8 && t <= 0x12a7) {
            ok = 1;
        }
        if (ok || (t >= 0x13c8 && t <= 0x1407) || (t >= 0x13a8 && t <= 0x13c7) || (t >= 0x1431 && t <= 0x1470)) {
            if (t >= 0x11a8 && t <= 0x12a7) {
                p->unk_B0->unk_734 = *func_02099710(h);
                m.h6 = p->unk_B0->unk_738;
                func_02095b58(&m.h6);
            } else if ((t >= 0x13c8 && t <= 0x1407) || (t >= 0x13a8 && t <= 0x13c7)) {
                if (t >= 0x13a8 && t <= 0x13c7) {
                    if (func_0204c4c0(&q->unk_738) == 0) {
                        p->unk_B0->unk_736 = *func_020996e0(h);
                        m.h8 = 0xfff1;
                        func_02095b4c(&m.h8);
                    }
                }
                p->unk_B0->unk_734 = *func_020996f8(h);
                m.ha = p->unk_B0->unk_738;
                func_02095b40(&m.ha);
            } else if (t >= 0x1431 && t <= 0x1470) {
                unsigned int ok2;
                u16 a, b;

                p->unk_B0->unk_734 = *func_020996e0(h);
                m.hc = p->unk_B0->unk_738;
                func_02095b4c(&m.hc);
                m.h4 = 0xfff1;
                m.h4 = *func_020996f8(h);
                ok2 = 0;
                a = m.h4;
                b = m.h4;
                if (b >= 0x13a8 && a <= 0x13c7) {
                    ok2 = 1;
                }
                if (ok2) {
                    if (func_0204c4c0((u16 *) &m.h4) == 0) {
                        p->unk_B0->unk_736 = *func_020996f8(h);
                        m.he = 0xfff1;
                        func_02095b40(&m.he);
                    }
                }
            }
            func_02095eec(1, 4);
            func_0203ae98();
            func_02068440(p->unk_40);
            func_ov049_022610c4(p, 7);
        }
    }
}
