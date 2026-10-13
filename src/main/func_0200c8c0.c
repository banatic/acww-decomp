/* func_0200c8c0 @ 0x0200c8c0, 0x16 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020778b0(void);

void func_0200c8c0(unsigned char *r0, int r1, unsigned char r2, unsigned char r3)
{
    unsigned char *r5 = r0;
    unsigned char r4 = r2;
    unsigned char r6 = r3;

    func_020778b0();
    r5[2] = r4;
    r5[3] = r6;
}
