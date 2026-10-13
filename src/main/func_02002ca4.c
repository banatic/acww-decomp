/* func_02002ca4 @ 0x02002ca4, 0x32 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02064b2c(int, int, int, int *);
extern int func_02002b40(int, int, int, int);
extern void func_020e993c(int, int);

int func_02002ca4(int a0, int a1, int a2)
{
    int local;
    int x;
    int y;

    x = func_02064b2c(a0, a1, ~3, &local);
    y = func_02002b40(x, a2, local, 0);
    func_020e993c(a1, x);
    return y;
}
