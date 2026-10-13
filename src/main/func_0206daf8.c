/* func_0206daf8 @ 0x0206daf8, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a8cac(void *self);
extern void func_020a8c1c(void *self);
extern unsigned int data_020df240;

void *func_0206daf8(void *self)
{
    func_020a8cac(self);
    *(unsigned int *) self = (unsigned int) &data_020df240;
    func_020a8c1c(self);
    return self;
}
