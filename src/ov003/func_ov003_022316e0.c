/* func_ov003_022316e0 @ 0x022316e0, 0x138 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_ov003_02233e4c(void *self, int *v);
extern void func_020550e4(void *p, int a);
extern void func_ov003_022353a4(void *self, int a, int b);
extern void func_02056fcc(void *p, int a, int b, int c, int d);

void func_ov003_022316e0(char *self, short *pn)
{
    int v[4];
    int *p;
    u8 c;
    int lim;
    u8 *q;
    int h;

    p = (int *) (self + 0x204);
    c = *(u8 *) (self + 0x254);
    func_ov003_02233e4c(self, v);
    if (v[0] == 0) {
        return;
    }
    if (*(u8 *) (self + 0x24a) != 0) {
        return;
    }
    lim = *(u8 *) (self + 0x255);
    if (c >= lim) {
        *(short *) (self + 0x23a) = v[0] > p[0] ? -0x6aac : 0x6aac;
        *(short *) (self + 0x238) = 0xd55;
        *(u8 *) (self + 0x251) = 7;
        *(u8 *) (self + 0x24a) = 1;
        func_020550e4(self + 0x50, 1);
        *pn = 0;
        func_ov003_022353a4(self, 1, 0);
        if (*(s8 *) (self + 0x24d) == 9) {
            func_02056fcc(self + 0xec, 9, 0, 0x1000, 0);
        }
    } else if (*(s8 *) (self + 0x24d) == 0x14) {
        if (c * 2 >= lim || *(u8 *) (self + 0x252) != 0) {
            if (((u32) * (int *) (self + 0xf4) << 4) >> 16 == 0) {
                func_02056fcc(self + 0xec, 4, 1, 0x1000, 0);
                *(u8 *) (self + 0x252) = 0x3c;
            } else {
                if (*(u8 *) (self + 0x252) != 0) {
                    *(u8 *) (self + 0x252) = *(u8 *) (self + 0x252) - 1;
                }
            }
        } else {
            h = *(int *) (self + 0xf4) >> 12;
            if ((u16) h != 0 || ((u32) * (int *) (self + 0xf0) << 4) >> 16 != 0) {
                func_02056fcc(self + 0xec, 0, 3, 0x1000, (u16) h);
            }
        }
    }
}
