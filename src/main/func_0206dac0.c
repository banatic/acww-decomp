/* func_0206dac0 @ 0x0206dac0, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020a8c38(void *self);
extern void func_020edb3c(void *self);

extern unsigned char data_020df240[];

void *func_0206dac0(void *self)
{
    void *vtable = (void *) data_020df240;
    *((void **) self) = vtable;
    func_020a8c38(self);
    func_020edb3c(self);
    return self;
}
