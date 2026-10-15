/* func_ov004_02216fb0 @ 0x02216fb0, 0x5e bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void *func_ov004_0223cb10(void);
extern void *func_ov004_0223ca9c(void *a, void *self);
extern int func_ov004_02217230(void *self);
extern int func_ov004_0223cb18(void *h);
extern char *func_ov004_0223cb24(void *h);
extern int func_ov004_0222c030(int *v, char *a, char *b, u16 *t);

int func_ov004_02216fb0(void *self)
{
    u16 t;
    int v;
    void *h;
    char *a;

    h = func_ov004_0223ca9c(func_ov004_0223cb10(), self);
    v = func_ov004_02217230(self);
    if (v != -1) {
        t = func_ov004_0223cb18(h);
        a = func_ov004_0223cb24(h);
        if (func_ov004_0222c030(&v, a, func_ov004_0223cb24(h) + 8, &t)) {
            return 1;
        }
        return 0;
    }
    return 1;
}
