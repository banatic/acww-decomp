/* func_0206f820 @ 0x0206f820, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void MI_CpuCopy8(int a, int b, int c);

extern unsigned char data_021cfc98[];

void func_0206f820(int a)
{
    MI_CpuCopy8(a, (unsigned int) data_021cfc98, 8);
}
