/* func_020a7964 @ 0x020a7964, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a941c(void *self);
extern void func_020edb3c(void *self);
extern unsigned int data_020e3e68;

void *func_020a7964(void *self)
{
    *(unsigned int *) self = (unsigned int) &data_020e3e68;
    func_020a941c(self);
    func_020edb3c(self);
    return self;
}
