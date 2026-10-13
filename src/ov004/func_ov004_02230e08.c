/* func_ov004_02230e08 @ 0x02230e08, 0x60 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_0206fbc0(void);
extern void *func_020682e0(int);
extern int func_0206fc6c(void);
extern void func_0206844c(void *, u8 *, void *);
extern int func_020b65c4(void);
extern void func_ov004_0223121c(void *, int);
extern int data_ov004_022558ac;

void func_ov004_02230e08(void *self)
{
    u8 b;
    if (func_0206fbc0() != 0) {
        void *h = func_020682e0(0);
        b = 0x10;
        if (func_0206fc6c() == 0) {
            b = 0x18;
        }
        func_0206844c(h, &b, &data_ov004_022558ac);
        *(int *) ((char *) h + 8) = 1;
        if (func_020b65c4() == 6) {
            func_ov004_0223121c(self, 0xc);
        } else {
            func_ov004_0223121c(self, 4);
        }
    }
}
