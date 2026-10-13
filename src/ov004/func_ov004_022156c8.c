/* func_ov004_022156c8 @ 0x022156c8, 0x2c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int data_ov004_02250c04;
extern unsigned int data_ov004_02250cb0;
extern void func_ov004_02210cf0(void *self);
extern void func_ov004_02211518(void *self);

typedef struct {
    unsigned int unk_00;
    unsigned char pad_04[0xe8];
    unsigned int unk_EC;
} UnkStruct_022156c8;

UnkStruct_022156c8 *func_ov004_022156c8(UnkStruct_022156c8 *self)
{
    self->unk_00 = (unsigned int) &data_ov004_02250c04;
    self->unk_EC = (unsigned int) &data_ov004_02250cb0;
    func_ov004_02210cf0(self);
    func_ov004_02211518(self);
    return self;
}
