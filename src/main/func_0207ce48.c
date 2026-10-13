/* func_0207ce48 @ 0x0207ce48, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0207ce48(unsigned short *r0, unsigned short *r1, int r2);

int func_0207ce48(unsigned short *r0, unsigned short *r1, int r2)
{
    int r5 = 0;
    int r4;
    int r3;
    int result;

    while (r5 < r2) {
        r4 = *r0;
        r3 = *r1;
        if (r4 != r3) {
            return 0;
        }
        r5++;
        r0 += 1;
        r1 += 1;
    }
    return 1;
}
