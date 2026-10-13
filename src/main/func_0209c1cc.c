/* func_0209c1cc @ 0x0209c1cc, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0209dffc(int a, int b, int c);
extern int func_0209c380(int a);
extern int func_0209e350(int a, int b);
extern unsigned int _s32_div_f(unsigned int a, unsigned int b);

int func_0209c1cc(int a, int b, unsigned int c)
{
    int t;

    if (func_0209dffc(a, b, c) != 0) {
        goto ret0;
    }
    if (func_0209c380(a) == 0) {
        goto ret0;
    }
    t = func_0209e350(a, b);
    if (t < 0) {
        t = -t;
    }
    return (_s32_div_f(t, 0x5a0) >= c) ? 1 : 0;

ret0:
    return 0;
}
