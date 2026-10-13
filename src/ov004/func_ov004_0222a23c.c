/* func_ov004_0222a23c @ 0x0222a23c, 0x46 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct Pair {
    u8 a;
    u8 b;
};

struct Msg {
    u8 pad_00[0xc];
    struct Pair p;
    u8 pad_0E[0x1c - 0xe];
};

extern void func_0200e92c(struct Msg *m);
extern void func_0200e90c(struct Msg *m, int kind, int arg, short v);
extern void func_ov004_0222a284(struct Pair *p, int a, int b);
extern int func_0200e894(void *self, struct Msg *m);
extern void func_0200e91c(struct Msg *m);

int func_ov004_0222a23c(void *self, int a, int b, int arg, short v)
{
    struct Msg m;
    int r;

    func_0200e92c(&m);
    func_0200e90c(&m, 0x1e, arg, v);
    func_ov004_0222a284(&m.p, a, b);
    r = func_0200e894(self, &m);
    func_0200e91c(&m);
    return r;
}
