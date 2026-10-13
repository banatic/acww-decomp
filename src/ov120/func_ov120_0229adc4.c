/* func_ov120_0229adc4 @ 0x0229adc4, 0xb4 bytes, Thumb, module ov120
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0xa8];
    unsigned char unk_A8;
    unsigned char unk_A9;
} UnkStruct_0229adc4;

extern void func_ov120_0229a8e8(UnkStruct_0229adc4 *self);
extern void func_ov120_0229a904(UnkStruct_0229adc4 *self);
extern unsigned char func_ov120_0229acf4(UnkStruct_0229adc4 *self, unsigned int idx);
extern unsigned char func_ov120_0229ac8c(UnkStruct_0229adc4 *self, unsigned int idx);
extern void func_ov120_0229a428(UnkStruct_0229adc4 *self, unsigned int val);
extern int func_ov120_0229a448(UnkStruct_0229adc4 *self, unsigned int val);
extern void func_ov120_0229b22c(UnkStruct_0229adc4 *self);
extern void func_ov120_0229ac60(UnkStruct_0229adc4 *self);
extern void func_ov120_0229b214(UnkStruct_0229adc4 *self);
extern void func_ov120_0229a438(UnkStruct_0229adc4 *self, unsigned int val);
extern void func_ov120_0229ac08(UnkStruct_0229adc4 *self);
extern void func_ov120_0229ad5c(UnkStruct_0229adc4 *self, unsigned char val);

void func_ov120_0229adc4(UnkStruct_0229adc4 *self, unsigned int idx)
{
    if (idx == 0) {
        self->unk_A8 = 0xe;
        self->unk_A9 = 0xe;
        func_ov120_0229a8e8(self);
        return;
    }
    func_ov120_0229a904(self);
    self->unk_A9 = func_ov120_0229acf4(self, idx);
    self->unk_A8 = func_ov120_0229ac8c(self, idx);
    if (idx >= 1 && idx < 0xf) {
        func_ov120_0229a428(self, 0x200);
        if (func_ov120_0229a448(self, 1)) {
            if (idx >= 1 && idx <= 9) {
                func_ov120_0229b22c(self);
                func_ov120_0229ac60(self);
                return;
            }
        } else {
            if (idx < 1 || idx > 9) {
                func_ov120_0229b214(self);
                func_ov120_0229ac60(self);
                return;
            }
        }
    } else {
        func_ov120_0229a438(self, 0x200);
    }
    func_ov120_0229ac08(self);
    func_ov120_0229ad5c(self, 0xe);
    func_ov120_0229ad5c(self, self->unk_A9);
}
