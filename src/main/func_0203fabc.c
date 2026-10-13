/* func_0203fabc @ 0x0203fabc, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020ee62c(void *);
extern void func_020edf54(void *);

extern unsigned char data_020da13c[];
extern unsigned char data_020dabc0[];

void *func_0203fabc(void *self)
{
    *(volatile unsigned int *) self = (unsigned int) data_020dabc0;
    *(volatile unsigned int *) self = (unsigned int) data_020da13c;
    func_020ee62c(self);
    func_020edf54(self);
    return self;
}
