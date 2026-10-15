/* func_02042c40 @ 0x02042c40, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void MI_CpuFill8(void *dst, unsigned char value, unsigned int size);

extern unsigned char data_021c7cb4[];

void func_02042c40(void *receiver)
{
    MI_CpuFill8((void *) data_021c7cb4, 0, 0x400);
}
