/* func_020c17f8 @ 0x020c17f8, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021fbbd8;
extern void func_020c176c(char *ptr);

void func_020c17f8(char *ptr)
{
    data_021fbbd8 = 0;
    ptr[7] = 0;
    ptr[0] = 1;
    ptr[1] = 1;
    ptr[2] = 0;
    ptr[3] = 0;
    ptr[0] = 0;
    func_020c176c(ptr);
}
