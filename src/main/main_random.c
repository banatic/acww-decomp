/* main_random: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0206154c @ 0x0206154c, 0x2 bytes, Thumb
 * func_02061530 @ 0x02061530, 0x1c bytes, Thumb
 */

extern unsigned int func_0209dbbc(void);
extern void func_020e930c(unsigned int *p, unsigned long value);
extern unsigned char data_021cb5a0[];

void func_0206154c(void *object) {}

void func_02061530(void)
{
    func_020e930c((unsigned int *) data_021cb5a0, func_0209dbbc());
}
