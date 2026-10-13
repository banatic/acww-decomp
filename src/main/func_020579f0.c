/* func_020579f0 @ 0x020579f0, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void *func_020579f0(unsigned char *b, int k)
{
    unsigned char *table = b + 0x3c;
    unsigned short off = *(unsigned short *) (b + 0x42);
    unsigned char *base = b + *(unsigned int *) (b + 0x14);
    unsigned short stride = *(unsigned short *) (table + off);
    unsigned char *entry = table + off + stride * k;
    unsigned int w = *(unsigned int *) (entry + 4);

    return base + ((w & 0xffff) << 3);
}
