/* func_02077e68 @ 0x02077e68, 0xc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void MI_CpuFill8(void *dest, int val, unsigned int count);

void func_02077e68(void *ptr)
{
    MI_CpuFill8(ptr, 0, 12);
}
