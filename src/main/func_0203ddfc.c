/* func_0203ddfc @ 0x0203ddfc, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void MI_CpuFill8(void *ptr, int value, int size);

void func_0203ddfc(void *arg0)
{
    MI_CpuFill8((char *) arg0 + 0xa4, 0, 0x200);
}
