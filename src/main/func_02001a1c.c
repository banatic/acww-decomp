/* func_02001a1c @ 0x02001a1c, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_0213fe94[];

void func_02001a1c(unsigned char value)
{
    data_0213fe94[0x14] = value;
    data_0213fe94[0x12] |= 4;
}
