/* func_ov053_02260bdc @ 0x02260bdc, 0x20 bytes, Thumb, module ov053
 * mwccarm 1.2/base -O4,s
 */

extern void func_0202eb20(void *p);
extern void func_020edb3c(void *p);

struct UnkStruct_02260bdc {
    void *vtable;
};

extern unsigned char data_ov053_02261b08[];

struct UnkStruct_02260bdc *func_ov053_02260bdc(struct UnkStruct_02260bdc *self)
{
    self->vtable = (void *) data_ov053_02261b08;
    func_0202eb20(self);
    func_020edb3c(self);
    return self;
}
