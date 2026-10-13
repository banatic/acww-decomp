/* func_02004260 @ 0x02004260, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020f1c00(int, int);

extern unsigned char data_021fd1bc[];

int func_02004260(int arg)
{
    return func_020f1c00((unsigned int) data_021fd1bc, arg);
}
