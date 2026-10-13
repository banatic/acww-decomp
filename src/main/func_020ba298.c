/* func_020ba298 @ 0x020ba298, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020ee62c(void *);

extern unsigned char data_020da13c[];
extern unsigned char data_020e69a4[];

void *func_020ba298(void *arg)
{
    volatile unsigned int *ptr;
    ptr = (volatile unsigned int *) arg;
    *ptr = (unsigned int) data_020e69a4;
    *ptr = (unsigned int) data_020da13c;
    func_020ee62c(arg);
    return arg;
}
