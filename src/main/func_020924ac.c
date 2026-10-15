/* func_020924ac @ 0x020924ac, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02094b58(int, int, int, int, int, int);

extern unsigned char data_020e2874[];

void func_020924ac(int r0, int r1, int r2, int r3)
{
    int sp[2];
    sp[0] = r3;
    sp[1] = (unsigned int) data_020e2874;
    func_02094b58(0x4f, r0, r1, r2, sp[0], sp[1]);
}
