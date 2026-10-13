/* func_02084160 @ 0x02084160, 0x1a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208602c(int);
extern int func_020860c4(int);
extern void func_02087f40(int, int);

int func_02084160(int a, int b)
{
    int x;
    int y;
    x = func_0208602c(a);
    y = func_020860c4(x);
    func_02087f40(y, b);
    return 1;
}
