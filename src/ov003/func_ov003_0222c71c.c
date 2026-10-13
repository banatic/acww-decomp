/* func_ov003_0222c71c @ 0x0222c71c, 0x3a bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

int func_ov003_0222c71c(unsigned short *p)
{
    unsigned short v = *p;
    if (v == 0x2a || v == 0x61 || (v >= 0x33 && v <= 0x36) || (v >= 0x3b && v <= 0x3e) || (v >= 0x43 && v <= 0x46) ||
        (v >= 0x4b && v <= 0x4e) || (v >= 0x53 && v <= 0x56)) {
        return 1;
    }
    return 0;
}
