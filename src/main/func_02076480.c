/* func_02076480 @ 0x02076480, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int data_020ccf94;
extern void func_020736bc(unsigned int, unsigned char *, int);
extern int func_02074d60(unsigned char);

int func_02076480(void)
{
    unsigned char byte_var;
    func_020736bc(data_020ccf94, &byte_var, 1);
    return func_02074d60(byte_var);
}
