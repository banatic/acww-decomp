/* func_ov118_0229b68c @ 0x0229b68c, 0x52 bytes, Thumb, module ov118
 * mwccarm 1.2/base -O4,s
 */

unsigned int func_ov118_0229b68c(void *self, unsigned int x, int idx)
{
    if (x == 0) {
        return 7;
    }
    if (x < 6) {
        return 0;
    }
    if (x >= 6 && x < 14) {
        return 1;
    }
    switch (x - 14) {
        case 2:
            return 2;
        case 0:
            return 3;
        case 3:
            return 4;
        case 1:
            return 5;
        case 4:
            return 6;
        default:
            return 7;
    }
}
