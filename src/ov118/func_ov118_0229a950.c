/* func_ov118_0229a950 @ 0x0229a950, 0x5c bytes, Thumb, module ov118
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov118_0229a460(const unsigned char *p, int n);
extern int func_ov002_0220a4d4(const unsigned char *p);

int func_ov118_0229a950(const unsigned char *p)
{
    unsigned char v;

    if (func_ov118_0229a460(p, 0x800) != 0) {
        return p[0xaf];
    }

    v = p[0xac];

    if (v >= 10 && v <= 15) {
        return (v - 10) * 16 + 0x58;
    }

    if (v >= 8 && v <= 9) {
        return 0x40;
    }

    if (v <= 7) {
        return 8;
    }

    if (v == 16) {
        return func_ov002_0220a4d4(p + 0x678);
    }

    return 0x60;
}
