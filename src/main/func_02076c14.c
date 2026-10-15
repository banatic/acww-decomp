/* func_02076c14 @ 0x02076c14, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020736bc(unsigned int, unsigned char *, int);
extern int func_02095578(unsigned char, int);
extern unsigned int data_020ccf94;

void func_02076c14(int length, int sequence, unsigned char category, unsigned int player)
{
    unsigned char buffer[8];
    func_020736bc(data_020ccf94, buffer, length);
    func_02095578(buffer[0], player);
}
