/* func_0204851c @ 0x0204851c, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020644cc(int);
extern int func_02048cb8(int, int, int, int, int, int (*)(void), int);
extern int func_02048ee4(void);

int func_0204851c(int a, int b, int c, int d)
{
    int t1 = func_020644cc(c);
    int t2 = func_020644cc(d);
    return func_02048cb8(a, b, t1 + 1, t2 + 1, 0x1b, func_02048ee4, 0);
}
