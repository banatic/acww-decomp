/* func_ov056_0226046c @ 0x0226046c, 0x28 bytes, Thumb, module ov056
 * mwccarm 1.2/base -O4,s
 */

extern char data_ov056_022604b0;
extern char data_020da13c;

extern void func_020ee62c(void *);
extern void func_020edf54(void *);

struct UnkStruct_0226046c {
    void *volatile unk_00;
};

void *func_ov056_0226046c(struct UnkStruct_0226046c *self)
{
    self->unk_00 = &data_ov056_022604b0;
    self->unk_00 = &data_020da13c;
    func_020ee62c(self);
    func_020edf54(self);
    return self;
}
