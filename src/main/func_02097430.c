/* func_02097430 @ 0x02097430, 0xea bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void *func_020984e8(void);
extern void *func_02098a0c(void);
extern void *func_020992e4(void *);
extern u32 func_02097cc8(void *);
extern void MI_CpuCopy8(const void *, void *, unsigned int);
extern void func_0209e29c(void *, int);
extern int func_0209e3ac(const void *, const void *, int);
extern int func_02097188(int, int, u8, int);

int func_02097430(u32 *arg)
{
    void *h1, *h2;
    u8 *p;
    u64 a, b, c;
    int flag;

    h1 = func_020984e8();
    h2 = func_02098a0c();
    p = func_020992e4(h1);

    if (*(u16 *) p == 0) {
        return 0;
    }

    if (arg[0] == func_02097cc8(h2)) {
        return 0;
    }

    a = 0;
    a = 0;
    ((u8 *) &a)[5] = (u8) arg[0];
    ((u8 *) &a)[4] = p[1];
    ((u8 *) &a)[3] = p[0];

    b = 0;
    b = 0;
    ((u8 *) &b)[5] = (u8) arg[0];
    ((u8 *) &b)[4] = (u8) arg[1];
    ((u8 *) &b)[3] = (u8) arg[2];

    c = 0;
    MI_CpuCopy8(&a, &c, 8);
    func_0209e29c(&c, 7);

    flag = 0;

    if (((u8 *) &c)[5] != ((u8 *) &a)[5]) {
        ((u8 *) &c)[5] = ((u8 *) &a)[5];
        if (!(func_0209e3ac(&b, &c, 0x38) == 1 && func_0209e3ac(&b, &a, 0x38) == -1)) {
            flag = 1;
        }
    } else {
        if (!(func_0209e3ac(&b, &c, 0x38) == 1 || func_0209e3ac(&b, &a, 0x38) == -1)) {
            flag = 1;
        }
    }

    if (flag) {
        flag = func_02097188(0x20, 2, (u8) arg[1], 1);
    }

    return flag;
}
