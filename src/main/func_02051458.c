/* func_02051458 @ 0x02051458, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void MI_CpuFill8(void *p, unsigned char b, unsigned int c);
extern int data_021c8344;

void func_02051458(void *ptr)
{
    unsigned char b = ((unsigned char *) ptr)[0x39];
    MI_CpuFill8(&data_021c8344, (unsigned char) (b | (b << 4)), 0x400);
}
