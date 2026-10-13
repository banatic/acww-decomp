/* func_02078224 @ 0x02078224, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02078224(unsigned char *param);

void func_02078224(unsigned char *param)
{
    unsigned char temp;
    unsigned char *ptr;

    ptr = param + 0xc3;
    temp = *ptr;
    temp |= 0x10;
    *ptr = temp;
}
