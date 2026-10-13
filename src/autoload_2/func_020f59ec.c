/* func_020f59ec @ 0x020f59ec, 0x24 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern char data_0213f090;
extern void func_020f5914(void *self);

void *func_020f59ec(void *self)
{
    *(void **) self = &data_0213f090;
    func_020f5914(self);
    return self;
}
