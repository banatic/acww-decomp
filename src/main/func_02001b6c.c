/* func_02001b6c @ 0x02001b6c, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_0213fe74[];

void func_02001b6c(unsigned char r0)
{
    data_0213fe74[0x19] &= ~r0;
}
