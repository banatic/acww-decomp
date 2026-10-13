/* func_0203d528 @ 0x0203d528, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_020da97c;
extern void func_020a8188(void *self);

struct UnkStruct_0203d528 {
    void *unk_00;
};

struct UnkStruct_0203d528 *func_0203d528(struct UnkStruct_0203d528 *self)
{
    self->unk_00 = (void *) &data_020da97c;
    func_020a8188(self);
    return self;
}
