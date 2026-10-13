/* func_ov004_02216360 @ 0x02216360, 0x64 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_0206fbc0(void);
extern int func_0206fc6c(void);
extern u16 func_0206f668(void);
extern void func_0205265c(void *self, int a, u8 b, int c);
extern void func_0203e020(void *self);

void func_ov004_02216360(void *self)
{
    volatile u16 t;
    int ok;
    u16 v;
    int k;

    if (func_0206fbc0()) {
        if (func_0206fc6c()) {
            t = func_0206f668();
            ok = 0;
            v = t;
            if (v >= 0x1323 && v <= 0x1368) {
                ok = 1;
            }
            if (ok) {
                k = v - 0x1323;
            } else {
                k = -1;
            }
            func_0205265c(self, 1, (u8) k, 1);
        }
        func_0203e020(self);
    }
}
