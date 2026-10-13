/* func_02088bc4 @ 0x02088bc4, 0xe bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_02088bc4(volatile unsigned char *field, unsigned char value)
{
    field[9] = value;
    if (field[9] > 0xf) {
        field[9] = 0xf;
    }
}
