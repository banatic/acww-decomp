/* villager_house_items_3: 15 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0207ffdc @ 0x0207ffdc, 0x9c bytes, Thumb
 * func_0207ffac @ 0x0207ffac, 0x30 bytes, Thumb
 * func_0207ffa0 @ 0x0207ffa0, 0xc bytes, Thumb
 * func_0207ff58 @ 0x0207ff58, 0x48 bytes, Thumb
 * func_0207ff0c @ 0x0207ff0c, 0x4c bytes, Thumb
 * func_0207ff00 @ 0x0207ff00, 0xc bytes, Thumb
 * func_0207fe94 @ 0x0207fe94, 0x6c bytes, Thumb
 * func_0207fe28 @ 0x0207fe28, 0x6c bytes, Thumb
 * func_0207fdbc @ 0x0207fdbc, 0x6c bytes, Thumb
 * func_0207fd94 @ 0x0207fd94, 0x28 bytes, Thumb
 * func_0207fd6c @ 0x0207fd6c, 0x28 bytes, Thumb
 * func_0207fd44 @ 0x0207fd44, 0x28 bytes, Thumb
 * func_0207fd1c @ 0x0207fd1c, 0x28 bytes, Thumb
 * func_0207fcc8 @ 0x0207fcc8, 0x54 bytes, Thumb
 * func_0207fc7c @ 0x0207fc7c, 0x4c bytes, Thumb
 */

typedef struct {
    unsigned int a;
    unsigned int b;
} Pair;

extern int func_0208150c(unsigned char *);
extern int func_02003704(int);
extern int func_02003648(int);
extern int func_02082500(int);
extern int func_0207f1c8(unsigned char *);
extern int func_0209b5ec(void *);
extern int func_0209c330(int);
extern int func_0209c2c0(int);
extern void *func_02080b64(int);
extern void func_02061b1c(void *dst, const void *src, int count);
extern int func_0207cc54(int a, int b, int c);
extern int func_0204c878(unsigned short *);
extern int func_0204bcdc(void *);
extern int func_02080834(void *, void *);
extern Pair data_021d1330[];
extern Pair __ptmf_null;
extern unsigned int func_0209c2d4(unsigned char *flag, unsigned int b);

int func_0207ffdc(unsigned char *param0, int *param1, int *param2)
{
    int ret = 0;
    int x;

    if (func_02003704(func_0208150c(param0)) == 0) {
        goto exit;
    }
    if (func_02082500(func_02003648(func_0208150c(param0))) == 0) {
        goto exit;
    }

    x = (func_0209b5ec((void *) func_0207f1c8(param0)));

    if (func_0209c330(x) == 2) {
        goto normal;
    }
    if (func_0209c330(x) == 8) {
        goto check2;
    }
    if (func_0209c330(x) == 9) {
        goto check2;
    }
    if (func_0209c330(x) == 10) {
        goto check2;
    }
    if (func_0209c330(x) != 11) {
        goto other;
    }

check2:
    if (func_0209c2c0(x) == 0) {
        goto other;
    }

normal:
    *param1 = 3;
    *param2 = param0[0x7d8] % 10;
    goto success;

other:
    *param1 = 2;
    *param2 = param0[0x7d8];

success:
    ret = 1;

exit:
    return ret;
}

int func_0207ffac(int argument0)
{
    unsigned char *p = (unsigned char *) func_02080b64((int) argument0);
    int shift = 0;
    if (p != 0) {
        shift = ((int) ((unsigned) (p[0] << 27) >> 27)) >> 2;
        if (shift < 0 || shift >= 5) {
            shift = 0;
        }
    }
    return shift + 0x1010;
}

int func_0207ffa0(int unused, unsigned int value)
{
    if (value >= 10) {
        return 0;
    } else {
        return 1;
    }
}

int func_0207ff58(int a, volatile unsigned short *p)
{
    int r = -1;
    unsigned int ok = 0;
    unsigned short v = *p;
    if (v >= 0xf000 && v <= 0xf02f) {
        ok = 1;
    }
    if (ok != 0) {
        if (v >= 0xf000 && v <= 0xf02f) {
            r = (*p - 0xf000) >> 2;
        } else {
            r = -1;
        }
        if (r >= 3) {
            r = r - 2;
        }
    }
    return r;
}

void func_0207ff0c(unsigned short *out, const void *p, int idx)
{
    unsigned short tmp;

    *out = 0xFFF1;
    if (func_0207ffa0((int) p, idx)) {
        *out = *(unsigned short *) ((const char *) p + idx * 2 + 0x78c);
        if (*out != 0xFFF1) {
            func_02061b1c(&tmp, out, 1);
            *out = tmp;
        }
    }
}

int func_0207ff00(int a)
{
    return a + 0x78c;
}

int func_0207fe94(int arg0, int *out1, int *out2, int mode, int step, unsigned char flag)
{
    int result = 0;
    switch (mode) {
        case 0:
            *out1 = 5;
            *out2 = 0xa;
            result = 1;
            break;
        case 1:
            *out1 = 1;
            *out2 = 5;
            if (step == 2 || (step == 8 && flag != 0)) {
                *out1 = 3;
            }
            result = 1;
            break;
        case 2:
            *out1 = 0;
            if (step == 2 || (step == 8 && flag != 0)) {
                *out2 = 3;
            } else {
                *out2 = 1;
            }
            result = 1;
            break;
    }
    return result;
}

int func_0207fe28(int a, int b, int c)
{
    if (func_0207ffa0(a, b) != 0) {
        unsigned short *ptr = (unsigned short *) (a + 0x78c) + b;
        unsigned short bits = 0;
        int count = 0;

        while (b < c) {
            if (func_0207ffa0(a, b) != 0) {
                if (*ptr == 0xfff1) {
                    bits |= (1 << b);
                    count++;
                }
            }
            ptr++;
            b++;
        }
        return func_0207cc54(bits, count, 10);
    } else {
        return -1;
    }
}

int func_0207fdbc(void *a, int i, int n)
{
    unsigned short *p;
    int best;
    int result;
    int t;
    if (func_0207ffa0((int) a, i) == 0) {
        goto fail;
    }
    p = (unsigned short *) ((char *) a + 0x78c) + i;
    best = 0x1869f;
    result = -1;
    for (; i < n; p++, i++) {
        if (func_0207ffa0((int) a, i) != 0) {
            if (*p != 0xfff1) {
                t = func_0204c878(p);
                if (t <= best) {
                    result = i;
                    best = t;
                }
            }
        }
    }
    return result;
fail:
    return -1;
}

int func_0207fd94(int unused, unsigned short *p)
{
    int found;
    unsigned short val;

    found = 0;
    val = *p;
    if (val >= 0x12b0 && val <= 0x12e7) {
        found = 1;
    }
    if (found) {
        return 1;
    } else {
        return 0;
    }
}

int func_0207fd6c(int unused, unsigned short *p)
{
    int flag = 0;
    unsigned short v = *p;
    if (v >= 0x12e8 && v <= 0x131f) {
        flag = 1;
    }
    if (flag) {
        return 1;
    }
    return 0;
}

int func_0207fd44(int unused, unsigned short *ptr)
{
    int flag = 0;
    unsigned short val = *ptr;
    if (val >= 0x450c && val <= 0x45db) {
        flag = 1;
    }
    if (flag) {
        return 1;
    } else {
        return 0;
    }
}

int func_0207fd1c(int unused, unsigned short *p)
{
    return (*p >= 0x11A8 && *p <= 0x12A7) ? 1 : 0;
}

int func_0207fcc8(void *p1, void *p2)
{
    int r6 = 0;
    int r4 = 0;
    int r1;
    unsigned short r0;
    int r2;

    if (func_0204bcdc(p2) != 0) {
        r1 = 0;
        r0 = *(unsigned short *) p2;
        if (r0 >= 0x450c && r0 <= 0x45db) {
            r1 = 1;
        }
        if (r1 == 0) {
            r4 = 1;
        }
    }
    if (r4 != 0) {
        if (func_02080834(p1, p2) > 0) {
            r6 = 1;
        }
    }
    return r6;
}

Pair func_0207fc7c(unsigned int unused, unsigned int b)
{
    unsigned char flag = 3;
    unsigned int ret = func_0209c2d4(&flag, b);

    if (flag == 0 && ret < 5) {
        return data_021d1330[ret];
    } else {
        return __ptmf_null;
    }
}
