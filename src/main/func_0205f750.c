/* func_0205f750 @ 0x0205f750, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0205f77c(int addr);
extern void func_020e9b9c(int arg);

extern unsigned char data_021cacd0[];

void func_0205f750(char *dst, char val)
{
    func_020e9b9c(func_0205f77c((unsigned int) data_021cacd0));
    *dst = val;
}
