/* func_02087830 @ 0x02087830, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_02087830(void *r0)
{
    unsigned char *p = (unsigned char *) r0;
    p[0x18] = 0xff;
    *(unsigned short *) (p + 8) = 0;
    p[0] = 1;
    p[1] = 1;
    p[2] = 0;
    p[3] = 0;
    p[4] = 1;
    p[5] = 1;
    p[6] = 0;
    p[7] = 0;
}
