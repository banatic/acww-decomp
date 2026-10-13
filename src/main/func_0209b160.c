/* func_0209b160 @ 0x0209b160, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209b160(unsigned char *r0, int r1);

void func_0209b160(unsigned char *r0, int r1)
{
    if ((unsigned int) (r1 - 2) <= 1) {
        r0[0xd] &= ~4;
        r0[0xd] &= ~8;
    } else {
        r0[0xd] &= ~(1 << r1);
    }
}
