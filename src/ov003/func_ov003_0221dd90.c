/* func_ov003_0221dd90 @ 0x0221dd90, 0x2c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0221dd90 {
    void *unk_00;
    unsigned char pad_04[0xe8];
    void *unk_EC;
} UnkStruct_0221dd90;

extern char data_ov003_02239254;
extern char data_ov003_02239318;
extern void func_ov009_0226539c(UnkStruct_0221dd90 *self);
extern void func_020edf54(UnkStruct_0221dd90 *self);

UnkStruct_0221dd90 *func_ov003_0221dd90(UnkStruct_0221dd90 *self)
{
    self->unk_00 = &data_ov003_02239254;
    self->unk_EC = &data_ov003_02239318;
    func_ov009_0226539c(self);
    func_020edf54(self);
    return self;
}
