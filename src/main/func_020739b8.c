/* func_020739b8 @ 0x020739b8, 0x16 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_020739b8(unsigned char *p)
{
    unsigned int *a1 = (unsigned int *) (p + 0x4c);
    unsigned int *a2 = (unsigned int *) (p + 0x58);
    int i = 2;
    do {
        *a1++ = 0;
        *a2++ = 0;
    } while (--i >= 0);
}
