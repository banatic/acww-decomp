/* func_ov123_0229afc0 @ 0x0229afc0, 0x11c bytes, Thumb, module ov123
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov123_0229afc0(int a, int b, int c);
extern int func_ov002_0220a7c0(int a, int b, int c, int d);
extern int _s32_div_f(int a, int b);

int func_ov123_0229afc0(int a, int b, int c)
{
    if (func_ov002_0220a7c0(a + 0x5030, 9, b, c) != 0) {
        return 0x1d;
    }
    if (func_ov002_0220a7c0(a + 0x5030, 8, b, c) != 0) {
        return 0x1e;
    }
    if (b >= 8 && b <= 0x28 && c >= 0x18 && c <= 0x38) {
        return 0xd;
    }
    if (b >= 0x40 && b < 0xc0 && c >= 8 && c < 0x88) {
        return 0x21;
    }
    if (b >= 0xca) {
        if (c >= 8) {
            if (b < 0xe1) {
                if (c < 0x50) {
                    if (c < 0x20) {
                        return 0;
                    } else if (c < 0x38) {
                        return 1;
                    } else {
                        return 2;
                    }
                } else {
                    if (c >= 0x58 && c < 0x88) {
                        if (c < 0x70) {
                            return 3;
                        } else {
                            return 4;
                        }
                    } else if (c >= 0x90 && c < 0xa8) {
                        return 5;
                    }
                }
            } else if (b < 0xf9) {
                if (c < 0x50) {
                    if (c < 0x20) {
                        return 6;
                    } else if (c < 0x38) {
                        return 7;
                    } else {
                        return 8;
                    }
                } else {
                    if (c >= 0x58 && c < 0xa0) {
                        if (c < 0x70) {
                            return 9;
                        } else if (c < 0x88) {
                            return 0xa;
                        } else {
                            return 0xb;
                        }
                    }
                }
            }
        }
    }
    if (b >= 8 && b <= 0x28 && c >= 0x80 && c <= 0x94) {
        return 0xc;
    }
    if (b >= 8 && b < 0xbc && c >= 0x94 && c <= 0xa4) {
        return (unsigned char) (_s32_div_f(b - 8, 0xc) + 0xe);
    }
    return 0x22;
}
