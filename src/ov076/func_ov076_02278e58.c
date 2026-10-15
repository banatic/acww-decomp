/* func_ov076_02278e58 @ 0x02278e58, 0x20 bytes, Thumb, module ov076
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0202eb20(void *self);
extern void func_020edb3c(void *self);
extern char data_ov076_02279744;

void *func_ov076_02278e58(void *self)
{
    *(void **) self = &data_ov076_02279744;
    func_0202eb20(self);
    func_020edb3c(self);
    return self;
}
