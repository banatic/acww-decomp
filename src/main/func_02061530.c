/* func_02061530 @ 0x02061530, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_0209dbbc(void);
extern void func_020e930c(unsigned int *p, unsigned long value);

extern unsigned char data_021cb5a0[];

void func_02061530(void)
{
    func_020e930c((unsigned int *) data_021cb5a0, func_0209dbbc());
}
