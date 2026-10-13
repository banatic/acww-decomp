/* func_ov003_0221cac4 @ 0x0221cac4, 0x38 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_ov003_02238b10;
extern unsigned char data_ov003_02238bd4;
extern void func_020565b0(void *);
extern void func_ov009_0226539c(void *);
extern void func_ov003_0221ca98(void *);

struct UnkStruct_0221cac4 {
    void *unk_00;
    char pad_04[0xec - 4];
    void *unk_EC;
    char pad_F0[0x2b8 - 0xec - 4];
    unsigned char unk_2B8[1];
};

void *func_ov003_0221cac4(struct UnkStruct_0221cac4 *self)
{
    self->unk_00 = &data_ov003_02238b10;
    self->unk_EC = &data_ov003_02238bd4;
    func_020565b0(self->unk_2B8);
    func_ov009_0226539c(self);
    func_ov003_0221ca98(self);
    return self;
}
