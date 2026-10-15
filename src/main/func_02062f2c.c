/* func_02062f2c @ 0x02062f2c, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02062f2c {
    int *unk_00;
};

extern int data_020de62c;
extern void *func_020a8c38(struct UnkStruct_02062f2c *self);
extern void func_020edb3c(struct UnkStruct_02062f2c *self);

struct UnkStruct_02062f2c *func_02062f2c(struct UnkStruct_02062f2c *self)
{
    self->unk_00 = &data_020de62c;
    func_020a8c38(self);
    func_020edb3c(self);
    return self;
}
