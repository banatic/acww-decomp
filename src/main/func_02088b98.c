/* func_02088b98 @ 0x02088b98, 0xe bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02088b98(unsigned char *r0, int r1);

void func_02088b98(unsigned char *r0, int r1)
{
    unsigned char r2;
    int r1_temp;

    r2 = r0[0xb];
    r1_temp = r2 + r1;
    if (r1_temp > 0xff) {
        r1_temp = 0xff;
    }
    r0[0xb] = (unsigned char) r1_temp;
}
