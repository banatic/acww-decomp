/* furniture_info: 53 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02053f00 @ 0x02053f00, 0x20 bytes, Thumb
 * func_02053ed8 @ 0x02053ed8, 0x26 bytes, Thumb
 * func_02053ea4 @ 0x02053ea4, 0x34 bytes, Thumb
 * func_02053e9c @ 0x02053e9c, 0x8 bytes, Thumb
 * func_02053e94 @ 0x02053e94, 0x8 bytes, Thumb
 * func_02053e8c @ 0x02053e8c, 0x8 bytes, Thumb
 * func_02053e7c @ 0x02053e7c, 0x10 bytes, Thumb
 * func_02053e6c @ 0x02053e6c, 0x10 bytes, Thumb
 * func_02053e5c @ 0x02053e5c, 0x10 bytes, Thumb
 * func_02053e4c @ 0x02053e4c, 0x10 bytes, Thumb
 * func_02053e18 @ 0x02053e18, 0x34 bytes, Thumb
 * func_02053de4 @ 0x02053de4, 0x34 bytes, Thumb
 * func_02053dac @ 0x02053dac, 0x38 bytes, Thumb
 * func_02053da4 @ 0x02053da4, 0x6 bytes, Thumb
 * func_02053d9c @ 0x02053d9c, 0x6 bytes, Thumb
 * func_02053d94 @ 0x02053d94, 0x6 bytes, Thumb
 * func_02053d60 @ 0x02053d60, 0x34 bytes, Thumb
 * func_02053d24 @ 0x02053d24, 0x3c bytes, Thumb
 * func_02053cf0 @ 0x02053cf0, 0x34 bytes, Thumb
 * func_02053cbc @ 0x02053cbc, 0x34 bytes, Thumb
 * func_02053c88 @ 0x02053c88, 0x34 bytes, Thumb
 * func_02053c68 @ 0x02053c68, 0x20 bytes, Thumb
 * func_02053c34 @ 0x02053c34, 0x34 bytes, Thumb
 * func_02053c14 @ 0x02053c14, 0x20 bytes, Thumb
 * func_02053be0 @ 0x02053be0, 0x34 bytes, Thumb
 * func_02053bc0 @ 0x02053bc0, 0x20 bytes, Thumb
 * func_02053b8c @ 0x02053b8c, 0x34 bytes, Thumb
 * func_02053b6c @ 0x02053b6c, 0x20 bytes, Thumb
 * func_02053b2c @ 0x02053b2c, 0x40 bytes, Thumb
 * func_02053aa8 @ 0x02053aa8, 0x84 bytes, Thumb
 * func_02053a88 @ 0x02053a88, 0x20 bytes, Thumb
 * func_02053a04 @ 0x02053a04, 0x84 bytes, Thumb
 * func_020539e4 @ 0x020539e4, 0x20 bytes, Thumb
 * func_020539b0 @ 0x020539b0, 0x34 bytes, Thumb
 * func_02053990 @ 0x02053990, 0x20 bytes, Thumb
 * func_0205395c @ 0x0205395c, 0x34 bytes, Thumb
 * func_0205391c @ 0x0205391c, 0x40 bytes, Thumb
 * func_020538dc @ 0x020538dc, 0x40 bytes, Thumb
 * func_0205389c @ 0x0205389c, 0x40 bytes, Thumb
 * func_02053818 @ 0x02053818, 0x84 bytes, Thumb
 * func_020537e8 @ 0x020537e8, 0x30 bytes, Thumb
 * func_020537a8 @ 0x020537a8, 0x40 bytes, Thumb
 * func_02053748 @ 0x02053748, 0x60 bytes, Thumb
 * func_02053728 @ 0x02053728, 0x20 bytes, Thumb
 * func_020536e8 @ 0x020536e8, 0x40 bytes, Thumb
 * func_020536c8 @ 0x020536c8, 0x20 bytes, Thumb
 * func_02053690 @ 0x02053690, 0x38 bytes, Thumb
 * func_02053658 @ 0x02053658, 0x38 bytes, Thumb
 * func_02053624 @ 0x02053624, 0x34 bytes, Thumb
 * func_020535f0 @ 0x020535f0, 0x34 bytes, Thumb
 * func_020535b4 @ 0x020535b4, 0x3c bytes, Thumb
 * func_0205352c @ 0x0205352c, 0x88 bytes, Thumb
 * func_020534ec @ 0x020534ec, 0x40 bytes, Thumb
 */

typedef struct {
    char pad_00[0x16];
    unsigned short unk_16;
} UnkStruct_02053e18;

typedef struct {
    char pad_00[0x1e];
    unsigned char byte;
} UnkStruct_02053d24;

typedef struct {
    unsigned char pad_00[6];
    unsigned char unk_06;
} UnkStruct_020539b0;

typedef struct {
    unsigned char pad_00[0x1b];
    unsigned char unk_1B;
} UnkStruct_02053690;

extern void func_0206e8c4(void *);
extern void func_0206e71c(void *ptr);
extern int func_0206e8b4(void *ptr);
extern int func_0206e73c(int a, int b, int c, int d, int e, int f, int g, int h);
extern unsigned char data_020dcfec[];
extern unsigned char data_020dd004[];
extern unsigned char data_020dd01c[];
extern int func_0206e704(void *, int);
extern int func_0206e6f0(void *);
extern unsigned char data_021c8c48[];
extern void *func_0206e6e4(void *a);
extern void *func_0206e7bc(void *arg, int arg2);
extern void *func_0206e6ec(void *);
extern int func_0204bcdc(int);
extern int func_0204bc64(int);
extern void *func_0206e6e8(void *);
extern int func_0204bc50(int, int);

void *func_02053f00(void *arg)
{
    func_0206e8c4(arg);
    func_0206e8c4((char *) arg + 0x1c);
    func_0206e8c4((char *) arg + 0x38);
    return arg;
}

void *func_02053ed8(void *param)
{
    func_0206e71c(param);
    func_0206e8b4((char *) param + 0x38);
    func_0206e8b4((char *) param + 0x1c);
    func_0206e8b4(param);
    return param;
}

int func_02053ea4(int a)
{
    return func_0206e73c(a, (unsigned int) data_020dcfec, 8, (unsigned int) data_020dd004, 4, (unsigned int) data_020dd01c,
                         0x20, 0x800);
}

void func_02053e9c(void *argument0)
{
    func_0206e71c((void *) argument0);
}

int func_02053e94(void *argument0, int argument1)
{
    return func_0206e704((void *) argument0, (int) argument1);
}

void func_02053e8c(void *argument0)
{
    func_0206e6f0((void *) argument0);
}

void func_02053e7c(void)
{
    func_02053ea4((int) ((void *) data_021c8c48));
}

void func_02053e6c(void)
{
    func_02053e9c(((char *) data_021c8c48));
}

void *func_02053e5c(void *arg)
{
    return (void *) func_02053e94((void *) data_021c8c48, (int) arg);
}

void func_02053e4c(void)
{
    func_02053e8c((void *) ((int) ((int *) data_021c8c48)));
}

unsigned short func_02053e18(int param)
{
    int clamped;
    void *p;
    UnkStruct_02053e18 *s;
    clamped = param;
    if (clamped >= 0x6e9) {
        clamped = 0x6e8;
    }
    p = func_0206e6e4(((int *) data_021c8c48));
    s = (UnkStruct_02053e18 *) func_0206e7bc(p, clamped);
    if (s) {
        return s->unk_16;
    }
    return 0;
}

unsigned char func_02053de4(int val)
{
    void *res;

    if (val >= 0x6e9) {
        val = 0x6e8;
    }
    res = func_0206e7bc(func_0206e6e4((void *) ((unsigned int) data_021c8c48)), val);
    if (res) {
        return ((unsigned char *) res)[0x18];
    }
    return 0;
}

int func_02053dac(int a)
{
    int v;
    void *p;
    void *q;
    int byte;

    v = a;
    if (v >= 0x6e9) {
        v = 0x6e8;
    }
    p = func_0206e6e4((void *) (((char *) data_021c8c48)));
    q = func_0206e7bc(p, v);
    if (q != 0) {
        byte = ((unsigned char *) q)[0x19];
    } else {
        byte = 0;
    }
    return (byte << 12) >> 4;
}

int func_02053da4(int value)
{
    return -1;
}

int func_02053d9c(int value)
{
    return -1;
}

int func_02053d94(int value)
{
    return -1;
}

int func_02053d60(int arg0)
{
    int val;
    int val2;
    int val3;

    val = arg0;
    if (arg0 < 0x6e9) {
        val2 = arg0;
    } else {
        val2 = 0x6e8;
    }
    val3 = (int) func_0206e6e4((void *) ((unsigned int) data_021c8c48));
    val = (int) func_0206e7bc((void *) val3, val2);
    if (val != 0) {
        return *(unsigned char *) (val + 0x1d);
    }
    return 0;
}

int func_02053d24(int param)
{
    int value;
    void *tmp;
    UnkStruct_02053d24 *s;
    int result;

    value = param;
    if (value >= 0x6e9) {
        value = 0x6e8;
    }
    tmp = func_0206e6e4((void *) data_021c8c48);
    s = func_0206e7bc(tmp, value);
    if (s) {
        result = s->byte;
    } else {
        result = 0;
    }
    if (result == 0xff) {
        result = -1;
    }
    return result;
}

int func_02053cf0(int r0)
{
    int r4;
    int r1;
    int r0_2;

    r4 = r0;
    if (r4 < 0x6e9) {
    } else {
        r4 = 0x6e8;
    }
    r0_2 = (int) func_0206e6ec((void *) ((unsigned int) data_021c8c48));
    r1 = r4;
    r0_2 = (int) func_0206e7bc((void *) r0_2, r1);
    if (r0_2 != 0) {
        return *(unsigned char *) (r0_2 + 1);
    } else {
        return 0;
    }
}

int func_02053cbc(int arg)
{
    int r;
    void *p1;
    unsigned char *p2;

    r = arg;
    if (r >= 1769) {
        r = 1768;
    }
    p1 = func_0206e6ec((void *) data_021c8c48);
    p2 = (unsigned char *) func_0206e7bc(p1, r);
    if (p2) {
        return p2[2];
    } else {
        return 0;
    }
}

unsigned char func_02053c88(int param)
{
    int idx = param;
    void *entry;

    if (idx >= 0x6e9) {
        idx = 0x6e8;
    }
    entry = func_0206e7bc(func_0206e6ec((void *) data_021c8c48), idx);
    if (entry) {
        return *(unsigned char *) entry;
    }
    return 0;
}

int func_02053c68(int arg)
{
    if (func_0204bcdc(arg)) {
        return (int) func_02053c88(func_0204bc64(arg));
    }
    return 0;
}

unsigned char func_02053c34(int param)
{
    void *p;
    void *res;

    if (param >= 0x6e9) {
        param = 0x6e8;
    }
    p = func_0206e6ec(((int *) data_021c8c48));
    res = func_0206e7bc(p, param);
    if (res) {
        return ((unsigned char *) res)[4];
    } else {
        return 0;
    }
}

int func_02053c14(int arg)
{
    if (func_0204bcdc(arg) != 0) {
        return (int) func_02053c34((int) func_0204bc64(arg));
    }
    return 0;
}

unsigned char func_02053be0(int arg)
{
    int n;
    void *p;
    void *q;

    n = arg;
    if (n >= 0x6e9) {
        n = 0x6e8;
    }
    p = func_0206e6ec(data_021c8c48);
    q = func_0206e7bc(p, n);
    if (q) {
        return ((unsigned char *) q)[5];
    } else {
        return 0;
    }
}

int func_02053bc0(int arg)
{
    if (func_0204bcdc(arg) != 0) {
        return (int) func_02053be0(func_0204bc64(arg));
    }
    return 0;
}

int func_02053b8c(int param)
{
    int r4;
    void *result;
    r4 = param;
    if (param >= 0x6e9) {
        r4 = 0x6e8;
    }
    result = func_0206e7bc(func_0206e6ec((void *) data_021c8c48), r4);
    if (result != 0) {
        return ((unsigned char *) result)[3];
    } else {
        return 0;
    }
}

int func_02053b6c(int param)
{
    if (func_0204bcdc(param) != 0) {
        return func_02053b8c((int) func_0204bc64(param));
    }
    return 0;
}

int func_02053b2c(int arg)
{
    int x = arg;
    unsigned char *res;
    if (x >= 1769) {
        x = 1768;
    }
    res = (unsigned char *) func_0206e7bc(func_0206e6ec((void *) data_021c8c48), x);
    if (res != 0) {
        if (((res[7] >> 4) & 1) != 0) {
            return 1;
        }
        return 0;
    }
    return 0;
}

int func_02053aa8(int id)
{
    unsigned char *p;
    int f1, f2;
    int idx;

    if (id >= 0x6e9) {
        idx = 0x6e8;
    } else {
        idx = id;
    }
    p = (unsigned char *) func_0206e7bc(func_0206e6ec((void *) data_021c8c48), idx);
    if (p != 0) {
        if ((p[7] & 1) != 0) {
            f1 = 1;
        } else {
            f1 = 0;
        }
    } else {
        f1 = 0;
    }

    if (id >= 0x6e9) {
        id = 0x6e8;
    }
    p = (unsigned char *) func_0206e7bc(func_0206e6ec((void *) data_021c8c48), id);
    if (f1 != 0) {
        return 1;
    }
    if (p != 0) {
        if (((p[7] >> 1) & 1) != 0) {
            f2 = 1;
        } else {
            f2 = 0;
        }
    } else {
        f2 = 0;
    }
    if (f2 != 0) {
        return 2;
    }
    return 0;
}

int func_02053a88(int arg)
{
    if (func_0204bcdc(arg)) {
        return func_02053aa8(func_0204bc64(arg));
    } else {
        return 0;
    }
}

int func_02053a04(int param)
{
    void *p1;
    void *q1;
    int flag1;
    int v1;
    void *p2;
    void *q2;
    int flag2;
    int v2;

    if (param >= 1769) {
        v1 = 1768;
    } else {
        v1 = param;
    }
    p1 = func_0206e6ec((void *) data_021c8c48);
    q1 = func_0206e7bc(p1, v1);

    if (q1 != 0) {
        flag1 = (((unsigned char *) q1)[7] >> 2) & 1 ? 1 : 0;
    } else {
        flag1 = 0;
    }

    if (param >= 1769) {
        v2 = 1768;
    } else {
        v2 = param;
    }
    p2 = func_0206e6ec((void *) data_021c8c48);
    q2 = func_0206e7bc(p2, v2);

    if (flag1 != 0) {
        return 1;
    }

    if (q2 != 0) {
        flag2 = (((unsigned char *) q2)[7] >> 3) & 1 ? 1 : 0;
    } else {
        flag2 = 0;
    }

    if (flag2 != 0) {
        return 2;
    }
    return 0;
}

int func_020539e4(int arg0)
{
    if (func_0204bcdc(arg0) != 0) {
        return func_02053a04(func_0204bc64(arg0));
    }
    return 0;
}

unsigned char func_020539b0(int param)
{
    int idx = param;
    void *base;
    UnkStruct_020539b0 *d;
    if (param >= 1769) {
        idx = 1768;
    }
    base = func_0206e6ec(data_021c8c48);
    d = func_0206e7bc(base, idx);
    if (d) {
        return d->unk_06;
    }
    return 0;
}

int func_02053990(int arg)
{
    if (func_0204bcdc(arg)) {
        return (int) func_020539b0(func_0204bc64(arg));
    }
    return 0;
}

int func_0205395c(int param)
{
    int r4;
    unsigned char *p;

    r4 = param;
    if (r4 >= 1769) {
        r4 = 1768;
    }

    p = (unsigned char *) func_0206e7bc(func_0206e6e4(((unsigned char *) data_021c8c48)), r4);
    if (p) {
        return p[0x1a];
    } else {
        return 0;
    }
}

int func_0205391c(int id)
{
    void *obj;
    unsigned char flags;

    if (id >= 0x6e9) {
        id = 0x6e8;
    }
    obj = func_0206e7bc(func_0206e6e8(((int *) data_021c8c48)), id);
    if (obj == 0) {
        goto fail;
    }
    flags = *((unsigned char *) obj + 1);
    if ((flags & 1) != 0) {
        return 1;
    }
    return 0;
fail:
    return 0;
}

int func_020538dc(int param0)
{
    int r4;
    void *a;
    unsigned char *p;
    unsigned char b;
    int flag;

    r4 = param0;
    if (param0 >= 0x6e9) {
        r4 = 0x6e8;
    }
    a = func_0206e6e8((void *) data_021c8c48);
    p = (unsigned char *) func_0206e7bc(a, r4);
    if (p != 0) {
        b = p[1];
        flag = (b >> 2) & 1;
        if (flag != 0) {
            return 1;
        } else {
            return 0;
        }
    } else {
        return 0;
    }
}

int func_0205389c(int arg)
{
    int r4;
    void *p;
    void *q;
    r4 = arg;
    if (r4 >= 0x6e9) {
        r4 = 0x6e8;
    }
    p = func_0206e6e8(((char *) data_021c8c48));
    q = func_0206e7bc(p, r4);
    if (q != 0) {
        if (((((unsigned char *) q)[1] >> 3) & 1) != 0) {
            return 1;
        }
        return 0;
    }
    return 0;
}

int func_02053818(int id)
{
    unsigned char *p;
    int flag;
    int idx;

    if (id >= 0x6e9) {
        idx = 0x6e8;
    } else {
        idx = id;
    }
    p = (unsigned char *) func_0206e7bc(func_0206e6e8((void *) data_021c8c48), idx);
    if (p != 0) {
        if (((p[1] >> 4) & 1) != 0) {
            flag = 1;
        } else {
            flag = 0;
        }
    } else {
        flag = 0;
    }
    if (flag != 0) {
        return 1;
    }

    if (id >= 0x6e9) {
        id = 0x6e8;
    }
    p = (unsigned char *) func_0206e7bc(func_0206e6e8((void *) data_021c8c48), id);
    if (p != 0) {
        if (((p[1] >> 5) & 1) != 0) {
            flag = 1;
        } else {
            flag = 0;
        }
    } else {
        flag = 0;
    }
    if (flag != 0) {
        return 2;
    }
    return 0;
}

int func_020537e8(int param)
{
    int a;
    int v;
    a = param;
    if (a >= 1769) {
        a = 1768;
    }
    v = (int) func_0206e7bc((void *) ((int) func_0206e6e4((void *) ((unsigned int) data_021c8c48))), a);
    if (v) {
        return v;
    } else {
        return 0;
    }
}

int func_020537a8(int param)
{
    int x;
    void *p;
    void *q;
    x = param;
    if (x >= 0x6E9) {
        x = 0x6E8;
    }
    p = func_0206e6e8((void *) data_021c8c48);
    q = func_0206e7bc(p, x);
    if (q != 0) {
        if ((((unsigned char *) q)[1] >> 6) & 1) {
            return 1;
        } else {
            return 0;
        }
    }
    return 0;
}

int func_02053748(int param)
{
    int x;
    void *p;
    void *q;
    int flag;
    int c;

    if (param >= 0x6E9) {
        x = 0x6E8;
    } else {
        x = param;
    }
    p = func_0206e6e8((void *) data_021c8c48);
    q = func_0206e7bc(p, x);
    if (q != 0) {
        if ((((unsigned char *) q)[1] >> 7) & 1) {
            flag = 1;
        } else {
            flag = 0;
        }
    } else {
        flag = 0;
    }

    c = (int) func_02053de4(param);
    if (c != 0x23 && c != 0x24 && c != 0x25) {
        return flag;
    }
    return 0;
}

int func_02053728(int arg)
{
    if (func_0204bcdc(arg) != 0) {
        return func_02053748((int) func_0204bc64(arg));
    } else {
        return 0;
    }
}

int func_020536e8(int param)
{
    unsigned char *q;
    if (param >= 0x6e9) {
        param = 0x6e8;
    }
    q = (unsigned char *) func_0206e7bc(func_0206e6e8((void *) (((unsigned char *) data_021c8c48))), param);
    if (q != 0) {
        if (q[2] & 1) {
            return 1;
        }
        return 0;
    } else {
        return 0;
    }
}

int func_020536c8(int arg)
{
    if (func_0204bcdc(arg) != 0) {
        return func_020536e8(func_0204bc64(arg));
    }
    return 0;
}

int func_02053690(int param)
{
    void *ptr;
    UnkStruct_02053690 *result;
    unsigned char val;

    if (param >= 0x6e9) {
        param = 0x6e8;
    }

    ptr = func_0206e6e4(((char *) data_021c8c48));
    result = (UnkStruct_02053690 *) func_0206e7bc(ptr, param);

    if (result != 0) {
        val = result->unk_1B;
    } else {
        val = 0;
    }

    return val << 12;
}

signed char func_02053658(int param)
{
    int index;
    void *base;
    void *ptr;

    if (param < 0x6e9) {
        index = param;
    } else {
        index = 0x6e8;
    }

    base = func_0206e6e4(((char *) data_021c8c48));
    ptr = func_0206e7bc(base, index);

    return (signed char) (ptr ? ((unsigned char *) ptr)[0x1c] : 0);
}

unsigned char func_02053624(int param)
{
    unsigned char *ptr;

    if (param >= 0x6e9) {
        param = 0x6e8;
    }

    ptr = (unsigned char *) func_0206e7bc((void *) ((int) func_0206e6e8((void *) data_021c8c48)), param);
    if (ptr) {
        return *ptr;
    }
    return 0;
}

int func_020535f0(unsigned short *p)
{
    unsigned int v;
    int flag;

    flag = 0;
    v = *p;
    if (v >= 0x450c && v <= 0x45db) {
        flag = 1;
    }
    if (flag != 0) {
        return (int) func_02053624(func_0204bc64((int) p));
    }
    return 0;
}

int func_020535b4(int arg)
{
    int count = 0;
    unsigned int i = 0;
    unsigned short val;

    do {
        val = (unsigned short) ((i < 0x34) ? (0x450c + (i << 2)) : 0x450c);
        if (arg == func_020535f0(&val)) {
            count++;
        }
        i++;
    } while (i < 0x34);

    return count;
}

unsigned char func_0205352c(unsigned short *a0)
{
    int flagA = 0;
    int argB = 0;
    int flagC = 0;
    int wanted = func_02053c68((int) a0);
    int count = 0;
    unsigned int i;
    int found;

    for (i = 0; i < 0x6e9; i++) {
        unsigned short local;

        local = func_0204bc50(i, argB);
        if (func_0204bcdc((int) (&local))) {
            int x = func_0204bc64((int) (&local));
            int y = func_0204bc64((int) a0);
            found = (x == y) ? 1 : flagA;
        } else {
            found = (local == *a0) ? 1 : flagC;
        }
        if (found) {
            return count;
        }
        if (wanted == (int) func_02053c88(i)) {
            count++;
        }
    }
    return 0;
}

unsigned char func_020534ec(unsigned int param)
{
    unsigned char count = 0;
    unsigned int i;
    for (i = 0; i < 0x6e9; i++) {
        volatile unsigned short tmp;
        tmp = (unsigned int) func_0204bc50(i, 0);
        if (param == (unsigned int) func_02053c88(i)) {
            count++;
        }
    }
    return count;
}
