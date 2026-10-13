/* func_020a7794 @ 0x020a7794, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a7794(unsigned char *r0, unsigned char r1, unsigned char r2, unsigned char r3, unsigned int r4);

void func_020a7794(unsigned char *r0, unsigned char r1, unsigned char r2, unsigned char r3, unsigned int r4)
{
    unsigned int r5;
    unsigned int r6;

    r6 = r4 & 1;
    if (r6 != 0) {
        *r0 = r1;
    }

    r5 = r4 & 2;
    if (r5 != 0) {
        *(r0 + 1) = r2;
    }

    r5 = r4 & 4;
    if (r5 != 0) {
        *(r0 + 2) = r3;
    }

    *(unsigned int *) (r0 + 4) |= r4;
}
