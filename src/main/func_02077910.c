/* func_02077910 @ 0x02077910, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void MI_CpuCopy8(int *dst, int src, int n);

void func_02077910(int a, int b)
{
    MI_CpuCopy8(&b, a, 2);
}
