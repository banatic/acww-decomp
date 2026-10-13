/* func_ov114_0229c60c @ 0x0229c60c, 0x1c bytes, Thumb, module ov114
 * mwccarm 1.2/base -O4,s
 */

int func_ov114_0229c60c(unsigned char *p)
{
    unsigned char v = p[0x12bc];
    if (v >= 5 && v <= 12) {
        return v - 5;
    } else {
        return -1;
    }
}
