/* player_actor_ops: 18 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02095944 @ 0x02095944, 0x66 bytes, Thumb
 * func_02095904 @ 0x02095904, 0x40 bytes, Thumb
 * func_0209583c @ 0x0209583c, 0xc8 bytes, Thumb
 * func_02095804 @ 0x02095804, 0x38 bytes, Thumb
 * func_020957b4 @ 0x020957b4, 0x50 bytes, Thumb
 * func_02095794 @ 0x02095794, 0x20 bytes, Thumb
 * func_02095764 @ 0x02095764, 0x30 bytes, Thumb
 * func_02095694 @ 0x02095694, 0xd0 bytes, Thumb
 * func_020955e0 @ 0x020955e0, 0xb4 bytes, Thumb
 * func_02095578 @ 0x02095578, 0x68 bytes, Thumb
 * func_02095558 @ 0x02095558, 0x20 bytes, Thumb
 * func_02095518 @ 0x02095518, 0x40 bytes, Thumb
 * func_020954c0 @ 0x020954c0, 0x58 bytes, Thumb
 * func_0209549c @ 0x0209549c, 0x24 bytes, Thumb
 * func_020953e4 @ 0x020953e4, 0xb8 bytes, Thumb
 * func_020953c4 @ 0x020953c4, 0x20 bytes, Thumb
 * func_020953a4 @ 0x020953a4, 0x20 bytes, Thumb
 * func_020953a0 @ 0x020953a0, 0x2 bytes, Thumb
 */

#include "types.h"

typedef struct {
    char pad_00[0x5c];
    int unk_5C;
    char pad_60[4];
    int unk_64;
    char pad_68[0x26];
    short unk_8E;
} UnkStruct_02095944;

struct UnkStruct_02095904 {
    char pad_00[0x7f0];
    int unk_7F0;
};

// Each field is read into a local before it is stored.

typedef struct Vec {
    int x;
    int y;
    int z;
} Vec;

struct UnkStruct_02095804 {
    unsigned char pad_00[0x7f0];
    unsigned int unk_7F0;
    unsigned char pad_7F4[8];
    unsigned int unk_7FC;
};

struct __obj {
    char pad_00[0x7f0];
    int unk_7F0;
    char pad_7F4[0x8];
    int unk_7FC;
};

struct UnkStruct_02095694 {
    u8 pad_00[0x5a0];
    s32 unk_5A0;
    u8 pad_5A4[0x704 - 0x5a0 - 4];
    s32 unk_704;
};

typedef struct {
    char pad_00[0x704];
    int unk_704;
    char pad_708[0x5];
    char unk_70D;
} UnkStruct_02095578;

struct Vec3 {
    int x;
    int y;
    int z;
};

struct Big {
    char pad_00[0x450];
    int a;
    int b;
    int c;
};

typedef struct {
    unsigned int d[12];
} BigT;

struct ThreeInts {
    int a;
    int b;
    int c;
};

struct UnkStruct_020953e4 {
    char pad_00[0x68];
    int unk_68;
};

struct _020953c4_struct {
    unsigned char pad_00[0x804];
    unsigned int value;
};

extern int func_0200fbe0(void *);
extern unsigned int *func_0200f27c(void *, int);
extern int func_0200c3b0(void *, int, int, int);
extern int func_ov003_02217c5c(void *, int, unsigned int, int, int, int, int, int);
extern int func_02096718(int);
extern int func_0200f290(void *p, int a);
extern int func_02008258(void *, int);
extern int func_020b5e10(void);
extern int func_020b6044(int, int, int *, s16 *);
extern int func_02064558(s16);
extern int func_ov004_022265dc(void *, Vec *, int, int);
extern struct UnkStruct_02095804; // unused
extern int func_0200c1b8(struct UnkStruct_02095804 *ptr, int a, int b);
extern unsigned char data_020d1894[];
extern int func_0200c0dc(struct __obj *obj, unsigned char c1, unsigned char c2, int n, int arg);
extern void func_020110c4(unsigned short *, int);
extern void *func_020984fc(void *x);
extern unsigned int func_02062230(void);
extern void func_020621d4(void *dst, unsigned int value);
extern void func_0209971c(void *x, void *p);
extern void func_0205eb8c(void *base, void *p, void *arg);
extern void func_02010934(void *base);
extern void func_0205ea60(void *base);
extern void func_02099704(void *ctx, void *p);
extern void func_020996d4(void *ctx, void *p);
extern void func_020996ec(void *ctx, void *p);
extern void func_02010680(void *obj, void *p);
extern int func_0201063c(void *obj);
extern int func_020103c0(void *obj, unsigned short *buf);
extern int func_020112e4(void *obj);
extern int func_020112d0(void *obj);
extern int func_020100e8(void *obj, unsigned short *buf, int a, int b, int c);
extern void func_02099740(void *, int);
extern char *func_0209984c(void *);
extern int func_0205dc94(void *, void *);
extern void func_020997b4(int param1, int param2);
extern int func_0203f7d0(void *a, void *b);
extern void func_0200fa1c(struct ThreeInts *out, char *unused, struct ThreeInts *in, u16 *p, int *q);
extern int func_020b67d4(void);
extern int func_ov004_0223bbc0(int *a, int *b, int c, int d);
extern int func_0204f5a8(u32 a, struct ThreeInts *b, u32 c);
extern int func_0204f260(u32 a, struct ThreeInts *b);
extern int data_020e2f7c[];
extern u8 data_020e54a8;
extern struct UnkStruct_020953e4 *data_020ccf94;
extern u32 data_021c80bc;

void func_02095944(unsigned int arg)
{
    void *p;
    int v;

    p = (void *) func_02096718(4);
    if (p == 0) {
        return;
    }

    v = func_0200fbe0(p);
    if (v == 0 || (v == 10 && arg == 1) || arg >= 2) {
        func_0200f27c(p, 1);
        func_0200c3b0(p, 3, 5, -1);
    } else {
        func_ov003_02217c5c(p, 0x10, arg, ((UnkStruct_02095944 *) p)->unk_5C, ((UnkStruct_02095944 *) p)->unk_64,
                            ((UnkStruct_02095944 *) p)->unk_8E, 6, -1);
    }
}

int func_02095904(void)
{
    void *ptr = (void *) func_02096718(4);
    if (ptr) {
        if (((struct UnkStruct_02095904 *) ptr)->unk_7F0 == 0x28) {
            if (func_0200f290(ptr, 0xb)) {
                return 1;
            }
        }
        return func_0200c3b0(ptr, 3, 5, -1);
    }
    return 0;
}

int func_0209583c(void)
{
    s16 h;
    int q;
    Vec pos;
    char *p;
    int a;
    int dir;
    Vec *src;
    int x;
    int y;
    int z;

    p = (char *) func_02096718(4);
    if (p != 0) {
        *(int *) (p + 0x7fc) = func_02008258(p, *(int *) (p + 0x7f0));
        if (*(int *) (p + 0x808) == 3) {
            a = *(int *) (p + 0x804);
            h = *(s16 *) (p + 0x8e);
            if (a != -1) {
                func_020b6044(func_020b5e10(), a, &q, &h);
            }
            dir = func_02064558(h);
            src = (Vec *) (p + 0x5c);
            x = src->x;
            pos.x = x;
            y = src->y;
            pos.y = y;
            z = src->z;
            pos.z = z;
            switch (dir) {
                case 2:
                    pos.z = z - 0x6000;
                    break;
                case 0:
                    pos.z = z + 0x6000;
                    break;
                case 3:
                    pos.x = x - 0x6000;
                    break;
                case 1:
                    pos.x = x + 0x6000;
                    break;
            }
            return func_ov004_022265dc(p, &pos, 6, -1);
        }
    }
    return 0;
}

int func_02095804(void)
{
    struct UnkStruct_02095804 *p = (struct UnkStruct_02095804 *) func_02096718(4);
    if (p != 0) {
        p->unk_7FC = (unsigned int) func_02008258((void *) p, p->unk_7F0);
        return func_0200c1b8(p, 5, -1);
    } else {
        return 0;
    }
}

int func_020957b4(unsigned char *p)
{
    struct __obj *obj;
    unsigned char c2;

    obj = (struct __obj *) func_02096718(4);
    c2 = data_020d1894[*p - 1];
    if (obj) {
        obj->unk_7FC = func_02008258((void *) obj, obj->unk_7F0);
        return func_0200c0dc(obj, *p, c2, 5, -1);
    } else {
        return 0;
    }
}

int func_02095794(int result)
{
    int temp;

    temp = func_02096718(result);
    if (temp != 0) {
        result = temp + 0x6f4;
    } else {
        result = 0;
    }
    return result;
}

void func_02095764(unsigned short *out, int param)
{
    unsigned short tmp;
    int ret;

    ret = func_02096718(param);
    *out = 0xFFF1;
    if (ret) {
        func_020110c4(&tmp, ret);
        *out = tmp;
    }
}

int func_02095694(unsigned int n, void *x)
{
    struct UnkStruct_02095694 *obj;
    u16 v0;
    u16 v1;
    u16 v2;
    u16 v3;
    u16 v4;

    obj = (struct UnkStruct_02095694 *) func_02096718((int) x);
    if (obj == 0) {
        return 0;
    }

    x = func_020984fc(x);

    if (obj->unk_704 >= 0xa1) {
        if (n == 0 || func_02062230() < n) {
            v1 = 0xfff1;
            func_0209971c(x, &v1);
        } else {
            func_020621d4(&v2, n - 1);
            func_0209971c(x, &v2);
        }
        return 0;
    } else {
        if (n == 0 || func_02062230() < n) {
            v3 = 0xfff1;
            func_0209971c(x, &v3);
            v4 = 0xfff1;
            func_0205eb8c(&obj->unk_5A0, &v4, 0);
            func_02010934(obj);
        } else {
            func_020621d4(&v0, n - 1);
            func_0209971c(x, &v0);
            func_0205eb8c(&obj->unk_5A0, &v0, x);
            func_02010934(obj);
            func_0205ea60(&obj->unk_5A0);
        }
        return 1;
    }
}

int func_020955e0(void *p, int mode, void *obj)
{
    void *ctx;
    unsigned short buf[2];
    int a, b;

    ctx = func_020984fc(obj);
    if (ctx == 0) {
        return 0;
    }

    switch (mode) {
        case 0:
            func_02099704(ctx, p);
            break;
        case 1:
            func_020996d4(ctx, p);
            break;
        case 2:
            func_020996ec(ctx, p);
            break;
        default:
            break;
    }

    obj = (void *) func_02096718((int) obj);
    if (obj == 0) {
        return 0;
    }
    if (*(int *) ((char *) obj + 0x704) >= 0xa1) {
        return 0;
    }

    switch (mode) {
        case 0:
            func_02010680(obj, p);
            func_0201063c(obj);
            break;
        case 1:
            buf[0] = *(unsigned short *) p;
            func_020103c0(obj, buf);
            break;
        case 2:
            buf[1] = *(unsigned short *) p;
            a = func_020112e4(obj);
            b = func_020112d0(obj);
            func_020100e8(obj, &buf[1], a, b, 0);
            break;
        default:
            break;
    }
    return 1;
}

int func_02095578(int a, void *b)
{
    void *ptr;
    UnkStruct_02095578 *info;
    char *tmp;

    ptr = func_020984fc(b);
    if (ptr == 0) {
        return 0;
    }
    func_02099740(ptr, a);
    info = (UnkStruct_02095578 *) func_02096718((int) b);
    if (info == 0) {
        return 0;
    }
    if (info->unk_704 >= 0xa1) {
        return 0;
    }
    if (a) {
        tmp = func_0209984c(ptr) + 0x10;
    } else {
        tmp = func_0209984c(ptr);
    }
    func_0205dc94(&info->unk_70D, tmp);
    return 1;
}

int func_02095558(int a, int b)
{
    int result = (int) func_020984fc((void *) b);
    if (result == 0) {
        return 0;
    }
    func_020997b4(result, a);
    return 1;
}

int func_02095518(int a, int b, int c)
{
    int r4;
    int r5 = a;
    int r6 = b;
    int r0 = c;

    r4 = func_02096718(r0);
    if (r4 != 0) {
        if (func_0200f290((void *) r4, 0x15) == 0) {
            func_0200f27c((void *) r4, 0x15);
        }
        *(unsigned short *) ((char *) r4 + 0x460) = r5;
        *(unsigned short *) ((char *) r4 + 0x462) = r6;
        return 1;
    }
    return 0;
}

int func_020954c0(struct Vec3 *out, void *arg)
{
    struct Big *p = (struct Big *) func_02096718((int) arg);

    if (p != 0) {
        if (p->a == 0 && p->b == 0 && p->c == 0) {
            return 0;
        }

        out->x = p->a;
        out->y = p->b;
        out->z = p->c;

        func_0203f7d0(out, out);
        return 1;
    }

    return 0;
}

void func_0209549c(BigT *dst, int src)
{
    *dst = *(BigT *) ((char *) func_02096718(src) + 0x698);
}

int func_020953e4(void)
{
    struct ThreeInts out;
    int a4;
    int a8;
    char *base = (char *) func_02096718(4);
    int ret = 0;

    if (base == 0) {
        return ret;
    }
    if (*(u32 *) ((char *) base + 0x7f0) != 2) {
        return ret;
    }
    func_0200fa1c(&out, base, (struct ThreeInts *) (base + 0x5c), (u16 *) (base + 0x8e), data_020e2f7c);
    {
        unsigned int cond = (data_020e54a8 == 1);
        if (cond != 0) {
            if (func_020b67d4() != 0) {
                if (data_020ccf94->unk_68 == 0) {
                    if (func_ov004_0223bbc0(&a4, &a8, 0, 0) < 0) {
                        ret = func_0204f5a8(data_021c80bc, &out, 0);
                    }
                }
            }
        } else {
            u32 v = data_021c80bc;
            if (func_0204f260(v, &out) != 0) {
                return 0;
            }
            ret = func_0204f5a8(v, &out, 0);
        }
    }
    return ret;
}

void func_020953c4(unsigned int *ptr)
{
    struct _020953c4_struct *res;
    res = (struct _020953c4_struct *) func_02096718(4);
    if (res != 0) {
        res->value = *ptr;
    }
}

void func_020953a4(int *param)
{
    int *result;
    int *ptr;

    result = (int *) func_02096718(4);
    if (result != 0) {
        ptr = (int *) param;
        *(int *) ((char *) result + 0x808) = *ptr;
    }
}

void func_020953a0(void) {}
