/* func_0206d5c0 @ 0x0206d5c0, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0206d5c0 {
    void *unk_00;
    char pad_04[0x2C];
    void *unk_30;
};

extern char data_020def7c;
extern void func_020a8fb8(void *ptr);
extern void func_020a9260(struct UnkStruct_0206d5c0 *self);

struct UnkStruct_0206d5c0 *func_0206d5c0(struct UnkStruct_0206d5c0 *self)
{
    self->unk_00 = &data_020def7c;
    if (self->unk_30 != 0) {
        func_020a8fb8(self->unk_30);
    }
    func_020a9260(self);
    return self;
}
