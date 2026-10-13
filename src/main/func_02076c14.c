/* func_02076c14 @ 0x02076c14, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020736bc(unsigned int, unsigned char *, int);
extern int func_02095578(unsigned char, int);
extern unsigned int data_020ccf94;

int func_02076c14(int arg0, int arg1, int arg2, int arg3)
{
    unsigned char buffer[8];
    func_020736bc(data_020ccf94, buffer, arg0);
    return func_02095578(buffer[0], arg3);
}
