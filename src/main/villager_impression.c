/* villager_impression: 34 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0207e664 @ 0x0207e664, 0x10 bytes, Thumb
 * func_0207e654 @ 0x0207e654, 0x10 bytes, Thumb
 * func_0207e648 @ 0x0207e648, 0xc bytes, Thumb
 * func_0207e60c @ 0x0207e60c, 0x3c bytes, Thumb
 * func_0207e604 @ 0x0207e604, 0x8 bytes, Thumb
 * func_0207e5dc @ 0x0207e5dc, 0x28 bytes, Thumb
 * func_0207e5d4 @ 0x0207e5d4, 0x8 bytes, Thumb
 * func_0207e5b0 @ 0x0207e5b0, 0x24 bytes, Thumb
 * func_0207e58c @ 0x0207e58c, 0x24 bytes, Thumb
 * func_0207e55c @ 0x0207e55c, 0x30 bytes, Thumb
 * func_0207e52c @ 0x0207e52c, 0x30 bytes, Thumb
 * func_0207e4fc @ 0x0207e4fc, 0x30 bytes, Thumb
 * func_0207e4d8 @ 0x0207e4d8, 0x24 bytes, Thumb
 * func_0207e458 @ 0x0207e458, 0x80 bytes, Thumb
 * func_0207e3f4 @ 0x0207e3f4, 0x64 bytes, Thumb
 * func_0207e390 @ 0x0207e390, 0x64 bytes, Thumb
 * func_0207e310 @ 0x0207e310, 0x80 bytes, Thumb
 * func_0207e2ec @ 0x0207e2ec, 0x22 bytes, Thumb
 * func_0207e2c8 @ 0x0207e2c8, 0x22 bytes, Thumb
 * func_0207e2a4 @ 0x0207e2a4, 0x22 bytes, Thumb
 * func_0207e280 @ 0x0207e280, 0x22 bytes, Thumb
 * func_0207e25c @ 0x0207e25c, 0x22 bytes, Thumb
 * func_0207e238 @ 0x0207e238, 0x22 bytes, Thumb
 * func_0207e214 @ 0x0207e214, 0x22 bytes, Thumb
 * func_0207e1f0 @ 0x0207e1f0, 0x22 bytes, Thumb
 * func_0207e1c4 @ 0x0207e1c4, 0x2c bytes, Thumb
 * func_0207e198 @ 0x0207e198, 0x2c bytes, Thumb
 * func_0207e16c @ 0x0207e16c, 0x2c bytes, Thumb
 * func_0207e144 @ 0x0207e144, 0x28 bytes, Thumb
 * func_0207e11c @ 0x0207e11c, 0x28 bytes, Thumb
 * func_0207e118 @ 0x0207e118, 0x4 bytes, Thumb
 * func_0207e0c4 @ 0x0207e0c4, 0x54 bytes, Thumb
 * func_0207e054 @ 0x0207e054, 0x6e bytes, Thumb
 * func_0207e008 @ 0x0207e008, 0x4c bytes, Thumb
 */

struct Triple {
    int a;
    int b;
    int c;
};

typedef int (*Fn)(int, int, int);

typedef struct UnkStruct_0207e0c4 {
    signed char kind;
    char pad_01[3];
    Fn fn;
} UnkStruct_0207e0c4;

extern unsigned int func_0203cc14(void);
extern int func_0203cbf4(void);
extern int func_0203cc1c(void);
extern unsigned int func_0203cc18(void);
extern int func_0203cc04(void);
extern int func_0203cc38(void);
extern int func_02099734(int);
extern int func_02098cf8(int, int);
extern unsigned short *func_020996e0(int);
extern int func_02099824(int);
extern int func_02099870(int);
extern int func_02094ffc(void *);
extern int func_02098880(char *ptr);
extern char data_021dc7bc[];
extern void func_0209e474(void *p);
extern UnkStruct_0207e0c4 data_020cd5c4[];
extern int func_020950c0(signed char *);
extern unsigned int func_0208150c(unsigned int);
extern int func_02003704(void *);
extern int func_020984e8(void);
extern int func_020807a8(int, int);
extern int func_02081d20(int);
extern int func_0207f270(int);
extern int func_020794c4(unsigned char *);
extern void func_02081a80(int, int);
extern unsigned int func_02081a88(int);
extern int func_020b4a20(int, void *, void *);
extern char data_020e195c[];

int func_0207e604(void);
int func_0207e5d4(int a, int b, int c);
int func_0207e2ec(int arg, int b, int c);
int func_0207e2c8(int param, int b, int c);
int func_0207e2a4(int x, int b, int c);
int func_0207e280(int arg, int b, int c);
int func_0207e25c(int arg, int b, int c);
int func_0207e238(int param, int b, int c);
int func_0207e214(int param, int b, int c);
int func_0207e1f0(int param, int b, int c);

int func_0207e664(int a, int b)
{
    if (b <= -30) {
        return 1;
    } else {
        return 0;
    }
}

int func_0207e654(int r0, int r1)
{
    if (r1 >= 0x46 && r1 < 0x6e) {
        return 1;
    } else {
        return 0;
    }
}

int func_0207e648(int r0, int r1)
{
    if (r1 < 0x6e) {
        return 0;
    }
    return 1;
}

int func_0207e60c(int a, int b, int c)
{
    int shift;
    if (func_0207e604() != 0) {
        goto ret0;
    }
    if (func_0207e5d4(a, b, c) != 0) {
        goto ret0;
    }
    shift = (unsigned) func_0203cc14() >> 1;
    if (func_0203cbf4() < shift) {
        return 0;
    }
    return 1;
ret0:
    return 0;
}

int func_0207e604(void)
{
    return func_0203cc1c();
}

int func_0207e5dc(int a, int b, int c)
{
    if (func_0207e5d4(a, b, c) == 0) {
        int tmp = (unsigned int) func_0203cc18() >> 1;
        if (func_0203cc04() < tmp) {
            return 0;
        } else {
            return 1;
        }
    } else {
        return 0;
    }
}

int func_0207e5d4(int a, int b, int c)
{
    return func_0203cc38();
}

int func_0207e5b0(int argument0)
{
    if (func_02098cf8(func_02099734((int) argument0), 1) > 300) {
        return 0;
    } else {
        return 1;
    }
}

int func_0207e58c(int argument0)
{
    if (func_02098cf8(func_02099734((int) argument0), 1) > 1000) {
        return 0;
    } else {
        return 1;
    }
}

int func_0207e55c(int object)
{
    int v;
    v = func_02098cf8(func_02099734(object), 1);
    if (v >= 10000 && v < 20000) {
        return 1;
    }
    return 0;
}

int func_0207e52c(int object)
{
    int y;
    y = func_02098cf8(func_02099734(object), 1);
    if (y >= 20000 && y < 40000) {
        return 1;
    } else {
        return 0;
    }
}

int func_0207e4fc(int object)
{
    int value;

    value = func_02098cf8(func_02099734(object), 1);
    if (value >= 0x9c40 && value < 0xea60) {
        return 1;
    } else {
        return 0;
    }
}

int func_0207e4d8(int argument0)
{
    return func_02098cf8(func_02099734((int) argument0), 1) >= 0xea60;
}

int func_0207e458(int a, int b, int c)
{
    int result = 0;
    unsigned short *ptr = func_020996e0(a);
    int flag = 0;
    unsigned short val = *ptr;
    if (val >= 0x1431 && val <= 0x1470) {
        flag = 1;
    }
    if (flag != 0) {
        if (func_0207e2ec(a, b, c) != 0 || func_0207e2c8(a, b, c) != 0 || func_0207e25c(a, b, c) != 0 ||
            func_0207e238(a, b, c) != 0 || func_0207e1f0(a, b, c) != 0) {
            result = 1;
        }
    }
    return result;
}

int func_0207e3f4(int a, int b, int c)
{
    int result = 0;
    int flag;
    unsigned short value;
    unsigned short *ptr;

    ptr = func_020996e0(a);
    flag = 0;
    value = *ptr;
    if (value >= 0x1431u && value <= 0x1470u) {
        flag = 1;
    }

    if (flag) {
        if (func_0207e2a4(a, b, c) != 0 || func_0207e280(a, b, c) != 0 || func_0207e214(a, b, c) != 0) {
            result = 1;
        }
    }

    return result;
}

int func_0207e390(int a, int b, int c)
{
    int result = 0;
    int flag;
    unsigned short value;
    unsigned short *ptr;

    ptr = func_020996e0(a);
    flag = 0;
    value = *ptr;
    if (value >= 0x1431u && value <= 0x1470u) {
        flag = 1;
    }

    if (flag) {
        if (func_0207e2a4(a, b, c) != 0 || func_0207e25c(a, b, c) != 0 || func_0207e214(a, b, c) != 0) {
            result = 1;
        }
    }

    return result;
}

int func_0207e310(int a, int b, int c)
{
    int result = 0;
    unsigned short *ptr = func_020996e0(a);
    int flag = 0;
    unsigned short val = *ptr;
    if (val >= 0x1431 && val <= 0x1470) {
        flag = 1;
    }
    if (flag != 0) {
        if (func_0207e2ec(a, b, c) != 0 || func_0207e2c8(a, b, c) != 0 || func_0207e280(a, b, c) != 0 ||
            func_0207e238(a, b, c) != 0 || func_0207e1f0(a, b, c) != 0) {
            result = 1;
        }
    }
    return result;
}

int func_0207e2ec(int arg, int b, int c)
{
    return (func_02099824(arg) == 0 || func_02099824(arg) == 8) ? 1 : 0;
}

int func_0207e2c8(int param, int b, int c)
{
    if (func_02099824(param) == 1 || func_02099824(param) == 9) {
        return 1;
    } else {
        return 0;
    }
}

int func_0207e2a4(int x, int b, int c)
{
    return (func_02099824(x) == 2) || (func_02099824(x) == 10);
}

int func_0207e280(int arg, int b, int c)
{
    return (func_02099824(arg) == 3) || (func_02099824(arg) == 0xb);
}

int func_0207e25c(int arg, int b, int c)
{
    if (func_02099824(arg) == 4 || func_02099824(arg) == 12) {
        return 1;
    } else {
        return 0;
    }
}

int func_0207e238(int param, int b, int c)
{
    if (func_02099824(param) == 5 || func_02099824(param) == 0xd) {
        return 1;
    }
    return 0;
}

int func_0207e214(int param, int b, int c)
{
    if (func_02099824(param) == 6 || func_02099824(param) == 14) {
        return 1;
    } else {
        return 0;
    }
}

int func_0207e1f0(int param, int b, int c)
{
    if (func_02099824(param) == 7 || func_02099824(param) == 15) {
        return 1;
    } else {
        return 0;
    }
}

int func_0207e1c4(int argument0)
{
    if (func_02094ffc((void *) func_02099870((int) argument0)) == 0 && func_02098880(data_021dc7bc) == 4) {
        return 1;
    }
    return 0;
}

int func_0207e198(int argument0)
{
    if (func_02094ffc((void *) func_02099870((int) argument0)) == 0 &&
        func_02098880((char *) (((char *) data_021dc7bc))) >= 2) {
        return 1;
    }
    return 0;
}

int func_0207e16c(void)
{
    struct Triple s;
    s.a = 0;
    s.b = 0;
    func_0209e474(&s);
    if (*(unsigned char *) &s.b == 12 || (*(unsigned char *) &s.b >= 1 && *(unsigned char *) &s.b <= 2)) {
        return 1;
    }
    return 0;
}

int func_0207e144(void)
{
    int a[3];
    a[0] = 0;
    a[1] = 0;
    func_0209e474((void *) a);
    if (((unsigned char *) a)[4] >= 9 && ((unsigned char *) a)[4] <= 11) {
        return 1;
    }
    return 0;
}

int func_0207e11c(void)
{
    int local[2];
    unsigned char b;

    local[0] = 0;
    local[1] = 0;
    func_0209e474(local);
    b = ((unsigned char *) local)[4];
    if (b >= 6 && b <= 8) {
        return 1;
    } else {
        return 0;
    }
}

int func_0207e118(void)
{
    return 1;
}

int func_0207e0c4(int a, int b, int c)
{
    UnkStruct_0207e0c4 *e;
    int k;
    int res;
    int i;

    k = func_020950c0((signed char *) func_02099870(a));
    e = data_020cd5c4;
    res = 0x58;
    for (i = 0; i < 0x58; i++) {
        if (e->kind == 2 || e->kind == k) {
            if (e->fn(a, b, c) != 0) {
                res = (unsigned char) i;
                goto done;
            }
        }
        e++;
    }
done:
    return res;
}

int func_0207e054(int arg1, int arg2, int arg3)
{
    int result = 0x58;

    if (func_02003704((void *) func_0208150c(arg1)) != 0) {
        if (arg3 == 0) {
            arg3 = func_020984e8();
        }
        if (arg3 != 0 && arg2 == 0) {
            arg2 = func_020807a8(arg1, func_02099870(arg3));
        }
        if (arg2 != 0) {
            result = func_02081d20(arg2);
            result = func_0207e0c4(arg3, result, func_020794c4((unsigned char *) func_0207f270(arg1)));
            func_02081a80(arg2, result);
        }
    }
    return result;
}

void func_0207e008(int a, int b, int c)
{
    int v;
    void *p;
    unsigned int t;
    char local;

    if (c == 0) {
        c = func_020984e8();
    }

    v = 0;
    if (c != 0) {
        p = (void *) func_02099870(c);
        v = func_020807a8(a, (int) p);
    }

    if (v) {
        t = func_02081a88(v);
        if (t < 0x58) {
            local = (char) t;
            func_020b4a20(b, &local, data_020e195c);
        }
    }
}
