/* func_ov146_0229a6dc @ 0x0229a6dc, 0x48 bytes, Thumb, module ov146
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229a6dc {
    unsigned char pad_00[0xB0];
    unsigned char unk_B0;
    unsigned char pad_B1[9];
    unsigned char unk_BA;
    unsigned char unk_BB;
};

extern void func_0206fc4c(int);
extern void func_0206fc80(int);
extern void func_ov146_02299660(struct UnkStruct_0229a6dc *, int);
extern void func_ov002_02208090(struct UnkStruct_0229a6dc *, int);
extern unsigned char *func_ov002_02208098(struct UnkStruct_0229a6dc *, unsigned char value);
extern void func_0200467c(int);

void func_ov146_0229a6dc(struct UnkStruct_0229a6dc *self)
{
    func_0206fc4c(1);
    func_0206fc80(self->unk_BB);
    self->unk_B0 = 10;
    func_ov146_02299660(self, 0x40);
    self->unk_BA = 5;
    func_ov002_02208090(self, 2);
    func_ov002_02208098(self, 9);
    func_0200467c(0x27);
}
