/* func_ov095_0229c750 @ 0x0229c750, 0x76 bytes, Thumb, module ov095
 * mwccarm 1.2/base -O4,s
 */

extern int _s32_div_f(int a, int b);

int func_ov095_0229c750(int unused, unsigned int y, unsigned int z)
{
    if (z < 0x68) {
        return -1;
    }
    if (z >= 0xa8) {
        return -1;
    }

    if (z >= 0x98) {
        if (y < 0x50) {
            goto fail3;
        }
        if (y >= 0xb0) {
            goto fail3;
        }
        return 0x91;
    fail3:
        return -1;
    }

    if (y < 8) {
        return -1;
    }
    if (y >= 0xf8) {
        return -1;
    }
    if (y < 0xd0) {
        int q = _s32_div_f(y - 8, 0x14);
        return q + (((int) z - 0x68) >> 4) * 10 + 0x70;
    }

    if (z >= 0x78) {
        return 0x90;
    }
    if (y < 0xe4) {
        return 0x8e;
    }
    return 0x8f;
}
