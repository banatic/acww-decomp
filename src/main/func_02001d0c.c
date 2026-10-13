/* func_02001d0c @ 0x02001d0c, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_0213fe74[];

void func_02001d0c(unsigned char mask)
{
    data_0213fe74[0x1a] &= ~mask;
}
