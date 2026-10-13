/* func_020b941c @ 0x020b941c, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020ee62c(void *);

extern unsigned char data_020da13c[];
extern unsigned char data_020e58cc[];

void *func_020b941c(void *self)
{
    volatile int *p = (volatile int *) self;
    *p = (unsigned int) data_020e58cc;
    *p = (unsigned int) data_020da13c;
    func_020ee62c(self);
    return self;
}
