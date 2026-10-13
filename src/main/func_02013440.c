/* func_02013440 @ 0x02013440, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void MI_CpuFill8(void *ptr, int value, int count);

void func_02013440(void *ptr)
{
    MI_CpuFill8((char *) ptr + 0x2c, 0, 0x5a);
}
