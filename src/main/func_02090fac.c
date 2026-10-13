/* func_02090fac @ 0x02090fac, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209099c(void *p);
extern void func_02090834(void *p);
extern void func_020fa270(unsigned int value);

int func_02090fac(unsigned char *param)
{
    func_0209099c(param + 0x58);
    func_02090834(param + 0x35c);
    func_020fa270(*(unsigned int *) (param + 0x50));
    return 1;
}
