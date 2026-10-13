/* func_020a8cac @ 0x020a8cac, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a9b50(void *arg);

extern unsigned char data_020da6dc[];
extern unsigned char data_020e3d94[];

void *func_020a8cac(void *arg)
{
    volatile unsigned int *p = (volatile unsigned int *) arg;
    p[0] = (unsigned int) data_020da6dc;
    p[0] = (unsigned int) data_020e3d94;
    p[1] = 0;
    func_020a9b50((char *) arg + 8);
    return arg;
}
