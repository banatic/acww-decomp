/* func_020af298 @ 0x020af298, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void MI_CpuCopy8(const void *src, void *dest, int size);

void func_020af298(unsigned char *a, const unsigned char *b)
{
    unsigned char buf[8];
    MI_CpuCopy8(b, buf, 8);
    a[0x50] = buf[5];
    a[0x4f] = buf[4];
    a[0x4e] = buf[3];
    a[0x51] = 0;
}
