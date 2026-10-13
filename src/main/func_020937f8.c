/* func_020937f8 @ 0x020937f8, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02094b58(int, int, int, int, int, int);

extern unsigned char data_020e27e4[];

void func_020937f8(int r0, int r1, int r2, int r3)
{
    int r6 = r0;
    int r5 = r1;
    int r4 = r2;
    int sp0 = r3;
    int sp4 = (unsigned int) data_020e27e4;

    func_02094b58(0x73, r6, r5, r4, sp0, sp4);
}
