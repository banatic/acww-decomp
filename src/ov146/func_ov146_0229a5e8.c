/* func_ov146_0229a5e8 @ 0x0229a5e8, 0x44 bytes, Thumb, module ov146
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_0220a4f8(unsigned char *);

int func_ov146_0229a5e8(unsigned char *arg)
{
    unsigned char b = arg[0xb2];

    if (b >= 3 && b <= 9) {
        return 0x1c;
    }

    switch (b) {
        case 0:
            return 0x47;
        case 1:
            return 0x99;
        case 2:
            return func_ov002_0220a4f8(arg + 0x1fb4);
        default:
            return 0x80;
    }
}
