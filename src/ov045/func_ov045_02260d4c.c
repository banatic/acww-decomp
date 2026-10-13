/* func_ov045_02260d4c @ 0x02260d4c, 0x18 bytes, Thumb, module ov045
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02260d4c {
    void *vtable;
};
extern void func_020161ac(void *self);
extern char data_ov045_02261460;
struct UnkStruct_02260d4c *func_ov045_02260d4c(struct UnkStruct_02260d4c *self)
{
    func_020161ac(self);
    self->vtable = &data_ov045_02261460;
    return self;
}
