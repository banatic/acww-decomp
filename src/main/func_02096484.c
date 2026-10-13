/* func_02096484 @ 0x02096484, 0x16 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020778b0(void);

void func_02096484(unsigned char *r0, int r1, unsigned char r2)
{
    unsigned char *r5 = r0;
    unsigned char r4 = r2;

    func_020778b0();
    r5[2] = r4;
}
