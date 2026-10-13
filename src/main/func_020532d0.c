/* func_020532d0 @ 0x020532d0, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_020532d0(unsigned char *p)
{
    unsigned int i;
    for (i = 0; i < 4; i++) {
        p[i] &= ~0xF;
        p[i] &= ~0xF0;
    }
    p[4] = 0;
    for (i = 0; i < 2; i++) {
        (p + i)[5] = 0;
    }
}
