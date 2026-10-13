/* func_02081974 @ 0x02081974, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_02081974(unsigned short *r0)
{
    unsigned short r2;
    unsigned short *r1;

    r1 = (unsigned short *) ((unsigned char *) r0 + 0x7c);
    r2 = *r1;
    r2 |= 0x0800;
    r0 = (unsigned short *) ((unsigned char *) r0 + 0x7c);
    *r0 = r2;
}
