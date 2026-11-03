/* sky_shots: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020bdf68 @ 0x020bdf68, 0x70 bytes, Thumb
 * func_020bdf58 @ 0x020bdf58, 0x10 bytes, Thumb
 */

struct element {
    char data[20];
};

struct container {
    char pad_00[0x2f58];
    struct element array[1];
};

extern int func_02095794(int);
extern void func_02095764(void *, int);
extern void func_020bebec(int, int, int, int);
extern void func_020beba4(void *, int);
extern void func_020beb98(void *, int);

struct element *func_020bdf58(struct container *base, int index);

void func_020bdf68(void *p, int n)
{
    int ret;
    struct {
        unsigned short a;
        unsigned short b;
        unsigned short c;
        unsigned short d;
    } loc;
    int sel;
    int flag;

    sel = 0;
    if (n < 4) {
        sel = n;
    }
    ret = func_02095794(n);
    if (ret != 0) {
        func_02095764(&loc, n);
        flag = 0;
        if (loc.a >= 0x137b && loc.a <= 0x137b) {
            flag = 1;
        }
        func_020bebec((int) func_020bdf58((struct container *) p, sel), n, ret, flag);
        func_020beba4((char *) p + 0x2fa8, n);
    } else {
        func_020beb98((char *) p + 0x2fa8, n);
    }
}

struct element *func_020bdf58(struct container *base, int index)
{
    return &base->array[index];
}
