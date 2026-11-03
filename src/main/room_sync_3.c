/* room_sync_3: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020525a4 @ 0x020525a4, 0xb8 bytes, Thumb
 * func_020523e4 @ 0x020523e4, 0x1c0 bytes, Thumb
 * func_020521d8 @ 0x020521d8, 0x20c bytes, Thumb
 * func_02052118 @ 0x02052118, 0xc0 bytes, Thumb
 */

#include "types.h"

typedef struct {
    short x, y;
} Pt;

typedef struct {
    unsigned int b0 : 4;
    unsigned int b4 : 4;
    unsigned int b8 : 4;
    unsigned int b12 : 1;
    unsigned int b13 : 1;
    unsigned int b14 : 1;
    unsigned int b15 : 16;
} BF;

typedef struct {
    int unk_00, w1;
} It;

typedef struct {
    unsigned int b0 : 1;
    unsigned int b1 : 4;
    unsigned int b5 : 4;
    unsigned int b9 : 1;
    unsigned int b10 : 1;
    unsigned int b11 : 16;
} BF_020521d8;

extern unsigned char data_020e54a8;
extern int func_02073918(unsigned int, int);
extern int func_020526b8(int, int, int, int, unsigned char, unsigned char, unsigned char);
extern int func_ov004_0223cd50(void);
extern unsigned char *func_ov004_0223cc10(int, int, int, int);
extern int func_02052794(int, int, int, int, unsigned char, unsigned char, unsigned char);
extern void *data_021c80bc;
extern void *data_020ccf94;
extern int func_020b65c4(void);
extern void *func_0204d5c8(int a);
extern int *func_02052e3c(It *it, unsigned short *src);
extern Pt *func_02052dc0(It *it, int i);
extern unsigned int func_02052e20(It *it);
extern void func_02052e38(It *it);
extern int func_0204f538(void *o, unsigned short *p, int x, int y, int q);
extern void func_02052ee8(int x, int y, int a, int b, int c);
extern int func_02052e98(int x, int y, int a, int b);
extern int func_02073d90(void *g);
extern void func_02073820(void *g);
extern void func_020737f0(void *g, void *p, int n);
extern void func_02073770(void *g, int off, int n);
extern int func_02052e70(int x, int y, int a);

int func_020525a4(int a, int b, int c, int d, unsigned char e, unsigned char f, unsigned char g)
{
    unsigned int saved;
    unsigned int cond;
    unsigned char *ret;

    saved = (*(unsigned int *) &data_020ccf94);
    if (func_02073d90((void *) saved) == 0) {
        goto first;
    }
    if (func_02073918(saved, 0) == 0) {
        goto later;
    }
first:
    return func_020526b8(a, b, c, d, e, f, g);

later:
    cond = (data_020e54a8 == 1) ? 1 : 0;
    if (cond == 0) {
        return 0;
    }

    ret = func_ov004_0223cc10(func_ov004_0223cd50(), a, b, c);
    if (ret == 0) {
        return 0;
    }

    if (g != 0) {
        if (func_02052794(a, b, c, d, e, f, 0) != 0) {
            ret[0x77d] = 1;
            return 1;
        }
        return 0;
    } else {
        return 0;
    }
}

void func_020523e4(int a0, int a1, int a2, int a3, int a4, int a5, int a6, unsigned short *a7, unsigned char a8)
{
    void *obj;
    int X, Y;
    unsigned short L[3];
    It it;
    BF bf;
    unsigned short *q;
    void *g;
    int i;
    unsigned int t;

    L[0] = *a7;
    t = (data_020e54a8 == 1) ? 1 : 0;
    if (t > 0 && a0 == func_020b65c4()) {
        obj = data_021c80bc;
    } else {
        obj = func_0204d5c8(a0);
    }
    if (obj == 0) {
        return;
    }
    func_02052e3c(&it, a7);
    for (i = 0; i < func_02052e20(&it); i++) {
        X = a1 + func_02052dc0(&it, i)->x;
        Y = a2 + func_02052dc0(&it, i)->y;
        if (i == 0) {
            q = &L[0];
        } else {
            L[2] = 0xf031;
            q = &L[2];
        }
        L[1] = *q;
        if (func_0204f538(obj, &L[1], X, Y, a3) == 0) {
            func_02052e38(&it);
            return;
        }
        func_02052ee8(X, Y, a3, a4, a0);
        if (a5 != 0 && a4 != 0 && i == 0) {
            func_02052e98(X, Y, a6, a0);
        }
    }
    if (func_02073d90(data_020ccf94) != 0 && a8 != 0) {
        bf.b0 = a1;
        bf.b4 = a2;
        bf.b8 = a6 & 0xf;
        bf.b12 = a3;
        bf.b13 = a4;
        bf.b14 = a5;
        bf.b15 = L[0];
        g = data_020ccf94;
        func_02073820(g);
        func_020737f0(g, &bf, 4);
        func_02073770(g, 0x1c, 4);
    }
    func_02052e38(&it);
}

void func_020521d8(int a0, int a1, int a2, int a3, int a4, unsigned short *a5, int a6, unsigned char a7)
{
    void *obj;
    unsigned int i;
    int X, Y;
    int flag;
    unsigned int ok;
    unsigned short L[4];
    It it;
    BF_020521d8 bf;
    void *g;
    unsigned int t;

    L[0] = *a5;
    t = (data_020e54a8 == 1) ? 1 : 0;
    if (t > 0 && a0 == func_020b65c4()) {
        obj = data_021c80bc;
    } else {
        obj = func_0204d5c8(a0);
    }
    if (obj == 0) {
        return;
    }
    func_02052e3c(&it, a5);
    flag = 0;
    if (*a5 >= 0x45dc && *a5 <= 0x47d7) {
        flag = 1;
    }
    for (i = 0; i < func_02052e20(&it); i++) {
        X = a1 + func_02052dc0(&it, i)->x;
        Y = a2 + func_02052dc0(&it, i)->y;
        L[1] = 0xfff1;
        ok = (func_0204f538(obj, &L[1], X, Y, a3) == 0) ? 1 : 0;
        if (ok != 0) {
            func_02052e38(&it);
            return;
        }
        if (a6 != 0 && a3 == 0) {
            L[2] = 0xfff1;
            ok = (func_0204f538(obj, &L[2], X, Y, 1) == 0) ? 1 : 0;
            if (ok != 0) {
                func_02052e38(&it);
                return;
            }
        }
        func_02052ee8(X, Y, a3, a4, a0);
        if (a6 != 0 && a3 == 0) {
            func_02052ee8(X, Y, 1, a4, a0);
        }
        if (flag != 0 && a4 != 0) {
            func_02052e70(X, Y, a0);
        }
    }
    if (func_02073d90(data_020ccf94) != 0 && a7 != 0) {
        bf.b0 = a3;
        bf.b1 = a1;
        bf.b5 = a2;
        bf.b9 = a6;
        bf.b10 = a4;
        bf.b11 = L[0];
        g = data_020ccf94;
        func_02073820(g);
        func_020737f0(g, &bf, 4);
        func_02073770(g, 0x1b, 4);
    }
    func_02052e38(&it);
}

void func_02052118(int a0, int a1, int a2, u16 *a3, u8 a4)
{
    u32 packed;
    void *obj;
    void *obj2;
    unsigned int cond;

    cond = ((*(u8 *) &data_020e54a8) == 1);
    if (cond && func_020b65c4() == a0) {
        obj = data_021c80bc;
    } else {
        obj = func_0204d5c8(a0);
    }
    if (obj == 0) {
        return;
    }
    if (func_0204f538(obj, (unsigned short *) a3, a1, a2, 1) == 0) {
        return;
    }
    if (a4 == 0) {
        return;
    }
    if (func_02073d90(data_020ccf94) == 0) {
        return;
    }

    packed = (packed & ~0xf) | (a1 & 0xf);
    packed = (packed & ~0xf0) | ((a2 & 0xf) << 4);
    packed = (packed & 0xff0000ff) | (((u32) *a3 & 0xffff) << 8);

    obj2 = data_020ccf94;
    func_02073820(obj2);
    func_020737f0(obj2, (void *) (&packed), 4);
    func_02073770(obj2, 0x1a, 4);
}
