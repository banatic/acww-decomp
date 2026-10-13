/* func_0207e60c @ 0x0207e60c, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0207e604(int, int, int);
extern int func_0207e5d4(int, int, int);
extern unsigned int func_0203cc14(void);
extern int func_0203cbf4(void);

int func_0207e60c(int a, int b, int c)
{
    int shift;
    if (func_0207e604(a, b, c) != 0) {
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
