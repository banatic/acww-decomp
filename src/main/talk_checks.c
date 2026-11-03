/* talk_checks: 5 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0202eac8 @ 0x0202eac8, 0x56 bytes, Thumb
 * func_0202ea80 @ 0x0202ea80, 0x46 bytes, Thumb
 * func_0202ea40 @ 0x0202ea40, 0x3e bytes, Thumb
 * func_0202ea28 @ 0x0202ea28, 0x18 bytes, Thumb
 * func_0202e9fc @ 0x0202e9fc, 0x2c bytes, Thumb
 */

typedef struct {
    unsigned char f : 2;
} TwoBit;

extern void *func_020160b4(void *);
extern void func_020ab670(void *, int, int);
extern void func_020ab628(void *, int, unsigned char *, int, unsigned char *, int, int);
extern void func_020ab5f8(void *);
extern int func_020984e8(void);
extern int func_0209967c(int a);
extern int func_020887c0(int a, int b);
extern void func_0208878c(int a, int b);
extern void func_0209e474(void *);
extern int func_02088470(unsigned char, unsigned char, unsigned char, void *);
extern int func_02099694(int);
extern void func_02088728(int, int);
extern int func_02073d90(int);
extern int func_02073918(int, int);
extern int data_020ccf94;

void func_0202eac8(void *A, const unsigned char *p, int n, int x)
{
    void *t;
    unsigned char buf[2];
    int zero;
    int i;

    t = func_020160b4(A);
    func_020ab670(t, n, x);
    zero = 0;
    for (i = 0; i < n; i++) {
        buf[0] = *p;
        buf[1] = 0xff;
        func_020ab628(t, i, buf, zero, &buf[1], zero, zero);
        p++;
    }
    func_020ab5f8(t);
}

int func_0202ea80(int p0, int p1)
{
    int r;
    int x;
    int ok;

    r = func_020984e8();
    if (!r) {
        return 0;
    }

    x = func_0209967c(r);
    ok = 1;
    if (func_020887c0(x, p0) == 0) {
        ok = 0;
    }

    if (p1 != 0) {
        func_0208878c(x, p0);
    }

    if (ok) {
        return 1;
    }
    return 0;
}

int func_0202ea40(int unused, TwoBit *p, int expected)
{
    unsigned int local[2];
    local[0] = 0;
    local[1] = 0;
    func_0209e474(local);
    if (func_02088470(((unsigned char *) local)[5], ((unsigned char *) local)[4], ((unsigned char *) local)[3], p) &&
        (p->f == expected)) {
        return 1;
    }
    return 0;
}

void func_0202ea28(int a, int b)
{
    func_02088728(func_02099694(func_020984e8()), b);
}

int func_0202e9fc(void)
{
    int tmp = data_020ccf94;
    if (func_02073d90(tmp) != 0 && func_02073918(tmp, 0) == 0) {
        return 0;
    }
    return 1;
}
