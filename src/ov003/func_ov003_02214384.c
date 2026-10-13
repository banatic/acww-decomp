/* func_ov003_02214384 @ 0x02214384, 0x1e4 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec;

struct S7d4 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 unk_03;
    u8 unk_04;
};

struct UnkStruct_02214384 {
    u8 pad_00[0x2d0];
    u8 unk_2D0[8];
    struct {
        unsigned int : 12;
        unsigned int f16 : 16;
        unsigned int : 4;
    } bf;
    u32 pad_2DC;
    u32 unk_2E0;
    u8 pad_2E4[0x68c - 0x2e4];
    int unk_68C, unk_690, unk_694;
    u8 pad_698[0x7d4 - 0x698];
    struct S7d4 unk_7D4;
};

struct St {
    u8 a;
    u8 b;
    u8 c;
    u8 d;
    volatile unsigned short id;
};

extern int func_02056f94(void *p);
extern void func_0203f7d0(Vec *a, Vec *b);
extern void func_ov003_02214200(struct UnkStruct_02214384 *self, Vec *a, Vec *b, Vec *c);
extern void func_020110c4(volatile unsigned short *p, struct UnkStruct_02214384 *self);
extern int func_020899a8(Vec *a, Vec *b, int d, u8 *out, int e);
extern void func_ov003_0222f458(Vec *v, u8 k);
extern u8 func_ov003_0222f490(u8 k);
extern unsigned int func_ov003_022140a8(struct UnkStruct_02214384 *self, struct St *st, Vec *v, u8 *p);
extern int func_ov003_0222e3a4(u8 k);
extern void func_0200f328(struct UnkStruct_02214384 *self, int id);
extern int func_ov003_02213da0(struct UnkStruct_02214384 *p, Vec *a, Vec *src, Vec *dst);
extern int func_020e8ed8(int a, int b);
extern int func_020e8b4c(int a, int b);

void func_ov003_02214384(struct UnkStruct_02214384 *self)
{
    struct St st;
    Vec va, vb, vc, vd;
    struct {
        Vec a;
        Vec b;
    } pr;
    Vec vf;
    struct S7d4 *s7;
    unsigned int ok;
    unsigned short hv, lv;
    int r;

    if (self->unk_2E0 == 0) {
        return;
    }
    if (func_02056f94(self->unk_2D0) != 0) {
        return;
    }
    if (self->bf.f16 < 3) {
        return;
    }

    st.a = 0;
    st.b = 0;

    {
        int t2 = self->unk_694, t1 = self->unk_690, t0 = self->unk_68C;
        va.x = t0;
        va.y = t1;
        va.z = t2;
    }
    func_0203f7d0(&va, &va);
    vb.x = va.x;
    vb.y = va.y;
    vb.z = va.z;
    func_ov003_02214200(self, &vb, &vc, &vd);

    s7 = &self->unk_7D4;
    if (s7->unk_00 == 0 && self->bf.f16 < 6) {
        func_020110c4(&st.id, self);
        ok = 0;
        hv = st.id;
        lv = st.id;
        if (lv >= 0x1376 && hv <= 0x1376) {
            ok = 1;
        }
        if (func_020899a8(&vb, &vc, ok ? 0xa00 : 0xd1f, &st.c, 0) != 0) {
            st.a = 1;
            func_ov003_0222f458((Vec *) &pr, st.c);
            st.b = func_ov003_0222f490(st.c);
            if (st.b != 0) {
                pr.a.z = pr.a.z + 0x100;
            }
        }
    }

    switch (func_ov003_022140a8(self, &st, (Vec *) &pr, &st.b)) {
        case 1:
            if (func_ov003_0222e3a4(st.c) != 0) {
                s7->unk_00 = 1;
                s7->unk_04 = st.c;
                func_0200f328(self, 0x847);
            }
            break;
        case 2:
            return;
        case 3:
            if (s7->unk_00 != 0) {
                break;
            }
            s7->unk_00 = 1;
            s7->unk_04 = 0xff;
            func_0200f328(self, 0x847);
            break;
        case 0:
        default:
            vf.x = va.x;
            vf.y = va.y;
            vf.z = va.z;
            r = func_ov003_02213da0(self, &vf, &vc, &vd);
            if (st.a == 0) {
                break;
            }
            if (r != 0) {
                pr.b.x = pr.a.x - vd.x;
                pr.b.z = pr.a.z - vd.z;
                r = func_020e8ed8(pr.b.x, pr.b.z);
            } else {
                r = 0x7fff;
            }
            if (func_020e8b4c(r, 0) > 0x4000) {
                if (func_ov003_0222e3a4(st.c) != 0) {
                    s7->unk_00 = 1;
                    s7->unk_04 = st.c;
                    func_0200f328(self, 0x847);
                }
            }
            break;
    }
}
