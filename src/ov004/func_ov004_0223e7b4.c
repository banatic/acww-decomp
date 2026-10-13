/* func_ov004_0223e7b4 @ 0x0223e7b4, 0x80 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void *data_020ccf94;
extern int func_02073d90(void *);
extern u8 data_ov004_02259a08;
extern u8 data_ov004_02259a0c;
extern void *data_ov004_02259a10;
extern int data_ov004_02259a18[];
extern int func_02003348(int, int, void *, void *, void *);

int func_ov004_0223e7b4(void *a, void *b)
{
    int ok = 0;
    int i;
    int *p;
    if (func_02073d90(data_020ccf94) != 0) {
        return ok;
    }
    if (data_ov004_02259a08 < 3 && (int) data_ov004_02259a0c - (int) data_ov004_02259a08 > 0) {
        i = ok;
        p = data_ov004_02259a18;
        for (; i < 3; i++) {
            if (p[i] == 0) {
                p[i] = func_02003348(0xc0, 0, a, b, data_ov004_02259a10);
                data_ov004_02259a08 = (u8) (data_ov004_02259a08 + 1);
                ok = 1;
                break;
            }
        }
    }
    return ok;
}
