/* func_ov004_02215b18 @ 0x02215b18, 0x2c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int data_ov004_02250f88;
extern unsigned int data_ov004_02251034;
extern void *func_ov004_02215e70(void *self);
extern void func_ov004_02211518(void *self);

typedef struct {
    unsigned int unk_00;
    unsigned char pad_04[0xe8];
    unsigned int unk_EC;
} UnkStruct_02215b18;

UnkStruct_02215b18 *func_ov004_02215b18(UnkStruct_02215b18 *self)
{
    self->unk_00 = (unsigned int) &data_ov004_02250f88;
    self->unk_EC = (unsigned int) &data_ov004_02251034;
    func_ov004_02215e70(self);
    func_ov004_02211518(self);
    return self;
}
