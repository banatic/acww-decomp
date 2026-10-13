/* func_020887f8 @ 0x020887f8, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void MI_CpuFill8(void *p, int value, int size);

void func_020887f8(void *p)
{
    MI_CpuFill8((char *) p + 4, 0, 8);
}
