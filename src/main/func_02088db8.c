/* func_02088db8 @ 0x02088db8, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02088dc8(unsigned int, unsigned int);

int func_02088db8(unsigned int *ptr)
{
    unsigned int val = *ptr;
    return func_02088dc8((val << 16) >> 30, val >> 30);
}
