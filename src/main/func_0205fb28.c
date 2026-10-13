/* func_0205fb28 @ 0x0205fb28, 0x9c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int _s32_div_f(int, int);
extern int func_020e8bb0(int *, int, int, int, int);

int func_0205fb28(int *a, int b, int *c, int *d, unsigned char flag)
{
    int key;
    int mode;
    int alloc;
    int result1;
    int result2;
    int sum;

    if (flag) {
        key = 0xccd;
        mode = 5;
    } else {
        key = 0xccd;
        mode = 10;
    }

    alloc = _s32_div_f(0x1000, mode);
    result1 = func_020e8bb0(c, a[0], alloc, key, 0x19a);
    result2 = func_020e8bb0(c + 2, a[2], alloc, key, 0x19a);
    sum = result1 + result2;

    if (*d < 0 && flag) {
        func_020e8bb0(c + 1, a[1], alloc, 0xccd, 0x52);
    } else {
        c[1] += *d;
        *d -= b;
    }

    return sum == 0;
}
