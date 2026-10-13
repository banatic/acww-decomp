/* func_02088bac @ 0x02088bac, 0x12 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02088bac(void *r0, int r1);

void func_02088bac(void *r0, int r1)
{
    unsigned char r2;
    unsigned char r1b;

    r2 = *(unsigned char *) ((char *) r0 + 0xa);
    r1b = (unsigned char) (r2 + r1);
    *(unsigned char *) ((char *) r0 + 0xa) = r1b;
    r1b = *(unsigned char *) ((char *) r0 + 0xa);
    if (r1b > 0x10) {
        *(unsigned char *) ((char *) r0 + 0xa) = 0x10;
    }
}
