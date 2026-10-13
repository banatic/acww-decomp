/* func_ov004_0223c264 @ 0x0223c264, 0x50 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

// fn is tested twice; the second test is redundant in the original as well.
extern void *func_ov004_0223ce84(void);
extern void *func_ov004_0223cd58(void *, unsigned);
extern unsigned func_ov004_0223c130(void);
extern int func_ov004_0220d2b8(void *);
typedef int (*PF)(void *);
int func_ov004_0223c264(PF fn)
{
    unsigned n = 0, i;
    void *e;
    for (i = 0; i < func_ov004_0223c130(); i++) {
        e = func_ov004_0223cd58(func_ov004_0223ce84(), i);
        if (e == 0) {
            continue;
        }
        if (fn == 0 || (fn != 0 && fn(e) != 0 && func_ov004_0220d2b8((char *) e + 0x740) != 0)) {
            n++;
        }
    }
    return n;
}
