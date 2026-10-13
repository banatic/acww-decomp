/* func_020f3e5c @ 0x020f3e5c, 0x28 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void func_020f4318(void);
extern void func_020f1d84(unsigned int, unsigned int);

extern unsigned char data_021fd1bc[];

void func_020f3e5c(void)
{
    unsigned int *p;

    func_020f4318();
    p = (unsigned int *) data_021fd1bc;
    func_020f1d84((unsigned int) p, 0x8f);
}
