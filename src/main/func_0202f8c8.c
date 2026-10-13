/* func_0202f8c8 @ 0x0202f8c8, 0x1a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0202f8fc(int a, int b, int c);

void func_0202f8c8(int a, int *b, int *c)
{
    func_0202f8fc(a, b[0] + c[0], b[1] + c[1]);
}
