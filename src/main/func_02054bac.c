/* func_02054bac @ 0x02054bac, 0x80 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02054e8c(void *self);
extern void func_02056ee0(void *self);

extern int data_020dd0ac;
extern int data_020dd0bc;
extern int data_020dd0cc;
extern int data_020dd184;

typedef struct UnkStruct_02054bac {
    int *unk_00;
    char pad_04[0x98];
    int *unk_9C;
    char pad_A0[0x18];
    int *unk_B8;
    char pad_BC[0x38];
    int unk_F4;
    int *unk_F8;
    char pad_FC[0x4];
    int unk_100;
    int unk_104;
    int unk_108;
    char pad_10C[0x4];
    char sub110;
    char pad_111[0x3b];
    int unk_14C;
    int unk_150;
} UnkStruct_02054bac;

UnkStruct_02054bac *func_02054bac(UnkStruct_02054bac *self)
{
    func_02054e8c(self);
    self->unk_00 = &data_020dd0ac;
    self->unk_9C = &data_020dd0bc;
    self->unk_B8 = &data_020dd0cc;
    self->unk_F8 = &data_020dd184;
    self->unk_100 = 0;
    self->unk_104 = 0;
    self->unk_108 = 0x1000;
    func_02056ee0(&self->sub110);
    self->unk_F4 = 0;
    self->unk_14C = 0;
    self->unk_150 = 0;
    return self;
}
