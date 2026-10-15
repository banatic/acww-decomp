/* func_02051c08 @ 0x02051c08, 0xc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void MI_CpuCopy8(int a, int b, int c);

void func_02051c08(int a, int b, int c)
{
    MI_CpuCopy8(a, b, c << 1);
}
