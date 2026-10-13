/* func_ov004_02214070 @ 0x02214070, 0x2c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int data_ov004_02252374;
extern unsigned int data_ov004_02252420;
extern void func_ov004_02210cf0(void *self);
extern void func_ov004_02211518(void *self);

typedef struct {
    unsigned int unk_00;
    unsigned char pad_04[0xe8];
    unsigned int unk_EC;
} UnkStruct_02214070;

UnkStruct_02214070 *func_ov004_02214070(UnkStruct_02214070 *self)
{
    self->unk_00 = (unsigned int) &data_ov004_02252374;
    self->unk_EC = (unsigned int) &data_ov004_02252420;
    func_ov004_02210cf0(self);
    func_ov004_02211518(self);
    return self;
}
