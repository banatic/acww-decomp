/* func_0209ccd4 @ 0x0209ccd4, 0x12c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void *func_0209cc30(int a, u32 b, u32 c);
extern int func_0209d030(int *);
extern int func_02037c0c(u32 a);
extern int func_020644cc(u32 a);
extern void func_0209d02c(void *a, u32 b);
extern void MI_CpuFill8(void *dst, int val, int size);

int func_0209ccd4(int param)
{
    int ret = 1;
    u32 sp8 = 0;
    u32 spc;
    u32 sp10;
    u32 sp14 = 0;
    u32 sp18 = 0;
    u32 sp1c = 0;
    u32 sp20 = 0;
    u32 sp24 = 0;
    u32 sp28 = 0;
    u32 sp2c = 0;
    int sp30 = 0;
    unsigned char sp34[0x86];
    u32 r6;
    int r7;
    u32 r5, r4;
    void *res;

    MI_CpuFill8(sp34, 0, 0x86);

    for (sp8 = 0; sp8 < 6; sp8++) {
        for (r6 = sp14; r6 < 6; r6++) {
            r7 = func_0209d030((int *) func_0209cc30(param, r6, sp8));

            r5 = sp18;
            r4 = r5;
            do {
                if (r7 == func_02037c0c(r4) && sp34[r4] == 0) {
                    r5++;
                }
                r4++;
            } while (r4 < 0x86);

            if (r5 != 0) {
                spc = func_020644cc(r5);
                r4 = sp1c;
                r5 = r4;
                while (r5 < 0x86) {
                    if (r7 == func_02037c0c(r5) && sp34[r5] == 0) {
                        if (r4 == spc) {
                            goto found1;
                        }
                        r4++;
                    }
                    r5++;
                }
                r5 = sp20;
            found1:
                res = func_0209cc30(param, r6, sp8);
                func_0209d02c(res, r5);
                sp34[r5] = 1;
            } else {
                r5 = sp24;
                r4 = r5;
                do {
                    if (r7 == func_02037c0c(r4)) {
                        r5++;
                    }
                    r4++;
                } while (r4 < 0x86);

                if (r5 != 0) {
                    sp10 = func_020644cc(r5);
                    r4 = sp28;
                    r5 = r4;
                    while (r5 < 0x86) {
                        if (r7 == func_02037c0c(r5)) {
                            if (r4 == sp10) {
                                goto found2;
                            }
                            r4++;
                        }
                        r5++;
                    }
                    r5 = sp2c;
                found2:
                    res = func_0209cc30(param, r6, sp8);
                    func_0209d02c(res, r5);
                    sp34[r5] = 1;
                } else {
                    ret = sp30;
                    res = func_0209cc30(param, r6, sp8);
                    func_0209d02c(res, 0x14);
                }
            }
        }
    }
    return ret;
}
