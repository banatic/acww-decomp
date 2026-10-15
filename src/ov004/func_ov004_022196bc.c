/* func_ov004_022196bc @ 0x022196bc, 0x2c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int data_ov004_02252248;
extern unsigned int data_ov004_022522f4;
extern void *func_ov004_02210cf0(void *self);
extern void func_ov004_02211518(void *self);

typedef struct {
    unsigned int unk_00;
    unsigned char pad_04[0xe8];
    unsigned int unk_EC;
} UnkStruct_022196bc;

UnkStruct_022196bc *func_ov004_022196bc(UnkStruct_022196bc *self)
{
    self->unk_00 = (unsigned int) &data_ov004_02252248;
    self->unk_EC = (unsigned int) &data_ov004_022522f4;
    func_ov004_02210cf0(self);
    func_ov004_02211518(self);
    return self;
}
