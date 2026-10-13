/* func_020818c0 @ 0x020818c0, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_020818c0(unsigned short *param)
{
    unsigned short *ptr;
    unsigned short value;

    ptr = (unsigned short *) ((unsigned char *) param + 0x7c);
    value = *ptr;
    value |= 0x4000;
    *ptr = value;
}
