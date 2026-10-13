/* func_02092f20 @ 0x02092f20, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02094cf8(int, int, int, int, int, int);

extern unsigned char data_020e27a4[];

void func_02092f20(int r0, int r1, int r2, int r3)
{
    int sp[2];
    sp[0] = r3;
    sp[1] = (unsigned int) data_020e27a4;
    func_02094cf8(0x63, r0, r1, r2, sp[0], sp[1]);
}
