/* func_02096a48 @ 0x02096a48, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020ee62c(void *self);
extern void func_020edf54(void *self);

extern unsigned char data_020da13c[];
extern unsigned char data_020e2f90[];

void *func_02096a48(void *self)
{
    *(volatile unsigned int *) self = (unsigned int) data_020e2f90;
    *(volatile unsigned int *) self = (unsigned int) data_020da13c;
    func_020ee62c(self);
    func_020edf54(self);
    return self;
}
