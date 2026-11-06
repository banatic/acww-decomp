/* mabel_4: 27 functions, module ov049
 * mwccarm 1.2/base -O4,s
 * func_ov049_02262a60 @ 0x02262a60, 0x34 bytes, Thumb
 * func_ov049_02262a4c @ 0x02262a4c, 0x12 bytes, Thumb
 * func_ov049_022629e4 @ 0x022629e4, 0x68 bytes, Thumb
 * func_ov049_02262914 @ 0x02262914, 0xd0 bytes, Thumb
 * func_ov049_022628e0 @ 0x022628e0, 0x34 bytes, Thumb
 * func_ov049_02262818 @ 0x02262818, 0xc8 bytes, Thumb
 * func_ov049_022627e4 @ 0x022627e4, 0x34 bytes, Thumb
 * func_ov049_022626e4 @ 0x022626e4, 0x100 bytes, Thumb
 * func_ov049_022626ac @ 0x022626ac, 0x38 bytes, Thumb
 * func_ov049_02262664 @ 0x02262664, 0x48 bytes, Thumb
 * func_ov049_0226262c @ 0x0226262c, 0x38 bytes, Thumb
 * func_ov049_022625fc @ 0x022625fc, 0x30 bytes, Thumb
 * func_ov049_022625f8 @ 0x022625f8, 0x4 bytes, Thumb
 * func_ov049_022625f4 @ 0x022625f4, 0x4 bytes, Thumb
 * func_ov049_022625c0 @ 0x022625c0, 0x34 bytes, Thumb
 * func_ov049_0226256c @ 0x0226256c, 0x54 bytes, Thumb
 * func_ov049_02262568 @ 0x02262568, 0x4 bytes, Thumb
 * func_ov049_02262470 @ 0x02262470, 0xf8 bytes, Thumb
 * func_ov049_0226246c @ 0x0226246c, 0x4 bytes, Thumb
 * func_ov049_02262414 @ 0x02262414, 0x58 bytes, Thumb
 * func_ov049_022623f0 @ 0x022623f0, 0x24 bytes, Thumb
 * func_ov049_022623b4 @ 0x022623b4, 0x3c bytes, Thumb
 * func_ov049_02262374 @ 0x02262374, 0x40 bytes, Thumb
 * func_ov049_02262344 @ 0x02262344, 0x30 bytes, Thumb
 * func_ov049_02262340 @ 0x02262340, 0x4 bytes, Thumb
 * func_ov049_0226233c @ 0x0226233c, 0x4 bytes, Thumb
 * func_ov049_022622fc @ 0x022622fc, 0x40 bytes, Thumb
 */

#include "types.h"

typedef struct {
    unsigned char pad_00[0x564];
    int unk_564;
    unsigned char pad_568[0x408]; // 0x970 - 0x568
    unsigned short unk_970;
    unsigned short unk_972;
    unsigned char pad_974;
    unsigned char unk_975;
} UnkStruct_022629e4;

typedef struct {
    unsigned int x, y, z;
} Vec3;

typedef struct UnkStruct_02262818 {
    u8 pad_00[0x5c];
    u8 unk_5C[0x8e - 0x5c];
    s16 unk_8E;
    u8 pad_90[0x350 - 0x90];
    u8 unk_350[0x564 - 0x350];
    u8 unk_564[1];
} UnkStruct_02262818;

typedef struct {
    int unk_00, x1, x2;
} UnkStruct_022626e4;

typedef struct UnkStruct_02262470 {
    char pad_00[0x64];
    int unk_64;
} UnkStruct_02262470;

struct UnkStruct_02262470_2;

typedef struct ObjVt {
    char pad_00[8];
    void (*unk_08)(struct UnkStruct_02262470_2 *o);
} ObjVt;

typedef struct UnkStruct_02262470_2 {
    ObjVt *vt;
} UnkStruct_02262470_2;

typedef struct UnkStruct_02262470_3 {
    char pad_00[0x658];
    UnkStruct_02262470_2 unk_658;
    char pad_65C[0x738 - 0x65c];
    u16 unk_738;
} UnkStruct_02262470_3;

typedef struct {
    unsigned char pad_00[0x64];
    int value;
} UnkStruct_02262414;

typedef struct {
    unsigned char pad_00[0x8e];
    signed short unk_8E;
} SelfType;

struct UnkStruct_022622fc {
    char pad_00[0x564];
    char sub[0x413];
    char unk_977;
};

extern int func_0202ea80(int, int);
extern void func_ov049_0226208c(void *, int);
extern int func_0203e0a8(int, int);
extern int func_02019c6c(void *, int, unsigned short);
extern int func_020644cc(int);
extern int func_0202ea40(void *, void *, int);
extern unsigned short data_020c80f8;
extern void *func_02095794(int param);
extern void func_0201b458(Vec3 *out, char *self, Vec3 *in);
extern int data_021c80bc;
extern int func_0204ed30(int value, char *ptr);
extern int func_020eaa2c(Vec3 *out, char *ptr);
extern int func_020e8840(char *ptr);
extern int func_ov049_0226048c(void *p);
extern int func_ov049_02260500(void *p);
extern int func_0201c378(void *p, int n);
extern int func_0201c2c8(void *p, int n);
extern int func_020e8b4c(int a, int b);
extern void func_ov049_02262a94(void *p, int n);
extern void func_0201aff4(void *a, int b);
extern int func_02019e00(void *a);
extern int func_02019de8(void *a);
extern int func_02019d0c(void *p, int r1, int r2, int r3, int s1, int s2, int s3, int s4, int s5, int s6, int s7);
extern void func_0201b044(void *p, UnkStruct_022626e4 *buf);
extern int func_020eaa6c(UnkStruct_022626e4 *buf, void *p);
extern int func_02016104(void *p);
extern int func_0201c314(void *p, int x);
extern int func_020147fc(void *p, int a, int b, int c);
extern int func_02014868(void *ptr);
extern int func_020ad8f0(void);
extern int func_0203e020(void *ptr);
extern int func_020b5e10(void);
extern int func_020b6098(int, int);
extern UnkStruct_02262470 *data_020ccf94;
extern int func_0201c0e0(void *unused0);
extern int func_0201c040(UnkStruct_02262470_3 *self, int *a, int *b);
extern void func_0201c054(UnkStruct_02262470_3 *self, int a, int b, int c);
extern int func_0201c2a4(UnkStruct_02262470_3 *self, int a);
extern void func_02016108(UnkStruct_02262470_2 *o, int a);
extern int func_0204bcdc(u16 *p);
extern int func_0204bc64(u16 *p);
extern int func_020a7278(void);
extern short data_020c80f0[];

int func_ov049_02262a60(void *arg)
{
    int result;
    void *ptr;

    result = func_0202ea80(0xf, 1);
    if (result != 0) {
        ptr = (char *) arg + 0x658;
        func_ov049_0226208c(ptr, 1);
    } else {
        ptr = (char *) arg + 0x658;
        func_ov049_0226208c(ptr, 0);
    }
    return 1;
}

int func_ov049_02262a4c(int arg0)
{
    func_0203e0a8(arg0, 0);
    return 1;
}

int func_ov049_022629e4(UnkStruct_022629e4 *self)
{
    int local[2];

    func_02019c6c(&self->unk_564, 1, self->unk_972);
    self->unk_972 = data_020c80f8;
    self->unk_970 = (unsigned short) (func_020644cc(5) * 20 + 100);
    if (func_0202ea40(self, local, 2) != 0) {
        self->unk_975 = 1;
    } else {
        self->unk_975 = 0;
    }
    return 1;
}

int func_ov049_02262914(char *self)
{
    Vec3 vec;
    Vec3 out;
    int r6, r1tmp, r4;
    unsigned int *pt;
    short s;

    pt = (unsigned int *) func_02095794(4);
    vec.x = pt[0];
    vec.y = pt[1];
    vec.z = pt[2];

    func_0201b458(&out, self, &vec);

    r6 = func_0201c378((void *) self, 4);
    r1tmp = func_0201c2c8((void *) self, 4);
    s = *(short *) (self + 0x8e);
    r4 = func_020e8b4c((short) s, r1tmp);

    func_0204ed30(data_021c80bc, self + 0x5c);

    if (r6 > 0x5000) {
        if (func_020eaa2c(&out, self + 0x5c) != 0) {
            func_ov049_02262a94((void *) self, 3);
            goto later;
        }
    }
    if (r4 > 0x2000) {
        func_ov049_02262a94((void *) self, 2);
    }
later:
    if (func_ov049_0226048c((void *) self) != 0) {
        return 1;
    }
    if (func_ov049_02260500((void *) self) != 0) {
        return 1;
    }
    if (*(unsigned char *) (self + 0x975) != 0) {
        if (func_020e8840(self + 0x970) == 0) {
            func_ov049_02262a94((void *) self, 7);
        }
    }
    return 1;
}

int func_ov049_022628e0(void *arg0)
{
    func_02019d0c((char *) arg0 + 0x564, 3, 1, 0, 0, 0, 0, 0, 0, (unsigned short) data_020c80f8, 0);
    return 1;
}

int func_ov049_02262818(UnkStruct_02262818 *self)
{
    u32 arr[3];
    u32 buf[3];
    int r6, r4;

    if (func_ov049_0226048c(self) != 0) {
        return 1;
    }
    if (func_ov049_02260500(self) != 0) {
        return 1;
    }

    {
        u32 *p = func_02095794(4);
        arr[0] = p[0];
        arr[1] = p[1];
        arr[2] = p[2];
    }
    func_0201b458((Vec3 *) buf, (char *) self, (Vec3 *) arr);
    r6 = func_0201c378(self, 4);
    r4 = func_0201c2c8(self, 4);
    func_020e8b4c(self->unk_8E, r4);
    func_0204ed30((int) ((*(void **) &data_021c80bc)), (char *) self->unk_5C);

    if (r6 > 0x5000) {
        if (func_020eaa2c((Vec3 *) buf, (char *) self->unk_5C) != 0) {
            func_ov049_02262a94(self, 3);
        }
    }

    func_0201aff4(self->unk_350, r4);
    if (func_02019e00(self->unk_564) == 3) {
        if (func_02019de8(self->unk_564) != 0) {
            func_ov049_02262a94(self, 1);
        }
    }
    return 1;
}

int func_ov049_022627e4(int param)
{
    func_02019d0c((void *) (param + 0x564), 1, 1, 0, 0, 0, 0, 0, 0, (unsigned short) data_020c80f8, 0);
    return 1;
}

int func_ov049_022626e4(void *self)
{
    UnkStruct_022626e4 src, buf;
    int t;

    if (func_ov049_0226048c(self)) {
        return 1;
    }
    if (func_ov049_02260500(self)) {
        return 1;
    }

    {
        UnkStruct_022626e4 *p = (UnkStruct_022626e4 *) func_02095794(4);
        src.unk_00 = p->unk_00;
        src.x1 = p->x1;
        src.x2 = p->x2;
    }
    func_0201b458((Vec3 *) (&buf), (char *) self, (Vec3 *) (&src));
    t = func_0201c378(self, 4);
    func_0204ed30(data_021c80bc, (char *) ((char *) self + 0x5c));

    if (t > 0x6000) {
        if (func_02019e00((char *) self + 0x564) == 1) {
            func_02019d0c((char *) self + 0x564, 2, 1, 0, 0, 0x800, 0, 0, 0, data_020c80f8, 0);
        }
    } else {
        if (func_02019e00((char *) self + 0x564) == 2) {
            func_02019d0c((char *) self + 0x564, 1, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
        }
    }

    func_0201b044((char *) self + 0x350, &buf);

    if (t <= 0x5000 || func_020eaa6c(&buf, (char *) self + 0x5c) != 0) {
        func_ov049_02262a94(self, 1);
    }

    return 1;
}

int func_ov049_022626ac(void *self)
{
    int r1 = func_02016104((char *) self + 0x658);
    int r2 = 0;
    if (r1 != 0) {
        r2 = func_0201c314(self, r1);
    }
    func_020147fc((char *) self + 0x618, 0, r2, 0);
    return 1;
}

int func_ov049_02262664(char *p)
{
    if (func_02014868(p + 0x618)) {
        return 1;
    }
    if (*(unsigned char *) (p + 0x974) != 0 && func_020ad8f0() == 0) {
        return 1;
    }
    func_0203e020(p);
    func_ov049_02262a94(p, 6);
    return 1;
}

int func_ov049_0226262c(void *self)
{
    int size = func_02016104((char *) self + 0x658);
    int ret = 0;
    if (size != 0) {
        ret = func_0201c314(self, size);
    }
    func_020147fc((char *) self + 0x618, 0, ret, 1);
    return 1;
}

int func_ov049_022625fc(void *self)
{
    if (func_02014868((char *) self + 0x618) == 0) {
        func_020b6098(func_020b5e10(), 0);
        func_ov049_02262a94(self, 6);
    }
    return 1;
}

int func_ov049_022625f8(void)
{
    return 1;
}

int func_ov049_022625f4(void)
{
    return 1;
}

int func_ov049_022625c0(void *arg)
{
    func_02019d0c((char *) arg + 0x564, 10, 1, 0, 0, 0, 0, 0, 0, (unsigned short) data_020c80f8, 0);
    return 1;
}

int func_ov049_0226256c(void *self)
{
    if (func_ov049_0226048c(self)) {
        return 1;
    }
    if (func_ov049_02260500(self)) {
        return 1;
    }
    if (func_02019e00((char *) self + 0x564) == 0xa) {
        if (func_02019de8((char *) self + 0x564)) {
            *(unsigned short *) ((char *) self + 0x972) = 0x18;
            func_ov049_02262a94(self, 1);
        }
    }
    return 1;
}

int func_ov049_02262568(void)
{
    return 1;
}

int func_ov049_02262470(UnkStruct_02262470_3 *self)
{
    u16 tmp;
    int r;
    unsigned int ok;
    int a;
    int b;

    if (func_0201c0e0(self) != 0) {
        a = 4;
        b = 4;
        if (func_0201c040(self, &a, &b) != 0 && a == data_020ccf94->unk_64 && a == b) {
            func_0201c054(self, 1, data_020ccf94->unk_64, data_020ccf94->unk_64);
            self->unk_658.vt->unk_08(&self->unk_658);
            func_02016108(&self->unk_658, func_0201c2a4(self, 4));
            if (func_0204bcdc(&self->unk_738) != 0) {
                tmp = 0xfff1;
                r = func_0204bc64(&self->unk_738);
                ok = (r == func_0204bc64(&tmp)) ? 1 : 0;
            } else {
                ok = (self->unk_738 == 0xfff1) ? 1 : 0;
            }
            if (ok != 0) {
                func_ov049_0226208c((void *) (&self->unk_658), 2);
            }
            func_ov049_02262a94((void *) self, 4);
        } else if (func_020a7278() != 0 && b == 4) {
            func_0201c054(self, 1, data_020ccf94->unk_64, 4);
            func_ov049_02262a94((void *) self, 0xa);
        }
    } else {
        func_ov049_02260500((void *) self);
    }
    return 1;
}

int func_ov049_0226246c(void)
{
    return 1;
}

int func_ov049_02262414(void *self)
{
    if (func_0201c0e0(self) != 0) {
        int a = 4;
        int b = 4;
        if (func_0201c040((UnkStruct_02262470_3 *) self, &a, &b) != 0) {
            if (a == 4) {
                if (func_020a7278() != 0) {
                    func_0201c054((UnkStruct_02262470_3 *) self, 1, (*(UnkStruct_02262414 **) &data_020ccf94)->value, 4);
                    func_ov049_02262a94(self, 0xa);
                }
            }
        }
    }
    return 1;
}

int func_ov049_022623f0(void *p)
{
    func_02019c6c((char *) p + 0x564, 1, *(unsigned short *) ((char *) p + 0x972));
    return 1;
}

int func_ov049_022623b4(SelfType *self)
{
    int result1;
    int result2;
    short diff;

    result1 = func_0201c2c8((void *) self, 4);
    result2 = func_020e8b4c(self->unk_8E, result1);
    diff = data_020c80f0[0];

    if (result2 >= diff) {
        func_ov049_02262a94((void *) self, 0xb);
    } else {
        func_ov049_02260500((void *) self);
    }
    return 1;
}

int func_ov049_02262374(char *self)
{
    int r;

    r = func_0201c2c8(self, 4);
    func_02019d0c(self + 0x564, 3, 1, 0, 0, 0, r, 0, 0, data_020c80f8, 0);
    return 1;
}

int func_ov049_02262344(void *self)
{
    if (func_02019e00((char *) self + 0x564) == 3) {
        if (func_02019de8((char *) self + 0x564) != 0) {
            func_ov049_02262a94(self, 10);
        }
    }
    return 1;
}

int func_ov049_02262340(void)
{
    return 1;
}

int func_ov049_0226233c(void)
{
    return 1;
}

int func_ov049_022622fc(struct UnkStruct_022622fc *self)
{
    self->unk_977 = 0x32;
    func_02019d0c(self->sub, 1, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
    return 1;
}
