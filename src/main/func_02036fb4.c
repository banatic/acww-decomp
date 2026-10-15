/* func_02036fb4 @ 0x02036fb4, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020356c4(unsigned char *, unsigned char *, int, int);

void func_02036fb4(unsigned char *r0, unsigned char *r1, unsigned short r2, int argument3)
{
    unsigned char *r5 = r0;
    unsigned short r4 = r2;

    func_020356c4(r1, (unsigned char *) r4, 0x7f, (int) argument3);
    *(unsigned short *) (r5 + 8) = r4;
}
