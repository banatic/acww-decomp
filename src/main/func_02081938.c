/* func_02081938 @ 0x02081938, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_02081938(unsigned short *arg0)
{
    unsigned short *ptr;
    unsigned short val;

    ptr = (unsigned short *) ((unsigned char *) arg0 + 0x7c);
    val = *ptr;
    val |= 0x1000;
    *ptr = val;
}
