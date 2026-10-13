/* func_02088a60 @ 0x02088a60, 0x12 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02088a60(void *r0);

void func_02088a60(void *r0)
{
    unsigned char *p = (unsigned char *) r0;
    unsigned char v;

    v = p[0xf];
    v++;
    p[0xf] = v;

    v = p[0xf];
    if (v < 0xff) {
        // nothing
    } else {
        p[0xf] = 0xff;
    }
}
