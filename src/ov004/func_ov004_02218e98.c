/* func_ov004_02218e98 @ 0x02218e98, 0x2c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int data_ov004_022510b4;
extern unsigned int data_ov004_02251160;
extern void *func_ov004_02210cf0(void *self);
extern void func_ov004_02211518(void *self);

typedef struct {
    unsigned int unk_00;
    unsigned char pad_04[0xe8];
    unsigned int unk_EC;
} UnkStruct_02218e98;

UnkStruct_02218e98 *func_ov004_02218e98(UnkStruct_02218e98 *self)
{
    self->unk_00 = (unsigned int) &data_ov004_022510b4;
    self->unk_EC = (unsigned int) &data_ov004_02251160;
    func_ov004_02210cf0(self);
    func_ov004_02211518(self);
    return self;
}
