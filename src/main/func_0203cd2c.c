/* func_0203cd2c @ 0x0203cd2c, 0xa0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

// Looks the id up and hands back the byte holding its bit, plus the mask.
extern u8 *func_0203cdf8(int a, u8 *maskOut, u16 *p);

int func_0203cd2c(int a, u16 *p, int mode, int set)
{
    u8 mask;
    u8 *slot;

    if (mode == 0) {
        unsigned int ok = 0;
        u16 v = *p;
        if (v >= 0x12e8 && v <= 0x131f) {
            ok = 1;
        }
        if (ok || (v >= 0x12b0 && v <= 0x12e7) || (v >= 0x4384 && v <= 0x4463) || (v >= 0x42a4 && v <= 0x4383)) {
            return 0;
        }
    }
    slot = func_0203cdf8(a, &mask, p);
    if (slot != 0) {
        if (set != 0) {
            *slot |= mask;
        } else {
            *slot &= ~mask;
        }
        return 1;
    }
    return 0;
}
