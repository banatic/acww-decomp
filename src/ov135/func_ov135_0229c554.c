/* func_ov135_0229c554 @ 0x0229c554, 0xe bytes, Thumb, module ov135
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov135_0229c554(unsigned short *r0, unsigned short r1);

void func_ov135_0229c554(unsigned short *r0, unsigned short r1)
{
    unsigned short r2;
    r2 = *(unsigned short *) ((char *) r0 + 0x92);
    r2 &= ~r1;
    *(unsigned short *) ((char *) r0 + 0x92) = r2;
}
