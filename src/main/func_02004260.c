/* func_02004260 @ 0x02004260, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020f1c00(int, int);

extern unsigned char data_021fd1bc[];

void func_02004260(int arg)
{
    func_020f1c00((unsigned int) data_021fd1bc, arg);
}
