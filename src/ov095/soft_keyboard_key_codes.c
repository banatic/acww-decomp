/* soft_keyboard_key_codes: 7 functions, module ov095
 * mwccarm 1.2/base -O4,s
 * func_ov095_0229c548 @ 0x0229c548, 0x4 bytes, Thumb
 * func_ov095_0229c52c @ 0x0229c52c, 0x1c bytes, Thumb
 * func_ov095_0229c510 @ 0x0229c510, 0x1c bytes, Thumb
 * func_ov095_0229c4f4 @ 0x0229c4f4, 0x1c bytes, Thumb
 * func_ov095_0229c4d8 @ 0x0229c4d8, 0x1c bytes, Thumb
 * func_ov095_0229c4bc @ 0x0229c4bc, 0x1c bytes, Thumb
 * func_ov095_0229c448 @ 0x0229c448, 0x74 bytes, Thumb
 */

extern unsigned short data_ov095_0229e874[];
extern short data_ov095_0229e8e0[];
extern short data_ov095_0229e774[];
extern short data_ov095_0229e7b8[];

int func_ov095_0229c548(int *p0)
{
    return p0[9];
}

int func_ov095_0229c52c(int a, int b)
{
    if (b >= 0xf7 && b <= 0x10f) {
        b += 0xf;
        return b;
    }
    return -1;
}

unsigned short func_ov095_0229c510(int unused, int index)
{
    if (index >= 0x3b && index <= 0x6f) {
        return data_ov095_0229e874[index - 0x3b];
    }
    return 0;
}

int func_ov095_0229c4f4(int param0, int index)
{
    if (index >= 59 && index <= 111) {
        return data_ov095_0229e8e0[index - 59];
    }
    return 0;
}

int func_ov095_0229c4d8(int unused, int index)
{
    if (index >= 0x70 && index <= 0x91) {
        return data_ov095_0229e774[index - 0x70];
    } else {
        return 0;
    }
}

int func_ov095_0229c4bc(int r0, int r1)
{
    if (r1 >= 0xc9 && r1 <= 0xf6) {
        return data_ov095_0229e7b8[r1 - 0xc9];
    }
    return 0;
}

int func_ov095_0229c448(void *p, int x, unsigned int y)
{
    unsigned int v = y;
    int ret, result;

    if (v >= 9) {
        v = ((unsigned char *) p)[0x1b];
    }
    ret = func_ov095_0229c52c((int) p, x);
    if (ret >= 0) {
        return ret;
    }
    switch (v) {
        case 2:
            result = (int) func_ov095_0229c510((int) p, x);
            break;
        case 3:
            result = func_ov095_0229c4f4((int) p, x);
            break;
        case 6:
            result = func_ov095_0229c4d8((int) p, x);
            break;
        case 8:
            result = func_ov095_0229c4bc((int) p, x);
            break;
        default:
            result = 0x3000;
            break;
    }
    return result;
}
