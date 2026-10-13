/* func_0206f4bc @ 0x0206f4bc, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_020df548;
extern char data_020da13c;
extern void func_020ee62c(void *self);
extern void func_020edf54(void *self);

struct UnkStruct_0206f4bc {
    void *volatile unk_00;
};

struct UnkStruct_0206f4bc *func_0206f4bc(struct UnkStruct_0206f4bc *self)
{
    self->unk_00 = &data_020df548;
    self->unk_00 = &data_020da13c;
    func_020ee62c(self);
    func_020edf54(self);
    return self;
}
