/* func_ov003_0222a088 @ 0x0222a088, 0xe4 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_ov003_02229f2c(char *self, int *a, int *b, int *c);

int func_ov003_0222a088(char *self)
{
    int x;
    int y;
    int z;
    int ok = 1;
    func_ov003_02229f2c(self, &x, &y, &z);
    switch (*(u8 *) (self + 0x1fe)) {
        case 0:
        case 1:
        case 2:
        case 3:
            if (((x >= 0xb && x <= 0x12) || x == 7 || x == 0x14) && ((y >= 0xb && y <= 0x12) || y == 7 || y == 0x14) &&
                ((z >= 0xb && z <= 0x12) || z == 7 || z == 0x14)) {
                ok = 0;
            }
            break;
        case 5:
        case 6:
            if ((x == 8 || x == 0x17) && (y == 8 || y == 0x17) && (z == 8 || z == 0x17)) {
                ok = 0;
            }
            break;
        default:
            if (((x >= 0xb && x <= 0x12) || x == 8 || x == 7 || x == 0x14) &&
                ((y >= 0xb && y <= 0x12) || y == 8 || y == 7 || y == 0x14) &&
                ((z >= 0xb && z <= 0x12) || z == 8 || z == 7 || z == 0x14)) {
                ok = 0;
            }
            break;
    }
    return ok;
}
