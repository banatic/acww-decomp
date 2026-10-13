/* func_ov004_02211bf0 @ 0x02211bf0, 0x2c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int data_ov004_02252950;
extern unsigned int data_ov004_022529fc;
extern void func_ov004_02210cf0(void *self);
extern void func_ov004_02211518(void *self);

typedef struct {
    unsigned int unk_00;
    unsigned char pad_04[0xe8];
    unsigned int unk_EC;
} UnkStruct_02211bf0;

UnkStruct_02211bf0 *func_ov004_02211bf0(UnkStruct_02211bf0 *self)
{
    self->unk_00 = (unsigned int) &data_ov004_02252950;
    self->unk_EC = (unsigned int) &data_ov004_022529fc;
    func_ov004_02210cf0(self);
    func_ov004_02211518(self);
    return self;
}
