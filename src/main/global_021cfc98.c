/* global_021cfc98: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0206f820 @ 0x0206f820, 0x10 bytes, Thumb
 * func_0206f80c @ 0x0206f80c, 0x14 bytes, Thumb
 */

extern void MI_CpuCopy8(int a, int b, int c);
extern unsigned char data_021cfc98[];

void func_0206f820(int a)
{
    MI_CpuCopy8(a, (unsigned int) data_021cfc98, 8);
}

void func_0206f80c(int val)
{
    MI_CpuCopy8((int) (((int *) data_021cfc98)), val, 8);
}
