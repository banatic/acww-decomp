/* func_ov003_0221c394 @ 0x0221c394, 0x24 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern char data_ov003_022387a8;
extern char data_ov003_0223886c;

struct UnkStruct_0221c394;

extern void func_ov009_0226539c(struct UnkStruct_0221c394 *self);

struct UnkStruct_0221c394 {
    void *unk_00;
    char pad_04[0xe8];
    void *unk_EC;
};

struct UnkStruct_0221c394 *func_ov003_0221c394(struct UnkStruct_0221c394 *self)
{
    self->unk_00 = &data_ov003_022387a8;
    self->unk_EC = &data_ov003_0223886c;
    func_ov009_0226539c(self);
    return self;
}
