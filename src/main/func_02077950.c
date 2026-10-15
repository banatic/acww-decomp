/* func_02077950 @ 0x02077950, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020779b8(int, int, int);
extern void func_02077a14(int, int, int);

void func_02077950(int a, int b, int c, int d, unsigned char e)
{
    func_020779b8(a, b, c + 0x80000);
    func_02077a14(a + 5, d, e);
}
