/* func_02088b68 @ 0x02088b68, 0x12 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_02088b68(unsigned char *p)
{
    p[13] += 1;
    if (p[13] > 6) {
        p[13] = 6;
    }
}
