/* func_02042c28 @ 0x02042c28, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_02042c28(unsigned char *p)
{
    int i = 0;
    unsigned char val = i;
    for (; i < 5; i++) {
        p[0] = val;
        *(unsigned short *) (p + 2) = 0xffff;
        p += 4;
    }
}
