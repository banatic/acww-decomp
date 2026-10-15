/* func_02076480 @ 0x02076480, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int data_020ccf94;
extern void func_020736bc(unsigned int, unsigned char *, int);
extern void func_02074d60(unsigned char);

void func_02076480(int length, int sequence, unsigned char category, unsigned int player)
{
    unsigned char byte_var;
    func_020736bc(data_020ccf94, &byte_var, 1);
    func_02074d60(byte_var);
}
