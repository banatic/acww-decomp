/* func_ov102_0229e130 @ 0x0229e130, 0x94 bytes, Thumb, module ov102
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov094_0229af40(void *ptr, int val);
extern void func_ov094_0229bbd8(void *ptr, int val);
extern void func_ov094_0229a2b0(void *ptr, int val);
extern void func_ov002_02209e18(void *ptr);
extern void func_020984e8(void);
extern void func_0209898c(void);
extern int func_0203a674(void);
extern void MI_CpuCopy8(int a, void *b, int c);
extern void func_0206fb58(void);

struct UnkStruct_0229e130 {
    char pad_00[0xcc];
    void *unk_CC;
    char pad_D0[0xb2c - (0xcc + 4)];
    void *unk_B2C;
    char pad_B30[0xb54 - (0xb2c + 4)];
    void *unk_B54;
    char pad_B58[0x225c - (0xb54 + 4)];
    void *unk_225C;
    char pad_2260[0x24cc - (0x225c + 4)];
    int unk_24CC;
    char pad_24D0[0x24e8 - (0x24cc + 4)];
    void *unk_24E8;
    char pad_24EC[0x259f - (0x24e8 + 4)];
    char unk_259F;
    char pad_25A0[0x25a1 - (0x259f + 1)];
    char unk_25A1;
    char pad_25A2[0x25a5 - (0x25a1 + 1)];
    char unk_25A5;
    char pad_25A6[0x25a8 - (0x25a5 + 1)];
    char unk_25A8;
    char pad_25A9[0x25aa - (0x25a8 + 1)];
    char unk_25AA;
};

void func_ov102_0229e130(struct UnkStruct_0229e130 *self)
{
    self->unk_24CC = 0;
    func_ov094_0229af40(&self->unk_CC, 1);
    func_ov094_0229bbd8(&self->unk_B2C, 2);
    func_ov094_0229a2b0(&self->unk_B54, 6);
    self->unk_25A1 = 0x25;
    func_ov002_02209e18(&self->unk_225C);
    self->unk_259F = 0;
    self->unk_25A5 = 0;
    self->unk_25A8 = 0;
    func_020984e8();
    func_0209898c();
    MI_CpuCopy8(func_0203a674(), &self->unk_24E8, 0xb4);
    func_0206fb58();
    self->unk_25AA = 0;
}
