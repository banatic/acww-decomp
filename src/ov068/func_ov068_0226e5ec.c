/* func_ov068_0226e5ec @ 0x0226e5ec, 0x18 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0202eb70(void *self);
extern char data_ov068_022774e4;

void *func_ov068_0226e5ec(void *self)
{
    func_0202eb70(self);
    *(void **) self = &data_ov068_022774e4;
    return self;
}
