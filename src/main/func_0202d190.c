/* func_0202d190 @ 0x0202d190, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0202d0ec(int a1, int a2, int a3, int a4, int a5, int a6);

void func_0202d190(int a1, int a2, int a3, int a4)
{
    int sp[2];
    sp[0] = 0x17;
    sp[1] = a4;
    func_0202d0ec(a1, a2, a3, 0, sp[0], sp[1]);
}
