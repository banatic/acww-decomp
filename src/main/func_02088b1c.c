/* func_02088b1c @ 0x02088b1c, 0x12 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_02088b1c(unsigned char *p, unsigned int v)
{
    p[0x10] = (p[0x10] & ~2) | ((v & 1) << 1);
}
