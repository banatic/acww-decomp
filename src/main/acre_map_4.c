/* acre_map_4: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0204f89c @ 0x0204f89c, 0x1c bytes, Thumb
 * func_0204f86c @ 0x0204f86c, 0x30 bytes, Thumb
 */

extern char *func_020e9958(int a, int b);

void func_0204f89c(int *p)
{
    int *q;
    int i;

    q = p + 1;
    p[0] = 0x102a;
    for (i = 0; i < 2; i++) {
        *q++ = 0;
    }
    p[3] = 0;
}

char *func_0204f86c(int arg0, int arg1)
{
    char *result;
    int i;
    result = func_020e9958(arg1, arg0 << 4);
    if (result != 0) {
        for (i = 0; i < arg0; i++) {
            if (result + (i << 4) != 0) {
                func_0204f89c((int *) (result + (i << 4)));
            }
        }
    }
    return result;
}
