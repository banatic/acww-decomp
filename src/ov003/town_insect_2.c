/* town_insect_2: 19 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_0222d83c @ 0x0222d83c, 0x23c bytes, Thumb
 * func_ov003_0222d7d0 @ 0x0222d7d0, 0x6c bytes, Thumb
 * func_ov003_0222d77c @ 0x0222d77c, 0x54 bytes, Thumb
 * func_ov003_0222d738 @ 0x0222d738, 0x44 bytes, Thumb
 * func_ov003_0222d6fc @ 0x0222d6fc, 0x3c bytes, Thumb
 * func_ov003_0222d6a8 @ 0x0222d6a8, 0x52 bytes, Thumb
 * func_ov003_0222d68c @ 0x0222d68c, 0x1c bytes, Thumb
 * func_ov003_0222d57c @ 0x0222d57c, 0x110 bytes, Thumb
 * func_ov003_0222d520 @ 0x0222d520, 0x5c bytes, Thumb
 * func_ov003_0222d518 @ 0x0222d518, 0x6 bytes, Thumb
 * func_ov003_0222d484 @ 0x0222d484, 0x94 bytes, Thumb
 * func_ov003_0222d40c @ 0x0222d40c, 0x78 bytes, Thumb
 * func_ov003_0222d388 @ 0x0222d388, 0x84 bytes, Thumb
 * func_ov003_0222d300 @ 0x0222d300, 0x88 bytes, Thumb
 * func_ov003_0222d248 @ 0x0222d248, 0xb6 bytes, Thumb
 * func_ov003_0222d230 @ 0x0222d230, 0x18 bytes, Thumb
 * func_ov003_0222d218 @ 0x0222d218, 0x18 bytes, Thumb
 * func_ov003_0222d1f8 @ 0x0222d1f8, 0x20 bytes, Thumb
 * func_ov003_0222d1bc @ 0x0222d1bc, 0x3c bytes, Thumb
 */

#include "types.h"

typedef struct {
    int m[12];
} Mtx;

typedef struct {
    char pad_00[0x64];
    int unk_64;
} UnkStruct_0222d77c;

typedef struct {
    unsigned char pad_00[252];
    unsigned long unk_FC;
} UnkStruct_0222d518;

typedef struct {
    char pad_00[0x64];
    int unk_64;
} UnkStruct_0222d40c;

struct _Obj {
    void *vtbl;
};

extern unsigned char data_ov003_02260e4c[];
extern int FX_MulFunc(int a, int b);
extern void func_ov003_0222e358(void *p, int a);
extern int func_0203f7d0(int *dst, int *src);
extern void func_02056fcc(void *a, int b, int c, int d, int e);
extern void func_020550e4(void *a, int b);
extern void func_0209129c(int h);
extern char data_ov003_022617bc[];
extern char data_ov003_02260994[];
extern UnkStruct_0222d77c *data_020ccf94;
extern char data_ov003_02260ac4[];
extern int func_02073dd4(void *a, int b);
extern void *func_0209d088(void *a);
extern int NNS_G3dMdlGetMdlAlpha(void *a, int b);
extern unsigned char data_ov003_02260540;
extern char data_ov003_02260558[];
extern void func_0204f818(int *x, int *y, void *src);
extern void func_0209df94(void *out);
extern void func_0209def4(unsigned char *p);
extern void *func_02032c64(void *unused0);
extern void *func_02055210(void *unused0);
extern void *func_02089b04(void *unused0);
extern void *func_0209d11c(void *unused0);
extern void __cxa_vec_ctor(void *, unsigned int, unsigned int, void (*)(void *), void (*)(void *));
extern void func_0209d34c(void *unused0);
extern void func_0209d0a4(void *argument0);
extern void func_020012e8(void *element);
extern void func_020012dc(void *element);
extern void *data_0213efe8;
extern void *data_0213f020;
extern void *func_02032c50(void *);
extern void *func_020551e0(void *);
extern int func_02089af4(void *);
extern int func_0209d104(void *);
extern void func_0209d340(void *);
extern void __cxa_vec_cleanup(void *, int, int, void *);
extern signed char data_ov003_0226054c[];
extern char data_ov003_02260bf0[];
extern unsigned char data_ov003_02260538;
extern int func_020ba4e4(void);
extern int func_02046730(void *a);
extern int func_020644cc(int a);
extern u8 *data_020dded8[];
extern unsigned short data_ov003_02260554;
extern void func_020565ec(void *arg);
extern int data_ov003_0223c0ec;
extern void *func_02056578(void *);
extern void func_020edb3c(void *);
extern void MI_CpuCopy8(const void *src, void *dst, unsigned int n);
extern char data_ov003_02260794[0x200];
extern char data_ov003_02260594[0x200];

int func_ov003_0222d6a8(void);
int func_ov003_0222d388(int a, int b, u8 *out);
int func_ov003_0222d248(int a, int b);
void *func_ov003_0222d230(void *arg);
void *func_ov003_0222d218(void *arg);

int func_ov003_0222d83c(int idx, short *ptr, Mtx *src, int flag)
{
    unsigned char *p;
    int *d;
    int *mp;
    int ret;
    short ty;
    char *q;
    int v;
    int st;

    p = data_ov003_02260e4c + idx * 0x25c;
    d = (int *) (p + 0x204);
    ret = 1;
    mp = (int *) (p + 0x180);
    *(Mtx *) mp = *src;
    mp = (int *) (p + 0x180);
    func_ov003_0222e358(p, *ptr);
    d[0] = mp[9];
    d[1] = mp[10];
    d[2] = mp[11];
    func_0203f7d0(d, d);
    if (p[0x251] != 0xb) {
        ty = *(signed char *) (p + 0x24d);
        if (ty == 0x1a) {
            *(short *) (p + 0x238) = 0;
            *(short *) (p + 0x23a) = (short) FX_MulFunc(0xb6, 0xc8000);
            *(short *) (p + 0x23c) = (short) FX_MulFunc(0xb6, 0x1e000);
        } else if (ty == 0xc || ty == 0xd || ty == 0x1d) {
            *(short *) (p + 0x238) = (short) FX_MulFunc(0xb6, 0x91000);
            *(short *) (p + 0x23a) = (short) FX_MulFunc(0xb6, 0xc8000);
            *(short *) (p + 0x23c) = (short) FX_MulFunc(0xb6, 0x96000);
        } else if (ty == 0x35) {
            *(short *) (p + 0x238) = (short) FX_MulFunc(0xb6, 0x91000);
            *(short *) (p + 0x23a) = (short) FX_MulFunc(0xb6, 0x64000);
            *(short *) (p + 0x23c) = 0;
        } else {
            *(short *) (p + 0x238) = (short) FX_MulFunc(0xb6, 0x35000);
            *(short *) (p + 0x23a) = (short) FX_MulFunc(0xb6, 0xc8000);
            *(short *) (p + 0x23c) = (short) FX_MulFunc(0xb6, 0x54000);
            if (p[0x250] == 3) {
                q = (char *) (p + 0x50);
                if (ty == 0x14 && (unsigned short) (*(int *) (q + 0xa4) >> 12) == 0) {
                    func_02056fcc(q + 0x9c, 4, 1, 0x1000, 0);
                    *(int *) (q + 0xa4) = 0x4000;
                } else if (ty == 0xa || ty == 0xb) {
                    if ((unsigned short) (*(int *) (q + 0xa4) >> 12) == 0) {
                        func_020550e4(q, 1);
                    } else {
                        func_020550e4(q, 0);
                    }
                } else if (ty == 0x37) {
                    v = *(int *) (q + 0xa0) >> 12;
                    if ((unsigned short) v == 0xe && (unsigned short) (*(int *) (q + 0xa4) >> 12) == 0xd) {
                        *(int *) (q + 0xa4) = 0xa000;
                    } else if ((unsigned short) v != 0xe) {
                        func_02056fcc(q + 0x9c, 0xe, 0, 0x1000, 0xa);
                    }
                }
            }
        }
    }
    st = p[0x250];
    if (st == 2 || st == 0) {
        ret = 0;
    }
    if (flag != 0) {
        p[0x251] = 0xa;
        if (*(signed char *) (p + 0x24d) == 0x39) {
            if (*(int *) (p + 0x22c) != -1) {
                func_0209129c(*(int *) (p + 0x22c));
                *(int *) (p + 0x22c) = -1;
            }
        }
    }
    return ret;
}

int func_ov003_0222d7d0(int code)
{
    unsigned char i = (unsigned char) (code & 0xf);
    char *o = (char *) code;
    if ((code >> 4) & 1) {
        o = data_ov003_022617bc + 0x25c * i;
    } else if ((code >> 5) & 1) {
        o = data_ov003_02260994 + 0x25c * i;
    }
    if (*(unsigned char *) (o + 0x251) != 0xa && *(unsigned char *) (o + 0x251) != 0xb &&
        *(unsigned char *) (o + 0x251) != 9 && *(unsigned char *) (o + 0x251) != 0x10 && *(unsigned char *) (o + 0x250) == 3) {
        *(char *) (o + 0x251) = 0x10;
        return 0;
    }
    return 1;
}

int func_ov003_0222d77c(void)
{
    if (func_02073dd4(data_020ccf94, data_020ccf94->unk_64) == 0) {
        char *o = data_ov003_02260994;
        if (NNS_G3dMdlGetMdlAlpha(func_0209d088(data_ov003_02260ac4), 0) > 0x1e && *(unsigned char *) (o + 0x250) == 3 &&
            *(signed char *) (o + 0x24d) != 0x13) {
            return 1;
        }
    }
    return 0;
}

int func_ov003_0222d738(void *self)
{
    int ax, ay;
    int bx, by;
    if (data_ov003_02260540 != 0) {
        func_0204f818(&bx, &by, self);
        func_0204f818(&ax, &ay, data_ov003_02260558);
        if (ax == bx && ay == by) {
            return 1;
        }
    }
    return 0;
}

int func_ov003_0222d6fc(void *self)
{
    unsigned char t[4];
    unsigned char m;
    func_0209df94(t);
    m = (unsigned char) (t[1] - 1);
    if (m > 0xb) {
        m = 0;
    }
    if (func_ov003_0222d388(m, func_ov003_0222d6a8(), (u8 *) self)) {
        return 1;
    }
    return 0;
}

int func_ov003_0222d6a8(void)
{
    unsigned char buf[4];
    unsigned char v;

    func_0209def4(buf);
    v = buf[1];
    if (v >= 4 && v <= 7) {
        return 1;
    }
    if (v >= 8 && v <= 0xf) {
        return 2;
    }
    if (v == 0x10) {
        return 3;
    }
    if (v == 0x11 || v == 0x12) {
        return 4;
    }
    if (v >= 0x13 && v <= 0x16) {
        return 5;
    }
    return 0;
}

void func_ov003_0222d68c(unsigned char *p)
{
    p += 0x24f;
    *p = *p + 1;
    if (*p > 0x50) {
        *p = 0;
    }
}

void *func_ov003_0222d57c(char *self)
{
    func_ov003_0222d230(self);
    func_02032c64(self + 0x20);
    func_02055210(self + 0x50);
    func_02089b04(self + 0x108);
    func_0209d11c(self + 0x130);
    *(void **) (self + 0x174) = &data_0213efe8;
    *(void **) (self + 0x174) = &data_0213f020;
    __cxa_vec_ctor(self + 0x1ec, 0x2, 0xc, func_020012e8, func_020012dc);
    func_0209d34c(self + 0x230);
    func_0209d0a4(self + 0x130);
    *(u8 *) (self + 0x251) = 0x13;
    *(u8 *) (self + 0x24f) = 0;
    *(u16 *) (self + 0x23a) = 0;
    *(u16 *) (self + 0x23c) = 0;
    *(u16 *) (self + 0x238) = 0;
    *(s8 *) (self + 0x24d) = -1;
    *(u8 *) (self + 0x250) = 0;
    *(int *) (self + 0x170) = 0;
    *(u8 *) (self + 0x24c) = 1;
    *(u16 *) (self + 0x242) = 0;
    *(u8 *) (self + 0x24b) = 1;
    *(u8 *) (self + 0x24a) = 0;
    *(u8 *) (self + 0x248) = 0;
    *(u8 *) (self + 0x249) = 0;
    *(u8 *) (self + 0x252) = 0;
    *(int *) (self + 0x22c) = -1;
    return self;
}

void *func_ov003_0222d520(char *self)
{
    // DECLS
    // ENDDECLS
    func_0209d340(self + 0x230);
    __cxa_vec_cleanup(self + 0x1ec, 0x2, 0xc, (void *) func_020012dc);
    func_0209d104(self + 0x130);
    func_02089af4(self + 0x108);
    func_020551e0(self + 0x50);
    func_02032c50(self + 0x20);
    func_ov003_0222d218(self);
    return self;
}

void func_ov003_0222d518(UnkStruct_0222d518 *p, unsigned long v)
{
    p->unk_FC = v;
}

int func_ov003_0222d484(unsigned char *a, unsigned char *b, int c)
{
    int t[4];
    int r = func_020ba4e4();
    if (c != 0) {
        if (r == 0) {
            if (func_02046730(t)) {
                *a = 0x33;
                *b = 8;
                return 1;
            }
            if (data_ov003_0226054c[0] > 0 && func_020644cc(0x64) < 0x14) {
                *a = 0x33;
                *b = 7;
                return 1;
            }
        }
    } else {
        if (r != 1) {
            char *o = data_ov003_02260bf0;
            if (data_ov003_02260538 != 0 && *(unsigned char *) (o + 0x250) == 3 && *(unsigned char *) (o + 0x251) == 0x13) {
                *a = 0x3b;
                *b = 7;
                return 1;
            }
        }
    }
    return 0;
}

int func_ov003_0222d40c(int k)
{
    if (!func_02073dd4((void *) ((*(UnkStruct_0222d40c * *) &data_020ccf94)), (*(UnkStruct_0222d40c * *) &data_020ccf94)->unk_64)) {
        return 1;
    }

    switch (k) {
        case 8:
        case 0xa:
        case 0x19:
        case 0x23:
        case 0x30:
        case 0x32:
        case 0x33:
        case 0x35:
        case 0x36:
        case 0x37:
        case 0x3a:
        case 0x3b:
            return 0;
        default:
            return 1;
    }
}

int func_ov003_0222d388(int a, int b, u8 *out)
{
    int h;
    u8 lvl;
    u8 *p;
    u8 *e;
    u8 i;
    u8 n;
    u8 c;

    lvl = func_020644cc(0x64);
    e = data_020dded8[a];
    if (e == 0) {
        return 0;
    }
    b = b * 8;
    n = *(e + b + 4);
    h = func_020ba4e4();
    for (i = 0; i < n; i++) {
        p = *(u8 **) ((int) e + b);
        c = *(p + i * 2);
        if (*(p + i * 2 + 1) <= lvl) {
            continue;
        }
        if (c != 0x30 && func_ov003_0222d40c(c) != 0 && func_ov003_0222d248((signed char) ((signed char) c), h) != 4) {
            *out = c;
            return 1;
        }
        return 0;
    }
    return 0;
}

void func_ov003_0222d300(void)
{
    data_ov003_02260554++;
    if (data_ov003_02260554 > 0x78) {
        char *o = data_ov003_022617bc;
        int i;
        data_ov003_02260554 = 0;
        for (i = 0; i < 8; i++) {
            if (*(signed char *) (o + 0x24d) == -10) {
                *(char *) (o + 0x24d) = -1;
                *(char *) (o + 0x248) = 0;
            } else if (*(unsigned char *) (o + 0x249) == 0 && *(short *) (o + 0x234) == 0 &&
                       *(unsigned char *) (o + 0x250) == 3) {
                *(char *) (o + 0x250) = 4;
                *(char *) (o + 0x251) = 0xa;
            }
            o += 0x25c;
        }
    }
}

int func_ov003_0222d248(int a, int b)
{
    switch (a) {
        case 16:
        case 17:
        case 18:
        case 19:
        case 20:
            if (b == 1 || b == 2) {
                return 5;
            }
            break;
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 10:
        case 12:
        case 13:
        case 14:
        case 15:
        case 21:
        case 22:
        case 23:
        case 25:
        case 27:
        case 28:
        case 29:
        case 32:
        case 37:
        case 50:
        case 51:
        case 54:
        case 55:
            if (b == 1 || b == 2) {
                return 4;
            }
            break;
        case 59:
            if (b == 1) {
                return 4;
            }
            break;
        case 26:
            if (b != 1) {
                return 4;
            }
            break;
        default:
            return 3;
    }
    return 3;
}

void *func_ov003_0222d230(void *arg)
{
    func_020565ec(arg);
    *(void **) arg = &data_ov003_0223c0ec;
    return arg;
}

void *func_ov003_0222d218(void *arg)
{
    *((void **) arg) = &data_ov003_0223c0ec;
    func_02056578(arg);
    return arg;
}

void *func_ov003_0222d1f8(struct _Obj *obj)
{
    obj->vtbl = ((char *) &data_ov003_0223c0ec);
    func_02056578(obj);
    func_020edb3c(obj);
    return obj;
}

void func_ov003_0222d1bc(void *dst, int kind)
{
    switch (kind) {
        case 0:
        case 5:
        case 6:
            MI_CpuCopy8(data_ov003_02260794, dst, 0x200);
            break;
        default:
            MI_CpuCopy8(data_ov003_02260594, dst, 0x200);
            break;
    }
}
