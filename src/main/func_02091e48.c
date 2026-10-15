/* func_02091e48 @ 0x02091e48, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02094b58(int, int, int, int, int, int);

extern unsigned char data_020e281c[];

void func_02091e48(int a1, int a2, int a3, int a4)
{
    int sp[2];
    sp[0] = a4;
    sp[1] = (unsigned int) data_020e281c;
    func_02094b58(7, a1, a2, a3, sp[0], sp[1]);
}
