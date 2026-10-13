/* func_0203ed58 @ 0x0203ed58, 0xe bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_0203ed58(unsigned char *ptr, unsigned short mask)
{
    *(unsigned short *) (ptr + 0xE8) &= ~mask;
}
