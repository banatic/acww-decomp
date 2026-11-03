/* birthday_villager_3: 21 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0221d1d8 @ 0x0221d1d8, 0x38 bytes, Thumb
 * func_ov004_0221d1a8 @ 0x0221d1a8, 0x30 bytes, Thumb
 * func_ov004_0221d188 @ 0x0221d188, 0x20 bytes, Thumb
 * func_ov004_0221d0c8 @ 0x0221d0c8, 0xc0 bytes, Thumb
 * func_ov004_0221d08c @ 0x0221d08c, 0x3c bytes, Thumb
 * func_ov004_0221d068 @ 0x0221d068, 0x24 bytes, Thumb
 * func_ov004_0221d050 @ 0x0221d050, 0x16 bytes, Thumb
 * func_ov004_0221d02c @ 0x0221d02c, 0x24 bytes, Thumb
 * func_ov004_0221d014 @ 0x0221d014, 0x16 bytes, Thumb
 * func_ov004_0221cff8 @ 0x0221cff8, 0x1a bytes, Thumb
 * func_ov004_0221cfe0 @ 0x0221cfe0, 0x16 bytes, Thumb
 * func_ov004_0221cf00 @ 0x0221cf00, 0xe0 bytes, Thumb
 * func_ov004_0221cee4 @ 0x0221cee4, 0x1a bytes, Thumb
 * func_ov004_0221cec8 @ 0x0221cec8, 0x1a bytes, Thumb
 * func_ov004_0221ceac @ 0x0221ceac, 0x1c bytes, Thumb
 * func_ov004_0221cd68 @ 0x0221cd68, 0x144 bytes, Thumb
 * func_ov004_0221cd48 @ 0x0221cd48, 0x20 bytes, Thumb
 * func_ov004_0221cc14 @ 0x0221cc14, 0x134 bytes, Thumb
 * func_ov004_0221cb28 @ 0x0221cb28, 0xec bytes, Thumb
 * func_ov004_0221cae4 @ 0x0221cae4, 0x44 bytes, Thumb
 * func_ov004_0221ca04 @ 0x0221ca04, 0xe0 bytes, Thumb
 */

#include "types.h"

#define OBJ (*(UnkStruct_0221cc14 **) (self + 0x1a4))

typedef struct {
    char pad_00[0x830];
    int unk_830;
} UnkStruct_0221d1d8;

struct UnkStruct_0221d1a8 {
    u8 pad_00[0x618];
    u8 sub[0x898 - 0x618];
    int phase;
};

typedef struct {
    int x, y, z;
} Vec3;

struct UnkStruct_0221d08c_2 {
    u8 pad_00[0x830];
    int handle;
};

struct UnkStruct_0221d08c {
    u8 pad_00[0x1a4];
    struct UnkStruct_0221d08c_2 *sub;
};

typedef struct {
    char pad_00[0x1a4];
    int unk_1A4;
} UnkStruct_0221cd48;

typedef struct {
    char pad_00[0x830];
    void *unk_830;
    char pad_834[0x898 - 0x834];
    int unk_898;
    char pad_89C[0x8a0 - 0x89c];
    char unk_8A0;
    char pad_8A1[0x8e0 - 0x8a1];
    int unk_8E0;
} UnkStruct_0221cc14;

typedef struct {
    int a, b;
} UnkStruct_0221cb28;

extern int func_020984e8(void);
extern int func_02099870(int arg);
extern int func_020804b8(int arg1, int arg2);
extern void func_02081e14(int arg1, int arg2, int arg3, int arg4);
extern int func_02014868(void *p);
extern int func_ov004_0221c844(void *s, int a);
extern int func_0201c2a4(void *s, int a);
extern void func_02016108(void *p, int a);
extern int func_0203af80(Vec3 *v);
extern int func_0203b144(void);
extern int func_0208194c(void *object);
extern void func_02081974(unsigned short *argument0);
extern int func_020819bc(void *object);
extern void func_020819e0(unsigned short *argument0);
extern int func_02081988(void *argument0);
extern void func_020819ac(void *argument0);
extern int func_0207f1c8(int a);
extern int func_0209b5ec(int a);
extern unsigned int func_0209c330(int a);
extern int func_0204bcdc(u16 *w);
extern int func_02081cec(void *argument0, int argument1);
extern int func_02081d20(void *argument0);
extern int func_0206fbc0(void);
extern int func_0206fc6c(void);
extern void *func_0206fc8c(void);
extern int func_020644cc(int k);
extern void func_0206844c(void *a, void *b, int c);
extern int func_0209a034(void *h);
extern int func_0204c878(void *obj);
extern void func_0209a050(void *h);
extern int func_02015330(void *self, void *obj, int a, int b, int c);
extern void func_0202dc3c(void *ptr, int value, int count);
extern void *func_0208150c(void *);
extern int func_0200366c(void *a, void *b, int c, void *d);
extern void *func_020826a8(int i);
extern int func_020826cc(void);
extern void func_02015e10(void *addr, void *a, int flag);
extern void func_02015de4(void *self, u16 *buf, int a, int b);
extern char data_ov004_02257a6c;
extern char data_ov004_02253734;
extern void func_02063ccc(UnkStruct_0221cb28 *t, int a, int b);
extern void func_02063cc8(UnkStruct_0221cb28 *t);
extern void func_020638d4(u16 *dst, UnkStruct_0221cb28 *t, int a, int b, int c, int d, int e);
extern void func_020630bc(u16 *dst, int v, int b);
extern u8 data_021f43e8;
extern int func_02068484(int h, u8 *p, int k);
extern int func_020154b4(void *s, void *p, int a, int b, int c);
extern int func_0209a000(void *p, int a);

void func_ov004_0221d1d8(UnkStruct_0221d1d8 *param)
{
    int a;
    int b;
    int c;

    a = func_020984e8();
    if (a == 0) {
        return;
    }
    if (param->unk_830 == 0) {
        return;
    }
    b = func_02099870(a);
    c = func_020804b8(param->unk_830, b);
    func_02081e14(c, 0, 0, 0);
}

int func_ov004_0221d1a8(struct UnkStruct_0221d1a8 *self)
{
    if (func_02014868(&self->sub)) {
        return 0;
    }
    if (self->phase <= 3) {
        return 1;
    }
    return 0;
}

int func_ov004_0221d188(int arg0)
{
    int result;
    int ret;

    result = func_02014868((void *) (arg0 + 0x618));
    if (result == 0) {
        ret = 1;
    } else {
        ret = 0;
    }
    return ret;
}

void func_ov004_0221d0c8(char *s, unsigned int sel, int a2)
{
    Vec3 v;
    v.x = *(int *) (s + 0x5c);
    v.y = *(int *) (s + 0x60);
    v.z = *(int *) (s + 0x64);
    v.y = v.y + 0x2000;
    switch (sel) {
        case 3:
            *(u8 *) (s + 0x560) = (u8) a2;
            func_ov004_0221c844(s, 4);
            break;
        case 0:
            *(u8 *) (s + 0x560) = (u8) a2;
            func_02016108(s + 0x8a0, func_0201c2a4(s, 4));
            func_0203af80(&v);
            func_ov004_0221c844(s, 5);
            break;
        case 1:
            *(u8 *) (s + 0x560) = (u8) a2;
            func_02016108(s + 0x8a0, func_0201c2a4(s, 4));
            func_0203af80(&v);
            func_ov004_0221c844(s, 8);
            break;
        case 8:
            func_0203b144();
            func_ov004_0221d1d8((UnkStruct_0221d1d8 *) s);
            func_ov004_0221c844(s, 0);
            break;
        case 4:
            func_ov004_0221c844(s, 0);
            break;
    }
}

int func_ov004_0221d08c(struct UnkStruct_0221d08c *self)
{
    if (self->sub != 0 && self->sub->handle != 0) {
        return func_020804b8(self->sub->handle, func_02099870(func_020984e8()));
    }
    return 0;
}

int func_ov004_0221d068(void *arg0)
{
    int object;
    if ((object = func_ov004_0221d08c((struct UnkStruct_0221d08c *) ((void *) arg0))) != 0) {
        if (func_0208194c((void *) object) == 0) {
            return 1;
        }
        return 0;
    }
    return 0;
}

void func_ov004_0221d050(void *arg0)
{
    unsigned short *conditionInput0;

    if ((conditionInput0 = (unsigned short *) (func_ov004_0221d08c((struct UnkStruct_0221d08c *) ((void *) arg0)))) != 0) {
        func_02081974((unsigned short *) conditionInput0);
    }
}

int func_ov004_0221d02c(void *arg0)
{
    int object;
    if ((object = func_ov004_0221d08c((struct UnkStruct_0221d08c *) ((void *) arg0))) != 0) {
        if (func_020819bc((void *) object) == 0) {
            return 1;
        }
        return 0;
    }
    return 0;
}

void func_ov004_0221d014(void *arg0)
{
    unsigned short *conditionInput0;

    if ((conditionInput0 = (unsigned short *) (func_ov004_0221d08c((struct UnkStruct_0221d08c *) ((void *) arg0)))) != 0) {
        func_020819e0((unsigned short *) conditionInput0);
    }
}

int func_ov004_0221cff8(char *self)
{
    // DECLS
    int v1;
    // ENDDECLS
    v1 = func_ov004_0221d08c((struct UnkStruct_0221d08c *) ((void *) self));
    if (v1 != 0x0) {
        return func_02081988((void *) (v1));
    }
    return 0x0;
}

void func_ov004_0221cfe0(void *arg0)
{
    void *conditionInput0;

    if ((conditionInput0 = (void *) (func_ov004_0221d08c((struct UnkStruct_0221d08c *) ((void *) arg0)))) != 0) {
        func_020819ac((void *) conditionInput0);
    }
}

int func_ov004_0221cf00(char *s, u16 *w)
{
    char *p;
    unsigned int k;
    int r;
    int t;
    p = (char *) *(int *) (s + 0x1a4);
    if (p != 0) {
        if (*(int *) (p + 0x830) != 0) {
            k = func_0209c330(func_0209b5ec(func_0207f1c8(*(int *) (p + 0x830))));
            r = 0;
            switch (k) {
                case 0:
                    if (*w >= 0x12b0 && *w <= 0x12e7) {
                        r = 1;
                    }
                    break;
                case 1:
                    if (*w >= 0x12e8 && *w <= 0x131f) {
                        r = 1;
                    }
                    break;
                case 2:
                    if (*w >= 0x450c && *w <= 0x45db) {
                        r = 1;
                    }
                    break;
                case 3:
                    if (*w >= 0x11a8 && *w <= 0x12a7) {
                        r = 1;
                    }
                    break;
                case 4:
                    if (func_0204bcdc(w) != 0) {
                        t = r;
                        if (*w >= 0x450c && *w <= 0x45db) {
                            t = 1;
                        }
                        if (t == 0) {
                            r = 1;
                        }
                    }
                    break;
            }
            return r;
        }
    }
    return 0;
}

int func_ov004_0221cee4(char *self, int a1)
{
    // DECLS
    int v1;
    // ENDDECLS
    v1 = func_ov004_0221d08c((struct UnkStruct_0221d08c *) ((void *) ((void *) (self))));
    if (v1 != 0x0) {
        return func_02081cec((void *) (v1), (int) ((char) a1));
    }
    return v1;
}

int func_ov004_0221cec8(char *self)
{
    // DECLS
    int v1;
    // ENDDECLS
    v1 = func_ov004_0221d08c((struct UnkStruct_0221d08c *) ((void *) self));
    if (v1 != 0x0) {
        return func_02081d20((void *) (v1));
    }
    return 0x0;
}

void func_ov004_0221ceac(char *self)
{
    // DECLS
    // ENDDECLS
    if (*(int *) ((char *) *(int *) (self + 0x1a4) + 0x898) == 0xc) {
        *(int *) ((char *) *(int *) (self + 0x40) + 0x8) = 0x1;
    }
}

void func_ov004_0221cd68(void *self)
{
    unsigned char b[4];
    char obj[8];
    int n;
    void *h;

    if (*(int *) ((char *) *(void **) ((char *) self + 0x1a4) + 0x898) == 0xb && func_0206fbc0() != 0) {
        if (func_0206fc6c() == 0) {
            *(int *) ((char *) *(void **) ((char *) self + 0x40) + 8) = 1;
            b[0] = (unsigned char) (func_020644cc(2) + 7);
            func_0206844c(*(void **) ((char *) self + 0x40), &b[0], 0);
            func_ov004_0221c844(*(void **) ((char *) self + 0x1a4), 6);
        } else {
            h = func_0206fc8c();
            *(short *) obj = (short) func_0209a034(h);
            n = func_0204c878(obj);
            func_0209a050(h);
            func_02015de4(self, (u16 *) obj, 0, 7);
            if (func_ov004_0221cf00((char *) self, (u16 *) obj) != 0) {
                b[1] = (unsigned char) (func_020644cc(2) + 0xd);
                func_0206844c(*(void **) ((char *) self + 0x40), &b[1], 0);
                func_ov004_0221cee4((char *) self, 5);
                if (n >= 0x3e8) {
                    func_ov004_0221cee4((char *) self, 5);
                }
                if (n >= 0x7d0) {
                    func_ov004_0221cee4((char *) self, 0xa);
                }
                func_02015330(self, obj, 0, 5, 0);
                func_ov004_0221c844(*(void **) ((char *) self + 0x1a4), 0xc);
            } else {
                b[2] = (unsigned char) (func_020644cc(2) + 0xb);
                func_0206844c(*(void **) ((char *) self + 0x40), &b[2], 0);
                func_ov004_0221cee4((char *) self, 2);
                if (n >= 0x3e8) {
                    func_ov004_0221cee4((char *) self, 5);
                }
                if (n >= 0x7d0) {
                    func_ov004_0221cee4((char *) self, 5);
                }
                func_02015330(self, obj, 0, 5, 0);
                func_ov004_0221c844(*(void **) ((char *) self + 0x1a4), 0xc);
            }
        }
    }
}

void func_ov004_0221cd48(UnkStruct_0221cd48 *obj, int val)
{
    func_0202dc3c(obj, val, 0x11);
    obj->unk_1A4 = val;
}

void func_ov004_0221cc14(char *self, void *out0)
{
    char *out = (char *) out0;
    int mode;
    int i;

    func_0200366c(func_0208150c(OBJ->unk_830), &data_ov004_02257a6c, 0x28, &data_ov004_02253734);
    *(void **) out = &data_ov004_02257a6c;

    if (OBJ->unk_898 == 9) {
        *(u8 *) (out + 4) = (u8) func_020644cc(2);
        return;
    }

    mode = 3;
    if (func_ov004_0221d02c(self) != 0) {
        mode = 1;
    } else if (func_ov004_0221cff8((char *) self) != 0) {
        mode = 2;
    }
    func_ov004_0221d014(self);

    switch (mode) {
        case 1:
            *(u8 *) (out + 4) = (u8) (func_020644cc(2) + 2);
            break;
        case 2:
            *(u8 *) (out + 4) = (u8) (func_020644cc(4) + 0x13);
            break;
        default:
            *(u8 *) (out + 4) = (u8) (func_020644cc(2) + 4);
            break;
    }

    if (OBJ->unk_8E0 == 0) {
        return;
    }
    if (OBJ != 0 && OBJ->unk_830 != 0) {
        func_02015e10((char *) OBJ + 0x8a0, func_0208150c(OBJ->unk_830), 1);
    }

    {
        UnkStruct_0221cc14 **objp;
        i = 0;
        objp = (UnkStruct_0221cc14 **) (self + 0x1a4);
        for (; i < func_020826cc(); i++) {
            void *cand = func_020826a8(i);
            if (cand != 0 && cand != (void *) *objp) {
                func_02015e10((char *) OBJ + 0x8a0, func_0208150c(((UnkStruct_0221cc14 *) cand)->unk_830), 0);
                break;
            }
        }
    }

    {
        u16 buf = 0x1100;
        func_02015de4(self, &buf, 0, 7);
        func_02015de4(self, &buf, 1, 7);
    }
}

u16 func_ov004_0221cb28(int n)
{
    // DECLS
    u16 a[5];
    UnkStruct_0221cb28 t[4];
    u16 r;
    // ENDDECLS

    if (n <= 0) {
        func_02063ccc(&t[0], 1, 0);
        func_020638d4(&a[1], &t[0], 0, 0, 1, 1, 0);
        r = a[1];
        func_02063cc8(&t[0]);
        return r;
    }
    if (n <= 0x3f) {
        if (func_020644cc(2) == 0) {
            func_02063ccc(&t[1], 0, 0);
            func_020638d4(&a[2], &t[1], 0, 0, 1, 1, 0);
            r = a[2];
            func_02063cc8(&t[1]);
            return r;
        }
        func_02063ccc(&t[2], 2, 0);
        func_020638d4(&a[3], &t[2], 0, 0, 1, 1, 0);
        r = a[3];
        func_02063cc8(&t[2]);
        return r;
    }
    func_020630bc(&a[0], func_020984e8(), 0);
    if (a[0] == 0xfff1) {
        func_02063ccc(&t[3], 0, 0);
        func_020638d4(&a[4], &t[3], 0, 0, 1, 1, 0);
        r = a[4];
        func_02063cc8(&t[3]);
        return r;
    }
    return a[0];
}

void func_ov004_0221cae4(char *self)
{
    u8 v = *(u8 *) (self + 0x1e);
    u16 t;

    switch (v) {
        case 0xf:
        case 0x10:
            t = func_ov004_0221cb28((int) func_ov004_0221cec8((char *) self));
            *(u16 *) (*(char **) (self + 0x1a4) + 0xa50) = t;
            func_02015de4(self, &t, 1, 7);
            break;
    }
}

void func_ov004_0221ca04(char *s)
{
    u8 buf[4];
    switch (*(u8 *) (s + 0x1e)) {
        case 4:
        case 5:
        case 6:
            break;
        case 7:
        case 8:
            buf[0] = data_021f43e8;
            func_02068484(*(int *) (s + 0x40), &buf[0], 0);
            break;
        case 9:
        case 10:
            func_ov004_0221c844((void *) (*(int *) (s + 0x1a4)), 0xa);
            break;
        case 11:
        case 12:
        case 13:
        case 14:
            buf[1] = (u8) (func_020644cc(2) + 0xf);
            func_0206844c((void *) (*(int *) (*(int *) (s + 0x1a4) + 0x8e0)), (void *) (&buf[1]), 0);
            break;
        case 15:
        case 16:
            func_020154b4(s, (char *) *(int *) (s + 0x1a4) + 0xa50, 0, 5, 0);
            func_0209a000((char *) *(int *) (s + 0x1a4) + 0xa50, 0);
            func_ov004_0221c844((void *) (*(int *) (s + 0x1a4)), 0xd);
            break;
        case 17:
        case 18:
            func_ov004_0221cfe0((void *) s);
            break;
        case 19:
        case 20:
        case 21:
        case 22:
            buf[2] = data_021f43e8;
            func_02068484(*(int *) (s + 0x40), &buf[2], 0);
            break;
    }
}
