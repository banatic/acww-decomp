/* func_ov004_02229eac @ 0x02229eac, 0xb0 bytes, Thumb, module ov004
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

extern unsigned char data_020e54a8;
extern int func_ov004_0223cb10(void);
extern int func_ov004_0223c964(int h);
extern int func_ov004_0223c984(int h);
extern void func_ov004_0223c954(int h);
extern void func_ov004_0223c974(int h);
extern unsigned int func_0200e92c(struct Msg *m);
extern void func_0200e90c(struct Msg *m, int kind, int arg, short v);
extern void func_ov004_02229f5c(struct Pair *p, int k);
extern int func_0200e894(void *self, struct Msg *m);
extern int func_0200e91c(struct Msg *m);
extern int func_020b67d4(void);
extern int func_0200f328(void *self, int a);

int func_ov004_02229eac(char *self, int k, int a, short b)
{
    struct Msg m;
    unsigned int t;
    int r;

    t = (data_020e54a8 == 1) ? 1 : 0;
    if (t == 0) {
        return 0;
    }
    if ((k != 0 && func_ov004_0223c964(func_ov004_0223cb10()) != 0) ||
        (k == 0 && func_ov004_0223c984(func_ov004_0223cb10()) != 0)) {
        func_0200e92c(&m);
        func_0200e90c(&m, 0x1f, a, b);
        func_ov004_02229f5c(&m.p, k);
        if (k != 0) {
            func_ov004_0223c954(func_ov004_0223cb10());
        } else {
            func_ov004_0223c974(func_ov004_0223cb10());
        }
        r = func_0200e894(self, &m);
        func_0200e91c(&m);
        return r;
    }
    if (func_020b67d4() != 0 && *(int *) (self + 0x800) == 0) {
        func_0200f328(self, 0x6d);
    }
    return 0;
}
