/* func_020780f0 @ 0x020780f0, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void MI_CpuCopy8(unsigned char *dst, const unsigned char *src, unsigned int size);

void func_020780f0(unsigned char *base, int start)
{
    int i;

    for (i = start; i < base[0xb7e] - 1; i++) {
        MI_CpuCopy8(base + (i + 1) * 0xc4, base + i * 0xc4, 0xc4);
    }

    base[0xb7e]--;
}
