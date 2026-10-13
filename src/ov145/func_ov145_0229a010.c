/* func_ov145_0229a010 @ 0x0229a010, 0x24 bytes, Thumb, module ov145
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov145_0229a058(const unsigned char *, const unsigned char *, int, int);

void func_ov145_0229a010(unsigned char *base)
{
    *(unsigned short *) (base + 0xb8) = (unsigned short) func_ov145_0229a058(base, base + 0x0c8c, 0x3894, 0x14);
}
