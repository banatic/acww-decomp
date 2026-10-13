/* func_0202c704 @ 0x0202c704, 0x120 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct Pair {
    u32 a;
    u32 b;
} Pair;

typedef union UnkStruct_0202c704 {
    Pair w;
    u8 b[8];
} UnkStruct_0202c704;

class UnkStruct_0202c704_2 {
  public:
    virtual int v00();
    virtual int v01();
    virtual int v02();
    virtual int v03();
    virtual int v04();
    virtual int v05();
    virtual int v06();
    virtual int v07();
    virtual int v08();
    virtual int v09();
    virtual int v10();
    virtual int v11();
    virtual int v12();
    virtual int v13();
    virtual int v14();
    virtual int v15();
    virtual int v16();
    virtual int v17();
    virtual int v18();
    virtual int v19();
    virtual int v20();
    virtual int v21();
    virtual int v22();
    virtual int v23();
    virtual int v24();
    virtual int v25();
};

extern "C" void *func_0209b91c(void *h);
extern "C" int func_0209bc40(void *x);
extern "C" int func_0209b914(void *h);
extern "C" int func_0202c824(UnkStruct_0202c704_2 *p0, void *h, UnkStruct_0202c704 *p5, u8 f);
extern "C" int func_020644cc(int n);
extern "C" u16 *func_0209bb70(void *x);
extern "C" int func_0202cef4(u16 *v, u8 a, u8 b, u8 c);
extern "C" int func_0202d6e4(void *p3, int k);
extern "C" int func_0202d190(u16 *v, int a, int b, u8 c);
extern "C" u16 *func_0209b8c4(void *h);
extern "C" Pair *func_0209b8c8(void *h);
extern "C" void func_02078478(int a, u16 *b);

extern "C" void func_0202c704(UnkStruct_0202c704_2 *p0, void *h, u8 *tbl, void *p3, u8 f, UnkStruct_0202c704 *p5)
{
    void *x;
    int idx;
    int lim;
    int rnd;
    u16 val;
    int n;
    int r;
    u32 w0, w1;
    Pair *dst;
    u16 *q;

    x = func_0209b91c(h);
    if (func_0209bc40(x) != 0) {
        return;
    }
    idx = func_0209b914(h);
    if (func_0202c824(p0, h, p5, f) == 0) {
        return;
    }
    if (idx < 5) {
        lim = tbl[idx];
    } else {
        lim = 0;
    }
    rnd = func_020644cc(100);
    val = *func_0209bb70(x);

    switch (idx) {
        case 1:
        case 3:
        case 4:
            if (rnd < lim) {
                if (func_0202cef4(&val, p5->b[2], p5->b[2], p5->b[4]) != 0) {
                    *func_0209b8c4(h) = val;
                }
            }
            break;
        case 2:
            if (rnd < lim) {
                n = func_0202d6e4(p3, 4);
                if (func_0202d190(&val, n, n + 1, p5->b[4]) != 0) {
                    *func_0209b8c4(h) = val;
                }
            }
            break;
        case 0:
            break;
    }

    if (p0->v25() != 0) {
        q = func_0209b8c4(h);
        r = 0;
        if (*q >= 0x12b0 && *q <= 0x12e7) {
            r = 1;
        }
        if (r != 0) {
            n = p0->v25();
            func_02078478(n, func_0209b8c4(h));
        }
    }

    w0 = p5->w.a;
    w1 = p5->w.b;
    dst = func_0209b8c8(h);
    dst->a = w0;
    dst->b = w1;
}
