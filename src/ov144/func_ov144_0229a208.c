/* func_ov144_0229a208 @ 0x0229a208, 0x5c bytes, Thumb, module ov144
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_0220a768(unsigned char *, int);
extern int func_ov002_0220a4f8(unsigned char *);

int func_ov144_0229a208(unsigned char *p)
{
    unsigned char b = p[0xc1];

    if (b <= 8) {
        return 0x48;
    }

    switch (b) {
        case 9:
            return func_ov002_0220a768(p + 0x170, 6);
        case 11:
        case 12:
        case 13:
            return 0x26;
        case 10:
            return func_ov002_0220a4f8(p + 0x128);
        default:
            return 0x80;
    }
}
