/* func_0207d788 @ 0x0207d788, 0xb8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_0208150c(void *a);
extern int func_0207f1c8(void *a);
extern int func_0209b5ec(int x);
extern int func_0209c2c0(int h);
extern int func_02003704(int t);
extern int func_0209c370(int h);
extern int func_0209c330(int h);
extern int func_0209c0a0(int h, s64 *d);
extern void func_0207f414(void *a, int ret, int e);
extern void MI_CpuCopy8(void *dst, void *src, int n);
extern int func_0209c020(int h, s64 *d);
extern int func_0207d840(void *a, s64 *d);

int func_0207d788(void *a, s64 *b, s64 *c, s64 *d)
{
    // DECLS
    int t;
    int e;
    int ret;
    int h;
    // ENDDECLS

    t = func_0208150c(a);
    h = func_0209b5ec(func_0207f1c8(a));
    ret = 0xc;
    e = func_0209c2c0(h);
    if (func_02003704(t)) {
        if (func_0209c370(h)) {
            switch (func_0209c330(h)) {
                case 0xb:
                    ret = func_0209c0a0(h, d);
                    if (ret != 0xc) {
                        func_0207f414(a, ret, e);
                    }
                    if (ret != 0xc) {
                        MI_CpuCopy8(d, b, 8);
                        if (*c != 0) {
                            MI_CpuCopy8(d, c, 8);
                        }
                    }
                    break;
                case 0xa:
                    ret = func_0209c020(h, d);
                    if (ret != 0xc) {
                        func_0207f414(a, ret, e);
                    }
                    break;
                default:
                    ret = func_0207d840(a, d);
                    break;
            }
        }
    }
    return ret;
}
