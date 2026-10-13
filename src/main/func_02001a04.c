/* func_02001a04 @ 0x02001a04, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_0213fe94[];

void func_02001a04(unsigned char a, unsigned char b, unsigned char c)
{
    data_0213fe94[0x13] = a;
    data_0213fe94[0x14] = b;
    data_0213fe94[0x15] = c;
    data_0213fe94[0x12] |= 8;
}
