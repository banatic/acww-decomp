/* func_02063f94 @ 0x02063f94, 0x14c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/main/helper_ctors.h"

extern "C" {
extern int func_0205be20(void);
extern int func_0205be2c(void);
extern int FX_Div(int, int);
extern int func_02063f18(void *, int);
}

struct UnkStruct_02063f94 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual unsigned int v3(int);
    int unk_04;
};

// Same layout as UnkStruct_02063f94; built and torn down by its out-of-line pair.
struct ObjBuf {
    void *vtbl;
    int unk_04;
};

extern "C" int func_02063f94(void *ctx, int mode, UnkStruct_02063f94 *p)
{
    unsigned char b, c;
    unsigned int n;

    b = 0x3c - (unsigned char) FX_Div(func_0205be20() + func_0205be2c(), 0xa000);
    c = 0x46 - b;
    if (mode == 0) {
        ObjBuf loc;
        int r;
        func_02063e98(&loc);
        if (p == 0) {
            p = (UnkStruct_02063f94 *) &loc;
        }
        n = p->v3(0x64);
        if (n < b) {
            r = func_02063f94(ctx, 1, p);
            func_02063e8c(&loc);
            return r;
        }
        if (n < (unsigned int) (b + c)) {
            r = func_02063f94(ctx, 3, p);
            func_02063e8c(&loc);
            return r;
        }
        r = func_02063f94(ctx, 2, p);
        func_02063e8c(&loc);
        return r;
    }
    if (mode == 1) {
        if (b >= 0x1e && b >= c) {
            return func_02063f18(ctx, 0x3c);
        }
        if (b <= 0x1e && c <= 0x1e) {
            return func_02063f18(ctx, 0x1e);
        }
        return func_02063f18(ctx, 0xa);
    }
    if (mode == 2) {
        if ((b <= 0x1e && b >= c) || (b >= 0x1e && b <= c)) {
            return func_02063f18(ctx, 0x3c);
        }
        if ((b >= 0x1e && c <= 0x1e) || (b <= 0x1e && c >= 0x1e)) {
            return func_02063f18(ctx, 0x1e);
        }
        return func_02063f18(ctx, 0xa);
    }
    if (mode == 3) {
        if (b <= 0x1e && b <= c) {
            return func_02063f18(ctx, 0x3c);
        }
        if (b >= 0x1e && c >= 0x1e) {
            return func_02063f18(ctx, 0x1e);
        }
        return func_02063f18(ctx, 0xa);
    }
    return mode;
}
