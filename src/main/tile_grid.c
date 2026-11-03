/* tile_grid: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02084e68 @ 0x02084e68, 0x28 bytes, Thumb
 * func_02084e40 @ 0x02084e40, 0x28 bytes, Thumb
 * func_02084e20 @ 0x02084e20, 0x1e bytes, Thumb
 * func_02084e00 @ 0x02084e00, 0x1e bytes, Thumb
 */

int func_02084e68(unsigned short *arg0, unsigned int arg1, unsigned int arg2)
{
    if (arg1 < 16 && arg2 < 16) {
        arg0[arg2] |= (1u << arg1);
        return 1;
    } else {
        return 0;
    }
}

int func_02084e40(unsigned short *arr, unsigned int bit, unsigned int index)
{
    unsigned short val;
    if (bit < 16 && index < 16) {
        val = arr[index];
        val &= ~(1 << bit);
        arr[index] = val;
        return 1;
    }
    return 0;
}

int func_02084e20(unsigned short *arr, unsigned int x, unsigned int y)
{
    if (x < 16 && y < 16) {
        if ((arr[y] >> x) & 1) {
            return 1;
        } else {
            return 0;
        }
    } else {
        return 0;
    }
}

int func_02084e00(unsigned short *p, unsigned int bit, unsigned int idx)
{
    if (bit < 0x10 && idx < 0xe) {
        if (((p[idx] >> bit) & 1) != 0) {
            return 1;
        }
        return 0;
    }
    return 0;
}
