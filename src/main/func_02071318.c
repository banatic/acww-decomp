/* func_02071318 @ 0x02071318, 0xd4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_02071318(int base, unsigned short *pid, int *out)
{
    unsigned int ok = 0;
    unsigned short id = *pid;
    int v;

    if (id >= 0x450c && id <= 0x45db) {
        ok = 1;
    }
    if (ok != 0) {
        if (out != 0) {
            if (id >= 0x450c && id <= 0x45db) {
                v = (id - 0x450c) >> 2;
            } else {
                v = -1;
            }
            *out = v;
        }
        return base;
    }
    if (id >= 0x3894 && id <= 0x38e3) {
        if (out != 0) {
            if (id >= 0x3894 && id <= 0x38e3) {
                v = (id - 0x3894) >> 2;
            } else {
                v = -1;
            }
            *out = v;
        }
        return base + 0x55;
    }
    if (id >= 0x12b0 && id <= 0x12e7) {
        if (out != 0) {
            if (id >= 0x12b0 && id <= 0x12e7) {
                v = id - 0x12b0;
            } else {
                v = -1;
            }
            *out = v;
        }
        return base + 0x38;
    }
    if (id >= 0x12e8 && id <= 0x131f) {
        if (out != 0) {
            if (id >= 0x12e8 && id <= 0x131f) {
                v = id - 0x12e8;
            } else {
                v = -1;
            }
            *out = v;
        }
        return base + 0x1b;
    }
    return 0;
}
