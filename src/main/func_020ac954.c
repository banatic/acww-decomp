/* func_020ac954 @ 0x020ac954, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020ac8a8(void *self);
extern char data_020e3fb4;

struct UnkStruct_020ac954 {
    void *unk_00;
};

struct UnkStruct_020ac954 *func_020ac954(struct UnkStruct_020ac954 *self)
{
    self->unk_00 = &data_020e3fb4;
    func_020ac8a8(self);
    return self;
}
