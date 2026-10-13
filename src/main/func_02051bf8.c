/* func_02051bf8 @ 0x02051bf8, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void MI_CpuFill8(int a, int b, int c);

void func_02051bf8(int a, int b)
{
    MI_CpuFill8(a, 0, b << 1);
}
