/* func_ov080_02278e48 @ 0x02278e48, 0x18 bytes, Thumb, module ov080
 * mwccarm 1.2/base -O4,s
 */

extern void func_0202eb70(void *self);
extern char data_ov080_0227925c[];

struct UnkStruct_02278e48 {
    void *vtable;
};

struct UnkStruct_02278e48 *func_ov080_02278e48(struct UnkStruct_02278e48 *self)
{
    func_0202eb70(self);
    self->vtable = data_ov080_0227925c;
    return self;
}
