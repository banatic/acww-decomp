/* func_ov144_022995fc @ 0x022995fc, 0x64 bytes, Thumb, module ov144
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_0220ba0c(void *);
extern void func_02138c48(void *, int, int, void *);
extern void func_ov002_0220afdc(void *);
extern void func_ov002_0220a5e4(void *);
extern void func_ov002_02209cb4(void *);
extern void func_ov002_0220826c(void *);
extern void func_ov002_02207f6c(void *);

typedef struct {
    unsigned int unk_00;
    unsigned char pad_04[192];
    unsigned int unk_C4;
    unsigned char pad_C8[96];
    unsigned int unk_128;
    unsigned char pad_12C[68];
    unsigned int unk_170;
    unsigned char pad_174[456];
    unsigned int unk_33C;
    unsigned char pad_340[1040];
    unsigned int unk_750;
} UnkStruct_022995fc;

extern void func_02070be8(void);

extern unsigned char data_ov144_0229b3f8[];

UnkStruct_022995fc *func_ov144_022995fc(UnkStruct_022995fc *self)
{
    self->unk_00 = (unsigned int) data_ov144_0229b3f8;
    func_ov002_0220ba0c(&self->unk_750);
    func_02138c48(&self->unk_33C, 9, 0x6c, (void *) func_02070be8);
    func_ov002_0220afdc(&self->unk_170);
    func_ov002_0220a5e4(&self->unk_128);
    func_ov002_02209cb4(&self->unk_C4);
    func_ov002_0220826c(self);
    func_ov002_02207f6c(self);
    return self;
}
