/* item_traits_4: 8 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0204ca48 @ 0x0204ca48, 0x18 bytes, Thumb
 * func_0204ca08 @ 0x0204ca08, 0x40 bytes, Thumb
 * func_0204c878 @ 0x0204c878, 0x190 bytes, Thumb
 * func_0204c86c @ 0x0204c86c, 0xc bytes, Thumb
 * func_0204c7f0 @ 0x0204c7f0, 0x7c bytes, Thumb
 * func_0204c7c8 @ 0x0204c7c8, 0x28 bytes, Thumb
 * func_0204c7c0 @ 0x0204c7c0, 0x8 bytes, Thumb
 * func_0204c788 @ 0x0204c788, 0x38 bytes, Thumb
 */

typedef struct UnkStruct_0204c878 {
    short v;
} UnkStruct_0204c878;

typedef struct UnkStruct_0204c788 UnkStruct_0204c788;

extern int func_0204bcdc(void *);
extern int func_0204bc64(int);
extern void func_02061e2c(UnkStruct_0204c878 *, void *);
extern int func_0204bcf8(UnkStruct_0204c878 *);
extern int func_0204b42c(void *);
extern void func_0204b3cc(UnkStruct_0204c878 *, int);
extern int func_020628ac(UnkStruct_0204c878 *);
extern void func_020051b0(UnkStruct_0204c878 *);
extern int func_0204ca64(UnkStruct_0204c878 *);
extern int func_0204ca60(int);
extern int func_02053e18(int object);
extern int func_020adde4(unsigned short);
extern int FX_Div(int numerator, int denominator);
extern int func_020984e8(void);
extern unsigned int func_020996a0(unsigned int object);
extern unsigned short *func_020adf50(void *record);
extern int data_021dc7a8;
extern int func_020afb90(int a);

int func_0204c7c8(unsigned short *p);
int func_0204c7c0(void);

unsigned short func_0204ca48(unsigned int x)
{
    if (x < 5) {
        return (unsigned short) (0x1518 + x);
    }
    return 0x1518;
}

int func_0204ca08(int a, int b)
{
    int r5 = a;
    int r4 = b;
    if (func_0204bcdc((void *) a)) {
        r5 = func_0204bc64(r5);
        if (r5 == func_0204bc64(r4)) {
            return 1;
        } else {
            return 0;
        }
    } else {
        if (*(unsigned short *) r5 == *(unsigned short *) r4) {
            return 1;
        } else {
            return 0;
        }
    }
}

int func_0204c878(void *arg)
{
    int forwarded_value;

    UnkStruct_0204c878 a, b, c, d, e, f;
    int r;

    func_02061e2c(&a, arg);
    switch (func_0204bcf8(&a)) {
        case 1:
            if (func_0204c7c8((unsigned short *) (&a)) != 0) {
                func_0204b3cc(&c, func_0204b42c(&a));
                r = 10 * func_020628ac(&c);
                func_020051b0(&c);
                func_020051b0(&a);
                return r;
            }
            if (func_0204ca64(&a) != 0) {
                func_0204b3cc(&b, (int) func_0204ca48((unsigned int) func_0204ca60(func_0204c7c0() + 0x17254)));
                if (func_0204ca08((int) (&a), (int) (&b)) != 0) {
                    func_0204b3cc(&d, func_0204b42c(&a));
                    r = func_020628ac(&d) / 5;
                    func_020051b0(&d);
                    func_020051b0(&b);
                    func_020051b0(&a);
                    return r;
                }
                func_020051b0(&b);
            } else if (func_0204b42c(arg) == 0x1406 || func_0204b42c(arg) == 0x1407) {
                func_0204b3cc(&e, func_0204b42c(&a));
                r = 100 * func_020628ac(&e);
                func_020051b0(&e);
                func_020051b0(&a);
                return r;
            }
            func_0204b3cc(&f, func_0204b42c(&a));
            r = func_020628ac(&f);
            func_020051b0(&f);
            func_020051b0(&a);
            return r;
        case 3:
        case 4:
            if ((forwarded_value = (int) func_0204bc64((int) (&a))) == 0x208) {
                r = 100 * func_02053e18((int) forwarded_value);
                func_020051b0(&a);
                return r;
            }
            r = func_02053e18((int) forwarded_value);
            func_020051b0(&a);
            return r;
        default:
            func_020051b0(&a);
            return 0;
    }
}

int func_0204c86c(unsigned short *ptr)
{
    return func_020adde4(*ptr);
}

int func_0204c7f0(void *p)
{
    int forwarded_value;

    int v;
    int pct;
    int mode;

    v = func_0204c878(p);
    if (func_0204c7c8((unsigned short *) p) != 0) {
        return v;
    }
    if ((forwarded_value = (int) func_020984e8()) == 0) {
        goto ret_v;
    }
    mode = func_0204c86c(func_020adf50((void *) func_020996a0((unsigned int) forwarded_value)));
    pct = 0;
    switch (mode) {
        case 2:
            pct = 5;
            break;
        case 3:
            pct = 10;
            break;
        case 4:
            pct = 20;
            break;
    }
    if (pct == 0) {
        return v;
    }
    v = (100 - pct) * v;
    if (v >= 100) {
        return v / 100;
    }
    return FX_Div(v << 12, 100 << 12) >> 12;
ret_v:
    return v;
}

int func_0204c7c8(unsigned short *p)
{
    unsigned short val;
    int flag;

    flag = 0;
    val = *p;
    if (val >= 0x1492 && val <= 0x14fd) {
        flag = 1;
    }
    if (flag) {
        return 1;
    } else {
        return 0;
    }
}

int func_0204c7c0(void)
{
    return (int) &data_021dc7a8;
}

int func_0204c788(UnkStruct_0204c788 *p)
{
    int v = func_0204c7f0((void *) p);
    if (func_0204c7c8((unsigned short *) p) != 0) {
        return v;
    }
    v = v >> func_020afb90(func_0204c7c0() + 0x171b4);
    return v;
}
