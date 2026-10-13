/* func_020372d4 @ 0x020372d4, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020edb3c(void *self);

extern unsigned char data_020da2c4[];

void *func_020372d4(void *self)
{
    *(unsigned int *) self = (unsigned int) data_020da2c4;
    func_020edb3c(self);
    return self;
}
