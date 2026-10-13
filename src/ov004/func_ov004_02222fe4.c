/* func_ov004_02222fe4 @ 0x02222fe4, 0x38 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_0201ad18(int, int, int, int, int, int, int, int);

extern unsigned char data_020c814c[];

extern unsigned char data_021fbee8[];

int func_ov004_02222fe4(int a)
{
    func_0201ad18(a + 0x3b0, 0, 0, 0, (unsigned int) data_021fbee8, 4, *((int *) data_020c814c), 1);
    return 1;
}
