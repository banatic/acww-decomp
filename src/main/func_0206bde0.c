/* func_0206bde0 @ 0x0206bde0, 0x8c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020a9484(void *);
extern void func_020a8754(void *);
extern void *func_0206bffc(void *, int, int);

struct UnkStruct_0206bde0 {
    int unk_00;
    char pad_04[0x20];
    int unk_24;
    int unk_28;
    int unk_2C;
    int unk_30;
    int unk_34;
    void *unk_38;
    char pad_3C[0x10];
    char unk_4C;
    char unk_4D;
    char unk_4E;
    char unk_4F;
    int unk_50;
    int unk_54;
    int unk_58;
    int unk_5C;
    char unk_60[0x3c];
    char unk_9C[0x3c];
    char unk_D8;
    char unk_D9;
    char pad_DA[2];
    int unk_DC;
    int unk_E0;
};

extern unsigned char data_020defe4[];
extern unsigned char data_020e3e68[];

struct UnkStruct_0206bde0 *func_0206bde0(struct UnkStruct_0206bde0 *self, int a, int b)
{
    func_020a9484(self);
    self->unk_00 = (int) (unsigned int) data_020e3e68;
    self->unk_00 = (int) (unsigned int) data_020defe4;
    self->unk_24 = a;
    self->unk_28 = b;
    self->unk_2C = 0;
    self->unk_30 = 0;
    self->unk_34 = 0;
    func_020a8754(&self->unk_38);
    self->unk_4C = 0;
    self->unk_4D = 0;
    self->unk_4E = 0;
    self->unk_4F = 0;
    self->unk_50 = 0;
    self->unk_54 = 0;
    self->unk_58 = 0;
    self->unk_5C = 0;
    func_0206bffc(self->unk_60, a, b);
    func_0206bffc(self->unk_9C, a, b);
    self->unk_D8 = 0;
    self->unk_D9 = 0;
    self->unk_DC = 0;
    self->unk_E0 = 0;
    return self;
}
