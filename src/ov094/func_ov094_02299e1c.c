/* func_ov094_02299e1c @ 0x02299e1c, 0x124 bytes, Thumb, module ov094
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void *func_020984e8(void);
extern void *func_02099870(void *a);
extern int func_020950c0(void *a);
extern u16 *func_02099728(void *a);
extern void func_ov094_02299dcc(void *self, int ret, int b);

void func_ov094_02299e1c(void *self)
{
    void *a;
    u16 *p;
    int b;
    unsigned int v;
    int ret;
    int ok;

    a = func_020984e8();
    b = func_020950c0(func_02099870(a));
    p = func_02099728(a);
    ret = 0;
    ok = 0;
    v = *p;
    if (v >= 0x1369 && v <= 0x1369) {
        ok = 1;
    }
    if (ok || (v >= 0x136a && v <= 0x136a)) {
        ret = 1;
    } else if ((v >= 0x136b && v <= 0x1372) || (v >= 0x1373 && v <= 0x1373)) {
        ret = 2;
    } else if ((v >= 0x1374 && v <= 0x1374) || (v >= 0x1375 && v <= 0x1375)) {
        ret = 3;
    } else if ((v >= 0x1380 && v <= 0x139f) || (v >= 0x13a0 && v <= 0x13a7)) {
        ret = 4;
    } else if ((v >= 0x1377 && v <= 0x1377) || (v >= 0x1376 && v <= 0x1376)) {
        ret = 5;
    } else if ((v >= 0x1379 && v <= 0x1379) || (v >= 0x1378 && v <= 0x1378)) {
        ret = 6;
    } else if ((v >= 0x137a && v <= 0x137a) || (v >= 0x137b && v <= 0x137b)) {
        ret = 7;
    }
    func_ov094_02299dcc(self, ret, b);
}
