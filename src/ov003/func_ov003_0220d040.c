/* func_ov003_0220d040 @ 0x0220d040, 0x168 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void *data_021c80bc;

extern int func_ov003_0220c934(void *self);
extern void func_0200fa6c(int *dst, void *self);
extern void func_0204f818(int *a, int *b, int *local);
extern int func_020310d0(int *local, int *v, int c);
extern u16 *func_0204f5a8(void *g, int *local, int zero);
extern int func_0200fdd0(void *self, int *t, int c, u8 p2);

int func_ov003_0220d040(void *self, u8 *p1, u8 *p2, int *out)
{
    int out0;
    int out1;
    int v;
    int temp[2];
    int local[4];
    int r7;
    int r4 = 1;

    if (*p1 != 0) {
        if (func_ov003_0220c934(self) != 0) {
            return 4;
        }
    }

    func_0200fa6c(local, self);
    func_0204f818(&out0, &out1, local);
    if (out != 0) {
        out[0] = out0;
        out[1] = out1;
    }

    r7 = func_020310d0(local, &v, 0x19);

    if (v != 4) {
        if (v != 6) {
            goto label_0x220d182;
        }

        if (data_021c80bc != 0) {
            u16 *p = func_0204f5a8(data_021c80bc, local, 0);
            int r3 = 1;
            int r2 = r3;
            int r6 = r3;
            int r1 = 0;
            u16 val = *p;

            if (val >= 0x2b && val <= 0x2e) {
                r1 = r3;
            }
            if (r1 == 0) {
                if (val < 0xff || val > 0x102) {
                    r6 = 0;
                }
            }
            if (r6 == 0) {
                if (val < 0x62 || val > 0x65) {
                    r2 = 0;
                }
            }
            if (r2 == 0) {
                if (val < 0xd0 || val > 0xd3) {
                    r3 = 0;
                }
            }
            if (r3 != 0) {
                return 1;
            }
        }
    }

    if (*p1 != 0) {
        if (r7 < 0x1000) {
            return 1;
        }
        temp[0] = 0;
        temp[1] = 0;
        temp[0] = out0;
        temp[1] = out1;
        switch (func_0200fdd0(self, temp, 1, *p2)) {
            case 0:
                return 5;
            case 1:
                return 0;
            case 2:
                return 4;
            default:
                break;
        }
    }

    if (*(int *) ((char *) self + 0x818) == 1) {
        switch (*(int *) ((char *) self + 0x814)) {
            case 6:
                r4 = 2;
                break;
            case 7:
                r4 = 3;
                break;
            case 12:
            case 13:
                r4 = 4;
                break;
            case 14:
                r4 = 6;
                break;
            default:
                break;
        }
    } else if (*(int *) ((char *) self + 0x818) == 2) {
        r4 = 5;
    } else {
        r4 = 0;
    }
    goto return_r4;

label_0x220d182:
    if (r7 >= 0x1000) {
        r4 = 4;
    }

return_r4:
    return r4;
}
