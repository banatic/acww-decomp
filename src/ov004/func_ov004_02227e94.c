/* func_ov004_02227e94 @ 0x02227e94, 0x6c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

#pragma opt_propagation off

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
extern int func_0200e894(void *self, struct Msg *m);
extern void func_0200e91c(struct Msg *m);
extern int func_020b5e10(void);
extern int func_020b6044(int x, int h, int *v, short *s);
extern void func_ov004_02227f00(struct Pair *p, int v, short s, short *ps);

int func_ov004_02227e94(char *self, int a, short b)
{
    short s;
    int v;
    struct Msg m;
    int h;
    int r;
    short *ps;
    struct Pair *pp;
    int vv;

    h = *(int *) (self + 0x804);
    if (h == -1) {
        return 0;
    }
    if (func_020b6044(func_020b5e10(), h, &v, &s) == 0) {
        return 0;
    }
    func_0200e92c(&m);
    func_0200e90c(&m, 0x40, a, b);
    pp = &m.p;
    vv = v;
    ps = &s;
    func_ov004_02227f00(pp, vv, *ps, ps);
    r = func_0200e894(self, &m);
    func_0200e91c(&m);
    return r;
}
