/* func_02042484 @ 0x02042484, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void MI_CpuFill8(void *ptr, int a, int b);

int func_02042484(void *ptr)
{
    ((char *) ptr)[0x10e8] = 0;
    ((char *) ptr)[0x10e9] = 0;
    ((char *) ptr)[0x10ea] = 0;
    MI_CpuFill8(ptr, 0, 0xc0);
    *(int *) ((char *) ptr + 0x64) = 2;
    return 2;
}
