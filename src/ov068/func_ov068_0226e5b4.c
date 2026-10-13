/* func_ov068_0226e5b4 @ 0x0226e5b4, 0x20 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern void func_0202eb20(void *self, void *arg);
extern void func_020edb3c(void *self);

extern unsigned char data_ov068_022774e4[];

void *func_ov068_0226e5b4(void *self)
{
    *(void **) self = (void *) data_ov068_022774e4;
    func_0202eb20(self, (void *) data_ov068_022774e4);
    func_020edb3c(self);
    return self;
}
