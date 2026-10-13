/* func_ov121_0229ab8c @ 0x0229ab8c, 0x20 bytes, Thumb, module ov121
 * mwccarm 1.2/base -O4,s
 */

extern char data_ov121_0229c258[][11];
extern void MI_CpuCopy8(char *dst, int off, int size);

void func_ov121_0229ab8c(int a, int b)
{
    MI_CpuCopy8(data_ov121_0229c258[b], a + 2320, 11);
}
