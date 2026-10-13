/* func_020bdf68 @ 0x020bdf68, 0x70 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02095794(int);
extern void func_02095764(void *, int);
extern int func_020bdf58(void *, int);
extern void func_020bebec(int, int, int, int);
extern void func_020beba4(void *, int);
extern void func_020beb98(void *, int);

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
        func_020bebec(func_020bdf58(p, sel), n, ret, flag);
        func_020beba4((char *) p + 0x2fa8, n);
    } else {
        func_020beb98((char *) p + 0x2fa8, n);
    }
}
