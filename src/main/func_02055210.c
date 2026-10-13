/* func_02055210 @ 0x02055210, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    void *vtable;
    char pad_04[0x98];
    int *unk_9C;
    char pad_A0[4];
    int unk_A4;
    int unk_A8;
    int unk_AC;
    char pad_B0[4];
    int unk_B4;
} UnkStruct_02055210;

extern void func_020557a0(UnkStruct_02055210 *self);
extern int data_020dd184;
extern int data_020dd05c;
extern int data_020dd06c;

UnkStruct_02055210 *func_02055210(UnkStruct_02055210 *self)
{
    func_020557a0(self);
    self->unk_9C = &data_020dd184;
    self->unk_A4 = 0;
    self->unk_A8 = 0;
    self->unk_AC = 0x1000;
    self->vtable = &data_020dd05c;
    self->unk_9C = &data_020dd06c;
    self->unk_B4 = 0;
    return self;
}
