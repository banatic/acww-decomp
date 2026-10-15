/* func_ov073_02278e7c @ 0x02278e7c, 0x20 bytes, Thumb, module ov073
 * mwccarm 1.2/base -O4,s
 */

extern char data_ov073_02279a70[];
extern void *func_0202eb20(void *self);
extern void func_020edb3c(void *self);

void *func_ov073_02278e7c(void *self)
{
    *(void **) self = data_ov073_02279a70;
    func_0202eb20(self);
    func_020edb3c(self);
    return self;
}
