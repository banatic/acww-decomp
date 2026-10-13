/* func_020778b0 @ 0x020778b0, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void MI_CpuCopy8(int *param1, int param2, int param3);

void func_020778b0(int a, int b, ...)
{
    MI_CpuCopy8(&b, a, 2);
}
