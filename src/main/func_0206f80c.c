/* func_0206f80c @ 0x0206f80c, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void MI_CpuCopy8(void *buf, int val, int size);
extern int data_021cfc98;

void func_0206f80c(int val)
{
    MI_CpuCopy8(&data_021cfc98, val, 8);
}
