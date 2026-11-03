/* player_pockets: 6 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02098be8 @ 0x02098be8, 0x44 bytes, Thumb
 * func_02098b44 @ 0x02098b44, 0xa4 bytes, Thumb
 * func_02098adc @ 0x02098adc, 0x68 bytes, Thumb
 * func_02098aa0 @ 0x02098aa0, 0x3c bytes, Thumb
 * func_02098a6c @ 0x02098a6c, 0x34 bytes, Thumb
 * func_02098a24 @ 0x02098a24, 0x48 bytes, Thumb
 */

extern unsigned short *func_02098f48(void *a, int b);
extern int func_02098c2c(void *a, int b);
extern int func_0204c878(unsigned short *p);
extern int func_02098f0c(void *self, unsigned short *p, int index, int zero);
extern int func_02098cc0(int a, int c, int d);
extern int func_02098cf8(int a, int c);

int func_02098be8(void *arg)
{
    unsigned short *p = func_02098f48(arg, 0);
    int i = 0;
    int found = ~0;

    while (i < 15) {
        if (*p == 0xFFF1) {
            found = i;
            break;
        }
        p++;
        i++;
    }

    if (found == ~0) {
        found = func_02098c2c(arg, 0);
    }
    return found;
}

unsigned int func_02098b44(void *self, unsigned int r5)
{
    unsigned short pair[2];
    int r7;
    int r4;
    unsigned int cond;
    unsigned short vv;

    pair[0] = 0x14fdu;
    r7 = func_0204c878(pair);
    pair[1] = 0xfff1u;

    while (r5 > 99999u) {
        r4 = func_02098be8(self);
        if (r4 == -1) {
            break;
        }

        pair[1] = *func_02098f48(self, r4);

        cond = 0;
        vv = *(volatile unsigned short *) &pair[1];
        if (pair[1] >= 0x1492u && vv <= 0x14fdu) {
            cond = 1;
        }

        if (cond) {
            func_02098f0c(self, pair, r4, 0);
            r5 -= (r7 - func_0204c878(&pair[1]));
        } else {
            if (vv != 0xfff1u) {
                break;
            }
            func_02098f0c(self, pair, r4, 0);
            r5 -= r7;
        }
    }
    return r5;
}

int func_02098adc(void *p, int n)
{
    int r5 = n;
    unsigned short local[2];

    if (r5 < 0) {
        r5 = 0;
    }
    local[0] = 0xFFF1;
    while (r5 > 0) {
        int ret = func_02098c2c(p, 1);
        if (ret == -1) {
            break;
        }
        local[0] = *func_02098f48(p, ret);
        local[1] = 0xFFF1;
        func_02098f0c(p, &local[1], ret, 0);
        r5 -= func_0204c878(local);
    }
    if (r5 != 0) {
        r5 = -r5;
    }
    return r5;
}

void func_02098aa0(int a, int b, int c)
{
    int value;
    if (b < 0) {
        b = 0;
    }
    if ((unsigned) b > 99999) {
        if (c == 1) {
            int ret = (int) func_02098b44((void *) a, b);
            if ((unsigned) ret <= 99999) {
                value = ret;
            } else {
                value = 99999;
            }
        } else {
            value = 99999;
        }
    } else {
        value = b;
    }
    *(int *) ((char *) a + 0xa68) = value;
}

int func_02098a6c(int a, int b, int c, int d)
{
    int result = 0;

    if (b >= 0) {
        int ret = func_02098cc0(a, c, d);
        if (b <= ret) {
            result = 1;
        }
    } else {
        int ret = func_02098cf8(a, c);
        if (-b <= ret) {
            result = 1;
        }
    }

    return result;
}

void func_02098a24(int a, int b, int c)
{
    int t;

    t = b + func_02098cf8(a, 0);
    if (t < 0) {
        if (c == 1) {
            t = func_02098adc((void *) a, -t);
            if (t < 0) {
                t = 0;
            } else if ((unsigned) t > 99999) {
                t = 99999;
            }
        } else {
            t = 0;
        }
    }
    func_02098aa0(a, t, c);
}
