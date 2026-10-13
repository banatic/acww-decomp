/* func_ov119_0229b9c8 @ 0x0229b9c8, 0x36 bytes, Thumb, module ov119
 * mwccarm 1.2/base -O4,s
 */

int func_ov119_0229b9c8(void *ptr)
{
    unsigned char v = ((unsigned char *) ptr)[0xa0];
    if (v <= 7) {
        return v * 16 + 56;
    }
    if (v >= 14 && v <= 21) {
        return 8;
    }
    if (v >= 8 && v <= 13) {
        return (v - 8) * 16 + 63;
    }
    if (v == 22) {
        return 170;
    }
    return 96;
}
