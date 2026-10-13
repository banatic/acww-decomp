/* func_ov003_0221edd0 @ 0x0221edd0, 0x24 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov009_0226552c(void *self);
extern int data_ov003_02239754;
extern int data_ov003_02239818;

struct UnkStruct_0221edd0 {
    void *unk_00;
    char pad_04[0xe8];
    void *unk_EC;
};

struct UnkStruct_0221edd0 *func_ov003_0221edd0(struct UnkStruct_0221edd0 *self)
{
    func_ov009_0226552c(self);
    self->unk_00 = &data_ov003_02239754;
    self->unk_EC = &data_ov003_02239818;
    return self;
}
