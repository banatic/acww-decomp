/* func_ov105_0229d908 @ 0x0229d908, 0x68 bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0229d908 UnkStruct_0229d908;
struct UnkStruct_0229d908 {
    unsigned char pad_00[0x2b4];
    unsigned char unk_2B4;
    unsigned char pad_2B5[0x2b7 - 0x2b5];
    unsigned char unk_2B7;
    unsigned char unk_2B8;
    unsigned char unk_2B9;
    unsigned char pad_2BA[0x2bd - 0x2ba];
    unsigned char unk_2BD;
    unsigned char pad_2BE[0x2c0 - 0x2be];
    unsigned char unk_2C0;
    unsigned char pad_2C1[0x23bc - 0x2c1];
    unsigned char unk_23BC;
};

extern void func_ov002_02207d24(void *p, int a);
extern void func_ov105_0229d0f8(UnkStruct_0229d908 *self, unsigned char v);
extern void func_ov105_0229d17c(UnkStruct_0229d908 *self);
extern void func_ov094_022999c0(void);

void func_ov105_0229d908(UnkStruct_0229d908 *self, unsigned char value)
{
    self->unk_2B7 = value;
    self->unk_2B9 = value;
    self->unk_2B8 = self->unk_2C0;
    func_ov002_02207d24(&self->unk_23BC, 1);
    func_ov105_0229d0f8(self, value);
    if (self->unk_2B4 == 1) {
        self->unk_2BD = 8;
    }
    func_ov105_0229d17c(self);
    func_ov094_022999c0();
}
