/* func_02042a9c @ 0x02042a9c, 0x18c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x;
    int y;
} Pt;
typedef struct {
    int a;
    int b;
    int c;
} UnkStruct_02042a9c;

typedef struct {
    u8 f0 : 1;
    u8 f1 : 2;
    u8 f2 : 5;
    u8 g0 : 5;
    u8 g1 : 2;
    u8 g2 : 1;
    u16 unk_02;
    u16 unk_04;
    u16 unk_06[3];
} UnkStruct_02042a9c_2;

typedef struct {
    u8 unk_00;
    u8 unk_01;
    u16 unk_02;
} Entry;

typedef struct {
    u8 pad_00[0x5c];
    UnkStruct_02042a9c vec;
} UnkStruct_02042a9c_3;

extern void func_02045e24(Pt *p, int k);
extern UnkStruct_02042a9c_3 *func_020961a8(int k);
extern void func_02042ff8(int k, Pt *p);
extern void func_ov003_02221304(int k, int w, Pt *p, UnkStruct_02042a9c *v);
extern void func_ov004_022335b8(int k, int w, Pt *p, UnkStruct_02042a9c *v, int z);
extern void func_ov003_02220e20(int k, int w, Pt *p, UnkStruct_02042a9c *v);

extern Entry data_021c7788[];
extern u8 data_020e54a8;

void func_02042a9c(UnkStruct_02042a9c_2 *self)
{
    volatile u16 hi1;
    volatile u16 lo1;
    volatile u16 hi3;
    volatile u16 lo3;
    volatile u16 t2;
    volatile u16 t1;
    volatile u16 t3;
    Pt a;
    Pt b;
    Pt p1;
    Pt p2;
    Pt p3;
    Pt p4;
    UnkStruct_02042a9c v1;
    UnkStruct_02042a9c v2;
    UnkStruct_02042a9c v3;
    Entry *e;
    volatile u16 *w;
    int k;
    int hi;
    int lo;
    UnkStruct_02042a9c_3 *o;
    UnkStruct_02042a9c *q;
    unsigned int f;
    u16 tmp;

    e = &data_021c7788[self->f1];
    if (e->unk_00 != 0) {
        t1 = e->unk_02;
        tmp = t1;
        lo1 = tmp;
        hi1 = tmp;
        a.x = (int) hi1 >> 8;
        a.y = lo1 & 0xff;
        func_02045e24(&a, 0);
        if (self->f0 == 1) {
            w = self->unk_06;
            for (k = 0; k < 3; w++, k++) {
                if (*w != 0xffff) {
                    tmp = *w;
                    b.x = (int) tmp >> 8;
                    b.y = tmp & 0xff;
                    func_02045e24(&b, 0);
                }
            }
        }
    }
    e->unk_00 = self->f2;
    t2 = self->unk_02;
    e->unk_02 = t2;
    e->unk_01 = self->g1;
    t3 = self->unk_02;
    tmp = t3;
    lo3 = tmp;
    hi3 = tmp;
    hi = (int) hi3 >> 8;
    lo = lo3 & 0xff;
    switch (self->f2) {
        case 0x10:
        case 0x11:
        case 0x12:
            o = func_020961a8(self->f1);
            if (o == 0) {
                break;
            }
            q = &o->vec;
            if (data_020e54a8 == 0) {
                f = 1;
            } else {
                f = 0;
            }
            if (f != 0) {
                v1.a = q->a;
                v1.b = q->b;
                v1.c = q->c;
                p1.x = hi;
                p1.y = lo;
                func_ov003_02221304(self->f1, self->unk_04, &p1, &v1);
            } else {
                v2.a = q->a;
                v2.b = q->b;
                v2.c = q->c;
                p2.x = hi;
                p2.y = lo;
                func_ov004_022335b8(self->f1, self->unk_04, &p2, &v2, 0);
            }
            break;
        case 0xf:
            p3.x = hi;
            p3.y = lo;
            func_02042ff8(self->f1, &p3);
            break;
        case 0x13:
            if (self->unk_04 == 0xfff1) {
                break;
            }
            o = func_020961a8(self->f1);
            if (o == 0) {
                break;
            }
            q = &o->vec;
            v3.a = o->vec.a;
            v3.b = q->b;
            v3.c = q->c;
            p4.x = hi;
            p4.y = lo;
            func_ov003_02220e20(self->f1, self->unk_04, &p4, &v3);
            break;
    }
}
