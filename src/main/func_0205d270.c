/* func_0205d270 @ 0x0205d270, 0xfc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern char data_021c9d1c;

extern void func_0205d598(unsigned short *dst, void *addr, int b);
extern int func_0204bcdc(void *b);
extern int func_0204bc64(void *ptr);
extern void *func_0205d5a8(void *addr, int b);
extern int func_0203cfc0(void);
extern void MI_CpuCopy8(void *a, void *b, int n);
extern void func_0205d58c(void *addr, unsigned char b, unsigned short *out);

void func_0205d270(unsigned char *a, int k)
{
    u16 loc[2];
    unsigned char byte;
    int f;
    u16 a0, a1;
    int r;
    void *p1, *p2;

    byte = *a;
    if (k == byte) {
        return;
    }

    func_0205d598(&loc[0], &data_021c9d1c, k);
    func_0205d598(&loc[1], &data_021c9d1c, byte);

    f = 0;
    a0 = *(volatile u16 *) &loc[0];
    a1 = *(volatile u16 *) &loc[0];
    if (a1 >= 0x12a8 && a0 <= 0x12af) {
        f = 1;
    }
    if (f != 0) {
        if (a0 >= 0x1429 && a0 <= 0x1430) {
            f = 1;
        } else {
            f = 0;
        }
        if (f != 0) {
            if (a0 >= 0x13a0 && a0 <= 0x13a7) {
                f = 1;
            } else {
                f = 0;
            }
            if (f != 0) {
                goto skip;
            }
        }
    }

    if (func_0204bcdc(&loc[0]) != 0) {
        if (func_0204bc64(&loc[0]) == func_0204bc64(&loc[1])) {
            r = 1;
        } else {
            r = 0;
        }
    } else {
        if (loc[0] == loc[1]) {
            r = 1;
        } else {
            r = 0;
        }
    }
    if (r != 0) {
        return;
    }

skip:
    p1 = func_0205d5a8(&data_021c9d1c, k);
    p2 = func_0205d5a8(&data_021c9d1c, byte);
    if (p1 == 0) {
        return;
    }
    if (p2 == 0) {
        return;
    }
    MI_CpuCopy8(p1, p2, func_0203cfc0());
    func_0205d58c(&data_021c9d1c, byte, &loc[0]);
}
