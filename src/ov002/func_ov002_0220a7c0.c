/* func_ov002_0220a7c0 @ 0x0220a7c0, 0x11c bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

int func_ov002_0220a7c0(void *self, int i, int x, int y)
{
    switch (i) {
        case 1:
            if (x >= 0xc0 && y >= 0x95 && y < 0xa5) {
                return 1;
            }
            return 0;
        case 2:
            if (x >= 0xc0 && y >= 0xa9 && y < 0xb9) {
                return 1;
            }
            return 0;
        case 0:
            if (x >= 0x52 && x <= 0xba && y >= 0xac && y <= 0xc0) {
                return 1;
            }
            return 0;
        case 3:
            if (y >= 0xa4 && y < 0xb4 && x >= 0x38 && x <= 0x68) {
                return 1;
            }
            return 0;
        case 4:
            if (y >= 0xa4 && y < 0xb4 && x >= 0x98 && x <= 0xc8) {
                return 1;
            }
            return 0;
        case 5:
            if (y >= 0xac && y <= 0xc0 && x >= 0 && x <= 0x40) {
                return 1;
            }
            return 0;
        case 6:
            if (y >= 0xac && y <= 0xc0 && x >= 0xc0 && x <= 0x100) {
                return 1;
            }
            return 0;
        case 7:
            if (y >= 0xac && y <= 0xc0 && x >= 0x78 && x <= 0xb8) {
                return 1;
            }
            return 0;
        case 8:
            if (x >= 0x6a && x <= 0xbc && y >= 0xac && y <= 0xc0) {
                return 1;
            }
            return 0;
        case 9:
            if (x >= 0xc0 && y >= 0 && y >= 0xac && y <= 0xc0) {
                return 1;
            }
            return 0;
    }
    return 0;
}
