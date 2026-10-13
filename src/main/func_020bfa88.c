/* func_020bfa88 @ 0x020bfa88, 0x90 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern signed char data_020d22c4[];
extern int func_020644cc(int);
extern int func_020644b4(int);

struct UnkStruct_020bfa88 {
    char pad_00[0x0c];
    int unk_0C;
    char pad_10[0x24];
    int unk_34;
    int unk_38;
    int unk_3C;
    int unk_40;
    int unk_44;
    int unk_48;
    char pad_4C[0x0c];
    int unk_58;
    char pad_5C[4];
    int unk_60;
    int unk_64;
    char pad_68[4];
    int unk_6C;
    int unk_70;
};

void func_020bfa88(struct UnkStruct_020bfa88 *self, int arg)
{
    int temp;

    self->unk_60 = arg;
    self->unk_64 = data_020d22c4[arg & 3] + 0x14;
    self->unk_0C = 0x2c;
    self->unk_58 = 2;
    temp = (func_020644cc(0x38) + 0x90) << 12;
    self->unk_34 = -0x8000;
    self->unk_38 = temp;
    self->unk_3C = 0;
    self->unk_40 = 0x1000;
    self->unk_44 = 0x2000;
    self->unk_48 = 0;
    self->unk_40 += func_020644b4(0x8000);
    self->unk_44 -= func_020644b4(0x2000);
    self->unk_6C = -0x666;
    self->unk_70 = 0xcd;
    self->unk_6C += 0x8cd;
    self->unk_70 -= 0x666;
}
