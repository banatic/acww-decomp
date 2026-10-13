/* func_ov004_022108d0 @ 0x022108d0, 0xfc bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_ov004_0223cf68(void *p);
extern void func_ov004_0220ecec(void *self);
extern void func_ov004_0220f994(void *self);
extern int func_ov004_0220cdf8(void *self);
extern int func_ov004_0220cdec(void *self);
extern void func_ov004_0220d2bc(void *p, void *self);
extern void func_ov004_0220e028(void *p);
extern void func_0209d200(void *d, void *p);
extern int func_ov004_0220e758(void *self, int *x, int *y, int a, int b);
extern int func_020b65c4(void);
extern int func_ov004_0223d348(void);
extern int func_020b6694(int v);
extern int func_020b67e8(int v);
extern void func_ov004_0220f100(void *self, int a, int b);
extern void func_0204f538(void *g, u16 *t, int x, int y, int k);
extern void func_ov004_0220e640(void *self);
extern int *func_ov004_0223ce84(void);
extern void func_ov004_0223cde8(int *a, void *self);
extern void func_02003510(void *self, int mode);
extern int data_ov004_02259698;
extern void *data_021c80bc;

void func_ov004_022108d0(char *self, int mode)
{
    u16 t;
    int x;
    int y;
    int v;
    void *g;

    if (mode == 2) {
        func_ov004_0223cf68(self + 0x798);
        func_ov004_0220ecec(self);
        func_ov004_0220f994(self);
        if (func_ov004_0220cdf8(self) == 0 && func_ov004_0220cdec(self) == 0) {
            func_ov004_0220d2bc(self + 0x740, self);
        }
        func_ov004_0220e028(self + 0x6cc);
        func_0209d200(&data_ov004_02259698, self + 0x132);
        if (func_ov004_0220cdf8(self) != 0) {
            func_ov004_0220e758(self, &x, &y, 0, 0);
            v = func_020b65c4();
            if (func_ov004_0223d348() != 0 && func_020b6694(v) == 0 && func_020b67e8(v) == 0) {
                g = data_021c80bc;
                func_ov004_0220f100(self, 0, 0);
                if (g != 0) {
                    t = 0x1547;
                    func_0204f538(g, &t, x, y, 0);
                }
            } else {
                func_ov004_0220f100(self, 1, 0);
            }
            func_ov004_0220e640(self);
        }
        func_ov004_0223cde8(func_ov004_0223ce84(), self);
    }
    func_02003510(self, mode);
}
