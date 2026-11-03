/* message_walker: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020a7964 @ 0x020a7964, 0x20 bytes, Thumb
 * func_020a794c @ 0x020a794c, 0x18 bytes, Thumb
 */

extern void *func_020a941c(void *self);
extern void func_020edb3c(void *self);
extern unsigned int data_020e3e68;

void *func_020a7964(void *self)
{
    *(unsigned int *) self = (unsigned int) &data_020e3e68;
    func_020a941c(self);
    func_020edb3c(self);
    return self;
}

void *func_020a794c(void *arg)
{
    *(int **) arg = ((int *) &data_020e3e68);
    func_020a941c(arg);
    return arg;
}
