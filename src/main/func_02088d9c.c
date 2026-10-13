/* func_02088d9c @ 0x02088d9c, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_02088d9c(unsigned int *p)
{
    unsigned int word = *p;
    int field = (int) ((word << 7) >> 23);
    if (field < 0x100) {
        return field;
    } else {
        return field - 0x200;
    }
}
