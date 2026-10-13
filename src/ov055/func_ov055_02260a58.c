/* func_ov055_02260a58 @ 0x02260a58, 0x18 bytes, Thumb, module ov055
 * mwccarm 1.2/base -O4,s
 */

extern void func_0202eb70(void *obj);
extern char data_ov055_02260f44;

struct UnkStruct_02260a58 {
    void *vtable;
};

struct UnkStruct_02260a58 *func_ov055_02260a58(struct UnkStruct_02260a58 *self)
{
    func_0202eb70(self);
    self->vtable = &data_ov055_02260f44;
    return self;
}
