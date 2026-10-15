/* func_ov049_0226124c @ 0x0226124c, 0x1c4 bytes, Thumb, module ov049
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_02095b58(u16 *);
extern int func_02095b40(u16 *);
extern void func_02095b4c(u16 *);
extern void func_02095eec(int, int);
extern void func_ov049_022610c4(void *, int);
extern int func_0203aeac(void);
extern int func_02099fe8(void);
extern int func_0201b43c(void *, int);
extern void func_ov049_02260ac4(void *);
extern void func_0206844c(int, u8 *, void *);
extern void *data_ov049_02263298;

typedef struct {
    char pad_00[0x734];
    u16 unk_734;
    u16 unk_736;
    u16 unk_738;
} UnkStruct_0226124c;

typedef struct {
    char pad_00[0x40];
    int unk_40;
    char pad_44[0x6c];
    UnkStruct_0226124c *unk_B0;
    char pad_B4[8];
    int unk_BC;
} UnkStruct_0226124c_2;

void func_ov049_0226124c(UnkStruct_0226124c_2 *p, int a1)
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

    {
        unsigned int ok;
        UnkStruct_0226124c *q;
        u16 t;
        q = p->unk_B0;
        ok = 0;
        t = q->unk_738;
        if (t >= 0x11a8 && t <= 0x12a7) {
            ok = 1;
        }
        if (ok) {
            m.h6 = q->unk_734;
            func_02095b58(&m.h6);
        }
    }
    {
        unsigned int ok;
        UnkStruct_0226124c *q;
        u16 t;
        q = p->unk_B0;
        ok = 0;
        t = q->unk_738;
        if (t >= 0x13c8 && t <= 0x1407) {
            ok = 1;
        }
        if (ok || (t >= 0x13a8 && t <= 0x13c7)) {
            m.h8 = q->unk_734;
            func_02095b40(&m.h8);
        }
    }
    {
        unsigned int ok;
        UnkStruct_0226124c *q;
        u16 t;
        q = p->unk_B0;
        ok = 0;
        t = q->unk_738;
        if (t >= 0x1431 && t <= 0x1470) {
            ok = 1;
        }
        if (ok) {
            m.ha = q->unk_734;
            func_02095b4c(&m.ha);
        }
    }
    {
        UnkStruct_0226124c *q;
        q = p->unk_B0;
        if (q->unk_736 != 0xfff1) {
            unsigned int ok;
            u16 a, b;
            m.h4 = q->unk_736;
            ok = 0;
            a = m.h4;
            b = m.h4;
            if (b >= 0x13a8 && a <= 0x13c7) {
                ok = 1;
            }
            if (ok || (a >= 0x13c8 && a <= 0x1407)) {
                m.hc = p->unk_B0->unk_736;
                func_02095b40(&m.hc);
            } else if (a >= 0x1431 && a <= 0x1470) {
                m.he = p->unk_B0->unk_736;
                func_02095b4c(&m.he);
            }
        }
    }

    func_02095eec(0, 4);
    func_ov049_022610c4(p, 8);
    func_0203aeac();
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
    }
}
