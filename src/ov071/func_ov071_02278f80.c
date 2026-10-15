/* func_ov071_02278f80 @ 0x02278f80, 0x20 bytes, Thumb, module ov071
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0202eb20(void *self);
extern void func_020edb3c(void *self);

extern unsigned char data_ov071_0227a1e8[];

void *func_ov071_02278f80(void *self)
{
    *(void **) self = (void *) data_ov071_0227a1e8;
    func_0202eb20(self);
    func_020edb3c(self);
    return self;
}
