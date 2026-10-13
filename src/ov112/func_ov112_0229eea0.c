/* func_ov112_0229eea0 @ 0x0229eea0, 0x8c bytes, Thumb, module ov112
 * mwccarm 1.2/base -O4,s
 */

extern char data_ov112_022a20d0;

extern void func_02078040(void *);
extern void func_020780b8(void *);
extern void func_ov002_02209cb4(void *);
extern void func_ov002_0220afdc(void *);
extern void func_ov002_0220a5e4(void *);
extern void func_02138c48(void *, int, int, void *);
extern void func_ov002_0220ba0c(void *);
extern void func_ov002_0220826c(void *);

struct UnkStruct_0229eea0 {
    void *unk_00;
    char pad_04[0x240];
    char unk_244[0x2490];
    char unk_26D4[0x18d8];
    char unk_3FAC[0x288];
    char unk_4234[0x48];
    char unk_427C[0x1cc];
    char unk_4448[0x64];
    char unk_44AC[0xd4];
    char unk_4580[1];
};

extern void func_02070be8(void);

void *func_ov112_0229eea0(struct UnkStruct_0229eea0 *self)
{
    self->unk_00 = (void *) &data_ov112_022a20d0;
    func_02078040(&self->unk_4580);
    func_020780b8(&self->unk_44AC);
    func_ov002_02209cb4(&self->unk_4448);
    func_ov002_0220afdc(&self->unk_427C);
    func_ov002_0220a5e4(&self->unk_4234);
    func_02138c48(&self->unk_3FAC, 6, 0x6c, (void *) func_02070be8);
    func_02138c48(&self->unk_26D4, 2, 0x6c, (void *) func_02070be8);
    func_ov002_0220ba0c(&self->unk_244);
    func_ov002_0220826c(self);
    return self;
}
