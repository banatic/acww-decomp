/* func_020f2640 @ 0x020f2640, 0x24 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern char data_0213ef18;
extern void func_020f3f14(void *);

void *func_020f2640(void *self)
{
    *(void **) self = &data_0213ef18;
    func_020f3f14(self);
    return self;
}
