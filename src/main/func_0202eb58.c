/* func_0202eb58 @ 0x0202eb58, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020d9ff8;
extern void func_0201615c(void *self);

void *func_0202eb58(void *self)
{
    *(void **) self = &data_020d9ff8;
    func_0201615c(self);
    return self;
}
