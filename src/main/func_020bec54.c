/* func_020bec54 @ 0x020bec54, 0xc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020bec54(unsigned short *r0, int r1);

void func_020bec54(unsigned short *r0, int r1)
{
    unsigned short r3;
    int r2;

    r3 = r0[4]; // offset 8 = 4 * sizeof(unsigned short)
    r2 = 1;
    r2 = r2 << r1;
    r3 = r3 & ~r2;
    r0[4] = r3;
}
