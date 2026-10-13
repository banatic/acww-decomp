/* func_02066830 @ 0x02066830, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void MI_CpuCopy8(int, int, int);

int func_02066830(int a, int b)
{
    MI_CpuCopy8(b, a, 0x100);
    return a;
}
