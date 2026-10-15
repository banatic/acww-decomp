/* func_ov074_02278fc4 @ 0x02278fc4, 0x20 bytes, Thumb, module ov074
 * mwccarm 1.2/base -O4,s
 */

extern char data_ov074_02279bd8[];
extern void *func_0202eb20(void *self);
extern void func_020edb3c(void *self);

void *func_ov074_02278fc4(void *self)
{
    struct UnkStruct_02278fc4 {
        void *field;
    } *obj = self;
    obj->field = data_ov074_02279bd8;
    func_0202eb20(self);
    func_020edb3c(self);
    return self;
}
