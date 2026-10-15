/* func_020f2614 @ 0x020f2614, 0x2c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern char data_0213ef18;
extern void *func_020f3f14(void *);
extern void func_020edb3c(void *);

void *func_020f2614(void *self)
{
    *(void **) self = &data_0213ef18;
    func_020f3f14(self);
    func_020edb3c(self);
    return self;
}
