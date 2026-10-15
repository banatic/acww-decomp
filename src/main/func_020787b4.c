/* func_020787b4 @ 0x020787b4, 0x1e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02078a0c(int, int, int);
extern void func_020778b0(int, unsigned short);

void func_020787b4(int a, int b, int c, unsigned short *d)
{
    func_02078a0c(a + 2, b, c);
    func_020778b0(a, *d);
}
