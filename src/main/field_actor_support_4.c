/* field_actor_support_4: 10 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02011520 @ 0x02011520, 0xb0 bytes, Thumb
 * func_020114b0 @ 0x020114b0, 0x6e bytes, Thumb
 * func_02011490 @ 0x02011490, 0x20 bytes, Thumb
 * func_02011404 @ 0x02011404, 0x8c bytes, Thumb
 * func_020113e0 @ 0x020113e0, 0x24 bytes, Thumb
 * func_020113bc @ 0x020113bc, 0x24 bytes, Thumb
 * func_020113b0 @ 0x020113b0, 0xa bytes, Thumb
 * func_020113a4 @ 0x020113a4, 0xa bytes, Thumb
 * func_02011398 @ 0x02011398, 0xc bytes, Thumb
 * func_0201138c @ 0x0201138c, 0xc bytes, Thumb
 */

extern void *data_020ccf94;
extern int func_02073908(void *a, int b);
extern int func_02096124(int size, int kind);
extern int func_02095794(int);
extern int func_02030890(int *);
extern void func_020953c4(int *);
extern int func_020b5e10(void);
extern int func_020b6044(int, int, int *, int *);
extern void func_020953a4(int *);
extern int func_0209d780(int);
extern int func_020b67ac(void);
extern int func_0203e110(void);
extern int func_0203e420(void);
extern int func_02096190(int);
extern int func_0203e444(int, int);
extern int FX_MulFunc(int, int);

int func_02011520(int param)
{
    int a;
    int v;
    int c;
    int ret;

    ret = func_02073908(data_020ccf94, param);
    if (ret == 0) {
        return ret;
    }

    ret = func_02096124(0xb, param);
    if (ret != 0) {
        return ret;
    }

    ret = func_02096124(0x13, param);
    if (ret != 0) {
        return ret;
    }

    ret = func_02096124(5, param);
    if (ret != 0) {
        return ret;
    }

    ret = func_02095794(4);
    if (ret == 0) {
        return ret;
    }

    v = func_02030890((int *) ret);
    if (v == -1) {
        return v;
    }

    func_020953c4(&v);

    ret = func_020b5e10();
    ret = func_020b6044(ret, v, &c, &a);
    if (ret == 0) {
        return ret;
    }

    func_020953a4(&c);

    if (c == 1 || c == 2 || c == 4 || func_0209d780(v) != 0) {
        if (func_020b67ac() != 0) {
            func_0203e110();
        }
        return func_0203e420();
    } else {
        ret = func_02096190(4);
        return func_0203e444(ret, v);
    }
}

void func_020114b0(int *p, int target, int a, int limit1, int limit2)
{
    int diff, adiff, res, ares;

    if (*p == target) {
        return;
    }

    diff = target - *p;
    adiff = (diff < 0) ? -diff : diff;

    if (adiff < limit2) {
        *p = target;
        return;
    }

    res = FX_MulFunc(diff, a);
    ares = (res < 0) ? -res : res;

    if (ares > limit1) {
        if (res >= 0) {
            *p += limit1;
        } else {
            *p -= limit1;
        }
        return;
    } else {
        if (ares < limit2) {
            if (res >= 0) {
                *p += limit2;
            } else {
                *p -= limit2;
            }
            return;
        } else {
            *p += res;
            return;
        }
    }
}

void func_02011490(int a1, int a2)
{
    func_020114b0((int *) a1, a2, 0x0e66, 0x01ec, 0x31);
}

int func_02011404(short *p, int b, int c, int d, int e)
{
    int diff;
    int from;
    int to;
    int step;
    short a = *p;

    if (a == b) {
        return 0;
    }
    from = a << 12;
    to = b << 12;
    diff = to - from;
    if (diff < 0) {
        diff = -diff;
    }
    if (diff > 0x08000000) {
        step = FX_MulFunc(c, 0x10000000 - diff);
    } else {
        step = FX_MulFunc(c, diff);
    }
    if (step <= e) {
        *p = b;
        return 0;
    }
    if (step > d) {
        step = d;
    }
    if (to >= from) {
        step = diff > 0x08000000 ? from - step : from + step;
    } else {
        step = diff > 0x08000000 ? from + step : from - step;
    }
    *p = step >> 12;
    return (short) (b - *p);
}

int func_020113e0(int a, int b)
{
    return func_02011404((short *) a, b, 0x800, 0x1770000, 0xc0000);
}

int func_020113bc(int a, int b)
{
    return func_02011404((short *) a, b, 0x666, 0x00bb8000, 0x000c0000);
}

int func_020113b0(int a, int b)
{
    a = a + 0x93;
    return (a <= b) ? a : b;
}

int func_020113a4(int a, int b, int c)
{
    int t = a - c;
    return (t >= b) ? t : b;
}

int func_02011398(int a1, int a2)
{
    return func_020113a4(a1, a2, 0x9c);
}

int func_0201138c(int a, int b)
{
    return func_020113a4(a, b, 0x8f);
}
