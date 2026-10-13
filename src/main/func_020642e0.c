/* func_020642e0 @ 0x020642e0, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void MI_CpuFill8(void *dst, int val, int size);

void func_020642e0(void *arg0)
{
    unsigned char *ptr = (unsigned char *) arg0;
    MI_CpuFill8(ptr + 2, 0, 12);
    *(unsigned short *) ptr = 0;
}
