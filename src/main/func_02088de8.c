/* func_02088de8 @ 0x02088de8, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020d0a04[];

int func_02088de8(int a, int b)
{
    return data_020d0a04[b + (a << 2)];
}
