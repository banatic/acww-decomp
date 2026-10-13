/* func_020877dc @ 0x020877dc, 0x22 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020644b4(int);

int func_020877dc(int r0, int r1, int r2)
{
    int r5 = r0;
    int r4 = r1;
    int r0_2 = r2;
    int r0_3 = func_020644b4(r0_2);
    unsigned char r1_2 = *(unsigned char *) (r5 + 0xa);
    int r0_4 = r4 + r0_3;
    int r1_3 = r1_2 * r0_4;
    int r0_5 = r1_3 >> 12;
    unsigned char r0_6 = (unsigned char) (r0_5 & 0xff);
    return r0_6;
}
