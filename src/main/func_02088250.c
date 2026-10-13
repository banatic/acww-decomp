/* func_02088250 @ 0x02088250, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02088224(void);

void func_02088250(void *r0)
{
    unsigned char *base = (unsigned char *) r0;
    base[0x236] = 0;
    func_02088224();
}
