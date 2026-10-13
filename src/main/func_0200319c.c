/* func_0200319c @ 0x0200319c, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#pragma arm
extern void func_020e8ce0(void *a, void *b);
extern void func_020ee62c(void *a);
extern void func_020edf54(void *a);
#pragma thumb on

extern unsigned char data_0213ff78[];

extern unsigned char data_020d7244[];
extern unsigned char data_020da13c[];

void *func_0200319c(void *self)
{
    *(unsigned int *) self = (unsigned int) data_020d7244;
    func_020e8ce0((void *) data_0213ff78, (void *) ((char *) self + 0x50));
    *(unsigned int *) self = (unsigned int) data_020da13c;
    func_020ee62c(self);
    func_020edf54(self);
    return self;
}
