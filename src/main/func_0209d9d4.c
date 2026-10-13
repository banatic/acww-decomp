/* func_0209d9d4 @ 0x0209d9d4, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_020e360c;
extern char data_020da13c;
extern void func_020ee62c(void *);

void *func_0209d9d4(void *self)
{
    volatile unsigned int *p;
    p = (volatile unsigned int *) self;
    *p = (unsigned int) &data_020e360c;
    *p = (unsigned int) &data_020da13c;
    func_020ee62c(self);
    return self;
}
