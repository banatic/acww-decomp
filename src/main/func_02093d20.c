/* func_02093d20 @ 0x02093d20, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02094b58(int, int, int, int, int, int);

extern unsigned char data_020e29ac[];

void func_02093d20(int r0, int r1, int r2, int r3)
{
    int sp[2];
    sp[0] = r3;
    sp[1] = (unsigned int) data_020e29ac;
    func_02094b58(0x3c, r0, r1, r2, sp[0], sp[1]);
}
