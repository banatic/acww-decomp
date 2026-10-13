/* func_ov095_0229c7c8 @ 0x0229c7c8, 0x11c bytes, Thumb, module ov095
 * mwccarm 1.2/base -O4,s
 */

int func_ov095_0229c7c8(int a, unsigned int b, unsigned int c)
{
    if (c < 0x60) {
        return -1;
    }
    if (c >= 0xb0) {
        return -1;
    }
    if (c < 0x70) {
        if (b < 4) {
            return -1;
        }
        if (b >= 0xf4) {
            return -1;
        }
        return (int) (b - 4) / 20 + 0x3b;
    }
    if (c < 0x80) {
        if (b < 0xc) {
            return -1;
        }
        if (b >= 0xfc) {
            return -1;
        }
        if (b >= 0xd4) {
            return 0x51;
        }
        return (int) (b - 0xc) / 20 + 0x47;
    }
    if (c < 0x90) {
        if (b < 4) {
            return -1;
        }
        if (b < 0x18) {
            return 0x52;
        }
        if (b >= 0xfc) {
            return -1;
        }
        if (b >= 0xcc) {
            return 0x5c;
        }
        return (int) (b - 0x18) / 20 + 0x53;
    }
    if (c < 0xa0) {
        if (b < 4) {
            return -1;
        }
        if (b < 0x20) {
            return 0x5d;
        }
        if (b >= 0xe8) {
            return -1;
        }
        return (int) (b - 0x20) / 20 + 0x5e;
    }
    if (c < 0xb0) {
        if (b < 0x18) {
            return -1;
        }
        if (b >= 0x40 && b < 0xcc) {
            return 0x6b;
        }
        if (b < 0x54) {
            return (int) (b - 0x18) / 20 + 0x68;
        }
        if (b >= 0xf4) {
            return -1;
        }
        return (int) (b - 0xa4) / 20 + 0x6c;
    }
    return -1;
}
