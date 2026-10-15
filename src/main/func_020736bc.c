/* func_020736bc @ 0x020736bc, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020736e4(int a);
extern void MI_CpuCopy8(int a, int b, int c);
extern void func_020736ec(int a, int b);

void func_020736bc(int a, int b, int c)
{
    int tmp;
    tmp = func_020736e4(a);
    MI_CpuCopy8(tmp, b, c);
    func_020736ec(a, tmp + c);
}
