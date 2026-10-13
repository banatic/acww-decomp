/* func_ov004_022192d8 @ 0x022192d8, 0x2c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int data_ov004_022518e8;
extern unsigned int data_ov004_02251994;
extern void func_ov004_02210cf0(void *self);
extern void func_ov004_02211518(void *self);

typedef struct {
    unsigned int unk_00;
    unsigned char pad_04[0xe8];
    unsigned int unk_EC;
} UnkStruct_022192d8;

UnkStruct_022192d8 *func_ov004_022192d8(UnkStruct_022192d8 *self)
{
    self->unk_00 = (unsigned int) &data_ov004_022518e8;
    self->unk_EC = (unsigned int) &data_ov004_02251994;
    func_ov004_02210cf0(self);
    func_ov004_02211518(self);
    return self;
}
