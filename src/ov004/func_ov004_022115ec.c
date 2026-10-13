/* func_ov004_022115ec @ 0x022115ec, 0x2c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int data_ov004_022526f8;
extern unsigned int data_ov004_022527a4;
extern void func_ov004_02210cf0(void *self);
extern void func_ov004_02211518(void *self);

typedef struct {
    unsigned int unk_00;
    unsigned char pad_04[0xe8];
    unsigned int unk_EC;
} UnkStruct_022115ec;

UnkStruct_022115ec *func_ov004_022115ec(UnkStruct_022115ec *self)
{
    self->unk_00 = (unsigned int) &data_ov004_022526f8;
    self->unk_EC = (unsigned int) &data_ov004_022527a4;
    func_ov004_02210cf0(self);
    func_ov004_02211518(self);
    return self;
}
