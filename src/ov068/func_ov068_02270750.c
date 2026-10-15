/* func_ov068_02270750 @ 0x02270750, 0x140 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_ov003_02232414(u8 *self);
extern void func_ov003_022353a4(u8 *self, int a, int b);
extern int func_ov003_02234984(u8 *self);
extern int func_020644cc(int a);
extern int FX_Div(int a, int b);
extern int FX_MulFunc(int a, int b);
extern u8 *func_020961a8(int a);
extern int func_0200322c(void *a, void *b);
extern int func_ov003_02235950(void *a);

void func_ov068_02270750(u8 *self, s16 *buf, int mode)
{
    func_ov003_02232414(self);

    if (self[0x251] == 4) {
        func_ov003_022353a4(self, 0, 1);
        if (func_ov003_02234984(self) != 0) {
            self[0x251] = 0x13;
            *(s16 *) (self + 0x244) = 0x14 * (func_020644cc(9) + 2);
        }
    } else if (self[0x251] == 5) {
        if (*(s8 *) (self + 0x24d) == 0x36 && (*buf > 0 || (self[0x24f] % 10 == 0 && func_020644cc(100) > 75))) {
            s16 v = *buf;
            int t = FX_MulFunc(FX_Div(0x1000, 0x12000), v << 12);
            *(int *) (self + 0x208) = *(int *) (self + 0x208) + (t + -10 * (v * v));
            if (*buf == 0) {
                u8 *q = func_020961a8(4);
                if (q != 0) {
                    *(s16 *) (self + 0x23a) = func_0200322c(self + 0x204, q + 0x5c);
                    func_ov003_022353a4(self, 1, 0);
                }
            }
            *buf = *buf + 3;
            if (*buf > 3) {
                if (func_ov003_02235950(self + 0x204) == 0) {
                    if (*(int *) (self + 0x208) <= 0) {
                        *buf = 0;
                    }
                }
            }
        } else {
            func_ov003_022353a4(self, 0, 1);
        }
        if (*(s8 *) (self + 0x24d) == 0x37 || *buf == 0) {
            if (mode != 2) {
                self[0x251] = 0x13;
                *buf = 0;
            }
        }
    }
}
