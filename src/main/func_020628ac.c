/* func_020628ac @ 0x020628ac, 0xec bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void *func_0206e6ec(void *tbl);
extern u16 *func_0206e7bc(void *h, unsigned int idx);
extern int data_021cb5e0;

int func_020628ac(u16 *p)
{
    u16 v;
    int cond;
    int d;
    volatile u16 t;
    unsigned int idx;
    u16 *e;
    int r;
    u16 w;
    int cond2;
    int d2;

    cond = 0;
    v = *p;
    if (v >= 0x1000 && v <= 0x10ff) {
        cond = 1;
    }
    if (cond != 0) {
        if (v >= 0x1000 && v <= 0x10ff) {
            d = v - 0x1000;
        } else {
            d = -1;
        }
        d |= 3;
        t = ((unsigned int) d < 0x100) ? (u16) (d + 0x1000) : 0x1000;
        idx = t & 0xfff;
        if (idx >= 0x56e) {
            idx = 0x56d;
        }
        e = func_0206e7bc(func_0206e6ec(&data_021cb5e0), idx);
        if (e != 0) {
            r = *e;
        } else {
            r = 0;
        }
    } else {
        idx = v & 0xfff;
        if (idx >= 0x56e) {
            idx = 0x56d;
        }
        e = func_0206e7bc(func_0206e6ec(&data_021cb5e0), idx);
        if (e != 0) {
            r = *e;
        } else {
            r = 0;
        }
    }
    cond2 = 0;
    w = *p;
    if (w >= 0x1000 && w <= 0x10ff) {
        cond2 = 1;
    }
    if (cond2 != 0) {
        if (w >= 0x1000 && w <= 0x10ff) {
            d2 = w - 0x1000;
        } else {
            d2 = -1;
        }
        d2 &= 3;
        r = (u16) ((r * (d2 + 1)) >> 2);
    }
    return r;
}
