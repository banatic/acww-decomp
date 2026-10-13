/* func_02001a30 @ 0x02001a30, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_0213fe94[];

unsigned char func_02001a30(unsigned char mask)
{
    data_0213fe94[0x13] &= ~mask;
    data_0213fe94[0x12] |= 4;
    return 4;
}
