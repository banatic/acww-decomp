/* func_020308e0 @ 0x020308e0, 0x3e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02030d68(int a, int b, int c);
extern void func_02030d48(int a, int b, int c);

void func_020308e0(int x, int y)
{
    func_02030d68(x, y, 0);
    func_02030d48(x, y - 1, 4);
    func_02030d48(x, y + 1, 1);
    func_02030d48(x - 1, y, 8);
    func_02030d48(x + 1, y, 2);
}
