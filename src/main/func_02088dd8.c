/* func_02088dd8 @ 0x02088dd8, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_02088de8(unsigned int a, unsigned int b);

unsigned int func_02088dd8(unsigned int *p)
{
    unsigned int x = *p;
    return func_02088de8((x << 16) >> 30, x >> 30);
}
