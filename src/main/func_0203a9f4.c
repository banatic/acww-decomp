/* func_0203a9f4 @ 0x0203a9f4, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020ee62c(void *);
extern void func_020edf54(void *);

extern unsigned char data_020da13c[];
extern unsigned char data_020da87c[];
extern unsigned char data_020e58cc[];

void *func_0203a9f4(volatile unsigned int *self)
{
    *self = (unsigned int) data_020da87c;
    *self = (unsigned int) data_020e58cc;
    *self = (unsigned int) data_020da13c;
    func_020ee62c((void *) self);
    func_020edf54((void *) self);
    return (void *) self;
}
