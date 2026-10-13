/* func_02097c14 @ 0x02097c14, 0xe bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_02097c14(unsigned char *ptr, unsigned int val)
{
    *(unsigned short *) (ptr + 0x50) |= val;
}
