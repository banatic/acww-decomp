/* func_02077928 @ 0x02077928, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02077978(int a, int b, int *c, int d);
extern int func_020779d8(int x, int y, int z);

int func_02077928(int a, int b, int *c, int d, int e)
{
    func_02077978(a, b, c, d);
    *c -= 0x80000;
    return func_020779d8(a + 5, d, e);
}
