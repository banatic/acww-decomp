/* func_ov004_0223c2b4 @ 0x0223c2b4, 0x5c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_ov004_0223c130(void);
extern void *func_ov004_0223ce84(void);
extern void *func_ov004_0223cd58(void *h, unsigned int i);
extern int func_ov004_0220d2b8(void *p);
extern void func_ov004_0220d280(void *p, int a, void *arg);

void func_ov004_0223c2b4(int a, int (*fn)(void), void *arg)
{
    unsigned int i;
    void *e;

    for (i = 0; i < func_ov004_0223c130(); i++) {
        e = func_ov004_0223cd58(func_ov004_0223ce84(), i);
        if (e == 0) {
            continue;
        }
        if (fn != 0) {
            if (fn == 0) {
                continue;
            }
            if (fn() == 0) {
                continue;
            }
        }
        if (a == func_ov004_0220d2b8((char *) e + 0x740)) {
            continue;
        }
        func_ov004_0220d280((char *) e + 0x740, a, arg);
    }
}
