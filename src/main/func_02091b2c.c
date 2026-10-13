/* func_02091b2c @ 0x02091b2c, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02094b58(int, int, int, int, int, int);

extern unsigned char data_020e2984[];

void func_02091b2c(int r0, int r1, int r2, int r3)
{
    int sp[2];
    sp[0] = r3;
    sp[1] = (unsigned int) data_020e2984;
    func_02094b58(0xd, r0, r1, r2, sp[0], sp[1]);
}
