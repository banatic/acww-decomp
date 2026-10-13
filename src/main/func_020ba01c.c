/* func_020ba01c @ 0x020ba01c, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020ba1cc(void *);
extern void func_020ba1b0(void *);
extern char data_020e5928;

void *func_020ba01c(void *self)
{
    func_020ba1cc(self);
    *(void **) self = &data_020e5928;
    func_020ba1b0((char *) self + 0x10);
    return self;
}
