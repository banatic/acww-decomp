/* func_0201b0bc @ 0x0201b0bc, 0xca bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020e8b4c(int a, int b);

int func_0201b0bc(int unused, short *p, short target, short step, unsigned char mode)
{
    short d = step;
    int a;
    int ret;

    if (step < 0) {
        a = (short) -step;
    } else {
        a = step;
    }
    ret = 0;
    if (step != 0) {
        switch (mode) {
            case 1:
            case 2:
                if (func_020e8b4c(target, p[0]) <= a) {
                    short t = p[0] - target;
                    if (t > 0) {
                        d = -step;
                    }
                } else if (mode == 1) {
                    d = a;
                } else {
                    d = -a;
                }
                break;
            default: {
                short t = p[0] - target;
                if (t > 0) {
                    d = -step;
                }
                break;
            }
        }
        p[0] = p[0] + d;
        {
            int raw = p[0] - target;
            short ad = raw;
            short adz;
            if (ad < 0) {
                ad = -ad;
            }
            if (d < 0) {
                adz = -d;
            } else {
                adz = d;
            }
            if (ad <= adz) {
                if ((short) raw * d >= 0) {
                    p[0] = target;
                    ret = 1;
                }
            }
        }
    } else {
        if (p[0] == target) {
            ret = 1;
        }
    }
    return ret;
}
