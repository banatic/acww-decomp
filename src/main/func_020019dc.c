/* func_020019dc @ 0x020019dc, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

// placeholder, not used

extern unsigned char data_0213fe94[];

void func_020019dc(unsigned char r0, unsigned char r1, unsigned char r2)
{
    unsigned char *base = (unsigned char *) data_0213fe94;
    unsigned char tmp;

    base[0x13] = r0;
    base[0x14] = r1;
    base[0x15] = r2;

    tmp = base[0x12];
    tmp |= 0x10;
    base[0x12] = tmp;
}
