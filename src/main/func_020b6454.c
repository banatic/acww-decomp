/* func_020b6454 @ 0x020b6454, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char func_020b6454(unsigned char *r0, unsigned char r1);

unsigned char func_020b6454(unsigned char *r0, unsigned char r1)
{
    if (r0[0] == 0x3f) {
        r0[0] = r1;
        r0[1] = 1;
        return 1;
    }
    return 0;
}
