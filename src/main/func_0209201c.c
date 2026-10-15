/* func_0209201c @ 0x0209201c, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02094b58(int, int, int, int, int, int);

extern unsigned char data_020e27d4[];

void func_0209201c(int r0, int r1, int r2, int r3)
{
    int sp[2];
    sp[0] = r3;
    sp[1] = (unsigned int) data_020e27d4;
    func_02094b58(0x95, r0, r1, r2, sp[0], sp[1]);
}
