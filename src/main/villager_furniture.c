/* villager_furniture: 10 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0207f4c8 @ 0x0207f4c8, 0xc8 bytes, Thumb
 * func_0207f454 @ 0x0207f454, 0x74 bytes, Thumb
 * func_0207f414 @ 0x0207f414, 0x40 bytes, Thumb
 * func_0207f3a0 @ 0x0207f3a0, 0x74 bytes, Thumb
 * func_0207f360 @ 0x0207f360, 0x40 bytes, Thumb
 * func_0207f318 @ 0x0207f318, 0x48 bytes, Thumb
 * func_0207f30c @ 0x0207f30c, 0xc bytes, Thumb
 * func_0207f300 @ 0x0207f300, 0xc bytes, Thumb
 * func_0207f2f4 @ 0x0207f2f4, 0xc bytes, Thumb
 * func_0207f2e8 @ 0x0207f2e8, 0xc bytes, Thumb
 */

#include "types.h"

typedef struct UnkStruct_0207f4c8 {
    u16 a;
    u16 b;
    u16 c;
} UnkStruct_0207f4c8;

struct _S {
    char pad_00[0x64];
    int unk_64;
};

typedef struct Key {
    int a;
    int b;
} Key;

typedef struct Entry {
    u16 id;
    u8 unk_02;
    u8 unk_03;
} Entry;

struct UnkStruct_0207f2f4 {
    unsigned char pad_00[0x7d4];
    unsigned char value;
};

extern int func_0207f150(void *a0);
extern int func_0207ff58(void *a0, u16 *p);
extern void func_0207ff0c(u16 *dst, void *a0, int t);
extern int func_0204bcdc(u16 *p);
extern int func_0207d608(void *a0, int t);
extern void func_0207f590(u16 *dst, void *a0, u16 *src);
extern void func_0204bc28(u16 *p, int k);
extern struct _S *data_020ccf94;
extern int func_02073dd4(struct _S *a, int b);
extern void *func_0208150c(void *a);
extern int func_02003704(void *a);
extern char *func_0207dfd4(void *a, int b);
extern int func_0207f76c(void *a, char *b);
extern void func_0207dfec(void *a);
extern void *func_0207f294(void *a);
extern int func_02052fdc(void *a);
extern void *func_0207f1c8(void *a);
extern void *func_0209b5e8(void *a);
extern void func_0209b998(void *object);
extern void func_0207f5c8(void *);
extern int func_020644cc(int);
extern int func_0207ffa0(int a, int b);
extern void func_0207d5dc(int a, int b);

void func_0207f4c8(void *a0, u16 *p)
{
    UnkStruct_0207f4c8 h;
    int i;
    int mode;
    int t;
    unsigned int in;

    h.a = 0xfff1;
    mode = (func_0207f150(a0) == 3) ? 0 : 1;
    for (i = 0; i < 0x100; i++) {
        in = 0;
        if (*p >= 0xf000 && *p <= 0xf02f) {
            in = 1;
        }
        if (in != 0) {
            t = func_0207ff58(a0, p);
            func_0207ff0c(&h.b, a0, t);
            h.a = h.b;
            if (mode != 0 && func_0204bcdc(&h.a) != 0) {
                if (func_0207d608(a0, t) != 0) {
                    func_0207f590(&h.c, a0, &h.a);
                    h.a = h.c;
                } else {
                    h.a = 0xfff1;
                }
            }
            if (func_0204bcdc(&h.a) != 0) {
                func_0204bc28(&h.a, *p & 3);
                *p = h.a;
            } else {
                *p = 0xfff1;
            }
        }
        p++;
    }
}

void func_0207f454(void *self)
{
    if (func_02073dd4(data_020ccf94, data_020ccf94->unk_64) != 0) {
        return;
    }
    if (func_02003704(func_0208150c(self)) == 0) {
        return;
    }
    {
        char *p = func_0207dfd4(self, 0);
        int flag = 0;
        int i;
        for (i = 0; i < 4; i++) {
            if (func_0207f76c(self, p) != 0) {
                flag = 1;
            }
            p += 2;
        }
        func_0207dfec(self);
        if (flag) {
            func_02052fdc(func_0207f294(self));
        }
        func_0209b998(func_0209b5e8(func_0207f1c8(self)));
    }
}

void func_0207f414(char *ptr, int flag, int other)
{
    if (flag == 2) {
        *(ptr + 0x7d8) = (char) func_020644cc(10);
        func_0207f5c8(ptr);
    } else {
        *(ptr + 0x7d8) = (char) func_020644cc(0x28);
        if (other != 0) {
            func_0207f5c8(ptr);
        }
    }
}

int func_0207f3a0(void *ctx, Key *key, Entry *e, int n)
{
    volatile u16 id;
    int i;
    unsigned int seed;
    int ka;
    int kb;

    if (e != 0) {
        kb = key->b;
        ka = key->a;
        if ((unsigned int) ka < 0x10 && (unsigned int) kb < 0x10) {
            seed = 0;
            for (i = 0; i < n; e++, i++) {
                if (key->a != e->unk_02) {
                    continue;
                }
                if (key->b != e->unk_03) {
                    continue;
                }
                id = e->id;
                {
                    unsigned int ok = seed;
                    u16 hi = id;
                    u16 lo = id;
                    if (lo >= 0xf000 && hi <= 0xf02f) {
                        ok = 1;
                    }
                    if (ok > 0) {
                        return func_0207ff58(ctx, (u16 *) (&id));
                    }
                }
            }
        }
    }
    return -1;
}

int func_0207f360(int a, void *argument1, void *argument2, int argument3)
{
    int b;
    int c;
    int d;

    b = func_0207f3a0((void *) a, (Key *) ((void *) argument1), (Entry *) ((void *) argument2), (int) argument3);
    c = a;
    d = b;
    if (func_0207ffa0(c, d) != 0) {
        *(volatile unsigned short *) ((char *) a + (b << 1) + 0x78c) = 0xfff1;
        func_0207d5dc(a, b);
        return 1;
    }
    return 0;
}

int func_0207f318(int p, void *argument1, void *argument2, int argument3)
{
    int v = func_0207f3a0((void *) p, (Key *) ((void *) argument1), (Entry *) ((void *) argument2), (int) argument3);
    int r = func_0207ffa0(p, v);
    if (r != 0) {
        if (*(unsigned short *) ((char *) p + v * 2 + 0x78c) != 0xfff1) {
            if (func_0207d608((void *) p, v) != 0) {
                return 1;
            }
        }
    }
    return 0;
}

unsigned char func_0207f30c(unsigned char *param0)
{
    return param0[0x7d4];
}

unsigned char func_0207f300(unsigned char *r0)
{
    return r0[0x7d5];
}

void func_0207f2f4(struct UnkStruct_0207f2f4 *data, unsigned char val)
{
    data->value = val;
}

void func_0207f2e8(unsigned char *r0, unsigned char r1)
{
    r0[0x7d5] = r1;
}
