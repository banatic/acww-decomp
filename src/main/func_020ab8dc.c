/* func_020ab8dc @ 0x020ab8dc, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a8cac(void *);
extern void func_020a8c1c(void *);
extern char data_020e3f9c;

void *func_020ab8dc(void *self)
{
    func_020a8cac(self);
    *(void **) self = &data_020e3f9c;
    func_020a8c1c(self);
    return self;
}
