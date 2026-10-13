/* func_020818ac @ 0x020818ac, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_020818ac(unsigned short *param)
{
    unsigned short value;
    unsigned short *ptr;

    ptr = (unsigned short *) ((unsigned char *) param + 0x7c);
    value = *ptr;
    value &= 0xffffbfff;
    *ptr = value;
}
