/* func_ov123_0229ac80 @ 0x0229ac80, 0x148 bytes, Thumb, module ov123
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_ov123_0229adc8(int a, u8 b, u8 c, int d);
extern void func_ov123_0229a148(int a, u8 b, u8 c, int d);

int func_ov123_0229ac80(int a, u8 b, u8 c, int d, int e)
{
    int result = 0;

    if (e < 0 || e > 3) {
        return 0;
    }

    switch (e) {
        case 0:
            result |= func_ov123_0229adc8(a, b, c, d);
            break;

        case 1:
            result |= func_ov123_0229adc8(a, b, c, d);
            {
                int bm1 = b - 1;
                result |= func_ov123_0229adc8(a, (u8) bm1, c, d);
                {
                    int cm1 = c - 1;
                    result |= func_ov123_0229adc8(a, b, (u8) cm1, d);
                    result |= func_ov123_0229adc8(a, (u8) bm1, (u8) cm1, d);
                }
            }
            break;

        case 2: {
            int cm1 = c - 1;
            int bm1 = b - 1;
            result |= func_ov123_0229adc8(a, (u8) bm1, (u8) cm1, d);
            result |= func_ov123_0229adc8(a, b, (u8) cm1, d);
            {
                int bp1 = b + 1;
                result |= func_ov123_0229adc8(a, (u8) bp1, (u8) cm1, d);
                result |= func_ov123_0229adc8(a, (u8) bm1, c, d);
                result |= func_ov123_0229adc8(a, b, c, d);
                result |= func_ov123_0229adc8(a, (u8) bp1, c, d);
                {
                    int cp1 = c + 1;
                    result |= func_ov123_0229adc8(a, (u8) bm1, (u8) cp1, d);
                    result |= func_ov123_0229adc8(a, b, (u8) cp1, d);
                    result |= func_ov123_0229adc8(a, (u8) bp1, (u8) cp1, d);
                }
            }
        } break;

        case 3:
            func_ov123_0229a148(a, b, c, d);
            break;
    }

    return result;
}
