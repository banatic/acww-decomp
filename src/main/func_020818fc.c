/* func_020818fc @ 0x020818fc, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_020818fc(char *p)
{
    unsigned short tmp;
    tmp = *(unsigned short *) (p + 0x7c);
    tmp |= 0x2000;
    *(unsigned short *) (p + 0x7c) = tmp;
}
