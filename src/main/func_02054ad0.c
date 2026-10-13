/* func_02054ad0 @ 0x02054ad0, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned int unk_00;
    char pad_04[0x98];
    unsigned int unk_9C;
    char pad_A0[0x18];
    unsigned int unk_B8;
    char pad_BC[0x3c];
    unsigned int unk_F8;
    char pad_FC[0x14];
    unsigned int unk_110;
} UnkStruct_02054ad0;
extern void func_02056ed4(void *p);
extern void func_02057078(void *p);
extern void func_02054d9c(void *p);
extern unsigned char data_020dd0ac[];
extern unsigned char data_020dd0bc[];
extern unsigned char data_020dd0cc[];

UnkStruct_02054ad0 *func_02054ad0(UnkStruct_02054ad0 *self)
{
    self->unk_00 = (unsigned int) data_020dd0ac;
    self->unk_9C = (unsigned int) data_020dd0bc;
    self->unk_B8 = (unsigned int) data_020dd0cc;
    func_02056ed4(&self->unk_110);
    func_02057078(&self->unk_F8);
    func_02054d9c(self);
    return self;
}
