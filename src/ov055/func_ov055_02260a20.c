/* func_ov055_02260a20 @ 0x02260a20, 0x20 bytes, Thumb, module ov055
 * mwccarm 1.2/base -O4,s
 */

extern void func_0202eb20(void *self);
extern void func_020edb3c(void *self);

extern unsigned char data_ov055_02260f44[];

void *func_ov055_02260a20(void *self)
{
    *(void **) self = (void *) data_ov055_02260f44;
    func_0202eb20(self);
    func_020edb3c(self);
    return self;
}
