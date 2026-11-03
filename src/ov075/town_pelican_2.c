/* town_pelican_2: 17 functions, module ov075
 * mwccarm 1.2/base -O4,s
 * func_ov075_0227944c @ 0x0227944c, 0x6c bytes, Thumb
 * func_ov075_02279448 @ 0x02279448, 0x4 bytes, Thumb
 * func_ov075_02279438 @ 0x02279438, 0x10 bytes, Thumb
 * func_ov075_022793e4 @ 0x022793e4, 0x54 bytes, Thumb
 * func_ov075_02279364 @ 0x02279364, 0x80 bytes, Thumb
 * func_ov075_0227930c @ 0x0227930c, 0x58 bytes, Thumb
 * func_ov075_022792d4 @ 0x022792d4, 0x38 bytes, Thumb
 * func_ov075_02279244 @ 0x02279244, 0x90 bytes, Thumb
 * func_ov075_02279208 @ 0x02279208, 0x3a bytes, Thumb
 * func_ov075_02279108 @ 0x02279108, 0x100 bytes, Thumb
 * func_ov075_022790e4 @ 0x022790e4, 0x22 bytes, Thumb
 * func_ov075_02278ecc @ 0x02278ecc, 0x218 bytes, Thumb
 * func_ov075_02278e44 @ 0x02278e44, 0x88 bytes, Thumb
 * func_ov075_02278e40 @ 0x02278e40, 0x4 bytes, Thumb
 * func_ov075_02278e18 @ 0x02278e18, 0x28 bytes, Thumb
 * func_ov075_02278dec @ 0x02278dec, 0x2c bytes, Thumb
 * func_ov075_02278de8 @ 0x02278de8, 0x4 bytes, Thumb
 */

#include "types.h"

struct Vec3 {
    u32 x, y, z;
};

struct UnkStruct_022793e4 {
    u8 pad_00[0x5c];
    struct Vec3 src; // offset 0x5c
    struct Vec3 dst; // offset 0x68
    u8 pad_74[0x4ed];
    u8 flag; // offset 0x561
};

typedef struct UnkStruct_02279364 {
    char pad_00[0x3b0];
    char unk_3B0;
    char pad_3B1[0x1a7];
    char unk_558;
    char pad_559[0xb];
    char unk_564;
    char pad_565[0x1b4];
    char unk_719;
} UnkStruct_02279364;

struct UnkStruct_0227930c {
    int unk_00;
    int unk_04;
    int unk_08;
};

struct UnkStruct_02279244 {
    char pad_00[0x5c];
    int unk_5C;
    char pad_60[4];
    int unk_64;
};

typedef struct UnkStruct_02278ecc {
    char pad_00[0x5c];
    char unk_5C[0x8e - 0x5c];
    short unk_8E;
    char pad_90[0x98 - 0x90];
    int unk_98;
    char pad_9C[0x350 - 0x9c];
    char unk_350[0x3aa - 0x350];
    char unk_3AA[0x564 - 0x3aa];
    char unk_564[0x719 - 0x564];
    unsigned char unk_719;
} UnkStruct_02278ecc;

struct UnkStruct_02278e44 {
    char pad_00[0x8e];
    short unk_8E;
    char pad_90[0x3b0 - 0x90];
    char unk_3B0[0x4e8 - 0x3b0];
    int unk_4E8;
    char pad_4EC[0x618 - 0x4ec];
    char unk_618[0x658 - 0x618];
    char unk_658[0x718 - 0x658];
    unsigned char unk_718;
};

extern void func_0201ad18(void *a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8);
extern int func_02019c20(void *a1, int a2, int a3, int a4, int a5, int a6);
extern void func_0201b38c(void *a1, int a2);
extern int data_020c814c;
extern unsigned short data_020c80f8;
extern unsigned char data_021fbee8[];
extern int func_0208602c(void);
extern int func_020860c0(int);
extern int func_02087e38(int);
extern void func_02087e4c(int, struct Vec3 *);
extern void func_ov075_022794b8(struct UnkStruct_022793e4 *, int);
int func_02019d0c(void *a, int b, int c, int d, int e, int f, int g, int h, int i, int j, int k);
void func_02013c0c(void *a);
extern int data_021c67a4;
extern int data_021c67d0[3];
extern int func_020e92e8(void *);
extern int FX_MulFunc(int, int);
extern void func_0204f7e0(int *, int *);
extern int func_02078e98(int *, int);
extern short FX_SinCosTable_[];
extern int data_021cb5a0;
extern void func_0201af58(void *out, void *in, int a, int b);
extern int func_0201ae8c(void *ptr);
extern void *func_0201ae40(void *p);
extern int func_0201aff8(void *p, void *self, int flag);
extern int func_0201afc0(void *p);
extern void func_0201af48(void *p);
extern void func_0201afd4(void *p, void *buf);
extern char data_ov075_02279afc;
extern char data_ov075_02279af0;
extern unsigned char func_020e8858(unsigned char *p);
extern int func_02019de8(void *p);
extern int func_0201b354(void *p);
extern int func_0200322c(void *p, int *v);
extern int func_0201c3dc(int a);
extern int func_020644cc(int a);
extern int func_02019e00(void *p);
extern int *func_0201afd0(void *p);
extern int func_02016104(void *);
extern int func_0201c314(void *, int);
extern int func_020147fc(void *, int, int, int);
extern int func_020147e0(void *dst, void *src, int size);
extern int func_02014868(void *);
extern int func_0203e020(void *);

int func_ov075_0227944c(void *param)
{
    func_0201ad18((char *) param + 0x3b0, 0, 0, 0, (unsigned int) data_021fbee8, 4, data_020c814c, 1);
    func_02019c20((char *) param + 0x564, 1, 0xef, 1, data_020c80f8, 0);
    func_0201b38c((char *) param + 0x2a0, 0xef);
    return 1;
}

int func_ov075_02279448(void)
{
    return 1;
}

int func_ov075_02279438(unsigned char *p)
{
    p[0x561] = 0;
    return 1;
}

int func_ov075_022793e4(struct UnkStruct_022793e4 *obj)
{
    int a, b, c;
    u32 *src;
    u32 *dst;

    a = func_0208602c();
    b = func_020860c0(a);
    c = func_02087e38(b);
    if (c != 0) {
        func_02087e4c(b, &obj->src);
        src = (u32 *) &obj->src;
        dst = (u32 *) &obj->dst;
        obj->dst.x = obj->src.x;
        dst[1] = src[1];
        dst[2] = src[2];
        obj->flag = 1;
        func_ov075_022794b8(obj, 0);
    }
    return 1;
}

int func_ov075_02279364(UnkStruct_02279364 *self)
{
    self->unk_719 = 0;
    func_02019d0c(&self->unk_564, 0, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
    func_02013c0c(&self->unk_558);
    func_02013c0c(&self->unk_558);
    func_0201ad18(&self->unk_3B0, 1, 0, 0, (unsigned int) ((char *) data_021fbee8), 4, (*(unsigned int *) &data_020c814c), 1);
    return 1;
}

int func_ov075_0227930c(int unused, struct UnkStruct_0227930c *p1, struct UnkStruct_0227930c *p2)
{
    int result = 0;
    unsigned int second_flag = 0;
    unsigned int first_flag = 0;
    int f0a = p1->unk_00;
    int f0b = p2->unk_00;

    if (f0b > f0a - 0x10000 && f0b < f0a + 0x10000) {
        first_flag = 1;
    }
    if (first_flag > 0) {
        int f8a = p1->unk_08;
        int f8b = p2->unk_08;
        if (f8b > f8a - 0x1a000) {
            second_flag = 1;
        }
    }
    if (second_flag > 0) {
        int f8a2 = p1->unk_08;
        int f8b2 = p2->unk_08;
        if (f8b2 < f8a2 + 0xa000) {
            result = 1;
        }
    }
    return result;
}

int func_ov075_022792d4(void *self)
{
    int local[3];
    void *p = (char *) self + 0x5c;
    int result = 0;
    if (data_021c67a4) {
        local[0] = data_021c67d0[0];
        local[1] = data_021c67d0[1];
        local[2] = data_021c67d0[2];
        result = func_ov075_0227930c((int) self, (struct UnkStruct_0227930c *) local, (struct UnkStruct_0227930c *) p);
    }
    return result;
}

int func_ov075_02279244(struct UnkStruct_02279244 *self, int *out1, int *out2)
{
    int r4;
    int r6;
    int r7;
    int local[3];
    int t1, t2;
    r6 = 0;
    local[0] = r6;
    local[1] = r6;
    local[2] = r6;
    r4 = r6;
    while (r4 < 6) {
        r7 = ((unsigned short) (short) func_020e92e8(&data_021cb5a0) >> 4) << 1;
        t1 = FX_MulFunc(0xc000, FX_SinCosTable_[r7]);
        local[0] = t1 + self->unk_5C;
        t2 = FX_MulFunc(0xc000, FX_SinCosTable_[r7 + 1]);
        local[2] = t2 + self->unk_64;
        func_0204f7e0(local, local);
        if (func_02078e98(local, r6) != 0) {
            *out1 = local[0];
            *out2 = local[2];
            r6 = 1;
            break;
        }
        r4++;
    }
    return r6;
}

int func_ov075_02279208(void *p, int *q, int param)
{
    int local[4];
    int result = 0;

    func_0201af58(local, (char *) p + 0x5c, param, *(short *) ((char *) p + 0x94));
    if (func_0201ae8c(local) != 1) {
        q[0] = local[0];
        q[1] = local[1];
        q[2] = local[2];
        result = 1;
    }
    return result;
}

int func_ov075_02279108(void *self)
{
    void *a = (char *) self + 0x564;
    void *b = (char *) self + 0x350;
    void *c = (char *) self + 0x3a8;
    int kind;
    int result;
    char buf[0xc];

    kind = (int) func_0201ae40(c);
    result = 0;
    if (func_0201aff8(b, self, 1) == 0) {
        if (kind == 1) {
            goto case1;
        }
        if (kind == 2) {
            goto case2;
        }
        if (kind != 3) {
            goto done;
        }
        func_02019d0c(a, 0, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
        result = 1;
        goto done;
    case1:
        if (func_ov075_02279208(self, (int *) buf, (int) (&data_ov075_02279afc))) {
            func_0201afd4(b, buf);
        } else {
            func_02019d0c(a, 0, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
        }
        result = 1;
        goto done;
    case2:
        if (func_ov075_02279208(self, (int *) buf, (int) (&data_ov075_02279af0))) {
            func_0201afd4(b, buf);
        } else {
            func_02019d0c(a, 0, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
        }
        result = 1;
        goto done;
    } else {
        if (func_0201afc0(b)) {
            func_0201af48(b);
        }
    }
done:
    return result;
}

int func_ov075_022790e4(void *self)
{
    if (*(int *) ((char *) self + 0x98) != 0) {
        if (func_ov075_02279108(self)) {
            return 1;
        }
    }
    return 0;
}

static __inline int GetState(UnkStruct_02278ecc *self)
{
    return func_02019e00(self->unk_564);
}

int func_ov075_02278ecc(UnkStruct_02278ecc *self)
{
    void *sub;
    int ok;
    int dir;
    int mode;
    int *p;
    int v[3];
    int v2[3];

    sub = self->unk_564;
    ok = func_ov075_022792d4((void *) self);
    func_020e8858(&self->unk_719);
    if (ok != 0) {
        if (func_ov075_022790e4((void *) self) == 0) {
            if (func_02019de8(sub) != 0) {
                if (func_0201b354(self->unk_3AA) == 2) {
                    func_02019d0c(sub, 0, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
                } else if ((func_020e92e8((void *) (&data_021cb5a0)) & 7) == 0) {
                    v[0] = ((int *) data_021fbee8)[0];
                    v[1] = ((int *) data_021fbee8)[1];
                    v[2] = ((int *) data_021fbee8)[2];
                    if (func_ov075_02279244((struct UnkStruct_02279244 *) self, v, &v[2]) != 0) {
                        dir = func_0200322c(self->unk_5C, v);
                        if (func_0201c3dc((short) (dir - self->unk_8E)) != 0) {
                            mode = 1;
                            if (func_020644cc(4) == 0) {
                                mode = 2;
                            }
                            func_02019d0c(sub, mode, 1, v[0], v[2], 0, 0, 0, 0, data_020c80f8, 0);
                            self->unk_719 = 0x64;
                        } else {
                            func_02019d0c(sub, 4, 1, v[0], v[2], 0, dir, 0, 0, data_020c80f8, 0);
                            self->unk_719 = 0x50;
                        }
                    } else {
                        func_02019d0c(sub, 0, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
                    }
                } else {
                    func_02019d0c(sub, 0, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
                }
            } else {
                if (self->unk_98 != 0) {
                    if (GetState(self) == 1 || GetState(self) == 2 || GetState(self) == 4) {
                        if (self->unk_719 == 0) {
                            func_02019d0c(sub, 0, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
                        } else {
                            p = func_0201afd0(self->unk_350);
                            v2[0] = p[0];
                            v2[1] = p[1];
                            v2[2] = p[2];
                            if (func_0201c3dc((short) (func_0200322c(self->unk_5C, v2) - self->unk_8E)) == 0) {
                                func_02019d0c(sub, 0, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
                            }
                        }
                    }
                }
            }
        }
    }
    return 0;
}

int func_ov075_02278e44(struct UnkStruct_02278e44 *self)
{
    int result = func_02016104(self->unk_658);
    int s = self->unk_8E;
    if (self->unk_718 != 0) {
        func_0201ad18(self->unk_3B0, 1, 0, 0, (unsigned int) data_021fbee8, 4, data_020c814c, 1);
        self->unk_4E8 &= ~2;
    }
    if (result != 0) {
        s = func_0201c314(self, result);
    }
    func_020147fc(self->unk_618, 0, s, 0);
    return 1;
}

int func_ov075_02278e40(void)
{
    return 1;
}

int func_ov075_02278e18(void *self)
{
    if (*(unsigned char *) ((char *) self + 0x718) == 0) {
        func_020147e0((char *) self + 0x618, 0, 0);
    }
    return 1;
}

int func_ov075_02278dec(void *self)
{
    if (!func_02014868((char *) self + 0x618)) {
        func_0203e020(self);
        func_ov075_022794b8((struct UnkStruct_022793e4 *) self, 3);
    }
    return 1;
}

int func_ov075_02278de8(void)
{
    return 1;
}
