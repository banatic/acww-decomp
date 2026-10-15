/* func_020015fc @ 0x020015fc, 0x12 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void MIi_CpuClearFast(unsigned int data, void *dest, unsigned int size);

void func_020015fc(unsigned int data, void *dest, unsigned int size)
{
    volatile unsigned int fill = data;
    MIi_CpuClearFast(fill, dest, size);
}
