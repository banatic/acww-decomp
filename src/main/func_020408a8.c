/* func_020408a8 @ 0x020408a8, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020408a8(unsigned char *r0);

void func_020408a8(unsigned char *r0)
{
    unsigned char r1;
    r1 = r0[2];
    if (r1 == 0x45) {
        return;
    }
    r1 = 0xff;
    r0[5] = r1;
    r1 = 2;
    r0[3] = r1;
}
