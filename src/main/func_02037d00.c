/* func_02037d00 @ 0x02037d00, 0xc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *MI_CpuFill8(void *dst, int c, unsigned int n);

void func_02037d00(void *dst)
{
    MI_CpuFill8(dst, 0, 0x20);
}
