/* func_0209ac50 @ 0x0209ac50, 0xdc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void *func_0209b0f0(void *);
extern int func_0209bd44(void *);
extern int func_0209b0c4(void *, void *);
extern void *func_0209ad9c(void *, int);
extern void *func_0209b4d4(void *);
extern void *func_0209bb70(void *);
extern int func_0204bcdc(void *);
extern int func_0204bc64(void *);
extern void *func_0209b4cc(void *, int);
extern int func_02003618(void *, void *);

int func_0209ac50(char *a0, void *a1, u16 *p)
{
    int result;
    unsigned int ok;
    unsigned int t;
    int mode;
    void *h;
    void *q;
    int eq;

    result = 0;
    ok = 0;
    if (*p >= 0x155f && *p <= 0x1560) {
        ok = 1;
    }
    if (ok != 0) {
        if (func_0209bd44(func_0209b0f0(a0 + 0x94)) != 0) {
            result = func_0209b0c4(a0 + 0x94, a1);
            goto end;
        }
    }
    mode = 0;
    t = 0;
    if (*p >= 0x1561 && *p <= 0x1564) {
        t = 1;
    }
    if (t != 0) {
        mode = 0;
    }
    h = func_0209ad9c(a0, mode);
    if (h != 0) {
        q = func_0209b4d4((void *) h);
        if (func_0209bd44(q) != 0) {
            q = func_0209bb70(q);
            if (func_0204bcdc(q) != 0) {
                eq = (func_0204bc64(q) == func_0204bc64(p)) ? 1 : 0;
            } else {
                eq = (*(u16 *) q == *p) ? 1 : 0;
            }
            if (eq != 0) {
                result = func_02003618(func_0209b4cc(h, 1), a1);
            }
        }
    }
end:
    return result;
}
