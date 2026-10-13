/* func_020919ac @ 0x020919ac, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02094b58(int, int, int, int, int, int);

extern unsigned char data_020e2934[];

void func_020919ac(int r0, int r1, int r2, int r3)
{
    int sp[2];
    sp[0] = r3;
    sp[1] = (unsigned int) data_020e2934;
    func_02094b58(0xe, r0, r1, r2, sp[0], sp[1]);
}
