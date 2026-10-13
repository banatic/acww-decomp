/* func_ov068_02271398 @ 0x02271398, 0xfc bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_ov003_02234cc4(u8 *self);
extern int func_ov003_02234d70(u8 *self);
extern void func_ov003_022353a4(u8 *self, int a, int b);
extern int func_ov068_022701b0(u8 *self, s16 *buf);
extern void func_ov068_0226fea4(u8 *self, s16 *buf, int c, int d, int e, int f);
extern int FX_Div(int a, int b);
extern int func_020644cc(int a);
extern void func_ov003_02234dac(u8 *self, int f232, int c, int d);

void func_ov068_02271398(u8 *self)
{
    s16 buf;
    s16 f232;

    buf = *(s16 *) (self + 0x23a);
    f232 = *(s16 *) (self + 0x232);

    func_ov003_02234cc4(self);

    if (func_ov003_02234d70(self) == 2) {
        self[0x24a] = 0;
    }

    func_ov003_022353a4(self, 0, 1);

    if (self[0x24a] == 0) {
        if (func_ov068_022701b0(self, &buf) == 0) {
            if (*(s8 *) (self + 0x24d) == 0xa) {
                *(s16 *) (self + 0x242) = 0;
                self[0x251] = 9;
                return;
            }
        }
    }

    func_ov068_0226fea4(self, &buf, 0xaaa, 0x1e, 0x46, ((int) self[0x257]) << 12);

    if (*(s8 *) (self + 0x24d) == 0xa) {
        int r;
        int r2;

        r = FX_Div(0x12000, 0x10000);
        r2 = func_020644cc(8);
        func_ov003_02234dac(self, f232, r, (r2 + 0xa) << 12);
        *(s16 *) (self + 0x232) = f232 + 0xaaa;
    } else {
        int r2;

        r2 = func_020644cc(8);
        func_ov003_02234dac(self, f232, 0x19a, (r2 + 0x12) << 12);
        *(s16 *) (self + 0x232) = f232 + 0x1554;
    }
}
