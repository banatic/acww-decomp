/* func_ov004_02215468 @ 0x02215468, 0x2c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int data_ov004_02252ba8;
extern unsigned int data_ov004_02252c54;
extern void func_ov004_02210cf0(void *self);
extern void func_ov004_02211518(void *self);

typedef struct {
    unsigned int unk_00;
    unsigned char pad_04[0xe8];
    unsigned int unk_EC;
} UnkStruct_02215468;

UnkStruct_02215468 *func_ov004_02215468(UnkStruct_02215468 *self)
{
    self->unk_00 = (unsigned int) &data_ov004_02252ba8;
    self->unk_EC = (unsigned int) &data_ov004_02252c54;
    func_ov004_02210cf0(self);
    func_ov004_02211518(self);
    return self;
}
