/* func_02001ba4 @ 0x02001ba4, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_0213fe74[];
void func_02001ba4(unsigned char mask)
{
    data_0213fe74[0x18] &= ~mask;
}
