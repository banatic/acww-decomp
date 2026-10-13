/* func_020b5cac @ 0x020b5cac, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020ee62c(void *);

extern unsigned char data_020da13c[];
extern unsigned char data_020e3c94[];
extern unsigned char data_020e5460[];

void *func_020b5cac(void *self)
{
    *(volatile unsigned int *) self = (unsigned int) data_020e5460;
    *(volatile unsigned int *) self = (unsigned int) data_020e3c94;
    *(volatile unsigned int *) self = (unsigned int) data_020da13c;
    func_020ee62c(self);
    return self;
}
