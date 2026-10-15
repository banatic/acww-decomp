/* func_ov068_022752ac @ 0x022752ac, 0x18 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0202de4c(void *p);

extern unsigned char data_ov068_022780b0[];

void *func_ov068_022752ac(void *self)
{
    *(void **) self = (void *) data_ov068_022780b0;
    func_0202de4c(self);
    return self;
}
