/* func_020b402c @ 0x020b402c, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020e5200;
extern void func_020a8188(void *);

void *func_020b402c(void *self)
{
    *(void **) self = &data_020e5200;
    func_020a8188(self);
    return self;
}
