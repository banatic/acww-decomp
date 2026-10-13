/* func_ov004_0222b214 @ 0x0222b214, 0x5c bytes, Thumb, module ov004
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
extern void func_ov004_0222b270(struct Pair *p, int a, int b, int c, int d, int e);
extern int func_0200e894(void *self, struct Msg *m);
extern void func_0200e91c(struct Msg *m);

int func_ov004_0222b214(void *self, int a, int b, int c, u8 e, int f, short g)
{
    struct Msg m;
    int r;
    int t;

    func_0200e92c(&m);
    func_0200e90c(&m, 0xe, f, g);
    t = (f == 6) ? 1 : 0;
    func_ov004_0222b270(&m.p, a, b, c, e, t);
    r = func_0200e894(self, &m);
    func_0200e91c(&m);
    return r;
}
