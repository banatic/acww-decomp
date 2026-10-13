/* func_ov071_02278fa0 @ 0x02278fa0, 0x18 bytes, Thumb, module ov071
 * mwccarm 1.2/base -O4,s
 */

extern void func_0202eb20(void *self);
extern unsigned char data_ov071_0227a1e8[];

void *func_ov071_02278fa0(void *self)
{
    ((void **) self)[0] = data_ov071_0227a1e8;
    func_0202eb20(self);
    return self;
}
