/* func_ov131_0229acc0 @ 0x0229acc0, 0x38 bytes, Thumb, module ov131
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    void *unk_00;
    char pad_04[0x90];
    char unk_94[4];
    char pad_98[0x60];
    char unk_F8[4];
    char pad_FC[0x1c8];
    char unk_2C4[4];
} UnkStruct_0229acc0;

extern void *func_ov130_0229a790(void *);
extern void *func_ov002_0220afdc(void *);
extern void *func_ov002_02209cb4(void *);
extern void *func_ov002_0220826c(void *);

extern unsigned char data_ov131_0229b8f0[];

void *func_ov131_0229acc0(UnkStruct_0229acc0 *self)
{
    self->unk_00 = (void *) data_ov131_0229b8f0;
    func_ov130_0229a790(&self->unk_2C4);
    func_ov002_0220afdc(&self->unk_F8);
    func_ov002_02209cb4(&self->unk_94);
    func_ov002_0220826c(self);
    return self;
}
