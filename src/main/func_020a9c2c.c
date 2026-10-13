/* func_020a9c2c @ 0x020a9c2c, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020ee62c(void *p);

extern unsigned char data_020da13c[];
extern unsigned char data_020e3e8c[];

void *func_020a9c2c(void *p)
{
    volatile unsigned int *v = p;
    *v = (unsigned int) data_020e3e8c;
    *v = (unsigned int) data_020da13c;
    func_020ee62c(p);
    return p;
}
