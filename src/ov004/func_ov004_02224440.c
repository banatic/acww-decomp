/* func_ov004_02224440 @ 0x02224440, 0x104 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_020984e8(int a);
extern int func_02099670(int a);
extern int func_020a12e8(void);
extern int func_0200338c(int a, int b);
extern int func_02073d90(void *p);
extern short *func_0209d358(int a, int b);
extern int func_020644cc(int n);
extern int func_0202ea80(int a, int b);
extern int func_ov068_02273974(int a);
extern int func_02088bd4(int a);
extern int func_020960f8(int a, int b);
extern void func_0208b520(void);
extern int data_ov004_02254594[2];
extern u8 data_ov004_02254508[];
extern void *data_020ccf94;

void func_ov004_02224440(int arg, char *out)
{
    // DECLS
    int a;
    int b;
    int c;
    // ENDDECLS

    a = func_02099670(func_020984e8(arg));
    if (func_020a12e8() != 0) {
        *(int *) out = data_ov004_02254594[1];
        out[4] = 0x1f;
        return;
    }
    *(int *) out = data_ov004_02254594[0];
    b = func_0200338c(0x66, 0);
    if (func_02073d90(data_020ccf94) != 0 || *func_0209d358(0, 0x4a) != 0) {
        out[4] = (char) (func_020644cc(3) + 0x55);
        return;
    }
    if (func_0202ea80(0x17, 0) != 0) {
        if (b != 0 && func_ov068_02273974(b) == 7) {
            out[4] = 0x58;
            return;
        }
        c = func_02088bd4(a) >> 2;
        out[4] = (char) (data_ov004_02254508[c] + func_020644cc(3));
        return;
    }
    if (func_020960f8(0x28, 4) == 0) {
        if (func_0202ea80(0x16, 1) == 0) {
            out[4] = (char) (func_02088bd4(a) >> 1);
            return;
        }
        if (b != 0 && func_ov068_02273974(b) == 7) {
            out[4] = 0x58;
            return;
        }
        out[4] = (char) ((func_02088bd4(a) >> 2) + 0x49);
        return;
    }
    if (func_0202ea80(0x17, 0) == 0) {
        func_0208b520();
    }
    out[4] = (char) ((func_02088bd4(a) >> 2) + 0x14);
}
