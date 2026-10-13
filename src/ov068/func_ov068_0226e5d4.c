/* func_ov068_0226e5d4 @ 0x0226e5d4, 0x18 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern void func_0202eb20(void *);
extern int data_ov068_022774e4;

void *func_ov068_0226e5d4(void *self)
{
    *(void **) self = (void *) &data_ov068_022774e4;
    func_0202eb20(self);
    return self;
}
