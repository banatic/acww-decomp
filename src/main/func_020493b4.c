/* func_020493b4 @ 0x020493b4, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_020493b4(unsigned int *r0, unsigned char *r1, int r2, int r3)
{
    int i;
    unsigned int val;
    unsigned int *p;

    r1 = r1 + (r2 << 1) + r3;
    *r0 = r1[4];
    r0[1] = 0;
    val = 0xFFFFFFFF;
    for (i = 0; i < 0x40; i++) {
        p = r0 + (i << 1);
        p[2] = val;
        p[3] = val;
    }
}
