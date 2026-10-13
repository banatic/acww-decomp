/* func_ov103_0229d580 @ 0x0229d580, 0xe4 bytes, Thumb, module ov103
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0229d580_2 UnkStruct_0229d580;
struct UnkStruct_0229d580_2 {
    unsigned char pad_00[0x8c];
    unsigned char unk_8C;
    unsigned char pad_8D[0x218c - 0x8d];
    int unk_218C;
    unsigned char pad_2190[0x2da4 - 0x2190];
    unsigned char unk_2DA4;
};

extern int func_ov002_02208014(UnkStruct_0229d580 *self);
extern int func_ov002_02208008(UnkStruct_0229d580 *self);
extern void func_ov002_02207d24(void *ptr, int value);
extern void func_ov002_02207d00(void *ptr);
extern void func_ov002_022080a0(UnkStruct_0229d580 *self, int value);

extern int func_ov103_0229c350(UnkStruct_0229d580 *self, int a, int b);
extern void func_ov103_0229cffc(UnkStruct_0229d580 *self);
extern void func_ov103_0229ca48(UnkStruct_0229d580 *self);
extern void func_ov103_0229c774(UnkStruct_0229d580 *self);
extern int func_ov103_0229cc3c(UnkStruct_0229d580 *self, unsigned char byte);
extern int func_ov103_0229cdfc(UnkStruct_0229d580 *self, unsigned char byte);
extern int func_ov103_0229cc08(UnkStruct_0229d580 *self, unsigned char byte);
extern void func_ov103_0229c444(UnkStruct_0229d580 *self, unsigned char byte);
extern void func_ov103_0229c7ec(UnkStruct_0229d580 *self);
extern void func_ov103_0229c2d4(UnkStruct_0229d580 *self, int value);

extern volatile unsigned short data_021fbe40[2];

void func_ov103_0229d580(UnkStruct_0229d580 *self)
{
    if (func_ov002_02208014(self) != 0) {
        func_ov103_0229cffc(self);
        func_ov002_02207d24(&self->unk_218C, 1);
        return;
    }

    if (func_ov103_0229c350(self, func_ov002_02208008(self), 0) != 0) {
        func_ov103_0229ca48(self);
        func_ov103_0229c774(self);
        func_ov002_02207d24(&self->unk_218C, 0);
        return;
    }

    if (func_ov103_0229cc3c(self, self->unk_2DA4) == 0 && (data_021fbe40[1] & 1) != 0) {
        if (func_ov103_0229cdfc(self, self->unk_2DA4) == 0) {
            return;
        }
        if (func_ov103_0229cc08(self, self->unk_2DA4) == 0) {
            func_ov103_0229c444(self, self->unk_2DA4);
        }
        return;
    }

    if ((data_021fbe40[1] & 0x800) != 0) {
        self->unk_8C = 3;
        func_ov002_022080a0(self, 1);
        func_ov002_02207d24(&self->unk_218C, 1);
        func_ov103_0229c7ec(self);
        func_ov103_0229c2d4(self, 0x100);
        return;
    }

    func_ov002_02207d00(&self->unk_218C);
}
