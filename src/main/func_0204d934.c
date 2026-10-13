/* func_0204d934 @ 0x0204d934, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020e993c(int a, int b);

void func_0204d934(int *p, int arg)
{
    int i;
    for (i = 0; i < 4; i++) {
        if (*p != 0) {
            func_020e993c(arg, *p);
            *p = 0;
            *(p + 1) = 0;
            p += 2;
        }
    }
}
