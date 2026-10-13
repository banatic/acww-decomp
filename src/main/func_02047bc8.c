/* func_02047bc8 @ 0x02047bc8, 0x2e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02047dd4(int a, int b, int c, int d, int e, int f, int g);
extern void func_0204886c(int a, int b, int c, int d);

void func_02047bc8(int a, int b, int c, int d, int e, int f, int g)
{
    int x;
    x = func_02047dd4(a, 14, c, d, e, f, g);
    func_0204886c(a, b, 1, x);
}
