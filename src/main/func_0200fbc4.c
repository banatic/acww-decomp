/* func_0200fbc4 @ 0x0200fbc4, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0200fb58(int a, int b, int c);
extern void func_0200fb34(int a, int b);

void func_0200fbc4(int a, int b, int c, int d)
{
    int tmp1 = a;
    int tmp2 = d;
    func_0200fb58(a, b, c);
    func_0200fb34(tmp1, tmp2);
}
