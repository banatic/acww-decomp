/* func_020716b4 @ 0x020716b4, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_02072a48(unsigned int a, unsigned int b);

extern unsigned char data_021ed278[];

int func_020716b4(int selector)
{
    return (int) func_02072a48((unsigned int) data_021ed278, (unsigned int) selector);
}
