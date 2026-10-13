/* func_ov093_0229937c @ 0x0229937c, 0x20 bytes, Thumb, module ov093
 * mwccarm 1.2/base -O4,s
 */

extern void MIi_CpuCopy16(void *dst, const void *src, unsigned int size);

void func_ov093_0229937c(void *dst, const void *src, int a, int b)
{
    MIi_CpuCopy16((char *) dst + 0x1028 + (a << 6), (char *) src + (b << 6), 0x40);
}
