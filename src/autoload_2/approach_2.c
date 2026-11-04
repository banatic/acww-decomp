/* approach_2: 6 functions, module autoload_2
 * mwccarm 1.2/base -O4,p
 * func_020e8a94 @ 0x020e8a94, 0x78 bytes, ARM
 * func_020e8a38 @ 0x020e8a38, 0x5c bytes, ARM
 * func_020e89dc @ 0x020e89dc, 0x5c bytes, ARM
 * func_020e895c @ 0x020e895c, 0x80 bytes, ARM
 * func_020e88dc @ 0x020e88dc, 0x80 bytes, ARM
 * func_020e8870 @ 0x020e8870, 0x6c bytes, ARM
 */

extern int _s32_div_f(int, int);

void func_020e8a94(short *r5, int r1, int r2, int r4)
{
    int r0;
    int r3;
    int r6;

    r0 = (short) r5[0];
    r0 = (short) (r1 - r0);
    r0 = _s32_div_f(r0, r2);
    r0 = (short) r0;
    r3 = r0;
    if (r3 > r4) {
        r0 = (short) r5[0];
        r0 = r0 + r4;
        r5[0] = (short) r0;
        return;
    }
    r0 = -r4;
    if (r3 < r0) {
        r0 = (short) r5[0];
        r0 = r0 - r4;
        r5[0] = (short) r0;
    } else {
        r0 = (short) r5[0];
        r0 = r0 + r3;
        r5[0] = (short) r0;
    }
}

int func_020e8a38(unsigned char *p, int a, short b)
{
    short newval;
    if (b != 0) {
        if ((int) *p > a) {
            b = -b;
        }
        newval = (short) (*p + b);
        if (b * (newval - a) >= 0) {
            *p = (unsigned char) a;
            return 1;
        }
        *p = (unsigned char) newval;
        goto fail;
    } else {
        if (*p == a) {
            return 1;
        }
    }
fail:
    return 0;
}

int func_020e89dc(short *p, int a, short b)
{
    if (b != 0) {
        if (*p > a) {
            b = -b;
        }
        *p = (short) (*(volatile short *) p + b);
        if (b * (*p - a) < 0) {
            goto fail;
        }
        *p = (short) a;
        return 1;
    } else {
        if (*p == a) {
            return 1;
        }
    }
fail:
    return 0;
}

int func_020e895c(int *p, int v, int d)
{
    if (d != 0) {
        if (*p > v) {
            d = -d;
        }
        *p += d;
        if ((long long) d * (*p - v) >= 0) {
            *p = v;
            return 1;
        }
    } else {
        if (*p == v) {
            return 1;
        }
    }
    return 0;
}

int func_020e88dc(int *p, int a, int b)
{
    if (b != 0) {
        if (*p > a) {
            b = -b;
        }
        *p = *p + b;
        if ((long long) b * (*p - a) < 0) {
            goto fail;
        }
        *p = a;
        return 1;
    } else {
        if (*p == a) {
            return 1;
        }
    }
fail:
    return 0;
}

int func_020e8870(short *p, int a, short b)
{
    if (b != 0) {
        if ((short) (*p - a) > 0) {
            b = -b;
        }
        *p = (short) (*(volatile short *) p + b);
        if ((int) b * (short) (*p - a) < 0) {
            goto fail;
        }
        *p = (short) a;
        return 1;
    } else {
        if (*p == a) {
            return 1;
        }
    }
fail:
    return 0;
}
