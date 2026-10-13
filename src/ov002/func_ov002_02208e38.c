/* func_ov002_02208e38 @ 0x02208e38, 0x120 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void *func_020984e8(void);
extern void *func_02099870(void *a);
extern int func_0209871c(void *tbl, void *x);
extern int func_020988a4(void *tbl, int t);
extern void *func_0207cec0(void *tbl, int t);
extern int func_0207cee4(void *tbl, int t);
extern int func_020807a8(void *e, void *x);
extern char data_021dc7bc[];
extern char data_021e5a2c[];

void func_ov002_02208e38(u8 *self)
{
    void *x;
    int n;
    int i;
    int j;
    int t;
    int k;

    self[0x1d] = 0;
    for (i = 0; i < 0x19; i++) {
        u8 *p = self + i;

        p[0x3cc] = 0;
    }
    x = func_02099870(func_020984e8());
    n = func_0209871c(data_021dc7bc, x);
    k = 0;
    for (j = 1, t = k; j < 5; j++, t++) {
        if (n != t && func_020988a4(data_021dc7bc, t)) {
            u8 *p = self + k;

            p[0x3cc] = j;
            k++;
        }
    }
    if (k % 5 == 4) {
        u8 *p = self + k;

        p[0x3cc] = 0xe;
        k++;
    }
    for (j = 5, t = 0; j < 0xd; j++, t++) {
        if (func_0207cee4(data_021e5a2c, t) && func_020807a8(func_0207cec0(data_021e5a2c, t), x)) {
            u8 *p = self + k;

            p[0x3cc] = j;
            k++;
        }
        if (k % 5 == 4) {
            u8 *p = self + k;

            p[0x3cc] = 0xe;
            k++;
        }
    }
    if (k % 5 != 0) {
        u8 *p = self + k;

        p[0x3cc] = 0xe;
        k++;
    }
    while (k % 5 != 0) {
        u8 *p = self + k;

        p[0x3cc] = 0;
        k++;
    }
    {
        u8 *p = self + k;

        p[0x3cc] = 0xd;
    }
    {
        u8 *p = self + (k + 1);

        p[0x3cc] = 0xf;
    }
    k += 2;
    if (k > 2) {
        u8 *p = self + k;

        p[0x3cc] = 0xe;
        k++;
    }
    self[0x1d] = (k + 4) / 5;
}
