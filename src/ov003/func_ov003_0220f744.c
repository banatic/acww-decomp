/* func_ov003_0220f744 @ 0x0220f744, 0x24 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov003_0220f744(unsigned char *r0, unsigned short r1, unsigned int r2, unsigned int r3, unsigned char r4,
                                unsigned char r5);

void func_ov003_0220f744(unsigned char *r0, unsigned short r1, unsigned int r2, unsigned int r3, unsigned char r4,
                         unsigned char r5)
{
    r0[0] = 0;
    *(unsigned short *) (r0 + 2) = r1;
    *(unsigned int *) (r0 + 4) = r2;
    *(unsigned int *) (r0 + 8) = r3;
    r0[12] = r4;
    r0[13] = r5;
}
