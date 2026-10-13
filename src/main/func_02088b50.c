/* func_02088b50 @ 0x02088b50, 0x12 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02088b50(unsigned char *r0, unsigned char r1);

void func_02088b50(unsigned char *r0, unsigned char r1)
{
    unsigned char r2;
    unsigned char r1b;

    r2 = r0[0xe];
    r1b = r2 + r1;
    r0[0xe] = r1b;
    r1b = r0[0xe];
    if (r1b > 0x64) {
        r1b = 0x64;
        r0[0xe] = r1b;
    }
}
