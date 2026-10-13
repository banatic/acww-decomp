/* func_020aec40 @ 0x020aec40, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020aef5c(int a, int b);
extern void func_020b0164(int a, int b, int c, int d, int e, int f, int g);

void func_020aec40(int a, int b)
{
    func_020b0164(a + 4, b, 1, 0, func_020aef5c(a, b), 0x25, 0);
}
