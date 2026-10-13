/* func_02001b34 @ 0x02001b34, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_0213fe74[];

void func_02001b34(unsigned char mask)
{
    data_0213fe74[0x14] &= ~mask;
}
