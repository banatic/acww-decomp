/* func_020c1b4c @ 0x020c1b4c, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0202eb20(void *self);
extern void func_020edb3c(void *self);

extern unsigned char data_020e7bd0[];

void *func_020c1b4c(void *self)
{
    *((unsigned int *) self) = (unsigned int) data_020e7bd0;
    func_0202eb20(self);
    func_020edb3c(self);
    return self;
}
