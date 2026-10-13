/* func_ov003_0221cafc @ 0x0221cafc, 0x34 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_020565b0(void *p);
extern void func_ov009_0226539c(void *p);
extern int data_ov003_02238b10;
extern int data_ov003_02238bd4;

struct UnkStruct_0221cafc_2 {
    char pad_00;
};

struct UnkStruct_0221cafc {
    void *unk_00;
    char pad_04[0xe8];
    void *unk_EC;
    char pad_F0[0x1c8];
    struct UnkStruct_0221cafc_2 sub;
};

struct UnkStruct_0221cafc *func_ov003_0221cafc(struct UnkStruct_0221cafc *self)
{
    self->unk_00 = (void *) &data_ov003_02238b10;
    self->unk_EC = (void *) &data_ov003_02238bd4;
    func_020565b0(&self->sub);
    func_ov009_0226539c(self);
    return self;
}
