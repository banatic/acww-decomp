/* func_02007d2c @ 0x02007d2c, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void MI_CpuFill8(void *dst, int src, int size);

void func_02007d2c(int r0)
{
    MI_CpuFill8((void *) (r0 + 0x7d4), 0, 0x1c);
}
