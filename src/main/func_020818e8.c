/* func_020818e8 @ 0x020818e8, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_020818e8(unsigned short *arg0)
{
    unsigned short *ptr;
    unsigned short val;
    unsigned int mask;

    ptr = (unsigned short *) ((unsigned char *) arg0 + 0x7c);
    val = *ptr;
    mask = 0xffffdfff;
    val = (unsigned short) (val & mask);
    *((unsigned short *) ((unsigned char *) arg0 + 0x7c)) = val;
}
