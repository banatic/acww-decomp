/* func_02001e14 @ 0x02001e14, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_0213fe74[];
extern unsigned short data_0213fe34[];

void func_02001e14(unsigned short p0, unsigned short p1)
{
    data_0213fe74[0x11] |= 0x10;
    data_0213fe34[4] = p0;
    data_0213fe34[5] = p1;
}
