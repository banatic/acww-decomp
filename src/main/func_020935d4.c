/* func_020935d4 @ 0x020935d4, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02094b58(int, int, int, int, int, int);

extern unsigned char data_020e2a64[];

void func_020935d4(int a, int b, int c, int d)
{
    int sp[2];
    sp[0] = d;
    sp[1] = (unsigned int) data_020e2a64;
    func_02094b58(0x5a, a, b, c, sp[0], sp[1]);
}
