/* func_ov004_0223e878 @ 0x0223e878, 0x120 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_020b67d4(void);
extern int func_02073d90(void *);
extern void func_ov004_0223e3d4(void *, int);
extern void func_020ee470(void *);
extern int func_ov004_0223e3e0(void *);
extern char *func_020961a8(int);
extern int func_020ea990(void *, void *);
extern void *data_020ccf94;
extern char *data_ov004_02259a18[3];
extern u8 data_ov004_02259a08;
extern u8 data_ov004_02259a0c;

int func_ov004_0223e878(void *self)
{
    u8 mask;
    signed char sel;
    int i;

    if (func_020b67d4() == 0 || func_02073d90(data_020ccf94) != 0) {
        return 1;
    }

    mask = 0;
    sel = 0;
    for (i = 0; i < 3; i++) {
        char **slot = &data_ov004_02259a18[i];
        char *o = *slot;
        if (o == 0) {
            continue;
        }
        if (*(int *) (o + 8) == 0xffff) {
            *(int *) (o + 8) = 0;
            func_ov004_0223e3d4(*slot, 0);
            func_020ee470(*slot);
            *slot = 0;
            if (data_ov004_02259a08 != 0) {
                data_ov004_02259a08--;
                data_ov004_02259a0c--;
            }
        } else if (func_ov004_0223e3e0(o) == 1) {
            mask |= 1 << i;
            sel--;
        } else if (func_ov004_0223e3e0(*slot) == 2) {
            mask = 0xff;
        }
    }
    if (mask != 0xff && mask != 0) {
        char *o = func_020961a8(4);
        int best = 0x0fffffff;
        if (o != 0) {
            int j;
            char *p;
            p = o + 0x5c;
            for (j = 0; j < 3; j++) {
                if (data_ov004_02259a18[j] == 0) {
                    continue;
                }
                if (((mask >> j) & 1) == 0) {
                    continue;
                }
                if (sel == -1) {
                    sel = j;
                    break;
                } else {
                    int d = func_020ea990(p, data_ov004_02259a18[j] + 0x5c);
                    if (best > d) {
                        best = d;
                        sel = j;
                    }
                }
            }
        }
        func_ov004_0223e3d4(data_ov004_02259a18[sel], 2);
    }
    return 1;
}
