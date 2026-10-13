/* func_020b5abc @ 0x020b5abc, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020ee62c(void *);

extern unsigned char data_020da13c[];
extern unsigned char data_020e3c94[];
extern unsigned char data_020e5408[];

void *func_020b5abc(void *arg)
{
    volatile unsigned int *p = (volatile unsigned int *) arg;
    *p = (unsigned int) data_020e5408;
    *p = (unsigned int) data_020e3c94;
    *p = (unsigned int) data_020da13c;
    func_020ee62c(arg);
    return arg;
}
