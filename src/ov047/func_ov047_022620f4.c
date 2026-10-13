/* func_ov047_022620f4 @ 0x022620f4, 0x38 bytes, Thumb, module ov047
 * mwccarm 1.2/base -O4,s
 */

extern void func_0201ad18(int, int, int, int, int, int, int, int);

extern unsigned char data_020c814c[];

extern unsigned char data_021fbee8[];

int func_ov047_022620f4(int a)
{
    func_0201ad18(a + 0x3b0, 0, 0, 0, (unsigned int) data_021fbee8, 4, *((int *) data_020c814c), 1);
    return 1;
}
