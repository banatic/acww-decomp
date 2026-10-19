/* func_ov140_0229a6dc @ 0x0229a6dc, 0x60 bytes, Thumb, module ov140
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229a6dc {
    char pad_00[0xa8];
    int unk_A8;
    char pad_AC[0x8db - 0xac];
    unsigned char unk_8DB;
    unsigned char pad_8DC;
    unsigned char unk_8DD;
    unsigned char unk_8DE;
};

extern void func_ov140_02299fa0(struct UnkStruct_0229a6dc *self, int n);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov140_02299fc8(struct UnkStruct_0229a6dc *self);
extern void func_ov140_0229a3fc(struct UnkStruct_0229a6dc *self, int n);
extern void func_0200467c(int n);

void func_ov140_0229a6dc(struct UnkStruct_0229a6dc *self)
{
    func_ov140_02299fa0(self, 0x20);
    func_ov002_02208098((void *) (self), 6);
    self->unk_8DB = 5;
    self->unk_8DD = self->unk_8DD + 1;
    if (self->unk_8DD > self->unk_8DE) {
        self->unk_8DD = 0;
    }
    func_ov140_02299fc8(self);
    self->unk_A8 = 0xa;
    func_ov140_0229a3fc(self, -1);
    func_0200467c(0xc);
}
