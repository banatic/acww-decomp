/* func_02083d54 @ 0x02083d54, 0x22 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208602c(int a, int b, int c, int d);
extern int func_020860bc(int x);
extern void func_02087a78(int a, int b, int c, int d);

int func_02083d54(int a, int b, int c, int d)
{
    func_02087a78(func_020860bc(func_0208602c(a, b, c, d)), b, c + 2, d);
    return 1;
}
