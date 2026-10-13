/* func_020785dc @ 0x020785dc, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020778b0(void *p, unsigned short value);

void func_020785dc(unsigned char *out, unsigned int flags, unsigned char b3, unsigned short *data, unsigned int lowbits,
                   unsigned char bit3)
{
    out[2] = (lowbits & 7) | (((flags << 4) & 0xf0) | ((bit3 & 1) << 3));
    out[3] = b3;
    func_020778b0(out, *data);
}
