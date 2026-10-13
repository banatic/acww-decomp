/* func_ov113_02299a08 @ 0x02299a08, 0x3a bytes, Thumb, module ov113
 * mwccarm 1.2/base -O4,s
 */

int func_ov113_02299a08(unsigned char *p)
{
    unsigned char b = p[0x9b];
    if (b <= 3) {
        return 0x30 * b + 0x47;
    }
    if (b == 5) {
        return 0x10;
    }
    if (b == 4) {
        return 0xf0;
    }
    if (b <= 0x14) {
        return p[0x9e] + 0x48 + (b - 6) * 8;
    } else {
        return 0x80;
    }
}
