/* func_020b00c8 @ 0x020b00c8, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020b00c8(unsigned short *r0, unsigned char *r1, unsigned int r2);

void func_020b00c8(unsigned short *r0, unsigned char *r1, unsigned int r2)
{
    unsigned int r5;
    unsigned int r3;
    unsigned int r4;
    unsigned int r0_temp;

    r5 = 0;
    r4 = 0x0000fff1;
    while (r5 < r2) {
        r0[r5] = (unsigned short) r4;
        r5++;
    }
    r3 = (r2 >> 3) + 1;
    r2 = 0;
    r0_temp = r2;
    while (r2 < r3) {
        r1[r2] = (unsigned char) r0_temp;
        r2++;
    }
}
