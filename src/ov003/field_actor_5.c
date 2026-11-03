/* field_actor_5: 7 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_0220d2d0 @ 0x0220d2d0, 0x140 bytes, Thumb
 * func_ov003_0220d2a4 @ 0x0220d2a4, 0x2a bytes, Thumb
 * func_ov003_0220d268 @ 0x0220d268, 0x3c bytes, Thumb
 * func_ov003_0220d1a8 @ 0x0220d1a8, 0xc0 bytes, Thumb
 * func_ov003_0220d040 @ 0x0220d040, 0x168 bytes, Thumb
 * func_ov003_0220cf68 @ 0x0220cf68, 0xd8 bytes, Thumb
 * func_ov003_0220ced4 @ 0x0220ced4, 0x94 bytes, Thumb
 */

#include "types.h"

typedef struct {
    int x, y, z;
} VecFx32;

typedef struct UnkStruct_0220d268 {
    char pad_00[0x7f0];
    int unk_7F0;
    char pad_7F4[8];
    int unk_7FC;
} UnkStruct_0220d268;

typedef struct {
    u8 pad_00[0x5c];
    u8 sub5c[0x32];
    u8 sub8e[0xca];
    int unk_158;
    int unk_15C;
    int unk_160;
    u8 pad_164[0x0c];
    int unk_170;
} UnkStruct_0220d1a8;

extern int func_ov003_0222a938(void *o);
extern VecFx32 *func_ov003_0222a918(void *o);
extern int func_020e8ed8(int a, int b);
extern int func_020ea990(VecFx32 *a, VecFx32 *b);
extern int func_02095518(int a, int b, void *o);
extern int func_02011404(void *p, int a, int b, int c, int d);
extern int func_02008258(u8 *self, int a);
extern int func_0200c9a8(u8 *self, int a, int b, int c);
extern int func_0200d4e8(u8 *self, int a, int b, int c);
extern void func_02010f5c(int argument0);
extern int func_0200f554(void *);
extern int func_0201100c(void *);
extern void func_02010d64(void *);
extern int func_02010718(UnkStruct_0220d268 *obj);
extern int func_0200d1a0(UnkStruct_0220d268 *obj, int a, int b, int c);
extern int func_02010538(UnkStruct_0220d268 *obj);
extern void func_0200fa1c(int *dst, void *self, const u8 *a, const u8 *b, const u8 *data);
extern int func_0201005c(void *self, int *data, int len);
extern int func_0200ff28(void *self, int *data, int mode, int val);
extern int func_0200fd04(void *self, int *data, int mode);
extern u8 data_ov003_02236608[];
extern void *data_021c80bc;
extern int func_ov003_0220c934(void *self);
extern void func_0200fa6c(int *dst, void *self);
extern void func_0204f818(int *a, int *b, int *local);
extern int func_020310d0(int *local, int *v, int c);
extern u16 *func_0204f5a8(void *g, int *local, int zero);
extern int func_0200fdd0(void *self, int *t, int c, u8 p2);
extern int func_020eaa6c(void *p, void *q);
extern int func_02031614(void *p);
extern char data_ov003_02238124[];
extern char data_ov003_0223810c[];

void func_ov003_0220d2d0(u8 *self)
{
    VecFx32 a;
    VecFx32 b;
    u8 *p;
    void *o;
    VecFx32 *v;
    VecFx32 *w;
    int ang;
    int e;
    int d;
    u16 t;

    p = self + 0x7d4;
    if (*p == 0) {
        return;
    }
    o = *(void **) (self + 0x800);
    if (func_ov003_0222a938(o) != 0) {
        v = func_ov003_0222a918(o);
        a.x = v->x;
        a.y = v->y;
        a.z = v->z;
        w = (VecFx32 *) (self + 0x5c);
        b.x = w->x;
        b.y = w->y;
        b.z = w->z;
        b.y = b.y + 0x1b33;
        ang = func_020e8ed8(a.x - b.x, a.z - b.z);
        d = func_020ea990(&a, &b);
        e = func_020e8ed8(a.y - b.y, d);
        if (e >= 0x1800) {
            e = 0x1800;
        } else if (e <= -0x1000) {
            e = -0x1000;
        }
        ang = (s16) (ang - *(s16 *) (self + 0x8e));
        t = (u16) (ang + 0x2aaa);
        if (t >= 0x5554) {
            func_02095518(0, 0, *(void **) (self + 0x800));
        } else {
            func_02011404(self + 0x45c, e, 0x400, 0x1770000, 0xc0000);
            func_02011404(self + 0x45e, ang, 0x400, 0x1770000, 0xc0000);
        }
    } else {
        func_02095518(0, 0, *(void **) (self + 0x800));
        *(int *) (self + 0x7fc) = func_02008258(self, *(int *) (self + 0x7f0));
        if (p[1] != 0) {
            func_0200c9a8(self, 3, 5, -1);
        } else {
            func_0200d4e8(self, 3, 1, -1);
        }
    }
}

void func_ov003_0220d2a4(void *p)
{
    func_02010f5c((int) p);
    if (func_0200f554(p)) {
        func_0201100c(p);
    }
    func_02010d64(p);
    func_ov003_0220d2d0((u8 *) p);
}

int func_ov003_0220d268(UnkStruct_0220d268 *obj)
{
    if (func_02010718(obj) > 0) {
        obj->unk_7FC = func_02008258((u8 *) obj, obj->unk_7F0);
        return func_0200d1a0(obj, 0, 1, -1);
    } else {
        return func_02010538(obj);
    }
}

int func_ov003_0220d1a8(UnkStruct_0220d1a8 *self, int *param)
{
    int triplet[3];
    int gen[3];

    if (self->unk_170 == 1) {
        func_0200fa1c(gen, self, self->sub5c, self->sub8e, data_ov003_02236608);
        triplet[0] = gen[0];
        triplet[1] = gen[1];
        triplet[2] = gen[2];

        if (func_0201005c(self, triplet, 0xd) != 0 && func_0200ff28(self, triplet, 2, *param) != 0 &&
            func_0200fd04(self, triplet, 0) != 0) {
            return 1;
        }
    } else {
        triplet[0] = self->unk_158;
        triplet[1] = self->unk_15C;
        triplet[2] = self->unk_160;

        if (func_0201005c(self, triplet, 0xd) != 0 && func_0200ff28(self, triplet, 2, *param) != 0 &&
            func_0200fd04(self, triplet, 0) != 0) {
            return 1;
        }
    }

    return 0;
}

int func_ov003_0220d040(void *self, u8 *p1, u8 *p2, int *out)
{
    int out0;
    int out1;
    int v;
    int temp[2];
    int local[4];
    int r7;
    int r4 = 1;

    if (*p1 != 0) {
        if (func_ov003_0220c934(self) != 0) {
            return 4;
        }
    }

    func_0200fa6c(local, self);
    func_0204f818(&out0, &out1, local);
    if (out != 0) {
        out[0] = out0;
        out[1] = out1;
    }

    r7 = func_020310d0(local, &v, 0x19);

    if (v != 4) {
        if (v != 6) {
            goto label_0x220d182;
        }

        if (data_021c80bc != 0) {
            u16 *p = func_0204f5a8(data_021c80bc, local, 0);
            int r3 = 1;
            int r2 = r3;
            int r6 = r3;
            int r1 = 0;
            u16 val = *p;

            if (val >= 0x2b && val <= 0x2e) {
                r1 = r3;
            }
            if (r1 == 0) {
                if (val < 0xff || val > 0x102) {
                    r6 = 0;
                }
            }
            if (r6 == 0) {
                if (val < 0x62 || val > 0x65) {
                    r2 = 0;
                }
            }
            if (r2 == 0) {
                if (val < 0xd0 || val > 0xd3) {
                    r3 = 0;
                }
            }
            if (r3 != 0) {
                return 1;
            }
        }
    }

    if (*p1 != 0) {
        if (r7 < 0x1000) {
            return 1;
        }
        temp[0] = 0;
        temp[1] = 0;
        temp[0] = out0;
        temp[1] = out1;
        switch (func_0200fdd0(self, temp, 1, *p2)) {
            case 0:
                return 5;
            case 1:
                return 0;
            case 2:
                return 4;
            default:
                break;
        }
    }

    if (*(int *) ((char *) self + 0x818) == 1) {
        switch (*(int *) ((char *) self + 0x814)) {
            case 6:
                r4 = 2;
                break;
            case 7:
                r4 = 3;
                break;
            case 12:
            case 13:
                r4 = 4;
                break;
            case 14:
                r4 = 6;
                break;
            default:
                break;
        }
    } else if (*(int *) ((char *) self + 0x818) == 2) {
        r4 = 5;
    } else {
        r4 = 0;
    }
    goto return_r4;

label_0x220d182:
    if (r7 >= 0x1000) {
        r4 = 4;
    }

return_r4:
    return r4;
}

int func_ov003_0220cf68(int a, int b, unsigned char *c)
{
    int x;
    int y;
    int t[2];

    func_0204f818(&x, &y, (int *) b);
    if (*c) {
        if (func_ov003_0220c934((void *) a)) {
            return 2;
        }
        t[0] = 0;
        t[1] = 0;
        t[0] = x;
        t[1] = y;
        switch (func_0200fdd0((void *) a, t, 2, 3)) {
            case 0:
                return 7;
            case 1:
                return 0;
            case 2:
                return 2;
        }
    }
    if (*(int *) ((char *) a + 0x818) == 2) {
        return 7;
    }
    if (*(int *) ((char *) a + 0x818) == 0) {
        return 0;
    }
    switch (*(int *) ((char *) a + 0x814)) {
        case 23:
            return 1;
        case 12:
        case 13:
            return 2;
        case 14:
            return 8;
        case 19:
        case 20:
            return 6;
        case 9:
        case 21:
            return 5;
        case 10:
        case 22:
            return 9;
        case 11:
            return 4;
        case 8:
        default:
            return 3;
    }
}

int func_ov003_0220ced4(void *p1, void *p2, void *p3)
{
    short local_short;
    int buf2[3];
    int buf1[3];
    int ret;

    if (func_020eaa6c(p3, (char *) p1 + 0x5c) != 0) {
        local_short = *(short *) ((char *) p1 + 0x8e);
    } else {
        local_short = (short) func_020e8ed8(*(int *) p3 - *(int *) ((char *) p1 + 0x5c),
                                            *(int *) ((char *) p3 + 8) - *(int *) ((char *) p1 + 0x64));
    }

    func_0200fa1c((int *) buf1, p1, (const u8 *) ((char *) p1 + 0x5c), (const u8 *) (&local_short), (const u8 *) data_ov003_02238124);
    ((int *) p2)[0] = buf1[0];
    ((int *) p2)[1] = buf1[1];
    ((int *) p2)[2] = buf1[2];

    ret = func_02031614(p2);

    func_0200fa1c((int *) buf2, p1, (const u8 *) ((char *) p1 + 0x5c), (const u8 *) (&local_short), (const u8 *) data_ov003_0223810c);

    if (ret != 0) {
        if (func_02031614(buf2) != 0) {
            return 1;
        }
    }
    return 0;
}
