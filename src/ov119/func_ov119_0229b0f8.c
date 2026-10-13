/* func_ov119_0229b0f8 @ 0x0229b0f8, 0x90 bytes, Thumb, module ov119
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_02088d9c(u8 *p);
extern int func_02088d94(u8 *p);
extern u8 *data_ov119_0229cca8[];

int func_ov119_0229b0f8(u8 *self, int x, int y)
{
    int i;
    int t;

    t = func_02088d9c(data_ov119_0229cca8[0] + 8) + 0x83;
    if (t <= x) {
        t += 0x22;
        if (t >= x) {
            for (i = 0; i < 6; i++) {
                t = func_02088d94(data_ov119_0229cca8[i] + 8) + 0x61;
                if (t <= y) {
                    t += 0x12;
                    if (t >= y) {
                        i += 8;
                        return (u8) i;
                    }
                }
            }
        }
    }
    if (x >= 0x18 && x <= 0xc0 && y >= 0x30 && y < 0xb0) {
        int k = (y - 0x30) >> 4;
        if (k < self[0xaf]) {
            return (u8) k;
        }
    }
    if (x >= 0xc3 && x <= 0xf3 && y >= 0x9f && y <= 0xb5) {
        return 0x16;
    }
    return 0x17;
}
