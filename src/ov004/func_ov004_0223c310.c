/* func_ov004_0223c310 @ 0x0223c310, 0x54 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov004_0223ce84(void);
extern void *func_ov004_0223cd58(void *, unsigned);
extern unsigned func_ov004_0223c130(void);
extern int func_ov004_0220e5b8(void *);
extern int func_ov004_0220d2b8(void *);
extern void func_02052738(void *, int, int, int);
int func_ov004_0223c310(void)
{
    unsigned i = 0;
    int z = 0;
    void *e;
    for (i = 0; i < func_ov004_0223c130(); i++) {
        e = func_ov004_0223cd58(func_ov004_0223ce84(), i);
        if (e == 0) {
            continue;
        }
        if (func_ov004_0220e5b8(e) == 0) {
            continue;
        }
        if (func_ov004_0220d2b8((char *) e + 0x740) == 0) {
            continue;
        }
        func_02052738(e, z, 0xff, 1);
    }
    return 1;
}
